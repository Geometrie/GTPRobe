#ifndef CLZRECEIVER_H
#define CLZRECEIVER_H
#include "CCanvas.h"
class CGTPReceiver: public wxThread
{
public:
    CGTPReceiver();
    virtual wxThread::ExitCode Entry();
    CCanvas *m_lpCanvas;
    wxInputStream *m_lpInputStream;
    bool m_bKeepLoop;
protected:
};
#endif // CLZRECEIVER_H
