#include "NHelperQuestionListDlg.h"
#include "NHelperQuestionOrAnswerDlg.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../Client/ninterface/nsoundonoffdlg/NSoundOnOffDlg.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../NHelperDlg/NHelperQuestionOrAnswerDlg.h"
#include "../../CommonLogic/MsgType-System.h"

NHelperQuestionListDlg::NHelperQuestionListDlg()
{

}


NHelperQuestionListDlg::~NHelperQuestionListDlg()
{
	Destroy();
}


void NHelperQuestionListDlg::Init()
{

}


void NHelperQuestionListDlg::Destroy()
{


}


void NHelperQuestionListDlg::Create()
{
	if( IsCreate() )
	{
		return;
	}
	
	// �亯���� â �ݱ�.
	cltClient * pclclient = (cltClient*) pclClient;
	NHelperQuestionOrAnswerDlg* pDialog = (NHelperQuestionOrAnswerDlg*)pclclient->m_pDialog[NHELPER_QUESTION_OR_ANSWER_DLG];
	if( NULL != pDialog ) pDialog->DeleteDialog(); 


	CInterfaceFile file;

	file.LoadFile("Ninterface/Data/NHelperDlg/NHelper_Question_List.ddf");

	file.CreatePopupDialog( this , NHELPER_QUESTION_LIST_DLG, "dialog_question_list" , StatiNHelperQuestionListDlgProc );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,	NHELPER_QUESTION_LIST_DLG_STATIC_LIST,	 this), NHELPER_QUESTION_LIST_DLG_STATIC_LIST,    "statictext_question_list");
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( LIST,	NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST,	 this), NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST,   "listbox_list"			);
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT,	NHELPER_QUESTION_LIST_DLG_EDIT_CONTENTS, this), NHELPER_QUESTION_LIST_DLG_EDIT_CONTENTS,  "editbox_contents"		);
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,	NHELPER_QUESTION_LIST_DLG_BUTTON_ANSWER, this), NHELPER_QUESTION_LIST_DLG_BUTTON_ANSWER,  "button_answer"			);
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,	NHELPER_QUESTION_LIST_DLG_BUTTON_GM_DEL, this), NHELPER_QUESTION_LIST_DLG_BUTTON_GM_DEL,  "button_gm_del_question"	);

	m_InterfaceFactory.GetEdit( NHELPER_QUESTION_LIST_DLG_EDIT_CONTENTS )->SetMaxEditTextLength( CONTENTS_LETTER_NUM );

	CList* pQuestionList = m_InterfaceFactory.GetList(NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST);
	pQuestionList->Clear();
	pQuestionList->SetBorder(true);
	pQuestionList->SetBKColorUse(true);
	pQuestionList->SetColumn( 0,  50, GetTxtFromMgr(1641) );		// ��ȣ
	pQuestionList->SetColumn( 1, 250, GetTxtFromMgr(9721) );		// ����    
	pQuestionList->SetColumn( 2, 110, GetTxtFromMgr(1556) );		// �̸�
 	pQuestionList->Refresh();

	m_InterfaceFactory.GetEdit(NHELPER_QUESTION_LIST_DLG_EDIT_CONTENTS)->SetText( GetTxtFromMgr(1565) );
		
	m_siQuestionListNum = 0;

	GM_Mode( false );
} 

void NHelperQuestionListDlg::Action()
{

}

void CALLBACK NHelperQuestionListDlg::StatiNHelperQuestionListDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	NHelperQuestionListDlg *pThis = (NHelperQuestionListDlg *)pControllerMgr;
	pThis->NHelperQuestionListDlgProc( nEvent, nControlID, pControl );
}


void CALLBACK NHelperQuestionListDlg::NHelperQuestionListDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient * pclclient = (cltClient*) pclClient;
	
	switch(nControlID)
	{
		case NHELPER_QUESTION_LIST_DLG_BUTTON_GM_DEL:
			{
				CList* pQuestionList = m_InterfaceFactory.GetList(NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST);

				SI16 siRow = -1, siCol = -1;

				pQuestionList->GetSelectedIndex( &siRow, &siCol );
				if( siRow == -1 || siCol == -1 )
					return;

				TCHAR* pNumber = pQuestionList->GetText( siRow, 0 );
				SI32 Index = atoi( pNumber ) - 1;

				if( 0 < m_siQuestionPersonID[Index] )
				{
					// �亯�� ��� ��û.
					cltMsg clMsg1( GAMEMSG_REQUEST_DEL_QUESTION, sizeof(m_siQuestionPersonID[Index]), (BYTE*)&m_siQuestionPersonID[Index]);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg1);
				}
			}
			break;
		case COMMON_DIALOG_CLOSEBUTTON:
			{
				DeleteDialog();
			}
			break;
		case NHELPER_QUESTION_LIST_DLG_BUTTON_ANSWER:
			{
				CList* pQuestionList = m_InterfaceFactory.GetList(NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST);

				SI16 siRow = -1, siCol = -1;

				pQuestionList->GetSelectedIndex( &siRow, &siCol );
				if( siRow == -1 || siCol == -1 )
					return;

				TCHAR* pNumber = pQuestionList->GetText( siRow, 0 );
				SI32 Index = atoi( pNumber ) - 1;

				if( 0 < m_siQuestionPersonID[Index] )
				{
					// �亯�� ��� ��û.
					cltGameMsgRequest_Add_Answer clInfo( m_siQuestionPersonID[Index] );
					cltMsg clMsg(GAMEMSG_REQUEST_ADD_ANSWER, sizeof(clInfo), (BYTE*)&clInfo);
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
			}
			break;
		case NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST:
			{
				switch( nEvent )
				{
					case EVENT_LISTBOX_SELECTION:
						{
							CList* pQuestionList = m_InterfaceFactory.GetList(NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST);

							SI16 siRow = -1, siCol = -1;

							pQuestionList->GetSelectedIndex( &siRow, &siCol );
							if( siRow == -1 || siCol == -1 )
								return;

							TCHAR* pNumber = pQuestionList->GetText( siRow, 0 );
							SI32 Index = atoi( pNumber )-1;
							
							// ���� ���� ���õ� ���빰 ������ ��û.
							cltGameMsgRequest_Question_Contents_Get clInfo( m_siQuestionPersonID[Index] );
							cltMsg clMsg(GAMEMSG_REQUEST_QUESTION_CONTENTS_GET, sizeof(clInfo), (BYTE*)&clInfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
						}
				}
			}
			break;
		default:	break;
	}
}

void NHelperQuestionListDlg::SetQuestionTileList( SI32* _psiQuestionPersonID, TCHAR** _pszQuestionTitle, TCHAR** _pszName, bool* _pbAleadyAnswer )
{
	// �ӽ� ���� ����� ���� ����.
	SI32	siQuestionPersonID[ SENDMSG_LIST_NUM ];							// ������ personID
	TCHAR	szQuestionTitle[ SENDMSG_LIST_NUM ][TITLE_LETTER_NUM];			// ����
	TCHAR	szName[ SENDMSG_LIST_NUM ][MAX_PLAYER_NAME];

	memcpy( siQuestionPersonID,	_psiQuestionPersonID,	sizeof(siQuestionPersonID) );
	memcpy( szQuestionTitle,	_pszQuestionTitle,		sizeof(szQuestionTitle)	   );
	memcpy( szName,				_pszName,				sizeof(szName)			   );
	
	stListBoxItemData Itemdata;
	TCHAR			  szBuffer[4] = "";
	
	CList* pQuestionList = m_InterfaceFactory.GetList(NHELPER_QUESTION_LIST_DLG_LISTBOX_LIST);
	//pQuestionList->Clear();
	
	TCHAR* pszQuestionTile = NULL;
	TCHAR* pszName		   = NULL;

	for ( SI32 Count = 0; Count < SENDMSG_LIST_NUM; ++Count )
	{
		if( 0 >= siQuestionPersonID[Count] ) break;

		Itemdata.Init();
				
		if(_pbAleadyAnswer[Count])
		{
			Itemdata.siSmallIconFileIndex[ 0 ] = 0;
			Itemdata.siSmallIconFontIndex[ 0 ] = 12; // �亯�� ����.
		} 
		else
		{
			Itemdata.siSmallIconFileIndex[ 0 ] = 0;
			Itemdata.siSmallIconFontIndex[ 0 ] = 11; // �亯�� ����. 
		}

		_itot( m_siQuestionListNum+1, szBuffer, 10 );
		Itemdata.Set( 0, szBuffer );		
		Itemdata.Set( 1, szQuestionTitle[Count], COLORREF(0xffffffff) );
		Itemdata.Set( 2, szName[Count] );
		
		pQuestionList->AddItem( &Itemdata );

		// ���� ������ �ִ� 100�� ���� ä���. 
		memcpy( &m_siQuestionPersonID[m_siQuestionListNum],	&siQuestionPersonID[Count],	sizeof(m_siQuestionPersonID[m_siQuestionListNum]) );
		memcpy(  m_szQuestionTitle[m_siQuestionListNum],	 szQuestionTitle[Count],	sizeof(m_szQuestionTitle[m_siQuestionListNum])	  );
		memcpy(  m_szName[m_siQuestionListNum],				 szName[Count],				sizeof(m_szName[m_siQuestionListNum])			  );

		++m_siQuestionListNum;
	}
	pQuestionList->Refresh();
}

void NHelperQuestionListDlg::SetQuestionContents( TCHAR* pContents )
{
	m_InterfaceFactory.GetEdit(NHELPER_QUESTION_LIST_DLG_EDIT_CONTENTS)->SetText( pContents );
}

void NHelperQuestionListDlg::GM_Mode( bool _bShow )
{
	m_InterfaceFactory.GetButton(NHELPER_QUESTION_LIST_DLG_BUTTON_GM_DEL)->Show( _bShow );
}
