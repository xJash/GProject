#ifndef _MAINFUNCTION_H
#define _MAINFUNCTION_H

#include <Directives.h>

//--------------------------------------------------------------------------
// Name: WindowProc()
// Desc: ������ Procedure
//-------------------------------------------------------------------------- 
LRESULT WINAPI WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------
// Name: GetVersionInfo()
// Desc: ���� ������ ���´�.
//--------------------------------------------------------------------------
TCHAR* GetVersionInfo();

//--------------------------------------------------------------------------
// Name: Restore()
// Desc: �̴ϸ������ ���¿��� �ٽ� �����Ҷ� ���Ǵ� �Լ� 
//--------------------------------------------------------------------------
BOOL Restore();

//KHY - 0701 - ��Ű �̺�Ʈ (F1~F12)�� 0.3�ʿ� �ѹ����� �۵��ϵ��� �Ѵ�.
bool UserdoubleKeyEvent(SI32 KeyEvent);

// ���߿� �޽����� �߰��Ѵ�.
void AddDevMsg(TCHAR* pmsg);

//�Ѱ��� ��ǥ ���
#if defined (USE_HANPOLL)
	// �Ѱ��� ���� ���� ���
	#include "../HanPollForClient/HanPollForClient.h"
#endif

#endif
