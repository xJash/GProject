#ifndef _ASTAROPENEDLIST_H_
#define _ASTAROPENEDLIST_H_

#include "List.h"

class CAStarNode;

class CAStarOpenedList : public CAStarList
{
public:
	CAStarOpenedList();										// �� �� ��
	~CAStarOpenedList();									// �� �� ��

	void Initialize();										// �� �� ȭ
	void Destroy();											// ���� ó��

	void AddNode( CAStarNode *pNode );				// OpendList �� �߰� ( overloading ���� )

	CAStarNode *Pop();										// �ϳ� ������ ��

private:

};

#endif