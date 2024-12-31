#include "GMProtocol.h"
#include "GMMsg.h"
#include <atlstr.h>

#include "../Client/Client.h"
#include "../Server/Server.h"

#include "../CommonLogic/House/House.h"
#include "../CommonLogic/MsgType-System.h"
#include "../common/skill/Skill-Manager.h"
#include "../common/Util/Util.h"


#include "../Common/Char/CharManager/CharManager.h"
#include "../Common/Char/CharServer/Char-Server.h"

#include "../CommonLogic/CommonLogic.h"
#include "../../Client/ninterface/ncharstatus/NCharPerson.h"
#include "../DBManager/GameDBManager_World/DBMsg-Log.h"

#include "../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../DBManager/GameDBManager_World/DBMsg-WorldMoney.h"
#include "../DBManager/GameDBManager_World/DBMsg-Stock.h"
#include "../DBManager/GameDBManager_World/DBMsg-Item.h"

#include "GMProtocol_Updata.h"
#include "GMDefine.h"


extern cltCommonLogic* pclClient;

SI16 CGMProtocol_Updata::BasicInfoUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar )
{
	if ( (pRecvMsg == NULL) || (siButtonID <= 0) )
	{
		return UPDATA_ERROR_MSG_DO_NOT_RUN;
	}

	cltServer*	pclserver	= (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return UPDATA_ERROR_MSG_DO_NOT_RUN;
	}

	SI32		siPersonID	= 0;
	SI32		siCharID	= 0;


	pRecvMsg->GetDataInt( "personid", &siPersonID );
	// PersonID�� 0 ���ϸ� �߸��޾ƿ� ���̵�
	if ( siPersonID <= 0 )
	{
		return UPDATA_ERROR_MSG_NO_PERSONID;
	}

	// pclChar�� �����Ͱ��� ���� �Ѵٸ�(ĳ���Ͱ� ������ �ִٸ�) �ɸ��� ID�� �޾ƿ´�
	if ( pclChar != NULL )
	{
		siCharID = pclChar->GetCharID();
	}


	switch( siButtonID ) 
	{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  �������ͽ� �ʱ�ȭ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case UPDATA_ID_BASICINFO_STATUS_RESET: // Status Reset
		{
			// ���� �������� �ƴ� �ɸ��͸� ������ �����ϴ�
			if ( pclChar != NULL )
			{
				return UPDATA_ERROR_MSG_ONLY_DISCONNECT_USER;
			}
			
			sDBRequest_InitStatus clMsg( 0, siPersonID, INITSTATUSMODE_GMTOOL , 0 , NULL );
			pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			if( pclClient->IsCountrySwitch( Switch_Elixir ) )
			{
				// �������ͽ� �ʱ�ȭ�� �������� ���� �ʱ�ȭ ��Ų��.
				if( pclChar->pcltElixir && pclChar->pcltElixir->IsElixir() ) 
				{
					cltElixir_Info  clElixirInfo;
					clElixirInfo.m_siEndMinuteVary	= pclChar->pcltElixir->GetMinuteVary();
					clElixirInfo.m_uiMultiple 		= pclChar->pcltElixir->GetMultiple();
					clElixirInfo.m_siPoint	  		= pclChar->pcltElixir->GetTotalPoint();

					if(pclChar->pclCI->GetPersonID() > 0)
					{
						sDBRequest_Elixir_Set clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), &clElixirInfo );
						pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
				}
			}
		}
		return Const_UpData_Success;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  ����ڰ� �����ִ� ���� �߰� �� �����ϱ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case UPDATA_ID_BASICINFO_MONEY_ADD:
	case UPDATA_ID_BASICINFO_MONEY_SUB:
		{
			SI32	siGetMoney	= 0;
			GMONEY	gmMoney		= 0;


			pRecvMsg->GetDataInt( "money", &siGetMoney );
			if ( siGetMoney <= 0 )
			{
				return UPDATA_ERROR_MSG_WRONG_MONEY;
			}

			// �����ϴ� ���̶�� -1�� �����ش�
			gmMoney = siGetMoney * ( siButtonID==UPDATA_ID_BASICINFO_MONEY_SUB ? (-1) : (1) );
			
			sDBRequest_ChangeMoney clMsg( siCharID, siPersonID, CHANGE_MONEY_REASON_GAMEMASTER, gmMoney);
			pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );
		}
		return Const_UpData_Success;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  ��ť(�����Ӵ�) �߰� �� �����ϱ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case UPDATA_ID_BASICINFO_ACU_ADD:
	case UPDATA_ID_BASICINFO_ACU_SUB:
		{
			SI32 siGetMoney		= 0;
			SI64 siWorldMoney	= 0;


			pRecvMsg->GetDataInt( "money", &siGetMoney );
			if ( siGetMoney <= 0 ) 
			{
				return UPDATA_ERROR_MSG_WRONG_MONEY;
			}
			
			// �����ϴ� ���̶�� -1�� �����ش�.
			siWorldMoney = siGetMoney * ( siButtonID==UPDATA_ID_BASICINFO_ACU_SUB ? (-1) : (1) );

			sDBRequest_WorldMoney_Set_Char clMsg( siCharID, siPersonID, siWorldMoney);
			pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );
		}
		return Const_UpData_Success;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  �ֽ� �߰��ϱ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	case UPDATA_ID_BASICINFO_STOCK_ADD:
		{
			SI32 siVillageUnique	= 0;
			SI32 siStockAmount		= 0;


			pRecvMsg->GetDataInt( "villageunique", &siVillageUnique );
			if ( (siVillageUnique <= 0) || (siVillageUnique >= MAX_VILLAGE_NUMBER) )
			{	
				return UPDATA_ERROR_MSG_WRONG_VILLAGE_UNIQUE;
			}

			pRecvMsg->GetDataInt( "stockamount", &siStockAmount );
			if (siStockAmount <= 0)
			{	
				return UPDATA_ERROR_MSG_WRONG_STOCK_AMOUNT;
			}

			sDBRequest_StockDistributionOrder clMsg( siVillageUnique, siPersonID, siCharID, siStockAmount, 0, false );
			pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );	
		}
		return Const_UpData_Success;
	*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  ���� �����ϱ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case UPDATA_ID_BASICINFO_BUF_MODIFY:
		{
			SI32	siBufNumber	= 0;
			SI32	siBufSlot	= -1;
			
			SI32	siBufTime	= 0;
			SI32	siBufMonth	= 0;
			SI32	siBufDay	= 0;
			SI32	siBufHour	= 0;
			
			SI16	siPercent	= 0;
			
			stBuf	bufAdd;

			
			pRecvMsg->GetDataInt( "bufnumber", &siBufNumber );
			if ( (siBufNumber < 1) || (siBufNumber >= BUF_END) )
			{
				return UPDATA_ERROR_MSG_WRONG_BUF_NUMBER;
			}

			pRecvMsg->GetDataInt( "bufslot", &siBufSlot );
			if ( (siBufSlot < 0) || (siBufSlot >= MAX_BUF) )
			{
				return UPDATA_ERROR_MSG_WRONG_BUF_SLOT;
			}

			pRecvMsg->GetDataInt( "bufmonth", &siBufMonth );
			pRecvMsg->GetDataInt( "bufday", &siBufDay );
			pRecvMsg->GetDataInt( "bufhour", &siBufHour );
			if ( ((siBufHour<0) || (siBufHour>24)) && ((siBufDay<0) || (siBufDay>30)) && ((siBufMonth<0) || (siBufMonth>12)) )
			{
				return UPDATA_ERROR_MSG_WRONG_BUF_TIME;
			}

			// Ȥ�� �� ���ϰ��� �߸� �Ǿ������� ���
			siBufTime = pclserver->pclTime->clDate.GetHourVary() + (siBufHour) + (24*siBufDay) + (24*30*siBufMonth);
			if ( (siBufTime <= 0) || (pclserver->pclTime->clDate.GetHourVary() > siBufTime) )
			{
				return UPDATA_ERROR_MSG_WRONG_BUF_TIME;
			}

			// ���� Ÿ�Կ����� ȿ������ ����
			switch (siBufNumber)
			{
				case BUF_MAKEEXPUP:
					{
						siPercent = 50;
					}
					break;
				case BUF_ATTACKUP:
				case BUF_ATTACKUP30:
				case BUF_DEFENSEUP:
				case BUF_DEFENSEUP30:
				case BUF_SUMMONATACUP:	
					{
						siPercent = 20;
					}
					break;
				default:
					{
						siPercent = 0;
					}
					break;
			}

			// ���� ���� ����			
			bufAdd.siBufType	= siBufNumber;
			bufAdd.siPercent	= siPercent;
			//bufAdd.siAdd		= 0;
			bufAdd.siOverTime	= siBufTime;
			//bufAdd.bOverlap	= false;

			bufAdd.siGetType	= 0;
			
			sDBRequest_AddBuf clMsg( siPersonID, siBufSlot, &bufAdd);
			pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );
			
		}
		return Const_UpData_Success;
	}

	return UPDATA_ERROR_MSG_DO_NOT_RUN;

}

SI16 CGMProtocol_Updata::SkillInfoUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar )
{
	/*
	if ( (pRecvMsg == NULL) || (siButtonID <= 0) )
	{
		return UPDATA_ERROR_MSG_DO_NOT_RUN;
	}

	cltServer*	pclserver	= (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return UPDATA_ERROR_MSG_DO_NOT_RUN;
	}

	SI32		siPersonID	= 0;
	SI32		siCharID	= 0;


	pRecvMsg->GetDataInt( "personid", &siPersonID );
	// PersonID�� 0 ���ϸ� �߸��޾ƿ� ���̵�
	if ( siPersonID <= 0 )
	{
		return UPDATA_ERROR_MSG_NO_PERSONID;
	}

	// pclChar�� �����Ͱ��� ���� �Ѵٸ�(ĳ���Ͱ� ������ �ִٸ�) �ɸ��� ID�� �޾ƿ´�
	if ( pclChar != NULL )
	{
		siCharID = pclChar->GetCharID();
	}


	switch( siButtonID ) 
	{
		case UPDATA_ID_SKILL_NONE:
			{
				return UPDATA_ERROR_MSG_DO_NOT_RUN;
			}
	
		return Const_UpData_Success;
	}
	*/
	return UPDATA_ERROR_MSG_DO_NOT_RUN;
}

SI16 CGMProtocol_Updata::InventoryUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar )
{
	if ( (pRecvMsg == NULL) || (siButtonID <= 0) )
	{
		return UPDATA_ERROR_MSG_DO_NOT_RUN;
	}

	cltServer*	pclserver	= (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return UPDATA_ERROR_MSG_DO_NOT_RUN;
	}

	SI32		siPersonID	= 0;
	SI32		siCharID	= 0;


	pRecvMsg->GetDataInt( "personid", &siPersonID );
	// PersonID�� 0 ���ϸ� �߸��޾ƿ� ���̵�
	if ( siPersonID <= 0 )
	{
		return UPDATA_ERROR_MSG_NO_PERSONID;
	}

	// pclChar�� �����Ͱ��� ���� �Ѵٸ�(ĳ���Ͱ� ������ �ִٸ�) �ɸ��� ID�� �޾ƿ´�
	if ( pclChar != NULL )
	{
		siCharID = pclChar->GetCharID();
	}


	switch( siButtonID ) 
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//  ������ �߰��ϱ�
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case UPDATA_ID_INVENTORY_ITEM_ADD:
			{
				char		szItemName[MAX_ITEM_NAME]	= {0, };	// ������ �̸�(Ȥ�� Unique��ȣ)
				SI32		siItemUnique				= 0;		// ���� ���޵� ������ Unique
				SI32		siItemAmount				= 0;		// ������ ����
				SI32		siInventorySlot				= 0;		// �������� �� �ɸ��� �κ� ��ȣ
				SI32		siReference					= 0;		// ������ ���Ⱓ�� ���ö� �����ϴ� ����
				UI16		uiUseDate					= 0;		// ������ ���Ⱓ

				cltItem		clItem;									// ���� ������� ������
				SI16		siRareSwitch				= 0;		// ������ ���鶧 �ʿ��� ����
				bool		bMakeResult					= false;	// ������ ���� ���
				bool		bPile						= false;	// ������ ��ø ���ɿ���

				// ������ �̸� ��������
				pRecvMsg->GetDataStr( "itemname", szItemName, MAX_ITEM_NAME );
				if ( strcmp( szItemName, "" )  == 0 )
				{
					return UPDATA_ERROR_MSG_WRONG_ITEM_NAME;
				}
				
				// �Ϻ��� �ƴ� �ٸ� ������ ������ �̸��� '_'ǥ�ø� �����̽��� ��ȯ�Ѵ�.(����ó���� �Լ��ȿ��� ��)
				ConvertUnderLineToSpace( szItemName, MAX_ITEM_NAME );
				
				// �������� unique�� �ƴ϶� �̸��� ��츦 ���� �˻�
				siItemUnique = pclserver->pclItemManager->FindUniqueFromName( szItemName );
				if ( siItemUnique <= 0 )
				{
					siItemUnique = atoi( szItemName );
					if ( siItemUnique <= 0 )
					{
						return UPDATA_ERROR_MSG_WRONG_ITEM_NAME;
					}
				}

				// ������ ���� üũ
				pRecvMsg->GetDataInt( "itemamount", &siItemAmount );
				if ( (siItemAmount <= 0) || (siItemAmount > MAX_ITEM_PILE_NUMBER) )
				{
					return UPDATA_ERROR_MSG_WRONG_ITEM_NUM;
				}
				
				// �������� ������ ĳ���� ���Թ�ȣ üũ
				pRecvMsg->GetDataInt( "inventoryslot", &siInventorySlot );
				if ( (siInventorySlot < PERSONITEM_INV0) || (siInventorySlot > (PERSONITEM_BAG1+MAX_ITEM_PER_BAG)) )
				{
					return UPDATA_ERROR_MSG_WRONG_INVENTORY_SLOT;
				}
				
				// ������ ���Ⱓ�� ���������� �����۾�
				siReference = pclClient->pclItemManager->FindItemRefFromUnique( siItemUnique );
				if ( siReference <= 0 )
				{
					return UPDATA_ERROR_MSG_DO_NOT_MAKE_ITEM;
				}
				
				// ������ ���Ⱓ
				uiUseDate = pclClient->pclItemManager->pclItemInfo[ siReference ]->clItem.uiDateDay;

				clItem.Init();

				bMakeResult = pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clItem, 0, 0, &siRareSwitch, 0, 0, 0, 0, 0, uiUseDate );
				
				// ������ ���� ����
				if ( bMakeResult == false )
				{
					return UPDATA_ERROR_MSG_DO_NOT_MAKE_ITEM;
				}

				// ������ ��ø ���ο� ���� ���������� �Ѵ�.
				bPile = clItem.CanPile( pclClient->pclItemManager );
				if ( (bPile == false) && (siItemAmount > 1) )
				{
					return UPDATA_ERROR_MSG_WRONG_ITEM_NUM;
				}

				clItem.SetItemNum( siItemAmount );
				
				sDBRequest_InputItemToPerson clMsg(
					siCharID, 
					siPersonID, 
					siInventorySlot, 
					INPUTITEMPERSON_OPTION_MASTER, 
					bPile, 
					&clItem, 
					0, 
					clItem.IsCreateSID(pclClient->pclItemManager));
				pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );
			}
			return Const_UpData_Success;
	}

	return UPDATA_ERROR_MSG_DO_NOT_RUN;

}