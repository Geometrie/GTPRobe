#include "CGTPInquirer.h"
CGTPInquirer::CGTPInquirer()
{
	m_lpOutputStream = NULL;
}

void CGTPInquirer::m_fnGTPSendInquire(wxString &wxstrCommand)
{
	if (m_lpOutputStream != NULL)
	{
		m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
	}
}

void CGTPInquirer::m_fnGTPEnd()
{
	if (m_lpOutputStream != NULL)
	{
		m_lpOutputStream->Write("q\n", 2);
	}
}