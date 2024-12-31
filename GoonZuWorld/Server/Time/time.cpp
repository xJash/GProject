#include "..\..\Client\Client.h"
#include "..\..\Server\Server.h"

#include "Char\CharManager\CharManager.h"

#include "mytime.h"
#include "..\..\Client\Music\Music.h"

extern cltCommonLogic* pclClient;

/*cyj
//------------------------------------
// cltDate
//------------------------------------
void cltDate::Set(SI32 year, SI32 month, SI32 day, SI32 hour, SI32 minute)
{
	uiYear		= year;
	uiMonth		= month;
	uiDay		= day;
	uiHour		= hour;
	uiMinute	= minute;
	uiReserved	= 0;
}

void cltDate::Set(const cltDate* pdate)
{
	memcpy(this, pdate, sizeof(cltDate));
}

SI32 cltDate::GetDateVary()
{
	SI32 vary ;
	vary = (uiDay-1) + (uiMonth-1)*30 + (uiYear*12)*30;

	return vary;
}


// �ð� ������ ���Ѵ�. 
SI32 cltDate::GetHourVary()
{
	return  GetDateVary() * 24 + uiHour;
}

// DateVary�� ������ ���� �ð� ������ �����Ѵ�. 
void cltDate::MakeFullDateFromDateVary(SI32 datevary)
{
	uiYear  = datevary / (12* 30);
	datevary %= (12* 30);

	uiMonth = datevary / 30 + 1;
	datevary %= 30;

	uiDay		= datevary + 1;
	uiHour		= 0;
	uiMinute	= 0;
}

SI32 cltDate::GetDay()
{
	return min(30, max(1, uiDay));
}

BOOL cltDate::IsLaterDayThan( cltDate* pclDate )
{

	UI32 a, b;
	a = uiYear * 10000 + uiMonth * 100 + uiDay;
	b = pclDate->uiYear * 10000 + pclDate->uiMonth * 100 + pclDate->uiDay;

	return ( a > b ); 
}

BOOL cltDate::IsLaterMonthThan( cltDate* pclDate )
{

	UI32 a, b;
	a = uiYear * 100 + uiMonth;
	b = pclDate->uiYear * 100 + pclDate->uiMonth;

	return ( a > b );
}


// ���� ���Ѵ�. 
void cltDate::AddMonth(SI32 addmonth)
{
	SI32 month = uiMonth;
	month += addmonth;

	SI32 addyear = ( month - 1 ) / 12;
	if(addyear)
	{
		uiYear += addyear;
		month  = (( month - 1 ) % 12) + 1;
	}

	uiMonth = (UI32)month;
}
	
BOOL cltDate::IncreaseTime(bool* pbdaychangedswitch, bool bforcetimeswitch)
{
	// ��¥�� ������� �ʾ����� �����Ѵ�. (����Ʈ. ) 
	*pbdaychangedswitch	= false;

	BOOL updateswitch = FALSE;

	uiMinute ++;

	if(bforcetimeswitch)
	{
		if(uiMinute >= 1)
		{
			uiMinute = 0;
			uiHour++;
			
			// ���� �ð� ���������� TRUE ����.
			if(uiHour % 2 ==0)
			{
				updateswitch = TRUE;
			}
			
			if(uiHour >= 1)
			{
				uiHour=0;
				uiDay++;
				
				// ��¥�� ����Ǿ����� �����Ѵ�. 
				*pbdaychangedswitch	= true;
				
				// ��¥�� ����Ǹ� �ݵ�� DB�� �����Ѵ�. 
				updateswitch = TRUE;
				
				if(uiDay > 30)
				{
					uiDay = 1;
					uiMonth++;
					
					if(uiMonth > 12)
					{
						uiMonth = 1;
						uiYear++;
					}
				}
			}
		}
	}
	else
	{
		
		if(uiMinute >= 60)
		{
			uiMinute = 0;
			uiHour++;
			
			// ���� �ð� ���������� TRUE ����.
			if(uiHour % 2 ==0)
			{
				updateswitch = TRUE;
			}
			
			if(uiHour >= 24)
			{
				uiHour=0;
				uiDay++;
				
				// ��¥�� ����Ǿ����� �����Ѵ�. 
				*pbdaychangedswitch	= true;
				
				// ��¥�� ����Ǹ� �ݵ�� DB�� �����Ѵ�. 
				updateswitch = TRUE;
				
				if(uiDay > 30)
				{
					uiDay = 1;
					uiMonth++;
					
					if(uiMonth > 12)
					{
						uiMonth = 1;
						uiYear++;
					}
				}
			}
		}
	}

	return updateswitch;
}

// �ð��� ���ڿ��� �����. 
BOOL cltDate::GetDateText(TCHAR* buffer)
{
	if(buffer == NULL)return FALSE;

	TCHAR* pText = GetTxtFromMgr(3808);
	wsprintf(buffer, pText, uiYear, uiMonth, uiDay, uiHour);

	return TRUE;
}

void cltDate::DiffDate( cltDate *pCurrentDate, cltDate *pOldDate )
{
	int temp;

	ZeroMemory( this, sizeof( cltDate ) );

	// minute
	temp = pCurrentDate->uiMinute - pOldDate->uiMinute;
	if( temp < 0 ) { uiMinute = 60 + temp; temp = -1; }
	else { uiMinute = temp; temp = 0; }

	// Hour
	temp += ( pCurrentDate->uiHour - pOldDate->uiHour );
	if( temp < 0 ) { uiHour = 24 + temp; temp = -1; }
	else { uiHour = temp; temp = 0; }

	// Day
	temp += ( pCurrentDate->uiDay - pOldDate->uiDay );
	if( temp < 0 ) { uiDay = 30 + temp; temp = -1; }
	else { uiDay = temp; temp = 0; }

	// Month
	temp += ( pCurrentDate->uiMonth - pOldDate->uiMonth );
	if( temp < 0 ) { uiMonth = 12 + temp; temp = -1; }
	else { uiMonth = temp; temp = 0; }

	// Year
	temp += ( pCurrentDate->uiYear - pOldDate->uiYear );
	uiYear = temp;
}

*/

//------------------------------------------
// cltTime
//------------------------------------------
cltTime::cltTime()
{
	bDayChangedSwitch	= false;
}


BOOL cltTime::Action(bool bforcetimeswitch)
{
	SI32 id;
	TCHAR buffer[256];
	BOOL rtnval = FALSE;

	// ��¥�� ����Ǿ����� �ʱ�ȭ�Ѵ�. 
	bDayChangedSwitch	= false;

	if(pclClient->GetFrame() % 40 != 0)return FALSE;

	if(clDate.IncreaseTime(&bDayChangedSwitch, bforcetimeswitch) == TRUE)
	{
		if(clDate.GetDateText(buffer) == TRUE)
		{
			pclClient->SetStatusBarText(buffer, 1);

			// Ŭ���̾�Ʈ�� ���� �ð��� ������. 
			SI32 index = 0;
			while(id = pclClient->pclCM->GetCharOrder(index))
			{
				index++;

				SI32 charunique	=	pclClient->pclCM->CR[id]->GetCharUnique();
				
				// ������� �Ŀ��Ը� �����Ѵ�. 
				if(pclClient->pclCM->CR[id]->IsValidConnection() == true)
				{
					cltMsg clMsg(GAMEMSG_RESPONSE_DATE, sizeof(cltDate), (BYTE*)(BYTE*)&clDate);
					
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					
				}

			}
		}

		rtnval = TRUE;
	}


	// �ð��� DB�� �����Ѵ�. 
	((cltServer*)pclClient)->UpdateDBTime(&clDate);


	return rtnval;
}
