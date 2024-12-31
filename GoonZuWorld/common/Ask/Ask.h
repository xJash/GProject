//---------------------------------
// 2004/1/17 ���°�
//---------------------------------
#ifndef _ASK_H
#define _ASK_H

#include <Directives.h>
#include <CommonHeader.h>

#define MAX_ASK_TEXT_SIZE	80

#define MAX_ASK_NUMBER		50

//-----------------------------
// ���� �Ѱ� ����. 
//-----------------------------

class cltAskUnit{
public:
	SI16 siCharUnique;		// �������� CharUnique
	SI32 siPersonID;		// �������� PersonID
	SI32 siSerialNum;		// �Ϸù�ȣ.	
	TCHAR szPersonName[MAX_PLAYER_NAME];
	TCHAR szAskText[MAX_ASK_TEXT_SIZE];
	


	cltAskUnit()
	{
		Init();
	}

	cltAskUnit(SI16 charunique, SI32 personid, SI32 serial, TCHAR* ppersonname, TCHAR* ptext)
	{
		siCharUnique	= charunique;
		siPersonID		= personid;
		siSerialNum		= serial;
		
		MStrCpy( szPersonName, ppersonname, MAX_PLAYER_NAME );
		MStrCpy( szAskText, ptext, MAX_ASK_TEXT_SIZE );
	}
	
	void Init()
	{
		siCharUnique	= 0;
		siPersonID		= 0;
		siSerialNum		= 0;
	}


};


//----------------------------
// ���� ������. 
//----------------------------
class cltAskManager{
public:
	HWND m_hDlg;					// ������ ����. 

	RECT DlgRect;
	bool bDlgRectInitSwitch;


	SI32		siIndex;			// ����. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltAskUnit, MAX_ASK_NUMBER>		clUnit;
#else
	cltAskUnit clUnit[MAX_ASK_NUMBER];
#endif

	bool		bUpdateSwitch;

	cltAskManager();
	~cltAskManager();


	// ������ �߰��Ѵ�. 
	bool Add(SI16 charunique, SI32 personid, TCHAR* ppersonname, TCHAR* ptext);

	// personid�� ������ ������ �����Ѵ�. 
	void DelAskPersonID(SI32 personid);

	// ������ �����Ѵ�. 
	void Update();

	BOOL CreateDlg(HINSTANCE hinst, HWND hwnd);
	static BOOL CALLBACK StaticAskDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK AskDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

};

#endif
