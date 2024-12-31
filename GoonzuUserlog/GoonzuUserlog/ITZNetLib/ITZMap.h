#ifndef _ITZMAP_H
#define _ITZMAP_H

#include "itzbase.h"
#include "ITZWorld.h"

class ITZPerson;
class ITZCell;


class ITZMap
{
public:
	ITZMap();
	~ITZMap();

public:
	void				CreateMap( int mapXtile, int mapYtile );
	void				SetWorld( ITZWorld< ITZMap > *pWorld ); 

	int					GetCellIndex( int x, int y );
	ITZCell*			GetCell( int x, int y );

	void				SetCellList( ITZCell *pOldCell, ITZCell *pCurrentCell );

	void				Warp( int x, int y, ITZPerson *pPerson, bool bticketusewarpswitch );
	void				MoveChar( int x, int y, ITZPerson *pPerson, bool bticketusewarpswitch );

	BOOL				AddItem( int x, int y, UI16 itemIndex );
	BOOL				DelItem( int x, int y, UI16 itemIndex );

public:
	virtual void		SendPersonEnterMsgToOthers( ITZPerson *pPerson, bool bticketusewarpswitch ) {};
	virtual void		SendPersonLeaveMsgToOthers( ITZPerson *pPerson ) {};
	virtual void		SendPersonMoveMsgToOthers( ITZPerson *pPerson ) {};

	virtual void		SendAddItemMsgToOthers( sItem *pItem ) {};
	virtual void		SendDelItemMsgToOthers( sItem *pItem ) {};

	virtual void		SendNewOthersInfoToPerson( ITZPerson *pPerson ) {};
	virtual void		SendNewItemsInfoToPerson( ITZPerson *pPerson ) {};


protected:
	ITZWorld< ITZMap >*	m_pWorld;

	ITZCell*			m_pCell;

	int					m_mapXtile;									// ���� ���� ũ�� (����:Ÿ��)
	int					m_mapYtile;									// ���� ���� ũ�� (����:Ÿ��)

	int					m_mapXcell;									// ���� ���� ũ�� (����:��)
	int					m_mapYcell;									// ���� ���� ũ�� (����:��)

	UI32				m_uiCellCount;								// ���� ��ü ���� ���� 

	ITZCell*			m_pRemoveCell[ 9 ];							// ���ÿ������� ���ܵǴ� ��
	ITZCell*			m_pNewCell[ 9 ];							// ���ÿ����� ���� �߰��Ǵ� ��

	UI32				m_uiRemoveCellCount;						// ���ÿ������� ���ܵǴ� �� ����
	UI32				m_uiNewCellCount;							// ���ÿ����� ���� �߰��Ǵ� �� ����

	sItem*				m_pItem;
};


#endif

