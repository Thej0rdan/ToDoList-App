#include "Mainframe.h"
#include <wx/wx.h>	
#include <vector>
#include <string>
#include "Task.h"


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventsHandlers();
}

void MainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "To-Do List", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);

	inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);
	addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(600, 80), wxSize(100, 35));
	checkList = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));

}

void MainFrame::BindEventsHandlers()
{
	addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
	checkList->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
}

void MainFrame::OnAddButtonClicked(wxCommandEvent& event)
{
	AddTaskFromInput();
}

void MainFrame::OnInputEnter(wxCommandEvent& event)
{
	AddTaskFromInput();
}

void MainFrame::OnListKeyDown(wxKeyEvent& event)
{
	switch (event.GetKeyCode())
	{
	case WXK_DELETE:
		DeleteSelectedTasks();
	break;
	}
}

void MainFrame::AddTaskFromInput()
{
	wxString description = inputField->GetValue();

	if (!description.IsEmpty())
	{
		checkList->Insert(description, checkList->GetCount());
		inputField->Clear();
	}

	inputField->SetFocus();	
} 

void MainFrame::DeleteSelectedTasks()
{
	int selectedIndex = checkList->GetSelection();

	if (selectedIndex == wxNOT_FOUND)
	{
		return;
	}

	checkList->Delete(selectedIndex);
}

void MainFrame::MoveSelectedTask(int offset)
{
}
