//---------------------------------
// 2005/03/11 ���ؿ�
//---------------------------------
#include "../Client/Client.h"

#include "CommonLogic.h"
#include "Char/CharCommon/Char-Common.h"
#include "Quest.h"
#include "Char/CharManager/CharManager.h"

#include "../resource.h"
#include "MsgType-Person.h"
#include "Msg/MsgType-Quest.h"
#include "../Client/Music/Music.h"
#include "../Skill/Skill-Manager.h"
#include "../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../Client/NInterface/NQuestDlg/NQuestDlg.h"
#include "../Client/ninterface/ncharstatus/NCharQuest.h"
#include "../Client/ninterface/ChristmasQuestDlg/ChristmasQuestDlg.h"

#include "../Client/InterfaceMgr/DialogController.h"
#include "../Client/InterfaceMgr/Interface/Button.h"
#include "../Client/InterfaceMgr/interface/ComboBox.h"
#include "../Client/InterfaceMgr/Interface/List.h"
#include "../Client/InterfaceMgr/Interface/Static.h"
#include "../Client/InterfaceMgr/Interface/Edit.h"
#include "../Client/InterfaceMgr/Interface/ImageStatic.h"

#include "../Client/InterfaceMgr/InterfaceMgr.h"
#include "../Client/InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../Client/InterfaceMgr/InterfaceFile.h"

#include "../SystemNPC/SystemNPC.h"
#include "../Client/NInterface/NNewQuestDlg/NNewQuestDlg.h"
#include "../Client/ninterface/nnewmakeitem/NNewMakeItemDlg.h"
#include "../Client/ninterface/niteminfodlg/ItemInfoDlg.h"
#include "../Client/ninterface/ninfodlg/NInfoDlg.h"
#include "../Client/ninterface/NQuestSelectItem/NQuestSelectItemDlg.h"

#include "../Client/Interface/ToolBarDlg/ToolBarDlg.h"

#include "../Client/Gametip/GameTip.h"

#include "Util/Util.h"

//------------------------------------
// Lib
//------------------------------------
#include "HashTable/HashTable_StringInt.h"

extern cltCommonLogic* pclClient;

void cltQuestManager::InitDialog(SI32 kind)
{
	cltClient* pclclient = (cltClient*)pclClient;

	siKind = kind;		// ����Ʈ NPC�� ������ �����Ѵ�. 
	//---------------------------------
	// �ʱ�ȭ.
	//---------------------------------
	siStartConversationNum	= 0;
	siStartConversationCounter = 0;
	siEndConversationNum	= 0;
	siEndConversationCounter = 0;
	siCurrentQuestUnique	= 0;

	siCurrentQuestStep		= QUEST_STEP_GREETING;
	siViewState = 1;

	//---------------------------------
	// ����Ʈ Ÿ���� �����ΰ� ?
	//---------------------------------
	// NPCKind�� �ο��ϴ� ����Ʈ�� Ÿ���� ���´�. 

	if(siKind == pclClient->GetUniqueFromHash(TEXT("KIND_RUDOLPH")))
	{
		// ���� �����ϰ� �ִ� ����Ʈ�� �ִٸ�, �����ϴ� ����Ʈ�� ���õȴ�.
		cltPersonQuestUnitInfo* pclunit[4];
		pclunit[0] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MAKESANTAHAT];
		pclunit[1] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MAKECAKE];
		pclunit[2] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_PLAYCHRISTMAS];
		pclunit[3] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_PLAYCHRISTMASHIDDEN];

		if( pclunit[0]->siCurQuestUnique > 0 || pclunit[0]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_MAKESANTAHAT;
		else if( pclunit[1]->siCurQuestUnique > 0 || pclunit[1]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_MAKECAKE;
		else if( pclunit[2]->siCurQuestUnique > 0 || pclunit[2]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_PLAYCHRISTMAS;
		else if( pclunit[3]->siCurQuestUnique > 0 || pclunit[3]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_PLAYCHRISTMASHIDDEN;
		else
			siQuestType = 0;

		// ���� �����ϰ� �ִ� ����Ʈ�� ���ٸ�
		// �絹�� ����â���� ������ ����Ʈ�� ���õȴ�.
		if(siQuestType <= 0)
		{
			if( pclclient->m_pDialog[ NNEWQUEST_DLG ] != NULL)
			{
				siQuestType = ((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_siQuestType_Rudolph;
			}
		}
	}

	else if(siKind == pclClient->GetUniqueFromHash(TEXT("KIND_PANG")))
	{
		// ���� �����ϰ� �ִ� ����Ʈ�� �ִٸ�, �����ϴ� ����Ʈ�� ���õȴ�.
		cltPersonQuestUnitInfo* pclunit[5];
		pclunit[0] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_DRESS];
		pclunit[1] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_HAT];
		pclunit[2] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_MENTAL];
		pclunit[3] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_RING];
		pclunit[4] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_NECK];

		if( pclunit[0]->siCurQuestUnique > 0 || pclunit[0]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_AVATAR_DRESS;
		else if( pclunit[1]->siCurQuestUnique > 0 || pclunit[1]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_AVATAR_HAT;
		else if( pclunit[2]->siCurQuestUnique > 0 || pclunit[2]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_AVATAR_MENTAL;
		else if( pclunit[3]->siCurQuestUnique > 0 || pclunit[3]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_AVATAR_RING;
		else if( pclunit[4]->siCurQuestUnique > 0 || pclunit[4]->siCurQuestStep > 0 )
			siQuestType = QUEST_TYPE_AVATAR_NECK;
		else
			siQuestType = 0;

		// ���� �����ϰ� �ִ� ����Ʈ�� ���ٸ�
		// �絹�� ����â���� ������ ����Ʈ�� ���õȴ�.
		if(siQuestType <= 0)
		{
			if( pclclient->m_pDialog[ NNEWQUEST_DLG ] != NULL)
			{
				siQuestType = ((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_siQuestType_Rudolph;
			}
		}
	}

	else
	{
		siQuestType = GetQuestTypeFromNPCKind(siKind);
	}

	// PCK : �Ҿ���� ���� ����Ʈ���� Ư�����ǽ÷� ���� ����Ʈ�� ������� �Ҷ� (09.05.12)
	if(siKind == pclClient->GetUniqueFromHash(TEXT("KIND_KELAN")) || siKind == pclClient->GetUniqueFromHash(TEXT("KIND_MOLDA")))
	{
		if( pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_GONPC_INFORMATION))
		{
			siQuestType = QUEST_TYPE_HUNTINGGROUND14;
		}
	}
	else if(siKind == pclClient->GetUniqueFromHash(TEXT("KIND_MERIEL")))
	{
		if ( pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestClearOrGoing(QUEST_TYPE_FINDTREASURE ))
		{
			siQuestType = QUEST_TYPE_FINDTREASURE;
		}
	}
	//--------------------------------
	// ���� �������� ����Ʈ�� �ش��ϴ� ��Ʈ�� ȭ�鿡 ����Ѵ�. 
	//--------------------------------

	// �������� ����Ʈ�� Ȯ���Ѵ�. 
	//����Ʈ�� �ؽ�Ʈ�� ���õ� �κе�.
	GetCurrentQuestInfo();
	ShowText(true);	// ������ �ؽ�Ʈ�� �����ش�. 
	bQuestInfoChangedSwitch = true;
}

void cltQuestManager::Action()
{
	static clock_t PreClock = 0;

	cltClient *pclclient = (cltClient *)pclClient;

	if( bNewQuseOpened ) //	�� ����Ʈâ�� ���ȴ�
	{
		if( pclclient->m_pDialog[ NNEWQUEST_DLG ] == NULL )			return;

		// �������� ����Ʈ�� Ȯ���Ѵ�. 
		GetCurrentQuestInfo();

		// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
		if(siCurrentQuestUnique)
		{
			cltQuestInfo* pclinfo = GetQuestInfo(siCurrentQuestUnique);
			if(pclinfo)
			{
				// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
				if(siCurrentQuestStep == QUEST_STEP_MIDDLE)
				{
				
					if(pclClient->pclCM->CR[siID]->IsClearCondition(siQuestType, &pclinfo->clQuestClearConditionInfo) == true)
					{
						//cyj ��������Ʈ �Ϸ������ �ð� ����
						if ( TABS( pclclient->CurrentClock - PreClock ) > 500 )
						{
							// ����, ���� ���� ����Ʈ ����
							//if( siQuestType == QUEST_TYPE_BEGINNER5 && pclClient->siServiceArea == ConstServiceArea_Korea && bNewQuestDoing == TRUE) 
							//{
							//	siViewState = 2;

							//	((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->InitNewQuest();
							//	((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg(true);
							//}

							if ( pclinfo->clQuestRewardInfo.bSelectItem )
							{
								ShowSelectItemDlg( &pclinfo->clQuestRewardInfo, siQuestType, siCurrentQuestUnique );
								PreClock = pclclient->CurrentClock;
								return;
							}

							cltGameMsgRequest_QuestGoing clInfo(siQuestType, siCurrentQuestUnique, QUEST_STEP_CLEAR);
							cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
							pclClient->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);
							PreClock = pclclient->CurrentClock;
						}
					}
				}
			}
		}

		ShowText(false);
			
		// ���� ��ư Ȱ��ȭ ����.
		if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_GREETING)
		{
			((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetAcceptButtonEnable(0, true);
		}
	

		// ��� ��ư Ȱ��ȭ ����. 
		if(siCurrentQuestUnique && siCurrentQuestStep != QUEST_STEP_GREETING
			&& siCurrentQuestUnique && siCurrentQuestStep < QUEST_STEP_CLEAR)
		{
			if( ((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_bOpened == TRUE )
			{
				((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pBtnAccept->Enable(false);
			}
		}
		
		// ���� �ӹ� ��ư  Ȱ��ȭ ����.
		if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_CLEAR)
		{
			((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetAcceptButtonEnable(2, true);
		}
		
		if (pclClient->pclCM->CR[siID]->pclCI->clQuestInfo.IsAllClear(this, siQuestType))
		{ 
            static SI32 siLastClearType = 0;
			bool bPlayOnetiem = false;

			if( siLastClearType == siQuestType )
				bPlayOnetiem = false;
			else
				bPlayOnetiem = true;

			ShowText( bPlayOnetiem );
			
			siLastClearType = siQuestType;

			((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pBtnAccept->Enable(false);
		}
		
	}
	else//��â�� �ȿ������.
	{
		if ( pclclient->m_pDialog[ NQUEST_DLG ] == NULL ) return ;

		// �������� ����Ʈ�� Ȯ���Ѵ�. 
		GetCurrentQuestInfo();

		// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
		if(siCurrentQuestUnique)
		{
			cltQuestInfo* pclinfo = GetQuestInfo(siCurrentQuestUnique);
			if(pclinfo)
			{
				// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
				if(siCurrentQuestStep == QUEST_STEP_MIDDLE)
				{
					if(pclClient->pclCM->CR[siID]->IsClearCondition(siQuestType, &pclinfo->clQuestClearConditionInfo) == true)
					{

						// �������� �����ϴ� ��쿡�� ����â�� �����ش�. ����Ʈ ������ ������ ����
						if ( pclinfo->clQuestRewardInfo.bSelectItem )
						{
							ShowSelectItemDlg( &pclinfo->clQuestRewardInfo, siQuestType, siCurrentQuestUnique );
							return;
						}

						cltGameMsgRequest_QuestGoing clInfo(siQuestType, siCurrentQuestUnique, QUEST_STEP_CLEAR);
						cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
						pclClient->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}

		ShowText(false);

		// ���� ��ư Ȱ��ȭ ����.
		if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_GREETING)
		{
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pAcceptButton->Enable(true);
		}
		else
		{
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pAcceptButton->Enable(false);
		}
		

		// ��� ��ư Ȱ��ȭ ����. 
		if(siCurrentQuestUnique && siCurrentQuestStep != QUEST_STEP_GREETING
			&& siCurrentQuestUnique && siCurrentQuestStep < QUEST_STEP_CLEAR)
		{
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pCancelButton->Enable(true);
		}
		else
		{
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pCancelButton->Enable(false);
		}
		

		// ���� �ӹ� ��ư  Ȱ��ȭ ����.
		if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_CLEAR)
		{
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pOKButton->Enable(true);
		}
		else
		{
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pOKButton->Enable(false);
		}
	}
	


/*
#ifdef _DEBUG
	if( pclclient->m_pDialog[ NNEWQUEST_DLG ] == NULL ) return;

	if ( pclclient->m_pDialog[ NQUEST_DLG ] == NULL ) return ;
#else
	

	if ( pclclient->m_pDialog[ NQUEST_DLG ] == NULL ) return ;
#endif
	
	// �������� ����Ʈ�� Ȯ���Ѵ�. 
	GetCurrentQuestInfo();

	// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
	if(siCurrentQuestUnique)
	{
		cltQuestInfo* pclinfo = GetQuestInfo(siCurrentQuestUnique);
		if(pclinfo)
		{
			// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
			if(siCurrentQuestStep == QUEST_STEP_MIDDLE)
			{
				if(pclClient->pclCM->CR[siID]->IsClearCondition(siQuestType, &pclinfo->clQuestClearConditionInfo) == true)
				{
					cltGameMsgRequest_QuestGoing clInfo(siQuestType, siCurrentQuestUnique, QUEST_STEP_CLEAR);
					cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
					pclClient->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
	}

	ShowText(false);
	
#ifdef _DEBUG
	// ���� ��ư Ȱ��ȭ ����.
	if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_GREETING)
	{
		((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetAcceptButtonEnable(0, true);
	}

	// ��� ��ư Ȱ��ȭ ����. 
	if(siCurrentQuestUnique && siCurrentQuestStep != QUEST_STEP_GREETING
		&& siCurrentQuestUnique && siCurrentQuestStep < QUEST_STEP_CLEAR)
	{
		((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetAcceptButtonEnable(1, true);
	}
	
	// ���� �ӹ� ��ư  Ȱ��ȭ ����.
	if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_CLEAR)
	{
		((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetAcceptButtonEnable(2, true);
	}
	
	// ���� ��ư Ȱ��ȭ ����.
	if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_GREETING)
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pAcceptButton->Enable(true);
	}
	else
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pAcceptButton->Enable(false);
	}

	// ��� ��ư Ȱ��ȭ ����. 
	if(siCurrentQuestUnique && siCurrentQuestStep != QUEST_STEP_GREETING
		&& siCurrentQuestUnique && siCurrentQuestStep < QUEST_STEP_CLEAR)
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pCancelButton->Enable(true);
	}
	else
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pCancelButton->Enable(false);
	}

	// ���� �ӹ� ��ư  Ȱ��ȭ ����.
	if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_CLEAR)
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pOKButton->Enable(true);
	}
	else
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pOKButton->Enable(false);
	}
#else


	// ���� ��ư Ȱ��ȭ ����.
	if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_GREETING)
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pAcceptButton->Enable(true);
	}
	else
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pAcceptButton->Enable(false);
	}
	
	// ��� ��ư Ȱ��ȭ ����. 
	if(siCurrentQuestUnique && siCurrentQuestStep != QUEST_STEP_GREETING
		&& siCurrentQuestUnique && siCurrentQuestStep < QUEST_STEP_CLEAR)
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pCancelButton->Enable(true);
	}
	else
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pCancelButton->Enable(false);
	}

	// ���� �ӹ� ��ư  Ȱ��ȭ ����.
	if(siCurrentQuestUnique && siCurrentQuestStep == QUEST_STEP_CLEAR)
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pOKButton->Enable(true);
	}
	else
	{
		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pOKButton->Enable(false);
	}
#endif*/
}

// �ؽ�Ʈ�� ȭ�鿡 �����ش�. 
void cltQuestManager::ShowText(bool forceswitch)
{
	cltClient *pclclient = (cltClient *)pclClient;

	if( bNewQuseOpened )	// �� ����Ʈ ���ȴ�
	{
		if ( pclclient->m_pDialog[ NNEWQUEST_DLG ] == NULL )
			return ;
	
		if( (siViewState == 0 || siViewState == 2) && bNewQuestDoing == TRUE )
		{
			if(siCurrentQuestUnique)
			{
				//--------------------
				// Ÿ��Ʋ�� �����ش�. 
				//--------------------
				cltQuestInfo* pclquestinfo = GetQuestInfo(siCurrentQuestUnique);
				if(pclquestinfo)
				{
					const TCHAR* pkindname = pclClient->pclKindInfoSet->GetName(siKind);
					if(pkindname)
					{
						TCHAR buffer[256];
						StringCchPrintf(buffer, 256, TEXT("%s - %s"), pkindname, pclquestinfo->szTitleText);

						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetQuestName(buffer);
					}
				
					if( siCurrentQuestStep == QUEST_STEP_MIDDLE)
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditConversation(TEXT(""));
					else
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditConversation(GetText(siCurrentQuestUnique,siCurrentQuestStep));
				}
			}
		}
		else
		{
			static SI32 oldcurrentquestunique	= 0;
			static SI32 oldcurrentqueststep		= 0;
			static SI32 oldpara2				= 0;

			//-----------------------
			// ���� ���¸� �����ش�. 
			//----------------------
			TCHAR szcurstatustext[1024] =TEXT("");
			
			//cyj ���� ���� ��� ����Ʈ ���� ���������� ����
			//pclClient->pclQuestManager->GetCurStatusText(siID, siQuestType, siCurrentQuestUnique, szcurstatustext, 1024);
			cltQuestInfo* clquestinfo = GetQuestInfo(siCurrentQuestUnique);
			if (clquestinfo)
				StringCchPrintf(szcurstatustext, 1024, TEXT("%s"), clquestinfo->szTitleText);

			((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditStatus(szcurstatustext);
			            
			SI32 para2	= pclClient->pclCM->CR[siID]->pclCI->clQuestInfo.clUnit[siQuestType].siQuestPara2;
			if(forceswitch == false)
			{
				// �޶��� ������ ���ٸ� ������� �ʴ´�. 
				if(oldcurrentquestunique == siCurrentQuestUnique
					&& oldcurrentqueststep	== 	siCurrentQuestStep
					&& oldpara2				== para2)
				{
					return ;
				}
			}

			// ����� ������ ����� ���´�. (�ٽ� ������� �ʱ� ����. ) 
			oldcurrentquestunique	= siCurrentQuestUnique;
			oldcurrentqueststep		= siCurrentQuestStep;
			oldpara2				= para2;

			// �ӹ� ����� ȿ���� ����. 
			if(siCurrentQuestStep == QUEST_STEP_CLEAR  )
			{
				pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_SUCCESS")), 0, 0);
			}

			const TCHAR* pkindname = pclClient->pclKindInfoSet->GetName(siKind);
			TCHAR titlename[256];
			StringCchPrintf(titlename, 256, TEXT("%s"), pkindname);

			((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetQuestName(titlename);

			if(siCurrentQuestUnique)
			{
				//--------------------
				// Ÿ��Ʋ�� �����ش�. //ȭ�鿡 ���� Ÿ��Ʋ
				//--------------------
				cltQuestInfo* pclquestinfo = GetQuestInfo(siCurrentQuestUnique);
				if(pclquestinfo)
				{
					const TCHAR* pkindname = pclClient->pclKindInfoSet->GetName(siKind);
					if(pkindname)
					{
						TCHAR buffer[256];
						StringCchPrintf(buffer, 256, TEXT("%s - %s"), pkindname, pclquestinfo->szTitleText);

						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetQuestName(buffer);
					}
				}

				//---------------------
				// ������ �����ش�. 
				//---------------------
				if(pclquestinfo)
				{
					//---------------------------
					// �ӹ� �ο� ������ �����ش�. 
					//---------------------------
					TCHAR buffer[1024] = TEXT("");
					if(pclquestinfo->clInitConditionInfo.siLevel)
					{
						TCHAR temp[256];

						TCHAR* pText = GetTxtFromMgr(3008);
						StringCchPrintf(temp, 256, pText, pclquestinfo->clInitConditionInfo.siLevel);
						StringCchCat(buffer, 1024, temp);
					}
					if(pclquestinfo->clInitConditionInfo.siSkillUnique)
					{
						TCHAR skillname[128];
						if(pclClient->pclSkillManager->GetSkillName(pclquestinfo->clInitConditionInfo.siSkillUnique, skillname) == true)
						{
							TCHAR temptext[128];
							TCHAR* pText = GetTxtFromMgr(3009);
							StringCchPrintf(temptext, 128, pText, skillname, pclquestinfo->clInitConditionInfo.siSkillLevel);

							StringCchCat(buffer, 1024, temptext);
						}
					}

					((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditCondition(buffer);
					
					TCHAR szText[1024 + 32] = { '\0', };

					// ��� ������ ������ �ִٸ�, ����Ʈ ����ũ ��ȣ�� ǥ���Ѵ�.
					if( pclClient->pclCM->CR[1]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL )
					{
						StringCchPrintf(szText, sizeof(szText), "%s[%d][%d]", GetText(siCurrentQuestUnique, siCurrentQuestStep), siQuestType, siCurrentQuestUnique);
					}
					else
					{
						StringCchCopy( szText, sizeof(szText), GetText(siCurrentQuestUnique, siCurrentQuestStep) );
					}

					// ����Ʈ ��翡 ĳ���� �̸�
					NTCHARString1024 strText = szText;
					strText.ReplaceAll( TEXT("#charname#"), (TCHAR*)pclClient->pclCM->CR[1]->GetName() );

					TCHAR	FullPathName[MAX_PATH] = TEXT("") ;
					SI32	Font  = 0 ;
					if ( !pclClient->IsWhereServiceArea(ConstServiceArea_Korea) &&		// �ѱ� �Ѱ����� �ӽ��ڵ�� ó���ȴ�.
						 GetSprPath(siCurrentQuestUnique,siCurrentQuestStep,&Font,FullPathName) == true )
					{
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[1]->Show(FALSE);
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[1]->SetText(TEXT(""));

						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[0]->Show(TRUE);
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[0]->SetText(strText);

						((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[4]->SetFileName(FullPathName);
						((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[4]->SetFontIndex(Font);
						((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[5]->SetFileName(TEXT("NInterface/Image/Image_92x92_00_000.SPR"));
						((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[5]->SetFontIndex(8);
						((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[5]->Show(TRUE);
					}
					else
					{
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[0]->Show(FALSE);
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[0]->SetText(TEXT(""));

						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[1]->Show(TRUE);
						((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[1]->SetText(strText);

						((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[4]->SetFileName(TEXT(""));
						((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[5]->SetFileName(TEXT(""));
						//	((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pStatic[5]->Show(FALSE);
					}
				}
			}
			else
			{
				//	((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pSprStatic->SetFileName(TEXT(""));
				((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[1]->Show(FALSE);
				((CNNewQuestDlg*)pclclient->m_pDialog[ NNEWQUEST_DLG ])->m_pEditExplain[1]->SetText(TEXT(""));

				((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditStatus(TEXT(""));
				((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditCondition(TEXT(""));
				((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditExplain(GetText(0,0));
			}

			TCHAR buffer[1024]=TEXT("");
			cltQuestInfo* pclquestinfo = GetQuestInfo(siCurrentQuestUnique);
			if(pclquestinfo)
			{
				pclquestinfo->clQuestRewardInfo.GetExplainText(buffer, 1024);
			}

			((CNNewQuestDlg *)pclclient->m_pDialog[ NNEWQUEST_DLG ])->SetEditQuestReward(buffer);
		}
	}
	else	// ���� ����Ʈâ
	{
		if ( pclclient->m_pDialog[ NQUEST_DLG ] == NULL || pclclient->m_pDialog[ NQUEST_DLG ]->IsShow() == false ) return ;

		static SI32 oldcurrentquestunique	= 0;
		static SI32 oldcurrentqueststep		= 0;
		static SI32 oldpara2				= 0;

		//------------------------------
		// ĳ������ �ʻ�ȭ�� �����ش�. 
		//------------------------------
		if(siKind)
		{
			TCHAR szPortrait[256];
			SI32 siPortraitFont;
			pclClient->pclKindInfoSet->GetNPCImageFileAndFont(siKind, szPortrait, sizeof(szPortrait), &siPortraitFont);
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pPortraitStatic->SetFileName(  szPortrait );
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pPortraitStatic->SetFontIndex( siPortraitFont ) ;
		}

		SI32 para2	= pclClient->pclCM->CR[siID]->pclCI->clQuestInfo.clUnit[siQuestType].siQuestPara2;
		if(forceswitch == false)
		{
			// �޶��� ������ ���ٸ� ������� �ʴ´�. 
			if(oldcurrentquestunique == siCurrentQuestUnique
				&& oldcurrentqueststep	== 	siCurrentQuestStep
				&& oldpara2				== para2)
			{
				return ;
			}
		}

		// ����� ������ ����� ���´�. (�ٽ� ������� �ʱ� ����. ) 
		oldcurrentquestunique	= siCurrentQuestUnique;
		oldcurrentqueststep		= siCurrentQuestStep;
		oldpara2				= para2;

		// �ӹ� ����� ȿ���� ����. 
		if(siCurrentQuestStep == QUEST_STEP_CLEAR)
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_SUCCESS")), 0, 0);
		}

		const TCHAR* pkindname = pclClient->pclKindInfoSet->GetName(siKind);
		TCHAR titlename[256];
		StringCchPrintf(titlename, 256, TEXT("%s"), pkindname);

		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->SetTitle(titlename);

		if(siCurrentQuestUnique)
		{
			//--------------------
			// Ÿ��Ʋ�� �����ش�. 
			//--------------------
			cltQuestInfo* pclquestinfo = GetQuestInfo(siCurrentQuestUnique);
			if(pclquestinfo)
			{
				const TCHAR* pkindname = pclClient->pclKindInfoSet->GetName(siKind);
				if(pkindname)
				{
					TCHAR buffer[256];
					StringCchPrintf(buffer, 256, TEXT("%s - %s"), pkindname, pclquestinfo->szTitleText);

					((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->SetTitle(buffer);
				}
			}

			//---------------------
			// ������ �����ش�. 
			//---------------------
			if(pclquestinfo)
			{
				((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pExplainEdit->SetText( GetText(siCurrentQuestUnique,siCurrentQuestStep));

				//---------------------------
				// �ӹ� �ο� ������ �����ش�. 
				//---------------------------
				TCHAR buffer[1024] = TEXT("");
				if(pclquestinfo->clInitConditionInfo.siLevel)
				{
					TCHAR temp[256];

					TCHAR* pText = GetTxtFromMgr(3008);
					StringCchPrintf(temp, 256, pText, pclquestinfo->clInitConditionInfo.siLevel);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclquestinfo->clInitConditionInfo.siSkillUnique)
				{
					TCHAR skillname[128];
					if(pclClient->pclSkillManager->GetSkillName(pclquestinfo->clInitConditionInfo.siSkillUnique, skillname) == true)
					{
						TCHAR temptext[128];
						TCHAR* pText = GetTxtFromMgr(3009);
						StringCchPrintf(temptext, 128, pText, skillname, pclquestinfo->clInitConditionInfo.siSkillLevel);

						StringCchCat(buffer, 1024, temptext);
					}
				}

				((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pConditionEdit->SetText(buffer);

				TCHAR	FullPathName[MAX_PATH] = TEXT("") ;
				SI32	Font  = 0 ;
				if ( GetSprPath(siCurrentQuestUnique,siCurrentQuestStep,&Font,FullPathName) == true )
				{
					((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pSprStatic->SetFileName(FullPathName);
					((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pSprStatic->SetFontIndex(Font);
				}
				else
				{
					((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pSprStatic->SetFileName(TEXT(""));
				}
			}
			//-----------------------
			// ���� ���¸� �����ش�. 
			//----------------------
			TCHAR szcurstatustext[1024] =TEXT("");
			pclClient->pclQuestManager->GetCurStatusText(siID, siQuestType, siCurrentQuestUnique, szcurstatustext, 1024);

			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pStatusEdit->SetText(szcurstatustext);
		}
		else
		{
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pSprStatic->SetFileName(TEXT(""));
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pStatusEdit->SetText(TEXT(""));
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pConditionEdit->SetText(TEXT(""));
			((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pExplainEdit->SetText(GetText(0,0));
		}

		TCHAR buffer[1024]=TEXT("");
		cltQuestInfo* pclquestinfo = GetQuestInfo(siCurrentQuestUnique);
		if(pclquestinfo)
		{
			pclquestinfo->clQuestRewardInfo.GetExplainText(buffer, 1024);
		}

		((cltNQuestDlg *)pclclient->m_pDialog[ NQUEST_DLG ])->m_pQuestRewardEdit->SetText(buffer);
	}
}

// ����Ʈ�� ����ũ�� ���ܿ� ���� ������ ��縦 ���´�.
TCHAR* cltQuestManager::GetText(SI32 questunique, SI32 queststep)
{
	if( (questunique == 0 && queststep == 0) || (pclClient->pclCM->CR[siID]->pclCI->clQuestInfo.IsAllClear(this, siQuestType)) )
	{
		if(pclClient->IsCountrySwitch(Switch_GameTip))
		{
			cltClient* pclclient = (cltClient*)pclClient;
			NTCHARString<2048> kGameTipText;
			kGameTipText = pclclient->m_pclGameTip->RandTipText();
			kGameTipText.ReplaceAll("\r", "");
			TCHAR* pGameTipText = kGameTipText;
			
			if( pGameTipText )
			{
				static TCHAR Buffer[1024] = "";	
				ZeroMemory( Buffer, sizeof(Buffer) );

				if( _tcscmp(pGameTipText,_TEXT("")))
				{
					StringCchPrintf( Buffer, sizeof(Buffer), TEXT("%s \r\n\r\n <C05>%s \r\n\r\n %s</C>"),
						GetTxtFromMgr(5064), "Tip!!", pGameTipText);
				}
				else
				{
					StringCchPrintf( Buffer, sizeof(Buffer), TEXT("%s \r\n\r\n"),
						GetTxtFromMgr(5064));
				}
				return Buffer;
			}
			else
			{
				return GetTxtFromMgr(5064) ;
			}
		}
		else
		{
			return GetTxtFromMgr(5064) ;
		}
	}
	// PCK : QUEST_CLEAR_COND_GONPC_INFORMATION�� ������ �ش� �κ��� �����ش�.
	else if((questunique == 29050) && siKind == pclClient->GetUniqueFromHash(TEXT("KIND_KELAN")) && pclClient->pclCM->CR[siID]->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_GONPC_INFORMATION))
	{
		return GetTxtFromMgr(30038);
	}
	else if((questunique == 29110) && siKind == pclClient->GetUniqueFromHash(TEXT("KIND_MOLDA")) && pclClient->pclCM->CR[siID]->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_GONPC_INFORMATION))
	{
		return GetTxtFromMgr(30039);
	}

	/*else if(siKind == pclClient->GetUniqueFromHash(TEXT("KIND_MERIEL")) && pclClient->pclCM->CR[siID]->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_GONPC_INFORMATION))
	{
		return GetTxtFromMgr(30038);
	}*/
	else
	{
		cltClient *pclclient = (cltClient *)pclClient;

		cltQuestInfo* pclquestinfo = GetQuestInfo(questunique);
		if(pclquestinfo == NULL)	
		{
			return TEXT("NoText") ;
		}

		SI32 bit = GetBitFromUnique(pclquestinfo->siType,questunique);
		switch(queststep)
		{
			case QUEST_STEP_GREETING:
				{
					return clQuestTxtInfo[pclquestinfo->siType][bit].szQuestGreeting ;
				}
				break;
			case QUEST_STEP_MIDDLE:
				{
					return clQuestTxtInfo[pclquestinfo->siType][bit].szQuestMiddle ;
				}
				break;
			case QUEST_STEP_CLEAR:
				{
					return clQuestTxtInfo[pclquestinfo->siType][bit].szQuestClear ;
				}
				break;
		}
	}

	return TEXT("NoText") ;
}

bool cltQuestManager::GetSprPath(SI32 questunique,SI32 queststep,SI32 * font , TCHAR * fullpathname)
{
	TCHAR  filename[256] = TEXT("") ;

	memset(fullpathname, 0, MAX_PATH);

	if(questunique == 0 && queststep == 0)
	{
		return false ;
	}
	else
	{
		cltQuestInfo* pclquestinfo = GetQuestInfo(questunique);
		if(pclquestinfo == NULL)	
		{
			memset(fullpathname, 0, MAX_PATH);
			return false;
		}

		StringCchPrintf(filename, 256, TEXT("Quest/%s/%s.spr"), szQuestTypeName[pclquestinfo->siType],szQuestTypeName[pclquestinfo->siType]);
		StringCchCat(fullpathname, _MAX_PATH, filename);

		SI32 bit = GetBitFromUnique(pclquestinfo->siType,questunique);
		switch(queststep)
		{
		case QUEST_STEP_GREETING:
			{
				*font = clQuestTxtInfo[pclquestinfo->siType][bit].siGreetingSpr ;
			}
			break;
		case QUEST_STEP_MIDDLE:
			{
				*font = clQuestTxtInfo[pclquestinfo->siType][bit].siMiddleSpr ;
			}
			break;
		case QUEST_STEP_CLEAR:
			{
				*font = clQuestTxtInfo[pclquestinfo->siType][bit].siClearSpr ;
			}
			break;
		}
	}

	FILE *fp = _tfopen(fullpathname, TEXT("rt"));
	if(fp == NULL || *font == -1 )
	{
		memset(fullpathname, 0, MAX_PATH);
		*font = -1 ;

		if ( fp )
			fclose(fp);

		return false;
	}

	if ( fp )
		fclose(fp);

	return true ;

}

void cltQuestManager::DrawClickMouse(LPDIRECTDRAWSURFACE7 lpSurface, SI32 unique)
{
	cltClient *pclclient = (cltClient *)pclClient;

	if ( siCurrentQuestStep != QUEST_STEP_MIDDLE )
		return;

	cltCharClient* pclchar = (cltCharClient*)pclclient->pclCM->CR[1];
	SI32 siCurrentQuestCommand	= pclchar->pclCI->clQuestInfo.clUnit[siQuestType].siQuestCmd;
	SI32 adjustX = 0;
	bool bShow = false;

	switch( siCurrentQuestCommand )
	{
	case QUEST_CLEAR_COND_OPENCHARSTATUS:
	case QUEST_CLEAR_COND_BONUSZERO:
		{
			if( pclclient->IsOpenInterface( CLTNCHARSTATUS_DLG ) == false )
			{
				adjustX += 40;
				bShow = true;
			}
		}
		break;
	case QUEST_CLEAR_COND_FULLLIFE:
		{
			if( pclclient->IsOpenInterface( NNEWINVENTORY_DLG ) == false  )
			{
				adjustX += 280;
				bShow = true;
			}
		}
		break;
	/*
	case QUEST_CLEAR_COND_OPENSKILL:
		{
            if( pclclient->IsOpenInterface( NSKILL_DLG ) == false )	
			{
				adjustX += 182;
				bShow = true;
			}
		}
		break;
	*/
	case QUEST_CLEAR_COND_ITEMINFODLG:
		{
			if( pclclient->IsOpenInterface( NINFO_DLG) == false )
			{
				adjustX += 370;
				bShow = true;
			}
		}
		break;
	}

	if ( bShow == false ) 
		return;

	if( GP.LockSurface(lpSurface) == TRUE )
	{			
		TSpr* pSpr = pclclient->GetGlobalSpr(GIMG_CLICKMOUSE);

		if(pSpr)
		{
			SI16 dlgPosX = pclclient->m_pDialog[NCHARMENUBAR_DLG]->GetX() + pclclient->GetScreenRX();
			SI16 dlgPosY = pclclient->m_pDialog[NCHARMENUBAR_DLG]->GetY() + pclclient->GetScreenRY();
			SI32 font = 0;

			font = font + (pclClient->CurrentClock / 200)  % 2; 
			if( g_SoundOnOffDlg.m_bBigDisplayMode )
			{
				if(dlgPosY > 350)    
					GP.PutSpr(pSpr, dlgPosX + adjustX, dlgPosY - 91, font);
				else
					GP.PutSpr(pSpr, dlgPosX + adjustX, dlgPosY + 25, font+2);
			}
		}
		GP.UnlockSurface(lpSurface);
	}
}
void cltQuestManager::DrawDirectionArrow( SI32 drawX, SI32 drawY )
{
	cltClient* pclclient = (cltClient*)pclClient;

	if ( siCurrentQuestStep != QUEST_STEP_MIDDLE )
		return;

	cltCharClient* pclchar = (cltCharClient*)pclclient->pclCM->CR[1];


	SI32 siCurrentQuestCommand	= pclchar->pclCI->clQuestInfo.clUnit[siQuestType].siQuestCmd;

	
	SI32 charXpos = pclchar->GetX();
	SI32 charYpos = pclchar->GetY();

	switch( siCurrentQuestCommand )
	{
	case QUEST_CLEAR_COND_KILLMON:
		{

			if ( pclClient->GetUniqueFromHash("KIND_RACCOON") 
				== pclchar->pclCI->clQuestInfo.clUnit[siQuestType].siQuestPara1 )
			{ 
				if ( MAPINDEX_PALACE == pclchar->GetMapIndex() )
				{
					cltGate clGate;
					pclClient->pclMapManager->pclGateManager->FindGate( MAPINDEX_PALACE, MAPINDEX_MAINFIELD, &clGate);

					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, clGate.SrcX-2, clGate.SrcY-2 ) );
				}
			}
		}
		break;
	case QUEST_CLEAR_COND_LEVEL:
		{
			if ( MAPINDEX_MAINFIELD == pclchar->GetMapIndex() )
			{
				cltGate clGate;
				pclClient->pclMapManager->pclGateManager->FindGate( MAPINDEX_MAINFIELD, MAPINDEX_BEGINNER1, &clGate);

				DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, clGate.SrcX, clGate.SrcY ) );
			}
		}
		break;
	case QUEST_CLEAR_COND_SELLNPC:
		{
			if ( MAPINDEX_PALACE == pclchar->GetMapIndex() || pclchar->GetCurrentVillageUnique() )
			{
				cltSystemNPC clSystemNpc;

				SI32 id = pclClient->pclCM->GetIDFromCharKind( pclchar->pclCI->clQuestInfo.clUnit[siQuestType].siQuestPara1 );
				if ( id )
				{
					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, pclClient->pclCM->CR[id]->GetX(), pclClient->pclCM->CR[id]->GetY() ) );

				}
			}
		}
		break;
	case QUEST_CLEAR_COND_SELLSWORDNPC:
		{
			if ( MAPINDEX_PALACE == pclchar->GetMapIndex() || 
				pclchar->GetCurrentVillageUnique() )
			{
				cltSystemNPC clSystemNpc;

				SI32 id = pclClient->pclCM->GetIDFromCharKind( pclClient->GetUniqueFromHash("KIND_CHINAMERCHANT") );
				if ( id )
				{
					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, pclClient->pclCM->CR[id]->GetX(), pclClient->pclCM->CR[id]->GetY() ) );

				}
			}
		}
		break;
	case QUEST_CLEAR_COND_LAMPGOMAP:		// ������� ���� ��ȸ
	case QUEST_CLEAR_COND_GOMAP:
		{
			if ( MAPINDEX_MAINFIELD == pclchar->GetMapIndex() )
			{
				// Para1���� MapIndex��ȣ��
				SI32 siMapIndex = pclchar->pclCI->clQuestInfo.clUnit[siQuestType].siQuestPara1;
				SI32 siParentMap = pclClient->pclMapManager->GetParentMap( siMapIndex );
			
				SI32 siXPos = 0;
				SI32 siYPos = 0;
				
				// siParentMap ���� 0�϶��� ���� �������� ��ǥ�� ���ؿ´�
				if ( siParentMap == 0)
				{
					SI32 siVillageUnique = pclClient->pclMapManager->clUnitMapInfo[ siMapIndex ].siVillageUnique;
					
					
					if ( (siVillageUnique > 0) && (pclClient->pclVillageManager->pclVillageInfo[ siVillageUnique ] != NULL) )
					{
						siXPos = pclClient->pclVillageManager->pclVillageInfo[ siVillageUnique ]->PosX;
						siYPos = pclClient->pclVillageManager->pclVillageInfo[ siVillageUnique ]->PosY;
					}
				}
				// ParentMap�� �������� ������ ��ġ�� �޾ƿ´�.
				else if (  siParentMap > 0 )
				{
					pclClient->pclMapManager->pclGateManager->FindMainFieldPos(siParentMap, &siXPos, &siYPos);
				}

				if ( siXPos>0 && siYPos>0 )
				{
					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, siXPos, siYPos) );
				}
			}
			//KHY - 0628 - ��������Ʈ���� ȭ��ǥ �߰�.
			else	 if ( MAPINDEX_PALACE == pclchar->GetMapIndex() )
			{
				cltGate clGate;
				pclClient->pclMapManager->pclGateManager->FindGate( MAPINDEX_PALACE, MAPINDEX_MAINFIELD, &clGate);

				DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, clGate.SrcX-2, clGate.SrcY-2 ) );
			}
		}
		break;
	case QUEST_CLEAR_COND_BANK:
		{
			if ( MAPINDEX_MAINFIELD == pclchar->GetMapIndex() )
			{
				SI32 xPos = pclClient->pclVillageManager->pclVillageInfo[1]->PosX;
				SI32 yPos = pclClient->pclVillageManager->pclVillageInfo[1]->PosY;

				DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, xPos, yPos) );
			}
			else if ( pclchar->GetCurrentVillageUnique()  )
			{
				SI32 xPos = 0;
				SI32 yPos = 0;

				SI32 strUnique = pclClient->pclVillageStructureSet->GetStrUniqueFromRankType( RANKTYPE_BANK );
				if ( pclClient->pclVillageManager->GetPosFromStrUnique( pclchar->GetCurrentVillageUnique(), strUnique,  &xPos, &yPos ) )
				{
					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, xPos+3, yPos+3) );
				}
			}
		}
		break;
	case QUEST_CLEAR_COND_STRUCTUREOPEN:
		{
			if ( MAPINDEX_MAINFIELD == pclchar->GetMapIndex() )
			{
				SI32 xPos = pclClient->pclVillageManager->pclVillageInfo[1]->PosX;
				SI32 yPos = pclClient->pclVillageManager->pclVillageInfo[1]->PosY;

				DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, xPos, yPos) );
			}
			else if ( pclchar->GetCurrentVillageUnique() )
			{
				SI32 xPos = 0;
				SI32 yPos = 0;

				SI32 strUnique = pclClient->pclVillageStructureSet->GetStrUniqueFromRankType( RANKTYPE_MARKET );
				if ( pclClient->pclVillageManager->GetPosFromStrUnique( pclchar->GetCurrentVillageUnique(), strUnique,  &xPos, &yPos ) )
				{
					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, xPos+3, yPos+3) );
				}
			}
		}
		break;
	case QUEST_CLEAR_COND_SENDITEMBYPOST:
		{
			if ( MAPINDEX_MAINFIELD == pclchar->GetMapIndex() )
			{
				SI32 xPos = pclClient->pclVillageManager->pclVillageInfo[1]->PosX;
				SI32 yPos = pclClient->pclVillageManager->pclVillageInfo[1]->PosY;

				DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, xPos, yPos) );
			}
			else if ( pclchar->GetCurrentVillageUnique() )
			{
				SI32 xPos = 0;
				SI32 yPos = 0;

				SI32 strUnique = pclClient->pclVillageStructureSet->GetStrUniqueFromRankType( RANKTYPE_POSTOFFICE );
				if ( pclClient->pclVillageManager->GetPosFromStrUnique( pclchar->GetCurrentVillageUnique(), strUnique,  &xPos, &yPos ) )
				{
					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, xPos+3, yPos+3) );
				}
			}
		}
		break;
	case QUEST_CLEAR_COND_GETQUEST:
		{
			if ( MAPINDEX_PALACE == pclchar->GetMapIndex() )
			{
				cltSystemNPC clSystemNpc;

				SI32 id = pclClient->pclCM->GetIDFromCharKind( pclchar->pclCI->clQuestInfo.clUnit[siQuestType].siQuestPara1 );
				if ( id )
				{
					DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, pclClient->pclCM->CR[id]->GetX(), pclClient->pclCM->CR[id]->GetY() ) );
				}
			}
		}
	//case QUEST_CLEAR_COND_GONPC:
	//	{
	//		if ( MAPINDEX_MAINFIELD == pclchar->GetMapIndex() )
	//		{
	//			cltSystemNPC clSystemNpc;

	//			SI32 id = pclClient->pclCM->GetIDFromCharKind( pclchar->pclCI->clQuestInfo.clUnit[siQuestType].siQuestPara1 );
	//			if ( id )
	//			{
	//				DrawDirectionArrow( drawX, drawY, DecideDirection8( charXpos, charYpos, pclClient->pclCM->CR[id]->GetX(), pclClient->pclCM->CR[id]->GetY() ) );

	//			}
	//		}
	//	}
	//	break;
	}
}
void cltQuestManager::DrawDirectionArrow( SI32 drawX, SI32 drawY, SI32 direction )
{
	TSpr* pSpr = pclClient->GetGlobalSpr(GIMG_QUESTARROW);

	static clock_t lastFontChangedClock = 0;
	static SI32	siAnistep = 0;

	if ( TABS(pclClient->CurrentClock - lastFontChangedClock ) > 300 ) 
	{
		if ( siAnistep )
		{
			siAnistep = 0;
		}
		else
		{
			siAnistep = 1;
		}
		lastFontChangedClock = pclClient->CurrentClock;
	}

	if ( pSpr )
	{
		SI32 font = 0;
		switch( direction )
		{
		case NORTH:
			font = 10; 
			break;			
		case NORTH|EAST:
			font = 12; 
			break;
		case EAST:
			font = 14; 
			break;
		case EAST|SOUTH:
			font = 0; 
			break;
		case SOUTH:			
			font = 2; 
			break;
		case SOUTH|WEST:	
			font = 4; 
			break;
		case WEST:			
			font = 6; 
			break;
		case WEST|NORTH:	
			font = 8; 
			break;
		}
		drawY -= 160;
		drawX -= 35;

		GP.PutSprScreen( pSpr, drawX, drawY, font + siAnistep);
	}
}

void cltQuestManager::ShowSelectItemDlg( cltQuestRewardInfo* pclinfo, SI16 questtype, SI16 questunique)
{
	cltClient* pclclient = (cltClient*)pclClient;

	pclclient->CreateInterface( NQUESTSELECTITEM_DLG );

	CNQuestSelectItemDlg* pDialog = (CNQuestSelectItemDlg*)pclclient->m_pDialog[ NQUESTSELECTITEM_DLG ];
	if ( pDialog )
	{
		pDialog->SetItemList( pclinfo, questtype, questunique );
	}
}

SI16 cltQuestManager::ConvertQuestTypeTextToNum( TCHAR* pszQuestType )
{
	if ( NULL == pszQuestType )
	{
		return QUEST_TYPE_NONE;
	}

	if     ( _tcscmp(pszQuestType, "QUEST_TYPE_NONE")				== 0 )	return QUEST_TYPE_NONE;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_SPECIAL")			== 0 )	return QUEST_TYPE_SPECIAL;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_BATTLE1")			== 0 )	return QUEST_TYPE_BATTLE1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEHEAL1")			== 0 )	return QUEST_TYPE_MAKEHEAL1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKESWORD1")			== 0 )	return QUEST_TYPE_MAKESWORD1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEBOW1")			== 0 )	return QUEST_TYPE_MAKEBOW1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEHELMET1")		== 0 )	return QUEST_TYPE_MAKEHELMET1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_BEGINNER3")			== 0 )	return QUEST_TYPE_BEGINNER3;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKESPEAR1")			== 0 )	return QUEST_TYPE_MAKESPEAR1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEARMOUR1")		== 0 )	return QUEST_TYPE_MAKEARMOUR1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEAX1")			== 0 )	return QUEST_TYPE_MAKEAX1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEGUN1")			== 0 )	return QUEST_TYPE_MAKEGUN1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKESTAFF1")			== 0 )	return QUEST_TYPE_MAKESTAFF1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEBELT1")			== 0 )	return QUEST_TYPE_MAKEBELT1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKESHOES1")			== 0 )	return QUEST_TYPE_MAKESHOES1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_BEGINNER2")			== 0 )	return QUEST_TYPE_BEGINNER2;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_BATTLE2")			== 0 )	return QUEST_TYPE_BATTLE2;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_BASIC1")				== 0 )	return QUEST_TYPE_BASIC1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_BEGINNER4")			== 0 )	return QUEST_TYPE_BEGINNER4;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEBEGINNER1")		== 0 )	return QUEST_TYPE_MAKEBEGINNER1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGETC01")		== 0 )	return QUEST_TYPE_HUNTINGETC01;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_NAMING")				== 0 )	return QUEST_TYPE_NAMING;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HAPPYBEAN")			== 0 )	return QUEST_TYPE_HAPPYBEAN;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND01")	== 0 )	return QUEST_TYPE_HUNTINGGROUND01;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND02")	== 0 )	return QUEST_TYPE_HUNTINGGROUND02;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKESANTAHAT")		== 0 )	return QUEST_TYPE_MAKESANTAHAT;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKECAKE")			== 0 )	return QUEST_TYPE_MAKECAKE;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_PLAYCHRISTMAS")		== 0 )	return QUEST_TYPE_PLAYCHRISTMAS;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND03")	== 0 )	return QUEST_TYPE_HUNTINGGROUND03;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND04")	== 0 )	return QUEST_TYPE_HUNTINGGROUND04;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND05")	== 0 )	return QUEST_TYPE_HUNTINGGROUND05;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND06")	== 0 )	return QUEST_TYPE_HUNTINGGROUND06;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND07")	== 0 )	return QUEST_TYPE_HUNTINGGROUND07;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND08")	== 0 )	return QUEST_TYPE_HUNTINGGROUND08;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND09")	== 0 )	return QUEST_TYPE_HUNTINGGROUND09;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND10")	== 0 )	return QUEST_TYPE_HUNTINGGROUND10;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND11")	== 0 )	return QUEST_TYPE_HUNTINGGROUND11;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEFOOD1")			== 0 )	return QUEST_TYPE_MAKEFOOD1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_BEGINNER1")			== 0 )	return QUEST_TYPE_BEGINNER1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_DAILYQUEST2")		== 0 )	return QUEST_TYPE_DAILYQUEST2;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_DAILYQUEST3")		== 0 )	return QUEST_TYPE_DAILYQUEST3;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MAKEARTIFACT1")		== 0 )	return QUEST_TYPE_MAKEARTIFACT1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_MISSION1")			== 0 )	return QUEST_TYPE_MISSION1;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND12")	== 0 )	return QUEST_TYPE_HUNTINGGROUND12;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND13")	== 0 )	return QUEST_TYPE_HUNTINGGROUND13;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_FINDTREASURE")		== 0 )	return QUEST_TYPE_FINDTREASURE;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND14")	== 0 )	return QUEST_TYPE_HUNTINGGROUND14;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_AVATAR_DRESS")	== 0 )		return QUEST_TYPE_AVATAR_DRESS;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_AVATAR_HAT")	== 0 )			return QUEST_TYPE_AVATAR_HAT;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_AVATAR_MENTAL")	== 0 )		return QUEST_TYPE_AVATAR_MENTAL;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_AVATAR_RING")	== 0 )		return QUEST_TYPE_AVATAR_RING;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_AVATAR_NECK")	== 0 )		return QUEST_TYPE_AVATAR_NECK;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_PLAYCHRISTMASHIDDEN")== 0 )	return QUEST_TYPE_PLAYCHRISTMASHIDDEN;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_HUNTINGGROUND15")	== 0 )	return QUEST_TYPE_HUNTINGGROUND15;
	/*else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_100")		== 0 )	return QUEST_TYPE_LEVELUP_100;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_101")		== 0 )	return QUEST_TYPE_LEVELUP_101;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_102")		== 0 )	return QUEST_TYPE_LEVELUP_102;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_103")		== 0 )	return QUEST_TYPE_LEVELUP_103;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_104")		== 0 )	return QUEST_TYPE_LEVELUP_104;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_105")		== 0 )	return QUEST_TYPE_LEVELUP_105;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_106")		== 0 )	return QUEST_TYPE_LEVELUP_106;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_107")		== 0 )	return QUEST_TYPE_LEVELUP_107;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_108")		== 0 )	return QUEST_TYPE_LEVELUP_108;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_109")		== 0 )	return QUEST_TYPE_LEVELUP_109;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_110")		== 0 )	return QUEST_TYPE_LEVELUP_110;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_111")		== 0 )	return QUEST_TYPE_LEVELUP_111;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_112")		== 0 )	return QUEST_TYPE_LEVELUP_112;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_113")		== 0 )	return QUEST_TYPE_LEVELUP_113;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_114")		== 0 )	return QUEST_TYPE_LEVELUP_114;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_115")		== 0 )	return QUEST_TYPE_LEVELUP_115;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_116")		== 0 )	return QUEST_TYPE_LEVELUP_116;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_117")		== 0 )	return QUEST_TYPE_LEVELUP_117;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_118")		== 0 )	return QUEST_TYPE_LEVELUP_118;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_119")		== 0 )	return QUEST_TYPE_LEVELUP_119;
	else if( _tcscmp(pszQuestType, "QUEST_TYPE_LEVELUP_120")		== 0 )	return QUEST_TYPE_LEVELUP_120;*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ο� Ÿ���� �� ���� �߰��� �ּ���
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	else 
	{
		NTCHARString256 strText( pszQuestType );
		NTCHARString64	strCaption( TEXT(" ����Ʈ Ÿ�Լ��� ���� ") );

		strText += _T(" Ÿ���� �������� �ʴ� Ÿ�� �Դϴ�");

		MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
	}
#endif


	return QUEST_TYPE_NONE;
}