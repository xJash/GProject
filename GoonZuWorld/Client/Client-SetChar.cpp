//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"


//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Order\Order.h"
#include "..\Common\Smoke\Smoke.h"
#include "..\Common\Map\Map.h"
#include "Char\CharClient\Char-Client.h"
#include "Char\CharManager\CharManager.h"

// Client
#include "Client.h"
#include "Music\Music.h"
#include "Effect\Regeneration\Regeneration.h"

// CommonLogic
#include "MsgType-System.h"

// Server
#include "..\Server\Candidate\Candidate.h"


#include "..\resource.h"




extern cltCommonLogic* pclClient;


//------------------------------------------
// SetChar
//-------------------------------------------

// ĳ���͸� ������ �� ���� �� �ֵ��� ���ۿ� �ִ´�. 
BOOL cltClient::PushChar(cltMakeCharInfo* pclinfo)
{
	if(siSetCharBufferIndex >= MAX_SETCHAR_RESERVE_NUMBER)
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("PushCharBufferFull"));
		return FALSE;
	}

	memcpy(&cltSetCharBuffer[siSetCharBufferIndex],  pclinfo, sizeof(cltMakeCharInfo));

	siSetCharBufferIndex++;

	return TRUE;
}

BOOL cltClient::PopChar(cltMakeCharInfo* pclinfo)
{
	SI32 i;

	if(siSetCharBufferIndex == 0)return FALSE;
	// ���� �ǹ� ������ �����κ��� ���⸦ ��ٸ��� ���̶�� ĳ���͸� �����ؼ��� �ȵȴ�. 
	// ĳ���Ͱ� ���� ��������� ���߿� �������� �ǹ��� ���� ������ �� �ֱ� �����̴�. 
	if(bWaitVillageStructureInfoSwitch == true)return FALSE;

#ifdef _SAFE_MEMORY
	memcpy(pclinfo, &cltSetCharBuffer[0], sizeof(cltMakeCharInfo));
#else
	memcpy(pclinfo, cltSetCharBuffer, sizeof(cltMakeCharInfo));
#endif
	for(i = 1; i < siSetCharBufferIndex;i++)
	{
		memcpy(&cltSetCharBuffer[i - 1], &cltSetCharBuffer[i], sizeof(cltMakeCharInfo));
	}

	siSetCharBufferIndex --;

	return TRUE;
}

// ���� ����� ĳ���Ϳ��� Ư�� ĳ���͸� �����Ѵ�. 
bool cltClient::DeleteReservedChar(SI32 charunique)
{

	SI32 i;

	for(i = 0; i < siSetCharBufferIndex;i++)
	{
		if((SI32)cltSetCharBuffer[i].uiMakeCharUnique == charunique)
		{
			memcpy(&cltSetCharBuffer[i], &cltSetCharBuffer[siSetCharBufferIndex-1], sizeof(cltMakeCharInfo));
			--siSetCharBufferIndex;
			return true;
		}
	}

	return false;
}

// ���鵵�� ����Ǿ� �ִ� ĳ���͸� �����. 
BOOL cltClient::SetCharReservedChar()
{
	SI32 id;
	cltMakeCharInfo clinfo;
	TCHAR buffer[256];

	// ���� ������ ���� ���ߴٸ� ĳ���͸� �������� �ʴ´�. 
	if(bReceiveServerInfoSwitch == false)return FALSE;

	while(PopChar(&clinfo) == TRUE)
	{
		// ������ �� ĳ���Ͱ� �ߺ��Ǿ� �ִ� ���� �ƴ��� Ȯ���Ѵ�. 
		id = cltCharCommon::CharUniqueInfo[ clinfo.uiMakeCharUnique] ;
		if(id)
		{
			// �� �������� ������ �����Ѵ�. 
			pclCM->CR[id]->DeleteInCell();
			pclCM->DeleteChar(id);
		}

		// �Ѱ��� ���� ���� �̿��� ĳ���ʹ� ������ �ʴ´�. 
		if((SI32)clinfo.uiMapIndex != pclMapManager->CurrentMapIndex)
		{
			continue;
		}

		if(MyCharUnique == (SI32)clinfo.uiMakeCharUnique)
		{
			id = 1;
		}
		else
		{
			id = pclCM->pclIDManager->GetID(0);
		}

		id = SetChar(id, &clinfo);

		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];
		if(pclchar == NULL)
		return false;

		if ( id != 1 )
		{
			pclchar->MakeRankMarkEncBuffer();
		}

		if(id)
		{
			//---------------------------------
			// ���� ���ϸ��̼�
			//---------------------------------

			pclchar->siPersonalMakeItemType = clinfo.siMakeAniType;
			
			pclchar->SetEnchantEffect(clinfo.siMakeAniType);

			//---------------------------------
			// �ź� 
			//---------------------------------
			pclchar->pclCI->clCharRank.Set(&clinfo.clRank);
			pclchar->pclBoss->Set(clinfo.clRank.GetRankType());
			
			//---------------------------------
			// ���� ȿ�� 
			//---------------------------------
			if(id == 1)
			{
				pclchar->SetCharRegeneration();
			}

			pclchar->pclCI->clBI.clGuildRank.Set(&clinfo.clGuildRank);
			
			// Ŭ���̾�Ʈ ������� ��� ���� ����� �����Ѵ�. 
			pclchar->SetGameMasterLevel(clinfo.siGameMasterLevel);
			pclchar->SetRareItemRate(0,0,0,0);
			pclchar->SetWennyOldMan(false,false);
		}


		// �����κ��� ���� ������ �ٰŷ� ĳ���͸� �����. 
		if((SI32)clinfo.uiMakeCharUnique == MyCharUnique )
		{

			// ���ΰ� ĳ������ ������ �޾Ҵ� ���¸�, 
			if(bReceiveMyCharAllInfoSwitch == true)
			{
				// ����� ������ �ִٸ�, 
				if(bBackUpSwitch == true)
				{
					//-------------------------------------------------------------------------------------------------
					pclchar->pclCI->Set(&pclHeroDataBackup->clMyCharPersonInfo);
					pclchar->siWarEnemyKillNumber				= pclHeroDataBackup->siWarEnemyKillNumber;
					pclchar->siWarKilledNumber					= pclHeroDataBackup->siWarKilledNumber;
					pclchar->siBlackArmyWarMapIndex				= pclHeroDataBackup->siBlackArmyWarMapIndex;

					//-------------------------------------------------------------------------------------------------
					pclchar->siBlackWarEnemyKillNumber			= pclHeroDataBackup->siBlackWarEnemyKillNumber;
					pclchar->siBlackWarKilledNumber				= pclHeroDataBackup->siBlackWarKilledNumber;

					//-------------------------------------------------------------------------------------------------
					//[�߰� : Ȳ���� 2008. 1. 28 => ���� ���� ���� ���� ���]
					pclchar->siBlackWarEnemyKillScore			= pclHeroDataBackup->siBlackWarEnemyKillScore;	       
					pclchar->siBlackWarEnemyKillVillageScore	= pclHeroDataBackup->siBlackWarEnemyKillVillageScore;

					//-------------------------------------------------------------------------------------------------
					pclchar->bStartMakeItemSwitch				= pclHeroDataBackup->bStartMakeItemSwitch;
					pclchar->dwStartMakeItemClock				= pclHeroDataBackup->dwStartMakeItemClock;
					pclchar->dwDelayMakeItemClock				= pclHeroDataBackup->dwDelayMakeItemClock;
					
					//-------------------------------------------------------------------------------------------------
					pclchar->ActiveWeapon						= pclHeroDataBackup->siOldActiveWeapon;
				
					//-------------------------------------------------------------------------------------------------
					pclchar->ActiveClothes						= pclHeroDataBackup->siOldActiveClothes;
					pclchar->ActiveHat							= pclHeroDataBackup->siOldActiveHat;
					pclchar->siCurrentMagic						= pclHeroDataBackup->siOldCurrnetMagic;
					pclchar->siCurrentMagicCastType				= pclHeroDataBackup->siOldCurrnetMagicCastType;
					
					//-------------------------------------------------------------------------------------------------
					pclchar->clPB.BasicMoveSpeed				= pclHeroDataBackup->siOldBasicMoveSpeed;
					pclchar->clPB.ShoesMoveSpeed				= pclHeroDataBackup->siOldShoesMoveSpeed;
					pclchar->clPB.TotalMoveSpeed				= pclHeroDataBackup->siOldTotalMoveSpeed;
					pclchar->clPB.GivenMoveSpeed				= pclHeroDataBackup->siOldGivenMoveSpeed;
/*
					pclchar->clPB.siGuildStr = pclHeroDataBackup->siGuildOldStr;
					pclchar->clPB.siGuildDex = pclHeroDataBackup->siGuildOldDex;
					pclchar->clPB.siGuildMag = pclHeroDataBackup->siGuildOldMag;
					pclchar->clPB.siGuildVit = pclHeroDataBackup->siGuildOldVit;
					pclchar->clPB.siGuildHnd = pclHeroDataBackup->siGuildOldHnd;
					pclchar->clPB.siGuildLuck = pclHeroDataBackup->siGuildOldLuck;
*/
					//-------------------------------------------------------------------------------------------------
					pclchar->clPB.clGuildBA.Set(&pclHeroDataBackup->clGuildOldBA);
					
					//-------------------------------------------------------------------------------------------------
					//�������� �������� ���� �ϴ� ������ �ƴϴ�.
					pclchar->clAddInfo.Set(&pclHeroDataBackup->clOldAddInfo);
					pclchar->pclCI->clItemMall.Set(&pclHeroDataBackup->clOldItemMall); // ������ �� ���� ������
					//pclchar->pclCI->clLimitDateItem.Set(&pclHeroDataBackup->clOldLimitDateItemInfo);
					
					//-------------------------------------------------------------------------------------------------
					//[����] ��������.  �������� ĳ���� �ʱ�ȭ�� �̷���� �� ����� ������ ����. => 2008-4-3.
					if(pclchar->pclSpaceBoxItem)	memcpy(pclchar->pclSpaceBoxItem,    &pclHeroDataBackup->clSpaceBoxItem,    sizeof(pclchar->pclSpaceBoxItem));
					if(pclchar->pclTreasureBoxItem)	memcpy(pclchar->pclTreasureBoxItem, &pclHeroDataBackup->clTreasureBoxItem, sizeof(pclchar->pclTreasureBoxItem));

					pclchar->m_clMagicBufMgr.Set( &pclHeroDataBackup->clOldMagicBufMgr );

					// ä�� ���� ���ѽð� ����
					memcpy(&pclchar->m_stMuteTime, &pclHeroDataBackup->stMuteTime, sizeof(pclchar->m_stMuteTime));
					// �߷�Ÿ�ε��� ���� 
					pclchar->pclValentineWar->Set( &pclHeroDataBackup->clValentinewarinfo);

					pclchar->pclPVP_LeagueInfo->Set( &pclHeroDataBackup->clPVP_LeagueInfo);
				}
			}
			else
			{
				// ���ΰ� ĳ������ ��� ������ ������ ��û�Ѵ�. 
				// Importantparameta, Skill���� ������ �ش�ȴ�.
				cltMsg clMsg(GAMEMSG_REQUEST_ALLCHARINFO, 0, NULL);
				SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		else if(pclchar->clIdentity.siIdentity == IDENTITY_VILLAGEGOD)
		{
			TCHAR* pText = GetTxtFromMgr(847);
			

			StringCchPrintf(buffer, 256, TEXT("%s %s"),  pText, pclchar->pclKI->GetName());
			pclchar->SetName(buffer);
		}
		else if(pclchar->clIdentity.siIdentity == IDENTITY_VILLAGEGOD_SUMMON)
		{
			pclchar->TransMode = TRANSPARENT_MODE_SCREEN;
		}
		else if(pclchar->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
		{
			SI32 siparentid = pclchar->GetSummonParentID();
			if(pclCM->IsValidID(siparentid) == TRUE)
			{
				cltCharClient* pclparentchar = (cltCharClient*)pclCM->CR[siparentid];
				cltSummon *pclSummon = pclparentchar->pclCI->clSummonInfo.GetSummon(pclchar->GetSummonIndex());
				if(pclSummon)	StringCchPrintf(buffer, 256, TEXT("%s"),  pclSummon->szName);
				else 
				{
					TCHAR* pText = GetTxtFromMgr(449);
					

					StringCchPrintf(buffer, 256, TEXT("%s"),  pText);
				}

				cltKindInfo * pclsummoninfo = pclKindInfoSet->pclKI[pclSummon->siKind];
				if ( pclsummoninfo == NULL ) return false ;
			}
			else
			{
				StringCchPrintf(buffer, 256, TEXT("%s"),  pclchar->pclKI->GetName());
			}
			pclchar->SetName(buffer);
			
			// ��ȯ�� �̸� IP�� ������ ���� ��û�Ѵ� 
			cltMsg clMsg(GAMEMSG_REQUEST_PERSON_IP, pclchar->GetCharUnique());
			SendMsgToServer((sPacketHeader*)&clMsg);
		}
		// [����] ��ȣ����_090525 : ��ȣ������ �̸����� ����
		else if ( IDENTITY_SOULGUARD == pclchar->clIdentity.siIdentity )
		{

		}



		//---------------------------------
		// �̿���� ����� ���� ȿ��. 
		//---------------------------------
		if(clinfo.uiTicketWarpSwitch)
		{
			SI32 centerx, centery;
			if(pclchar->pclMap->GetXYDotFromXYCord(pclchar->GetX(), pclchar->GetY(),  centerx, centery) == TRUE)
			{
				pclClient->pclSmokeManager->SetSmoke(SMOKE_ENDWARP, centerx, centery - 115, pclchar->pclMap);
			}
			
		}


	}

	return TRUE;
}


void cltClient::NPCMgr( )
{
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	TCHAR datfilename[MAX_PATH] = {0,};


	if( pclClient->siServiceArea ==  ConstServiceArea_Korea )	// �ѱ�
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrK.txt") );
	}
	else if( pclClient->siServiceArea ==  ConstServiceArea_English )
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrE.txt") );
	}
	else if(pclClient->siServiceArea ==  ConstServiceArea_China )
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrC.txt") );
	}
	else if(pclClient->siServiceArea ==  ConstServiceArea_Japan )
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrJ.txt") );
	}
	else if(pclClient->siServiceArea ==  ConstServiceArea_Taiwan )
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrT.txt") );
	}
	else if(pclClient->siServiceArea ==  ConstServiceArea_USA  )
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrU.txt") );
	}
	else if( pclClient->siServiceArea ==  ConstServiceArea_NHNChina )
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrC.txt") );
	}
	else if( pclClient->siServiceArea ==  ConstServiceArea_EUROPE )
	{
		StringCchPrintf(datfilename,  MAX_PATH, TEXT("TextMgr\\NPCMgrG.txt") );
	}

	//KHY - 0809 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( datfilename );		
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( datfilename );
		}
		else
		{
			bLoadFile = dataloader.LoadDataFromFile( datfilename );
		}
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("LoadNpcMgr()"), TEXT("LoadError:[%s]"), datfilename);
		return;
	}

	for ( SI32 i = 0 ; i < MAX_NPCKINDFORRANKMARK ; i ++ )
	{
		StringCchCopy(m_NPCName[i], 64, TEXT(""));
		m_NPCImgIndex[i]=0;		
	}

	SI32	siindex = 0;
	TCHAR	szname[128] = {0,};
	SI32	sikind =0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siindex,	4,		
			NDATA_MBSTRING,	szname,	64,
			NDATA_INT32,	&sikind, 4,
			0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	SI32 index = 0;

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData())
		{
			StringCchCopy( m_NPCName[index], 64, szname );
			m_NPCImgIndex[index] = sikind;
			index++;
		}
	}



	//TCHAR buffer[1024] = TEXT("");
	//FILE* fp= NULL;

	//if( pclClient->siServiceArea ==  ConstServiceArea_Korea )	// �ѱ�
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrK.txt"), TEXT("rt"));
	//}
	//else if( pclClient->siServiceArea ==  ConstServiceArea_English )
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrE.txt"), TEXT("rt"));
	//}
	//else if(pclClient->siServiceArea ==  ConstServiceArea_China )
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrC.txt"), TEXT("rt"));
	//}
	//else if(pclClient->siServiceArea ==  ConstServiceArea_Japan )
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrJ.txt"), TEXT("rt"));
	//}


	//if(fp == NULL)
	//{
	//	MsgBox(TEXT("fileError"), TEXT("not NPCMgrtextFile"));
	//	return ;
	//}

	//// ���Ǿ� �ؽ�Ʈ�� 4���� �ּ����� �����Ѵ�.
	//for(SI32 i = 0;i < 4;i++)
	//	_fgetts(buffer, 1024, fp);

	//for ( i = 0 ; i < MAX_NPCKINDFORRANKMARK ; i ++ )
	//{
	//	StringCchCopy(m_NPCName[i], 64, TEXT(""));
	//	m_NPCImgIndex[i]=0;		
	//}


	//i = 0 ;

	//while( _fgetts(buffer, 1024, fp) != NULL)
	//{
	//	if ( i >= MAX_NPCKINDFORRANKMARK ) break ;

	//	TCHAR * szindex;
	//	TCHAR * szname;
	//	TCHAR * szkind;

	//	szname = _tcstok(buffer, TEXT("\t"));
	//	szkind = _tcstok(NULL,TEXT("\r\n"));

	//	if ( !szname || !szkind ) break ;
	//	{

	//		szindex= _tcstok(szname,TEXT(":"));
	//		szname =_tcstok(NULL,TEXT(" ") );
	//		StringCchCopy(m_NPCName[i], 64, szname);
	//	}
	//	m_NPCImgIndex[i] = _tstoi(szkind);
	//	i ++ ;
	//}

	//fclose(fp);	
}
