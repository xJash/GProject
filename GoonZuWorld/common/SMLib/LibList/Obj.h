#ifndef _OBJ_H_
#define _OBJ_H_

#include "LibListBaseInfo.h"

class	CLibObjBuffer;

class	CObj
{
public:
	CObj( UI32 uiMaxBufferSize = 0 );		// �⺻ �����͸� ���� ���۰� �ʿ���� ��쿡�� �Ķ���� ������ �ƹ��͵� ���� ������ ��.
	virtual	~CObj();

	void	Initialize();
	void	ObjPtrInitialize();
	void	Destroy();

	CObj	*GetPre();
	void	SetPre( CObj *pPre );

	CObj	*GetNext();
	void	SetNext( CObj *pNext );

	void	SetData( BYTE *pData, UI32 ui32DataSize );
	void	GetData( BYTE *pData, UI32 *pDataSize );
	BYTE	*GetDataPtr();

private:
	CObj			*m_pPre;
	CObj			*m_pNext;

	CLibObjBuffer	*m_pObjBuffer;

};

#endif