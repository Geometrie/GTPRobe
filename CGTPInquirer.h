#ifndef CLZINQUIRER_H
#define CLZINQUIRER_H
#include <wx/string.h>
#include <wx/stream.h>
#include <wx/thread.h>
#include "CSGFFileIO.h"
#include "International.h"

class CGTPInquirer
{
public:
	wxOutputStream *m_lpOutputStream;
	CSGFFileIO m_GameBoardManager;
	CGTPInquirer();
	void m_fnGTPSendInquire(wxString &wxstrCommand);
	void m_fnGTPEnd();
};
#endif