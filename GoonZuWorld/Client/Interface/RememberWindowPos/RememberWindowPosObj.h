#ifndef _REMEMBERWINDOWPOSOBJ_H_
#define _REMEMBERWINDOWPOSOBJ_H_

#include "..\..\..\Common\SMLib\LibList\Obj.h"

class CRememberWindowPosObj : public CObj
{
public:
	CRememberWindowPosObj();
	~CRememberWindowPosObj();

	void	Initialize();
	void	Destroy();

	bool	IsAvailablePos( SI32 siLeft, SI32 siTop, SI32 siRight, SI32 siBottom );
	void	ChangePos( UI32 uiWindowKind, SI32 siLeft, SI32 siTop, SI32 siRight, SI32 siBottom );

	UI32	GetRememberWindowKind();
	void	GetRememberWindowPosData( UI32 *pWindowKind, SI32 *pLeftPos, SI32 *pTopPos, SI32 *pRightPos, SI32 *pBottomPos );
		

private:

	UI32	m_uiWindowKind;				// �����찡 � �ų�?

	SI32	m_siLeftPos;				// ������ ���� ��ǥ
	SI32	m_siTopPos;					// ������ ��� ��ǥ

	SI32	m_siRightPos;				// ������ ������ ��ǥ
	SI32	m_siBottomPos;				// ������ �ϴ� ��ǥ
};

#endif