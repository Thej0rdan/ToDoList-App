#include "Mainframe.h"
#include <wx/wx.h>	
#include <vector>
#include <string>
#include "Task.h"


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventsHandlers();
	AddSavedTasks();
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
	clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);
}

void MainFrame::AddSavedTasks()
{
	std::vector<Task> tasks;

	for (Task task : tasks)
	{
		int index = checkList->GetCount();
		checkList->Insert(task.description, index);
		checkList->Check(index, task.done);
	}
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
	case WXK_UP:
		MoveSelectedTask(-1);
		break;
	case WXK_DOWN:
		MoveSelectedTask(1);
		break;
	}
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& event)
{
	if (checkList->IsEmpty()) {
		return;
	}

	wxMessageDialog* dialog = new wxMessageDialog(this, "Are you sure you want to clear the list?", "Clear", wxYES_NO | wxCANCEL| wxNO_DEFAULT | wxICON_QUESTION);
	int answer = dialog->ShowModal();

	if (answer == wxID_YES)
	{
		checkList->Clear();
	}
}

void MainFrame::OnWindowClosed(wxCloseEvent& event)
{
	wxMessageDialog* dialog = new wxMessageDialog(this, "Are you sure you want to exit?", "Exit", wxYES_NO | wxCANCEL | wxNO_DEFAULT | wxICON_QUESTION);
	int answer = dialog->ShowModal();

	if (answer == wxID_YES)
	{
		Destroy();
	}
	else
	{
		event.Veto();
	}

	std::vector<Task> tasks;

	for (int i = 0; i < checkList->GetCount(); i++)
	{
		Task task;
		task.description = checkList->GetString(i);
		task.done = checkList->IsChecked(i);
		tasks.push_back(task);
	}

	SaveTasksToFile(tasks, "task.txt");
	event.Skip();
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
	int selectedIndex = checkList->GetSelection();

	if (selectedIndex == wxNOT_FOUND){
		return;
	}

	int newIndex = selectedIndex + offset;

	if (newIndex >= 0 && newIndex < checkList->GetCount())
	{
		SwapTasks(selectedIndex, newIndex);
		checkList->SetSelection(newIndex, true);
	}
}

void MainFrame::SwapTasks(int i, int j)
{
	Task taskI{ checkList->GetString(i).ToStdString(), checkList->IsChecked(i)};
	Task taskJ{ checkList->GetString(j).ToStdString(), checkList->IsChecked(j)};

	checkList->SetString(j, taskI.description);
	checkList->Check(j, taskJ.done);
}
