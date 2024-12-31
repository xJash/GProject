#ifndef _CONSTRUCTION_H_
#define _CONSTRUCTION_H_

#include "../CommonHeader.h"

#include "../../NLib/NArray.h"

class CConstruction
{
public:
	CConstruction();
	~CConstruction();

	void	Initialize();
	void	Destroy();

	void	ReadStructureInfoData();

	void	Set( SI16 *psiUniqueConstructionID );					// ������ ��ü�� �����͸� ����( �ʱ�ȭ �ÿ� DB ���� ������ �޾ƿö��� ��� �� ), �Ʒ��� �Լ��� ����ص� ��
	bool	Set( SI16 siUniqueConstructionID, SI16 siIndex );		// �ǹ� �߰��ÿ� ���
	
	bool	Del( SI16 siIndex );
	
	SI16*	Get();
	SI16	Get( SI16 siIndex );

	SI32	GetSlotFromStrUnique( SI32 strunique );
	
	bool	IsExist( SI16 siIndex );
	bool	IsDuplicate( SI16 siUniqueConstructionID );

	BOOL	IsThereStructure( SI16 ranktype ) { return m_bStructure[ ranktype ]; }

	bool	GetPosFromStrUnique( SI32 strunique, SI32* xpos, SI32 *ypos );
	
private:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_CONSTRUCTION_NUM>		m_siUniqueConstructionID;
	NSafeTArray<BOOL, MAX_RANKTYPE_NUMBER>		m_bStructure;
#else
	SI16	m_siUniqueConstructionID[ MAX_CONSTRUCTION_NUM ];			// �ǹ� Unique ID�� ����
	BOOL	m_bStructure[ MAX_RANKTYPE_NUMBER ];						// RankType�� �ǹ� ���翩��
#endif

};

#endif