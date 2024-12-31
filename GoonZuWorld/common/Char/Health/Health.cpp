//---------------------------------
// 2003/9/27 ���°�
//---------------------------------
#include "CommonLogic.h"
#include "Health.h"

#include "Char/CharManager/CharManager.h"
#include "Char/CharCommon/Char-Common.h"
#include "Skill/Skill-Manager.h"

extern cltCommonLogic* pclClient;

//---------------------------------------------------------------
// �ǰ� 
//----------------------------------------------------------------
cltHealth::cltHealth()
{
	pclInfo = NULL;
}

SI32 cltHealth::GetBasic(SI32 level)
{
	return  min(100, max(30, level));
}

SI32 cltHealth::GetHungryMaxLimit(SI32 level)
{
	SI32 basic = GetBasic(level);

	return basic * 2;
}

// ����� ����� ã�´�. 
SI32 cltHealth::GetHungryStatus(SI32 level)
{
	SI32 basic	= GetBasic(level);
	SI32 status = 0;

	SI32 interval1 = (300 - basic) / 3;

	
	if(pclInfo->siHungry  > basic  + (interval1 * 2))	
	{
		status |= HEALTH_STATUS_HUNGRY_1;
	}
	else if(pclInfo->siHungry  > basic  + (interval1 * 1))	
	{
		status |= HEALTH_STATUS_HUNGRY_2;
	}
	else if(pclInfo->siHungry  > basic  + (interval1 * 0))	
	{
		status |= HEALTH_STATUS_HUNGRY_3;
	}
	else if(pclInfo->siHungry  >= -basic)
	{
		status |= HEALTH_STATUS_HUNGRY_NORMAL;

		SI32 interval2 = (basic * 2) / 6;
		if(pclInfo->siHungry >  interval2)
		{
			status |= HEALTH_STATUS_HUNGRY_4;
		}
		else if(pclInfo->siHungry >  -interval2)
		{
			status |= HEALTH_STATUS_HUNGRY_5;
		}
		else
		{
			status |= HEALTH_STATUS_HUNGRY_6;
		}

	}
	else if(pclInfo->siHungry  >= -basic - interval1)
	{
		status |= HEALTH_STATUS_HUNGRY_7;
	}
	else if(pclInfo->siHungry  >= -basic - (interval1 * 2))
	{
		status |= HEALTH_STATUS_HUNGRY_8;
	}
	else 
	{
		status |= HEALTH_STATUS_HUNGRY_9;
	}


	return status;

}


bool cltHealth::Action(SI32 level, DWORD currentclock)
{

	SI32 penalty = 0;
	bool rtnval = false;
	cltDiseaseInfo* pcldisease ;

	if(TABS(currentclock - ActionClock) < HEALTH_ACTION_DELAY)return false;
	ActionClock	= currentclock;

	SI32 diff = 0;


	//---------------------------------------------------
	// ���� ��� ����. 
	//---------------------------------------------------
	
	// ��ȭ ���. 

	// �谡 �ʹ� �θ� ���� 
	diff = pclInfo->siHungry;

	// ����� ���¿� ������ ���ٸ�, 
	if(level >= FATHER_LEVEL && GetHungryStatus(level) != HEALTH_STATUS_HUNGRY_NORMAL && TABS(diff) > (rand() % GetHungryMaxLimit(level)) )
	{
		// ��ȭ�迡 �̻� ��ȣ�� ������. 
		SI32 max = MAXORG(level);
		if(pclInfo->siInnerOrg1 > -max)
		{
			pclInfo->siInnerOrg1--;
		}
		rtnval	= true;
		
	}
	else
	{
		// ������ ���� ���¿��� ��ȭ�谡 ������ ã�� �� �ִ�. 
		if(pclInfo->siInnerOrg1 < 0 && pclInfo->uiOrg1Disease == 0)
		{
			pclInfo->siInnerOrg1+=2;		// ��ȭ�谡 ������ ã�´�. 
			if(pclInfo->siInnerOrg1 > 0)pclInfo->siInnerOrg1 = 0;

			rtnval	= true;
		}
	}
	
	// ��ȯ ��� 
	// ������ ���� ���¿��� ��ȭ�谡 ������ ã�� �� �ִ�. 
	if(pclInfo->siInnerOrg2 < 0 && pclInfo->uiOrg2Disease == 0)
	{
		pclInfo->siInnerOrg2++;		// ��ȯ�谡 ������ ã�´�. 
		rtnval	= true;
	}

	// ȣ�� ��� 
	// ������ ���� ���¿��� ȣ��谡 ������ ã�� �� �ִ�. 
	if(pclInfo->siInnerOrg3 < 0 && pclInfo->uiOrg3Disease == 0)
	{
		pclInfo->siInnerOrg3++;	
		rtnval	= true;
	}

	// �Ű� ��� 
	// ������ ���� ���¿��� �Ű�谡 ������ ã�� �� �ִ�. 
	if(pclInfo->siInnerOrg4 < 0 && pclInfo->uiOrg4Disease == 0)
	{
		pclInfo->siInnerOrg4++;		// ��ȯ�谡 ������ ã�´�. 
		rtnval	= true;
	}

	//----------------------------------------------------
	// ���� ������ ����ڵ��� �ǰ��� ������ ���� �ʴ´�. 
	//---------------------------------------------------
	if( pclClient->IsCountrySwitch( Switch_Health ) )
	{
		if(level < INIT_LEVEL_SECOND )
			return rtnval;
	}
	else
	{
		if(level < FATHER_LEVEL )
			return rtnval;
	}


	//----------------------------------------------
	// ������ �ɸ��� �Ѵ�. 
	//----------------------------------------------
	// ��ȭ���� ���¸� �����Ѵ�. 
	// ������ �ɸ���. 
	if(pclInfo->siInnerOrg1 < -30)
	{
		if(rand() % (1000 + pclInfo->uiOrg1Disease * 30)  < (-pclInfo->siInnerOrg1))
		{
			if(pclInfo->uiOrg1Disease < min(level/2, 50))
			{
				pclInfo->uiOrg1Disease++;
				rtnval	= true;
			}
		}
	}

	// ��ȯ���� ���¸� �����Ѵ�. 
	// ������ �ɸ���. 
	if(pclInfo->siInnerOrg2 < -30)
	{
		if(rand() % (500 + pclInfo->uiOrg2Disease * 20)  < (-pclInfo->siInnerOrg2))
		{
			if(pclInfo->uiOrg2Disease < min(level/2, 50))
			{
				pclInfo->uiOrg2Disease++;
				rtnval	= true;
			}
		}
	}

	// ȣ����� ���¸� �����Ѵ�. 
	// ������ �ɸ���. 
	if(pclInfo->siInnerOrg3 < -30)
	{
		if(rand() % (500 + pclInfo->uiOrg3Disease * 20)  < (-pclInfo->siInnerOrg3))
		{
			if(pclInfo->uiOrg3Disease < min(level/2, 50))
			{
				pclInfo->uiOrg3Disease++;
				rtnval	= true;
			}
		}
	}

	// �Ű���� ���¸� �����Ѵ�. 
	// ������ �ɸ���. 
	if(pclInfo->siInnerOrg4 < -30)
	{
		if(rand() % (500 + pclInfo->uiOrg4Disease * 20)  < (-pclInfo->siInnerOrg4))
		{
			if(pclInfo->uiOrg4Disease < min(level/2, 50))
			{
				pclInfo->uiOrg4Disease++;
				rtnval	= true;
			}
		}
	}



	//------------------------------------------------
	// �������� óġ. 
	//------------------------------------------------

	// ��ȭ�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_1, pclInfo->uiOrg1Disease);
	if(pcldisease)
	{
		penalty += pcldisease->siPenalty;
	}

	// ��ȯ�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_2, pclInfo->uiOrg2Disease);
	if(pcldisease)
	{
		penalty += pcldisease->siPenalty;
	}

	// ȣ��� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_3, pclInfo->uiOrg3Disease);
	if(pcldisease)
	{
		penalty += pcldisease->siPenalty;
	}

	// �Ű�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_4, pclInfo->uiOrg4Disease);
	if(pcldisease)
	{
		penalty += pcldisease->siPenalty;
	}
	
	// ���Ƽ�� �ִ� ������ �����Ѵ�. 
	if(penalty)
	{
		penalty = min(50, penalty);
	}
	


	//  ������ ������, 
	if(penalty)
	{
		// �ǰ��� ������ ���Ƽ��ŭ �ٿ��ش�. 
		SI32 limit = 100 - penalty;
		if(pclInfo->uiHealthPoint > limit)
		{
			pclInfo->uiHealthPoint--;
			rtnval = true;
		}
	}
	// ������ ���µ� �ǰ��� ������ ������ �ǰ��� 100���� �÷��ش�. 
	else if(pclInfo->uiHealthPoint < 100)
	{
		pclInfo->uiHealthPoint++;
		rtnval = true;
	}
	// ������ ���� �ǰ��� ���� �̻��̸�, 
	else
	{
		// ��Ȥ �ǰ��� �����ش�. 
		if(rand() % 10 == 0)
		{
			if(pclInfo->siInnerOrg1 >= 0 && pclInfo->siInnerOrg2 >= 0
			&& pclInfo->siInnerOrg3 >= 0 && pclInfo->siInnerOrg4 >= 0)	// ���� ����� �����̾�� �Ѵ�. 		
			{
				if(pclInfo->uiHealthPoint < 110)	// �ִ� �ǰ� ��ġ�� �ѱ� ���� ����. 
				{
					pclInfo->uiHealthPoint ++;
					rtnval = true;
				}
			}
		}
	}



	return rtnval;

}

// �ǰ� ���¸� �м��ؼ� �� ����� �����ش�. 
SI32 cltHealth::AnalyzeHealth(SI32 level)
{
	SI32 status = 0;
	SI32 diff = 0 ;

	// �谡 ���� ������ ���Ѵ�. 
	status = GetHungryStatus(level);

	// ��ȭ���� �̻� ������ ���Ѵ�.
	if(pclInfo->siInnerOrg1 < -80)
	{
		status |= HEALTH_STATUS_ORG1_SERIOUS;
	}
	else if(pclInfo->siInnerOrg1 < -50)
	{
		status |= HEALTH_STATUS_ORG1_BAD;
	}
	else if(pclInfo->siInnerOrg1 < -20)
	{
		status |= HEALTH_STATUS_ORG1_NORMAL;
	}
	else 
	{
		status |= HEALTH_STATUS_ORG1_GOOD;
	}

	// ��ȯ����  �̻� ������ ���Ѵ�.
	if(pclInfo->siInnerOrg2 < -80)
	{
		status |= HEALTH_STATUS_ORG2_SERIOUS;
	}
	else if(pclInfo->siInnerOrg2 < -50)
	{
		status |= HEALTH_STATUS_ORG2_BAD;
	}
	else if(pclInfo->siInnerOrg2 < -20)
	{
		status |= HEALTH_STATUS_ORG2_NORMAL;
	}
	else 
	{
		status |= HEALTH_STATUS_ORG2_GOOD;
	}

	// ȣ�����  �̻� ������ ���Ѵ�.
	if(pclInfo->siInnerOrg3 < -80)
	{
		status |= HEALTH_STATUS_ORG3_SERIOUS;
	}
	else if(pclInfo->siInnerOrg3 < -50)
	{
		status |= HEALTH_STATUS_ORG3_BAD;
	}
	else if(pclInfo->siInnerOrg3 < -20)
	{
		status |= HEALTH_STATUS_ORG3_NORMAL;
	}
	else 
	{
		status |= HEALTH_STATUS_ORG3_GOOD;
	}

	// �Ű����  �̻� ������ ���Ѵ�.
	if(pclInfo->siInnerOrg2 < -80)
	{
		status |= HEALTH_STATUS_ORG4_SERIOUS;
	}
	else if(pclInfo->siInnerOrg4 < -50)
	{
		status |= HEALTH_STATUS_ORG4_BAD;
	}
	else if(pclInfo->siInnerOrg4 < -20)
	{
		status |= HEALTH_STATUS_ORG4_NORMAL;
	}
	else 
	{
		status |= HEALTH_STATUS_ORG4_GOOD;
	}

	return status;
}

// ������ �ǰ� ���¿� ���� Text�� ���Ѵ�.
bool cltHealth::GetHealthText(SI32 level, TCHAR* text, SI16 txtSize)
{
	cltCharCommon* pclchar = pclClient->pclCM->GetChar( 1 );
	if ( NULL == pclchar )
	{
		return false;
	}

	TCHAR buffer[2048] =TEXT("");
	TCHAR temp[1024];

	SI32 status = AnalyzeHealth(level);
	SI32 max	= min(100, MAXORG(level));

	// ����. 
	SI32 healthpoint = pclInfo->uiHealthPoint;


	bool bhungryshowswitch = false;
	if(status & (HEALTH_STATUS_HUNGRY_1 | HEALTH_STATUS_HUNGRY_2))
	{
		TCHAR* pText = GetTxtFromMgr(532);
		StringCchPrintf(temp, 1024, pText);
		StringCchCat(temp, 1024, "\r\n");
		StringCchCat(buffer, 2048, temp);
		bhungryshowswitch = true;
	}
	if(status & HEALTH_STATUS_HUNGRY_3)
	{
		TCHAR* pText = GetTxtFromMgr(533);
		StringCchPrintf(temp, 1024, pText);
		StringCchCat(temp, 1024, "\r\n");
		StringCchCat(buffer, 2048, temp);
		bhungryshowswitch = true;
	}
	if(status & HEALTH_STATUS_HUNGRY_NORMAL)
	{
		TCHAR* pText = GetTxtFromMgr(534);
		StringCchPrintf(temp, 1024, pText);
		StringCchCat(temp, 1024, "\r\n");
		StringCchCat(buffer, 2048, temp);
		bhungryshowswitch = true;
	}
	if(status & HEALTH_STATUS_HUNGRY_7)
	{
		TCHAR* pText = GetTxtFromMgr(535);
		StringCchPrintf(temp, 1024, pText);
		StringCchCat(temp, 1024, "\r\n");
		StringCchCat(buffer, 2048, temp);
		bhungryshowswitch = true;
	}
	if(status & (HEALTH_STATUS_HUNGRY_8 | HEALTH_STATUS_HUNGRY_9))
	{
		TCHAR* pText = GetTxtFromMgr(536);
		StringCchPrintf(temp, 1024, pText);
		StringCchCat(temp, 1024, "\r\n");
		StringCchCat(buffer, 2048, temp);
		bhungryshowswitch = true;
	}

	if(bhungryshowswitch)
	{
		TCHAR* pText = GetTxtFromMgr(537);
		StringCchPrintf(temp, 1024, pText, pclInfo->siHungry, -GetBasic(level), GetBasic(level));
		StringCchCat(buffer, 2048, temp);
	}

	// ��ȭ�� ������ �����Ѵ�. 
	cltDiseaseInfo* pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_1, pclInfo->uiOrg1Disease);
	if(pcldisease)
	{
		TCHAR* pText = GetTxtFromMgr(538);
		StringCchPrintf(temp, 1024, pText, pcldisease->szName, pclInfo->uiOrg1Disease - pcldisease->siLevel + 1);
		StringCchCat(buffer, 2048, temp);
	}
	// ��ȭ���� �������� ���¸� �˷��ش�. 
	else
	{
		if(status & HEALTH_STATUS_ORG1_SERIOUS)
		{
			TCHAR* pText = GetTxtFromMgr(539);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg1, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG1_BAD)
		{
			TCHAR* pText = GetTxtFromMgr(540);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg1, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG1_NORMAL)
		{
			TCHAR* pText = GetTxtFromMgr(541);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg1, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG1_GOOD)
		{
			TCHAR* pText = GetTxtFromMgr(542);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg1, max);
			StringCchCat(buffer, 2048, temp);
		}
	}

	// ��ȯ�� ������ �����Ѵ�. 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_2, pclInfo->uiOrg2Disease);
	if(pcldisease)
	{
		TCHAR* pText = GetTxtFromMgr(538);
		StringCchPrintf(temp, 1024, pText, pcldisease->szName, pclInfo->uiOrg2Disease - pcldisease->siLevel + 1);
		StringCchCat(buffer, 2048, temp);
	}
	// �������� ���¸� �˷��ش�. 
	else
	{
		if(status & HEALTH_STATUS_ORG2_SERIOUS)
		{
			TCHAR* pText = GetTxtFromMgr(543);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg2, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG2_BAD)
		{
			TCHAR* pText = GetTxtFromMgr(544);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg2, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG2_NORMAL)
		{
			TCHAR* pText = GetTxtFromMgr(545);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg2, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG2_GOOD)
		{
			TCHAR* pText = GetTxtFromMgr(546);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg2, max);
			StringCchCat(buffer, 2048, temp);
		}

	}

	// ȣ��� ������ �����Ѵ�. 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_3, pclInfo->uiOrg3Disease);
	if(pcldisease)
	{
		TCHAR* pText = GetTxtFromMgr(538);
		StringCchPrintf(temp, 1024, pText, pcldisease->szName, pclInfo->uiOrg3Disease - pcldisease->siLevel + 1);
		StringCchCat(buffer, 2048, temp);
	}
	// �������� ���¸� �˷��ش�. 
	else
	{
		if(status & HEALTH_STATUS_ORG3_SERIOUS)
		{
			TCHAR* pText = GetTxtFromMgr(547);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg3, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG3_BAD)
		{
			TCHAR* pText = GetTxtFromMgr(548);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg3, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG3_NORMAL)
		{
			TCHAR* pText = GetTxtFromMgr(549);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg3, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG3_GOOD)
		{
			TCHAR* pText = GetTxtFromMgr(550);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg3, max);
			StringCchCat(buffer, 2048, temp);
		}

	}

	// �Ű�� ������ �����Ѵ�. 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_4, pclInfo->uiOrg4Disease);
	if(pcldisease)
	{
		TCHAR* pText = GetTxtFromMgr(538);
		StringCchPrintf(temp, 1024, pText, pcldisease->szName, pclInfo->uiOrg4Disease - pcldisease->siLevel + 1);
		StringCchCat(buffer, 2048, temp);
	}
	// �������� ���¸� �˷��ش�. 
	else
	{
		if(status & HEALTH_STATUS_ORG4_SERIOUS)
		{
			TCHAR* pText = GetTxtFromMgr(551);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg4, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG4_BAD)
		{
			TCHAR* pText = GetTxtFromMgr(552);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg4, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG4_NORMAL)
		{
			TCHAR* pText = GetTxtFromMgr(553);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg4, max);
			StringCchCat(buffer, 2048, temp);
		}
		if(status & HEALTH_STATUS_ORG4_GOOD)
		{
			TCHAR* pText = GetTxtFromMgr(554);
			StringCchPrintf(temp, 1024, pText, pclInfo->siInnerOrg4, max);
			StringCchCat(buffer, 2048, temp);
		}

	}

												
	if(pclClient->IsCountrySwitch(Switch_PeriodItem) == false)				//	������ �ڵ�� Switch_PeriodItem�� false�� ��쿡��  ����Ǿ�� �Ѵ�.
	{											//	Switch_PeriodItem�� true�� ���� perioditemlistdlgŬ�������� ���� �ڵ屸���� ���� �Ǿ��ִ�.
		TCHAR warpbuf[2048] = TEXT("") ;
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bUseNoLimitTicketWarp )
		{
			//���� ���� �Ⱓ ǥ��.
			
			cltDate MaxWarpDate;//���� Ƽ�� ���� �ִ� ����
			MaxWarpDate.uiYear = 255;
			MaxWarpDate.uiMonth = 12;
			MaxWarpDate.uiDay = 30;
			SI32 MAX_GAME_DATE = MaxWarpDate.GetDateVary();
			SI32 warpdate = pclClient->pclCM->CR[1]->pclCI->clBI.siNoLimitTicketWarpDateVary;//���� �������� ���� 
			if (warpdate >=MAX_GAME_DATE) {
				TCHAR* timebuf= GetTxtFromMgr(7866);
				TCHAR* pText = GetTxtFromMgr(3187);
				StringCchPrintf(warpbuf, 2048, pText,timebuf);
				StringCchCat(buffer, 2048, warpbuf);


			}
			else{
				TCHAR timebuf[512] = TEXT("") ;
				cltDate cldate ;
				cldate.MakeFullDateFromDateVary(pclClient->pclCM->CR[1]->pclCI->clBI.siNoLimitTicketWarpDateVary);
				if ( cldate.GetDateText(timebuf) )
				{
					TCHAR* pText = GetTxtFromMgr(3187);
					StringCchPrintf(warpbuf, 2048, pText,timebuf);
				}
				StringCchCat(buffer, 2048, warpbuf);
				StringCchCopy(text, txtSize, buffer);
				StringCchCopy(buffer, txtSize, text);
			}
		}
		//����ġ 150%���� �Ⱓǥ��
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_PREMIUMEXPUP)){
			
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_PREMIUMEXPUP);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			/*cldate.MakeFullDateFromDateVary( BuffMinute );*/
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(7937);
				StringCchPrintf(warpbuf, 2048, pText,timebuf);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else{
			StringCchCopy(text, txtSize, buffer);
		}
		//����ġ 200%���� �Ⱓǥ��
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_SUPEREXPUP))
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_SUPEREXPUP);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(7938);
				StringCchPrintf(warpbuf, 2048, pText,timebuf);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		//����ġ 300%���� �Ⱓǥ��(����� ����)
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_SPECIALAMPUL_EXPUP300))
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_SPECIALAMPUL_EXPUP300);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(9888);
				StringCchPrintf(warpbuf, 2048, pText, timebuf);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		// ���� EXP ĸ��
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_RESIDENTS_EXPUP_10 ) )
		{
			TCHAR timebuf[512] = TEXT("");
			cltDate cldate;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime( BUF_RESIDENTS_EXPUP_10 );
			cldate.MakeFullHourFromHourVary( BuffMinute );
			if (cldate.GetDateText( timebuf ) )
			{
				TCHAR* pText = GetTxtFromMgr( 40827 );
				StringCchPrintf( warpbuf, 2048, pText, timebuf );
			}
			StringCchCat( buffer, 2048, warpbuf );
			StringCchCopy( text, txtSize, buffer );
			StringCchCopy( buffer, txtSize, text );
		}
		else
		{
			StringCchCopy( text, txtSize, buffer );
		}

		// ���� ��ȭ��
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_RESIDENTS_STRONG ) )
		{
			TCHAR timebuf[512] = TEXT("");
			cltDate cldate;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime( BUF_RESIDENTS_STRONG );
			cldate.MakeFullHourFromHourVary( BuffMinute );
			if (cldate.GetDateText( timebuf ) )
			{
				TCHAR* pText = GetTxtFromMgr( 40828 );
				StringCchPrintf( warpbuf, 2048, pText, timebuf );
			}
			StringCchCat( buffer, 2048, warpbuf );
			StringCchCopy( text, txtSize, buffer );
			StringCchCopy( buffer, txtSize, text );
		}
		else
		{
			StringCchCopy( text, txtSize, buffer );
		}

		//ä�� ���� ������
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FARMINGNMININGFOREVER)){

			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_FARMINGNMININGFOREVER);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(7962);
				StringCchPrintf(warpbuf, 2048, pText,timebuf);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}
		//��������.
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bSpaceBoxPremiumService)
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary(pclClient->pclCM->CR[1]->pclCI->clBI.siSpaceBoxPremiumServiceDate);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(7913);
				StringCchPrintf(warpbuf, 2048, pText,timebuf);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}
		
		//[����] ���� ���� ������ ���� �ð�ǥ�� => 2008-6-19 
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_STR))
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_STATUE_UP_STR);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(8468);
				StringCchPrintf(warpbuf, 2048, pText,
								timebuf, 
								pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_STR)->siPercent);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		//[����] ���� ���� ������ ���� �ð�ǥ�� => 2008-6-19 
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_DEX))
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_STATUE_UP_DEX);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(8469);
				StringCchPrintf(warpbuf, 2048, pText,
								timebuf, 
								pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_DEX)->siPercent);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}


		//[����] ���� ���� ������ ���� �ð�ǥ�� => 2008-6-19 
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_MAG))
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_STATUE_UP_MAG);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(8470);
				StringCchPrintf(warpbuf, 2048, pText,
								timebuf, 
								pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_MAG)->siPercent);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		//[����] ���� ���� ������ ���� �ð�ǥ�� => 2009-10-23 
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_WIS))
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_STATUE_UP_WIS);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(40327);
				StringCchPrintf(warpbuf, 2048, pText,
					timebuf, 
					pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_WIS)->siPercent);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}


		//[����] ���� ���� ������ ���� �ð�ǥ�� => 2008-6-19 
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_VIT))
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_STATUE_UP_VIT);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(8471);
				StringCchPrintf(warpbuf, 2048, pText,
								timebuf, 
								pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_VIT)->siPercent);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}


		//[����] ���� ���� ������ ���� �ð�ǥ�� => 2008-6-19 
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_HAND))
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_STATUE_UP_HAND);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(8472);
				StringCchPrintf(warpbuf, 2048, pText,
								timebuf, 
								pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_HAND)->siPercent);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}
		//[����] ���� ���� ������ ���� �ð�ǥ�� => 2008-6-19 
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_EXP_UP))
		{ 
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_EXP_UP);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(8542);  
				StringCchPrintf(warpbuf, 2048, pText,
					timebuf, 
					pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBuf(BUF_EXP_UP)->siPercent+100);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}


		TCHAR premiumbuf[2048] = TEXT("") ;

		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bPremiumService )
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary(pclClient->pclCM->CR[1]->pclCI->clBI.siPremiumServiceDate);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(5606);
				StringCchPrintf(premiumbuf, 2048, pText,timebuf);
			}

		
			StringCchCat(buffer, 2048, premiumbuf);
			StringCchCopy(text,txtSize, buffer);
			StringCchCopy(buffer, 2048, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		TCHAR combatbuf[2048] = TEXT("") ;	
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bCombatService )
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary(pclClient->pclCM->CR[1]->pclCI->clBI.siCombatServiceDate);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(5620);
				StringCchPrintf(combatbuf, 2048, pText,timebuf);
			}       
			StringCchCat(buffer, 2048, combatbuf);
			StringCchCopy(text, txtSize, buffer);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		TCHAR MakeItembuf[2048] = TEXT("") ;	
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bMakeItemService )
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary(pclClient->pclCM->CR[1]->pclCI->clBI.siMakeItemServiceDate);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(6130);
				StringCchPrintf(MakeItembuf, 2048, pText,timebuf);
			}

			StringCchCat(buffer, 2048, MakeItembuf);
			StringCchCopy(text,txtSize, buffer);
			StringCchCopy(buffer, 2048, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		TCHAR Bulletbuf[2048] = TEXT("") ;	
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bBulletService )
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary(pclClient->pclCM->CR[1]->pclCI->clBI.siBulletServiceDate);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(6275);
				StringCchPrintf(Bulletbuf, 2048, pText,timebuf);
			}

			StringCchCat(buffer, 2048, Bulletbuf);
			StringCchCopy(text,txtSize, buffer);
			StringCchCopy(buffer, 2048, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		TCHAR SummonStaminabuf[2048] = TEXT("") ;	
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bSummonStaminaService )
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary(pclClient->pclCM->CR[1]->pclCI->clBI.siSummonStaminaServiceDate);
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(6440);
				StringCchPrintf(SummonStaminabuf, 2048, pText,timebuf);
			}

			StringCchCat(buffer, 2048, SummonStaminabuf);
			StringCchCopy(text,txtSize, buffer);
			StringCchCopy(buffer, 2048, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		TCHAR marketPremiumBuf[2048] = TEXT("") ;	
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bMarKetPremiumService )
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary( pclClient->pclCM->CR[1]->pclCI->clBI.siMarKetPremiumServiceDate );
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(10169);
				StringCchPrintf(marketPremiumBuf, 2048, pText,timebuf);
			}

			StringCchCat(buffer, 2048, marketPremiumBuf);
			StringCchCopy(text,txtSize, buffer);
			StringCchCopy(buffer, 2048, text);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		//[����] ���ս��� �����̾� ���� ���̱�.
		TCHAR NewMarketPremiumBuf[2048] = TEXT("") ;	
		if ( pclClient->pclCM->CR[1]->pclCI->clBI.bNewMarketPremiumService )
		{
			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			cldate.MakeFullDateFromDateVary( pclClient->pclCM->CR[1]->pclCI->clBI.siNewMarketPremiumServiceDate );
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = "[%s]����  ���ս��� �����̾��� ��� ���Դϴ�.";//GetTxtFromMgr(10169);
				StringCchPrintf(NewMarketPremiumBuf, 2048, pText,timebuf);
			}

			StringCchCat(  buffer, sizeof(buffer),	NewMarketPremiumBuf	);
			StringCchCopy( text,   txtSize,			buffer					);
			StringCchCopy( buffer, sizeof(buffer),	text					);
		}
		else
		{
			StringCchCopy(text, txtSize, buffer);
		}

		//	�޴� �ð�ǥ��
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_OLYMPICMEDAL)){

			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_OLYMPICMEDAL);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			if ( cldate.GetDateText(timebuf) )
			{
				SI16 bufpersent = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufPercent( BUF_OLYMPICMEDAL ) ;
				if (bufpersent == 20) {
					TCHAR* pText = GetTxtFromMgr(8648); // �ݸ޴�
					StringCchPrintf(warpbuf, 2048, pText,timebuf);
				}
				else if (bufpersent == 10) {
					TCHAR* pText = GetTxtFromMgr(8649); //���޴�
					StringCchPrintf(warpbuf, 2048, pText,timebuf);
				}
				else if (bufpersent == 5) {
					TCHAR* pText = GetTxtFromMgr(8650); //���޴�
					StringCchPrintf(warpbuf, 2048, pText,timebuf);
				}
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else{
			StringCchCopy(text, txtSize, buffer);
		}

		// PCK : ���� �����̾� �Ⱓ ǥ��
		if (pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_PREMIUMMAKEEXPUP)){

			TCHAR timebuf[512] = TEXT("") ;
			cltDate cldate ;
			SI32 BuffMinute = pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufOvertime(BUF_PREMIUMMAKEEXPUP);
			cldate.MakeFullHourFromHourVary(BuffMinute);
			/*cldate.MakeFullDateFromDateVary( BuffMinute );*/
			if ( cldate.GetDateText(timebuf) )
			{
				TCHAR* pText = GetTxtFromMgr(9554);
				StringCchPrintf(warpbuf, 2048, pText,timebuf);
			}
			StringCchCat(buffer, 2048, warpbuf);
			StringCchCopy(text, txtSize, buffer);
			StringCchCopy(buffer, txtSize, text);
		}
		else{
			StringCchCopy(text, txtSize, buffer);
		}
	}
	else
	{
		StringCchCopy(text, txtSize, buffer);
	}


	// ������� ���� - ���� ǥ��
	if ( (PERSONITEM_WEAPON1 == pclchar->ActiveWeapon) || (PERSONITEM_WEAPON2 == pclchar->ActiveWeapon) )
	{
		TCHAR szEmblemText[512] = TEXT("");

		SI32 siItemType		= pclchar->pclCI->clCharItem.GetWeaponType( pclClient->pclItemManager, pclchar->ActiveWeapon );
		SI32 siSkillUnique	= pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel = pclchar->pclCI->clCharSkill.GetSkillExpLevel( siSkillUnique );

			if ( pclClient->pclSkillManager->m_clMasterManager.GetEmblemExplain(siItemType, siSkillLevel, szEmblemText, sizeof(szEmblemText)) )
			{
				StringCchCat(buffer, 2048, szEmblemText);
				StringCchCopy(text, txtSize, buffer);
				StringCchCopy(buffer, txtSize, text);
			}
		}
	}
	else
	{
		StringCchCopy(text, txtSize, buffer);
	}


	return true;
}


// ���� ������ �ִ� ������ ������ �˷��ش�. 
bool cltHealth::GetCurDisease(cltCurDisease* pclcurdisease)
{

	bool rtnval = false;
	cltDiseaseInfo* pcldisease ;

	// ��ȭ�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_1, pclInfo->uiOrg1Disease);
	if(pcldisease)
	{
		pclcurdisease->siOrg1Unique = pcldisease->siUnique;
		rtnval = true;
	}

	// ��ȯ�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_2, pclInfo->uiOrg2Disease);
	if(pcldisease)
	{
		pclcurdisease->siOrg2Unique = pcldisease->siUnique;
		rtnval = true;
	}

	// ȣ��� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_3, pclInfo->uiOrg3Disease);
	if(pcldisease)
	{
		pclcurdisease->siOrg3Unique = pcldisease->siUnique;
		rtnval = true;
	}

	// �Ű�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_4, pclInfo->uiOrg4Disease);
	if(pcldisease)
	{
		pclcurdisease->siOrg4Unique = pcldisease->siUnique;
		rtnval = true;
	}

	return rtnval;

}

// ���� ������ �̸��� ���Ѵ�. 
bool cltHealth::GetCurDiseaseName(TCHAR* pname, SI16 txtSize)
{
	cltCurDisease cldisease;

	// ���� ���� �ִ� ������ ���¸� ���Ѵ�. 
	if(GetCurDisease(&cldisease) == false)
	{
		return false;
	}

	SI32 diseaseunique = 0;

	if(cldisease.siOrg1Unique)
	{
		diseaseunique = cldisease.siOrg1Unique;
	}
	else if(cldisease.siOrg2Unique)
	{
		diseaseunique = cldisease.siOrg2Unique;
	}
	else if(cldisease.siOrg3Unique)
	{
		diseaseunique = cldisease.siOrg3Unique;
	}
	else if(cldisease.siOrg4Unique)
	{
		diseaseunique = cldisease.siOrg4Unique;
	}

	if(diseaseunique == 0)return false;

	if(pclClient->pclDiseaseManager->GetNameFromdUnique(diseaseunique, pname, txtSize) == true)
	{
		return true;
	}

	return false;
}



// ������ ġ���Ѵ�. 
bool cltHealth::CureDisease(SI32 diseaseunique)
{

	cltDiseaseInfo* pcldisease ;

	// ��ȭ�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_1, pclInfo->uiOrg1Disease);
	if(pcldisease)
	{
		if(pcldisease->siUnique == diseaseunique)
		{
			pclInfo->uiOrg1Disease--;

			// ��ȭ����� �ټ� ȸ����Ų��. 
			if(pclInfo->siInnerOrg1 < 10)
			{
				pclInfo->siInnerOrg1 += 10;
			}

			// ġ�� ��� ������ �������ٸ� Disease�� 0���� �����ؾ� �Ѵ�. 
			pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_1, pclInfo->uiOrg1Disease);
			if(pcldisease == NULL)
			{
				pclInfo->uiOrg1Disease = 0;
			}

			return true;
		}
	}

	// ��ȯ�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_2, pclInfo->uiOrg2Disease);
	if(pcldisease)
	{
		if(pcldisease->siUnique == diseaseunique)
		{
			pclInfo->uiOrg2Disease--;

			// ����� �ټ� ȸ����Ų��. 
			if(pclInfo->siInnerOrg2 < 10)
			{
				pclInfo->siInnerOrg2 += 10;
			}


			// ġ�� ��� ������ �������ٸ� Disease�� 0���� �����ؾ� �Ѵ�. 
			pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_2, pclInfo->uiOrg2Disease);
			if(pcldisease == NULL)
			{
				pclInfo->uiOrg2Disease = 0;
			}

			return true;
		}
	}

	// ȣ��� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_3, pclInfo->uiOrg3Disease);
	if(pcldisease)
	{
		if(pcldisease->siUnique == diseaseunique)
		{
			pclInfo->uiOrg3Disease--;

			// ����� �ټ� ȸ����Ų��. 
			if(pclInfo->siInnerOrg2 < 10)
			{
				pclInfo->siInnerOrg2 += 10;
			}

			// ġ�� ��� ������ �������ٸ� Disease�� 0���� �����ؾ� �Ѵ�. 
			pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_3, pclInfo->uiOrg3Disease);
			if(pcldisease == NULL)
			{
				pclInfo->uiOrg3Disease = 0;
			}

			return true;
		}
	}

	// �Ű�� ����, 
	pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_4, pclInfo->uiOrg4Disease);
	if(pcldisease)
	{
		if(pcldisease->siUnique == diseaseunique)
		{
			pclInfo->uiOrg4Disease--;

			// ����� �ټ� ȸ����Ų��. 
			if(pclInfo->siInnerOrg2 < 10)
			{
				pclInfo->siInnerOrg2 += 10;
			}

			// ġ�� ��� ������ �������ٸ� Disease�� 0���� �����ؾ� �Ѵ�. 
			pcldisease = pclClient->pclDiseaseManager->FindDisease(ORG_4, pclInfo->uiOrg4Disease);
			if(pcldisease == NULL)
			{
				pclInfo->uiOrg4Disease = 0;
			}

			return true;
		}
	}

	return false;

}



