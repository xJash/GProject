#pragma once

#include "../InterfaceMgr/DialogController.h"
//#include "..\CommonLogic\PostOffice\PostOffice.h"

class CButton;
class CStatic;


// ���� ��ȸ ���� ����
class NGeneralMeetingLetterDlg : public CDialogController
{
public:

	CStatic*			m_pStatic;
	CStatic*			m_pStatic1;//������ ���� ���� �޺κ��� ©���⿡ ����ƽ �и�. [2007.07.05 �ռ���]
	CButton*			m_pButton[2];

	NGeneralMeetingLetterDlg();
	~NGeneralMeetingLetterDlg();

	void Create();

	void InitInfo();
	void AddInfo( int villageunique );
	void SetText();

	static void CALLBACK StaticCallBackDialogNGeneralMeetingLetterDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNGeneralMeetingLetterDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	SI32 m_siVillageUnique[ MAX_STOCK_KIND_IN_ACOUNT ];
	SI32 m_curIndex;

};