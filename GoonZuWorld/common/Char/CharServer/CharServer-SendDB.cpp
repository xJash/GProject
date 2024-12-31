//---------------------------------
// 2004/11/23 ���°�
//---------------------------------


//--------------------------------------
// Common
//--------------------------------------
#include "Char\CharServer\Char-Server.h"
#include "..\CharManager\CharManager.h"

//--------------------------------------
// Server
//--------------------------------------
#include "..\..\Server\Server.h"
#include "MsgRval-Define.h"


//--------------------------------------
// DBManager
//--------------------------------------
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Summon.h"

extern cltCommonLogic* pclClient;

// ��ġ, ü��, ������ ������ DB�� �����Ѵ�. 
void cltCharServer::SendDB_PosLifeMana()
{
	sDBRequest_SetPosLifeMana clMsg(pclCI->GetPersonID(), 
		&pclCI->clBI.clPos, 
		GetLife(), GetMana(), 
		pclCI->clBI.siPlaySecond, pclCI->clBI.siPlayEventSecond, 
		&pclCI->clBI.clLastMainMapPos);

	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// LEEKH MODIFY 2007.10.24
	//	// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ġ, ü��, ������ ������ DB�� ����.
	//	// param1 = Life, 
	//	// param2 = Mana, 
	//	// param3 = Map Index, 
	//	// param4 = Pos x, 
	//	// param5 = Pos y
	//	// charparam1 = "PlaySec = %d, PlayEventSec = %d"
	//	// charparam2 = ""
	//	TCHAR szCharParam1[50] = { '\0', };
	//	TCHAR szCharParam2[50] = { '\0', };
	//	StringCchPrintf(szCharParam1, sizeof(szCharParam1), TEXT("PlaySec = %d, PlayEventSec = %d"), pclCI->clBI.siPlaySecond, pclCI->clBI.siPlayEventSecond);
	//	StringCchPrintf(szCharParam2, sizeof(szCharParam2), TEXT(""));

	//	cltServer* pclserver = (cltServer*)pclClient;
	//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_SETPOSLIFEMANA,
	//									0, this, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
	//									GetLife(), GetMana(), pclCI->clBI.clPos.GetMapIndex(), pclCI->clBI.clPos.GetX(), pclCI->clBI.clPos.GetY(),
	//									szCharParam1, szCharParam2);
	//}
}

// level ������ DB�� �����Ѵ�. 
void cltCharServer::SendDBLevelInfo(SI32 incbonus, SI32 incskillbonus)
{
	if(IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique()))return ;
	if(pclCI->GetPersonID() <= 0)return ;

	//  �����ؾ� �� ������ �Ͻ� ����Ѵ�. 
	clOldLevelInfo.Set(pclCI->clIP.GetCurExp(), pclCI->clIP.GetLevel(), pclCI->clIP.GetBonus(), pclCI->clIP.GetSkillBonus(), pclCI->clIP.siFameExp, pclCI->clIP.siFameLevel);

	sDBRequest_SetLevelInfo clMsg( GetID(), 
		pclCI->GetPersonID(), 
		pclCI->clIP.GetCurExp(), 
		pclCI->clIP.GetLevel(), 
		pclCI->clIP.siFameExp,
		pclCI->clIP.siFameLevel, 
		incbonus, 
		incskillbonus,
		pclCI->clBI.siPlaySecond );

	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}


void cltCharServer::SendDBSkillExp()
{
	if(clSimpleVary.bSkillExpUpdateSwitch == false)return ;
	clSimpleVary.bSkillExpUpdateSwitch = false;

	//------------------------------------
	// ���� ����Ǿ� �ִ� ��� ����ġ�� ����Ѵ�.
	//------------------------------------
	for(SI32 i = 0; i < MAX_SKILL_NUMBER; ++i)
	{
		if(clSimpleVary.SkillUpdateSwitch[i] == true)
		{
			clSimpleVary.SkillUpdateSwitch[i] = false;

			sDBRequest_SetSkillExp clMsg(GetID(), pclCI->GetPersonID(), i, pclCI->clCharSkill.clSkill[i].siSkillExp);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 11] // ��ų ����ġ�� ����� ��.
			//	// param1 == ��� ����ũ, 
			//	// param2 == ��� ����ġ.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_SET_SKILL_EXP, 
			//									0, this, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									i, pclCI->clCharSkill.clSkill[i].siSkillExp, 0, 0, 0, NULL, NULL);
			//}
		}
	}
}

void cltCharServer::SendDBWasteDurability()
{

	if(clSimpleVary.bWasteDurSwitch == false)return ;
	clSimpleVary.bWasteDurSwitch = false;

	//------------------------------------
	// ���� ����Ǿ� �ִ� ��� ����ġ�� ����Ѵ�.
	//------------------------------------
	for(SI32 i = 0; i < MAX_ITEM_PER_PERSON; ++i)
	{
		if(clSimpleVary.WasteDurUpdateSwitch[i] == true)
		{
			clSimpleVary.WasteDurUpdateSwitch[i] = false;

			// DBManager���� �������� �Ҹ��� ���� ��û�Ѵ�. 
			sDBRequest_WasteDurability clMsg(GetID(), pclCI->GetPersonID(), i, &pclCI->clCharItem.clItem[i]);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			
		}
	}
}

void cltCharServer::SendDBSummonWasteDurability()
{
	for( SI32 j = 0; j < clSimpleVary.bSummonWasteDurSwitch.GetSize(); ++j )
	{
		if( clSimpleVary.bSummonWasteDurSwitch[j] == false )	continue;
		clSimpleVary.bSummonWasteDurSwitch[j] = false;

		for( SI32 i = 0; i < clSimpleVary.SummonWasteDurUpdateSwitch[j].GetSize(); ++i )
		{
			if( clSimpleVary.SummonWasteDurUpdateSwitch[j][i] == true)
			{
				clSimpleVary.SummonWasteDurUpdateSwitch[j][i] = false;

				cltSummon* pclsummon = pclCI->clSummonInfo.GetSummon( j );
				cltItem* pclItem = pclCI->clSummonInfo.GetSummonEquipItem( j, i );

				sDBRequest_SummonItem_StatusChange clMsg(GetID(), pclCI->GetPersonID(), pclsummon->siSummonID, i, pclItem, SUMMONITEM_STATUSCHANGE_REASON_NONE);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
	}
}

//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. 
void cltCharServer::SendDBCrystalDurability()
{
	if(clSimpleVary.bCrystalDurSwitch == false)return ;
	clSimpleVary.bCrystalDurSwitch = false;
	//------------------------------------
	// ���� ����Ǿ� �ִ� ����ü �������� ����Ѵ�.
	//------------------------------------
	for(SI32 i = 0; i < MAX_SHAPE_ITEM; ++i)
	{
		if(clSimpleVary.CrystalDurUpdateSwitch[i] == true)
		{
			clSimpleVary.CrystalDurUpdateSwitch[i] = false;

			// DBManager���� �������� �Ҹ��� ���� ��û�Ѵ�. 
			sDBRequest_CrystalDurability clMsg(GetID(), pclCI->GetPersonID(), i, &pclCI->clCharItem.clItem[i]);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);			
		}
	}
}

void cltCharServer::SendDBCrystalDurabilityForSummon()
{
	// �Ϲ����� ���� �˻�
	if ( false == clSimpleVary.bCheckFameLevelSwitch )
	{
		return;
	}
	clSimpleVary.bCheckFameLevelSwitch = false;

	SI32 siParentID = GetSummonParentID();
	if ( FALSE == pclCM->IsValidID(siParentID) )
	{
		return;
	}

	cltCharServer* pclParentChar = (cltCharServer*)pclCM->CR[siParentID];
	if ( NULL == pclParentChar )
	{
		return;
	}

	SI16 siSummonIndex = GetSummonIndex();
	if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}

	cltSummon* pclsummon = pclParentChar->pclCI->clSummonInfo.GetSummon( siSummonIndex );
	if( pclsummon == NULL )				return;

	SI32 siParentPersonID = pclParentChar->pclCI->GetPersonID();
	// �Ϲ����� ���� �˻�


	// �������� �������� ���� ��Ŵ
	for ( SI32 siIndex=0; siIndex<MAX_SHAPE_ITEM; ++siIndex )
	{
		if ( true == clSimpleVary.CrystalDurUpdateSwitch[siIndex] )
		{
			clSimpleVary.CrystalDurUpdateSwitch[siIndex] = false;

			cltItem* pclitem = pclParentChar->pclCI->clSummonInfo.GetSummonEquipItem( siSummonIndex, siIndex );
			if ( NULL == pclitem )
			{
				continue;
			}

			sDBRequest_SummonItem_StatusChange clMsg( siParentID, siParentPersonID, pclsummon->siSummonID, siIndex, pclitem, SUMMONITEM_STATUSCHANGE_REASON_DECREASE );
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);			
		}
	}

}

void cltCharServer::UpdateTakeOutSummon()
{
	SI32 siSummonID = GetSummonID();
	if(pclCM->IsValidID(siSummonID))	
	{
		// ���� �����ִ� ��ȯ���� ���� ���̶�� ������ Update��Ų��.
		SI32 siSummonIndex = pclCM->CR[siSummonID]->GetSummonIndex();
		cltSummon *pclSummon = pclCI->clSummonInfo.GetSummon(siSummonIndex);
		if(pclSummon)
		{
			pclSummon->clIP.Set(&pclCM->CR[siSummonID]->pclCI->clIP);
		}
	}
}

void cltCharServer::SendDBSummon(SI32 siReason, SI32 siSummonIndex)
{
	// ������ ������ ����� �ȵȴ�.
	if(siSummonIndex<0 || siSummonIndex>MAX_SUMMON_OWN) return;

	SI32 siMaxCount	  = MAX_SUMMON_OWN;
	SI32 siStartIndex = 0;

	if(siSummonIndex >= MAX_SUMMON_OWN)
	{
		siMaxCount   = MAX_SUMMON_OWN;
		siStartIndex = 0;
	}
	else
	{
		siMaxCount   = 1;
		siStartIndex = siSummonIndex;
	}

	for(SI32 i = siStartIndex, siCount = 0;  (i <MAX_SUMMON_OWN &&  siCount < siMaxCount); ++i, ++siCount)
	{
		cltSummon *pSummon = pclCI->clSummonInfo.GetSummon(i);

		SI32 siSummonID = GetSummonID();
		if(pclCM->IsValidID(siSummonID))	
		{
			// ���� �����ִ� ��ȯ���� ���� ���̶�� ������ Update��Ų��.
			if(pclCM->CR[siSummonID]->GetSummonIndex() == i)
			{
				if(pSummon)
					pSummon->clIP.Set(&pclCM->CR[siSummonID]->pclCI->clIP);
			}
		}

		if(pSummon)
		{
			if(pSummon->siKind >0 && pSummon->siKind < MAX_KIND_NUMBER)
			{
				cltSummon* pTransformSummon = NULL;
				if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
				{
					if( pclCI->clSummonInfo.IsSummonTranform( i ) )
					{
						cltServer* pclServer = (cltServer*)pclClient;
						UpDateSummonTransForm( pclServer->GetSummonTransformManager(), pSummon, i, &pTransformSummon );
					}
				}
				//Life�� 0 ���� �۴ٸ� ������ ���� ���·� �����Ѵ�.
				if(pSummon->clIP.GetLife() <=0)	
				{
					pSummon->siStatus = SUMMON_STATUS_DEAD;
					pSummon->clIP.SetLife(0);
					pSummon->clIP.SetMana(0);

					if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
					{
						if( pclCI->clSummonInfo.IsSummonTranform( i ) )
						{
							cltServer* pclServer = (cltServer*)pclClient;
							// ������ ������ Ǭ��.
							TransformSummon( pclServer->pclCM, pclServer->GetSummonTransformManager() );
						}
					}
				}

				sDBRequest_SetSummon cldbmsg(GetCharUnique(), pclCI->GetPersonID(), siReason, i, pTransformSummon ? pTransformSummon : pSummon);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&cldbmsg);
			}
		}
	}
}
void cltCharServer::SendDBSummon(SI32 siReason, UI08 siSummonIndex, cltSummon *pSummon)
{
	if(pSummon == NULL)													return;
	if(pSummon->siKind <= 0 && pSummon->siKind >= MAX_KIND_NUMBER)		return;

	if(pclClient->IsCountrySwitch(Switch_SummonHouse))
	{	
		if(siSummonIndex < 0 || siSummonIndex >= MAX_HAVE_SUMMON)			
			return;		
	}
	else
	{	
		if(siSummonIndex < 0 || siSummonIndex >= MAX_SUMMON_OWN)			
			return;		
	}


	cltSummon* pTransformSummon = NULL;
	if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
	{
		if( pclCI->clSummonInfo.IsSummonTranform( siSummonIndex ) )
		{
			cltServer* pclServer = (cltServer*)pclClient;
			UpDateSummonTransForm( pclServer->GetSummonTransformManager(), pSummon, siSummonIndex, &pTransformSummon );
		}
	}

	//Life�� 0 ���� �۴ٸ� ������ ���� ���·� �����Ѵ�.
	if(pSummon->clIP.GetLife() <= 0)
	{
		pSummon->siStatus = SUMMON_STATUS_DEAD;
		pSummon->clIP.SetLife(0);
		pSummon->clIP.SetMana(0);
	
		if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
		{
			if( pclCI->clSummonInfo.IsSummonTranform( siSummonIndex ) )
			{
				// ������ ������ Ǭ��.
				cltServer* pclServer = (cltServer*)pclClient;
				// ������ ������ Ǭ��.
				TransformSummon( pclServer->pclCM, pclServer->GetSummonTransformManager() );
			}
		}
	}

	sDBRequest_SetSummon cldbmsg(GetCharUnique(), pclCI->GetPersonID(), siReason, siSummonIndex, pTransformSummon ? pTransformSummon : pSummon);
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&cldbmsg);
}

void cltCharServer::SendDBUpdateTeacherPoint( SI32 Level )
{
	if( 19 >= Level || 71 <= Level )
		return;

	if( 0 >= pclCI->clBI.clFatherInfo.clFather.GetPersonID() )
		return;

	if( 20 == Level )
	{
		// ���ڿ��� �������� ������ �ش�
		cltItem clInputItem1;
		clInputItem1.siUnique = 7980;

		// �Ƿι��� �ý��� ����
		clInputItem1.siItemNum = CalcTiredPoint( 5 );

		if ( clInputItem1.siItemNum > 0 )
		{
			((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
		}

		cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
		((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);

		// ���¿��� �������� ������ �ش�
		cltItem clInputItem2;
		clInputItem2.siUnique = 7980;
		clInputItem2.siItemNum = 10;

		// ������ ������ �ִٸ� ������ �Ƿι��� �ý��� ����
		SI32 fatherPersonID = pclCI->clBI.clFatherInfo.clFather.GetPersonID();
		SI32 fatherID = pclClient->pclCM->GetIDFromPersonID(fatherPersonID);
		UI08 tiredState = 0;
		if ( pclClient->pclCM->IsValidID(fatherID) )
		{
			clInputItem2.siItemNum = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->CalcTiredPoint( clInputItem2.siItemNum );
			tiredState = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->uiTiredState;
		}

		if ( clInputItem2.siItemNum > 0)
		{
			((cltServer*)pclClient)->SendPostOfficeItemToPerson( fatherPersonID, &clInputItem2 , NULL ,0  );
		}

		cltLetterMsg_TeacherReward_PupilReward clletter2( cltLetterMsg_TeacherReward_PupilReward::TEACHER, tiredState, (TCHAR*)pclCI->clBI.GetName(), Level, clInputItem2.siUnique, clInputItem2.siItemNum );
		((cltServer*)pclClient)->SendLetterMsg( fatherPersonID, (cltLetterHeader*)&clletter2);
	}
	else if( 25 == Level )
	{
		if( pclClient->IsCountrySwitch( Switch_TeacherLevelReward ) )
		{
			cltItem clInputItem1;
			clInputItem1.siUnique = 15900;
			// �Ƿι��� �ý��� ����
			clInputItem1.siItemNum = CalcTiredPoint( 1 );
			clInputItem1.uiDateUseDay = 15;

			if ( clInputItem1.siItemNum > 0 )
			{
				((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
			}

			cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
			((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);
		}
	}
	else if( 30 == Level )
	{
		// ���¿��� �������� ������ �ش�
		cltItem clInputItem1;
		clInputItem1.siUnique = 7985;
		clInputItem1.siItemNum = 10;

		// ������ ������ �ִٸ� ������ �Ƿι��� �ý��� ����
		SI32 fatherPersonID = pclCI->clBI.clFatherInfo.clFather.GetPersonID();
		SI32 fatherID = pclClient->pclCM->GetIDFromPersonID(fatherPersonID);
		UI08 tiredState = 0;
		if ( pclClient->pclCM->IsValidID(fatherID) )
		{
			clInputItem1.siItemNum = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->CalcTiredPoint( clInputItem1.siItemNum );
			tiredState = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->uiTiredState;
		}

		if ( clInputItem1.siItemNum > 0)
		{
			((cltServer*)pclClient)->SendPostOfficeItemToPerson( fatherPersonID, &clInputItem1 , NULL ,0  );
		}

		cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::TEACHER, tiredState, (TCHAR*)pclCI->clBI.GetName(), Level, clInputItem1.siUnique, clInputItem1.siItemNum );
		((cltServer*)pclClient)->SendLetterMsg( fatherPersonID, (cltLetterHeader*)&clletter);
	}
	else if( 35 == Level )
	{
		// ���ڿ��� �������� ������ �ش�
		cltItem clInputItem1;
		clInputItem1.siUnique = 7985;
		// �Ƿι��� �ý��� ����
		clInputItem1.siItemNum = CalcTiredPoint( 5 );
		if ( clInputItem1.siItemNum > 0 )
		{
			((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
		}

		cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
		((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);

		if( pclClient->IsCountrySwitch( Switch_TeacherLevelReward ) )
		{
			// ���ڿ��� ��ö�� �ش�
			clInputItem1;
			clInputItem1.siUnique = 5017;
			// �Ƿι��� �ý��� ����
			clInputItem1.siItemNum = CalcTiredPoint( 10 );
			if ( clInputItem1.siItemNum > 0 )
			{
				((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
			}

			cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
			((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);
		}
	}
	else if( 40 == Level )
	{
		// ���¿��� �������� ������ �ش�
		cltItem clInputItem1;
		clInputItem1.siUnique = 7990;
		clInputItem1.siItemNum = 10;

		// ������ ������ �ִٸ� ������ �Ƿι��� �ý��� ����
		SI32 fatherPersonID = pclCI->clBI.clFatherInfo.clFather.GetPersonID();
		SI32 fatherID = pclClient->pclCM->GetIDFromPersonID(fatherPersonID);
		UI08 tiredState = 0;
		if ( pclClient->pclCM->IsValidID(fatherID) )
		{
			clInputItem1.siItemNum = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->CalcTiredPoint( clInputItem1.siItemNum );
			tiredState = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->uiTiredState;
		}

		if ( clInputItem1.siItemNum > 0 )
		{
			((cltServer*)pclClient)->SendPostOfficeItemToPerson( fatherPersonID, &clInputItem1 , NULL ,0  );
		}

		cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::TEACHER, tiredState, (TCHAR*)pclCI->clBI.GetName(), Level, clInputItem1.siUnique, clInputItem1.siItemNum );
		((cltServer*)pclClient)->SendLetterMsg( fatherPersonID, (cltLetterHeader*)&clletter);
	}
	else if( 45 == Level )
	{
		if( pclClient->IsCountrySwitch( Switch_TeacherLevelReward ) )
		{
			// ���ڿ��� ����� ��ġ�� �ش�
			cltItem clInputItem1;
			clInputItem1.siUnique = 13606;
			// �Ƿι��� �ý��� ����
			clInputItem1.siItemNum = CalcTiredPoint( 10 );
			if ( clInputItem1.siItemNum > 0 )
			{
				((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
			}

			cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
			((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);
		}
	}
	else if( 50 == Level )
	{
		// ���ڿ��� �������� ������ �ش�
		cltItem clInputItem1;
		clInputItem1.siUnique = 7990;
		clInputItem1.siItemNum = CalcTiredPoint( 5 );
		if ( clInputItem1.siItemNum > 0 )
		{
			((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
		}

		cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
		((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);
	}
	else if( 60 == Level )
	{
		if( pclClient->IsCountrySwitch( Switch_TeacherLevelReward ) )
		{
			// ���ڿ��� �������ڸ� �ش�
			cltItem clInputItem1;
			clInputItem1.siUnique = 13314;

			// �Ƿι��� �ý��� ����
			clInputItem1.siItemNum = CalcTiredPoint( 2 );

			if ( clInputItem1.siItemNum > 0 )
			{
				((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
			}


			cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
			((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);

			// ���¿��� �����ڸ� �ش�
			cltItem clInputItem2;
			clInputItem2.siUnique = 13314;

			// �Ƿι��� �ý��� ����
			clInputItem2.siItemNum = 2;

			// ������ ������ �ִٸ� ������ �Ƿι��� �ý��� ����
			SI32 fatherPersonID = pclCI->clBI.clFatherInfo.clFather.GetPersonID();
			SI32 fatherID = pclClient->pclCM->GetIDFromPersonID(fatherPersonID);
			UI08 tiredState = 0;
			if ( pclClient->pclCM->IsValidID(fatherID) )
			{
				clInputItem2.siItemNum = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->CalcTiredPoint( clInputItem2.siItemNum );
				tiredState = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->uiTiredState;
			}

			if ( clInputItem2.siItemNum > 0)
			{
				((cltServer*)pclClient)->SendPostOfficeItemToPerson( fatherPersonID, &clInputItem2 , NULL ,0  );
			}

			cltLetterMsg_TeacherReward_PupilReward clletter2( cltLetterMsg_TeacherReward_PupilReward::TEACHER, tiredState, (TCHAR*)pclCI->clBI.GetName(), Level, clInputItem2.siUnique, clInputItem2.siItemNum );
			((cltServer*)pclClient)->SendLetterMsg( fatherPersonID, (cltLetterHeader*)&clletter2);
		}
	}
	else if( 70 == Level )
	{
		if( pclClient->IsCountrySwitch( Switch_TeacherLevelReward ) )
		{
			// ���ڿ��� �ູ�� ���� �ش�
			cltItem clInputItem1;
			clInputItem1.siUnique = 5370;

			// �Ƿι��� �ý��� ����
			clInputItem1.siItemNum = CalcTiredPoint( 20 );

			if ( clInputItem1.siItemNum > 0 )
			{
				((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem1 , NULL ,0  );
			}


			cltLetterMsg_TeacherReward_PupilReward clletter( cltLetterMsg_TeacherReward_PupilReward::PUPIL, uiTiredState, "", Level, clInputItem1.siUnique, clInputItem1.siItemNum );
			((cltServer*)pclClient)->SendLetterMsg( pclCI->GetPersonID(), (cltLetterHeader*)&clletter);

			// ���¿��� �ູ�� ���� �ش�
			cltItem clInputItem2;
			clInputItem2.siUnique = 5370;

			// �Ƿι��� �ý��� ����
			clInputItem2.siItemNum = 20;

			// ������ ������ �ִٸ� ������ �Ƿι��� �ý��� ����
			SI32 fatherPersonID = pclCI->clBI.clFatherInfo.clFather.GetPersonID();
			SI32 fatherID = pclClient->pclCM->GetIDFromPersonID(fatherPersonID);
			UI08 tiredState = 0;
			if ( pclClient->pclCM->IsValidID(fatherID) )
			{
				clInputItem2.siItemNum = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->CalcTiredPoint( clInputItem2.siItemNum );
				tiredState = ((cltCharServer*)pclClient->pclCM->CR[fatherID])->uiTiredState;
			}

			if ( clInputItem2.siItemNum > 0)
			{
				((cltServer*)pclClient)->SendPostOfficeItemToPerson( fatherPersonID, &clInputItem2 , NULL ,0  );
			}

			cltLetterMsg_TeacherReward_PupilReward clletter2( cltLetterMsg_TeacherReward_PupilReward::TEACHER, tiredState, (TCHAR*)pclCI->clBI.GetName(), Level, clInputItem2.siUnique, clInputItem2.siItemNum );
			((cltServer*)pclClient)->SendLetterMsg( fatherPersonID, (cltLetterHeader*)&clletter2);
		}
	}
}

