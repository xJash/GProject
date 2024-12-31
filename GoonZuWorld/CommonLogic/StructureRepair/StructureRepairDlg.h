#ifndef _STRUCTUREREPAIRDLG_H
#define _STRUCTUREREPAIRDLG_H

#include "CommonHeader.h"
#include "StructureClass/StructureClass.h"

class cltStructureMngBasic;

class cltStructureRepairDlg
{
public:
	cltStructureRepairDlg();
	~cltStructureRepairDlg();

	void							Create( HINSTANCE hInst, HWND hParent, cltStructureMngBasic *pclStructureManager );

//	void							LoadMyInventory( HWND hDlg );
	BOOL							IsMyInventoryChanged();

	static cltStructureMngBasic*	m_pclStructureManager;

	cltItem							*m_pclMyItem;				// �� �κ��丮 üũ

	HWND							m_hUserInventory;

	HIMAGELIST						m_hImageList;
	
	SI32							m_siInventorySelectedIndex;
};

#endif


