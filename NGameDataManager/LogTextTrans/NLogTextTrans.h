//=============================================================================
//
//=============================================================================
#ifndef _NLOGTEXTTRANS_H_
#define _NLOGTEXTTRANS_H_

#include "../../NetworkLib/ITZNetLib/itzbase.h"

class NLogTextTrans
{
public:
	TCHAR		m_szCommand[128];	// LogText�� Ŀ�ǵ�����
	TCHAR		m_szType[128];		// LogText�� Ÿ��
	SI32		m_siIndex;			// �ؽ�Ʈ�� ��ȯ�� Index
	TCHAR		m_szText[128];		// ��ȯ�� �ؽ�Ʈ

public:
	NLogTextTrans()
	{
		m_szCommand[0]	= '\0';
		m_szType[0]	= '\0';
		m_siIndex = 0;
		m_szText[0] = '\0';
	}

	~NLogTextTrans()
	{
	}

	void Set()
	{

	}
};

#endif
