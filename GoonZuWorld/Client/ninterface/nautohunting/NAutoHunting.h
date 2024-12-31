//---------------------------------
// 2004/9/01 ���ؿ�
//---------------------------------
/* ==========================================================================
	Ŭ���� :		CNStaticNAutoHuntingDlgMsgProc

	�ۼ��� :		05/03/25
	�ۼ��� :		���¾�

	��  �� :		

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/
#pragma once

#include <Directives.h>

#define MAX_SUSPECT_NUM		3000

#define PRISON_TIME			300

#define CLIENT_UPDATE_TIME			2
#define NOSUSPICTION_PRISON_TIME	5	// ��ũ�� ����� ���� �Ű�� ���� �ð�(��) 

#ifdef _CHINA
	#define REPORT_MINLEVEL			70
#else
	#define REPORT_MINLEVEL			20
#endif

#include "../../../Resource.h"
#include "../../InterfaceMgr/DialogController.h"

class CStatic;
class CEdit;
class CButton;


class CNcltAutoHuntingManager : public CDialogController
{
public: // Client
	CNcltAutoHuntingManager();
	~CNcltAutoHuntingManager();

	void Create();

	static void CALLBACK StatiCNAutoHuntingDlgMsgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NAutoHuntingDlgMsgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	// Txt : �䱸�ܾ�,request : �Ƿ��� �̸�
	void Set(TCHAR * Txt,SI32 slot,SI32 minuts,SI16 prisontime,SI16 prisonerpenalty);
	
	void Action();
	void SetStaticTime(SI32 totaltime);
	
	void SetLeftTime(SI32 time)
	{
		m_siLeftTime = time;
	}
	SI32 GetLeftTime()
	{
		return m_siLeftTime ;
	}

	
private: // Client
	
	CStatic     	*m_pAutoHuntStatic1;
	CEdit       	*m_pAutoHuntStatic2;
	CStatic     	*m_pAutoHuntStatic3;
	CStatic     	*m_pAutoHuntStatic4;
	CButton			*m_pAutoHuntButton;
	CEdit           *m_pAutoHuntEdit;    

	SI32	m_siLeftTime;
	SI32	m_siSlot;

	



};
