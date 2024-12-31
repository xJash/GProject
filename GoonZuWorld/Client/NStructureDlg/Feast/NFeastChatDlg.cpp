#include "NFeastDlg.h"

#include "../../InterfaceMgr/Interface/List.h"
//#include "../StrBaseDlg/StrInventory.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/Msg/MsgType-Feast.h"

#include "../Lib/JYLibFunction.h"
#include "..\..\Client\Music\Music.h"

#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../../FeastEffect/FeastEffectManager.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NFeastChatDlg::NFeastChatDlg()
{

}

NFeastChatDlg::~NFeastChatDlg()
{

}

void NFeastChatDlg::InitDlg()
{

	SetControlMap( BUTTON_INPUT, TEXT("button_input") );
	SetControlMap( EDIT_CHAT, TEXT("editbox_chat") );
	SetControlMap( EDIT_EFFECT, TEXT("editbox_effectname"));
	SetControlMap( LIST_EFFECT, TEXT("listbox_effect"));
	SetControlMap( BUTTON_USEEFFECT, TEXT("button_useeffect"));

	cltFeastManager *pFeastManager = ((cltFeastManager *)m_pStrManager);
	CList *pList = (CList*)m_pControlMap[ LIST_EFFECT ];

	pList->SetBKColorUse( true );
	pList->SetBorder( true );

	int width[] = { 40, 66, 216, 18 };

	TCHAR* pText[4];

	pText[0] = GetTxtFromMgr(1641);
	pText[1] = GetTxtFromMgr(1782);
	pText[2] = GetTxtFromMgr(5223);
	pText[3] = TEXT("");

	for(SI16 i=0; i<3; i++ )
	{
		pList->SetColumn( i, width[i], pText[i] );
	}

	pList->Refresh();

	ShowEffectInfo();
}



void NFeastChatDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	TCHAR buffer[ 1024 ];

	cltFeastManager *pFeastManager = ((cltFeastManager *)m_pStrManager);

	cltClient* pclclient = (cltClient*)pclClient;

	CList *pList = (CList*)m_pControlMap[ LIST_EFFECT ];

	CASE_CONTROL( BUTTON_INPUT )
	{

		MStrCpy( buffer, GetEditText( EDIT_CHAT ), 128 );

		SI32 k;
		for ( k = 0 ; k < sizeof(buffer) ; k ++ )
		{
			if( buffer[k] == '\r' ||
				buffer[k] == '\n' )
			{
				buffer[k] = ' ';
			}
		}

		cltGameMsgRequest_FeastSendChat sendmsg( buffer );
	
		cltMsg clMsg(GAMEMSG_REQUEST_FEAST_SENDCHAT, sendmsg.siSize, (BYTE*)&sendmsg);
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);				

	} else CASE_CONTROL( LIST_EFFECT )
	{
        switch( nEvent )
		{
		case EVENT_LISTBOX_SELECTION:
			{
				SI16 siIndex = pList->GetSelectedIndex();

				if(siIndex < 0 ) return;

				stListBoxItemData* pTmpListBoxItemData = NULL;
				pTmpListBoxItemData = pList->GetItemData( siIndex );

				if( pTmpListBoxItemData == NULL ) return;
			
				pFeastManager->siChiefEffectSelectIndex = pTmpListBoxItemData->siParam[0];

				SetEditText( EDIT_EFFECT, pTmpListBoxItemData->strText[2] );
			}
			break;
		}

	} else CASE_CONTROL( BUTTON_USEEFFECT )
	{
//#if defined(_LEON_FEAST_EFFECT)

		if( pFeastManager->siChiefEffectSelectIndex < 0 || pFeastManager->siChiefEffectSelectIndex > cltFeastManager::MAX_FEAST_EFFECT_NUM ) return;

 		pclclient->m_pFeastEffectManager->StopFeastEffect();

		TCHAR* pTitle = GetTxtFromMgr(5227);
		TCHAR* pText = GetTxtFromMgr(5230);

		SI32 siFeastStatus = 0;
		SI32 personid = 0;
		SI32 reserverid = 0;

		// ��ȸ ������ üũ
		siFeastStatus = pclClient->pclFeastManager->clClientStrInfo.clFeastStrInfo.clFeastInfo.siStatus;
		//KHY - 0710 -��ȸ�� ���� ���� : 0=����. 1=��ȸ��,  2 = ������
		if( siFeastStatus != 1 ) 
		{
			TCHAR* pTempText = GetTxtFromMgr(5243);
			SetMainExplain( pTempText );
			return;
		}
		
		// ��ȸ�� ���� üũ
		personid = pclCM->CR[1]->pclCI->GetPersonID();
		reserverid = pclClient->pclFeastManager->clClientStrInfo.clFeastStrInfo.clFeastResvInfo.siPersonID ;

		if( personid != reserverid ) 
		{
			TCHAR* pTempText = GetTxtFromMgr(5243);
			SetMainExplain( pTempText );
			return;
		}

		stMsgBox MsgBox;
		// ���� dialog�� �� â ���� Child Dialog�϶�
		CControllerMgr *pParent = NULL;
		pParent = this->GetParentDialog();
		if(pParent == NULL ) return;
		MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_YESNO, 0 );
		pclclient->SetMsgBox( &MsgBox, NULL, 0 );

//#endif        
	}

}

void NFeastChatDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltFeastManager *pFeastManager = ((cltFeastManager *)m_pStrManager);

	SI32 id = 1;

	switch( MsgIndex )
	{
	case 0:
		{
			if(RetValue)
			{
				cltGameMsgRequest_FeastUseEffect sendmsg( &(pFeastManager->siChiefEffectSelectIndex) );
		        
				cltMsg clMsg(GAMEMSG_REQUEST_FEAST_USEEFFECT, sizeof(sendmsg), (BYTE*)&sendmsg );
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			}
		}
		break;

	}
}

// ����Ʈ ����Ʈ�� ����Ʈ �߰�
void NFeastChatDlg::ShowEffectInfo()
{
	cltFeastManager *pFeastManager = ((cltFeastManager *)m_pStrManager);

	CList *pList = (CList*)m_pControlMap[ LIST_EFFECT ];

	/*cyj TextMgr������ ��ȯ
	TCHAR* FeastEffectName[cltFeastManager::MAX_FEAST_EFFECT_NUM] = {

			// �ϴÿ��� �������°�
			TEXT("�ɴ�"),
			TEXT("�ɰ���"),
			TEXT("���̸���"),

			// �ϴÿ��� �������°�
			TEXT("����Ҳ�"),
			TEXT("�պ�"),
			TEXT("�Ҳ�"),
			TEXT("ȸ���Ҳ�"),
			TEXT("��Ʈ�Ҳ�"),

			// 2���� �ϳ� �Ǵ°�
			TEXT("��"),
			TEXT("����"),
			TEXT("����"),
	};

	TCHAR* FeastEffectKindName[cltFeastManager::MAX_FEAST_EFFECT_NUM] = {

			// �ϴÿ��� �������°�
			TEXT("������"),
			TEXT("������"),
			TEXT("������"),

			// �ϴÿ��� �������°�
			TEXT("�Ҳɷ�"),
			TEXT("���׷�"),
			TEXT("�Ҳɷ�"),
			TEXT("�Ҳɷ�"),
			TEXT("�Ҳɷ�"),

			// 2���� �ϳ� �Ǵ°�
			TEXT("���׷�"),
			TEXT("���׷�"),
			TEXT("���׷�"),
	};
	*/
	SI32 FeastEffectName[cltFeastManager::MAX_FEAST_EFFECT_NUM] = {

		// �ϴÿ��� �������°�
			5711,
			5712,
			5713,

			// �ϴÿ��� �������°�
			5714,
			5715,
			5716,
			5717,
			5718,

			// 2���� �ϳ� �Ǵ°�
			5719,
			5720,
			5721,
	};

	SI32 FeastEffectKindName[cltFeastManager::MAX_FEAST_EFFECT_NUM] = {

			// �ϴÿ��� �������°�
			5708,
			5708,
			5708,

			// �ϴÿ��� �������°�
			5709,
			5710,
			5709,
			5709,
			5709,

			// 2���� �ϳ� �Ǵ°�
			5710,
			5710,
			5710,
	};

	TCHAR buffer[10];

	// List�� Item ��� �����
	pList->Clear();


	for( SI16 i = 0; i < cltFeastManager::MAX_FEAST_EFFECT_NUM; i++)
	{
		stListBoxItemData tmpListBoxItemData;

		tmpListBoxItemData.Init();

		StringCchPrintf(buffer, 10, TEXT("%d"), i + 1);

		tmpListBoxItemData.Set( 0, buffer );
		tmpListBoxItemData.siParam[0] = i;

		//cyj �ؽ�Ʈ �޴����� �ҷ���
		//tmpListBoxItemData.Set( 1, FeastEffectKindName[ i ] );
		//tmpListBoxItemData.Set( 2, FeastEffectName[ i ] );

		tmpListBoxItemData.Set( 1, GetTxtFromMgr(FeastEffectKindName[ i ]) );
		tmpListBoxItemData.Set( 2, GetTxtFromMgr(FeastEffectName[ i ]) );

		pList->AddItem( &tmpListBoxItemData );
	}

	pList->Refresh();
}
