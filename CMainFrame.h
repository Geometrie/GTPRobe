#ifndef CMAINFRAME_H
#define CMAINFRAME_H
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/stattext.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <fstream>
#include <wx/colordlg.h>
#include "CGTPReceiver.h"
#include "CGTPProcess.h"
#include "CManualDialog.h"
class CMainFrame: public wxFrame
{
public:
    CMainFrame(const wxString &title, wxSize init_size);
    wxMenu *m_lpFileMenu, *m_lpViewMenu, *m_lpCoordMenu, *m_lpEditMenu, *m_lpHelpMenu;
    wxToolBar *m_lpToolBar;
	wxStatusBar *m_lpStatusBar;
    CCanvas *m_lpCanvas;
    CGTPReceiver *m_lpGTPReceiver;
    CGTPProcess *m_lpGTPProcess;
	PROCESS_EXIT_TYPE m_ProcessExitType;
	void m_fnOpenSGF(char *lpstrFile);
protected:
    void OnNew(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
	void OnDropFile(wxDropFilesEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnShowStep(wxCommandEvent &event);
	void OnSetGameboardColor(wxCommandEvent &event);
	void OnHideCoord(wxCommandEvent &event);
	void OnSetNetCoord(wxCommandEvent &event);
	void OnSetNumCoord(wxCommandEvent &event);
	void OnSetSGFCoord(wxCommandEvent &event);
	void OnSetGTPCoord(wxCommandEvent &event);
	void OnScore(wxCommandEvent &event);
    void OnBackward(wxCommandEvent &event);
    void OnForward(wxCommandEvent &event);
    void OnGTP(wxCommandEvent &event);
	void OnSendCommand(wxCommandEvent &event);
	void OnManual(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);
    long m_fnOpenLZProcess();
    void OnLZProcessExit(wxProcessEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);
private:
	void m_fnSetupMenu();
	void m_fnSetupToolBar();
	void m_fnSetupStatusBar();
	void m_fnCreateCanvas();
	void m_fnPrepareEngine();
    DECLARE_EVENT_TABLE()
};


enum
{
	ID_COORDINATE = 1000,
	ID_COORD_NULL,
	ID_COORD_NET,
	ID_COORD_NUM,
	ID_COORD_SGF,
	ID_COORD_GTP,
	ID_SEND_COMMAND,
	ID_GTP,
	ID_SHOW_STEP,
	ID_FINAL_SCORE
};
#endif // CMAINFRAME_H
