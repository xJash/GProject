
#define NOSUSPICTION_PRISON_TIME	5	// ��ũ�� ����� ���� �Ű�� ���� �ð�(��) 
//---------------------------------
// 2004/9/01 ���ؿ�
//---------------------------------

#ifndef _AUTOHUNTING_H
#define _AUTOHUNTING_H

#include <Directives.h>

#define MAX_SUSPECT_NUM		3000

#define PRISON_TIME			300

#define CLIENT_UPDATE_TIME			2
#define NOSUSPICTION_PRISON_TIME	5	// ��ũ�� ����� ���� �Ű�� ���� �ð�(��) 

class cltAutoHuntingManager{
public:
	cltAutoHuntingManager();
	~cltAutoHuntingManager();

public: // Client
/*	void Create( HINSTANCE hInst, HWND hParent );

	static BOOL CALLBACK StaticAutoHuntingDlgMsgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK AutoHuntingDlgMsgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	// Txt : �䱸�ܾ�,request : �Ƿ��� �̸�
	void Set(TCHAR * Txt,SI32 slot,SI32 minuts,SI16 prisontime,SI16 prisonerpenalty);
	void Hide();

	void SetLeftTime(SI32 time)
	{
		m_siLeftTime = time;
	}
	SI32 GetLeftTime()
	{
		return m_siLeftTime ;
	}*/

public: // Server
	void Init();
	bool Set(const TCHAR * Txt,TCHAR * request,TCHAR * suspect,SI32* slot,SI32 requestid);
	void SetStaticTime(SI32 totaltime);
	void Action();
	void DeletePerson(const TCHAR* szSuspectName);
	void DeletePerson(const SI32 siSlot);
	bool CheckAnswer(const TCHAR* szSuspectName,const TCHAR* szAnswer,SI32 siSlot,SI32* siCheck);
	bool IsRequest(const TCHAR* name);
	void PrisonUser(TCHAR* name,SI32 requestid,SI32 time,TCHAR * reason);

private: // Client
/*	HWND		m_hWnd;
	HINSTANCE	m_hInst;

	HWND	m_hDlg;

	HBRUSH m_hStaticBrush;
	HBRUSH m_hDlgBrush;

	SI32	m_siLeftTime;
	SI32	m_siSlot;*/

protected: // Server
#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_SUSPECT_NUM>		m_bActionSwitch;

	NSafeTArray<SI32, MAX_SUSPECT_NUM>		m_szRequestPersonID; // �Ƿ����� personid
	NSafeTArray<SI32, MAX_SUSPECT_NUM>		m_siCheckNum;		// ������ ���°�ΰ�

	NSafeTArray<DWORD, MAX_SUSPECT_NUM>		m_dwWatingClock;
	NSafeTArray<DWORD, MAX_SUSPECT_NUM>		m_dwUpdateColok;
#else
	bool	m_bActionSwitch[MAX_SUSPECT_NUM];

	SI32	m_szRequestPersonID[MAX_SUSPECT_NUM]; // �Ƿ����� personid
	SI32	m_siCheckNum[MAX_SUSPECT_NUM]; // ������ ���°�ΰ�

	DWORD	m_dwWatingClock[MAX_SUSPECT_NUM];
	DWORD	m_dwUpdateColok[MAX_SUSPECT_NUM];
#endif

	TCHAR	m_szRequestName[MAX_SUSPECT_NUM][MAX_PLAYER_NAME]; // �Ƿ���
	TCHAR	m_szSuspectName[MAX_SUSPECT_NUM][MAX_PLAYER_NAME]; // ������

	TCHAR	m_szRequestTxt[MAX_SUSPECT_NUM][MAX_ITEM_NAME]; // ����
};

#endif
