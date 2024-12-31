// GoonzuLogView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GoonzuUserlog.h"
#include "GoonzuLogView.h"
#include ".\goonzulogview.h"
#include "ItemExplain.h"
#include "ODBC/RichODBC.h" 
#include "../../GoonZuWorld/common/Item/ItemCommon/cltItem.h"
#include "GoonzuUserlogDlg.h"
#include "VillageManager/VillageManager.h"
#include "LogUnit.h"

// CGoonzuLogView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGoonzuLogView, CDialog)
CGoonzuLogView::CGoonzuLogView(CWnd* pParent /*=NULL*/)
	: CDialog(CGoonzuLogView::IDD, pParent)
	, m_subitem(0)
	, m_ChildProcess(NULL)
	, m_siMaxRowcount(0)
	, m_siCurRow(0)
	, m_iSortColumn(-1)
	, m_bSortAscending(TRUE)
	, m_bExit(FALSE)
{
	m_pItemManager = new cltItemManagerCommon();
	m_pItemManager->Create();
	m_pItemExplain = new CItemExplain();
	m_pItemExplain->Create( IDD_DIALOG2, this);
	m_pItemExplain->ShowWindow(SW_HIDE);

	m_ChildHwnd = NULL;
	m_hLoadThread = NULL;
	m_hQueryThread = NULL;

	// �����θ� ��´�.
	GetModuleFileName(NULL, m_strAppFullPath, sizeof(m_strAppFullPath));

	// Accelerator�� �ε��Ѵ�.
	m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_USERLOG_ACCEL));
}

CGoonzuLogView::~CGoonzuLogView()
{
	if ( m_pItemManager )
	{
		delete m_pItemManager;
		m_pItemManager = NULL;
	}

	if(m_pItemExplain)
	{
		delete m_pItemExplain;
		m_pItemExplain= NULL;
	}

	if(m_ChildProcess != NULL)
		CloseHandle(m_ChildProcess);

	if(m_hQueryThread) CloseHandle(m_hQueryThread);
	if(m_hLoadThread) CloseHandle(m_hLoadThread);
}

void CGoonzuLogView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO8, m_SearchServer);
	DDX_Control(pDX, IDC_EDIT2, m_UserEdit);
	DDX_Control(pDX, IDC_EDIT3, m_ItemEdit);
	DDX_Control(pDX, IDC_BUTTON3, m_SearchButton3);
	DDX_Control(pDX, IDC_LIST2, m_ListView);
	DDX_Control(pDX, IDC_COMBO9, m_SearchItem);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_EDIT6, m_ViewEdit);
	DDX_Control(pDX, IDC_EDIT1, m_SearchItemEdit);
	DDX_Control(pDX, IDC_EDIT4, m_BinaryEdit);
	DDX_Control(pDX, IDC_EDIT5, m_UniqueEdit);
	DDX_Control(pDX, IDC_BUTTON_SAVEFILE, m_ButtonSaveFile);
	DDX_Control(pDX, IDC_EDIT_ROWCOUNT, m_RowcountEdit);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_SearchEdit);
	DDX_Control(pDX, IDC_EDIT_USER_SEARCH, m_UserSearchEdit);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_DTDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME, m_DTStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME, m_DTEndTime);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonGetUnique);
}


void CGoonzuLogView::SetCombo()
{
	COleDateTime time = COleDateTime::GetCurrentTime();
	
	switch (m_siServerSelect)
	{
	case NDOORS:
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("����");
		m_SearchServer.AddString("���걺");
		break;
	case NETMARBLE:
		m_SearchServer.AddString("���");
		m_SearchServer.AddString("�Ѷ�");
		m_SearchServer.AddString("�ݰ�");
		break;
	}
	m_SearchServer.SetCurSel(0);

	m_SearchItem.AddString("����");
	m_SearchItem.AddString("������");
	m_SearchItem.SetCurSel(0);

	m_DTDate.SetTime(time);
	m_DTStartTime.SetTime(time);
	m_DTEndTime.SetTime(time);
}

void CGoonzuLogView::SetListView()
{
	
	char* cListHeader[]={"��ȣ","��¥","���","�ൿ��","�ǵ���","����������ũ","��������"};
	int nHeaderWidth[]={56,138,155,135,135,178,0};
	
	LV_COLUMN lvColomn;
	lvColomn.mask =LVCF_FMT |  LVCF_TEXT | LVCF_WIDTH;
	
	
	for(int i=0; i<7;i++)
	{
		m_ListView.InsertColumn(i, cListHeader[i]);
		m_ListView.SetColumnWidth(i, nHeaderWidth[i]);
		m_subitem++;
	}
}

void CGoonzuLogView::SetFilterBox()
{
	InsertFilter(0, "��ü");
	InsertFilter(1, "�����۸��ŷ�");
	InsertFilter(2, "����");
	InsertFilter(3, "�α�/�α׾ƿ�");
	InsertFilter(4, "���ΰŷ�");
	InsertFilter(5, "��ȯ���ŷ�");

	m_ListView.SetExtendedStyle
		(m_ListView.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

	m_ListBox.SetCurSel(0);
}

void CGoonzuLogView::ShowUserLog()
{
	SetFilterBox();
	SetCombo();
	SetListView();
}

BEGIN_MESSAGE_MAP(CGoonzuLogView, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnLvnItemchangedList2)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnLvnColumnclickList2)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_EN_CHANGE(IDC_EDIT6, OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON_UNSELECTED_DELETE, OnBnClickedButtonUnselectedDelete)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SENDCHILDWINDOW, OnBnClickedButtonSendchildwindow)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnNMDblclkList2)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON_SELECTED_DELETE, OnBnClickedButtonSelectedDelete)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST2, OnLvnKeydownList2)
	ON_EN_SETFOCUS(IDC_EDIT1, OnEnSetfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT4, OnEnSetfocusEdit4)
	ON_EN_SETFOCUS(IDC_EDIT5, OnEnSetfocusEdit5)
	ON_EN_SETFOCUS(IDC_EDIT_SEARCH, OnEnSetfocusEditSearch)
	ON_EN_SETFOCUS(IDC_EDIT2, OnEnSetfocusEdit2)
	ON_EN_SETFOCUS(IDC_EDIT3, OnEnSetfocusEdit3)
	ON_EN_SETFOCUS(IDC_EDIT_USER_SEARCH, OnEnSetfocusEditUserSearch)
	ON_LBN_SETFOCUS(IDC_LIST1, OnLbnSetfocusList1)
	ON_COMMAND(ID_EXIT_APP, OnExitApp)
	ON_COMMAND(ID_OPEN_FILE, OnOpenFile)
	ON_COMMAND(ID_SAVE_FILE, OnSaveFile)
	ON_COMMAND(ID_SEND_DATA, OnSendData)
	ON_COMMAND(ID_DELETE_SELECTED, OnDeleteSelected)
	ON_COMMAND(ID_DELETE_UNSELECTED, OnDeleteUnselected)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DATEVARY, OnBnClickedButtonDatevary)
	ON_EN_SETFOCUS(IDC_EDIT_DATEVARY, OnEnSetfocusEditDatevary)
END_MESSAGE_MAP()


// CGoonzuLogView �޽��� ó�����Դϴ�.

void CGoonzuLogView::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	unsigned uThreadId;

	m_hQueryThread = (HANDLE)_beginthreadex(NULL, 0, QueryLogData, this, 0, &uThreadId);
	if(m_hQueryThread == NULL)
	{
		AfxMessageBox("CreateThread����");
	}
}

unsigned __stdcall CGoonzuLogView::QueryLogData(LPVOID lpParam)
{
	CGoonzuLogView *pLogView = (CGoonzuLogView*)lpParam;

	CLogUnit LogUnit;
	BOOL bExecute = FALSE;
	CString szAutoSave;

	pLogView->m_ListView.DeleteAllItems();
	pLogView->m_ViewEdit.Clear();

	//--------------------------------------
	// �Է¿� ���� ����..
	//--------------------------------------
	int siLogType = 0;
	char szServerName[20] = "";
	char szPersonName[20] = "";
	char szUserSearch[MAX_SEARCH_LEN] = "";
	char text_itemunique[20]="";
	int siItemUnique = 0;
	char szStartDate[24] = "";
	char szEndDate[24] = "";
	CString szRowcount;

	COleDateTime SearchDate, StartTime, EndTime, CurrTime = COleDateTime::GetCurrentTime();
	COleDateTimeSpan TimeSpan;

	// �Էµ� �ð��� �����´�.
	pLogView->m_DTDate.GetTime(SearchDate);
	pLogView->m_DTStartTime.GetTime(StartTime);
	pLogView->m_DTEndTime.GetTime(EndTime);

	// ���۽ð��� ����ð��� �˻����� �����Ѵ�.
	StartTime.SetDateTime(SearchDate.GetYear(), SearchDate.GetMonth(), SearchDate.GetDay(), StartTime.GetHour(), StartTime.GetMinute(), 0);
	EndTime.SetDateTime(SearchDate.GetYear(), SearchDate.GetMonth(), SearchDate.GetDay(), EndTime.GetHour(), EndTime.GetMinute(), 0);

	strcpy(szStartDate, StartTime.Format("%Y-%m-%d %H:%M:00.000"));
	strcpy(szEndDate, EndTime.Format("%Y-%m-%d %H:%M:59.999"));

	// ���� �˻��ɼ��� �����´�.
	siLogType=pLogView->m_ListBox.GetCaretIndex();
	pLogView->m_UserEdit.GetWindowText(szPersonName,20);
	pLogView->m_UserSearchEdit.GetWindowText( szUserSearch, MAX_SEARCH_LEN);
	pLogView->m_SearchServer.GetWindowText(szServerName,20);
	pLogView->m_ItemEdit.GetWindowText(text_itemunique,20);

	if(pLogView->IsNumber(text_itemunique) == true)
		siItemUnique = atoi(text_itemunique);
	else
		siItemUnique = pLogView->m_pItemManager->FindUniqueFromName(text_itemunique);

	// ���������� �߸��Ǿ��ٸ� ����.
	if(pLogView->m_SearchServer.GetWindowTextLength() == 0)
		return 0;

	pLogView->DisableButton();

	// AutoSave ���ϸ��� �����.
	szAutoSave.Format("%s_%s_%d_%d_%s_%s_%s.txt"
		, szServerName, szPersonName, siItemUnique, siLogType, StartTime.Format("%Y%m%d%H%M"), EndTime.Format("%Y%m%d%H%M")
		, szUserSearch);

	// ���ϸ����� �� �� ���� ���ڸ� �����Ѵ�.
	szAutoSave.Replace("\\", "-"); szAutoSave.Replace("/", "-"); szAutoSave.Replace(":", "-"); szAutoSave.Replace("*", "-"); szAutoSave.Replace("<", "-"); szAutoSave.Replace(">", "-"); szAutoSave.Replace("|", "-");

	if(pLogView->LoadLogFile(szAutoSave))
		bExecute = FALSE;
	else
		bExecute = TRUE;

	if(bExecute)
	{
		// �ν��Ͻ� ����
		RichODBC *pDB = new RichODBC;
		// DB ����
		
		switch (pLogView->m_siServerSelect)
		{
		case NDOORS:
			pDB->Connect("SQL Server", SERVERIP, "RichLog", pLogView->m_username, pLogView->m_password);
			break;
		case NETMARBLE:
			pDB->Connect("SQL Server", NETMARBLESERVERIP, "RichLog", pLogView->m_username, pLogView->m_password);
			break;
		}

		// ���� �غ�..
		pDB->SetQuery("{call rsp_PersonalLog3 (?, ?, ?, ?, ?, ?, ?)}");

		// �Է� �Ķ��Ÿ�� ����.

		pDB->SetParam( 1, SQL_INTEGER, &siLogType, sizeof(siLogType) );
		pDB->SetParam( 2, SQL_VARCHAR, &szServerName, sizeof(szServerName) );
		pDB->SetParam( 3, SQL_VARCHAR, &szPersonName, sizeof(szPersonName) );
		pDB->SetParam( 4, SQL_INTEGER, &siItemUnique, sizeof(siItemUnique) );
		pDB->SetParam( 5, SQL_VARCHAR, &szStartDate, sizeof(szStartDate) );
		pDB->SetParam( 6, SQL_VARCHAR, &szEndDate, sizeof(szEndDate) );
		pDB->SetParam( 7, SQL_VARCHAR, &szUserSearch, sizeof(szUserSearch) );

		// ���� ����
		pDB->ExecSQL();

		// ��� ���ϱ�.
		pLogView->m_siMaxRowcount=0;

		while(pDB->FetchData()>0)
		{
			// �ε��� ���α׷��� �����Ű���ϸ� ������ ����������.
			if(pLogView->m_bExit == TRUE)
				break;

			char szItemUnique[10] = "";

			pDB->GetData( 1, LogUnit.szDate, sizeof(LogUnit.szDate) );
			pDB->GetData( 2, LogUnit.szCommand, sizeof(LogUnit.szCommand) );
			pDB->GetData( 3, LogUnit.szRetPersonName, sizeof(LogUnit.szRetPersonName) );
			pDB->GetData( 4, LogUnit.szDstPersonName, sizeof(LogUnit.szDstPersonName) );
			pDB->GetData( 5, szItemUnique, sizeof(szItemUnique) );
			pDB->GetData( 6, LogUnit.szLogTxt, sizeof(LogUnit.szLogTxt) );

			sprintf(LogUnit.szItemUnique,"%s(%s)", szItemUnique, pLogView->m_pItemManager->GetName(atoi(szItemUnique)));

			pLogView->InsertLogUnit(&LogUnit);

			if(pLogView->m_siMaxRowcount % 100 == 0)
			{
				szRowcount.Format("�˻��� : %d", pLogView->m_siMaxRowcount);
				pLogView->m_SearchButton3.SetWindowText(szRowcount);
			}
			//printf("%s, %s, %s, %s, %d, %s\n", szDate, szCommand, szRetPersonName, szDstPersonName, siRetItemUnique, szLogTxt);
		}

		// DB ��������..
		pDB->Disconnect();

		// ���似�̺�. EndTime�� ����ð��� 20�� �̻� ���̳��� �����Ѵ�(Ŭ���̾�Ʈ�ð��� �α׼����ð��� �ٸ� �� �����Ƿ� �ֱٽð��ϰ�� �߸����� �� �� ����).
		if(pLogView->m_bExit == FALSE)
		{
			TimeSpan = CurrTime - EndTime;
			if(TimeSpan.GetTotalMinutes() >= 20 && pLogView->m_siMaxRowcount > 0)
			{

				pLogView->SaveLogFile(szAutoSave, false);
			}
		}
	}

	pLogView->EnableButton();
	pLogView->ShowRowcount();
	return 0;
}

void CGoonzuLogView::ShowRowcount()
{
	CString szCount;
	szCount.Format("%d/%d", m_siCurRow, m_siMaxRowcount);
	m_RowcountEdit.SetWindowText(szCount);
}

void CGoonzuLogView::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if ( pNMLV->iItem >= 0 && ( (pNMLV->uNewState == 3 && pNMLV->uOldState == 0) || (pNMLV->uNewState == 1 && pNMLV->uOldState == 0) ) )
	{
		int nIndex = pNMLV->iItem;
		CString szLog = m_ListView.GetItemText(nIndex, 6);
		CString szItemUnique = m_ListView.GetItemText(nIndex, 5);

		// �����׸񳻿��� ����Ʈ�信 ���� ǥ���Ѵ�.
		m_ViewEdit.SetWindowText(szLog);

		// ����������ũ���� �ڵ����� �־��ش�.
		m_UniqueEdit.SetWindowText(szItemUnique.Left(szItemUnique.Find("(")));

		// �������������� �ڵ����� �־��ش�.
		int nFirst = szLog.Find("0x");
		if( nFirst >= 0 )
			m_BinaryEdit.SetWindowText(szLog.Mid(nFirst, 26));
		else
			m_BinaryEdit.SetWindowText("");

        m_siCurRow = nIndex+1;
		ShowRowcount();

		// ����������â�� �������� ������Ʈ�� �Ѵ�.
		if(m_pItemExplain->IsWindowVisible())
		{
            ShowItemInfo();
		}
	}

	*pResult = 0;
}



void CGoonzuLogView::SetAccount(char* UserID,char * PassWord )
{
	strcpy(m_username,UserID);
	strcpy(m_password,PassWord);

}
void CGoonzuLogView::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CGoonzuLogView::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CGoonzuLogView::OnBnClickedButton4()
{
	CFileDialog fileDlg(FALSE, "txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||", NULL, 0);
	if(fileDlg.DoModal() == IDOK)
	{
		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		SaveLogFile(fileDlg.GetPathName());
	}
}

void CGoonzuLogView::SaveLogFile(CString szFileName, bool bInfo)
{
	FILE *fp;
	char filename[MAX_PATH]="";
	char data1[128]="";
	char data2[128]="";
	char data3[128]="";
	char data4[128]="";
	char data5[128]="";
	char data6[128]="";

	// ������ ������ ������ �����Ѵ�.
	if(m_siMaxRowcount == 0)
		return;

	strncpy(filename, szFileName, szFileName.GetLength());

	fp=fopen(filename,"w+t");
	if(fp != NULL)
	{
		int ItemCount = m_ListView.GetItemCount();

		CString ItemStr[6];

		fprintf(fp,"����\t���\t�ൿ��\t�ǵ���\t����������ũ\t��������\n");
		for ( int i = 0; i < ItemCount; ++i )
		{
			ItemStr[0] = m_ListView.GetItemText( i, 1 );
			ItemStr[1] = m_ListView.GetItemText( i, 2 );
			ItemStr[2] = m_ListView.GetItemText( i, 3 );
			ItemStr[3] = m_ListView.GetItemText( i, 4 );
			ItemStr[4] = m_ListView.GetItemText( i, 5 );
			ItemStr[5] = m_ListView.GetItemText( i, 6 );
			fprintf(fp,"\"%s\"\t\"%s\"\t\"%s\"\t\"%s\"\t\"%s\"\t\"%s\"\n",ItemStr[0],ItemStr[1],ItemStr[2],ItemStr[3],ItemStr[4],ItemStr[5]);
		}
		fclose(fp);

		if(bInfo)
			AfxMessageBox( szFileName += "�� ����Ǿ����ϴ�" );
	}
	else
	{
		AfxMessageBox( "���� �� �� �����ϴ�." );
	}
}


void CGoonzuLogView::OnBnClickedButton1()
{
	char itemname[64]="";
	char itemedit[64]="";
	
	m_SearchItem.GetWindowText(itemname,40);
	m_SearchItemEdit.GetWindowText(itemedit,40);
	if(strcmp(itemname,"����")==0)
	{
        CVillageManager *village= new CVillageManager();

		m_SearchItemEdit.GetWindowText(itemedit,40);		
		GetDlgItem(IDC_EDIT_VIEWNAMECHANGE)->SetWindowText(village->Set(itemedit));
		if(village)
		{
			delete village;
			village=NULL;
		}
	}
	else
	{
		CString szItemUnique;
		m_SearchItemEdit.GetWindowText(itemedit,40);
		if(IsNumber(itemedit) == true)
		{
			int unique = atoi(itemedit);
			szItemUnique.Format("%s", m_pItemManager->GetName(unique));
		}
		else
		{
			szItemUnique.Format("%d", m_pItemManager->FindUniqueFromName(itemedit));
		}
		GetDlgItem(IDC_EDIT_VIEWNAMECHANGE)->SetWindowText(szItemUnique);
	}


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CGoonzuLogView::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShowItemInfo();
	m_pItemExplain->ShowWindow(SW_SHOWNA);
}

void CGoonzuLogView::ShowItemInfo()
{
	char Binaryedit[32]="";
	char Uniqueedit[32]="";
	SI32 itemunique = 0 ;

	m_BinaryEdit.GetWindowText(Binaryedit,32);
	m_UniqueEdit.GetWindowText(Uniqueedit,32);

	itemunique = atoi(Uniqueedit);

	if ( Binaryedit[0] == '0' && Binaryedit[1] == 'x' )
	{
		for ( int i = 0 ; i < 12 ; i ++ )
		{
			char buf[2] = "" ;
			memcpy(buf,&Binaryedit[i*2+2],sizeof(char)*2);

			int n = 0;
			for(int j = 0; j < 2; j++)
			{
				char c = toupper(buf[j]);
				if(c < '0' || c > 'F' || (c > '9' && c < 'A'))
					break;
				int d = c - '0';
				if(d > 9) d -= 7;
				n = n * 16 + d;
			}

			if ( i < 4 )
				Uniqueedit[(i%4)+4] = (char)n ;
			else if ( i < 8 )
				Uniqueedit[(i%4)+8] = (char)n ;
			else if ( i < 12 )
				Uniqueedit[(i%4)+12] = (char)n ;
		}
	}
	else
	{
		for ( int i = 0 ; i < 12 ; i ++ )
		{
			char buf[2] = "" ;
			memcpy(buf,&Binaryedit[i*2],sizeof(char)*2);

			int n = 0;
			for(int j = 0; j < 2; j++)
			{
				char c = toupper(buf[j]);
				if(c < '0' || c > 'F' || (c > '9' && c < 'A'))
					break;
				int d = c - '0';
				if(d > 9) d -= 7;
				n = n * 16 + d;
			}

			if ( i < 4 )
				Uniqueedit[7-(i%4)] = (char)n ;
			else if ( i < 8 )
				Uniqueedit[11-(i%4)] = (char)n ;
			else if ( i < 12 )
				Uniqueedit[15-(i%4)] = (char)n ;
		}
	}

	cltItem pclItem ;
	pclItem.Set(Uniqueedit);
	pclItem.siUnique = itemunique;
	pclItem.siItemNum = 1 ;

	char buffer[1024] = "" ;


	//m_pItemManager->GetExplain(pclItem.siUnique,buffer);
	m_pItemManager->GetExplain(&pclItem,buffer, true);

	m_pItemExplain->m_ExplainEdit.SetWindowText(buffer);
}

void CGoonzuLogView::OnCancel()
{
	// �� ������ ����
	m_bExit = TRUE;

	if ( m_pItemExplain )
	{
		delete m_pItemExplain;
		m_pItemExplain = NULL;
	}

	CDialog::OnCancel();
	((CGoonzuUserlogDlg *)AfxGetApp()->GetMainWnd())->ExitProcess();

	return;
}

void CGoonzuLogView::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CGoonzuLogView::OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int siTotItems = m_ListView.GetItemCount();
	m_bSortAscending = (pNMLV->iSubItem == m_iSortColumn ? !m_bSortAscending : TRUE);
	m_iSortColumn = pNMLV->iSubItem;

	// Callback Item Setting
	for(int i=0; i<siTotItems; i++) 
	{
		m_ListView.SetItemData( i,  i);
	}

	m_ListView.SortItems( CompareFunction, (LPARAM)(CGoonzuLogView*)this );

	*pResult = 0;
}

bool CGoonzuLogView::IsNumber(LPCTSTR pszText)
{
	ASSERT_VALID_STRING( pszText );

	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;

	return true;
}


int CGoonzuLogView::NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 )
{
	ASSERT_VALID_STRING( pszNumber1 );
	ASSERT_VALID_STRING( pszNumber2 );

	const int iNumber1 = atoi( pszNumber1 );
	const int iNumber2 = atoi( pszNumber2 );

	if( iNumber1 < iNumber2 )
		return -1;

	if( iNumber1 > iNumber2 )
		return 1;

	return 0;
}


bool CGoonzuLogView::IsDate( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );

	// format should be 99/99/9999.

	if( lstrlen( pszText ) != 10 )
		return false;

	return _istdigit( pszText[ 0 ] )
		&& _istdigit( pszText[ 1 ] )
		&& pszText[ 2 ] == _T('/')
		&& _istdigit( pszText[ 3 ] )
		&& _istdigit( pszText[ 4 ] )
		&& pszText[ 5 ] == _T('/')
		&& _istdigit( pszText[ 6 ] )
		&& _istdigit( pszText[ 7 ] )
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] );
}

int CGoonzuLogView::DateCompare( const CString& strDate1, const CString& strDate2 )
{
	const int iYear1 = atoi( strDate1.Mid( 6, 4 ) );
	const int iYear2 = atoi( strDate2.Mid( 6, 4 ) );

	if( iYear1 < iYear2 )
		return -1;

	if( iYear1 > iYear2 )
		return 1;

	const int iMonth1 = atoi( strDate1.Mid( 3, 2 ) );
	const int iMonth2 = atoi( strDate2.Mid( 3, 2 ) );

	if( iMonth1 < iMonth2 )
		return -1;

	if( iMonth1 > iMonth2 )
		return 1;

	const int iDay1 = atoi( strDate1.Mid( 0, 2 ) );
	const int iDay2 = atoi( strDate2.Mid( 0, 2 ) );

	if( iDay1 < iDay2 )
		return -1;

	if( iDay1 > iDay2 )
		return 1;

	return 0;
}

int CALLBACK CGoonzuLogView::CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
	CGoonzuLogView* pLogView = (CGoonzuLogView*)lParamData;

	CString pszText1 = pLogView->m_ListView.GetItemText((int)lParam1, pLogView->m_iSortColumn);
	CString pszText2 = pLogView->m_ListView.GetItemText((int)lParam2, pLogView->m_iSortColumn);

	if(pszText1.GetLength() == 0)
		pszText1 = " ";
	if(pszText2.GetLength() == 0)
		pszText2 = " ";

	if(pLogView->m_iSortColumn == 0)
		return pLogView->m_bSortAscending ? pLogView->NumberCompare( pszText1, pszText2 ) : pLogView->NumberCompare( pszText2, pszText1 );
	else
        return pLogView->m_bSortAscending ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
/*
	if( IsNumber( pszText1 ) )
		return m_bSortAscending ? NumberCompare( pszText1, pszText2 ) : NumberCompare( pszText2, pszText1 );
	else if( IsDate( pszText1 ) )
		return m_bSortAscending ? DateCompare( pszText1, pszText2 ) : DateCompare( pszText2, pszText1 );
	else
		// text.
		return m_bSortAscending ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
*/
}

void CGoonzuLogView::OnBnClickedButtonSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString szSearch;
	int siStart = 0, siFind = 0;

	DisableButton();

	// ���õ��ִ¿��� ������ ���������Ѵ�.
	int nIndex = 0;
	nIndex = m_ListView.GetNextItem(-1, LVNI_SELECTED);
	while(nIndex != -1)
	{
		m_ListView.SetItemState(nIndex, 0, LVNI_SELECTED | LVNI_FOCUSED );
		nIndex = m_ListView.GetNextItem(nIndex, LVNI_SELECTED);
	}

	// �˻�����
	m_SearchEdit.GetWindowText(szSearch);

	if(szSearch.GetLength() == 0)
		return;

	siFind = ListFindItem(szSearch, siStart);

	EnableButton();

	CString szMsg;
	if(siFind > 0)
		szMsg.Format("%d�� ã��", siFind);
	else
		szMsg.Format("ã�� �� ����");

	AfxMessageBox(szMsg);
}

int CGoonzuLogView::ListFindItem(CString szSearch, int siStart)
{
	int iCount;
	int	siFind = 0;
	iCount = m_ListView.GetItemCount();    // ����Ʈ�� ��ü ����

	for(int i=siStart; i<iCount; i++)
	{
		for(int j=2; j<m_subitem; j++)
		{
			CString szItemText = m_ListView.GetItemText(i, j);
			if(szItemText.MakeLower().Find(szSearch.MakeLower()) >= 0)
			{
				m_ListView.SetItemState(i, LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED );
				m_ListView.SetFocus();
				siFind++;
				break;
			}
		}
	}
	return siFind;
}

void CGoonzuLogView::OnEnChangeEdit6()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CGoonzuLogView::OnBnClickedButtonUnselectedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iMaxCount = m_ListView.GetItemCount();
	for(int nIndex = iMaxCount-1; nIndex >= 0; nIndex--)
	{
		if(m_ListView.GetItemState( nIndex, LVNI_SELECTED) != LVNI_SELECTED)
		{
			m_ListView.DeleteItem(nIndex);
			m_siMaxRowcount--;
		}
	}
}

void CGoonzuLogView::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog fileDlg(TRUE, "txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||", NULL, 0);
	if(fileDlg.DoModal() == IDOK)
	{
		// ���� ��³����� �����.
		m_ListView.DeleteAllItems();
		m_ViewEdit.SetWindowText("");

		m_szFileName = fileDlg.GetPathName();

		unsigned uThreadId;

		m_hLoadThread = (HANDLE)_beginthreadex(NULL, 0, LoadLogFile, this, 0, &uThreadId);
		if(m_hLoadThread == NULL)
		{
			AfxMessageBox("CreateThread����");
		}

		ShowRowcount();
	}
}

unsigned __stdcall CGoonzuLogView::LoadLogFile(LPVOID lpParam)
{
	CGoonzuLogView *pLogView = (CGoonzuLogView*)lpParam;

	pLogView->LoadLogFile(pLogView->m_szFileName);
	return 0;
}

bool CGoonzuLogView::LoadLogFile(CString szFileName)
{
	char strbuffer[1024] = "";
	CString szRowcount;
	CLogUnit LogUnit;

	m_siMaxRowcount = 0;
	DisableButton();

	FILE *fp = fopen(szFileName, "r");
	if(fp == NULL)
		return false;

	while(fgets(strbuffer, 1024, fp) != NULL)
	{
		// �ε��� ���α׷��� �����Ű���ϸ� ������ ����������.
		if(m_bExit == TRUE)
			break;

		LogUnit.Init();
		
		int point = 0;
		int startpoint = 0;
		if(GetStringFromLogfile(&strbuffer[point], LogUnit.szDate, &point, sizeof(LogUnit.szDate)) == false) continue;
		if(GetStringFromLogfile(&strbuffer[point], LogUnit.szCommand, &point, sizeof(LogUnit.szCommand)) == false) continue;
		if(GetStringFromLogfile(&strbuffer[point], LogUnit.szRetPersonName, &point, sizeof(LogUnit.szRetPersonName)) == false) continue;
		if(GetStringFromLogfile(&strbuffer[point], LogUnit.szDstPersonName, &point, sizeof(LogUnit.szDstPersonName)) == false) continue;
		if(GetStringFromLogfile(&strbuffer[point], LogUnit.szItemUnique, &point, sizeof(LogUnit.szItemUnique)) == false) continue;
		if(GetStringFromLogfile(&strbuffer[point], LogUnit.szLogTxt, &point, sizeof(LogUnit.szLogTxt)) == false) continue;
		
		InsertLogUnit(&LogUnit);

		if(m_siMaxRowcount % 100 == 0)
		{
			szRowcount.Format("�˻��� : %d", m_siMaxRowcount);
			m_SearchButton3.SetWindowText(szRowcount);
		}

	}

	if(fp != NULL)
		fclose(fp);

	EnableButton();

	return true;
}

void CGoonzuLogView::OnBnClickedButtonSendchildwindow()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DisableButton();
	OpenChildProcess();
	SendSelectedLogUnit();
	EnableButton();
}

void CGoonzuLogView::OpenChildProcess()
{
	STARTUPINFO si={0,};
	PROCESS_INFORMATION pi;
	char strCmdLine[512] = "";
	DWORD ExitCode;

	GetExitCodeProcess(m_ChildProcess, &ExitCode);
	if(ExitCode != STILL_ACTIVE)
	{
		if(m_ChildProcess != NULL)
		{
			m_ChildHwnd = NULL;
			CloseHandle(m_ChildProcess);
		}

		strcat(strCmdLine, " ");
		strcat(strCmdLine, m_username);
		strcat(strCmdLine, " ");
		strcat(strCmdLine, m_password);

		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = 0;

		if(CreateProcess( m_strAppFullPath, strCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == FALSE)
		{
			AfxMessageBox("�ڽ����μ����� �� �� �����ϴ�.");
			return;
		}

		m_dwProcessId = pi.dwProcessId;
		m_ChildProcess = pi.hProcess;
		
		// ���μ����� ������ ���µ� ������ ��ٸ���.
		WaitForInputIdle(pi.hProcess, INFINITE);
		Sleep(1000 );

		// HWND�� ��´�.
		EnumWindows(FindChildWindow, (LPARAM)(CGoonzuLogView*)this);
	}
}

void CGoonzuLogView::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedButton2();
	*pResult = 0;
}

void CGoonzuLogView::InsertLogUnit(CLogUnit *pLogUnit)
{
	char buffer[64]="";

	LV_ITEM LI;
	LI.mask=LVIF_TEXT;
	LI.state=0;
	LI.stateMask=0;

	sprintf(buffer,"%d",m_siMaxRowcount+1);
	LI.iItem=m_siMaxRowcount;
	LI.iSubItem=0;
	LI.pszText=buffer;
	LI.lParam = m_siMaxRowcount;
	m_ListView.InsertItem(&LI);

	LI.iSubItem=1;
	LI.pszText=pLogUnit->szDate;
	m_ListView.SetItem(&LI);

	LI.iSubItem=2;
	LI.pszText=pLogUnit->szCommand;
	m_ListView.SetItem(&LI);

	LI.iSubItem=3;
	LI.pszText=pLogUnit->szRetPersonName;
	m_ListView.SetItem(&LI);

	LI.iSubItem=4;
	LI.pszText=pLogUnit->szDstPersonName;
	m_ListView.SetItem(&LI);

	LI.iSubItem=5;
	LI.pszText=pLogUnit->szItemUnique;
	m_ListView.SetItem(&LI);

	LI.iSubItem=6;
	LI.pszText=pLogUnit->szLogTxt;
	m_ListView.SetItem(&LI);

	m_siMaxRowcount++;
}


void CGoonzuLogView::DisableButton()
{
	GetDlgItem(IDC_LIST2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SENDCHILDWINDOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SELECTED_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UNSELECTED_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVEFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_VIEWNAMECHANGE)->EnableWindow(FALSE);
	m_SearchButton3.SetWindowText("�˻���");
}

void CGoonzuLogView::EnableButton()
{
	GetDlgItem(IDC_LIST2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SENDCHILDWINDOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SELECTED_DELETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UNSELECTED_DELETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SAVEFILE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_VIEWNAMECHANGE)->EnableWindow(TRUE);
	m_SearchButton3.SetWindowText("�˻��ϱ�");
	m_siCurRow = 0;
	ShowRowcount();
}

void CGoonzuLogView::SendSelectedLogUnit()
{
	COPYDATASTRUCT cds;
	CLogUnit LogUnit;
	CString szTotalSend;
	int nIndex = 0, siSendCount = 0;

	// ���콺�� ���õ� �׸��� ������.
	nIndex = m_ListView.GetNextItem(-1, LVNI_SELECTED);
	while(nIndex != -1)
	{
		m_ListView.GetItemText(nIndex, 1, LogUnit.szDate, sizeof(LogUnit.szDate));
		m_ListView.GetItemText(nIndex, 2, LogUnit.szCommand, sizeof(LogUnit.szCommand));
		m_ListView.GetItemText(nIndex, 3, LogUnit.szRetPersonName, sizeof(LogUnit.szRetPersonName));
		m_ListView.GetItemText(nIndex, 4, LogUnit.szDstPersonName, sizeof(LogUnit.szDstPersonName));
		m_ListView.GetItemText(nIndex, 5, LogUnit.szItemUnique, sizeof(LogUnit.szItemUnique));
		m_ListView.GetItemText(nIndex, 6, LogUnit.szLogTxt, sizeof(LogUnit.szLogTxt));

		cds.dwData = 0;
		cds.cbData = sizeof(CLogUnit);
		cds.lpData = &LogUnit;
		::SendMessage(m_ChildHwnd, WM_COPYDATA, (WPARAM)AfxGetInstanceHandle(), (LPARAM)&cds);

		siSendCount++;
		// �׽�Ʈ�ڵ�.. �ڱ��ڽſ��� ������.
		//::SendMessage(GetSafeHwnd(), WM_COPYDATA, (WPARAM)AfxGetInstanceHandle(), (LPARAM)&cds);

		nIndex = m_ListView.GetNextItem(nIndex, LVNI_SELECTED);
	}
}

int CALLBACK CGoonzuLogView::FindChildWindow(HWND hwnd, LPARAM lParam)
{
	DWORD dwID;
	char szText[100];
	CGoonzuLogView *pLogView = (CGoonzuLogView*)lParam;

	GetWindowThreadProcessId(hwnd, &dwID);

	if(dwID == pLogView->m_dwProcessId)
	{
		// ���� ProcessID�� ���� �ڵ鸸 10���� ���Դ�. ���߿��� ���� ����ؾ��� �ڵ���?
		// ĸ���� �����ؼ� GoonzuUserLog�� �Ǿ��ִ³��� ���� �ڵ�
		::GetWindowTextA(hwnd, szText, 100);
		if(strcmp("GoonzuUserLog", szText) == 0)
		{
			pLogView->m_ChildHwnd = hwnd;
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CGoonzuLogView::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CLogUnit LogUnit;
	memcpy(&LogUnit, pCopyDataStruct->lpData, sizeof(CLogUnit));

	InsertLogUnit(&LogUnit);

	ShowRowcount();	
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CGoonzuLogView::OnBnClickedButtonSelectedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex = 0;
	nIndex = m_ListView.GetNextItem(-1, LVNI_SELECTED);
	while(nIndex != -1)
	{
		m_ListView.DeleteItem(nIndex);
		m_siMaxRowcount--;
		nIndex = m_ListView.GetNextItem(nIndex-1, LVNI_SELECTED);
	}
}

BOOL CGoonzuLogView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CString szTimeformatStr = _T(" HH�� mm��");
	m_DTStartTime.SetFormat(szTimeformatStr);
	m_DTEndTime.SetFormat(szTimeformatStr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGoonzuLogView::InsertFilter(int nIndex, char *strFilter)
{
//	m_ListBox.AddString((LPCTSTR)strFilter);
	m_ListBox.InsertString(nIndex, strFilter);
}

bool CGoonzuLogView::GetStringFromLogfile(char *source, char *out, int *index, int size)
{
	char *pdst = NULL;
	char ch = '"';
	int nResult = -1, nStart = -1, nEnd = -1;

	pdst = strchr( source, ch );
	nStart = (int)(pdst - source + 1);
	if(pdst == NULL)
		return false;

	pdst = strchr( &source[nStart], ch );
	nEnd = (int)(pdst - &source[nStart] + 1);
	if(pdst == NULL)
		return false;

	memcpy(out, &source[nStart], (nEnd-1) > size ? size : (nEnd-1));
	*index += (nEnd + nStart);
	return true;
}

void CGoonzuLogView::OnLvnKeydownList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(pLVKeyDow->wVKey == VK_DELETE)
	{
		OnBnClickedButtonSelectedDelete();
	}
	*pResult = 0;
}

void CGoonzuLogView::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// OnOk�� �ּ�ó���Ͽ� Default ��ư�� ���»��¿��� ���͸� �������� â�� ������ ��츦 ���´�.
	//CDialog::OnOK();
}

void CGoonzuLogView::OnEnSetfocusEdit1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON1);
}

void CGoonzuLogView::OnEnSetfocusEdit4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON2);
}

void CGoonzuLogView::OnEnSetfocusEdit5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON2);
}

void CGoonzuLogView::OnEnSetfocusEditSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON_SEARCH);
}

void CGoonzuLogView::OnEnSetfocusEdit2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON3);
}

void CGoonzuLogView::OnEnSetfocusEdit3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON3);
}

void CGoonzuLogView::OnEnSetfocusEditUserSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON3);
}

void CGoonzuLogView::OnLbnSetfocusList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON3);
}

void CGoonzuLogView::OnExitApp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// ������ ���� Ȯ��
	OnCancel();
}

void CGoonzuLogView::OnOpenFile()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedButtonLoad();
}

void CGoonzuLogView::OnSaveFile()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedButton4();
}

void CGoonzuLogView::OnSendData()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedButtonSendchildwindow();
}

void CGoonzuLogView::OnDeleteSelected()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedButtonSelectedDelete();
}

void CGoonzuLogView::OnDeleteUnselected()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedButtonUnselectedDelete();
}

BOOL CGoonzuLogView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// ESC�� ����Ǵ°� ����
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;

	// �޴� ����Ű ó��
	if(m_hAccel) {
		if( ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg ) ) {
			return (TRUE);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CGoonzuLogView::OnBnClickedButtonDatevary()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString szDateVary;
	CString szGameTime;
	SI32	siDateVary = 0;
	UI32	uiYear = 0, uiMonth = 0, uiDay = 0;
	GetDlgItem(IDC_EDIT_DATEVARY)->GetWindowText(szDateVary);

	siDateVary = atoi(szDateVary);

	uiYear  = siDateVary / (12* 30);
	siDateVary %= (12* 30);

	uiMonth = siDateVary / 30 + 1;
	siDateVary %= 30;

	uiDay		= siDateVary + 1;

	szGameTime.Format("%d�� %d�� %d��", uiYear, uiMonth, uiDay);
	GetDlgItem(IDC_EDIT_GAMETIME)->SetWindowText(szGameTime);
}

void CGoonzuLogView::OnEnSetfocusEditDatevary()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage (DM_SETDEFID, IDC_BUTTON_DATEVARY);
}
