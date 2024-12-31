#include "NMainMapDlg.h"

#include "../../Client.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../commonlogic/Msg/MsgType-Quest.h"

extern cltCommonLogic* pclClient;

CMainMapDlg::CMainMapDlg()
{
	//�̹��� ���� �ε�
	GP.LoadSprFromFile( TEXT("gImg/MAINMAP_sign.SPR"), &m_sprImageList); // �ε���0~4   Ninterface/Image/

	ZeroMemory( m_arTown,			sizeof(m_arTown) ); 
	ZeroMemory( m_arHuntingZone,	sizeof(m_arHuntingZone) );
	ZeroMemory( m_arNPC,			sizeof(m_arNPC) );
	ZeroMemory( m_arETC,			sizeof(m_arETC) );

	m_siCurrentTownPos = 0;
	m_siCurrentHuntingZonePos = 0;
	m_siCurrentNPCPos = 0;
	m_siCurrentETCPos = 0;

	m_pMapImage = NULL;

	m_pTownBalloon = NULL;
	m_pHuntBalloon = NULL;
	m_pNPCBalloon = NULL;
	m_pEtcBalloon = NULL;
	m_pMouseBalloon = NULL;

	// �̴ϸ� ������ ���
	m_siRealMapXSize = DEFAULT_MAP_X_SIZE * MAP_TILE_XSIZE_HALF + DEFAULT_MAP_Y_SIZE * MAP_TILE_XSIZE_HALF;
	m_siRealMapYSize = DEFAULT_MAP_X_SIZE * MAP_TILE_YSIZE_HALF + DEFAULT_MAP_Y_SIZE * MAP_TILE_YSIZE_HALF;

	ZeroMemory(m_siCheckIndex, sizeof(m_siCheckIndex));
}

CMainMapDlg::~CMainMapDlg()
{
	if( m_sprImageList.pImage )
	{
		GP.FreeSpr(m_sprImageList);
	}
}


void CMainMapDlg::init()
{

}

void CMainMapDlg::Create()
{
	if (IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	CInterfaceFile file;
	file.LoadFile( TEXT ( "Ninterface/Data/DLG_NMainMap.ddf" ) );
	file.CreatePopupDialog( this, NMAINMAP_DLG, TEXT("dialog_NMainMap"), StaticCallBackDialogCMainMap );

	//------------------------------------------------
	// üũ�ڽ�
	//------------------------------------------------
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( CHECKBOX, NMAINMAP_DLG_VILLAGE,			this ), NMAINMAP_DLG_VILLAGE,			TEXT("checkbox_village") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( CHECKBOX, NMAINMAP_DLG_HUNTINGZONE,		this ), NMAINMAP_DLG_HUNTINGZONE,		TEXT("checkbox_huntingzone") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( CHECKBOX, NMAINMAP_DLG_NPC, 			this ), NMAINMAP_DLG_NPC, 				TEXT("checkbox_npc") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( CHECKBOX, NMAINMAP_DLG_ETC, 			this ), NMAINMAP_DLG_ETC, 				TEXT("checkbox_etc") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( COMBOBOX, NMAINMAP_DLG_VILLAGENAMELIST, this ), NMAINMAP_DLG_VILLAGENAMELIST, 	TEXT("combobox_villagename") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( COMBOBOX, NMAINMAP_DLG_HUNTINGZONELIST, this ), NMAINMAP_DLG_HUNTINGZONELIST, 	TEXT("combobox_huntingzone") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( COMBOBOX, NMAINMAP_DLG_NPCLIST, 		this ), NMAINMAP_DLG_NPCLIST, 			TEXT("combobox_npc") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( COMBOBOX, NMAINMAP_DLG_ETCLIST, 		this ), NMAINMAP_DLG_ETCLIST, 			TEXT("combobox_etc") );

	// �ƿ�����
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(OUTLINE, NMAINMAP_DLG_OUTLINE_NONAME1,	this), NMAINMAP_DLG_OUTLINE_NONAME1,	TEXT("outline_NONAME1") );

	//--------------------------------------------------
	// ��ǳ��
	//--------------------------------------------------
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NMAINMAP_DLG_MOUSEBALLOON,		this ), NMAINMAP_DLG_MOUSEBALLOON,		TEXT("statictext_mouseballoon") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NMAINMAP_DLG_TOWNBALLOON,		this ), NMAINMAP_DLG_TOWNBALLOON,		TEXT("statictext_townballoon") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NMAINMAP_DLG_HUNTBALLOON,		this ), NMAINMAP_DLG_HUNTBALLOON,		TEXT("statictext_huntballoon") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NMAINMAP_DLG_NPCBALLOON,		this ), NMAINMAP_DLG_NPCBALLOON,		TEXT("statictext_npcballoon") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NMAINMAP_DLG_ETCBALLOON,		this ), NMAINMAP_DLG_ETCBALLOON,		TEXT("statictext_etcballoon") );
	
	//--------------------------------------------------
	// ���θ� �̹���
	//--------------------------------------------------
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( IMAGESTATIC , NMAINMAP_DLG_DRAWMAP,		this ), NMAINMAP_DLG_DRAWMAP,			TEXT("imagestatic_mapimage") );	// ��ü�� �̹���

	m_pMapImage = m_InterfaceFactory.GetImageStatic( NMAINMAP_DLG_DRAWMAP );

	// �̴ϸ� �̹����� ũ�⸦ ����
	m_siCurrentMapWidth = m_pMapImage->GetWidth();
	m_siCurrentMapHeight = m_pMapImage->GetHeight();

	m_pTownBalloon	=	m_InterfaceFactory.GetStatic( NMAINMAP_DLG_TOWNBALLOON );
	m_pHuntBalloon	=	m_InterfaceFactory.GetStatic( NMAINMAP_DLG_HUNTBALLOON );
	m_pNPCBalloon	=	m_InterfaceFactory.GetStatic( NMAINMAP_DLG_NPCBALLOON );
	m_pEtcBalloon	=	m_InterfaceFactory.GetStatic( NMAINMAP_DLG_ETCBALLOON );
	m_pMouseBalloon =	m_InterfaceFactory.GetStatic( NMAINMAP_DLG_MOUSEBALLOON );

	if ( NULL != m_pTownBalloon  )	m_pTownBalloon->Show( false );
	if ( NULL != m_pHuntBalloon  )	m_pHuntBalloon->Show( false );
	if ( NULL != m_pNPCBalloon   )	m_pNPCBalloon->Show( false );
	if ( NULL != m_pEtcBalloon   )	m_pEtcBalloon->Show( false );
	if ( NULL != m_pMouseBalloon )	m_pMouseBalloon->Show( false );
 
	// ����
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_VILLAGE)->SetFontColor( RGB(0xff,0xff,0xff) ); // üũ �ڽ��� �ؽ�Ʈ �������..
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_VILLAGE)->SetTextPrintOption( DT_SINGLELINE|DT_VCENTER|DT_CENTER );
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_VILLAGE)->Refresh();//SetText("test");

	// �����
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_HUNTINGZONE)->SetFontColor( RGB(0xff,0xff,0xff) );
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_HUNTINGZONE)->SetTextPrintOption( DT_SINGLELINE|DT_VCENTER|DT_CENTER );
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_HUNTINGZONE)->Refresh();

	// NPC
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_NPC)->SetFontColor( RGB(0xff,0xff,0xff) );
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_NPC)->SetTextPrintOption( DT_SINGLELINE|DT_VCENTER|DT_CENTER );
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_NPC)->Refresh();

	// ��Ÿ
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_ETC)->SetFontColor( RGB(0xff,0xff,0xff) );
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_ETC)->SetTextPrintOption( DT_SINGLELINE|DT_VCENTER|DT_CENTER );
	m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_ETC)->Refresh();
	
	LoadMapInfo_FromFile();
}

void CMainMapDlg::LoadMapInfo_FromFile()
{
	//////////////////////////////////////////////////////////////////////////
	// ���� �ε�
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/MainMapInfo/MainMapInfo.txt") );
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/MainMapInfo/MainMapInfo.txt"));
		}

		else
		{
			bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/MainMapInfo/MainMapInfo.txt") );
		}	
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile MainMapInfo.txt"),TEXT("Error"));
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// �о���� ���� �������� �迭 �ʱ�ȭ
	SI32 siMapObjectType = 0;		// �� ������Ʈ Ÿ�� (����, �����, npc, ��Ÿ)
	SI32 siPosX = 0;				// ������Ʈ�� ��ǥ X
	SI32 siPosY = 0;				// ������Ʈ�� ��ǥ Y
	SI32 siTextUnique = 0;			// ������Ʈ�� ������ ���ڿ��� ����ũ
	TCHAR	szDescription[128] = TEXT("");	// ����

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siMapObjectType,	4,
		NDATA_INT32,	&siPosX,			4,
		NDATA_INT32,	&siPosY,			4,
		NDATA_INT32,	&siTextUnique,		4,
		NDATA_MBSTRING,	&szDescription,		128,
		0,				0,					0

	};	
	dataloader.RegDataType( pDataTypeInfo );


	//////////////////////////////////////////////////////////////////////////
	m_siCurrentTownPos = 0;
	m_siCurrentHuntingZonePos = 0;
	m_siCurrentNPCPos = 0;
	m_siCurrentETCPos = 0;

	while( !dataloader.IsEndOfData() )
	{
		if ( dataloader.ReadData(true) )
		{
			POINT oriPos;
			oriPos.x = siPosX / 8;
			oriPos.y = siPosY / 8;

			POINT minimapPos = ConvertMinimapPos( oriPos );

			switch( siMapObjectType )
			{
			case MAINMAP_OBEJCTTYPE_TOWN:
				{
					if ( MAINMAP_OBJECT_TOWN_MAX > m_siCurrentTownPos )
					{
						m_arTown[m_siCurrentTownPos].siMapObjectType = siMapObjectType;
						m_arTown[m_siCurrentTownPos].siPosX = minimapPos.x;
						m_arTown[m_siCurrentTownPos].siPosY = minimapPos.y;
						m_arTown[m_siCurrentTownPos].siTextUnique = siTextUnique;

						TCHAR* pText = GetTxtFromMgr( siTextUnique );

						if ( NULL != pText )
						{
							stComboBoxItemData ComboBoxItemData;
							ComboBoxItemData.Init();
							ComboBoxItemData.Set( pText );

							m_InterfaceFactory.GetComboBox( NMAINMAP_DLG_VILLAGENAMELIST )->AddItem( &ComboBoxItemData );
						}

						++m_siCurrentTownPos;
					}
				}
				break;
			case MAINMAP_OBEJCTTYPE_HUNTINGZONE:
				{
					if ( MAINMAP_OBJECT_HUNTINGZONE_MAX > m_siCurrentHuntingZonePos )
					{
						m_arHuntingZone[m_siCurrentHuntingZonePos].siMapObjectType = siMapObjectType;
						m_arHuntingZone[m_siCurrentHuntingZonePos].siPosX = minimapPos.x;
						m_arHuntingZone[m_siCurrentHuntingZonePos].siPosY = minimapPos.y;
						m_arHuntingZone[m_siCurrentHuntingZonePos].siTextUnique = siTextUnique;

						TCHAR* pText = GetTxtFromMgr( siTextUnique );

						if ( NULL != pText )
						{
							stComboBoxItemData ComboBoxItemData;
							ComboBoxItemData.Init();
							ComboBoxItemData.Set( pText );

							m_InterfaceFactory.GetComboBox( NMAINMAP_DLG_HUNTINGZONELIST )->AddItem( &ComboBoxItemData );
						}

						++m_siCurrentHuntingZonePos;
					}
				}
				break;
			case MAINMAP_OBEJCTTYPE_NPC:
				{
					if ( MAINMAP_OBJECT_NPC_MAX > m_siCurrentNPCPos )
					{
						m_arNPC[m_siCurrentNPCPos].siMapObjectType = siMapObjectType;
						m_arNPC[m_siCurrentNPCPos].siPosX = minimapPos.x;
						m_arNPC[m_siCurrentNPCPos].siPosY = minimapPos.y;
						m_arNPC[m_siCurrentNPCPos].siTextUnique = siTextUnique;

						TCHAR* pText = GetTxtFromMgr( siTextUnique );

						if ( NULL != pText )
						{
							stComboBoxItemData ComboBoxItemData;
							ComboBoxItemData.Init();
							ComboBoxItemData.Set( pText );

							m_InterfaceFactory.GetComboBox( NMAINMAP_DLG_NPCLIST )->AddItem( &ComboBoxItemData );
						}

						++m_siCurrentNPCPos;
					}
				}
				break;
			case MAINMAP_OBEJCTTYPE_ETC:
				{
					if ( MAINMAP_OBJECT_ETC_MAX > m_siCurrentETCPos )
					{
						m_arETC[m_siCurrentETCPos].siMapObjectType = siMapObjectType;
						m_arETC[m_siCurrentETCPos].siPosX = minimapPos.x;
						m_arETC[m_siCurrentETCPos].siPosY = minimapPos.y;
						m_arETC[m_siCurrentETCPos].siTextUnique = siTextUnique;

						TCHAR* pText = GetTxtFromMgr( siTextUnique );

						if ( NULL != pText )
						{
							stComboBoxItemData ComboBoxItemData;
							ComboBoxItemData.Init();
							ComboBoxItemData.Set( pText );

							m_InterfaceFactory.GetComboBox( NMAINMAP_DLG_ETCLIST )->AddItem( &ComboBoxItemData );
						}

						++m_siCurrentETCPos;
					}
				}
				break;
			}
		}
	}
}

void CALLBACK CMainMapDlg::StaticCallBackDialogCMainMap(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CMainMapDlg *pThis = (CMainMapDlg * )pControllerMgr;
	if( pThis )
	{
		pThis->CallBackDialogCMainMap( nEvent, nControlID, pControl);
	}
}

void CALLBACK CMainMapDlg::CallBackDialogCMainMap( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			//Show( false );
			DeleteDialog();
		}
		break;
	case NMAINMAP_DLG_VILLAGE:
		{
			Process_ComboBox_Village();	// �޺��ڽ����� ���� �����Ŀ� üũ �ڽ��� Ŭ���ϸ� ��ǳ���� �ٷ� ������ �ʴ� ������ �߰� ����.
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_HUNTINGZONE:
		{
			Process_ComboBox_HuntingZone();
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_NPC:
		{
			Process_ComboBox_NPC();
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_ETC:
		{
			Process_ComboBox_ETC();
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_VILLAGENAMELIST:
		{
			Process_ComboBox_Village();
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_HUNTINGZONELIST:
		{
			Process_ComboBox_HuntingZone();
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_NPCLIST:
		{
			Process_ComboBox_NPC();
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_ETCLIST:
		{
			Process_ComboBox_ETC();
			UpdateState();
		}
		break;
	case NMAINMAP_DLG_DRAWMAP:
		{
			switch ( nEvent )
			{
			case EVENT_IMAGESTATIC_MOUSEMOVE:
				{
					Process_Dlg_MouseMove();
				}
				break;
			}
		}
		break;
	}
}

void CMainMapDlg::DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY )
{
	if ( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_VILLAGE)->IsCheck() ) // üũ�� �������� 
	{
	
		for ( int i = 0; i < m_siCurrentTownPos; ++i )
		{
			TCHAR* pText = GetTxtFromMgr( m_arTown[i].siTextUnique );
			if ( NULL != pText && NULL != m_sprImageList.pImage )
			{
				SI32 siPosX = m_arTown[i].siPosX + GetX() + ScreenRX;
				SI32 siPosY = m_arTown[i].siPosY + GetY() + ScreenRY;
				SI32 siFontIndex	= 0;

				SI16 siImageWidth = m_sprImageList.GetXSize() / m_sprImageList.GetImageNum() / 2;
				SI16 siImageHeight = m_sprImageList.GetYSize() / 2;
				GP.PutSpr(&m_sprImageList, siPosX - siImageWidth, siPosY - siImageHeight, siFontIndex);
			}
		}

		//Process_ComboBox_Village();
	}
	else
	{
		if ( NULL != m_pTownBalloon && true == m_pTownBalloon->IsShow() )
		{
			m_pTownBalloon->Show( false );
		}
	}

	if( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_HUNTINGZONE)->IsCheck() )
	{
		for ( int i = 0; i < m_siCurrentHuntingZonePos; ++i )
		{
			TCHAR* pText = GetTxtFromMgr( m_arHuntingZone[i].siTextUnique );
			if ( NULL != pText && NULL != m_sprImageList.pImage )
			{
				SI32 siPosX = m_arHuntingZone[i].siPosX + GetX() + ScreenRX;
				SI32 siPosY = m_arHuntingZone[i].siPosY + GetY() + ScreenRY;

				SI32 siFontIndex	= 1;

				// �������� ��ġ�� �̹����� �߽��� ������ �ϱ� ���� �̹��� ũ���� ���ݾ� ��ǥ�� �Ű���
				SI16 siImageWidth = m_sprImageList.GetXSize() / m_sprImageList.GetImageNum() / 2;
				SI16 siImageHeight = m_sprImageList.GetYSize() / 2;
				GP.PutSpr(&m_sprImageList, siPosX - siImageWidth, siPosY - siImageHeight, siFontIndex);
			}
		}

		//Process_ComboBox_HuntingZone();
	}
	else
	{
		if ( NULL != m_pHuntBalloon && true == m_pHuntBalloon->IsShow() )
		{
			m_pHuntBalloon->Show( false );
		}
	}

	if( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_NPC)->IsCheck() )
	{
		for ( int i = 0; i < m_siCurrentNPCPos; ++i )
		{
			TCHAR* pText = GetTxtFromMgr( m_arNPC[i].siTextUnique );
			if ( NULL != pText && NULL != m_sprImageList.pImage )
			{
				SI32 siPosX = m_arNPC[i].siPosX + GetX() + ScreenRX;
				SI32 siPosY = m_arNPC[i].siPosY + GetY() + ScreenRY;

				SI32 siFontIndex	= 2;

				SI16 siImageWidth = m_sprImageList.GetXSize() / m_sprImageList.GetImageNum() / 2;
				SI16 siImageHeight = m_sprImageList.GetYSize() / 2;
				GP.PutSpr(&m_sprImageList, siPosX - siImageWidth, siPosY - siImageHeight, siFontIndex);
			}
		}

		//Process_ComboBox_NPC();
	}
	else
	{
		if ( NULL != m_pNPCBalloon && true == m_pNPCBalloon->IsShow() )
		{
			m_pNPCBalloon->Show( false );
		}
	}

	if( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_ETC)->IsCheck() )
	{
		for ( int i = 0; i < m_siCurrentETCPos; ++i )
		{
			TCHAR* pText = GetTxtFromMgr( m_arETC[i].siTextUnique );
			if ( NULL != pText && NULL != m_sprImageList.pImage )
			{
				SI32 siPosX = m_arETC[i].siPosX + GetX() + ScreenRX;
				SI32 siPosY = m_arETC[i].siPosY + GetY() + ScreenRY;

				SI32 siFontIndex	= 3;

				SI16 siImageWidth = m_sprImageList.GetXSize() / m_sprImageList.GetImageNum() / 2;
				SI16 siImageHeight = m_sprImageList.GetYSize() / 2;
				GP.PutSpr(&m_sprImageList, siPosX - siImageWidth, siPosY - siImageHeight, siFontIndex);
			}
		}

		//Process_ComboBox_ETC();
	}
	else
	{
		if ( NULL != m_pEtcBalloon && true == m_pEtcBalloon->IsShow() )
		{
			m_pEtcBalloon->Show( false );
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	/*if ( NULL != m_pTownBalloon && true == m_pTownBalloon->IsShow() )
	{
		m_pTownBalloon->Refresh();
	}

	if ( NULL != m_pHuntBalloon && true == m_pHuntBalloon->IsShow() )
	{
		m_pHuntBalloon->Refresh();
	}

	if ( NULL != m_pNPCBalloon && true == m_pNPCBalloon->IsShow() )
	{
		m_pNPCBalloon->Refresh();
	}

	if ( NULL != m_pEtcBalloon && true == m_pEtcBalloon->IsShow() )
	{
		m_pEtcBalloon->Refresh();
	}*/

	/*if ( NULL != m_pMouseBalloon )
	{
		if ( true == m_pMouseBalloon->IsShow() )
		{
			m_pMouseBalloon->Refresh();
		}
	}*/
	////////////////////////////////////////////////////////////////////////////////////////////
}


//------------------------------------------------------------------------------------
// �޺��ڽ�
//------------------------------------------------------------------------------------
void CMainMapDlg::Process_ComboBox_Village()
{
	int siIndex = m_InterfaceFactory.GetComboBox(NMAINMAP_DLG_VILLAGENAMELIST)->GetSelectedIndex();
	if( 0 > siIndex || m_siCurrentTownPos < siIndex ) return;

	// ��ǳ�� �׸�
	POINT point;
	point.x = m_arTown[siIndex].siPosX;
	point.y = m_arTown[siIndex].siPosY;

	if ( NULL != m_pTownBalloon && true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_VILLAGE)->IsCheck() )
	{
		TCHAR* pText = GetTxtFromMgr( m_arTown[siIndex].siTextUnique );
		if ( NULL != pText )
		{
			DrawBalloon( m_pTownBalloon, pText, point ); // ���� ��ǳ��
		}
	}
}

void CMainMapDlg::Process_ComboBox_HuntingZone()
{
	int siIndex = m_InterfaceFactory.GetComboBox(NMAINMAP_DLG_HUNTINGZONELIST)->GetSelectedIndex();
	if( 0 > siIndex || m_siCurrentHuntingZonePos < siIndex ) return;

	// ��ǳ�� �׸�
	POINT point;
	point.x = m_arHuntingZone[siIndex].siPosX;
	point.y = m_arHuntingZone[siIndex].siPosY;

	if ( NULL != m_pHuntBalloon && true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_HUNTINGZONE)->IsCheck() )
	{
		TCHAR* pText = GetTxtFromMgr( m_arHuntingZone[siIndex].siTextUnique );
		if ( NULL != pText )
		{
			DrawBalloon( m_pHuntBalloon, pText, point ); // ����� ��ǳ��
		}
	}
}

void CMainMapDlg::Process_ComboBox_NPC()
{
	int siIndex = m_InterfaceFactory.GetComboBox(NMAINMAP_DLG_NPCLIST)->GetSelectedIndex();
	if( 0 > siIndex || m_siCurrentNPCPos < siIndex ) return;

	// ��ǳ�� �׸�
	POINT point;
	point.x = m_arNPC[siIndex].siPosX;
	point.y = m_arNPC[siIndex].siPosY;

	if ( NULL != m_pNPCBalloon && true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_NPC)->IsCheck() )
	{
		TCHAR* pText = GetTxtFromMgr( m_arNPC[siIndex].siTextUnique );
		if ( NULL != pText )
		{
			DrawBalloon( m_pNPCBalloon, pText, point );	// NPC ��ǳ��
		}
	}
}

void CMainMapDlg::Process_ComboBox_ETC()
{
	int siIndex = m_InterfaceFactory.GetComboBox(NMAINMAP_DLG_ETCLIST)->GetSelectedIndex();
	if( 0 > siIndex || m_siCurrentETCPos < siIndex ) return;

	// ��ǳ�� �׸�
	POINT point;
	point.x = m_arETC[siIndex].siPosX;
	point.y = m_arETC[siIndex].siPosY;

	if ( NULL != m_pEtcBalloon && true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_ETC)->IsCheck() )
	{
		TCHAR* pText = GetTxtFromMgr( m_arETC[siIndex].siTextUnique );
		if ( NULL != pText )
		{
			DrawBalloon( m_pEtcBalloon, pText, point );	// etc ��ǳ��
		}
	}
}

void CMainMapDlg::Process_Dlg_MouseMove()
{
	if ( NULL == m_pMapImage ) return;

	POINT mousePos;
	m_pMapImage->GetImageStaticPos( mousePos );
	mousePos.y += 20;	// ��ȭ������ Ÿ��Ʋ�� �β���ŭ ������

    RECT rect;

	if ( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_VILLAGE)->IsCheck() )
	{
		for ( int i = 0; i < m_siCurrentTownPos; ++i )
		{
			rect.top = m_arTown[i].siPosY - 5;
			rect.left = m_arTown[i].siPosX - 5;
			rect.bottom = m_arTown[i].siPosY + 5;
			rect.right = m_arTown[i].siPosX + 5;

			if ( true == IsInRect( rect, mousePos ) )
			{
				TCHAR* pText = GetTxtFromMgr( m_arTown[i].siTextUnique );
				if ( NULL != pText )
				{
					POINT point;
					point.x = m_arTown[i].siPosX;
					point.y = m_arTown[i].siPosY;

					DrawBalloon( m_pMouseBalloon, pText, point );	// ���콺 ��ǳ��
					return;
				}
			}
		}
	}
	
	if ( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_HUNTINGZONE)->IsCheck() )
	{
		for ( int i = 0; i < m_siCurrentHuntingZonePos; ++i )
		{
			rect.top = m_arHuntingZone[i].siPosY - 5;
			rect.left = m_arHuntingZone[i].siPosX - 5;
			rect.bottom = m_arHuntingZone[i].siPosY + 5;
			rect.right = m_arHuntingZone[i].siPosX + 5;

			if ( true == IsInRect( rect, mousePos ) )
			{
				TCHAR* pText = GetTxtFromMgr( m_arHuntingZone[i].siTextUnique );
				if ( NULL != pText )
				{
					POINT point;
					point.x = m_arHuntingZone[i].siPosX;
					point.y = m_arHuntingZone[i].siPosY;

					DrawBalloon( m_pMouseBalloon, pText, point );
					return;
				}
			}
		}
	}

	if ( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_NPC)->IsCheck() )
	{
		for ( int i = 0; i < m_siCurrentNPCPos; ++i )
		{
			rect.top = m_arNPC[i].siPosY - 5;
			rect.left = m_arNPC[i].siPosX - 5;
			rect.bottom = m_arNPC[i].siPosY + 5;
			rect.right = m_arNPC[i].siPosX + 5;

			if ( true == IsInRect( rect, mousePos ) )
			{
				TCHAR* pText = GetTxtFromMgr( m_arNPC[i].siTextUnique );
				if ( NULL != pText )
				{
					POINT point;
					point.x = m_arNPC[i].siPosX;
					point.y = m_arNPC[i].siPosY;

					DrawBalloon( m_pMouseBalloon, pText, point );
					return;
				}
			}
		}
	}

	if ( true == m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_ETC)->IsCheck() )
	{
		for ( int i = 0; i < m_siCurrentETCPos; ++i )
		{
			rect.top = m_arETC[i].siPosY - 5;
			rect.left = m_arETC[i].siPosX - 5;
			rect.bottom = m_arETC[i].siPosY + 5;
			rect.right = m_arETC[i].siPosX + 5;

			if ( true == IsInRect( rect, mousePos ) )
			{
				TCHAR* pText = GetTxtFromMgr( m_arETC[i].siTextUnique );
				if ( NULL != pText )
				{
					POINT point;
					point.x = m_arETC[i].siPosX;
					point.y = m_arETC[i].siPosY;

					DrawBalloon( m_pMouseBalloon, pText, point );
					return;
				}
			}
		}
	}
	

	// ������� �Դٴ°� ���콺�� Ư�� ����Ʈ�� ��ġ ���� �ʴٴ� ���̹Ƿ� ���콺 ��ǳ���� ���ش�.
	m_pMouseBalloon->Show( false );
}

void CMainMapDlg::DrawBalloon(CStatic* pBalloon, TCHAR* pText, POINT& point)
{
	if ( NULL == pBalloon ) return;
	if ( 0 == point.x && 0 == point.y ) return; // x�� y�� ��ǥ�� 0�ϰ�� ��ǳ���� �׸��� �ʴ´�. �� �÷��� ù ������ 0���� �ּ� ���� ���̴°� �������� �ֱ� ����.

	// ��ǳ���� ���� �ؽ�Ʈ�� ����
	SIZE sizeText;
	if ( NULL != pText )
	{
		pBalloon->SetText( pText, DT_CENTER|DT_VCENTER|DT_SINGLELINE, &sizeText );
		pBalloon->SetSurfaceWidth( sizeText.cx + 10 );
		pBalloon->SetWidth( sizeText.cx + 10 );
		//pBalloon->SetSurfaceHeight( sizeText.cy + 8 );
		//pBalloon->SetHeight( sizeText.cy + 8 );
		pBalloon->Refresh();

		// ��ǳ���� �׸���
		SI32 siPosX = point.x + 2;
		SI32 siPosY = point.y - 37;
		pBalloon->SetX( siPosX );
		pBalloon->SetY( siPosY );
		pBalloon->Show( true );
	}
}

bool CMainMapDlg::IsInRect(RECT& rect, POINT& point)
{
	if ( rect.left <= point.x && rect.right >= point.x
		&& rect.top <= point.y && rect.bottom >= point.y ) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

POINT CMainMapDlg::ConvertMinimapPos(const POINT& rResourcePos)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;

	// ���ҽ����� ���� ��ǥ�� �̴ϸ� �̹��� ���� ���� ��ǥ�� ��ȯ (���� ��ǥ -> �̴ϸ� ��ǥ)
	cltMapClient *pMap = (cltMapClient * )pclClient->pclMapManager->pclCurrentMap;
	if ( pMap )
	{
		pt.x = ( ( DEFAULT_MAP_Y_SIZE * MAP_TILE_XSIZE_HALF + rResourcePos.x * MAP_TILE_XSIZE_HALF - rResourcePos.y * MAP_TILE_XSIZE_HALF ) / (double)m_siRealMapXSize ) * (double)m_siCurrentMapWidth;

		pt.y = ( ( rResourcePos.x * MAP_TILE_YSIZE_HALF + rResourcePos.y * MAP_TILE_YSIZE_HALF ) / (double)m_siRealMapYSize ) * (double)m_siCurrentMapHeight;
	}

	// ���� �̴ϸ� ��ǥ�� ��Ÿ �۾� ó��
	pt.x -= 2;	// �� �̹����� �߾ӿ� ������� 2�ȼ���ŭ -x������ �̵�
	pt.y += 20;	// �̴ϸ� ��ȭ������ Ÿ��Ʋ�� �β���ŭ ���ѵ� �̴ϸ� ��ǥ ���� //22

	return pt;
}


// [��ȣ] üũ�ڽ��� üũ���¸� �����մϴ�.
bool CMainMapDlg::IsChecked(SI32 siIndex)
{
	if(siIndex >= 0 && siIndex < MAX_MAINMAP_OBJECTTYPE_NUM) 
		return m_siCheckIndex[siIndex];
	else
		return false;
}	

void CMainMapDlg::UpdateState()
{
	// üũ�ڽ��� �޺��ڽ��� index�� ���ǵǾ����� �����Ƿ� ���⼭ ������ ���ݴϴ�.

	m_siCheckIndex[0] = m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_VILLAGE)->IsCheck();
	m_siCheckIndex[1] = m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_HUNTINGZONE)->IsCheck();
	m_siCheckIndex[2] = m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_NPC)->IsCheck();
	m_siCheckIndex[3] = m_InterfaceFactory.GetCheckBox(NMAINMAP_DLG_ETC)->IsCheck();

	// ��ü�� �˻� ����Ʈ ���̶��
	SI16 questtype		= 0;
	SI16 questunique	= 0;
	SI16 para1			= 0;
	SI16 para2			= 0;
	SI16 questclearcond = QUEST_CLEAR_COND_SEARCH_TOTALMAP;

	if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
	{
		SI32 siTypeID = 0;

		switch(para1)
		{
		case 0:	siTypeID = NMAINMAP_DLG_VILLAGENAMELIST;	break;
		case 1:	siTypeID = NMAINMAP_DLG_HUNTINGZONELIST;	break;
		case 2:	siTypeID = NMAINMAP_DLG_NPCLIST;			break;
		case 3:	siTypeID = NMAINMAP_DLG_ETCLIST;			break;
		
		default: 
			return;
		}

		
		if(m_siCheckIndex[para1] ==true && m_InterfaceFactory.GetComboBox(siTypeID)->GetSelectedIndex() == para2)
		{
			cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
			cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			cltClient* pclclient = (cltClient* )pclClient;
			pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
		}
	}	
}






