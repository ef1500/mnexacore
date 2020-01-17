//Declare Headers
#include <CtrlLib/CtrlLib.h>

 
//Declare namespaces
using namespace Upp;

 
//Declare our little function
GUI_APP_MAIN

{

    TopWindow w;
    
    w.Title("Mnexacore").MinimizeBox().Sizeable();

    w.SetRect(0, 0, 200, 300);

    w.Run();

}
