#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../Client.h"
#include "Char/CharManager/CharManager.h"
#include "../common/SystemNPC/SystemNPC.h"
#include "Msg/MsgType-ItemMall.h"

#include "NQuestNoticeDlg.h"

CNQuestNoticeDlg::CNQuestNoticeDlg() : CDialogController()
{
	m_siMapIndex	= 0;
	m_siMapNameNum	= 0;
}

CNQuestNoticeDlg::~CNQuestNoticeDlg()
{

}

void CNQuestNoticeDlg::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	//-- ���� ��ü���� ����
	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NQuestNoticeDlg/DLG_NQuestNotice.ddf" ) );
	file.CreatePopupDialog( this, NQUESTNOTICE_DLG, TEXT( "dialog_questnotice" ), StaticQuestNoticeDlgProc );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( IMAGESTATIC,	NQUESTNOTICE_IMAGESTATIC_FACE,	this ), NQUESTNOTICE_IMAGESTATIC_FACE,	TEXT( "imagestatic_face" ) );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( OUTLINE,		NQUESTNOTICE_OUTLINE_FACE,		this ), NQUESTNOTICE_OUTLINE_FACE,		TEXT( "outline_face" ) );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,			NQUESTNOTICE_BUTTON_GOTO,		this ), NQUESTNOTICE_BUTTON_GOTO,		TEXT( "button_goto" ) );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT,			NQUESTNOTICE_EDITBOX_TITLE,		this ), NQUESTNOTICE_EDITBOX_TITLE,		TEXT( "editbox_title" ) );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT,			NQUESTNOTICE_EDITBOX_EXPLAIN,	this ), NQUESTNOTICE_EDITBOX_EXPLAIN,	TEXT( "editbox_explain" ) );


	
	Hide();
}

void CALLBACK CNQuestNoticeDlg::StaticQuestNoticeDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNQuestNoticeDlg *pThis = (CNQuestNoticeDlg*) pControllerMgr;
	pThis->NQuestNoticeDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CNQuestNoticeDlg::NQuestNoticeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{
	switch( nControlID )
	{
		case NQUESTNOTICE_BUTTON_GOTO:
			{
				CheckWarp();
			}
			break;

		case COMMON_DIALOG_CLOSEBUTTON:
			{
				DeleteDialog();
			}
			break;

	}

}

void CNQuestNoticeDlg::Show()
{
	CControllerMgr::Show( true );
}

void CNQuestNoticeDlg::Hide()
{
	CControllerMgr::Show( false );
}

void CNQuestNoticeDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	if ( pData == NULL || DataLen < 1 )
	{
		return;
	}

	if ( false == RetValue )
	{
		return;
	}


	switch ( MsgIndex )
	{
		case 1:
			{
				SI32 siMapIndex = *((SI32*)pData);

				cltGameMsgRequest_HuntMapWarp pclInfo( siMapIndex, 0, false );
				cltMsg clMsg( GAMEMSG_REQUEST_HUNTMAPWARP, sizeof(pclInfo), (BYTE*)&pclInfo );
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
			break;
	}


}

void CNQuestNoticeDlg::CheckNotice()
{
	// �⺻������ �ʱ�ȭ
	m_siMapIndex = 0;

	cltSystemNPC clSystemNPCList[ MAX_SYSTEM_NPC_NUMBER ];
	if ( false == pclClient->pclSystemNPCManager->GetSystemNPCListForShowNotice(clSystemNPCList, MAX_SYSTEM_NPC_NUMBER) )
	{
		return;
	}

	cltSystemNPC	clNoticeSystemNPC;


	for ( SI32 siIndex=0; siIndex<MAX_SYSTEM_NPC_NUMBER; ++siIndex )
	{
		cltSystemNPC* pclSystemNPC = &clSystemNPCList[siIndex];
		if ( (NULL == pclSystemNPC) || (0 >= pclSystemNPC->m_siShowNotice) )
		{
			break;
		}
		
		CheckCondition( pclSystemNPC, &clNoticeSystemNPC );
	}

	if ( 0 < clNoticeSystemNPC.m_siShowNotice )
	{
		DisplayNoticeDlg( &clNoticeSystemNPC );
	}
	else
	{
		DeleteDialog();
	}
}

void CNQuestNoticeDlg::CheckCondition( IN cltSystemNPC* pclConditionNPC, OUT cltSystemNPC* pclResultNPC )
{
	if ( (NULL == pclConditionNPC) || (NULL == pclResultNPC) )
	{
		return;
	}

	cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[1];
	if ( NULL == pclchar )
	{
		return;
	}

	// �ش�����Ʈ�� �̹� �������̰ų� Ŭ���� �ߴٸ� �ٷ� ����
	SI32 siQuestType = pclConditionNPC->m_siQuestType;
	if ( true == pclchar->pclCI->clQuestInfo.IsQuestClearOrGoing(siQuestType) )
	{
		return;
	}
	
	cltQuestInfo* pclQuestInfo = &pclClient->pclQuestManager->clQuestInfo[siQuestType][0];
	if ( NULL == pclQuestInfo )
	{
		return;
	}

	SI32 siNowLevel		= pclchar->pclCI->clIP.GetLevel();
	SI32 siNeedLevel	= pclQuestInfo->clInitConditionInfo.siLevel;
	SI16 siClearCond	= pclQuestInfo->clQuestClearConditionInfo.siFlag;
	SI32 siQuestUinque	= pclQuestInfo->clQuestClearConditionInfo.siPara1;
	bool bLevelCheck	= false;
	bool bCondCheck		= true;	// �ʱⰪ�� true�� �� ������ �ڵ����� ���̱� ����

	// ������ ��������Ʈ ������ ���� �ٸ��� ����ɼ� �����Ƿ� �и��ؼ� �˻�
	if ( siNeedLevel <= siNowLevel )
	{
		bLevelCheck = true;
	}

	if ( QUEST_CLEAR_COND_CLEARQUEST == siClearCond )
	{
		if ( true == pclchar->pclCI->clQuestInfo.IsClear(pclClient->pclQuestManager, siQuestUinque) )
		{
			bCondCheck = true;
		}
		else
		{	
			bCondCheck = false;
		}
	}

	// �������� ������ų��
	if ( (true == bLevelCheck) && (true == bCondCheck) )
	{
		if ( 0 >= pclResultNPC->m_siShowNotice )
		{
			pclResultNPC->Set( pclConditionNPC );
		}
		else if( pclConditionNPC->m_siShowNotice < pclResultNPC->m_siShowNotice )
		{
			pclResultNPC->Set( pclConditionNPC );
		}
	}

}

void CNQuestNoticeDlg::DisplayNoticeDlg( cltSystemNPC* pclNoticeNPCInfo )
{
	if ( NULL == pclNoticeNPCInfo )
	{
		return;
	}

	CImageStatic*	pclFaceImage	= m_InterfaceFactory.GetImageStatic( NQUESTNOTICE_IMAGESTATIC_FACE );
	CEdit*			pclTitleEdit	= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_TITLE );
	CEdit*			pclExplainEdit	= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_EXPLAIN );

	if ( (NULL == pclFaceImage) || (NULL == pclTitleEdit) || (NULL == pclExplainEdit) )
	{
		return;
	}

	TCHAR	szFileName[512] = { '\0', };
	SI32	siFont = 0;

	if ( false == pclClient->pclKindInfoSet->GetNPCImageFileAndFont(pclNoticeNPCInfo->m_siKind, szFileName, 512, &siFont) )
	{
		return;
	}
	
	pclFaceImage->SetFileName( szFileName );
	pclFaceImage->SetFontIndex( siFont );

	pclTitleEdit->SetText( GetTxtFromMgr(pclNoticeNPCInfo->m_siNoticeExplainNum) );
	pclExplainEdit->SetText( GetTxtFromMgr(pclNoticeNPCInfo->m_siNoticeLocationNum) );

	Show();

	m_siMapIndex	= pclNoticeNPCInfo->m_siMapIndex;
	m_siMapNameNum	= pclNoticeNPCInfo->m_siLocationNum;

}

void CNQuestNoticeDlg::CheckWarp( void )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	cltCharCommon* pclchar = (cltCharCommon*)pclClient->pclCM->CR[1];
	if ( NULL == pclchar )
	{
		return;
	}

	if ( false == pclchar->CanWarpFrom() )
	{
		return;
	}

	// Ȥ�� �𸣴� �� �ε��� �˻�
	if ( (0 >= m_siMapIndex) || (MAX_MAP_NUMBER <= m_siMapIndex) )
	{
		return;
	}

	SI32 siTitleNum	= 0;
	SI32 siTextNum	= 0;
	
	// ��¥ ���� �˻�
	if ( pclchar->CanFreeWarp(m_siMapIndex) )
	{
		siTitleNum	= (3189);
		siTextNum	= (3760);
	}
	// ����Ƽ�ϰ˻�
	else if ( 0 < pclchar->pclCI->clCharItem.GetItemNum(ITEMUNIQUE( 24000 )) )
	{
		siTitleNum	= (3326);
		siTextNum	= (3332);
	}
	// �ȵǸ� ����
	else
	{
		TCHAR* pszTitle	= GetTxtFromMgr(3326);
		TCHAR* pszText	= GetTxtFromMgr(3756);

		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pszTitle, pszText );
		return;
	}

	SetRetMsgBox( siTitleNum, siTextNum );
}

void CNQuestNoticeDlg::SetRetMsgBox( SI32 siTitleNum, SI32 siTextNum )
{
	if ( (0 >= siTitleNum) || (0 >= siTextNum) )
	{
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	// �ؽ�Ʈ �޴������� ���� �̸��� �̾ƿ���
	TCHAR* pszMapName = GetTxtFromMgr( m_siMapNameNum );
	if ( NULL == pszMapName )
	{
		// ���� �ȵǸ� MapIndex�� �����̸��� �̾ƿ´�
		pszMapName = pclClient->pclMapManager->GetMapName( m_siMapIndex );
		if ( NULL == pszMapName )
		{
			return;
		}
	}

	TCHAR*	pTitle			= GetTxtFromMgr(siTitleNum);
	TCHAR*	pText			= GetTxtFromMgr(siTextNum);
	TCHAR	szBuffer[256]	= { '\0', };

	StringCchPrintf( szBuffer, 256, pText, pszMapName);

	stMsgBox MsgBox;
	MsgBox.Set( this, pTitle, szBuffer, MSGBOX_TYPE_YESNO, 1 );

	// Ȥ�� �������� �� �ε����� �ٲ�������� �� �ε����� ���⿡�� ���ڷ� �����ش�
	BYTE TempBuffer[ 128 ];
	SI16 Size = 0;
	memcpy( &TempBuffer[Size], &m_siMapIndex, sizeof(m_siMapIndex) );	Size += sizeof(m_siMapIndex);

	pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

}

void CNQuestNoticeDlg::NoticeEvent( SI32 siNpcKind, SI32 siMapIndex )// �̺�Ʈ�� �ش� ��ġ�� ���ǽ� ���� ��Ÿ���� ���ؼ�
{
	// ���� ����Ʈ �̵� ��ư�� ������ �ʵ��� �Ѵ�
	m_InterfaceFactory.GetButton( NQUESTNOTICE_BUTTON_GOTO )->Show( false );
	CImageStatic*	pclFaceImage	= m_InterfaceFactory.GetImageStatic( NQUESTNOTICE_IMAGESTATIC_FACE );
	CEdit*	pcNPCEditTitle		= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_TITLE );
	CEdit*	pcNPCEditExplain	= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_EXPLAIN );
	
	// ���� �����ְ�
	TCHAR	szFileName[512] = { '\0', };
	SI32	siFont = 0;

	if ( false == pclClient->pclKindInfoSet->GetNPCImageFileAndFont(siNpcKind, szFileName, 512, &siFont) )
	{
		return;
	}
	pclFaceImage->SetFileName( szFileName );
	pclFaceImage->SetFontIndex( siFont );

	// �ؽ�Ʈ ���븸 �������ָ� ��
	TCHAR* NpcEdit = GetTxtFromMgr( 8867 );

	NTCHARString256	strText( GetTxtFromMgr(8868) );
	strText.Replace( TEXT("#map#"),		pclClient->pclMapManager->GetMapName( siMapIndex ) );

	pcNPCEditTitle->SetText( NpcEdit );
	pcNPCEditExplain->SetText( strText );
	Show();

}

void CNQuestNoticeDlg::NoticeEvent( SI32 siNpcKind, const TCHAR* pszTitle, const TCHAR* pszExplain ) // �ؽ�Ʈ ������ ������ ä���ִ� �Լ�
{
	// ���� ����Ʈ �̵� ��ư�� ������ �ʵ��� �Ѵ�
	m_InterfaceFactory.GetButton( NQUESTNOTICE_BUTTON_GOTO )->Show( false );
	CImageStatic*	pclFaceImage	= m_InterfaceFactory.GetImageStatic( NQUESTNOTICE_IMAGESTATIC_FACE );
	CEdit*	pcNPCEditTitle		= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_TITLE );
	CEdit*	pcNPCEditExplain	= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_EXPLAIN );

	// ���� �����ְ�
//	TCHAR	szFileName[512] = { '\0', };
//	SI32	siFont = 0;

//	if ( false == pclClient->pclKindInfoSet->GetNPCImageFileAndFont(siNpcKind, szFileName, 512, &siFont) )
//	{
//		return;
//	}
//	pclFaceImage->SetFileName( szFileName );
//	pclFaceImage->SetFontIndex( siFont );
	
	pclFaceImage->SetFileName("Gimg/hcandy.SPR");
	pclFaceImage->SetFontIndex( 0 );

	// �ؽ�Ʈ ���븸 �������ָ� ��
	pcNPCEditTitle->SetText( (TCHAR*)pszTitle );
	pcNPCEditExplain->SetText( (TCHAR*)pszExplain );
	Show();

}
void CNQuestNoticeDlg::NoticeEvent2( SI32 siNpcKind, const TCHAR* pszTitle, const TCHAR* pszExplain )// �̺�Ʈ�� �ش� ��ġ�� ���ǽ� ���� ��Ÿ���� ���ؼ�
{
	// ���� ����Ʈ �̵� ��ư�� ������ �ʵ��� �Ѵ�
	m_InterfaceFactory.GetButton( NQUESTNOTICE_BUTTON_GOTO )->Show( false );
	CImageStatic*	pclFaceImage	= m_InterfaceFactory.GetImageStatic( NQUESTNOTICE_IMAGESTATIC_FACE );
	CEdit*	pcNPCEditTitle		= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_TITLE );
	CEdit*	pcNPCEditExplain	= m_InterfaceFactory.GetEdit( NQUESTNOTICE_EDITBOX_EXPLAIN );

	// ���� �����ְ�
	TCHAR	szFileName[512] = { '\0', };
	SI32	siFont = 0;

	if ( false == pclClient->pclKindInfoSet->GetNPCImageFileAndFont(siNpcKind, szFileName, 512, &siFont) )
	{
		return;
	}
	pclFaceImage->SetFileName( szFileName );
	pclFaceImage->SetFontIndex( siFont );

	pcNPCEditTitle->SetText( (TCHAR*)pszTitle );
	pcNPCEditExplain->SetText( (TCHAR*)pszExplain );
	Show();

}