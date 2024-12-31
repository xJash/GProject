//=============================================================================
//
//	CryptToolDlg.cpp
//
//	Copyright 2005 HQGame
//
//=============================================================================

#include "stdafx.h"
#include "CryptTool.h"
#include "CryptToolDlg.h"
#include ".\crypttooldlg.h"

#include "FolderDlg.h"
#include "ViewerDialog.h"

#include "NUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//=============================================================================
//	CLASS   CAboutDlg
//! @brief  ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
//=============================================================================
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//=============================================================================
	// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };
	//=============================================================================

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

protected:
	DECLARE_MESSAGE_MAP()
};

//=============================================================================
//  @Name   CAboutDlg()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  ������
//=============================================================================
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

//=============================================================================
//  @Name   DoDataExchange()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

//=============================================================================
// CAboutDlg - Message Map
//=============================================================================
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()



//=============================================================================
// CCryptToolDlg ��ȭ ����
//=============================================================================

//=============================================================================
//  @Name   CCryptToolDlg()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  ������
//=============================================================================
CCryptToolDlg::CCryptToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCryptToolDlg::IDD, pParent)
	, m_wKeyR(_T("0x0816"))
	, m_wKeyC1(_T("0x6081"))
	, m_wKeyC2(_T("0x1608"))
	, m_bDelText(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//=============================================================================
//  @Name   DoDataExchange()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CCryptToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LSTRESULT, m_lstResult);
	DDX_Text(pDX, IDC_EDTKEY_R, m_wKeyR);
	DDX_Text(pDX, IDC_EDTKEY_C1, m_wKeyC1);
	DDX_Text(pDX, IDC_EDTKEY_C2, m_wKeyC2);
	DDX_Control(pDX, IDC_LIST1, m_lstFolders);
	DDX_Check(pDX, IDC_CHKDELTEXT, m_bDelText);
}

//=============================================================================
// CCryptToolDlg - Message Map
//=============================================================================
BEGIN_MESSAGE_MAP(CCryptToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTNPROCESS, OnBnClickedBtnprocess)
	ON_BN_CLICKED(IDC_BTNVIEW, OnBnClickedBtnview)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNDEL, OnBnClickedBtndel)
	ON_BN_CLICKED(IDC_BTNDECODE, OnBnClickedBtndecode)
	ON_BN_CLICKED(IDC_BTNDECODEPROCESS, OnBnClickedBtndecodeprocess)
END_MESSAGE_MAP()


//=============================================================================
//  @Name   OnInitDialog()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  �ʱ�ȭ �۾�
//=============================================================================
BOOL CCryptToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// ����Ʈ ��Ʈ�� �ʱ�ȭ �۾�
	CRect	rc;
	m_lstResult.GetClientRect(rc);
	m_lstResult.ModifyStyle(LVS_ICON, LVS_REPORT, 0);
	m_lstResult.InsertColumn(0, "���", LVCFMT_LEFT, rc.Width() - 5, 0);

	TCHAR	szPath[MAX_PATH*2];
	TCHAR	szValue[1024];
	CString	kConfig;

	// ���� ���� ���丮 ����
	GetModuleFileName(NULL, szPath, MAX_PATH*2);
	TCHAR	*pSep = HQStrrChr(szPath, '\\');
	szPath[pSep - szPath+1] = '\0';

	// 'config.ini'������ ��ġ ����
	kConfig = szPath;
	kConfig += "config.ini";

//	m_wKeyR.Format("0x%04X", HQCryptTextFile::HQ_CRYPTTEXTFILE_CRYPTOGRAPH_KEY_R);
//	m_wKeyC1.Format("0x%04X", HQCryptTextFile::HQ_CRYPTTEXTFILE_CRYPTOGRAPH_KEY_C1);
//	m_wKeyC2.Format("0x%04X", HQCryptTextFile::HQ_CRYPTTEXTFILE_CRYPTOGRAPH_KEY_C2);

	// ����Ʈ�ڽ��� PATH�������� �߰� (������ ',')
	GetPrivateProfileString("PATH", "PATHES", "", szValue, 1024, kConfig);
	TCHAR *pToken = HQStrTok(szValue, ",");
	while (pToken != NULL)
	{
		m_lstFolders.AddString(pToken);
		pToken = HQStrTok(NULL, ",");
	}

	// ����Ʈ ��Ʈ�ѿ� �̹�������Ʈ �Ҵ�
	m_imgIcons.Create(IDB_ICONS, 20, 5, RGB(255, 255, 255));
	m_lstResult.SetImageList(&m_imgIcons, LVSIL_SMALL);

	UpdateData(FALSE);
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

//=============================================================================
//  @Name   OnSysCommand()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CCryptToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//=============================================================================
//  @Name   OnPaint()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CCryptToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//=============================================================================
//  @Name   OnQueryDragIcon()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CCryptToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//=============================================================================
//  @Name   OnBnClickedBtnprocess()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CCryptToolDlg::OnBnClickedBtnprocess()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileFind			fileFinder;
	CString			kTxtPathName, stTxtName;
	CString	kFolder;
	TCHAR				szCryptTxtName[MAX_PATH * 2], szCryptTxtPathName[MAX_PATH*2];
	BOOL				bSuccess;
	CString				strResultString;

	// ���̾�α��� ������ �Ҵ�
	UpdateData();

	// ����Ʈ��Ʈ���� ��� ������ ����
	m_lstResult.DeleteAllItems();
	// �������� ����� ����Ʈ�ڽ��� ������ ������ŭ ����
	for (int i=0; i<m_lstFolders.GetCount(); i++)
	{
		// ������ ����
		CString	strText;
		m_lstFolders.GetText(i, strText);
		kFolder = strText;
		
		// �۾� ����
		strResultString.Format(_T("========= Process %s ========"), (LPCTSTR)kFolder);
		m_lstResult.InsertItem(m_lstResult.GetItemCount(), strResultString, 2);

		// Text���ϸ� ã��
		kFolder += "\\*.txt";
		// ���� ã�� ����
		if (!fileFinder.FindFile((LPCTSTR)kFolder))	return;

		// ��� Text���Ͽ� ���� �۾�
		while(TRUE)
		{
			// ���� ���� ã�� - bSuccess �� FALSE�̸� ���� ������ ���ٴ� ������
			// ���������� �۾��ϰ� ��
			bSuccess = fileFinder.FindNextFile();
			
			stTxtName = fileFinder.GetFileName();		// ���ϸ�
			NLibStrCpy(szCryptTxtName, stTxtName);			// ���ο� ���ϸ� ����
			kTxtPathName = fileFinder.GetFilePath();	// ����+���ϸ�
			NLibStrCpy(szCryptTxtPathName, kTxtPathName);	// ���ο� ����+���ϸ� ����

			// ���ο� ���ϸ��� Ȯ���ڸ� '.txe'�� ����
			char	*pSep;
			pSep = NLibStrrChr(szCryptTxtName, '.');
			szCryptTxtName[pSep - szCryptTxtName] = '\0';
			NLibStrCat(szCryptTxtName, ".txe");

			pSep = NLibStrrChr(szCryptTxtPathName, '.');
			szCryptTxtPathName[pSep - szCryptTxtPathName] = '\0';
			NLibStrCat(szCryptTxtPathName, ".txe");

			// HQCryptTextFileŬ������ static �Լ��� ����Ͽ� ��ȣȭ �� ���� ����
			switch (NWriteEnCryptFile(kTxtPathName, szCryptTxtPathName))
			{
				case 1 :
				{				
					// �۾� ��Ȳ ���
					strResultString.Format(_T("%s -> %s : Success"), (LPCTSTR)stTxtName, szCryptTxtName);
					m_lstResult.InsertItem(m_lstResult.GetItemCount(), strResultString, 0);
					// ���������� ����� �ɼ��� Ȱ��ȭ �� ��� ���������� ����
					//if (m_bDelText)			DeleteFile(kTxtPathName);
					DeleteFile(kTxtPathName);

					CopyFile(szCryptTxtPathName,kTxtPathName,false);

					DeleteFile(szCryptTxtPathName);
					break;
				}
				case 2 :
				{
					// �۾� ��Ȳ ���
					strResultString.Format(_T("%s -> %s : Already EnCrypted!!"), (LPCTSTR)stTxtName, szCryptTxtName);
					m_lstResult.InsertItem(m_lstResult.GetItemCount(), strResultString, 1);
					break;
				}
				case 0 :
				{
					// �۾� ��Ȳ ���
					strResultString.Format(_T("%s -> %s : Fail"), (LPCTSTR)stTxtName, szCryptTxtName);
					m_lstResult.InsertItem(m_lstResult.GetItemCount(), strResultString, 1);
					break;
				}

			}
			// ���� ������ ������ ���� ����
			if (!bSuccess)		break;
		}
	}
}

//=============================================================================
//  @Name   OnBnClickedBtndecode()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  *.txe ������ �����Ͽ� *.txt���Ϸ� ��ȣȭ
//=============================================================================
void CCryptToolDlg::OnBnClickedBtndecode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog	filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"CryptText Files (*.txt) |*.txt||", NULL);

	CString	kCryptTxtPathName;
	TCHAR				szTxtPathName[MAX_PATH*2];

	// ���� ����â ����
	if (filedlg.DoModal() == IDOK)
	{
		kCryptTxtPathName = filedlg.GetPathName();
		NLibStrCpy(szTxtPathName, kCryptTxtPathName);

		// ���ο� ���ϸ��� Ȯ���ڸ� '.txt'�� ����
		char	*pSep;
		pSep = NLibStrrChr(szTxtPathName, '.');
		szTxtPathName[pSep - szTxtPathName] = '\0';
		NLibStrCat(szTxtPathName, ".txe");

		NWriteDeCryptFile(kCryptTxtPathName, szTxtPathName);

		DeleteFile((LPCTSTR)kCryptTxtPathName);

		CopyFile(szTxtPathName,kCryptTxtPathName,false);

		DeleteFile(szTxtPathName);
		
	}
}

//=============================================================================
//  @Name   OnBnClickedBtnview()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  ��ȣȭ �� �ؽ�Ʈ�� ������ ���� â ����
//=============================================================================
void CCryptToolDlg::OnBnClickedBtnview()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CViewerDialog	viewerdlg;

	// �ؽ�Ʈ ������ ���� â�� ����.
	viewerdlg.DoModal();
}

//=============================================================================
//  @Name   OnBnClickedBtnadd()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  ����Ʈ�ڽ� ��Ʈ�ѿ� �۾��� ���丮�� �߰��ϴ� ���
//=============================================================================
void CCryptToolDlg::OnBnClickedBtnadd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFolderDialog	folderdlg(_T("Text ������ ��ġ�� �����ϼ���."), _T("C:\\GoonzuWorld"), this);

	// ���� ����â�� �����Ѵ�.
	if (folderdlg.DoModal() == IDOK)
	{
		m_lstFolders.AddString(folderdlg.GetFolderPath());
	}

	// ����Ʈ�ڽ� ��Ʈ�ѿ� �ִ� �������� ','�� ��ū���� �Ͽ� ���ڿ��� �����Ѵ�.
	CString	 kWrite;
	for (int i=0; i<m_lstFolders.GetCount(); i++)
	{
		// ����Ʈ�ڽ� ��Ʈ���� ������ ���ڿ� ���
		CString strText;
		m_lstFolders.GetText(i, strText);

		// ','�� �߰��Ͽ� ���ڿ� ����
//		if (kWrite.Length() > 0)			
		kWrite += ",";

		kWrite += strText;
	}

	TCHAR		szPath[MAX_PATH*2];
	CString		kConfig;

	// ���� ���� ���丮 ����
	GetModuleFileName(NULL, szPath, MAX_PATH*2);
	TCHAR	*pSep = HQStrrChr(szPath, '\\');
	szPath[pSep - szPath+1] = '\0';

	// 'config.ini' ��ġ ����
	kConfig = szPath;
	kConfig += "config.ini";

	// 'config.ini'�� ������ ���ڿ��� ����
	WritePrivateProfileString("PATH", "PATHES", (LPCTSTR)kWrite, (LPCTSTR)kConfig);
}


//=============================================================================
//  @Name   OnBnClickedBtndel()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  ����Ʈ�ڽ� ��Ʈ�ѿ��� ���õ� ������ ����
//=============================================================================
void CCryptToolDlg::OnBnClickedBtndel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ���� ���õ� �������� �ִٸ� �� ������ ����
	if (m_lstFolders.GetCurSel() >= 0)
		m_lstFolders.DeleteString(m_lstFolders.GetCurSel());
	else
	// ���õ� ���� ������ ����
		return;

	// ����Ʈ �ڽ��� ��� �����۵��� ','�� �������� ���ڿ��� ����
	CString kWrite;
	for (int i=0; i<m_lstFolders.GetCount(); i++)
	{
		// ������ ���ڿ� ����
		CString strText;
		m_lstFolders.GetText(i, strText);

		// �����۰� ������ ���̿� ',' �߰�
		//if (kWrite.Length() > 0)			
		kWrite += ",";
		kWrite += strText;
	}

	TCHAR		szPath[MAX_PATH*2];
	CString	kConfig;

	// ���� ���� ���丮 ����
	GetModuleFileName(NULL, szPath, MAX_PATH*2);
	TCHAR	*pSep = HQStrrChr(szPath, '\\');
	szPath[pSep - szPath+1] = '\0';

	// 'config.ini' ��ġ ����
	kConfig = szPath;
	kConfig += "config.ini";

	// 'config.ini'�� ������ ���ڿ��� ����
	WritePrivateProfileString("PATH", "PATHES", (LPCTSTR)kWrite, (LPCTSTR)kConfig);
}

//=============================================================================
//  @Name   OnBnClickedBtndecodeprocess()
//! @author LeeKH						
//! @date   2006-1-23
//! @param  X   X
//! @return X
//! @brief  ��ϵ� ���丮���� ��� ��ȣȭ ������ txt���Ϸ� ��ȣȭ
//=============================================================================
void CCryptToolDlg::OnBnClickedBtndecodeprocess()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileFind			fileFinder;
	CString	kCryptTxtName, kCryptTxtPathName;
	CString	kFolder;
	TCHAR				szTxtName[MAX_PATH * 2], szTxtPathName[MAX_PATH*2];
	BOOL				bSuccess;
	CString				strResultString;

	// ���̾�α��� ������ �Ҵ�
	UpdateData();

	// ����Ʈ��Ʈ���� ��� ������ ����
	m_lstResult.DeleteAllItems();
	// �������� ����� ����Ʈ�ڽ��� ������ ������ŭ ����
	for (int i=0; i<m_lstFolders.GetCount(); i++)
	{
		// ������ ����
		CString	strText;
		m_lstFolders.GetText(i, strText);
		kFolder = strText;

		// �۾� ����
		strResultString.Format(_T("========= Process %s ========"), (LPCTSTR)kFolder);
		m_lstResult.InsertItem(m_lstResult.GetItemCount(), strResultString, 2);

		// Txe���ϸ� ã��
		kFolder += "\\*.txt";
		// ���� ã�� ����
		if (!fileFinder.FindFile((LPCTSTR)kFolder))	return;

		// ��� Text���Ͽ� ���� �۾�
		while(TRUE)
		{
			// ���� ���� ã�� - bSuccess �� FALSE�̸� ���� ������ ���ٴ� ������
			// ���������� �۾��ϰ� ��
			bSuccess = fileFinder.FindNextFile();

			kCryptTxtName = fileFinder.GetFileName();		// ���ϸ�
			NLibStrCpy(szTxtName, kCryptTxtName);			// ���ο� ���ϸ� ����
			kCryptTxtPathName = fileFinder.GetFilePath();	// ����+���ϸ�
			NLibStrCpy(szTxtPathName, kCryptTxtPathName);	// ���ο� ����+���ϸ� ����

			// ���ο� ���ϸ��� Ȯ���ڸ� '.txt'�� ����
			char	*pSep;
			pSep = NLibStrrChr(szTxtName, '.');
			szTxtName[pSep - szTxtName] = '\0';
			NLibStrCat(szTxtName, ".txe");

			pSep = NLibStrrChr(szTxtPathName, '.');
			szTxtPathName[pSep - szTxtPathName] = '\0';
			NLibStrCat(szTxtPathName, ".txe");

			// HQCryptTextFileŬ������ static �Լ��� ����Ͽ� ��ȣȭ �� ���� ����
			if (NWriteDeCryptFile(kCryptTxtPathName, szTxtPathName))
			{
				// �۾� ��Ȳ ���
				strResultString.Format(_T("%s -> %s : Success"), (LPCTSTR)kCryptTxtName, szTxtName);
				m_lstResult.InsertItem(m_lstResult.GetItemCount(), strResultString, 0);
				// ���������� ����� �ɼ��� Ȱ��ȭ �� ��� ���������� ����
				//if (m_bDelText)			DeleteFile((LPCTSTR)kCryptTxtPathName);
				DeleteFile((LPCTSTR)kCryptTxtPathName);

				CopyFile(szTxtPathName,kCryptTxtPathName,false);

				DeleteFile(szTxtPathName);
			}
			else
			{
				// �۾� ��Ȳ ���
				strResultString.Format(_T("%s -> %s : Fail"),  (LPCTSTR)kCryptTxtName, szTxtName);
				m_lstResult.InsertItem(m_lstResult.GetItemCount(), strResultString, 1);
			}

			// ���� ������ ������ ���� ����
			if (!bSuccess)		break;
		}
	}
}
