/*

Copyright (C) 2011-2012 Neil Cafferkey

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

#ifndef RHINE_H
#define RHINE_H


/* General */
/* ======= */

#define RH_DESCSIZE 0x10


/* Registers */
/* ========= */

#define RH_REG_ADDRESS       0x0
#define RH_REG_RXCONFIG      0x6
#define RH_REG_TXCONFIG      0x7
#define RH_REG_CONTROL       0x8
#define RH_REG_CONTROL1      0x9
#define RH_REG_INTSTATUS     0xc
#define RH_REG_INTMASK       0xe
#define RH_REG_MCASTFILTER  0x10
#define RH_REG_RXLIST       0x18
#define RH_REG_TXLIST       0x1c
#define RH_REG_MIICONFIG    0x6c
#define RH_REG_PCIBUSCONFIG 0x6e
#define RH_REG_MIICTRL      0x70
#define RH_REG_MIIREGNO     0x71
#define RH_REG_MIIDATA      0x72
#define RH_REG_EEPROM       0x74
#define RH_REG_MIIINTMASK   0x86


/* Interrupts */
/* ========== */

#define RH_INTB_TXERR  3
#define RH_INTB_RXERR  2
#define RH_INTB_TXOK   1
#define RH_INTB_RXOK   0

#define RH_INTF_TXERR (1 << RH_INTB_TXERR)
#define RH_INTF_RXERR (1 << RH_INTB_RXERR)
#define RH_INTF_TXOK  (1 << RH_INTB_TXOK)
#define RH_INTF_RXOK  (1 << RH_INTB_RXOK)


/* Register Details */
/* ================ */

/* RX Configuration Register */

#define RH_REG_RXCONFIGB_ALLUCAST 4
#define RH_REG_RXCONFIGB_BCAST    3
#define RH_REG_RXCONFIGB_MCAST    2

#define RH_REG_RXCONFIGF_ALLUCAST (1 << RH_REG_RXCONFIGB_ALLUCAST)
#define RH_REG_RXCONFIGF_BCAST    (1 << RH_REG_RXCONFIGB_BCAST)
#define RH_REG_RXCONFIGF_MCAST    (1 << RH_REG_RXCONFIGB_MCAST)

/* Control Register (0) */

#define RH_REG_CONTROLB_NOTXPOLL 11
#define RH_REG_CONTROLB_RXPOLL    6
#define RH_REG_CONTROLB_TXPOLL    5
#define RH_REG_CONTROLB_TXENABLE  4
#define RH_REG_CONTROLB_RXENABLE  3
#define RH_REG_CONTROLB_STOP      2
#define RH_REG_CONTROLB_START     1

#define RH_REG_CONTROLF_NOTXPOLL (1 << RH_REG_CONTROLB_NOTXPOLL)
#define RH_REG_CONTROLF_RXPOLL   (1 << RH_REG_CONTROLB_RXPOLL)
#define RH_REG_CONTROLF_TXPOLL   (1 << RH_REG_CONTROLB_TXPOLL)
#define RH_REG_CONTROLF_RXENABLE (1 << RH_REG_CONTROLB_RXENABLE)
#define RH_REG_CONTROLF_TXENABLE (1 << RH_REG_CONTROLB_TXENABLE)
#define RH_REG_CONTROLF_STOP     (1 << RH_REG_CONTROLB_STOP)
#define RH_REG_CONTROLF_START    (1 << RH_REG_CONTROLB_START)

/* Control Register 1 */

#define RH_REG_CONTROL1B_RESET    7

#define RH_REG_CONTROL1F_RESET    (1 << RH_REG_CONTROL1B_RESET)

/* MII Configuration Register */

#define RH_REG_MIICONFIGB_PHYADDR  0

#define RH_REG_MIICONFIGF_PHYADDR  (0x1f << RH_REG_MIICONFIGB_PHYADDR)

/* MII Control Register */

#define RH_REG_MIICTRLB_AUTOPOLL  7
#define RH_REG_MIICTRLB_READ      6
#define RH_REG_MIICTRLB_WRITE     5
#define RH_REG_MIICTRLB_NOPROGRAM 4
#define RH_REG_MIICTRLB_DIRECTION 3
#define RH_REG_MIICTRLB_DATAIN    2
#define RH_REG_MIICTRLB_DATAOUT   1
#define RH_REG_MIICTRLB_CLK       0

#define RH_REG_MIICTRLF_AUTOPOLL  (1 << RH_REG_MIICTRLB_AUTOPOLL)
#define RH_REG_MIICTRLF_READ      (1 << RH_REG_MIICTRLB_READ)
#define RH_REG_MIICTRLF_WRITE     (1 << RH_REG_MIICTRLB_WRITE)
#define RH_REG_MIICTRLF_NOPROGRAM (1 << RH_REG_MIICTRLB_PROGRAM)
#define RH_REG_MIICTRLF_DIRECTION (1 << RH_REG_MIICTRLB_DIRECTION)
#define RH_REG_MIICTRLF_DATAIN    (1 << RH_REG_MIICTRLB_DATAIN)
#define RH_REG_MIICTRLF_DATAOUT   (1 << RH_REG_MIICTRLB_DATAOUT)
#define RH_REG_MIICTRLF_CLK       (1 << RH_REG_MIICTRLB_CLK)

/* EEPROM Register */

#define RH_REG_EEPROMB_READY   7
#define RH_REG_EEPROMB_LOAD    5
#define RH_REG_EEPROMB_PROGRAM 4
#define RH_REG_EEPROMB_SELECT  3
#define RH_REG_EEPROMB_CLK     2
#define RH_REG_EEPROMB_DATAOUT 1
#define RH_REG_EEPROMB_DATAIN  0

#define RH_REG_EEPROMF_READY   (1 << RH_REG_EEPROMB_READY)
#define RH_REG_EEPROMF_LOAD    (1 << RH_REG_EEPROMB_LOAD)
#define RH_REG_EEPROMF_PROGRAM (1 << RH_REG_EEPROMB_PROGRAM)
#define RH_REG_EEPROMF_SELECT  (1 << RH_REG_EEPROMB_SELECT)
#define RH_REG_EEPROMF_CLK     (1 << RH_REG_EEPROMB_CLK)
#define RH_REG_EEPROMF_DATAOUT (1 << RH_REG_EEPROMB_DATAOUT)
#define RH_REG_EEPROMF_DATAIN  (1 << RH_REG_EEPROMB_DATAIN)


/* Frame descriptor */
/* ================ */

#define RH_DESC_TXSTATUS  0
#define RH_DESC_RXSTATUS  0
#define RH_DESC_TXCONTROL 1
#define RH_DESC_RXCONTROL 1
#define RH_DESC_DATA      2
#define RH_DESC_NEXT      3

/* TX Status field */

#define RH_DESC_TXSTATUSB_INUSE     31
#define RH_DESC_TXSTATUSB_TXERR     15
#define RH_DESC_TXSTATUSB_UNDERFLOW 11

#define RH_DESC_TXSTATUSF_INUSE     (1 << RH_DESC_TXSTATUSB_INUSE)
#define RH_DESC_TXSTATUSF_TXERR     (1 << RH_DESC_TXSTATUSB_TXERR)
#define RH_DESC_TXSTATUSF_UNDERFLOW (1 << RH_DESC_TXSTATUSB_UNDERFLOW)

/* RX Status field */

#define RH_DESC_RXSTATUSB_INUSE     31
#define RH_DESC_RXSTATUSB_LENGTH    16
#define RH_DESC_RXSTATUSB_OK        15
#define RH_DESC_RXSTATUSB_MCAST     13
#define RH_DESC_RXSTATUSB_BCAST     12
#define RH_DESC_RXSTATUSB_UCAST     11
#define RH_DESC_RXSTATUSB_CHAIN     10
#define RH_DESC_RXSTATUSB_FIRSTFRAG  9
#define RH_DESC_RXSTATUSB_LASTFRAG   8
#define RH_DESC_RXSTATUSB_BADRING    7
#define RH_DESC_RXSTATUSB_RUNT       5
#define RH_DESC_RXSTATUSB_LONG       4
#define RH_DESC_RXSTATUSB_OVERFLOW   3
#define RH_DESC_RXSTATUSB_BADALIGN   2
#define RH_DESC_RXSTATUSB_BADCRC     1
#define RH_DESC_RXSTATUSB_RXERR      0

#define RH_DESC_RXSTATUSF_INUSE     (1 << RH_DESC_RXSTATUSB_INUSE)
#define RH_DESC_RXSTATUSF_LENGTH    (0x7fff << RH_DESC_RXSTATUSB_LENGTH)
#define RH_DESC_RXSTATUSF_OK        (1 << RH_DESC_RXSTATUSB_OK)
#define RH_DESC_RXSTATUSF_MCAST     (1 << RH_DESC_RXSTATUSB_MCAST)
#define RH_DESC_RXSTATUSF_BCAST     (1 << RH_DESC_RXSTATUSB_BCAST)
#define RH_DESC_RXSTATUSF_UCAST     (1 << RH_DESC_RXSTATUSB_UCAST)
#define RH_DESC_RXSTATUSF_CHAIN     (1 << RH_DESC_RXSTATUSB_CHAIN)
#define RH_DESC_RXSTATUSF_FIRSTFRAG (1 << RH_DESC_RXSTATUSB_FIRSTFRAG)
#define RH_DESC_RXSTATUSF_LASTFRAG  (1 << RH_DESC_RXSTATUSB_LASTFRAG)
#define RH_DESC_RXSTATUSF_BADRING   (1 << RH_DESC_RXSTATUSB_BADRING)
#define RH_DESC_RXSTATUSF_RUNT      (1 << RH_DESC_RXSTATUSB_RUNT)
#define RH_DESC_RXSTATUSF_LONG      (1 << RH_DESC_RXSTATUSB_LONG)
#define RH_DESC_RXSTATUSF_OVERFLOW  (1 << RH_DESC_RXSTATUSB_OVERFLOW)
#define RH_DESC_RXSTATUSF_BADALIGN  (1 << RH_DESC_RXSTATUSB_BADALIGN)
#define RH_DESC_RXSTATUSF_BADCRC    (1 << RH_DESC_RXSTATUSB_BADCRC)
#define RH_DESC_RXSTATUSF_RXERR     (1 << RH_DESC_RXSTATUSB_RXERR)

/* TX Control field */

#define RH_DESC_TXCONTROLB_INT       23
#define RH_DESC_TXCONTROLB_LASTFRAG  22
#define RH_DESC_TXCONTROLB_FIRSTFRAG 21
#define RH_DESC_TXCONTROLB_NOCRC     16
#define RH_DESC_TXCONTROLB_CHAIN     15
#define RH_DESC_TXCONTROLB_LENGTH     0

#define RH_DESC_TXCONTROLF_INT       (1 << RH_DESC_TXCONTROLB_INT)
#define RH_DESC_TXCONTROLF_LASTFRAG  (1 << RH_DESC_TXCONTROLB_LASTFRAG)
#define RH_DESC_TXCONTROLF_FIRSTFRAG (1 << RH_DESC_TXCONTROLB_FIRSTFRAG)
#define RH_DESC_TXCONTROLF_NOCRC     (1 << RH_DESC_TXCONTROLB_NOCRC)
#define RH_DESC_TXCONTROLF_CHAIN     (1 << RH_DESC_TXCONTROLB_CHAIN)
#define RH_DESC_TXCONTROLF_LENGTH    (0x7fff << RH_DESC_TXCONTROLB_LENGTH)

#endif
