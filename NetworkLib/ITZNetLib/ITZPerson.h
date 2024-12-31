#ifndef _ITZPERSON_H
#define _ITZPERSON_H

#include "ITZObject.h"

class ITZSession;
class ITZRecvBuffer;
class ITZSendBuffer;
class ITZMap;
class ITZCell;


class ITZPerson : public ITZObject
{
public:
	ITZPerson();
	~ITZPerson();
	
	virtual void		Init();

	UI32				GetCharID() { return m_uiCharID; }

	ITZRecvBuffer*		GetRecvBuffer();
	ITZSendBuffer*		GetSendBuffer();

	void				SetSession( ITZSession *pSession ) { m_pSession = pSession; }
	ITZSession*			GetSession() { return m_pSession; }

	void				SetCell( ITZCell *pCell ) { m_pCell = pCell; };
	ITZCell*			GetCell() { return m_pCell; };

	void				SetMap( ITZMap *pMap ) { m_pMap = pMap; };
	ITZMap*				GetMap() { return m_pMap; };

public:
	ITZSession*			m_pSession;

	UI32				m_uiCharID;

	ITZMap*				m_pMap;								// ���� ��
	ITZCell*			m_pCell;							// ���� �� 
	SI32				m_siCellPersonIndex;				// �������� �ε���
};

#endif