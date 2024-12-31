//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#define _JEWAN_WORK

#include "../Common/CommonHeader.h"
#include "../Common/Util/Util.h"

#include "../Client/Client.h"

#include <Mouse.h>
#include <MainFunction.h>

#include "../Client/Music/Music.h"
#include "../../Lib/Sound/SoundMgr.h"
#include "../MapEdit/MapEdit.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"
#include "../../Common/Map/Map.h"


#include <MoveMark.h>

#include "../../Common/Map/Map.h"
#include "Bullet/Bullet.h"
#include "../Inventory/ItemInventory.h"
#include "../Interface/NPC1/NPCTradeDlg.h"

//#include "../Interface/PartyDlg/PartyDlg.h"
#include "../Interface/DailyQuestDlg/DailyQuestSelectDlg.h"
#include "../Interface/DailyQuestDlg/DailyQuestSituationDlg.h"

#include "../Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "../NInterface/NQuestDlg/NQuestDlg.h"
#include "../NInterface/NMiningDlg/NMiningDlg.h"
#include "../NInterface/NFarmingDlg/NFarmingDlg.h"
#include "../NInterface/NFishingDlg/NFishingDlg.h"
#include "../ninterface/nchatbardlg/NChatBarDlg.h"
#include "../ninterface/NMofuMofuList/NMofuMofuList.h"
#include "../ninterface/NDestroyItemDlg/NDestroyItemDlg.h"

#include "../CommonLogic/Msg/MsgType-DailyQuest.h"
#include "../CommonLogic/MsgType-Person.h"

#include "../CommonLogic/Guild/Guild.h"

#include "../Interface/InvestmentDlg/InvestmentDlg.h"
#include "../Interface/TradeMerchantDlg/TradeMerchantDlg.h"
#include "../Interface/TradeMerchantDish/TradeMerchantDish.h"
#include "../Interface/TradeMerchantHorse/TradeMerchantHorse.h"

#include "../Interface/HouseUnit/HouseUnitBaseInfo.h"

#include "../Interface/RichEditChatMgrDlg/RichEditChatMgrDlg.h"

#include "../Interface/NPCMenuDlg/NPCMenuDlg.h"

// ��ä����
#include "../Interface/FanPriest/FanPriestDlg.h"

#include "../NInterface/NChatDlg/NChatDlg.h"
#include "../Client/NInterface/NPartyDlg/NPartyDlg.h"
#include "../Client/NInterface/NStatusBarDlg/NStatusBarDlg.h"

//#endif
// ���� ���ο��� ��ǰ �Ǹ� ����
//#include "../Interface/ForeignMerchant/ForeignMerchantOpenDlg.h"
//#include "../Interface/ForeignMerchant/ForeignMerchantDlg.h"

// ���ΰ� �ŷ�
#include "../NInterface/NPrivateTradeDlg/NPrivateTradeDlg.h"
#include "../NInterface/NPrivateRepair/NPrivateRepairDlg.h"

// ���콺 ������ ��ư �������� �޴�
#include "../Interface/RightMouseMenu/RightMouseMenu.h"


// Chat ���� 
#include "../StatusBar/ChatStatusBar/ChatStatusBarBaseInfo.h"
#include "../StatusBar/ChatStatusBar/ChatStatusBar.h"

#include "../NInterface/NStatusBarDlg/NStatusBarDlg.h"

// �ӼӸ� ä�� ����. 
//#include "../Client/Interface/PrivateChatDlg/PrivateChatBaseInfo.h"
//#include "../Client/Interface/PrivateChatDlg/PrivateChatDlgMgr.h"

#include "../CommonLogic/MagicMgr/MagicMgr.h"
#include "../../Common/Order/Order.h"

#include "../../Common/Skill/Skill-Manager.h"

#include "../CommonLogic/MsgType-RealEstate.h"
#include "../CommonLogic/MsgType-House.h"
#include "../CommonLogic/MsgType-Item.h"
#include "../CommonLogic/MsgType-System.h"
#include "../CommonLogic//Msg/MsgType-Quest.h"
#include "../CommonLogic//Msg/MsgType-HappyBeanQuest.h"

#include "../CommonLogic/Msg/MsgType-ItemMall.h"

#include "../CommonLogic/Msg/MsgType-NPC.h"

#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../Client/Cursor/Cursor.h"
// NPC ���� 
#include "../Client/NPCRepair/NPCRepair.h"
// Ȥ�θ�����
#include "../Interface/WennyOldMan/WennyOldMan.h"

// ����
// �����Ǽ�
#include "../Interface/Byungzo/ByungzoDlg.h"
// �����Ǽ�
#include "../Interface/Yezo/YezoDlg.h"
// ȣ���Ǽ�
#include "../Interface/Hozo/HozoDlg.h"
// ���� ( �� )
#include "../Interface/GoonzuDlg/GoonzuDlg.h"
// �����Ǽ�
#include "../Interface/Izo/IzoDlg.h"
// �����Ǽ�
#include "../Interface/Gongzo/GongzoDlg.h"
// �����Ǽ�
#include "../Interface/Hyungzo/HyungzoDlg.h"

#include "../Interface/JangGilSan/JangGilSanDlg.h"

#include "../Interface/MuDang/MuDangDlg.h"
#include "NInterface/NMudangDlg/NMudangDlg.h"
#include "../InterfaceMgr/InterfaceMgr.h"
#include "../Interface/NInventory/NInventory.h"
#include "../NInterface/NNewInventory/NNewInventory.h"
#include "../NInterface/ncharstatus/NEquipWindow.h"

#include "../NInterface/NBossMarket/NBossMarketDlg.h"
#include "NInterface/NNPCMenuDlg/NNPCMenuDlg.h"    //npc �޴� 
#include "NInterface/NNPCRepairDlg/NNPCRepair.h" //�念��
#include "NInterface/NWennyOldMan/NWennyOldMan.h"

#include "NInterface/NNPC1/NNPCTradeDlg.h"
#include "NInterface/NForeignMerchantDlg/NForeignMerchantDlg.h"
#include "NInterface/NForeignMerchantDlg/NForeignMerchantBuyItemDlg.h"
#include "NInterface/NTradeMerchant/NTradeMerchant.h"

#include "NStructureDlg/House/UserInfo/NHouseUserInfoBaseDlg.h"
#include "NInterface/NHozoDlg/NHozoBaseDlg.h"
#include "NInterface/NNewQuestDlg/NNewQuestDlg.h"
#include "NInterface/NHongGilDongDlg/NHongGilDongDlg.h"
#include "NInterface/NQuestViewer/NQuestViewerDlg.h"
#include "ninterface/ChristmasQuestDlg/ChristmasQuestDlg.h"

#include "NInterface/NPrivateChatDlg/NPrivateChatDlgMgr.h"
#include "NInterface/NRightMouseMenuDlg/NRightMouseMenuDlg.h"
#include "ninterface/nRightMouseUserListDlg/NRightMouseUserListDlg.h"
#include "NInterface/NNewEnchantOther/NNewEnchantOther.h"
#include "ninterface/NChristmasEventDlg/NChristmasEventDlg.h"//ũ���������̺�Ʈ
#include "Prompt/PromptMgr.h"

// ���ݹ�� Ŀ�� �޽��� �ڽ�
#include "Ninterface/NCommonMsgDlg/NCommonMsgDlg.h"

#include "../Interface/LoginNoticeDlg/LoginNoticeDlg.h"

#include "InterfaceMgr/InterfaceMgr.h"
//���ϸ� ����Ʈ 2 
#include "../Client/ninterface/NDailyQuest2/NDailyQuest2SelectDlg.h"
//#include "../Interface/DailyQuestDlg/DailyQuestSituationDlg.h"
#include "../GawiBawiBoMgr/GawiBawiBoMgr_Client.h"

// ���Һ�
#include "../Client/Client_BokBulBokMgr/Client_BBBMgr.h"

// �ʺ��� ��Ƽ ����Ʈ ��Ʈ��(��Ƽ��Ī)
#include "../CommonLogic/PartyMatchingMgr/Client_PartyMatchingMgr.h"

#include "GZMacroAnalysis/GMA.h"					// Goonzu Macro Analysis

extern _InputDevice			IpD;
extern	RECT				ScreenRect;					// ������ ǥ�õǴ� ���� 

class	CPromptMgr;
extern	CPromptMgr			g_PromptMgr;

int 				MouseMode;							// ���콺�� ó�� ���¸� ���� 

SHORT	GameRealX;
SHORT	GameRealY;

SI32 HardwareMouseX, HardwareMouseY;

//---------------------
// ������� �Է� ��Ȳ. 
//---------------------
DWORD	GameWParam;
SHORT	GameLeftPressSwitch = FALSE;
SHORT	GameRightPressSwitch= FALSE;
SHORT   GameDoubleLeftPressSwich = FALSE;

SHORT	LeftPressSelectedSwitch = FALSE;
SHORT	RightPressSelectedSwitch = FALSE;


//-------------------------------------------------------------
// cltClient
//-------------------------------------------------------------
// Ű���� ó���� ������ ��ƾ 
BOOL cltClient::GameOverHead()
{
	static DWORD dwLastHorseMoveClock = 0;

	cltMapClient* pclmap = (cltMapClient*)pclMapManager->pclCurrentMap;

	// �� �����͸��� �׼�. 
	MapEditAction();

	//---------------------------------------------------------------------------------
	// ������� �Է� ��Ȳ�� Ȯ���Ѵ�. 
	//---------------------------------------------------------------------------------
	cltKey clkey;
	bool PopKey = false;
	if(clKeyManager.Pop(&clkey) == true)
	{
		GameMouseX = clkey.siMouseX + MAP_TILE_XSIZE + GetScreenRX();//pclUnderMouseObject->GetRX();
		GameMouseY = clkey.siMouseY + MAP_TILE_YSIZE + GetScreenRY();//;// + pclUnderMouseObject->GetRY();
		GameWParam = clkey.wParam;

		if( m_pclGMA )
		{
			if( m_pclGMA->Add( GMA_ACTION_TYPE_MOUSEMOVE, MAKELPARAM( GameMouseY, GameMouseX ) ) == FALSE )
			{
				m_pclGMA->Write( "goonzu.gma" );			

				cltGameMsgRequest_RecordActionFinished	clinfo( m_siGMA_ByAdminPersonID, "goonzu.gma",  m_bGMA_ReportedByAdminCommand );
				/*cltMsg	clmsg( GAMEMSG_REQUEST_RECORD_ACTION_FINISHED, sizeof( clinfo ), ( char* )&clinfo );
				pclCM->CR[1]->SendNetMsg( (char*)&clmsg );*/
				cltMsg clmsg( GAMEMSG_REQUEST_RECORD_ACTION_FINISHED, sizeof(clinfo), (BYTE*)&clinfo );
				pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clmsg);

				m_siGMA_ByAdminPersonID			=	0;
				m_bGMA_ReportedByAdminCommand	=	FALSE;

				delete m_pclGMA;
				m_pclGMA	=	NULL;
			}
		}



		// ���� ���콺 ��ư ���� 
		if(clkey.siLeftPressMode != KEY_MODE_NONE)
		{
			GameLeftPressSwitch		=	clkey.siLeftPressMode;
			GameRightPressSwitch	=	clkey.siRightPressMode;
			GameDoubleLeftPressSwich  = clkey.siDoubleLeftPressMode;

		}

		PopKey = true;
	}
	else
	{
		GameWParam=0;
	}
/*
#ifdef _DEBUG
	static SI32 keytype = 0;
	static bool pressKey = false;
	static SI32 destX = pclClient->pclCM->CR[1]->GetX();
	static SI32 destY = pclClient->pclCM->CR[1]->GetY();
	static SI32 x = 0;
	static SI32 y = 0;
	static SI32 currentVector = 0;
	static SI32 directionVector = 0;
	const SI32 depth = 4;

	ScanVKey();

	if( VKRepeat(VK_RIGHT) && VKRepeat(VK_UP) )
	{
		keytype = 5;
		pressKey = true;
	}
	else if( VKRepeat(VK_RIGHT) && VKRepeat(VK_DOWN) )
	{
		keytype = 6;
		pressKey = true;
	}
	else if( VKRepeat(VK_LEFT) && VKRepeat(VK_UP) )
	{
		keytype = 7;
		pressKey = true;
	}
	else if( VKRepeat(VK_LEFT) && VKRepeat(VK_DOWN) )
	{
		keytype = 8;
		pressKey = true;
	}
	else if( VKRepeat(VK_RIGHT) ) 
	{
		keytype = 1;
		pressKey = true;
	}
	else if( VKRepeat(VK_LEFT) ) 
	{
		keytype = 2;
		pressKey = true;
	}
	else if( VKRepeat(VK_UP) ) 
	{
		keytype = 3;
		pressKey = true;
	}
	else if( VKRepeat(VK_DOWN) ) 
	{
		keytype = 4;
		pressKey = true;
	}
	else
		keytype = 0;

	directionVector = keytype;

	if( keytype == 0 && pressKey == true )
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];

		pclOrderManager->clOrder.MakeOrder(
			ORDER_FORCESTOP, 
			0, 0, 
			0,
			0);

		pressKey = false;

		destX = 0;
		destY = 0;
		currentVector = 0;

		pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
	}
	else if( keytype == 1 )
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{
			x = pclchar->GetX() + 1 * depth;
			y = pclchar->GetY() - 1 * depth;

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);

			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
		}
	}
	else if( keytype ==  2 )
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{

			x = pclchar->GetX() - 1 * depth;
			y = pclchar->GetY() + 1 * depth;

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);
			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
		}
	}
	else if( keytype ==  3)
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{
			x = pclchar->GetX() - 1 * depth;
			y = pclchar->GetY() - 1 * depth;

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);
			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
		}
	}
	else if( keytype ==  4)
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{
			x = pclchar->GetX() + 1 * depth;
			y = pclchar->GetY() + 1 * depth;

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);
			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
		}
	}
	else if( keytype ==  5)
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{
			x = pclchar->GetX();
			y = pclchar->GetY() - 2 * depth;

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);
			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );

		}
	}
	else if( keytype ==  6)
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{
			x = pclchar->GetX() + 2 * depth;
			y = pclchar->GetY();

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);
			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
		}
	}
	else if( keytype ==  7)
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{
			x = pclchar->GetX() - 2 * depth;
			y = pclchar->GetY();

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);
			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
		}
	}
	else if( keytype ==  8)
	{
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		if( ( currentVector != directionVector ) ||
			( destX == 0 || destX == pclchar->GetX() ) 	&& ( destY == 0 || destY == pclchar->GetY() ) )
		{
			x = pclchar->GetX();
			y = pclchar->GetY() + 2 * depth;

			destX = x;
			destY = y;
			currentVector = directionVector;

			pclOrderManager->clOrder.MakeOrder(
				ORDER_MOVE, 
				x, y, 
				0,
				0);
			pclLog->FilePrint( TEXT("MoveLog.txt"), "%d", keytype );
		}
	}
#endif
*/
	//------------------------------------------------
	// ���콺�� ��ġ�� ���� �� ������ ��´�. 
	//------------------------------------------------

	// ���콺 ������ �ʱ�ȭ �Ѵ�.

	pclUnderMouseObject->MapX = -1; 
	pclUnderMouseObject->MapY = -1;

	// ���콺�� ū ���� ���� ������ 
	// �׸��� ���콺�� �ٸ� ��Ʈ������ �����ؼ��� �ȵȴ�. 
	if(pclmap->IsPtInMap(GameMouseX, GameMouseY) == TRUE)
	{
		// ȭ�� ��ǥ�� ���� ��ǥ�� ��ȯ�Ѵ�.
		pclmap->TransFromScreenToRealXY(GameMouseX, GameMouseY, GameRealX, GameRealY);

		// ���� ��Ʈ ��ǥ�� �ٰŷ� ����Ÿ����ǥ�� ��´�. 
		pclmap->GetRealTileByRealDot(GameRealX, GameRealY, &pclUnderMouseObject->MapX, &pclUnderMouseObject->MapY);

		// ���콺 �Ʒ��� ��ü��  �����Ѵ�. 
		pclUnderMouseObject->GetUnderMouseObject(pclmap, GetScreenMouseX(), GetScreenMouseY());

	}

	//-------------------------------------------------------------------------
	// ���콺�� ��ġ�� �������� ���踦 �������� ���콺�� ó�� ��Ȳ�� ���´�.
	//--------------------------------------------------------------------------
	GetMouseMode();

	//--------------------------------------------
	// ���� ��ư�� ������, ������ ����� �Է��Ѵ�.
	//---------------------------------------------
	if (bPassFirstOrder == TRUE)
	{
		if ( PopKey )
		{
			if(IpD.DoubleLeftPressDoneSwich == TRUE)
			{
				OperateAutoDoubleLeftOrder();			
			}
			if(IpD.LeftPressDoneSwitch == TRUE)
			{
				OperateAutoLeftOrder();
			}
			else if(IpD.RightPressDoneSwitch == TRUE)
			{
				OperateAutoRightOrder();
			}

		}

	}
	bPassFirstOrder = TRUE;

	//--------------------------------------------------------
	// ����� �ԷµǾ� ������ �� ����� �����ϵ��� ��ġ�Ѵ�. 
	//--------------------------------------------------------
	if(siSelectedOrder)
	{
		bool bPassOrder = FALSE;

		//cyj ä�����϶� �ٸ� ��� ������ �޼��� �ڽ� ����
		if (pclCM->CR[1]->GetCurrentOrder() == ORDER_MINE)
		{
			if (m_pDialog[ NMINING_DLG ])
			{
				if (((CNMiningDlg*)m_pDialog[ NMINING_DLG ])->m_siMiningItemUnique > 0)
				{
					if (bStopDoingSwitch == FALSE)
					{
						bStopDoingSwitch = TRUE;

						stMsgBox MsgBox;
						TCHAR *pText = GetTxtFromMgr(5745);
						TCHAR *pTitle = GetTxtFromMgr(1937);
						MsgBox.Set((CControllerMgr*)m_pDialog[ NMINING_DLG ], pTitle, pText, MSGBOX_TYPE_YESNO, 1);

						SetMsgBox(&MsgBox, NULL, 0);
					}

					if (((CNMiningDlg*)m_pDialog[ NMINING_DLG ])->m_bStopMining == FALSE)
					{
						bPassOrder = TRUE;
					}
				}
			}
		}

		if (pclCM->CR[1]->GetCurrentOrder() == ORDER_FARM)
		{
			if (m_pDialog[ NFARMING_DLG ])
			{
				if (((CNFarmingDlg*)m_pDialog[ NFARMING_DLG ])->m_siFarmingItemUnique > 0)
				{
					if (bStopDoingSwitch == FALSE)
					{
						bStopDoingSwitch = TRUE;

						stMsgBox MsgBox;
						TCHAR *pText = GetTxtFromMgr(5745);
						TCHAR *pTitle = GetTxtFromMgr(1937);
						MsgBox.Set((CControllerMgr*)m_pDialog[ NFARMING_DLG ], pTitle, pText, MSGBOX_TYPE_YESNO, 1);

						SetMsgBox(&MsgBox, NULL, 0);
					}

					if (((CNFarmingDlg*)m_pDialog[ NFARMING_DLG ])->m_bStopFarming == FALSE)
					{
						bPassOrder = TRUE;
					}
				}
			}
		}

		if (pclCM->CR[1]->GetCurrentOrder() == ORDER_FISH)
		{
			if (m_pDialog[ NFISHING_DLG ])
			{
				if (((CNFishingDlg*)m_pDialog[ NFISHING_DLG ])->m_siFishingBaitItemUnique >= 0)
				{
					if (bStopDoingSwitch == FALSE)
					{
						bStopDoingSwitch = TRUE;

						stMsgBox MsgBox;
						TCHAR *pText = GetTxtFromMgr(5745);
						TCHAR *pTitle = GetTxtFromMgr(1937);
						MsgBox.Set((CControllerMgr*)m_pDialog[ NFISHING_DLG ], pTitle, pText, MSGBOX_TYPE_YESNO, 1);

						SetMsgBox(&MsgBox, NULL, 0);
					}
					
					if( pclClient->IsCountrySwitch( Switch_FishFarmMineChange ) )
					{
						if (((CNFishingDlg*)m_pDialog[ NFISHING_DLG ])->m_bStopFishing == FALSE)
						{
							bPassOrder = TRUE;
						}
					}
					else
					{
						bPassOrder = TRUE;
					}
				}
			}
		}

		// ���õ� ����� �̵��϶� �̵� ��ũ�� ǥ���ϰ� �ϰ� �̵� ȿ������ ����. 
		if( siSelectedOrder == ORDER_MOVE || siSelectedOrder == ORDER_MOVE_SUMMON)
		{
			SHORT realx, realy;
			pclmap->TransFromScreenToRealXY(GameMouseX, GameMouseY, realx, realy);
			pclmap->pclMoveMark->SetMoveMarkReal(realx, realy);

			// ���� Ÿ�� ������ ���޸��� ȿ���� ����. 
			if(TABS(CurrentClock - dwLastHorseMoveClock) > 5000 && siSelectedOrder != ORDER_MOVE_SUMMON)
			{
				dwLastHorseMoveClock = CurrentClock;
				//KHY - 1001 - ��µ��� 5���� ���� ����.
				cltHorse*	pclHorse		= pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();

				SI32		siSoundEffect	= 0;

				if( (pclHorse != NULL) && (pclCM->CR[1]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true) )
				{
					// [����] ��µ��� ���� �߰� (2008.06.17)
					switch ( pclHorse->siHorseUnique )
					{
					case HORSEUNIQUE_GRAYWOLF:
					case HORSEUNIQUE_WOLF:
					case HORSEUNIQUE_TIGER:
					case HORSEUNIQUE_TIGER2:
					case HORSEUNIQUE_BEAST:
					case HORSEUNIQUE_WHITETIGER:
						{
							siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_WOLF_MOVE") );
						}
						break;

					case HORSEUNIQUE_ELEPHANT:
						{
							siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_ELEPHANT_MOVE") );
						}
						break;
					case HORSEUNIQUE_MOTORCYCLE:
						{
							siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_MOTORCYCLE_MOVE") );
						}
						break;
					case HORSEUNIQUE_FIREHATCH:
						{
							siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_FIREHATCH_MOVE") );
						}
						break;
					case HORSEUNIQUE_SASURI:
						{
							siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_SASURI_MOVE") );
						}
						break;

					default:
						{
							siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_HORSE_MOVE") );
						}
						break;
					}	// switch ( pclHorse->siHorseUnique ) ����
				}
				else
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_HERO_MOVING") );

				}

				if ( siSoundEffect )
				{
					PushEffect( siSoundEffect, 0, 0 );
				}
				
			}
		}

		// ���õ� ĳ���Ͱ� ������, 
		if(clMouseObject.ID)
		{
			if(pclCM->IsAlive(clMouseObject.ID)==TRUE)
			{
				// obj�� ���õ� ĳ������ newselectedswitch�� �����Ѵ�.  
				((cltCharClient*) pclCM->CR[clMouseObject.ID])->SetNewSelectedSwitch(TRUE);
			}
		}

		//---------------------------------------
		// ����� �����. 
		//---------------------------------------
		if (bPassOrder == FALSE)
		{
			pclOrderManager->clOrder.MakeOrder(
				siSelectedOrder, 
				clMouseObject.X, clMouseObject.Y, 
				clMouseObject.ID,
				siSelectedOrderPara1, siSelectedOrderPara2); 

			//pclLog->FilePrint( TEXT("MoveLog.txt"), "���콺" );
		}
	
		//---------------------------------
		// ������ ��ɰ� ������Ʈ�� �ʱ�ȭ�Ѵ�. 
		//---------------------------------
		siSelectedOrder			= 0;
		siSelectedOrderPara1	= 0;
		siSelectedOrderPara2	= 0;

		// ���õ� ������ �ʱ�ȭ�Ѵ�. 
		clMouseObject.Init();

	}


	// ������  ���콺 ��ư�� ���������� ó�� 
	if(IpD.RightPressDoneSwitch==TRUE)
	{
		IpD.RightPressDoneSwitch=FALSE;
	}
	// ����  ���콺 ��ư�� ���������� ó�� 
	if(IpD.LeftPressDoneSwitch==TRUE)
	{
		IpD.LeftPressDoneSwitch=FALSE;
		bDropTrySwitch = false;		// ��ǰ ����߸��� �õ��� �ʱ�ȭ�Ѵ�. 

	}

	if(IpD.DoubleLeftPressDoneSwich==TRUE)
	{
		IpD.DoubleLeftPressDoneSwich = FALSE;
	}

	//--------------------------------
	// ��Ƽä��
	//--------------------------------
	stPartyChatSend PartyChatSendData;

	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if(m_pDialog[ NPARTY_DLG ])
		{
			if( ((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PopPartyChatSendData( &PartyChatSendData ) )
			{
				SendChatMessage(CHATMODE_PARTY, PartyChatSendData.strChatData );
			}
		}
	}

	//--------------------------------
	// Chat
	//--------------------------------
	stChatStatusBarData ChatData;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if( m_pDialog[ NCHATBAR_DLG ] && ((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG  ])->Pop(&ChatData) == TRUE)
		{
			switch(ChatData.si16Msg)
			{

			case GUILD_CHAT_DATA_SEND:
				if(pclCM->CR[1]->pclCI->clBI.clGuildRank.siType 
					&& pclCM->CR[1]->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_STANDING
					&& pclCM->CR[1]->pclCI->clBI.clGuildRank.uiConfirm != GUILDSTATUS_STANDING
					)
				{					
					SendChatMessage(CHATMODE_GUILD, ChatData.strChatData);
				}
				else
				{
					PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
					TCHAR* pTitle = GetTxtFromMgr(5556);
					TCHAR* pText = GetTxtFromMgr(5557);

					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,  pText);
				}
				break;
				// ��� ����鿡�� ����. 
				//case GUILDNOTIFY_CHAT_DATA_SEND:
				//	if(pclCM->CR[1]->pclCI->clBI.clGuildRank.siType == cltGuildRankManager::GUILDRANK_CHIEF)
				//	{
				//		SendChatMessage(CHATMODE_GUILDALL, ChatData.strChatData);
				//	}
				//	else
				//	{
				//		PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
				//		TCHAR* pTitle = GetTxtFromMgr(5558);
				//		TCHAR* pText = GetTxtFromMgr(5559);

				//		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
				//	}
				//	break;
				//#endif

			case RESIDENTS_CHAT_DATA_SEND:
				if(pclCM->CR[1]->pclCI->clBI.siHomeVillage)
				{
					// �޽����� ������ ������. 
					SendChatMessage(CHATMODE_HOME, ChatData.strChatData);
				}
				else
				{
					PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
					TCHAR* pTitle = GetTxtFromMgr(1041);
					TCHAR* pText = GetTxtFromMgr(1042);


					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,  pText);
				}
				break;

			case CHAT_DATA_SEND:
				{
					bool bclientgmswitch = false;

					if(pclCM->CR[1]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL	// ��� ������ �ְų�.. 
						|| pclCM->CR[1]->pclCI->clBI.uiGRank	== GRANK_KING			// ���̸�, 
						|| pclCM->CR[1]->pclCI->clBI.uiGRank	== GRANK_MINISTER5)		// �����Ǽ� 
					{
						if(ChatData.strChatData[0] == '/')
						{
							TCHAR order[1024];
							_stscanf(&ChatData.strChatData[1], TEXT("%s"), order);

							if(pclCM->CR[1]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL)
							{

								if(_tcscmp(order, TEXT("watch")) == 0)
								{
									if(bWatchModeSwitch)
									{
										bWatchModeSwitch = false;
									}
									else
									{
										bWatchModeSwitch = true;
									}

									bclientgmswitch = true;
								}

								else if ( _tcscmp( order, TEXT("questviewer") ) == 0 )
								{
									// PCK : ���� - �ش� ��ɾ�� 100�������� ���డ���ϵ��� �Ѵ�.
									if( pclCM->CR[1]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL )
									{
										if(m_pDialog[QUESTVIEWER_DLG]== NULL)
										{
											CreateInterface(QUESTVIEWER_DLG);
										}
									}									
								}
								/*								else if(_tcscmp(order, TEXT("userlog")) == 0)
								{
								if(pclCM->CR[1]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL+1 &&
								m_pGameMasterPersonalLogDlg!= NULL &&
								!IsWindow(m_pGameMasterPersonalLogDlg->GetDlgHwnd()))
								m_pGameMasterPersonalLogDlg->Set();
								}*/
							}
						}
					}

					if(bclientgmswitch == false)
					{
						// �޽����� ������ ������. 
						SendChatMessage(CHATMODE_NORMAL, ChatData.strChatData);
					}
				}
				break;
			case TOWN_CHAT_DATA_SEND:
				// �޽����� ������ ������. 
				if(pclCM->CR[1]->pclCI->clCharRank.siType == RANKTYPE_CITYHALL)
				{
					SendChatMessage(CHATMODE_TOWN, ChatData.strChatData);
				}
				else
				{
					PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
					TCHAR* pTitle = GetTxtFromMgr(1043);
					TCHAR* pText = GetTxtFromMgr(1044);


					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
				}
				break;

				// ���� �ֹε鿡�� ����. 
			case RESIDENTSNOTIFY_CHAT_DATA_SEND:
				// �޽����� ������ ������. 
				if(pclCM->CR[1]->pclCI->clCharRank.siType == RANKTYPE_CITYHALL)
				{
					SendChatMessage(CHATMODE_VILLAGER, ChatData.strChatData);
				}
				else
				{
					PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
					TCHAR* pTitle = GetTxtFromMgr(1049);
					TCHAR* pText = GetTxtFromMgr(1044);


					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
				}
				break;

			case HEAD_CHAT_DATA_SEND:
				if(pclCM->CR[1]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)
				{
					if(pclCM->CR[1]->bPersonalShopSwitch == true)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1045);
						TCHAR* pText	=	NULL	;
						if ( pclClient->IsCountrySwitch( Switch_Change_manufacture_request_interface ) ) 
						{
							pText = GetTxtFromMgr(40848);
						}
						else
						{
							pText = GetTxtFromMgr(1046);
						}
						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
					else if ( g_SoundOnOffDlg.m_bNotifyHeadChat == true )
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1045);
						TCHAR* pText = GetTxtFromMgr(1047);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
					// [����] ���� : �����߿��� ����â �Ұ��� ��
					else if ( pclCM->CR[1]->bIsElectionStump == true )
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1045);
						TCHAR* pText = GetTxtFromMgr(8278);

						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
					// [����] �����Ƿ� �߿��� ����â�� �Ұ����ϴ�.
					else if ( pclCM->CR[1]->bRepairShopSwitch == true )
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1045);
						TCHAR* pText = GetTxtFromMgr(8278);

						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
					else 
					{
						SendChatMessage(CHATMODE_HEAD, ChatData.strChatData);
					}
				}
				else
				{
					PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);

					TCHAR* pTitle = GetTxtFromMgr(1045);
					TCHAR* pText = GetTxtFromMgr(1048);


					m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText,	FATHER_LEVEL);
				}
				break;
			case KINGNOTIFY_CHAT_DATA_SEND:
				{
					SendChatMessage(CHATMODE_KING, ChatData.strChatData);
				}
				break;
			case PARTY_CHAT_DATA_SEND:
				{
					if( m_pDialog[ NPARTY_DLG ] != NULL && ((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->IsPartyUser(pclCM->CR[1]->GetCharUnique()) )
					{
						SendChatMessage(CHATMODE_PARTY,ChatData.strChatData);
					}
					else
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(5584);
						TCHAR* pText = GetTxtFromMgr(5585);

						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,  pText);
					}
				}
				break;

			case NEWS_CHAT_DATA_SEND:
				{
					SendChatMessage(CHATMODE_NEWSITEM,ChatData.strChatData);
				}
				break;

			default:
				MsgBox(TEXT("a0874"), TEXT("vc94:%d"), ChatData.si16Msg);
				break;
			}
		}

	}

	//------------------------------------
	// �Ӹ� ä��. 
	//------------------------------------
	stWhisperChatDataSend stchat;
	while( m_pNPrivateChatDlgMgr->Pop(&stchat) )
	{
		cltGameMsgSecretChat clSecretChat( stchat.siToID, stchat.szToCharName, stchat.strChatData );
		cltMsg clMsg( GAMEMSG_REQUEST_SECRETCHAT, sizeof(clSecretChat), (BYTE*)&clSecretChat );
		SendMsgToServer((sPacketHeader*)&clMsg);
	}

	//--------------------------------
	// ���� ����
	//--------------------------------
	stHouseUnitData HouseUnitData;

	if( m_pDialog[ NHOUSEUSERINFOBASE_DLG ] && ((CNHouseUserInfoBaseDlg*)m_pDialog[ NHOUSEUSERINFOBASE_DLG ])->Pop(&HouseUnitData) == TRUE)
	{
		SI32 id = 1;
		if(pclCM->IsAlive(1) == TRUE)
		{
			switch(HouseUnitData.si16Msg)
			{
				// �κ����� â��� �������� �ִ´�. 
			case HOUSEUNIT_INPUT_USERINVENTORY_TO_WAREHOUSE:
				{
					cltMsg clMsg(GAMEMSG_REQUEST_MOVEITEMINVTOSTG,  
						sizeof(stHouseUnitData), (BYTE*)&HouseUnitData);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case HOUSEUNIT_OUTPUT_USERINVENTORY_FROM_WAREHOUSE:
				{
					cltMsg clMsg(GAMEMSG_REQUEST_MOVEITEMSTGTOINV, 
						sizeof(stHouseUnitData), (BYTE*)&HouseUnitData);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
				// �������� �����Ѵ�. 
			case HOUSEUNIT_WAREHOUSE_MAKEITEM:
				{
					cltGameMsgRequest_MakeItemInStg clInfo(HouseUnitData.si32lParam1, 
						HouseUnitData.si32lParam2, 
						HouseUnitData.si32VillageUnique, 
						HouseUnitData.si32HouseUnitSlot);

					cltMsg clMsg(GAMEMSG_REQUEST_MAKEITEM,
						sizeof(clInfo), (BYTE*)&clInfo);

					SendMsgToServer((sPacketHeader*)&clMsg);

				}
				break;

				// ��� ����. 
			case HOUSEUNIT_RETAL_EXTENSION:
				{
					// �ʿ� �ڰ� ������ ������Ű�� �ִ��� Ȯ���Ѵ�. 
					if(pclCM->CR[id]->pclCI->clIP.GetLevel() < LEVELLIMIT_USE_HOUSE)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1050);
						TCHAR* pText = GetTxtFromMgr(1051);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, LEVELLIMIT_USE_HOUSE);
						break;
					}

					// ���Ӽ����� ��� ���� ��û�� ������. 
					cltGameMsgRequest_ExtendContract clinfo(HouseUnitData.si32VillageUnique, REALESTATE_TYPE_HOUSE, HouseUnitData.si32HouseUnitSlot, &HouseUnitData.clContract);

					cltMsg clMsg(GAMEMSG_REQUEST_EXTENDCONTRACT,
						sizeof(clinfo), (BYTE*)&clinfo);

					SendMsgToServer((sPacketHeader*)&clMsg);

				}
				break;

			default:
				MsgBox(TEXT("fds98n"), TEXT("vcu3:%d"), HouseUnitData.si16Msg);
			}

		}
	}

	/*	{
	SI32 id = 1;
	if(pclCM->IsAlive(1) == TRUE)
	{
	switch(HouseUnitData.si16Msg)
	{
	// �κ����� â��� �������� �ִ´�. 
	case HOUSEUNIT_INPUT_USERINVENTORY_TO_WAREHOUSE:
	{
	cltMsg clMsg(GAMEMSG_REQUEST_MOVEITEMINVTOSTG,  
	sizeof(stHouseUnitData), (BYTE*)&HouseUnitData);

	SendMsgToServer((sPacketHeader*)&clMsg);
	}
	break;
	case HOUSEUNIT_OUTPUT_USERINVENTORY_FROM_WAREHOUSE:
	{
	cltMsg clMsg(GAMEMSG_REQUEST_MOVEITEMSTGTOINV, 
	sizeof(stHouseUnitData), (BYTE*)&HouseUnitData);

	SendMsgToServer((sPacketHeader*)&clMsg);
	}
	break;
	// �������� �����Ѵ�. 
	case HOUSEUNIT_WAREHOUSE_MAKEITEM:
	{
	cltGameMsgRequest_MakeItemInStg clInfo(HouseUnitData.si32lParam1, 
	HouseUnitData.si32lParam2, 
	HouseUnitData.si32VillageUnique, 
	HouseUnitData.si32HouseUnitSlot);

	cltMsg clMsg(GAMEMSG_REQUEST_MAKEITEM,
	sizeof(clInfo), (BYTE*)&clInfo);

	SendMsgToServer((sPacketHeader*)&clMsg);

	}
	break;

	// ��� ����. 
	case HOUSEUNIT_RETAL_EXTENSION:
	{
	// �ʿ� �ڰ� ������ ������Ű�� �ִ��� Ȯ���Ѵ�. 
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() < LEVELLIMIT_USE_HOUSE)
	{
	PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
	TCHAR* pTitle = GetTxtFromMgr(1050);
	TCHAR* pText = GetTxtFromMgr(1051);


	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, LEVELLIMIT_USE_HOUSE);
	break;
	}

	// ���Ӽ����� ��� ���� ��û�� ������. 
	cltGameMsgRequest_ExtendContract clinfo(HouseUnitData.si32VillageUnique, REALESTATE_TYPE_HOUSE, HouseUnitData.si32HouseUnitSlot, &HouseUnitData.clContract);

	cltMsg clMsg(GAMEMSG_REQUEST_EXTENDCONTRACT,
	sizeof(clinfo), (BYTE*)&clinfo);

	SendMsgToServer((sPacketHeader*)&clMsg);

	}
	break;

	default:
	MsgBox(TEXT("fds98n"), TEXT("vcu3:%d"), HouseUnitData.si16Msg);
	}

	}

	}*/

	//--------------------------------
	// NPC Trade
	//--------------------------------
	stNPCTradeData NPCTradeData;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if(( m_pDialog[ NNPCTRADE1_DLG ])!=NULL)
		{
			if (((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG  ])->Pop(&NPCTradeData) == TRUE) 
			{
				SI32 id = 1;
				if(pclCM->IsAlive(1) == TRUE)
				{
					switch(NPCTradeData.si16Msg)
					{
					case NPCTRADE_SELLITEM_TO_NPC:
						{
							cltMsg clMsg(GAMEMSG_REQUEST_SELLNPC, 
								sizeof(stNPCTradeData), (BYTE*)&NPCTradeData);

							SendMsgToServer((sPacketHeader*)&clMsg);
						}
						break;

					case NPCTRADE_BUYITEM_FROM_NPC:
						{
							cltMsg clMsg(GAMEMSG_REQUEST_BUYNPC,
								sizeof(stNPCTradeData), (BYTE*)&NPCTradeData);

							SendMsgToServer((sPacketHeader*)&clMsg);
						}
						break;

					default:
						MsgBox(TEXT("fdk9jfdc"), TEXT("vc09873:%d"), NPCTradeData.si16Msg);
					}
				}

			}
		}
	}

	//--------------------------------
	// ���ΰ� �ŷ�
	//--------------------------------

	BYTE cData[ MAX_PRIVATETRADE_OBJ_BUFFER_SIZE ];
	//	 CNPrivateTradeDlg* NPrivateTradeDlg= ((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG]);

	if(m_pDialog[NPRIVATETRADE_DLG])
	{
		CNPrivateTradeDlg* NPTradeDlg= ((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG]);


		if(( NPTradeDlg->Pop( cData ) )== TRUE ) 
		{
			stPrivateTradeHeader *pTradeHeader = (stPrivateTradeHeader *)&cData;

			switch( pTradeHeader->uiMsg )
			{
			case PRIVATETRADE_CANCEL:
				{
					// ��� �޽��� ��û
					stPrivateTrade_Cancel *pCancel = (stPrivateTrade_Cancel *)cData;

					cltGameMsgRequest_PrivateTrade_Cancel clPrivateTradeCancel( pCancel->siOtherCharUnique, pCancel->siPrivateTradeOrderMgrIndex, pCancel->siPrivateTradeOrderCountIndex );
					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_CANCEL,
						sizeof(clPrivateTradeCancel), (BYTE*)&clPrivateTradeCancel);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_ADD_ITEM:
				{
					stPrivateTrade_Add_Item *pAddItemInfo = (stPrivateTrade_Add_Item *)cData;

					cltGameMsgRequest_PrivateTrade_AddItem clPrivateTradeAddItem
						(
						pAddItemInfo->siOtherCharUnique, 
						pAddItemInfo->siPrivateTradeOrderMgrIndex, 
						pAddItemInfo->siPrivateTradeOrderCountIndex,
						pAddItemInfo->siItemPos,
						&pAddItemInfo->clItem,
						pAddItemInfo->siAddItemNum					
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDITEM,
						sizeof(clPrivateTradeAddItem), (BYTE*)&clPrivateTradeAddItem);

					SendMsgToServer((sPacketHeader*)&clMsg);				
				}
				break;
			case PRIVATETRADE_DEL_LIST:
				{
					stPrivateTrade_Del_List *pDelList = (stPrivateTrade_Del_List *)cData;

					cltGameMsgRequest_PrivateTrade_DelList clPrivateTradeDelList
						( 
						pDelList->siOtherCharUnique,
						pDelList->siPrivateTradeOrderMgrIndex,
						pDelList->siPrivateTradeOrderCountIndex,
						pDelList->siDelType,
						pDelList->siParam
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_DELLIST,
						sizeof(clPrivateTradeDelList), (BYTE*)&clPrivateTradeDelList);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_DEL_ITEM:
				{
					stPrivateTrade_Del_Item *pDelItemInfo = (stPrivateTrade_Del_Item *)cData;

					cltGameMsgRequest_PrivateTrade_DelItem clPrivateTradeDelItem
						( 
						pDelItemInfo->siOtherCharUnique,
						pDelItemInfo->siPrivateTradeOrderMgrIndex,
						pDelItemInfo->siPrivateTradeOrderCountIndex,
						pDelItemInfo->siDelIndex,
						&pDelItemInfo->clItem
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_DELITEM,
						sizeof(clPrivateTradeDelItem), (BYTE*)&clPrivateTradeDelItem);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_PRICE:
				{
					stPrivateTrade_Price *pMyPrice = (stPrivateTrade_Price*)cData;
					cltGameMsgRequest_PrivateTrade_AddPrice clPrivateTrade_AddPrice
						(
						pMyPrice->siOtherCharUnique,
						pMyPrice->siPrivateTradeOrderMgrIndex,
						pMyPrice->siPrivateTradeOrderCountIndex,
						pMyPrice->siPrice
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDPRICE, sizeof(clPrivateTrade_AddPrice), (BYTE*)&clPrivateTrade_AddPrice);

					SendMsgToServer((sPacketHeader*)&clMsg);

				}
				break;
			case PRIVATETRADE_STOCK:
				{
					stPrivateTrade_Stock *pMyStock = (stPrivateTrade_Stock*)cData;
					cltGameMsgRequest_PrivateTrade_AddStock clPrivateTrade_AddStock
						(
						pMyStock->siOtherCharUnique,
						pMyStock->siPrivateTradeOrderMgrIndex,
						pMyStock->siPrivateTradeOrderCountIndex,
						pMyStock->siStockVillageUnique,
						pMyStock->siStockNum					
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDSTOCK, sizeof(clPrivateTrade_AddStock), (BYTE*)&clPrivateTrade_AddStock);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_HOUSEUNIT:
				{
					stPrivateTrade_HouseUnit *pMyHouseUnit = (stPrivateTrade_HouseUnit*)cData;
					cltGameMsgRequest_PrivateTrade_AddHouseUnit clPrivateTrade_AddHouseUnit
						(
						pMyHouseUnit->siOtherCharUnique,
						pMyHouseUnit->siPrivateTradeOrderMgrIndex,
						pMyHouseUnit->siPrivateTradeOrderCountIndex,
						pMyHouseUnit->siHouseVillageUnique,
						pMyHouseUnit->siHouseUnitSlot
						);

					cltMsg clMsg( GAMEMSG_REQUEST_PRIVATETRADE_ADDHOUSEUNIT, sizeof(clPrivateTrade_AddHouseUnit), (BYTE*)&clPrivateTrade_AddHouseUnit );

					SendMsgToServer((sPacketHeader*)&clMsg);

				}
				break;

			case PRIVATETRADE_HORSE:
				{
					cltHorse *pclHorse = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();
					if ( pclHorse == NULL )
					{
						break;
					}

					stPrivateTrade_Horse *pMyHorse = (stPrivateTrade_Horse*)cData;
					cltGameMsgRequest_PrivateTrade_AddHorse clPrivateTrade_AddHorse
						(
						pMyHorse->siOtherCharUnique,
						pMyHorse->siPrivateTradeOrderMgrIndex,
						pMyHorse->siPrivateTradeOrderCountIndex,
						pMyHorse->siHorseIndex
						);
					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDHORSE, sizeof(clPrivateTrade_AddHorse), (BYTE*)&clPrivateTrade_AddHorse);
					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_MYACCEPT:
				{
					stPrivateTrade_MyAccept *pMyAccept = ( stPrivateTrade_MyAccept * )cData;

					cltGameMsgRequest_PrivateTrade_MyAccept clPrivateTrade_MyAccept
						(
						pMyAccept->siOtherCharUnique, 
						pMyAccept->siPrivateTradeOrderMgrIndex, 
						pMyAccept->siPrivateTradeOrderCountIndex,
						pMyAccept->siAcceptCounter
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_MYACCEPT,
						sizeof(clPrivateTrade_MyAccept), (BYTE*)&clPrivateTrade_MyAccept);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_MYCANCEL:
				{
					stPrivateTrade_MyCancel *pMyCancel = ( stPrivateTrade_MyCancel * )cData;

					cltGameMsgRequest_PrivateTrade_MyCancel clPrivateTrade_MyCancel
						(
						pMyCancel->siOtherCharUnique,
						pMyCancel->siPrivateTradeOrderMgrIndex,
						pMyCancel->siPrivateTradeOrderCountIndex
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_MYCANCEL,
						sizeof(clPrivateTrade_MyCancel), (BYTE*)&clPrivateTrade_MyCancel);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;

			}	
		}
	}
	if(m_pDialog[NNEWENCHANTOTHER_DLG])
	{
		CNNewEnchantOther* NPTradeDlg= ((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG]);   

		if(( NPTradeDlg->Pop( cData ) )== TRUE ) 
		{
			stPrivateTradeHeader *pTradeHeader = (stPrivateTradeHeader *)&cData;

			switch( pTradeHeader->uiMsg )
			{
			case PRIVATETRADE_CANCEL:
				{
					// ��� �޽��� ��û
					stPrivateTrade_Cancel *pCancel = (stPrivateTrade_Cancel *)cData;

					cltGameMsgRequest_PrivateTrade_Cancel clPrivateTradeCancel( pCancel->siOtherCharUnique, pCancel->siPrivateTradeOrderMgrIndex, pCancel->siPrivateTradeOrderCountIndex );
					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_CANCEL,
						sizeof(clPrivateTradeCancel), (BYTE*)&clPrivateTradeCancel);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;

			}
		}
	}
	if(m_pDialog[NPTRADEREPRAIR_DLG])
	{
		CNPrivateRepairDlg* NPRepairDlg= ((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG]);



		if((NPRepairDlg->Pop( cData ) )== TRUE ) 
		{
			stPrivateTradeHeader *pTradeHeader = (stPrivateTradeHeader *)&cData;

			switch( pTradeHeader->uiMsg )
			{
			case PRIVATETRADE_CANCEL:
				{
					// ��� �޽��� ��û
					stPrivateTrade_Cancel *pCancel = (stPrivateTrade_Cancel *)cData;

					cltGameMsgRequest_PrivateTrade_Cancel clPrivateTradeCancel( pCancel->siOtherCharUnique, pCancel->siPrivateTradeOrderMgrIndex, pCancel->siPrivateTradeOrderCountIndex );
					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_CANCEL,
						sizeof(clPrivateTradeCancel), (BYTE*)&clPrivateTradeCancel);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_ADD_ITEM:
				{
					stPrivateTrade_Add_Item *pAddItemInfo = (stPrivateTrade_Add_Item *)cData;

					cltGameMsgRequest_PrivateTrade_AddItem clPrivateTradeAddItem
						(
						pAddItemInfo->siOtherCharUnique, 
						pAddItemInfo->siPrivateTradeOrderMgrIndex, 
						pAddItemInfo->siPrivateTradeOrderCountIndex,
						pAddItemInfo->siItemPos,
						&pAddItemInfo->clItem,
						pAddItemInfo->siAddItemNum					
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDITEM,
						sizeof(clPrivateTradeAddItem), (BYTE*)&clPrivateTradeAddItem);

					SendMsgToServer((sPacketHeader*)&clMsg);				
				}
				break;
			case PRIVATETRADE_DEL_LIST:
				{
					stPrivateTrade_Del_List *pDelList = (stPrivateTrade_Del_List *)cData;

					cltGameMsgRequest_PrivateTrade_DelList clPrivateTradeDelList
						( 
						pDelList->siOtherCharUnique,
						pDelList->siPrivateTradeOrderMgrIndex,
						pDelList->siPrivateTradeOrderCountIndex,
						pDelList->siDelType,
						pDelList->siParam
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_DELLIST,
						sizeof(clPrivateTradeDelList), (BYTE*)&clPrivateTradeDelList);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_DEL_ITEM:
				{
					stPrivateTrade_Del_Item *pDelItemInfo = (stPrivateTrade_Del_Item *)cData;

					cltGameMsgRequest_PrivateTrade_DelItem clPrivateTradeDelItem
						( 
						pDelItemInfo->siOtherCharUnique,
						pDelItemInfo->siPrivateTradeOrderMgrIndex,
						pDelItemInfo->siPrivateTradeOrderCountIndex,
						pDelItemInfo->siDelIndex,
						&pDelItemInfo->clItem
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_DELITEM,
						sizeof(clPrivateTradeDelItem), (BYTE*)&clPrivateTradeDelItem);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_PRICE:
				{
					stPrivateTrade_Price *pMyPrice = (stPrivateTrade_Price*)cData;
					cltGameMsgRequest_PrivateTrade_AddPrice clPrivateTrade_AddPrice
						(
						pMyPrice->siOtherCharUnique,
						pMyPrice->siPrivateTradeOrderMgrIndex,
						pMyPrice->siPrivateTradeOrderCountIndex,
						pMyPrice->siPrice
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDPRICE, sizeof(clPrivateTrade_AddPrice), (BYTE*)&clPrivateTrade_AddPrice);

					SendMsgToServer((sPacketHeader*)&clMsg);

				}
				break;
			case PRIVATETRADE_STOCK:
				{
					stPrivateTrade_Stock *pMyStock = (stPrivateTrade_Stock*)cData;
					cltGameMsgRequest_PrivateTrade_AddStock clPrivateTrade_AddStock
						(
						pMyStock->siOtherCharUnique,
						pMyStock->siPrivateTradeOrderMgrIndex,
						pMyStock->siPrivateTradeOrderCountIndex,
						pMyStock->siStockVillageUnique,
						pMyStock->siStockNum					
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDSTOCK, sizeof(clPrivateTrade_AddStock), (BYTE*)&clPrivateTrade_AddStock);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_HOUSEUNIT:
				{
					stPrivateTrade_HouseUnit *pMyHouseUnit = (stPrivateTrade_HouseUnit*)cData;
					cltGameMsgRequest_PrivateTrade_AddHouseUnit clPrivateTrade_AddHouseUnit
						(
						pMyHouseUnit->siOtherCharUnique,
						pMyHouseUnit->siPrivateTradeOrderMgrIndex,
						pMyHouseUnit->siPrivateTradeOrderCountIndex,
						pMyHouseUnit->siHouseVillageUnique,
						pMyHouseUnit->siHouseUnitSlot
						);

					cltMsg clMsg( GAMEMSG_REQUEST_PRIVATETRADE_ADDHOUSEUNIT, sizeof(clPrivateTrade_AddHouseUnit), (BYTE*)&clPrivateTrade_AddHouseUnit );

					SendMsgToServer((sPacketHeader*)&clMsg);

				}
				break;

			case PRIVATETRADE_HORSE:
				{
					cltHorse *pclHorse = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();
					if ( pclHorse == NULL )
					{
						break;
					}

					stPrivateTrade_Horse *pMyHorse = (stPrivateTrade_Horse*)cData;
					cltGameMsgRequest_PrivateTrade_AddHorse clPrivateTrade_AddHorse
						(
						pMyHorse->siOtherCharUnique,
						pMyHorse->siPrivateTradeOrderMgrIndex,
						pMyHorse->siPrivateTradeOrderCountIndex,
						pMyHorse->siHorseIndex
						);
					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ADDHORSE, sizeof(clPrivateTrade_AddHorse), (BYTE*)&clPrivateTrade_AddHorse);
					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_MYACCEPT:
				{
					stPrivateTrade_MyAccept *pMyAccept = ( stPrivateTrade_MyAccept * )cData;

					cltGameMsgRequest_PrivateTrade_MyAccept clPrivateTrade_MyAccept
						(
						pMyAccept->siOtherCharUnique, 
						pMyAccept->siPrivateTradeOrderMgrIndex, 
						pMyAccept->siPrivateTradeOrderCountIndex,
						pMyAccept->siAcceptCounter
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_MYACCEPT,
						sizeof(clPrivateTrade_MyAccept), (BYTE*)&clPrivateTrade_MyAccept);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case PRIVATETRADE_MYCANCEL:
				{
					stPrivateTrade_MyCancel *pMyCancel = ( stPrivateTrade_MyCancel * )cData;

					cltGameMsgRequest_PrivateTrade_MyCancel clPrivateTrade_MyCancel
						(
						pMyCancel->siOtherCharUnique,
						pMyCancel->siPrivateTradeOrderMgrIndex,
						pMyCancel->siPrivateTradeOrderCountIndex
						);

					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_MYCANCEL,
						sizeof(clPrivateTrade_MyCancel), (BYTE*)&clPrivateTrade_MyCancel);

					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;

			}	
		}
	}


	//--------------------------------
	// ������ �ܱ� ����( û, �Ϻ� ) NPC ���� ��ǰ �Ǹ� �۾�
	//--------------------------------
	stSellToForeignMerchant sSellToForeignMerchant;

	if ( m_pDialog[ NFOREIGNMERCHANTBUYITEM_DLG ] && 
		((CNForeignMerchantBuyItemDlg *)m_pDialog[ NFOREIGNMERCHANTBUYITEM_DLG ])->Pop( &sSellToForeignMerchant ) )
	{
		SI32 id = 1;
		if(pclCM->IsAlive(id) == TRUE)			// ���� ���� �϶��� �����ϰ���...
		{
			switch( sSellToForeignMerchant.sHeader.uiMsg )
			{
			case SELL_TO_FOREIGNMERCHANT:
				{
					cltGameMsgRequest_SellToForeignMerchant clSellToForeignMerchant;
					clSellToForeignMerchant.siForeignMerchantKind = sSellToForeignMerchant.siForeignMerchantKind;
					clSellToForeignMerchant.siSellItemUnique = sSellToForeignMerchant.siSellItemUnique;
					clSellToForeignMerchant.uiSellItemNum = sSellToForeignMerchant.uiSellItemNum;
					clSellToForeignMerchant.uiSelectedIndex = sSellToForeignMerchant.uiSelectedIndex;
					clSellToForeignMerchant.siNPCCharUnique = sSellToForeignMerchant.siNPCCharUnique;
					clSellToForeignMerchant.uiRareInfo = (((*((*(((*pclCM).CR)[1])).pclCI)).clCharItem).clItem)[sSellToForeignMerchant.uiSelectedIndex].clItemCommon.clCommonInfo.uiRareInfo;
					
					cltMsg clMsg(GAMEMSG_REQUEST_SELLTOFOREIGNMERCHANT,
						sizeof(cltGameMsgRequest_SellToForeignMerchant), (BYTE*)&clSellToForeignMerchant);

					SendMsgToServer((sPacketHeader*)&clMsg);

					//------------------------------------------
					// NPC���� ������ �Ǹ��ϴ� ����Ʈ ���̾��ٸ�, 
					//------------------------------------------
					SI16 questtype, questunique, para1, para2;
					SI16 questclearcond =  QUEST_CLEAR_COND_SELLSWORDNPC;
					if(pclCM->CR[id]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
					{
						if(para1 == sSellToForeignMerchant.siSellItemUnique)
						{
							cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
							cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
							SendMsgToServer((sPacketHeader*)&clMsg);
						}
					}
				}
				break;
			default:
				MsgBox( TEXT("235dg"), TEXT("sdg43:%d"), sSellToForeignMerchant.sHeader.uiMsg );
			}
		}
	}

	//--------------------------------
	// �κ��丮������ ������ �۾�. 
	//--------------------------------
	stMoveData clinvinfo;
    
	if( ( m_pDialog[ NNEWINVENTORY_DLG ] && ((CNNewInventory*)m_pDialog[ NNEWINVENTORY_DLG ])->Pop(&clinvinfo) ) || 
		( m_pDialog[ NNEWINVENTORY_HORSE_DLG ] && ((CNNewInventory*)m_pDialog[ NNEWINVENTORY_HORSE_DLG ])->Pop(&clinvinfo) ) ||
		( m_pDialog[ NNEWINVENTORY_BAG0_DLG ] && ((CNNewInventory*)m_pDialog[ NNEWINVENTORY_BAG0_DLG ])->Pop(&clinvinfo) ) ||
		( m_pDialog[ NNEWINVENTORY_BAG1_DLG ] && ((CNNewInventory*)m_pDialog[ NNEWINVENTORY_BAG1_DLG ])->Pop(&clinvinfo) ) )
	{
		SI32 id = 1;
		if(pclCM->IsAlive(id) == TRUE)
		{
			switch(clinvinfo.si16Message)
			{
			case INV_MAKE_ITEM:
				{
					//KHY - 0507 - ��þƮ �߿��� ������  ���� ���Ѵ�. 
					if(pclCM->CR[1]->siPersonalMakeItemType > 0 ) // ���� �������̴�.
					{
						TCHAR* pTitle = GetTxtFromMgr(5893);
						TCHAR* pText = GetTxtFromMgr(8416);

						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						
						break;
					}
					SI32 unique		= clinvinfo.si32lParam;
					SI32 itemnum	= clinvinfo.si32lParam1;
														
					SI32 itemtype = pclItemManager->GetItemType(unique);
					SI08 maketype = pclItemManager->FindMakeAniTypeFromUnique(unique);

					// �ڽ��� �ϴ� �͵��̴� �� PSHOP_MODE_NONE �׸������ ����� ����� ������ �����ϴ�
					cltGameMsgRequest_MakeItemInv clInfo(unique, itemnum, 0,0,PSHOP_MODE_NONE,maketype);
					cltMsg clMsg(GAMEMSG_REQUEST_MAKEITEMINV,sizeof(clInfo), (BYTE*)&clInfo);
					SendMsgToServer((sPacketHeader*)&clMsg);
					// ��������� ���ǿ� ���� ȿ������ �����Ѵ�. 
					pclItemManager->PlaySound(unique, ITEMSOUND_MAKE);
				}
				break;
				// �������� ��æƮ �Ѵ�.
			case INV_ENCHANT_ITEM:
				{
					SI32 unique		= clinvinfo.si32lParam;
					SI32 itemnum	= clinvinfo.si32lParam1;

					SI32 MaterialCharUnique =0;

					//KHY - 0507 - �����߿��� ��þƮ�� ���� ���Ѵ�. 
					if(pclCM->CR[1]->siPersonalMakeItemType > 0 ) // ���� �������̴�.
					{
						TCHAR* pTitle = GetTxtFromMgr(5893);
						TCHAR* pText = GetTxtFromMgr(8415);

						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						
						break;
					}
					if(m_pDialog[NNEWENCHANTOTHER_DLG])
					{
						MaterialCharUnique  = ((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG])->GetMatOtherCharUnique();
					}
					
                    SI08 enchantanitype = pclClient->pclItemManager->FindEnchantAniTypeFromUnique( unique );

					// �ڽ��� �ϴ� �͵��̴� �� PSHOP_MODE_NONE �׸������ ����� ����� ������ �����ϴ�
					cltGameMsgRequest_MakeItemInv clInfo(unique, itemnum, MaterialCharUnique,MaterialCharUnique,PSHOP_MODE_NONE,enchantanitype);
					cltMsg clMsg(GAMEMSG_REQUEST_ENCHANTITEMINV,sizeof(clInfo), (BYTE*)&clInfo);
					SendMsgToServer((sPacketHeader*)&clMsg);

					// ��������� ���ǿ� ���� ȿ������ �����Ѵ�. 
					pclItemManager->PlaySound(unique, ITEMSOUND_MAKE);

				}
				break;
			case INV_CHANGE_ITEM:
				{					

					SI32 topos = HIWORD(clinvinfo.si32lParam);
					if(pclItemManager->CheckProperItemPos(&clinvinfo.clMoveItem, topos, pclCM->CR[1]->GetKind()) == TRUE)
					{
						SI32 type = clinvinfo.clMoveItem.GetType(pclItemManager);
						SI32 returnval	= 0;
						bool bsuccessswitch = true;

						if ( topos < PERSONITEM_INV0 ) //|| topos >= PERSONITEM_SUMMON1EQUIP0)
						{
							if(topos < PERSONITEM_INV0)
							{
								if(pclItemManager->CheckCondition(clinvinfo.clMoveItem.siUnique, pclCM->CR[id], &returnval) == false)
								{
									bsuccessswitch = false;
								}
							}

							if ( bsuccessswitch == false )
							{
								ShowMessageForItemEquipFail( returnval );
								break;
							}
						}

						if(topos == PERSONITEM_WEAPON1 || topos == PERSONITEM_WEAPON2)
						{							

							returnval = 0;

							//KHY - 1023 - �Ѿ� ȭ�� ���ѻ�� ����. 
							if( m_pDialog[ NPERSONALSHOP_DLG ] )
							{
								TCHAR* pTitle = GetTxtFromMgr(1074);
								TCHAR* pText = GetTxtFromMgr(7215);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
								
								break;
							}
							//cyj ChcekUseWeaponSkill �ι�° ���ڿ� �ű������ �ֵ��� ����
							//if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &pclCM->CR[id]->pclCI->clCharItem.clItem[0], &returnval)== false)
							if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &clinvinfo.clMoveItem, &returnval)== false)
							{
								TCHAR skillname[128];
								if(pclSkillManager->GetSkillName(returnval, skillname) == true)
								{
									TCHAR* pTitle = GetTxtFromMgr(1076);
									TCHAR* pText = GetTxtFromMgr(1077);


									m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText, skillname);
								}
								break;
							}
						}


						// ������ �������� ��ġ�� ������ ���� ��û�Ѵ�.
						cltMoveItemInfo clmoveitem(LOWORD(clinvinfo.si32lParam), HIWORD(clinvinfo.si32lParam));
						cltMsg clMsg(GAMEMSG_REQUEST_ITEMCHANGE,
							sizeof(cltMoveItemInfo), (BYTE*)&clmoveitem);

						SendMsgToServer((sPacketHeader*)&clMsg);
					}
				}
				break;
			case INV_ADD_ITEM:
				{
					SI16 frompos		= clinvinfo.si32lParam;
					SI16 fromunique		= clinvinfo.si16lParam2;
					SI16 topos			= clinvinfo.si32lParam1;
					cltItem clitem; 
					clitem.Set(&clinvinfo.clMoveItem);

					//--------------------------------------------------------
					// ������ �ƴϸ� ������ �� ����. 
					//--------------------------------------------------------
					cltItemInfo* pcliteminfo = pclItemManager->FindItemInfo(fromunique);
					if(pcliteminfo)
					{
						if(pcliteminfo->siType != ITEMTYPE_SCROLL)
						{
							PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
							TCHAR* pTitle = GetTxtFromMgr(1052);
							TCHAR* pText = GetTxtFromMgr(1053);


							m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							break;
						}
					}
					else
					{
						break;
					}

					//------------------------------------------------------
					// ����� obj�� �ƴϸ� �ȵȴ�.
					//------------------------------------------------------
					SI64 atb = pclItemManager->GetItemAtb(clitem.siUnique);
					if(clitem.siUnique && (atb & ITEMATB_OBJECT) == 0)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1052);
						TCHAR* pText = GetTxtFromMgr(1054);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						break;
					}

					//-----------------------------------------------------
					// ����� �������� �ּҰ��̻��̾�� �Ѵ�. 
					//-----------------------------------------------------
					if((SI32)clitem.clItemCommon.clCommonInfo.uiDurability <= pcliteminfo->siScrollDecDuration)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1052);
						TCHAR* pText = GetTxtFromMgr(1055);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						break;
					}


					cltGameMsgRequest_Enchant cladd(frompos, fromunique, topos, &clitem);

					cltMsg clMsg(GAMEMSG_REQUEST_ENCHANT, sizeof(cladd), (BYTE*)&cladd);
					SendMsgToServer((sPacketHeader*)&clMsg);

				}
				break;

			case INV_DROP_ITEM:
				{

					// �������� ������ ���� �õ��� �ߴ�. 
					bDropTrySwitch = true;

					SI32 pos = clinvinfo.si32lParam;
					cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ];

					if(pclMapManager->pclCurrentMap->IsInMapArea(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY()) == false)
					{
						TCHAR* pText = GetTxtFromMgr(1056);


						pclMessage->SetMsg(pText);
					}
					if(pclMapManager->pclCurrentMap->IsColl(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY(), BLOCK_DEEPWATER|BLOCK_SHALLOWWATER))
					{
						TCHAR* pText = GetTxtFromMgr(1057);


						pclMessage->SetMsg(pText);
					}
					else
					{
						// ������ ��� �ı� �׽�Ʈ 
						if ( IsCountrySwitch(Switch_DestroyDropItem) )
						{

							cltClient *pclclient = (cltClient*)pclClient;
							pclclient->CreateInterface( NDESTROYITEM_DLG );	
							((NDestroyItemDlg*)pclclient->m_pDialog[NDESTROYITEM_DLG])->SetDropItem(clinvinfo.si32lParam, clinvinfo.clMoveItem );
						}
						else
						{
							if (pclitem->IsBelonging(pclItemManager))
							{
								// �ͼӾ������� �ı��ϵ��� ��û�Ѵ�.
								cltGameMsgRequest_InvDrop cldrop(clinvinfo.si32lParam, &clinvinfo.clMoveItem);

								cltMsg clMsg(GAMEMSG_REQUEST_BELONGITEM_DESTROY, sizeof(cldrop), (BYTE*)&cldrop);

								SendMsgToServer((sPacketHeader*)&clMsg);
							}
							else
							{
								// ���Ӽ����� ����ϵ��� ��û�Ѵ�. 
								cltGameMsgRequest_InvDrop cldrop(clinvinfo.si32lParam, &clinvinfo.clMoveItem);

								cltMsg clMsg(GAMEMSG_REQUEST_INVDROP, sizeof(cldrop), (BYTE*)&cldrop);

								SendMsgToServer((sPacketHeader*)&clMsg);
							}
						}
						
					}

				}
				break;

			case INV_CANCELLATIONSEALINGUP_ITEM:
				{
					SI32 pos = clinvinfo.si32lParam;
					cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ];

					//----------------------------------------
					// �к��� Ǯ ���������� Ȯ���Ѵ�. 
					//----------------------------------------
					if(pclitem->siUnique <= 0)
					{
						break;
					}

					if(pclitem->IsSealingUp(pclItemManager) == false)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						break;
					}

					//--------------------------------------
					// �к����� ȿ������ ����. (����ȿ�������� ���) 
					//--------------------------------------
					if(pclitem)
					{
						pclItemManager->PlaySound(pclitem->siUnique, ITEMSOUND_REPAIR);
					}

					// ���Ӽ����� �����ϵ��� ��û�Ѵ�. 
					cltGameMsgRequest_Inv_CancellationSealingUp clcancell(clinvinfo.si32lParam, pclitem);
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CANCELLATIONSEALINGUP,	sizeof(clcancell), (BYTE*)&clcancell);
					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;

			case INV_REPAIR_ITEM:
				{
					SI32 pos = clinvinfo.si32lParam;
					cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ];

					//----------------------------------------
					// ������ �ʿ��� ���������� Ȯ���Ѵ�. 
					//----------------------------------------
					if(pclitem->siUnique <= 0)
					{
						break;
					}

					if(pclitem->CanRepair(pclItemManager) == false)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1058);
						TCHAR* pText = GetTxtFromMgr(1059);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						break;
					}

					if(pclitem->GetMaxDurability(pclItemManager) == pclitem->GetDurability())
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1058);
						TCHAR* pText = GetTxtFromMgr(1060);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						break;
					}

					if(pclitem->GetMaxDurability(pclItemManager) <= MIN_DUR_FOR_REPAIR)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1058);
						TCHAR* pText = GetTxtFromMgr(1061);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText,MIN_DUR_FOR_REPAIR);
						break;
					}


					//--------------------------------------
					// ������ ���� ȿ������ ����. 
					//--------------------------------------
					if(pclitem)
					{
						pclItemManager->PlaySound(pclitem->siUnique, ITEMSOUND_REPAIR);
					}

					// ���Ӽ����� �����ϵ��� ��û�Ѵ�. 
					cltGameMsgRequest_InvRepair clrepair(clinvinfo.si32lParam, pclitem);

					cltMsg clMsg(GAMEMSG_REQUEST_INVREPAIR,	sizeof(clrepair), (BYTE*)&clrepair);
					SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			case INV_MOVE_ITEM:// �κ��丮���� ������ �̵� 
				{

					SI32 topos					= HIWORD(clinvinfo.si32lParam);
					SI32 siCurrentSummonIndex	= SELECTED_HUMAN;
					SI32 siGetKind				= 0;

					// ���â���� �̵�
					if ( (PERSONITEM_HELMET <= topos) && (MAX_SHAPE_ITEM > topos) )
					{
						// ���â������ �̵��̶�� ���� ����Ұ����� üũ�Ѵ�
						siCurrentSummonIndex = ((CNEquipWindow*)m_pDialog[ NNEWEQUIPWINDOW_DLG ])->m_siCurrentSummonIndex;

						// �ε����� ��ȿ���� �˻�
						if ( (SELECTED_HUMAN > siCurrentSummonIndex) && (MAX_SUMMON_OWN >= siCurrentSummonIndex) )
						{
							break;
						}
					}
					
					// ���� ��� ���� Kind ��������
					if ( SELECTED_HUMAN == siCurrentSummonIndex )
					{
						siGetKind = pclCM->CR[1]->GetKind();
					}
					else
					{
						siGetKind = pclCM->CR[1]->pclCI->clSummonInfo.GetSummon( siCurrentSummonIndex )->siKind;
					}


					if ( pclItemManager->CheckProperItemPos(&clinvinfo.clMoveItem, topos, siGetKind) == TRUE )
					{
						
						SI16 siItemUnique			= clinvinfo.clMoveItem.siUnique;
						SI32 type					= clinvinfo.clMoveItem.GetType(pclItemManager);
						SI32 returnval				= 0;
						bool bsuccessswitch			= true;

						// ���â���� �̵�
						if ( (PERSONITEM_HELMET <= topos) && (MAX_SHAPE_ITEM > topos) )
						{
							// ����϶�
							if ( SELECTED_HUMAN == siCurrentSummonIndex )
							{
								if ( pclItemManager->CheckCondition(siItemUnique, pclCM->CR[id], &returnval) == false )
								{
									bsuccessswitch = false;
								}
							}
							// ��ȯ�� �϶�
							else 
							{
								// ��ȯ���� ���� ������ ��ġ�� ��� �ƴ϶��
								if ( false == pclItemManager->IsCanEquipItemPosForSummon( topos, siItemUnique ) )
								{
									bsuccessswitch = false;
								}
								// ��ȯ���� ���� ������ ��ġ�� �������̶�� ���������� ���� ��������
								else
								{
									cltSummon* pclsummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siCurrentSummonIndex);
									if ( NULL == pclsummon )
									{
										break;
									}
									
									if ( pclsummon->siStatus != SUMMON_STATUS_TAKEOUT )
									{
										returnval		= ITEMEQUIP_FAIL_NOTTAKEOUTSTATUS;
										bsuccessswitch	= false;
									}

									cltItem* pclitemlist = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonEquipItemList( siCurrentSummonIndex );
									if ( NULL == pclitemlist )
									{
										break;
									}

									if ( false == pclItemManager->CheckConditionForSummon( pclCM->CR[id], siItemUnique, pclsummon, pclitemlist, &returnval) )
									{
										bsuccessswitch = false;
									}
								}
							}

							if ( bsuccessswitch == false )
							{
								ShowMessageForItemEquipFail( returnval );
								break;
							}
						}

						if(topos == PERSONITEM_WEAPON1 || topos == PERSONITEM_WEAPON2)
						{							

							returnval = 0;

							//KHY - 1023 - �Ѿ� ȭ�� ���ѻ�� ����. 
							if( m_pDialog[ NPERSONALSHOP_DLG ] )
							{
								TCHAR* pTitle = GetTxtFromMgr(1074);
								TCHAR* pText = GetTxtFromMgr(7215);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
								
								break;
							}
							//cyj ChcekUseWeaponSkill �ι�° ���ڿ� �ű������ �ֵ��� ����
							//if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &pclCM->CR[id]->pclCI->clCharItem.clItem[0], &returnval)== false)
							if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &clinvinfo.clMoveItem, &returnval)== false)
							{
								TCHAR skillname[128];
								if(pclSkillManager->GetSkillName(returnval, skillname) == true)
								{
									TCHAR* pTitle = GetTxtFromMgr(1076);
									TCHAR* pText = GetTxtFromMgr(1077);


									m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText, skillname);
								}
								break;
							}
						}

						// ������ �������� ��ġ�� ������ ���� ��û�Ѵ�.
						UI16 uiFrom	= LOWORD(clinvinfo.si32lParam);
						UI16 uiTo	= HIWORD(clinvinfo.si32lParam);
						
						// ������� �������
						if ( SELECTED_HUMAN == siCurrentSummonIndex )
						{
								cltMoveItemInfo clMoveItem( uiFrom, uiTo );
								cltMsg clMsg( GAMEMSG_REQUEST_ITEMMOVE, sizeof(cltMoveItemInfo), (BYTE*)&clMoveItem );
								SendMsgToServer((sPacketHeader*)&clMsg);
						}
						// ������� ��ȯ����
						else
						{
							cltGameMsgRequest_SummonPushItem clSummonPushItemInfo( siCurrentSummonIndex, uiFrom, uiTo );
							cltMsg clMsg( GAMEMSG_REQUEST_SUMMONPUSHITEM, sizeof(cltGameMsgRequest_SummonPushItem), (BYTE*)&clSummonPushItemInfo );
							SendMsgToServer((sPacketHeader*)&clMsg);
						}
					}
				}
				break;

			case INV_USE_ITEM:
				{
					SI32 pos = clinvinfo.si32lParam;

					cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ];

					SI32 returnval = 0;
					if(pclCM->CR[id]->CanUseItem(*pclitem, &returnval , pos) == false)
					{
						switch(returnval)
						{
						case CANUSEITEM_ERROR_INVALID:
							{
								/*
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1079);


								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
								*/
							}
							break;
						case CANUSEITEM_ERROR_DEADCHAR:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1080);


								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOSKILLPOINT:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1081);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOTFITCOND:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1082);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_ALREADYMAXSKILL:
							{

								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1083);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NEEDPARENTSKILL:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1084);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);							break;
							}
							break;
						case CANUSEITEM_ERROR_LIMITSKILLLEVEL:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1085);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOUSEABLE:
							{
								TCHAR* pText = GetTxtFromMgr(1086);
								//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
								if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
								{
									pclMessage->SetPersonalMsg(pText);
								}
								else
								{
									pclMessage->SetMsg(pText);
								}
							}
							break;
						case CANUSEITEM_ERROR_NOUSE_THISPLACE:
							{
								TCHAR* pText = GetTxtFromMgr(6451);
								
								pclMessage->SetMsg(pText);
							}
							break;
						case CANUSEITEM_ERROR_NOT_ENOUGH_GET_TREASUR:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(30215);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOMOREUSE:
							{
								TCHAR* pTitle = GetTxtFromMgr(5608);
								TCHAR* pText = GetTxtFromMgr(5609);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOCOUNTRY:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(5568);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOHORSE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1087);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NEEDLEVEL:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1088);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOMORE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1089);


								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_SUMMON_NOMORE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1090);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOPROPERFISHAREA:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1091);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOMORE_DIGEST:
							{
 								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(6048);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOMORE_DESEASE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(6050);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						//KHY - 1001 - ��µ��� 5���� ���� ����.	
						case CANUSEITEM_ERROR_OVERMAXHORSE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1618);
								TCHAR* pText = GetTxtFromMgr(7202);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_RIDEHORSEUSEITEM:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(7208);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_CANTOVERSLOT:
							{
								TCHAR* pTitle = GetTxtFromMgr(449);
								TCHAR* pText = GetTxtFromMgr(8772);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_TICKETOVERDATE:
							{
								TCHAR* pTitle = GetTxtFromMgr(449);
								TCHAR* pText = GetTxtFromMgr(8773);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_BEFOREUSE_SAMEITEM:
							{
								TCHAR* pText = GetTxtFromMgr(9830);

								pclMessage->SetMsg(pText);
							}
							break;
						case CANUSEITEM_ERROR_CANNOTUSETYPEGORSE_SAMEITEM:
							{
								TCHAR* pText = GetTxtFromMgr(9831);

								pclMessage->SetMsg(pText);
							}
							break;
							// �ν������� ��� �ϰ�� ����Ҽ� �����ϴ�.
						case CANUSEITEM_ERROR_CANNOTUSEPREMIUMITEM:
							{
								TCHAR* pText = GetTxtFromMgr(9851);

								pclMessage->SetMsg(pText);
							}
							break;

						case CANUSEITEM_ERROR_NOTMARRIED:
							{
								TCHAR* pText = GetTxtFromMgr( 30049 );

								pclMessage->SetMsg(pText);
							}
							break;

						case CANUSEITEM_ERROR_CANNOT_SAMEMAP:
							{
								TCHAR* pText = GetTxtFromMgr( 30050 );

								pclMessage->SetMsg(pText);
							}
							break;

						case CANUSEITEM_ERROR_ALREADY_MAX_LOVELEVEL:
							{
								TCHAR* pText = GetTxtFromMgr( 30051 );

								pclMessage->SetMsg(pText);
							}
							break;

						case CANUSEITEM_ERROR_CAN_NOT_USETIME:
							{
								TCHAR* pText = GetTxtFromMgr( 30052 );

								pclMessage->SetMsg(pText);
							}
							break;
						case CANUSEITEM_ERROR_CANNOT_USE_COOKIE_NO_OVER_TIME:// ���� ��Ű �� �ð��� �ȵƴ� �ؽ�Ʈ ���߰�.
							{
								TCHAR* pText = GetTxtFromMgr( 30264 );

								pclMessage->SetMsg(pText);
							}
							break;

						case CANUSEITEM_ERROR_SOULGUARD_NOMORE:
							{
								TCHAR* pText = GetTxtFromMgr( 30245 );

								pclMessage->SetMsg(pText);
							}
							break;
						case CANUSEITEM_ERROR_SKILL_BOOK_SUB_MAGIC_FULL:
							{
								/*TCHAR* pText = GetTxtFromMgr( 15612 );
								pclMessage->SetMsg(pText);*/
		
								TCHAR* pTitle = GetTxtFromMgr(5614);
								TCHAR* pText = GetTxtFromMgr(15612);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_SKILL_BOOK: 
							{
								
							}
							break;
						case CANUSEITEM_ERROR_BATTLEROYALMAP: 
							{

							}
							break;
						default:
							MsgBox(TEXT("fds83nfd"), TEXT("F334fdf:%d"), returnval);
							break;
						}

						break;
					}

					//--------------------------------------
					// ������ ��� ȿ������ ����. 
					//--------------------------------------
					if(pclitem)
					{
						pclItemManager->PlaySound(pclitem->siUnique, ITEMSOUND_USE);
					}


					SI32 itemunique = pclitem->siUnique;
					SI32 ref		= pclItemManager->FindItemRefFromUnique(itemunique);
					if(ref)
					{

						SI32 itemtype	= pclitem->GetType(pclItemManager);
						if(itemtype >= 0)
						{
							if(pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_CANUSEITEM))
							{
								// ������ ������ ��� ��û�� ������. 
								cltItemUseInfo clitemuse( pos,	itemunique);

								cltMsg clMsg(GAMEMSG_REQUEST_USEITEM, sizeof(cltItemUseInfo), (BYTE*)&clitemuse);

								SendMsgToServer((sPacketHeader*)&clMsg);
							}
						}

					}
				}
				break;


			default:
				MsgBox(TEXT("fds8y"), TEXT("fd9j:%d"), clinvinfo.si16Message);
			}
		}
	}



	if( m_pDialog[ NNEWEQUIPWINDOW_DLG ] && ((CNEquipWindow*)m_pDialog[ NNEWEQUIPWINDOW_DLG ])->Pop(&clinvinfo))
	{
		SI32 id = 1;
		if(pclCM->IsAlive(id) == TRUE)
		{
			switch(clinvinfo.si16Message)
			{
				// ������ ��� ��ģ��. 
			case INV_CHANGE_ITEM:
				{					

					SI32 topos = HIWORD(clinvinfo.si32lParam);
					if(pclItemManager->CheckProperItemPos(&clinvinfo.clMoveItem, topos, pclCM->CR[1]->GetKind()) == TRUE)							
					{

						SI32 type = clinvinfo.clMoveItem.GetType(pclItemManager);
						SI32 returnval	= 0;
						bool bsuccessswitch = true;

						if ( topos < PERSONITEM_INV0 ) //|| topos >= PERSONITEM_SUMMON1EQUIP0)
						{
							if(topos < PERSONITEM_INV0)
							{
								if(pclItemManager->CheckCondition(clinvinfo.clMoveItem.siUnique, pclCM->CR[id], &returnval) == false)
								{
									bsuccessswitch = false;
								}

							}
	
							if(bsuccessswitch == false)
							{
								ShowMessageForItemEquipFail( returnval );
								break;
							}
						}

						if(topos == PERSONITEM_WEAPON1 || topos == PERSONITEM_WEAPON2)
						{							

							returnval = 0;
							//cyj ChcekUseWeaponSkill �ι�° ���ڿ� �ű������ �ֵ��� ����
							//if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &pclCM->CR[id]->pclCI->clCharItem.clItem[0], &returnval)== false)
							if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &clinvinfo.clMoveItem, &returnval)== false)
							{
								TCHAR skillname[128];
								if(pclSkillManager->GetSkillName(returnval, skillname) == true)
								{
									TCHAR* pTitle = GetTxtFromMgr(1076);
									TCHAR* pText = GetTxtFromMgr(1077);


									m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText, skillname);
								}
								break;
							}
						}


						// ������ �������� ��ġ�� ������ ���� ��û�Ѵ�.
						cltMoveItemInfo clmoveitem(LOWORD(clinvinfo.si32lParam), HIWORD(clinvinfo.si32lParam));
						cltMsg clMsg(GAMEMSG_REQUEST_ITEMCHANGE,
							sizeof(cltMoveItemInfo), (BYTE*)&clmoveitem);

						SendMsgToServer((sPacketHeader*)&clMsg);
					}
				}
				break;
			case INV_ADD_ITEM:
				{
					SI16 frompos		= clinvinfo.si32lParam;
					SI16 fromunique		= clinvinfo.si16lParam2;
					SI16 topos			= clinvinfo.si32lParam1;
					cltItem clitem; 
					clitem.Set(&clinvinfo.clMoveItem);

					//--------------------------------------------------------
					// ������ �ƴϸ� ������ �� ����. 
					//--------------------------------------------------------
					cltItemInfo* pcliteminfo = pclItemManager->FindItemInfo(fromunique);
					if(pcliteminfo)
					{
						if(pcliteminfo->siType != ITEMTYPE_SCROLL)
						{
							PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
							TCHAR* pTitle = GetTxtFromMgr(1052);
							TCHAR* pText = GetTxtFromMgr(1053);


							m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							break;
						}
					}
					else
					{
						break;
					}

					//------------------------------------------------------
					// ����� obj�� �ƴϸ� �ȵȴ�.
					//------------------------------------------------------
					SI64 atb = pclItemManager->GetItemAtb(clitem.siUnique);
					if(clitem.siUnique && (atb & ITEMATB_OBJECT) == 0)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pTitle = GetTxtFromMgr(1052);
						TCHAR* pText = GetTxtFromMgr(1054);


						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						break;
					}

					//-----------------------------------------------------
					// ����� �������� �ּҰ��̻��̾�� �Ѵ�. 
					//-----------------------------------------------------
					/*						if((SI32)clitem.clItemCommon.clCommonInfo.uiDurability <= pcliteminfo->siScrollDecDuration)
					{
					PushEffect(EFFECT_FAILURE, 0, 0);
					TCHAR* pTitle = GetTxtFromMgr(1052);
					TCHAR* pText = GetTxtFromMgr(1055);


					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					break;
					}*/



					//SI32 AddItemnum=1;
					//cltGameMsgRequest_Enchant cladd(frompos, fromunique,AddItemnum, topos, &clitem);

					//cltMsg clMsg(GAMEMSG_REQUEST_ENCHANT, sizeof(cladd), (char*)&cladd);
					//SendMsgToServer((char*)&clMsg);

				}
				break;

			case INV_DROP_ITEM:
				{

					// �������� ������ ���� �õ��� �ߴ�. 
					bDropTrySwitch = true;

					SI32 pos = clinvinfo.si32lParam;
					cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ];



					if(pclMapManager->pclCurrentMap->IsInMapArea(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY()) == false)
					{
						TCHAR* pText = GetTxtFromMgr(1056);


						pclMessage->SetMsg(pText);
					}
					if(pclMapManager->pclCurrentMap->IsColl(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY(), BLOCK_DEEPWATER|BLOCK_SHALLOWWATER))
					{
						TCHAR* pText = GetTxtFromMgr(1057);


						pclMessage->SetMsg(pText);
					}
					else
					{
						if (pclitem->IsBelonging(pclItemManager))
						{
							// �ͼӾ������� �ı��ϵ��� ��û�Ѵ�.
							cltGameMsgRequest_InvDrop cldrop(clinvinfo.si32lParam, &clinvinfo.clMoveItem);

							cltMsg clMsg(GAMEMSG_REQUEST_BELONGITEM_DESTROY, sizeof(cldrop), (BYTE*)&cldrop);

							SendMsgToServer((sPacketHeader*)&clMsg);
						}
						else
						{
							// ���Ӽ����� ����ϵ��� ��û�Ѵ�. 
							cltGameMsgRequest_InvDrop cldrop(clinvinfo.si32lParam, &clinvinfo.clMoveItem);

							cltMsg clMsg(GAMEMSG_REQUEST_INVDROP, sizeof(cldrop), (BYTE*)&cldrop);

							SendMsgToServer((sPacketHeader*)&clMsg);
						}
					}

				}
				break;
			case INV_CANCELLATIONSEALINGUP_ITEM:
				{
					SI32 pos = clinvinfo.si32lParam;
					cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ];

					//----------------------------------------
					// ������ �ʿ��� ���������� Ȯ���Ѵ�. 
					//----------------------------------------
					if(pclitem->siUnique <= 0)
					{
						break;
					}

					if(pclitem->IsSealingUp(pclItemManager) == false)
					{
						PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						break;
					}

					//--------------------------------------
					// ������ ���� ȿ������ ����. 
					//--------------------------------------
					if(pclitem)
					{
						pclItemManager->PlaySound(pclitem->siUnique, ITEMSOUND_REPAIR);
					}

					// ���Ӽ����� �����ϵ��� ��û�Ѵ�. 
					cltGameMsgRequest_Inv_CancellationSealingUp clcancell(clinvinfo.si32lParam, pclitem);
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CANCELLATIONSEALINGUP,	sizeof(clcancell), (BYTE*)&clcancell);
					SendMsgToServer((sPacketHeader*) &clMsg);
				}
				break;

			case INV_MOVE_ITEM:
				{
					UI16 siFromPos				= LOWORD(clinvinfo.si32lParam);
					SI32 topos					= HIWORD(clinvinfo.si32lParam);
					SI32 siCurrentSummonIndex	= SELECTED_HUMAN;
					SI32 siGetKind				= 0;

					
					// ���â���� �̵�
					if ( ((PERSONITEM_HELMET <= topos) && (MAX_SHAPE_ITEM > topos)) || ((PERSONITEM_HELMET <= siFromPos) && (MAX_SHAPE_ITEM > siFromPos)) )
					{
						// ���â������ �̵��̶�� ���� ����Ұ����� üũ�Ѵ�
						siCurrentSummonIndex = ((CNEquipWindow*)m_pDialog[ NNEWEQUIPWINDOW_DLG ])->m_siCurrentSummonIndex;

						// �ε����� ��ȿ���� �˻�
						if ( (SELECTED_HUMAN > siCurrentSummonIndex) && (MAX_SUMMON_OWN >= siCurrentSummonIndex) )
						{
							break;
						}
					}
					

					// ���� ��� ���� Kind ��������
					if ( SELECTED_HUMAN == siCurrentSummonIndex )
					{
						siGetKind = pclCM->CR[1]->GetKind();
					}
					else
					{
						siGetKind = pclCM->CR[1]->pclCI->clSummonInfo.GetSummon( siCurrentSummonIndex )->siKind;
					}

					if ( pclItemManager->CheckProperItemPos(&clinvinfo.clMoveItem, topos, siGetKind) == TRUE )
					{
						SI16		siItemUnique	= clinvinfo.clMoveItem.siUnique;
						SI32		type			= clinvinfo.clMoveItem.GetType(pclItemManager);
						SI32		returnval		= 0;
						bool		bsuccessswitch	= true;

						cltSummon*	pclsummon		= NULL;

						if ( SELECTED_HUMAN != siCurrentSummonIndex )
						{
							pclsummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siCurrentSummonIndex);
							if ( NULL == pclsummon )
							{
								break;
							}

							if ( pclsummon->siStatus != SUMMON_STATUS_TAKEOUT )
							{
								returnval		= ITEMEQUIP_FAIL_NOTTAKEOUTSTATUS;
								bsuccessswitch	= false;
							}
						}

						// ���â���� �̵�
						if ( (true == bsuccessswitch) && (PERSONITEM_HELMET <= topos) && (MAX_SHAPE_ITEM > topos) )
						{
							// ����϶�
							if ( SELECTED_HUMAN == siCurrentSummonIndex )
							{
								if ( pclItemManager->CheckCondition(siItemUnique, pclCM->CR[id], &returnval) == false )
								{
									bsuccessswitch = false;
								}
							}
							// ��ȯ�� �϶�
							else 
							{
								// ��ȯ���� ���� ������ ��ġ�� ��� �ƴ϶��
								if ( false == pclItemManager->IsCanEquipItemPosForSummon( topos, siItemUnique ) )
								{
									bsuccessswitch = false;
								}
								// ��ȯ���� ���� ������ ��ġ�� �������̶�� ���������� ���� ��������
								else
								{
									cltItem* pclitemlist = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonEquipItemList( siCurrentSummonIndex );
									if ( NULL == pclitemlist )
									{
										break;
									}

									if ( false == pclItemManager->CheckConditionForSummon( pclCM->CR[id], siItemUnique, pclsummon, pclitemlist, &returnval) )
									{
										bsuccessswitch = false;
									}
								}
							}
						}


						if ( bsuccessswitch == false )
						{
							ShowMessageForItemEquipFail( returnval );
							break;
						}


						if(topos == PERSONITEM_WEAPON1 || topos == PERSONITEM_WEAPON2)
						{							

							returnval = 0;
							//cyj ChcekUseWeaponSkill �ι�° ���ڿ� �ű������ �ֵ��� ����
							//if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &pclCM->CR[id]->pclCI->clCharItem.clItem[0], &returnval)== false)
							if(pclCM->CR[id]->pclCI->clCharSkill.ChcekUseWeaponSkill(type, &clinvinfo.clMoveItem, &returnval)== false)
							{
								TCHAR skillname[128];
								if(pclSkillManager->GetSkillName(returnval, skillname) == true)
								{
									TCHAR* pTitle = GetTxtFromMgr(1076);
									TCHAR* pText = GetTxtFromMgr(1077);


									m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText, skillname);
								}
								break;
							}
						}

						// ������ �������� ��ġ�� ������ ���� ��û�Ѵ�.
						UI16 uiFrom	= LOWORD(clinvinfo.si32lParam);
						UI16 uiTo	= HIWORD(clinvinfo.si32lParam);

						// ������� �������
						if ( -1 == siCurrentSummonIndex )
						{
							cltMoveItemInfo clMoveItem( uiFrom, uiTo );
							cltMsg clMsg( GAMEMSG_REQUEST_ITEMMOVE, sizeof(cltMoveItemInfo), (BYTE*)&clMoveItem );
							SendMsgToServer((sPacketHeader*)&clMsg);
						}
						// ��ȯ������ �������
						else
						{
							if ( (PERSONITEM_HELMET <= uiTo) && (MAX_SHAPE_ITEM > uiTo) )
							{
								cltGameMsgRequest_SummonPushItem clSummonPushItemInfo( siCurrentSummonIndex, uiFrom, uiTo );
								cltMsg clMsg( GAMEMSG_REQUEST_SUMMONPUSHITEM, sizeof(cltGameMsgRequest_SummonPushItem), (BYTE*)&clSummonPushItemInfo );
								SendMsgToServer((sPacketHeader*)&clMsg);
							}
							else
							{
								cltGameMsgRequest_SummonPopItem clSummonPopItemInfo( siCurrentSummonIndex, uiFrom, uiTo );
								cltMsg clMsg( GAMEMSG_REQUEST_SUMMONPOPITEM, sizeof(cltGameMsgRequest_SummonPopItem), (BYTE*)&clSummonPopItemInfo );
								SendMsgToServer((sPacketHeader*)&clMsg);
							}
						}
					}
				}
				break;
			case INV_USE_ITEM:
				{
					SI32 pos = clinvinfo.si32lParam;

					cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ];

					SI32 returnval = 0;
					if(pclCM->CR[id]->CanUseItem(*pclitem, &returnval, pos) == false)
					{
						switch(returnval)
						{
						case CANUSEITEM_ERROR_INVALID:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1079);


								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_DEADCHAR:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1080);


								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOSKILLPOINT:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1081);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOTFITCOND:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1082);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_ALREADYMAXSKILL:
							{

								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1083);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NEEDPARENTSKILL:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1084);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);							break;
							}
							break;
						case CANUSEITEM_ERROR_LIMITSKILLLEVEL:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1085);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOUSEABLE:
							{
								TCHAR* pText = GetTxtFromMgr(1086);

								//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
								if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
								{
									pclMessage->SetPersonalMsg(pText);
								}
								else
								{
									pclMessage->SetMsg(pText);
								}
							}
							break;
						case CANUSEITEM_ERROR_NOMOREUSE:
							{
								TCHAR* pTitle = GetTxtFromMgr(5608);
								TCHAR* pText = GetTxtFromMgr(5609);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOCOUNTRY:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(5568);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOHORSE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1087);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NEEDLEVEL:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1088);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_NOMORE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1089);


								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_SUMMON_NOMORE:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1090);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}break;
						case CANUSEITEM_ERROR_CANTOVERSLOT:
							{
								TCHAR* pTitle = GetTxtFromMgr(449);
								TCHAR* pText = GetTxtFromMgr(8772);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
							
						case CANUSEITEM_ERROR_NOPROPERFISHAREA:
							{
								TCHAR* pTitle = GetTxtFromMgr(1078);
								TCHAR* pText = GetTxtFromMgr(1091);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						case CANUSEITEM_ERROR_TICKETOVERDATE:
							{
								TCHAR* pTitle = GetTxtFromMgr(449);
								TCHAR* pText = GetTxtFromMgr(8773);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							break;
						default:
							MsgBox(TEXT("fds83nfd"), TEXT("F334fdf:%d"), returnval);
							break;
						}

						break;
					}

					//--------------------------------------
					// ������ ��� ȿ������ ����. 
					//--------------------------------------
					if(pclitem)
					{
						pclItemManager->PlaySound(pclitem->siUnique, ITEMSOUND_USE);
					}


					SI32 itemunique = pclitem->siUnique;
					SI32 ref		= pclItemManager->FindItemRefFromUnique(itemunique);
					if(ref)
					{

						SI32 itemtype	= pclitem->GetType(pclItemManager);
						if(itemtype >= 0)
						{
							if(pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_CANUSEITEM))
							{
								// ������ ������ ��� ��û�� ������. 
								cltItemUseInfo clitemuse( pos,	itemunique);

								cltMsg clMsg(GAMEMSG_REQUEST_USEITEM, sizeof(cltItemUseInfo), (BYTE*)&clitemuse);

								SendMsgToServer((sPacketHeader*)&clMsg);
							}
						}

					}
				}
				break;


			default:
				MsgBox(TEXT("fds8y"), TEXT("fd9j:%d"), clinvinfo.si16Message);
			}
		}
	}


	return FALSE;
}


// �����󿡼� ���콺�� ��ġ�� �������� üũ�Ѵ�. 
BOOL cltClient::GetMouseMode()
{
	int x=0, y=0;
	SI32 id = 1;

	SI32 mapx	= pclUnderMouseObject->MapX;
	SI32 mapy	= pclUnderMouseObject->MapY;

	// ���콺 ��带 �ʱ�ȭ�Ѵ�. 
	MouseMode=0;

	// ��ȿ�� �������� �ִ°�?
	if(pclMapManager->pclCurrentMap->IsInMapArea(mapx, mapy) == false)return FALSE;

	SI32 undermouseid = pclUnderMouseObject->GetUnderMouseID();

	// �������̽� ���� ���콺�� ��ġ�� ���, 
	if ( m_pInterfaceMgr->IsInInterfaceAraea() )
	{
		// ���콺 �Ʒ� HTML��ũ�� �ִ� ���
		if ( g_PromptMgr.HaveUrl() )
		{
			MouseMode|=MOUSEMODE_MOVE;
			pclCursor->SetCursor( GAME_CURSOR_LINK );
		}
		else
		{
			MouseMode|=MOUSEMODE_MOVE;
			pclCursor->SetCursor( GAME_CURSOR_NORMAL );
		}
	}
	else if(pclCM->IsValidID(id) && pclCM->IsAlive( undermouseid)  )
	{
		// ������ ���̸� , 
		if(pclCM->CR[id]->IsEnemy(undermouseid) ) 
		{
			MouseMode |= MOUSEMODE_ATTACK;

			// ����Ʈ Ŀ�� ����. 
			if(GetAsyncKeyState(VK_SHIFT) < -1)
			{
				pclCursor->SetCursor(GAME_CURSOR_SUMMON_ATTACK);
			}
			else
			{
				((cltCharClient*)pclCM->CR[undermouseid])->SetMouseOverSwitch(TRUE);
				pclCursor->SetCursor(GAME_CURSOR_ATTACK);
			}

		}
		// ��Ʈ��Ű ������ Į��
		else if( GetAsyncKeyState(VK_CONTROL) < -1) 
		{
		// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
		//if( IsWhereServiceArea(ConstSwitch_PVP) )
		if(siEnablePVP == 1)
			{
				if( pclCM->CR[id]->IsEnemyPCvsPC(undermouseid) )
				{
					MouseMode |= MOUSEMODE_ATTACK;
					((cltCharClient*)pclCM->CR[undermouseid])->SetMouseOverSwitch(TRUE);
					pclCursor->SetCursor(GAME_CURSOR_ATTACK);
				}
			}
		} 
		// ĳ����  NPC
		else if(IsNPC(pclCM->CR[undermouseid]->GetCharUnique())||IsInstanceNPC(pclCM->CR[undermouseid]->GetCharUnique()))
		{
			if( pclCM->CR[id]->IsEnemy(undermouseid) )
			{
				MouseMode |= MOUSEMODE_ATTACK;
				((cltCharClient*)pclCM->CR[undermouseid])->SetMouseOverSwitch(TRUE);
				pclCursor->SetCursor(GAME_CURSOR_ATTACK);
			}
			else
			{
				MouseMode |= MOUSEMODE_CHARNPC;

				pclCursor->SetCursor(GAME_CURSOR_NPC);
			}

		}
		else  
		{
			if( pclCM->CR[id]->IsEnemy(undermouseid) )
			{
				MouseMode |= MOUSEMODE_ATTACK;
				((cltCharClient*)pclCM->CR[undermouseid])->SetMouseOverSwitch(TRUE);
				pclCursor->SetCursor(GAME_CURSOR_ATTACK);
			}
			else
			{
				MouseMode |= MOUSEMODE_OTHERUSER;

				// ����Ʈ Ŀ�� ����. 
				pclCursor->SetCursor(GAME_CURSOR_NPC);
			}
		}
	}
	else
	{
		SI32 Temp1;
		// ���콺 �Ʒ� NPC�� �ִ� ���, 
		if(pclUnderMouseObject->GetNPCUnique())
		{
			MouseMode |= MOUSEMODE_SELECTNPC;

			pclCursor->SetCursor( GAME_CURSOR_NPC );
		}
		// ���콺 �Ʒ� �ǹ��� �ִ� ���, 
		else if(pclUnderMouseObject->GetStructureUnique())
		{
			MouseMode |= MOUSEMODE_SELECTSTRUCTURE;

			pclCursor->SetCursor( GAME_CURSOR_GATE );
		}
		else if(pclUnderMouseObject->GetItemUnique())
		{
			MouseMode |= MOUSEMODE_PICKUPITEM;

			pclCursor->SetCursor( GAME_CURSOR_GRAB );
		}
		// �޴��� �̵��� �ְ�, 
		else if(pclUnderMouseObject->GetGateUnique()) 
		{
			MouseMode|=MOUSEMODE_MOVE;  // ���콺�� �ִ� ������ �� �����̴�. 

			pclCursor->SetCursor( GAME_CURSOR_GATE );
		}
		// ������� ���콺�� ��� �ִ� ���̶��, 
		else if(pclUnderMouseObject->siTileAtb & MOUSETILEATB_FARM) 
		{
			MouseMode|=MOUSEMODE_FARM;  // ��� ���� �����̴�.

			pclCursor->SetCursor( GAME_CURSOR_FARM );
		}
		else if(pclCM->CR[1]->CanMine(mapx, mapy, &Temp1))
		{
			MouseMode|=MOUSEMODE_MINE;  // ä�� ���� �����̴�.

			pclCursor->SetCursor( GAME_CURSOR_MINE );
		}
		else if(pclUnderMouseObject->GetVillageUnique()) 
		{
			MouseMode|=MOUSEMODE_MOVE;  // ���콺�� �ִ� ������ �� �����̴�. 

			pclCursor->SetCursor( GAME_CURSOR_GATE );
		}
		// ���콺 �Ʒ� å���� �ִ� ���, 
		else if(pclUnderMouseObject->siDeskUnique)
		{
			MouseMode |= MOUSEMODE_DESK;

			pclCursor->SetCursor( GAME_CURSOR_NPC );
		}
		else 
		{
			MouseMode|=MOUSEMODE_MOVE;  // ���콺�� �ִ� ������ �� �����̴�. 

			// ����Ʈ Ŀ���� ����
			if( pclCursor->GetCursorState() != GAME_CURSOR_CLICK ) {
				pclCursor->SetCursor( GAME_CURSOR_NORMAL );
			}
		}
	}


	return TRUE;
}


// �޴� �Էµ��� ó���Ѵ�. 
void cltClient::OperateMenu()
{


}

BOOL cltClient::SetMousePos(SI32* psix, SI32* psiy)
{
	SI32 orgx, orgy ;

	orgx	= *psix;
	orgy	= *psiy;

	if(pclToolBar)
	{
		*psiy = orgy - pclToolBar->GetToolBarYsize();
	}
	else 
		*psiy = orgy;

	return TRUE;
}

bool cltClient::OperateAutoDoubleLeftOrder()
{

	if(MouseMode&MOUSEMODE_SELECTSTRUCTURE)
	{        
		// ���. 
		if(pclUnderMouseObject->GetStructureUnique() == CITYHALL_UNIQUE)
		{
			if( m_pDialog[ NCITYHALL_DLG ] == NULL ) CreateInterface( NCITYHALL_DLG ); 
		}

		// ����. 
		else if(pclUnderMouseObject->GetStructureUnique() == BANK_UNIQUE)
		{
			if( m_pDialog[ NBANK_DLG ] == NULL ) CreateInterface( NBANK_DLG ); 
		}
		// ����. 
		else if(pclUnderMouseObject->GetStructureUnique() == STOCK_UNIQUE)
		{
			if( m_pDialog[ NSTOCK_DLG ] == NULL ) CreateInterface( NSTOCK_DLG ); 
		}
		// ����. 
		else if(pclUnderMouseObject->GetStructureUnique() == MARKET_UNIQUE)
		{
			// ���� 3���� ���ָ� �̿��� �� �ִ�. 
			if(pclCM->IsAlive(1) && pclCM->CR[1]->pclCI->clIP.GetLevel() >= 3)
			{
				if( m_pDialog[ NMARKET_DLG ] == NULL ) CreateInterface( NMARKET_DLG ); 

			}
			else
			{
				TCHAR* pTitle = GetTxtFromMgr(1093);
				TCHAR* pText = GetTxtFromMgr(1094);

				m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			}
		}

		else if(pclUnderMouseObject->GetStructureUnique() == HOUSE_UNIQUE)
		{
			if( m_pDialog[ NHOUSE_DLG ] == NULL ) CreateInterface( NHOUSE_DLG ); 	

		}
		// ������
		else if(pclUnderMouseObject->GetStructureUnique() == HUNT_UNIQUE)
		{
			if( m_pDialog[ NHUNT_DLG ] == NULL ) CreateInterface( NHUNT_DLG ); 
		}
		// ����
		else if(pclUnderMouseObject->GetStructureUnique() == POSTOFFICE_UNIQUE)
		{
			if( m_pDialog[ NPOSTOFFICE_DLG ] == NULL ) CreateInterface( NPOSTOFFICE_DLG ); 
		}
		// �纹��
		else if(pclUnderMouseObject->GetStructureUnique() == HORSEMARKET_UNIQUE)
		{			
			if( m_pDialog[ NHORSEMARKET_DLG ] == NULL ) CreateInterface( NHORSEMARKET_DLG ); 	
		}

		// �Ű�
		else if(pclUnderMouseObject->GetStructureUnique() == REALESTATEMARKET_UNIQUE)
		{
			if( m_pDialog[ NREALESTATEMARKET_DLG ] == NULL ) CreateInterface( NREALESTATEMARKET_DLG ); 

		}


		// �忹��
		else if(pclUnderMouseObject->GetStructureUnique() == SUMMONMARKET_UNIQUE)
		{
			if(pclSummonMarketManager)
			{

				if( m_pDialog[ NSUMMONMARKET_DLG ] == NULL ) CreateInterface( NSUMMONMARKET_DLG ); 

				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_OPEN_HORSE")),0,0);
			}
		}
		// ����
		else if(pclUnderMouseObject->GetStructureUnique() == LAND_UNIQUE)
		{
			if( m_pDialog[ NLAND_DLG ] == NULL ) CreateInterface( NLAND_DLG ); 			

		}

		// ���ڽ�
		else if(pclUnderMouseObject->GetStructureUnique() == FEAST_UNIQUE)
		{			//CreateStrDlg(0, (cltStructureMngBasic*)pclFeastManager, IDD_DIALOG_BANK, StaticFeastDlgProc);
			if( m_pDialog[ NFEAST_DLG ] == NULL ) CreateInterface( NFEAST_DLG ); 
		}

		// �񺯻�
		else if(pclUnderMouseObject->GetStructureUnique() == SUMMONHEROMARKET_UNIQUE)
		{
			//CreateStrDlg(0, (cltStructureMngBasic*)pclFeastManager, IDD_DIALOG_BANK, StaticFeastDlgProc);
			if( m_pDialog[ NSUMMONHEROMARKET_DLG ] == NULL ) CreateInterface( NSUMMONHEROMARKET_DLG ); 
		}

		// ����
		else if(pclUnderMouseObject->GetStructureUnique() == MINE_UNIQUE)
		{
			if( m_pDialog[ NMINE_DLG ] == NULL ) CreateInterface( NMINE_DLG ); 

		}

		// �����
		else if(pclUnderMouseObject->GetStructureUnique() == GUILD_UNIQUE)
		{
			
			//if(	siServiceArea == ConstServiceArea_Japan	)
			//{
			//	TCHAR* pTitle = GetTxtFromMgr(6584);
			//	TCHAR* pText = GetTxtFromMgr(6655);

			//	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );

			//	return true;
			//}	

			if( m_pDialog[ NGUILDSTR_DLG ] == NULL ) CreateInterface( NGUILDSTR_DLG ); 	

		}
		//[����] ���ո���
		else if(NEWMARKET_UNIQUE == pclUnderMouseObject->GetStructureUnique())
		{
			if( m_pDialog[ NNEWMARKET_DLG ] == NULL ) CreateInterface( NNEWMARKET_DLG  ); 
		}

		else
		{
			TCHAR buffer[256];
			StringCchPrintf(buffer, 256, TEXT("NotProperStructureUnique:%d"), pclUnderMouseObject->GetStructureUnique());
			pclMessage->SetMsg(buffer);
		}

	}


	else if(MouseMode & MOUSEMODE_DESK)
	{
		//	[��ȣ] ����Ŭ���� ������ â Ȱ��ȭ
		if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(9468) )		// ������
		{
			CreateInterface( NWEDDINGCEREMONY_MENU_DLG );
		}
	}

	return true;
}
// ���콺 ��ư�� ���� �ڵ� ����� ó���Ѵ�. (������ ���콺 ��ư)
bool cltClient::OperateAutoRightOrder()
{
	cltCharClient* pclchar = pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return false;
	}

	// �޴��� ������ �ְ� ���콺�� �� ���� ������, 
	if(MouseMode & MOUSEMODE_ATTACK)
	{	

		bool CanNotAttSantaRaccoon = false;

		SI32 underMouseID = pclUnderMouseObject->GetUnderMouseID();
		if( pclCM->CR[underMouseID]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SANTARACCOON_ZIQ")) )
		{
			if( (pclchar->pclCI->clIP.GetLevel() < 10) || (pclchar->pclCI->clIP.GetLevel() > 40) )
			{				
				CanNotAttSantaRaccoon = true;
			}
		}

		
		// �����̾� ���� ���� �����߿� ������ ���Ѵ�
		if (pclchar->bPersonalShopSwitch && pclchar->bPremiumPersonalShop)
		{
			if (m_pDialog[NCOMMONMSG_DLG] == NULL)
			{
				CreateInterface( NCOMMONMSG_DLG );
			}
			((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_CLOSE_PREMIUMSHOP);
		}
		else if( CanNotAttSantaRaccoon == true )
		{
			TCHAR* pTitle = GetTxtFromMgr(512);
			TCHAR* pText = GetTxtFromMgr(6656);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,  pText);
		}
		else
		{
			bool bShowErrorMessage	= false;
			SI32 returnval			= 0;

			SI32 summonid = pclchar->GetSummonID() ;
			if( GetAsyncKeyState(VK_SHIFT) <-1 ||
				(pclCM->IsAlive(summonid) && pclchar->siSelectedCharIndex == pclCM->CR[summonid]->GetSummonIndex()) )
			{
				if( pclCM->IsValidID(summonid) && pclCM->CR[summonid]->GetCurrentMagic() &&
					(MAGIC_CASTTYPE_ACTIVE == pclCM->CR[summonid]->GetCurrentMagicCastType()) )
				{
					clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclUnderMouseObject->GetUnderMouseID());
					siSelectedOrder			= ORDER_MAGIC_SUMMON;
					siSelectedOrderPara1	= pclCM->CR[summonid]->GetCurrentMagic();
					siSelectedOrderPara2	= 0;
				}
			}
			else
			{
				// ���� ������ Magic���ְ� Active Magic �̶�� �߻縦 �Ѵ�.
				if ( pclchar->GetCurrentMagic() && (MAGIC_CASTTYPE_ACTIVE == pclCM->CR[1]->GetCurrentMagicCastType()) )
				{
					bool pvp = false;
					// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
					//if( IsWhereServiceArea(ConstSwitch_PVP) )
					if(siEnablePVP == 1)
					{
						if( GetAsyncKeyState(VK_CONTROL) <-1 )
						{
							pvp = true;
							siSelectedOrderPara2	= 1;
						}
						else
							siSelectedOrderPara2	= 0;
					}
					else
						siSelectedOrderPara2	= 0;
                    
					if ( pclchar->CanMagic(pclUnderMouseObject->GetUnderMouseID(), pclchar->GetCurrentMagic(), &returnval, pvp) == true)
					{
						clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclUnderMouseObject->GetUnderMouseID());
						siSelectedOrder			= ORDER_MAGIC;
						siSelectedOrderPara1	= pclchar->GetCurrentMagic();
					}
					else
					{
						bShowErrorMessage = true;
					}
				}	// if (pclCM->CR[1]->GetCurrentMagic() && (MAGIC_CASTTYPE_ACTIVE == pclCM->CR[1]->GetCurrentMagicCastType()) ) ����
				else if ( pclchar->GetCurrentMagic() && (MAGIC_CASTTYPE_BUF == pclchar->GetCurrentMagicCastType()) )
				{
					if ( true == pclchar->CanMagicBuf(pclchar->GetCurrentMagic(), &returnval) )
					{
						clMouseObject.Set( pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclchar->GetID() );
						siSelectedOrder			= ORDER_MAGIC;
						siSelectedOrderPara1	= pclchar->GetCurrentMagic();
						siSelectedOrderPara2	= 0;
					}
					else
					{
						bShowErrorMessage = true;
					}
				}

				if ( true == bShowErrorMessage)
				{
					if(returnval == CANUSEMAGIC_ERROR_NEEDMANA)
					{
						TCHAR* pText = GetTxtFromMgr(495);

						pclMessage->SetMsg(pText);

						PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_NO_MANA")), 0, 0);
					}
					else if(returnval == CANUSEMAGIC_ERROR_FARDISTANCE)
					{
						TCHAR* pText = GetTxtFromMgr(496);

						pclMessage->SetMsg(pText);
					}
					else if(returnval == CANUSEMAGIC_ERROR_NOTENOUGHSKILL)
					{
						TCHAR* pText = GetTxtFromMgr(1092);

						pclMessage->SetMsg(pText);
					}
				}
			}
		}
	}
	else if(MouseMode & MOUSEMODE_OTHERUSER)
	{
		SI32 id = pclUnderMouseObject->GetUnderMouseID();
		if (pclCM->CR[1]->siSelectedCharIndex == -1 )
		{
			if( pclCM->IsValidID(id) )
			{ 
				if ( g_SoundOnOffDlg.m_bRightMouseMentAllow )
				{   
					/*
					if ( m_pDialog[ NRIGHTMOUSEMENU_DLG ] == NULL )
					{
						CreateInterface( NRIGHTMOUSEMENU_DLG  );
					}

					if ( m_pDialog[ NRIGHTMOUSEMENU_DLG ] )
					{
						((CNRightMouseMenuDlg *)m_pDialog[ NRIGHTMOUSEMENU_DLG ])->Set( id, pclCM->CR[id]->GetCharUnique(),GameMouseX-10, GameMouseY-40, pclCM->CR[id]->bPersonalShopSwitch?1:0 );
					}*/				

					if( pclUnderMouseObject->GetUnderUserCnt() > 1 )
					{
						if ( m_pDialog[ NRIGHTMOUSEUSERLIST_DLG ] == NULL )
						{
							CreateInterface(NRIGHTMOUSEUSERLIST_DLG);
						}

						if( m_pDialog[ NRIGHTMOUSEUSERLIST_DLG ] )
						{
  							((NRightMouseUserListDlg*)m_pDialog[ NRIGHTMOUSEUSERLIST_DLG ])->SetUnderUserList(TRUE);
  							m_pDialog[ NRIGHTMOUSEUSERLIST_DLG ]->Show(true);					                            
							m_pDialog[ NRIGHTMOUSEUSERLIST_DLG ]->MovePos(GameMouseX - 5,GameMouseY - m_pDialog[ NRIGHTMOUSEUSERLIST_DLG ]->GetHeight());
						}						
					}
					// ������ ���콺 ���� ����Ʈ�� �Ⱥ��������� ������ ���콺 �����޴��� �����ش�.
					else if( m_pDialog[ NRIGHTMOUSEUSERLIST_DLG] != NULL && m_pDialog[ NRIGHTMOUSEUSERLIST_DLG ]->IsShow() == false  )
					{
						if ( m_pDialog[ NRIGHTMOUSEMENU_DLG ] == NULL )
						{
							CreateInterface( NRIGHTMOUSEMENU_DLG  );
						}

						if ( m_pDialog[ NRIGHTMOUSEMENU_DLG ] )
						{
							SI16 siMode = 0;
							if( pclCM->CR[id]->bPersonalShopSwitch )
							{
								cltCharClient* pChar = pclCM->GetCharClient(id)	;	
								if(pChar != NULL )
								{
									if(pChar->siShopMode == PSHOP_MODE_MAKEITEM ||
										pChar->siShopMode == PSHOP_MODE_MAKEITEM_WANT)
									{
										siMode |= RIGHTMOUSEMENU_ONLY_MAKESHOP;
									}
									else
									{
										siMode |= RIGHTMOUSEMENU_ADD_PERSONSHOP;
									}

								}
							}
							if( IsCountrySwitch( Switch_NewDurability ) )
							{
								if( pclCM->CR[id]->bRepairShopSwitch )				siMode |= RIGHTMOUSEMENU_ADD_REPAIRSHOP;
							}

							if( IsCountrySwitch( Switch_IKillU ) )
							{
								siMode |= RIGHTMOUSEMENU_ADD_PVP;
							}

							((CNRightMouseMenuDlg *)m_pDialog[ NRIGHTMOUSEMENU_DLG ])->Set( id, pclCM->CR[id]->GetCharUnique(),GameMouseX-10, GameMouseY-40, siMode );
						}
					}		
					
				}
			}
		}
		else
		{
			// ��ȯ����� ������ ����Ѵ�.
			SI32 summonid = pclCM->CR[1]->GetSummonID() ;
			if( pclCM->IsValidID(summonid) && pclCM->CR[summonid]->GetCurrentMagic() &&
				(MAGIC_CASTTYPE_ACTIVE == pclCM->CR[summonid]->GetCurrentMagicCastType()) )
			{
				clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclUnderMouseObject->GetUnderMouseID());
				siSelectedOrder			= ORDER_MAGIC_SUMMON;
				siSelectedOrderPara1	= pclCM->CR[summonid]->GetCurrentMagic();
				siSelectedOrderPara2	= 0;
			}
		}
	}
	else if(MouseMode&MOUSEMODE_SELECTSTRUCTURE)
	{
		// ���. 
		if(pclUnderMouseObject->GetStructureUnique() == 1)
		{

			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				if( m_pDialog[ NCITYHALL_DLG ] == NULL ) CreateInterface( NCITYHALL_DLG ); 
				else m_pDialog[ NCITYHALL_DLG ]->DeleteDialog();

			//}
		}
		// ����. 
		else if(pclUnderMouseObject->GetStructureUnique() == 10)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				if( m_pDialog[ NBANK_DLG ] == NULL ) CreateInterface( NBANK_DLG ); 
				else m_pDialog[ NBANK_DLG ]->DeleteDialog();
			//}
		}
		// ����. 
		else if(pclUnderMouseObject->GetStructureUnique() == 20)
		{

			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{

				if( m_pDialog[ NSTOCK_DLG ] == NULL ) CreateInterface( NSTOCK_DLG ); 
				else m_pDialog[ NSTOCK_DLG ]->DeleteDialog();
			//}


		}
		// ����. 
		else if(pclUnderMouseObject->GetStructureUnique() == 40)
		{
			// ���� 3���� ���ָ� �̿��� �� �ִ�. 
			if(pclCM->IsAlive(1) && pclCM->CR[1]->pclCI->clIP.GetLevel() >= 3)
			{

				//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
				//{
					if( m_pDialog[ NMARKET_DLG ] == NULL ) CreateInterface( NMARKET_DLG ); 
					else m_pDialog[ NMARKET_DLG ]->DeleteDialog();
				//}
			}
			else
			{
				TCHAR* pTitle = GetTxtFromMgr(1093);
				TCHAR* pText = GetTxtFromMgr(1094);


				m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			}
		}
		// ����
		else if(pclUnderMouseObject->GetStructureUnique() == 50)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{

				if( m_pDialog[ NHOUSE_DLG ] == NULL ) CreateInterface( NHOUSE_DLG ); 
				else m_pDialog[ NHOUSE_DLG ]->DeleteDialog();
			//}
		}
		// ������
		else if(pclUnderMouseObject->GetStructureUnique() == 60)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				if( m_pDialog[ NHUNT_DLG ] == NULL ) CreateInterface( NHUNT_DLG ); 
				else m_pDialog[ NHUNT_DLG ]->DeleteDialog();
			//}
		}
		// ����
		else if(pclUnderMouseObject->GetStructureUnique() == 70)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{

				if( m_pDialog[ NPOSTOFFICE_DLG ] == NULL ) CreateInterface( NPOSTOFFICE_DLG ); 
				else m_pDialog[ NPOSTOFFICE_DLG ]->DeleteDialog();
			//}
		}
		// �纹��
		else if(pclUnderMouseObject->GetStructureUnique() == 90)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				if( m_pDialog[ NHORSEMARKET_DLG ] == NULL ) CreateInterface( NHORSEMARKET_DLG ); 
				else m_pDialog[ NHORSEMARKET_DLG ]->DeleteDialog();
			//}
		}

		// �Ű�
		else if(pclUnderMouseObject->GetStructureUnique() == 100)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				if( m_pDialog[ NREALESTATEMARKET_DLG ] == NULL ) CreateInterface( NREALESTATEMARKET_DLG ); 
				else m_pDialog[ NREALESTATEMARKET_DLG ]->DeleteDialog();
			//}
		}


		// �忹��
		else if(pclUnderMouseObject->GetStructureUnique() == 110)
		{
			if(pclSummonMarketManager)
			{
				//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
				//{
					if( m_pDialog[ NSUMMONMARKET_DLG ] == NULL ) CreateInterface( NSUMMONMARKET_DLG ); 
					else m_pDialog[ NSUMMONMARKET_DLG ]->DeleteDialog();
				//} 
			}
		}
		// ����
		else if(pclUnderMouseObject->GetStructureUnique() == 130)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				if( m_pDialog[ NLAND_DLG ] == NULL ) CreateInterface( NLAND_DLG ); 
				else m_pDialog[ NLAND_DLG ]->DeleteDialog();
			//}
		}

		// ���ڽ�
		else if(pclUnderMouseObject->GetStructureUnique() == 140)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				//CreateStrDlg(0, (cltStructureMngBasic*)pclFeastManager, IDD_DIALOG_BANK, StaticFeastDlgProc);
				if( m_pDialog[ NFEAST_DLG ] == NULL ) CreateInterface( NFEAST_DLG ); 
				else m_pDialog[ NFEAST_DLG ]->DeleteDialog();
			//}
		}

		// �񺯻�
		else if(pclUnderMouseObject->GetStructureUnique() == 150)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				//CreateStrDlg(0, (cltStructureMngBasic*)pclFeastManager, IDD_DIALOG_BANK, StaticFeastDlgProc);
				if( m_pDialog[ NSUMMONHEROMARKET_DLG ] == NULL ) CreateInterface( NSUMMONHEROMARKET_DLG ); 
				else m_pDialog[ NSUMMONHEROMARKET_DLG ]->DeleteDialog();

			//}
		}

		// ����
		else if(pclUnderMouseObject->GetStructureUnique() == 160)
		{
			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{
				if( m_pDialog[ NMINE_DLG ] == NULL ) CreateInterface( NMINE_DLG ); 
				else m_pDialog[ NMINE_DLG ]->DeleteDialog();
			//}
		}

		// �����
		else if(pclUnderMouseObject->GetStructureUnique() == 170)
		{
			//if(	siServiceArea == ConstServiceArea_Japan	)
			//{
			//	TCHAR* pTitle = GetTxtFromMgr(6584);
			//	TCHAR* pText = GetTxtFromMgr(6655);

			//	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );

			//	return true;
			//}


			//if( g_SoundOnOffDlg.m_bFullScreenMode || true)
			//{				
				if( m_pDialog[ NGUILDSTR_DLG ] == NULL ) CreateInterface( NGUILDSTR_DLG ); 
				else m_pDialog[ NGUILDSTR_DLG ]->DeleteDialog();				
			//}
		}
		//[����] ���ո���
		else if(NEWMARKET_UNIQUE == pclUnderMouseObject->GetStructureUnique())
		{
			if( m_pDialog[ NNEWMARKET_DLG ] == NULL ) CreateInterface( NNEWMARKET_DLG ); 
		}

		else
		{
			TCHAR buffer[256];
			StringCchPrintf(buffer, 256, TEXT("NotProperStructureUnique:%d"), pclUnderMouseObject->GetStructureUnique());
			pclMessage->SetMsg(buffer);
		}

	}
	else if(MouseMode & MOUSEMODE_DESK)
	{
#ifdef _DEBUG
		if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(30) ) // �����Ǽ�
		{
			CreateInterface(NBYUNGZO_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(31) ) // �����Ǽ�
		{
			CreateInterface(NGONGZO_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(32) ) // �����Ǽ�
		{
			CreateInterface(NHYUNGZOBASE_DLG);

		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(34) ) // ȣ���Ǽ�
		{
			if(g_SoundOnOffDlg.m_bFullScreenMode)
				CreateInterface( NHOZOBASE_DLG );
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(35) ) // �����Ǽ�
		{
			if(g_SoundOnOffDlg.m_bFullScreenMode)
				CreateInterface(NIZOBASE_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(39) )		  // ����
		{
			if(g_SoundOnOffDlg.m_bFullScreenMode)
				CreateInterface(NGOONZU_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(303) )		  // ���ŰԽ���
		{
			//if( pclClient->siServiceArea == ConstServiceArea_Japan )
			//	g_LoginNoticeDlg.Set( TEXT("http://www.kunshu.jp/vote/"), 800, 600 );
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(301) )		  // ���뱺��
		{
			//if( pclClient->siServiceArea == ConstServiceArea_Japan )
			//	g_LoginNoticeDlg.Set( TEXT("http://www.kunshu.jp/vote/monarch.aspx"), 800, 600 );
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(9468) )		// ������
		{
			CreateInterface( NWEDDINGCEREMONY_MENU_DLG );
		}
		
#else
	#ifdef _CHINA
	#else
		if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(30) ) // �����Ǽ�
		{
			CreateInterface(NBYUNGZO_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(31) ) // �����Ǽ�
		{
			CreateInterface(NGONGZO_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(32) ) // �����Ǽ�
		{
			CreateInterface(NHYUNGZOBASE_DLG);

		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(34) ) // ȣ���Ǽ�
		{
			if(g_SoundOnOffDlg.m_bFullScreenMode)
				CreateInterface( NHOZOBASE_DLG );
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(35) ) // �����Ǽ�
		{
			if(g_SoundOnOffDlg.m_bFullScreenMode)
				CreateInterface(NIZOBASE_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(39) )		  // ����
		{
			if(g_SoundOnOffDlg.m_bFullScreenMode)
				CreateInterface(NGOONZU_DLG);
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(303) )		  // ���ŰԽ���
		{
			//if( pclClient->siServiceArea == ConstServiceArea_Japan )
			//	g_LoginNoticeDlg.Set( TEXT("http://www.kunshu.jp/vote/"), 800, 600 );
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(301) )		  // ���뱺��
		{
			//if( pclClient->siServiceArea == ConstServiceArea_Japan )
			//	g_LoginNoticeDlg.Set( TEXT("http://www.kunshu.jp/vote/monarch.aspx"), 800, 600 );
		}
		else if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(9468) )		// ������
		{
			CreateInterface( NWEDDINGCEREMONY_MENU_DLG );
		}
	#endif
#endif
	}

	else if(MouseMode & MOUSEMODE_MOVE)
	{
		SI32 returnval			= 0;
		bool bShowErrorMessage	= false;

		if ( pclchar->GetCurrentMagic() && (MAGIC_CASTTYPE_BUF == pclchar->GetCurrentMagicCastType()) )
		{
			if ( true == pclchar->CanMagicBuf(pclchar->GetCurrentMagic(), &returnval) )
			{
				clMouseObject.Set( pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclchar->GetID() );
				siSelectedOrder			= ORDER_MAGIC;
				siSelectedOrderPara1	= pclchar->GetCurrentMagic();
				siSelectedOrderPara2	= 0;
			}
			else
			{
				bShowErrorMessage = true;
			}
		}

		if ( true == bShowErrorMessage)
		{
			if(returnval == CANUSEMAGIC_ERROR_NEEDMANA)
			{
				TCHAR* pText = GetTxtFromMgr(495);

				pclMessage->SetMsg(pText);

				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_NO_MANA")), 0, 0);
			}
			else if(returnval == CANUSEMAGIC_ERROR_FARDISTANCE)
			{
				TCHAR* pText = GetTxtFromMgr(496);

				pclMessage->SetMsg(pText);
			}
			else if(returnval == CANUSEMAGIC_ERROR_NOTENOUGHSKILL)
			{
				TCHAR* pText = GetTxtFromMgr(1092);

				pclMessage->SetMsg(pText);
			}
		}

	}
	// [����] �߷�Ÿ�ε��� �̺�Ʈ - Ư�� npc�鿡�� ���� �ֱ� �޴� 
	else if(MouseMode & MOUSEMODE_CHARNPC)
	{
		if( NULL != m_pclValentineEventMgr)
		{
			SI32 siTargetCharID = pclUnderMouseObject->GetUnderMouseID();

			cltCharClient *pclTargetNPC = pclCM->GetCharClient(siTargetCharID);
			if( NULL != pclTargetNPC)
			{
				if( true == m_pclValentineEventMgr->IsValentineNPC(pclTargetNPC->GetKind()))
				{
					((CValentineEventClientMgr*)m_pclValentineEventMgr)->ClickNPC(pclTargetNPC->GetCharUnique());
				}
			}
		}
	}
	return true;

}

// ���콺 ��ư�� ���� �ڵ� ����� ó���Ѵ�. (���� ���콺 ��ư)
bool cltClient::OperateAutoLeftOrder()
{
	bool bdoneswitch =false;

	if(bdoneswitch == false && pclCM->CR[1]->GetCurrentOrder() == ORDER_SITDOWN )
	{
		bdoneswitch = true;

		SI32 Direction = DecideDirection8( pclCM->CR[1]->GetX(), pclCM->CR[1]->GetY(), pclUnderMouseObject->MapX, pclUnderMouseObject->MapY );

		// ���� ���� ���¿����� ���� ���Ѵ�. - �ɾƼ� ȸ������ε� ������ �ʴ´�.
		//if(pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM) == false)
		{
			cltGameMsgRequest_SitDown clinfo( true, Direction );
			cltMsg clMsg(GAMEMSG_REQUEST_SITDOWN, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);
		}
	}

	if(bdoneswitch == false && (MouseMode&MOUSEMODE_CHARNPC))
	{
		SI32 id = pclUnderMouseObject->GetUnderMouseID();
		//SI32 tempcode = GetUniqueFromHash( TEXT("KIND_REVISENPC"));
		if(pclCM->IsValidID(id) && pclCM->CR[id]->IsAtb(ATB_ATTACK) == false)
		{

			bdoneswitch = true;

			// ���� ȿ������ �����Ѵ�. 
			SI32 siSelectEffect = pclCM->CR[id]->pclKI->clKIEffectInfo.GetRandomeSelectEffect();
			if( siSelectEffect > 0 )
			{
				PushEffect(siSelectEffect, 0, 0);
			}

			// ���� �Ǵ� �� ������ ���

			if(	pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_CHINAMERCHANT")) 
				//|| pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_JAPANMERCHANT")) 			
				//pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTBOW")) 
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTFOOD"))*/
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTSHOES"))*/
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTBELT"))*/
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTHEAL"))*/	
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTHARDWARE"))*/
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTRING"))*/
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTCLOTHES"))*/
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTHAT"))*/
				/*|| pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTNECKLACE"))*/
				)
			{

				CreateInterface( NFOREIGNMERCHANTBUYITEM_DLG );
				((CNForeignMerchantBuyItemDlg*)m_pDialog[ NFOREIGNMERCHANTBUYITEM_DLG ])->SetNormalItemBuyMode(pclCM->CR[id]->GetCharUnique());

				/*cyj ó������ ��־����� �Ǹ� â ��Ÿ������ ����
				CreateInterface( NFOREIGNMERCHANT_DLG );
				if( (CNForeignMerchantDlg*)m_pDialog[ NFOREIGNMERCHANT_DLG ] )
				((CNForeignMerchantDlg*)m_pDialog[ NFOREIGNMERCHANT_DLG ])->SetNPCCharUnique(pclCM->CR[id]->GetCharUnique());
				*/


				/*	if( g_SoundOnOffDlg.m_bFullScreenMode)
				{
				//m_pDialog[ NFOREIGNMERCHANT_DLG ]->SetData((SI32*)pclCM->CR[id]->GetCharUnique());
				CreateInterface( NFOREIGNMERCHANT_DLG );
				if( (CNForeignMerchantDlg*)m_pDialog[ NFOREIGNMERCHANT_DLG ] )
				((CNForeignMerchantDlg*)m_pDialog[ NFOREIGNMERCHANT_DLG ])->SetNPCCharUnique(pclCM->CR[id]->GetCharUnique());
				}
				else
				m_pForeignMerchantOpenDlg->Show( pclCM->CR[id]->GetCharUnique() );*/
			}
			// �ϸ�
			//else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_HAMEL"))  )
			//{
			//	//if(g_SoundOnOffDlg.m_bFullScreenMode)
			//	//{
			//	//CreateInterface( NTRADEMERCHANTHAMEL_DLG );
			//	//}
			//	//else
			//	//	m_pTradeMerchantHamelDlg->Show( id );
			//}
			// �������ε��̸�
			else if( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_JAPANTRADER")) )
			{
				if(g_SoundOnOffDlg.m_bFullScreenMode)
				{
					CreateInterface( NTRADEMERCHANT_DLG );
					if( m_pDialog[NTRADEMERCHANT_DLG] )
						((CNTradeMerchantDlg*) m_pDialog[NTRADEMERCHANT_DLG])->SetTradeMerChant(id);
				}
			}
			// �������̸�
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTHORSE")) )
			{
				if(g_SoundOnOffDlg.m_bFullScreenMode)
				{
					CreateInterface( NTRADEMERCHANTHORSE_DLG );
				}
			}
			// DailyQuest �̸�,
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_DAILYQUEST")))
			{
				//cyj 25�� �̻� ����Ʈ �޵���
				if ( pclCM->CR[1]->pclCI->clIP.GetLevel() >= 25 )
				{
					// �𺴰�
					CreateInterface( NDAILYQUEST_DLG );
				}
				else
				{
					TCHAR* pTitle = GetTxtFromMgr(5598);
					TCHAR* pText = GetTxtFromMgr(6027);
					TCHAR buf[256];

					StringCchPrintf(buf, 256, pText, 25);

					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buf );
					return false;
				}
			}
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_DAILYQUEST2")))
			{
				//���� 90��
				if ( pclCM->CR[1]->pclCI->clIP.GetLevel() >= 90 )
				{

					CreateInterface( NDAILYQUEST2_DLG );

				}
				else
				{
					TCHAR* pTitle = GetTxtFromMgr(512);//25���̻����� �Ǿ� ���� �ؽ� Ʈ ���� �ؾ���
					TCHAR* pText = GetTxtFromMgr(8073);
					TCHAR buf[256];

					StringCchPrintf(buf, 256, pText, 25);

					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buf );
					return false;
				}
			}
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_DAILYQUEST3")))
			{
				//���� 90��
				/*if ( pclCM->CR[1]->pclCI->clIP.GetLevel() >= 90 )
				{*/

					CreateInterface( NDAILYQUEST3_DLG );

				//}
				//else
				//{
				//	TCHAR* pTitle = GetTxtFromMgr(6073);//25���̻����� �Ǿ� ���� �ؽ� Ʈ ���� �ؾ���
				//	TCHAR* pText = GetTxtFromMgr(8073);
				//	TCHAR buf[256];

				//	StringCchPrintf(buf, 256, pText, 25);

				//	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buf );
				//	return false;
				//}
			}
			//���Ǻ� ����Ʈ���[2007.08.22 �ռ���]
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC1"))
				|| pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC2"))
				|| pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC3")))
			{
					CreateInterface( NHAPPYBEAN_DLG );				
			}			
			//ũ�������� �̺�Ʈ [07.11.20 �ռ���]
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_CHRISTMASTREE")))
			{
				//CreateInterface( NCHRISTMASEVENT_DLG );				
			}
			// ���̾�α� �ٲ���.
			//KHY - 1113 - ũ�������� �̺�Ʈ - ũ�������� Ʈ�� ����� ��������
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_CHRISTMASTREEBASE")))
			{
				CreateInterface( NCHRISTMASEVENT_DLG );				
			}			
			//KHY - 1113 - ũ�������� �̺�Ʈ -
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_CHRISTMASTREE1")))
			{
				// ũ�������� �̺�Ʈ�� ���� �귿���� �ٲ����.
				CreateInterface( NBUFF_ROULETTE_DLG );					
			}
			
			//[����] ������ ���� 1�ܰ� Ŭ��. => 2008-6-9
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_ROULETTESTATUEBASE")))
			{
				if (pclClient->IsCountrySwitch(Switch_Hero_Bronze_Statue)) 
				{			
					//CreateInterface( NBUFF_ROULETTE_DLG );	test
					CreateInterface( NCHRISTMASEVENT_DLG );	 	
				}
			}
			//[����] ������ ���� 2�ܰ� Ŭ�� . => 2008-6-9
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_ROULETTESTATUE")))
			{
				if (pclClient->IsCountrySwitch(Switch_Hero_Bronze_Statue)) 
				{			
					//CreateInterface( NCHRISTMASEVENT_DLG );	 	
					CreateInterface( NBUFF_ROULETTE_DLG );			
				}
			}
			// [���] ũ�������� �̺�Ʈ - ���縮�� �տ� Ʈ���� Ŭ��
			else if (pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE01"))
				|| pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE02")))
			{
				CreateInterface( NCHRISTMASEVENT_DLG );					
			}
			//	[��ȣ_BALLANCECRRENCY] ��ȭ�� ���� NPC Ŭ����
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_BALANCECURRENCY")))
			{
				if(pclClient->IsCountrySwitch(Switch_BalanceCurrency)) 
				{	
					cltMsg clMsg( GAMEMSG_REQUEST_BALANCECANUSECURRENCY, 0, 0);
					pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );


					//if(pclClient->m_pclBalanceCurrencyMgr->GetCanUseMoney() >= pclClient->m_pclBalanceCurrencyMgr->GetBuffCost())
					//	CreateInterface(NBALANCECURRENCY_DLG);			
					//else
					//{
					//	cltClient *pclclient = (cltClient*)pclClient;

					//	TCHAR *pTitle = GetTxtFromMgr(5662);
					//	TCHAR *pText = GetTxtFromMgr(10336);
					//	pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					//}

				}
			}

			//	[��ȣ_GAWIBAWIBO] ���������� npcŬ����
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_RACCOONTOWER_SRP")))
			{
				if(pclClient->IsCountrySwitch(Switch_GawiBawiBo) == true)
				{
					if(GetClientClass()->m_pDialog[NGAWIBAWIBO_DLG] == NULL)
						GetClientClass()->GetGawiBawiBoMgr()->StartGame();
				}
			}

			//[����] �ҷ��� �д� �⺻ Ŭ��
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_HALLOWEENBASE")))
			{
				if (pclClient->IsCountrySwitch(Switch_HalloweenEvent)) 
				{			
					CreateInterface( NCHRISTMASEVENT_DLG );	 	
				}
			}
			//[����] �ҷ��� �д� �ϼ��� Ŭ��
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_HALLOWEEN")))
			{
				if (pclClient->IsCountrySwitch(Switch_HalloweenEvent)) 
				{			
					CreateInterface( NCHARBUFF_ROULETTE_DLG );	// �ϴ� ����â�� ���µ�..�����ϳ�.....		
				}
			}
			// ���� �̼� ����Ʈ�� ���� �Ǵ� ���� ������ �ҷ��� ����ƮNPC�� �ִ�.
			else if( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_HALLOWEENPC")) )
			{
				if (pclClient->IsCountrySwitch(Switch_HalloweenEvent)) 
				{
					cltCharClient* pclchar = pclCM->GetCharClient(1);
					if(pclchar)
					{
						if( pclchar->clTransFormInfo.bTransFormMode == true ||
							pclchar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM ) == true )
						{
							if( pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique == 0 )
							{
								cltGameMsgRequest_MissionQuest_Start clMissionQuest_Start( MISSIONQUEST_UNIQUE_HOLLOWEEN );
								cltMsg clMsg( GAMEMSG_REQUEST_MISSIONQUEST_START, sizeof(cltGameMsgRequest_MissionQuest_Start), (BYTE*)&clMissionQuest_Start );
								pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
							}
						}
						else
						{
							NTCHARString128	kTitle(GetTxtFromMgr(8880));
							NTCHARString128 kText(GetTxtFromMgr(8877));

							m_pDialog[ NOTIFYMSG_DLG ]->SetText(kTitle, kText);
						}
					}
				}
			}
			else if( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_ANTIQUITY")) )	// �׽�Ʈ ������ npc�� �ҷ��� npc ���
			{
				if (pclClient->IsCountrySwitch(Switch_TreasureEvent)) 
				{
					if( pclEventTimeManager->InEventTime(TEXT("TreasureEvent"), &sTime) )
					{
						cltCharClient* pclchar = pclCM->GetCharClient(1);
						if(pclchar)
						{
							if( true == pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_EVENT_FINDTREASURE ) )
							{
								// ���� npc ��ǥ
								SI32 siMapX	=	pclUnderMouseObject->MapX	;
								SI32 siMapY	=	pclUnderMouseObject->MapY	;
								SI32 siID	=	pclUnderMouseObject->GetUnderMouseID()	;

								TCHAR* pNaner = (TCHAR*)pclCM->CR[siID]->pclCI->clBI.GetName()	;
								SI32 siNPC_CharUnique  = pclCM->CR[siID]->GetCharUnique()	;

								if( pclCM->CR[siID]->pclCI->clIP.Life  >  0  )
								{
									TCHAR* pNaner = (TCHAR*)pclCM->CR[siID]->pclCI->clBI.GetName()	;
									SI32 siNPC_CharUnique  = pclCM->CR[siID]->GetCharUnique()	;

									cltGameMsgRequest_TreasureEvent_Npc_Kill clTrasureNpcKill( siNPC_CharUnique );
									cltMsg clMsg( GAMEMSG_REQUEST_TREASUREEVENT_KILLNPC, sizeof(cltGameMsgRequest_TreasureEvent_Npc_Kill), (BYTE*)&clTrasureNpcKill );
									pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );

								}
							}
						}
					}					
				}
			}
			//[����] �����̺�Ʈ ���� ���� ����Ʈ. => 2008-6-27
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_EVENTGATE")))
			{
				cltMsg clMsg( GAMEMSG_REQUEST_SERVER_EVENT_BONUS_STAGE, 0, NULL );
				pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );					
			}

			// ���� ���� NPC
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_REVISENPC")))
			{

				CreateInterface( NCHANGE_DLG );
			}

			
			/*   // �念���� ���� �ʺ� ���� ����Ʈ npc �̴�
			// �念���̸�, 
			else if(pclCM->CR[id]->GetKind() == KIND_JANGYOUNGSIL)
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(( m_pDialog[ NNPCREPAIR_DLG  ])==NULL)
					{
						CreateInterface( NNPCREPAIR_DLG );
						((NcltNPCRepairManager*)m_pDialog[ NNPCREPAIR_DLG  ])->Create(pclCM->CR[id]->CharUnique);
					}
					else
					{
						((NcltNPCRepairManager*)m_pDialog[ NNPCREPAIR_DLG  ])->DeleteDialog();
					}
				}
			}*/
			// ��������, 
			else if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_WAITINGWOMAN")))
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(( m_pDialog[ NNPCTRADE1_DLG ])==NULL)
					{
						CreateInterface( NNPCTRADE1_DLG );
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->Show(pclCM->CR[id]->GetKind());
					} 

					else
					{
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->DeleteDialog(); 
					}
				}                                                                                                                                                                                                                                                                                               
			}
			// ���ĸ��Ļ��� �̶��
			else if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_MAGICALRACCOON_NPC")))
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(( m_pDialog[ NNPCTRADE1_DLG ])==NULL)
					{
						CreateInterface( NNPCTRADE1_DLG );
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->Show(pclCM->CR[id]->GetKind());
					} 

					else
					{
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->DeleteDialog(); 
					}
				}
			}
			// ���� NPC ���.
			else if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR1")) ||
				pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR2"))||
				pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR3"))||
				pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR4")))
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(( m_pDialog[ NNPCTRADE1_DLG ])==NULL)
					{
						CreateInterface( NNPCTRADE1_DLG );
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->Show(pclCM->CR[id]->GetKind());
					} 

					else
					{
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->DeleteDialog(); 
					}
				}
			}
			// �븸 ���� 1�ֳ� ��� NPC
			else if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_ANNIVERSARY")))
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(( m_pDialog[ NNPCTRADE1_DLG ])==NULL)
					{
						CreateInterface( NNPCTRADE1_DLG );
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->Show(pclCM->CR[id]->GetKind());
					} 

					else
					{
						((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG ])->DeleteDialog(); 
					}
				}
			}
			// ��ä�����,
			//else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_FANPRIEST")) )
			//{
			//	/*cyj ��ä���� ���̾�׷� ����
			//	//
			//	if ( g_SoundOnOffDlg.m_bFullScreenMode)
			//	{
			//	if(m_pDialog[ NFANPRIEST_DLG ]==NULL)
			//	{
			//	CreateInterface(NFANPRIEST_DLG);
			//	((CNFanPriestDlg*)m_pDialog[ NFANPRIEST_DLG ])->Set();
			//	}
			//	else
			//	{
			//	((CNFanPriestDlg*)m_pDialog[ NFANPRIEST_DLG ])->DeleteDialog();

			//	}
			//	}
			//	*/
			//}
			// Ȥ�θ������̸�, (ƾƾ NPC)
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_WENNYOLDMAN")) )
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(( m_pDialog[ NWENNYMAN_DLG ])==NULL)
					{
						CreateInterface( NWENNYMAN_DLG);
					}
				}
			}
			// ������NPC �̸�
			//cyj �ջ�� �߰�
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_BATTLEZONE")) )
			{
				CreateInterface(NPLAYMATCH_DLG);
			}
			// ȣ�����̸�(��ť�ŷ���)
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_CHINATRADER")) )
			{ 
				if ( true == IsCountrySwitch(Switch_Trade_Renewal) )
				{
					CreateInterface(NACUTRADEDLG_PARENT);
				}
				else
				{
					CreateInterface(NAQTRADEWINDOW_DLG);
				}
				
			}
			// �߸���Ű�̸� ����â
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_RUSSIATRADER")) )
			{ 
				CreateInterface(NTRADESERVERBASE_DLG);
			} 
			//(��õ�� NPC)
			else if (pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_RECOMMENDER")) )
			{
				CreateInterface(NRPBASE_DLG);
			}
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_GUYAJA")) )
			{
				CreateInterface(NMANUFACTURENPC_DLG);
			}	
			// �����̸�,
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_JANGGILSAN")))
			{
				if ( siServiceArea == ConstServiceArea_China )
				{
				}
				else
				{
					if ( pclCM->CR[1]->pclKI->siDefaultCountry == ConstServiceArea_China )
						return false ;
				}

				// ���� 10�̻����
				/*if( pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() <= 9)
				{
					TCHAR* pTitle = GetTxtFromMgr(5598);
					TCHAR* pText = GetTxtFromMgr(5599);
					TCHAR buf[256];

					StringCchPrintf(buf, 256, pText, 10);

					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buf );

					return false;
				}*/

				if ( !g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
					{
						CreateInterface( NNEWQUEST_DLG );

						if(m_pDialog[ NNEWQUEST_DLG ])
						{
							pclQuestManager->bNewQuseOpened = TRUE;
							((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
							((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
							((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
						}
					}
					else
						CreateInterface( NNEWQUEST_DLG );

				}
				else
				{
					if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
					{
						CreateInterface( NNEWQUEST_DLG );

						if(m_pDialog[ NNEWQUEST_DLG ])
						{
							pclQuestManager->bNewQuseOpened = TRUE;
							((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
							((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
							((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
						}
					}
					else
						CreateInterface( NNEWQUEST_DLG );

					//	((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->Show(KIND_JANGGILSAN);
				}
			}
			// �����̸�,
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_MUDANG")))
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					CreateInterface( NMUDANG_DLG );
				}
			}
			else if( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_PKMAPARBEIT"))
				)
			{
				// pvp ���̵�
				//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
				((cltClient*)pclClient)->CreateInterface( NPVPMAPGODLG );	// ����â
				//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
			}
			// [����] ��Ƽ��Ʈ. npc Ŭ���ϸ� ��Ƽ��Ʈ â �߰�. => 2008. 3. 21
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_ARTIFACTNPC")))
			{
				if ( m_pDialog[ARTIFACT_BASE_DLG] == NULL )
				{							
					CreateInterface( ARTIFACT_BASE_DLG );
				}

				if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
				{
					CreateInterface( NNEWQUEST_DLG );

					if(m_pDialog[ NNEWQUEST_DLG ])
					{
						pclQuestManager->bNewQuseOpened = TRUE;
						((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
						((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
						((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
					}
				}
				else
				{
					CreateInterface( NNEWQUEST_DLG );
				}
			}
			// [����] ��ƼȦ. npc Ŭ���ϸ� ��Ƽ��Ʈ â �߰�. => 2008. 3. 21
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_PARTYNPC")))
			{
				if ( m_pDialog[PARTYHALL_IN_BASE_DLG] == NULL )
				{							
					CreateInterface( PARTYHALL_IN_BASE_DLG );
				}
				else
				{
					DestroyInterface( m_pDialog[PARTYHALL_IN_BASE_DLG] );
				}
			}

			// ���� �輱��(���ڻ�㰡)
			else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_INVESTMENT")) )
			{
				//m_pInvestmentDlg->Set(pclCM->CR[id]->GetCharUnique());
				TCHAR buffer[1024] = TEXT("") ;
				TCHAR* pText1 = GetTxtFromMgr(1097);
				TCHAR* pText2 = GetTxtFromMgr(1098);
				TCHAR* pText3 = GetTxtFromMgr(1099);

				StringCchPrintf(buffer, 1024, pText1);

				if ( g_SoundOnOffDlg.m_bFullScreenMode )
				{
					if(( m_pDialog[ NNPCMENU_DLG  ])==NULL)
					{
						CreateInterface( NNPCMENU_DLG );
						((CNNPCMenuDlg*)m_pDialog[ NNPCMENU_DLG ])->CreateDlg(GetUniqueFromHash(TEXT("KIND_INVESTMENT")),pclCM->CR[id]->GetCharUnique(),
							pText2, pText3,true,true,buffer);
					}
					else
					{
						((CNNPCMenuDlg*)m_pDialog[ NNPCMENU_DLG ])->DeleteDialog();
					}
				}
			}
			// ���þƹ�������
			//else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_RUSSIATRADER")) )
			//{
			//	TCHAR buffer[1024] = TEXT("") ;
			//	TCHAR* pText1 = GetTxtFromMgr(1100);
			//	TCHAR* pText2 = GetTxtFromMgr(1101);
			//	TCHAR* pText3 = GetTxtFromMgr(1102);

			//	StringCchPrintf(buffer, 1024, pText1);


			//	if ( g_SoundOnOffDlg.m_bFullScreenMode )
			//	{
			//		if(( m_pDialog[ NNPCMENU_DLG  ])==NULL)
			//		{
			//			CreateInterface( NNPCMENU_DLG );
			//			((CNNPCMenuDlg*)m_pDialog[ NNPCMENU_DLG ])->CreateDlg(GetUniqueFromHash(TEXT("RUSSIATRADER")),id,
			//				pText2, pText3 ,true,true,buffer);
			//		}
			//		else
			//		{
			//			((CNNPCMenuDlg*)m_pDialog[ NNPCMENU_DLG ])->DeleteDialog();
			//		}


			//	}
			//}
			// ����ȣ�� ���
			else if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_WAITINGMAN2") ) )
			{

				if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
				{
					CreateInterface( NNEWQUEST_DLG );

					if(m_pDialog[ NNEWQUEST_DLG ])
					{
						pclQuestManager->bNewQuseOpened = TRUE;
						((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
						((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
						((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
					}
				}
				else
					CreateInterface( NNEWQUEST_DLG );

			}
			// ��ȯ�������̸�
			else if( pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_SUMMONMERCHANT") ) )
			{
				CreateInterface(NSUMMONUNITBUYNPC_DLG);
			}
			// ���� �̼����̸�
			/*else if( pclCM->CR[id]->GetKind() == KIND_EVENTNPC)
			{
			if( siServiceArea == ConstServiceArea_Korea)
			CreateInterface(NEVENT_DLG);
			else
			return false;
			}
			*/
			// õ�����̸�
			else if( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MERCHANTPOTTER")) )
			{
				if(g_SoundOnOffDlg.m_bFullScreenMode)
				{
					CreateInterface(NTRADEMERCHANTHIGHCLASS_DLG);
				}
			}
			// ���λ��̸�
			//else if( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_BOBUSANG")) )
			//{
			//	CreateInterface(NBOBUSANG_DLG);
			//}
			//else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_WANGCHO")) )
			//{
			//	CreateInterface(NBOSSMARKET_DLG);				
			//}
			// [����] ��������(�󷺽�)
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_ALEX")) )
			{
				CreateInterface(NHONGGILDONG_DLG);
			}
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_RACCOONLORD_NPC1")) ||
					  pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_RACCOONLORD_NPC2")) ||
					  pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_RACCOONLORD_NPC3")) )
			{
				cltClient* pclclient = (cltClient*)pclClient;

				SI32 siFieldIndex = pclCM->CR[id]->GetKind() - GetUniqueFromHash( TEXT("KIND_RACCOONLORD_NPC1"));

				cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(pclCM->CR[1]->GetMapIndex());
				BOOL bInField = FALSE;
				if(pclmap != NULL)
				{
					SI32 siColl = pclmap->CalcCollInfo(pclCM->CR[1]->GetX(), pclCM->CR[1]->GetY());
					if(siColl & BLOCK_EVENT4 || siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6)
					{
						bInField = TRUE;
					}
				}

				if(bInField == TRUE)
				{
					// �̺�Ʈ�� ����Ǿ ���̾�α׸� ����Ͽ� ���� �� �ִ�.
					if (pclclient->m_pDialog[NCOMMONMSG_DLG] == NULL)	{	pclclient->CreateInterface( NCOMMONMSG_DLG );	}

					switch(siFieldIndex)
					{
					case 0:	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_MOFUMOFU_LEAVE_FIELD1);	break;
					case 1:	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_MOFUMOFU_LEAVE_FIELD2);	break;
					case 2:	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_MOFUMOFU_LEAVE_FIELD3);	break;
					}
				}
				else
				{
					// ����� ���̾�α� ����
					if(	pclclient->siMofuMofuEvent_VilliageUnique > 0 &&		// ���� �̺�Ʈ�� �������̰�, �����ϴ� ������ �ֹ��̸�,
						pclClient->pclCM->CR[1]->pclCI->clBI.siHomeVillage == pclclient->siMofuMofuEvent_VilliageUnique )
					{
						if (pclclient->m_pDialog[NCOMMONMSG_DLG] == NULL)	{	pclclient->CreateInterface( NCOMMONMSG_DLG );	}

						switch(siFieldIndex)
						{
						case 0:	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_MOFUMOFU_ENTER_FIELD1);	break;
						case 1:	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_MOFUMOFU_ENTER_FIELD2);	break;
						case 2:	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_MOFUMOFU_ENTER_FIELD3);	break;
						}
					}
				}
			}
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_ZORRORACCOON_NPC")) )
			{
				cltClient* pclclient = (cltClient*)pclClient;

				if(true == pclclient->IsCountrySwitch(Switch_Event_MofuMofu))
				{
					pclclient->CreateInterface( NMOFUMOFULIST_DLG );
					((CNMofuMofuListDlg*)m_pDialog[NMOFUMOFULIST_DLG])->SetViewerMode();
				}
			}
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_TITLENPC")) )
			{
				((cltClient*)pclClient)->CreateInterface( NNAMINGQUESTLIST_DLG );

			}
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_REWARD")) ) //���� NPC 
			{
				((cltClient*)pclClient)->CreateInterface( NSYSTEMREWARDLIST_DLG );
				
			}
			// [����] ������ : �������� ������ �� �ִ��� ������ ������ Ȯ���ϱ�
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_PIRATESHIP_GATE")) )
			{
				cltMsg clMsg( GAMEMSG_REQUEST_PIRATESHIP_ENTERFIELD, 0, NULL );
				pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
			}
			//KHY - 1113 - ũ�������� �̺�Ʈ -  ����ͺ� �и� ����.
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_SANTAGATE")) )
			{
				//cltMsg clMsg( GAMEMSG_REQUEST_CHRISTMASEVET_ENTERFIELD, 0, NULL );
				//pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
				NTCHARString64	kTitle( GetTxtFromMgr( 4045 ) ); // �̺�Ʈ ����.
				NTCHARString128	kText( GetTxtFromMgr( 8929 ) );

				stMsgBox MsgBox;
				MsgBox.Set( m_pDialog[NOTIFYMSG_DLG], kTitle, kText, MSGBOX_TYPE_YESNO, 20 );
				SetMsgBox( &MsgBox, NULL, 0 );				
			}
			// [����] ���� : ���� ��ǥ�� �������� �̵���Ų��
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_POLLINGGATE")) )
			{
				cltMsg clMsg( GAMEMSG_REQUEST_WARPTOPOLLMAP, 0, NULL );
				pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
			}
			// [����] ���� : ��ǥ���� Ŭ���ߴٸ� ���� ��ǥ�� �����ϵ���
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_BALLOTBOX")) )
			{
				cltMsg clMsg( GAMEMSG_REQUEST_VOTEKINGAVAILABLE, 0, NULL );
				pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
			}
			// [����] ���� �̺�Ʈ : ���� �̺�Ʈ �δ� �κ���� �̵� ��û
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_SERVERGATE")) )
			{
				cltMsg clMsg( GAMEMSG_REQUEST_SERVER_EVENT_LOBBY_ENTERFIELD, 0, NULL );
				pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
			}
			// [����] ���� �̺�Ʈ : �����̺�Ʈ �������� �κ�� ���� ����Ʈ
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_ROBIGATE")) )
			{
				cltMsg clMsg( GAMEMSG_REQUEST_SERVER_EVENT_LOBBY_ENTERFIELD, 0, NULL );
				pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
			}
			// [����] ��ȥ �ý��� : �ַ�NPC
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_OFFICIATOR")) )
			{
				// ó������
			}
			//Switch_10MonthEvent_RacoonDodge
			//[����] �������ϱ� �̺�Ʈ
			else if ( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_MAGICALRACCOON_NPC2")) )
			{
				if(pclClient->IsCountrySwitch( Switch_10MonthEvent_RacoonDodge ) )
				{
					//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
					((cltClient*)pclClient)->CreateInterface( NRACOONDODGE_EVENT_DLG );	// ����â
					//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
				}
			}
			// [����] ���ο� ������ ���� NPC
			else if( pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_REPAIRMAN")) )
			{
				if( IsCountrySwitch(Switch_NewDurability) )
				{
					CreateInterface( NNEWNPCREPAIR_DLG );
				}
			}

			//�ν��Ͻ�����  ���� ���̾�α� + ���� ���� ���̾�α� ���� 2007.01.07 �ռ���
			
			else if(pclCM->CR[id]->pclKI->IsAtb(ATB_SYSTEMNPC))
			{
					if( pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_JANGGUMI")) || pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_ROYALGUARD") ) 
 						||	pclCM->CR[id]->GetKind() == GetUniqueFromHash( TEXT("KIND_WAITINGMAN") ) )
					{
						if( ((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->IsShow() )
							((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->Hide();

						if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
						{
							CreateInterface( NNEWQUEST_DLG );

							if(m_pDialog[ NNEWQUEST_DLG ])
							{
								pclQuestManager->bNewQuseOpened = TRUE;
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
							}
						}
						else
							CreateInterface( NNEWQUEST_DLG );
					}
					else if( pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_JANGILSAN")) || //pclCM->CR[id]->GetKind() == KIND_PRISONER ||  
						pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_BONGSAMI")) || pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_BONG")) ||
						pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_BONGTAGI")) || pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_BONGDAL")) || 
						pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_BONGSUNI")) || pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_JANGYOUNGSIL")) ) 
					{
						// 10�̻���� ������ ����Ʈ�� �Ѵ�
						/*if(pclCM->CR[1]->pclCI->clIP.GetLevel() <= 9 )
						{
							TCHAR* pTitle = GetTxtFromMgr(5598);
							TCHAR* pText = GetTxtFromMgr(5599);
							TCHAR buf[256];

							StringCchPrintf(buf, 256, pText, 10);

							m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buf );
							return false;
						}*/

						if( ((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->IsShow() )
							((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->Hide();

						if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
						{
							CreateInterface( NNEWQUEST_DLG );

							if(m_pDialog[ NNEWQUEST_DLG ])
							{
								pclQuestManager->bNewQuseOpened = TRUE;
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
							}
						}
						else
							CreateInterface( NNEWQUEST_DLG );
					}
					else if( pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_RUDOLPH")) )
					{
						bool bQuestRunning = false;

						cltPersonQuestUnitInfo* pclunit[4];
						pclunit[0] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MAKESANTAHAT];
						pclunit[1] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MAKECAKE];
						pclunit[2] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_PLAYCHRISTMAS];
						pclunit[3] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_PLAYCHRISTMASHIDDEN];

						if( pclunit[0]->siCurQuestUnique > 0 || pclunit[0]->siCurQuestStep > 0 )	bQuestRunning = true;
						if( pclunit[1]->siCurQuestUnique > 0 || pclunit[1]->siCurQuestStep > 0 )	bQuestRunning = true;
						if( pclunit[2]->siCurQuestUnique > 0 || pclunit[2]->siCurQuestStep > 0 )	bQuestRunning = true;
						if( pclunit[3]->siCurQuestUnique > 0 || pclunit[3]->siCurQuestStep > 0 )	bQuestRunning = true;

						if( bQuestRunning == true)
						{
							if(m_pDialog[ NNEWQUEST_DLG ] != NULL)
								CreateInterface( NNEWQUEST_DLG );

							if( ((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->IsShow() )
								((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->Hide();

							if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
							{
								CreateInterface( NNEWQUEST_DLG );

								if(m_pDialog[ NNEWQUEST_DLG ])
								{
									pclQuestManager->bNewQuseOpened = TRUE;
									((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
									((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
									((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
								}
							}
							else
								CreateInterface( NNEWQUEST_DLG );
						}
						else
						{
							((cltClient*)pclClient)->CreateInterface( NCHRISMASQUEST_DLG );
						}
					}

					//[��ȣ_PANG] �ε巹�� NPC
					else if( pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_PANG")) )
					{
						bool bQuestRunning = false;

						cltPersonQuestUnitInfo* pclunit[5];
						pclunit[0] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_DRESS];
						pclunit[1] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_HAT];
						pclunit[2] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_MENTAL];
						pclunit[3] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_RING];
						pclunit[4] = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_AVATAR_NECK];

						if( pclunit[0]->siCurQuestUnique > 0 || pclunit[0]->siCurQuestStep > 0 )	bQuestRunning = true;
						if( pclunit[1]->siCurQuestUnique > 0 || pclunit[1]->siCurQuestStep > 0 )	bQuestRunning = true;
						if( pclunit[2]->siCurQuestUnique > 0 || pclunit[2]->siCurQuestStep > 0 )	bQuestRunning = true;
						if( pclunit[3]->siCurQuestUnique > 0 || pclunit[3]->siCurQuestStep > 0 )	bQuestRunning = true;
						if( pclunit[4]->siCurQuestUnique > 0 || pclunit[4]->siCurQuestStep > 0 )	bQuestRunning = true;

						if( bQuestRunning == true)
						{
							if(m_pDialog[ NNEWQUEST_DLG ] != NULL)
								CreateInterface( NNEWQUEST_DLG );

							if( ((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->IsShow() )
								((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->Hide();

							if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
							{
								CreateInterface( NNEWQUEST_DLG );

								if(m_pDialog[ NNEWQUEST_DLG ])
								{
									pclQuestManager->bNewQuseOpened = TRUE;
									((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
									((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
									((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
								}
							}
							else
								CreateInterface( NNEWQUEST_DLG );
						}
						else
						{
							((cltClient*)pclClient)->CreateInterface( NAVATARQUEST_DLG );
						}
					}

					//[�߰� : Ȳ���� 2007. 12. 11 �ų� Ʈ�� ���ý� �ƹ��͵� �������� ���ϰ�.]

					else if( pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_KADOMACH"))    ||
							 pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_RETURNTOWER")) ||//����Ÿ�� ������ �ƹ��͵� �������� ���ϰ� �߰�.
							 pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_HINADOLL"))			)
					{
						return false;				
					}
					// [���] 2008.11.12 : �ų� Ʈ��1�ܰ� ���ý� ������ �ϼ� â ������.
					else if( pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_NEWYEARTREEBASE")) )
					{
						CreateInterface( NCHRISTMASEVENT_DLG );
					}
					// [���] �ų⳪�� 2�ܰ� Ŭ��
					else if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_NEWYEARTREE")))
					{
						//CreateInterface(NCHARBUFF_ROULETTE_DLG);
						CreateInterface( NEWYEAR_ROULETTE_DLG );
					}
					//[����] ������ NPC
					else if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_ELIXIRNPC")))
					{
						CreateInterface( NELIXIR_NPC_DLG );
					}
					//[����] ���Һ� NPC Ŭ����
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_BOKBULBOKNPC")) )
					{
						if(pclClient->IsCountrySwitch(Switch_BokBulBok) == true)
						{
							cltClient* pClient = (cltClient*)pclClient;
							cltCharClient* pCharClient = pClient->pclCM->GetCharClient( 1 );

							SI32 siMapIndex = pCharClient->GetMapIndex();
							if ( PLAY_MAP_INDEX == siMapIndex )
							{
								cltMapCommon* pMap = pClient->pclMapManager->GetMapPointer( siMapIndex );

								if( NULL != pMap )
								{
									SI32 siColl = pMap->CalcCollInfo( pCharClient->GetX(), pCharClient->GetY());
									if( !(siColl & BLOCK_EVENT2 || siColl & BLOCK_EVENT3 || siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6) )	// 2, 3, 5, 6�� �̺�Ʈ Ÿ���� ��� ���� �������� npc���� �� �ɾ�����.
									{
										//((cltClient*) pclClient)->CreateInterface( NBOKBULBOK_EVENT_DLG );
										pClient->m_pClient_BBBMgr->Check_AlreadyReserved();
									}
								}
							}
						}
					}
					//[����] ��Ʋ�ξ�
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_BattleRoyalNPC")) )
					{
						cltClient* pClient = (cltClient*)pclClient;
						CBattleRoyalClient* pclBattleRoyalClient = pClient->m_pclBattleRoyal;
						if( NULL != pclBattleRoyalClient )
						{
							pclBattleRoyalClient->RequestTime();
						}
					}
					//[����] �߷�Ÿ�ε��� �̺�Ʈ
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_CHOCOLATE")) )
					{
						cltClient* pClient = (cltClient*)pclClient;
						CValentineEventClientMgr* pclValentineEventClientMgr = (CValentineEventClientMgr*)pClient->m_pclValentineEventMgr;
						if( NULL != pclValentineEventClientMgr )
						{
							pclValentineEventClientMgr->ClickNPC(pclCM->CR[id]->GetCharUnique());	
						}
					}
					//[����] ��ų�� npc
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_COPFIELD")) )
					{
						CreateInterface( NCOPFIELD_DLG );
					}
					//[����] ���̾�Ʈ ���� ��Ȱ ���� �̺�Ʈ NPC
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_RACCOONTREEBASE")) )
					{
						CreateInterface( NGIANTRACCOONRESURRECTEVENTDLG );
					}
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_RACCOONTREE")) )
					{
						// ������ ���ٸ� ����.
						cltCharClient* pclchar = pclCM->GetCharClient(1);
						if( NULL == pclchar ) return false;
						if( 0 >= pclchar->pclCI->clBI.siHomeVillage )								
						{
							m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(6481));
							return false;
						}
						
						// ���̾�Ʈ ���� ��Ȱ ���ڸ� �ִµ� �̹� �ִٸ� ����.
						if( 0    <= pclchar->pclCI->clCharItem.FindItemInv( ITEMUNIQUE(23499) ) )	
						{						
							m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(2214));
							return false;
						}
						if( true == pclchar->pclCI->clCharItem.HaveInEquip( ITEMUNIQUE(23499) ) )	
						{
							m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(2214));
							return false;
						}

						cltMsg clMsg( GAMEMSG_REQUEST_GIANTRACCOON_RESURRECT_EVENT_ITEM_GET, PACKET_EMPTY );
						pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );						
					}
					//[����] ���̾�Ʈ ���� ��Ȱ ���� �̺�Ʈ NPC
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_POTRACCOON")) )
					{
						CreateInterface( NPOTRACCOONDLG );
					}
					// [����] �ʺ��� ��Ƽ ����Ʈ �ý���(��Ƽ��Ī) - ��Ƽ����ƮNPC Ŭ����
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_PARTYQUESTNPC")))
					{
						if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
						{
							cltClient* pClient = (cltClient*)pclClient;
							
							pClient->m_pClient_PartyMatchingMgr->Click_PartyMatchingNPC();		
						}
					}
					//[����] �߷�Ÿ�ε��� NPC
					else if(pclCM->CR[id]->GetKind() == GetUniqueFromHash(TEXT("KIND_GIFTRACCOON")) )
					{
						cltGameMsgRequest_NPCSellItemInfo clNPCSellItemInfo( true, GetUniqueFromHash( TEXT("KIND_GIFTRACCOON") ) );
						cltMsg clMsg( GAMEMSG_REQUEST_NPCSELLITEMINFO, PACKET(clNPCSellItemInfo) );
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
					}
					else
					{
						if(m_pDialog[ NNEWQUEST_DLG ] != NULL)
							CreateInterface( NNEWQUEST_DLG );

						if( ((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->IsShow() )
							((cltNQuestDlg *)m_pDialog[ NQUEST_DLG ])->Hide();

						if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
						{
							CreateInterface( NNEWQUEST_DLG );

							if(m_pDialog[ NNEWQUEST_DLG ])
							{
								pclQuestManager->bNewQuseOpened = TRUE;
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(pclCM->CR[id]->GetKind());
								((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
							}
						}
						else
							CreateInterface( NNEWQUEST_DLG );
						// ��¿�� ���� �̰����� �޼����� ����.
						if (pclClient->IsCountrySwitch(Switch_TreasureEvent) )	
						{
							if( pclEventTimeManager->InEventTime(TEXT("TreasureEvent"), &sTime) )
							{
								cltClient* pclclient = (cltClient*)pclClient;
								cltCharCommon* pclchar = pclClient->pclCM->CR[1]	;
								if(pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_MERIEL")))
								{
									if(pclchar)		
									{		
										if(	true  == pclchar->pclCI->clQuestInfo.IsQuestClearOrGoing(QUEST_TYPE_FINDTREASURE )	)		
										{		
											if ( pclchar->pclCI->clQuestInfo.IsClear( pclClient->pclQuestManager, 31515) )		
											{		
												if (pclclient->m_pDialog[NCOMMONMSG_DLG] == NULL)	
												{	
													pclclient->CreateInterface( NCOMMONMSG_DLG );	
												}		
												((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_REQUEST_TREASUREEVENT);
											}
										}
									}

								}

							}
						}

					}
					
				//}
			}
		}
	}

	// ������ �ݱ�. 
	if(bdoneswitch == false && (MouseMode&MOUSEMODE_PICKUPITEM))
	{
		bdoneswitch = true;

		SI32 id = 1;
		if(pclCM->IsAlive(id))
		{
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_ITEM_PICKUP")), 0, 0);
			cltGameMsgRequest_InvPickUp clInfo(pclUnderMouseObject->GetItemUnique(), pclUnderMouseObject->GetItemIndex(), pclMapManager->CurrentMapIndex, pclUnderMouseObject->GetItemX(), pclUnderMouseObject->GetItemY());
			cltMsg clMsg(GAMEMSG_REQUEST_INVPICKUP, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}


	// ��� 
	if(bdoneswitch == false && (MouseMode&MOUSEMODE_FARM))
	{

		bdoneswitch = true;

		SI32 returnval = 0;
		if(pclCM->CR[1] && pclCM->CR[1]->CanFarm(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, &returnval) == true)
		{
			clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, 0);
			siSelectedOrder			= ORDER_FARM;
			siSelectedOrderPara1	= 0;
			siSelectedOrderPara2	= 0;
		}
		else
		{
			switch(returnval)
			{
			case CANFARM_ERROR_NOSKILL:
				{
					TCHAR* pText = GetTxtFromMgr(1105);

					pclMessage->SetMsg(pText);
				}
				break;
			case CANFARM_ERROR_NOTOOL:
				{
					TCHAR* pText = GetTxtFromMgr(1106);


					pclMessage->SetMsg(pText);
				}
				break;
			default:
				break;
			}
		}
	}

	// ä��
	//SI32 Temp1;
	//if(bdoneswitch == false && pclCM->CR[1] && pclCM->CR[1]->CanMine(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, &Temp1) == true)
	if(bdoneswitch == false && (MouseMode&MOUSEMODE_MINE))
	{
		bdoneswitch = true;

		SI32 returnval = 0;
		if(pclCM->CR[1] && pclCM->CR[1]->CanMine(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, &returnval) == true)
		{
			clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, 0);
			siSelectedOrder			= ORDER_MINE;
			siSelectedOrderPara1	= 0;
			siSelectedOrderPara2	= 0;

			//cyj ���� ��ġ�� NMineDlg�� ����
			if (m_pDialog[NMINING_DLG] != NULL)
			{
				((CNMiningDlg*)m_pDialog[NMINING_DLG])->SetMinePos(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY);
			}

		}
		else
		{
			switch(returnval)
			{
			case CANMINE_ERROR_NOSKILL:
				{
					TCHAR* pText = GetTxtFromMgr(3198);

					pclMessage->SetMsg(pText);
				}
				break;
			case CANMINE_ERROR_NOTOOL:
				{
					TCHAR* pText = GetTxtFromMgr(3199);

					pclMessage->SetMsg(pText);
				}
				break;
			default:
				break;
			}
		}
	}

	// �޴��� �̵��� �ְ� ���콺�� ���ڸ��� ������, 
	if(bdoneswitch == false && ((MouseMode&MOUSEMODE_MOVE) || (MouseMode&MOUSEMODE_OTHERUSER)))
	{
		bdoneswitch = true;

		SI32 summonid = pclCM->CR[1]->GetSummonID() ;
		bool bSummon = false ;

		if( pclCM->IsAlive(summonid) && pclCM->CR[1]->siSelectedCharIndex == pclCM->CR[summonid]->GetSummonIndex() )
		{
			bSummon			= true;
		}

		if(bDropTrySwitch == false )
		{
			//cyj �ʿ����͸�忡�� ����Ʈ Ŭ���Ͽ��� ���׵��� ����
			if (GameMode != GAMEMODE_MAPEDIT)
			{
				SI32 siGateUnique = pclUnderMouseObject->GetGateUnique();

				// ���� ����Ʈ�� �ο����� ���� ���¿��� �������� �ϸ�, 
				if( siGateUnique ) 
				{
					// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
					//if( IsWhereServiceArea( ConstSwitch_PVP ) )
					if(siEnablePVP == 1)
					{
						if( pclMapManager->pclGateManager->IsPkAreaGate(siGateUnique) )
						{
							if (m_pDialog[NOTIFYMSG_DLG])
							{
								clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclUnderMouseObject->GetUnderMouseID());

								SI32 selectedOrder = 0;
								if ( bSummon )
									selectedOrder			= ORDER_MOVE_SUMMON;
								else
									selectedOrder			= ORDER_MOVE;
								siSelectedOrderPara1	= 0;
								siSelectedOrderPara2	= 0;

								TCHAR* title = GetTxtFromMgr(10096);
								TCHAR* text = GetTxtFromMgr(10097);

								stMsgBox MsgBox;
								MsgBox.Set( m_pDialog[NOTIFYMSG_DLG],  title, text, MSGBOX_TYPE_YESNO, 0 );		
								BYTE TempBuffer[256] = {'\0'};
								SI16 Size = sizeof(selectedOrder)  + sizeof(clMouseObject.X) + sizeof(clMouseObject.Y)  + sizeof(clMouseObject.ID);
								memcpy( TempBuffer, &selectedOrder, sizeof(selectedOrder) );
								memcpy( &TempBuffer[ sizeof( siSelectedOrder ) ], &clMouseObject.X, sizeof( siSelectedOrder ) );
								memcpy( &TempBuffer[ sizeof( siSelectedOrder ) + sizeof( clMouseObject.X ) ], &clMouseObject.Y, sizeof( clMouseObject.Y ) );
								memcpy( &TempBuffer[ sizeof( siSelectedOrder ) + sizeof( clMouseObject.X ) + sizeof( clMouseObject.Y )], &clMouseObject.ID, sizeof( clMouseObject.ID ) );
								SetMsgBox( &MsgBox, TempBuffer, Size );	

								return TRUE;
							}
						}
					}
					else
					{
						if( pclMapManager->pclGateManager->IsPkAreaGate(siGateUnique) )
						{
							if (m_pDialog[NOTIFYMSG_DLG])
							{
								clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclUnderMouseObject->GetUnderMouseID());

								SI32 selectedOrder = 0;
								if ( bSummon )
									selectedOrder			= ORDER_MOVE_SUMMON;
								else
									selectedOrder			= ORDER_MOVE;
								siSelectedOrderPara1	= 0;
								siSelectedOrderPara2	= 0;

								TCHAR* title = GetTxtFromMgr(7203);
								TCHAR* text = GetTxtFromMgr(7204);

								stMsgBox MsgBox;
								MsgBox.Set( m_pDialog[NOTIFYMSG_DLG],  title, text, MSGBOX_TYPE_OK, 10 );		
								BYTE TempBuffer[256] = {'\0'};
								SI16 Size = sizeof(selectedOrder)  + sizeof(clMouseObject.X) + sizeof(clMouseObject.Y)  + sizeof(clMouseObject.ID);
								memcpy( TempBuffer, &selectedOrder, sizeof(selectedOrder) );
								memcpy( &TempBuffer[ sizeof( siSelectedOrder ) ], &clMouseObject.X, sizeof( siSelectedOrder ) );
								memcpy( &TempBuffer[ sizeof( siSelectedOrder ) + sizeof( clMouseObject.X ) ], &clMouseObject.Y, sizeof( clMouseObject.Y ) );
								memcpy( &TempBuffer[ sizeof( siSelectedOrder ) + sizeof( clMouseObject.X ) + sizeof( clMouseObject.Y )], &clMouseObject.ID, sizeof( clMouseObject.ID ) );
								SetMsgBox( &MsgBox, TempBuffer, Size );	

								return TRUE;
							}
						}
					}

					if( (pclCM->CR[1]->ClearQuest(30005) == false)
						// [����] Beginner2 ������ ������ ����Ʈ Ŭ���� ����(����� ���� ����Ʈ�� ȣȯ���� ���� ���߿� ����Ʈ �� �ٲ�� ��������)
						&& (pclCM->CR[1]->ClearQuest(30006) == false)
						&& (pclCM->CR[1]->GetMapIndex() == MAPINDEX_PALACE)
						&& (pclCM->CR[1]->pclCI->clIP.GetLevel() < 10)
					)
					{
						TCHAR* pTitle = GetTxtFromMgr(1107);
						TCHAR* pText = GetTxtFromMgr(1108);
						m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						return TRUE;
					}
					else if ( bSummon )
					{
						return TRUE;
					}

					if ( IsEnterGate( siGateUnique ) == false )
					{
						TCHAR* pTitle = GetTxtFromMgr(6234);
						TCHAR* pText = GetTxtFromMgr(6235);
						if ( !m_pDialog[NDOWNLOADADDON_DLG] )
						{
							CreateInterface( NDOWNLOADADDON_DLG );
						}
						return TRUE;
					}

					
				}
			}

			clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclUnderMouseObject->GetUnderMouseID());

			if ( bSummon )
				siSelectedOrder			= ORDER_MOVE_SUMMON;
			else
				siSelectedOrder			= ORDER_MOVE;
			siSelectedOrderPara1	= 0;
			siSelectedOrderPara2	= 0;
		}
	}

	// �޴��� ������ �ְ� ���콺�� �� ���� ������, 
	if(bdoneswitch == false && (MouseMode&MOUSEMODE_ATTACK))
	{
		// �����̾� ���� ���� �����߿� ������ ���Ѵ�
		if(pclCM->CR[1]->bPersonalShopSwitch && pclCM->CR[1]->bPremiumPersonalShop)
		{
			if (m_pDialog[NCOMMONMSG_DLG] == NULL)
			{
				CreateInterface( NCOMMONMSG_DLG );
			}
			((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_CLOSE_PREMIUMSHOP);

			return TRUE;
		}

		SI32 underMouseID = pclUnderMouseObject->GetUnderMouseID();

		if( pclCM->CR[underMouseID]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SANTARACCOON_ZIQ")) )
		{
			if( pclCM->CR[1]->pclCI->clIP.GetLevel() < 10 
				|| pclCM->CR[1]->pclCI->clIP.GetLevel() > 40   )
			{				
				TCHAR* pTitle = GetTxtFromMgr(512);
				TCHAR* pText = GetTxtFromMgr(6656);

				m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,  pText);

				return TRUE;
			}

		}

		bdoneswitch = true;

		clMouseObject.Set(pclUnderMouseObject->MapX, pclUnderMouseObject->MapY, pclUnderMouseObject->GetUnderMouseID());

		SI32 summonid = pclCM->CR[1]->GetSummonID() ;
		if( GetAsyncKeyState(VK_SHIFT) <-1 ||
			(pclCM->IsAlive(summonid) && pclCM->CR[1]->siSelectedCharIndex == pclCM->CR[summonid]->GetSummonIndex()) )
		{
			siSelectedOrder			= ORDER_ATTACK_SUMMON;
			siSelectedOrderPara2	= 0;

			//-----------------------------------------------------------
			// ���� ������ ����Ʈ�� �Ϸ�Ǿ����� �˷��ش�.
			//-----------------------------------------------------------
			SI16 questtype, questunique, para1, para2;
			SI16 questclearcond =  QUEST_CLEAR_COND_SUMMONATTACK;
			if( pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
			{
				cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
				cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		//��Ʈ��Ű ������ Į��
		else if( GetAsyncKeyState(VK_CONTROL) < -1 )
		{
			// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
			//if( IsWhereServiceArea(ConstSwitch_PVP) )
			if(siEnablePVP == 1)
			{
				if( pclCM->CR[1]->IsEnemyPCvsPC(underMouseID) )
				{
					siSelectedOrder = ORDER_ATTACK;
					siSelectedOrderPara2	= 1;
				}
				else
				{
					siSelectedOrder = ORDER_ATTACK;
					siSelectedOrderPara2	= 0;
				}
			}
			else
			{
				siSelectedOrder = ORDER_ATTACK;
				siSelectedOrderPara2	= 0;
			}
		}
		else
		{
			if( pclCM->CR[1]->IsEnemyPCvsPC(underMouseID) )
			{
				siSelectedOrder = ORDER_ATTACK;
				siSelectedOrderPara2	= 1;
			}
			else
			{
				siSelectedOrder = ORDER_ATTACK;
				siSelectedOrderPara2	= 0;
			}

		}

		siSelectedOrderPara1	= 0;
	}

	else if(bdoneswitch == false && (MouseMode&MOUSEMODE_DESK))
	{
		//[�߰� : Ȳ���� 2008. 1. 10 => �δ� ���� ��Ȳ���� �Խ��� Ŭ���� â ����.]
		if ( pclUnderMouseObject->siDeskUnique == FOUNIQUE(305) ) 
		{
			cltMsg clMsg( GAMEMSG_REQUEST_INSTANTSDUNGEON_STATUS, NULL);
			pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );	
		}

		//�δ����� ���� �Խ���.
		if (pclUnderMouseObject->siDeskUnique == FOUNIQUE(307))
		{
			((cltClient*)pclClient)->CreateInterface( NINSTANTDUNGEONBOARD_DLG );
		}

		bdoneswitch = true;
	}
	
	return bdoneswitch;

}


// ������ ��� �������� ���� �޽���
void cltClient::ShowMessageForItemEquipFail( SI32 siFailCode )
{
	TCHAR* pText = NULL;

	switch ( siFailCode )
	{
		case ITEMEQUIP_FAIL_OUTOFSKILL:
			pText = GetTxtFromMgr(1062);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_OUTOFLEVEL:
			pText = GetTxtFromMgr(1063);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_OUTOFSTR:
			pText = GetTxtFromMgr(1064);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_OUTOFDEX:
			pText = GetTxtFromMgr(1065);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_OUTOFMAG:
			pText = GetTxtFromMgr(1066);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_OUTOFVIT:
			pText = GetTxtFromMgr(1067);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_OUTOFHND:
			pText = GetTxtFromMgr(1068);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_FORWOMAN:
			pText = GetTxtFromMgr(1069);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_FORMAN:
			pText = GetTxtFromMgr(1070);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_NOEQUIPFORHERO:
			pText = GetTxtFromMgr(1071);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_OUTOFFAME:
			pText = GetTxtFromMgr(1072);

			pclMessage->SetMsg(pText);		break;
		case ITEMEQUIP_FAIL_NOSUMMONHERO:
		case ITEMEQUIP_FAIL_OUTOFSUMMONLEVEL:
			{
				NTCHARString64	strTitle( GetTxtFromMgr(1074) );
				NTCHARString256 strText( GetTxtFromMgr(1073) );

				strText.Replace( TEXT("#level#"), SI32ToString(SUMMON_EQUIP_LIMITMINLEVEL) );
				
				m_pDialog[ NOTIFYMSG_DLG ]->SetText( strTitle, strText);
			}
			break;

		case ITEMEQUIP_FAIL_NOTTAKEOUTSTATUS:
			{
				NTCHARString64	strTitle( GetTxtFromMgr(1074) );
				NTCHARString256 strText( GetTxtFromMgr(8641) );

				m_pDialog[ NOTIFYMSG_DLG ]->SetText( strTitle, strText);
			}
			break;

		case ITEMEQUIP_FAIL_NOTENOUGHSTONE:
			pText = GetTxtFromMgr(8646);

			pclMessage->SetMsg(pText);		break;

		case ITEMEQUIP_FAIL_WRONGEQUIPTYPE:
			{
				NTCHARString64	strTitle( GetTxtFromMgr(1074) );
				NTCHARString256 strText( GetTxtFromMgr(8653) );

				m_pDialog[ NOTIFYMSG_DLG ]->SetText( strTitle, strText);
			}
			break;

		default:
			TCHAR* pTitle = GetTxtFromMgr(1074);
			pText = GetTxtFromMgr(1075);


			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			break;
	}
	

}
