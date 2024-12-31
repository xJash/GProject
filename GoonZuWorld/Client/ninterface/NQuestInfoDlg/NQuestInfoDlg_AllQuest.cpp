#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../Client.h"
#include "Char/CharManager/CharManager.h"
#include "../common/SystemNPC/SystemNPC.h"

#include "NQuestInfoDlg_AllQuest.h"


CNQuestInfoDlg_AllQuest::CNQuestInfoDlg_AllQuest() : CDialogController()
{
	for ( SI32 siIndex=0; siIndex<Const_Max_Category_Button; ++siIndex )
	{
		m_pclButton[ siIndex ] = NULL;
	}

	m_pclList = NULL;

}

CNQuestInfoDlg_AllQuest::~CNQuestInfoDlg_AllQuest()
{
	for ( SI32 siIndex=0; siIndex<Const_Max_Category_Button; ++siIndex )
	{
		SAFE_DELETE( m_pclButton[siIndex] );
	}

	SAFE_DELETE( m_pclList );
}

void CNQuestInfoDlg_AllQuest::Create(CControllerMgr* pParent)
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		return;
	}

	//-- ���� ��ü���� ����
	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NQuestInfoDlg/DLG_NQuestInfo_AllQuest.ddf" ) );
	file.CreateChildDialog( this, NQUESTINFODLG_ALLQUEST, TEXT( "dialog_allquest" ), StaticQuestInfoDlg_AllQuestProc, pParent );


	//-- �޼����� ����
	NEWCLIST( m_pclList );			file.CreateControl( m_pclList,		NQUESTINFO_ALLQUEST_LISTBOX_LIST,		TEXT("listbox_list") );
	NEWCBUTTON( m_pclButton[0] );	file.CreateControl( m_pclButton[0], NQUESTINFO_ALLQUEST_BUTTON_BEGINNER,	TEXT("button_beginner") );
	NEWCBUTTON( m_pclButton[1] );	file.CreateControl( m_pclButton[1], NQUESTINFO_ALLQUEST_BUTTON_MANUFACTURE,	TEXT("button_manufacture") );
	NEWCBUTTON( m_pclButton[2] );	file.CreateControl( m_pclButton[2], NQUESTINFO_ALLQUEST_BUTTON_WORLD,		TEXT("button_world") );


	//-- ��Ʈ�� ����
	SI16 siHeader0 = 80;
	SI16 siHeader1 = (m_pclList->GetWidth() - siHeader0) / 2;
	SI16 siHeader2 = siHeader1;
	

	m_pclList->SetColumn( 0, siHeader0, GetTxtFromMgr(6087) );
	m_pclList->SetColumn( 1, siHeader1, GetTxtFromMgr(647) );
	m_pclList->SetColumn( 2, siHeader2, GetTxtFromMgr(1611) );
	m_pclList->SetBorder( true );
	m_pclList->SetBKColorUse( true );
	m_pclList->SetTextPrintOption( DT_CENTER | DT_VCENTER );
	m_pclList->Refresh();

	//-- �⺻ �ʱ� ����
	// ��ư�� �⺻ ��ġ�� ����Ѵ�
	for ( SI32 siIndex=0; siIndex<Const_Max_Category_Button; ++siIndex )
	{
		m_siButtonPosY[ siIndex ] = m_pclButton[ siIndex ]->GetY();
	}

	SelectCategory( NQUESTINFO_ALLQUEST_BUTTON_BEGINNER );

}

void CALLBACK CNQuestInfoDlg_AllQuest::StaticQuestInfoDlg_AllQuestProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNQuestInfoDlg_AllQuest *pThis = (CNQuestInfoDlg_AllQuest*) pControllerMgr;
	pThis->NQuestInfoDlg_AllQuestProc( nEvent, nControlID, pControl );
}

void CALLBACK CNQuestInfoDlg_AllQuest::NQuestInfoDlg_AllQuestProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{
	switch (nControlID)
	{
		case NQUESTINFO_ALLQUEST_BUTTON_BEGINNER:
		case NQUESTINFO_ALLQUEST_BUTTON_MANUFACTURE:
		case NQUESTINFO_ALLQUEST_BUTTON_WORLD:
			{
				SelectCategory( nControlID );
			}
			break;

	}
}

void CNQuestInfoDlg_AllQuest::Action()
{
	// Hide�����϶��� ó������ �ʴ´�
	if ( false == IsShow() )
	{
		return;
	}

}

void CNQuestInfoDlg_AllQuest::Show()
{
	CControllerMgr::Show( true );

}

void CNQuestInfoDlg_AllQuest::Hide()
{
	CControllerMgr::Show( false );
}

void CNQuestInfoDlg_AllQuest::SelectCategory( SI32 siControlID )
{
	SI32 siNowIndex = siControlID - NQUESTINFO_ALLQUEST_BUTTON_BEGINNER;
	if ((0 > siNowIndex) || (Const_Max_Category_Button <= siNowIndex) )
	{
		return;
	}
	
	ChangeList( siNowIndex );
	
	SI16 siAddY = 0;

	for ( SI32 siIndex=0; siIndex<Const_Max_Category_Button; ++siIndex )
	{
		SI16 siNowPostionY	= m_siButtonPosY[ siIndex ] + siAddY;

		m_pclButton[ siIndex ]->SetY( siNowPostionY );
		m_pclButton[ siIndex ]->SetFontIndex( 0 );

		// ���� ���� ���� ��ư�� ���� ó���ϴ� ��ư�� ���� ���̶��
		if ( siIndex == siNowIndex )
		{
			m_pclButton[ siIndex ]->SetFontIndex( 12 );
			// ����Ʈ�� �̵���Ű��
			m_pclList->SetY( siNowPostionY + m_pclButton[siIndex]->GetHeight() );
			// ����Ʈ�� ���� ��ŭ�� ���� ó���ϴ� ��ư�� Y pon�� ����(+4�� ���̶�� ��)
			siAddY = m_pclList->GetHeight() + 4;
		}

	}

	// ����Ʈ�� ��ġ�� �ٲ�����Ƿ� �ٽ��ѹ� ��ġ�� ����� �ش�
	CalcListHeight();

}

void CNQuestInfoDlg_AllQuest::ChangeList( SI32 siIndex )
{
	if ( (0 > siIndex) || (Const_Max_Category_Button <= siIndex) )
	{
		return;
	}
	
	SI32 siCategory = CATEGORY_NONE;
	switch ( siIndex )
	{
		case 0: siCategory = CATEGORY_BEGINNER;		break;
		case 1: siCategory = CATEGORY_MANUFACTURE;	break;
		case 2: siCategory = CATEGORY_WORLD;		break;
		default: return;
	}

	cltSystemNPC clSystemNPCList[MAX_SYSTEM_NPC_NUMBER];
	if ( false == pclClient->pclSystemNPCManager->GetSystemNPCListFormCategory(siCategory, clSystemNPCList, MAX_SYSTEM_NPC_NUMBER) )
	{
		return ;
	}

	stListBoxItemData listBoxItemDate;

	m_pclList->Clear();

	for ( SI32 siCount=0; siCount<MAX_SYSTEM_NPC_NUMBER; ++siCount )
	{
		cltSystemNPC* pclSystemNPC( &clSystemNPCList[siCount] );
		if ( 0 >= pclSystemNPC->m_siKind )
		{
			break;
		}

		TCHAR* pszNPCName		= (TCHAR*)pclClient->pclKindInfoSet->GetName( pclSystemNPC->m_siKind );
		TCHAR* pszSimpleExplain	= GetTxtFromMgr( pclSystemNPC->m_siSimpleExplainNum );
		TCHAR* pszMapName		= GetTxtFromMgr( pclSystemNPC->m_siLocationNum );

		if ( (NULL == pszNPCName) || (NULL == pszSimpleExplain) || (NULL == pszMapName) )
		{
			continue;
		}

		listBoxItemDate.Init();

		listBoxItemDate.Set(0, pszNPCName);
		listBoxItemDate.Set(1, pszSimpleExplain);
		listBoxItemDate.Set(2, pszMapName);

		m_pclList->AddItem( &listBoxItemDate );
	}
	
	CalcListHeight();
}

void CNQuestInfoDlg_AllQuest::CalcListHeight( void )
{
	SI16 siHeaderHeight	= 15;
	SI16 siRowHeight	= m_pclList->GetLineHeight();

	SI32 siNowHeight	= (m_pclList->GetListNum() * siRowHeight) + siHeaderHeight;
	SI32 siMaxHeight	= (siRowHeight * Const_Max_ListBox_Item) + siHeaderHeight;

	SI16 siListX		= m_pclList->GetX();
	SI16 siListY		= m_pclList->GetY();
	SI16 siListWidth	= m_pclList->GetWidth();

	// Max ���̺��� ���ٸ� Max���̷� ����
	if ( siNowHeight > siMaxHeight )
	{
		m_pclList->SetControllerPos( siListX, siListY, siListWidth, siMaxHeight, siListWidth, siMaxHeight );
	}
	else
	{
		m_pclList->SetControllerPos( siListX, siListY, siListWidth, siNowHeight, siListWidth, siNowHeight );
	}

	// ���̰� ���Կ� ���� ��ũ�ѵ� ���� ���������� �Ѵ�
	CScroll* pclScroll = m_pclList->GetScroll();
	if ( pclScroll )
	{
		pclScroll->SetScrollPos( pclScroll->GetX(), siListY, pclScroll->GetWidth(), m_pclList->GetHeight() );
	}

	m_pclList->Refresh();

}
