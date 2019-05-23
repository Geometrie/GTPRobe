#include "CCanvas.h"
CCanvas::CCanvas(wxWindow *lpParent): CPainter(lpParent)
{
    m_bShowStep = false;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}


void CCanvas::m_fnShowResignResult()
{
    wxString wxstrResult;
    switch (m_GameBoardManager.m_scTurnColor)
    {
    case SC_WHITE:
        wxstrResult = wxString(STR_WHITE_RESIGN);
        break;
    case SC_BLACK:
        wxstrResult = wxString(STR_BLACK_RESIGN);
        break;
    default:
        wxstrResult = wxEmptyString;
        break;
    }
    wxMessageDialog MD(this, wxstrResult, _(STR_CURRENT_SITUATION));
    MD.ShowModal();
}

void CCanvas::m_fnShowCountResult()
{
	float fltKomi;
	int iTerrtoryDif;
	wxString wxstrMessage;
	fltKomi = 7.5f;
	m_TerritoryMutex.Lock();
	m_GameBoardManager.m_fnMarkTerritory();
	iTerrtoryDif = m_GameBoardManager.m_fnTerritoryComp();
	Refresh();
	if (iTerrtoryDif > fltKomi)
	{
		wxstrMessage = wxString::Format(wxString(STR_BLACK_OWN), (float(iTerrtoryDif) - fltKomi));
	}
	else
	{
		wxstrMessage = wxString::Format(wxString(STR_WHITE_OWN), (fltKomi - float(iTerrtoryDif)));
	}
	wxMessageDialog MD(this, wxstrMessage, _(STR_CURRENT_SITUATION));
	MD.ShowModal();
	m_GameBoardManager.m_fnClearTerritoryMark();
	m_TerritoryMutex.Unlock();
	Refresh();
}


bool CCanvas::m_fnChangePosition(int x, int y)
{
	CGameBase::ExtendMove *lpemSearch;
	wxMessageDialog MD(this, _(STR_ADD_BRANCH_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
	bool bChanged = false;
	if (m_GameBoardManager.DoublePass(x, y))
	{
		m_fnShowCountResult();
	}
	else if (m_GameBoardManager.Resign(x, y))
	{
		m_fnShowResignResult();
	}
	else if(m_GameBoardManager.OnTestMove(x, y))
	{
		lpemSearch = m_GameBoardManager.m_lpemCurrentMove->search(x, y);
		if (m_GameBoardManager.m_lpemCurrentMove->child == NULL || lpemSearch != NULL || MD.ShowModal() == wxID_OK)
		{
			m_GameBoardManager.OnAddMove(x, y);
			Refresh();
		}
		bChanged = true;
	}
	return bChanged;
}

void CCanvas::m_fnForward()
{
	if (m_GameBoardManager.m_lpemCurrentMove->child != NULL)
	{
		m_GameBoardManager.OnRedoMove();
		Refresh();
	}
	else if (m_GameBoardManager.m_lpemCurrentMove == m_GameBoardManager.m_lpemLivingMove && !m_GameBoardManager.m_qubmGTPMoves.empty())
	{
		if (m_GameBoardManager.Resign(m_GameBoardManager.m_qubmGTPMoves.front().x, m_GameBoardManager.m_qubmGTPMoves.front().y))//(m_GameBoardManager.m_qubmGTPMoves.front().x == nBoardSize && m_GameBoardManager.m_qubmGTPMoves.front().y == 1)
		{
			m_fnShowResignResult();
			m_GameBoardManager.m_qubmGTPMoves.pop();
			m_GameBoardManager.m_lpemLivingMove = NULL;
		}
		else if (m_GameBoardManager.DoublePass(m_GameBoardManager.m_qubmGTPMoves.front().x, m_GameBoardManager.m_qubmGTPMoves.front().y))//(m_GameBoardManager.m_qubmGTPMoves.front().x == nBoardSize && m_GameBoardManager.m_qubmGTPMoves.front().y == 0 && m_GameBoardManager.m_lpemCurrentMove->x == nBoardSize && m_GameBoardManager.m_lpemCurrentMove->y == 0)
		{
			m_fnShowCountResult();
			m_GameBoardManager.m_qubmGTPMoves.pop();
			m_GameBoardManager.m_lpemLivingMove = NULL;
		}
		else
		{
			m_GameBoardManager.OnRedoMove();
			Refresh();
		}
	}
}

void CCanvas::m_fnBackward()
{
	if (m_GameBoardManager.m_lpemCurrentMove->parent != NULL)
	{
		m_GameBoardManager.OnBackMove();
		Refresh();
	}
}

void CCanvas::OnLeftButtonUp(wxMouseEvent &event)
{
	wxPoint ptMouse, ptScroll;
    int x, y, xPos, yPos, iNewStep;
    ptMouse = event.GetPosition();
	ptScroll = GetViewStart();
	xPos = ptMouse.x + ptScroll.x * m_iGridSize;
	yPos = ptMouse.y + ptScroll.y * m_iGridSize;
    x = (xPos - m_iBoardLeft + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
    y = (yPos - m_iBoardTop + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
    if (x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize)
    {
		m_fnChangePosition(x, y);
    }
	else
	{
		x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
		y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
		if (x == 0 && y == 0)
		{
			m_fnChangePosition(nBoardSize, 0);
		}
		else
		{
			x = (xPos - m_iResignTipX + m_iGridSize / 2) / m_iGridSize;
			y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
			if (x == 0 && y == 0)
			{
				m_fnChangePosition(nBoardSize, 1);
			}
			else
			{
				x = ((xPos - m_iProgressGraphX) * 2 + m_iGridSize / 2) / m_iGridSize - 1;
				y = ((yPos - m_iProgressGraphY) * 2 + m_iGridSize / 2) / m_iGridSize;
				if ((x > 0 && y >= 0 && y < 25) || (x == 0 && y == 0))
				{
					iNewStep = (x - 1) * 25 + 13 + (x % 2 * 2 - 1) * (y - 12);
					if (iNewStep >= 0 && iNewStep <= m_GameBoardManager.m_lpemCurrentMove->step + m_GameBoardManager.m_lpemCurrentMove->depth)
					{
						m_GameBoardManager.OnJumpTo(iNewStep);
						Refresh();
					}
				}
			}
		}
	}
}

void CCanvas::OnRightButtonUp(wxMouseEvent &event)
{
	wxMessageDialog MD(this, _(STR_DELETE_BRANCH_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
	wxPoint ptMouse, ptScroll;
	int x, y, xPos, yPos;
	CGameBase::ExtendMove *lpemSearch;
	ptMouse = event.GetPosition();
	ptScroll = GetViewStart();
	xPos = ptMouse.x + ptScroll.x * m_iGridSize;
	yPos = ptMouse.y + ptScroll.y * m_iGridSize;
	x = (xPos - m_iBoardLeft + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
	y = (yPos - m_iBoardTop + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
	lpemSearch = NULL;
	if (x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize || (x == nBoardSize && y == 0))
	{
		lpemSearch = m_GameBoardManager.m_lpemCurrentMove->search(x, y);
	}
	else
	{
		x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
		y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
		if (x == 0 && y == 0)
		{
			lpemSearch = m_GameBoardManager.m_lpemCurrentMove->search(nBoardSize, 0);
		}
	}
	if (lpemSearch == NULL)
	{
		if (m_GameBoardManager.m_lpemCurrentMove->parent != NULL)
		{
			m_GameBoardManager.OnBackMove();
			Refresh();
		}
	}
	else if (lpemSearch->test)
	{
		if (MD.ShowModal() == wxID_OK)
		{
			m_GameBoardManager.OnDeleteBranch(lpemSearch);
			Refresh();
		}
	}
}


void CCanvas::m_fnDrawBuffer(wxDC &dc)
{
	wxPoint ptMouse, ptClient, ptScroll;
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	m_fnDrawGameBoard(dc);
	m_fnDrawCoordinates(dc);
	m_fnDrawPass(dc);
	m_fnDrawMoveTurn(dc);
	m_fnDrawPrisoners(dc);
	m_fnDrawNoMoveChoice(dc);
	m_fnDrawProcess(dc);
	if (m_GameBoardManager.m_bTerritoryMarked)
	{
		m_fnDrawTerritory(dc);
	}
	else
	{
		m_fnDrawStones(dc);
		m_fnDrawRecentMove(dc);
		m_fnDrawBranch(dc);
	}
}

void CCanvas::OnKeyEvent(wxKeyEvent &event)
{
	int iKeyCode;
	iKeyCode = event.GetKeyCode();
	switch (iKeyCode)
	{
	case WXK_LEFT:
		m_fnBackward();
		break;
	case WXK_RIGHT:
		m_fnForward();
		break;
	}
}

void CCanvas::OnSize(wxSizeEvent &event)
{
	m_fnSetSize();
}


void CCanvas::OnPaint(wxPaintEvent&event)
{
    wxAutoBufferedPaintDC dc(this);
	DoPrepareDC(dc);
	m_fnDrawBuffer(dc);
}


BEGIN_EVENT_TABLE(CCanvas, wxScrolledWindow)
EVT_KEY_UP(CCanvas::OnKeyEvent)
EVT_LEFT_UP(CCanvas::OnLeftButtonUp)
EVT_RIGHT_UP(CCanvas::OnRightButtonUp)
EVT_SIZE(CCanvas::OnSize)
EVT_PAINT(CCanvas::OnPaint)
END_EVENT_TABLE()
