/*
 * $Id$
 */
/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston,
    MA 02111-1307, USA.
*/

#include <exec/types.h>
#include <exec/resident.h>
#include <exec/io.h>
#include <exec/ports.h>
#include <exec/errors.h>

#include <aros/io.h>

#include <devices/sana2.h>
#include <devices/sana2specialstats.h>
#include <devices/newstyle.h>
#include <devices/timer.h>

#include <utility/utility.h>
#include <utility/tagitem.h>
#include <utility/hooks.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/oop.h>
#include <proto/timer.h>
#include <proto/utility.h>

#include <stdlib.h>
#include <stdio.h>

#include "e1000_hw.h"
#include "e1000_api.h"
#include "e1000_defines.h"
#include "unit.h"
#include LC_LIBDEFS_FILE

/*
 * Report incoming events to all hyphotetical event receivers
 */
VOID ReportEvents(struct e1000Base *e1KBase, struct e1000Unit *unit, ULONG events)
{
    struct IOSana2Req *request, *tail, *next_request;
    struct List *list;

    list = &unit->e1ku_request_ports[EVENT_QUEUE]->mp_MsgList;
    next_request = (APTR)list->lh_Head;
    tail = (APTR)&list->lh_Tail;

    /* Go through list of event listeners. If send messages to receivers if event found */
    Disable();
    while(next_request != tail)
    {
        request = next_request;
        next_request = (APTR)request->ios2_Req.io_Message.mn_Node.ln_Succ;

        if((request->ios2_WireError&events) != 0)
        {
            request->ios2_WireError = events;
            Remove((APTR)request);
            ReplyMsg((APTR)request);
        }
    }
    Enable();

    return;
}

struct TypeStats *FindTypeStats(struct e1000Base *e1KBase, struct e1000Unit *unit, 
                    struct MinList *list, ULONG packet_type)
{
    struct TypeStats *stats, *tail;
    BOOL found = FALSE;

    stats = (APTR)list->mlh_Head;
    tail = (APTR)&list->mlh_Tail;

    while(stats != tail && !found)
    {
        if(stats->packet_type == packet_type)
            found = TRUE;
        else
            stats = (APTR)stats->node.mln_Succ;
    }

    if(!found)
        stats = NULL;

    return stats;
}

void FlushUnit(LIBBASETYPEPTR LIBBASE, struct e1000Unit *unit, UBYTE last_queue, BYTE error)
{
    struct IORequest *request;
    UBYTE i;
    struct Opener *opener, *tail;

D(bug("[%s] unit.FlushUnit\n", unit->e1ku_name));

    /* Abort queued operations */

    for (i=0; i <= last_queue; i++)
    {
        while ((request = (APTR)GetMsg(unit->e1ku_request_ports[i])) != NULL)
        {
            request->io_Error = IOERR_ABORTED;
            ReplyMsg((struct Message *)request);
        }
    }

    opener = (APTR)unit->e1ku_Openers.mlh_Head;
    tail = (APTR)&unit->e1ku_Openers.mlh_Tail;

    /* Flush every opener's read queue */

    while(opener != tail)
    {
        while ((request = (APTR)GetMsg(&opener->read_port)) != NULL)
        {
            request->io_Error = error;
            ReplyMsg((struct Message *)request);
        }
        opener = (struct Opener *)opener->node.mln_Succ;
    }
}

/*
 * Interrupt generated by Cause() to push new packets into the NIC interface
 */
static AROS_INTH1(e1000func_TX_Int, struct e1000Unit *,  unit)
{
    AROS_INTFUNC_INIT

    struct e1000Base *e1KBase = unit->e1ku_device;
	struct e1000_tx_ring *tx_ring = &unit->e1ku_txRing[0];
	struct e1000_tx_desc *tx_desc = NULL;
	struct e1000_buffer *buffer_info;
    struct eth_frame *frame;
    struct IOSana2Req *request;
    struct Opener *opener;
    struct MsgPort *port;
    struct TypeStats *tracker;
    int tx_flags = E1000_TX_FLAGS_IPV4;
	unsigned int i;
	ULONG txd_upper = 0, txd_lower = E1000_TXD_CMD_IFCS;
    UWORD packet_size, data_size;
    UBYTE *buffer, error;
    ULONG wire_error=0;
    BOOL proceed = FALSE;

D(bug("[%s]: ## e1000func_TX_Int()\n", unit->e1ku_name));

	if (tx_flags & E1000_TX_FLAGS_TSO) {
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D |
		             E1000_TXD_CMD_TSE;
		txd_upper |= E1000_TXD_POPTS_TXSM << 8;

		if (tx_flags & E1000_TX_FLAGS_IPV4)
			txd_upper |= E1000_TXD_POPTS_IXSM << 8;
	}

	if (tx_flags & E1000_TX_FLAGS_CSUM) {
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D;
		txd_upper |= E1000_TXD_POPTS_TXSM << 8;
	}

	if (tx_flags & E1000_TX_FLAGS_VLAN) {
		txd_lower |= E1000_TXD_CMD_VLE;
		txd_upper |= (tx_flags & E1000_TX_FLAGS_VLAN_MASK);
	}

	i = tx_ring->next_to_use;

    proceed = TRUE; /* Success by default */
    port = unit->e1ku_request_ports[WRITE_QUEUE];

D(bug("[%s]: ## e1000func_TX_Int: nxt to use = %d, write queue port @ %p\n", unit->e1ku_name, i, port));

    while(proceed && (!IsMsgPortEmpty(port)))
    {
        error = 0;
        request = (APTR)port->mp_MsgList.lh_Head;
        data_size = packet_size = request->ios2_DataLength;

        opener = (APTR)request->ios2_BufferManagement;

        buffer_info = &tx_ring->buffer_info[i];

        if ((buffer_info->buffer = AllocMem(ETH_MAXPACKETSIZE, MEMF_PUBLIC|MEMF_CLEAR)) != NULL)
        {
            frame = buffer_info->buffer;

            if ((buffer_info->dma = HIDD_PCIDriver_CPUtoPCI(unit->e1ku_PCIDriver, buffer_info->buffer)) == NULL)
            {
D(bug("[%s]: e1000func_TX_Int: Failed to Map Tx DMA buffer\n", unit->e1ku_name));
            }
            else
            {
D(bug("[%s]: e1000func_TX_Int: Tx DMA buffer %d @ %p\n", unit->e1ku_name, i, buffer_info->dma));
            }

            if((request->ios2_Req.io_Flags & SANA2IOF_RAW) == 0)
            {
                packet_size += ETH_PACKET_DATA;
                CopyMem(request->ios2_DstAddr, frame->eth_packet_dest, ETH_ADDRESSSIZE);
                CopyMem(unit->e1ku_dev_addr, frame->eth_packet_source, ETH_ADDRESSSIZE);
                frame->eth_packet_type = AROS_WORD2BE(request->ios2_PacketType);

                buffer = frame->eth_packet_data;
            }
            else
                buffer = (UBYTE *)frame;

            if (!opener->tx_function(buffer, request->ios2_Data, data_size))
            {
                error = S2ERR_NO_RESOURCES;
                wire_error = S2WERR_BUFF_ERROR;
                ReportEvents(LIBBASE, unit,
                    S2EVENT_ERROR | S2EVENT_SOFTWARE | S2EVENT_BUFF
                    | S2EVENT_TX);
            }

            /* Now the packet is already in TX buffer, update flags for NIC */
            if (error == 0)
            {
                Disable();
D(bug("[%s]: e1000func_TX_Int: packet %d [type = %d] queued for transmission.\n", unit->e1ku_name, i, AROS_BE2WORD(frame->eth_packet_type)));

              /* DEBUG? Dump frame if so */
#ifdef DEBUG
                {
                    int j;
                    D(bug("[%s]: Tx Buffer %d Packet Dump -:", unit->e1ku_name, i));
                    for (j=0; j<64; j++) {
                        if ((j%16) == 0)
                            D(bug("\n[%s]:     %03x:", unit->e1ku_name, j));
                        D(bug(" %02x", ((unsigned char*)frame)[j]));
                    }
                    D(bug("\n"));
                }
#endif
                Enable();

                /* Set the ring details for the packet .. */
                buffer_info->length = packet_size;

                tx_desc = E1000_TX_DESC(tx_ring, i);
                tx_desc->buffer_addr = (IPTR)buffer_info->dma;
                tx_desc->lower.data = AROS_WORD2LE(txd_lower | buffer_info->length);
                tx_desc->upper.data = AROS_WORD2LE(txd_upper);
                tx_desc->lower.data |= AROS_WORD2LE(unit->txd_cmd);
		MMIO_W32((APTR)(((struct e1000_hw *)unit->e1ku_Private00)->hw_addr + tx_ring->tdt), i);
            }
        }

        buffer_info->next_to_watch = i;

        if (++i == tx_ring->count) i = 0;

        /* Reply packet */
        request->ios2_Req.io_Error = error;
        request->ios2_WireError = wire_error;
        Disable();
        Remove((APTR)request);
        Enable();
        ReplyMsg((APTR)request);

        /* Update statistics */
        if(error == 0)
        {
            tracker = FindTypeStats(LIBBASE, unit, &unit->e1ku_type_trackers, request->ios2_PacketType);

            if(tracker != NULL)
            {
                tracker->stats.PacketsSent++;
                tracker->stats.BytesSent += packet_size;
            }
        }
	}

	tx_ring->next_to_use = i;

	return 0;

    AROS_INTFUNC_EXIT
}

/*
 * Watchdog Interupt
 */
AROS_INTH1(e1000func_WatchdogHandler,struct e1000Unit *,unit)
{
    AROS_INTFUNC_INIT

    struct Device *TimerBase = unit->e1ku_TimerSlowReq->tr_node.io_Device;
    struct timeval time;

    GetSysTime(&time);
//D(bug("[%s]: ## e1000func_WatchdogHandler()\n", unit->e1ku_name));

    /*
     * If timeout timer is expected, and time elapsed - regenerate the 
     * interrupt handler 
     */
    if (unit->e1ku_toutNEED && (CmpTime(&time, &unit->e1ku_toutPOLL ) < 0))
    {
        unit->e1ku_toutNEED = FALSE;
        //Cause(&unit->e1ku_tx_end_int);
    }

    return FALSE;

    AROS_INTFUNC_EXIT
}

/*
 * The interrupt handler - schedules code execution to proper handlers depending
 * on the message from e1000.
 * 
 * NOTE.
 * 
 * Don't be surprised - this driver used to restart itself several times, in
 * order to handle events which occur when the driver was handling previous
 * events. It reduces the latency and amount of dropped packets. Additionally, 
 * this interrupt may put itself into deep sleep (or just quit) and restarts 
 * after certain amount of time (POLL_WAIT).
 */
AROS_INTH1(e1000func_IntHandler,struct e1000Unit *,unit)
{
    AROS_INTFUNC_INIT

    struct Device *TimerBase = unit->e1ku_TimerSlowReq->tr_node.io_Device;
    struct timeval time;
	int rx_cleaned, tx_cleaned, i, j;

	ULONG icr = E1000_READ_REG((struct e1000_hw *)unit->e1ku_Private00, E1000_ICR);

D(bug("[%s]: e1000func_IntHandler(status %x): ", unit->e1ku_name, icr));

	if (!icr)
    {
D(bug("Skipping\n"));
		return FALSE;  /* Not our interrupt */
    }

D(bug("Processing ..\n"));
    GetSysTime(&time);
	if (((struct e1000_hw *)unit->e1ku_Private00)->mac.type == e1000_82547 || ((struct e1000_hw *)unit->e1ku_Private00)->mac.type == e1000_82547_rev_2)
		E1000_WRITE_REG((struct e1000_hw *)unit->e1ku_Private00, E1000_IMC, ~0);

//	adapter->total_tx_bytes = 0;
//	adapter->total_rx_bytes = 0;
//	adapter->total_tx_packets = 0;
//	adapter->total_rx_packets = 0;

	for (i = 0; i < E1000_MAX_INTR; i++) {
		rx_cleaned = 0;
		for (j = 0; j < unit->e1ku_rxRing_QueueSize; j++)
			rx_cleaned |= e1000func_clean_rx_irq(unit, &unit->e1ku_rxRing[j]);

		tx_cleaned = 0;
		for (j = 0 ; j < unit->e1ku_txRing_QueueSize ; j++)
			tx_cleaned |= e1000func_clean_tx_irq(unit, &unit->e1ku_txRing[j]);

		if (!rx_cleaned && !tx_cleaned)
			break;
	}

//	if (adapter->itr_setting & 3)
//		e1000_set_itr(adapter);
    
	if (((struct e1000_hw *)unit->e1ku_Private00)->mac.type == e1000_82547 || ((struct e1000_hw *)unit->e1ku_Private00)->mac.type == e1000_82547_rev_2)
		e1000func_irq_enable(unit);    

   return 0;
 
   AROS_INTFUNC_EXIT
}

VOID CopyPacket(struct e1000Base *e1KBase, struct e1000Unit *unit, 
    struct IOSana2Req *request, UWORD packet_size, UWORD packet_type,
    struct eth_frame *buffer)
{
    struct Opener *opener;
    BOOL filtered = FALSE;
    UBYTE *ptr;
    const UBYTE broadcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

D(bug("[%s]: CopyPacket(packet @ %x, len = %d)\n", unit->e1ku_name, buffer, packet_size));

    /* Set multicast and broadcast flags */

    request->ios2_Req.io_Flags &= ~(SANA2IOF_BCAST | SANA2IOF_MCAST);
    if(memcmp(buffer->eth_packet_dest, broadcast, ETH_ADDRESSSIZE) == 0)
    {
       request->ios2_Req.io_Flags |= SANA2IOF_BCAST;
D(bug("[%s]: CopyPacket: BROADCAST Flag set\n", unit->e1ku_name));
    }
    else if((buffer->eth_packet_dest[0] & 0x1) != 0)
    {
       request->ios2_Req.io_Flags |= SANA2IOF_MCAST;
D(bug("[%s]: CopyPacket: MULTICAST Flag set\n", unit->e1ku_name));
    }

    /* Set source and destination addresses and packet type */
    CopyMem(buffer->eth_packet_source, request->ios2_SrcAddr, ETH_ADDRESSSIZE);
    CopyMem(buffer->eth_packet_dest, request->ios2_DstAddr, ETH_ADDRESSSIZE);
    request->ios2_PacketType = packet_type;

    /* Adjust for cooked packet request */

    if((request->ios2_Req.io_Flags & SANA2IOF_RAW) == 0)
    {
        packet_size -= ETH_PACKET_DATA;
        ptr = (UBYTE*)&buffer->eth_packet_data[0];
    }
    else
    {
        ptr = (UBYTE*)buffer;
    }

    request->ios2_DataLength = packet_size;

D(bug("[%s]: CopyPacket: packet @ %x (%d bytes)\n", unit->e1ku_name, ptr, packet_size));

    /* Filter packet */

    opener = request->ios2_BufferManagement;
    if((request->ios2_Req.io_Command == CMD_READ) &&
        (opener->filter_hook != NULL))
        if(!CallHookPkt(opener->filter_hook, request, ptr))
        {
D(bug("[%s]: CopyPacket: packet filtered\n", unit->e1ku_name));
            filtered = TRUE;
        }

    if(!filtered)
    {
        /* Copy packet into opener's buffer and reply packet */
D(bug("[%s]: CopyPacket: opener recieve packet .. ", unit->e1ku_name));
        if(!opener->rx_function(request->ios2_Data, ptr, packet_size))
        {
D(bug("ERROR occured!!\n"));
            request->ios2_Req.io_Error = S2ERR_NO_RESOURCES;
            request->ios2_WireError = S2WERR_BUFF_ERROR;
            ReportEvents(LIBBASE, unit, S2EVENT_ERROR | S2EVENT_SOFTWARE | S2EVENT_BUFF | S2EVENT_RX);
        }
        else
        {
D(bug("SUCCESS!!\n"));
        }
        Disable();
        Remove((APTR)request);
        Enable();
        ReplyMsg((APTR)request);
D(bug("[%s]: CopyPacket: opener notified.\n", unit->e1ku_name));
    }
}

BOOL AddressFilter(struct e1000Base *e1KBase, struct e1000Unit *unit, UBYTE *address)
{
    struct AddressRange *range, *tail;
    BOOL accept = TRUE;
    const UBYTE broadcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

    /* Check whether address is unicast/broadcast or multicast */

    if((address[0] & 0x01) != 0 && memcmp(address, broadcast, ETH_ADDRESSSIZE) != 0)
    {
        /* Check if this multicast address is wanted */

        range = (APTR)unit->e1ku_multicast_ranges.mlh_Head;
        tail = (APTR)&unit->e1ku_multicast_ranges.mlh_Tail;
        accept = FALSE;

        while((range != tail) && !accept)
        {
            if ((memcmp(address, range->lower_bound, ETH_ADDRESSSIZE) >= 0) &&
                (memcmp(address, range->upper_bound, ETH_ADDRESSSIZE) <= 0))
                accept = TRUE;
            range = (APTR)range->node.mln_Succ;
        }

        if(!accept)
            unit->e1ku_special_stats[S2SS_ETHERNET_BADMULTICAST & 0xffff]++;
    }
    return accept;
}

/*
 * Unit process
 */
AROS_UFH3(void, e1000func_Schedular,
    AROS_UFHA(STRPTR,              argPtr, A0),
    AROS_UFHA(ULONG,               argSize, D0),
    AROS_UFHA(struct ExecBase *,   SysBase, A6))
{
    AROS_USERFUNC_INIT

    struct e1000Startup *sm_UD = FindTask(NULL)->tc_UserData;
    struct e1000Unit *unit = sm_UD->e1ksm_Unit;

    LIBBASETYPEPTR LIBBASE = unit->e1ku_device;
    struct MsgPort *reply_port, *input;

D(bug("[%s] e1000func_Schedular()\n", unit->e1ku_name));
D(bug("[%s] e1000func_Schedular: Setting device up\n", unit->e1ku_name));

    reply_port = CreateMsgPort();
    input = CreateMsgPort();

    unit->e1ku_input_port = input; 

    unit->e1ku_TimerSlowPort = CreateMsgPort();

    if (unit->e1ku_TimerSlowPort)
    {
        unit->e1ku_TimerSlowReq = (struct timerequest *)
            CreateIORequest((struct MsgPort *)unit->e1ku_TimerSlowPort, sizeof(struct timerequest));

        if (unit->e1ku_TimerSlowReq)
        {
            if (!OpenDevice("timer.device", UNIT_VBLANK,
                (struct IORequest *)unit->e1ku_TimerSlowReq, 0))
            {
                struct Message *msg = AllocVec(sizeof(struct Message), MEMF_PUBLIC|MEMF_CLEAR);
                ULONG sigset;

D(bug("[%s] e1000func_Schedular: Got VBLANK unit of timer.device\n", unit->e1ku_name));

                e1000func_reset(unit);

                msg->mn_ReplyPort = reply_port;
                msg->mn_Length = sizeof(struct Message);

D(bug("[%s] e1000func_Schedular: Setup complete. Sending handshake\n", unit->e1ku_name));
                PutMsg(sm_UD->e1ksm_SyncPort, msg);
                WaitPort(reply_port);
                GetMsg(reply_port);

                FreeVec(msg);

D(bug("[%s] e1000func_Schedular: entering forever loop ... \n", unit->e1ku_name));

                unit->e1ku_signal_0 = AllocSignal(-1);
                unit->e1ku_signal_1 = AllocSignal(-1);
                unit->e1ku_signal_2 = AllocSignal(-1);
                unit->e1ku_signal_3 = AllocSignal(-1);

                sigset = 1 << input->mp_SigBit  |
                         1 << unit->e1ku_signal_0  |
                         1 << unit->e1ku_signal_1  |
                         1 << unit->e1ku_signal_2  |
                         1 << unit->e1ku_signal_3;
                for(;;)
                {	
                    ULONG recvd = Wait(sigset);
                    if (recvd & unit->e1ku_signal_0)
                    {
                        /*
                         * Shutdown process. Driver should close everything 
                         * already and waits for our process to complete. Free
                         * memory allocared here and kindly return.
                         */
//                        unit->deinitialize(unit);
                        CloseDevice((struct IORequest *)unit->e1ku_TimerSlowReq);
                        DeleteIORequest((struct IORequest *)unit->e1ku_TimerSlowReq);
                        DeleteMsgPort(unit->e1ku_TimerSlowPort);
                        DeleteMsgPort(input);
                        DeleteMsgPort(reply_port);

D(bug("[%s] e1000func_Schedular: Process shutdown.\n", unit->e1ku_name));
                        return;
                    }
                    else if (recvd & (1 << input->mp_SigBit))
                    {
                        struct IOSana2Req *io;

                        /* Handle incoming transactions */
                        while ((io = (struct IOSana2Req *)GetMsg(input))!= NULL)
                        {
D(bug("[%s] e1000func_Schedular: Handle incomming transaction.\n", unit->e1ku_name));
                            ObtainSemaphore(&unit->e1ku_unit_lock);
                            handle_request(LIBBASE, io);
                        }
                    }
                    else
                    {
D(bug("[%s] e1000func_Schedular: Handle incomming signal.\n", unit->e1ku_name));
                        /* Handle incoming signals */
                    }
                }
            }
        }
    }

    AROS_USERFUNC_EXIT
}

/*
 * Create new e1000 ethernet device unit
 */
/* TODO: Handle cleanup on failure in CreateUnit more elegantly */
struct e1000Unit *CreateUnit(struct e1000Base *e1KBase, OOP_Object *pciDevice)
{
    struct e1000Unit *unit;
//	UWORD eeprom_data = 0;
//	UWORD eeprom_apme_mask = E1000_EEPROM_APME;
    BOOL success = TRUE;
    int i;

D(bug("[e1000] CreateUnit()\n"));

    if ((unit = AllocMem(sizeof(struct e1000Unit), MEMF_PUBLIC | MEMF_CLEAR)) != NULL)
    {
        IPTR                    DeviceID,
                                RevisionID,
                                BaseAddr,
                                BaseType,
                                BaseLen,
                                IOBase = (IPTR)NULL,
                                Flash_Base = (IPTR)NULL,
                                MMIO_Base = (IPTR)NULL,
                                Flash_Size = 0,
                                MMIO_Size = 0,
				PCIe_Cap = 0;
        OOP_Object              *driver;

        unit->e1ku_UnitNum = e1KBase->e1kb_UnitCount++;

        unit->e1ku_Sana2Info.HardwareType = S2WireType_Ethernet;
        unit->e1ku_Sana2Info.MTU = ETH_MTU;
        unit->e1ku_Sana2Info.AddrFieldSize = 8 * ETH_ADDRESSSIZE;

        if ((unit->e1ku_Private00 = (IPTR)AllocMem(sizeof(struct e1000_hw), MEMF_PUBLIC | MEMF_CLEAR)) == (IPTR)NULL)
        {
            FreeMem(unit, sizeof(struct e1000Unit));
            return NULL;
        }

        if ((unit->e1ku_hw_stats = (struct e1000_hw_stats *)AllocMem(sizeof(struct e1000_hw_stats), MEMF_PUBLIC | MEMF_CLEAR)) == NULL)
        {
            FreeMem((APTR)unit->e1ku_Private00, sizeof(struct e1000_hw));
            FreeMem(unit, sizeof(struct e1000Unit));
            return NULL;
        }

        ((struct e1000_hw *)unit->e1ku_Private00)->back = unit;
        
        if ((unit->e1ku_name = AllocVec(6 + (unit->e1ku_UnitNum/10) + 2, MEMF_PUBLIC | MEMF_CLEAR)) == NULL)
        {
            FreeMem(unit->e1ku_hw_stats, sizeof(struct e1000_hw_stats));
            FreeMem((APTR)unit->e1ku_Private00, sizeof(struct e1000_hw));
            FreeMem(unit, sizeof(struct e1000Unit));
            return NULL;
        }

        sprintf((char *)unit->e1ku_name, "e1000.%d", unit->e1ku_UnitNum);

        OOP_GetAttr(pciDevice, aHidd_PCIDevice_ProductID, &DeviceID);
        OOP_GetAttr(pciDevice, aHidd_PCIDevice_RevisionID, &RevisionID);
        OOP_GetAttr(pciDevice, aHidd_PCIDevice_Driver, (APTR)&driver);

	OOP_GetAttr(pciDevice, aHidd_PCIDevice_CapabilityPCIE, (APTR)&PCIe_Cap);
	
        unit->e1ku_device     = e1KBase;
        ((struct e1000_hw *)unit->e1ku_Private00)->device_id         = DeviceID;
        ((struct e1000_hw *)unit->e1ku_Private00)->revision_id       = RevisionID;

	unit->e1ku_PCIeCap = (UWORD)PCIe_Cap;

        unit->e1ku_mtu        = unit->e1ku_Sana2Info.MTU;
        unit->rx_buffer_len   = MAXIMUM_ETHERNET_VLAN_SIZE;
        unit->e1ku_frame_max  = unit->e1ku_mtu + ETH_HEADERSIZE + ETH_CRCSIZE;
        unit->e1ku_frame_min  = 60 + ETH_CRCSIZE;

        unit->e1ku_PCIDevice  = pciDevice;
        unit->e1ku_PCIDriver  = driver;

        InitSemaphore(&unit->e1ku_unit_lock);
        NEWLIST(&unit->e1ku_Openers);
        NEWLIST(&unit->e1ku_multicast_ranges);
        NEWLIST(&unit->e1ku_type_trackers);

        OOP_GetAttr(pciDevice, aHidd_PCIDevice_INTLine, &unit->e1ku_IRQ);
D(bug("[%s] CreateUnit: Device IRQ  : %d\n", unit->e1ku_name, unit->e1ku_IRQ));

        for (i = 1; i <= 5; i++)
        {
            OOP_GetAttr(pciDevice, aHidd_PCIDevice_Base0 + (i * 3), &BaseAddr);
            OOP_GetAttr(pciDevice, aHidd_PCIDevice_Type0 + (i * 3), &BaseType);
            OOP_GetAttr(pciDevice, aHidd_PCIDevice_Size0 + (i * 3), &BaseLen);
            if ((BaseAddr != (IPTR)NULL) && (BaseLen > 0))
            {
                if (BaseType & ADDRF_IO)
                {
                    IOBase = BaseAddr;
D(bug("[%s] CreateUnit: Device IO @ %p [%d bytes]\n", unit->e1ku_name, IOBase, BaseLen));
                }
                else
                {
                    Flash_Base = BaseAddr;
                    Flash_Size = BaseLen;
D(bug("[%s] CreateUnit: Device Flash @ %p [%d bytes]\n", unit->e1ku_name, Flash_Base, Flash_Size));
                }
            }
        }

        OOP_GetAttr(pciDevice, aHidd_PCIDevice_Base0, &MMIO_Base);
        OOP_GetAttr(pciDevice, aHidd_PCIDevice_Size0, &MMIO_Size);
D(bug("[%s] CreateUnit: Device MMIO @ %p\n", unit->e1ku_name, MMIO_Base));

        ((struct e1000_hw *)unit->e1ku_Private00)->io_base = (unsigned long)IOBase;
        ((struct e1000_hw *)unit->e1ku_Private00)->hw_addr = (UBYTE *)HIDD_PCIDriver_MapPCI(driver, (APTR)MMIO_Base, MMIO_Size);
        unit->e1ku_MMIOSize = MMIO_Size;

D(bug("[%s] CreateUnit: Mapped MMIO @ %p [%d bytes]\n", unit->e1ku_name, ((struct e1000_hw *)unit->e1ku_Private00)->hw_addr, unit->e1ku_MMIOSize));

        ((struct e1000_hw *)unit->e1ku_Private00)->flash_address = (UBYTE *)HIDD_PCIDriver_MapPCI(driver, (APTR)Flash_Base, Flash_Size);
        unit->e1ku_FlashSize = Flash_Size;

D(bug("[%s] CreateUnit: Mapped Flash Memory @ %p [%d bytes]\n", unit->e1ku_name, ((struct e1000_hw *)unit->e1ku_Private00)->flash_address, unit->e1ku_FlashSize));

        if ((((struct e1000_hw *)unit->e1ku_Private00)->io_base) && (((struct e1000_hw *)unit->e1ku_Private00)->hw_addr))
        {
            struct TagItem attrs[] = {
                { aHidd_PCIDevice_isIO,     TRUE },
                { aHidd_PCIDevice_isMEM,    TRUE },
                { aHidd_PCIDevice_isMaster, TRUE },
                { TAG_DONE,                 0    },
            };
            OOP_SetAttrs(pciDevice, (struct TagItem *)&attrs);

            unit->e1ku_DelayPort.mp_SigBit = SIGB_SINGLE;
            unit->e1ku_DelayPort.mp_Flags = PA_SIGNAL;
            unit->e1ku_DelayPort.mp_SigTask = FindTask(NULL);
            unit->e1ku_DelayPort.mp_Node.ln_Type = NT_MSGPORT;
            NEWLIST(&unit->e1ku_DelayPort.mp_MsgList);

            unit->e1ku_DelayReq.tr_node.io_Message.mn_ReplyPort = &unit->e1ku_DelayPort;
            unit->e1ku_DelayReq.tr_node.io_Message.mn_Length = sizeof(struct timerequest);

            OpenDevice((STRPTR)"timer.device", UNIT_MICROHZ, (struct IORequest *)&unit->e1ku_DelayReq, 0);

            /* Call e1000_api.c->e1000_setup_init_funcs */
            if (e1000_setup_init_funcs((struct e1000_hw *)unit->e1ku_Private00, FALSE) != E1000_SUCCESS)
            {
                /* Should never have loaded on this device */
D(bug("[%s] CreateUnit: Called on unsupported NIC type!!\n", unit->e1ku_name));
                e1KBase->e1kb_UnitCount = unit->e1ku_UnitNum;
                FreeVec(unit->e1ku_name);
                FreeMem((APTR)unit->e1ku_Private00, sizeof(struct e1000_hw));
                FreeMem(unit, sizeof(struct e1000Unit));
                return NULL;
            }

            D(bug("[%s] CreateUnit: Initialised Intel NIC functions..\n", unit->e1ku_name));

            unit->e1ku_txRing_QueueSize = 1;
            if ((unit->e1ku_txRing = AllocMem(sizeof(struct e1000_tx_ring) * unit->e1ku_txRing_QueueSize, MEMF_PUBLIC|MEMF_CLEAR)) == NULL)
            {
/* TODO: Handle Tx Queue allocation failure more elegantly! */
D(bug("[%s] CreateUnit: Failed to Allocate Tx Ring Queue!!!\n", unit->e1ku_name));
                return NULL;
            }
            D(bug("[%s] CreateUnit: Queue 0 TxRing @ %p\n", unit->e1ku_name, unit->e1ku_txRing));

            unit->e1ku_rxRing_QueueSize = 1;
            if ((unit->e1ku_rxRing = AllocMem(sizeof(struct e1000_rx_ring) * unit->e1ku_rxRing_QueueSize, MEMF_PUBLIC|MEMF_CLEAR)) == NULL)
            {
/* TODO: Handle Rx Queue allocation failure more elegantly! */
D(bug("[%s] CreateUnit: Failed to Allocate Rx Ring Queue!!!\n", unit->e1ku_name));
                return NULL;
            }
            D(bug("[%s] CreateUnit: Queue 0 RxRing @ %p\n", unit->e1ku_name, unit->e1ku_rxRing));

            e1000func_irq_disable(unit);
            D(bug("[%s] CreateUnit: e1000 IRQ disabled\n", unit->e1ku_name));

            if (e1000_init_mac_params((struct e1000_hw *)unit->e1ku_Private00) != E1000_SUCCESS)
            {
D(bug("[%s] CreateUnit: Failed to init mac params\n", unit->e1ku_name));
            }
            D(bug("[%s] CreateUnit: MAC Params Initialised\n", unit->e1ku_name));

            if (e1000_init_nvm_params((struct e1000_hw *)unit->e1ku_Private00) != E1000_SUCCESS)
            {
D(bug("[%s] CreateUnit: Failed to init nvm params\n", unit->e1ku_name));
            }
            D(bug("[%s] CreateUnit: NVM Params Initialised\n", unit->e1ku_name));

            if (e1000_init_phy_params((struct e1000_hw *)unit->e1ku_Private00) != E1000_SUCCESS)
            {
D(bug("[%s] CreateUnit: Failed to init phy params\n", unit->e1ku_name));
            }
            D(bug("[%s] CreateUnit: PHY Params Initialised\n", unit->e1ku_name));

            e1000_get_bus_info((struct e1000_hw *)unit->e1ku_Private00);

            D(bug("[%s] CreateUnit: Retrieved Bus information..\n", unit->e1ku_name));

            e1000_init_script_state_82541((struct e1000_hw *)unit->e1ku_Private00, TRUE);
            e1000_set_tbi_compatibility_82543((struct e1000_hw *)unit->e1ku_Private00, TRUE);

            D(bug("[%s] CreateUnit: 82541/82543 Setup complete\n", unit->e1ku_name));

            ((struct e1000_hw *)unit->e1ku_Private00)->phy.autoneg_wait_to_complete = FALSE;
            ((struct e1000_hw *)unit->e1ku_Private00)->mac.adaptive_ifs = TRUE;

            /* Copper options */

            if (((struct e1000_hw *)unit->e1ku_Private00)->phy.media_type == e1000_media_type_copper)
            {
                ((struct e1000_hw *)unit->e1ku_Private00)->phy.mdix = AUTO_ALL_MODES;
                ((struct e1000_hw *)unit->e1ku_Private00)->phy.disable_polarity_correction = FALSE;
                ((struct e1000_hw *)unit->e1ku_Private00)->phy.ms_type = E1000_MASTER_SLAVE;
            }

            if (e1000_check_reset_block((struct e1000_hw *)unit->e1ku_Private00))
            {
D(bug("[%s] CreateUnit: PHY reset is blocked due to SOL/IDER session.\n", unit->e1ku_name));
            }

            /* Hardware features, flags and workarounds */
            if (((struct e1000_hw *)unit->e1ku_Private00)->mac.type >= e1000_82540) {
                unit->e1ku_hwflags |= E1000_FLAG_HAS_SMBUS;
                unit->e1ku_hwflags |= E1000_FLAG_HAS_INTR_MODERATION;
            }

            if (((struct e1000_hw *)unit->e1ku_Private00)->mac.type == e1000_82543)
                unit->e1ku_hwflags |= E1000_FLAG_BAD_TX_CARRIER_STATS_FD;

            e1000_reset_hw((struct e1000_hw *)unit->e1ku_Private00);
            D(bug("[%s] CreateUnit: e1000 hardware reset\n", unit->e1ku_name));

            if (e1000_validate_nvm_checksum((struct e1000_hw *)unit->e1ku_Private00) < 0) {
D(bug("[%s] CreateUnit: Warning: The NVM Checksum Is Not Valid!\n", unit->e1ku_name));
                return NULL;
            }
            else
            {
                D(bug("[%s] CreateUnit: NVM Checksum validated succesfully\n", unit->e1ku_name));
            }
    
            /* copy the MAC address out of the NVM */

            if (e1000_read_mac_addr((struct e1000_hw *)unit->e1ku_Private00))
            {
D(bug("[%s] CreateUnit: NVM Read Error\n", unit->e1ku_name));
            }
            else
            {
                D(bug("[%s] CreateUnit: MAC Address Read\n", unit->e1ku_name));
            }
            memcpy(unit->e1ku_org_addr, ((struct e1000_hw *)unit->e1ku_Private00)->mac.addr, ETH_ADDRESSSIZE);
            memcpy(unit->e1ku_dev_addr, unit->e1ku_org_addr, ETH_ADDRESSSIZE);

D(bug("[%s] CreateUnit: MAC Address %02x:%02x:%02x:%02x:%02x:%02x\n", unit->e1ku_name,
            unit->e1ku_dev_addr[0], unit->e1ku_dev_addr[1], unit->e1ku_dev_addr[2],
            unit->e1ku_dev_addr[3], unit->e1ku_dev_addr[4], unit->e1ku_dev_addr[5]));

            {
D(bug("[%s] CreateUnit: (PCI%s:%s:%s)\n", unit->e1ku_name,
                ((((struct e1000_hw *)unit->e1ku_Private00)->bus.type == e1000_bus_type_pcix) ? "-X" :
                 (((struct e1000_hw *)unit->e1ku_Private00)->bus.type == e1000_bus_type_pci_express ? " Express":"")),
                ((((struct e1000_hw *)unit->e1ku_Private00)->bus.speed == e1000_bus_speed_2500) ? "2.5Gb/s" :
                 (((struct e1000_hw *)unit->e1ku_Private00)->bus.speed == e1000_bus_speed_133) ? "133MHz" :
                 (((struct e1000_hw *)unit->e1ku_Private00)->bus.speed == e1000_bus_speed_120) ? "120MHz" :
                 (((struct e1000_hw *)unit->e1ku_Private00)->bus.speed == e1000_bus_speed_100) ? "100MHz" :
                 (((struct e1000_hw *)unit->e1ku_Private00)->bus.speed == e1000_bus_speed_66) ? "66MHz" : "33MHz"),
                ((((struct e1000_hw *)unit->e1ku_Private00)->bus.width == e1000_bus_width_64) ? "64-bit" :
                 (((struct e1000_hw *)unit->e1ku_Private00)->bus.width == e1000_bus_width_pcie_x4) ? "Width x4" :
                 (((struct e1000_hw *)unit->e1ku_Private00)->bus.width == e1000_bus_width_pcie_x1) ? "Width x1" :
                 "32-bit")));
            }

            {
                struct Message *msg;

                unit->e1ku_irqhandler.is_Node.ln_Type = NT_INTERRUPT;
                unit->e1ku_irqhandler.is_Node.ln_Pri = 100;
                unit->e1ku_irqhandler.is_Node.ln_Name = LIBBASE->e1kb_Device.dd_Library.lib_Node.ln_Name;
                unit->e1ku_irqhandler.is_Code = (VOID_FUNC)e1000func_IntHandler;
                unit->e1ku_irqhandler.is_Data = unit;

                unit->e1ku_touthandler.is_Node.ln_Type = NT_INTERRUPT;
                unit->e1ku_touthandler.is_Node.ln_Pri = 100;
                unit->e1ku_touthandler.is_Node.ln_Name = LIBBASE->e1kb_Device.dd_Library.lib_Node.ln_Name;
                unit->e1ku_touthandler.is_Code = (VOID_FUNC)e1000func_WatchdogHandler;
                unit->e1ku_touthandler.is_Data = unit;

                unit->e1ku_tx_int.is_Node.ln_Type = NT_INTERRUPT;
                unit->e1ku_tx_int.is_Node.ln_Name = unit->e1ku_name;
                unit->e1ku_tx_int.is_Code = (VOID_FUNC)e1000func_TX_Int;
                unit->e1ku_tx_int.is_Data = unit;

                for (i = 0; i < REQUEST_QUEUE_COUNT; i++)
                {
                    struct MsgPort *port;

                    if ((port = AllocMem(sizeof(struct MsgPort), MEMF_PUBLIC | MEMF_CLEAR)) == NULL) success = FALSE;

                    if (success)
                    {
                        unit->e1ku_request_ports[i] = port;
                        NEWLIST(&port->mp_MsgList);
                        port->mp_Flags = PA_IGNORE;
                        port->mp_SigTask = &unit->e1ku_tx_int;
                    }
                }

                unit->e1ku_request_ports[WRITE_QUEUE]->mp_Flags = PA_SOFTINT;

                if (success)
                {
                    struct e1000Startup *sm_UD;
                    UBYTE tmpbuff[100];

                    if ((sm_UD = AllocMem(sizeof(struct e1000Startup), MEMF_PUBLIC | MEMF_CLEAR)) != NULL)
                    {
                        sprintf((char *)tmpbuff, e1000_TASK_NAME, unit->e1ku_name);

                        sm_UD->e1ksm_SyncPort = CreateMsgPort();
                        sm_UD->e1ksm_Unit = unit;

                        unit->e1ku_Process = CreateNewProcTags(
                                                NP_Entry, (IPTR)e1000func_Schedular,
                                                NP_Name, tmpbuff,
                                                NP_Synchronous , FALSE,
                                                NP_Priority, 0,
                                                NP_UserData, (IPTR)sm_UD,
                                                NP_StackSize, 140960,
                                                TAG_DONE);

                        WaitPort(sm_UD->e1ksm_SyncPort);
                        msg = GetMsg(sm_UD->e1ksm_SyncPort);
                        ReplyMsg(msg);
                        DeleteMsgPort(sm_UD->e1ksm_SyncPort);
                        FreeMem(sm_UD, sizeof(struct e1000Startup));

D(bug("[%s]  CreateUnit: Device Initialised. Unit %d @ %p\n", unit->e1ku_name, unit->e1ku_UnitNum, unit));
                        return unit;
                    }
                }
            }
        }
        else
        {
            if ((((struct e1000_hw *)unit->e1ku_Private00)->io_base) == 0)
            {
D(bug("[%s]  CreateUnit: PANIC! Couldn't find IO area. Aborting\n", unit->e1ku_name));
            }

            if ((((struct e1000_hw *)unit->e1ku_Private00)->hw_addr) == NULL)
            {
D(bug("[%s]  CreateUnit: PANIC! Couldn't get MMIO area. Aborting\n", unit->e1ku_name));
            }
        }
    }
    DeleteUnit(e1KBase, unit);	
    return NULL;
}

/*
 * DeleteUnit - removes selected unit. Frees all resources and structures.
 * 
 * The caller should be sure, that given unit is really ready to be freed.
 */

void DeleteUnit(struct e1000Base *e1KBase, struct e1000Unit *unit)
{
    int i;
    if (unit)
    {
        if (unit->e1ku_Process)
        {
            Signal(&unit->e1ku_Process->pr_Task, unit->e1ku_signal_0);
        }

        for (i=0; i < REQUEST_QUEUE_COUNT; i++)
        {
            if (unit->e1ku_request_ports[i] != NULL) 
                FreeMem(unit->e1ku_request_ports[i], sizeof(struct MsgPort));

            unit->e1ku_request_ports[i] = NULL;
        }

        if ((struct e1000_hw *)unit->e1ku_Private00)
        {
            if (((struct e1000_hw *)unit->e1ku_Private00)->hw_addr)
            {
                HIDD_PCIDriver_UnmapPCI(unit->e1ku_PCIDriver, 
                                        (APTR)((struct e1000_hw *)unit->e1ku_Private00)->hw_addr,
                                        unit->e1ku_MMIOSize);
            }
            FreeMem((APTR)unit->e1ku_Private00, sizeof(struct e1000_hw));
        }

        if (unit->e1ku_name)
            FreeVec(unit->e1ku_name);

        FreeMem(unit, sizeof(struct e1000Unit));
    }
}

static struct AddressRange *FindMulticastRange(LIBBASETYPEPTR LIBBASE, struct e1000Unit *unit, const UBYTE *lower_bound, const UBYTE *upper_bound)
{
    struct AddressRange *range, *tail;
    BOOL found = FALSE;

    range = (APTR)unit->e1ku_multicast_ranges.mlh_Head;
    tail = (APTR)&unit->e1ku_multicast_ranges.mlh_Tail;

    while((range != tail) && !found)
    {
        if (memcmp(lower_bound, range->lower_bound, ETH_ADDRESSSIZE) == 0 &&
            memcmp(upper_bound, range->upper_bound, ETH_ADDRESSSIZE) == 0)
            found = TRUE;
        else
            range = (APTR)range->node.mln_Succ;
    }

    if(!found)
        range = NULL;

    return range;
}

BOOL AddMulticastRange(LIBBASETYPEPTR LIBBASE, struct e1000Unit *unit, const UBYTE *lower_bound,
   const UBYTE *upper_bound)
{
    struct AddressRange *range;

    range = FindMulticastRange(LIBBASE, unit, lower_bound, upper_bound);

    if(range != NULL)
        range->add_count++;
    else
    {
        range = AllocMem(sizeof(struct AddressRange), MEMF_PUBLIC);
        if(range != NULL)
        {
            memcpy(range->lower_bound, lower_bound, ETH_ADDRESSSIZE);
            memcpy(range->upper_bound, upper_bound, ETH_ADDRESSSIZE);
            range->add_count = 1;

            Disable();
            AddTail((APTR)&unit->e1ku_multicast_ranges, (APTR)range);
            Enable();

            if (unit->e1ku_range_count++ == 0)
            {
                unit->e1ku_ifflags |= IFF_ALLMULTI;
                e1000func_set_multi(unit);
            }
        }
    }

    return range != NULL;
}

BOOL RemMulticastRange(LIBBASETYPEPTR LIBBASE, struct e1000Unit *unit, const UBYTE *lower_bound, const UBYTE *upper_bound)
{
    struct AddressRange *range;

    range = FindMulticastRange(LIBBASE, unit, lower_bound, upper_bound);

    if(range != NULL)
    {
        if(--range->add_count == 0)
        {
            Disable();
            Remove((APTR)range);
            Enable();
            FreeMem(range, sizeof(struct AddressRange));

            if (--unit->e1ku_range_count == 0)
            {
                unit->e1ku_ifflags &= ~IFF_ALLMULTI;
                e1000func_set_multi(unit);
            }
        }
    }
    return range != NULL;
}

