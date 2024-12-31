#include "NRightMouseUserListDlg.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../client.h"
#include "../../ninterface/nrightmousemenudlg/NRightMouseMenuDlg.h"
#include "../../../common/Char/CharManager/CharManager.h"

extern cltCommonLogic * pclClient;

NRightMouseUserListDlg::NRightMouseUserListDlg()
{
	m_pUserList = NULL;
	m_pTempStaticUserList = NULL;
	m_bShow = FALSE;
}

NRightMouseUserListDlg::~NRightMouseUserListDlg()
{
    SAFE_DELETE(m_pUserList)
	SAFE_DELETE(m_pTempStaticUserList);
}

void NRightMouseUserListDlg::Create()
{
	m_bShow = FALSE;

	cltClient *pclclient = (cltClient *)pclClient;

	CDialogController::Create( NRIGHTMOUSEUSERLIST_DLG, CONTROLLER_KIND_POPUPDIALOG, NULL, StaticCallBackDialogNRightMouseUserListDlg, NULL, NULL, 0, false, 0, 0, 0, NRIGHTMOUSEUSERLIST_DLG_WIDTH, NRIGHTMOUSEUSERLIST_DLG_HEIGHT, false, false, false );
	
	m_pUserList = new CList(this);
	m_pTempStaticUserList = new CStatic(this);

	m_pUserList->Create(NRIGHTMOUSEUSERLIST_LIST, NULL, 0, false, 0, 0, 0, NRIGHTMOUSEUSERLIST_DLG_WIDTH, NRIGHTMOUSEUSERLIST_DLG_HEIGHT, NRIGHTMOUSEUSERLIST_DLG_WIDTH, NRIGHTMOUSEUSERLIST_DLG_HEIGHT, true, false, true, true, 22);
	m_pTempStaticUserList->Create(NRIGHTMOUSEUSERLIST_STATIC, NULL, 0, false, 0, 0, 0, 0, NRIGHTMOUSEUSERLIST_DLG_WIDTH, NRIGHTMOUSEUSERLIST_DLG_HEIGHT, NRIGHTMOUSEUSERLIST_DLG_WIDTH, NRIGHTMOUSEUSERLIST_DLG_HEIGHT);

	m_pUserList->SetDrawOption(SPR_PUTSPRALPHAT);
	m_pUserList->SetListAlphaValue(13);

	TCHAR * pText = GetTxtFromMgr(6081);
	m_pUserList->SetColumn(0, NRIGHTMOUSEUSERLIST_DLG_WIDTH, pText);

	m_pUserList->SetBorder(TRUE);
	m_pUserList->SetBKColorUse(TRUE);
	m_pUserList->SetBKColor(RGB(0, 0, 51));

	m_pUserList->SetMouseOverImageFileName("NInterface/Common/Common_4X22_00_103.Spr");
	m_pUserList->SetShowMouseOverImage(TRUE);	

	m_pTempStaticUserList->Show(FALSE);

	m_pUserList->Refresh();
}

void CALLBACK NRightMouseUserListDlg::StaticCallBackDialogNRightMouseUserListDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	NRightMouseUserListDlg* pThis = (NRightMouseUserListDlg*)pControllerMgr;
	pThis->CallBackDialogNRightMouseUserListDlg(nEvent,nControlID,pControl);
}

void CALLBACK NRightMouseUserListDlg::CallBackDialogNRightMouseUserListDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient* pclclient = (cltClient*)pclClient;

	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
            Hide();
		}
	
	case NRIGHTMOUSEUSERLIST_LIST:
		{
			switch(nEvent)
			{
			case EVENT_LISTBOX_MOUSEOVER:
				{

					SI32 TempSelectIndex = m_pUserList->GetMouseOverIndex();

					if(TempSelectIndex < 0)
						break;

					// ������ �̸��� ���� ��쿡 ��ȿ
					TCHAR * pNameText = m_pUserList->GetText(TempSelectIndex,0);
					if( pNameText == NULL  ) return;

					if( pNameText[0] == '\0') return;

					m_UnderMouseUserListItr = m_UnderMouseUserList.begin();

					for( SI32 i = 0; i < TempSelectIndex; i++)
					{
						m_UnderMouseUserListItr++;
					}

					stUnderMouseUserData * pUnderMouerUserData = &(*m_UnderMouseUserListItr);

					SI32 id = pUnderMouerUserData->siUserId;

					if ( pclclient->m_pDialog[ NRIGHTMOUSEMENU_DLG ] == NULL )
					{
						pclclient->CreateInterface( NRIGHTMOUSEMENU_DLG  );
					}

 					if ( pclclient->m_pDialog[ NRIGHTMOUSEMENU_DLG ] )
					{
						SI16 siMode = 0;
						if( pclclient->pclCM->CR[id]->bPersonalShopSwitch )			siMode |= 0x0001;
						if( pclClient->IsCountrySwitch( Switch_NewDurability ) )
						{
							if( pclclient->pclCM->CR[id]->bRepairShopSwitch )			siMode |= 0x0002;
						}

						((CNRightMouseMenuDlg *)pclclient->m_pDialog[ NRIGHTMOUSEMENU_DLG ])->Set( id, pclclient->pclCM->CR[id]->GetCharUnique(),pclclient->GameMouseX-10, pclclient->GameMouseY-40, siMode );
						SI16 Xpos = GetX() + GetWidth();
						SI16 YPos = GetY() + (TempSelectIndex - m_pUserList->GetScrollTrackPos()) * 22 ;
						pclclient->m_pDialog[ NRIGHTMOUSEMENU_DLG ]->MovePos(Xpos,YPos);
					}

				//	SetFocus(true);

				}
				break;

			case EVENT_LISTBOX_SELECTION:
				{
					SI32 TempSelectIndex = m_pUserList->GetSelectedIndex();

					if(TempSelectIndex < 0)
						break;
					
					// ������ �̸��� ���� ��쿡 ��ȿ
					TCHAR * pNameText = m_pUserList->GetText(TempSelectIndex,0);
					if( pNameText == NULL  ) return;

					if( pNameText[0] == '\0') return;

					m_UnderMouseUserListItr = m_UnderMouseUserList.begin();
					
					for( SI32 i = 0; i < TempSelectIndex; i++)
					{
						m_UnderMouseUserListItr++;
					}

					stUnderMouseUserData * pUnderMouerUserData = &(*m_UnderMouseUserListItr);
                    
					SI32 id = pUnderMouerUserData->siUserId;

					if ( pclclient->m_pDialog[ NRIGHTMOUSEMENU_DLG ] == NULL )
					{
						pclclient->CreateInterface( NRIGHTMOUSEMENU_DLG  );
					}

					if ( pclclient->m_pDialog[ NRIGHTMOUSEMENU_DLG ] )
					{
						SI16 siMode = 0;
						if( pclclient->pclCM->CR[id]->bPersonalShopSwitch )			siMode |= 0x0001;
						if( pclClient->IsCountrySwitch( Switch_NewDurability ) )
						{
							if(pclclient->pclCM->CR[id]->bRepairShopSwitch )			siMode |= 0x0002;
						}

						((CNRightMouseMenuDlg *)pclclient->m_pDialog[ NRIGHTMOUSEMENU_DLG ])->Set( id, pclclient->pclCM->CR[id]->GetCharUnique(),pclclient->GameMouseX-10, pclclient->GameMouseY-40, siMode );
					}
					
					Hide();

				}
				break;
			}
		}
	}
}

void NRightMouseUserListDlg::Initialize()
{
	m_pUserList->Clear();

	m_UnderMouseUserList.clear();
	m_UnderMouseUserListItr = m_UnderMouseUserList.end();
}

// ����Ʈ ��Ʈ���� ����� �����Ѵ�. ���� ������ ����Ʈ -> ������ ����Ʈ
// �� �������� �̸� �����Ͱ� ������ ��� ������ ��û
void NRightMouseUserListDlg::SetUnderUserList(BOOL bCheckName )
{
	cltClient* pclclient = (cltClient*)pclClient;

	m_pUserList->Clear();

	m_UnderMouseUserListItr = m_UnderMouseUserList.begin();

	SI32 UserCnt = 0;
    stUnderMouseUserData * pUnderMouseUserData = NULL;
	SIZE sizeString = {0, };
	SI32 siStringSize[MAX_STRING_SIZE];
	SI32 siStringSizeMax = 0;

	stListBoxItemData Data;

	while( m_UnderMouseUserListItr != m_UnderMouseUserList.end() )
	{
		pUnderMouseUserData = &(*m_UnderMouseUserListItr);
		
		//����Ʈ�� ���Ե� ĳ���͵��� ��¦�̰Բ�
		
		if( pclClient->pclCM->IsValidID( pUnderMouseUserData->siUserId) == false )
		{
			m_UnderMouseUserListItr++;
			continue;
		}
	
		((cltCharClient*)pclclient->pclCM->CR[pUnderMouseUserData->siUserId ])->SetNewSelectedSwitch(TRUE);
		
		// �̸��� ���� �𸣸� ������ ��û
		if( bCheckName == TRUE )
		{
			if ( (_tcscmp(pUnderMouseUserData->strCharName, TEXT("")) == 0  
				|| pUnderMouseUserData->strCharName[0] == NULL) )
			{
				cltGameMsgRequest_GetName clInfo( pclclient->pclCM->CR[pUnderMouseUserData->siUserId]->GetCharUnique() );
				cltMsg clMsg(GAMEMSG_REQUEST_RIGHTMOUSE_USERLIST_NAME, sizeof(clInfo), (BYTE*)&clInfo);

				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
				m_UnderMouseUserListItr++;
				continue;
			}
		}

		LVITEM Li;
		Li.mask = LVIF_TEXT;
		Li.state = 0;
		Li.stateMask = 0;	

		Li.iItem = 0;	

		Li.iSubItem = 0;	
		Li.pszText = pUnderMouseUserData->strCharName;
       
		Data.Set(0, Li.pszText, RGB(255,255,255));
		Data.siSmallIconFileIndex[0] = 4;
  		Data.siSmallIconFontIndex[0] = pUnderMouseUserData->siKind-5;

		m_pTempStaticUserList->SetText(Li.pszText, DT_CENTER | DT_VCENTER | DT_SINGLELINE, &sizeString);
		m_pUserList->AddItem(&Data);

		siStringSize[UserCnt] = sizeString.cx;
		m_UnderMouseUserListItr++;
 		UserCnt++;
		
 	}

	for(SI32 i =0; i<UserCnt; i++)
	{
		if(siStringSize[i] > siStringSizeMax)
		{
			siStringSizeMax = siStringSize[i];
		}
	}
	CalcWitdhUserList(siStringSizeMax);
	CalcHeightUserList(UserCnt + 1);

	m_pUserList->Refresh();
}

void NRightMouseUserListDlg::AddUser(SI32 id, SI32 Kind , SI32 Level, TCHAR * CharName )
{
	// list �� ����־��ٰ� �����ٶ� CList�� ä���ش�. 
		
	list<stUnderMouseUserData>::size_type	ListDataNum;
	ListDataNum = m_UnderMouseUserList.size();

	if(ListDataNum >= 7 ) return;
    

	stUnderMouseUserData UnderMouserUserData( id, Kind, Level, CharName );

	m_UnderMouseUserList.push_back(UnderMouserUserData );
	
}

void NRightMouseUserListDlg::SetUserName(SI32 id, TCHAR * CharName )
{
	stUnderMouseUserData * pUnderMouseUserData;
	m_UnderMouseUserListItr = m_UnderMouseUserList.begin();
	
	while(m_UnderMouseUserListItr != m_UnderMouseUserList.end())
	{
		pUnderMouseUserData = &(*m_UnderMouseUserListItr);
        
		if(pUnderMouseUserData->siUserId == id)
		{
			StringCchCopy(pUnderMouseUserData->strCharName, MAX_PLAYER_NAME, CharName);

			break;
		}
		m_UnderMouseUserListItr++;
	}
}

void NRightMouseUserListDlg::Show()
{
	
	if(IsShow() == false)
	{
		CDialogController::Show(true);			
		m_bShow = TRUE;
	}
}

void NRightMouseUserListDlg::Hide()
{
	if(IsShow() == true)
	{
		CDialogController::Show(false);
		m_bShow = FALSE;
	}	
}

void NRightMouseUserListDlg::ClearFocus()
{

	CDialogController::ClearFocus();
	return;
}

void NRightMouseUserListDlg::SetFocus( bool Focus )
{
	
	CDialogController::SetFocus( Focus );

	if ( ! Focus )
	{
		Hide();
	}

	return;
}

void NRightMouseUserListDlg::CalcWitdhUserList( SI32 siStringSizeMax )
{
	TCHAR * pText = GetTxtFromMgr(6081);

	// <<4 >>4������ 8�� ����� ����� ����, 8�� ������, 16�� ���� ��׶��� 8�ȼ��� ������
	SI16 siCalcWidth = ((siStringSizeMax >> 3) << 3) +8 + 32;
	// �⺻ ũ�⺸�� �۴ٸ� ������ �⺻ ũ��� ����
	if (NRIGHTMOUSEUSERLIST_DLG_WIDTH > siCalcWidth )
	{
		siCalcWidth = NRIGHTMOUSEUSERLIST_DLG_WIDTH;
	}

	// ���� ������ ũ��� ���� ũ�Ⱑ ���ٸ� ����
	if ( m_pUserList->GetWidth() == siCalcWidth )
	{
		return;
	}

	m_pUserList->SetSurfaceWidth( siCalcWidth );
	m_pUserList->SetWidth( siCalcWidth );

	// ��ġ ����
	SI16 siWidth	= ((siCalcWidth - m_pUserList->GetWidth()) / 2);
	SI16 siX		= m_pUserList->GetX() - siWidth;

	m_pUserList->SetX( siX );

	m_pUserList->SetColumn(0, siCalcWidth, pText);
}

void NRightMouseUserListDlg::CalcHeightUserList(SI32 UserListIndex)
{
	// �÷� �ϳ��� �⺻ ����
	SI16 siBasicHeight = 21;
	SI16 siCalcHeight = 0;

	// �ּ� 2���� ĳ���� ���̷� ��´�.
	if (UserListIndex <= 2 )
	{
		siBasicHeight = siBasicHeight * 2;
	}

	siCalcHeight = siBasicHeight * UserListIndex;

	// �⺻ ũ�⺸�� ũ�ٸ� ������ �⺻ ũ��� ����
	if (NRIGHTMOUSEUSERLIST_DLG_HEIGHT < siBasicHeight * UserListIndex )
	{
		siCalcHeight = NRIGHTMOUSEUSERLIST_DLG_HEIGHT;
	}

	m_pUserList->SetSurfaceHeight(siCalcHeight );
	m_pUserList->SetHeight( siCalcHeight);
}
