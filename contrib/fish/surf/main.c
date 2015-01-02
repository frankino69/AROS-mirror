#include <aros/oldprograms.h>
#include "scrnio.h"
#include "mytypes.h"

void SwitchBox();
struct Library * MathTransBase;
struct Library * MathBase;

int main(int argc, char **argv)
{
    MathBase = OpenLibrary("mathffp.library",0);
    MathTransBase = OpenLibrary("mathtrans.library",0);
    if (MathTransBase)
    {
      sqrt(1.0);          /* transcedental math library to be loaded */
      InitWindow();
    /*  ClrWindow(true); */
      SwitchBox();
      CloseDisplay();
      CloseLibrary(MathTransBase);
      return RETURN_OK;
    }
    return RETURN_FAIL;
}

