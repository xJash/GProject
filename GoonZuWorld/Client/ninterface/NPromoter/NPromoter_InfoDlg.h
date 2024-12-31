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

#include "../../Promoter/NHNChinaPromoter.h"

#include "../../../Server/ServerReward/ServerReward.h"

class CInterfaceFile;	

class NPromoter_InfoDlg : public CDialogController
{
public:

	NPromoter_InfoDlg();
	~NPromoter_InfoDlg();

	void 	Init( CInterfaceFile* _pfile );

	void 	Create();								// �����ϰ� �� â�� ���.
	void	Create( CControllerMgr *pParent );		// ��õ�� NPC�� ����â�� ������ �߰��ɶ� ����Ѵ�.

	void	VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );

	void 	Destroy();
	void 	Action();

	void	SetPotrait( void );
	void	RequestPromoter( void );
	void	SetPromoterInfo( SI16 _siKind, SI16 _siLevel, bool _bAuth, TCHAR* _pszPromoterCharName );
	void	SetGiveItem( SI32* _pItemUnique, SI32* _pItemNum );

	void	Hide();
	void	Show();

	
	static void CALLBACK StatiNPromoter_InfoDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NPromoter_InfoDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

   
private:
	InterfaceFactory	m_InterfaceFactory;
	
	SI32				m_siImageType;
	SI32				m_siImageIndex;
	SI32				m_GiveItemUnique[Const_Max_RecommandReward_Item];

	char 				m_promoterCharid[NHNCHINAPROMOTER_PROMOTER_CHARID_SIZE];

	bool				m_bChildCreate;	// �� â�� Ȱ��ȭ �Ǵ� ��찡 2������. NRPBASE_DLG�� �ڽ�â�� ���� �ƴѰ��.
};
 