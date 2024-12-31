//=====================================================================
// PICAManager.h
//=====================================================================

#ifndef _PICAMANAGERCHECK_H_
#define _PICAMANAGERCHECK_H_

#include "ITZHttpConnect.h"

class cltPICAManagerCheck
{
public:
	cltPICAManagerCheck();
	~cltPICAManagerCheck();

	//=====================================================================
	// �Ѱ��� PC�� ��ī�޴��� Ȯ��
	//=====================================================================
	void				Request_PICAManager( TCHAR* pszIP );
	BOOL				CheckUpdate_PICAManager();
	BOOL				m_bPCBang;

private:
	BOOL				m_bRequest;

public:
	ITZHttpConnect		m_httpconnect;
};

#endif