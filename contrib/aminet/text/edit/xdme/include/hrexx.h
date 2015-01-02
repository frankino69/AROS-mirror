#include <dos/dos.h>
#include <exec/types.h>
#ifndef Prototype
#define Prototype extern
#endif

/*********************************************************************/
/*      Die Funktion OpenRexx �ffnet, wenn m�glich einen RexxPort.   */
/*********************************************************************/

/*
 * OpenRexx     initialisiert die ARexxumgebung. Daf�r wird, wenn ben�tigt
 *      Arexxlibrary ge�ffnet, ein Port initialisiert, die Defaultextension
 *      festgelegt und die std Ein- und Ausgabekan�le bestimmt.
 *
 * --> name     Name des ARexxPorts den unser Programm bekommt.
 *              Existiert ein solcher Port bereits wird der FehlerCode
 *              ERROR_PORT_ALLREADY_EXISTS zur�ckgegeben
 * --> ext      Zeiger auf die extension, wenn NULL dan .REXX
 * --> do_res   Zeiger auf die Funktion zum Message handling.
 *              Wird aufgerufen wenn w�hrend der Arbeit ein RexxMsg anf�llt
 * --> in,out   std input/output handle
 * <-- RESLUT   SigBit   Success FALSE wenn nicht ge�ffnet
 */


/******************************************************************/
/*      beantwortet alle anstehenden Messages, mit RXRERRORIMGONE  */
/*      wartet auf alle noch zu beantwortenden Messages           */
/*      schlie�t den Port                                         */
/*      schlie�t die ArexxSysBase                                 */
/******************************************************************/


/********************************************************************/
/*      Mit dieser Funktion kann man den letzten aufegetreten       */
/*      FehlerCode festellen                                        */
/********************************************************************/


/****************************************************************/
/*      BuildRexxMsg erstellt eine ARexx Message und f�llt      */
/*      die Argument slots mit den Parametern                   */
/****************************************************************/
/*
 *      Aufruf erfolgt: BuildRexxMsg(com,flags,arg0,arg1,arg2,...,argn)
 *      Es d�rfen maximal 15 Argumente �bergeben werden. Weitere Argumente
 *      werden ignoriert. Will man nur 3 Argumente �bergeben (arg1-arg3)
 *      �bergibt man als letztes Argument (arg4) NULL
 *      Die Funktion gibt einen Zeiger auf die erstellte Message zur�ck,
 *      im Fehlerfalle NULL.
 */
   /*
    *      com ist der Name des aufzurufenden Kommandos.
    *      Alles Strings (com & args) sind normale mit NULL abgeschlo�ene
    *      C-Strings.
    */
   /*
    *      action dieses Flag wir direkt im Command (action) Field
    *      der RexxMessage struktur eingef�gt
    */
   /*
    *      first_arg is ein Zeiger auf das erste Argument (aufruf der
    *      Funktion s.o.
    *      Aufgrund der internen Handhabung wird nur der erste Parameter im
    *      Funktionskopf angenommen.
    *      Die Argumente sind normale 0-terminierte C-Strings
    */
   /*
    *      Weitere Argumente:
    */


/*****************************************************************/
/*      Dies Funktion gibt den Speicher einer RexxMessage frei.  */
/*      Also die Argumente, einen ggf vorhandenen ReturnWert     */
/*      und die Message selbst. Aus diesem Grund m��en Felder    */
/*      (Argumente und Return Code, wenn sie au�erhalb der       */
/*      Funktion freigegeben worden sind auf NULL gesetzt werden */
/*****************************************************************/
   /* Zeiger auf die zu l�schende RexxMessage */
   /*
    *      gibt TRUE f�r Erfolg zur�ck
    */


/****************************************************************/
/*      PutRexxMsg schickt eine Message an den genannten Port   */
/*      un �bernimmt die Buchf�hrung �ber fehlende Antworten    */
/****************************************************************/
   /*
    *      Port ist der Name des Ziel Ports. Der Name ist NULL beendeter
    *      String. Achtung !! kein PortPointer.
    *      Ist port NULL so wird die Message an den RexxHostPort geschickt.
    *      Da man einen eigenen Namen angeben kann, ist m�glich, Messages
    *      direkt an andere Rexxf�hige Programme zu senden.
    */
   /*
    *      rmsg    ist ein Zeiger auf g�ltige, vollst�nig initialisierte
    *      RexxMessage-Struktur.
    */


/****************************************************************/
/*      GetRexxMsg funktioniert GetMsg des Betriebsystems,      */
/*      nur das �ber die Messages Buchgef�hrt wird              */
/****************************************************************/
/*
 *      Die Funktion gibt einen Zeiger auf die Message oder NULL
 *      zur�ck.
 *      Ist NULL ein Fehler, so kann das mit LastRexxError festgestellt
 *      werden. Sonst bedeutet es einfach, das keine Msg am Port
 *      wartet.
 */


/****************************************************************/
/*      FetchRexxMsg wartet bis eine Message an unserm          */
/*      Port ankommt und gibt diese zur�ck.                     */
/****************************************************************/
/*
 *      Die Funktion kehrt mit einem Zeiger auf die vom
 *      Port geholte Message zur�ck.
 */


/****************************************************************/
/*      ReplyRexxMsg    setzt den ArexxErrorCode, f�llt den     */
/*      Returnwert_slot und beantwortet die Message.            */
/*      sollte es eine NonReply Message sein, so wird sie       */
/*      einfach gel�scht                                        */
/****************************************************************/
/*
 *      Im falle eines Fehlers kehrt die Funktion mit FALSE zur�ck.
 *      N�here Information kann man LastRexxError holen
 */
   /*
    *      rmsg    ist ein Zeiger auf die zu beantwortende Message
    */
   /*
    *      rexx_error ist ein Langwort, das den ArexxErrorCode enth�lt.
    *      Der Code wird in das Result1 Fe ld der Message eingetragen.
    */
   /*
    *      return_string ist ein String, der als Return wert and den
    *      Caller zur�ckgegeben wird. ReplyRexxMsg generiert aus diesem
    *      C-String ein ArexxArgument un f�llt dies in das Result2
    *      Feld ein.
    *      Ist rexx_error != 0, also ein Fehler aufgetreten, so wird der
    *      String ignoriert und das Feld auf NULL gesetz. Soll kein
    *      Returnwert zur�ckgegeben werden ist ein NULL-Pointer zu �bergeben.
    */


/**********************************************************************/
/*      SyncRexxCommand sendet ein Kommando, und wartet bis das       */
/*      Kommando abgearbeitet ist. Sollten in der Zwischenzeit        */
/*      Kommandos an unser Port gehen, wird die Funktion              */
/*      process_message mit dem Zeiger auf die Message aufgerufen.    */
/*      So ist es m�glich, w�hren eines SyncAufrufes Kommandos zu     */
/*      Empfangen. SyncRexxCommand unterst�tzt einen returncode.      */
/*      Dazu mu� eine StringBuffer und die Gr��e des Buffer �ber-     */
/*      geben werden .                                                */
/*      Der aufruf erfolgt:                                           */
/*      SyncRexxCommand(port,com,result,result_len,arg1,arg2,...,argn)*/
/*      Werden nicht alle Argumente genutzt, mu� das letzte Argument  */
/*      NULL sein. Mehr als 15 Argumente werden ignoriert.            */
/**********************************************************************/
/*
 *      Die Funktion kehrt mit dem ArexxErrorCode oder dem Internen
 *      errorcode zur�ck.
 *      0 f�r eine erfolgreiche aktion.
 *      Kommt es zu einem RexxFehler, so wird der ResultString gel�scht.
 */
   /*
    *      port ist der Name des Ports an den das Kommando gesendet werden soll.
    *      wird als PortName 0 angegeben, so wird das Kommando an den Rexx-
    *      Host geschickt.
    */
   /*
    *      Com ist der String der den KommandoNamen enth�lt
    */
   /*
    *      result ist ein Pointer auf den StringBuffer in den der
    *      ResultString des Kommandos kopiert werden soll. Ist result == NULL
    *      oder result_len == NULL so wird die Fukntion als Kommando
    *      ohne ReturnWert betrachtet, und die Flags in der RexxMsg
    *      entsprechend gesetzt.
    */
   /*
    *      first_arg Zeiger auf den ersten Argument String. Der aufruf Syntax
    *      ist oben beschrieben, und Funktioniert wie bei BuildRexxMessage.
    */
   /*
    *   weitere args
    */


/****************************************************************/
/*      RexxMessageHandler sucht die FunktionsListe durch, und  */
/*      ruft, falls es das Kommando gibt, die dazugeh�rige      */
/*      Funktion auf. Sollte das Kommando nicht existieren      */
/*      wird der ARexxFehlerCode Label NotFound zur�ckgegeben.  */
/****************************************************************/
/*
 * RexxMessageHandler ruft bei ankommenden Messages die in der
 * Funktionliste �bergebenen Kommandos auf.
 *
 * --> rmsg     Zeiger auf die RexxMessage, die bearbeitet werden soll
 */


/****************************************************************/
/*      ChangeProcessMessage    �ndert den Zeiger der process_  */
/*      message funktion.                                       */
/****************************************************************/
/*
 * ChangeProcessMessage �ndert die Funktion f�r das InterneMessagehandling
 *
 * --> new_function     Zeiger auf die neue Funktion, bei -1 wird
 *              der HRexx interne Handler verwendet
 * <-- RESULT   Pointer auf alten hndler
 */

/****************************************************************/
/*      SetRexxCommandTable  �ndert die interne Kommandotabelle */
/****************************************************************/
   /*
    *      Zeiger auf eine vom Benutzer definierte Kommando Tabelle
    */
   /*
    *      gibt den Zeiger auf die alte Funktiontabelle zur�ck.
    */


/* Internal ErrorCodes */
#define  RERROR_AREXX_ALLREADY_OPEN      -1
#define  RERROR_OUT_OF_MEMORY            -2
#define  RERROR_NO_AREXX                 -3
#define  RERROR_PORT_ALLREADY_EXISTS     -4
#define  RERROR_INVALID_PORT_NAME        -5
#define  RERROR_NO_PORT                  -6
#define  RERROR_AREXX_NOT_OPEN           -7
#define  RERROR_INVALID_COMMAND_NAME     -8
#define  RERROR_UNKNOWN_DESTINATION_PORT -9
#define  RERROR_NO_MSG                   -10
#define  RERROR_STRING_TOO_LONG          -11
#define  RERROR_NO_COMMAND_TABLE         -12

struct  RexxCommand
{
   char *Name;
   long  (*Function)(char * _s,struct RexxMsg *rmsg);
};

/*************************************************************/
/*  ModifyRepCount  �ndert Anzahl fehlender Messages         */
/*************************************************************/
/*
 ModifyRepCount
        �ndert den Counter mit den fehlenden Messages um den in
        delta angegebenen Betrag.
        Der alte wert von RepCount wird zur�ckgegeben
*/

/*
 AttempCloseRexx
        probiert den ARexxPort zu schliessen (funktioniert nur, wenn
        OutstandingReplies==0 ist), kann das RexxSystem geschlossen
        werden kommt TRUE zur�ck, sonst False
*/


