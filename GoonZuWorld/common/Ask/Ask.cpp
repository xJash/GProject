#include "Ask.h"
#include "CommonLogic.h"
#include "..\..\Client\Client.h"
#include "..\Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"
#include "..\..\Resource.h"

// �ӼӸ� ä�� ����. 
//#include "..\..\Client\Interface\PrivateChatDlg\PrivateChatBaseInfo.h"
//#include "..\..\Client\Interface\PrivateChatDlg\PrivateChatDlgMgr.h"

#include "MsgType-System.h"

extern cltCommonLogic* pclClient;

/*
cltAskManager::cltAskManager()
{
	m_hDlg = NULL;
	bDlgRectInitSwitch	= false;
	
	siIndex				= 0;

	bUpdateSwitch		= false;
}


cltAskManager::~cltAskManager()
{
}

// ������ �����Ѵ�. 
void cltAskManager::Update()
{
	SI32 i;
	TCHAR buffer[256];

	// ������ ����Ʈ�� �����Ѵ�. 
	ListDelete(m_hDlg, IDC_LIST_ASK);

	for(i = 0;i < MAX_ASK_NUMBER;i++)
	{
		if(clUnit[i].siCharUnique <= 0)continue;
		
		sprintf(buffer, TEXT("%s-%s"), clUnit[i].szPersonName, clUnit[i].szAskText);
		SI32 index = ListAddString(m_hDlg, IDC_LIST_ASK, (LPARAM)buffer);
		
		// ����Ʈ �׸� �����͸� �����Ѵ�. 
		ListSetItemData(m_hDlg, IDC_LIST_ASK, index, (LPARAM)i);

	}
}

// ������ �߰��Ѵ�. 
bool cltAskManager::Add(SI16 charunique, SI32 personid, TCHAR* ppersonname, TCHAR* ptext)
{
	SI32 i;
	SI32 index = -1;

	//--------------------------------------
	// ���� ������� ������ �ִ��� Ȯ���Ѵ�. 
	//--------------------------------------
	for(i = 0;i < MAX_ASK_NUMBER;i++)
	{
		if(clUnit[i].siPersonID == personid)
		{
			index = i;
			break;
		}
	}

	// �̹� ������ �÷� ���� ���� �ִ� ��� �� ������ �����. 
	if(index >= 0)
	{
		clUnit[index].siCharUnique	= charunique;
		clUnit[index].siPersonID	= personid;
		clUnit[index].siSerialNum	= siIndex;

		MStrCpy( clUnit[index].szPersonName, ppersonname, MAX_PLAYER_NAME );
		MStrCpy( clUnit[index].szAskText, ptext, MAX_ASK_TEXT_SIZE );


		siIndex++;

		return true;

	}
	// ���� ������ ������ ã�´�. 
	else
	{
		SI32 minindex	= 2000000000;
		SI32 minpos		= -1;
		for(i = 0;i < MAX_ASK_NUMBER;i++)
		{
			if(clUnit[i].siSerialNum < minindex)
			{
				minindex	= clUnit[i].siSerialNum;
				minpos		= i;
			}
		}

		if(minpos >= 0)
		{
			clUnit[minpos].siCharUnique	= charunique;
			clUnit[minpos].siPersonID	= personid;
			clUnit[minpos].siSerialNum	= siIndex;

			MStrCpy( clUnit[minpos].szPersonName, ppersonname, MAX_PLAYER_NAME );
			MStrCpy( clUnit[minpos].szAskText, ptext, MAX_ASK_TEXT_SIZE );
	
			siIndex++;

			return true;
		}

	}

	return false;
}

// personid�� ������ ������ �����Ѵ�. 
void cltAskManager::DelAskPersonID(SI32 personid)
{
	for(SI32 i = 0;i < MAX_ASK_NUMBER;i++)
	{
		if(clUnit[i].siCharUnique == 0)continue;

		if(clUnit[i].siPersonID == personid)
		{
			clUnit[i].Init();
		}
	}
	
}

BOOL cltAskManager::CreateDlg(HINSTANCE hinst, HWND hwnd)
{
	// ��ȭ���ڰ� ���� ���¶�� �����. 
	if(!IsWindow(m_hDlg))
	{

		m_hDlg = CreateDialog(hinst, MAKEINTRESOURCE(IDD_DIALOG_ASK), hwnd, StaticAskDlgProc);

		if(bDlgRectInitSwitch == true)
		{
			MoveWindow(m_hDlg, 
				DlgRect.left, DlgRect.top, 
				DlgRect.right - DlgRect.left, 
				DlgRect.bottom - DlgRect.top, FALSE);
		}

		ShowWindow(m_hDlg, SW_SHOW);

		return TRUE;
	}
	else
	{
		DestroyWindow(m_hDlg);
	}


	return 0;
}

BOOL CALLBACK cltAskManager::StaticAskDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	return pclClient->pclAskManager->AskDlgProc(hDlg, iMsg, wParam, lParam);
}


BOOL CALLBACK cltAskManager::AskDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	SI32 id = 1;

	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			SetTimer(hDlg, 1, 1000, NULL);

			// ������ ����Ʈ�� �����Ѵ�. 
			ListDelete(hDlg, IDC_LIST_ASK);

			//-----------------------------------------
			// ���� ������ �ʱ�ȭ�Ѵ�. 
			//-----------------------------------------
			for(SI32 i = 0;i < MAX_ASK_NUMBER;i++)
			{
				clUnit[i].Init();
			}


			//-------------------------------------------------
			// ���Ӽ����� ���� ����Ʈ�� ��û�Ѵ�. 
			//-------------------------------------------------
			cltMsg clMsg(GAMEMSG_REQUEST_ASKLIST, 0, NULL);
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		return TRUE;

	case WM_NOTIFY:
		return TRUE;

	case WM_TIMER:
		if(bUpdateSwitch == true)
		{
			bUpdateSwitch = false;

			Update();
		}
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			{

				//----------------------------------------------------------
				// ������ ������ ã�´�. 
				//----------------------------------------------------------
				SI32 index = ListGetCurrentSel(hDlg, IDC_LIST_ASK);
				if(index < 0)break;

				SI32 pos = SendDlgItemMessage(hDlg, IDC_LIST_ASK, LB_GETITEMDATA,	index, 0);
				if(pos < 0)break;
				
				//----------------------------------------------------------
				// ������ �޽����� �����ϵ��� ��û�Ѵ�. 
				//----------------------------------------------------------
				cltGameMsgResponse_DelAsk clinfo(clUnit[pos].siPersonID);
				cltMsg clMsg(GAMEMSG_REQUEST_DELASK, sizeof(clinfo), (BYTE*)&clinfo);
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


				//-------------------------------------------
				//�Ӹ� 
				//-------------------------------------------
				SI32 charunique		= clUnit[pos].siCharUnique;
				TCHAR* pplayername	= clUnit[pos].szPersonName;

				cltClient* pclclient = (cltClient*)pclClient;

				//pclclient->pclPrivateChatDlgMgr->Push(charunique, pplayername, TEXT(""));
				pclclient->RequestSecretChatByCharUnique(charunique);

				//---------------------------------------
				// �ش� �޽����� Ŭ���̾�Ʈ���� �����Ѵ�.
				//---------------------------------------
				DelAskPersonID(clUnit[pos].siPersonID);
				bUpdateSwitch = true;

			}
			return TRUE;
			
		case IDCANCEL:
			DestroyWindow(m_hDlg);
			return TRUE;
		}
		return TRUE;
		
	case WM_DESTROY:


		//-------------------------
		// ���� ����Ʈ�� �����Ѵ�. 
		//-------------------------
		for(SI32 i = 0;i < MAX_ASK_NUMBER;i++)
		{
			clUnit[i].Init();
		}

		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);

		// �������� ��ġ�� ����Ѵ�. 
		GetWindowRect(hDlg, &DlgRect);
		bDlgRectInitSwitch = true;

		m_hDlg = NULL;
		return TRUE;

	}

	return FALSE;
}
*/