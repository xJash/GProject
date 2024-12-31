#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../Client.h"
#include "Char/CharManager/CharManager.h"

#include "Msg/MsgType-WorldMoney.h"

#include "NAcuTradeDlg_Buy.h"


CNAcuTradeDlg_Buy::CNAcuTradeDlg_Buy() : CDialogController()
{
	ZeroMemory( m_siSelectedIndex, sizeof(m_siSelectedIndex) );
}

CNAcuTradeDlg_Buy::~CNAcuTradeDlg_Buy()
{

}

void CNAcuTradeDlg_Buy::Create(CControllerMgr* pParent)
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		return;
	}

	//-- ���� ��ü���� ����
	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NAcuTradeDlg/DLG_NAcuTrade_Buy.ddf" ) );
	file.CreateChildDialog( this, NACUTRADEDLG_BUY, TEXT( "dialog_acutrade_buy" ), StaticAcuTradeDlg_BuyProc, pParent );


	file.CreateControl( m_InterfaceFactory.CreateUserInterface( LIST,	NACUTRADE_BUY_LIST_ACULIST,		this ), NACUTRADE_BUY_LIST_ACULIST,		TEXT( "listbox_aculist" ) );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,	NACUTRADE_BUY_STATIC_NONAME1,	this ), NACUTRADE_BUY_STATIC_NONAME1,	TEXT( "statictext_NONAME1" ) );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT,	NACUTRADE_BUY_EDIT_BUYACU,		this ), NACUTRADE_BUY_EDIT_BUYACU,		TEXT( "editbox_buyacu" ) );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,	NACUTRADE_BUY_BUTTON_BUY,		this ), NACUTRADE_BUY_BUTTON_BUY,		TEXT( "button_buy" ) );

	//-- ��Ʈ�� ����
	
	// ����Ʈ
	CList* pAcuList = m_InterfaceFactory.GetList( NACUTRADE_BUY_LIST_ACULIST );
	if ( pAcuList )
	{
		SI16	siColumn0	= pAcuList->GetWidth()/2;
		SI16	siColumn1	= pAcuList->GetWidth() - siColumn0;

		TCHAR*	pText		= GetTxtFromMgr( 6149 );
		pAcuList->SetColumn( 0, siColumn0, pText );

		pText = GetTxtFromMgr( 6148 );
		pAcuList->SetColumn( 1, siColumn1, pText );

		pAcuList->SetBorder(TRUE);
		pAcuList->SetBKColorUse(TRUE);
		pAcuList->Refresh();
	}


	// ��ť �Է�
	CEdit* pBuyAcu = m_InterfaceFactory.GetEdit( NACUTRADE_BUY_EDIT_BUYACU );
	if ( pBuyAcu )
	{
		pBuyAcu->SetNumberMode( true );
	}


	//-- �⺻ �ʱ� ����

}

void CALLBACK CNAcuTradeDlg_Buy::StaticAcuTradeDlg_BuyProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNAcuTradeDlg_Buy *pThis = (CNAcuTradeDlg_Buy*) pControllerMgr;
	if ( pThis )
	{
		pThis->NAcuTradeDlg_BuyProc( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNAcuTradeDlg_Buy::NAcuTradeDlg_BuyProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{

	switch( nControlID )
	{
		case NACUTRADE_BUY_BUTTON_BUY:
			{
				OrderToBuy();
			}
			break;
	}

}

void CNAcuTradeDlg_Buy::Action()
{
}

void CNAcuTradeDlg_Buy::Show()
{
	CControllerMgr::Show( true );
}

void CNAcuTradeDlg_Buy::Hide()
{
	CControllerMgr::Show( false );
}

void CNAcuTradeDlg_Buy::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{

}

void CNAcuTradeDlg_Buy::Refresh( void )
{
	cltWorldMoneyTradeList clSortList[MAX_WORLDMONEY_TRADELIST_NUM];
	ZeroMemory( clSortList, sizeof(clSortList) );

	// ��ť�� ������������ �����Ѵ�
	SortTradeList( clSortList );

	// �����ڽ��� ���� �����͸� �Է��Ѵ�
	SetTradeListBox( clSortList );

}

void CNAcuTradeDlg_Buy::OrderToBuy( void )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclClient )
	{
		return;
	}

	CList* pclAcuList = m_InterfaceFactory.GetList( NACUTRADE_BUY_LIST_ACULIST );
	if ( NULL == pclAcuList )
	{
		return;
	}
	
	// ��ȿ�� �˻�
	SI32 siSelectedIndex = pclAcuList->GetSelectedIndex();
	if ( (0 > siSelectedIndex) || (MAX_WORLDMONEY_TRADELIST_NUM <= siSelectedIndex) )
	{
		NTCHARString128 strTitle( GetTxtFromMgr(1898) );
		NTCHARString128 strText( GetTxtFromMgr(1868) );

		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( strTitle, strText );
		return;
	}

	// ��ȿ�� �˻�
	SI32 siOrderIndex = m_siSelectedIndex[ siSelectedIndex ];
	if ( (0 > siOrderIndex) || (MAX_WORLDMONEY_TRADELIST_NUM <= siOrderIndex) )
	{
		return;
	}


	CEdit* pclBuyAcu = m_InterfaceFactory.GetEdit( NACUTRADE_BUY_EDIT_BUYACU );
	if ( NULL == pclBuyAcu )
	{
		return;
	}

	// ��ȿ�� �˻�
	GMONEY gmBuyAcu = _tstoi( pclBuyAcu->GetText() );
	if ( 0 >= gmBuyAcu )
	{
		SetFocus( pclBuyAcu );
		return;
	}


	cltGameMsgRequest_WorldMoney_BuyOrder clinfo( siOrderIndex, gmBuyAcu );
	cltMsg clMsg( GAMEMSG_REQUEST_WORLDMONEY_BUYORDER, sizeof(clinfo), (BYTE *)&clinfo );
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
}

bool CNAcuTradeDlg_Buy::IsEmptyTradeList( cltWorldMoneyTradeList* pclList )
{
	if ( NULL == pclList )
	{
		return false;
	}

	if ( (0 >= pclList->siDate) && (0 >= pclList->siPersonID) && (0 >= pclList->siPrice) && (0 >= pclList->siWorldMoney) )
	{
		return true;
	}

	return false;
}

void CNAcuTradeDlg_Buy::SwapTradeList( cltWorldMoneyTradeList* pclLParam, cltWorldMoneyTradeList* pclRParam )
{
	if ( (NULL == pclLParam) || (NULL == pclRParam) )
	{
		return;
	}

	cltWorldMoneyTradeList clSwapList;
	clSwapList.Set( pclLParam );

	pclLParam->Set( pclRParam );
	pclRParam->Set( &clSwapList );

}

void CNAcuTradeDlg_Buy::SwapTradeIndex( SI32* psiLParam, SI32* psiRParam )
{
	if ( (NULL == psiLParam) || (NULL == psiRParam) )
	{
		return;
	}

	SI32 siSwapIndex = *psiLParam;

	*psiLParam = *psiRParam;
	*psiRParam = siSwapIndex;
}

void CNAcuTradeDlg_Buy::SortTradeList( cltWorldMoneyTradeList* pclTradeList )
{
	if ( NULL == pclTradeList )
	{
		return;
	}

	// ����Ʈ�� ������������ ���������� ���� �ε����� �˰� �־�� �ϱ� ������ ���� �ε����� ���� �۾��Ѵ�
	ZeroMemory( m_siSelectedIndex, sizeof(m_siSelectedIndex) );

	for ( SI32 siIndex=0; siIndex<MAX_WORLDMONEY_TRADELIST_NUM; ++siIndex )
	{
		pclTradeList[siIndex].Set( 0, 0, 0, 0 );

		cltWorldMoneyTradeList* pclList = &pclClient->pclDistributionWorldMoney->clTradeList[ siIndex ];
		if ( NULL == pclList )
		{
			continue;
		}

		if ( true == IsEmptyTradeList(pclList) )
		{
			continue;
		}

		// �� ����� �Ǵ� ����Ʈ(�����ϸ鼭 �ȿ� ������ �ٲ���ִ�)
		cltWorldMoneyTradeList clCompareList;
		clCompareList.Set( pclList );

		SI32 siCompareIndex = siIndex;

		for ( SI32 siCompare=0; siCompare<=siIndex; ++siCompare )
		{
			if ( true == IsEmptyTradeList(&pclTradeList[siCompare]) )
			{
				pclTradeList[siCompare].Set( &clCompareList );

				m_siSelectedIndex[siCompare] = siCompareIndex;
				break;
			}
			else if ( pclTradeList[siCompare].siWorldMoney > clCompareList.siWorldMoney )
			{
				SwapTradeList( &pclTradeList[siCompare], &clCompareList );
				SwapTradeIndex( &m_siSelectedIndex[siCompare], &siCompareIndex );
			}
		}
	}

}

void CNAcuTradeDlg_Buy::SetTradeListBox( cltWorldMoneyTradeList* pclTradeList )
{
	if ( NULL == pclTradeList )
	{
		return;
	}

	CList* pclAcuList = m_InterfaceFactory.GetList( NACUTRADE_BUY_LIST_ACULIST );
	if ( NULL == pclAcuList )
	{
		return;
	}

	stListBoxItemData WorldMoneyListBoxData;

	pclAcuList->Clear();

	for ( SI32 siCount=0; siCount<MAX_WORLDMONEY_TRADELIST_NUM; ++siCount )
	{
		if ( true == IsEmptyTradeList(&pclTradeList[siCount]) )
		{
			break;
		}

		WorldMoneyListBoxData.Init();
		
		TCHAR szWorldMoney[128] = { '\0', };
		g_JYLibFunction.SetNumUnit( pclTradeList[siCount].siWorldMoney, szWorldMoney, sizeof(szWorldMoney) );
		WorldMoneyListBoxData.Set( 0, szWorldMoney );

		TCHAR szPrice[128] = { '\0', };
		g_JYLibFunction.SetNumUnit( pclTradeList[siCount].siPrice, szPrice, sizeof(szPrice) );
		WorldMoneyListBoxData.Set( 1, szPrice );

		pclAcuList->AddItem( &WorldMoneyListBoxData );	

	}

	pclAcuList->SetTextPrintOption( DT_LEFT | DT_VCENTER | DT_SINGLELINE );	
	pclAcuList->Refresh();

}
