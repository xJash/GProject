#ifndef _MAGICWHIRLPOOLOBJ_H_
#define _MAGICWHIRLPOOLOBJ_H_

#include "../MagicBaseInfo.h"
#include "../MagicBaseObj.h"

#define		MOVEMENT				5				// ȸ������ �����̴� ũ��( X, Y �Ѵ� �̰� ��� )
#define		MOVEMENTDELAYTIME		5				// Action�� 10�� ȣ�� �ɶ� ���� ȸ���� ������ �����. �׷��� ���� ������ ��� ����ٴϸ鼭, Ÿ���� �ְ� �ǹǷ�...

class cltMapCommon;

class	CMagicWhirlPoolObj : public CMagicBaseObj
{
public:
	CMagicWhirlPoolObj( CMagicMgr *pMagicMgr );
	~CMagicWhirlPoolObj();

	void	Initialize();
	void	Destroy();

	bool	SetMagic( stMagicInfo *pstMagicInfo, SI32 si32AddDamage, cltMapCommon *pclMap, SI32 si32SkillLevel, SI32 siOrganUnique );	// Set
	bool	Action();											// Action
	void	Draw();												// Draw

	
	bool	Push( BYTE *pData, SI32 si32Size );					// Push
	


	//--------------------- �޽��� �� ó��------------------
	void	SetDamage( SI32 si32Damage );
	bool	GetMinMaxDamage(SI32 &Min, SI32 &Max);

private:

	stMagicInfo				*m_pMagicInfo;

	SI32					m_si32DrawXPos;
	SI32					m_si32DrawYPos;

	//SI32					m_si32CurrentFrame;
	//SI32					m_si32MaxFrameNum;
	SI32					m_si32AddDamage;
	SI32					m_si32TotalDamage;

	SI32					m_si32CurrentMagicActionFrame;

	SI32					m_si32DotStartXPos;
	SI32					m_si32DotStartYPos;

	cltMapCommon			*m_pclMap;

	SI32					m_si32MoveMentDelayTime;

	SI32					m_si32TargetDotXPos;
	SI32					m_si32TargetDotYPos;

	char					m_cBigXPos;			// ȸ������ ���� �������� ��� ���� �ϱ� ���ؼ�..
	char					m_cBigYPos;
};


#endif