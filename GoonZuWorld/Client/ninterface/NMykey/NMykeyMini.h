/* ==========================================================================
Ŭ���� :		 

�ۼ��� :		 
�ۼ��� :		 

������� :		 

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class CNMykeyMiniDlg : public CDialogController
{
public:

	CNMykeyMiniDlg();
	~CNMykeyMiniDlg();

	void Init();

	void Create();
	void Destroy();
	void Action();

	static void CALLBACK StaticNMykeyMiniDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NMykeyMiniProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	void SetDialogKind(SI32* _psiDialogKind);	
	void KeyAction( SI32 _KeyKind );

	void SaveFile();
	void LoadFile();

private:
	InterfaceFactory	m_InterfaceFactory;

	SI32				m_siDialogKind[MYKEY_NUM];		// ���̾�α� ����(��ȣ)�� ����.
};
 