#include "App.h"
#include "Mainframe.h"


wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainframe = new MainFrame("To-Do List");
    mainframe->SetClientSize(800, 600);
    mainframe->Center();
    mainframe->Show();
    return true;
}                                                     