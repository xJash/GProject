#ifndef _ASTARLISTMGR_H_
#define _ASTARLISTMGR_H_

#include "../../common/commonheader.h"


class CAStarOpenedList;
class CAStarClosedList;
class CAStarNotUsingNodeList;
class CAStarNode;

class CAStarStackListMgr;

//typedef bool (__stdcall *IsBlocking)( int, int );

#define MAX_NODE_NUM	120								// �ִ� ã�� ������ Ƚ���� 800/8 = 100(�ִ� ���� ���� Ƚ��) ���� ��.
//SI32	MAX_NODE_NUM = 240;


class CAStarListMgr
{
public:
	CAStarListMgr( void *pParent );	// �� �� ��
	~CAStarListMgr();									// �� �� ��

	void Initialize();									// �� �� ȭ
	void Destroy();										// ����ó��

	CAStarOpenedList *GetOpenedList();					// OpendList ������ ����
	CAStarClosedList *GetClosedList();					// ClosedList ������ ����

	//IsBlocking isblockfunc;
	bool (*IsBlocking)(int, int, int, int, void*);

	CAStarNode *GetBest();								// m_pOpendList ���� ���� �տ� �ִ� ��带 �����ϰ�, �� ��带 m_pClosedList ���� �տ� ����.

	CAStarNode *GetBestPtr();							// m_pBestPtr�� ������ ��������

	bool FindNextPath( int siStartXIndex, int siStartYIndex, int siEndXIndex, int siEndYIndex, int *siNextXIndex, int *siNextYIndex, bool (*IsBlocked)( int, int, void * ) );	// ���� ������ ��ǥ�� ��������
	bool FindNextPath( bool bNotUseAStar, int siStartXIndex, int siStartYIndex, int siEndXIndex, int siEndYIndex, cltPos *pNextPos, int *psiRetNum );		// ���� ������ ��ǥ�� ��������

	void GetNextPath( CAStarNode* pNode, int siStartXIndex, int siStartYIndex, int *siNextXIndex, int *siNextYIndex );					// ���� �� �ε��� �˻� �ϴ� ��
	void GetNextPath( CAStarNode* pNode, int siStartXIndex, int siStartYIndex, cltPos *pNextPos, int *psiRetNum );	// ���� �� ���� ������ŭ �ε��� �˻� �ϴ� ��
	//void GetNextPathNotFoundEndPos( int siStartXIndex, int siStartYIndex, int *siNextXIndex, int *siNextYIndex );	// ���� �� �ε��� �˻� �ϴ� �� ( ���� ��θ� ã�� ������ �ÿ��� ��򰡷δ� �����ϰ� �ٰ����� �ϹǷ�...)	
	void GetNextPathNotFoundEndPos( int siStartXIndex, int siStartYIndex, cltPos *pNextPos, int *psiRetNum);		// �������� heuristic �� �����Ѵ�. �׷��� �ణ�� ������ �ִ�. �������� ���� ���� �ִ� ��쿡 ���ؼ��� ó�� ���� �ʱ� ������ ���������� ������ ���ư��� ��찡 �߻��� �� �ִ�. �̰��� ���� �������� üũ�ؼ� �� ������ ��θ� ã�� �� �� ������ ���� ���� ���̶� ������ �Ǵ� �����, �� ���� �߰ߵǴ� �������� üũ�Ѵ�.
	bool CreateChildren( CAStarNode *pParent );			// ���ϵ� ����( �����̶�� ���ٴ� m_pNotUsingNodeList ���� ��� �ϳ� �����ͼ� ������ �̵��� �� ��Ȯ�� �� )
	void UpdateParents( CAStarNode *pNode );			// �θ� ����

	int Step();											// ����

	void SetMode( bool Mode )
	{
		m_bMode = Mode;
	}

private:
	void *m_pParentPtr;									// �� ��ü�� ������ ��ü(�θ�)�� ������

	CAStarOpenedList *m_pOpenedList;					// OpenedList
	CAStarClosedList *m_pClosedList;					// ClosedList

	int m_siStartXIndex;
	int m_siStartYIndex;

	int m_siEndXIndex;									// ���� Tile X Index
	int m_siEndYIndex;									// ���� Tile Y Index 

	CAStarNotUsingNodeList *m_pNotUsingNodeList;		// ���� �޸𸮿��� �������� ���� �ʴ� ������ ����Ʈ ( �������� �� ���̹Ƿ�, new �� delete �� ���� �ʰ� �ϱ� ���ؼ���. )

	CAStarStackListMgr *m_pStackListMgr;				// Stack �� �޸� ������ ���ؼ�...

	CAStarNode *m_pBest;

	//CAStarNode *m_pPathList[ MAX_NODE_NUM ];			// �� ã�� ���� ���� ��θ� ������ ����.
	int			m_siPathListNum;						// �� ã�� ���� ���� ��ΰ� � �ִ���...

	int			m_siMaxFindPathNum;						// �ִ� �� ã�� ����.

	bool		m_bMode;								// true : 8����, false : 4 ���� 

};

#endif
