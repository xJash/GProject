#pragma once 

#include "../../../Lib/Directives.h"
#include "../../../../NLib/NArray.h"

#define MAX_BOOK_NUM	30

enum
{
	BOOKTYPE_BGN = 0,
	BOOKTYPE_INT,
	BOOKTYPE_ADV,
	BOOKTYPE_NUM
};

class cltBookBox
{
public:
	cltBookBox();
	~cltBookBox();

	void Init();
	void Destroy();

private:
	SI32	m_siDropRate;
	SI32	m_siPercentBGN;						// �ʱ�å�� ���� Ȯ��
	SI32	m_siPercentINT;						// �߱�å�� ���� Ȯ��
	SI32	m_siPercentADV;						// ���å�� ���� Ȯ��
#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<SI32, MAX_BOOK_NUM>, BOOKTYPE_NUM>		m_siUnique;
	NSafeTArray< NSafeTArray<SI32, MAX_BOOK_NUM>, BOOKTYPE_NUM>		m_siPercent;
#else
	SI32	m_siUnique[BOOKTYPE_NUM][MAX_BOOK_NUM];
	SI32	m_siPercent[BOOKTYPE_NUM][MAX_BOOK_NUM];
#endif

public:
	void SetFromFile();
	SI32 GetDropRate();
	SI32 GetRandBookUnique();
};