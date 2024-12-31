// Id\IdView.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "../MainFrm.h"

#include "GMClientView.h"
#include ".\gmclientview.h"

// CGMClientView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGMClientView, CDialog)
CGMClientView::CGMClientView(CWnd* pParent /*=NULL*/)
	: CDialog(CGMClientView::IDD, pParent)
{
	m_clGMProcess = new GMProcess(this);
	m_clGMProcess->Init();

	m_strGMCmd = "";
	
	//m_clGMProcess = new GMProcess(this);
}

CGMClientView::~CGMClientView()
{
	delete m_clGMProcess;
}

void CGMClientView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITID, m_LoginID);
	DDX_Control(pDX, IDC_EDITPW, m_LoginPW);
	DDX_Control(pDX, IDC_LOGINBUTTON, m_LoginButton);
	DDX_Control(pDX, IDC_EDIT_COMMAND, m_GMCommand);
	DDX_Control(pDX, IDC_SEARCHBUTTON, m_SearchButton);
	DDX_Control(pDX, IDC_INFOBOX, m_InfoBox);
	DDX_Control(pDX, IDC_LOGINSECTION, m_LoginSection);
}

BEGIN_MESSAGE_MAP(CGMClientView, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_LOGINBUTTON, OnBnClickedLoginbutton)
	ON_BN_CLICKED(IDC_SEARCHBUTTON, OnBnClickedSearchbutton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
END_MESSAGE_MAP()


// CGMClientView �޽��� ó�����Դϴ�.

void CGMClientView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CGMClientView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	SetTimer(100, 200, NULL);
	SetTimer(200, 200, NULL);
    	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

// �α��� ��ư Ŭ���� 
void CGMClientView::OnBnClickedLoginbutton()
{
	// �ش� ID�� PW�� �о��
	m_LoginID.GetWindowText(m_strID);
	m_LoginPW.GetWindowText(m_strPW);

	// ���� ����
	m_clGMProcess->Connect("192.168.100.89", 11400);
}


// Excute ��ư Ŭ���� 
void CGMClientView::OnBnClickedSearchbutton()
{
	m_GMCommand.GetWindowText(m_strGMCmd);

	if( m_clGMProcess->IsConnected() && m_strGMCmd.GetLength() > 0 );
	{
		// Ŀ�ǵ� ������
		sGMRequest_GMCommand GMCmd(m_strGMCmd);
		m_clGMProcess->SendPacket((sPacketHeader*)&GMCmd);

		m_strGMCmd = "";

		//sDBRequest_BasicInfoByName 
	}
}


void CGMClientView::OnTimer(UINT nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	switch( nIDEvent )
	{
	case 100:
		{
			BOOL IsBeforeLogin = m_clGMProcess->IsLoggedIn();

			m_clGMProcess->Run();

			if( m_clGMProcess->IsConnected() &&
				m_strID.GetLength() > 0 && m_strPW.GetLength() > 0 )
			{
				// �α��� �õ�
				sGMRequest_Login Login(m_strID, m_strPW);
				m_clGMProcess->SendPacket((sPacketHeader*)&Login);
				
				m_strID = "";
				m_strPW = "";
			}

			// �α��� ���� ����
			if( IsBeforeLogin == FALSE && m_clGMProcess->IsLoggedIn() )
			{
				// �α��� â ��Ȱ��
				GetDlgItem(IDC_EDITID)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDITPW)->EnableWindow(FALSE);
				GetDlgItem(IDC_LOGINBUTTON)->EnableWindow(FALSE);
				GetDlgItem(IDC_LOGINSECTION)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATICID)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATICPW)->EnableWindow(FALSE);

				AfxMessageBox("�α��� ����");
			}
			break;
		}
	}

	CDialog::OnTimer(nIDEvent);
}

// ȭ�鿡 �ٴ����� ����ϱ�
void CGMClientView::AddInfoFromServer(const char* pszLine)
{
	CString tmp;
	m_InfoBox.GetWindowText(tmp);
	if( tmp.GetLength() > 0 )	{		tmp += "\r\n";		}
	tmp += pszLine;
	m_InfoBox.SetWindowText(tmp);
}
void CGMClientView::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
