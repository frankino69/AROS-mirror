
/* prototypes from icon.c */
struct WBStartup;

BOOL GetOurIcon(struct WBStartup *WBenchMsg);
void FreeOurIcon(void);
char *TTString(char *name, char *def);
LONG TTInt(char *name, LONG def);
BOOL TTBool(char *name, BOOL def);
