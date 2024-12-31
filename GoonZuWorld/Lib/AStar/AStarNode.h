#ifndef _ASTARNODE_H_
#define _ASTARNODE_H_

#include <windows.h>

class CAStarNode
{
public:
	CAStarNode();								// �� �� ��
	~CAStarNode();								// �� �� ��

	void Initialize();							// �� �� ȭ
	void Destroy();								// ���� ó��

	inline unsigned int GetTileXIndex()	{ return m_uiTileXIndex; };			// Ÿ�� X ��ǥ ��� ��	
	void SetTileXIndex( int siTileXIndex );		// Ÿ�� X ��ǥ ����
	
	inline unsigned int GetTileYIndex()	{ return m_uiTileYIndex; };			// Ÿ�� X ��ǥ ��� ��		
	void SetTileYIndex( int siTileYIndex );		// Ÿ�� Y ��ǥ ����

	float GetFitness();							// ���յ� �� ����
	void SetFitness( float fFitness );			// ���յ� �� ����
	void SetFitness( int siStartXIndex, int siStartYIndex, int siEndXIndex, int siEndYIndex, int siGoal );	// �ѹ��� ���� �����ϰ� �ϱ� ���ؼ�
	

	int GetGoal();								// ��ǥ �� ����
	void SetGoal( int siGoal );					// ��ǥ �� ����

	
	float GetHeuristic();						// �޸���ƽ �� ����
	//void SetHeuristic( float fHeuristic );		// �޸���ƽ �� ����
	

	CAStarNode *GetParentNode();				// Parent Node ������ ����
	void SetParentNode( CAStarNode *pNode );	// Parent Node ������ ����

	inline CAStarNode *GetNextNode() { return m_pNext; };					// Next Node ������ ����
	void SetNextNode( CAStarNode *pNode );		// Next Node ������ ����


	CAStarNode *GetEmptyPre();					// m_pEmptyPre ������ ����
	void SetEmptyPre( CAStarNode *pNode );		// m_pEmptyPre ������ ����

	CAStarNode *GetEmptyNext();					// m_pEmptyNext ������ ����
	void SetEmptyNext( CAStarNode *pNode );		// m_pEmptyNext ������ ����

	CAStarNode *GetChild( char cIndex);			// ���ϵ� ����
	void SetChild( CAStarNode *pNode );			// ���ϵ� ����	
	char GetChildrenNum();						// ���ϵ� �� ����


	
private:
	CAStarNode *m_pParent;						// Parent Node
	CAStarNode *m_pNext;						// OpenedList �Ǵ� ClosedList �� �� �ϳ��� �ݵ�� �߰��Ǿ�� �ϹǷ�...

	CAStarNode *m_pEmptyPre;					// NotUsingList �� ���� ��쿡�� ����� ��ũ�带 ���Ƿ�...
	CAStarNode *m_pEmptyNext;					// NotUsingList �� ���� ��쿡�� ����� ��ũ�带 ���Ƿ�...

	float m_fFitness;							// f : �� �� ��
	int m_siGoal;								// g : ��    ǥ
	float m_fHeuristic;							// h : �޸���ƽ
	
	unsigned int m_uiTileXIndex;				// ��� �ִ� Ÿ�Ͽ� �ִ��� Ÿ�� X ��ǥ
	unsigned int m_uiTileYIndex;				// ��� �ִ� Ÿ�Ͽ� �ִ��� Ÿ�� Y ��ǥ

	CAStarNode *m_pChildren[8];					// ���ϵ尡 �ɼ� �ִ� ������ 8���� ( ��, ��, ��, ��, �»�, ����, ���, ���� )
	char m_cChildrenNum;						// ���ϵ��� ��
};

struct stAStarStack
{
	CAStarNode *m_pNode;
	stAStarStack *m_pNext;
};

#endif