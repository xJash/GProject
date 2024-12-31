
#include "NWarnDurabilityDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client.h"

#include "../../common/Char/CharManager/CharManager.h"

extern cltCommonLogic* pclClient;

CNWarnDurabilityDlg::CNWarnDurabilityDlg( void )
{

}

CNWarnDurabilityDlg::~CNWarnDurabilityDlg( void )
{

}

void CNWarnDurabilityDlg::Init( )
{
		
}

void CNWarnDurabilityDlg::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{ 
		DeleteDialog();
		return;
	}

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NWarnDurabilityDlg/DLG_WarnDurability.ddf" ) );
	file.CreatePopupDialog( this, NWARNDURABILITY_DLG, TEXT( "dialog_warndurability" ), StaticCallBackDialogNWarnDurabilityDlg );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_WEAPON,	this),	WARNDURABILITY_DLG_IMAGESTATIC_WEAPON,	TEXT("imagestatic_weapon") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_SHOES,	this),	WARNDURABILITY_DLG_IMAGESTATIC_SHOES,	TEXT("imagestatic_shoes") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_BELT,	this),	WARNDURABILITY_DLG_IMAGESTATIC_BELT,	TEXT("imagestatic_belt") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_RING,	this),	WARNDURABILITY_DLG_IMAGESTATIC_RING,	TEXT("imagestatic_ring") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_NECK,	this),	WARNDURABILITY_DLG_IMAGESTATIC_NECK,	TEXT("imagestatic_neck") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_HELMET,	this),	WARNDURABILITY_DLG_IMAGESTATIC_HELMET,	TEXT("imagestatic_helmet") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_ARMOUR,	this),	WARNDURABILITY_DLG_IMAGESTATIC_ARMOUR,	TEXT("imagestatic_armour") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_CHAR,	this),	WARNDURABILITY_DLG_IMAGESTATIC_CHAR,	TEXT("imagestatic_char") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	WARNDURABILITY_DLG_IMAGESTATIC_MANTLE,	this),	WARNDURABILITY_DLG_IMAGESTATIC_MANTLE,	TEXT("imagestatic_mantle") );

	// ������ �Է��� ���ֱ� ���� ũ�⸦ 0���� ����
	SI16 siCalcX = 0;
	SI16 siCalcY = 0;

	if ( g_bFullScreen )
	{
		siCalcX = ((cltClient*)pclClient)->siClientScreenXsize - 80 - GetWidth() - 20;
		siCalcY = ((cltClient*)pclClient)->siClientScreenYsize - 80 - GetHeight() - 50;
	}
	else
	{
		siCalcX = ((cltClient*)pclClient)->siClientScreenXsize - 80 - GetWidth();
		siCalcY = ((cltClient*)pclClient)->siClientScreenYsize - 80 - GetHeight() - 20;
	}
		
	SetDialogPos( siCalcX, siCalcY, 0, 0 );

	// ��� ��Ʈ�ѷ��� �ϴ� ���д�
	SetAllControllersShowMode( false );

	// �׼� Ÿ�̸� On
	SetActionTimer( 200 );
	SetTimerOnOff( true );

}

void CALLBACK CNWarnDurabilityDlg::StaticCallBackDialogNWarnDurabilityDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNWarnDurabilityDlg* pThis = (CNWarnDurabilityDlg*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNWarnDurabilityDlg( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNWarnDurabilityDlg::CallBackDialogNWarnDurabilityDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	return;
}

void CNWarnDurabilityDlg::Action()
{
	WarnDurabilityForAction();
}

void CNWarnDurabilityDlg::SetAllControllersShowMode( bool bShowMode )
{
	SI32 siControllersID[] = {
		WARNDURABILITY_DLG_IMAGESTATIC_MANTLE,
		WARNDURABILITY_DLG_IMAGESTATIC_CHAR,
		WARNDURABILITY_DLG_IMAGESTATIC_ARMOUR,
		WARNDURABILITY_DLG_IMAGESTATIC_HELMET,
		WARNDURABILITY_DLG_IMAGESTATIC_NECK,
		WARNDURABILITY_DLG_IMAGESTATIC_RING,
		WARNDURABILITY_DLG_IMAGESTATIC_BELT,
		WARNDURABILITY_DLG_IMAGESTATIC_SHOES,
		WARNDURABILITY_DLG_IMAGESTATIC_WEAPON,
	};
	SI32 siControllerCount = sizeof(siControllersID)/sizeof(siControllersID[0]);

	CImageStatic* pclImageStatic = NULL;

	for ( SI32 siCount=0; siCount<siControllerCount; siCount++ )
	{
		pclImageStatic = m_InterfaceFactory.GetImageStatic( siControllersID[siCount] );
		if ( NULL == pclImageStatic )
		{
			continue;
		}

		pclImageStatic->Show( bShowMode );
	}
}

void CNWarnDurabilityDlg::WarnDurabilityForAction( void )
{
	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	SI32 siCompareValue[PERSONITEM_INV0];
	ZeroMemory( siCompareValue, sizeof(siCompareValue) );

	stWarnController sWarnController[] = {
		{PERSONITEM_HELMET,		WARNDURABILITY_DLG_IMAGESTATIC_HELMET,	&siCompareValue[PERSONITEM_HELMET]}
		,{PERSONITEM_ARMOUR,	WARNDURABILITY_DLG_IMAGESTATIC_ARMOUR,	&siCompareValue[PERSONITEM_ARMOUR]}
		,{PERSONITEM_WEAPON1,	WARNDURABILITY_DLG_IMAGESTATIC_WEAPON,	&siCompareValue[PERSONITEM_WEAPON1]}
		,{PERSONITEM_NECK,		WARNDURABILITY_DLG_IMAGESTATIC_NECK,	&siCompareValue[PERSONITEM_NECK]}
		,{PERSONITEM_RING1,		WARNDURABILITY_DLG_IMAGESTATIC_RING,	&siCompareValue[PERSONITEM_RING1]}
		,{PERSONITEM_RING2,		WARNDURABILITY_DLG_IMAGESTATIC_RING,	&siCompareValue[PERSONITEM_RING1]}
		,{PERSONITEM_BELT,		WARNDURABILITY_DLG_IMAGESTATIC_BELT,	&siCompareValue[PERSONITEM_BELT]}
		,{PERSONITEM_SHOES,		WARNDURABILITY_DLG_IMAGESTATIC_SHOES,	&siCompareValue[PERSONITEM_SHOES]}
		,{PERSONITEM_WEAPON2,	WARNDURABILITY_DLG_IMAGESTATIC_WEAPON,	&siCompareValue[PERSONITEM_WEAPON1]}
		,{PERSONITEM_MANTLE,	WARNDURABILITY_DLG_IMAGESTATIC_MANTLE,	&siCompareValue[PERSONITEM_MANTLE]}
		,{PERSONITEM_HAT,		WARNDURABILITY_DLG_IMAGESTATIC_HELMET,	&siCompareValue[PERSONITEM_HELMET]}
		,{PERSONITEM_DRESS,		WARNDURABILITY_DLG_IMAGESTATIC_ARMOUR,	&siCompareValue[PERSONITEM_ARMOUR]}
	};

	SI32 siWarnControllerCount	= sizeof(sWarnController) / sizeof(sWarnController[0]);

	SI32 siForeverDurValue		= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	SI32 siForeverDurValue2		= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	SI32		siIndex			= 0;

	cltItem*	pclGetItem		= NULL;
	SI32		siGetDurability	= 0;
	SI32		siInventoryPos	= 0;
	SI32		siControllerID	= 0;

	SI32		siShowColor		= WARNDURABILITY_SHOW_COLOR_NONE;

	for( siIndex=0; siIndex<siWarnControllerCount; siIndex++ )
	{
		siInventoryPos = sWarnController[siIndex].m_siInventoryPos;

		// ����� ���� ����ϴ� ���⸸ �������� ǥ�����ش�
		if ( (PERSONITEM_WEAPON1 == siInventoryPos) || (PERSONITEM_WEAPON2 == siInventoryPos) )
		{
			if ( pclChar->ActiveWeapon != siInventoryPos )
			{
				continue;
			}
		}

		// �������â�� ��� ��������
		pclGetItem = &pclChar->pclCI->clCharItem.clItem[siInventoryPos];
		if ( NULL == pclGetItem )
		{
			continue;
		}

		if ( 0 >= pclGetItem->siUnique )
		{
			continue;
		}

		siGetDurability = pclGetItem->GetDurability();
		// ���ѳ������� ����ϰ�� ǥ������ �ʴ´�
		if ( (siForeverDurValue == siGetDurability) || (siForeverDurValue2 == siGetDurability) )
		{
			continue;
		}

		// �� ������ ������ �����Ѵ�
		if ( 201 <= siGetDurability )
		{
			siShowColor = WARNDURABILITY_SHOW_COLOR_NONE;
		}
		else if ( (200 >= siGetDurability) && (101 <= siGetDurability) )
		{
			siShowColor = WARNDURABILITY_SHOW_COLOR_01;
		}
		else if ( (100 >= siGetDurability) && (51 <= siGetDurability) )
		{
			siShowColor = WARNDURABILITY_SHOW_COLOR_02;
		}
		else
		{
			siShowColor = WARNDURABILITY_SHOW_COLOR_03;
		}
		
		// ���� �����Ǿ� �ִ� Į�󰪺��� Ŭ���� �־��ش�
		if ( *(sWarnController[siIndex].m_psiCompareValue) < siShowColor )
		{
			*(sWarnController[siIndex].m_psiCompareValue) = siShowColor;
		}
	}

	CImageStatic*	pclImageStatic	= NULL;
	bool			bShowMode		= false;
	SI32			siColorValue	= 0;

	// ������ ��� ǥ���ؾߵ� ��� �ϳ��� �ִٸ� ĳ���͵� ���� ǥ���Ѵ�
	bool			bShowChar		= false;

	// ���� ��Ȳ�鶧���� For���� �ѹ� �� ���� �Ѵ� ��� ����Ǿ������� �������� ����Ǿ����� ǥ�ð� �߸��Ǵ� ���� �����ϱ� ���ؼ� �̴�
	for( siIndex=0; siIndex<siWarnControllerCount; siIndex++ )
	{
		pclImageStatic = m_InterfaceFactory.GetImageStatic( sWarnController[siIndex].m_siControllerID );
		if ( NULL == pclImageStatic )
		{
			continue;
		}

		siColorValue	= *(sWarnController[siIndex].m_psiCompareValue);
		bShowMode		= pclImageStatic->IsShow();

		if ( WARNDURABILITY_SHOW_COLOR_NONE == siColorValue )
		{
			if ( bShowMode )
			{
				pclImageStatic->Show( false );
			}
		}
		else
		{
			if ( false == bShowMode )
			{
				pclImageStatic->Show( true );
			}

			pclImageStatic->SetFontIndex( (siColorValue-1) );

			bShowChar = true;
		}
	}
	
	pclImageStatic = m_InterfaceFactory.GetImageStatic( WARNDURABILITY_DLG_IMAGESTATIC_CHAR );
	if ( pclImageStatic )
	{
		pclImageStatic->Show( bShowChar );
	}

}