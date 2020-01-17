#include <CtrlLib/CtrlLib.h>

 

using namespace Upp;

 

struct MyAppWindow : TopWindow {

    MenuBar menu;

 

    void Exit() {

        if(PromptOKCancel("Exit Mnexacore?"))

            Break();

    }

 

    void SubMenu(Bar& bar) {

        bar.Add("Exit", [=] { Exit(); });

    }

 

    void MainMenu(Bar& bar) {

        bar.Sub("Options", [=](Bar& bar) { SubMenu(bar); });

    }

 

    typedef MyAppWindow CLASSNAME;

 

    MyAppWindow() {

        Title("Mnexacore").Sizeable();

        AddFrame(menu);

        menu.Set([=](Bar& bar) { MainMenu(bar); });

    }

};

 

GUI_APP_MAIN

{

    MyAppWindow app;

    app.Run();

}
