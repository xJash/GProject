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
#include "MsgType-System.h"

class NElixirNPCDlg : public CDialogController
{
public:

	NElixirNPCDlg();
	~NElixirNPCDlg();

	void Init();

	void Create();
	void Destroy();
	void Action();

	static void CALLBACK StatiNElixirNPCDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NElixirNPCDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	void SetItemListInfo( SI32* siItemUnique, SI32* siWaterNum );	// �޺��ڽ��� �ش��ϴ� �������� ������ �������� �޾� ����Ʈ�ڽ��� ����.
	void SetMyInventory();											// �� �κ��丮�� �޺��ڽ��� �ش��ϴ� ������ ������ �߰��ϱ�~
	void SetSelectItem();											// ����Ʈ �ڽ��� ���õ� ������ �̹����� ���̱����� ����Ʈ�信 �߰�.

private:
	InterfaceFactory	m_InterfaceFactory;

	bool				m_bClickSelectItem;
	SI32				m_siComboBoxItemtype;
	SI32				m_siSelectChangeItemInvenPos;

	SI32				m_siItemUnique[ELIXIR_LIST_NUM]; 
	SI32				m_siWaterNum[ELIXIR_LIST_NUM];
};
 