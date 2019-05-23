#include "CMainFrame.h"
void CMainFrame::m_fnSetupMenu()
{
    wxMenuBar *lpMenuBar;
    m_lpFileMenu = new wxMenu(_(""));
    m_lpFileMenu->Append(wxID_NEW, _(STR_NEW), _(""), wxITEM_NORMAL);
    m_lpFileMenu->Append(wxID_OPEN, _(STR_OPEN), _(""), wxITEM_NORMAL);
    m_lpFileMenu->Append(wxID_SAVE, _(STR_SAVE), _(""), wxITEM_NORMAL);
    m_lpFileMenu->Append(wxID_EXIT, _(STR_EXIT), _(""), wxITEM_NORMAL);
    m_lpEditMenu = new wxMenu(_(""));
    m_lpEditMenu->Append(wxID_UNDO, _(STR_BACKWARD), _(""), wxITEM_NORMAL);
    m_lpEditMenu->Append(wxID_REDO, _(STR_FORWARD), _(""), wxITEM_NORMAL);
	m_lpEditMenu->Append(ID_GTP, _(STR_RUN_ENGINE), _(""), wxITEM_NORMAL);
	m_lpEditMenu->Append(ID_SEND_COMMAND, _(STR_SEND_COMMAND), _(""), wxITEM_NORMAL);
	m_lpCoordMenu = new wxMenu(_(""));
	m_lpCoordMenu->Append(ID_COORD_NULL, _(STR_COORD_NULL), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_NET, _(STR_COORD_NET), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_NUM, _(STR_COORD_NUM), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_SGF, _(STR_COORD_SGF), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_GTP, _(STR_COORD_GTP), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Check(ID_COORD_NULL, true);
    m_lpViewMenu = new wxMenu(_(""));
    m_lpViewMenu->Append(ID_SHOW_STEP, _(STR_STEP), _(""), wxITEM_CHECK);
	m_lpViewMenu->Append(wxID_SELECT_COLOR, _(STR_SET_GAMEBOARD_COLOR), _(""), wxITEM_NORMAL);
	m_lpViewMenu->Append(ID_COORDINATE, _(STR_COORDINATE), m_lpCoordMenu);
	m_lpHelpMenu = new wxMenu(_(""));
	m_lpHelpMenu->Append(wxID_HELP_CONTEXT, _(STR_MANUAL), _(""), wxITEM_NORMAL);
	m_lpHelpMenu->Append(wxID_ABOUT, _(STR_ABOUT), _(""), wxITEM_NORMAL);
    lpMenuBar = new wxMenuBar();
    lpMenuBar->Append(m_lpFileMenu, STR_FILE);
    lpMenuBar->Append(m_lpEditMenu, STR_EDIT);
    lpMenuBar->Append(m_lpViewMenu, STR_VIEW);
	lpMenuBar->Append(m_lpHelpMenu, STR_HELP);
    SetMenuBar(lpMenuBar);
}

void CMainFrame::m_fnSetupToolBar()
{
    m_lpToolBar = new wxToolBar(this, wxID_ANY);
    m_lpToolBar->AddTool(wxID_NEW, _(""), wxBITMAP(NEW_BMP), _(STR_NEW));
    m_lpToolBar->AddTool(wxID_OPEN, _(""), wxBITMAP(OPEN_BMP), _(STR_OPEN));
    m_lpToolBar->AddTool(wxID_SAVE, _(""), wxBITMAP(SAVE_BMP), _(STR_SAVE));
    m_lpToolBar->AddTool(wxID_UNDO, _(""), wxBITMAP(BACKWARD_BMP), _(STR_BACKWARD));
    m_lpToolBar->AddTool(wxID_REDO, _(""), wxBITMAP(FORWARD_BMP), _(STR_FORWARD));
    m_lpToolBar->AddTool(ID_GTP, _(""), wxBITMAP(RUN_BMP), _(STR_RUN_ENGINE));
	m_lpToolBar->AddTool(ID_FINAL_SCORE, _(""), wxBITMAP(SCORE_BMP), _(STR_RESULT));
    m_lpToolBar->Realize();
    SetToolBar(m_lpToolBar);
}

void CMainFrame::m_fnSetupStatusBar()
{
	m_lpStatusBar = new wxStatusBar(this);
	SetStatusBar(m_lpStatusBar);
	m_lpStatusBar->SetStatusText(_(STR_NO_ENGINE));
}

void CMainFrame::m_fnCreateCanvas()
{
    m_lpCanvas = new CCanvas(this);
	m_lpCanvas->m_bmpOriginalBlackStone = wxBITMAP(BLACK_STONE_BMP);
	m_lpCanvas->m_bmpOriginalWhiteStone = wxBITMAP(WHITE_STONE_BMP);
	m_lpCanvas->m_bmpOriginalPass = wxBITMAP(PASS_BMP);
	m_lpCanvas->m_bmpOriginalResign = wxBITMAP(RESIGN_BMP);
	DragAcceptFiles(true);
}

void CMainFrame::m_fnPrepareEngine()
{
    std::ifstream ifs;
    char buffer[2048] = {'\0'};
    ifs.open("config.txt");
	ifs.getline(buffer, 2048);
    ifs.close();
	m_ProcessExitType = PET_FAILURE;
    m_lpGTPProcess = new CGTPProcess(this, wxID_ANY);
}

CMainFrame::CMainFrame(const wxString &title, wxSize init_size = wxDefaultSize): wxFrame(0, wxID_ANY, title, wxDefaultPosition, init_size)
{
	m_fnSetupMenu();
	m_fnSetupToolBar();
	m_fnSetupStatusBar();
	m_fnCreateCanvas();
	m_fnPrepareEngine();
}

void CMainFrame::OnNew(wxCommandEvent &event)
{
    wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK|wxCANCEL);
    if ((m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0) || MD.ShowModal() == wxID_OK)
    {
        if (!(m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0))
        {
            m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
        }
        Refresh();
    }
}


void CMainFrame::m_fnOpenSGF(char *lpstrFile)
{
	std::ifstream ifs;
	ifs.open(lpstrFile);
    m_lpCanvas->m_GameBoardManager.OnReadSGF(ifs);
	m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove = &(m_lpCanvas->m_GameBoardManager.m_emBlankMove);
	while (m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove->child != NULL)
	{
		m_lpCanvas->m_GameBoardManager.OnRedoMove();
		m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove->test = false;
	}
	m_lpCanvas->m_GameBoardManager.m_lpemLivingMove = m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove;
    ifs.close();
}

void CMainFrame::OnOpen(wxCommandEvent &event)
{
    wxFileDialog OpenFileDialog(this, _(""), _(""), _(""), _("Smart Game File (*.sgf)|*.sgf"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK|wxCANCEL);
    std::ifstream ifs;
    if (OpenFileDialog.ShowModal() == wxID_OK)
    {
        if ((m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0) || MD.ShowModal() == wxID_OK)
        {
            if (!(m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0))
            {
				m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
            }
			m_fnOpenSGF(OpenFileDialog.GetPath().char_str());
            Refresh();
        }
    }
}

void CMainFrame::OnDropFile(wxDropFilesEvent &event)
{
    wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK|wxCANCEL);
    std::ifstream ifs;
	wxString wxstrFile;
	wxstrFile = *(event.GetFiles());
	if (wxstrFile.length() > 4 && strcmp(strrchr((char*)(wxstrFile.char_str()), '.'), ".sgf") == 0)
	{
		if ((m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0) || MD.ShowModal() == wxID_OK)
		{
			if (!(m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0))
			{
				m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
			}
			m_fnOpenSGF(wxstrFile.char_str());
			Refresh();
		}
	}
}

void CMainFrame::OnSave(wxCommandEvent &event)
{
    wxFileDialog SaveFileDialog(this, _(""), _(""), _(""), _("Smart Game File (*.sgf)|*.sgf"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	std::ofstream ofs;
    if (SaveFileDialog.ShowModal() == wxID_OK)
    {
		ofs.open(SaveFileDialog.GetPath().char_str());
		m_lpCanvas->m_GameBoardManager.OnWriteSGF(ofs);
		ofs.close();
    }
}

void CMainFrame::OnShowStep(wxCommandEvent &event)
{
    m_lpCanvas->m_bShowStep = !m_lpCanvas->m_bShowStep;
    Refresh();
}

void CMainFrame::OnSetGameboardColor(wxCommandEvent &event)
{
	wxColourData wxclrdata;
	wxclrdata.SetColour(m_lpCanvas->m_brGameBoard.GetColour());
	wxColourDialog CD(this, &wxclrdata);
	if (CD.ShowModal() == wxID_OK)
	{
		wxclrdata = CD.GetColourData();
		m_lpCanvas->m_brGameBoard.SetColour(wxclrdata.GetColour());
		Refresh();
	}
}


void CMainFrame::OnHideCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_NULL;
	Refresh();
}
void CMainFrame::OnSetNetCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_NET;
	Refresh();
}
void CMainFrame::OnSetNumCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_NUM;
	Refresh();
}
void CMainFrame::OnSetSGFCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_SGF;
	Refresh();
}
void CMainFrame::OnSetGTPCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_GTP;
	Refresh();
}


void CMainFrame::OnScore(wxCommandEvent &event)
{
	m_lpCanvas->m_fnShowCountResult();
}

void CMainFrame::OnBackward(wxCommandEvent &event)
{
	m_lpCanvas->m_fnBackward();
}

void CMainFrame::OnForward(wxCommandEvent &event)
{
	m_lpCanvas->m_fnForward();
}


void CMainFrame::OnGTP(wxCommandEvent &event)
{
    wxMessageDialog MD(this, _(STR_CLOSE_ENGINE_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
    if (m_lpGTPProcess->m_bAlive)
    {
        if (MD.ShowModal() == wxID_OK)
        {
			m_ProcessExitType = PET_STOP;
			m_lpGTPReceiver->m_bKeepLoop = false;
			m_lpCanvas->m_fnGTPEnd();
        }
    }
    else
    {
        if(m_fnOpenLZProcess() != 0)
        {
			m_lpGTPProcess->m_bAlive = true;
			m_ProcessExitType = PET_COLLAPSE;
			m_lpEditMenu->SetLabel(ID_GTP, _(STR_CLOSE_ENGINE));
			m_lpToolBar->SetToolNormalBitmap(ID_GTP, wxBITMAP(STOP_BMP));
			m_lpToolBar->SetToolShortHelp(ID_GTP, _(STR_CLOSE_ENGINE));
			m_lpStatusBar->SetStatusText(_(STR_ENGINE_AVAILABLE));
        }
    }
}


void CMainFrame::OnSendCommand(wxCommandEvent &event)
{
	wxTextEntryDialog TED(this, _(STR_INPUT_COMMAND), _(STR_TIP));
	wxString wxstrCommand;
	if (TED.ShowModal() == wxID_OK)
	{
		wxstrCommand = TED.GetValue() + _("\n");
		m_lpCanvas->m_fnGTPSendInquire(wxstrCommand);
	}
}


void CMainFrame::OnManual(wxCommandEvent &event)
{
	CManualDialog MD(this, _(STR_MANUAL), _(STR_DIRECTION), _(STR_CLOSE));
	MD.ShowModal();
}

void CMainFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageDialog MD(this, _(STR_VERSION), _(STR_ABOUT));
	MD.ShowModal();
}

long CMainFrame::m_fnOpenLZProcess()
{
    long lProcessId;
    wxString wxstrCommand;
	wxstrCommand = wxString("autogtp.exe");
    m_lpGTPProcess->Redirect();
    lProcessId = wxExecute(wxstrCommand, wxEXEC_ASYNC, m_lpGTPProcess);
    if (lProcessId > 0)
    {
        m_lpGTPReceiver = new CGTPReceiver();
        m_lpGTPReceiver->m_lpCanvas = m_lpCanvas;
        m_lpGTPReceiver->m_lpInputStream = m_lpGTPProcess->GetInputStream();
        m_lpGTPReceiver->Run();
        m_lpCanvas->m_lpOutputStream = m_lpGTPProcess->GetOutputStream();
    }
    return lProcessId;
}

void CMainFrame::OnLZProcessExit(wxProcessEvent &event)
{
    m_lpCanvas->m_lpOutputStream = 0;
    switch (m_ProcessExitType)
    {
	case PET_FAILURE:
        delete m_lpGTPProcess;
        m_lpGTPProcess = new CGTPProcess(this, wxID_ANY);
		break;
    case PET_STOP:
        m_lpGTPReceiver->m_bKeepLoop = false;
        delete m_lpGTPProcess;
        m_lpGTPProcess = new CGTPProcess(this, wxID_ANY);
		m_lpEditMenu->SetLabel(ID_GTP, _(STR_RUN_ENGINE));
		m_lpToolBar->SetToolNormalBitmap(ID_GTP, wxBITMAP(RUN_BMP));
		m_lpToolBar->SetToolShortHelp(ID_GTP, _(STR_RUN_ENGINE));
		m_lpStatusBar->SetStatusText(_(STR_NO_ENGINE));
        m_ProcessExitType = PET_COLLAPSE;
        break;
	case PET_COLLAPSE:
		m_lpGTPReceiver->m_bKeepLoop = false;
        delete m_lpGTPProcess;
        m_lpGTPProcess = new CGTPProcess(this, wxID_ANY);
		m_lpEditMenu->SetLabel(ID_GTP, _(STR_RUN_ENGINE));
		m_lpToolBar->SetToolNormalBitmap(ID_GTP, wxBITMAP(RUN_BMP));
		m_lpToolBar->SetToolShortHelp(ID_GTP, _(STR_RUN_ENGINE));
		m_lpStatusBar->SetStatusText(_(STR_NO_ENGINE));
		break;
    case PET_QUIT:
        delete m_lpGTPProcess;
        Destroy();
        break;
    }
}

void CMainFrame::OnExit(wxCommandEvent &event)
{
    std::ofstream ofs;
    if (m_lpGTPProcess->m_bAlive)
    {
        m_ProcessExitType = PET_QUIT;
		m_lpGTPReceiver->m_bKeepLoop = false;
		m_lpCanvas->m_fnGTPEnd();
    }
    else
    {
        delete m_lpGTPProcess;
        Destroy();
    }
}

void CMainFrame::OnClose(wxCloseEvent &event)
{
	std::ofstream ofs;
	if (m_lpGTPProcess->m_bAlive)
	{
		m_ProcessExitType = PET_QUIT;
		m_lpGTPReceiver->m_bKeepLoop = false;
		m_lpCanvas->m_fnGTPEnd();
	}
	else
	{
		delete m_lpGTPProcess;
		Destroy();
	}
}


BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
EVT_MENU(wxID_NEW, CMainFrame::OnNew)
EVT_TOOL(wxID_NEW, CMainFrame::OnNew)
EVT_MENU(wxID_OPEN, CMainFrame::OnOpen)
EVT_TOOL(wxID_OPEN, CMainFrame::OnOpen)
EVT_DROP_FILES(CMainFrame::OnDropFile)
EVT_MENU(wxID_SAVE, CMainFrame::OnSave)
EVT_TOOL(wxID_SAVE, CMainFrame::OnSave)
EVT_TOOL(ID_SHOW_STEP, CMainFrame::OnShowStep)
EVT_MENU(ID_COORD_NULL, CMainFrame::OnHideCoord)
EVT_MENU(ID_COORD_NET, CMainFrame::OnSetNetCoord)
EVT_MENU(ID_COORD_NUM, CMainFrame::OnSetNumCoord)
EVT_MENU(ID_COORD_SGF, CMainFrame::OnSetSGFCoord)
EVT_MENU(ID_COORD_GTP, CMainFrame::OnSetGTPCoord)
EVT_TOOL(ID_FINAL_SCORE, CMainFrame::OnScore)
EVT_TOOL(wxID_SELECT_COLOR, CMainFrame::OnSetGameboardColor)
EVT_MENU(wxID_UNDO, CMainFrame::OnBackward)
EVT_TOOL(wxID_UNDO, CMainFrame::OnBackward)
EVT_MENU(wxID_REDO, CMainFrame::OnForward)
EVT_TOOL(wxID_REDO, CMainFrame::OnForward)
EVT_MENU(ID_GTP, CMainFrame::OnGTP)
EVT_TOOL(ID_GTP, CMainFrame::OnGTP)
EVT_MENU(ID_SEND_COMMAND, CMainFrame::OnSendCommand)
EVT_MENU(wxID_HELP_CONTEXT, CMainFrame::OnManual)
EVT_MENU(wxID_ABOUT, CMainFrame::OnAbout)
EVT_END_PROCESS(wxID_ANY, CMainFrame::OnLZProcessExit)
EVT_MENU(wxID_EXIT, CMainFrame::OnExit)
EVT_CLOSE(CMainFrame::OnClose)
END_EVENT_TABLE()
