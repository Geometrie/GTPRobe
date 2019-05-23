#include <fstream>
#include "CGTPReceiver.h"
#include <fstream>
#define horizonal_coord_range(x) (((x) >= 'A' && (x) <= 'H') || ((x) >= 'a' && (x) <= 'h') || ((x) >= 'J' && (x) <= 'T') || ((x) >= 'j' && (x) <= 't'))
CGTPReceiver::CGTPReceiver(): wxThread()
{
}

wxThread::ExitCode CGTPReceiver::Entry()
{
	int i, j;
	char lpstrBuffer[256], lpstrMessage[256];
	CGameBase::BaseMove bmNewMove;
	m_bKeepLoop = true;
	while (m_bKeepLoop)
	{
		m_lpInputStream->Read(lpstrBuffer, 1);
		if (lpstrBuffer[0] == '(')
		{
			i = 0;
			do
			{
				++i;
				m_lpInputStream->Read(lpstrBuffer + i, 1);
			} while (lpstrBuffer[i] != ')');
			memset(lpstrMessage, 0, 256 * sizeof(char));
			for (j = 1; j < i; ++j)
			{
				lpstrMessage[j - 1] = lpstrBuffer[j];
			}
			if (i >= 1 && i < 256)
			{
				lpstrMessage[i - 1] = '\0';
				bmNewMove.import_move(lpstrMessage);
				if ((bmNewMove.stone_color == SC_BLACK || bmNewMove.stone_color == SC_WHITE) && ((bmNewMove.x >= 0 && bmNewMove.x < nBoardSize && bmNewMove.y >= 0 && bmNewMove.y < nBoardSize) || (bmNewMove.x == nBoardSize && (bmNewMove.y == 0 || bmNewMove.y == 1))))
				{
					m_lpCanvas->m_GameBoardManager.m_qubmGTPMoves.push(bmNewMove);
					if (m_lpCanvas->m_GameBoardManager.m_lpemLivingMove == m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove)
					{
						m_lpCanvas->m_TerritoryMutex.Lock();
						m_lpCanvas->m_fnForward();
						m_lpCanvas->m_TerritoryMutex.Unlock();
					}
				}
				else
				{
					bmNewMove.stone_color = SC_NULL;
				}
			}
			memset(lpstrBuffer, 0, 256 * sizeof(char));
		}
	}
    return wxThread::ExitCode(0);
}
