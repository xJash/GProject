//---------------------------------
// 2004/10/6 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :

	�ۼ��� :		05/03/14
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		
					1. leon todo - QuestManager�� Server�� Interface ���� ���� �ʿ�!!
					=> �켱, ���⼭ �����ϴ� QuestManager�� �Լ��� ��������

   ========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#include "..\Client\Client.h"
#include "./NCharQuest.h"
#include <tchar.h>
//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"


//----------------------------
// CommonLogic
//---------------------------
#include "Msg\MsgType-Quest.h"
#include "Msg/MsgType-DailyQuest.h"
#include "Msg/MsgType-DailyQuest2.h"

#include "../../CommonLogic/Msg/MsgType-DailyQuest3.h"

#include "../../Client/InterfaceMgr/Interface/Button.h"
#include "../../Client/InterfaceMgr/Interface/list.h"
#include "../../Client/InterfaceMgr/Interface/Static.h"
#include "../../Client/InterfaceMgr/Interface/Edit.h"

#include "../../Client/InterfaceMgr/InterfaceFile.h"

#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../../Client/NInterface/NNewQuestDlg/NNewQuestDlg.h"

extern cltCommonLogic* pclClient;

cltNQuestStatus::cltNQuestStatus()
{

	m_pStatictext_generalquest	 = NULL; 
	m_pEditbox_generalquest	 = NULL; 
	m_pStatictext_quest_clear	 = NULL; 
	m_pListbox_quest_clear	 = NULL; 
	m_pStatictext_questsum	 = NULL; 
	m_pButton_cancel_quest	 = NULL;

	m_pStatictext_SpecialQuest	= NULL;
	m_pStatictext_CollectWord	= NULL;
	m_pEditbox_SpecialExplain	= NULL;
	m_pStatictext_CompleteCount	= NULL;
	m_pButton_Cancel_Special	= NULL;
	m_pOutLine_SpecialQuest		= NULL;

	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	m_pButton_SpeicalQuest		= NULL;
	m_pButton_HappyBeanQuest 	=NULL;
	

	m_bShow = false;
	pclCM = NULL;
	CharUnique = 0;

	for( SI16 i = 0; i < MAX_QUEST_TYPE; i++)
	{
		m_QuestListData[i] = -1;
	}

}

cltNQuestStatus::~cltNQuestStatus()
{
	
	if(		m_pButton_cancel_quest	)			delete	m_pButton_cancel_quest;
	if( 	m_pStatictext_generalquest	 )  	delete 	m_pStatictext_generalquest	;
	if( 	m_pEditbox_generalquest	 )  	delete 	m_pEditbox_generalquest	;
	if( 	m_pStatictext_quest_clear	 )  	delete 	m_pStatictext_quest_clear	;
	if( 	m_pListbox_quest_clear	 )  	delete 	m_pListbox_quest_clear	;
	if( 	m_pStatictext_questsum	 )  	delete 	m_pStatictext_questsum	;

	SAFE_DELETE( m_pStatictext_SpecialQuest );
	SAFE_DELETE( m_pStatictext_CollectWord );
	SAFE_DELETE( m_pEditbox_SpecialExplain );
	SAFE_DELETE( m_pStatictext_CompleteCount );
	SAFE_DELETE( m_pButton_Cancel_Special );
	SAFE_DELETE( m_pOutLine_SpecialQuest );

	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	SAFE_DELETE( m_pButton_SpeicalQuest );
	SAFE_DELETE( m_pButton_HappyBeanQuest );

	SetTimerOnOff( false );        
}

void cltNQuestStatus::Create()
{
	if(!IsCreate())
	{
		cltClient *pclclient = (cltClient*)pclClient;
		CharUnique = pclclient->MyCharUnique;
		pclCM = pclclient->pclCM;
		//CDialogController::Create( CLTNQUESTSTATUS_DLG, CONTROLLER_KIND_CHILDDIALOG, pParent, NQuestStatusStaticProc, NULL, NULL, 0, false, 10, 40, 325, 480, false, false, false);

		CInterfaceFile file;

		file.LoadFile( TEXT("NInterface/Data/NCharStatusDlg/DLG_NCharStatus_Child_NStatusQuest.ddf") );
		file.CreatePopupDialog( this, NQUESTINFO_DLG, TEXT("dialog_quest"), NQuestStatusStaticProc);

		m_pStatictext_generalquest	 = new 	CStatic	( this )	;
		m_pEditbox_generalquest	 = new 	CEdit	( this )	;
		m_pStatictext_quest_clear	 = new 	CStatic	( this )	;
		m_pListbox_quest_clear	 = new 	CList	( this )	;
		m_pStatictext_questsum	 = new 	CStatic	( this )	;
		m_pButton_cancel_quest	= new CButton ( this )		;

		//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
		if( pclClient->IsCountrySwitch( Switch_HappyBeanQuest ) )
		{
			NEWCBUTTON( m_pButton_SpeicalQuest );
			NEWCBUTTON( m_pButton_HappyBeanQuest );
		}

		NEWCSTATIC( m_pStatictext_SpecialQuest );
		NEWCSTATIC( m_pStatictext_CollectWord );
		NEWCEDIT( m_pEditbox_SpecialExplain );
		NEWCSTATIC( m_pStatictext_CompleteCount );
		NEWCBUTTON( m_pButton_Cancel_Special );
		NEWCOUTLINE( m_pOutLine_SpecialQuest );

		//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
		if( pclClient->IsCountrySwitch( Switch_HappyBeanQuest ) )
		{
			file.CreateControl( m_pButton_SpeicalQuest, CLTNQUESTSTATUS_DLG_BUTTON_SPECIALQUEST, TEXT("button_special") );
			file.CreateControl( m_pButton_HappyBeanQuest, CLTNQUESTSTATUS_DLG_BUTTON_HAPPYBEANQUEST, TEXT("button_HappyBean") );
		}

		file.CreateControl( m_pStatictext_generalquest, CLTNQUESTSTATUS_DLG_STATICTEXT_GENERALQUEST, TEXT("statictext_generalquest") );
		file.CreateControl( m_pEditbox_generalquest, CLTNQUESTSTATUS_DLG_EDITBOX_GENERALQUEST, TEXT("editbox_generalquest") );
		file.CreateControl( m_pStatictext_quest_clear, CLTNQUESTSTATUS_DLG_STATICTEXT_QUEST_CLEAR, TEXT("statictext_quest_clear") );
		file.CreateControl( m_pListbox_quest_clear, CLTNQUESTSTATUS_DLG_LISTBOX_QUEST_CLEAR, TEXT("listbox_quest_clear") );
		file.CreateControl( m_pStatictext_questsum, CLTNQUESTSTATUS_DLG_STATICTEXT_QUESTSUM, TEXT("statictext_questsum") );
		file.CreateControl( m_pButton_cancel_quest, CLTNQUESTSTATUS_DLG_BUTTON_CANCEL_QUEST, TEXT("button_QuestCancel") );
		file.CreateControl( m_pStatictext_SpecialQuest, CLTNQUESTSTATUS_DLG_STATICTEXT_SPECIALQUEST, TEXT("statictext_specialquest") );
		file.CreateControl( m_pStatictext_CollectWord, CLTNQUESTSTATUS_DLG_STATICTEXT_COLLECTWORD, TEXT("statictext_collectword") );
		file.CreateControl( m_pEditbox_SpecialExplain, CLTNQUESTSTATUS_DLG_EDITBOX_SPECIALEXPLAIN, TEXT("editbox_specialexplain") );
		file.CreateControl( m_pStatictext_CompleteCount, CLTNQUESTSTATUS_DLG_STATICTEXT_COMPLETECOUNT, TEXT("statictext_completecount") );
		file.CreateControl( m_pButton_Cancel_Special, CLTNQUESTSTATUS_DLG_BUTTON_CANCEL_SPECIAL, TEXT("button_special_cancel") );
		file.CreateControl( m_pOutLine_SpecialQuest, CLTNQUESTSTATUS_DLG_OUTLINE_SPECIALQUEST, TEXT("outline_NONAME2") );

		m_pEditbox_generalquest->SetMaxEditTextLength(3072);
		m_pEditbox_generalquest->SetChangeTextDrawMode(true);
		

		m_pListbox_quest_clear->SetColumn( 0, m_pListbox_quest_clear->GetWidth() , NULL );		
		m_pListbox_quest_clear->SetBorder( true );
		m_pListbox_quest_clear->SetBKColorUse( true );
		m_pListbox_quest_clear->SetTextPrintOption(DT_LEFT|DT_VCENTER);
		m_pListbox_quest_clear->SetMultyLineNumber(2);
		m_pListbox_quest_clear->Refresh();
		
		TCHAR * pText = GetTxtFromMgr(601);
        
		SetTitle(pText);

		SetTimerOnOff( true );
		SetActionTimer( 1000 );
   
	
		ShowCurrentQuestInfo( 1 );

		Hide();

		//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
		siQuestSwitch = QUEST_TYPE_SPECIAL; //���â�� �⺻������ ���� ����Ʈ.(����� ���伣, �ƴϸ� ���Ǻ�)

		if( pclClient->IsCountrySwitch( Switch_HappyBeanQuest ) )
		{
			m_pButton_SpeicalQuest->Show(TRUE);
			m_pButton_HappyBeanQuest->Show(TRUE);
		}		
	}
	else
	{
		DeleteDialog();
	}
}


void CALLBACK cltNQuestStatus::NQuestStatusStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltNQuestStatus* pThis = (cltNQuestStatus*)pControllerMgr;
	pThis->NQuestStatusProc( nEvent, nControlID, pControl );	
}


void CALLBACK cltNQuestStatus::NQuestStatusProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	SI32 id = 1;
	TCHAR buffer[256]=TEXT("");
	
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			Hide();
		}
		break;
	case CLTNQUESTSTATUS_DLG_LISTBOX_QUEST_CLEAR:
		{
			switch( nEvent )
			{
			case EVENT_LISTBOX_SELECTION:
				{
					SI32 TempSelectIndex = m_pListbox_quest_clear->GetSelectedIndex();

					if(TempSelectIndex < 0 || TempSelectIndex >= MAX_QUEST_TYPE )
						break;

					//if(m_QuestListData[TempSelectIndex] < 0 ) 
					//	break;

					ShowSelectedQuestStory(TempSelectIndex);
					
				}
				return;
			}
		}
		break;
	case CLTNQUESTSTATUS_DLG_BUTTON_CANCEL_QUEST	:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					cltClient * pclclient = (cltClient*)pclClient;

					SI32 TempSelectIndex = m_pListbox_quest_clear->GetSelectedIndex();
                    
					if(TempSelectIndex < 0 || TempSelectIndex >= MAX_QUEST_TYPE )
						break;
					
					//����Ʈ Ÿ���� ���� �ϴ� �κ�. ����Ʈ Ÿ���� ������ �޾� ������ �˾ƺ��� �Ѵ�.
					SI16 siQuestType = m_QuestListData[TempSelectIndex] ;									
					SI16 siQuestUnique = 0;

					if( siQuestType >= 0 && siQuestType < MAX_QUEST_TYPE )
					{
						cltPersonQuestUnitInfo* pclunit = NULL;
						pclunit = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[siQuestType];
						siQuestUnique =  pclunit->siCurQuestUnique;
					}
					else if( siQuestType < 0 )
					{
						   siQuestType = QUESTTYPE_DAILY;
						
					}
					//������ý..�̤�
					else if( siQuestType == QUESTTYPE_DAILY2	)
					{
						siQuestType = QUESTTYPE_DAILY2;

					}
					else if( siQuestType == QUESTTYPE_DAILY3  )
					{
						siQuestType = QUESTTYPE_DAILY3;

					}
					else
					{
						break;
					}
					

					TCHAR * pTitle = GetTxtFromMgr(6398);
					TCHAR * pBody = GetTxtFromMgr(6399);
					stMsgBox MsgBox;
					MsgBox.Set( this, pTitle, pBody, MSGBOX_TYPE_YESNO, 1 );					
					
					BYTE TempBuffer[ 128 ];
					
					SI16 Size = sizeof( siQuestType ) + sizeof( siQuestUnique ) ;

					memcpy( TempBuffer, &siQuestType, sizeof( siQuestType ) );
					
					memcpy( &TempBuffer[ sizeof( siQuestType ) ] , &siQuestUnique, sizeof(siQuestUnique) );

					pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
				}
				return;
			}
		}
		break;
	case CLTNQUESTSTATUS_DLG_BUTTON_CANCEL_SPECIAL:
		{
			if ( EVENT_BUTTON_CLICKED == nEvent )
			{
				cltClient * pclclient = (cltClient*)pclClient;

				cltPersonQuestUnitInfo* pclunit = NULL;
				SI16 siQuestType;
				//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
				siQuestType = siQuestSwitch;//QUEST_TYPE_SPECIAL or QUEST_TYPE_HAPPYBEAN
				
				pclunit = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[siQuestType];

				if ( pclunit == NULL )
					break;

				SI16 siQuestUnique =  pclunit->siCurQuestUnique;

				if ( siQuestUnique <= 0 )
					break;

				TCHAR * pTitle = GetTxtFromMgr(6398);
				TCHAR * pBody = GetTxtFromMgr(6399);
				stMsgBox MsgBox;
				MsgBox.Set( this, pTitle, pBody, MSGBOX_TYPE_YESNO, 1 );					

				BYTE TempBuffer[ 128 ];

				SI16 Size = sizeof( siQuestType ) + sizeof( siQuestUnique ) ;

				memcpy( TempBuffer, &siQuestType, sizeof( siQuestType ) );

				memcpy( &TempBuffer[ sizeof( siQuestType ) ] , &siQuestUnique, sizeof(siQuestUnique) );

				pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
			}
		}
		break;
//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	case CLTNQUESTSTATUS_DLG_BUTTON_HAPPYBEANQUEST:
		{
			if ( EVENT_BUTTON_CLICKED == nEvent )
			{
//				cltClient * pclclient = (cltClient*)pclClient;
				TCHAR * pText = GetTxtFromMgr(7144);
				TCHAR * pText2 = GetTxtFromMgr(7145);
				
				m_pStatictext_SpecialQuest->SetText(pText,false);
				m_pButton_Cancel_Special->SetText(pText2, false);
				
				m_pStatictext_CompleteCount->Show(false);
				m_pStatictext_CollectWord->Show(false);
	
				siQuestSwitch = QUEST_TYPE_HAPPYBEAN;
			}
		}
		break;
//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	case CLTNQUESTSTATUS_DLG_BUTTON_SPECIALQUEST:
		{
			if ( EVENT_BUTTON_CLICKED == nEvent )
			{
//				cltClient * pclclient = (cltClient*)pclClient;
				TCHAR * pText = GetTxtFromMgr(4382);
				TCHAR * pText2 = GetTxtFromMgr(4387);
				
				m_pStatictext_SpecialQuest->SetText(pText,false);
				m_pButton_Cancel_Special->SetText(pText2, false);
				
				m_pStatictext_CompleteCount->Show(TRUE);
				m_pStatictext_CollectWord->Show(TRUE);

				siQuestSwitch = QUEST_TYPE_SPECIAL;

			}
		}
		break;

	}
}

void cltNQuestStatus::Action()
{
	// ����Ʈ �����Ͱ� ���Ͽ������� üũ�Ͽ� ���Ͽ��ٸ� ���̾�α� ������Ʈ

	ShowCurrentQuestInfo( 1 );
}


// ���� �������� ����Ʈ ������ ȭ�鿡 �����ش�. 
void cltNQuestStatus::ShowCurrentQuestInfo( SI32 id )
{
	SI32 i, j;

	TCHAR text[1024]				= TEXT("");
	TCHAR name[1024]				= TEXT("");
	TCHAR buffer[2048]				= TEXT("");
	TCHAR specialquesttext[512]		= TEXT("");

	bool	bQuestSwitch			= false;
	SI32	siQuestListIndex		= 0;

	stListBoxItemData	tmpListBoxItemData;
	
	// ����Ʈ�� �ټ��� ������ �ʾҴٸ� ���÷��� �ű� ���� ���û��·� �ǵ���.
	SI32	siOldRowNum				= 0;
	SI32	siOldListSelectedItem	= -1;
	SI32	siOldListScrollPos		= 0;

	// ����Ʈ ������
	siOldRowNum = m_pListbox_quest_clear->GetListNum();
	siOldListSelectedItem = m_pListbox_quest_clear->GetSelectedIndex();
	siOldListScrollPos = m_pListbox_quest_clear->GetScrollTrackPos();

	m_pListbox_quest_clear->Clear();
	for( j = 0; j < MAX_QUEST_TYPE; j++)	{	m_QuestListData[j] = -1;	}

	// DailyQuest1 ���� ǥ��
	if ( pclClient->pclCM->CR[id]->pclCI->clDailyQuestInfo.siMonsterKind > 0 )
	{		
		cltPDailyQuestInfo *pDailyQuestInfo = &pclClient->pclCM->CR[id]->pclCI->clDailyQuestInfo;
		TCHAR *MonsterName = (TCHAR*)pclClient->pclKindInfoSet->GetName( pDailyQuestInfo->siMonsterKind );
		TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName( pDailyQuestInfo->siRewardItemUnique );

		if( pDailyQuestInfo != NULL && MonsterName != NULL && ItemName != NULL )
		{
			TCHAR* pText = GetTxtFromMgr(3085);
			StringCchPrintf( buffer, 2048, pText, MonsterName, pDailyQuestInfo->siKillMonsterNum, pDailyQuestInfo->siMonsterNum, pDailyQuestInfo->siLeftTime );

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );

			m_pListbox_quest_clear->AddItem( &tmpListBoxItemData );
			m_QuestListData[siQuestListIndex++] = QUESTTYPE_DAILY;
		}
	}

	// DailyQuest2 ���� ǥ��
	if ( pclClient->pclCM->CR[id]->pclCI->clDailyQuest2Info.siMonsterKind > 0 )
	{		
		cltPDailyQuest2Info *pDailyQuest2Info = &pclClient->pclCM->CR[id]->pclCI->clDailyQuest2Info;
		TCHAR *MonsterName = (TCHAR*)pclClient->pclKindInfoSet->GetName( pDailyQuest2Info->siMonsterKind );
		TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName( pDailyQuest2Info->siRewardItemUnique );

		if( pDailyQuest2Info != NULL && MonsterName != NULL && ItemName != NULL )
		{
			TCHAR* pText = GetTxtFromMgr(8096);
			StringCchPrintf( buffer, 2048, pText, MonsterName, pDailyQuest2Info->siKillMonsterNum, pDailyQuest2Info->siMonsterNum, pDailyQuest2Info->siLeftTime );

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );

			m_pListbox_quest_clear->AddItem( &tmpListBoxItemData );
			m_QuestListData[siQuestListIndex++] = QUESTTYPE_DAILY2;
		}
	}

	// DailyQuest3 ���� ǥ��
	if ( pclClient->pclCM->CR[id]->pclCI->clDailyQuest3Info.siItemUnique > 0 )
	{		
		cltPDailyQuest3Info *pDailyQuest3Info = &pclClient->pclCM->CR[id]->pclCI->clDailyQuest3Info;
		TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName( pDailyQuest3Info->siItemUnique );
		TCHAR *RewardItemName = (TCHAR*)pclClient->pclItemManager->GetName( pDailyQuest3Info->siRewardItemUnique );

		if( pDailyQuest3Info != NULL && ItemName != NULL && RewardItemName != NULL )
		{
			// ���� ����Ʈ
			if (pDailyQuest3Info->bHiddenQuest == true)
			{
				TCHAR* pText = GetTxtFromMgr(8453);//�̰� �ٲ�� �Ѵ� ���� ���
				StringCchPrintf( buffer, 2048, pText, ItemName, pDailyQuest3Info->siMadeItemNum, pDailyQuest3Info->siItemNum, pDailyQuest3Info->siLeftTime );
				tmpListBoxItemData.Init();
				COLORREF co=RGB(255,0,0);			
				tmpListBoxItemData.Set( 0, buffer,co);
			}
			// �Ϲ� ����Ʈ
			else
			{
				TCHAR* pText = GetTxtFromMgr(8217);//�̰� �ٲ�� �Ѵ� ���� ���
				StringCchPrintf( buffer, 2048, pText, ItemName, pDailyQuest3Info->siMadeItemNum, pDailyQuest3Info->siItemNum, pDailyQuest3Info->siLeftTime );
				tmpListBoxItemData.Init();
				tmpListBoxItemData.Set( 0, buffer);
			}
			m_pListbox_quest_clear->AddItem( &tmpListBoxItemData );
			m_QuestListData[siQuestListIndex++] = QUESTTYPE_DAILY3;

		}
	}

	cltQuestInfoCommon* pclspecialinfo = NULL;
	for(i = 0;i < MAX_QUEST_TYPE;i++)
	{
		cltPersonQuestUnitInfo* pclunit = NULL;
		pclunit = &pclClient->pclCM->CR[id]->pclCI->clQuestInfo.clUnit[i];

		// Ư�� ����Ʈ ���� ���� Ȯ��. 
		if(i == QUEST_TYPE_SPECIAL)
		{
			pclspecialinfo	= &pclClient->pclCM->CR[id]->pclCI->clQuestInfo.clSpecialQuestInfo;

			// Ư�� ����Ʈ�� �����Ǿ� ���� �ʴٸ� ����, 
			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. 
			if(pclspecialinfo->clQuestClearConditionInfo.siFlag == 0)//Ư�� ����Ʈ�� �����Ǿ� �ִ���, ��ư���û��°� �ƴϸ� �н���.
			{
				if(siQuestSwitch ==QUEST_TYPE_SPECIAL)
					m_pEditbox_SpecialExplain->Clear();
				
				continue;
			}
		}
		else if ( i == QUEST_TYPE_NAMING )
		{
			cltQuestInfoCommon* pclnaminginfo = NULL;
			pclnaminginfo = &pclClient->pclCM->CR[id]->pclCI->clQuestInfo.clNamingQuestInfo;

			if( pclnaminginfo->clQuestClearConditionInfo.siFlag == 0 )
			{
				continue;
			}

		}
		//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
		else if ( i == QUEST_TYPE_HAPPYBEAN )
		{
			cltQuestInfoCommon* pclhappybeaninfo = NULL;
			pclhappybeaninfo = &pclClient->pclCM->CR[id]->pclCI->clQuestInfo.clHappyBeanQuestInfo;

			if( pclhappybeaninfo->clQuestClearConditionInfo.siFlag == 0 )
			{
				if(siQuestSwitch ==QUEST_TYPE_HAPPYBEAN)
					m_pEditbox_SpecialExplain->Clear();

				continue;
			}

		}
		else
		{
			// ����Ʈ�� �ϰ� �ִ� ������ ���θ� �Ǵ��Ѵ�. 
			if(pclunit->siQuestState)
			{
				bQuestSwitch = true;
			}
			
			// �������� ����Ʈ�� ���ٸ�, 
			if(pclunit->siCurQuestUnique == 0)continue;
			
		}
		


		// �������� ����Ʈ�� �־..
		bQuestSwitch = true;

		memset(name, 0, sizeof(name));
		memset(text, 0, sizeof(text));

		TCHAR szreward[256] = TEXT("");

		// ������ ���ؼ� ȭ�鿡 ǥ���Ѵ�. 
		if(pclClient->pclQuestManager->GetCurStatusText(id, i, pclunit->siCurQuestUnique, text, 1024) == true
			&& pclunit->siCurQuestStep != QUEST_STEP_CLEAR)
		{
			// ����Ʈ �ο����� �̸��� ã�´�.
			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
			if((i == QUEST_TYPE_SPECIAL)&&(siQuestSwitch ==QUEST_TYPE_SPECIAL)) //��ư ���û��¶��.
			{
				TCHAR* pText = GetTxtFromMgr(3086);
				StringCchPrintf(name, 1024, TEXT("[ %s ]"), pText);

				// Ư�� ����Ʈ�� ��� ���� ���뵵 ���´�. 
				pclspecialinfo->clQuestRewardInfo.GetExplainText(szreward, 256);
			}
			else if(i == QUEST_TYPE_NAMING)
			{
				TCHAR* pText = GetTxtFromMgr(10087);
				StringCchPrintf(name, 1024, TEXT("[ %s ]"), pText);
			}
			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ����Ʈ ���. �̸�.
			else if((i == QUEST_TYPE_HAPPYBEAN)&&(siQuestSwitch ==QUEST_TYPE_HAPPYBEAN)) //��ư ���û��¶��.
			{
				TCHAR* pText = GetTxtFromMgr(7144);
				StringCchPrintf(name, 1024, TEXT("[ %s ]"), pText);
			}
			else if( i == QUEST_TYPE_MISSION1 )
			{
				TCHAR* pText = "";

				if( pclunit->siCurQuestUnique == MISSIONQUEST_UNIQUE_HOLLOWEEN)
					pText = GetTxtFromMgr(8874);

				StringCchPrintf(name, 1024, TEXT("[ %s ]"), pText);

			}
			else// if(( i !=QUEST_TYPE_HAPPYBEAN)&&(i != QUEST_TYPE_SPECIAL))
			{
				SI32 npckind = pclClient->pclQuestManager->GetNPCKindFromQuestType(i);

				SI32 tempclearnum	= pclClient->pclCM->CR[1]->pclCI->clQuestInfo.GetClearQuestNum(pclClient->pclQuestManager, i );				

				SI32 temptotalnum	= pclClient->pclQuestManager->GetQuestNum(i);


				if(npckind)
				{
					const TCHAR* pname = pclClient->pclKindInfoSet->GetName(npckind);
					if(pname)
					{
						// [���� : Ȳ���� 2007. 11. 8 ����Ʈ ��ȣ�� 1������ ���۵ǰ�.]
						StringCchPrintf(name, 1024, TEXT("[%s]  (%d / %d)"), pname, tempclearnum+1, temptotalnum);
					}
				}
			}

			// �����߿� ���ʿ��� �ܾ�� �����Ѵ�.
			for(j = 0;j < lstrlen(text);j++)
			{
				if(text[j] == '\r' || text[j] == '\n')
				{
					text[j] = ' ';
				}
			}

		
			StringCchPrintf( buffer, 2048, TEXT(" %s \r %s"), name,text );

			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
			if((i == QUEST_TYPE_SPECIAL)&&(siQuestSwitch ==QUEST_TYPE_SPECIAL)) //��ư ���û��¶��.
			{
				m_pEditbox_SpecialExplain->Clear();
				m_pEditbox_SpecialExplain->SetText( buffer );
			}
			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ����Ʈ ���. �̸�.
			else if((i == QUEST_TYPE_HAPPYBEAN)&&(siQuestSwitch ==QUEST_TYPE_HAPPYBEAN)) //��ư ���û��¶��.
			{
				m_pEditbox_SpecialExplain->Clear();
				m_pEditbox_SpecialExplain->SetText( buffer );			
			}
			else if(( i !=QUEST_TYPE_HAPPYBEAN)&&(i != QUEST_TYPE_SPECIAL))
			{

				tmpListBoxItemData.Init();
				tmpListBoxItemData.Set( 0, buffer );

				m_pListbox_quest_clear->AddItem( &tmpListBoxItemData );				

				m_QuestListData[siQuestListIndex++] = i;
			}
		}
	}



	if(siOldRowNum == m_pListbox_quest_clear->GetListNum())
	{
		m_pListbox_quest_clear->SetSelectIndex(siOldListSelectedItem);
		m_pListbox_quest_clear->SetScrollTrackPos(siOldListScrollPos);
	}
    

	m_pListbox_quest_clear->Refresh();


	// ������� �ܾ� ���� ���
	SI16 wordNumber = pclClient->pclQuestManager->siWordAssemblyNumber;
	TCHAR szWordBuffer[256] = {0,};

	for ( SI32 i = 0 ; i < wordNumber ; ++i )
	{
		if ( pclClient->pclCM->CR[1]->pclCI->clQuestInfo.bWordAssemblySwitch[i] )
		{
			StringCchCat( szWordBuffer, 256, pclClient->pclQuestManager->szWordAssemblyString[i] );
		}
		else
		{
			StringCchCat( szWordBuffer, 256, "?" );
		}
		StringCchCat( szWordBuffer, 256, " " );
	}

	TCHAR* pText = GetTxtFromMgr( 4383 );
	TCHAR szTextBuffer[256] = {0,};

	StringCchPrintf( szTextBuffer, 256, pText, szWordBuffer );
	m_pStatictext_CollectWord->SetText( szTextBuffer );

	// ������� �ܾ� ���� �ϼ� Ƚ��

	pText = GetTxtFromMgr(2833);
	StringCchPrintf( szTextBuffer, 256, pText, pclClient->pclCM->CR[1]->pclCI->clQuestInfo.siClearWordSpecialQuest);

	m_pStatictext_CompleteCount->SetText( szTextBuffer );
	
}

void cltNQuestStatus::ShowSelectedQuestStory( SI32 SelectedListIndex )
{
	// ����Ʈ ����â �ʱ�ȭ
	m_pEditbox_generalquest->Clear();

	if( SelectedListIndex  < 0 || SelectedListIndex >= MAX_QUEST_TYPE ) return;
	
	SI32 siQuestType =	m_QuestListData[SelectedListIndex];

	if( siQuestType < 0 || siQuestType >= MAX_QUEST_TYPE) 
	{
		return;
	}


	cltPersonQuestUnitInfo* pclunit = NULL;
	pclunit = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[siQuestType];
							  
	SI32 bit = pclClient->pclQuestManager->GetBitFromUnique(siQuestType, pclunit->siCurQuestUnique);
	
	if(bit < 0) return;

	TCHAR pBuffer[3072];

	StringCchPrintf(pBuffer,3072,TEXT("%s\n%s"),
	pclClient->pclQuestManager->clQuestTxtInfo[siQuestType][bit].szQuestGreeting,
	pclClient->pclQuestManager->clQuestTxtInfo[siQuestType][bit].szQuestMiddle);
	
	m_pEditbox_generalquest->SetText(pBuffer);
}

void cltNQuestStatus::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient* pclclient = (cltClient*)pclClient;

	switch( MsgIndex )
	{
	case 1:	// ����Ʈ ���
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI16 siQuestType = *((SI16*)pData);
				
				if( siQuestType >= 0 && siQuestType < MAX_QUEST_TYPE )
				{
					SI16 siQuestUnique = *((SI16*)&pData[sizeof(siQuestType)]);

					if(siQuestUnique > 0)
					{
						// ����Ʈ ������ �����Ѵ�. 
						cltGameMsgRequest_CancelQuest clInfo( siQuestType , siQuestUnique );
						cltMsg clMsg(GAMEMSG_REQUEST_CANCELQUEST, sizeof(clInfo), (BYTE*)&clInfo);
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

						pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0 );
						//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
						if (( siQuestType == QUEST_TYPE_SPECIAL)||( siQuestType == QUEST_TYPE_HAPPYBEAN) )
						{
							m_pEditbox_SpecialExplain->Clear();
						}
						else
						{
							m_pEditbox_generalquest->Clear();
						}

						// ����Ʈ ��ҽ� �����ִ� ����Ʈ ���̾�α� �ݱ�
						if(pclclient->m_pDialog[ NNEWQUEST_DLG ] != NULL)
						{
							if( ((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->IsShow() )
								((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->Show( false );
						}
					}
				}
				else if( siQuestType == QUESTTYPE_DAILY )
				{
					///  ���ϸ� ����Ʈ ���

					if  ( pclClient->pclCM->CR[1]->pclCI->clDailyQuestInfo.siMonsterKind > 0 )
					{
						cltGameMsgRequest_DailyQuestEnd clDailyQuestEnd;
						cltMsg clMsg( GAMEMSG_REQUEST_DAILYQUESTEND, sizeof( clDailyQuestEnd ), (BYTE*)&clDailyQuestEnd );
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

						pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_DAILYQUEST_GIVEUP")), 0, 0 );
					}

				}
				else if( siQuestType == QUESTTYPE_DAILY2 )
				{
					///  ���ϸ� ����Ʈ2 ���

					if  ( pclClient->pclCM->CR[1]->pclCI->clDailyQuest2Info.siMonsterKind > 0 )
					{
						cltGameMsgRequest_DailyQuest2End clDailyQuest2End;
						cltMsg clMsg( GAMEMSG_REQUEST_DAILYQUEST2END, sizeof( clDailyQuest2End ), (BYTE*)&clDailyQuest2End );
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

						pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_DAILYQUEST_GIVEUP")), 0, 0 );
					}

				}
				else if( siQuestType == QUESTTYPE_DAILY3 )
				{
					///  ���ϸ� ����Ʈ3 ���

					if  ( pclClient->pclCM->CR[1]->pclCI->clDailyQuest3Info.siItemUnique > 0 )
					{
						cltGameMsgRequest_DailyQuest3End clDailyQuest3End;
						cltMsg clMsg( GAMEMSG_REQUEST_DAILYQUEST3END, sizeof( clDailyQuest3End ), (BYTE*)&clDailyQuest3End );
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

						pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_DAILYQUEST_GIVEUP")), 0, 0 );
					}

				}
				else
				{
					break;
				}					
			}
		}
		break;
	}
}

void cltNQuestStatus::Hide()
{
	m_bShow = false;
	CControllerMgr::Show( false );
}

void cltNQuestStatus::Show()
{
	m_bShow = true;
	CControllerMgr::Show( true );

	pclClient->pclCM->CR[1]->DoQuestCheckAndAction( QUEST_CLEAR_COND_OPENQUESTDIALOG );
}

bool cltNQuestStatus::IsShow()
{
    return m_bShow;
}


//#endif
