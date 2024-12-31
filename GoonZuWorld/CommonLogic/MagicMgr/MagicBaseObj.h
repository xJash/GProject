#ifndef _MAGICBASEOBJ_H_
#define _MAGICBASEOBJ_H_

#include "MagicBaseInfo.h"

#include "../../Common/SMLib/LibList/Obj.h"
#include "../../Client/Music/Music.h"

class	CLibList;
class	CMagicMgr;
class	CMagicMsgObj;

class CMagicBaseObj : public CObj
{
public:
	CMagicBaseObj( CMagicMgr *pMagicMgr);
	virtual ~CMagicBaseObj();

	void			Initialize();
	void			Destroy();

	SI32			GetStatus();
	void			SetStatus( SI32 si32Status );

	void			GetMagicAttribute( SI32 si32MagicKind );
	stMagicAttributeData	*GetMagicAttributePtr();

	// cltTSpr			*GetMagicSpr();
	TSpr			*GetMagicSpr();

	void			SetMagicSpr( SI32 gImageIndex );

	SI32			GetCurrentFrame();
	void			SetCurrentFrame( SI32 siCurrentFrame );

	SI32			GetCurrentMagicDelayFrame();

	SI32			GetMaxFrameNum();
	
	SI32			GetSkillLevel();

	stMagicHeader	*GetMagicHeader();
	void			SetKind(SI32 kind);
	SI32			GetKind()	{return m_siMagicKind;}
	virtual	bool	SetMagic( stMagicHeader *pstMagicHeader, SI32 si32SkillLevel);			// Set
	virtual	bool	Action();											// Action
	virtual	void	Draw();												// Draw

	virtual	bool	Push( BYTE *pData, SI32 si32Size );					// Push
	

private:

	SI32					m_si32CurrentFrame;
	SI32					m_si32MaxFrameNum;

	SI32					m_si32CurrentMagicDelayFrame;

	CMagicMgr				*m_pMagicMgr;							// Push, Pop �� CMagicMgr ���� �����ϴµ�, �� �����͸� ã�ư��� ���ؼ���.

	SI32					m_si32Status;							// ���� ����( ������ ���� ���̳�, ���� ���̳�, ������ ������ ��� )
	stMagicHeader			*m_pMagicHeader;

	stMagicAttributeData	*m_pMagicAttributeData;					// ������ �⺻ �Ӽ�(txt)�� ������ �ִ� ������

	TSpr					*m_pMagicSpr;							// ���� �̹��� ������

	SI32					m_si32SkillLevel;
	SI32					m_siMagicKind;
};

#endif
