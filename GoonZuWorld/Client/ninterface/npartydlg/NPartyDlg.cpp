#include "../client/NInterface/NPartyDlg/NPartyDlg.h"

#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/ListView.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/Interface/ImageStatic.h"
#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/ChatEdit.h"
#include "../../InterfaceMgr/Interface/RadioButton.h"
#include "../../InterfaceMgr/Interface/OutLine.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"

#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../../Client.h"
#include "../CommonLogic/TextMgr/TextMgr.h"

#include "../../CommonLogic/MsgType-Person.h"
#include "Char\CharManager\CharManager.h"
#include "..\..\..\CommonLogic\Msg\MsgType-Party.h"
#include "..\..\..\Common\SMLib\LibList\LibList.h"
#include "../../../common/SMLib/LibList/LibListMgr.h"

#include "../../ninterface/nprivatechatdlg/NPrivateChatDlgMgr.h"
#include "../../ninterface/nprivatechatdlg/NPrivateChatDlg.h"

#include "../../ninterface/nletterdlg/NLetterDlg.h"

#include "../../CommonLogic/Msg/MsgType-ItemMall.h"

#include "../../common/Item/ItemCommon/ItemUnit.h"

#include "../NHelpButton/NHelpButtonDlg.h"

#include "../NMarriageLoveLevelDlg/NMarriageLoveLevelDlg.h"
#include "../NFamilyCookieDlg/NFamilyCookieDlg.h"
#include "../NFamilyInfoDlg/NFamilyInfoDlg.h"
#include "../NDormancyAccount/NDormancyPointDlg.h"

#include "../../../CommonLogic/MsgType-PartyQuest.h"

#include "../../../client/PartyQuestMgr/PartyQuestMgr_Client.h"
#include "../../../common/PartyMgr/PartyMgr.h"
#include "../../../CommonLogic/PartyMatchingMgr/Client_PartyMatchingMgr.h"

extern cltCommonLogic* pclClient;
extern SI32 gsiResolution;

CNPartyDlg::CNPartyDlg() :CDialogController()
{
	m_bMini = FALSE;
	m_siOldPosX = 0;
	m_siOldPosY = 0;
	m_siPartyUserNum = 0;
	m_siMinimizedSlot = 0;
	m_strViewData = new TCHAR[ MAX_RICHEDIT_OBJ_SIZE ];
	memset( m_strViewData, 0, MAX_RICHEDIT_OBJ_SIZE );

	m_strChatData = new TCHAR[ MAX_CHAT_DATA_LENGTH ];
	memset( m_strChatData, 0, MAX_CHAT_DATA_LENGTH );

	m_siSelectedUserListIndex = -1;

	m_pChatDataList = new CLibListMgr();
	m_pChatDataList->CreateMaxEmptyObj( 2, 200 );

	Initialize();

	m_pStatic[0] = NULL;
	m_pStatic[1] = NULL;
	m_pStatic[2] = NULL;
	m_pList = NULL;
	m_pButton = NULL;
	m_pMoveButton = NULL;
	m_pEdit = NULL;
	m_pChatEdit = NULL;
	m_pRadioItemGetPattern[0] = NULL;
	m_pRadioItemGetPattern[1] = NULL;
	m_pRadioItemGetPattern[2] = NULL;
	m_pRadioItemGetPattern[3] = NULL;
	m_pImageMinimized = NULL;
	m_pButtonMinimize = NULL;
	m_pOutLine[0] = NULL;
	m_pOutLine[1] = NULL;
	
	ColorIndex[0] =RGB(210,15,15);
	ColorIndex[1] = RGB(255,100,10);
	ColorIndex[2] = RGB(40,150,0);
	ColorIndex[3] = RGB(0,200,210);
	ColorIndex[4] = RGB(30,30,240);
	ColorIndex[5] = RGB(130,20,240);

	m_pBtnStartQuest = NULL;
	m_siInviteCharUniqueForPartyQuest = 0;

	m_bIsPartyQuestParty = false;
	m_siCategory = -1;
	m_siMission = -1;
	
}

CNPartyDlg::~CNPartyDlg()
{
	if( m_strViewData )
	{
		delete [] m_strViewData;
		m_strViewData = NULL;
	}

	if ( m_strChatData )
	{
		delete [] m_strChatData;
		m_strChatData = NULL;
	}
	SAFE_DELETE(m_pOutLine[0]);	
	SAFE_DELETE(m_pOutLine[1]);
	SAFE_DELETE(m_pButtonMinimize);
	SAFE_DELETE(m_pImageMinimized);

	SAFE_DELETE(m_pChatDataList);

	SAFE_DELETE(m_pStatic[2]);
	SAFE_DELETE(m_pStatic[1]);
	SAFE_DELETE(m_pStatic[0]);
	SAFE_DELETE(m_pList);
	SAFE_DELETE(m_pButton);
	SAFE_DELETE(m_pMoveButton);
	SAFE_DELETE(m_pEdit);
	SAFE_DELETE(m_pChatEdit);
	SAFE_DELETE(m_pRadioItemGetPattern[3]);
	SAFE_DELETE(m_pRadioItemGetPattern[2]);
	SAFE_DELETE(m_pRadioItemGetPattern[1]);
	SAFE_DELETE(m_pRadioItemGetPattern[0]);
	SAFE_DELETE(m_pBtnStartQuest);
}

void CNPartyDlg::Initialize()
{
	m_bIsPartyLeader = false;
	m_bPartyStatus = false;
	m_siMinimizedSlot = 0;
	m_siItemGetPattern = ITEM_GETPATTERN_ROTATION;

	//	m_bShow = false;

	for ( int i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		m_stClientPartyUser[ i ].Init();
	}

	return;
}

void CNPartyDlg::SendPartyChat()
{
	CObj *pTemp = m_pChatDataList->PopFrontToEmptyListAndPushBackToExistList();
	if ( pTemp == NULL )
	{
		return;
	}

#ifdef _IAF_EXPORT
	if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
	{
		TCHAR ResultBuf[MAX_CHAT_DATA_LENGTH] = "";
		IAF::Filtering( m_strChatData, ResultBuf, sizeof(ResultBuf) );
		memcpy( m_strChatData, ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
	}
#endif

	stPartyChatSend PartyChatSend( m_strChatData ) ;
	pTemp->SetData( (BYTE*)&PartyChatSend, sizeof( stPartyChatSend ) );
}

void CNPartyDlg::AddChat( TCHAR *strUserID, TCHAR *strChatData)
{
//	SI32 PreLineCount = 0, NextLineCount = 0;
//	PreLineCount = SendMessage( m_hRichEdit, EM_GETLINECOUNT, 0, 0 );

	stChatEditData ChatEditData;

	ChatEditData.siChatDataColorIndex = CHATEDIT_COLOR_BLACK;
	ChatEditData.siNameDataColorIndex = CHATEDIT_COLOR_BLUE;

	StringCchCopy( m_strViewData, MAX_RICHEDIT_OBJ_SIZE, TEXT("") );	
	//	strcat( m_strViewData, TEXT("[") );
	//	strcat( m_strViewData, strUserID );
	//	strcat( m_strViewData, TEXT("] : ") );
	StringCchCopy( ChatEditData.strNameData, CHATEDIT_NAMEDATA_LENGTH, strUserID );
	//	AddName( m_strViewData, NameColor );

	StringCchCopy( m_strViewData, MAX_RICHEDIT_OBJ_SIZE, TEXT("") );
	StringCchCat( m_strViewData, MAX_RICHEDIT_OBJ_SIZE, strChatData );
//KHY - 0625 - ��Ƽä�� ���׼���.
//	StringCchCat( m_strViewData, MAX_RICHEDIT_OBJ_SIZE, TEXT("\r\n") );

	StringCchCopy( ChatEditData.strChatData, CHATEDIT_CHATDATA_LENGTH, m_strViewData );
	m_pChatEdit->Insert(&ChatEditData);
	//	AddText( m_strViewData, TextColor );

	//	NextLineCount = SendMessage( m_hRichEdit, EM_GETLINECOUNT, 0, 0 );

	//	SendMessage( m_hRichEdit, EM_LINESCROLL, 0, NextLineCount - PreLineCount );
	return;
/*
	_tcscpy( m_strViewData, TEXT("") );	
	strcat( m_strViewData, TEXT("[") );
	strcat( m_strViewData, strUserID );
	strcat( m_strViewData, TEXT("] : ") );
	AddName( m_strViewData, NameColor );

	_tcscpy( m_strViewData, TEXT("") );
	strcat( m_strViewData, strChatData );
	strcat( m_strViewData, TEXT("\r\n") );
	AddText( m_strViewData, TextColor );
*/	
//	NextLineCount = SendMessage( m_hRichEdit, EM_GETLINECOUNT, 0, 0 );

//	SendMessage( m_hRichEdit, EM_LINESCROLL, 0, NextLineCount - PreLineCount );
	return;
}

void CNPartyDlg::AddChat( TCHAR *strChatData)
{
//	SI32 PreLineCount = 0, NextLineCount = 0;
//	PreLineCount = SendMessage( m_hRichEdit, EM_GETLINECOUNT, 0, 0 );

	stChatEditData ChatEditData;

	ChatEditData.siChatDataColorIndex = CHATEDIT_COLOR_BLACK;
	ChatEditData.siNameDataColorIndex = CHATEDIT_COLOR_BLUE;

	StringCchCopy( m_strViewData, MAX_RICHEDIT_OBJ_SIZE, TEXT("") );
	StringCchCat( m_strViewData, MAX_RICHEDIT_OBJ_SIZE, strChatData );
//KHY - 0625 - ��Ƽä�� ���׼���.
//	StringCchCat( m_strViewData, MAX_RICHEDIT_OBJ_SIZE, TEXT("\r\n") );

	StringCchCopy( ChatEditData.strChatData, CHATEDIT_CHATDATA_LENGTH, m_strViewData );
	m_pChatEdit->Insert(&ChatEditData);
//	AddText( m_strViewData, TextColor );

//	NextLineCount = SendMessage( m_hRichEdit, EM_GETLINECOUNT, 0, 0 );

//	SendMessage( m_hRichEdit, EM_LINESCROLL, 0, NextLineCount - PreLineCount );
	return;
}

void CNPartyDlg::AddName( TCHAR *PlayerName)
{	
/*	SetFont( Color );

	int iTotalTextLength = GetWindowTextLength(m_hRichEdit);
	SendMessage( m_hRichEdit, EM_SETSEL, iTotalTextLength, iTotalTextLength );
	int iStartPos = iTotalTextLength;
	SendMessage( m_hRichEdit, EM_REPLACESEL, 0, (LPARAM)PlayerName );
	
	int iEndPos = GetWindowTextLength(m_hRichEdit);
	SendMessage( m_hRichEdit, EM_SETSEL, iStartPos, iEndPos );

	SendMessage( m_hRichEdit, EM_HIDESELECTION, 1, 0 );
	*/
//	m_pEdit[0]->Insert() >SetText(PlayerName);
	return;
}

void CNPartyDlg::AddText( TCHAR *ChatText)
{	
/*	SetFont( Color );

	int iTotalTextLength = GetWindowTextLength(m_hRichEdit);
	SendMessage( m_hRichEdit, EM_SETSEL, iTotalTextLength, iTotalTextLength );
	int iStartPos = iTotalTextLength;	
	SendMessage( m_hRichEdit, EM_REPLACESEL, 0, (LPARAM)ChatText );	
		
	int iEndPos = GetWindowTextLength(m_hRichEdit);
	SendMessage( m_hRichEdit, EM_SETSEL, iStartPos, iEndPos );
	
	SendMessage( m_hRichEdit, EM_HIDESELECTION, 1, 0 );	
*/
//	m_pEdit[0]->SetText(ChatText);
	return;
}


bool CNPartyDlg::IsPartyStatus()
{
	return m_bPartyStatus;
}

bool CNPartyDlg::IsPartyLeader()
{
	return m_bIsPartyLeader;
}

bool CNPartyDlg::IsPartyUser( SI32 CharUnique )
{
	if ( m_bPartyStatus )
	{
		for ( int i = 0; i < MAX_PARTY_USER_NUM; ++i )
		{
			if ( m_stClientPartyUser[ i ].bPartyStatus && m_stClientPartyUser[ i ].siCharUnique == CharUnique )
			{
				return true;
			}
		}
	}

	return false;
}

SI32 CNPartyDlg::GetPartyIndex()
{
	return m_siPartyIndex;
}

/*
// ��Ƽ¡���μ� ��Ƽ�� ����
void CNPartyDlg::PartyCreate( SI32 PartyIndex )
{
	m_siSelectedUserListIndex = -1;
	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LB_RESETCONTENT, 0, 0 );

	m_siPartyIndex = PartyIndex;

	m_bPartyStatus = true;
	m_bIsPartyLeader = true;

	SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_PARTY_EXPLAIN ), TEXT("��Ƽ�� ����̽��ϴ�."));

//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LB_ADDSTRING, 0, (LPARAM)pclClient->pclCM->CR[1]->GetName() );
	stListBoxItemData Data;
	Data.Set(0, pclClient->pclCM->CR[1]->GetName());
	m_pList->AddItem(&Data);
	m_pList->Refresh();


	m_siPartyUserNum = 1;
	m_stClientPartyUser[ 0 ].bPartyStatus = true;
	m_stClientPartyUser[ 0 ].bIsPartyLeader = true;
	m_stClientPartyUser[ 0 ].siCharUnique = pclClient->pclCM->CR[1]->GetCharUnique();
	_tcscpy ( m_stClientPartyUser[ 0 ].strCharName, pclClient->pclCM->CR[1]->GetName() );

	Show();

	PrintUserNum();

	return;
}
*/

void CNPartyDlg::PartyCreateJoin( SI32 PartyIndex, SI32 LeaderPersonID, SI32 LeaderCharUnique, TCHAR *strLeaderChatName, SI32 LeaderLevel, cltCharPos* LeaderCharPos , SI32 MemberPersonID, SI32 MemberCharUnique, TCHAR *strMemberCharName, SI32 MemberLevel, cltCharPos* MemberCharPos )
{
	m_siSelectedUserListIndex = -1;
//	ListView_DeleteAllItems( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ) );
	m_pList->Clear();

	m_siPartyIndex = PartyIndex;

	m_bPartyStatus = true;

	if ( pclClient->pclCM->CR[1]->pclCI->GetPersonID() == LeaderPersonID )
	{
		m_bIsPartyLeader = true;
		ItemGetPatternButtonEnable(true);
		TCHAR* pText = GetTxtFromMgr(1990);
		AddChat( pText);
	}
	else
	{
		m_bIsPartyLeader = false;
		//SetWindowText( GetDlgItem( m_hDlg, IDC_PARTY_CHAT ), TEXT("��Ƽ�� �����ϼ̽��ϴ�. ��Ƽ�� �߰� 1��� 10%�� ����ġ�� �� ���� �� �ֽ��ϴ�."));
		TCHAR* pText = GetTxtFromMgr(1991);
		AddChat(pText);
	}

	m_stClientPartyUser[ 0 ].bPartyStatus = true;
	m_stClientPartyUser[ 0 ].bIsPartyLeader = true;
	m_stClientPartyUser[ 0 ].siCharUnique = LeaderCharUnique;
	m_stClientPartyUser[ 0 ].siLevel = LeaderLevel;
	StringCchCopy( m_stClientPartyUser[ 0 ].strCharName, MAX_PLAYER_NAME, strLeaderChatName );
	m_stClientPartyUser[ 0 ].clCharPos.Set(LeaderCharPos);

	m_stClientPartyUser[ 1 ].bPartyStatus = true;
	m_stClientPartyUser[ 1 ].bIsPartyLeader = false;
	m_stClientPartyUser[ 1 ].siCharUnique = MemberCharUnique;
	m_stClientPartyUser[ 1 ].siLevel = MemberLevel;
	StringCchCopy( m_stClientPartyUser[ 1 ].strCharName, MAX_PLAYER_NAME, strMemberCharName );
	m_stClientPartyUser[ 1 ].clCharPos.Set(MemberCharPos);

	stListBoxItemData Data;

	LVITEM Li;
	Li.mask = LVIF_TEXT;
	Li.state = 0;
	Li.stateMask = 0;	

	Li.iItem = 0;
	Li.iSubItem = 0;
	Li.pszText = m_stClientPartyUser[ 0 ].strCharName;
//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LVM_INSERTITEM, 0, (LPARAM)&Li );
	
	Data.Set(0, Li.pszText);
	
	TCHAR strLevel1[32] = TEXT("");
	TCHAR strLevel2[32] = TEXT("");

	Li.iSubItem = 1;
	StringCchPrintf( strLevel1, 32, TEXT("%d"), m_stClientPartyUser[0].siLevel );
	Li.pszText = strLevel1;
//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LVM_SETITEM, 0, (LPARAM)&Li );

	Data.Set(1, Li.pszText);

	Li.iSubItem = 2;
	Li.pszText = TEXT("0");
//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LVM_SETITEM, 0, (LPARAM)&Li );
	Data.Set(2, Li.pszText);
	

	// ��ġ�� �⺻���� ���ε��� 0(�߿�����) �� �̸��̴�.
	// ��ġ�˸�����

	//���� �����̸� ù��° ���� ��ġ ���� �� �� �ε����� �̸��� �־��ش�.

	Li.iSubItem = 3; 
	Li.pszText = pclClient->pclMapManager->GetMapName( LeaderCharPos->GetMapIndex() );
	Data.Set(3, Li.pszText)	;
	
	Data.ColumnColor[0] = ColorIndex[0];
	Data.ColumnColor[1] = ColorIndex[0];
	Data.ColumnColor[2] = ColorIndex[0];
	Data.ColumnColor[3] = ColorIndex[0];
	
	m_pList->AddItem(&Data);

	Li.iItem = 1;
	Li.iSubItem = 0;
	Li.pszText = m_stClientPartyUser[ 1 ].strCharName;
	
//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LVM_INSERTITEM, 0, (LPARAM)&Li );
	Data.Set(0, Li.pszText);

	Li.iSubItem = 1;
	StringCchPrintf( strLevel2, 32, TEXT("%d"), m_stClientPartyUser[1].siLevel );
	Li.pszText = strLevel2;
//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LVM_SETITEM, 0, (LPARAM)&Li );

	Data.Set(1, Li.pszText);


	Li.iSubItem = 2;
	Li.pszText = TEXT("0");
//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LVM_SETITEM, 0, (LPARAM)&Li );

	Data.Set(2, Li.pszText);
	// ��ġ�˸�����

	//���� ������ �ι�° ���� ��ġ ���� ���̸��� �־��ش�.
	Li.iSubItem = 3; 
	Li.pszText = pclClient->pclMapManager->GetMapName( MemberCharPos->GetMapIndex() );
	Data.Set(3, Li.pszText)	;
	
	Data.ColumnColor[0] = ColorIndex[1];
	Data.ColumnColor[1] = ColorIndex[1];
	Data.ColumnColor[2] = ColorIndex[1];
	Data.ColumnColor[3] = ColorIndex[1];

	m_pList->AddItem(&Data);

	m_pList->Refresh();

	m_siPartyUserNum = 2;
	PrintUserNum();

	pclClient->pclCM->CR[1]->siPartyIndex = PartyIndex;

	Show();

	return;
}

void CNPartyDlg::PartyJoin( SI32 PartyIndex, SI16 UserListIndex ,SI16 ItemGetPattern )
{
	m_siSelectedUserListIndex = -1;
	m_pList->Clear();
//	ListView_DeleteAllItems( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ) );

	m_siPartyIndex = PartyIndex;

	m_bPartyStatus = true;
	m_bIsPartyLeader = false;

	m_siPartyUserNum = 0;
	//SetWindowText( GetDlgItem( m_hDlg, IDC_PARTY_CHAT ), TEXT("��Ƽ�� ���� �Ǽ̽��ϴ�. ��Ƽ�� �߰� 1��� 5%�� ����ġ�� �� ���� �� �ֽ��ϴ�.") );
	TCHAR* pText = GetTxtFromMgr(1992);
	AddChat( pText);

	cltGameMsgRequest_Party_AllUserList clPartyAllUserList( m_siPartyIndex );
	cltMsg clMsg(GAMEMSG_REQUEST_PARTY_ALLUSERLIST, sizeof(clPartyAllUserList), (BYTE*)&clPartyAllUserList);
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

	pclClient->pclCM->CR[1]->siPartyIndex = PartyIndex;
	
	ChangeItemGetPattern(ItemGetPattern);

	Show();

	return;
}

void CNPartyDlg::PartyDelete( SI32 PartyIndex )
{
	cltClient *pclclient = (cltClient *)pclClient;
	if ( m_siPartyIndex == PartyIndex )
	{
		TCHAR* pTitle	= GetTxtFromMgr(1993);
		TCHAR* pText	= GetTxtFromMgr(1994);

		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
		pclclient->pclCM->CR[1]->siPartyIndex = 0;
		Hide();

		// [����] ������ : ������ ������ ��Ƽ�� �����Ǿ��� ��� ���縮���� �̵���Ų��
		SI32 siMapIndex		= pclclient->pclCM->CR[1]->GetMapIndex();

		if ( pclclient->pclMapManager->IsPartyMap( siMapIndex ) == true )
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);
			pclclient->pclCM->CR[1]->SetWarpInfo(&clWarpInfo, 56);
			pclclient->pclCM->CR[1]->Warp();
		}

	}

	return;
}

void CNPartyDlg::PartyAddUser( bool PartyLeader, SI32 CharUnique, TCHAR *CharName, SI16 UserListIndex, SI32 Level , cltCharPos* pclCharPos)
{
	m_stClientPartyUser[ UserListIndex ].bPartyStatus = true;
	m_stClientPartyUser[ UserListIndex ].bIsPartyLeader = PartyLeader;
	m_stClientPartyUser[ UserListIndex ].siCharUnique = CharUnique;
	StringCchCopy( m_stClientPartyUser[ UserListIndex ].strCharName, MAX_PLAYER_NAME, CharName );
	m_stClientPartyUser[ UserListIndex ].siLevel = Level;
	m_stClientPartyUser[ UserListIndex ].clCharPos.Set(pclCharPos);

	TCHAR Buffer[ 1024 ] = TEXT("");
	TCHAR* pText = GetTxtFromMgr(1995);
	StringCchPrintf( Buffer, 1024, pText, CharName );
//	int len = sizeof(Buffer);
	//SetWindowText( GetDlgItem( m_hDlg, IDC_PARTY_CHAT ), Buffer );
	AddChat( Buffer);

	++m_siPartyUserNum;

	ReloadPartyUserList();

	PrintUserNum();

	return;
}

void CNPartyDlg::PartyDelUser( SI32 CharUnique, SI16 UserListIndex )
{
	if ( m_stClientPartyUser[ UserListIndex ].siCharUnique == CharUnique )
	{
		if ( CharUnique == pclClient->pclCM->CR[1]->GetCharUnique() )
		{
			m_siSelectedUserListIndex = -1;
		//	ListView_DeleteAllItems( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ) );
			m_pList->Clear();

			m_stClientPartyUser[ UserListIndex ].Init();

			--m_siPartyUserNum;

			Hide();
			return;
		}

		TCHAR Buffer[256 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(1996);
		StringCchPrintf( Buffer, 256, pText, m_stClientPartyUser[ UserListIndex ].strCharName );
		//SetWindowText( GetDlgItem( m_hDlg, IDC_PARTY_CHAT ), Buffer );
		AddChat( Buffer);
		m_stClientPartyUser[ UserListIndex ].Init();

		--m_siPartyUserNum;

		ReloadPartyUserList();
	}

	if ( m_siPartyUserNum < 1 )
	{
		Hide();
	}

	PrintUserNum();

	return;
}

void CNPartyDlg::PartyForceDelUser( SI32 CharUnique, SI16 UserListIndex )
{
	cltClient *pclclient = (cltClient *)pclClient;
	if ( m_stClientPartyUser[ UserListIndex ].siCharUnique == CharUnique )
	{
		if ( CharUnique == pclClient->pclCM->CR[1]->GetCharUnique() )
		{
			m_siSelectedUserListIndex = -1;
		//	ListView_DeleteAllItems( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ) );
			m_pList->Clear();
			Hide();
			TCHAR* pTitle = GetTxtFromMgr(1997);
			TCHAR* pText = GetTxtFromMgr(1998);
			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		TCHAR Buffer[256 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(1999);
		StringCchPrintf( Buffer, 256, pText, m_stClientPartyUser[ UserListIndex ].strCharName );

		//SetWindowText( GetDlgItem( m_hDlg, IDC_PARTY_CHAT ), Buffer );
		AddChat( Buffer);
		m_stClientPartyUser[ UserListIndex ].Init();
		--m_siPartyUserNum;

		ReloadPartyUserList();
	}

	PrintUserNum();

	return;
}

void CNPartyDlg::PartyChangeLeader( SI32 CharUnique, SI16 UserListIndex )
{
	if ( m_stClientPartyUser[ UserListIndex ].siCharUnique == CharUnique )
	{
		m_stClientPartyUser[ UserListIndex ].bIsPartyLeader = true;
		m_stClientPartyUser[ 0 ].Set( &m_stClientPartyUser[ UserListIndex ] );
		m_stClientPartyUser[ UserListIndex ].Init();

		// �� Ŭ���̾�Ʈ�� ��Ƽ���� �� ���
		if ( m_stClientPartyUser[0].siCharUnique == pclClient->pclCM->CR[1]->GetCharUnique() )
		{
			m_bIsPartyLeader = true; 
			ItemGetPatternButtonEnable(true);
		}

		ReloadPartyUserList();
	}

	return;
}

void CNPartyDlg::PartyNotifyExp( SI32 CharUnique, SI16 UserListIndex, SI32 Exp )
{
	if ( m_stClientPartyUser[ UserListIndex ].siCharUnique == CharUnique && Exp > 0 )
	{
		m_stClientPartyUser[ UserListIndex ].siExp = Exp;
		ReloadPartyUserList();
	}

	return;
}

SI32 CNPartyDlg::FindUserSelectedIndex( TCHAR *CharName )
{
	for ( int i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stClientPartyUser[ i ].bPartyStatus )
		{
			if ( _tcscmp( m_stClientPartyUser[ i ].strCharName, CharName ) == 0 )
			{
				return i;
			}
		}
	}

	return -1;
}

void CNPartyDlg::PrintUserNum()
{
	TCHAR Buffer[256] = TEXT("");
	TCHAR* pText = GetTxtFromMgr(2000);
	StringCchPrintf( Buffer, 256, pText, m_siPartyUserNum, MAX_PARTY_USER_NUM );

//	SetWindowText( GetDlgItem( m_hDlg, IDC_STATIC_PARTY_USER_NUM ), Buffer );
	m_pStatic[0]->SetText(Buffer, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return;
}

void CNPartyDlg::ReloadPartyUserList()
{
	m_siSelectedUserListIndex = -1;
	m_pList->Clear();
//	ListView_DeleteAllItems( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ) );
	
	LVITEM Li;
	Li.mask = LVIF_TEXT;
	Li.state = 0;
	Li.stateMask = 0;	

	Li.iItem = 0;	
	Li.iSubItem = 0;

	SI32 Count = 0;
	TCHAR strExp[32];
	TCHAR strLevel[32];
	stListBoxItemData Data;
	for ( int i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stClientPartyUser[ i ].bPartyStatus )
		{
			Li.iItem = Count;
			Li.iSubItem = 0;			
			Li.pszText = m_stClientPartyUser[ i ].strCharName;
			Data.Set(0, Li.pszText);
		//	SendMessage( GetDlgItem( m_hDlg, IDC_LIST_PARTY_USER ), LVM_INSERTITEM, 0, (LPARAM)&Li );

			Li.iSubItem = 1;
			StringCchPrintf( strLevel, 32, TEXT("%d"), m_stClientPartyUser[ i ].siLevel );
			Li.pszText = strLevel;
			Data.Set(1, Li.pszText);
	
			Li.iSubItem = 2;
			StringCchPrintf( strExp, 32, TEXT("%d"), m_stClientPartyUser[ i ].siExp );
			Li.pszText = strExp;
			Data.Set(2, Li.pszText);
	

			Li.iSubItem = 3; 

			if(m_stClientPartyUser[ i ].siCharUnique == pclClient->pclCM->CR[1]->GetCharUnique())
				Li.pszText = pclClient->pclMapManager->GetMapName( pclClient->pclCM->CR[1]->GetMapIndex() );
			else
				Li.pszText = pclClient->pclMapManager->GetMapName( m_stClientPartyUser[i].clCharPos.GetMapIndex() );
				
			Data.Set(3, Li.pszText)	;
			
			Data.ColumnColor[0] = ColorIndex[Count];
			Data.ColumnColor[1] = ColorIndex[Count];
			Data.ColumnColor[2] = ColorIndex[Count];
			Data.ColumnColor[3] = ColorIndex[Count];
	
			m_pList->AddItem(&Data);
			

			Count++;
		}
	}
	m_pList->Refresh();

	return;
}

bool CNPartyDlg::PopPartyChatSendData( stPartyChatSend *pPartyChatSend )
{
	CObj *pFirst = m_pChatDataList->GetExistList()->GetFirst();

	if ( pFirst == NULL )
	{
		return false;
	}

	UI32 uiSize;
	pFirst->GetData( (BYTE*)pPartyChatSend, &uiSize );

	m_pChatDataList->GetExistList()->Pop( pFirst );
	m_pChatDataList->PushBackToEmptyList( pFirst );

	return true;
}

void CNPartyDlg::Create()
{
	CInterfaceFile file;

	file.LoadFile(TEXT("NInterface/Data/DLG_NParty.ddf"));
	file.CreatePopupDialog( this, NPARTY_DLG, TEXT("dialog_Party"), StaticCallBackDialogNPartyDlg );

	if(gsiResolution == 2 ||gsiResolution == 4) // 1024x768 || 1024x600
	{
		MovePos( 620, 220 );		
	}	
	else
	{
		MovePos( 554, 66 );
	}
	
	m_pOutLine[0] = new COutLine(this);
	m_pOutLine[1] = new COutLine(this);
	m_pButtonMinimize = new CButton(this);
	m_pImageMinimized = new CImageStatic(this);

	m_pRadioItemGetPattern[0] = new CRadioButton(this);
	m_pRadioItemGetPattern[1] = new CRadioButton(this);
	m_pRadioItemGetPattern[2] = new CRadioButton(this);
	m_pRadioItemGetPattern[3] = new CRadioButton(this);

	m_pStatic[0] = new CStatic( this );
	m_pStatic[1] = new CStatic( this );
	m_pStatic[2] = new CStatic( this );
	m_pList = new CList( this );
	m_pButton = new CButton( this );
	NEWCBUTTON(m_pMoveButton);
	m_pEdit = new CEdit( this );

	m_pChatEdit = new CChatEdit( this );
	m_pBtnStartQuest = new CButton(this);
	
	
	file.CreateControl(m_pButtonMinimize,NPRATY_DIALOG_BUTTON_MINIMIZE, TEXT("button_minimize"));
	file.CreateControl(m_pImageMinimized, NPARTY_DIALOG_IMAGESTATIC_MINIMIZED, TEXT("imagestatic_minimize"));
	file.CreateControl( m_pRadioItemGetPattern[0], NPARTY_DIALOG_RADIO1, TEXT("radiobutton_NONAME1"));
	file.CreateControl( m_pRadioItemGetPattern[1], NPARTY_DIALOG_RADIO2, TEXT("radiobutton_NONAME2"));
	file.CreateControl( m_pRadioItemGetPattern[2], NPARTY_DIALOG_RADIO3, TEXT("radiobutton_NONAME3"));
	file.CreateControl( m_pRadioItemGetPattern[3], NPARTY_DIALOG_RADIO4, TEXT("radiobutton_NONAME4"));

	file.CreateControl( m_pStatic[0], NPARTY_DIALOG_STATIC1, TEXT("statictext_Party_User_Num"));  
	file.CreateControl( m_pStatic[1], NPARTY_DIALOG_STATIC2, TEXT("statictext_NONAME1"));  // �׳� ��Ƽ ä�� ����
	file.CreateControl( m_pStatic[2], NPARTY_DIALOG_STATIC3, TEXT("statictext_NONAME2")); // �׳� ȹ�� ��� ����
	file.CreateControl( m_pList,   NPARTY_DIALOG_LIST,   TEXT("listbox_Party_list"));  
	file.CreateControl( m_pButton, NPARTY_DIALOG_BUTTON, TEXT("button_Party_Leave"));  
	file.CreateControl( m_pMoveButton, NPARTY_DIALOG_MOVE_BUTTON, TEXT("button_NONAME1"));  
	file.CreateControl( m_pEdit, NPARTY_DIALOG_EDIT1, TEXT("editbox_NONAME1"));	// ��Ƽ�� ���� ǥ��ǥ��
	file.CreateControl( m_pChatEdit, NPARTY_DIALOG_CHATEDIT, TEXT("chatedit_NONAME1"));	// ��Ƽ�� ���� ǥ��ǥ��
	file.CreateControl(m_pOutLine[0],NPARTY_DIALOG_OUTLINE, TEXT("outline_NONAME1"));
	file.CreateControl(m_pOutLine[1],NPARTY_DIALOG_OUTLINE, TEXT("outline_NONAME2"));
	file.CreateControl(m_pBtnStartQuest,NPARTY_DIALOG_STARTQUEST, TEXT("button_Party_quest"));

	m_pChatEdit->SetBorder( true );
	m_pChatEdit->SetBKColorUse( true );
	m_pChatEdit->Show(TRUE);

	// ��Ƽ����Ʈ ��ư�� �Ⱥ��̴� ���·� ����
	m_pBtnStartQuest->Show( false );
	m_pBtnStartQuest->Refresh();

	TCHAR* pText = GetTxtFromMgr(3413);
	m_pList->SetColumn(0, 100, pText);

	pText = GetTxtFromMgr(4008);
	m_pList->SetColumn(1, 30,  pText);

	pText = GetTxtFromMgr(1985);
	m_pList->SetColumn(2, 100, pText);

	pText = GetTxtFromMgr(1611);
	m_pList->SetColumn(3, 100, pText);

	m_pList->SetBorder(TRUE);
	m_pList->SetBKColorUse(TRUE);
	m_pList->Refresh();
	
	m_pRadioItemGetPattern[0]->SetNonEventCheck();
	
	m_pImageMinimized->Show(false);
	ItemGetPatternButtonEnable(false);
	CControllerMgr::Show( false );

	SetActionTimer( 200 );	
	SetTimerOnOff( true );


}


void CALLBACK CNPartyDlg::StaticCallBackDialogNPartyDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNPartyDlg *pThis = (CNPartyDlg *)pControllerMgr;
	pThis->CallBackDialogNPartyDlg( nEvent, nControlID, pControl );

}

void CALLBACK CNPartyDlg::CallBackDialogNPartyDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient *)pclClient;


	switch ( nControlID )
	{
//	case COMMON_DIALOG_CLOSEBUTTON:
//		{
//			DeleteDialog();
//		}
//		break;
	//case COMMON_DIALOG_CLOSEBUTTON:		Minimi(TRUE);		break;

	case NPARTY_DIALOG_RADIO1:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if(m_pRadioItemGetPattern[0]->IsCheck())
					{   // �̹� �����Ǿ� �ִ� ���°ų�, ��Ƽ�� ������ �ƴ϶��, ��ư�� ��Ȱ��ȭ �Ǿ��ִٸ� �޽��� �Ⱥ���
						if(m_siItemGetPattern == ITEM_GETPATTERN_ROTATION || m_bIsPartyLeader == false 
							|| m_pRadioItemGetPattern[0]->IsEnable() == false) 
							break;
						
						m_siItemGetPattern = ITEM_GETPATTERN_ROTATION;

						// ������ �ٲ�°��̸� ��Ƽ�� �����̸� ��ư�� Ȱ��ȭ �Ǿ��ִٸ� ��Ƽ�� �������� �޽��� ����(�ڽ��� ����?)
						cltGameMsgRequest_Party_ChangeItemGetPattern clinfo( ITEM_GETPATTERN_ROTATION );
						cltMsg clMsg(GAMEMSG_REQUEST_PARTY_CHANGEITEMGETPATTERN, sizeof(clinfo) ,(BYTE*)&clinfo);
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);			
					}
				}
				break;
			}
		}
		break;
	case NPARTY_DIALOG_RADIO2:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if(m_pRadioItemGetPattern[1]->IsCheck())
					{   // �̹� �����Ǿ� �ִ� ���°ų�, ��Ƽ�� ������ �ƴ϶��, ��ư�� ��Ȱ��ȭ �Ǿ��ִٸ� �޽��� �Ⱥ���
						if(m_siItemGetPattern == ITEM_GETPATTERN_NORMAL || m_bIsPartyLeader == false 
							|| m_pRadioItemGetPattern[1]->IsEnable() == false) 
							break;

						// ������ �ٲ�°��̸� ��Ƽ�� �����̸� ��ư�� Ȱ��ȭ �Ǿ��ִٸ� ��Ƽ�� �������� �޽��� ����(�ڽ��� ����?)                 
						m_siItemGetPattern = ITEM_GETPATTERN_NORMAL;
						cltGameMsgRequest_Party_ChangeItemGetPattern clinfo( ITEM_GETPATTERN_NORMAL );
						cltMsg clMsg(GAMEMSG_REQUEST_PARTY_CHANGEITEMGETPATTERN, sizeof(clinfo) ,(BYTE*)&clinfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);			
					}
				}
				break;
			}
		}
		break;
	case NPARTY_DIALOG_RADIO3:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if(m_pRadioItemGetPattern[2]->IsCheck())
					{ // �̹� �����Ǿ� �ִ� ���°ų�, ��Ƽ�� ������ �ƴ϶��, ��ư�� ��Ȱ��ȭ �Ǿ��ִٸ� �޽��� �Ⱥ���
						if(m_siItemGetPattern == ITEM_GETPATTERN_FINISH || m_bIsPartyLeader == false 
							|| m_pRadioItemGetPattern[2]->IsEnable() == false) 
							break;

						// ������ �ٲ�°��̸� ��Ƽ�� �����̸� ��ư�� Ȱ��ȭ �Ǿ��ִٸ� ��Ƽ�� �������� �޽��� ����(�ڽ��� ����?)                   
						m_siItemGetPattern = ITEM_GETPATTERN_FINISH;
						cltGameMsgRequest_Party_ChangeItemGetPattern clinfo( ITEM_GETPATTERN_FINISH );
						cltMsg clMsg(GAMEMSG_REQUEST_PARTY_CHANGEITEMGETPATTERN, sizeof(clinfo) ,(BYTE*)&clinfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);			
					}
				}
				break;
			}
		}
		break;
	case NPARTY_DIALOG_RADIO4:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if(m_pRadioItemGetPattern[3]->IsCheck())
					{ // �̹� �����Ǿ� �ִ� ���°ų�, ��Ƽ�� ������ �ƴ϶��, ��ư�� ��Ȱ��ȭ �Ǿ��ִٸ� �޽��� �Ⱥ���
						if(m_siItemGetPattern == ITEM_GETPATTERN_RANDOM || m_bIsPartyLeader == false 
							|| m_pRadioItemGetPattern[3]->IsEnable() == false) 
							break;

						// ������ �ٲ�°��̸� ��Ƽ�� �����̸� ��ư�� Ȱ��ȭ �Ǿ��ִٸ� ��Ƽ�� �������� �޽��� ����(�ڽ��� ����?)                    
						m_siItemGetPattern = ITEM_GETPATTERN_RANDOM;
						cltGameMsgRequest_Party_ChangeItemGetPattern clinfo( ITEM_GETPATTERN_RANDOM );
						cltMsg clMsg(GAMEMSG_REQUEST_PARTY_CHANGEITEMGETPATTERN, sizeof(clinfo) ,(BYTE*)&clinfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);			
					}
				}
				break;
			}
		}
		break;
	case NPARTY_DIALOG_LIST:
		{
			switch( nEvent )
			{
			case EVENT_LISTBOX_SELECTION:
				{
					SI32 TempSelectIndex = m_pList->GetSelectedIndex();

					if(TempSelectIndex < 0)
						break;

					m_siSelectedUserListIndex = TempSelectIndex;
				}
				break;
			}
			
		}
		break;

	case NPRATY_DIALOG_BUTTON_MINIMIZE: 
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					Minimi(TRUE);
				}
				break;
			}
		}
		break;
	
	case NPARTY_DIALOG_IMAGESTATIC_MINIMIZED:
		{
			switch( nEvent )
			{
			case EVENT_IMAGESTATIC_LBUTTONUP:
				{
					Minimi(FALSE);
				}
				break;
			}
		}
		break;


	case NPARTY_DIALOG_MOVE_BUTTON:	// ��Ƽ������ �����̵�
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if ( m_siSelectedUserListIndex >= 0 )
					{
						SI16 siSelectedPartyIndex = -1;
						TCHAR* szSelectedUserName = m_pList->GetText(m_siSelectedUserListIndex,0);

						// �̸��� ������ �Ұ���
						if( szSelectedUserName == NULL) 
							return;						

						// �ڽſ��Է��� ������� �Ұ���
						if(_tcscmp(pclclient->pclCM->CR[1]->GetName(),szSelectedUserName) == 0  ) 
							return;
						
												
						for(SI16 i = 0; i < MAX_PARTY_USER_NUM; i++)
						{
							// ������ �̸��� ã�� ��Ƽ �ε����� ã�´�.
							if(  _tcscmp(m_stClientPartyUser[i].strCharName , szSelectedUserName ) == 0 )
							{
								siSelectedPartyIndex = i;
								break;
							}
						}	

						// ���һ�. ���õ� ��Ƽ���� ����.
						if( siSelectedPartyIndex < 0 ) 
							return;											

						TCHAR buffer[256] = TEXT("") ;
						TCHAR * pText = NULL ;

						// ĳ���Ͱ� ������ �� �� �ִ°�?
						if( pclclient->pclCM->CR[1]->CanWarpFrom() == false )
							return;

						// ��¥ ���� üũ
						if( pclclient->pclCM->CR[1]->CanFreeWarp( 0 ) == false )
						{
							SI32 itemunique = ITEMUNIQUE(24000) ;  // �����̵��̿��
							if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
							{
								TCHAR* pText = GetTxtFromMgr(3756);
								StringCchPrintf(buffer, 256, pText);
								pText = GetTxtFromMgr(3326);
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pText, buffer);
								return;
							}

							pText = GetTxtFromMgr(5184);
							StringCchPrintf(buffer, 256, pText,m_stClientPartyUser[ siSelectedPartyIndex ].strCharName);
						}
						else
						{
							pText = GetTxtFromMgr(5185);
							StringCchPrintf(buffer, 256, pText,m_stClientPartyUser[ siSelectedPartyIndex ].strCharName);
						}

						stMsgBox MsgBox;
						pText = GetTxtFromMgr(5183);
						MsgBox.Set( this, pText, buffer, MSGBOX_TYPE_YESNO, 2);
												
						pclclient->SetMsgBox( &MsgBox, (BYTE*)m_stClientPartyUser[ siSelectedPartyIndex ].strCharName , MAX_PLAYER_NAME );
					}
				}
				break;
			}
		}
		break;

	case NPARTY_DIALOG_BUTTON:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:	// ���� Ȯ�� ���̾�α� �˾�
				{		// ��Ƽ�� �̸鼭 �ڱ� �ڽ��� �ƴ� ���� ����������
					SI16 siSelectedPartyIndex = 0;
					TCHAR* szSelectedUserName = m_pList->GetText(m_siSelectedUserListIndex,0);
					if( szSelectedUserName == NULL) 
					{	// ���õ� �ε����� ���ų� �̸��� ���ٸ� �ڱ� �ڽ��� ��ƼŻ���Ų��.
						siSelectedPartyIndex = 0;
					}
					else
					{
						for(SI16 i = 0; i < MAX_PARTY_USER_NUM; i++)
						{
							// ������ �̸��� ã�� ��Ƽ �ε����� ã���ش�
							if(  _tcscmp(m_stClientPartyUser[i].strCharName , szSelectedUserName ) == 0 )
							{
								siSelectedPartyIndex = i;
								break;
							}
						}
					}
					if ( m_bIsPartyLeader && siSelectedPartyIndex > 0 )
					{
						TCHAR Buffer[256 ] = TEXT("");
						TCHAR* pText = GetTxtFromMgr(1986);
						StringCchPrintf( Buffer, 256, pText, m_stClientPartyUser[ siSelectedPartyIndex ].strCharName );

						TCHAR* pTitle = GetTxtFromMgr(1987);

						stMsgBox MsgBox;
						MsgBox.Set( this,  pTitle, Buffer, MSGBOX_TYPE_YESNO, 0 );
						BYTE TempBuffer[ 128 ];
						SI16 Size = sizeof( m_siPartyIndex ) + sizeof(m_stClientPartyUser[ siSelectedPartyIndex ].siCharUnique);
						memcpy( TempBuffer, &m_siPartyIndex, sizeof(m_siPartyIndex) );
						memcpy( &TempBuffer[ sizeof(m_siPartyIndex) ] , &m_stClientPartyUser[ siSelectedPartyIndex ].siCharUnique, sizeof(m_stClientPartyUser[ siSelectedPartyIndex ].siCharUnique) );
						pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
					}
					// ��Ƽ���� �ƴҶ� ( �ڱ� �ڽŸ� ������ )
					else
					{
						TCHAR* pText = GetTxtFromMgr(1988);
						TCHAR* pTitle = GetTxtFromMgr(1987);

						stMsgBox MsgBox;
						MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 1 );
						BYTE TempBuffer[ 128 ];
						SI16 Size = sizeof( m_siPartyIndex );
						memcpy( TempBuffer, &m_siPartyIndex, Size );
						pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
				
					}
				}
				break;
			}
			
		}
		break;

	case NPARTY_DIALOG_EDIT1:
		{
			switch( nEvent )
			{
//			case EVENT_EDITBOX_CHANGE:
			case EVENT_EDITBOX_STRING:
				{
					memset( m_strChatData, 0, MAX_CHAT_DATA_LENGTH );
				//	GetWindowText( hWnd, m_strChatData, MAX_CHAT_DATA_LENGTH );
				//	m_strChatData = m_pEdit->GetText();
					MStrCpy(m_strChatData, m_pEdit->GetText(), MAX_CHAT_DATA_LENGTH);

					// ��Ʈ���� ���̰� 0���� ū ��츸 ����. 
					// �ߺ��� ä�� �����͵� ���ƾ� ��... ( �峭��� ��� ���� �� �����Ƿ�.. )
					if ( _tcslen( m_strChatData ) > 0 )
					{
						SendPartyChat();
					//	SetWindowText( m_hChatDataInputEdit, TEXT("") );
						m_pEdit->SetText(TEXT(""));

					}
				//	else if (wParam == VK_ESCAPE )
				//	{
				//		SetWindowText( m_hChatDataInputEdit, TEXT("") );
				//	}
				}
				break;
			}
		}
		break;

	case NPARTY_DIALOG_STARTQUEST:		// ��Ƽ����Ʈ ����
		{
			switch(nEvent)
			{
				case EVENT_BUTTON_CLICKED:
					{
						// ��Ƽ����Ʈ �ӹ��� �ο� ������ �ִ� ��Ƽ���� üũ �մϴ�.
						// �ش� üũ�� Ŭ���̾�Ʈ�� ���� ���ʿ��� üũ �մϴ�.

						cltClient* pClient = (cltClient*)pclClient;

						bool bResult = pClient->m_pPartyQuestMgr->DoCheckPartyQuest(m_siPartyUserNum, m_stClientPartyUser);

						if(bResult == true)
						{
							cltGameMsgRequest_PartyQuest_CheckStart clData(GetPartyIndex());
							cltMsg clMsg(GAMEMSG_REQUEST_PARTY_QUEST_CHECKSTART, sizeof(cltGameMsgRequest_PartyQuest_CheckStart), (BYTE*)&clData);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);														
						}
						else
						{
							StartPartyQuestMessage(false);
						}
					}
					break;
			}
		}
		break;
	}
}

void CNPartyDlg::Hide()
{
	Initialize();				// ��Ƽ�� ����Ǿ����Ƿ� ������ �ִ� �������� �ʱ�ȭ ����
	
	ItemGetPatternButtonEnable(false);
	m_pRadioItemGetPattern[0]->SetNonEventCheck();

	m_siPartyUserNum = 0;

	m_bIsPartyLeader = false;
	m_bPartyStatus = false;

	m_pList->Clear();

	if ( m_strViewData )
	{	
		memset( m_strViewData, 0, MAX_RICHEDIT_OBJ_SIZE );
	}

	if ( m_strChatData )
	{
		memset( m_strChatData, 0, MAX_CHAT_DATA_LENGTH );
	}	

	m_siSelectedUserListIndex = -1;

	TCHAR* pText = GetTxtFromMgr(1989);
//	SetWindowText( GetDlgItem( m_hDlg, IDC_STATIC_PARTY_USER_NUM ), pText );
	m_pStatic[0]->SetText(pText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	CControllerMgr::Show( false );
}

void CNPartyDlg::Show()
{	
	if(IsMinimi() == TRUE) Minimi(FALSE);
	
	
	///////////
	
	//��Ƽȹ�渷��
	//m_pRadioItemGetPattern[1]->SetNonEventCheck();
	//ItemGetPatternButtonEnable(false);


	CControllerMgr::Show( true );	
	SetFocus(m_pEdit);
}

void CNPartyDlg::EnableButton(CButton* pButton, TCHAR* pText, BOOL Flag /* = false */)
{
	if(Flag)
	{
		pButton->SetFontColor(RGB(0, 0, 0));
		pButton->SetText(pText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pButton->Enable(true);
	}
	else
	{
		pButton->SetFontColor(RGB(225, 225, 225));
		pButton->SetText(pText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pButton->Enable(false);
	}
}

void CNPartyDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient*)pclClient;

	switch( MsgIndex )
	{
	case 0:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}
			if ( RetValue )
			{
				cltGameMsgRequest_Party_ForceLeave clPartyForceLeave( *((SI32*)pData), *((SI32*)&pData[4]) );
				cltMsg clMsg(GAMEMSG_REQUEST_PARTY_FORCELEAVE, sizeof(clPartyForceLeave), (BYTE*)&clPartyForceLeave);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		break;

	case 1:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}
			if ( RetValue )
			{
				cltGameMsgRequest_Party_Leave clPartyLeave( *((SI32*)pData) );
				cltMsg clMsg(GAMEMSG_REQUEST_PARTY_LEAVE, sizeof(clPartyLeave), (BYTE*)&clPartyLeave);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				Hide();
			}
		}
		break;

	case 2:
		{
			if( RetValue )
			{
				cltGameMsgRequest_PartyWarp clinfo((TCHAR*)pData );
				cltMsg clMsg(GAMEMSG_REQUEST_PARTYWARP,sizeof(clinfo),(BYTE*)&clinfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
			else
				return;
		}
		break;

	case 3:
		{
			if( RetValue )
			{
				// ��Ƽ����Ʈ ���� Ȯ�ν� ������ �Դϴ�.

				// 1.������ ��Ƽ����Ʈ �ӹ� �ο� ��û �մϴ�.
				cltGameMsgRequest_PartyQuest_Start clData(GetPartyIndex());
				cltMsg clMsg(GAMEMSG_REQUEST_PARTY_QUEST_START, sizeof(cltGameMsgRequest_PartyQuest_Start), (BYTE*)&clData);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);															
			}
		}
		break;

	case 4:
		{
			if( RetValue )
			{
				// ��Ƽ�� �ʴ�� ��Ƽ����Ʈ�� ����ɼ� �ִٴ� �޼����� �����ݴϴ�.

				cltGameMsgRequest_Party_Invite clPartyInvite( m_siInviteCharUniqueForPartyQuest, GetPartyIndex() );
				cltMsg clMsg( GAMEMSG_REQUEST_PARTY_INVITE, sizeof( clPartyInvite ), (BYTE*)&clPartyInvite );
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		break;
	}
}

void CNPartyDlg::ItemGetPatternButtonEnable(bool bEnable)
{
	m_pRadioItemGetPattern[0]->Enable(bEnable);
	m_pRadioItemGetPattern[1]->Enable(bEnable);
	m_pRadioItemGetPattern[2]->Enable(bEnable);
	m_pRadioItemGetPattern[3]->Enable(bEnable);

}

void CNPartyDlg::ChangeItemGetPattern( SI16 ItemGetPattern )
{
  	cltClient* pclclient = (cltClient*)pclClient;

	// ������ �ٲ���� �ƴ϶�� �ƹ� ��ȭ �ʿ� ���� ����
	/*
	if( m_siItemGetPattern == ItemGetPattern )
		return;
	*/
	m_siItemGetPattern = ItemGetPattern;

	TCHAR DestTxt[256] = TEXT("");
	TCHAR *pPatternChangeMsg = GetTxtFromMgr(5850);	
	TCHAR *pText = NULL;

	if(ItemGetPattern == ITEM_GETPATTERN_ROTATION)
	{
		m_pRadioItemGetPattern[0]->SetNonEventCheck();
		pText = GetTxtFromMgr(5845);
		StringCchPrintf(DestTxt,256,pPatternChangeMsg,pText);
	}
	else if(ItemGetPattern == ITEM_GETPATTERN_NORMAL)
	{
		m_pRadioItemGetPattern[1]->SetNonEventCheck();
		pText = GetTxtFromMgr(5848);
		StringCchPrintf(DestTxt,256,pPatternChangeMsg,pText);
	} 
	else if(ItemGetPattern == ITEM_GETPATTERN_FINISH)
	{
		m_pRadioItemGetPattern[2]->SetNonEventCheck();
		pText = GetTxtFromMgr(5846);
		StringCchPrintf(DestTxt,256,pPatternChangeMsg,pText);
	}
	else if(ItemGetPattern == ITEM_GETPATTERN_RANDOM)
	{
		m_pRadioItemGetPattern[3]->SetNonEventCheck();
		pText = GetTxtFromMgr(5847);
		StringCchPrintf(DestTxt,256,pPatternChangeMsg,pText);
	}

	pclclient->pclMessage->SetMsg(DestTxt,0,RGB(170,255,170),RGB(0,0,0));//   RGB(50,145,50));

}

void CNPartyDlg::PartyNotifyItemGet(SI32 CharUnique, cltItem* pclItem)
{
	cltClient* pclclient = (cltClient*)pclClient;
		
	for(SI16 i = 0; i<MAX_PARTY_USER_NUM; i++ )
	{
		if(m_stClientPartyUser[i].bPartyStatus && m_stClientPartyUser[i].siCharUnique == CharUnique )
		{
			
			TCHAR strBuffer[256] = TEXT("");		//������ ����� ���ؼ�	
			TCHAR* pMsgSrc = GetTxtFromMgr(5855);	//������ ����� ���ؼ�	
			TCHAR strItemName[128] = TEXT("");		//������ ����� ���ؼ�	
			pclItem->GetFullName( pclClient->pclItemManager ,strItemName, 128);	//������ ����� ���ؼ�	
			StringCchPrintf(strBuffer, 256,pMsgSrc,m_stClientPartyUser[i].strCharName, strItemName, pclItem->GetItemNum());//����ϼ�

			if( pclClient->IsCountrySwitch( Switch_PartyMassageimprovement ) ){
				stChatEditData ChatEditData;			// ��Ƽ ê�� ���̾�α� ������ �ֱ� ���ؼ�
				ChatEditData.siChatDataColorIndex = CHATEDIT_COLOR_BLACK;
				ChatEditData.siNameDataColorIndex = CHATEDIT_COLOR_BLUE;

				StringCchCopy( ChatEditData.strChatData, CHATEDIT_CHATDATA_LENGTH, strBuffer );
				m_pChatEdit->Insert(&ChatEditData);			//��Ƽ ê�þ����� ���� �ִ´�.
			}
			else{
				pclclient->pclMessage->SetMsg(strBuffer,0, RGB(220,220,220),RGB(0,0,0) );
			}
			
			break;
		}	
	}
}

void CNPartyDlg::SetPartyUserPos(SI32 CharUnique, cltCharPos* pclCharPos)
{
	BOOL bReroadFlg = FALSE;

	for(SI16 i = 0; i<MAX_PARTY_USER_NUM; i++ )
	{
		if(m_stClientPartyUser[i].bPartyStatus && m_stClientPartyUser[i].siCharUnique == CharUnique )
		{
			if(m_stClientPartyUser[i].clCharPos.GetMapIndex() != pclCharPos->GetMapIndex() )
				bReroadFlg = TRUE;

			m_stClientPartyUser[i].clCharPos.Set(pclCharPos);	

			if(bReroadFlg)	// ��Ƽ���� ���ε����� ����Ǿ��ٸ� ��Ƽ���̾�α��� ����Ʈ ����
				ReloadPartyUserList();
			break;
		}	
	}
}


void CNPartyDlg::SetPartyUserLevel(SI32 CharUnique, SI32 Level)
{
	for(SI16 i = 0; i < MAX_PARTY_USER_NUM; i++ )
	{
		if(m_stClientPartyUser[i].bPartyStatus && m_stClientPartyUser[i].siCharUnique == CharUnique )
		{			
			m_stClientPartyUser[i].siLevel = Level;
			break;
		}	
	}
	ReloadPartyUserList();
}

cltCharPos* CNPartyDlg::GetPartyUserPos(SI16 partyuserindex)
{
	if( MAX_PARTY_USER_NUM <= partyuserindex || partyuserindex < 0 ) return NULL;

	return &m_stClientPartyUser[partyuserindex].clCharPos;    	
}

void CNPartyDlg::Minimi(BOOL bMini )
{	
	if(m_bMini == bMini) return; 

	cltClient *pclclient = (cltClient*)pclClient;

	if( bMini )
	{	
		m_siOldPosX = GetX();
		m_siOldPosY = GetY();
		SetMoveable(FALSE);

		// �ּ�ȭ�� ���̾�α��� ��ġ�� �ٸ� �ּ�ȭ���̾�α��� ��ġ�� ���� �����Ѵ�.
	
		SI16 LetterMinimizedSlot = 0, PrivateChatMinimizedSlot = 0, HelpButtonMiniMizedSlot = 0, LoveLevelMiniMizedSlot = 0 , FamilyCookieEffect = 0 , FamilyMini = 0 , siDormancyMiniMizedSlot = 0;
		
		if( pclclient->m_pDialog[NLETTER_DLG])
			LetterMinimizedSlot = ((CNLetterDlg*)pclclient->m_pDialog[NLETTER_DLG])->GetMinimizedSlot();
		
		if( pclclient->m_pNPrivateChatDlgMgr)
			PrivateChatMinimizedSlot = pclclient->m_pNPrivateChatDlgMgr->GetMinimizedSlot();

		if(pclClient->IsCountrySwitch(Switch_FreshManHelpDialog))
		{
			if( pclclient->m_pDialog[NHELPBUTTON_DLG])
				HelpButtonMiniMizedSlot = ((CNHelpButtonDlg*)pclclient->m_pDialog[NHELPBUTTON_DLG])->GetMinimizedSlot();
		}

		if ( pclclient->m_pDialog[NMARRIAGELOVELEVEL_DLG] )
			LoveLevelMiniMizedSlot = ((CNMarriageLoveLevelDlg*)pclclient->m_pDialog[NMARRIAGELOVELEVEL_DLG])->GetMinimizedSlot();

		if ( pclclient->m_pDialog[NFAMILYCOOKIELEVEL_DLG] )
			FamilyCookieEffect = ((CNFamilyCookieDlg*)pclclient->m_pDialog[NFAMILYCOOKIELEVEL_DLG])->GetMinimizedSlot();

		if ( pclclient->m_pDialog[NFAMILYINFO_DLG] )
			FamilyCookieEffect = ((CNFamilyInfoDlg*)pclclient->m_pDialog[NFAMILYINFO_DLG])->GetMinimizedSlot();
		
		if ( pclclient->m_pDialog[NDORMANCYPOINT_DLG] )
			siDormancyMiniMizedSlot = ((CNDormancyPointDlg*)pclclient->m_pDialog[NDORMANCYPOINT_DLG])->GetMinimizedSlot();


		// �� ������ ã�´�.
		for(SI16 i = 1; i <= MAX_MINIMIZE_SLOT; i++)
		{
			if( i == LetterMinimizedSlot || i == PrivateChatMinimizedSlot || i == HelpButtonMiniMizedSlot || i == LoveLevelMiniMizedSlot || i == FamilyCookieEffect || i == FamilyMini || i == siDormancyMiniMizedSlot)
				continue;
			
			m_siMinimizedSlot = i;
			break;
		}
		
		// ���Կ� ���� x ��ǥ�� ������ �ش�.
		SetDialogPos( pclclient->GetScreenXSize() - 40 - (m_siMinimizedSlot-1) * 45 , 215, 34, 34 );
	
//		SetDialogPos( pclclient->GetScreenXSize() - 102 , 210, 32, 34 );
		SetFileName(NULL);
		SetTitle(NULL);
		
		m_pImageMinimized->Show(TRUE);	

		m_pStatic[0]->Show(FALSE);
		m_pStatic[1]->Show(FALSE);
		m_pStatic[2]->Show(FALSE);
		m_pList->Show(FALSE);
		m_pButton->Show(FALSE);
		m_pMoveButton->Show(FALSE);
		m_pEdit->Show(FALSE);
		m_pRadioItemGetPattern[0]->Show(FALSE);
		m_pRadioItemGetPattern[1]->Show(FALSE);
		m_pRadioItemGetPattern[2]->Show(FALSE);
		m_pRadioItemGetPattern[3]->Show(FALSE);
		m_pChatEdit->Show(FALSE);
		m_pOutLine[0]->Show(FALSE);
		m_pOutLine[1]->Show(FALSE);
	}
	else
	{
		SetMoveable(TRUE);
		SetDialogPos( m_siOldPosX, m_siOldPosY, 347, 416 );
		SetFileName("ninterface/interface/interface_20x20_00_109.spr");
		SetTitle(GetTxtFromMgr(1221));	// Ÿ��Ʋ �缳��
		m_pImageMinimized->Show(FALSE);	

		m_pStatic[0]->Show(TRUE);
		m_pStatic[1]->Show(TRUE);
		m_pStatic[2]->Show(TRUE);
		m_pList->Show(TRUE);
		m_pButton->Show(TRUE);
		m_pMoveButton->Show(TRUE);
		m_pEdit->Show(TRUE);
		m_pRadioItemGetPattern[0]->Show(TRUE);
		m_pRadioItemGetPattern[1]->Show(TRUE);
		m_pRadioItemGetPattern[2]->Show(TRUE);
		m_pRadioItemGetPattern[3]->Show(TRUE);
		m_pChatEdit->Show(TRUE);
		m_pOutLine[0]->Show(TRUE);
		m_pOutLine[1]->Show(TRUE);
		
		m_siMinimizedSlot = 0;
	}
	m_bMini = bMini;

	UpdatePartyQuestBtn();

}

// [����] ������ : ������ �ȿ� ��� �������� Ż���ư ��Ȱ��ȭ ��Ű��
void CNPartyDlg::DoNotLeaveParty()
{
	if ( m_bMini == TRUE ) return;

	SI32 siMapIndex		= pclClient->pclCM->CR[1]->GetMapIndex();
	bool bConditionA	= pclClient->pclMapManager->IsPartyMap( siMapIndex );

	if ( bConditionA == true )
	{
		m_pButton->Enable( false );
	}
	else
	{
		m_pButton->Enable( true );
	}
}

bool CNPartyDlg::IsPartyMember( const SI32 siFindCharID )
{
	if ( 0 >= siFindCharID )
	{
		return false;
	}

	for ( SI32 siIndex=0; siIndex<MAX_PARTY_USER_NUM; siIndex++ )
	{
		if ( (true == m_stClientPartyUser[siIndex].bPartyStatus) && (siFindCharID == m_stClientPartyUser[siIndex].siCharUnique) )
		{
			return true;
		}
	}
	
	return false;
}

void CNPartyDlg::Action()
{
	DoNotLeaveParty();
	UpdatePartyQuestBtn();
}

void CNPartyDlg::StartPartyQuestMessage(SI32 siMessage)
{
	// ��Ƽ����Ʈ ���۽� ����üũ ��� ���õ� �޼��� ��� �κ� �Դϴ�.

	switch(siMessage)
	{
	case 	PARTYQUEST_MESSAGE_CAN_START:
		{
			// ��Ƽ����Ʈ ����

			if ( true == m_bIsPartyQuestParty )
			{
				TCHAR* pTitle	= GetTxtFromMgr(40428);
				NTCHARString256	pText(GetTxtFromMgr(40429));

				cltClient *pClient = (cltClient*)pclClient;

				SI32 siMinLevel = pClient->m_pPartyQuestMgr->GetPartyQuestCategoryData(m_siCategory)->m_siMinLevel;
				SI32 siMaxLevel = pClient->m_pPartyQuestMgr->GetPartyQuestCategoryData(m_siCategory)->m_siMaxLevel;

				NTCHARString64	pNeedLevel("");
				TCHAR pTemp[64] = "";

				pNeedLevel += itoa(siMinLevel, pTemp, 10);
				ZeroMemory(pTemp, sizeof(pTemp));
				pNeedLevel += " ~ ";
				pNeedLevel += itoa(siMaxLevel, pTemp, 10);

				pText.Replace("#LEVEL#", pNeedLevel);


				stMsgBox MsgBox;
				MsgBox.Set( this,  pTitle, pText, MSGBOX_TYPE_YESNO, 3);		
				pClient->SetMsgBox(&MsgBox, NULL, 0);
			}
		}
		break;

	case PARTYQUEST_MESSAGE_CANNOT_START:
		{
			// ��Ƽ����Ʈ ���� �����
			TCHAR*	pTitle	= GetTxtFromMgr(512);
			TCHAR*	pBody	= GetTxtFromMgr(40446);

			cltClient *pClient = (cltClient*)pclClient;
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);	
		}
		break;

	case PARTYQUEST_MESSAGE_FAILED_LESS_USER:
		{
			// ��Ƽ����Ʈ ���� �����
			TCHAR*	pTitle	= GetTxtFromMgr(512);
			TCHAR*	pBody	= GetTxtFromMgr(40801);

			cltClient *pClient = (cltClient*)pclClient;
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);	
		}
		break;

	case PARTYQUEST_MESSAGE_ANSWER_FAILED:
		{
			// ��Ƽ����Ʈ ����

			TCHAR* pTitle	= GetTxtFromMgr(512);
			TCHAR* pText	= GetTxtFromMgr(40802);

			stMsgBox MsgBox;
			MsgBox.Set( this,  pTitle, pText, MSGBOX_TYPE_YESNO, 4);		
			cltClient* pClient = (cltClient*)pclClient;
			pClient->SetMsgBox(&MsgBox, NULL, 0);
		}
		break;

	case PARTYQUEST_MESSAGE_FAILED_ADDED_USER:
		{
			// ��Ƽ����Ʈ ���� �����
			TCHAR*	pTitle	= GetTxtFromMgr(512);
			TCHAR*	pBody	= GetTxtFromMgr(40803);

			cltClient *pClient = (cltClient*)pclClient;
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);	
		}
		break;

	case PARTYQUEST_MESSAGE_TIMEOUT:
		{
			// ��Ƽ����Ʈ ���� �����
			TCHAR*	pTitle	= GetTxtFromMgr(512);
			TCHAR*	pBody	= GetTxtFromMgr(1257);

			cltClient *pClient = (cltClient*)pclClient;
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);	
		}
		break;

	default:
		break;
	}
}


void CNPartyDlg::UpdatePartyQuestBtn()
{
	cltClient* pClient = (cltClient*) pclClient;

	// ��Ƽ��Ī switch üũ
	if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == false)
	{ m_pBtnStartQuest->Show(false); return; }
	if ( false == m_bIsPartyQuestParty ) { m_pBtnStartQuest->Show(false); return; }
	if ( 0 > m_siCategory ) { m_pBtnStartQuest->Show(false); return; }

	// â�� �ּ�ȭ �Ǿ� ���� �������� ��ư�� ���δ�.
	if(m_bMini == false)
	{
		if ( 0 > m_siCategory ) { m_pBtnStartQuest->Show(false); return; }

		if(m_bIsPartyLeader == true && pClient->m_pPartyQuestMgr->m_PartyQuestData.m_bGoingQuest == false )
			m_pBtnStartQuest->Show(true);
		else
			m_pBtnStartQuest->Show(false);
	}
	else
	{
		m_pBtnStartQuest->Show(false);
	}


	//// ��Ƽ����Ʈ ���� ��ư�� ��Ƽ���̰� ���� ��Ƽ����Ʈ�� ������������ �÷��̾ Ȱ��ȭ �˴ϴ�. (��Ƽ��Ī�� ��ϵǾ������ʾƵ� ������ �ʽ��ϴ�.)
	//if(m_bMini == false)
	//{
	//	if(m_bIsPartyLeader == true && pClient->m_pPartyQuestMgr->m_PartyQuestData.m_bGoingQuest == false && pClient->m_pClient_PartyMatchingMgr->Get_Category() > -1)
	//		m_pBtnStartQuest->Show(true);
	//	else
	//		m_pBtnStartQuest->Show(false);
	//}
	//else
	//	m_pBtnStartQuest->Show(false);

}

void CNPartyDlg::Set_PartyQuestInfo(bool isPartyQuest, SI32 siCategory, SI32 siMission)
{
	if( pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching)  == true )
	{
		cltClient* pClient = (cltClient*) pclClient;

		if( false == m_bIsPartyLeader ) return;
		if (false == isPartyQuest )	 return;
		if(  0 > siCategory && 0 > siMission ) return;

		// ��ư�� �ϴ� �Ⱥ��̴� ���°� ����Ʈ. �׸��� ��Ƽ��Ī���� �Ѿ�� �� ���� ���� �Ѵ�
		m_pBtnStartQuest->Show(false);

		m_bIsPartyQuestParty  = isPartyQuest;
		m_siCategory = siCategory;
		m_siMission = siMission;
		
		//// ��Ƽ����Ʈ ���� ��ư�� ��Ƽ���̰� ���� ��Ƽ����Ʈ�� ������������ �÷��̾ Ȱ��ȭ �˴ϴ�. (��Ƽ��Ī�� ��ϵǾ������ʾƵ� ������ �ʽ��ϴ�.)
		if(m_bMini == false)
		{
			if(m_bIsPartyLeader == true && pClient->m_pPartyQuestMgr->m_PartyQuestData.m_bGoingQuest == false )
				m_pBtnStartQuest->Show(true);
		}
	}	
}


