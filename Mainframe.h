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

	

	wxPanel* panel;
	wxStaticText* headlineText;
	wxTextCtrl* inputField;
	wxButton* addButton;
	wxCheckListBox* checkList;	
	wxButton* clearButton;

};

