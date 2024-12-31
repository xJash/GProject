#include "Marriage.h"

SI16 CMarriage::CalcNowLoveLevel( SI32 siNowHourVary )
{
	// �̰� ���� �߸� ������
	if ( 0 >= siNowHourVary )
	{
		return m_siLoveLevel;
	}

	if ( 0 >= m_siLimitHourVary )
	{
		return m_siLoveLevel;
	}

	// ���� �ð����� �Ϸ�(24�ð��� ���ش�)
	SI32 siDiffHour = siNowHourVary - (m_siLimitHourVary - 24);
	if ( 0 >= siDiffHour )
	{
		return m_siLoveLevel;
	}

	// �Ϸ縦 �������� ������
	SI32 siDivHour = (SI32)(siDiffHour / 24);
	if ( 0 >= siDivHour )
	{
		return m_siLoveLevel;
	}

	// ���ӽð� �Ϸ翡 2�ܰ辿 ��������
	SI16 siCalcLoveLevel = m_siLoveLevel - ( 2 * siDivHour );
	if ( 0 >= siCalcLoveLevel )
	{
		// ��ȥ�������� 1��
		if ( TRUE == IsMarried() )
		{
			siCalcLoveLevel = MARRIAGE_LOVE_LEVEL_01;
		}
		else
		{
			siCalcLoveLevel = 0;
		}
	}

	return siCalcLoveLevel;
}

BOOL CMarriage::IsWeddingAnniversary( SI32 siNowDateVary )
{
	if ( 0 >= siNowDateVary )
	{
		return FALSE;
	}

	if ( 0 >= m_siWeddingDateVary )
	{
		return FALSE;
	}

	cltDate clNowDate;
	clNowDate.MakeFullDateFromDateVary( siNowDateVary );

	cltDate clWeddingDate;
	clWeddingDate.MakeFullDateFromDateVary( m_siWeddingDateVary );

	// �켱 ��ȥ�� ���� �⵵ ���� ��ȥ ������� ����Ҽ� �ִ�
	if ( (clWeddingDate.uiYear < clNowDate.uiYear) 
		&& (clWeddingDate.uiMonth == clNowDate.uiMonth) 
		&& (clWeddingDate.uiDay == clNowDate.uiDay) )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CMarriage::IsWeddingItemGet( SI32 siNowDateVary )
{
	if ( 0 >= siNowDateVary )
	{
		return FALSE;
	}

	if ( 0 >= m_siItemGetDateVary )
	{
		return FALSE;
	}

	cltDate clNowDate;
	clNowDate.MakeFullDateFromDateVary( siNowDateVary );

	cltDate clItemGetDate;
	clItemGetDate.MakeFullDateFromDateVary( m_siItemGetDateVary );

	// �⵵,��,�� ��� ���ٸ� �̹� ���� ���̴�
	if ( (clNowDate.uiYear == clItemGetDate.uiYear)
		&& (clNowDate.uiMonth == clItemGetDate.uiMonth)
		&& (clNowDate.uiDay == clItemGetDate.uiDay) )
	{
		return TRUE;
	}

	return FALSE;
}

SI32 CMarriage::GetRemainHourVary( SI32 siNowHourVary )
{
	if ( 0 >= siNowHourVary )
	{
		return 0;
	}

	if ( 0 >= m_siLimitHourVary )
	{
		return 0;
	}

	SI32 siRemainHourVary = m_siLimitHourVary - siNowHourVary;
	if ( 0 > siRemainHourVary )
	{
		siRemainHourVary = 0;
	}

	return siRemainHourVary;

}