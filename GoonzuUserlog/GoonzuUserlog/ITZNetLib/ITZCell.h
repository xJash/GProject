#ifndef _ITZCELL_H
#define _ITZCELL_H

#include "ITZObject.h"
#include "ITZList.h"
#include "ITZWorld.h"

class ITZPerson;
class ITZMap;

class ITZCell
{
public:
	ITZCell();
	~ITZCell();

	void				CreateCell( ITZWorld< ITZMap > *pWorld, ITZMap *pMap );
	void				SetPerson( ITZPerson *pPerson );
	void				DelPerson( ITZPerson *pPerson );

	void				SendPacket( sPacketHeader *pPacket );
	void				SendPacketExceptOne( ITZPerson *pExceptedPerson, sPacketHeader *pPacket );
	
	void				SendPacketNearAll( sPacketHeader *pPacket );
	
	// ���� ���� �ִ� �÷��̾���ڸ� ��ȯ�Ѵ�
	UI32				GetPlayerCount() { return m_uiPlayerCount; }

	// ���� �� �ֺ� �����߿� �÷��̾ �Ѹ��̶� ������ TRUE�� ��ȯ�Ѵ�.
	BOOL				IsTherePlayerNearCells();


public:
	ITZList< ITZObjectPtr >		m_personPtrList;

	ITZWorld< ITZMap >*			m_pWorld;
	ITZMap*						m_pMap;

	ITZCell*					m_pNearCell[9];
	UI32						m_uiNearCellCount;

	sItem**						m_ppItem;
	UI32						m_uiItemSlotCount;

	UI32						m_uiPlayerCount;


};



#endif