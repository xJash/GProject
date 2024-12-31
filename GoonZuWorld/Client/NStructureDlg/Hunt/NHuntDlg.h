#ifndef _NHUNTDLG_H
#define _NHUNTDLG_H

#include "../StrBaseDlg/StrBaseDlg.h"
#include "../../CommonLogic/Hunt/Hunt.h"

class NStrInventory;	

class NHuntDlg : public NStrBaseDlg
{
public:
	NHuntDlg();
	virtual ~NHuntDlg();

	void Create();

	void GreetingMsg();

	void RetMsgBox(bool RetValue, SI16 MsgIndex, BYTE* pData, SI16 DataLen);

	void VDirectDrawToBackScreen(LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY);
};

// ����� �޴� 
class NHuntUserDlg : public NStrTabDlg
{
public:
	enum {
		EDIT_EXPLAIN,
		LIST_MONSTERINFO,
		BUTTON_ENTER
	};

	NHuntUserDlg();
	virtual ~NHuntUserDlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

};


// ������ ��� �޴� 
class NHuntChiefDlg : public NStrTabDlg
{
public:
	enum {
		BUTTON_DELETE,
		BUTTON_ADD,
		BUTTON_INPUT,
		BUTTON_OUTPUT,

		EDIT_MONSTERLEVEL,
		COMBO_MONSTERNUMBER,
		EDIT_INPUTNUMBER,

		LIST_MONSTERINFO,

		COMBO_MONSTERKIND,

		LISTVIEW_MYINVENTORY,
		LISTVIEW_HUNTSTG

	};

	NHuntChiefDlg();
	virtual ~NHuntChiefDlg();

	void InitDlg();

	void Action();

	void LoadLineUpInfoList();
	void LoadHuntStg();


	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

public:
	NStrInventory*	m_pMyInventory;

	SI32			m_siSelectedStgIndex;

	BOOL			m_Count;



};

// ������ ���� ���� 
class NHuntChangeMapDlg : public NStrTabDlg
{
public:
	enum {

		IMAGESTATIC_MAP	,
		BUTTON_PREV	,
		BUTTON_SETUP	,
		BUTTON_NEXT	,
		EDITBOX_COST	,
		EDITBOX_HUNTTYPE	,
		EDITBOX_NEEDLEVEL	,
	};

	enum {

		FIXED_WIDTH = 280,		// �̴ϸ� �� �ּҰ�
		FIXED_HEIGHT = 140,
	};

	TSpr	Spr;

	LPDIRECTDRAWSURFACE7	m_lpSmallMapSurface;
	LPDIRECTDRAWSURFACE7	m_lpSmallMapWorkSurface;


	NHuntChangeMapDlg();
	virtual ~NHuntChangeMapDlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
	
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void ShowHuntMap();

	void VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );
};

#endif

