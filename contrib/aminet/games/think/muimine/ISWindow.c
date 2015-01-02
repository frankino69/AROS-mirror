/*
        MUI Custom Window class for selecting image files for MUIMine
*/

#include "MFStrings.h"
#include "MUIMine.h"
#include "ISWindow.h"

/*
    class's instance data
*/
struct ISWindowData
{
    Object *    MineFieldString;    // string for mine field image file name
    Object *    StartButtonString;  // string for the start button image file name
    Object *    MinesDigitsString;  // string for the mines left digits image file name
    Object *    TimeDigitsString;   // string for the time taken digits image file name
    Object *    MineFieldPop;       // asl popup for the mine field image file
    Object *    StartButtonPop;     // asl popup for the start button image file
    Object *    MinesDigitsPop;     // asl popup for the mines left digits image file
    Object *    TimeDigitsPop;      // asl popup for the time taken digits image file
    ULONG       ExitCode;           // exit code to indicate OK or Cancel exit
};



/*
    function :    get the image file name from a string object and place
                  it in the given store location

    parameters :  strobj = pointer to the string object to get the name from
                  store = pointer to the location to store the result to

    return :      TRUE if the name was retrieved, FALSE otherwise
*/
ULONG GetImageName(Object * strobj, IPTR * store)
{
    STRPTR pstr;
    int l;

    if (GetAttr(MUIA_String_Contents, strobj, (IPTR *)&pstr))
    {
        l = (pstr) ? strlen(pstr) : 0;
        *store = (l) ? (IPTR)pstr : (IPTR)NULL;
        return TRUE;
    }
    *store = (IPTR)NULL;
    return FALSE;
}


/*
    function :    OM_NEW method handler
*/
SAVEDS IPTR mNew(struct IClass *cl, Object *obj, struct opSet * msg)
{
    struct ISWindowData * data;
    struct TagItem *tags;
    struct TagItem *tag;
    Object * mfstring, * sbstring, * mdstring, * tdstring,
           * mfpop, * sbpop, * mdpop, * tdpop, * okbutt, * cancelbutt;
    STRPTR mfimage, sbimage, mdimage, tdimage,
           mflabel, sblabel, mdlabel, tdlabel,
           oklabel, cancellabel;

    /*
        parse initial taglist
    */
    mfimage = sbimage = mdimage = tdimage = NULL;
    for (tags = msg->ops_AttrList; (tag = NextTagItem(&tags));)
    {
        switch (tag->ti_Tag)
        {
            case MUIA_ISWindow_MineFieldImage:
                mfimage = (STRPTR)tag->ti_Data;
                break;

            case MUIA_ISWindow_StartButtonImage:
                sbimage = (STRPTR)tag->ti_Data;
                break;

            case MUIA_ISWindow_MinesDigitsImage:
                mdimage = (STRPTR)tag->ti_Data;
                break;

            case MUIA_ISWindow_TimeDigitsImage:
                tdimage = (STRPTR)tag->ti_Data;
                break;
        }
    }

    /*
        get strings
    */
    mflabel = GetStr(MSG_ISWINDOW_MFLABEL);
    sblabel = GetStr(MSG_ISWINDOW_SBLABEL);
    mdlabel = GetStr(MSG_ISWINDOW_MDLABEL);
    tdlabel = GetStr(MSG_ISWINDOW_TDLABEL);
    oklabel = GetStr(MSG_OKBUTT_LABEL);
    cancellabel = GetStr(MSG_CANCELBUTT_LABEL);

    okbutt = TextObject,
        ButtonFrame,
        MUIA_CycleChain, 1,
        MUIA_ShortHelp, GetStr(MSG_ISWINDOW_OKHELP),
        MUIA_Text_Contents, oklabel + 2,
        MUIA_Text_PreParse, "\33c",
        MUIA_Text_HiChar  , *oklabel,
        MUIA_ControlChar  , *oklabel,
        MUIA_InputMode    , MUIV_InputMode_RelVerify,
        MUIA_Background   , MUII_ButtonBack,
        End;
    /*
        create the window object
    */
    obj = (Object *)DoSuperNew(cl, obj,
        MUIA_Window_Title, GetStr(MSG_ISWINDOW_TITLE),
        WindowContents, VGroup,
            Child, ColGroup(2),

                Child, KeyLabel2(mflabel + 2, *mflabel),
                Child, mfpop = PopaslObject,
                    MUIA_ShortHelp, GetStr(MSG_ISWINDOW_MFHELP),
                    MUIA_Popstring_String, mfstring = StringObject,
                        StringFrame,
                        MUIA_CycleChain, 1,
                        MUIA_ControlChar, *mflabel,
                        MUIA_String_MaxLen, 256,
                        MUIA_String_Contents, mfimage,
                        MUIA_String_AdvanceOnCR, TRUE,
                        End,
                    MUIA_Popstring_Button, PopButton(MUII_PopFile),
                    ASLFR_TitleText, GetStr(MSG_ISWINDOW_MFTITLE),
                    End,

                Child, KeyLabel2(sblabel + 2, *sblabel),
                Child, sbpop = PopaslObject,
                    MUIA_ShortHelp, GetStr(MSG_ISWINDOW_SBHELP),
                    MUIA_Popstring_String, sbstring = StringObject,
                        StringFrame,
                        MUIA_CycleChain, 1,
                        MUIA_ControlChar, *sblabel,
                        MUIA_String_MaxLen, 256,
                        MUIA_String_Contents, sbimage,
                        MUIA_String_AdvanceOnCR, TRUE,
                        End,
                    MUIA_Popstring_Button, PopButton(MUII_PopFile),
                    ASLFR_TitleText, GetStr(MSG_ISWINDOW_SBTITLE),
                    End,

                Child, KeyLabel2(mdlabel + 2, *mdlabel),
                Child, mdpop = PopaslObject,
                    MUIA_ShortHelp, GetStr(MSG_ISWINDOW_MDHELP),
                    MUIA_Popstring_String, mdstring = StringObject,
                        StringFrame,
                        MUIA_CycleChain, 1,
                        MUIA_ControlChar, *mdlabel,
                        MUIA_String_MaxLen, 256,
                        MUIA_String_Contents, mdimage,
                        MUIA_String_AdvanceOnCR, TRUE,
                        End,
                    MUIA_Popstring_Button, PopButton(MUII_PopFile),
                    ASLFR_TitleText, GetStr(MSG_ISWINDOW_MDTITLE),
                    End,

                Child, KeyLabel2(tdlabel + 2, *tdlabel),
                Child, tdpop = PopaslObject,
                    MUIA_ShortHelp, GetStr(MSG_ISWINDOW_TDHELP),
                    MUIA_Popstring_String, tdstring = StringObject,
                        StringFrame,
                        MUIA_CycleChain, 1,
                        MUIA_ControlChar, *tdlabel,
                        MUIA_String_MaxLen, 256,
                        MUIA_String_Contents, tdimage,
                        MUIA_String_AdvanceOnCR, TRUE,
                        End,
                    MUIA_Popstring_Button, PopButton(MUII_PopFile),
                    ASLFR_TitleText, GetStr(MSG_ISWINDOW_TDTITLE),
                    End,

                End,  // ColGroup(2)

            Child, HGroup,
                MUIA_Group_SameSize, TRUE,
                Child, okbutt,

                Child, cancelbutt = TextObject,
                    ButtonFrame,
                    MUIA_CycleChain, 1,
                    MUIA_ShortHelp, GetStr(MSG_ISWINDOW_CANCELHELP),
                    MUIA_Text_Contents, cancellabel + 2,
                    MUIA_Text_PreParse, "\33c",
                    MUIA_Text_HiChar  , *cancellabel,
                    MUIA_ControlChar  , *cancellabel,
                    MUIA_InputMode    , MUIV_InputMode_RelVerify,
                    MUIA_Background   , MUII_ButtonBack,
                    End,

                End,  // HGroup

            End,  // VGroup

        MUIA_Window_DefaultObject, okbutt,
        TAG_MORE, msg->ops_AttrList);

    if (obj == NULL)
    {
        return 0;
    }

    data = INST_DATA(cl,obj);

    /*
            initialize the instance data
    */
    data->MineFieldString = mfstring;
    data->StartButtonString = sbstring;
    data->MinesDigitsString = mdstring;
    data->TimeDigitsString = tdstring;

    data->MineFieldPop = mfpop;
    data->StartButtonPop = sbpop;
    data->MinesDigitsPop = mdpop;
    data->TimeDigitsPop = tdpop;

    data->ExitCode = MUIV_ISWindow_ExitCode_Cancel;

    /*
        setup notification
    */
    DoMethod(okbutt, MUIM_Notify, MUIA_Pressed, FALSE,
                obj, 2, MUIM_ISWindow_ExitCheck, MUIV_ISWindow_ExitCode_OK);
    DoMethod(cancelbutt, MUIM_Notify, MUIA_Pressed, FALSE,
                obj, 2, MUIM_ISWindow_ExitCheck, MUIV_ISWindow_ExitCode_Cancel);
    DoMethod(obj, MUIM_Notify,  MUIA_Window_CloseRequest, TRUE,
                obj, 2, MUIM_ISWindow_ExitCheck, MUIV_ISWindow_ExitCode_Cancel);

    return (IPTR)obj;
}


/*
    function :    OM_DISPOSE method handler
*/
SAVEDS ULONG mDispose(struct IClass *cl, Object *obj, Msg msg)
{
//        struct ISWindowData *data = INST_DATA(cl,obj);

    return DoSuperMethodA(cl,obj,msg);
}


/*
    function :    OM_SET method handler
*/
SAVEDS IPTR mSet(struct IClass *cl, Object *obj, struct opSet * msg)
{
    struct ISWindowData *data = INST_DATA(cl,obj);
    struct TagItem *tags;
    struct TagItem *tag;

    for (tags = msg->ops_AttrList; (tag = NextTagItem(&tags));)
    {
        switch (tag->ti_Tag)
        {
            case MUIA_ISWindow_ExitCode:
                data->ExitCode = tag->ti_Data;
                break;
        }
    }

    return DoSuperMethodA(cl, obj, (APTR)msg);
}


/*
    function :    OM_GET method handler
*/
static IPTR mGet(struct IClass *cl, Object *obj, struct opGet * msg)
{
    struct ISWindowData *data = INST_DATA(cl,obj);
    IPTR *store = msg->opg_Storage;

    switch (msg->opg_AttrID)
    {
        case MUIA_ISWindow_MineFieldImage:
            return GetImageName(data->MineFieldString, store);

        case MUIA_ISWindow_StartButtonImage:
            return GetImageName(data->StartButtonString, store);

        case MUIA_ISWindow_MinesDigitsImage:
            return GetImageName(data->MinesDigitsString, store);

        case MUIA_ISWindow_TimeDigitsImage:
            return GetImageName(data->TimeDigitsString, store);

        case MUIA_ISWindow_ExitCode:
            *store = data->ExitCode;
            return TRUE;
    }

    return DoSuperMethodA(cl, obj, (APTR)msg);
}


/*
    function :    MUIM_ISWindow_ExitCheck method handler, determines if it is
                  ok to close the window and sets the exit code if it can be
                  else gives a message to close the requesters
*/
static IPTR mExitCheck(struct IClass *cl, Object *obj, struct MUIP_ISWindow_ExitCheck * msg)
{
    struct ISWindowData *data = INST_DATA(cl,obj);
    IPTR isactive;

    GetAttr(MUIA_Popasl_Active, data->MineFieldPop, &isactive);
    if (!isactive) GetAttr(MUIA_Popasl_Active, data->StartButtonPop, &isactive);
    if (!isactive) GetAttr(MUIA_Popasl_Active, data->MinesDigitsPop, &isactive);
    if (!isactive) GetAttr(MUIA_Popasl_Active, data->TimeDigitsPop, &isactive);

    if (isactive)
    {
        MUI_Request(_app(obj), obj, 0, GetStr(MSG_ISWINDOW_TITLE),
                                       GetStr(MSG_CONTINUE_GADGET),
                                       GetStr(MSG_CLOSE_IMAGE_ASL),
#ifdef __AROS__ 
                                       NULL);
#endif
    }
    else
    {
        SetAttrs(obj, MUIA_ISWindow_ExitCode, msg->ExitCode, TAG_DONE);
    }

    return 0;
}


/*
    function :    class dispatcher
*/
DISPATCHER(ISWindowDispatcher)
{
    switch (msg->MethodID)
    {
        case OM_NEW        : return(mNew      (cl, obj, (APTR)msg));
        case OM_DISPOSE    : return(mDispose  (cl, obj, (APTR)msg));
        case OM_SET        : return(mSet      (cl, obj, (APTR)msg));
        case OM_GET        : return(mGet      (cl, obj, (APTR)msg));

        case MUIM_ISWindow_ExitCheck:
                             return mExitCheck(cl, obj, (APTR)msg);
    }

    return(DoSuperMethodA(cl,obj,msg));
}



/*
    function :    creates the ISWindow MUI custom class

    return :      pointer to the created custom class or NULL
*/
struct MUI_CustomClass * CreateISWindowClass()
{
    return MUI_CreateCustomClass(NULL, MUIC_Window, NULL,
                                       sizeof(struct ISWindowData),
                                       ENTRY(ISWindowDispatcher));
}

/*
    function :    deletes the ISWindow custom class

    parameters :  mcc = pointer to the ISWindow MUI_CustomClass to delete
*/
void DeleteISWindowClass(struct MUI_CustomClass * mcc)
{
    MUI_DeleteCustomClass(mcc);
}


