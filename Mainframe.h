#pragma once	
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	void BindEventsHandlers();


	void OnAddButtonClicked(wxCommandEvent& event);
	void OnInputEnter(wxCommandEvent& event);
	void OnListKeyDown(wxKeyEvent& event);

	void AddTaskFromInput();
	void DeleteSelectedTasks();
	void MoveSelectedTask(int offset);
	void SwapTasks(int i, int j);

	

	wxPanel* panel;
	wxStaticText* headlineText;
	wxTextCtrl* inputField;
	wxButton* addButton;
	wxCheckListBox* checkList;	
	wxButton* clearButton;

};

