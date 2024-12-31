// [����] ��ť �ŷ�â ������
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/WorldPassport/WorldPassport.h"

class CNAcuTradeDlg_Passport : public CDialogController
{
// ��������
private:
	InterfaceFactory	m_InterfaceFactory;

// �Լ�����
public:
	CNAcuTradeDlg_Passport();
	~CNAcuTradeDlg_Passport();

	void Create(CControllerMgr* pParent);

	static void CALLBACK StaticAcuTradeDlg_PassportProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NAcuTradeDlg_PassportProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

	void Show();
	void Hide();

	void Refresh();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:
	void SetController( void );
	void ShowNotifyMsg( SI32 siTitleNum, SI32 siTextNum );
	void ShowNotifyMsg( TCHAR* pszTitle, TCHAR* pszText );

	void CheckTheCorrectID( void );

	void OrderToIssue( void );	// ���� �߱�
	void OrderToExtend( void );	// ���� ����


};
