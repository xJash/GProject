#ifndef _LIBLiSTMGR_H_
#define _LIBLiSTMGR_H_

#include "LibListBaseInfo.h"

class	CLibList;
class	CObj;

class CLibListMgr
{
public:
	CLibListMgr( bool bCircleLinkedListMode = false );					// bCircleLinkedListMode �� ��尡 �� á����, ���ο� ��带 �߰��϶�� �ϸ� ���� ó���� ��� ��带 �ʱ�ȭ �ϰ�, �� ��带 ���� ������ ���ġ ��Ŵ...
																		// ���� ���ϸ� emptylist �� ��尡 ������, existlist �� ���� ó���� �Էµ� ��带 �ʱ�ȭ �� ������, �� ���� existlist ���� ���� ���� ������...
																		// �̰��� true�� ����ϴ� ���� �̹��� �ε��� ������, ��尡 �����ϸ� exist List �� ���� ������带 �ʱ�ȭ ���Ѽ� ��ü ��Ű�� ���� ������... �ַ� Ŭ���̾�Ʈ���� ����� �Ǿ���.
																		// �������� ������ �����ؾ���....
																		// �׷��� default ������ false �� �� ������
																		// bCircleLinkedListMode �� false �� �� ��쿡�� CircalMode�� ����� if ���� ��� �����ؼ� �� ���� �ӵ��� ����� �� �ְ� �ȴ�.
	virtual	~CLibListMgr();

	void	Initialize();
	void	Destroy();

	void	CreateMaxEmptyObj( int si32MaxObjNum, int si32BufferSize );	// �����ÿ� Empty List �� �ִ� ������ �����ؼ� �־��ֱ� ���ؼ�.
	void	Clear();

	void	Lock();
	void	UnLock();

	void	PushFrontToExistList( CObj *pObj );
	void	PushBackToExistList( CObj *pObj );

	void	PushFrontToEmptyList( CObj *pObj );
	void	PushBackToEmptyList( CObj *pObj );


	CObj	*PopFrontToExistList();
	CObj	*PopBackToExistList();

	CObj	*PopFrontToEmptyList();
	CObj	*PopBackToEmptyList();

	// ������ ���� 8�� �Լ��� ���ٴ� �Ʒ��� 8�� �Լ��� ���� ����. ( �Ʒ� �Լ����� ���� �Լ��� ������ ����� �����ϹǷ�, �� ���ϰ� ���ɵ� ����. )
	CObj	*PopFrontToExistListAndPushFrontToEmptyList();
	CObj	*PopFrontToExistListAndPushBackToEmptyList();
	CObj	*PopBackToExistListAndPushFrontToEmptyList();
	CObj	*PopBackToExistListAndPushBackToEmptyList();

	CObj	*PopFrontToEmptyListAndPushFrontToExistList();
	CObj	*PopFrontToEmptyListAndPushBackToExistList();
	CObj	*PopBackToEmptyListAndPushFrontToExistList();
	CObj	*PopBackToEmptyListAndPushBackToExistList();

	int		GetExistListObjNum();
	int		GetEmptyListObjNum();

	CLibList	*GetExistList();
	CLibList	*GetEmptyList();

private:

	bool				m_bCircleLinkedListMode;

	CLibList			*m_pExistList;
	CLibList			*m_pEmptyList;

	CRITICAL_SECTION	m_LibListMgrCrit;
};

#endif