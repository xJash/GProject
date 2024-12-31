#ifndef _FourleafMANAGER_H_
#define _FourleafMANAGER_H_

#include <Directives.h>
#include "CommonLogic.h"

#define Fourleaf_MAX_LIST	10
#define MAX_UNIQUENUM	20	//m_100healmanager.txt �� �� �ִ� ����ũ ����

struct stFourleafProduct
{
	SI32 ItemUnique;
	SI32 ItemNum;

	stFourleafProduct()
	{
		Init();
	}

	void Init()
	{
		memset(this, 0, sizeof(stFourleafProduct));
	}

	void Set( stFourleafProduct * src )
	{
		memcpy(this,src, sizeof(stFourleafProduct));
	}
	bool IsSame( stFourleafProduct * src )
	{
		if( ItemUnique == src->ItemUnique && ItemNum == src->ItemNum )
		{
			return true;
		}

		return false;
	}

};

class CFourLeafManager
{
public:

	CFourLeafManager();
	~CFourLeafManager();

	void Init();

	//����Ŭ�ι��� 2�� �����ۼ��������� �ȵǾ� �ϴ� ���� ������ ����� ��� �´�..
	bool LoadFourleafProductDataFromTxt();

#ifdef _SAFE_MEMORY
	NSafeTArray<stFourleafProduct, MAX_UNIQUENUM>	m_FourleafProduct;
	NSafeTArray<SI32, MAX_UNIQUENUM>				m_100healmanager;
#else
	stFourleafProduct	m_FourleafProduct[MAX_UNIQUENUM];
	SI32 m_100healmanager[MAX_UNIQUENUM];
#endif

	// ���� �ý��ۿ��� �������־��ų� �������ִ� �����۵��� ����� �о�´�.
	// ��ϵ� �����۵��� �������� ���鶧, �����Ҷ� Ư���� ������ ���Ѵ�.
	
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, Fourleaf_MAX_LIST>		m_FourleafRareList;
#else
	SI32 m_FourleafRareList[Fourleaf_MAX_LIST];
#endif

	bool IsFourleafRareItem(SI32 ItemUnique );


private:	

};

#endif
