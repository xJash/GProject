#ifndef _ITZQLIST_H
#define _ITZQLIST_H

#include "itzbase.h"

class ITZObject;

// push, pop�� ���ÿ� ���� �ٸ� �����忡�� ���ÿ� ó���� �����ϴ� 
// getFirst, getLast, remove ���� ���� �����忡���� ����Ͽ��� �Ѵ�

class ITZQList
{
public:
	ITZQList();
	~ITZQList();

public:

	ITZObject*			getFirst() { return m_pFirst; };
	ITZObject*			getLast() { return m_pLast; };

	void				clear();

	void				push( ITZObject *pElem );
	ITZObject*			pop();

	void				remove( ITZObject *pElem );
	
	SI32				size() { return m_siNumberOfElements; };

private:
	
	ITZObject*			m_pFirst;
	ITZObject*			m_pLast;

	SI32				m_siNumberOfElements;

	CRITICAL_SECTION	m_cs;

};

#endif