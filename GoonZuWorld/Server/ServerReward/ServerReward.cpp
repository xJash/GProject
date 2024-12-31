#include "ServerReward.h"
#include "../Server.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../CommonLogic/MsgRval-Define.h"
#include "../../common/Char/CharManager/CharManager.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"

#include "../../Lib/dxutil.h"



extern cltCommonLogic* pclClient;

//----------------------------------------------------------------------------------
// ĳ���� ������ ���� Ŭ����
//----------------------------------------------------------------------------------
cltCreateCharReward::cltCreateCharReward()
{
	Init();
}

cltCreateCharReward::~cltCreateCharReward()
{
	for ( SI32 siIndex=0; siIndex<Const_Max_CreateCharReward_Item; ++siIndex )
	{
		SAFE_DELETE( m_pclCreateCharReward[siIndex] );
	}
}

void cltCreateCharReward::Init( void )
{
	ZeroMemory( this, sizeof(cltCreateCharReward) );
}

bool cltCreateCharReward::LoadRewardItemList( void )
{
	TCHAR		szFileName[MAX_PATH] = { '\0', };
	if( pclClient->siServiceArea == ConstServiceArea_Korea )	// �ѱ�
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardK.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardJ.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China )	
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_English )  // ����
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardE.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Taiwan )  
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardT.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )  
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardU.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )  //NHN�߱�
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\CreateCharRewardG.txt"));
	}

	NDataLoader	dataloader;
	BOOL		bLoadFile				= FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("cltCreateCharReward::LoadRewardItemList()"), TEXT("LoadError:[%s]"), szFileName);
		return false;
	}


	SI32 siItemUnique	= 0;
	SI32 siItemNum		= 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siItemUnique,	4,		
		NDATA_INT32,	&siItemNum,		4,		
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			cltRewardItem clRewardItem( siItemUnique, siItemNum );

			if ( AddRewardItem( &clRewardItem ) )
			{
				m_siCreateCharRewardCount++;
			}

			if ( Const_Max_CreateCharReward_Item <= m_siCreateCharRewardCount )
			{
				break;
			}
		}
	}

	return true;
}

void cltCreateCharReward::GiveRewardItem( SI32 siPersonID )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	if ( 0 >= siPersonID )
	{
		return;
	}

	bool bRewardItem = false;

	for ( SI32 siIndex=0; siIndex<Const_Max_CreateCharReward_Item; ++siIndex )
	{
		if ( NULL == m_pclCreateCharReward[siIndex] )
		{
			continue;
		}

		SI32 siItemUnique	= m_pclCreateCharReward[siIndex]->GetItemUnique();
		SI32 siItemNum		= m_pclCreateCharReward[siIndex]->GetItemNum();
		
		if ( (0 >= siItemUnique) || (0 >= siItemNum) )
		{
			continue;
		}

		cltItem clGiveItem;
		if ( false == GetRewardItem(siItemUnique, siItemNum, &clGiveItem) )
		{
			continue;
		}
		
		cltSystemRewardInfo clRewardInfo;

		// ������
		clRewardInfo.m_sGiveTime = pclserver->sTime;

		// �����Ⱓ
		TimeAddDate( &clRewardInfo.m_sGiveTime, 30, &clRewardInfo.m_sExpireTime );

		// ������ ����
		clRewardInfo.m_clItem.Set( &clGiveItem );

		// ���޻���
		TCHAR* pszReason = GetTxtFromMgr( 8931 );
		StringCchCopy( clRewardInfo.m_szReason, 256, pszReason );

		// ���� ������
		sDBRequest_GiveSystemReward clMsg( GIVEREWARD_CHAR, siPersonID, 0, &clRewardInfo );
		pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

		bRewardItem = true;
	}

	// �������� �������� ���´ٴ� �޽����� ����
	if ( true == bRewardItem )
	{
		cltLetterMsg_CreateCharReward clletter;
		sDBRequest_PushLetter clMsg( siPersonID, (cltLetterUnit*)&clletter );
		pclserver->SendDBMsg( DBSELECT_LETTER, (sPacketHeader*)&clMsg );
	}

}

bool cltCreateCharReward::GetRewardItem( IN SI32 siItemUnique, IN SI32 siItemNum, OUT cltItem* pclGiveItem )
{
	if ( (0 >= siItemUnique) || (0 >= siItemNum) || (NULL == pclGiveItem) )
	{
		return false;
	}

	SI32 siRef = pclClient->pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( 0 >= siRef )
	{
		return false;
	}

	cltItem	clGiveItem;
	SI16	siUseDate		= pclClient->pclItemManager->pclItemInfo[siRef]->clItem.uiDateUseDay;
	SI16	siRareSwitch	= 0;

	bool	bCanMakeItem	= pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clGiveItem, 0, 0, &siRareSwitch, 0, 0, 0, 0, 0, siUseDate );
	if ( false == bCanMakeItem )
	{
		return false;
	}

	// ������ �����Ѵ�. 
	// ��ø ������ �������� ���ϴ� ������ŭ ���� �� �ִ�. 
	if ( true == clGiveItem.CanPile(pclClient->pclItemManager) )
	{
		clGiveItem.SetItemNum(siItemNum);
	}
	else
	{
		// ��ø �Ұ� �������� 1���� ���� �� �ִ�. 
		clGiveItem.SetItemNum(1);
	}

	// �Ⱓ�� �ִ� �������� �к��ؼ� �־��ش�
	if ( clGiveItem.uiDateUseDay )
	{
		clGiveItem.uiDateYear	= 0;
		clGiveItem.uiDateMonth	= 0;
		clGiveItem.uiDateDay	= 0;
	}

	pclGiveItem->Init();
	pclGiveItem->Set( &clGiveItem );

	if ( 0 >= pclGiveItem->siUnique )
	{
		return false;
	}

	return true;

}

bool cltCreateCharReward::AddRewardItem( cltRewardItem* pclRewardItem )
{
	if ( NULL == pclRewardItem )
	{
		return false;
	}

	if ( Const_Max_CreateCharReward_Item <= m_siCreateCharRewardCount )
	{
		return false;
	}

	m_pclCreateCharReward[m_siCreateCharRewardCount] = new cltRewardItem;
	if ( NULL == m_pclCreateCharReward )
	{
		return false;
	}

	m_pclCreateCharReward[m_siCreateCharRewardCount]->Set( pclRewardItem );

	return true;

}

//----------------------------------------------------------------------------------
// ĳ���� ��õ�� ���� Ŭ����
//----------------------------------------------------------------------------------
cltRecommendReward::cltRecommendReward()
{
	Init();
}

cltRecommendReward::~cltRecommendReward()
{
	for ( SI32 siIndex=0; siIndex<Const_Max_RecommandReward_Item; ++siIndex )
	{
		SAFE_DELETE( m_pclRecommendReward[siIndex] );
		SAFE_DELETE( m_pclRecommendeeReward[siIndex] );
	}
}

void cltRecommendReward::Init( void )
{
	ZeroMemory( this, sizeof(cltRecommendReward) );
}

bool cltRecommendReward::LoadRewardItemList( void )
{
	if( false == LoadRecommendRewardItemList() )	return false;
	if( false == LoadRecommendeeRewardItemList() )	return false;

	return true;
}

bool cltRecommendReward::LoadRecommendRewardItemList( void )
{
	TCHAR		szFileName[MAX_PATH] = { '\0', };
	if( pclClient->siServiceArea == ConstServiceArea_Korea )	// �ѱ�
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardK.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardJ.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China )	
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_English )  // ����
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardE.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Taiwan )  
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardT.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )  
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardU.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )  //NHN�߱�
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardG.txt"));
	}

	NDataLoader	dataloader;
	BOOL		bLoadFile				= FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("cltRecommendReward::LoadRewardItemList()"), TEXT("LoadError:[%s]"), szFileName);
		return false;
	}


	SI32 siLevel		= 0;
	SI32 siItemUnique	= 0;
	SI32 siItemNum		= 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siLevel,		4,
		NDATA_INT32,	&siItemUnique,	4,
		NDATA_INT32,	&siItemNum,		4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			cltRewardItem clRewardItem( siItemUnique, siItemNum, siLevel );

			AddRecommendRewardItem( &clRewardItem );
		}
	}

	/***************************************************************************************
	*
	*	[����] �߱����� �ڵ��� ������ �ȵ��� �� �� ������ ���� �ε�
	*
	***************************************************************************************/
	if( pclClient->siServiceArea != ConstServiceArea_NHNChina )  return true;
	
	StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendRewardNoAuthC.txt"));
	
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("cltRecommendReward::LoadRewardItemList()"), TEXT("LoadError:[%s]"), szFileName);
		return false;
	}


	NDataTypeInfo pDataTypeInfo2[] =
	{
		NDATA_INT32,	&siLevel,		4,
		NDATA_INT32,	&siItemUnique,	4,
		NDATA_INT32,	&siItemNum,		4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo2 );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			cltRewardItem clRewardItem( siItemUnique, siItemNum, siLevel );

			AddRecommendRewardItemNoAuth( &clRewardItem );
		}
	}

	return true;
}

bool cltRecommendReward::LoadRecommendeeRewardItemList( void )
{
	TCHAR		szFileName[MAX_PATH] = { '\0', };
	if( pclClient->siServiceArea == ConstServiceArea_Korea )	// �ѱ�
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardK.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardJ.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China )	
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_English )  // ����
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardE.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Taiwan )  
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardT.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )  
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardU.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )  //NHN�߱�
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardG.txt"));
	}

	NDataLoader	dataloader;
	BOOL		bLoadFile				= FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("cltRecommendeeReward::LoadRecommendeeRewardItemList()"), TEXT("LoadError:[%s]"), szFileName);
		return false;
	}


	SI32 siLevel		= 0;
	SI32 siItemUnique	= 0;
	SI32 siItemNum		= 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
			NDATA_INT32,	&siLevel,		4,
			NDATA_INT32,	&siItemUnique,	4,
			NDATA_INT32,	&siItemNum,		4,
			0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			cltRewardItem clRewardItem( siItemUnique, siItemNum, siLevel );

			AddRecommendeeRewardItem( &clRewardItem );
		}
	}



	/***************************************************************************************
	*
	*	[����] �߱����� �ڵ��� ������ �ȵ��� �� �� ������ ���� �ε�
	*
	***************************************************************************************/
	if( pclClient->siServiceArea != ConstServiceArea_NHNChina )  return true;

	StringCchCopy(szFileName, MAX_PATH, TEXT("ServerData\\RecommendeeRewardNoAuthC.txt"));

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("cltRecommendReward::LoadRewardItemList()"), TEXT("LoadError:[%s]"), szFileName);
		return false;
	}

	NDataTypeInfo pDataTypeInfo2[] =
	{
		NDATA_INT32,	&siLevel,		4,
		NDATA_INT32,	&siItemUnique,	4,
		NDATA_INT32,	&siItemNum,		4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo2 );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			cltRewardItem clRewardItem( siItemUnique, siItemNum, siLevel );

			AddRecommendeeRewardItemNoAuth( &clRewardItem );
		}
	}

	return true;
}

bool cltRecommendReward::GiveRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName, bool _bAuth  )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return false;
	}

	if ( (0 >= siPersonID) || (0 >= siLevel) || (Const_Max_RecommandReward_Item <= siLevel) )
	{
		return false;
	}
	
	cltRewardItem* pRewardItem = NULL;
	if( bGiveMode )	pRewardItem	= _bAuth ? m_pclRecommendReward[siLevel]   : m_pclRecommendRewardNoAuth[siLevel];		// ��õ�� ���.
	else			pRewardItem	= _bAuth ? m_pclRecommendeeReward[siLevel] : m_pclRecommendeeRewardNoAuth[siLevel];	// ��õ�� ���� ���. 		


	if ( NULL == pRewardItem )
	{
		return false;
	}

	SI32 siItemUnique = pRewardItem->GetItemUnique();
	if ( 0 >= siItemUnique )
	{
		return false;
	}

	SI32 siItemNum = pRewardItem->GetItemNum();
	if ( 0 >= siItemNum )
	{
		return false;
	}

	SI32 siRef = pclClient->pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( 0 >= siRef )
	{
		return false;
	}

	SI32 siDateUseday = pclClient->pclItemManager->pclItemInfo[siRef]->clItem.uiDateUseDay;

	// �̰����� ��ȿ�� �˻�� ���� �ʴ´� �ֳ��ϸ� �� ���� ������ �������� �����ֱ� �����̴�
	cltCharServer*	pclchar		= NULL;
	SI32			siCharID	= pclserver->pclCM->GetIDFromPersonID( siPersonID );
	if ( pclClient->pclCM->IsValidID(siCharID) )
	{
		pclchar = pclClient->pclCM->GetCharServer( siCharID );
	}

	bool bGiveItem = false;
	
	// �������� �ɸ��� �κ��丮�� �ִ´�
	if ( (pclchar) && (pclchar->GiveItem(siItemUnique, siItemNum, INPUTITEMPERSON_OPTION_RECOMMEND, siDateUseday) == GIVEITEM_RESULT_SUCCESS) )
	{
		bGiveItem = true;
	}

	// �������� �κ��丮�� ���� ���ߴٸ�
	if ( false == bGiveItem )
	{
		cltItem	clGiveItem;
		SI16	siUseDate		= pclClient->pclItemManager->pclItemInfo[siRef]->clItem.uiDateUseDay;
		SI16	siRareSwitch	= 0;
		
		if ( pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clGiveItem, 0, 0, &siRareSwitch, 0, 0, 0, 0, 0, siUseDate ) )
		{
			clGiveItem.SetItemNum( siItemNum );

			pclserver->SendPostOfficeItemToPerson( siPersonID, &clGiveItem, NULL );

			bGiveItem = true;
		}
	}

	// �������� �޾Ҵٸ� �޽����� ��������
	if ( true == bGiveItem )
	{
		// ��õ��
		if ( true == bGiveMode )
		{
			SendRecommenderMessage( pRewardItem, siPersonID, siLevel, _bAuth );

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				cltServer* pclserver = (cltServer*)pclClient;
				// [�α��߰� : Ȳ���� 2007. 10. 19] // ����õ�� ����.
				// param1 == ������ ����ũ.
				// param2 == ������ ����.
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_COMMENDER_REWARD, 
												0, NULL, NULL, siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
												siItemUnique, siItemNum, 0, 0, 0, NULL, NULL);
			}
		}
		// ��õ�� ���� ���
		else
		{
			SendRecommendMessage( pRewardItem, siPersonID, siLevel, pszRecommenderName, _bAuth );

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				cltServer* pclserver = (cltServer*)pclClient;
				// [�α��߰� : Ȳ���� 2007. 10. 19] // ��õ�� ����.
				// param1 == ������ ����ũ.
				// param2 == ������ ����.
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_RECOMMENDER_REWARD, 
												0, NULL, NULL, siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
												siItemUnique, siItemNum, 0, 0, 0, NULL, NULL);
			}
		}
	}

	return bGiveItem;

}

bool cltRecommendReward::IsGiveRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return false;
	}

	if ( (0 >= siPersonID) || (0 >= siLevel) || (Const_Max_RecommandReward_Item <= siLevel) )
	{
		return false;
	}

	cltRewardItem* pRewardItem = NULL;
	if( bGiveMode )	pRewardItem	= m_pclRecommendReward[siLevel];	// ��õ�� ���.
	else			pRewardItem	= m_pclRecommendeeReward[siLevel];	// ��õ�� ���� ���. 		


	if ( NULL == pRewardItem )
	{
		return false;
	}

	SI32 siItemUnique = pRewardItem->GetItemUnique();
	if ( 0 >= siItemUnique )
	{
		return false;
	}

	SI32 siItemNum = pRewardItem->GetItemNum();
	if ( 0 >= siItemNum )
	{
		return false;
	}

	SI32 siRef = pclClient->pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( 0 >= siRef )
	{
		return false;
	}

	return true;
}

bool cltRecommendReward::AddRecommendRewardItemNoAuth( cltRewardItem* pclRewardItem )
{
	if ( NULL == pclRewardItem )
	{
		return false;
	}

	// ������ ���� �迭�ε����� ���� ����
	SI32 siLevel = pclRewardItem->GetPara1();
	if ( (0 > siLevel) || (Const_Max_RecommandReward_Item <= siLevel) )
	{
		return false;
	}

	//m_siRecommendGiveItemMaxLevel = siLevel;

	SI32 siItemUnique	= pclRewardItem->GetItemUnique();
	SI32 siItemNum		= pclRewardItem->GetItemNum();

	if ( m_pclRecommendRewardNoAuth[siLevel] )
	{
#ifdef _DEBUG
		NTCHARString256 strMessage( TEXT("�ش� #level#�� �������� �̹� �����Ǿ� �ֽ��ϴ�") );
		strMessage.Replace( TEXT("#level#"), SI32ToString(siLevel) );

		MsgBox( TEXT("��õ�� ���� ������ ����"), strMessage );
#endif

		return false;
	}

	m_pclRecommendRewardNoAuth[siLevel] = new cltRewardItem;
	if ( NULL == m_pclRecommendRewardNoAuth[siLevel] )
	{
		return false;
	}

	m_pclRecommendRewardNoAuth[siLevel]->Set( pclRewardItem );

	return true;
}

bool cltRecommendReward::AddRecommendRewardItem( cltRewardItem* pclRewardItem )
{
	if ( NULL == pclRewardItem )
	{
		return false;
	}

	// ������ ���� �迭�ε����� ���� ����
	SI32 siLevel = pclRewardItem->GetPara1();
	if ( (0 > siLevel) || (Const_Max_RecommandReward_Item <= siLevel) )
	{
		return false;
	}
	
	m_siRecommendGiveItemMaxLevel = siLevel;

	SI32 siItemUnique	= pclRewardItem->GetItemUnique();
	SI32 siItemNum		= pclRewardItem->GetItemNum();

	if ( m_pclRecommendReward[siLevel] )
	{
		#ifdef _DEBUG
			NTCHARString256 strMessage( TEXT("�ش� #level#�� �������� �̹� �����Ǿ� �ֽ��ϴ�") );
			strMessage.Replace( TEXT("#level#"), SI32ToString(siLevel) );

			MsgBox( TEXT("��õ�� ���� ������ ����"), strMessage );
		#endif

		return false;
	}

	m_pclRecommendReward[siLevel] = new cltRewardItem;
	if ( NULL == m_pclRecommendReward[siLevel] )
	{
		return false;
	}

	m_pclRecommendReward[siLevel]->Set( pclRewardItem );

	return true;

}

bool cltRecommendReward::AddRecommendeeRewardItemNoAuth( cltRewardItem* pclRewardItem )
{
	if ( NULL == pclRewardItem )
	{
		return false;
	}

	// ������ ���� �迭�ε����� ���� ����
	SI32 siLevel = pclRewardItem->GetPara1();
	if ( (0 > siLevel) || (Const_Max_RecommandReward_Item <= siLevel) )
	{
		return false;
	}

	//m_siRecommendeeGiveItemMaxLevel = siLevel;

	SI32 siItemUnique	= pclRewardItem->GetItemUnique();
	SI32 siItemNum		= pclRewardItem->GetItemNum();

	if ( m_pclRecommendeeRewardNoAuth[siLevel] )
	{
#ifdef _DEBUG
		NTCHARString256 strMessage( TEXT("�ش� #level#�� �������� �̹� �����Ǿ� �ֽ��ϴ�") );
		strMessage.Replace( TEXT("#level#"), SI32ToString(siLevel) );

		MsgBox( TEXT("��õ�� ��� ���� ������ ����"), strMessage );
#endif

		return false;
	}

	m_pclRecommendeeRewardNoAuth[siLevel] = new cltRewardItem;
	if ( NULL == m_pclRecommendeeRewardNoAuth[siLevel] )
	{
		return false;
	}

	m_pclRecommendeeRewardNoAuth[siLevel]->Set( pclRewardItem );

	return true;

}

bool cltRecommendReward::AddRecommendeeRewardItem( cltRewardItem* pclRewardItem )
{
	if ( NULL == pclRewardItem )
	{
		return false;
	}

	// ������ ���� �迭�ε����� ���� ����
	SI32 siLevel = pclRewardItem->GetPara1();
	if ( (0 > siLevel) || (Const_Max_RecommandReward_Item <= siLevel) )
	{
		return false;
	}
	
	m_siRecommendeeGiveItemMaxLevel = siLevel;

	SI32 siItemUnique	= pclRewardItem->GetItemUnique();
	SI32 siItemNum		= pclRewardItem->GetItemNum();

	if ( m_pclRecommendeeReward[siLevel] )
	{
#ifdef _DEBUG
		NTCHARString256 strMessage( TEXT("�ش� #level#�� �������� �̹� �����Ǿ� �ֽ��ϴ�") );
		strMessage.Replace( TEXT("#level#"), SI32ToString(siLevel) );

		MsgBox( TEXT("��õ�� ��� ���� ������ ����"), strMessage );
#endif

		return false;
	}

	m_pclRecommendeeReward[siLevel] = new cltRewardItem;
	if ( NULL == m_pclRecommendeeReward[siLevel] )
	{
		return false;
	}

	m_pclRecommendeeReward[siLevel]->Set( pclRewardItem );

	return true;

}

void cltRecommendReward::SendRecommenderMessage( cltRewardItem* pclRewardItem, SI32 siPersonID, SI32 siLevel, bool _bAuth )
{
	if ( (NULL == pclRewardItem) || (0 >= siPersonID) || (0 >= siLevel) )
	{
		return;
	}

	cltServer*		pclserver	= (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	cltCharServer*	pclchar		= NULL;
	SI32			siCharID	= pclClient->pclCM->GetIDFromPersonID( siPersonID );
	if ( pclClient->pclCM->IsValidID(siCharID) )
	{
		pclchar = pclClient->pclCM->GetCharServer(siCharID);
	}

	SI32 siItemUnique	= pclRewardItem->GetItemUnique();
	SI32 siItemNum		= pclRewardItem->GetItemNum();

	// ���� ���� ��
	if ( pclchar )
	{
#ifdef USE_PROMOTOR_SERVER 
		//pclserver->SendServerResponseMsg(0, SRVAL_PROMOTER_NOT_CELLULAR_PHONE_AUTH, siItemUnique, 1, pclchar->GetCharUnique()); 
		TCHAR*	pszItemName	= (TCHAR*)pclClient->pclItemManager->GetName( siItemUnique );
		NTCHARString64 strItemName;
		
		SI16 siSrval = 0;
		if( _bAuth )	
		{
			siSrval = SRVAL_RECOMMEND_GIVE_ITEM_SUCCEED;
			strItemName = "Y";
		}
		else			
		{
			siSrval = SRVAL_RECOMMEND_GIVE_ITEM_SUCCEED_NO_AUTH;
			strItemName = "N";
		}

		strItemName += pszItemName;

		pclserver->SendServerResponseCharMsg2( 0, siSrval, NULL, strItemName, SI32ToString(siItemNum), pclchar->GetCharUnique() );
#else
		pclserver->SendServerResponseMsg( 0, SRVAL_GIVEITEM_RECOMMANDER, siLevel, siItemUnique, pclchar->GetCharUnique() );
#endif
		
	}
	// ���� ���� �ƴҶ�
	else
	{
		cltLetterMsg_LevelUpREcommandReward clletter( siLevel, siItemUnique, siItemNum );
		pclserver->SendLetterMsg( siPersonID, (cltLetterHeader*)&clletter );			
	}

	if ( pclClient->IsWhereServiceArea(ConstSwitch_NewLog) ) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 19] // ����õ�� ����.
		// param1 == ������ ����ũ.
		// param2 == ������ ����.
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_COMMENDER_REWARD, 
			0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			siItemUnique, siItemNum, 0, 0, 0, NULL, NULL);
	}
}

void cltRecommendReward::SendRecommendMessage( cltRewardItem* pclRewardItem, SI32 siPersonID, SI32 siLevel, TCHAR* pszRecommenderName, bool _bAuth  )
{
	if ( (NULL == pclRewardItem) || (0 >= siPersonID) || (0 >= siLevel) )
	{
		return;
	}

	cltServer*		pclserver	= (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	cltCharServer*	pclchar		= NULL;
	SI32			siCharID	= pclClient->pclCM->GetIDFromPersonID( siPersonID );
	if ( pclClient->pclCM->IsValidID(siCharID) )
	{
		pclchar = pclClient->pclCM->GetCharServer(siCharID);
	}

	SI32 siItemUnique	= pclRewardItem->GetItemUnique();
	SI32 siItemNum		= pclRewardItem->GetItemNum();

	TCHAR*	pszItemName	= (TCHAR*)pclClient->pclItemManager->GetName( siItemUnique );

	NTCHARString64 strRecommenderName( pszRecommenderName );

	// ���� ���� ��
	if ( pclchar )
	{
		NTCHARString64 strItemName;
#ifdef USE_PROMOTOR_SERVER 
		//pclserver->SendServerResponseMsg(0, SRVAL_PROMOTER_NOT_CELLULAR_PHONE_AUTH, 1, 1, pclchar->GetCharUnique()); 
	
		SI16 siSrval = 0;
		if( _bAuth )	
		{
			strItemName = "Y";
			siSrval = SRVAL_RECOMMENDEE_GIVE_ITEM_SUCCEED;
		}
		else			
		{
			strItemName = "N";
			siSrval = SRVAL_RECOMMENDEE_GIVE_ITEM_SUCCEED_NO_AUTH;
		}

		strItemName += pszItemName;

		pclserver->SendServerResponseCharMsg2( 0, siSrval, pszRecommenderName, strItemName, SI32ToString(siItemNum), pclchar->GetCharUnique() );		
#else
		pclserver->SendServerResponseCharMsg2( 0, SRVAL_GIVEITEM_RECOMMAND, pszRecommenderName, SI32ToString(siLevel), strItemName, pclchar->GetCharUnique() );		
#endif
	}
	// ���� ���� �ƴҶ�
	else
	{
		cltLetterMsg_LevelUpREcommandRewardForRecommender clletter( strRecommenderName, siLevel, siItemUnique, siItemNum );
		pclserver->SendLetterMsg( siPersonID, (cltLetterHeader*)&clletter );
	}

}

//----------------------------------------------------------------------------------
// ���� ������� �޴���
//----------------------------------------------------------------------------------
cltRewardMgr::cltRewardMgr()
{
	Init();
}

cltRewardMgr::~cltRewardMgr()
{

}

void cltRewardMgr::Init()
{
	ZeroMemory( this, sizeof(cltRewardMgr) );
}

void cltRewardMgr::LoadRewardList()
{
	m_clCreateCharReward.LoadRewardItemList();
	m_clRecommendReward.LoadRewardItemList();
}

void cltRewardMgr::GiveCreateCharRewardItem( SI32 siPersonID )
{
	m_clCreateCharReward.GiveRewardItem( siPersonID );
}

bool cltRewardMgr::GiveRecommendRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName, bool _bAuth  )
{
	// �߱��� �ƴ� �������� ��� �ڵ��� ������ ���������� ����.
	if(false == pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina) ) _bAuth = true;

	return m_clRecommendReward.GiveRewardItem( siPersonID, siLevel, bGiveMode, pszRecommenderName, _bAuth );
}

bool cltRewardMgr::IsGiveRecommendRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName )
{
	return m_clRecommendReward.IsGiveRewardItem( siPersonID, siLevel, bGiveMode, pszRecommenderName );
}

cltRewardItem**	cltRewardMgr::GetRecommendRewardItemList( void )
{
	return m_clRecommendReward.GetRecommendRewardList();
}

cltRewardItem** cltRewardMgr::GetRecommendeeRewardItemList( void )
{
	return m_clRecommendReward.GetRecommendeeRewardList();
}


