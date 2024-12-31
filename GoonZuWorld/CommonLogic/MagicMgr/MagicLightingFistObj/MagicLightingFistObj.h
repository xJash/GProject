#ifndef  _MAGICLIGHTINGFISTOBJ_H_
#define  _MAGICLIGHTINGFISTOBJ_H_

#include "../MagicBaseInfo.h"
#include "../MagicBaseObj.h"

class cltMapCommon;

class	CMagicLightingFistObj : public CMagicBaseObj
{
public:
	CMagicLightingFistObj( CMagicMgr *pMagicMgr );
	~CMagicLightingFistObj();

	void	Initialize();
	void	Destroy();

	bool	SetMagic( stMagicInfo *pstMagicInfo, SI32 si32AddDamage, cltMapCommon *pclMap, SI32 si32SkillLevel, SI32 siOrganUnique );	// Set
	bool	Action();											// Action
	void	Draw();												// Draw

	
	bool	Push( BYTE *pData, SI32 si32Size );					// Push
	


	//--------------------- �޽��� �� ó��------------------
	void	SetDamage( SI32 si32Damage, SI32 si32CurrentRadius );


private:

	stMagicInfo				*m_pMagicInfo;

	SI32					m_si32DrawXPos;
	SI32					m_si32DrawYPos;

	//SI32					m_si32CurrentFrame;
	//SI32					m_si32MaxFrameNum;
	SI32					m_si32AddDamage;
	SI32					m_si32TotalDamage;
	
	cltMapCommon			*m_pclMap;
};


#endif