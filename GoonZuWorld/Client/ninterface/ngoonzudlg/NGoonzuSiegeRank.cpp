#include "NGoonzuSiege.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client/Client.h"
#include "../nvillagedetailinfo/NVillageDetailInfo.h"

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"


extern cltCommonLogic* pclClient;

CNGoonzuSiegeRankDlg::CNGoonzuSiegeRankDlg() : CDialogController()
{
	m_pListVillageRank = NULL;
	m_pButtonSiege = NULL;
}

CNGoonzuSiegeRankDlg::~CNGoonzuSiegeRankDlg()
{

	SAFE_DELETE( m_pListVillageRank );
	SAFE_DELETE( m_pButtonSiege );
}

void CNGoonzuSiegeRankDlg::Create( CControllerMgr *pParent )
{
	CInterfaceFile	file;

	NEWCLIST( m_pListVillageRank );
	NEWCBUTTON( m_pButtonSiege );

	file.LoadFile("NInterface/Data/NGoonzuDlg/DLG_GoonzuSiegeRank.ddf");
	file.CreateChildDialog( this, NGOONZUSIEGE_DLG, TEXT("dialog_goonzusiegerank"), StaticCallBackDialogNGoonzuSiegeRankDlg, pParent);


	file.CreateControl( m_pListVillageRank, NGOONZUSIEGERANK_LIST_RANK, "listbox_villagerank"); 
	file.CreateControl( m_pButtonSiege, NGOONZUSIEGERANK_BUTTON_SIEGE, "button_siege"); 


	cltGameMsgRequest_VillageDetailInfo clinfo(NVILLAGEDETAILINFOTYPE_SCORE);
	cltMsg clMsg(GAMEMSG_REQUEST_VILLAGEDETAILINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);

	// ������ ����Ʈ�� �����Ѵ�. 
	m_pListVillageRank->SetColumn( 0, 270, NULL );
	m_pListVillageRank->SetBorder( true );
	m_pListVillageRank->SetBKColorUse( true );
	m_pListVillageRank->SetDrawLine( true );
	m_pListVillageRank->SetTextPrintOption( DT_LEFT );
	m_pListVillageRank->Refresh();
	m_pListVillageRank->Clear();

	if ( pclClient->siServiceArea == ConstServiceArea_China )
	{
		m_pButtonSiege->Enable( false );
	}
	if ( pclClient->pclCM->CR[1]->pclCI->clCharRank.siType != RANKTYPE_CITYHALL )
	{
		m_pButtonSiege->Enable( false );
	}
}

void CNGoonzuSiegeRankDlg::Action()
{
}

void CALLBACK CNGoonzuSiegeRankDlg::StaticCallBackDialogNGoonzuSiegeRankDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNGoonzuSiegeRankDlg *pThis = (CNGoonzuSiegeRankDlg *)pControllerMgr;
	pThis->CallBackDialogNGoonzuSiegeRankDlg( nEvent, nControlID, pControl );
}

void CALLBACK CNGoonzuSiegeRankDlg::CallBackDialogNGoonzuSiegeRankDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient* pclclient = (cltClient*)pclClient;

	switch(nControlID)
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NGOONZUSIEGERANK_BUTTON_SIEGE:
		{
			if ( EVENT_BUTTON_CLICKED == nEvent )
			{
				// ������� ��û�Ҽ� �ִ�.
				if ( pclClient->pclCM->CR[1]->pclCI->clCharRank.siType == RANKTYPE_CITYHALL )
				{
					stListBoxItemData* pTmpListBoxItemData = NULL;

					// ���� ���õ� ������  Ȯ���Ѵ�. 
					SI32 siTargetVillage = 0;
					SI32 siHomeVillage = 0;
					SI16 tmpRow = 0, tmpColumn = 0;

					m_pListVillageRank->GetSelectedIndex(&tmpRow, &tmpColumn);

					SI32 index = tmpRow;

					bool bCanDeclare = true;

					if ( index > -1 )
					{
						pTmpListBoxItemData = m_pListVillageRank->GetItemData( tmpRow, 0);
						siTargetVillage = pTmpListBoxItemData->siParam[0];
						siHomeVillage = pclclient->pclCM->CR[1]->pclCI->clBI.siHomeVillage;

						for ( SI32 i = 0; i < MAX_VILLAGE_NUMBER ; i++ )
						{
							// �������� �츮�������� �̹� ������
							if ( siHomeVillage != 0 && pclclient->pclVillageManager->siDeclareWarVillage[i] == siHomeVillage )
							{
								TCHAR* pText = GetTxtFromMgr(6474);
								TCHAR* pTitle = GetTxtFromMgr(6475);
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);

								bCanDeclare = false;
							}
							// ���� ������ �̹� �ٸ� �������� ���� ����
							if ( pclclient->pclVillageManager->siDeclareWarVillage[i] == siTargetVillage )
							{
								TCHAR* pText = GetTxtFromMgr( 6473 );
								TCHAR* pTitle = GetTxtFromMgr( 6475 );
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);

								bCanDeclare = false;
							}
						}
						// �츮 ������ �̹� �ٸ������� ������
						if ( pclclient->pclVillageManager->siDeclareWarVillage[siHomeVillage] > 0 )
						{
							TCHAR* pText = GetTxtFromMgr(6474);
							TCHAR* pTitle = GetTxtFromMgr(6475 );
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);

							bCanDeclare = false;
						}
						// ���� ������ �ٸ� �������� �̹� ������ ������
						if ( pclclient->pclVillageManager->siDeclareWarVillage[siTargetVillage] > 0 )
						{
							TCHAR* pText = GetTxtFromMgr(6473);
							TCHAR* pTitle = GetTxtFromMgr(6475 );
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);

							bCanDeclare = false;
						}
						if ( bCanDeclare )
						{
							cltMsg clMsg( GAMEMSG_REQUEST_DECLAREWAR, siTargetVillage );
							pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg );
						}
					}
				}
			}
		}
	default:
		break;
	}
}
void CNGoonzuSiegeRankDlg::ShowRank(cltGameMsgResponse_VillageDetailInfo* pclinfo)
{
	SI32 i;
	TCHAR buffer[256] = TEXT("");

	stListBoxItemData tmpListBoxItemData;

	// ������ ����Ʈ�� �����Ѵ�. 
	m_pListVillageRank->Clear();

	SI64 sidata[MAX_VILLAGE_NUMBER];
	SI32 siVillageInfo[MAX_VILLAGE_NUMBER];

	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SCORE)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siTotalVillageScore[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)
				continue;

			// ��ȿ���� ���� �ǹ��� �����Ѵ�. 
			//if(pclinfo->siTotalVillageScore[villageunique] < 0)
			//	continue;

			TCHAR *pText = GetTxtFromMgr(5997);

			SI32	score = pclinfo->siTotalVillageScore[villageunique];
			TCHAR	buf[64];
			g_JYLibFunction.SetNumUnit( score, buf, 64 );

			StringCchPrintf(buffer, 256, pText, i+1, pclClient->pclVillageManager->GetName(villageunique),buf); 

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;

			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pListVillageRank->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pListVillageRank->Refresh();
	}
}
// ������������ �����Ѵ�. 
SI32 CNGoonzuSiegeRankDlg::Sort(SI64 sisortdata[], SI32* pvillageunique)
{
	SI32 i;
	SI32 index = 0;

	SI32 tempbuf[ MAX_VILLAGE_NUMBER ];

	for( i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		tempbuf[ i ] = i;
	}

	for(SI32 vill = 0; vill < MAX_VILLAGE_NUMBER - 1; vill++)
	{
		if(pclClient->pclVillageManager->pclVillageInfo[vill] == NULL)continue;

		for(i = vill + 1; i < MAX_VILLAGE_NUMBER; i++)
		{
			if(pclClient->pclVillageManager->pclVillageInfo[i] == NULL)continue;

			int cmpindex1 = tempbuf[ vill ];
			int cmpindex2 = tempbuf[ i ];

			if(sisortdata[cmpindex1] < sisortdata[cmpindex2])
			{
				int temp = tempbuf[ vill ];
				tempbuf[ vill ] = tempbuf[ i ];
				tempbuf[ i ] = temp;
			}
		}
	}

	for(i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		if( pclClient->pclVillageManager->pclVillageInfo[ tempbuf[i] ]== NULL)continue;
		pvillageunique[ index ] = tempbuf[ i ];
		index++;
	}

	return index;
}
