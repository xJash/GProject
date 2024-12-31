// ��Ƽ��Ī
#include "NPartyMatching_SelectQuestDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client.h"

#include "../../CommonLogic/CommonLogic.h"
#include "Char/CharManager/CharManager.h"

#include "../../CommonLogic/PartyQuestMgr/PartyQuestMgr_Common.h"








extern cltCommonLogic* pclClient;








CNSelectQuest_PartyMatching::CNSelectQuest_PartyMatching( void )
{
	ZeroMemory( paButtonList, sizeof(paButtonList) );

	m_pImageStatic_portrait = NULL;
}

CNSelectQuest_PartyMatching::~CNSelectQuest_PartyMatching( void )
{

}

void CNSelectQuest_PartyMatching::Init( )
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) DeleteDialog();
	if ( NULL == pClient->m_pPartyQuestMgr ) DeleteDialog();
	CPartyQuestMgr_Common* pPQMgr = (CPartyQuestMgr_Common*)pClient->m_pPartyQuestMgr;
	//-----------------------------------------------------------------------------------

	SI08 siShowButtonCount = 0;
	SI16 siCurrent_XPos = 22;		// ��ȭ���� ���ҽ����� �� ���� ��ġ�� ��ư�� x ��ǥ
	SI16 siCurrent_YPos = 162;		// ��ȭ���� ���ҽ����� �� ���� ��ġ�� ��ư�� y ��ǥ
	SI16 siButtonHeight = 24;				// ��ư�� ����
	SI16 siWhiteSpace = 8;					// ��ư ������ ���� ����
	SI16 siNeedSpace = siButtonHeight + siWhiteSpace;	// ��ư �ϳ��� ���� ���� �ʿ��� ��ư+������ ������ ����
	bool bHasPCroomQuest = false;			// �Ǿ��� ī�װ��� ���۵ƴ�. (�Ǿ��� ����Ʈ ����ƽ �ؽ�Ʈ ��� ���ؼ�)

	for ( SI08 i = 0; i < MAX_PARTYQUEST_CATEGORY_NUM; ++i )
	{
		PartyQuest_CatecoryData* pCategoryData = NULL;
		pCategoryData = pPQMgr->GetPartyQuestCategoryData(i);

		if ( NULL == pCategoryData || 0 >= pCategoryData->m_siKind )
		{
			if ( NULL != paButtonList[i] )
			{
				paButtonList[i]->Enable( false );
				paButtonList[i]->Show( false );
			}
		}
		else
		{
			if ( NULL != paButtonList[i] )
			{
				// ��ư �ؽ�Ʈ ����
				NTCHARString256 strText;

				if ( PARTYQUEST_KIND_PCROOM == pCategoryData->m_siKind )
				{
					if ( false == bHasPCroomQuest )
					{
						bHasPCroomQuest = true;
						// ����ƽ �ؽ�Ʈ ���, �׸�ŭ�� y �� �÷���
						siCurrent_YPos += 4;

						CStatic* pPCBangText = NULL;
						pPCBangText = m_InterfaceFactory.GetStatic( NSELECT_QUEST_BASE_DLG_STATICTEXT_PCBANG_QUEST );
						pPCBangText->SetY( siCurrent_YPos );
						pPCBangText->Show( true );

						siCurrent_YPos += 18 + siWhiteSpace;
					}

					strText = GetTxtFromMgr( 40805 );			// "#level# ���� ���� PC�� ����Ʈ"
				}
				else if ( PARTYQUEST_KIND_NORMAL == pCategoryData->m_siKind )
				{
					strText = GetTxtFromMgr( 40804 );			// "#level# ���� ��Ƽ ����Ʈ"
				}

				NTCHARString32 strLevel;
				strLevel = SI16ToString( pCategoryData->m_siMinLevel );
				strLevel = strLevel + TEXT("~");
				strLevel = strLevel + ((TCHAR*)(SI16ToString( pCategoryData->m_siMaxLevel )));
				strText.Replace( TEXT("#level#"), strLevel );

				paButtonList[i]->SetText( strText, paButtonList[i]->GetTextPrintOption() );

				// ��ư ��ǥ ����
				paButtonList[i]->SetX( siCurrent_XPos );
				paButtonList[i]->SetY( siCurrent_YPos );
				siCurrent_YPos += siNeedSpace;

				// ���
				paButtonList[i]->Show( true );
				++siShowButtonCount;
			}
		}
	}

	// [�ݱ�] ��ư�� ��ġ ����
	CButton* pCloseButton = NULL;
	pCloseButton = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CLOSE );
	if ( NULL != pCloseButton )
	{
		pCloseButton->SetY( siCurrent_YPos );
		siCurrent_YPos += 30;
	}

	// ��ȭ������ ũ�⸦ �����Ѵ�
	this->SetHeight( siCurrent_YPos );
}

void CNSelectQuest_PartyMatching::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	this->Show( false );

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NPartyMatchingDlg/DLG_NSelect_Level_PartyQuest_Dlg.ddf" ) );
	file.CreatePopupDialog( this, NSELECT_QUEST_BASE_DLG, TEXT( "dialog_select_quest_base" ), StaticCallBackDialogNSelectQuest_PartyMatching );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC, NSELECT_QUEST_BASE_DLG_IMAGESTATIC_NPC_IMG, this), NSELECT_QUEST_BASE_DLG_IMAGESTATIC_NPC_IMG, TEXT("imagestatic_npc_img") );
	//file.CreateControl( m_pImageStatic_portrait, NSELECT_QUEST_BASE_DLG_IMAGESTATIC_NPC_IMG	, TEXT("imagestatic_npc_img") );	// ��Ƽ��Ī npc ��
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT, NSELECT_QUEST_BASE_DLG_EDITBOX_NPC_SAYS, this), NSELECT_QUEST_BASE_DLG_EDITBOX_NPC_SAYS, TEXT("editbox_npc_says") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC, NSELECT_QUEST_BASE_DLG_STATICTEXT_PARTY_QUEST, this), NSELECT_QUEST_BASE_DLG_STATICTEXT_PARTY_QUEST, TEXT("statictext_party_quest") );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC, NSELECT_QUEST_BASE_DLG_STATICTEXT_PCBANG_QUEST, this), NSELECT_QUEST_BASE_DLG_STATICTEXT_PCBANG_QUEST, TEXT("statictext_pcbang_quest") );
	
	CStatic* pPCBangText = NULL;
	pPCBangText = m_InterfaceFactory.GetStatic( NSELECT_QUEST_BASE_DLG_STATICTEXT_PCBANG_QUEST );
	pPCBangText->Show( false );

	// npc �� �̹���
	SI32 siNpcKind = pclClient->GetUniqueFromHash( TEXT("KIND_PARTYQUESTNPC") );
	TCHAR szPortrait[256];
	SI32 siPortraitFont;
	pclClient->pclKindInfoSet->GetNPCImageFileAndFont(siNpcKind, szPortrait, sizeof(szPortrait), &siPortraitFont);
	m_pImageStatic_portrait = m_InterfaceFactory.GetImageStatic( NSELECT_QUEST_BASE_DLG_IMAGESTATIC_NPC_IMG );
	m_pImageStatic_portrait->SetFileName( szPortrait );
	m_pImageStatic_portrait->SetFontIndex( siPortraitFont );

	// ��ư���� �ϴ� ���δ� �����صд�.
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_01, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_01, TEXT("button_quest_01") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_02, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_02, TEXT("button_quest_02") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_03, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_03, TEXT("button_quest_03") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_04, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_04, TEXT("button_quest_04") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_05, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_05, TEXT("button_quest_05") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_06, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_06, TEXT("button_quest_06") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_07, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_07, TEXT("button_quest_07") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_08, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_08, TEXT("button_quest_08") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_09, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_09, TEXT("button_quest_09") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_10, this), NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_10, TEXT("button_quest_10") );

	paButtonList[0] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_01 );
	paButtonList[1] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_02 );
	paButtonList[2] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_03 );
	paButtonList[3] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_04 );
	paButtonList[4] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_05 );
	paButtonList[5] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_06 );
	paButtonList[6] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_07 );
	paButtonList[7] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_08 );
	paButtonList[8] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_09 );
	paButtonList[9] = m_InterfaceFactory.GetButton( NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_10 );



	//file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_11_20, this), NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_11_20, TEXT("button_quest_11_20") );
	//file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_21_30, this), NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_21_30, TEXT("button_quest_21_30") );
	//file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_31_40, this), NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_31_40, TEXT("button_quest_31_40") );
	//file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_41_50, this), NSELECT_QUEST_BASE_DLG_BUTTON_QUEST_41_50, TEXT("button_quest_41_50") );

	// PC�� ����Ʈ
	//
	//file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_PCBANG_1_50, this), NSELECT_QUEST_BASE_DLG_BUTTON_PCBANG_1_50, TEXT("button_pcbang_1_50") );
	//file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_PCBANG_51, this), NSELECT_QUEST_BASE_DLG_BUTTON_PCBANG_51, TEXT("button_pcbang_51") );
	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NSELECT_QUEST_BASE_DLG_BUTTON_CLOSE, this), NSELECT_QUEST_BASE_DLG_BUTTON_CLOSE, TEXT("button_close") );

	CEdit* pclExplain = m_InterfaceFactory.GetEdit( NSELECT_QUEST_BASE_DLG_EDITBOX_NPC_SAYS );
	if( pclExplain )
	{
		pclExplain->SetText( GetTxtFromMgr(40809) ); // test - �ؽ�Ʈ �����ؾ� ��.
		pclExplain->Enable( true );
	}

	Init();

	m_pImageStatic_portrait->Refresh();

	this->Show( true );
}

void CALLBACK CNSelectQuest_PartyMatching::StaticCallBackDialogNSelectQuest_PartyMatching( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNSelectQuest_PartyMatching* pThis = (CNSelectQuest_PartyMatching*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNSelectQuest_PartyMatching( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNSelectQuest_PartyMatching::CallBackDialogNSelectQuest_PartyMatching( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient* pClient = (cltClient*) pclClient;
	if( NULL == pClient ) return;

	switch ( nEvent )
	{
	case EVENT_BUTTON_CLICKED:
		{
			switch ( nControlID )
			{
			case COMMON_DIALOG_CLOSEBUTTON:
			case NSELECT_QUEST_BASE_DLG_BUTTON_CLOSE:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_DestroyDlgButton();
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_01:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_01 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_02:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_02 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_03:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_03 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_04:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_04 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_05:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_05 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_06:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_06 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_07:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_07 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_08:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_08 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_09:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_09 );
				}
				break;
			case NSELECT_QUEST_BASE_DLG_BUTTON_CATEGORY_10:
				{
					pClient->m_pClient_PartyMatchingMgr->Click_CategoryButton( PARTYMATCHING_GROUP_10 );
				}
				break;
			}
		}
		break;
	default:
		{
		}
	}
}

