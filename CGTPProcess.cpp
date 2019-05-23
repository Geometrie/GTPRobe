#include "CGTPProcess.h"
CGTPProcess::CGTPProcess(wxEvtHandler *lpParent, int nId): wxProcess(lpParent, nId)
{
	m_bAlive = false;
}
