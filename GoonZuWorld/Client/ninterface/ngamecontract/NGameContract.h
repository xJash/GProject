
//�Ŀ� �ٽ� �۾� ����.. �켱 ���� .. 050325
#ifdef __SUN_GAMECONTRACT__


//---------------------------------
// 2004/1/28 ���°�
//---------------------------------

#include <Directives.h>

class cltGameContract{
public:
	HWND m_hDlg;					// ������ ����. 

	RECT DlgRect;
	bool bDlgRectInitSwitch;


	cltGameContract();
	~cltGameContract();


	BOOL CreateDlg(HINSTANCE hinst, HWND hwnd);
	static BOOL CALLBACK StaticDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

};

#endif