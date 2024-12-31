#include "CommonHeader.h"

#include "../Client/ninterface/NCharTransformDlg/CharTransformDlg.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../Client/Client.h"
#include "Char\CharManager\CharManager.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../NLib/NTCHARString.h"
#include "../../Client/InterfaceMgr/InterfaceMgr.h"
#include "../Client/ninterface/NInstantDungeonDlg/NInstantDungeonBoardDlg.h"
#include "../Client/InterfaceMgr/Interface/List.h"
#include "../Client/Client.h"
#include "../../CommonLogic/Msg/MsgType-Hunt.h"
#include "../../../../NLib/NUtil.h"
#include "../Client/MarkManager/MarkManager.h"



extern cltCommonLogic* pclClient;

NInstantDungeonBoradDlg :: NInstantDungeonBoradDlg()
{
	Initialize();
}

NInstantDungeonBoradDlg ::~NInstantDungeonBoradDlg(){
	Destroy();
}
void NInstantDungeonBoradDlg::Initialize(){
	m_siRequestPage = 1;
	m_siMaxPage = 50;
	m_MaxDisplatPage = MAX_DISPLAY_PAGE_NUM;
}
void NInstantDungeonBoradDlg :: Destroy(){

}
void NInstantDungeonBoradDlg ::Create(){

	if ( IsCreate() )		return;
	CInterfaceFile file;


	file.LoadFile(TEXT("NInterface/Data/NInstantDungeonDlg/NInstantDungeonBoardDlg.ddf"));
	file.CreatePopupDialog( this, NINSTANTDUNGEONBOARD_DLG , TEXT("dialog_instantdungeonBoard"), StaticNInstantDungeonBoradDlgProc );
	//��ư ����.

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NINSTANTDUNGEONBOARDDLG_BUTTON_RANKING , this ), NINSTANTDUNGEONBOARDDLG_BUTTON_RANKING,   "button_Ranking");
    file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NINSTANTDUNGEONBOARDDLG_BUTTON_HOF , this ), NINSTANTDUNGEONBOARDDLG_BUTTON_HOF,   "button_HOF");
	//���� ���� ������ �̵� ��ư ����
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NINSTANTDUNGEONBOARDDLG_BUTTON_PREV , this ), NINSTANTDUNGEONBOARDDLG_BUTTON_PREV,   "button_PREV");//�ڷ�
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NINSTANTDUNGEONBOARDDLG_BUTTON_NEXTV , this ), NINSTANTDUNGEONBOARDDLG_BUTTON_NEXTV,   "button_NEXTV");//������
	//��ŷ������ǥ�� �ؽ�Ʈ �ڽ� ����
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NINSTANTDUNGEONBOARDDLG_EDIT_PAGEVIEW , this ), NINSTANTDUNGEONBOARDDLG_EDIT_PAGEVIEW,   "editbox_PageView");
	//��ŷ ������ �̵� ��ư ����
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NINSTANTDUNGEONBOARDDLG_BUTTON_RANKPREV , this ), NINSTANTDUNGEONBOARDDLG_BUTTON_RANKPREV,   "button_RankPREV");//�ڷ�
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NINSTANTDUNGEONBOARDDLG_BUTTON_RANKNEXTV , this ), NINSTANTDUNGEONBOARDDLG_BUTTON_RANKNEXTV,   "button_RankNEXTV");//������
	
	//����Ʈ �ڽ� ����
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( LIST, NINSTANTDUNGEONBOARDDLG_LISTBOX_RHLIST , this ), NINSTANTDUNGEONBOARDDLG_LISTBOX_RHLIST,   "listbox_RHList");
	//�⺻ �����δ� ��ŷ�� �����ش�.
	CList* pList = m_InterfaceFactory.GetList(NINSTANTDUNGEONBOARDDLG_LISTBOX_RHLIST);
	TCHAR * pTextRank = GetTxtFromMgr(7843);
	TCHAR * pTextHOF = GetTxtFromMgr(7842);
	CButton* bRank = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_RANKING);
	CButton* bHOF = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_HOF);
	bRank->SetText(pTextRank);
	bHOF->SetText(pTextHOF);
	SetListBoxRanking();//��ŷ����Ʈ �ڽ��� ȭ���� �����ش�.
	//ChangeListBoxRanking();//������ �ϴ� �����ش�.
}

void CALLBACK NInstantDungeonBoradDlg :: StaticNInstantDungeonBoradDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl){
	NInstantDungeonBoradDlg *pThis = (NInstantDungeonBoradDlg*)pControllerMgr;
	pThis->NInstantDungeonBoradDlgProc(nEvent, nControlID, pControl);
}
void CALLBACK NInstantDungeonBoradDlg :: NInstantDungeonBoradDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl){

	cltClient *pclclient = (cltClient *)pclClient;
	switch(nControlID)
	{
	case COMMON_DIALOG_CLOSEBUTTON :
		{
			DeleteDialog();
		}break;
		//��ŷ�� ����.
	case NINSTANTDUNGEONBOARDDLG_BUTTON_RANKING :
		{
			//������ ��ȯ��ư�� ��Ȱ��ȭ ���������
			//�׸��� ����Ʈ �ڽ��� ��ŷ���� ����.
			//������ 10�����
			SetListBoxRanking();
		}break;
		//���� ������ ����
	case NINSTANTDUNGEONBOARDDLG_BUTTON_HOF :
		{
			SetListBoxHOF();

		}break;
		//��ŷ ���� ������
	case NINSTANTDUNGEONBOARDDLG_BUTTON_RANKPREV :
		{
			cltClient* pclclient = (cltClient*)pclClient;
			UI08 uiYear = pclclient->clClientDate.uiYear;//���ַ� 
			--m_siRequestPage;
			if( 0 < m_siRequestPage )
			{
				cltGameMsgRequest_RankingList sendMsg( uiYear, m_siRequestPage );//���� ���ַ��� �����ش�.
				cltMsg clMsg( GAMEMSG_REQUEST_RAKINGLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );
			}
			else
			{
				m_siRequestPage = 1;
			}
			
		}break;
		//��ŷ ���� ������
	case NINSTANTDUNGEONBOARDDLG_BUTTON_RANKNEXTV :
		{
			cltClient* pclclient = (cltClient*)pclClient;
			UI08 uiYear = pclclient->clClientDate.uiYear;//���ַ�
			++m_siRequestPage;

			if( m_siRequestPage <= m_siMaxPage )
			{
				cltGameMsgRequest_RankingList sendMsg( uiYear, m_siRequestPage );//���� ���ַ��� �����ش�.
				cltMsg clMsg( GAMEMSG_REQUEST_RAKINGLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );
			}
			else
			{
				m_siRequestPage = m_siMaxPage;
			}

		}break;
		//���� �������� ����
	case NINSTANTDUNGEONBOARDDLG_BUTTON_PREV :
		{
			--m_siRequestPage;
			

			if( 0 < m_siRequestPage )
			{	
				cltGameMsgRequest_HOFList sendMsg(m_siRequestPage );//���ϴ� �������� �����ش�
				cltMsg clMsg( GAMEMSG_REQUEST_HOFLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );
			}
			else
			{
				m_siRequestPage = 1;
			}
		}break;
		//���� �������� ����
	case NINSTANTDUNGEONBOARDDLG_BUTTON_NEXTV :
		{
			++m_siRequestPage;

			if( m_siRequestPage <= m_siMaxPage )
			{
				cltGameMsgRequest_HOFList sendMsg( m_siRequestPage );//���ϴ� �������� �����ش�
				cltMsg clMsg( GAMEMSG_REQUEST_HOFLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );
			}
			else
			{
				m_siRequestPage = m_siMaxPage;
			}
		}break;
	}

}

//��ŷ��ư �������� ����Ʈ �ڽ� ����.
void NInstantDungeonBoradDlg::SetListBoxRanking()
{
	cltClient* pclclient = (cltClient*)pclClient;
	//Į�� ����.
	CList* pList = m_InterfaceFactory.GetList(NINSTANTDUNGEONBOARDDLG_LISTBOX_RHLIST);
	//�⺻ ��ŷ ��ư�� ���������� ���� ���� ������ �̵� ��ư�� �������� �ȵȴ�.
	CButton * pPrev = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_PREV);
	CButton * pNextv = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_NEXTV);
	//�ؽ�Ʈ �ڽ��� ������ �ʵ��� �Ѵ�.
	CEdit * pPageview = m_InterfaceFactory.GetEdit(NINSTANTDUNGEONBOARDDLG_EDIT_PAGEVIEW);
	//�⺻ ��ŷ ��ư�� ���������� ������ �̵� ��ư�� �������� �ȵȴ�.
	CButton * pRankPrev = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_RANKPREV);
	CButton * pRankNextv = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_RANKNEXTV);
	
	pPrev->Show(false);
	pNextv->Show(false);
	pRankPrev->Show(true);
	pRankNextv->Show(true);

    pPageview->Clear();	
	pList->Clear();//����Ʈ �ڽ��� �����ش�.
    if ( pList )
	{
		pList->SetBorder(true);
		pList->SetBKColorUse(true);

		TCHAR* pText = GetTxtFromMgr( 5398 );
		pList->SetColumn(0,50 , pText);
		pText = GetTxtFromMgr( 7818 );
		pList->SetColumn(1,55 , pText);
		pText = GetTxtFromMgr( 6580 );
		pList->SetColumn(2, 100, pText);
		pText = GetTxtFromMgr( 7820 );
		pList->SetColumn(3, 70, pText);
		pText = GetTxtFromMgr( 7821 );
		pList->SetColumn(4, 70, pText);
		pText = GetTxtFromMgr( 7822 );
		pList->SetColumn(5, 120, pText);
		
		m_siRequestPage = 1; //�ֽ� ù�������� �޶�� �Ѵ�
		//SI32 datevary = pclclient->clClientDate.uiYear.GetDateVary();//���ַ�
		//UI08 uiYear  = datevary / (12* 30);//���� �⵵�� ���Ѵ�.

		UI08 uiYear = pclclient->clClientDate.uiYear;//���ַ� 

		cltGameMsgRequest_RankingList sendMsg( uiYear, m_siRequestPage );//���� ���ַ��� �����ش�.
		cltMsg clMsg( GAMEMSG_REQUEST_RAKINGLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
		pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );
		pList->Refresh();


	}
}
//���� ���� ����
void NInstantDungeonBoradDlg::SetListBoxHOF(){
	//Į�� ����.
	CList* pList = m_InterfaceFactory.GetList(NINSTANTDUNGEONBOARDDLG_LISTBOX_RHLIST);
	//���� ������ ��쿡�� ����Ʈ�� ������ ������ �Űܾ� �ϹǷ� ��ư�� ���̵��� �Ѵ�.
	CButton * pPrev = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_PREV);
	CButton * pNextv = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_NEXTV);
	//�⺻ ��ŷ ��ư�� ���������� ������ �̵� ��ư�� �������� �ȵȴ�.
	CButton * pRankPrev = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_RANKPREV);
	CButton * pRankNextv = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_RANKNEXTV);
	//�ؽ�Ʈ �ڽ��� ���̵��� �Ѵ�.
	CEdit * pPageview = m_InterfaceFactory.GetEdit(NINSTANTDUNGEONBOARDDLG_EDIT_PAGEVIEW);

	m_siRequestPage = 1; //ó�� ���� �Ҷ��� ù �������Ƿ�.
	
	pPrev->Show(true);
	pNextv->Show(true);
	pRankPrev->Show(false);
	pRankNextv->Show(false);
	
	pPageview->Clear();
	pList->Clear();//����Ʈ �ڽ��� �����ش�.
	if ( pList )
	{
		pList->SetBorder(true);
		pList->SetBKColorUse(true);

		TCHAR* pText = GetTxtFromMgr( 7823 );
		pList->SetColumn(0, 50, pText);
		pText = GetTxtFromMgr( 7818 );
		pList->SetColumn(1, 55, pText);
		pText = GetTxtFromMgr( 6580 );
		pList->SetColumn(2, 100, pText);
		pText = GetTxtFromMgr( 7820 );
		pList->SetColumn(3, 70, pText);
		pText = GetTxtFromMgr( 7821 );
		pList->SetColumn(4, 70, pText);
		pText = GetTxtFromMgr( 7822 );
		pList->SetColumn(5, 120, pText);
		pList->Refresh();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

		cltGameMsgRequest_HOFList sendMsg( m_siRequestPage );//���ϴ� �������� �����ش�
		cltMsg clMsg( GAMEMSG_REQUEST_HOFLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
		pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );
		pList->Refresh();
	}
}


//��ȯ ��ư�� ������ ����Ʈ �ڽ��� �ٲ��� �Լ���
void NInstantDungeonBoradDlg::ChangeListBoxRanking(HOFList *hoflist, SI16 requestpage, SI16 Maxpage){
	//��ŷ�� �����ٶ��� ���� �״��� ���� ������. �ϴ� ������ ����� �ϴ� ����� ��. ���� �ٸ� ����� ������ ������?
	CList* pList = m_InterfaceFactory.GetList(NINSTANTDUNGEONBOARDDLG_LISTBOX_RHLIST);
	CEdit* pEdit = m_InterfaceFactory.GetEdit(NINSTANTDUNGEONBOARDDLG_EDIT_PAGEVIEW);//�������� �����ִ� ����Ʈ �ڽ� 
	CButton* pRankPrevB = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_RANKPREV);//����������
	CButton* pRankNextv = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_RANKNEXTV);//���� ������
	TCHAR buffer[128] = {'\0'};	
	pList->Clear();//����Ʈ �ڽ��� �����ش�.
	pEdit->Clear();

	SI32 point = hoflist->siClearPoint;	
	stListBoxItemData tempItemData;

	if (requestpage== Maxpage) {
		pRankNextv->Enable(false);
	}
	else if (requestpage < Maxpage) {
		pRankNextv->Enable(true);
	}
	if (requestpage<=1) {
		pRankPrevB->Enable(false);
	}	
	else if (requestpage>1) {
		pRankPrevB->Enable(true);
	}
	//����Ʈ �ڽ��� ������ �����ش�.	
	pEdit->SetTextPrintOption( DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	StringCchPrintf( buffer, 128, "%d/%d", requestpage, Maxpage );
	pEdit->SetText( buffer );
	
	for(int Cnt = 0; Cnt < MAX_HOF_RANKCOUNT; ++Cnt)
	{
		tempItemData.Init();
		TCHAR	szBuffer[32] = "";
		//��ŷ�� 0���� ������ȵǱ� ������ +1 ���ش�.
		//2 page���ʹ� 11�� ���� ���;� �ϴϱ�.
		if (requestpage>=2) {
			itoa((requestpage*10-10)+Cnt+1, szBuffer, 10);
		}
		else
		{
			itoa(Cnt+1, szBuffer, 10);
		}

		TCHAR buffer[ 256 ];

		SI32 year = hoflist[Cnt].ClearDateTime.wYear;
		SI32 month = hoflist[Cnt].ClearDateTime.wMonth;
		SI32 day = hoflist[Cnt].ClearDateTime.wDay;
		
		TCHAR * pText = GetTxtFromMgr(1508);
		sprintf( buffer, pText, 
			hoflist[Cnt].ClearDateTime.wYear, hoflist[Cnt].ClearDateTime.wMonth, hoflist[Cnt].ClearDateTime.wDay );	

		SI32  guildicon  = -1 ;
		TSpr* guildspr	= NULL;

		cltClient* pclclient = (cltClient*)pclClient;
		pclclient->m_pMarkManager->GetMarkSprAndFontIndex( hoflist[Cnt].siGuildMarkindex, &guildspr, &guildicon );
				
		SI16 SprNum = -1;
		switch(hoflist[Cnt].siGuildMarkindex / 256)
		{
			case 0: SprNum = GIMG_VILLAGEMARK01;	break;
			case 1: SprNum = GIMG_VILLAGEMARK02;	break;
			case 2: SprNum = GIMG_VILLAGEMARK03;	break;
		}	

		tempItemData.Set( 0,szBuffer);

		//��� ��ũ�� �������� �׷��ش� 
		if(guildicon >= 0)
		{
			tempItemData.SetSmallIconGImg( 1, SprNum, guildicon);
		}		

		tempItemData.Set( 2, hoflist[Cnt].szHOFGuildName);
		tempItemData.Set( 3, SI32ToString(hoflist[Cnt].siClearPoint));
		TCHAR szClearTime[128];
		TCHAR *pszText = GetTxtFromMgr(1252);
		StringCchPrintf(szClearTime, sizeof(szClearTime), pszText, hoflist[Cnt].ClearTime / (1000 * 60) );
		tempItemData.Set( 4, szClearTime );
		tempItemData.Set( 5, buffer);
		pList->AddItem( &tempItemData );
		pList->Refresh();
	}
}
//
void NInstantDungeonBoradDlg::ChangeListBoxHOF(HOFList *hoflist, SI16 requestpage, SI16 Maxpage){
	CList* pList = m_InterfaceFactory.GetList(NINSTANTDUNGEONBOARDDLG_LISTBOX_RHLIST);
	CEdit* pEdit = m_InterfaceFactory.GetEdit(NINSTANTDUNGEONBOARDDLG_EDIT_PAGEVIEW);//�������� �����ִ� ����Ʈ �ڽ� 
	CButton* pPrevB = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_PREV);//����������
	CButton* pNextv = m_InterfaceFactory.GetButton(NINSTANTDUNGEONBOARDDLG_BUTTON_NEXTV);//���� ������
	pList->Clear();//����Ʈ �ڽ��� �����ش�.
	pEdit->Clear();
	TCHAR buffer[128] = {'\0'};
	SI32 point = hoflist->siClearPoint;	
	stListBoxItemData tempItemData;
	
	if (requestpage== Maxpage) {
		pNextv->Enable(false);
	}
	else if (requestpage < Maxpage) {
		pNextv->Enable(true);
	}
	if (requestpage<=1) {
		pPrevB->Enable(false);
	}	
	else if (requestpage>1) {
		pPrevB->Enable(true);
	}
	//����Ʈ �ڽ��� ������ �����ش�.	
	pEdit->SetTextPrintOption( DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	StringCchPrintf( buffer, 128, "%d/%d", requestpage, Maxpage );
	pEdit->SetText( buffer );
	
	for(int Cnt = 0; Cnt < MAX_HOF_RANKCOUNT; ++Cnt)
	{
		tempItemData.Init();
		//���̻� �����Ͱ� ������ �׷����� �ʴ´�.
		if( hoflist[Cnt].uiYear <= 0 )		continue;

		TCHAR * pText = GetTxtFromMgr(1508);
		sprintf( buffer, pText, 
			hoflist[Cnt].ClearDateTime.wYear, hoflist[Cnt].ClearDateTime.wMonth, hoflist[Cnt].ClearDateTime.wDay );	

		SI32  guildicon  = -1 ;
		TSpr* guildspr	= NULL;

		cltClient* pclclient = (cltClient*)pclClient;
		pclclient->m_pMarkManager->GetMarkSprAndFontIndex( hoflist[Cnt].siGuildMarkindex, &guildspr, &guildicon );


		SI16 SprNum = -1;
		switch(hoflist[Cnt].siGuildMarkindex / 256)
		{
			case 0: SprNum = GIMG_VILLAGEMARK01;	break;
			case 1: SprNum = GIMG_VILLAGEMARK02;	break;
			case 2: SprNum = GIMG_VILLAGEMARK03;	break;
		}	

		//��� ��ũ�� �������� �׷��ش� 
		if(guildicon >= 0)
		{
			tempItemData.SetSmallIconGImg( 1, SprNum, guildicon);
		}

		tempItemData.Set( 0,UI08ToString(hoflist[Cnt].uiYear));
		tempItemData.Set( 2, hoflist[Cnt].szHOFGuildName);
		tempItemData.Set( 3, SI32ToString(hoflist[Cnt].siClearPoint) );
		TCHAR szClearTime[128];
		TCHAR *pszText = GetTxtFromMgr(1252);
		StringCchPrintf(szClearTime, sizeof(szClearTime), pszText, hoflist[Cnt].ClearTime / (1000 * 60) );
		tempItemData.Set( 4, szClearTime );
		tempItemData.Set( 5, buffer);
		pList->AddItem( &tempItemData );
		pList->Refresh();
	}
}
