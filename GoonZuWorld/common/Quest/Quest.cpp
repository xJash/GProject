//---------------------------------
// 2003/11/24 ���°�
//---------------------------------
#include "CommonLogic.h"
#include "Char\CharCommon\Char-Common.h"

#include "Quest.h"
#include "..\resource.h"
#include "MsgType-Person.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\Server\GameDBProcess\GameDBProcess.h"
#include "../Server/Server.h"
#include "../common/Skill/Skill-Manager.h"

extern cltCommonLogic* pclClient;

// ���� ������ �ؽ�Ʈ�� ��Ƴ���. 
bool cltQuestRewardInfo::GetExplainText(TCHAR* ptext, SI16 txtSize)
{
	TCHAR temp[256];

	StringCchCopy(ptext, txtSize, TEXT(""));

	if(siExp)
	{
		TCHAR* pText= GetTxtFromMgr(3090);
		StringCchPrintf(temp, 256, pText, siExp);
		StringCchCat(ptext, txtSize, temp);
	}
	if(siMoney)
	{
		GMONEY siGetMoney = siMoney;

		// ���� ��������� NPC Rate������ ����ȴٸ�
		if ( true == bApplyNpcRate )
		{
			SI64 siNPCPriceRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			siGetMoney = siGetMoney * siNPCPriceRate / 100;
		}

		// ȭ����� �޸� ǥ��
		TCHAR szPrice[64] = { '\0', };
		g_JYLibFunction.SetNumUnit(siGetMoney, szPrice, sizeof(szPrice));

		// ���� ȭ�� �Է�
		NTCHARString128	strMoney( GetTxtFromMgr(3091) );
		strMoney.Replace( TEXT("#money#"), szPrice );

		StringCchCat(ptext, txtSize, strMoney);
	}
	if(siItemUnique[0])
	{
		// [����] ��� �������� �������� �޽����� �ٸ��� �Ѵ�
		const TCHAR* pitemname = pclClient->pclItemManager->GetName(siItemUnique[0]);

		if ( bIsGetMaterial == false )
		{
			TCHAR* pText= GetTxtFromMgr(3092);

			StringCchPrintf( temp, 256, pText, pitemname, siItemNum[0] );
			StringCchCat( ptext, txtSize, temp );
		}
		else
		{
			NTCHARString64 kText( GetTxtFromMgr(8077) );
			
			kText.Replace( TEXT("#itemname#"), pitemname );
			StringCchCat( ptext, txtSize, kText );
		}

	}
	if(siItemUnique[1])
	{
		const TCHAR* pitemname = pclClient->pclItemManager->GetName(siItemUnique[1]);
		TCHAR* pText= GetTxtFromMgr(3092);
		StringCchPrintf(temp, 256, pText, pitemname, siItemNum[1]);
		StringCchCat(ptext, txtSize, temp);
	}
	if(siItemUnique[2])
	{
		const TCHAR* pitemname = pclClient->pclItemManager->GetName(siItemUnique[2]);
		TCHAR* pText= GetTxtFromMgr(3092);
		StringCchPrintf(temp, 256, pText, pitemname, siItemNum[2]);
		StringCchCat(ptext, txtSize, temp);
	}
	if(siItemUnique[3])
	{
		const TCHAR* pitemname = pclClient->pclItemManager->GetName(siItemUnique[3]);
		TCHAR* pText= GetTxtFromMgr(3092);
		StringCchPrintf(temp, 256, pText, pitemname, siItemNum[3]);
		StringCchCat(ptext, txtSize, temp);
	}
	if(siItemUnique[4])
	{
		const TCHAR* pitemname = pclClient->pclItemManager->GetName(siItemUnique[4]);
		TCHAR* pText= GetTxtFromMgr(3092);
		StringCchPrintf(temp, 256, pText, pitemname, siItemNum[4]);
		StringCchCat(ptext, txtSize, temp);
	}
	if(siFameExp)
	{
		TCHAR* pText= GetTxtFromMgr(3093);
		StringCchPrintf(temp, 256, pText, siFameExp);
		StringCchCat(ptext, txtSize, temp);
	}
	if(siNCoin)
	{
		TCHAR* pText= GetTxtFromMgr(3094);
		StringCchPrintf(temp, 256, pText, siNCoin);
		StringCchCat(ptext, txtSize, temp);
	}
	// ��ų ����ġ
	if ( (siSkillExp>0) && (siSkillType>0) )
	{
		NTCHARString128	kSkillExplain( GetTxtFromMgr(8362) );
		TCHAR			szSkillName[MAX_SKILL_NAME_LENGTH] = {'\0',};

		if ( pclClient->pclSkillManager->GetSkillName( siSkillType, szSkillName ) == true )
		{
			kSkillExplain.Replace( TEXT("#skilltype#"), szSkillName );
			kSkillExplain.Replace( TEXT("#skillexp#"), SI32ToString(siSkillExp) );

			StringCchCat( ptext, txtSize, kSkillExplain );
		}
	}
	// �̵��ӵ�
	if(bMoveBuf)
	{
		TCHAR* pText= GetTxtFromMgr(6409);		
		StringCchCat(ptext, txtSize, pText);
	}
	// [����] : ����� ����
	if ( true == bDeBuff )
	{
		// ���� ������ ���� ���� �޼����� �־�� ������ ������ �ϴ��� �ٸ� ��ȭ���ڿ��� ��� �޼����� ����ֱ� ������ ���� �����Ѵ�
		// 		TCHAR* pText = GetTxtFromMgr();
		// 		StringCchCat( ptext, txtSize, pText );
	}

	return true;

}


//--------------------------------------------
// cltPQuestInfo
//--------------------------------------------
// Ư�� Ÿ���� ����Ʈ�� �������̰ų� ����� ���� �ִ��� Ȯ���Ѵ�. 
bool cltPQuestInfo::IsQuestClearOrGoing(SI32 questtype)
{

	if(questtype < 0 || questtype >= MAX_QUEST_TYPE)return false;
	
	//Clear�� ���� �ֵ�. 
	if(clUnit[questtype].siQuestState)return true;

	// ���� �������� ���� �ֵ�. 
	if(clUnit[questtype].siCurQuestUnique)return true;

	return false;

}

// Ư�� ����Ʈ�� ���������� Ȯ���Ѵ� 
bool cltPQuestInfo::IsQuestGoing(SI32 clearcond, SI16* ptype, SI16* punique, SI16* ppara1, SI16* ppara2, SI32* pstartindex)
{
	SI32 i;
	cltQuestInfoCommon* pclquestinfo ;

	SI32 startpos = 0;
	if(pstartindex)			{		startpos = *pstartindex;		}

	for(i = startpos;i < MAX_QUEST_TYPE;i++)
	{
		if(clUnit[i].siCurQuestUnique == 0)									continue;

		switch(i)
		{
		case QUEST_TYPE_SPECIAL:		pclquestinfo = &clSpecialQuestInfo;				break;
		case QUEST_TYPE_NAMING:			pclquestinfo = &clNamingQuestInfo;				break;
		case QUEST_TYPE_HAPPYBEAN:		pclquestinfo = &clHappyBeanQuestInfo;			break;
		case QUEST_TYPE_MISSION1:		pclquestinfo = &clMissionQuestInfo;				break;
		default:						pclquestinfo = pclClient->pclQuestManager->GetQuestInfo( clUnit[i].siCurQuestUnique );	break;
		}
		
		if(pclquestinfo == NULL)											continue;
		if(pclquestinfo->clQuestClearConditionInfo.siFlag != clearcond)		continue;

		if(ptype)	*ptype		= i;
		if(punique)	*punique	= pclquestinfo->siUnique;
		if(ppara1)	*ppara1		= pclquestinfo->clQuestClearConditionInfo.siPara1;
		if(ppara1)	*ppara2		= pclquestinfo->clQuestClearConditionInfo.siPara2;

		if(pstartindex)		{		*pstartindex = i + 1;			}

		return true;
	}

	if(pstartindex)			{		*pstartindex = 0;				}

	return false;
}

bool cltPQuestInfo::IsQuestGoing( SI32 siClearCondition )
{
	SI16 siType		= 0;
	SI16 siUnique	= 0;
	SI16 siPara1	= 0;
	SI16 siPara2	= 0;

	return IsQuestGoing( siClearCondition, &siType, &siUnique, &siPara1, &siPara2 );
}

bool cltPQuestInfo::IsSameParaQuestGoing( SI32 siClearCond, SI16 siPara1, SI16 siPara2/* =0  */)
{
	cltQuestInfoCommon* pclQInfo = NULL;

	for ( SI32 siIndex=0; siIndex<MAX_QUEST_TYPE; siIndex++ )
	{
		// ���� ����Ʈ�� �������� �ƴ϶��
		if ( 0 == clUnit[siIndex].siCurQuestUnique )
		{
			continue;
		}

		// ����Ʈ �ܰ谡 ������ Going������ �۵��ȴ�
		if ( QUEST_STEP_MIDDLE != clUnit[siIndex].siCurQuestStep )
		{
			continue;
		}

		switch ( siIndex )
		{
		case QUEST_TYPE_SPECIAL:	pclQInfo = &clSpecialQuestInfo;																break;
		case QUEST_TYPE_NAMING:		pclQInfo = &clNamingQuestInfo;																break;
		case QUEST_TYPE_HAPPYBEAN:	pclQInfo = &clHappyBeanQuestInfo;															break;
		case QUEST_TYPE_MISSION1:	pclQInfo = &clMissionQuestInfo;																break;
		default:					pclQInfo = pclClient->pclQuestManager->GetQuestInfo( clUnit[siIndex].siCurQuestUnique );	break;
		}

		if ( NULL == pclQInfo )
		{
			continue;
		}

		if ( siClearCond != pclQInfo->clQuestClearConditionInfo.siFlag )
		{
			continue;
		}

		if ( siPara1 != pclQInfo->clQuestClearConditionInfo.siPara1 )
		{
			continue;
		}

		if ( (0 < siPara2) && (siPara2 != pclQInfo->clQuestClearConditionInfo.siPara2) )
		{
			continue;
		}

		return true;
	}

	return false;
}


// �Ķ��Ÿ�� ������Ų��. 
bool cltPQuestInfo::IncPara(SI32 questtype, SI32 para1, SI32 incnum)
{
	cltQuestInfoCommon* pclquestinfo ;

	if(clUnit[questtype].siCurQuestUnique == 0)return false;
	
	// Ư�� ����Ʈ�̸�, 
	switch( questtype )
	{
	case QUEST_TYPE_SPECIAL:		pclquestinfo = &clSpecialQuestInfo;			break;
	case QUEST_TYPE_NAMING:			pclquestinfo = &clNamingQuestInfo;			break;
	case QUEST_TYPE_HAPPYBEAN:		pclquestinfo = &clHappyBeanQuestInfo;		break;
	case QUEST_TYPE_MISSION1:		pclquestinfo = &clMissionQuestInfo;			break;
	default:						pclquestinfo = pclClient->pclQuestManager->GetQuestInfo( clUnit[questtype].siCurQuestUnique );	break;
	}
	
	if(pclquestinfo == NULL)return false;
	
	// ��� ���Ϳ� ��ġ�ؾ� �Ѵ�. 
	// ����Ʈ �Ϸ� ������ ��� ����ũ�� �������(0) ���� ����

	if ( pclquestinfo->clQuestClearConditionInfo.siPara1 != 0 && pclquestinfo->clQuestClearConditionInfo.siPara1 != para1 ) return false;
	
	if ( MAX_SI16 < (clUnit[questtype].siQuestPara2 + incnum) )
	{
		clUnit[questtype].siQuestPara2 = MAX_SI16;
	}
	else
	{
		clUnit[questtype].siQuestPara2 += incnum;
	}
	
	return true;
}


// �������� ����Ʈ�� DB�� �����Ѵ�. 
bool cltPQuestInfo::SaveGoingQuestToDB(cltCharCommon* pclchar)
{
	SI32 i;
	cltQuestInfoCommon* pclquestinfo = NULL;

	for(i = 0;i < MAX_QUEST_TYPE;i++)
	{
		if(clUnit[i].siCurQuestUnique == 0)continue;

		switch( i )
		{
		case QUEST_TYPE_SPECIAL:		pclquestinfo = &clSpecialQuestInfo;		break;
		case QUEST_TYPE_NAMING:			pclquestinfo = &clNamingQuestInfo;		break;
		case QUEST_TYPE_HAPPYBEAN:		pclquestinfo = &clHappyBeanQuestInfo;	break;
		case QUEST_TYPE_MISSION1:		pclquestinfo = &clMissionQuestInfo;		break;
		default:						pclquestinfo = pclClient->pclQuestManager->GetQuestInfo( clUnit[i].siCurQuestUnique );		break;
		}

		if(pclquestinfo == NULL)continue;

		// ����Ʈ�� �߰� ������ �Բ� �����Ѵ�.
		switch( i )
		{
		case QUEST_TYPE_NAMING:
			{
				// ��Ī ����Ʈ ������ DB�� �����Ѵ�.
				sDBRequest_SetNamingQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &clNamingQuestInfo );
				pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);
			}
			break;
		case QUEST_TYPE_MISSION1:
			{
				// �̼� ����Ʈ ������ DB�� �����Ѵ�.
				sDBRequest_SetMissionQuestInfo clMissionQuestInfo(pclchar->pclCI->GetPersonID(), &clMissionQuestInfo );
				pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);
			}
			break;
		}

		// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
		sDBRequest_SetQuestInfo clMsg(pclchar->pclCI->GetPersonID(), i,	&pclchar->pclCI->clQuestInfo.clUnit[i]);		
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}

	return true;
}

// Ư�� Ÿ���� ����Ʈ�� ��� �Ϸ�Ǿ����� Ȯ���Ѵ�. 
bool cltPQuestInfo::IsAllClear(cltQuestManager* pclquestmanager, SI32 questtype)
{
	SI32 i;
	SI32 count = 0;

	for(i = 0;i < MAX_QUEST_PER_TYPE_NUMBER;i++)
	{
		if(pclquestmanager->GetQuestUniqueFromBit(questtype, i))
		{
			SI32 data = clUnit[questtype].GetBit(i);
			if(data == 0)
			{
				return false;
			}

		}
	}

	return true;
}

// �Ϸ�� ����Ʈ�� ���� ���Ѵ�. 
SI32 cltPQuestInfo::GetClearQuestNum(cltQuestManager* pclquestmanager, SI32 questtype)
{
	SI32 i;
	SI32 count = 0;

	for(i = 0;i < MAX_QUEST_PER_TYPE_NUMBER;i++)
	{
		SI32 data = clUnit[questtype].GetBit(i);
		if(data)
		{
			if(pclquestmanager->GetQuestUniqueFromBit(questtype, i))
			{
				count++;
			}
		}
	}

	return count;
}

// Ư�� ����ũ�� ����Ʈ�� �����ߴ°�. 
bool cltPQuestInfo::IsClear(cltQuestManager* pclquestmanager, SI32 questunique)
{
	cltQuestInfo* pclquestinfo = pclquestmanager->GetQuestInfo(questunique);
	if(pclquestinfo == NULL)return false;

	// ����Ʈ�� Ÿ���� ���Ѵ�. 
	SI32 questtype = pclquestinfo->siType;

	// �ش� ����Ʈ Ÿ�Կ����� ��Ʈ�� ���Ѵ�. 
	SI32 bit  = pclquestmanager->GetBitFromUnique(questtype, questunique);

	if(clUnit[questtype].GetBit(bit))return true;

	return false;
}

// ��ι� ����Ʈ�� �ܾ� ���߱Ⱑ  �Ϸ�Ǿ��ٸ�, 
bool cltPQuestInfo::IsWordAssembleCompleted(cltQuestManager* pclQuestManager)
{
	if(pclQuestManager->siWordAssemblyNumber <= 0)return false;

	for(SI32 i = 0;i < pclQuestManager->siWordAssemblyNumber;i++)
	{
		if(bWordAssemblySwitch[i] == false)return false;
	}

	return true;
}

// �ܾ� ���� ������ �ʱ�ȭ�Ѵ�. 
void cltPQuestInfo::InitWordAssemble()
{
	for(SI32 i = 0;i < MAX_WORD_ASSEMBLY_CHAR_NUMBER;i++)
	{
		bWordAssemblySwitch[i] = false;
	}
}

bool cltPQuestInfo::GetWordAssembleText( cltQuestManager* pclQuestManager, TCHAR* pszBuffer, SI32 siBufferSize )
{
	if ( (NULL == pclQuestManager) || (NULL == pszBuffer) || (0 >= siBufferSize) )
	{
		return false;
	}

	TCHAR	szWord[256]		= { '\0', };
	SI32	siWordNumber	= pclQuestManager->siWordAssemblyNumber;

	for ( SI32 siIndex=0 ; siIndex<siWordNumber; ++siIndex )
	{
		if ( bWordAssemblySwitch[siIndex] )
		{
			StringCchCat( szWord, 256, pclQuestManager->szWordAssemblyString[siIndex] );
		}
		else
		{
			StringCchCat( szWord, 256, "?" );
		}

		StringCchCat( szWord, 256, " " );
	}


	TCHAR* pText = GetTxtFromMgr( 4383 );
	StringCchPrintf( pszBuffer, siBufferSize, pText, szWord );

	return true;
}

//--------------------------------------------
// cltQuestInfo
//--------------------------------------------
void cltQuestInfo::Set(SI32 type, SI32 unique, 
					   cltQuestInitConditionInfo* pclinitcond, 
					   cltQuestClearConditionInfo* pclclearcond, 
					   cltQuestRewardInfo* pclreward, 
					   TCHAR* titletext, 
					   TCHAR* pimagefilename)
{
	siType		= type;
	siUnique	= unique;

	// �ʱ�����. 
	clInitConditionInfo.Set(pclinitcond);

	// �Ϸ� ���� ����. 
	clQuestClearConditionInfo.Set(pclclearcond);

	// ���� ����. 
	clQuestRewardInfo.Set(pclreward);

	MStrCpy( szTitleText, titletext,	MAX_TITLE_TEXT_SIZE );

	if(pimagefilename)
	{
		pImageFileName = new TCHAR[_tcslen(pimagefilename) + 1];
		StringCchCopy(pImageFileName, _tcslen(pimagefilename) + 1, pimagefilename);
	}

}



