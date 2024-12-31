// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

class NGMClientProcess;
class ServerInfo;

enum
{
	CHILD_START,
	//========================================
	CHILD_ID,
	CHILD_CHAR,
	CHILD_LOG1,
	CHILD_LOG2,
	CHILD_ITEM,
	CHILD_BLOCK,
	CHILD_GUILD,
	CHILD_NOTICE,
	//========================================
	CHILD_END
};

#pragma once
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Ư��
public:
	ServerInfo*				m_pServerInfo;

	int GetGameServerID(TCHAR* pszWorldName);

// �۾�
public:
	CMDIChildWnd*			m_pkChildWnd[CHILD_END];

	CMDIChildWnd*			GetChild(int nChildID)
	{
		if(nChildID > CHILD_START && nChildID < CHILD_END)
		{
			return m_pkChildWnd[nChildID];
		}
		return NULL;
	}

	void SetChild(int nChildID, CMDIChildWnd* pMDIChildWnd)
	{
		if(nChildID > CHILD_START && nChildID < CHILD_END)
		{
			m_pkChildWnd[nChildID] = pMDIChildWnd;
		}
	}

// ������
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMenuId();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
};


