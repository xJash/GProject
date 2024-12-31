//---------------------------------
// 2004/2/5 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :		CNVillageDetailInfo

	�ۼ��� :		05/03/02
	�ۼ��� :		���뷡

	��  �� :		CNVillageDetailInfo Ŭ������  ��ü ȭ�� ��� ����� NInterface��
					���� ���� ȭ�� �ȿ��� ���� �� ���� ���̾�α׸� �����Ѵ�.

	������� :		����
	
	�����۾� :		

   ========================================================================*/

//#if (defined(__LEON_START_ALL__) || defined(__LEON_NVILLAGEDETAILINFO__)) && defined(_DEBUG)

#include "..\..\Client.h"
#include "NVillageDetailInfo.h"
#include "..\..\Resource.h"

#include "Msg\MsgType-Village.h"
#include "MsgType-Structure.h"
#include "MsgType-System.h"
#include "Msg/MsgType-ItemMall.h"

#include "..\Client\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\Client\Interface\NotifyMsgDlg\NotifyMsgDlg.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/interface/ComboBox.h"
#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/CheckBox.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../NSoundOnOffDlg/NSoundOnOffDlg.h"

#include "../../InterfaceMgr/InterfaceFile.h"

#include "../Lib/JYLibFunction.h"
#include "../../NLib/NUtil.h"

// NUtil.cpp�� ����� ����
extern UI64	uiSec; // �ð� ����� ���� ���� ����


extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

cltNVillageDetailData villagedata[]={
		NVILLAGEDETAILINFOTYPE_VILLAGELIST,			TEXT("3643"),		TEXT(""),
        NVILLAGEDETAILINFOTYPE_SCORE,				TEXT("5995"),		TEXT("5996"),
		NVILLAGEDETAILINFOTYPE_VISITORNUM,			TEXT("3645"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_VILLAGEMONEY,		TEXT("3646"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_VILLAGEPROFIT,		TEXT("3647"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_VILLAGESTOCK,		TEXT("3648"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_GENERALMEETING,		TEXT("3649"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_PEOPLE,				TEXT("3650"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_WAR,					TEXT("3651"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_WARPERRESIDENT,		TEXT("3652"),	    TEXT(""),
		NVILLAGEDETAILINFOTYPE_USER,				TEXT("3653"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_PREVYEARDBID,		TEXT("3654"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_DECLAREWAR,			TEXT("3655"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_HUNT,				TEXT("3656"),		TEXT(""),
		NVILLAGEDETAILINFOTYPE_HORSEMARKET,			TEXT("3657"),		TEXT("3667"),
		NVILLAGEDETAILINFOTYPE_STOCK,				TEXT("3658"),		TEXT("3668"),
		NVILLAGEDETAILINFOTYPE_REALESTATEMARKET,	TEXT("3659"),		TEXT("3669"),
//KHY - 0611 - �񺯻�, �忹�� ����.
//		NVILLAGEDETAILINFOTYPE_SUMMONMARKET,		TEXT("3660"),		TEXT("3670"),
//		NVILLAGEDETAILINFOTYPE_SUMMONHEROMARKET,	TEXT("3661"),		TEXT("3671"),
		NVILLAGEDETAILINFOTYPE_FARM,				TEXT("3664"),		TEXT("3674"), 	
		NVILLAGEDETAILINFOTYPE_FEAST,				TEXT("3665"),		TEXT("3675"), 	
		NVILLAGEDETAILINFOTYPE_MINE,				TEXT("3666"),		TEXT("3676"),
//		NVILLAGEDETAILINFOTYPE_GUILD,				TEXT("5360"),		TEXT("5405"),
		NVILLAGEDETAILINFOTYPE_CITYHALLSTATE,		TEXT("5403"),		TEXT("5404"),	// ��û��������(����, �Ļ�, ������ ��)
		NVILLAGEDETAILINFOTYPE_VILLAGEWARRECORD,	TEXT("6484"),		TEXT(""), 								
		NVILLAGEDETAILINFOTYPE_NEWMARKET,			TEXT("9839"),		TEXT("9860"), 		// [����] ���ո��� ����.					
		0,											TEXT(""),			TEXT("")												
};

CNVillageDetailInfo::CNVillageDetailInfo()
{
	ZeroMemory( m_clvillagedata, sizeof(m_clvillagedata));

	SI32 siCount = 0;
	SI32 index = 0;

	while (villagedata[index].siType != 0)
	{
		if( false == pclClient->IsCountrySwitch( Switch_NewMarket ) )
		{
			if( NVILLAGEDETAILINFOTYPE_NEWMARKET == villagedata[index].siType )
			{
				index++;
				continue;
			}
		}

		m_clvillagedata[siCount].siType = villagedata[index].siType;
		StringCchCopy(m_clvillagedata[siCount].szExplainText, 256, villagedata[index].szExplainText);
		StringCchCopy(m_clvillagedata[siCount].szTypeText, 64, villagedata[index].szTypeText);

		index++;
		siCount++;
	}

	for (int i = 0; i < siCount; i++)
	{
		if (_tcscmp(m_clvillagedata[i].szTypeText, TEXT("")) != 0)
		{
			TCHAR* pText = GetTxtFromMgr(_tstoi(m_clvillagedata[i].szTypeText));
			StringCchCopy(m_clvillagedata[i].szTypeText, 64, pText);
		}

		if (_tcscmp(m_clvillagedata[i].szExplainText, TEXT("")) != 0)
		{
			TCHAR* pText = GetTxtFromMgr(_tstoi(m_clvillagedata[i].szExplainText));
			StringCchCopy(m_clvillagedata[i].szExplainText, 256, pText);
		}
	}

	bDlgRectInitSwitch = false;
	bCheckSortVillage	= false;
	siCurrentType		= 0;
	siOldCurrentType	= 0;
	siOldViliage		= 0;

	m_bShow = false;

	m_pNVillageDetailStatic		= NULL;  
	m_pNVillageDetailComboBox	= NULL;
	m_pNVillageDetailList		= NULL;    
	m_pWarpToNVillageButton		= NULL;  
	m_pNVillageDetailEdit		= NULL;    
	m_pCloseButton				= NULL;          
	m_pSortVillageCheckBox		= NULL;  

	for( SI16 i = 0; i < MAX_VILLAGE_NUMBER ; i++ )
	{
		m_siListdata[ i ] = -1;
	}

	bMasterView					= false;
	pSetGeneralmeetingButton	= NULL;
	// �˻����
	m_timerCount				= 0;
	m_pListBox_AutoMake			= NULL;
	m_pEdit_Name				= NULL;
	m_pButton_Accept			= NULL;
	m_pStatic_Back				= NULL;	//��׶���
}


CNVillageDetailInfo::~CNVillageDetailInfo()
{
	if(m_pNVillageDetailStatic)
	{
		delete m_pNVillageDetailStatic;  
		m_pNVillageDetailStatic = NULL;
	}
	if(m_pNVillageDetailComboBox)
	{
		delete m_pNVillageDetailComboBox;
		m_pNVillageDetailComboBox = NULL;
	}
	if(m_pNVillageDetailList)
	{
		delete m_pNVillageDetailList;    
		m_pNVillageDetailList = NULL;
	}
	if(m_pWarpToNVillageButton)
	{
		delete m_pWarpToNVillageButton;  
		m_pWarpToNVillageButton = NULL;
	}
	if(m_pNVillageDetailEdit)
	{
		delete m_pNVillageDetailEdit;    
		m_pNVillageDetailEdit = NULL;
	}
	if(m_pCloseButton)
	{
		delete m_pCloseButton;          
		m_pCloseButton = NULL;
	}
	if(m_pSortVillageCheckBox)
	{
		delete m_pSortVillageCheckBox;  
		m_pSortVillageCheckBox = NULL;
	}

	if(pSetGeneralmeetingButton)
	{
		delete pSetGeneralmeetingButton;  
		pSetGeneralmeetingButton = NULL;
	}
	// �˻����
	if(m_pListBox_AutoMake)
		delete m_pListBox_AutoMake;
	if(m_pEdit_Name)
		delete m_pEdit_Name;
	if(m_pButton_Accept)
		delete m_pButton_Accept;
	if(m_pStatic_Back)
		delete m_pStatic_Back;// ��׶���
	// �˻����
	m_pListBox_AutoMake	= NULL;
	m_pEdit_Name		= NULL;
	m_pButton_Accept	= NULL;
	m_pStatic_Back		= NULL; // ��׶���
	

	// Ÿ�̸Ӹ� �����Ѵ�. 
	SetTimerOnOff( false );
	
	// �������� ��ġ�� ����Ѵ�. 
	//GetWindowRect(hDlg, &DlgRect);
	bDlgRectInitSwitch = true;
}


void CNVillageDetailInfo::Create(CControllerMgr * pParent)
{
	SetTimerOnOff( true );
	SetActionTimer( 400 );
	if( !IsCreate() )
	{
		cltClient *pclclient = (cltClient *)pclClient;

		CInterfaceFile file;
		if(pclClient->IsCountrySwitch(Switch_FindInfo)) {
		file.LoadFile(TEXT("NInterface/Data/DLG_NVillageinfo.ddf"));
		}
		else{
			file.LoadFile(TEXT("NInterface/Data/DLG_NVillageinfo_J.ddf"));
		}

		file.CreateChildDialog(this, NVILLAGEDETAILINFO_DLG, TEXT("dialog_villageinfo") , StaticDlgProc , pParent );

		m_pNVillageDetailStatic		= new CStatic( this );  
		m_pNVillageDetailList		= new CList( this );    
		m_pWarpToNVillageButton		= new CButton( this );  
		m_pNVillageDetailEdit		= new CEdit( this );    		
		m_pSortVillageCheckBox		= new CCheckBox( this );   
		m_pNVillageDetailComboBox	= new CComboBox( this );
		pSetGeneralmeetingButton	= new CButton( this ); 
		

		// �˻����
		m_pListBox_AutoMake = new CList(this);
		m_pEdit_Name		= new CEdit(this);
		m_pButton_Accept	= new CButton(this);
		m_pStatic_Back		= new CStatic( this );	// ��׶���
		
		if(pclClient->IsCountrySwitch(Switch_FindInfo)) 
		{
			// �˻����
			file.CreateControl( m_pEdit_Name, NVILLAGEDETAILINFO_EDIT_NAME, TEXT("editbox_name") );
			file.CreateControl( m_pListBox_AutoMake, NVILLAGEDETAILINFO_LISTBOX_AUTOBOX , TEXT("listbox_automake") );
			file.CreateControl( m_pButton_Accept, NVILLAGEDETAILINFO_BUTTON_ACCEPT, TEXT("button_accept") );
			file.CreateControl( m_pStatic_Back, NVILLAGEDETAILINFO_DIALOG_CSTATICBACK,   TEXT("statictext_Back")); // ��׶��� 
			//---------------------------------------------------------------------------------------------------------
		}

		// [���� : Ȳ���� 2008. 2. 22 => �̹�ư�� �����ڸ� ����ϵ��� �ؾ��ϹǷ� ������ �ʰ� �Ѵ�.]
		file.CreateControl(pSetGeneralmeetingButton,  NVILLAGEDETAILINFO_DIALOG_SETGENERALMEETINGBUTTON,  TEXT("button_Set_General_meeting"));
		pSetGeneralmeetingButton->Show(false);

		file.CreateControl(m_pNVillageDetailStatic,  NVILLAGEDETAILINFO_DIALOG_NVILLAGEDETAILSTATIC,  TEXT("statictext_villagedetail"));
		file.CreateControl(m_pNVillageDetailList,    NVILLAGEDETAILINFO_DIALOG_NVILLAGEDETAILLIST,    TEXT("listbox_villagedetail"));
		file.CreateControl(m_pWarpToNVillageButton,  NVILLAGEDETAILINFO_DIALOG_WARPTONVILLAGEBUTTON,  TEXT("button_warptovillage"));
		file.CreateControl(m_pNVillageDetailEdit,    NVILLAGEDETAILINFO_DIALOG_NVILLAGEDETAILEDIT,    TEXT("editbox_villageinfo"));
		
		file.CreateControl(m_pSortVillageCheckBox,   NVILLAGEDETAILINFO_DIALOG_SORTNVILLAGECHECKBOX,  TEXT("checkbox_sortvillage"));
		file.CreateControl(m_pNVillageDetailComboBox,NVILLAGEDETAILINFO_DIALOG_NVILLAGEDETAILCOMBOBOX, TEXT("combobox_villagedetail"));
		
		m_pNVillageDetailList->SetTextPrintOption( DT_LEFT | DT_VCENTER | DT_SINGLELINE );

		//TCHAR* pText = GetTxtFromMgr(1831);
		m_pNVillageDetailList->SetColumn( 0, 328, NULL );
		m_pNVillageDetailList->SetColumn( 1, 18, NULL );
		m_pNVillageDetailList->SetBorder( true );
		m_pNVillageDetailList->SetBKColorUse( true );
		m_pNVillageDetailList->Refresh();
		
		siCurrentType		= NVILLAGEDETAILINFOTYPE_VILLAGELIST;
		siOldCurrentType	= 0;
		siOldViliage		= 0;
		SetDataTypeInCombo();

		if(m_pNVillageDetailComboBox->GetItemNum() > 0)
			m_pNVillageDetailComboBox->SetCursel( 0 );

		// ���̾�α� �ʱⰪ ����
		// �˻����
		m_pEdit_Name->Refresh();
		m_pButton_Accept->Refresh();
		m_pListBox_AutoMake->SetColumn(0,1,NULL);
		m_pListBox_AutoMake->SetColumn(1,160,NULL);
		m_pListBox_AutoMake->SetShowHeader(FALSE);
		m_pListBox_AutoMake->Show(false);
		SetActionTimer( 400 );
		SetTimerOnOff( true );
	}
	else
	{
		DeleteDialog();       
	}
}

void CALLBACK CNVillageDetailInfo::StaticDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNVillageDetailInfo *pThis = (CNVillageDetailInfo*)pControllerMgr;
	pThis->DlgProc( nEvent, nControlID, pControl);
}


void CALLBACK CNVillageDetailInfo::DlgProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient* pclclient = (cltClient*)pclClient;
	SI32 id = 1;

	stListBoxItemData tmpListBoxItemData;
	stListBoxItemData *pTmpListBoxItemData = NULL;

	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NVILLAGEDETAILINFO_DIALOG_SETGENERALMEETINGBUTTON:
		{
			// ���� ���õ� ������  Ȯ���Ѵ�. 
			SI32 siCurrentVillage = 0;
			SI16 tmpRow = 0, tmpColumn = 0;

			m_pNVillageDetailList->GetSelectedIndex(&tmpRow, &tmpColumn);
			SI32 index = tmpRow;
			
			if( 0 >= index || MAX_VILLAGE_NUMBER <= index )
				return;

			bool bResult = pclClient->pclVillageManager->pclVillageInfo[index]->clVillageVary.m_bGeneralMeetingSuggest;
	
			NTCHARString128 kbuf; 
			if(	bResult )
			{
				kbuf = "/cityhalloff #value#";
			}
			else
			{
				kbuf = "/cityhallon #value#";
			}

			kbuf.Replace( "#value#", SI32ToString( index ) );

			// ä�� ���
			if( pclClient->pclCM->GetCharClient(1)->m_stMuteTime.wYear > 0 )
			{
				NTCHARString256		kText(GetTxtFromMgr(9626));
				NTCHARString256		kTitle(GetTxtFromMgr(5614));

				SI64 siTimeDiff = TimeOperation(&pclClient->pclCM->GetCharClient(1)->m_stMuteTime, &pclclient->sTime);
				if( siTimeDiff > 0 )
				{
					kText.Replace("#minute#", SI32ToString(siTimeDiff / (uiSec * 60)));
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( kTitle, kText);
				}
			}
			else
			{
				cltGameMsgRequest_Chat clinfo( 1, 0, kbuf );
				cltMsg clMsg( GAMEMSG_REQUEST_CHAT, clinfo.siDataSize, (BYTE*)&clinfo );
				pclClient->SendMsgToServer( ( sPacketHeader* )&clMsg );
			}
		}
		break;
	case NVILLAGEDETAILINFO_DIALOG_WARPTONVILLAGEBUTTON: // ������ �̵�
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[1];
					if( pclchar == NULL ) return; // ����

					// ���� ���õ� ������  Ȯ���Ѵ�. 
					SI32 siCurrentVillage = 0;
					SI16 tmpRow = 0, tmpColumn = 0;

					m_pNVillageDetailList->GetSelectedIndex(&tmpRow, &tmpColumn);
					SI32 index = tmpRow;

					if(index < 0)
					{
						TCHAR* pTitle = GetTxtFromMgr(1413);
						TCHAR* pText = GetTxtFromMgr(1415);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
					else
					{
						pTmpListBoxItemData = m_pNVillageDetailList->GetItemData( tmpRow, 0);
						if(pTmpListBoxItemData == NULL)		return;

						siCurrentVillage = pTmpListBoxItemData->siParam[0];
						
						// �̵��� ������ �����Ѵ�. 
						if(siCurrentVillage <= 0)
						{
							TCHAR* pTitle = GetTxtFromMgr(1413);
							TCHAR* pText = GetTxtFromMgr(1415);

							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							return;
						}
					}
					
					TCHAR buffer[256] = TEXT("") ;
					TCHAR* pTitle = NULL ;
					TCHAR* pText = NULL ;
                    
					TCHAR* pname = pclClient->pclVillageManager->GetName(siCurrentVillage);
					if(pname == NULL)return ;

					// ĳ���Ͱ� ���� �� �� �ִ��� üũ
					//if( pclchar->CanWarpFrom() == false)
					//	return;

					// [���� : Ȳ���� 2008. 1. 15 => ��¥ ���� ���� �Լ� ���.]
					if( pclchar->CanFreeWarp( siCurrentVillage ) == false )
					{
						// �����̵��̿���� �����ϰ� �ִ��� Ȯ���Ѵ�. 
						SI32 itemunique = ITEMUNIQUE(24000) ;  // �����̵��̿��
						SI32 pos = pclchar->pclCI->clCharItem.FindItemInv(itemunique);
						if(pos < 0)
						{
							TCHAR* pTitle = GetTxtFromMgr(1413);
							TCHAR* pText = GetTxtFromMgr(1414);

							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);

							return ;
						}
						pTitle = GetTxtFromMgr(1418);
						pText = GetTxtFromMgr(1417);

						StringCchPrintf(buffer, 256, pText,pname);
					}
					else
					{
						pTitle = GetTxtFromMgr(3189);
						pText = GetTxtFromMgr(1893);

						StringCchPrintf(buffer, 256, pText,pname);
					}

					stMsgBox MsgBox;
					MsgBox.Set( this->GetParentDialog(), pTitle, buffer, MSGBOX_TYPE_YESNO, 4 );
					BYTE TempBuffer[ 128 ];
					SI16 Size = sizeof( siCurrentVillage );
					memcpy( TempBuffer, &siCurrentVillage, Size );
					pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
				}				
				return;
				break;
			}
		}
		break;

		case NVILLAGEDETAILINFO_DIALOG_SORTNVILLAGECHECKBOX:
			{
				switch( nEvent )
				{
				case EVENT_CHECKBOX_CHANGED: 
					{
						if(siCurrentType == NVILLAGEDETAILINFOTYPE_VILLAGELIST)
						{
							TCHAR* sidata[MAX_VILLAGE_NUMBER];
							SI32  siVillageInfo[MAX_VILLAGE_NUMBER];

							// ������ ����Ʈ�� �����Ѵ�. 
							m_pNVillageDetailList->Clear();

							SI32 i;

							for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
							{
								sidata[i] = pclClient->pclVillageManager->GetName(i);
							}
							SI32 index = Sort(sidata, siVillageInfo);

							SI32 villindex = 1;

							if( m_pSortVillageCheckBox->IsCheck() == true )
								bCheckSortVillage = true;
							else
								bCheckSortVillage  = false;

							//bCheckSortVillage = !bCheckSortVillage;
							if(TRUE == bCheckSortVillage)
							{
								for(i = 0;i < index; ++i)
								{
									SI32 villageunique = siVillageInfo[i];

									if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

									TCHAR buffer[256];
									StringCchPrintf(buffer, 256, TEXT("%d. %s"), villindex, pclClient->pclVillageManager->GetName(villageunique)); 

									tmpListBoxItemData.Init();
									tmpListBoxItemData.Set( 0, buffer );
									tmpListBoxItemData.siParam[0] = villageunique;
									villindex++;

									// ����Ʈ �׸� �����͸� �����Ѵ�. 
									SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
									m_siListdata[index] = villageunique;
								}
							}
							else
							{
								for(SI32 i = 0;i < MAX_VILLAGE_NUMBER;i++)
								{

									if(pclClient->pclVillageManager->pclVillageInfo[i] == NULL)continue;

									TCHAR buffer[256];
									StringCchPrintf(buffer, 256, TEXT("%d. %s"), villindex, pclClient->pclVillageManager->GetName(i)); 
									villindex++;

									tmpListBoxItemData.Init();
									tmpListBoxItemData.Set( 0, buffer );
									tmpListBoxItemData.siParam[ 0 ] = i;

									// ����Ʈ �׸� �����͸� �����Ѵ�. 
									SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
									m_siListdata[index] = i;
								}

							}
                            m_pNVillageDetailList->Refresh();
						}
					}
					return;
				}
			}
			break;
			//ã�� ���
		case NVILLAGEDETAILINFO_EDIT_NAME:
			{
				switch(nEvent) 
				{
				case EVENT_EDITBOX_CHANGE:
					{
					}break;
				case EVENT_EDITBOX_STRING:
					{
						TCHAR* pItemname = m_pEdit_Name->GetText();
						if (pItemname == NULL)	return;
						Find(pItemname);
					}break;
				}
			}
		case NVILLAGEDETAILINFO_LISTBOX_AUTOBOX:
			{
				switch(nEvent) {
						case EVENT_LISTBOX_SELECTION:
						{
							SI16 SelectIndex= m_pListBox_AutoMake->GetSelectedIndex();
							if(SelectIndex >= 0)
							{
								TCHAR* pItemname = m_pListBox_AutoMake->GetText(SelectIndex,1);
								m_pEdit_Name->SetText(pItemname);
								m_pEdit_Name->Refresh();
							}
							m_pListBox_AutoMake->Clear();
							m_pListBox_AutoMake->Show(false);
						}break;
					}
			}
		case NVILLAGEDETAILINFO_BUTTON_ACCEPT:
			{
				switch(nEvent) 
				{
					case EVENT_BUTTON_CLICKED:
						{
							TCHAR* pItemname = m_pEdit_Name->GetText();
							if (pItemname == NULL)	return;
							Find(pItemname);
							
						}break;
				}
			}break;

		case NVILLAGEDETAILINFO_DIALOG_NVILLAGEDETAILCOMBOBOX:
			{
				switch( nEvent )
				{
				case EVENT_COMBOBOX_SELECTION_CHANGED:
					{
						SI32 id = 1;
						if(pclClient->pclCM->IsAlive(id) == false)break;

						TCHAR szSelText[128]=TEXT("");
						TCHAR* pTmpChar = NULL;

						pTmpChar = m_pNVillageDetailComboBox->GetText(m_pNVillageDetailComboBox->GetSelectedIndex());

						if(pTmpChar == NULL)
							break;

						StringCchCopy(szSelText, 128, pTmpChar);

						// ������ �ڵ带 ã�´�.
						SI32 type = GetVillageDetailType(szSelText);

						if(type)
						{
							siCurrentType = type;
						}

					}
					break;
				}
			}
			break;
	}
	
	return;
}


// �޺��� ������ Ÿ���� �ִ´�. 
void CNVillageDetailInfo::SetDataTypeInCombo()
{
	stComboBoxItemData tmpComboBoxItemData;

	// �޺� �ڽ��� �����.
	m_pNVillageDetailComboBox->Clear();

	SI32 index = 0;
	while(m_clvillagedata[index].siType > 0)
	{
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( m_clvillagedata[index].szTypeText );

		m_pNVillageDetailComboBox->AddItem( &tmpComboBoxItemData );

		index++;
	}

}

// �ؽ�Ʈ�� �ٰŷ� ���� �� ���� �ڵ带 ���Ѵ�. 
SI32 CNVillageDetailInfo::GetVillageDetailType(TCHAR* ptext)
{
	SI32 index = 0;

	while(m_clvillagedata[index].siType > 0)
	{
		if(_tcscmp(m_clvillagedata[index].szTypeText, ptext) == 0)
		{
			return m_clvillagedata[index].siType;
		}

		index++;
	}

	return 0;
}

// Ÿ���� �ٰŷ� ���� �����͸� ���Ѵ�. 
cltNVillageDetailData* CNVillageDetailInfo::GetNVillageDetailData(SI32 type)
{
	SI32 index = 0;

	while(m_clvillagedata[index].siType > 0)
	{
		if(m_clvillagedata[index].siType == type)
		{
			return &m_clvillagedata[index];
		}

		index++;
	}

	return NULL;
}

// �ǹ� �� ������ ǥ���Ѵ�. 
void CNVillageDetailInfo::ShowStrInfo(TCHAR*  pText)
{
	if(m_pNVillageDetailEdit)
		m_pNVillageDetailEdit->SetText( pText );
}

// ������ ���� ���� ������ ǥ���Ѵ�. 
void CNVillageDetailInfo::ShowInfo(cltGameMsgResponse_VillageDetailInfo* pclinfo)
{
	SI32 i;
	TCHAR buffer[256] = TEXT("");

	stListBoxItemData tmpListBoxItemData;

	// ������ ����Ʈ�� �����Ѵ�. 
	m_pNVillageDetailList->Clear();

	SI64 sidata[MAX_VILLAGE_NUMBER];
	SI32 siVillageInfo[MAX_VILLAGE_NUMBER];

	// ���� ��� �뺸. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_WAR)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siWarKillNum[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			StringCchPrintf(buffer, 256, TEXT("%d. %s - %d"), i+1, pclClient->pclVillageManager->GetName(villageunique),pclinfo->siWarKillNum[villageunique]); 

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	}
	// ���� ��� �뺸. (�ֹ� 100���) 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_WARPERRESIDENT)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siWarKillNum[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			StringCchPrintf(buffer, 256, TEXT("%d. %s - %d"), i+1, pclClient->pclVillageManager->GetName(villageunique),pclinfo->siWarKillNum[villageunique]); 

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[0] = villageunique;

			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	}


	// �ֹμ� ��� �뺸. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_PEOPLE)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->uiPeople[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			TCHAR* pText = GetTxtFromMgr(1419);

			StringCchPrintf(buffer, 256, pText, i+1, pclClient->pclVillageManager->GetName(villageunique),pclinfo->uiPeople[villageunique]); 

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	}
	// ���� ���� ����ڼ�. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_USER)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siUserNum[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0 ;i < index ;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			TCHAR* pText = GetTxtFromMgr(1419);

            StringCchPrintf(buffer, 256, pText, i+1, pclClient->pclVillageManager->GetName(villageunique),pclinfo->siUserNum[villageunique]); 

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();

	}

	// ���⵵ ���� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_PREVYEARDBID)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siBidMoney[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			GMONEY money = pclinfo->siBidMoney[villageunique];
			TCHAR buf[64] = TEXT("");

			g_JYLibFunction.SetNumUnit( money, buf, 64 );

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			StringCchPrintf(buffer, 256, TEXT("%d. %s - %s"), i+1, pclClient->pclVillageManager->GetName(villageunique), buf); 

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	}

	// ������ ���� ����. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_HUNT
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_HORSEMARKET
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_STOCK
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_REALESTATEMARKET
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SUMMONMARKET
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SUMMONHEROMARKET
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_FARM
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_FEAST
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_MINE 
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_NEWMARKET	)
//	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_GUILD )
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siStrData[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			// ��ȿ���� ���� �ǹ��� �����Ѵ�. 
			if(pclinfo->siStrData[villageunique] <= 0)continue;

			if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_HUNT)
			{
				TCHAR* pText = GetTxtFromMgr(1420);

				StringCchPrintf(buffer, 256, pText, i+1, 
					pclClient->pclVillageManager->GetName(villageunique),
					max(0, (pclinfo->siStrData[villageunique] - 1)) );	// �������� 1���� ���߱� ������ Ŭ���̾�Ʈ������ 1���� ����. 
			}
			else if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_HORSEMARKET
				||  pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_STOCK
				||  pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_REALESTATEMARKET
				||  pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SUMMONMARKET
				||  pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SUMMONHEROMARKET
				||  pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_NEWMARKET
				)
			{
				TCHAR* pText = GetTxtFromMgr(1421);

				StringCchPrintf(buffer, 256, pText, i+1, 
					pclClient->pclVillageManager->GetName(villageunique),
					(float)((pclinfo->siStrData[villageunique] - 1)/ 10.0)); 

				if( pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_STOCK )
				{
					pclClient->pclCM->CR[1]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SEARCHSTOCKINFO);
				}
			}
			else if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_FARM)
			{
				pclClient->pclCM->CR[1]->DoQuestCheckAndAction( QUEST_CLEAR_COND_SEARCHFARM );

				SI32 siRentpay = pclinfo->siStrData[villageunique] - 1;
				TCHAR payBuf[128];
				g_JYLibFunction.SetNumUnit( siRentpay, payBuf, 128 );

				TCHAR* pText = GetTxtFromMgr(1423);
				StringCchPrintf(buffer, 256, pText, 
					i+1, pclClient->pclVillageManager->GetName(villageunique), payBuf );
			}
			else if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_FEAST)
			{
				TCHAR* pText = GetTxtFromMgr(1424);
				StringCchPrintf(buffer, 256, pText, 
					i+1, pclClient->pclVillageManager->GetName(villageunique), pclinfo->siStrData[villageunique] - 1);
			}
			else if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_MINE)
			{
				SI32 siRentpay = pclinfo->siStrData[villageunique] - 1;
				TCHAR payBuf[128];
				g_JYLibFunction.SetNumUnit( siRentpay, payBuf, 128 );

				TCHAR* pText = GetTxtFromMgr(1423);
				StringCchPrintf(buffer, 256, pText, 
					i+1, pclClient->pclVillageManager->GetName(villageunique), payBuf );
			}
/*			else if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_GUILD)
			{
				SI32 siRentpay = pclinfo->siStrData[villageunique] - 1;
				TCHAR payBuf[128];
				g_JYLibFunction.SetNumUnit( siRentpay, payBuf, 128 );

				TCHAR* pText = GetTxtFromMgr(1423);
				StringCchPrintf(buffer, 256, pText, 
					i+1, pclClient->pclVillageManager->GetName(villageunique), payBuf );
			}*/

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	
	}
	// �������� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGEWARRECORD)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siVillageWarRecordWinAndLose[0][i]; // �¸����� �������� ����
		}
		SI32 index = Sort(sidata, siVillageInfo);

		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;
			
			TCHAR * pTextWin = GetTxtFromMgr(6487);
			TCHAR * pTextLose = GetTxtFromMgr(6488);

			StringCchPrintf(buffer, 256, TEXT("%d. %s - %s [%2d]  %s [%2d]"), i+1, pclClient->pclVillageManager->GetName(villageunique), pTextWin ,pclinfo->siVillageWarRecordWinAndLose[0][villageunique], pTextLose ,pclinfo->siVillageWarRecordWinAndLose[1][villageunique]); 

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	}
	// �������  
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGELIST)
	{

	}


	// ���� �ڱ� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGEMONEY
	|| pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGEPROFIT)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siStrData[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		TCHAR buf[256];
		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			// ���ڿ� �޸��� ��´�. 
			TCHAR* pText = GetTxtFromMgr(4837);
			g_JYLibFunction.SetNumUnit( pclinfo->siStrData[villageunique], buf, 256, pText );

			StringCchPrintf(buffer, 256, TEXT("%d. %s - %s"), i+1, 
				pclClient->pclVillageManager->GetName(villageunique), buf);

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			GMONEY index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	
	}
	// ���� �湮�ڼ�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VISITORNUM)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siStrData[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		TCHAR buf[256];
		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			// ���ڿ� �޸��� ��´�. 
			TCHAR* pText = GetTxtFromMgr(2085);
			g_JYLibFunction.SetNumUnit( pclinfo->siStrData[villageunique], buf, 256, pText );

			StringCchPrintf(buffer, 256, TEXT("%d. %s - %s"), i+1, 
				pclClient->pclVillageManager->GetName(villageunique), buf);

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
		
	}

	// ���� �ֽļ�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGESTOCK)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siStrData[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		TCHAR buf[256];
		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

			// ���ڿ� �޸��� ��´�. 
			TCHAR* pText = GetTxtFromMgr(1663);
			g_JYLibFunction.SetNumUnit( pclinfo->siStrData[villageunique], buf, 256, pText);

			StringCchPrintf(buffer, 256, TEXT("%d. %s - %s"), i+1, 
				pclClient->pclVillageManager->GetName(villageunique), buf);

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
		
	}
	// ������ȸ ���ึ�� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_GENERALMEETING)
	{
		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = pclinfo->siStrData[i];
		}
		SI32 index = Sort(sidata, siVillageInfo);

		TCHAR buf[256] = TEXT("") ;
		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;
			
			// ��ȿ���� ���� �ǹ��� �����Ѵ�. 
			if(pclinfo->siStrData[villageunique] <= 0)continue;


			StringCchPrintf(buffer, 256, TEXT("%d. %s"), i+1, 
				pclClient->pclVillageManager->GetName(villageunique));

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}
		m_pNVillageDetailList->Refresh();
		
	}

	// ��û��������(����, �Ļ�, ���� �� )
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_CITYHALLSTATE )
	{
		//UI08 uidata[MAX_VILLAGE_NUMBER];

		//--------------------------------
		// ������������ �����Ѵ�. 
		//--------------------------------
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			sidata[i] = (SI32)pclinfo->uiCityHallState[i];
			siVillageInfo[i] = i;
		}
		//SI32 index = Sort(sidata, siVillageInfo);
		SI32 index = MAX_VILLAGE_NUMBER;
		SI32 count = 0;

		TCHAR buf[256] = TEXT("") ;
		for(i = 0;i < index;i++)
		{
			SI32 villageunique = siVillageInfo[i];

			if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL 
				|| sidata[i] >= CITYHALL_UNDEFINED_STATE 
				|| sidata[i] >= CITYHALL_BEING_PROCESSING )continue;
			
			TCHAR* pStateName = NULL;

            switch( sidata[ i ] )
			{
			case 	CITYHALL_BEING_BANKRUPT	:		// �Ļ��
				pStateName = GetTxtFromMgr(5240);
				break;
			case 	CITYHALL_BEING_INITIALIZED	:	// �ʱ�ȭ��
				pStateName = GetTxtFromMgr(5241);
				break;
			case 	CITYHALL_BEING_STABLE		:	// ������
				pStateName = GetTxtFromMgr(5242);
				break;
			case CITYHALL_BEING_NORMAL			:	// �����
				//pStateName = GetTxtFromMgr(5239);
				break;
			default:
				continue;
				break;
			}

			if( sidata[i] != CITYHALL_BEING_NORMAL)
			{
				StringCchPrintf(buffer, 256, TEXT("%d. %s - %s"), ++count, 
					pclClient->pclVillageManager->GetName(villageunique), 
					pStateName );
			}
			else
			{
				StringCchPrintf(buffer, 256, TEXT("%d. %s"), ++count, 
					pclClient->pclVillageManager->GetName(villageunique) );
			}

			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, buffer );
			tmpListBoxItemData.siParam[ 0 ] = villageunique;
			
			// ����Ʈ �׸� �����͸� �����Ѵ�. 
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
		
	}

	// ���� ����
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

			//// ��ȿ���� ���� �ǹ��� �����Ѵ�. 
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
			SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
			m_siListdata[index] = villageunique;
		}

		m_pNVillageDetailList->Refresh();
	}


}

// ������������ �����Ѵ�. 
SI32 CNVillageDetailInfo::Sort(SI32 sisortdata[], SI32* pvillageunique)
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
// ������������ �����Ѵ�. 
SI32 CNVillageDetailInfo::Sort(SI64 sisortdata[], SI32* pvillageunique)
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

SI32 CNVillageDetailInfo::Sort(TCHAR* psortname[], SI32* pvillageunique)
{
	SI32 i;
	SI32 index = 0;

	SI32 tempbuf[ MAX_VILLAGE_NUMBER ];

	for( i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		tempbuf[ i ] = i;
	}

	for(SI32 vill = 0;vill < MAX_VILLAGE_NUMBER - 1;vill++)
	{
		if(pclClient->pclVillageManager->pclVillageInfo[vill] == NULL)continue;

		for(i = vill + 1;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclClient->pclVillageManager->pclVillageInfo[i] == NULL)continue;

			int cmpindex1 = tempbuf[ vill ];
			int cmpindex2 = tempbuf[ i ];

			SI32 result = _tcscmp( psortname[ cmpindex1 ], psortname[ cmpindex2 ] );
			if( result > 0 )
			{
				int temp = tempbuf[ vill ];
				tempbuf[ vill ] = tempbuf[ i ];
				tempbuf[ i ] = temp;
			}
		}
	}

	index = 0;
	for(i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		if( pclClient->pclVillageManager->pclVillageInfo[ tempbuf[i] ]== NULL)continue;
		pvillageunique[ index ] = tempbuf[ i ];
		index++;
	}

	return index;
}

// Action() : WM_TIMER ó�� �Լ�
void CNVillageDetailInfo::Action()
{
	cltClient* pclclient = (cltClient*)pclClient;

	stListBoxItemData tmpListBoxItemData;

	// ���� �̸��� ���� ���̱�, �Ⱥ��̱�
	if(siCurrentType == NVILLAGEDETAILINFOTYPE_VILLAGELIST)
	{
        m_pSortVillageCheckBox->Show( true );
	}
	else
	{
		m_pSortVillageCheckBox->Show( false );
	}
	if( false == IsShow() )	return;
	if( m_timerCount >= LEAST_COMMON_MULTILPLE + 1 )
		m_timerCount = 1;
	m_timerCount++;
	Update();

	// ���õ� �׸��� �ִٸ�,
	if(siCurrentType && (siCurrentType != siOldCurrentType))
	{
		siOldCurrentType = siCurrentType;

		// �������� ����� Ŭ���̾�Ʈ���� �̹� �ľ��ϰ��ִ�. 
		if(siCurrentType == NVILLAGEDETAILINFOTYPE_DECLAREWAR)
		{
			cltClient* pclclient = (cltClient*)pclClient;
			TCHAR buffer[256] = TEXT("");

			stListBoxItemData tmpListBoxItemData;

			// ������ ����Ʈ�� �����Ѵ�. 
			m_pNVillageDetailList->Clear();

			SI64 sidata[MAX_VILLAGE_NUMBER];
			SI32 siVillageInfo[MAX_VILLAGE_NUMBER];

			NDate currentDate;
			currentDate.m_uiYear = pclclient->sTime.wYear;
			currentDate.m_uiMonth = pclclient->sTime.wMonth;
			currentDate.m_uiDay = pclclient->sTime.wDay;


			//--------------------------------
			// ������������ �����Ѵ�. 
			//--------------------------------
			SI32 i;
			for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
			{
				sidata[i] = pclClient->pclVillageManager->clDeclareWarDate[i].GetDateVary();
			}
			SI32 index = Sort(sidata, siVillageInfo);

			NDate warDate;					// ���� ������ �����ϴ� �ð�

			UI32 warStartHour;				// ������ �����ϴ� �ð�
			if ( pclClient->siServiceArea == ConstServiceArea_English	||
				pclClient->siServiceArea == ConstServiceArea_NHNChina	|| 
				pclClient->siServiceArea == ConstServiceArea_EUROPE
			)
			{
				warStartHour = 1;
			}
			else
			{
				warStartHour = 21;
			}


			for(i = 0;i < index;i++)
			{
				SI32 villageunique = siVillageInfo[i];
				warDate = pclClient->pclVillageManager->clDeclareWarDate[villageunique];

				if ( warDate.m_uiYear == 0 )
					continue;

				warDate.AddDays( 2 );

				if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)
					continue;

				// ����ð��� ������ �����ϴ� �ð����� �������� ���ġ ����
				if( warDate.GetDateVary() <= currentDate.GetDateVary() && pclclient->sTime.wHour > warStartHour )
					continue;

				//�����Ϸ��� ��� ������ ������ ���ġ ����
				if( pclclient->pclVillageManager->siDeclareWarVillage[villageunique] == 0 )
					continue;

				if ( pclclient->siServiceArea == ConstServiceArea_English	||
					pclclient->siServiceArea == ConstServiceArea_NHNChina	||
					pclclient->siServiceArea == ConstServiceArea_EUROPE
				)
				{
					StringCchPrintf(buffer, 256, TEXT("%02d-%02d-%04d"), 
						warDate.m_uiMonth, warDate.m_uiDay, warDate.m_uiYear );
				}
				else
				{
					StringCchPrintf(buffer, 256, TEXT("%04d/%02d/%02d"), 
						warDate.m_uiYear, warDate.m_uiMonth, warDate.m_uiDay );
				}

				TCHAR szDeclareVillage[256] = TEXT("");

				StringCchPrintf( szDeclareVillage, 256, TEXT("%s - %s [%s]"),
					pclClient->pclVillageManager->GetName(villageunique),
					pclClient->pclVillageManager->GetName(pclClient->pclVillageManager->siDeclareWarVillage[villageunique]),
					buffer );


				tmpListBoxItemData.Init();
				tmpListBoxItemData.Set( 0, szDeclareVillage );

				// ����Ʈ �׸� �����͸� �����Ѵ�. 
				SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
				m_siListdata[index] = villageunique;
			}
			m_pNVillageDetailList->Refresh();
		}
		else if(siCurrentType == NVILLAGEDETAILINFOTYPE_VILLAGELIST)
		{
			if( true == bMasterView )
			{
				// ä�� ���
				if( pclClient->pclCM->GetCharClient(1)->m_stMuteTime.wYear > 0 )
				{
					NTCHARString256		kText(GetTxtFromMgr(9626));
					NTCHARString256		kTitle(GetTxtFromMgr(5614));

					SI64 siTimeDiff = TimeOperation(&pclClient->pclCM->GetCharClient(1)->m_stMuteTime, &pclclient->sTime);
					if( siTimeDiff > 0 )
					{
						kText.Replace("#minute#", SI32ToString(siTimeDiff / (uiSec * 60)));
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( kTitle, kText);
					}
				}
				else
				{
					cltGameMsgRequest_Chat clinfo(1, 0, "/cityhallinfo");
					cltMsg clMsg(GAMEMSG_REQUEST_CHAT, clinfo.siDataSize, (BYTE*)&clinfo);
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
				//GeneralMeetingSuggestInfo();
				return;
			}
			else
			{
				// ������ ����Ʈ�� �����Ѵ�. 
				m_pNVillageDetailList->Clear();

				TCHAR* sidata[MAX_VILLAGE_NUMBER];
				SI32  siVillageInfo[MAX_VILLAGE_NUMBER];

				SI32 i;
				for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
				{
					sidata[i] = pclClient->pclVillageManager->GetName(i);
				}
				SI32 index = Sort(sidata, siVillageInfo);

				SI32 villindex = 1;
				if(TRUE == bCheckSortVillage)
				{
					//m_pSortVillageCheckBox->SetCheck( true );
					bCheckSortVillage = true;

					for(i = 0;i < index; ++i)
					{
						SI32 villageunique = siVillageInfo[i];

						if(pclClient->pclVillageManager->pclVillageInfo[villageunique] == NULL)continue;

						TCHAR buffer[256];
						StringCchPrintf(buffer, 256, TEXT("%d. %s"), villindex, pclClient->pclVillageManager->GetName(villageunique)); 

						villindex++;

						tmpListBoxItemData.Init();
						tmpListBoxItemData.Set( 0, buffer );
						tmpListBoxItemData.siParam[ 0 ] = villageunique;

						// ����Ʈ �׸� �����͸� �����Ѵ�. 
						SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
						m_siListdata[index] = villageunique;
					}

					m_pNVillageDetailList->Refresh();
				}
				else
				{
					//m_pSortVillageCheckBox->SetCheck( false );
					bCheckSortVillage = false;

					for(SI32 i = 0;i < MAX_VILLAGE_NUMBER;i++)
					{

						if(pclClient->pclVillageManager->pclVillageInfo[i] == NULL)continue;

						TCHAR buffer[256];
						StringCchPrintf(buffer, 256, TEXT("%d. %s"), villindex, pclClient->pclVillageManager->GetName(i)); 
						villindex++;

						tmpListBoxItemData.Init();
						tmpListBoxItemData.Set( 0, buffer );
						tmpListBoxItemData.siParam[ 0 ] = i;					

						// ����Ʈ �׸� �����͸� �����Ѵ�. 
						SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
						m_siListdata[index] = i;
					}

					m_pNVillageDetailList->Refresh();
				}
			}
		}
		else
		{
			cltGameMsgRequest_VillageDetailInfo clinfo(siCurrentType);
			cltMsg clMsg(GAMEMSG_REQUEST_VILLAGEDETAILINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);

			// ������ ����Ʈ�� �����Ѵ�. 
            m_pNVillageDetailList->Clear();

			// ������ �����ش�.
			cltNVillageDetailData* pinfo = GetNVillageDetailData(siCurrentType);
			if(pinfo)
			{
				ShowStrInfo(pinfo->szExplainText);
			}

		}

	}

	if(siCurrentType)
	{
		// ���� ���õ� �б���  Ȯ���Ѵ�. 
		SI16 tmpRow = 0, tmpColumn = 0;
		m_pNVillageDetailList->GetSelectedIndex( &tmpRow, &tmpColumn );

		SI32 index = tmpRow;
		
		if(index < 0) return;
		if(tmpColumn < 0 || tmpRow < 0)
			return;

		stListBoxItemData *pTmpListBoxItemData = NULL;

		pTmpListBoxItemData = m_pNVillageDetailList->GetItemData( tmpRow, tmpColumn );

		SI32 siCurrentVillage =  pTmpListBoxItemData->siParam[0];

		//sscanf( m_pNVillageDetailList->GetText( tmpRow, tmpColumn ), TEXT("%d"), &siCurrentVillage );

		if(siCurrentVillage > 0 && siCurrentVillage != siOldViliage)
		{
			siOldViliage = siCurrentVillage;
			// ���ο������� ��û�Ѵ�.
			switch( siCurrentType )
			{
			case NVILLAGEDETAILINFOTYPE_HUNT:
				{
					cltGameMsgRequest_VillageInfoStrInfo clinfo(siCurrentVillage, RANKTYPE_HUNT);
					cltMsg clMsg(GAMEMSG_REQUEST_VILLAGEINFOSTRINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				break;
			case NVILLAGEDETAILINFOTYPE_CITYHALLSTATE:
				{
					cltGameMsgRequest_VillageInfoStrInfo clinfo(siCurrentVillage, RANKTYPE_CITYHALL);
					cltMsg clMsg(GAMEMSG_REQUEST_VILLAGEINFOSTRINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				break;
			case NVILLAGEDETAILINFOTYPE_STOCK:
				{
					//pclClient->pclCM->CR[1]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SEARCHSTOCKINFO);
				}
				break;
			default:		// ���� �Ұ��� ��û
				{
					cltGameMsgRequest_GetStrNotice clinfo( siCurrentVillage, RANKTYPE_CITYHALL );
					cltMsg clMsg(GAMEMSG_REQUEST_GETSTRNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				break;
			}
		}
	}
}

void CNVillageDetailInfo::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
	case 4:	// ������ �̵�
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32 siCurrentVillage = *((SI32*)pData);
				//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.Ŭ���� ����.
				cltGameMsgRequest_HuntMapWarp pclInfo(siCurrentVillage,0);
				cltMsg clMsg( GAMEMSG_REQUEST_HUNTMAPWARP, sizeof( pclInfo ), (BYTE*)&pclInfo );
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		break;
	}
}

//bool CNVillageDetailInfo::IsShow()
//{
//	return m_bShow;
//}
//
void CNVillageDetailInfo::Show()
{
    if( IsShow() )
	{
		//Hide();
		return;
	}

	SetTimerOnOff( true );

	m_bShow = true;

	CDialogController::Show( true );

	pclClient->pclCM->CR[1]->DoQuestCheckAndAction(QUEST_CLEAR_COND_VILLAGEDETAILINFO);

	return;
}

void CNVillageDetailInfo::Hide()
{
	SetTimerOnOff( false );

	m_bShow = false;

	CDialogController::Show( false );

	return;
}

void CNVillageDetailInfo::GeneralMeetingSuggestInfo(void)
{
	siCurrentType = 0;
	bMasterView   =  true;
	
	// �︮�� �̹Ƿ� ��ư�� ���̰� �Ѵ�
	pSetGeneralmeetingButton->Show( true );
		 
	// ������ ����Ʈ�� �����Ѵ�. 
	m_pNVillageDetailList->Clear();
	
	stListBoxItemData tmpListBoxItemData;

	TCHAR* sidata[MAX_VILLAGE_NUMBER];
	SI32   siVillageInfo[MAX_VILLAGE_NUMBER];

	SI32 i;
	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		sidata[i] = pclClient->pclVillageManager->GetName(i);
	}
	SI32 index = Sort(sidata, siVillageInfo);

	//cltStrInfo* pclStrInfo = NULL;       
	TCHAR buffer[256]  = "";
	StringCchPrintf( buffer, 256, TEXT(" ��  %s  ��"), GetTxtFromMgr( 3649 ) );         

	SI32 villageunique = 0;

	tmpListBoxItemData.Init();
	tmpListBoxItemData.Set( 0,  buffer );    
	
	// ����Ʈ �׸� �����͸� �����Ѵ�. 
	m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
	
	
	for(i = 1;i <= index; ++i)
	{
		//villageunique = siVillageInfo[i];

		if( pclClient->pclVillageManager->pclVillageInfo[i] == NULL )
			continue;
		
		bool Result = pclClient->pclVillageManager->pclVillageInfo[i]->clVillageVary.m_bGeneralMeetingSuggest;
			
		ZeroMemory( buffer, sizeof( buffer ) );
		StringCchPrintf( buffer, 256, TEXT("  %2d.   %s < %s  %s >"), i, pclClient->pclVillageManager->GetName( i ),
																	     Result ? GetTxtFromMgr( 1617 ) : GetTxtFromMgr( 1618 ),
																		 Result ? "O" : "X"	); 
                 
                                             
		tmpListBoxItemData.Init();
		tmpListBoxItemData.Set( 0, buffer );
		tmpListBoxItemData.siParam[ 0 ] = i;//villageunique;       

		// ����Ʈ �׸� �����͸� �����Ѵ�. 
		SI32 index = m_pNVillageDetailList->AddItem( &tmpListBoxItemData );
		m_siListdata[index] = i;//villageunique;
	}

	m_pNVillageDetailList->Refresh();
}
void CNVillageDetailInfo :: FindVillage(TCHAR * szVillagename)
{	
	if(szVillagename == NULL)			
		return;
	TCHAR* pVillageName = NULL;
	//�������̸����� �ε����� ã�Ƽ�
	for (SI16 i = 0; i < MAX_VILLAGE_NUMBER ; i ++ ) 
	{
		pVillageName = m_pNVillageDetailList->GetText( i, 0 );
		if(NULL == pVillageName)
			continue;

		TCHAR* findname = _tcsstr( pVillageName, szVillagename );
		if (findname) {
			m_pNVillageDetailList->SetSelectIndex( i );
			break;
		}		
	}	
}
void CNVillageDetailInfo :: Find(TCHAR* pItemname)
{
	if ( strlen(pItemname) == 0) return;// ���ڿ��� ���� ����
	Show();
	FindVillage(pItemname);
	m_pEdit_Name->Clear();
}
void CNVillageDetailInfo ::Update(){

	cltClient *pclclient = (cltClient *)pclClient;
	NTCHARString64		kInputText(m_pEdit_Name->GetText());

	if( m_pEdit_Name->IsFocus() == false && 
		!(m_pListBox_AutoMake->IsFocus() == true || m_pListBox_AutoMake->GetScroll()->IsFocus() == true) )
	{
		m_pListBox_AutoMake->Clear();
		m_pListBox_AutoMake->Refresh();
		m_pListBox_AutoMake->Show(false);
		//pclClient->pclLog->LogPrint("Lose Focus\n");
		return;
	}
	if (kInputText.IsEmpty())
	{
		m_pListBox_AutoMake->Clear();
		m_pListBox_AutoMake->Refresh();
		m_pListBox_AutoMake->Show(false);
		m_LastInput = kInputText;
		return;
	}
	// ���� ������ ó������ �ʴ´�.
	if (m_LastInput == kInputText)		return;
	m_pListBox_AutoMake->Clear();
//-------------------------------------------------------------
	for (SI32 i = 1 ;i < MAX_VILLAGE_NUMBER; i++ ) {
        cltVillageInfo* pInfo = pclclient->pclVillageManager->pclVillageInfo[i];
		if(pInfo == NULL) continue;
		TCHAR* findname = _tcsstr(pInfo->szName, kInputText);				
		if(findname)	AddListItem(pInfo->szName);
	}	
//-------------------------------------------------------------
	m_pListBox_AutoMake->Refresh();
	m_pListBox_AutoMake->Show(true);

	if( m_pListBox_AutoMake->GetListNum() <= 1 )
	{
		NTCHARString64 kText(m_pListBox_AutoMake->GetText(0, 1));
		if( kText == kInputText)
		{
			m_pListBox_AutoMake->Clear();
			m_pListBox_AutoMake->Show(false);
		}
	}

	m_LastInput = kInputText;
}
void CNVillageDetailInfo :: AddListItem(TCHAR* findname){
	if(findname == NULL)	return;
	SI16 cnt = 0;
	stListBoxItemData Data;

	Data.Init();
	Data.Set( 1, findname );
	m_pListBox_AutoMake->AddItem(&Data);
}

//#endif 