#include "../Client/NInterface/NNewQuestDlg/NNewQuestDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"


#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/ListView.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/Interface/ImageStatic.h"
#include "../../InterfaceMgr/Interface/List.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include "../../Client.h"

#include "../CommonLogic/TextMgr/TextMgr.h"

#include "../common/Char/CharCommon/Char-Common.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../common/Skill/Skill-Manager.h"

#include "../../../resource.h"
#include "MsgType-Person.h"
#include "Msg/MsgType-Quest.h"

#include "Music/Music.h"


#include "../../../Common/SystemNPC/SystemNPC.h"
#include "HashTable/HashTable_StringInt.h"
#include "../CommonLogic/CommonLogic.h"
#include "../../../Common/Father/Father.h"

// ����ã�� �̺������� ������..�߰�
#include "Ninterface/NCommonMsgDlg/NCommonMsgDlg.h"

//------------------------------------
// Lib
//------------------------------------
#include "HashTable/HashTable_StringInt.h"

extern cltCommonLogic* pclClient;
extern SI32 gsiResolution;

CNNewQuestDlg::CNNewQuestDlg() : CDialogController()
{
	m_siSprKind = SPR_NONE;
	m_siNpcKind = 0;
	m_siButtonType = 0;
	m_siOldButtonType = 0;
	m_siCurrentState = 0;
	m_siViewState = 0;
	m_siNpcFontType = 0;
	m_bOpened = FALSE;	// �ȿ����� �ְ�
	QuestTwinkle=12;

	m_pStatic[0] = NULL;
	m_pStatic[1] = NULL;
	m_pStatic[2] = NULL;
	m_pStatic[3] = NULL;
	m_pStatic[4] = NULL;
	m_pStatic[5] = NULL;
	m_pStatic[6] = NULL;

	m_pEditCondition = NULL;
	m_pEditStatus = NULL;
	m_pEditQuestReward = NULL;
	m_pEditExplain[0] = NULL;
	m_pEditExplain[1] = NULL;
	m_pEditConversation	= NULL;

	m_pBtnClose = NULL;
	m_pBtnHide = NULL;
	m_pBtnAccept = NULL;

	m_siQuestType_Rudolph = 0;
}

CNNewQuestDlg::~CNNewQuestDlg()
{
	SetTimerOnOff( false );

	SAFE_DELETE(m_pStatic[0]);
	SAFE_DELETE(m_pStatic[1]);
	SAFE_DELETE(m_pStatic[2]);
	SAFE_DELETE(m_pStatic[3]);
	SAFE_DELETE(m_pStatic[4]);
	SAFE_DELETE(m_pStatic[5]);
	SAFE_DELETE(m_pStatic[6]);

	SAFE_DELETE(m_pEditCondition);
	SAFE_DELETE(m_pEditStatus);
	SAFE_DELETE(m_pEditQuestReward);
	SAFE_DELETE(m_pEditExplain[0]);
	SAFE_DELETE(m_pEditExplain[1]);
	SAFE_DELETE(m_pEditConversation);

	SAFE_DELETE(m_pBtnClose);
	SAFE_DELETE(m_pBtnHide);
	SAFE_DELETE(m_pBtnAccept);

	GP.FreeSpr(m_SprNpcFace2);
	GP.FreeSpr(m_SprNpcFace1);
}

void CNNewQuestDlg::InitNewQuest()
{
	m_pStatic[4]->SetFileName( TEXT(""));
	m_pStatic[5]->SetFileName( TEXT(""));
	m_pEditExplain[0]->SetText( TEXT(""));
	m_pEditExplain[1]->SetText( TEXT(""));
	m_pEditConversation->SetText( TEXT(""));

}

void CNNewQuestDlg::Create()
{
	if ( ! IsCreate() )
	{
		CInterfaceFile file;

		file.LoadFile( TEXT("NInterface/Data/NNewQuestDlg/DLG_NewQuest.ddf"));
		file.CreatePopupDialog( this, NNEWQUEST_DLG,  TEXT("dialog_NewQuest"), StaticCallBackDialogNNewQuestDlg );

		cltClient *pclclient = (cltClient *)pclClient;

		
		if(gsiResolution == 2 ||gsiResolution == 4) // 1024x768 || 1024x600
		{
			MovePos(pclclient->GetScreenXSize() -566, pclclient->GetScreenYSize() - 270);
		}
		else
		{

		}

		NEWCSTATIC(m_pStatic[0]);
		NEWCSTATIC(m_pStatic[1]);
		NEWCSTATIC(m_pStatic[2]);
		NEWCSTATIC(m_pStatic[3]);
		NEWCSTATIC(m_pStatic[4]);
		NEWCSTATIC(m_pStatic[5]);
		NEWCSTATIC(m_pStatic[6]);

		NEWCEDIT(m_pEditCondition);
		NEWCEDIT(m_pEditStatus);
		NEWCEDIT(m_pEditQuestReward);
		NEWCEDIT(m_pEditExplain[0]);
		NEWCEDIT(m_pEditExplain[1]);
		NEWCEDIT(m_pEditConversation);

		NEWCBUTTON(m_pBtnClose);
		NEWCBUTTON(m_pBtnHide);
		NEWCBUTTON(m_pBtnAccept);

		file.CreateControl( m_pBtnClose, NNEWQUEST_DIALOG_BUTTON1,  TEXT("button_NONAME1") );
		file.CreateControl( m_pBtnHide,  NNEWQUEST_DIALOG_BUTTON2,  TEXT("button_NONAME2") );
		file.CreateControl( m_pBtnAccept,    NNEWQUEST_DIALOG_BUTTON3,  TEXT("button_NONAME3") );


		
		file.CreateControl( m_pEditCondition,  NNEWQUEST_DIALOG_EDIT1,  TEXT("editbox_NONAME1") );
		file.CreateControl( m_pEditStatus,		 NNEWQUEST_DIALOG_EDIT2,  TEXT("editbox_NONAME2") );
		file.CreateControl( m_pEditQuestReward, NNEWQUEST_DIALOG_EDIT3,  TEXT("editbox_NONAME3") );
		file.CreateControl( m_pEditExplain[0],  NNEWQUEST_DIALOG_EDIT4,  TEXT("editbox_NONAME4") );
		file.CreateControl( m_pEditExplain[1],  NNEWQUEST_DIALOG_EDIT5,  TEXT("editbox_NONAME5") );
		file.CreateControl( m_pEditConversation,  NNEWQUEST_DIALOG_EDIT6,  TEXT("editbox_NONAME6") );


	//	file.CreateControl( m_pStatic[0], NNEWQUEST_DIALOG_STATIC1,  TEXT("statictext_NONAME1") );
	//	file.CreateControl( m_pStatic[1], NNEWQUEST_DIALOG_STATIC2,  TEXT("statictext_NONAME2") );
	//	file.CreateControl( m_pStatic[2], NNEWQUEST_DIALOG_STATIC3,  TEXT("statictext_NONAME3") );
		file.CreateControl( m_pStatic[3], NNEWQUEST_DIALOG_STATIC4,  TEXT("statictext_NONAME4") );
		file.CreateControl( m_pStatic[4], NNEWQUEST_DIALOG_STATIC5,  TEXT("statictext_NONAME5") );
		file.CreateControl( m_pStatic[5], NNEWQUEST_DIALOG_STATIC6,  TEXT("statictext_NONAME6") );
		file.CreateControl( m_pStatic[6], NNEWQUEST_DIALOG_STATIC7,  TEXT("statictext_NONAME7") );
		
        
		m_pEditExplain[0]->SetFontColor( NNEWQUEST_TEXTCOLOR);
		m_pEditExplain[1]->SetFontColor( NNEWQUEST_TEXTCOLOR);
		m_pEditCondition->SetFontColor( NNEWQUEST_CONDITION_REWARD_COLOR);
		m_pEditQuestReward->SetFontColor( NNEWQUEST_CONDITION_REWARD_COLOR);
		//m_pEditExplain[1]->SetFontSize(13);
		//m_pEditExplain[0]->SetFontSize(13);
		m_pStatic[6]->Show(false);

		m_pEditExplain[0]->SetChangeTextDrawMode( true );
		m_pEditExplain[1]->SetChangeTextDrawMode( true );
		m_pEditConversation->SetChangeTextDrawMode( true );

		GP.LoadSprFromFile(SPR_NPCFACE1, &m_SprNpcFace1);
		GP.LoadSprFromFile(SPR_NPCFACE2, &m_SprNpcFace2);


		SetTimerOnOff( true );

		m_bOpened = TRUE;

		SetFileName(  TEXT("NInterface/interface/INTERFACE_566X222_00_000.SPR") );

		if( pclClient->pclQuestManager->bNewQuestDoing == TRUE)
		{
			if(pclClient->pclQuestManager->siCurrentQuestStep == QUEST_STEP_GREETING)
			{
				if(pclClient->pclQuestManager->siViewState == 0 || pclClient->pclQuestManager->siViewState == 2)
				{
					SetFontIndex( 1 );
					SetBKTileImgNum( 0 );

//					m_pStatic[0]->Show(false);
//					m_pStatic[1]->Show(false);
//					m_pStatic[2]->Show(false);
					m_pStatic[4]->Show(false);
					m_pStatic[5]->Show(false);
					m_pStatic[6]->Show(false);

					m_pEditCondition->Show(false);
					m_pEditStatus->Show(false);
					m_pEditQuestReward->Show(false);
					m_pEditExplain[0]->Show(false);
					m_pEditExplain[1]->Show(false);
				}
				else
				{
					SetFontIndex( 0 );
					SetBKTileImgNum( 0 );

					m_pStatic[3]->Show(false);
					m_pEditConversation->Show(false);
				}
			}
			// ������
			if(pclClient->pclQuestManager->siCurrentQuestStep == QUEST_STEP_MIDDLE)
			{
				pclClient->pclQuestManager->siViewState = 1;
				SetFontIndex( 0 );
				SetBKTileImgNum( 0 );

				m_pStatic[3]->Show(false);
				m_pEditConversation->Show(false);
			}
		}
		else
		{
			pclClient->pclQuestManager->siViewState = 1;

			SetFontIndex( 0 );
			SetBKTileImgNum( 0 );

			m_pStatic[3]->Show(false);
			m_pEditConversation->Show(false);

		}
	}
	else
	{
		DeleteDialog();
	}
}

void CNNewQuestDlg::SetNewQuest(SI32 kind)
{
	pclClient->pclQuestManager->InitDialog(kind);
	SetOpenedQuestDlg(true);

	//[�߰��� : Ȳ���� 2007. 11. 22 ũ�������� ����Ʈ �絹�� Ŭ���� â ����]
	/*if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_RUDOLPH"))  )			// �絹��
	{
		cltPersonQuestUnitInfo* pclunit[3];
		pclunit[0] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[24];
		pclunit[1] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[25];
		pclunit[2] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[26];
		
		if(pclunit[0]->siQuestState || pclunit[1]->siQuestState || pclunit[2]->siQuestState)
		{
			m_siSprKind = SPR_KIND1;
			m_siNpcKind = 86;
		}
	}
	else*/ 
	
	if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_JANGGUMI"))  )			// ���(����)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 0;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_ROYALGUARD")) )	// ������(��ũ)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 2;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_WAITINGMAN")) )	// ����(�����)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 4;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_BONGSUNI")) )	// ������(����þ�)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 6;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_BONGTAGI")) )	// ������(�÷�)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 8;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_SEOSANSAINT")) )	// ������(�����)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 10;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_DOCTOR")) )	// ���ǿ�(�ĳ�)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 12;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_BONGDAL")) )	// ������(ī����)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 14;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_BONGSAMI")) )	// ������(������)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 16;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_YONGCHUNI")) )	// ������(��)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 18;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_BONG")) )	// ������(Ƽ��)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 20;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_YONGTAGI")) )	// ������(����Ű)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 22;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_YONGPAL")) )	// ������(ũ�ε�)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 24;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_YONGSAMI")) )	// �����(����ƴ�)
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 26;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_JANGYOUNGSIL")) )	// ������
	{
		m_siSprKind = SPR_KIND1;
		m_siNpcKind = 28;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_JANGGILSAN")) )	// ����
	{
		m_siSprKind = SPR_KIND2;
		m_siNpcKind = 0;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_WAITINGMAN2")) )	// �������
	{
		m_siSprKind = SPR_KIND2;
		m_siNpcKind = 2;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_PRISONER")) )	// ��ù���
	{
		m_siSprKind = SPR_KIND2;
		m_siNpcKind = 4;
	}
	else if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_FREESIA")) )	// ��������(��������)
	{
		m_siSprKind = SPR_KIND2;
		m_siNpcKind = 6;
	}
	else
	{
		m_siSprKind = SPR_NONE;
		m_siNpcKind = -1;
	}

	SI16 questtype, para1, para2;
	SI16 questunique;
	bool bQuestCondCheck = false;

	// PCK : �Ҿ���� ����Ʈ �������̶��
	if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_GONPC_INFORMATION, &questtype, &questunique, &para1, &para2) == true)
	{
		if(para1 == kind )
		{
			cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, QUEST_CLEAR_COND_GONPC_INFORMATION, para1, para2  );
			cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
		}
	}
	else if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_GONPC, &questtype, &questunique, &para1, &para2) == true)
	{
		if(para1 == kind )
		{
			cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, QUEST_CLEAR_COND_GONPC, para1, para2  );
			cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
		}
	}
}

void CNNewQuestDlg::Action()
{
	pclClient->pclQuestManager->Action();
	
	if( m_pEditExplain[1]->IsFocus())
	{
		 SetFocus(m_pBtnAccept);
	}


	if(pclClient->pclQuestManager->siCurrentQuestStep == QUEST_STEP_CLEAR && m_bOpened == FALSE)
	{

		if(QuestTwinkle==12)
		{
			QuestTwinkle=14;
			m_pBtnAccept->SetFontIndex(QuestTwinkle);

		}
		else
		{
			QuestTwinkle=12;
			m_pBtnAccept->SetFontIndex(QuestTwinkle);
		}		
	}	
}

void CNNewQuestDlg::DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY )
{
	cltClient	*pclclient		= (cltClient *)pclClient;

	SI32		siCorrectionY	= 456;

	//==============================================================================
	// DUMP CODE - ����N(�ѱ�����) ������ �ʻ��� ������ �ʴ´�. - By LEEKH
	//==============================================================================
	if( m_bOpened  )
	{
		// â�̰� Ǯ��ũ���̰� ���ʱ������� ���
		if( SPR_KIND1 == m_siSprKind && m_siNpcKind >= 0 )
		{
			if(0 == m_siButtonType || 1 == m_siButtonType|| 3 == m_siButtonType || 4 == m_siButtonType)	// �ӹ� ������ ���
			{
				GP.PutSpr( &m_SprNpcFace1,  ScreenRX + MAP_TILE_XSIZE, pclclient->GetScreenYSize() - siCorrectionY + ScreenRY , m_siNpcKind);
			}
			else if(2 == m_siButtonType)	// �ӹ� �Ϸ������� ���
			{
				GP.PutSpr( &m_SprNpcFace1,  ScreenRX + MAP_TILE_XSIZE, pclclient->GetScreenYSize() - siCorrectionY + ScreenRY , m_siNpcKind + 1);
			}
		}
		else if( SPR_KIND2 == m_siSprKind && m_siNpcKind >= 0 )
		{
			if(0 == m_siButtonType || 1 == m_siButtonType|| 3 == m_siButtonType || 4 == m_siButtonType)	// �ӹ� ������ ���
			{
				GP.PutSpr( &m_SprNpcFace2,  ScreenRX + MAP_TILE_XSIZE, pclclient->GetScreenYSize() - siCorrectionY + ScreenRY , m_siNpcKind);
			}
			else if(2 == m_siButtonType)	// �ӹ� �Ϸ������� ���
			{
				GP.PutSpr( &m_SprNpcFace2,  ScreenRX + MAP_TILE_XSIZE, pclclient->GetScreenYSize() - siCorrectionY + ScreenRY , m_siNpcKind + 1);
			}
		}

		//==========================================================================================================
		// ���� �ѱ� �Ѱ��� �� �ӽ� �ڵ� - ���Ŀ� �ý����� �����ϰ� �����Ǿ�� �ϰ���. - By LEEKH 2007.07.02
		//==========================================================================================================
		if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
		{
			static TCHAR	szBeforeFullPathName[MAX_PATH] = TEXT("");
			static TSpr		SprHelp;

			SI32		siFont  = 0;
			TCHAR		szFullPathName[MAX_PATH] = TEXT("");

			bool bFile = pclClient->pclQuestManager->GetSprPath(pclClient->pclQuestManager->siCurrentQuestUnique,
																pclClient->pclQuestManager->siCurrentQuestStep,
																&siFont, szFullPathName);

			if( (bFile && _tcscmp(szBeforeFullPathName, szFullPathName) != 0) ||
				SprHelp.pImage == NULL )
			{
				GP.LoadSprFromFile(szFullPathName, &SprHelp);

				_tcsncpy(szBeforeFullPathName, szFullPathName, sizeof(szBeforeFullPathName));
			}
			GP.PutSpr(&SprHelp, GetX() + GetWidth() - 370 + pclClient->GetScreenRX(), GetY() - 170 + pclClient->GetScreenRY(), siFont);
		}
		//=================================================================================================
	}
}

void CALLBACK CNNewQuestDlg::StaticCallBackDialogNNewQuestDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNNewQuestDlg *pThis = (CNNewQuestDlg *)pControllerMgr;
	pThis->CallBackDialogNNewQuestDlg( nEvent, nControlID, pControl );
}

void CALLBACK CNNewQuestDlg::CallBackDialogNNewQuestDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient *)pclClient;
	TCHAR Nbuffer[512]= TEXT(" ");

	switch ( nControlID )
	{
	case NNEWQUEST_DIALOG_EDIT5 :
		{


		}
		break;

	case NNEWQUEST_DIALOG_BUTTON1:	// ����
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					DeleteDialog();
				}
				break;
			}
		}
		break;

	case NNEWQUEST_DIALOG_BUTTON2:	// �����
		{

			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					m_bOpened = FALSE;	// ������
					m_siOldButtonType = m_siButtonType;
					SetOpenedQuestDlg(m_bOpened);
					m_siButtonType = 3;
					SetAcceptButtonEnable(3, TRUE);

					m_pBtnAccept->SetFileName( TEXT("NInterface/button/BUTTON_26x90_00_000.SPR"));
					m_pBtnAccept->SetFontIndex(12);
					/*	if(g_SoundOnOffDlg.m_bFullScreenMode)
					{						
					m_pBtnAccept->MoveControl( 570, 70 );
					}
					else
					{
					if(gsiResolution==1	)
					m_pBtnAccept->MoveControl( 563, 50 );
					else
					m_pBtnAccept->MoveControl( 570, 50 );

					}
					*/



				}
				break;
			}
		}
		break;

	case NNEWQUEST_DIALOG_BUTTON3:	// ����, �ӹ����, �����ӹ�, ����Ʈ
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					switch(m_siButtonType)
					{
					case 0:	// ����
						{
							// ���� ������ ����Ʈ�� ���� ��û�� ������. 
							if(pclClient->pclQuestManager->siCurrentQuestUnique)
							{
								//-----------------------------
								// �ڰ��� �ִ��� Ȯ���Ѵ�. 
								//-----------------------------
								cltQuestInfo* pclquestinfo = pclClient->pclQuestManager->GetQuestInfo(pclClient->pclQuestManager->siCurrentQuestUnique);
								// Ư�� ����Ʈ�� �����ϱ� ���ؼ� ���� ����Ʈ�� Ŭ���� �ؾ� �Ѵ�.								
								////// ����Ʈ ���� ���� (�ϵ��ڵ�) ����
								if( pclClient->siServiceArea != ConstServiceArea_Korea )
								{
									// ��ũ�� 6400 �� ����Ʈ�� �ޱ� ���ؼ� ������� ��� ����Ʈ�� Ŭ���� �ؾ� ��
									if(pclquestinfo->siUnique == QUESTUNIQUE(6400) )
									{
										if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsAllClear(pclClient->pclQuestManager, QUEST_TYPE_BEGINNER2) == false)
										{
											TCHAR* pTitle = GetTxtFromMgr(3087);
											TCHAR* pText = GetTxtFromMgr(6417);
											pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
											break;
										}								
									}


									//���˼�, ����ȣ�� ���� �ޱ� ���ؼ� ������� ��� ����Ʈ�� Ŭ���� �ؾ� ��
									if( pclquestinfo->siType == QUEST_TYPE_BEGINNER3 
										||  pclquestinfo->siType == QUEST_TYPE_BEGINNER4 )
									{
										if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsAllClear(pclClient->pclQuestManager, QUEST_TYPE_BEGINNER2) == false)
										{
											TCHAR* pTitle = GetTxtFromMgr(3087);
											TCHAR* pText = GetTxtFromMgr(6417);
											pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
											break;
										}                                   

									}

									// ��� ���� ����Ʈ�� �ޱ� ���ؼ� ������ ��� ����Ʈ�� Ŭ���� �ؾ� ��
									if( pclquestinfo->siType == QUEST_TYPE_MAKEHEAL1 
										||  pclquestinfo->siType == QUEST_TYPE_MAKESWORD1
										||  pclquestinfo->siType == QUEST_TYPE_MAKEBOW1 
										||  pclquestinfo->siType == QUEST_TYPE_MAKEHELMET1 
										||  pclquestinfo->siType == QUEST_TYPE_MAKESPEAR1 
										||  pclquestinfo->siType == QUEST_TYPE_MAKEARMOUR1									
										||  pclquestinfo->siType == QUEST_TYPE_MAKEAX1 
										||  pclquestinfo->siType == QUEST_TYPE_MAKEGUN1
										||  pclquestinfo->siType == QUEST_TYPE_MAKESTAFF1
										||  pclquestinfo->siType == QUEST_TYPE_MAKEBELT1
										||  pclquestinfo->siType == QUEST_TYPE_MAKESHOES1 )
									{
											if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsAllClear(pclClient->pclQuestManager, QUEST_TYPE_MAKEBEGINNER1) == false)
											{
												TCHAR* pTitle = GetTxtFromMgr(3087);
												TCHAR* pText = GetTxtFromMgr(6429);
												pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
												break;
											}                                   

									}

									// BATTLE1 �� ��� Ŭ���� �ؾ� BATTLE2 ����Ʈ�� ���� �� �ִ�.
									if( pclquestinfo->siType == QUEST_TYPE_BATTLE2 )
									{
										if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsAllClear(pclClient->pclQuestManager, QUEST_TYPE_BATTLE1) == false)
										{
											TCHAR* pTitle = GetTxtFromMgr(3087);
											TCHAR* pText = GetTxtFromMgr(6856);
											pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
											break;
										}    
									}
								}

								////// ����Ʈ ���� ���� (�ϵ��ڵ�) ��

								

								// ���� Ȯ��. 
								if(pclquestinfo->clInitConditionInfo.siLevel)
								{
									if(pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() < pclquestinfo->clInitConditionInfo.siLevel)
									{
										TCHAR* pTitle = GetTxtFromMgr(3087);
										TCHAR* pText = GetTxtFromMgr(3088);
										pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclquestinfo->clInitConditionInfo.siLevel);
										break;
									}
								}
								// ��� Ȯ��. 
								SI32 skillunique = pclquestinfo->clInitConditionInfo.siSkillUnique;
								if(skillunique)
								{
									if(pclClient->pclCM->CR[1]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[0]) < pclquestinfo->clInitConditionInfo.siSkillLevel)
									{
										TCHAR skillname[128];
										if(pclClient->pclSkillManager->GetSkillName(skillunique, skillname) == true)
										{
											TCHAR* pTitle = GetTxtFromMgr(3087);
											TCHAR* pText = GetTxtFromMgr(3089);
											TCHAR level[128]=  TEXT(" ") ;

											StringCchPrintf(level, 128,  TEXT("%d"),pclquestinfo->clInitConditionInfo.siSkillLevel);
											Nsprintf(Nbuffer,pText, TEXT("what"), skillname   , TEXT("level"),  level  ,NULL);
											pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,Nbuffer);
											//pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, skillname, pclquestinfo->clInitConditionInfo.siSkillLevel);
										}
										break;
									}
								}

								// �ʼ� ���� ����Ʈ Ȯ��.
								SI32 mustclearquestunique = pclquestinfo->clInitConditionInfo.siMustClearQuestUnique;
								if( mustclearquestunique > 0 )
								{
									if( pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsClear(pclClient->pclQuestManager , mustclearquestunique) == false )
									{
										// Ŭ���� �� ���°� �ƴ϶�� ���������� �������� ���� Ŭ���� �ؾ��մϴ�. ��� �˷��ش�.
									
										cltQuestInfo* pclMustClearQuestInfo = pclClient->pclQuestManager->GetQuestInfo( mustclearquestunique );
										
										if( pclMustClearQuestInfo != NULL )
										{
											SI32 npckind = pclClient->pclQuestManager->GetNPCKindFromQuestType(pclMustClearQuestInfo->siType);

											const TCHAR * pNpcName = pclClient->pclKindInfoSet->GetName(npckind);

											if( pNpcName != NULL )
											{
												TCHAR * pTitle = GetTxtFromMgr(3087);
												TCHAR szBuffer[256] ;
												szBuffer[0] = 0;
												TCHAR * pText = GetTxtFromMgr(7075);

												StringCchPrintf( szBuffer , 256 , pText , pNpcName , pclMustClearQuestInfo->szTitleText );
												pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, szBuffer );	
											}
										}

									}
								}

								// Ư�� ���� Ȯ��


								if( pclquestinfo->clQuestClearConditionInfo.siFlag == QUEST_CLEAR_COND_SETFATHER )
								{
									if( pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() < 20)
									{
										if( pclclient->m_pDialog[ NCHILD_DLG ] == NULL)
											pclclient->CreateInterface( NCHILD_DLG );
									}
								}
								pclClient->pclQuestManager->bNewQuseOpened = true;
							
								cltGameMsgRequest_QuestGoing clInfo(pclClient->pclQuestManager->siQuestType,
									pclClient->pclQuestManager->siCurrentQuestUnique, QUEST_STEP_MIDDLE);
								cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
								pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
								
								m_pBtnAccept->SetFontIndex(0);
								m_pBtnAccept->Enable(false);

								m_siCurrentState = QUEST_STEP_MIDDLE;

							}
						}
						break;

					case 1:	// �ӹ� ���
						{
							TCHAR* pTitle = GetTxtFromMgr(5424);
							TCHAR* pText = GetTxtFromMgr(5425);

							stMsgBox MsgBox;
							MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 0 );
							pclclient->SetMsgBox( &MsgBox, NULL, 0 );
						}
						break;

					case 2:	// ���� �ӹ�
						{
							if(pclClient->pclQuestManager->siCurrentQuestUnique)
							{
								if(pclClient->pclQuestManager->siCurrentQuestStep == QUEST_STEP_CLEAR)
								{
									SetAcceptButtonEnable(0, TRUE);

									cltGameMsgRequest_QuestGoing clInfo(pclClient->pclQuestManager->siQuestType,
										pclClient->pclQuestManager->siCurrentQuestUnique, QUEST_STEP_NEXTQUEST);
									cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
									pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
								}
							}
						}
						break;

					case 3:	//	 �ٽ� ����â ���̱�
						{
							m_bOpened = TRUE;
							SetOpenedQuestDlg(m_bOpened);

							SetAcceptButtonEnable(m_siOldButtonType, TRUE);
						}
						break;

					case 4:	// �������� �Ѿ��
						{
							// ���� ������ ��ȭ ���� ��û�� ������. 
							if(pclClient->pclQuestManager->siCurrentQuestUnique)
							{
								if( pclClient->pclQuestManager->siViewState == 0)
								{
									pclClient->pclQuestManager->siStartConversationCounter++;

									if(pclClient->pclQuestManager->siStartConversationNum <= pclClient->pclQuestManager->siStartConversationCounter)
									{
										//-----------------------------
										// �ڰ��� �ִ��� Ȯ���Ѵ�. 
										//-----------------------------
										cltQuestInfo* pclquestinfo = pclClient->pclQuestManager->GetQuestInfo(pclClient->pclQuestManager->siCurrentQuestUnique);

										// ���� Ȯ��. 
										if(pclquestinfo->clInitConditionInfo.siLevel)
										{
											if(pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() < pclquestinfo->clInitConditionInfo.siLevel)
											{
												TCHAR* pTitle = GetTxtFromMgr(3087);
												TCHAR* pText = GetTxtFromMgr(3088);
												pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclquestinfo->clInitConditionInfo.siLevel);
												break;
											}
										}
										// ��� Ȯ��. 
										SI32 skillunique = pclquestinfo->clInitConditionInfo.siSkillUnique;
										if(skillunique)
										{
											if(pclClient->pclCM->CR[1]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[0]) < pclquestinfo->clInitConditionInfo.siSkillLevel)
											{
												TCHAR skillname[128];
												if(pclClient->pclSkillManager->GetSkillName(skillunique, skillname) == true)
												{
													TCHAR* pTitle = GetTxtFromMgr(3087);
													TCHAR* pText = GetTxtFromMgr(3089);
													TCHAR level[128]= TEXT(" ") ;

													StringCchPrintf(level, 128,  TEXT("%d"),pclquestinfo->clInitConditionInfo.siSkillLevel);
													Nsprintf(Nbuffer,pText, TEXT("what"), skillname   , TEXT("level"),  level  ,NULL);
													pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,Nbuffer);
													//pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, skillname, pclquestinfo->clInitConditionInfo.siSkillLevel);
												}
												break;
											}
										}

										if( pclquestinfo->clQuestClearConditionInfo.siFlag == QUEST_CLEAR_COND_SETFATHER )
										{
											if( pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() < 20)
											{
												if( pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() < 20)
												{
													if( pclclient->m_pDialog[ NCHILD_DLG ] == NULL)
														pclclient->CreateInterface( NCHILD_DLG );
												}
											}
										}

										pclClient->pclQuestManager->siStartConversationCounter = 0;
										pclClient->pclQuestManager->siStartConversationNum = 0;
										pclClient->pclQuestManager->siViewState = 1;
										pclClient->pclQuestManager->bNewQuseOpened = true;
										SetOpenedQuestDlg(true);

										//if( pclClient->pclQuestManager->siQuestType == QUEST_TYPE_BEGINNER5 )
										//	SetNpcFontIndex(0);

										cltGameMsgRequest_QuestGoing clInfo(pclClient->pclQuestManager->siQuestType,
											pclClient->pclQuestManager->siCurrentQuestUnique, QUEST_STEP_MIDDLE);
										cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
										pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);

										SetAcceptButtonEnable(1, TRUE);

										m_siCurrentState = QUEST_STEP_MIDDLE;
									}
								}
								else if(pclClient->pclQuestManager->siViewState == 2)
								{
									pclClient->pclQuestManager->siEndConversationCounter++;

									if(pclClient->pclQuestManager->siEndConversationNum <= pclClient->pclQuestManager->siEndConversationCounter)
									{
										pclClient->pclQuestManager->siEndConversationCounter = 0;
										pclClient->pclQuestManager->siEndConversationNum = 0;
										pclClient->pclQuestManager->siViewState = 0;

										if(pclClient->pclQuestManager->siCurrentQuestStep == QUEST_STEP_CLEAR)
										{
											SetAcceptButtonEnable(0, TRUE);

											cltGameMsgRequest_QuestGoing clInfo(pclClient->pclQuestManager->siQuestType,
												pclClient->pclQuestManager->siCurrentQuestUnique, QUEST_STEP_NEXTQUEST);
											cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
											pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
										}

									}
								}
							}
						}
						break;
					}

				}
				break;
			}
		}
		break;
	}
}

void CNNewQuestDlg::SetAcceptButtonEnable(SI16 type, bool flag)
{

	cltClient *pclclient = (cltClient *)pclClient;

 
	if(m_pBtnHide->IsShow())
	{
		m_pBtnAccept->SetFileName( TEXT("NInterface/button/BUTTON_42x63_00_000.SPR"));
		m_pBtnAccept->MoveControl( 507, 142 );
		m_pBtnAccept->SetFontIndex(0);
	}


	switch( type)
	{
	case 0:
		if(m_bOpened)
			m_pBtnAccept->SetFontIndex(0);
		//m_pBtnAccept->SetFontIndex(4);

		else
			type = 3;

		m_siCurrentState = 0;
		break;

	case 1:
		if(m_bOpened)
			m_pBtnAccept->SetFontIndex(0);
		else
			type = 3;

		m_siCurrentState = 0;
		break;

	case 2:
		if(m_bOpened)
			m_pBtnAccept->SetFontIndex(0);
		else
			type = 3;

		m_siCurrentState = QUEST_STEP_CLEAR;
		break;

	case 3:
		
		m_pBtnAccept->SetFileName( TEXT("NInterface/button/BUTTON_26x90_00_000.SPR"));
		m_pBtnAccept->SetFontIndex(12);

		break;

	case 4:
		if(m_bOpened)
			m_pBtnAccept->SetFontIndex(0);			
		else
			type = 3;
		break;
	}
	
	m_siButtonType = type;
	m_pBtnAccept->Enable(flag);

}

void CNNewQuestDlg::SetEditCondition(TCHAR* pText)
{
	m_pEditCondition->SetText(pText);
}

void CNNewQuestDlg::SetEditStatus(TCHAR* pText)
{
	m_pEditStatus->SetText(pText);
}

void CNNewQuestDlg::SetEditQuestReward(TCHAR* pText)
{
	m_pEditQuestReward->SetText(pText);
}

void CNNewQuestDlg::SetEditExplain(TCHAR* pText)
{
	m_pEditExplain[0]->SetText(pText);
}

void CNNewQuestDlg::SetQuestName(TCHAR* pText)
{
	m_pStatic[3]->SetText(pText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_pStatic[6]->SetText(pText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CNNewQuestDlg::SetEditConversation(TCHAR* pText)
{
	m_pEditConversation->SetFontWeight(FW_BOLD);
	
	if (pclClient->siServiceArea != ConstServiceArea_English
		|| pclClient->siServiceArea != ConstServiceArea_NHNChina 
		|| pclClient->siServiceArea != ConstServiceArea_EUROPE
	)
	{
		m_pEditConversation->SetFontKind( TEXT("����"));
	}

	m_pEditConversation->SetFontSize(20);
	m_pEditConversation->SetLineHeight( 25 );
	m_pEditConversation->SetText(pText);
}
void CNNewQuestDlg::SetOpenedQuestDlg( BOOL Open )
{
 	cltClient *pclclient = (cltClient *)pclClient;

	if(Open)	// ��������
	{
		m_bOpened = TRUE;

		SetFileName(  TEXT("NInterface/interface/Interface_566x220_00_000.SPR") );
	
		if(pclClient->pclQuestManager->siViewState == 0 || pclClient->pclQuestManager->siViewState == 2)
		{
			SetFontIndex( 1 );

			m_pStatic[0]->Show(false); // 0: ���� 1: �ӹ� 2: ���� 3: ����Ʈ ����
			m_pStatic[1]->Show(false);
			m_pStatic[2]->Show(false);
			m_pStatic[3]->Show(true);
			m_pStatic[4]->Show(false);
			m_pStatic[5]->Show(false);
			m_pStatic[6]->Show(false);

			m_pEditCondition->Show(false);
			m_pEditStatus->Show(false);
			m_pEditQuestReward->Show(false);
			m_pEditExplain[0]->Show(false);
			m_pEditExplain[1]->Show(false);
			m_pEditConversation->Show(true);

			m_pBtnClose->Show(true);
			m_pBtnHide->Show(true);
		}
		else
		{
			SetFontIndex( 0 );

			m_pStatic[3]->Show(false);
			m_pStatic[4]->Show(TRUE);
			m_pStatic[5]->Show(TRUE);

			m_pEditCondition->Show(TRUE);
			m_pEditStatus->Show(TRUE);
			m_pEditQuestReward->Show(TRUE);
			m_pEditExplain[0]->Show(TRUE);
			m_pEditExplain[1]->Show(TRUE);
			m_pEditConversation->Show(false);

			m_pBtnClose->Show(TRUE);
			m_pBtnHide->Show(TRUE);
		}

		SetBKTileImgNum( 0 );

		SetHaveCaption( false );
		SetMoveable( false );

		if((gsiResolution == 2) ||(gsiResolution == 4)) // 1024x768 || 1024x600
		{
			SetDialogPos(pclclient->GetScreenXSize() - 566, pclclient->GetScreenYSize() - 270, 566, 220 );
		}
		else
		{

		}

		m_pBtnAccept->SetFileName( TEXT("NInterface/button/BUTTON_42x63_00_000.SPR"));
		
		
			}

	else	//	������ ����
	{
		SetFileName(  TEXT("") );
		//	SetFontIndex( 12 );
		//	SetBKTileImgNum( 0 );

		SetHaveCaption( false );
		SetMoveable( false );


		if( g_SoundOnOffDlg.m_bFullScreenMode )
			SetDialogPos( pclclient->GetScreenXSize() - 26, pclclient->GetScreenYSize() - 139, 26, 90 );
		else
			SetDialogPos( pclclient->GetScreenXSize() - 26, pclclient->GetScreenYSize() - 117, 26, 90 );

		m_pBtnAccept->SetFileName( TEXT("NInterface/button/BUTTON_26x90_00_000.SPR"));
		m_pBtnAccept->SetFontIndex(12);
		m_pBtnAccept->MoveControl( 0, 0 );

		m_pStatic[3]->Show(FALSE);
		m_pStatic[4]->Show(FALSE);
		m_pStatic[5]->Show(FALSE);

		m_pEditCondition->Show(FALSE);
		m_pEditStatus->Show(FALSE);
		m_pEditQuestReward->Show(FALSE);
		m_pEditExplain[0]->Show(FALSE);
		m_pEditExplain[1]->Show(FALSE);
		m_pEditConversation->Show(false);

		m_pBtnClose->Show(FALSE);
		m_pBtnHide->Show(FALSE);

		//	SetTopMostWindow( true );

	}
	
}


void CNNewQuestDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient*)pclClient;

	switch( MsgIndex )
	{
	case 0:
		{
			if ( RetValue )
			{
				if(pclClient->pclQuestManager->siCurrentQuestUnique)
				{
					cltGameMsgRequest_CancelQuest clInfo(pclClient->pclQuestManager->siQuestType,
						pclClient->pclQuestManager->siCurrentQuestUnique);
					cltMsg clMsg(GAMEMSG_REQUEST_CANCELQUEST, sizeof(clInfo), (BYTE*)&clInfo);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);

					SetAcceptButtonEnable(0, TRUE);
					pclClient->pclQuestManager->bNewQuseOpened = FALSE;
				}

			}
		}
		break;
	}
}
