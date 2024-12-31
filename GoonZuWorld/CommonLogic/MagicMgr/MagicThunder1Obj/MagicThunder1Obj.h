#ifndef _MAGICTHUNDER1OBJ_H_
#define _MAGICTHUNDER1OBJ_H_

#include "../MagicBaseInfo.h"
#include "../MagicBaseObj.h"

class cltMapCommon;

class CMagicThunder1Obj : public CMagicBaseObj
{
public:
	CMagicThunder1Obj( CMagicMgr *pMagicMgr );
	~CMagicThunder1Obj();

	void	Initialize();
	void	Destroy();

	bool	SetMagic( stMagicInfo *pstMagicInfo, SI32 si32AddDamage, cltMapCommon *pclMap, SI32 si32SkillLevel, SI32 siOrganUnique );	// Set
	bool	Action();										// Action
	void	Draw();											// Draw

	
	bool	Push( BYTE *pData, SI32 si32Size );				// Push
	


	//--------------------- �޽��� �� ó��------------------
	void	SetDamage( SI32 si32Damage );

private:

	stMagicInfo			*m_pMagicInfo;

	SI32				m_si32DrawXPos;
	SI32				m_si32DrawYPos;

	SI32				m_si32AddDamage;
	SI32				m_si32TotalDamage;

	cltPos				m_clDotHitPos;
	cltMapCommon*		m_pclMap;


};


#endif