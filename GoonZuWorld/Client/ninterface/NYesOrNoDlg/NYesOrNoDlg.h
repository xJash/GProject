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

enum REASON
{
	NONE
	,REASON_VILLAGE_RESIDENT_INVITE		// ���� �ֹ� ���� �ʴ�.(������ �ʴ�.)
	,REASON_HELPER_ALREADY_QUESTION		// �����. �ߺ����� ������ �Ϸ��� ���.
	,REASON_ELIXIR_SET					// ������ ����.
};


class CNYesOrNoDlg : public CDialogController
{
public:

	CNYesOrNoDlg();
	~CNYesOrNoDlg();

	void Init();

	void Create();
	void Destroy();
	void Action();

	static void CALLBACK StaticNYesOrNoDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NYesOrNoDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	void Yes( void );
	void No( void );
	void SetText( TCHAR* pStr );

	void SetVillageResidentInvite( SI32 _siCreateReason, NTCHARStringName _kCharName, SI32 _siPara1 );
	void SetHelpMe( SI32 _siCreateReason, NTCHARStringName _kCharName, SI32 _siPara1 );
	void SetHelpYesorNo( SI32 _siCreateReason, SI32 _siPara1 );
	void SetHelperAlreadyQuestion( void );
	void SetElixirNew( void );

private:
	InterfaceFactory	m_InterfaceFactory;

	SI32				m_siCreateReason;			// ��â�� ������ ����.(�̰����� ��, �ƴϿ� ��ư�� �����ÿ� ó���� ����.)
	SI32				m_siPara1;					// REASON_VILLAGE_RESIDENT_INVITE : ���� ���� ����ũ.
	NTCHARStringName	m_kCharName;				// REASON_VILLAGE_RESIDENT_INVITE : ������. REASON_HELP_ME : ���� ��û�� �� ĳ���� �̸�.
};
