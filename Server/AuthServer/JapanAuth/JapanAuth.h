#ifndef _JAPANAUTH_H_
#define _JAPANAUTH_H_

#include <windows.h>
#include "AuthInfo.h"

#ifdef JAPANAUTH_EXPORTS
	#define JAPANAUTH_API __declspec(dllexport)
#else
	#define JAPANAUTH_API __declspec(dllimport)
#endif

typedef int (CALLBACK* JAPANAUTHCALLBACK) (AuthInfo, int);

JAPANAUTH_API int JapanAuthInit(int nThreadCount, JAPANAUTHCALLBACK CallBack);
JAPANAUTH_API void JapanAuthShutdown();

JAPANAUTH_API int JapanAuth_GamaniaAuth(AuthInfo Info);	// For �����Ͼ�
JAPANAUTH_API int JapanAuth_GamepotAuth(AuthInfo Info);	// For ������
JAPANAUTH_API int USAAuth_NHNAuth(AuthInfo Info);		// [����] USA ���ο� ����.

#endif