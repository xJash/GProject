#pragma once

enum // �ൿ�� Ÿ��
{
	ACTERTYPE_CHAR = 1, // ĳ���� ��
	ACTERTYPE_ID,	    // ���� ��
	ACTERTYPE_IP        // ������ �ּ�
};

struct cltListViewColumn
{
	TCHAR		szName[32];
	TCHAR		szColumnName[32];	// ���̴� �̸�.
	int			nFormat;
	int			nWidth;
	int			nDataType;		// 1: Number, 2: String
	int			nSortOrder;		// 1: ��������, 0: ��������

	void Set(cltListViewColumn* pListViewColumn)
	{
		if(pListViewColumn == NULL)		return;

		memcpy(this, pListViewColumn, sizeof(*this));
	}
};

struct cltNewLogString
{
	CString		Name;
	CString		Data;
};

// CNewLogView ��ȭ �����Դϴ�.

class CNewLogView : public CDialog
{
	DECLARE_DYNAMIC(CNewLogView)

public:
	CNewLogView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNewLogView();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NEWLOGVIEW };

	void AddLogData(cltNewLogString* LogStringData, int nCount);

	BOOL RequestLog();

protected:
	int		m_nRowCount;

	CTime	m_StartTime, m_EndTime;
	CTime	m_CurrentTime;

	BOOL AddColumnFromName(TCHAR* pName);


public:
	int					m_siItemDataColumnNum;
	int					m_nSortColumn;
	cltListViewColumn	m_ActiveListViewColumn[80];
	int					m_ActiveListViewColumnCount;

protected:
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSearchNew();
	afx_msg void OnBnClickedButtonStopNew();
	afx_msg void OnHdnItemclickListResultNew(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListResultNew(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSelDeleteNew();
	afx_msg void OnBnClickedButtonDeselDeleteNew();
	afx_msg void OnBnClickedButtonAllDeleteNew();
	afx_msg void OnBnClickedButtonSelExportNew();
	afx_msg void OnBnClickedButtonAllExportNew();
	afx_msg void OnBnClickedButtonSearchinresultNew();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonSelectAll();
	afx_msg void OnBnClickedButtonUnSelectAll();
	afx_msg void OnCbnSelchangeComboCommandtype();
	afx_msg void OnBnClickedRadioCharacter();
	afx_msg void OnBnClickedRadioAccountid();
	afx_msg void OnBnClickedGroupClickeditem2();
	afx_msg void OnBnClickedBtnLoadnewviewer();
};
