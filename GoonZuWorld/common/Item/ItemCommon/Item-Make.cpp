//---------------------------------
// 2004/5/19 ���°�
//---------------------------------
#include <stdio.h>
#include "cltItem.h"
#include "CommonLogic.h"

#include "Skill/Skill-Manager.h"
#include "Char/Disease/Disease.h"
#include "Util/Util.h"
#include "Char/CharCommon/Char-Common.h"
#include "../../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../../DBManager/GameDBManager_World/DBMsg-Market.h"

#include "Char\CharManager\CharManager.h"
#include "../../../Server/Server.h"

#include "../../../Server/GachaManager/GachaManager.h"
#include "../../../Server/ArtifactRestoreManager/ArtifactRestoreManager.h"
//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"

extern cltCommonLogic* pclClient;

// ���ݷ��� �ο��Ѵ�. 
void cltItemManagerCommon::MakeApower(cltItem* pclitem, SI32 qualityrate)
{
	if ( NULL == pclitem )
	{
		return;
	}

	pclitem->clItemWeapon.uiMinDamage	= max(1, pclitem->clItemWeapon.uiMinDamage * qualityrate / 100 );
	pclitem->clItemWeapon.uiMaxDamage	= max(1, pclitem->clItemWeapon.uiMaxDamage * qualityrate / 100 );
}

//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
void cltItemManagerCommon::MakeCrystal(cltItem* pclitem, SI32 qualityrate) // qualityrate ���� ���� .
{
	if ( NULL == pclitem )
	{
		return;
	}

	UI08 temCrystalAbility = 0;
	UI08 temCrystalAbilityNum = 0;
	
	SI32 ref = FindItemRefFromUnique(pclitem->siUnique);

	SI32 randAbility = rand()%100+1; // MAX Ȯ�� ��ġ.
	SI32 bCrystalAbMin = 0;
	SI32 bCrystalAbMax = 0;
	//SI32 rateIndex[MAX_CAN_CRYSTALABILITY_NUM]={0,}; // �� �ɷ��� ���õ� Ȯ�� ����.
	//SI32 selectAbilityIndex = 0; // ���õ� �ɷ��� �ε���.

	cltCrystalItemData tempCrystalData[MAX_CAN_CRYSTALABILITY_NUM];
	SI32 tempIndex = 0;

	// ���Ͽ� �ִ� �Ķ���� ������ �о� �´�.
	for(int i = 0; i <MAX_CAN_CRYSTALABILITY_NUM ; i++)
	{
		if((pclItemInfo[ref]->CrystalData[i].siCrystalType) > 0)
		{
			tempCrystalData[tempIndex].Set(&pclItemInfo[ref]->CrystalData[i]); // ���ҽ��� �����͸� �о�´�. ������ ���.
			tempIndex++;
		}		
	}

	SI32 tempRate1 = 0;
	SI32 tempRate2 = 0;

	for(int k = 0; k <tempIndex ; k++)
	{	
		for(int x = 0; x < k+1; x++)
		{	
			tempRate2 = tempRate2 + tempCrystalData[x].siTypeRate;
		}

		if((randAbility > tempRate1) &&(randAbility <= tempRate2))
		{
			temCrystalAbility = tempCrystalData[k].siCrystalType;
			bCrystalAbMin 	= tempCrystalData[k].siMinValue;
			bCrystalAbMax 	= tempCrystalData[k].siMaxValue;
			break;
		}

		tempRate1 = tempRate2;
		tempRate2 =0;
	}

	// ���õ� �ɷ¿� ���� ��ġ ����.
	if(temCrystalAbility !=0)
	{
		// ���������� �� �κп��� �߰��Ѵ�.
		//KHY - 0805 - ��Ʈ�彺 ����.
		//if(qualityrate >0)
		//	temCrystalAbilityNum = (UI08)((float)(bCrystalAb*qualityrate/100)+(float)0.5);
		//else

		// ���ݿ���, ���밪 ������ ���� ������. (10 -> 5~10)
		//SI32 randCrystalAb = rand()%((bCrystalAb/2)+1);
		//temCrystalAbilityNum = (bCrystalAb/2)+randCrystalAb ;

		if(IsItemInfoAtb(pclitem->siUnique,ITEMINFOATB_ITEMMALL) == true ) // ����ü �̸鼭 ������ �� ��ǰ �̶��.
		{
			// ���� ����ü ( �ƹ�Ÿ ����ü ) �� �ɷ��� �����̴�.
			temCrystalAbilityNum = bCrystalAbMin; // �ּҰ��� �������� �Ѵ�.
		}
		else
		{
			// �Ϲ� ����ü
			// ��ǰ�� ���� �� �ִ�. - 100~280%
			SI32 qualityrate = max(100, GetAverage(100, true, 0));

			SI32 randAB = rand()%(bCrystalAbMax-bCrystalAbMin+1);

			temCrystalAbilityNum = max(1, (((bCrystalAbMin+randAB)*qualityrate)/100));
		}

		pclitem->clItemCrystal.siMaxDurability = 30000; // ����ü �ִ� ������  - ����.
		pclitem->clItemCrystal.uiCrystalAbility = temCrystalAbility; 
		pclitem->clItemCrystal.uiCrystalAbilityNum = temCrystalAbilityNum; 
	}
}

// ������ �ο��Ѵ�. 
void cltItemManagerCommon::MakeDpower(cltItem* pclitem, SI32 qualityrate)
{
	if ( NULL == pclitem )
	{
		return;
	}

	SI32 ref = FindItemRefFromUnique(pclitem->siUnique);
	if(ref >  0)
	{
		// �������� Type�� ���Ѵ�. 
		SI32 type = pclItemInfo[ref]->siType;

		//if (type == ITEMTYPE_DRESS || type == ITEMTYPE_HAT)
		//{
		//	pclitem->clItemStatusArmour.uiAC	= max(1, pclitem->clItemStatusArmour.uiAC * qualityrate / 100 );
		//}
		//else
		//{
			pclitem->clItemArmour.uiAC	= max(1, pclitem->clItemArmour.uiAC * qualityrate / 100 );
		//}
	}

}

// ��ǰ�� �������� �����. 
void cltItemManagerCommon::MakeDur(SI16* pbrareswitch, SI32 orgqualityrate, SI32 addlevel, cltItem* pclitem, bool bforseswitch,
								   SI32 durrate,SI32 monstercorp)
{
	if( pclClient->IsCountrySwitch( Switch_NewDurability ) == false )		return;
	if ( (NULL == pbrareswitch) || (NULL == pclitem) )						return;

	// ���ɽű��� ��� �������� GV_Dur_HIGHGRADEDURABILITY�� �����ϱ� ����
	SI16 siRareSwitch = *pbrareswitch;

	SI32 qualityrate = 0;

	// ������ ������ ������ �����Ѵ�. 
	if(bforseswitch)
	{
		qualityrate = orgqualityrate;
	}
	else if ( durrate <= 0 || durrate > 500 )
	{
		qualityrate = GetAverage( max(10, orgqualityrate), bCanMakeRareItemSwitch, addlevel, false );
	}
	else if ( durrate != 0 && durrate > 0 && durrate <= 500 )
	{
		qualityrate = durrate ;
	}

	qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;

	if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
	else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
	else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )
	{
		// ������ �ű� ����϶��� �űⱸ���� ������ �ȳ����� 100~149������ �����ϰ� ��������
		qualityrate = rand() % 50;
		qualityrate += 100;
	}

	if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
	{
		if(orgqualityrate < 100)
		{
			qualityrate = orgqualityrate;
			// ��ǰ
			*pbrareswitch = -1;
		}
	}

	UI32 uiMaxDurability		= (UI32)pclClient->GetGlobalValue( TEXT("GV_MaxDurability") );
	UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	if( uiForeverDurability == pclitem->clItemCommon.clCommonInfo.uiMaxDurability ||
		uiForeverDurability2 == pclitem->clItemCommon.clCommonInfo.uiMaxDurability )
	{
		// FOREVER DURABILITY ------------------------------------------------------------------------------------------
		pclitem->clItemCommon.clCommonInfo.uiMaxDurability = pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
		//--------------------------------------------------------------------------------------------------------------
	}
	else if ( 3 == siRareSwitch )
	{
		UI32 uiHighGradeMaxDur = (UI32)pclClient->GetGlobalValue( "GV_Dur_HIGHGRADEDURABILITY" );

		pclitem->clItemCommon.clCommonInfo.uiMaxDurability = uiHighGradeMaxDur;
	}
	else
	{
		// SET MAX DURABILITY ----------------------------------------------------------------------------------------------
		pclitem->clItemCommon.clCommonInfo.uiMaxDurability = min(uiMaxDurability, max(10, pclitem->clItemCommon.clCommonInfo.uiMaxDurability * qualityrate / 100)  );
		pclitem->clItemCommon.clCommonInfo.uiMaxDurability -= (pclitem->clItemCommon.clCommonInfo.uiMaxDurability%10);	// 1������ �����Ѵ�. 
		//--------------------------------------------------------------------------------------------------------------
	}

	// SET DURABILITY ----------------------------------------------------------------------------------------------
	pclitem->clItemCommon.clCommonInfo.uiDurability = pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
	//--------------------------------------------------------------------------------------------------------------
}


// ��ǰ�� �Ⱓ�� �����.
void cltItemManagerCommon::MakeDate(SI16* pbrareswitch, SI32 orgqualityrate, SI32 addlevel, cltItem* pclitem, bool bforseswitch,
									SI32 durrate,SI32 monstercorp)
{
	if ( (NULL == pbrareswitch) || (NULL == pclitem) )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL ) return ;

	SI32 qualityrate = 0;

	// ������ ������ ������ �����Ѵ�. 
	if(bforseswitch)
	{
		qualityrate = orgqualityrate;
	}
	else if ( durrate <= 0 || durrate > 500 )
	{
		qualityrate = GetAverage( max(10, orgqualityrate), bCanMakeRareItemSwitch, addlevel);
	}
	else if ( durrate != 0 && durrate > 0 && durrate <= 500 )
		qualityrate = durrate ;
	qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;

	if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
	else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����

	pclitem->uiDateUseDay = min(360,max(1,pclitem->uiDateUseDay* qualityrate / 100)) ;
	
	if(pclitem->uiDateUseDay < 1)
	{
		pclitem->uiDateUseDay = 5;
	}

	if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		// �ű��̸鼭 ���ѳ������� �ƴϸ� ��ǰ ��¥�� ����
		if ( 3 == *pbrareswitch )
		{
			UI32 uiMaxDurability		= (UI32)pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
			UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
			UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

			if ( (uiForeverDurability != uiMaxDurability) && (uiForeverDurability2 != uiMaxDurability) )
			{
				pclitem->uiDateUseDay = 0;
			}
		}
	}

	//	pclitem->uiDateYear = pclserver->sTime.wYear - 2000 ;
	//	pclitem->uiDateMonth = pclserver->sTime.wMonth ;
	//	pclitem->uiDateDay = pclserver->sTime.wDay ;
}


// ��ǰ�� �Ⱓ�� �����.
void cltItemManagerCommon::MakeAvatarDate(SI16* pbrareswitch, SI32 orgqualityrate, SI32 addlevel, cltItem* pclitem, bool bforseswitch,
									SI32 durrate,SI32 monstercorp)
{
	if ( (NULL == pbrareswitch) || (NULL == pclitem) )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL ) return ;

	SI32 qualityrate = 0;

	// ������ ������ ������ �����Ѵ�. 
	if(bforseswitch)
	{
		qualityrate = orgqualityrate;
	}
	// ����� ������ �ƴϴ�. - �⺻ ����.
	else if ( durrate <= 0 || durrate > 500 )
	{
		qualityrate = GetAverage( max(10, orgqualityrate), bCanMakeRareItemSwitch, addlevel);

		SI32 randaddrate = rand() % 2 ;

		if ( randaddrate == 0 )	// �̴ϰ��� ��� ���� -> ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
			qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
	}
	// ��� ������.
	else if ( durrate != 0 && durrate > 0 && durrate <= 500 )
		qualityrate = durrate ;


	if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
	else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
	else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����

	// ���� ��¥�� ����� �Է��ϴ� �κ�.
	pclitem->uiDateUseDay = min(360,max(1,pclitem->uiDateUseDay* qualityrate / 100)) ;
	
	if(pclitem->uiDateUseDay < 1)
	{
		pclitem->uiDateUseDay = 5;
	}
}
// ���ǰ�� �Ⱓ�� ���´�. (����)
SI32 cltItemManagerCommon::GetHighItemDate()
{
	// �߱��� ����
	if ( pclClient->IsWhereServiceArea( ConstServiceArea_China ) )
		return 0;

	//SI32 siUseDate = 7;
	//SI32 siRand = rand()% 100;
	//if(siRand >= 0 && siRand < 10)			// 10% : 7 ~ 13��
	//{
	//	siUseDate = 7;
	//	siUseDate += rand() % 7;
	//}
	//else if(siRand >= 10 && siRand < 80)	// 70% : 14�� ~ 22��
	//{
	//	siUseDate = 18;
	//	siUseDate += (rand() % 9) - 4;
	//}
	//else if(siRand >= 80 && siRand < 100)	// 20% : 23 ~ 28��
	//{
	//	siUseDate = 23;
	//	siUseDate += rand() % 6;
	//}


	// 7 ~ 14�ϱ��� �������� ������.
	SI32 siUseDate = 7;
	SI32 siPlusDate = 0;
    siPlusDate = rand() % 8;

	return siUseDate + siPlusDate;
}


// [�߰� : Ȳ���� 2008. 3. 3 => �������� ȯ���� ������ ������.]
bool cltItemManagerCommon::MakeItembyRestore( cltItem* pclEquipItem, cltItem* pclRestoreItem, cltCharCommon* pclchar )
{
	if ( (NULL == pclEquipItem) || (NULL == pclchar) )
	{
		return false;
	}

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclEquipItem->siUnique );
	if( ref <= 0 ) 
		return false;

	// �������� ���� ����.
	SI32 siItemLevel = pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLevel; 
	if( 0 >= siItemLevel )
		return false;

	SI32 siRand				= rand()%100 + 1;	
	SI32 siRestoreItemCount	= 0;
	SI32 siIndex			= siItemLevel - 1;	// �������� ������ �����Ƿ� 		
	SI32 siItemUnique		= 0;
	SI16 brareswitch		= 0;

	//___________________________________________________________________________________________________	
	// ���� �������� ��´�.
	//___________________________________________________________________________________________________	
	
	// ���� �迭 ������ ���.
	clElementRestore* pclElementRestore = &pclClient->pclArtifactRestoreManager->m_clElementRestore[ siIndex ];

	for( SI32 ItemCount = ITEM_BY_ELEMENT_KIND_NUM - 1; 0 <= ItemCount; --ItemCount )
	{
		if( siRand < pclElementRestore->m_siRate[ ItemCount ] )
		{
			siItemUnique = pclElementRestore->m_siItemUnique[ ItemCount ];	
			brareswitch  = 0;

			if( false ==  MakeRandItemUnique( siItemUnique, pclRestoreItem, 0, 0, &brareswitch ) )
			{
				return false;
			}
			
			SI32 siMinItemNum = pclElementRestore->m_siMinNum[ ItemCount ];
			SI32 siMaxItemNum = pclElementRestore->m_siMaxNum[ ItemCount ];
			
			//// �ش� �ִ� ������ �����۰����� �̴´�.
			//SI32 siItemNum = 1 + rand()%siMaxItemNum;
			//			
			//// �ִ밪���� ���� ������ �ּҰ����� ������� �ּҰ��� �����Ѵ�.
			//if(  siItemNum < siMinItemNum )
			//	siItemNum = siMinItemNum;

			//�����۰����� �̴´�.
			SI32 siItemNum = siMinItemNum + ( rand() % ( siMaxItemNum - siMinItemNum +1) );

#ifdef _SAFE_MEMORY
			SI32 SkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_ARTIFACT, 0, 0,  &pclchar->pclCI->clCharItem.clItem[0]);
#else
			SI32 SkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_ARTIFACT, 0, 0,  pclchar->pclCI->clCharItem.clItem);
#endif

			if(30 <= SkillLevel)
			{
				/*float Percent = 0;
					 if( 45  >  SkillLevel)  Percent = 0.2f;
				else if( 60  >  SkillLevel)  Percent = 0.4f;
				else if( 75  >  SkillLevel)  Percent = 0.6f;
				else if( 100 >  SkillLevel)  Percent = 0.8f;
				else						 Percent = 1.0f;

				siItemNum += siItemNum * Percent;
				*/
				SI32 temMinnum = 0;
				SI32 temnum = 0;
				SI32 AddPer = 0;

				//makeitemnum =((makeitemnum*140)/100);
				if(SkillLevel >= 30 && SkillLevel < 45)
				{
					temMinnum = ((siItemNum*1200)/1000); // �ּҰ�.

					AddPer = (SkillLevel - 30) * 13; 
					temnum = ((siItemNum*(1200+AddPer))/1000); // ��� ������ ���� �ƽ���.
						
					siItemNum = max(temMinnum ,temnum );
				}
				else if(SkillLevel >= 45 && SkillLevel < 60)
				{
					temMinnum = ((siItemNum*1400)/1000); // �ּҰ�.

					AddPer = (SkillLevel - 45) * 13; 
					temnum = ((siItemNum*(1400+AddPer))/1000); // ��� ������ ���� �ƽ���.
						
					siItemNum = max(temMinnum ,temnum );			
				}
				else if(SkillLevel >= 60 && SkillLevel < 75)
				{
					temMinnum = ((siItemNum*1600)/1000); // �ּҰ�.

					AddPer = (SkillLevel - 60) * 13; 
					temnum = ((siItemNum*(1600+AddPer))/1000); // ��� ������ ���� �ƽ���.
						
					siItemNum = max(temMinnum ,temnum );
				}
				else if(SkillLevel >= 75 && SkillLevel < 100)
				{
					temMinnum = ((siItemNum*1800)/1000); // �ּҰ�.

					AddPer = (SkillLevel - 75) * 13; 
					temnum = ((siItemNum*(1800+AddPer))/1000); // ��� ������ ���� �ƽ���.
						
					siItemNum = max(temMinnum ,temnum );
				}
				else if(SkillLevel ==  100)
				{
					siItemNum =((siItemNum*2000)/1000);
				}
			}
			
			// ������ ����.
			pclRestoreItem->siItemNum = siItemNum;
			break;
		}
	}									  
	
	if( 0 >= pclRestoreItem->siUnique )
	{
		siItemUnique = pclElementRestore->m_siItemUnique[0];
		brareswitch  = 0;
		
		if( false ==  MakeRandItemUnique( siItemUnique, pclRestoreItem, 0, 0, &brareswitch ) )
		{
			return false;
		}

		SI32 siMinItemNum = pclElementRestore->m_siMinNum[ 0 ];
		SI32 siMaxItemNum = pclElementRestore->m_siMaxNum[ 0 ];

		//// �ش� �ִ� ������ �����۰����� �̴´�.
		//SI32 siItemNum = 1 + rand()%siMaxItemNum;
		//			
		//// �ִ밪���� ���� ������ �ּҰ����� ������� �ּҰ��� �����Ѵ�.
		//if(  siItemNum < siMinItemNum )
		//	siItemNum = siMinItemNum;

		//�����۰����� �̴´�.
		SI32 siItemNum = siMinItemNum + ( rand() % ( siMaxItemNum - siMinItemNum +1 ) );

#ifdef _SAFE_MEMORY
		SI32 SkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_ARTIFACT, 0, 0,  &pclchar->pclCI->clCharItem.clItem[0]);
#else
		SI32 SkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_ARTIFACT, 0, 0,  pclchar->pclCI->clCharItem.clItem);
#endif
		if(30 <= SkillLevel)
		{
			/*float Percent = 0;
				 if( 45  >  SkillLevel)  Percent = 0.2f;
			else if( 60  >  SkillLevel)  Percent = 0.4f;
			else if( 75  >  SkillLevel)  Percent = 0.6f;
			else if( 100 >  SkillLevel)  Percent = 0.8f;
			else						 Percent = 1.0f;

			siItemNum += siItemNum * Percent;
			*/
			SI32 temMinnum = 0;
			SI32 temnum = 0;
			SI32 AddPer = 0;

			//makeitemnum =((makeitemnum*140)/100);
			if(SkillLevel >= 30 && SkillLevel < 45)
			{
				temMinnum = ((siItemNum*1200)/1000); // �ּҰ�.

				AddPer = (SkillLevel - 30) * 13; 
				temnum = ((siItemNum*(1200+AddPer))/1000); // ��� ������ ���� �ƽ���.
					
				siItemNum = max(temMinnum ,temnum );
			}
			else if(SkillLevel >= 45 && SkillLevel < 60)
			{
				temMinnum = ((siItemNum*1400)/1000); // �ּҰ�.

				AddPer = (SkillLevel - 45) * 13; 
				temnum = ((siItemNum*(1400+AddPer))/1000); // ��� ������ ���� �ƽ���.
					
				siItemNum = max(temMinnum ,temnum );			
			}
			else if(SkillLevel >= 60 && SkillLevel < 75)
			{
				temMinnum = ((siItemNum*1600)/1000); // �ּҰ�.

				AddPer = (SkillLevel - 60) * 13; 
				temnum = ((siItemNum*(1600+AddPer))/1000); // ��� ������ ���� �ƽ���.
					
				siItemNum = max(temMinnum ,temnum );
			}
			else if(SkillLevel >= 75 && SkillLevel < 100)
			{
				temMinnum = ((siItemNum*1800)/1000); // �ּҰ�.

				AddPer = (SkillLevel - 75) * 13; 
				temnum = ((siItemNum*(1800+AddPer))/1000); // ��� ������ ���� �ƽ���.
					
				siItemNum = max(temMinnum ,temnum );
			}
			else if(SkillLevel ==  100)
			{
				siItemNum =((siItemNum*2000)/1000);
			}
		}

		// ������ ����.
		pclRestoreItem->siItemNum = siItemNum;
	}
	//___________________________________________________________________________________________________
	
	//___________________________________________________________________________________________________	
	// ���� �������� ��´�.
	//___________________________________________________________________________________________________	

	// ���� ������ �迭�� ���縦 �����ϱ� ���� �ϳ� ����.
	++pclRestoreItem;
	
	// �������� ���� ��æƮ �Ӽ�. 
	SI32 siElementType			= pclEquipItem->Element.siType;
	SI32 siEnchantTypeSlotNum	= -1;
	
	// �Ӽ��� ������ ����.
	switch( siElementType )
	{
		case ENCHANT_TYPE_DEFAULT:	siEnchantTypeSlotNum =  0;	break;
		case ENCHANT_TYPE_FIRE_A:	
		case ENCHANT_TYPE_FIRE_D:	siEnchantTypeSlotNum =  1;	break;
		case ENCHANT_TYPE_WATER_A:
		case ENCHANT_TYPE_WATER_D:	siEnchantTypeSlotNum =  2;	break;
		case ENCHANT_TYPE_GROUND_A:
		case ENCHANT_TYPE_GROUND_D:	siEnchantTypeSlotNum =  3;	break;
		case ENCHANT_TYPE_WIND_A:	
		case ENCHANT_TYPE_WIND_D:	siEnchantTypeSlotNum =  4;	break;	
		default:					siEnchantTypeSlotNum = -1;	break;	
	}

	if( -1 == siEnchantTypeSlotNum )
		return false;
	
	// ���� �迭 ������ ���.
	clPowderRestore* pclPowderRestore = &pclClient->pclArtifactRestoreManager->m_clPowderRestore[ siIndex ];
	
	if( siRand < pclPowderRestore->m_siRate[ siEnchantTypeSlotNum ] )
	{
		siItemUnique = pclPowderRestore->m_siItemUnique[ siEnchantTypeSlotNum ];	
		brareswitch  = 0;

		if( false ==  MakeRandItemUnique( siItemUnique, pclRestoreItem, 0, 0, &brareswitch ) )
		{
			return false;
		}

		SI32 siMinItemNum = pclPowderRestore->m_siMinNum[ siEnchantTypeSlotNum ];
		SI32 siMaxItemNum = pclPowderRestore->m_siMaxNum[ siEnchantTypeSlotNum ];

		//// �ش� �ִ� ������ �����۰����� �̴´�.
		//SI32 siItemNum = 1 + rand()%siMaxItemNum;
		//			
		//// �ִ밪���� ���� ������ �ּҰ����� ������� �ּҰ��� �����Ѵ�.
		//if(  siItemNum < siMinItemNum )
		//	siItemNum = siMinItemNum;

		//�����۰����� �̴´�.
		SI32 siItemNum = siMinItemNum + ( rand() % ( siMaxItemNum - siMinItemNum +1 ) );

#ifdef _SAFE_MEMORY
		SI32 SkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_ARTIFACT, 0, 0,  &pclchar->pclCI->clCharItem.clItem[0]);
#else
		SI32 SkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_ARTIFACT, 0, 0,  pclchar->pclCI->clCharItem.clItem);
#endif
		/*if(30 <= SkillLevel)
		{
			float Percent = 0;
				 if( 45  >  SkillLevel)  Percent = 0.2f;
			else if( 60  >  SkillLevel)  Percent = 0.4f;
			else if( 75  >  SkillLevel)  Percent = 0.6f;
			else if( 100 >  SkillLevel)  Percent = 0.8f;
			else						 Percent = 1.0f;

			siItemNum += siItemNum * Percent;
		}
		*/
		SI32 temMinnum = 0;
		SI32 temnum = 0;
		SI32 AddPer = 0;

		//makeitemnum =((makeitemnum*140)/100);
		if(SkillLevel >= 30 && SkillLevel < 45)
		{
			temMinnum = ((siItemNum*1200)/1000); // �ּҰ�.

			AddPer = (SkillLevel - 30) * 13; 
			temnum = ((siItemNum*(1200+AddPer))/1000); // ��� ������ ���� �ƽ���.
				
			siItemNum = max(temMinnum ,temnum );
		}
		else if(SkillLevel >= 45 && SkillLevel < 60)
		{
			temMinnum = ((siItemNum*1400)/1000); // �ּҰ�.

			AddPer = (SkillLevel - 45) * 13; 
			temnum = ((siItemNum*(1400+AddPer))/1000); // ��� ������ ���� �ƽ���.
				
			siItemNum = max(temMinnum ,temnum );			
		}
		else if(SkillLevel >= 60 && SkillLevel < 75)
		{
			temMinnum = ((siItemNum*1600)/1000); // �ּҰ�.

			AddPer = (SkillLevel - 60) * 13; 
			temnum = ((siItemNum*(1600+AddPer))/1000); // ��� ������ ���� �ƽ���.
				
			siItemNum = max(temMinnum ,temnum );
		}
		else if(SkillLevel >= 75 && SkillLevel < 100)
		{
			temMinnum = ((siItemNum*1800)/1000); // �ּҰ�.

			AddPer = (SkillLevel - 75) * 13; 
			temnum = ((siItemNum*(1800+AddPer))/1000); // ��� ������ ���� �ƽ���.
				
			siItemNum = max(temMinnum ,temnum );
		}
		else if(SkillLevel ==  100)
		{
			siItemNum =((siItemNum*2000)/1000);
		}
		
		// ������ ����.
		pclRestoreItem->siItemNum = siItemNum;
	}
			
	return true;
}


// �������� Unique������ ���� �����ϰ� �������� �ϳ� �����.
// �������� Unique������ ���� �����ϰ� �������� �ϳ� �����.
//====================================================
// PARAMETER
//====================================================
// siunique			: ������ ������ ����ũ
// pclitem			: ������ ������
// orgqualityrate	: Quality Rate
// addlevel			: ����������(1000�ڸ�), ��������(1�ڸ�)
// pbrareswitch		: ��ǰ �Ǵ� ȣǰ�� ������ ��� ��ȯ
// attackrate		: ��ڱ��� ������ 
// magrate			: ��ڱ��� ������
// skillrate		: ��ڱ��� ������
// durrate			: ��ڱ��� ������
// monstercorp		: �̴ϰ��� ��
// usedate			: ���Ⱓ
// enchanttype		: ��ڱ��� ������
// enchantlevel		: ��ڱ��� ������
// slotnum			: ��ڱ��� ������
//====================================================
bool cltItemManagerCommon::MakeRandItemUnique(SI32 siunique, cltItem* pclitem,
											  SI32 orgqualityrate, SI32 addlevel,SI16* pbrareswitch,
											  SI32 attackrate , SI32 magrate ,SI32 skillrate, SI32 durrate,
											  SI32 monstercorp,SI32 usedate, SI32 enchanttype, SI32 enchantlevel, SI32 slotnum,
											  bool bSEQCreate)
{
	if ( (NULL == pclitem) || (NULL == pbrareswitch) )
	{
		return false;
	}

	if(siunique == 0)return false;
	SI32 qualityrate  = 0;

	cltServer* pclserver = (cltServer*)pclClient;

	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)
	{
		TCHAR buffer[256];
		StringCchPrintf(buffer, 256, TEXT("MakeRandItem() f87s3:%d"), siunique);
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("Error"), buffer, MB_OK|MB_TOPMOST);

		return false;
	}

	// �������� Type�� ���Ѵ�. 
	SI32 type = pclItemInfo[ref]->siType;

	// ������ Type�� Atb�� ���Ѵ�. 
	SI64 atb = pclItemTypeInfo[type]->siAtb;

	// �������� Object�̸�, 
	if(atb & ITEMATB_OBJECT)
	{
		pclitem->Set(&pclItemInfo[ref]->clItem);
	}
	else
	{
		pclitem->Set(&pclItemInfo[ref]->clItem);
	}

	if ( usedate > 0 && (atb & ITEMATB_OBJECT))
	{
		pclitem->uiDateYear = 0;
		pclitem->uiDateMonth = 0;
		pclitem->uiDateDay = 0;
		pclitem->uiDateUseDay = usedate;
	}
 
	//-----------------------------------------------
	//    ��æƮ���� ó���� ���鶧�� 0   by tae-yang
	//-----------------------------------------------
	pclitem->Element.siType = ENCHANT_TYPE_DEFAULT;
	pclitem->Element.siPower = 0;

	// [���] /seq��ɾ�� ������ �����ÿ� ��æƮ ���� ������ �־��ش�. (09.10.12)
	if(bSEQCreate == true)
	{
		if(enchanttype > 0)		pclitem->Element.siType = enchanttype;
		if(enchantlevel > 0)	pclitem->Element.siPower = enchantlevel;
	}

	// ������ �� ��ǰ�̸� �Ǻ��̳� ����, �����̸� ���� �Ⱓ�� ������ �ش�.
	if ( IsItemInfoAtb(siunique,ITEMINFOATB_ITEMMALL) == true )
	{
		//etc �����۵� �Ⱓ���� [����] -> �����Ѿ�, ����ȭ���� �����̾����� �Űܰ�
		// �����̾� ������ �߿� usedate�� �ִ� �͸� �ڵ����� ���۽ð��� �����Ѵ�. - by LEEKH 2008-10-07
		if( type == ITEMTYPE_DRESS || type == ITEMTYPE_HAT || type == ITEMTYPE_MANTLE || 
			(type == ITEMTYPE_PREMIUM && usedate > 0) || 
			type == ITEMTYPE_BAG )
		{			
			pclitem->uiDateYear = pclserver->sTime.wYear - 2000 ;
			pclitem->uiDateMonth = pclserver->sTime.wMonth ;
			pclitem->uiDateDay = pclserver->sTime.wDay ;			
		}
	}

	// [����/ 09-05-06 - �ƹ�Ÿ ������ ������ ������ 3�� ����� �ش�. ����̸� 1�� �������.
	if(pclClient->IsCountrySwitch(Switch_Avatar_artisan))
	{
		if(IsItemInfoAtb(siunique,ITEMINFOATB_ITEMMALL) != true ) // ������ �� ��ǰ�� ������ �ȸ�����ش�.
		{
			if(pclClient->pclItemManager->UsedSlotItem(siunique) == SLOTITEMTYPE_AVATAR) // �ƹ�Ÿ ���������� ���Ի����� �����Ұ��.
			{
				if(type ==ITEMTYPE_AVATAR_NECK )
				{
					pclitem->siUseCrystalNum =1; // ���� 1��
				}	
				else
				{
					pclitem->siUseCrystalNum = 3; // ���� 3��
				}
			}
		}
	}

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ������ ������ ������ ����� �ش�.
	if(pclClient->IsCountrySwitch(Switch_Artifact))
	{
		if ( IsItemInfoAtb(siunique,ITEMINFOATB_ITEMMALL) != true ) // ������ �� ��ǰ�� ������ �ȸ�����ش�.
		{
			if(pclClient->pclItemManager->UsedSlotItem(siunique) == SLOTITEMTYPE_WEAPON) // �ƹ�Ÿ �������� ������ ������ �����۵�.
			{
				cltItemConition  *pclCondition = &pclItemInfo[ref]->clCondition;
				SI08 temCrystalNum = 0;

				SI16 randNum = rand()%100; // ���� �߻�.

				if((pclCondition->siLevel >= 1)&&(pclCondition->siLevel <= 29))
				{
					if((randNum>=0)&&(randNum < 15))
					{
						temCrystalNum = 1;
					}
					else if((randNum>=15)&&(randNum < 28))
					{
						temCrystalNum = 2;
					}
				}
				else if((pclCondition->siLevel >= 30)&&(pclCondition->siLevel <= 59))
				{
					if((randNum>=0)&&(randNum < 13))
					{
						temCrystalNum = 1;
					}
					else if((randNum>=13)&&(randNum < 24))
					{
						temCrystalNum = 2;
					}
					else if((randNum>=24)&&(randNum < 30))
					{
						temCrystalNum = 3;
					}
				}
				else if((pclCondition->siLevel >= 60)&&(pclCondition->siLevel <= 89))
				{
					if((randNum>=0)&&(randNum < 12))
					{
						temCrystalNum = 1;
					}
					else if((randNum>=12)&&(randNum < 22))
					{
						temCrystalNum = 2;
					}
					else if((randNum>=22)&&(randNum < 29))
					{
						temCrystalNum = 3;
					}
					else if((randNum>=29)&&(randNum < 33))
					{
						temCrystalNum = 4;
					}
				}
				else if(pclCondition->siLevel >= 90)
				{
					if((randNum>=0)&&(randNum < 10))
					{
						temCrystalNum = 1;
					}
					else if((randNum>=10)&&(randNum < 19))
					{
						temCrystalNum = 2;
					}
					else if((randNum>=19)&&(randNum < 27))
					{
						temCrystalNum = 3;
					}
					else if((randNum>=27)&&(randNum < 33))
					{
						temCrystalNum = 4;
					}
					else if((randNum>=33)&&(randNum < 35))
					{
						temCrystalNum = 5;
					}
				}
				pclitem->siUseCrystalNum = temCrystalNum;

				//if(pclitem->SetUseCrystalNum(temCrystalNum) != true)
				//	return false;
			}
		}
	}

	// [���] /SEQ ��ɾ�� ���� ��ǰ�̸� ������ �־��ش�.
	if(bSEQCreate == true)
	{
		if(slotnum > 0)		pclitem->siUseCrystalNum = slotnum;
	}

	// �⺻ ��ǰ���� ������ �ϴ� �����̸� ����. 
	if((orgqualityrate == 0)&&(type != ITEMTYPE_CRYSTAL))
	{
		if (usedate == 0 && type != ITEMTYPE_NECK)
			pclitem->uiDateUseDay = 0;

		SI32 rndStateKind	= 0;
		SI32 rndStateAmount = 0;

		// ������ �� ��ǰ�̸� �Ǻ��̳� �����̸� ������ �߶��ش�.
		if( IsItemInfoAtb(siunique,ITEMINFOATB_ITEMMALL) == true )
		{
			if ( type == ITEMTYPE_DRESS || type == ITEMTYPE_HAT )
			{
				pclitem->clItemStatusArmour.clOptionInfo.uiType1 = SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON ;
				pclitem->clItemStatusArmour.clOptionInfo.uiPara1 = 20 ;

				// ���� ��Ͽ� �� �������̶�� �������� �ɷ�ġ�� �־��ش�.
				if ( pclserver->pclGachaManager->IsGachaRareItem( siunique ) == true )
				{
					pclitem->clItemStatusArmour.clOptionInfo.uiType1 = SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON ;

					SI32 rndWeaponSkillUpLevel = 0;
					SI32 rndMakeSkillUpLevel = 0;

					// PCK : ������� 4~8���� �������� �ش�.
					// PCK : �������� 4~8���� �������� �ش�.
					if(	  siunique == ITEMUNIQUE(23734) || siunique == ITEMUNIQUE(23735) || siunique == ITEMUNIQUE(23115) || siunique == ITEMUNIQUE(23116)		// ������ �Ǻ�
					   || siunique == ITEMUNIQUE(23696) || siunique == ITEMUNIQUE(23698) || siunique == ITEMUNIQUE(23117) || siunique == ITEMUNIQUE(23118)		// ��ȥ ����
					   || siunique == ITEMUNIQUE(23410) || siunique == ITEMUNIQUE(23411) || siunique == ITEMUNIQUE(23742) || siunique == ITEMUNIQUE(23741)  )	// �Ǹ� �Ǻ�		
					{
						rndWeaponSkillUpLevel	= rand() % 5 + 4;
						rndMakeSkillUpLevel		= rand() % 5 + 4;
					}
					else
					{
						rndWeaponSkillUpLevel	= rand() % 5 + 3;
						rndMakeSkillUpLevel		= rand() % 5 + 3;
					}
					
					pclitem->clItemStatusArmour.clOptionInfo.uiPara1 = rndWeaponSkillUpLevel * 10 ;
					pclitem->clItemStatusArmour.uiSkillUp			 = rndMakeSkillUpLevel;

					rndStateKind   = rand() % 6;
					rndStateAmount = 0;

					// PCK : ������ �Ǻ��� ��� �ɷ�ġ�� 20���� ���Ѵ�.
					// PCK : ��ȥ ���� �߰� (09.05.06)
					if(   siunique == ITEMUNIQUE(23734) || siunique == ITEMUNIQUE(23735) || siunique == ITEMUNIQUE(23115) || siunique == ITEMUNIQUE(23116)			// ������ �Ǻ�
					   || siunique == ITEMUNIQUE(23696) || siunique == ITEMUNIQUE(23698) || siunique == ITEMUNIQUE(23117) || siunique == ITEMUNIQUE(23118)			// ��ȥ ����
					   || siunique == ITEMUNIQUE(23410) || siunique == ITEMUNIQUE(23411 )|| siunique == ITEMUNIQUE(23742) || siunique == ITEMUNIQUE(23741) )		// �Ǹ� �Ǻ�	
					{
						rndStateAmount = 20;
					}
					else
					{
						rndStateAmount = 15;
					}

					switch( rndStateKind )
					{
						case 0 : pclitem->clItemStatusArmour.uiStr = rndStateAmount; break;
						case 1 : pclitem->clItemStatusArmour.uiDex = rndStateAmount; break;
						case 2 : pclitem->clItemStatusArmour.uiVit = rndStateAmount; break;
						case 3 : pclitem->clItemStatusArmour.uiMag = rndStateAmount; break;
						case 4 : pclitem->clItemStatusArmour.uiHnd = rndStateAmount; break;
						case 5 : pclitem->clItemStatusArmour.uiLuk = rndStateAmount; break;
					}
				}
			}
		}
		
		// �巹���� �����ΰ�� ���� �������� ��� ������ ó��.
		if( type == ITEMTYPE_DRESS || type == ITEMTYPE_HAT )
		{
			// ���̺��� ���� �����ϴ� �������̸�.
			if( UPGRADESKILLTYPE_USE_TABLE_VALUE & pclItemInfo[ref]->siUpgradeSkillType ) 
			{
				pclitem->clItemStatusArmour.clOptionInfo.uiType1 = SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON ;
				pclitem->clItemStatusArmour.clOptionInfo.uiPara1 = 0;

				// ���� ��Ͽ� �� �������̶�� �������� �ɷ�ġ�� �־��ش�.
				if ( pclserver->pclGachaManager->IsGachaRareItem( siunique ) == true )
				{
					if( UPGRADESKILLTYPE_USEWEAPON & pclItemInfo[ref]->siUpgradeSkillType )
					{
						pclitem->clItemStatusArmour.clOptionInfo.uiPara1 = ((rand() % 5) + pclItemInfo[ref]->clItem.GetAC(this)) * 10 ;
					}
					if( UPGRADESKILLTYPE_MAKE & pclItemInfo[ref]->siUpgradeSkillType )
					{
						pclitem->clItemStatusArmour.uiSkillUp = ((rand() % 5) + pclItemInfo[ref]->clItem.GetAC(this));
					}
				}
				else
				{
					if( UPGRADESKILLTYPE_USEWEAPON & pclItemInfo[ref]->siUpgradeSkillType )
					{
						pclitem->clItemStatusArmour.clOptionInfo.uiPara1 = pclItemInfo[ref]->clItem.GetAC(this) * 10 ;
					}
					if( UPGRADESKILLTYPE_MAKE & pclItemInfo[ref]->siUpgradeSkillType )
					{
						pclitem->clItemStatusArmour.uiSkillUp = pclItemInfo[ref]->clItem.GetAC(this);
					}
				}
			}
			
			//[����] �������ͽ� 20�� �����Ѵ�.
			if( UPGRADESKILLTYPE_STATUS_UP_20 & pclItemInfo[ref]->siUpgradeSkillType ) 
			{
				rndStateAmount = 20;
				switch( rndStateKind )
				{
					case 0 : pclitem->clItemStatusArmour.uiStr = rndStateAmount; break;
					case 1 : pclitem->clItemStatusArmour.uiDex = rndStateAmount; break;
					case 2 : pclitem->clItemStatusArmour.uiVit = rndStateAmount; break;
					case 3 : pclitem->clItemStatusArmour.uiMag = rndStateAmount; break;
					case 4 : pclitem->clItemStatusArmour.uiHnd = rndStateAmount; break;
					case 5 : pclitem->clItemStatusArmour.uiLuk = rndStateAmount; break;
				}
			}
		}

		return true;
	}

	// ������ ���� ������ �������̸鼭 �Ǻ��̳� ���ڶ�� ������ �߶��ش�.
	if ( (type == ITEMTYPE_DRESS || type == ITEMTYPE_HAT) &&(siunique != ITEMUNIQUE(23061)))  // ��Ÿ���ڸ� ���ܴ�;;
	{
		pclitem->clItemStatusArmour.clOptionInfo.uiType1 = SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON ;
		pclitem->clItemStatusArmour.clOptionInfo.uiPara1 = 20 ;
	}

	// ǰ�� Ȯ���� ���� �������� �ɷ�ġ�� �����Ѵ�.
	switch(type)
	{
	//KHY - 20090526 - �ƹ�Ÿ ����ü.
	case ITEMTYPE_CRYSTAL:
		{
			if(IsItemInfoAtb(siunique,ITEMINFOATB_ITEMMALL) == true ) // ����ü �̸鼭 ������ �� ��ǰ �̶��.
			{
				// �ɷ�ġ�� ������ ������.
				MakeCrystal(pclitem, qualityrate);
			}
		}
		break;
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
		{
			SI32 randaddrate = rand() % 2 ;	// �̴ϰ��� ����� �������� ����

			// ���ݷ��� �����Ѵ�. 
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;	// ��� ������
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);

			if ( randaddrate == 0 )	// �̴ϰ��� ��� ���� -> ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
			{
				// ���� ��ġ�� �ִ� 110%������ �÷��ش�.
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}

			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����

			MakeApower(pclitem, qualityrate);

			// ���� ����� �����Ѵ�. 
			if(pclitem->clItemWeapon.uiMag)
			{
				if ( magrate != 0 && magrate > 0 && magrate <= 500 )
					qualityrate = magrate ;
				else
					qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);	// -> ���������� �����ؾ� �Ѵ�. 

				if ( randaddrate == 1 )	// �̴ϰ��� ��� ���� ->  ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
				{
					randaddrate = rand() % 2 ;	// �ٽ��ѹ� �̴ϰ��� ����� �������� �����Ѵ�.
					if ( randaddrate == 0 )
					{
						qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
					}
				}

				// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
				if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
				{
					if(orgqualityrate < 100)
					{
						qualityrate = orgqualityrate;
						// ��ǰ
						*pbrareswitch = -1;
					}
				}

				SI16 beforerareswitch = *pbrareswitch;

				if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
				else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
				else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����

				UI32 basicMag = pclitem->clItemWeapon.uiMag;

				pclitem->clItemWeapon.uiMag = min(1000, pclitem->clItemWeapon.uiMag * qualityrate / 100);

				if( beforerareswitch <= 0 && *pbrareswitch > 0 && basicMag == pclitem->clItemWeapon.uiMag)
				{
					*pbrareswitch = 0; //�Ϲ�ǰ���� 
				}
			}

			if ( randaddrate == 0 )
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
			}
			else
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
			}

			// ITEMTYPE_CANNON�� �ƴϰ�, ���ǰ�� ��� ���Ⱓ�� �����Ѵ�. - By LEEKH
			if(type != ITEMTYPE_CANNON && *pbrareswitch == 3)
			{
				pclitem->uiDateUseDay = GetHighItemDate();
			}

			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				// �ű��̸鼭 ���ѳ������� �ƴϸ� ��ǰ ��¥�� ����
				if ( 3 == *pbrareswitch )
				{
					UI32 uiMaxDurability		= (UI32)pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
					UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
					UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

					if ( (uiForeverDurability != uiMaxDurability) && (uiForeverDurability2 != uiMaxDurability) )
					{
						pclitem->uiDateUseDay = 0;
					}
				}
			}

			/*if ( type == ITEMTYPE_TORPEDO )
			{
				if ( randaddrate == 0 )
				{
					// �������� �����Ѵ�.
					MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
				}
				else
				{
					// �������� �����Ѵ�.
					MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
				}
			}*/ // -- ������ �ڵ� ���� - by LEEKH 2007.07.30
			/*else
			{
			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate,monstercorp);
			}
			}*/
		}
		break;

	case ITEMTYPE_HELMET:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_BELT:
		{
			SI32 randaddrate = rand() % 2 ;
			// ������ �����Ѵ�. 
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);

			if ( randaddrate == 0 )
			{
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}

			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����


			MakeDpower(pclitem, qualityrate);

			// ����� �����Ѵ�. 
			if(pclitem->clItemArmour.uiLuck)
			{
				if ( magrate != 0 && magrate > 0 && magrate <= 500 )
					qualityrate = magrate ;
				else
					qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
				if ( randaddrate == 1 )
				{
					randaddrate = rand() % 2 ;
					if ( randaddrate == 0 )
					{
						qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
					}
				}

				// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
				if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
				{
					if(orgqualityrate < 100)
					{
						qualityrate = orgqualityrate;
						// ��ǰ
						*pbrareswitch = -1;
					}
				}

				SI16 beforerareswitch = *pbrareswitch;

				if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
				else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
				else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����

				UI32 basicLuck = pclitem->clItemArmour.uiLuck;

				pclitem->clItemArmour.uiLuck	= min(500, pclitem->clItemArmour.uiLuck * qualityrate / 100 );

				if( beforerareswitch <= 0 && *pbrareswitch > 0 && basicLuck == pclitem->clItemArmour.uiLuck)
				{
					*pbrareswitch = 0; //�Ϲ�ǰ���� 
				}
			}

			// ��� ����� �����Ѵ�. 
			if(pclitem->clItemArmour.uiSkillUp)
			{
				if ( skillrate != 0 && skillrate > 0 && skillrate <= 500 )
					qualityrate = skillrate ;
				else
					qualityrate = GetAverage( max(10, orgqualityrate) , bCanMakeRareItemSwitch, addlevel);
				if ( randaddrate == 1 )
				{
					randaddrate = rand() % 2 ;
					if ( randaddrate == 0 )
					{
						qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
					}
				}

				// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
				if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
				{
					if(orgqualityrate < 100)
					{
						qualityrate = orgqualityrate;
						// ��ǰ
						*pbrareswitch = -1;
					}
				}

                SI16 beforerareswitch = *pbrareswitch;

				if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
				else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
				else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����

				UI32 basicSkillUp = pclitem->clItemArmour.uiSkillUp;

				// [����] 2010.02.02 "���� ���� ����" ��ų Ÿ�� �� ��� ������ ����Ƽ�ʹ� ��� ���� �⺻������ �Ѵ�.
				if(!( pclItemInfo[ref]->siUpgradeSkillType & UPGRADESKILLTYPE_USEWEAPON))
				{
					pclitem->clItemArmour.uiSkillUp	= min(60, pclitem->clItemArmour.uiSkillUp * qualityrate / 100 );
				}

				if( beforerareswitch <= 0 && *pbrareswitch > 0 && basicSkillUp == pclitem->clItemArmour.uiSkillUp)
				{
					*pbrareswitch = 0; //�Ϲ�ǰ���� 
				}
			}

			if ( randaddrate == 0 )
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
			}
			else
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
			}

			// ���ǰ�� ��� ���Ⱓ�� �����Ѵ�. - By LEEKH
			if ( *pbrareswitch == 3 )
			{
				pclitem->uiDateUseDay = GetHighItemDate();
			}

			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				// �ű��̸鼭 ���ѳ������� �ƴϸ� ��ǰ ��¥�� ����
				if ( 3 == *pbrareswitch )
				{
					UI32 uiMaxDurability		= (UI32)pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
					UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
					UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

					if ( (uiForeverDurability != uiMaxDurability) && (uiForeverDurability2 != uiMaxDurability) )
					{
						pclitem->uiDateUseDay = 0;
					}
				}
			}

			/*			//MakeDur(pbrareswitch, 100, pclitem, true);
			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
			}*/
		}
		break;
	case ITEMTYPE_HAT:
	case ITEMTYPE_DRESS:
		{
			SI32 randaddrate = rand() % 2 ;
			// ������ �����Ѵ�. 
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);

			if ( randaddrate == 0 )
			{
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}

			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����


			//MakeDpower(pclitem, qualityrate);

			//// ����� �����Ѵ�. 
			//if(pclitem->clItemArmour.uiLuck)
			//{
			//	if ( magrate != 0 && magrate > 0 && magrate <= 500 )
			//		qualityrate = magrate ;
			//	else
			//		qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			//	if ( randaddrate == 1 )
			//	{
			//		randaddrate = rand() % 2 ;
			//		if ( randaddrate == 0 )
			//		{
			//			qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			//		}
			//	}
			//	if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			//	else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����

			//	pclitem->clItemArmour.uiLuck	= min(500, pclitem->clItemArmour.uiLuck * qualityrate / 100 );
			//}

			//// ��� ����� �����Ѵ�. 
			//if(pclitem->clItemArmour.uiSkillUp)
			//{
			//	if ( skillrate != 0 && skillrate > 0 && skillrate <= 500 )
			//		qualityrate = skillrate ;
			//	else
			//		qualityrate = GetAverage( max(10, orgqualityrate) , bCanMakeRareItemSwitch, addlevel);
			//	if ( randaddrate == 1 )
			//	{
			//		randaddrate = rand() % 2 ;
			//		if ( randaddrate == 0 )
			//		{
			//			qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			//		}
			//	}
			//	if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			//	else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����

			//	pclitem->clItemArmour.uiSkillUp	= min(60, pclitem->clItemArmour.uiSkillUp * qualityrate / 100 );
			//}

			/*			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate,monstercorp);
			}*/
			if ( randaddrate == 0 )
			{
				// �������� �����Ѵ�.
				MakeDate(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
			}
			else
			{
				// �������� �����Ѵ�.
				MakeDate(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
			}
		}
		break;
	case ITEMTYPE_BAG:
		// ������ �����Ѵ�. 
		qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);

		if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
		else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����


		pclitem->clItemBag.uiAC	= max(1, pclitem->clItemBag.uiAC * qualityrate / 100 );

		// �������� �����Ѵ�. - ������ ���� - by LEEKH 2007.04.25
		//MakeDur(pbrareswitch, orgqualityrate,  addlevel, pclitem, false);
		break;

	case ITEMTYPE_MANTLE:
		// ������ �����Ѵ�. 
		qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
		if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
		else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����

		pclitem->clItemMantle.uiAC	= max(1, pclitem->clItemMantle.uiAC * qualityrate / 100 );

		// �������� �����Ѵ�. - ������ ���� - by LEEKH 2007.04.25
		//MakeDur(pbrareswitch, orgqualityrate,  addlevel, pclitem, false);
		break;

		// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_MANTLE:
		{
			// �������� �⺻���� qualityrate �� �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			//---------------------------------------------------------------------------------------------

			// �����ۿ� �̴ϰ��ӿ� ���� qualityrate ������ �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			SI32 randaddrate = rand() % 2 ;

			if ( randaddrate == 0 )	// �̴ϰ��� ��� ���� -> ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
			{
				// ���� ��ġ�� �ִ� 110%������ �÷��ش�.
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}
			//---------------------------------------------------------------------------------------------

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			//---------------------------------------------------------------------------------------------
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}
			//---------------------------------------------------------------------------------------------
			// 1�� ���¸�������, ��ǰ�� ������.
			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����


			// ���� ����
			pclitem->clItemAvatarMantle.uiAC	= max(1, pclitem->clItemAvatarMantle.uiAC * qualityrate / 100 );

			//  �ƹ�Ÿ ����� ���¸� �ִ�.

			// ����, ��Ÿ �ٸ� ������ �߰� �Ǿ�, �߰� ����� ���� ���, �̺κп� �߰�.

			// ��� ���� ��¥�� MakeDate() �Լ��� �̿��� �����Ѵ�.
			// ȣǰ, ��ǰ, �ű⿡ ���� ���Ⱓ ����. - ���ο��� �Ѵ�.
			// bforseswitch = true , �Ⱓ�� ����, �߰��� ����. - ��ǰ�� �ȸ��������.
			//MakeAvatarDate( pbrareswitch, 100, addlevel, pclitem, true, durrate );

			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				// �ű��̸鼭 ���ѳ������� �ƴϸ� ��ǰ ��¥�� ����
				if ( 3 == *pbrareswitch )
				{
					UI32 uiMaxDurability		= (UI32)pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
					UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
					UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

					if ( (uiForeverDurability != uiMaxDurability) && (uiForeverDurability2 != uiMaxDurability) )
					{
						pclitem->uiDateUseDay = 0;
					}
				}
			}
		}
		break;

	// �ƹ�Ÿ �Ǻ�
	case ITEMTYPE_AVATAR_DRESS:
		{
			// �ƹ�Ÿ �Ǻ��� �ٸ� �ɷ��� ��������, ���ǹ� �ϴ�.
			/*
			// �������� �⺻���� qualityrate �� �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			//---------------------------------------------------------------------------------------------

			// �����ۿ� �̴ϰ��ӿ� ���� qualityrate ������ �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			SI32 randaddrate = rand() % 2 ;

			if ( randaddrate == 0 )	// �̴ϰ��� ��� ���� -> ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
			{
				// ���� ��ġ�� �ִ� 110%������ �÷��ش�.
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}
			//---------------------------------------------------------------------------------------------

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			//---------------------------------------------------------------------------------------------
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}
			//---------------------------------------------------------------------------------------------
			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����
			*/
			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			//---------------------------------------------------------------------------------------------
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}

			// �ƹ�Ÿ �巹���� ��¥ �ۿ� ����.


			// ��� ���� ��¥�� MakeDate() �Լ��� �̿��� �����Ѵ�.
			// ȣǰ, ��ǰ, �ű⿡ ���� ���Ⱓ ����. - ���ο��� �Ѵ�.
			// bforseswitch = false , �Ⱓ�� ����, �߰��� �ִ�. - ��ǰ�� ���������.
			MakeAvatarDate( pbrareswitch, orgqualityrate, addlevel, pclitem, false, durrate );

			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel, pclitem, false, durrate);
		}
		break;

	// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_HAT:
		{
			// �ٸ� �ɷ��� ������, ���ǹ��ϴ�.
			/*
			// �������� �⺻���� qualityrate �� �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			//---------------------------------------------------------------------------------------------

			// �����ۿ� �̴ϰ��ӿ� ���� qualityrate ������ �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			SI32 randaddrate = rand() % 2 ;

			if ( randaddrate == 0 )	// �̴ϰ��� ��� ���� -> ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
			{
				// ���� ��ġ�� �ִ� 110%������ �÷��ش�.
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}
			//---------------------------------------------------------------------------------------------

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			//---------------------------------------------------------------------------------------------
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}
			//---------------------------------------------------------------------------------------------
			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����
			*/

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			//---------------------------------------------------------------------------------------------
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}
			
			// ��� ���� ��¥�� MakeDate() �Լ��� �̿��� �����Ѵ�.
			// ȣǰ, ��ǰ, �ű⿡ ���� ���Ⱓ ����. - ���ο��� �Ѵ�.
			// bforseswitch = false , �Ⱓ�� ����, �߰��� �ִ�. - ��ǰ�� ���������.
			MakeAvatarDate( pbrareswitch, orgqualityrate, addlevel, pclitem, false, durrate );

			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
		}
		break;

	// �ƹ�Ÿ �����
	case ITEMTYPE_AVATAR_NECK:
		{
			// �������� �⺻���� qualityrate �� �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			//if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
			//	qualityrate = attackrate ;
			//else
			//	qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);

			if(pclitem->clItemAvatarNeck.uiSkillValue >0 )
			{
				if ( skillrate != 0 && skillrate > 0 && skillrate <= 500 )
					qualityrate = skillrate ;
				else
					qualityrate = GetAverage( max(10, orgqualityrate) , bCanMakeRareItemSwitch, addlevel);

				//---------------------------------------------------------------------------------------------
				// �����ۿ� �̴ϰ��ӿ� ���� qualityrate ������ �����Ѵ�.
				//---------------------------------------------------------------------------------------------
				SI32 randaddrate = rand() % 2 ;

				if ( randaddrate == 0 )	// �̴ϰ��� ��� ���� -> ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
				{
					// ���� ��ġ�� �ִ� 110%������ �÷��ش�.
					qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
				}
				//---------------------------------------------------------------------------------------------

				// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
				//---------------------------------------------------------------------------------------------
				if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
				{
					if(orgqualityrate < 100)
					{
						qualityrate = orgqualityrate;
						// ��ǰ
						*pbrareswitch = -1;
					}
				}
				//---------------------------------------------------------------------------------------------
				if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
				else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
				else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����


				// �ּ� �ִ밪�� �����Ǵ�, �κ��� ���� �����Ѵ�.
				//SI32 skillup = (rand() % (TABS(pclitem->clItemAvatarNeck.uiMaxSkillPoint - pclitem->clItemAvatarNeck.uiSkillValue) + 1)) + pclitem->clItemAvatarNeck.uiSkillValue;
				//pclitem->clItemAvatarNeck.uiSkillValue	= max(pclitem->clItemAvatarNeck.uiSkillValue, (UI32)skillup);

				//SI32 usedate = (rand() % (TABS(pclitem->clItemAvatarNeck.uiMaxUsedate - pclitem->uiDateUseDay) + 1)) + pclitem->uiDateUseDay;
				//pclitem->uiDateUseDay = max(pclitem->uiDateUseDay, usedate);

				// qualityrate �� ���� �ƹ�Ÿ ����� ��ų ����Ʈ.
				//SI32 skillup = (float)pclitem->clItemAvatarNeck.uiMaxSkillPoint * (float)(qualityrate/100);
				//skillup = max(1,skillup);

				// �ƹ�Ÿ ������� ��ų ����.
				//---------------------------------------------------------------------------------------------
				// �������� ref�� ���Ѵ�. 
				SI32 ref = FindItemRefFromUnique(siunique);
				if(ref <= 0)
				{
#ifdef _DEBUG
					_ASSERT( ref > 0 );
#endif
					return false;    
				}
				else
				{
					// �⺻ ��ų Ÿ���� ������ ���� ��ų�� �����Ѵ�.
					SI32 szIncSkillUnique =  pclitem->SelectUseBaseSkillTypeToAvatar(pclItemInfo[ref]->siUpgradeSkillUnique);

					// ��ų ����.
					 pclitem->clItemAvatarNeck.uiUpgradeSkillUnique	=  szIncSkillUnique;

					// ���� : ������ ���� ��� ���� �������� ��ų ���� �κ��� ����ǵ��� ����					
					pclitem->clItemAvatarNeck.uiSkillValue = max(pclitem->clItemAvatarNeck.uiSkillValue, pclitem->clItemAvatarNeck.uiSkillValue * qualityrate / 100 );
				}
			}

			// �ƹ�Ÿ ����̴� ��ų�� �ִ�.

			// ��� ���� ��¥�� MakeDate() �Լ��� �̿��� �����Ѵ�.
			// ȣǰ, ��ǰ, �ű⿡ ���� ���Ⱓ ����. - ���ο��� �Ѵ�.
			// bforseswitch = true , �Ⱓ�� ����, �߰��� ����. - ��ǰ�� �ȸ��������.
			//MakeAvatarDate( pbrareswitch, 100, addlevel, pclitem, true, durrate );    << �߹�Ÿ

			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				// �ű��̸鼭 ���ѳ������� �ƴϸ� ��ǰ ��¥�� ����
				if ( 3 == *pbrareswitch )
				{
					UI32 uiMaxDurability		= (UI32)pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
					UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
					UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

					if ( (uiForeverDurability != uiMaxDurability) && (uiForeverDurability2 != uiMaxDurability) )
					{
						pclitem->uiDateUseDay = 0;
					}
				}
			}
		}
		break;

	// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_RING:
		{
			// �������� �⺻���� qualityrate �� �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			//---------------------------------------------------------------------------------------------

			// �����ۿ� �̴ϰ��ӿ� ���� qualityrate ������ �����Ѵ�.
			//---------------------------------------------------------------------------------------------
			SI32 randaddrate = rand() % 2 ;

			if ( randaddrate == 0 )	// �̴ϰ��� ��� ���� -> ����ƼRate ���� (���ݷ°� ������ �ѹ��� �����Ѵ�.)
			{
				// ���� ��ġ�� �ִ� 110%������ �÷��ش�.
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}
			//---------------------------------------------------------------------------------------------

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			//---------------------------------------------------------------------------------------------
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}
			//---------------------------------------------------------------------------------------------
			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����
			
			// ���� : ���� ��ġ�� ���� ������ ������ ��ġ�� �޶�����. (������ ���ȵ��� �� ���� ����)
			pclitem->clItemAvatarRing.SetQualityRate( qualityrate );

			// �ƹ�Ÿ ������ ���ø� �ִ�.

			// ��� ���� ��¥�� MakeDate() �Լ��� �̿��� �����Ѵ�.
			// ȣǰ, ��ǰ, �ű⿡ ���� ���Ⱓ ����. - ���ο��� �Ѵ�.
			// bforseswitch = true , �Ⱓ�� ����, �߰��� ����. - ��ǰ�� �ȸ��������.
			//MakeAvatarDate( pbrareswitch, 100, addlevel, pclitem, true, durrate );

			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				// �ű��̸鼭 ���ѳ������� �ƴϸ� ��ǰ ��¥�� ����
				if ( 3 == *pbrareswitch )
				{
					UI32 uiMaxDurability		= (UI32)pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
					UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
					UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

					if ( (uiForeverDurability != uiMaxDurability) && (uiForeverDurability2 != uiMaxDurability) )
					{
						pclitem->uiDateUseDay = 0;
					}
				}
			}
		}
		break;


	case ITEMTYPE_SHOES:
		{
			SI32 randaddrate = rand() % 2 ;
			// ������ �����Ѵ�. 
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			if ( randaddrate == 0 )
			{
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}

			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����


			pclitem->clItemShoes.uiAC	= max(1, pclitem->clItemShoes.uiAC * qualityrate / 100 );

			// �̵��ӵ��� �����Ѵ�. 
			if ( magrate != 0 && magrate > 0 && magrate <= 500 )
				qualityrate = magrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			if ( randaddrate == 1 )
			{
				randaddrate = rand() % 2 ;
				if ( randaddrate == 0 )
				{
					qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
				}
			}

			// �������й��� - ��ǰ�� �ɷ��� 100%���� ����. - by LEEKH 2007.07.23
			if( pclClient->IsCountrySwitch( Switch_DoNotFailedMakeItem ) )
			{
				if(orgqualityrate < 100)
				{
					qualityrate = orgqualityrate;
					// ��ǰ
					*pbrareswitch = -1;
				}
			}

			SI16 beforerareswitch = *pbrareswitch;

			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����
			else if ( qualityrate >= RARE3_ITEM_RATE && *pbrareswitch != 1 && *pbrareswitch != 2 )*pbrareswitch = 3; // ���ǰ����

			UI32 basicSpeedUp = pclitem->clItemShoes.uiMoveSpeed;

			pclitem->clItemShoes.uiMoveSpeed	= min(9, max(1, pclitem->clItemShoes.uiMoveSpeed * qualityrate / 100 ));

			if( beforerareswitch <= 0 && *pbrareswitch > 0 && basicSpeedUp == pclitem->clItemShoes.uiMoveSpeed )
				*pbrareswitch = 0; //�Ϲ�ǰ���� 

			if ( randaddrate == 0 )
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
			}
			else
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false, durrate, monstercorp);
			}

			// ���ǰ�� ��� ���Ⱓ�� �����Ѵ�. - By LEEKH
			if ( *pbrareswitch == 3 )
			{
				pclitem->uiDateUseDay = GetHighItemDate();
			}

			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				// �ű��̸鼭 ���ѳ������� �ƴϸ� ��ǰ ��¥�� ����
				if ( 3 == *pbrareswitch )
				{
					UI32 uiMaxDurability		= (UI32)pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
					UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
					UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

					if ( (uiForeverDurability != uiMaxDurability) && (uiForeverDurability2 != uiMaxDurability) )
					{
						pclitem->uiDateUseDay = 0;
					}
				}
			}

			/*			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate,monstercorp);
			}*/
			/*			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
			}*/
		}
		break;

	case ITEMTYPE_RING:
		{
			SI32 randaddrate = rand() % 2 ;
			if ( attackrate != 0 && attackrate > 0 && attackrate <= 500 )
				qualityrate = attackrate ;
			else
				qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
			if ( randaddrate == 0 )
			{
				qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
			}
			if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
			else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����

			// �ٷ� 
			pclitem->clItemRing.uiStr	= pclitem->clItemRing.uiStr * (qualityrate / 100);
			// ���߷�
			pclitem->clItemRing.uiDex	= pclitem->clItemRing.uiDex * (qualityrate / 100) ;
			// ����
			pclitem->clItemRing.uiMag	= pclitem->clItemRing.uiMag * (qualityrate / 100) ;
			// ����� 
			pclitem->clItemRing.uiVit	= pclitem->clItemRing.uiVit * (qualityrate / 100) ;
			// �� 
			pclitem->clItemRing.uiLuk	= pclitem->clItemRing.uiLuk * (qualityrate / 100) ;
			// ������ 
			pclitem->clItemRing.uiHnd	= pclitem->clItemRing.uiHnd * (qualityrate / 100) ;

			if ( randaddrate == 0 )
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
			}
			else
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
			}

			/*			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate,monstercorp);
			}*/
			/*			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate,monstercorp);
			}*/
		}
		break;

	case ITEMTYPE_NECK:
		{
			SI32 randaddrate = rand() % 2 ;
			// ��� ����� �����Ѵ�. 
			if(pclitem->clItemNeck.uiSkillPointUp)
			{
				if ( skillrate != 0 && skillrate > 0 && skillrate <= 500 )
					qualityrate = skillrate ;
				else
					qualityrate = GetAverage(orgqualityrate, bCanMakeRareItemSwitch, addlevel);
				if ( randaddrate == 0 )
				{
					qualityrate = qualityrate + ( qualityrate * monstercorp / 100000 ) ;
				}
				if(qualityrate >= RARE2_ITEM_RATE)*pbrareswitch = 1;		// ��ǰ ����
				else if ( qualityrate >= RARE1_ITEM_RATE && *pbrareswitch != 1 )*pbrareswitch = 2; // ȣǰ����

				pclitem->clItemNeck.uiSkillPointUp	= min(60, pclitem->clItemNeck.uiSkillPointUp * qualityrate / 100 );
			}

			if ( randaddrate == 0 )
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate);
			}
			else
			{
				// �������� �����Ѵ�.
				MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);
			}

			/*			if ( randaddrate == 0 )
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate);
			}
			else
			{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, pclitem, false,durrate,monstercorp);
			}*/
			if ( randaddrate == 0 )
			{
				// �������� �����Ѵ�.
				MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate);
			}
			else
			{
				// �������� �����Ѵ�.
				MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate, monstercorp);
			}
		}
		break;

	case ITEMTYPE_IRON:
	case ITEMTYPE_DISH:		
	case ITEMTYPE_PAPER:
	case ITEMTYPE_FISHINGROD:
		{
			// �������� �����Ѵ�.
			MakeDur(pbrareswitch, orgqualityrate, addlevel, pclitem, false,durrate,monstercorp);

			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				if ( 0 < pclitem->uiDateUseDay )
				{
					MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate,monstercorp);
				}
			}
			else
			{
				MakeDate(pbrareswitch, orgqualityrate, addlevel,  pclitem, false,durrate,monstercorp);
			}
		}
		break;
	}
	// �߱��� ���ǰ ���´�.

	if ( pclClient->IsWhereServiceArea( ConstServiceArea_China) )
	{
		if ( *pbrareswitch == 3 )
			*pbrareswitch = 0;
	}

	//--------------------------------------------------------
	// ��ǰ�� ��������� ���� �ð� �����鵵�� �����Ѵ�. 
	//--------------------------------------------------------
	// [���] /SEQ �� ����� �������� �ð�������� �ٷ� ����� �ְ� �Ѵ�.
	if(bSEQCreate == true)
	{
		//��ǰ
		if(*pbrareswitch == 1)
		{
			pclitem->clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_2;
		}
		// ȣǰ
		else if(*pbrareswitch == 2)
		{
			pclitem->clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_1;
		}
		// ���ǰ
		else if(*pbrareswitch == 3)
		{
			pclitem->clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_5;
		}

		return true;
	}

	if( *pbrareswitch > 0 && *pbrareswitch < 3 )
	{
		bCanMakeRareItemSwitch	= false;
		dwLastMakeRareItemClock = pclClient->CurrentClock;
	}
	else
	{
		if(bCanMakeRareItemSwitch == false && TABS(pclClient->CurrentClock - dwLastMakeRareItemClock) >= 600000)
		{
			bCanMakeRareItemSwitch = true;
		}
	}

	return true;
}


bool cltItemManagerCommon::MakeDefaultItem(SI32 siunique, SI32 itemnum, cltItem* pclitem)
{
	if(siunique == 0)		return false;
	if(itemnum == 0)		return false;
	if(pclitem == NULL)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver == NULL)		return false;

	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)
	{
#ifdef _DEBUG
		_ASSERT( ref > 0 );
#endif
		return false;
	}

	pclitem->Set(&pclItemInfo[ref]->clItem);

	pclitem->Element.siType = ENCHANT_TYPE_DEFAULT;
	pclitem->Element.siPower = 0;

	return true;
}


// �־��� ��Ḧ �ٰŷ� ���� ������ �������� ����Ʈ�� �ۼ��ؼ� �����Ѵ�. 
// ���� ����Ʈ�� ����� ������ �־�� �Ѵ�. 
// pclskill					: ������� ��� ����.(NULL�̸� ����� ���õȴ�.) 
// bonlymaterialcheckswitch : ���Ḹ ������ ����� �ִ� ǰ���� üũ�Ѵ�.(������ ���õ�) 
#define MAX_FINDMAKABLEITEM_NUM		100
bool cltItemManagerCommon::FindMakeableItem(cltPSkillInfo* pclskill, cltPItemInfo* pclcharitem, cltBasicAbility* pclBA, SI32 materialnum, cltItem pclmaterialitem[], SI32* pmakeableitemnum, SI32** ppitemlist, bool bonlymaterialcheckswitch)
{
	SI32	palliteminfo[MAX_FINDMAKABLEITEM_NUM * 2];
	ZeroMemory(palliteminfo, sizeof(SI32) * MAX_FINDMAKABLEITEM_NUM * 2);
	
	SI32 i;
	BOOL bTutorialMake = FALSE;
	SI32 siTutorialItemUnique = 0;
	BOOL bTutorialLevelMake = FALSE;
	SI32 siTutorialItemLevel = 0;

	SI32 producenum;
	SI32 returnval;
	SI32 returnpara1;

	SI16 questtype = 0, questunique = 0, para1 = 0, para2 = 0;
	SI16 questclearcond =  QUEST_CLEAR_COND_TUTORIALMAKEITEM;

	SI16 siAntiPotion	= ITEMUNIQUE(2796);
	SI16 siLostWorldQuestItem1 = ITEMUNIQUE(8115);
	SI16 siLostWorldQuestItem2 = ITEMUNIQUE(8116);
	SI16 siLostWorldQuestItem3 = ITEMUNIQUE(8117);
	SI16 siLostWorldQuestItem4 = ITEMUNIQUE(8118);

	BOOL bAntiPotion	= FALSE;
	BOOL bLostWorldQuestItem1 = FALSE;
	BOOL bLostWorldQuestItem2 = FALSE;
	BOOL bLostWorldQuestItem3 = FALSE;
	BOOL bLostWorldQuestItem4 = FALSE;

	// ����Ʈ Ȯ���� Ŭ���̾�Ʈ�� �Ѵ�. - by LEEKH 2008-09-09
	if(pclClient->GameMode == GAMEMODE_CLIENT)
	{
		cltCharClient* pclcharclient = pclClient->pclCM->GetCharClient( 1 );
		if ( pclcharclient )
		{
			if(pclcharclient->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
			{
				if(	( pclcharclient->pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 == para1) 
					&& ( pclcharclient->pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 < para2) )
				{
					bTutorialMake = TRUE;
					siTutorialItemUnique = para1;
				}
			}//����Ʈ ������ Ȯ�� �Ѵ�.

			questclearcond =  QUEST_CLEAR_COND_TUTORIALMAKELEVELITEM;
			if(pclcharclient->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
			{
				if(	( pclcharclient->pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 == para1) 
					&& ( pclcharclient->pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 < para2) )
				{
					bTutorialLevelMake = TRUE;
					siTutorialItemLevel = para1;
				}
			}//����Ʈ ������ Ȯ�� �Ѵ�.

			// ��Ƽ����(2796)�� �ش�����Ʈ ������ �ɷ������� �����ϴ�
			questclearcond = QUEST_CLEAR_COND_MAKEITEM;
			if ( true == pclcharclient->pclCI->clQuestInfo.IsSameParaQuestGoing(questclearcond, siAntiPotion) )
			{
				bAntiPotion = TRUE;
			}
			// ��Ƽ����üũ �������

			// PCK : �Ҿ���� ���� ����Ʈ ���� �������� �ش� ����Ʈ ������ ������ �ɷ������� �����ϴ�.(09.05.12)
			if ( true == pclcharclient->pclCI->clQuestInfo.IsSameParaQuestGoing(questclearcond, siLostWorldQuestItem1))
			{
				bLostWorldQuestItem1 = TRUE;
			}

			if ( true == pclcharclient->pclCI->clQuestInfo.IsSameParaQuestGoing(questclearcond, siLostWorldQuestItem2))
			{
				bLostWorldQuestItem2 = TRUE;
			}

			if ( true == pclcharclient->pclCI->clQuestInfo.IsSameParaQuestGoing(questclearcond, siLostWorldQuestItem3))
			{
				bLostWorldQuestItem3 = TRUE;
			}

			if ( true == pclcharclient->pclCI->clQuestInfo.IsSameParaQuestGoing(questclearcond, siLostWorldQuestItem4))
			{
				bLostWorldQuestItem4 = TRUE;
			}
			// �Ҿ���� ���� ����Ʈ ���� üũ �������
		}
	}

	// �ʱ�ȭ ����� �Ѵ�.
	*pmakeableitemnum	= 0;

	for(i = 0; i<MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i] == NULL)		continue;

		// ��Ƽ������ �ش������ ���� ����Ʈ���� ����� �ֵ��� �Ѵ�
		if ( (siAntiPotion == pclItemInfo[i]->clItem.siUnique) )
		{
			if ( FALSE == bAntiPotion )	continue;
		}
		
		// PCK : �Ҿ���� ���� ����Ʈ�� �������� �ش� ������ ���� ����Ʈ���� ����� �ֵ��� �Ѵ�. (09.05.12)
		if ( (siLostWorldQuestItem1 == pclItemInfo[i]->clItem.siUnique) )
		{
			if ( FALSE == bLostWorldQuestItem1 )	continue;
		}
		if ( (siLostWorldQuestItem2 == pclItemInfo[i]->clItem.siUnique) )
		{
			if ( FALSE == bLostWorldQuestItem2 )	continue;
		}
		if ( (siLostWorldQuestItem3 == pclItemInfo[i]->clItem.siUnique) )
		{
			if ( FALSE == bLostWorldQuestItem3 )	continue;
		}
		if ( (siLostWorldQuestItem4 == pclItemInfo[i]->clItem.siUnique) )
		{
			if ( FALSE == bLostWorldQuestItem4 )	continue;
		}

		// Ʃ�丮�� ����Ʈ ���̶�� ��ų������ üũ���� �ʴ´�. ����Ʈ ��ᰡ �ִٸ� ��Ḧ �缳���� �ֱ⵵ �Ѵ�.
		if( (bTutorialMake && siTutorialItemUnique == pclItemInfo[i]->clItem.siUnique) || 
			(bTutorialLevelMake && siTutorialItemLevel == pclItemInfo[i]->clCondition.siLevel) )
		{
			cltMaterialInfo	TutorialQuestMaterial[MAX_MATERIAL_NUMBER];
			BOOL bUseQuestItem = FALSE;

			if(pclClient->pclQuestManager->GetTutorialMakeQuestItem(questunique,siTutorialItemUnique,TutorialQuestMaterial) == true)
			{
				bUseQuestItem = TRUE;
			}

			producenum = returnval = returnpara1 = 0;
			if(pclItemInfo[i]->CanMake(materialnum,  pclmaterialitem, pclmaterialitem, &producenum, &returnval, &returnpara1, bonlymaterialcheckswitch,TRUE,bUseQuestItem,TutorialQuestMaterial) == true)
			{
				// ��ȿ�� ���� ���� �ȿ���. 
				if((*pmakeableitemnum) < MAX_FINDMAKABLEITEM_NUM)
				{
					palliteminfo[(*pmakeableitemnum)*2]	= pclItemInfo[i]->clItem.siUnique;
					palliteminfo[(*pmakeableitemnum)*2+1] = producenum;

					(*pmakeableitemnum)++;
				}
			}//�κ��丮���� �˻�.
			continue;
		}
	
		// ����� �ٰŷ� ��ǰ�� ���� �� �ִ��� Ȯ���Ѵ�. 
		if(pclskill && pclItemInfo[i]->CanMake_Skill(pclskill, pclcharitem, pclBA) == false)continue;

		producenum = returnval = returnpara1 = 0;
		if(pclItemInfo[i]->CanMake(materialnum,  pclmaterialitem, pclmaterialitem, &producenum, &returnval, &returnpara1, bonlymaterialcheckswitch) == true)
		{
			// ��ȿ�� ���� ���� �ȿ���. 
			if((*pmakeableitemnum) < MAX_FINDMAKABLEITEM_NUM)
			{
				palliteminfo[(*pmakeableitemnum)*2]	= pclItemInfo[i]->clItem.siUnique;
				palliteminfo[(*pmakeableitemnum)*2+1] = producenum;
				
				(*pmakeableitemnum)++;
			}
		}
	}	

	// ���� ������ �����ؼ� �����Ѵ�. 
	// �ƹ��͵� ������ �� ������ ����. 
	if((*pmakeableitemnum) == 0)return false;
	
	(*ppitemlist) = new SI32 [(*pmakeableitemnum) * 2];
	
	for(i = 0;i< (*pmakeableitemnum);i++)
	{
		(*ppitemlist)[i*2]		= palliteminfo[i*2];
		(*ppitemlist)[i*2+1]	= palliteminfo[i*2+1];
	}
	
	return true;	
	
}
// ��ǰ�� ��ǰ���� ������ش�. 
bool cltItemManagerCommon::MakeRareItem(cltItem* pclitem,SI32 mode)
{
	if(pclitem == NULL)return false;
	if(pclitem->siUnique <= 0)return false;

	SI32 siunique = pclitem->siUnique;

	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)
	{
		TCHAR buffer[256];
		StringCchPrintf(buffer, 256, TEXT("MakeRareItem() f827s3:%d"), siunique);
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("Error"), buffer, MB_OK|MB_TOPMOST);
		return false;
	}

	// �������� Type�� ���Ѵ�. 
	SI32 type = pclItemInfo[ref]->siType;

	// ������ Type�� Atb�� ���Ѵ�. 
	SI64 atb = pclItemTypeInfo[type]->siAtb;

	// �������� Object�� �ƴϸ� ����. 
	if((atb & ITEMATB_OBJECT) == 0)
	{
		return false;
	}

	SI16 brareswitch = 0;

	// ǰ�� Ȯ���� ���� �������� �ɷ�ġ�� �����Ѵ�. 
	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
		// ���ݷ� ��ǰ�� �����. 
		if( ( rand() % 3 && mode == 0 ) || mode == 1 )
		{
			brareswitch	= true;

			pclitem->clItemWeapon.uiMaxDamage = pclItemInfo[ref]->clItem.clItemWeapon.uiMaxDamage;
			pclitem->clItemWeapon.uiMinDamage = pclItemInfo[ref]->clItem.clItemWeapon.uiMinDamage;

			MakeApower(pclitem, 300);
		}
		break;
	case ITEMTYPE_STAFF:
		// ���ݷ� ��ǰ�� �����. 
		if( ( rand() % 3 && mode == 0 ) || mode == 1 )
		{
			brareswitch	= true;

			pclitem->clItemWeapon.uiMaxDamage = pclItemInfo[ref]->clItem.clItemWeapon.uiMaxDamage;
			pclitem->clItemWeapon.uiMinDamage = pclItemInfo[ref]->clItem.clItemWeapon.uiMinDamage;

			MakeApower(pclitem, 300);
		}
		// ���� ��ǰ�� �����.
		if ( !brareswitch )
		{
			if( ( rand() % 4 && mode == 0 ) || mode == 2 )
			{
				brareswitch	= true;

				pclitem->clItemWeapon.uiMag = pclItemInfo[ref]->clItem.clItemWeapon.uiMag;

				pclitem->clItemWeapon.uiMag = min(1000, pclitem->clItemWeapon.uiMag * 3 );
			}
		}
		break;

	case ITEMTYPE_HELMET:
	case ITEMTYPE_BELT:
	case ITEMTYPE_ARMOUR:
		// ���� ��ǰ�� �����. 
		if( ( rand() % 3 && mode == 0 ) || mode == 1 )
		{
			brareswitch	= true;

			pclitem->clItemArmour.uiAC = pclItemInfo[ref]->clItem.clItemArmour.uiAC;

			MakeDpower(pclitem, 300);
		}
		break;

	case ITEMTYPE_DRESS:
	case ITEMTYPE_HAT:
		// ���� ��ǰ�� �����. 
		//if( ( rand() % 3 && mode == 0 ) || mode == 1 )
		//{
		//	brareswitch	= true;

		//	pclitem->clItemStatusArmour.uiAC = pclItemInfo[ref]->clItem.clItemStatusArmour.uiAC;

		//	MakeDpower(pclitem, 300);
		//}
		break;
	case ITEMTYPE_BAG:
		break;

	case ITEMTYPE_MANTLE:
		break;
		
	case ITEMTYPE_SHOES:
		break;
		
	case ITEMTYPE_RING:
		break;

	case ITEMTYPE_NECK:
		break;

	case ITEMTYPE_IRON:
	case ITEMTYPE_DISH:		
	case ITEMTYPE_PAPER:
	case ITEMTYPE_FISHINGROD:
	//case ITEMTYPE_CRYSTAL: //��Ƽ��Ʈ
		break;
	}

	// ��ǰ�� �ƴϸ� �������� ��ǰ�� �����. 
	SI32 dur = 0;
	if(brareswitch == false)
	{
		dur = 300;
	}
	else
	{
		dur = 100;
	}

	// �������� �����Ѵ�.(������ �����Ѵ�.) 
	//MakeDur(&brareswitch, dur, pclitem, true);

	//cyj �Ⱓ���� ����
	MakeDate(&brareswitch, dur, 0, pclitem, true);

	return true;

}

// ����� ��ǰ�� ������ �ٰŷ� ����ġ�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetMakeExpFromItemPrice(INT64 totalprice, SI32 level)
{
	// NPC�ü����� ���� �����Ѵ�. 
	SI32 npcrate = clItemStatistic.siNPCPriceRate;
	if(npcrate == 0)npcrate = 100;

	return min(level * 20, totalprice / 50 * 100 / npcrate) ;
}


// ����� ��ǰ�� ������ �ٰŷ� ����ġ�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetMakeSkillExpFromItemPrice(INT64 totalprice, SI32 skilllevel)
{
	// NPC�ü����� ���� �����Ѵ�. 
	SI32 npcrate = clItemStatistic.siNPCPriceRate;
	if(npcrate == 0)npcrate = 100;

	if (skilllevel < 6)	totalprice = totalprice * 1.7;
	else if (skilllevel < 11)	totalprice = totalprice * 1.6;
	else if (skilllevel < 16)	totalprice = totalprice * 1.5;
	else if (skilllevel < 21)	totalprice = totalprice * 1.4;
	else if (skilllevel < 26)	totalprice = totalprice * 1.3;
	else if (skilllevel < 31)	totalprice = totalprice * 1.2;
	else if (skilllevel < 36)	totalprice = totalprice * 1.1;
	else if (skilllevel >= 36)	totalprice = totalprice * 1.0;

	INT64 price = (totalprice / 4000 ) * 100  / npcrate;

	// �ż��� ��庥Ƽ�� 
	SI32 adv = max(0, 150 - npcrate);
	price = price + price * adv / 100;

	return  min(max(10, skilllevel * 20), price);
}

// �� ��ǰ�� ����� ���Ѵ�.
SI16 cltItemManagerCommon::GetTradeServerObjectRank(cltItem*pclitem)
{
	if ( NULL == pclitem )
	{
		return 0;
	}

	SI32 ref = FindItemRefFromUnique(pclitem->siUnique);
	if(ref <= 0)
	{
		char buffer[256];
		sprintf(buffer, "GetTradeServerObjectRank() a35d6:%d", pclitem->siUnique);
		MessageBox(NULL, "Error", buffer, MB_OK|MB_TOPMOST);

		return 0 ;
	}

	cltItemInfo* pinfo = pclItemInfo[ref];
	if ( pinfo == NULL )
		return 0 ;

	// �������� Type�� ���Ѵ�. 
	SI32 type = pinfo->siType;
	cltItemTypeInfo* ptypeinfo = pclItemTypeInfo[type];
	if ( ptypeinfo == NULL )
		return 0 ;

	if ( ptypeinfo->IsAtb(ITEMATB_TRADESERVER) == FALSE )
		return 0 ;

	SI32 quality = 0 ;

	// �����?
	if ( ptypeinfo->IsAttach(ITEMATTACH_WEAPON) )
	{
		// ���� �ƽ� �������� �����Ѵ�
		quality = ( pclitem->clItemWeapon.uiMaxDamage * 100 ) / pinfo->clItem.clItemWeapon.uiMaxDamage ;
	}
	// ����?
	else if ( ptypeinfo->IsAttach(ITEMATTACH_ARMOUR) )
	{
		quality = ( pclitem->clItemArmour.uiAC * 100 ) / pinfo->clItem.clItemArmour.uiAC ;
	}
	else return 0 ;

	SI16 index = 0 ;
	for ( SI16 i = 0 ; i < MAX_TRADESERVER_OBJECT_RANK ; i ++ )
	{
		if ( quality <= siTradeServerObejectRank[i] )
		{
			index = i ;
			break; 
		}
		else if ( siTradeServerObejectRank[MAX_TRADESERVER_OBJECT_RANK-1] <= quality )
		{
			index = MAX_TRADESERVER_OBJECT_RANK - 1;
			break;
		}
	}

	return index ;
}

// ������ ���� �������� �����.
BOOL cltItemManagerCommon::MakeTradeServerObjectForRank(cltItem*pclitem,SI16 unique,SI16 num ,SI16 rank,SI08 rare,SI16 type,SI16 power)
{
	if ( NULL == pclitem )
	{
		return FALSE;
	}

	SI32 index = 0 ;

	SI32 ref = FindItemRefFromUnique(unique);
	if(ref <= 0)
	{
		char buffer[256];
		sprintf(buffer, "MakeTradeServerObjectForRank() f3d67:%d", unique);
		MessageBox(NULL, "Error", buffer, MB_OK|MB_TOPMOST);

		return FALSE ;
	}

	cltItemInfo* pinfo = pclItemInfo[ref];
	if ( pinfo == NULL )
		return FALSE ;

	// �������� Type�� ���Ѵ�. 
	SI32 itemtype = pinfo->siType;
	cltItemTypeInfo* ptypeinfo = pclItemTypeInfo[itemtype];
	if ( ptypeinfo == NULL )
		return FALSE ;

	if ( ptypeinfo->IsAtb(ITEMATB_TRADESERVER) == FALSE )
		return FALSE ;

	if ( rank < 0 || rank >= MAX_TRADESERVER_OBJECT_RANK )
		return FALSE ;

	SI32 quality =  siTradeServerObejectRank[rank] ;
	cltItem clitem;
	clitem.Init();
	clitem.siUnique = unique ;
	clitem.siItemNum = num ;
	SI16 brareswitch = false ;

	if( MakeRandItemUnique(clitem.siUnique, &clitem , quality, 0,&brareswitch,quality) )
	{
		clitem.Element.siPower = power ;
		clitem.Element.siType = type ;
		clitem.clItemCommon.clCommonInfo.uiRareInfo = rare ;

		pclitem->Set(&clitem);
	}
	else
	{
		return FALSE ;
	}

	return TRUE ;
}
