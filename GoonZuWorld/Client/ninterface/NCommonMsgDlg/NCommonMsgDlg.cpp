#include "./NCommonMsgDlg.h"

#include <Client.h>

#include "../../common/char/CharManager/CharManager.h"

#include "MsgType-Person.h"
#include "Msg/MsgType-PersonalShop.h"
#include "Msg/MsgType-MofuMofuEvent.h"
#include "Msg/MsgType-Empire.h"
#include "Msg/MsgType-HappyBeanQuest.h"
#include "MsgType-Guild.h"

#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/Edit.h"

#include "../ndailyquestdlg/NDailyQuestSelectDlg.h"
#include "../NDailyQuest2/NDailyQuest2SelectDlg.h"
#include "../NDailyQuest3/NDailyQuest3SelectDlg.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"

#include "../CommonLogic/Msg/MsgType-ItemMall.h"
#include "../CommonLogic/msg/MsgType-Quest.h"

#include "../../Interface/LoginNoticeDlg/LoginNoticeDlg.h"

#include "../CommonLogic/Msg/MsgType-RacoonDodgeEvent.h"
#include "../Client/Client_BokBulBokMgr/Client_BBBMgr.h"







extern cltCommonLogic* pclClient;
extern DWORD dwQuitTimer;

CNCommonMsgDlg::CNCommonMsgDlg()
{
	m_pEdit = NULL;
	m_pOKButton = NULL;
	m_pCancelButton = NULL;

	siExitCount = 0;
	siPupilPersonID = 0;
	szPupilName[0] = '\0';

	siInviteType = 0;
	siEmpireUnique = 0;
	siFromPersonID = 0;
	siEmproerVillageUnique = 0;

	m_dwStartTime	= 0;
	m_dwShowTimeMS	= 0;
}

CNCommonMsgDlg::~CNCommonMsgDlg()
{
	NDelete( m_pEdit );
	NDelete( m_pOKButton );
	NDelete( m_pCancelButton );
}

void CNCommonMsgDlg::Create()
{
	if ( ! IsCreate() )
	{
		m_pEdit = new CEdit( this );
		m_pOKButton = new CButton( this );
		m_pCancelButton = new CButton( this );

		CDialogController::Create( NCOMMONMSG_DLG, CONTROLLER_KIND_POPUPDIALOG, NULL, StaticCallBackDialogNCommonMsgDlg, NULL, TEXT("NInterface/Interface/Interface_20x20_00_109.Spr"), 9, true, 9, 430, 340, 280, 120, true, false, true );

		m_pEdit->Create( NMSGBOX_DIALOG_EDIT, NULL, TEXT("NInterface/Common/COMMON_16X15_00_109.SPR"), 0, true, 9, 9, 21, 260, 60, 260, 60, true  );
		m_pOKButton->Create( NMSGBOX_DIALOG_BUTTONOK, TEXT("OK"), TEXT("Ninterface/Button/Buttona_4x24_00_103.spr"), 0, true, 3, 50, 86, 72, 24, 72, 24 );
		m_pCancelButton->Create( NMSGBOX_DIALOG_BUTTONCANCEL, TEXT("CANCEL"), TEXT("Ninterface/Button/Buttona_4x24_00_103.spr"), 0, true, 3, 50, 86, 72, 24, 72, 24 );
	    
#ifndef _NEW_INTERFACE_
		m_pOKButton->SetAniType(TRUE);
		m_pCancelButton->SetAniType(TRUE);
#else
		
#endif

		SetTopMostWindow( true );
		SetModalDialog( true );
		SetActionTimer(100);
		SetTimerOnOff( true );

	}
}

void CALLBACK CNCommonMsgDlg::StaticCallBackDialogNCommonMsgDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNCommonMsgDlg *pThis = (CNCommonMsgDlg *)pControllerMgr;
	pThis->CallBackDialogNCommonMsgDlg( nEvent, nControlID, pControl );
}

void CALLBACK CNCommonMsgDlg::CallBackDialogNCommonMsgDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient *)pclClient;

	switch ( nEvent )
	{
	case EVENT_BUTTON_CLICKED:
		{
			switch (nControlID)
			{
			case COMMON_DIALOG_CLOSEBUTTON:
				{
					if( siCommonDlg_mode == COMMONDLG_REQUEST_SETFATHER )
					{
						cltGameMsgRequest_SetFather clinfo( siPupilPersonID, 1, 2);
						cltMsg clMsg(GAMEMSG_REQUEST_SETFATHER, sizeof(clinfo), (BYTE*)&clinfo);
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

						DeleteDialog();
					}
					else if(siCommonDlg_mode == COMMONDLG_HALLOWEENMISSION_START)
					{
						cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
						if(pclchar)
						{
							cltGameMsgRequest_MissionQuest_Cancel pclInfo( pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique );
							cltMsg clMsg( GAMEMSG_REQUEST_MISSIONQUEST_CANCEL, sizeof( pclInfo ), (BYTE*)&pclInfo );
							pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

							pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
						}
						DeleteDialog();
					}
					else if (siCommonDlg_mode != COMMONDLG_EXITCOUNT)
						DeleteDialog();
					// 2007.05.15�� �߰� - ����� : X�� ������ ������ ����ǰԼ���.
					/*else if (siCommonDlg_mode == COMMONDLG_EXITCOUNT)
						LogOut();*/
					// ���� �׳� â�� �ݱ�� ������ �ʵ��� �Ѵ�.
					else
					{
						DeleteDialog();
					}
				}
				break;
			case NMSGBOX_DIALOG_BUTTONOK :
				{
					switch (siCommonDlg_mode)
					{
					case COMMONDLG_NONE :
						{
							DeleteDialog();
						}
						// [����] : 2010�ų��̺�Ʈ - ���� ����Ʈ �˸� ��ȭ������ �����ϱ� ��ư Ŭ��������
					case COMMONDLG_2010NEWYEARFORTUNE_QUEST:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								// �̼� ����Ʈ�� �ϰڴٰ� �޾� �鿴��.
								cltGameMsgRequest_MissionQuest_Accept pclInfo( MISSIONQUEST_UNIQUE_REMOVE_UNLUCK );
								cltMsg clMsg( GAMEMSG_REQUEST_MISSIONQUEST_ACCEPT, sizeof( pclInfo ), (BYTE*)&pclInfo );
								pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
							}

							// ������ �̹� ���� ��ϵǾ� �ִ� ���´ϱ� ��ȭ���ڸ� �ݾ��ش�.
							DeleteDialog();
						}
						break;
					case COMMONDLG_REVIVE :	
						{
							if (pclclient->bReviveRequestSwitch)
							{
								SI32 charid = ((cltClient *)pclClient)->MyCharUnique;

								cltGameMsgRequest_Revive clinfo(charid, 1,NORMAL);

								cltMsg clMsg(GAMEMSG_REQUEST_REVIVE, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

								pclclient->bReviveRequestSwitch = false;

								DeleteDialog();
							}
						}
						break;
					case COMMONDLG_RELOGIN :
						{
							cltClient* pclclient = (cltClient*)pclClient;

							pclclient->pGameSession->CloseSocket();

							pclclient->pFrontSession->CloseSocket() ;

							pclclient->bReceiveMyCharAllInfoSwitch	= false;
							pclclient->bBackUpSwitch				= false;

							pclclient->siAuthKey		= 0;
							pclclient->bFrontServerActionSwitch	= true;
							pclclient->bGameServerActionSwitch		= false;

							pclclient->bFrontServerSecretKeySwitch	= false;
							pclclient->bGameServerSecretKeySwitch	= false;

							Sleep(1000);

							pclclient->SetGameStatus(GS_INITCONNECTFRONTSERVER);

							DeleteDialog();
						}
						break;
					case COMMONDLG_EXITCOUNT :
						{
							SetTopMostWindow(FALSE);
							LogOut();
						}
						break;
					case COMMONDLG_CLOSE_PREMIUMSHOP :
						{


							cltGameMsgRequest_StopPersonalShop clshopdata( pclClient->pclCM->CR[1]->GetCharUnique());
							cltMsg clMsg( GAMEMSG_REQUEST_STOPPERSONALSHOP, sizeof( clshopdata ), (BYTE*)&clshopdata );
							cltClient *pclclient = ( cltClient * )pclClient;
							pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

							if(pclclient->m_pDialog[ NPERSONALSHOP_DLG ])			
								pclclient->m_pDialog[ NPERSONALSHOP_DLG ]->DeleteDialog();

							((cltCharClient*)pclclient->pclCM->CR[1])->clMyShopData.Init();
							((cltCharClient*)pclclient->pclCM->CR[1])->bMyShopStart = FALSE;

							DeleteDialog();
						}
						break;
					case COMMONDLG_RESURRECTION :
					case COMMONDLG_INSURANCE_POLICY:
						{
							if (pclclient->bReviveRequestSwitch)
							{
								SI32 charid = ((cltClient *)pclClient)->MyCharUnique;

								cltGameMsgRequest_Resurrection clinfo(charid, 1,NORMAL);

								cltMsg clMsg(GAMEMSG_REQUEST_RESURRECTION, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

								pclclient->bReviveRequestSwitch = false;

								DeleteDialog();
							}
						}
						break;
					case COMMONDLG_RESURRECTION_PVP:
						{
							SI32 charid = ((cltClient *)pclClient)->MyCharUnique;
							cltGameMsgRequest_Resurrection clinfo(charid, 1,PVP_DIE);
							cltMsg clMsg(GAMEMSG_REQUEST_RESURRECTION, sizeof(clinfo), (BYTE*)&clinfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							DeleteDialog();
						}
						break;
					case COMMONDLG_INITLEVEL :
						{
							if(pclclient->pclCM->CR[1]->pclCI->clIP.GetLevel() == INIT_LEVEL) 
							{
								cltGameMsgRequest_InitStatus clInit(INITSTATUSMODE_LEVEL_10);
								cltMsg clMsg(GAMEMSG_REQUEST_INITSTATUS, sizeof(clInit), (BYTE*)&clInit);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							else if(pclclient->pclCM->CR[1]->pclCI->clIP.GetLevel() == INIT_LEVEL_SECOND)
							{
								cltGameMsgRequest_InitStatus clInit(INITSTATUSMODE_LEVEL_30);
								cltMsg clMsg(GAMEMSG_REQUEST_INITSTATUS, sizeof(clInit), (BYTE*)&clInit);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}

							TCHAR *pTitle = GetTxtFromMgr(6990);
							TCHAR *pText = GetTxtFromMgr(6992);

							stMsgBox MsgBox;
							MsgBox.Set( this,  pTitle, pText, MSGBOX_TYPE_OK, 0 );
							pclclient->SetMsgBox( &MsgBox, NULL, 0 );

							DeleteDialog();
						}
						break;
					case COMMONDLG_MOFUMOFU_ENTER_FIELD1:
					case COMMONDLG_MOFUMOFU_ENTER_FIELD2:
					case COMMONDLG_MOFUMOFU_ENTER_FIELD3:
						{
							SI32 siFieldIndex = siCommonDlg_mode - COMMONDLG_MOFUMOFU_ENTER_FIELD1;
							cltGameMsgResquest_MofuMofuEvent_EnterField	clInfo(siFieldIndex, 1);
							cltMsg clMsg(GAMEMSG_REQUEST_MOFUMOFUEVENT_ENTERFIELD, sizeof(clInfo), (BYTE*)&clInfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

							DeleteDialog();
						}
						break;						

					case COMMONDLG_MOFUMOFU_LEAVE_FIELD1:
					case COMMONDLG_MOFUMOFU_LEAVE_FIELD2:
					case COMMONDLG_MOFUMOFU_LEAVE_FIELD3:
						{
							SI32 siFieldIndex = siCommonDlg_mode - COMMONDLG_MOFUMOFU_LEAVE_FIELD1;
							cltGameMsgResquest_MofuMofuEvent_EnterField	clInfo(siFieldIndex, 0);
							cltMsg clMsg(GAMEMSG_REQUEST_MOFUMOFUEVENT_ENTERFIELD, sizeof(clInfo), (BYTE*)&clInfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

							DeleteDialog();
						}
						break;
					case COMMONDLG_MOFUMOFU_AUTO_WARP:
						{
							GMONEY Money = pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();
							if(Money < 1000)
							{
								TCHAR* pTitle = GetTxtFromMgr(5614);
								TCHAR* pText  = GetTxtFromMgr(1178);

								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
								return;
							}
							cltGameMsgResquest_MofuMofuEvent_Warp clInfo;
							cltMsg clMsg(GAMEMSG_REQUEST_MOFUMOFUEVENT_WARP, sizeof(clInfo), (BYTE*)&clInfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

							DeleteDialog();
						}
						break;
					case COMMONDLG_REQUEST_SETFATHER:
						{
							cltGameMsgRequest_SetFather clinfo( siPupilPersonID, 1, 1);
							cltMsg clMsg(GAMEMSG_REQUEST_SETFATHER, sizeof(clinfo), (BYTE*)&clinfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
                            
							DeleteDialog();
						}
						break;
					case COMMONDLG_DAILYQUEST_REWARD:
						{
							CNDailyQuestSelectDlg* m_pDialog = (CNDailyQuestSelectDlg*)pclclient->m_pDialog[NDAILYQUEST_DLG];
							if ( m_pDialog )
							{
								m_pDialog->SelectRewardMoney( FALSE );
							}
							DeleteDialog();
						}
						break;
					case COMMONDLG_DAILYQUEST2_REWARD:
						{
							CDailyQuest2SelectDlg* m_pDialog = (CDailyQuest2SelectDlg*)pclclient->m_pDialog[NDAILYQUEST2_DLG];
							if ( m_pDialog )
							{
								m_pDialog->SelectRewardMoney( FALSE );
							}
							DeleteDialog();
						}
						break;
					case COMMONDLG_DAILYQUEST3_REWARD:
						{
							CDailyQuest3SelectDlg* m_pDialog = (CDailyQuest3SelectDlg*)pclclient->m_pDialog[NDAILYQUEST3_DLG];
							if ( m_pDialog )
							{
								m_pDialog->SelectRewardMoney( FALSE );
							}
							DeleteDialog();
						}
						break;

					case COMMONDLG_CANNOTLOGIN_AGE:
						{
							DeleteDialog();
						}
						break;
					case COMMONDLG_CANNOTLOGIN_ERROR:
						{
							DeleteDialog();
						}
						break;
					//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.	
					case COMMONDLG_TICKETMONEY_WARP:
						{
							TCHAR* pText = NULL;
							TCHAR	buffer[256] = {0,};

							//�������� �����̵� ��뺸�� ������ �˻�.		
							GMONEY mymoney = pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();
							
							if(siWarpMoney > mymoney)
							{
								pText= GetTxtFromMgr(7540);
								StringCchPrintf(buffer, 256, pText);
								pText= GetTxtFromMgr(7538);
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, buffer );
								DeleteDialog();
								return;
							}
							else
							{
								//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.
								cltGameMsgRequest_HuntMapWarp pclInfo(szMapIndex ,siWarpMoney);
								cltMsg clMsg( GAMEMSG_REQUEST_HUNTMAPWARP, sizeof( pclInfo ), (BYTE*)&pclInfo );
								pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							
							DeleteDialog();
						}
						break;
					//KHY - 0906 - ���ӹ� �̺�Ʈ ����. - ���������� ���� ������ ���� �κ�.
					case COMMONDLG_EVENTCOUPON:
						{
							TCHAR* pText = NULL;
							TCHAR	buffer[256] = {0,};

							TCHAR FullURL[1024] = {'\0', };
#ifdef USE_HANAUTH
							if(pclclient->m_siHanAuth_ServiceTypeCode == SERVICE_ALPHA)
							{
								StringCchPrintf(FullURL,1024,
									"http://alpha-gzs.hangame.com/event/freecoupon.nhn?m=freecoupon");
								ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
							}
							else
							{
								StringCchPrintf(FullURL,1024,
									"http://gzs.hangame.com/event/freecoupon.nhn?m=freecoupon");
								ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
							}
#endif // USE_HANAUTH
							DeleteDialog();
						}
						break;
					//KHY - 1024 - �Ѱ��� VIP �̺�Ʈ
					case COMMONDLG_HANGAME_VIP_EVENT:
						{
							TCHAR* pText = NULL;
							TCHAR	buffer[256] = {0,};

							TCHAR FullURL[1024] = {'\0', };
#ifdef USE_HANAUTH //�����ؾ���.
							if(pclclient->m_siHanAuth_ServiceTypeCode == SERVICE_ALPHA)
							{
								StringCchPrintf(FullURL,1024,
									"http://alpha-eventpark.hangame.com/event/publish/vipevent.nhn");
								ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
							}
							else
							{
								StringCchPrintf(FullURL,1024,
									"http://eventpark.hangame.com/event/publish/vipevent.nhn");
								ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
							}
#endif // USE_HANAUTH
							DeleteDialog();
						}
						break;						
					//KHY - 1024 - �Ѱ��� VIP �̺�Ʈ
					case COMMONDLG_HANGAME_VIP_EVENT_ITEM:
						{
							DeleteDialog();
						}
						break;
					//KHY - 1025 - ������ �̺�Ʈ
					case COMMONDLG_NOWCOM_EVENT_COUPON:
					case COMMONDLG_NOWCOM_EVENT_10LEVEL:
					case COMMONDLG_NOWCOM_EVENT_HAVEFATHER:						
						{
							DeleteDialog();
						}
						break;
					case COMMONDLG_AUCTIONEVENTCOUPON:
						{
							DeleteDialog();
						}
						break;
					case COMMONDLG_GOSTOPPOCKERCOMPLETE:
						{
							TCHAR* pText = NULL;
							TCHAR	buffer[256] = {0,};

							TCHAR FullURL[1024] = {'\0', };
#ifdef USE_HANAUTH
							if(pclclient->m_siHanAuth_ServiceTypeCode)
							{
								if (pclclient->m_siGoStopPockerEventType == 1)	// ���Ŀ� ��Ŀ�̺�Ʈ ������
								{
									StringCchPrintf(FullURL,1024,
										"http://alpha-eventpark.hangame.com/event/publish/gzsevent.nhn?m=poker");
									ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
								}
								else if (pclclient->m_siGoStopPockerEventType == 2)	//���Ŀ� �����̺�Ʈ ������
								{
									StringCchPrintf(FullURL,1024,
										"http://alpha-eventpark.hangame.com/event/publish/gzsevent.nhn?m=gostop");
									ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
								}
							}
							else
							{
								if (pclclient->m_siGoStopPockerEventType == 1)	// ����� ��Ŀ�̺�Ʈ ������
								{
									StringCchPrintf(FullURL,1024,
										"http://eventpark.hangame.com/event/publish/gzsevent.nhn?m=poker");
									ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
								}
								else if (pclclient->m_siGoStopPockerEventType == 2)	// ����� �����̺�Ʈ ������
								{
									StringCchPrintf(FullURL,1024,
										"http://eventpark.hangame.com/event/publish/gzsevent.nhn?m=gostop");
									ShellExecute(NULL,NULL,TEXT("IEXPLORE.EXE"),FullURL,NULL,SW_SHOWNORMAL);
								}
							}
#endif
							DeleteDialog();
						}
						break;
					case COMMONDLG_GOSTOPPOCKERSTART :
						{
							DeleteDialog();
						}
						break;

					case COMMONDLG_HALLOWEENMISSION_START:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								// �̼� ����Ʈ�� �ϰڴٰ� �޾� �鿴��.
								cltGameMsgRequest_MissionQuest_Accept pclInfo( pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique );
								cltMsg clMsg( GAMEMSG_REQUEST_MISSIONQUEST_ACCEPT, sizeof( pclInfo ), (BYTE*)&pclInfo );
								pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;
					case COMMONDLG_REQUEST_PVP:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameMsgRequest_PVP_Request clinfo ( READY_PVP ,siPVPRequestID);// ok �Ѵٸ� ������ ���� READY �޼����� ������.
								cltMsg clMsg(GAMEMSG_REQUEST_PVP_FILED, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

							}
							DeleteDialog();
						}
						break;
						// ������ �ڽ����� ��� 
					case COMMONDLG_REQUEST_FAMILY_ADD_CHILDREN:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameRequest_Add_Children clinfo ( m_siParentPersonID); //ok�Ѵٸ� �ڽ��� �ǰڴٴ� �޼����� ������.
								cltMsg clMsg(GAMEMSG_REQUEST_FAMILY_ADD_FAMILY, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;
						// ���� Ż��
					case COMMONDLG_REQUEST_FAMILY_DELL_CHILDREN:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameRequest_Del_Children clinfo ( m_siParentPersonID); //ok�Ѵٸ� �ڽ��� �ǰڴٴ� �޼����� ������.
								cltMsg clMsg(GAMEMSG_REQUEST_FAMILY_DEL_CHILDREN, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;
						// �������� ����
					case COMMONDLG_REQUEST_FAMILY_REMOVE_TARGET_CHILDREN:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameRequest_Del_Children clinfo ( m_siParentPersonID);
								cltMsg clMsg(GAMEMSG_REQUEST_FAMILY_DEL_CHILDREN, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;
						// ���� ȿ�� ���� 
					case COMMONDLG_REQUEST_FAMILY_PLUS_FAMILYEFFECTDATE:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameRequest_Plus_FamilyEffectDate clinfo ( m_siParentPersonID); //ok�Ѵٸ� �ڽ��� �ǰڴٴ� �޼����� ������.
								cltMsg clMsg(GAMEMSG_REQUEST_FAMILY_PLUS_FAMILYEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}break;
						// ���� ���ϱ� �̺�Ʈ �����Ҳ��Ĵ� ������ ���� �亯//Switch_10MonthEvent_RacoonDodge
					case COMMONDLG_REQUEST_RACOONDODGEEVENT_ANSWER:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameMsgReQuest_Request_PlayEvent clinfo ( pclchar->pclCI->GetPersonID()); //ok�Ѵٸ� �ڽ��� �ǰڴٴ� �޼����� ������.
								cltMsg clMsg(GAMEMSG_REQUEST_RACOONDODGE_EVENT_REQUEST_PLAYEVENT, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();

						}break;
					// ���Һ�- ����� ����Ʈ�� ����ϰڳĴ� ������ ���������� ó��.
					case COMMONDLG_BBB_WAIT_QUESTION:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameMsgRequest_BBB_WaitList_Answer clinfo( pclchar->pclCI->GetPersonID());
								cltMsg clMsg( GAMEMSG_REQUEST_BBB_WAITLIST_ANSWER, sizeof(clinfo), (BYTE*)&clinfo );
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;
					// ���Һ� - 1���� ����ڿ��� ���� "�����ҷ���?" ��ȭ���ڿ��� [��]�� Ŭ���������� ���� ó��.
					case COMMONDLG_BBB_WARPMAPQUESTION:
						{
							cltClient* pClient = (cltClient*)pclClient;
							cltCharClient* pCharClient = pClient->pclCM->GetCharClient( 1 );
							if ( NULL != pCharClient )
							{
								// ���� �ҷ��信 ���� ������� true�� ������ ����
								cltGameMsgRequest_BBB_WarpMapAnswer clinfo( pCharClient->pclCI->GetPersonID(), true );
								cltMsg clMsg( GAMEMSG_REQUEST_BBB_WARPMAPANSWER, sizeof(clinfo), (BYTE*)&clinfo );
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;
					case COMMONDLG_BBB_DELETE_WAITLIST:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltClient *pClient = (cltClient *)pclClient;
								if ( true == pClient->m_pClient_BBBMgr->IsReserved() )
								{
									cltGameMsgRequest_BBB_WaitList_Cancel clinfo( pclchar->pclCI->GetPersonID());
									cltMsg clMsg( GAMEMSG_REQUEST_BBB_WAITLIST_CANCEL, sizeof(clinfo), (BYTE*)&clinfo );
									pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
								}
							}
							DeleteDialog();
						}
						break;
					
					case COMMONDLG_REQUEST_TREASUREEVENT :	// ����ã�� ��ī�� ���� ���� �ޱ�.
							{
								cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
								if(pclchar)
								{
									if ( false == pclchar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_EVENT_FINDTREASURE ) )
									{
										// ��ī�� 
										SI32 siUseItem = ITEMUNIQUE( 2017 );
										if( pclchar->pclCI->clCharItem.GetItemNum( siUseItem ) >= 10)
										{
											SI32 charid = ((cltClient *)pclClient)->MyCharUnique;									
											cltGameMsgRequest_TreasureEvent_Use_Okara clinfo ( charid );// ok �Ѵٸ� ������ ���� READY �޼����� ������.
											cltMsg clMsg(GAMEMSG_REQUEST_TREASUREEVENT_USEOKARA, sizeof(clinfo), (BYTE*)&clinfo);
											pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

										}
										else
										{
											TCHAR *pTitle = GetTxtFromMgr(512);
											TCHAR *pText = GetTxtFromMgr(30056);

											stMsgBox MsgBox;
											MsgBox.Set( this,  pTitle, pText, MSGBOX_TYPE_OK, 0 );
											pclclient->SetMsgBox( &MsgBox, NULL, 0 );

										}
									}
									else
									{	// �̹� ������ �޾ҽ��ϴ�.
										TCHAR *pTitle = GetTxtFromMgr(512);
										TCHAR *pText = GetTxtFromMgr(30057);

										stMsgBox MsgBox;
										MsgBox.Set( this,  pTitle, pText, MSGBOX_TYPE_OK, 0 );
										pclclient->SetMsgBox( &MsgBox, NULL, 0 );

									}
									
								}
								DeleteDialog();

							}
							break;
					case COMMONDLG_REQUEST_GUILDHUNTMAPWAR_WARP://���� ����
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameMsgRequest_GuildHuntMapWarWar_Request clinfo ( REQUEST_WARP_HUNTMAPGUILDWAR_WARP_OK ,siGuildMapWar_PersonID);// ok �Ѵٸ� ������ ���� �޼����� ������.
								cltMsg clMsg(GAMEMSG_REQUEST_GUILDHUNTMAPWAR_REQUEST_WARP, sizeof(clinfo), (BYTE*)&clinfo);
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;
					}
				}
				break;
			case NMSGBOX_DIALOG_BUTTONCANCEL :
				{ 
					switch ( siCommonDlg_mode )
					{
					case COMMONDLG_RESURRECTION:
					case COMMONDLG_INSURANCE_POLICY://	��������
					case COMMONDLG_RESURRECTION_PVP:
						{
							Set(COMMONDLG_REVIVE);
						}
						break;
						// [����] : 2010�ų��̺�Ʈ - ���� ���� �˸� ��ȭ������ Ȯ�� ��ư Ŭ��������
					case COMMONDLG_2010NEWYEARFORTUNE_BUF:
						{
							DeleteDialog();
						}
						break;
						// [����] : 2010�ų��̺�Ʈ - ���� ����Ʈ �˸� ��ȭ������ ��� ��ư�� ��������
					case COMMONDLG_2010NEWYEARFORTUNE_QUEST:
						{
							// ������ '��'���� ����� ���� ����Ʈ ���� ��Ŷ ����
							/*
							cltClient* pClient = (cltClient*)pclClient;
							cltPersonQuestUnitInfo* pQuestInfo = &pClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1];

							// ����Ʈ Ÿ���� �̼��̰�
							if ( NULL != pQuestInfo )
							{
								// �̼��� Ÿ���� MISSIONQUEST_UNIQUE_REMOVE_UNLUCK �̸� ������ �̼� ���� �޼��� ����
								if ( MISSIONQUEST_UNIQUE_REMOVE_UNLUCK == pQuestInfo->siCurQuestUnique )
								{
									cltGameMsgRequest_CancelQuest clInfo( QUEST_TYPE_MISSION1 , MISSIONQUEST_UNIQUE_REMOVE_UNLUCK );
									cltMsg clMsg(GAMEMSG_REQUEST_CANCELQUEST, sizeof(clInfo), (BYTE*)&clInfo);
									pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
								}
							}*/
							
							DeleteDialog();
						}
						break;
					case COMMONDLG_REQUEST_SETFATHER:
						{
							cltGameMsgRequest_SetFather clinfo( siPupilPersonID, 1, 2);
							cltMsg clMsg(GAMEMSG_REQUEST_SETFATHER, sizeof(clinfo), (BYTE*)&clinfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

							DeleteDialog();
						}
						break;
					case COMMONDLG_DAILYQUEST_REWARD:
						{
							CNDailyQuestSelectDlg* m_pDialog = (CNDailyQuestSelectDlg*)pclclient->m_pDialog[NDAILYQUEST_DLG];

							if ( m_pDialog )
							{
								m_pDialog->SelectRewardMoney( TRUE );
							}
							DeleteDialog();
						}
						break;
					case COMMONDLG_DAILYQUEST2_REWARD:
						{
							CDailyQuest2SelectDlg* m_pDialog = (CDailyQuest2SelectDlg*)pclclient->m_pDialog[NDAILYQUEST2_DLG];

							if ( m_pDialog )
							{
								m_pDialog->SelectRewardMoney( TRUE );
							}
							DeleteDialog();
						}
						break;
					case COMMONDLG_DAILYQUEST3_REWARD:
						{
							CDailyQuest3SelectDlg* m_pDialog = (CDailyQuest3SelectDlg*)pclclient->m_pDialog[NDAILYQUEST3_DLG];

							if ( m_pDialog )
							{
								m_pDialog->SelectRewardMoney( TRUE );
							}
							DeleteDialog();
						}
						break;

					// [����] ���Һ� : 1���� ����ڰ� "���� �ҷ���?" ��ȭ���ڿ��� [�ƴϿ�]�� Ŭ�������� ó�� �۾�
					case COMMONDLG_BBB_WARPMAPQUESTION:
						{
							cltClient* pClient = (cltClient*)pclClient;
							cltCharClient* pCharClient = pClient->pclCM->GetCharClient( 1 );
							if ( NULL != pCharClient )
							{
								// ���� �ҷ��信 ���� ������� false�� ������ ����
								cltGameMsgRequest_BBB_WarpMapAnswer clinfo( pCharClient->pclCI->GetPersonID(), false );
								cltMsg clMsg( GAMEMSG_REQUEST_BBB_WARPMAPANSWER, sizeof(clinfo), (BYTE*)&clinfo );
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							DeleteDialog();
						}
						break;

					//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.	
					case COMMONDLG_TICKETMONEY_WARP:
						{
							TCHAR* pText = NULL;
							TCHAR	buffer[256] = {0,};

							SI32 itemunique = ITEMUNIQUE(24000);  // �����̵��̿��   14005 -> 24000
							cltClient* pclclient = (cltClient *)pclClient;

							if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
							{
								pText= GetTxtFromMgr(7539);
								StringCchPrintf(buffer, 256, pText);
								pText= GetTxtFromMgr(7538);
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, buffer );
								DeleteDialog();
								return;
							}
							else
							{
								cltGameMsgRequest_HuntMapWarp pclInfo(szMapIndex,0);
								cltMsg clMsg( GAMEMSG_REQUEST_HUNTMAPWARP, sizeof( pclInfo ), (BYTE*)&pclInfo );
								pclclient->SendMsgToServer((sPacketHeader*)&clMsg);					
							}

							DeleteDialog();
						}
						break;

					case COMMONDLG_INVITEEMPIRE:
						{
							cltGameMsgRequest_JoinEmpire pclInfo( siInviteType, siFromPersonID, siEmpireUnique );
							cltMsg clMsg( GAMEMSG_REQUEST_JOINEMPIRE, sizeof( pclInfo ), (BYTE*)&pclInfo );
							pclclient->SendMsgToServer((sPacketHeader*)&clMsg);				
						}
						break;

					case COMMONDLG_HALLOWEENMISSION_START:
						{
							cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
							if(pclchar)
							{
								cltGameMsgRequest_MissionQuest_Cancel pclInfo( pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique );
								cltMsg clMsg( GAMEMSG_REQUEST_MISSIONQUEST_CANCEL, sizeof( pclInfo ), (BYTE*)&pclInfo );
								pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

								pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
							}
							DeleteDialog();
						}
						break;

					default:
						DeleteDialog();
						break;
					}
				}
				break;
			}
		}
		break;
	}

	return;
}


void CNCommonMsgDlg::Set(SI32 CommonDlg_mode)
{
	m_dwStartTime	= 0;
	m_dwShowTimeMS	= 0;

	siCommonDlg_mode = CommonDlg_mode;

	TCHAR buf[256] = TEXT("");
	TCHAR* pTitle = NULL;
	TCHAR* pText = NULL;
	TCHAR* pButtonText;

	m_pOKButton->Show(FALSE);
	m_pCancelButton->Show(FALSE);

	switch (siCommonDlg_mode)
	{
	case COMMONDLG_REVIVE :	
		{
			pTitle = GetTxtFromMgr(2273);
			if( pclClient->pclMapManager->IsInstanceMap( pclClient->pclCM->CR[1]->GetMapIndex() ) == false)
				pText = GetTxtFromMgr(5722);
			else
				pText = GetTxtFromMgr(7828);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_RELOGIN :
		{
			pTitle = GetTxtFromMgr(836);
			pText = GetTxtFromMgr(5731);
			pButtonText = GetTxtFromMgr(3889);

			m_pOKButton->SetControllerPos(103, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

		}
		break;
	case COMMONDLG_EXITCOUNT :
		{
			// �α׾ƿ����� 20�� ���ҽ��ϴ�. �� ����
			siExitCount = LOGOUT_DELAYTIME;
			pText = GetTxtFromMgr(5743);
			StringCchPrintf(buf, 256, pText, siExitCount);
			pText = buf;

			pTitle = GetTxtFromMgr(3168);
			pButtonText = GetTxtFromMgr(5744);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			m_pOKButton->SetControllerPos(88, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			SetActionTimer(1000);
			SetTimerOnOff(TRUE);
		}
		break;
	
	case COMMONDLG_CLOSE_PREMIUMSHOP :
		{
			// �����Ϸ��� ���� ������ �����ؾ� �մϴ�. �Ͻðڽ��ϱ�?

			pTitle = GetTxtFromMgr(3420);
			pText = GetTxtFromMgr(6630);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

		}
		break;
	case COMMONDLG_RESURRECTION :
		{
			// ��Ȱ������ ����Ͽ� ���ڸ����� ��Ȱ �Ͻðڽ��ϱ�?

			pTitle = GetTxtFromMgr(2273);
			pText = GetTxtFromMgr(6707);
			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_INSURANCE_POLICY :
		{
			// ����ó�� �Ǿ����ϴ�. ���ڸ����� ��Ȱ �Ͻðڽ��ϱ�?

			pTitle = GetTxtFromMgr(2273);
			pText = GetTxtFromMgr(40810);
			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_RESURRECTION_PVP :
		{
			// ����Ͽ� ���ڸ����� ��Ȱ �Ͻðڽ��ϱ�?

			pTitle = GetTxtFromMgr(2273);
			pText = TEXT(" ���ڸ����� ��Ȱ �Ͻðڽ��ϱ�?");
			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_INITLEVEL :
		{
			// �ɷ� �ʱ�ȭ�� �����Ͻðڽ��ϱ�? �ɷ��� �ʱ�ȭ�Ǹ� �ɷ��� �ٽ� ������ �� �ֽ��ϴ�.

			pTitle = GetTxtFromMgr(6990);
			pText = GetTxtFromMgr(6991);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_MOFUMOFU_ENTER_FIELD1 :
	case COMMONDLG_MOFUMOFU_ENTER_FIELD2 :
	case COMMONDLG_MOFUMOFU_ENTER_FIELD3 :
		{
			SI32 siFieldIndex = CommonDlg_mode - COMMONDLG_MOFUMOFU_ENTER_FIELD1;
			
			pTitle = GetTxtFromMgr(4155);
			pText = GetTxtFromMgr(7064);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;

	case COMMONDLG_MOFUMOFU_LEAVE_FIELD1 :
	case COMMONDLG_MOFUMOFU_LEAVE_FIELD2 :
	case COMMONDLG_MOFUMOFU_LEAVE_FIELD3 :
		{
			SI32 siFieldIndex = CommonDlg_mode - COMMONDLG_MOFUMOFU_LEAVE_FIELD1;

			pTitle = GetTxtFromMgr(4155);
			pText = GetTxtFromMgr(7065);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;

	case COMMONDLG_MOFUMOFU_AUTO_WARP:
		{			
			pTitle = GetTxtFromMgr(3308);
			pText = "";

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_REQUEST_SETFATHER:
		{
			pTitle = GetTxtFromMgr(10032);
			pText = GetTxtFromMgr(10033);

			TCHAR tempBuf[256] = {'\0'};
			StringCchPrintf( tempBuf, 256, pText, szPupilName );

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(10022);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(10024);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(pTitle);
			m_pEdit->SetText( tempBuf );

			return;
		}
		break;
	case COMMONDLG_DAILYQUEST_REWARD:
		{
			pText = GetTxtFromMgr(10047);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(1928);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(10048);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(TEXT(""));
			m_pEdit->SetText( pText );

			return;
		}
		break;
	case COMMONDLG_DAILYQUEST2_REWARD:
		{
			pText = GetTxtFromMgr(10047);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 72, 24, 72, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(1928);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(10048);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(TEXT(""));
			m_pEdit->SetText( pText );

			return;
		}
		break;
	case COMMONDLG_CANNOTLOGIN_AGE:
		{
			pTitle = GetTxtFromMgr(7205);
			pText = GetTxtFromMgr(7206);

			pButtonText = GetTxtFromMgr(3889);

			m_pOKButton->SetControllerPos(103, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle( pTitle );
			m_pEdit->SetText( pText );

			return;
		}
		break;
	case COMMONDLG_CANNOTLOGIN_ERROR:
		{
			pTitle = GetTxtFromMgr(7205);
			pText = GetTxtFromMgr(7207);

			pButtonText = GetTxtFromMgr(3889);

			m_pOKButton->SetControllerPos(103, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle( pTitle );
			m_pEdit->SetText( pText );

			return;
		}
		break;
	//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�
	case COMMONDLG_TICKETMONEY_WARP :
		{
			cltClient* pclclient = (cltClient *)pclClient;

			pTitle = GetTxtFromMgr(7541);
			pText= GetTxtFromMgr(7537);

			const TCHAR * szMapName = pclclient->pclMapManager->GetMapName(MAPINDEX_PALACE);

			TCHAR tempBuf[256] = {'\0'};
			StringCchPrintf(tempBuf,256, pText,szMapName,siWarpMoney);

			m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(7542);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(7543);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(pTitle);
			m_pEdit->SetText( tempBuf );

			return;
		}
		break;
	 //KHY - 0906 - ���ӹ� �̺�Ʈ ����.	
	case COMMONDLG_EVENTCOUPON :
		{
			cltClient* pclclient = (cltClient *)pclClient;

			pTitle = GetTxtFromMgr(5579);
			pText= GetTxtFromMgr(7162);

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(7163);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(7164);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(pTitle);
			m_pEdit->SetText( pText );

			return;
		}
		break;
	 //KHY - 1024 - �Ѱ��� VIP �̺�Ʈ - 5�� �޼���.
	case COMMONDLG_HANGAME_VIP_EVENT :
		{
			cltClient* pclclient = (cltClient *)pclClient;

			pTitle = GetTxtFromMgr(5579);
			pText= GetTxtFromMgr(7210);

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(pTitle);
			m_pEdit->SetText( pText );

			return;
		}
		break;
	 //KHY - 1024 - �Ѱ��� VIP �̺�Ʈ - �����۸� Ŭ����.	
	case COMMONDLG_HANGAME_VIP_EVENT_ITEM:
		{
			pTitle = "";
			pText = GetTxtFromMgr(7211);

			pButtonText = GetTxtFromMgr(3889);

			m_pOKButton->SetControllerPos(103, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle( pTitle );
			m_pEdit->SetText( pText );

			return;
		}
		break;
	//KHY - 1025 - ������ �̺�Ʈ
	case COMMONDLG_NOWCOM_EVENT_COUPON:
	case COMMONDLG_NOWCOM_EVENT_10LEVEL:
	case COMMONDLG_NOWCOM_EVENT_HAVEFATHER:
		{
			pTitle = "";

			if(siCommonDlg_mode == COMMONDLG_NOWCOM_EVENT_COUPON)
				pText = GetTxtFromMgr(7212);				
			else if(siCommonDlg_mode == COMMONDLG_NOWCOM_EVENT_10LEVEL)
				pText = GetTxtFromMgr(7213);	
			else if(siCommonDlg_mode == COMMONDLG_NOWCOM_EVENT_HAVEFATHER)
				pText = GetTxtFromMgr(7214);	

//			pText = GetTxtFromMgr(7211);

			pButtonText = GetTxtFromMgr(3889);

			m_pOKButton->SetControllerPos(103, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle( pTitle );
			m_pEdit->SetText( pText );

			return;
		}
		break;
		//�����̺�Ʈ ���� [2007.09.10]	
	//case COMMONDLG_AUCTIONEVENTCOUPON :
	//	{
	//		cltClient* pclclient = (cltClient *)pclClient;

	//		pTitle = GetTxtFromMgr(5579);
	//		pText= GetTxtFromMgr(7162);

	//		m_pOKButton->SetControllerPos(53, 86, 72, 24, 72, 24);
	//		m_pOKButton->Show(TRUE);

	//		m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
	//		m_pCancelButton->Show(TRUE);

	//		pButtonText = GetTxtFromMgr(7163);
	//		m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	//		pButtonText = GetTxtFromMgr(7164);
	//		m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	//		SetTitle(pTitle);
	//		m_pEdit->SetText( pText );

	//		return;
	//	}
	//	break;
	
	// ����, ��Ŀ �̺�Ʈ (PCK - 2007.09.17) - 5���� �޼������� ������ â.
	case COMMONDLG_GOSTOPPOCKERCOMPLETE :
		{
			cltClient* pclclient = (cltClient *)pclClient;

			pTitle = GetTxtFromMgr(5579);
			pText= GetTxtFromMgr(7566);

			pButtonText = GetTxtFromMgr(3889);

			m_pOKButton->SetControllerPos(103, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			SetTitle(pTitle);
			m_pEdit->SetText( pText );

			return;
		}
		break;

		// ����, ��Ŀ �̺�Ʈ (PCK - 2007.09.17) - ���ӿ� ó�� ���������� ������ â.
	case COMMONDLG_GOSTOPPOCKERSTART :
		{
			cltClient* pclclient = (cltClient *)pclClient;

			pTitle = GetTxtFromMgr(7568);
			pText= GetTxtFromMgr(7567);
			
			pButtonText = GetTxtFromMgr(3889);

			m_pOKButton->SetControllerPos(103, 86, 72, 24, 72, 24);
			m_pOKButton->Show(TRUE);

			SetTitle(pTitle);
			m_pEdit->SetText( pText );

			return;
		}
		break;

	case COMMONDLG_HALLOWEENMISSION_START:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = GetTxtFromMgr(8874);
			kText = "";

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;
		}
		break;
	case COMMONDLG_REQUEST_PVP:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = GetTxtFromMgr(9569)	;
			kText = "";

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;
		}
		break;
	case COMMONDLG_REQUEST_FAMILY_ADD_CHILDREN:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = "";
			kText = "";

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;

		}
	case COMMONDLG_REQUEST_FAMILY_DELL_CHILDREN:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = "";
			kText = "";

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;

		}
	case COMMONDLG_REQUEST_FAMILY_REMOVE_TARGET_CHILDREN:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = "";
			kText = "";

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;

		}
	case COMMONDLG_REQUEST_FAMILY_PLUS_FAMILYEFFECTDATE:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = "";
			kText = "";

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;

		}
	case COMMONDLG_REQUEST_RACOONDODGEEVENT_ANSWER://Switch_10MonthEvent_RacoonDodge
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = GetTxtFromMgr(9569)	;
			kText = GetTxtFromMgr(40020)	;

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);	// �亯
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;

		}
	case COMMONDLG_REQUEST_TREASUREEVENT :	
		{
			// ����ã�� - �ؽ�Ʈ �ȸ������
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = ""; 
			kText = GetTxtFromMgr(30055)	;

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;
		}
		break;
	// ���Һ�
	case COMMONDLG_BBB_WAIT_QUESTION:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = GetTxtFromMgr(40065); // ���Һ� ����
			kText = GetTxtFromMgr(40071); // ���� ��� ������������ ���Һ� ���� ������, ����� ��ܿ� ��� �Ҳ�?

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(40072);	// ����ڽ�û
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(40073);	// ��������
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );
		}
		break;
	case COMMONDLG_BBB_DELETE_WAITLIST:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = GetTxtFromMgr(40065); // ���Һ� ����
			kText = GetTxtFromMgr(40075);  // ����� ����Ʈ���� �����˴ϴ�. ���� ���� �� �Ͻ� �ǰ���?

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);	// ��
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);	// �ƴϿ�
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

		}
		break;
	case COMMONDLG_BBB_WARPMAPQUESTION:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			SI32 siNPCRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

			GMONEY	siEntranceFee = siNPCRate * 10;	// npcrate(�ü�) * 10

			kTitle = GetTxtFromMgr(40065); // ���Һ� ����

			NTCHARString256 pBody(GetTxtFromMgr(40077));	// ��������� �̵� ����? 
			NTCHARString256 strMoney; 
			g_JYLibFunction.SetNumUnit(siEntranceFee, strMoney, 256);
			pBody.Replace( "#money#", strMoney );

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);	// ��
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);	// �ƴϿ�
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( (TCHAR*)pBody );
		}
		break;
	case COMMONDLG_BBB_NOTENOUGHMONEY:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = GetTxtFromMgr(362); // ������
			kText = GetTxtFromMgr(1178);  // ����� �����ؼ� ���� ���ߴٴ� �޼���

			m_pOKButton->SetControllerPos(33,86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3887);	// ��
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(3888);	// �ƴϿ�
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );
		}
		break;
	case COMMONDLG_2010NEWYEARFORTUNE_BUF:
		{
			m_pOKButton->Show(FALSE);

			m_pCancelButton->SetControllerPos(93, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(3889);	// Ȯ��
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_2010NEWYEARFORTUNE_QUEST:
		{
			m_pOKButton->SetControllerPos(33,86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);	// ����
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);	// ����
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		}
		break;
	case COMMONDLG_REQUEST_GUILDHUNTMAPWAR_WARP:
		{
			cltClient* pclclient = (cltClient *)pclClient;

			NTCHARString<128>	kTitle;
			NTCHARString<128>	kText;

			kTitle = GetTxtFromMgr(9569)	;
			kText = "";

			m_pOKButton->SetControllerPos(33, 86, 102, 24, 102, 24);
			m_pOKButton->Show(TRUE);

			m_pCancelButton->SetControllerPos(153, 86, 92, 24, 92, 24);
			m_pCancelButton->Show(TRUE);

			pButtonText = GetTxtFromMgr(4430);
			m_pOKButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			pButtonText = GetTxtFromMgr(4431);
			m_pCancelButton->SetText( pButtonText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

			SetTitle(kTitle);
			m_pEdit->SetText( kText );

			return;

		}break	;
	}

	SetTitle(pTitle);
	m_pEdit->SetText( pText );

	return;
}

void CNCommonMsgDlg::SetText(TCHAR* pText)
{
	if(pText == NULL)			return;

	m_pEdit->SetText( pText );
}

// â�� ���̴� �ð��� �����Ѵ�. �Լ� ȣ��ð� ���ĺ��� �ð��� ���.
void CNCommonMsgDlg::SetShowTimeSec(SI32 siShowTimeSec)
{
	m_dwStartTime = pclClient->CurrentClock;
	m_dwShowTimeMS = siShowTimeSec * 1000;
}

void CNCommonMsgDlg::Action()
{
	// �ð������� ������ ��� �ڵ����� â�� �ݴ´�.
	if (m_dwShowTimeMS > 0 && m_dwStartTime > 0)
	{
		if( pclClient->CurrentClock >= m_dwStartTime + m_dwShowTimeMS)
		{
			DeleteDialog();
		}
	}

	switch (siCommonDlg_mode)
	{ 
	case COMMONDLG_EXITCOUNT :
		{
			TCHAR buf[256] = TEXT("");
			TCHAR *pText = GetTxtFromMgr(5743);
			StringCchPrintf(buf, 256, pText, siExitCount);

			m_pEdit->SetText(buf);

			if (siExitCount > 0)
			{
				siExitCount--;

			}
			else
			{
				SetTimerOnOff(FALSE);
				LogOut();
			}
		}
	}
}

void CNCommonMsgDlg::LogOut()
{
	cltClient* pclclient = (cltClient *)pclClient;

	if( pclClient->GetFrame() <= 0 ||
		( pclclient->dwLastReceiveFromServerClock && TABS(pclclient->CurrentClock - pclclient->dwLastReceiveFromServerClock) > 5000))
	{
		dwQuitTimer = 1;
	}
	else
	{
		//dwQuitTimer = pclClient->CurrentClock;

		cltMsg clMsg(GAMEMSG_REQUEST_HOPETOQUIT, 0, NULL);
		pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
	}

	DeleteDialog();
}

SI32 CNCommonMsgDlg::GetMode()
{
	return siCommonDlg_mode;
}

void CNCommonMsgDlg::SetFather( SI32 PupilPersonID, TCHAR* PupilName )
{
	siPupilPersonID = PupilPersonID;
	MStrCpy( szPupilName, PupilName, MAX_PLAYER_NAME );
}

void CNCommonMsgDlg::SetInviteEmpire( SI08 InviteType, SI32 EmpireUnique, SI32 FromPersonID, SI32 EmproerVillageUnique )
{
	siInviteType = InviteType;
	siEmpireUnique = EmpireUnique;
	siFromPersonID = FromPersonID;
	siEmproerVillageUnique = EmproerVillageUnique;
}

//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�
void CNCommonMsgDlg::SetWarpMoney(SI32 MapIndex, SI32 Money  )
{
	szMapIndex = MapIndex;
	siWarpMoney= Money;
}
// PVPRequestID �� ���� �Ѵ�.
void CNCommonMsgDlg::SetPVPRequrstID( SI32 PVPRequestId  )
{
	siPVPRequestID	=	PVPRequestId	;

}
void CNCommonMsgDlg::SetGuildMapWar_PersonID( SI32 GuildMapWar_PersonID  )
{
	siGuildMapWar_PersonID = GuildMapWar_PersonID;
}
// ���� �ý��� �θ� ���̵� ���� �Ѵ�.
void CNCommonMsgDlg::SetParentPersonID( SI32 siParentPersonID  )
{
	m_siParentPersonID	=	siParentPersonID	;

}