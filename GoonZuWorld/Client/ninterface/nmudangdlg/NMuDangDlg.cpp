/* ==========================================================================
	Ŭ���� :		CNMudangDlg

	�ۼ��� :		05/04/08
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/

#include "./NMuDangDlg.h"

#include <tchar.h>
//#if defined(_DEBUG) && defined( _LEON_NNMUDANGDLG_)

#include "../../Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/Msg/MsgType-Summon.h"
#include "..\..\Client\Client.h"
#include "..\..\Client\Music\Music.h"
#include "Char\KindInfo\KindInfo.h"

#include "../../../../DBManager/GameDBManager_World/DBMsg-Summon.h"

#include "../../../Client/InterfaceMgr/Interface/ImageStatic.h"
#include "../../../Client/InterfaceMgr/Interface/Button.h"
#include "../../../Client/InterfaceMgr/Interface/Edit.h"
#include "../../../Client/InterfaceMgr/Interface/OutLine.h"
#include "../../../Client/InterfaceMgr/Interface/ComboBox.h"
#include "../../../Client/InterfaceMgr/Interface/RadioButton.h"
#include "../../../Client/InterfaceMgr/Interface/Static.h"
#include "../../../Client/InterfaceMgr/Interface/List.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../NSoundOnOffDlg/NSoundOnOffDlg.h"

#include <Graphic_Capsule.h>

extern cltCommonLogic* pclClient;

// CNMudangReviveDlg ==============================================
CNMudangReviveDlg::CNMudangReviveDlg()
{
	m_bShow = false;
	m_pParent = NULL;
	m_pStatic_now_summon	 = NULL; 
	m_pButton_summon_revive	 = NULL; 
	m_pEdit_summon_revive_explain	 = NULL; 
	m_pComboBox_now_summon	 = NULL; 
}

CNMudangReviveDlg::~CNMudangReviveDlg()
{
	if( 	m_pStatic_now_summon	 )  	delete 	m_pStatic_now_summon	;
	if( 	m_pButton_summon_revive	 )  	delete 	m_pButton_summon_revive	;
	if( 	m_pEdit_summon_revive_explain	 )  	delete 	m_pEdit_summon_revive_explain	;
	if( 	m_pComboBox_now_summon	 )  	delete 	m_pComboBox_now_summon	;
}

void CNMudangReviveDlg::Create( CControllerMgr *pParent )
{
	if(!IsCreate())
	{
		m_pParent = (CNMudangDlg*)pParent;

		CInterfaceFile file;

		file.LoadFile(TEXT("NInterface/Data/NMudangDlg/DLG_NMudangRevive.ddf"));
		file.CreateChildDialog( this, NMUDANG_REVIVE_DLG, TEXT("dialog_revive"), NMuDangReviveStaticProc, pParent );

		m_pStatic_now_summon	 = new 	CStatic	( this )	;
		m_pButton_summon_revive	 = new 	CButton	( this )	;
		m_pEdit_summon_revive_explain	 = new 	CEdit	( this )	;
		m_pComboBox_now_summon	 = new 	CComboBox	( this )	;

		file.CreateControl( 	m_pStatic_now_summon,		NMUDANG_REVIVE_STATICTEXT_NOW_SUMMON	, TEXT("statictext_now_summon") )	;
		file.CreateControl( 	m_pButton_summon_revive,		NMUDANG_REVIVE_BUTTON_SUMMON_REVIVE	, TEXT("button_summon_revive") )	;
		file.CreateControl( 	m_pEdit_summon_revive_explain,		NMUDANG_REVIVE_EDITBOX_SUMMON_REVIVE_EXPLAIN	, TEXT("editbox_summon_revive_explain") )	;
		file.CreateControl( 	m_pComboBox_now_summon,		NMUDANG_REVIVE_COMBOBOX_NOW_SUMMON	, TEXT("combobox_now_summon") )	;

		//m_pParent->UpdateCurrentSummonInfo(FALSE);
		//m_pParent->UpdateReviveMent();
	}
	else
	{
		DeleteDialog();
	}
}

void CNMudangReviveDlg::Show()
{
	//SetTimerOnOff( true );
	//SetActionTimer( 2000 );

	m_bShow = true;
	CControllerMgr::Show( true );
}

void CNMudangReviveDlg::Hide()
{
	//SetTimerOnOff( false );
	m_bShow = false;
	CControllerMgr::Show( false );
}

bool CNMudangReviveDlg::IsShow()
{
	return m_bShow;
}

void CALLBACK CNMudangReviveDlg::NMuDangReviveStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CNMudangReviveDlg *pThis = (CNMudangReviveDlg*) pControllerMgr;
	pThis->NMuDangReviveProc( nEvent, nControlID, pControl );
}

void CALLBACK CNMudangReviveDlg::NMuDangReviveProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NMUDANG_REVIVE_BUTTON_SUMMON_REVIVE:
		{
			switch ( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				m_pParent->SendSummonReviveMessageToServer(1);	
				break;

			}
		}
		break;
	}
}

// CNMudangScrollDlg ==============================================
CNMudangScrollDlg::CNMudangScrollDlg()
{
	m_pParent = NULL;

	m_bShow = false;
	m_pStatic_now_summon	 = NULL; 
	m_pStatic_arrow	 = NULL; 
	m_pStatic_scroll	 = NULL; 
	m_pStatic_scroll_percent_1	 = NULL; 
	m_pStatic_scroll_percent_2	 = NULL; 
	m_pRadioButton_have_scroll_1	 = NULL; 
	m_pRadioButton_have_scroll_2	 = NULL; 
	m_pButton_summon_scroll	 = NULL; 
	m_pEdit_summon_scroll_explain	 = NULL; 
	m_pComboBox_now_summon	 = NULL; 
	m_pOutLine_scroll	 = NULL; 
}

CNMudangScrollDlg::~CNMudangScrollDlg()
{
	if( 	m_pStatic_now_summon	 )  	delete 	m_pStatic_now_summon	;
	if( 	m_pStatic_arrow	 )  	delete 	m_pStatic_arrow	;
	if( 	m_pStatic_scroll	 )  	delete 	m_pStatic_scroll	;
	if( 	m_pStatic_scroll_percent_1	 )  	delete 	m_pStatic_scroll_percent_1	;
	if( 	m_pStatic_scroll_percent_2	 )  	delete 	m_pStatic_scroll_percent_2	;
	if( 	m_pRadioButton_have_scroll_1	 )  	delete 	m_pRadioButton_have_scroll_1	;
	if( 	m_pRadioButton_have_scroll_2	 )  	delete 	m_pRadioButton_have_scroll_2	;
	if( 	m_pButton_summon_scroll	 )  	delete 	m_pButton_summon_scroll	;
	if( 	m_pEdit_summon_scroll_explain	 )  	delete 	m_pEdit_summon_scroll_explain	;
	if( 	m_pComboBox_now_summon	 )  	delete 	m_pComboBox_now_summon	;
	if( 	m_pOutLine_scroll	 )  	delete 	m_pOutLine_scroll	;

	//SetTimerOnOff( false );
}

void CNMudangScrollDlg::Create( CControllerMgr *pParent )
{
	if(pParent == NULL ) return;

	if(!IsCreate())
	{
		m_pParent = (CNMudangDlg*)pParent;

		CInterfaceFile file;

		file.LoadFile(TEXT("NInterface/Data/NMudangDlg/DLG_NMudangScroll.ddf"));
		file.CreateChildDialog( this, NMUDANG_SCROLL_DLG, TEXT("dialog_scroll"), NMudangScrollStaticProc, pParent );

		m_pStatic_now_summon	 = new 	CStatic	( this )	;
		m_pStatic_arrow	 = new 	CStatic	( this )	;
		m_pStatic_scroll	 = new 	CStatic	( this )	;
		m_pStatic_scroll_percent_1	 = new 	CStatic	( this )	;
		m_pStatic_scroll_percent_2	 = new 	CStatic	( this )	;
		m_pRadioButton_have_scroll_1	 = new 	CRadioButton	( this )	;
		m_pRadioButton_have_scroll_2	 = new 	CRadioButton	( this )	;
		m_pButton_summon_scroll	 = new 	CButton	( this )	;
		m_pEdit_summon_scroll_explain	 = new 	CEdit	( this )	;
		m_pComboBox_now_summon	 = new 	CComboBox	( this )	;
		m_pOutLine_scroll	 = new 	COutLine	( this )	;

		file.CreateControl( 	m_pStatic_now_summon,		NMUDANG_SCROLL_STATICTEXT_NOW_SUMMON	, TEXT("statictext_now_summon") )	;
		file.CreateControl( 	m_pStatic_arrow	,	NMUDANG_SCROLL_STATICTEXT_ARROW	, TEXT("statictext_arrow") )	;
		file.CreateControl( 	m_pStatic_scroll,		NMUDANG_SCROLL_STATICTEXT_SCROLL	, TEXT("statictext_scroll") )	;
		file.CreateControl( 	m_pStatic_scroll_percent_1	,	NMUDANG_SCROLL_STATICTEXT_SCROLL_PERCENT_1	, TEXT("statictext_scroll_percent_1") )	;
		file.CreateControl( 	m_pStatic_scroll_percent_2,		NMUDANG_SCROLL_STATICTEXT_SCROLL_PERCENT_2	, TEXT("statictext_scroll_percent_2") )	;
		file.CreateControl( 	m_pRadioButton_have_scroll_1,		NMUDANG_SCROLL_RADIOBUTTON_HAVE_SCROLL_1	, TEXT("radiobutton_have_scroll_1") )	;
		file.CreateControl( 	m_pRadioButton_have_scroll_2,		NMUDANG_SCROLL_RADIOBUTTON_HAVE_SCROLL_2	, TEXT("radiobutton_have_scroll_2") )	;
		file.CreateControl( 	m_pButton_summon_scroll	,	NMUDANG_SCROLL_BUTTON_SUMMON_SCROLL	, TEXT("button_summon_scroll") )	;
		file.CreateControl( 	m_pEdit_summon_scroll_explain,		NMUDANG_SCROLL_EDITBOX_SUMMON_SCROLL_EXPLAIN	, TEXT("editbox_summon_scroll_explain") )	;
		file.CreateControl( 	m_pComboBox_now_summon,		NMUDANG_SCROLL_COMBOBOX_NOW_SUMMON	, TEXT("combobox_now_summon") )	;
		file.CreateControl( 	m_pOutLine_scroll	,	NMUDANG_SCROLL_OUTLINE_SCROLL	, TEXT("outline_scroll") )	;

		//============================================
		// ��ȭ %
		//============================================
		TCHAR textbuffer[256] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(2276);
		StringCchPrintf(textbuffer, 256, pText, (float)(LIMIT_SUMMON_ADD_SCROLL_PERCENT/10.0));
		m_pStatic_scroll->SetText( textbuffer, DT_LEFT | DT_VCENTER );
		m_pRadioButton_have_scroll_1->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );

		//m_pParent->UpdateCurrentSummonInfo( TRUE);
		//m_pParent->UpdateScrollSummonInfo();
		//m_pParent->UpdateScrollMent();

		//SetTimerOnOff( true );
		//SetActionTimer( 2000 );
	}
	else
	{
		DeleteDialog();
	}
}

void CNMudangScrollDlg::Show()
{
	//SetTimerOnOff( true );
	//SetActionTimer( 2000 );

	m_bShow = true;
	CControllerMgr::Show( true );
}

void CNMudangScrollDlg::Hide()
{
	//SetTimerOnOff( false );
	m_bShow = false;
	CControllerMgr::Show( false );
}

bool CNMudangScrollDlg::IsShow()
{
	return m_bShow;
}

void CALLBACK CNMudangScrollDlg::NMudangScrollStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CNMudangScrollDlg *pThis = (CNMudangScrollDlg*) pControllerMgr;
	pThis->NMudangScrollProc( nEvent, nControlID, pControl );
}

void CALLBACK CNMudangScrollDlg::NMudangScrollProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NMUDANG_SCROLL_BUTTON_SUMMON_SCROLL:
		{
			switch ( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				if(m_pParent)
					m_pParent->SendSummonScrollMessageToServer( 1);
				break;
			}
		}
		break;
	case NMUDANG_SCROLL_RADIOBUTTON_HAVE_SCROLL_1:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButton_have_scroll_1->IsCheck() )
					{
						if(m_pParent)
							m_pParent->m_siActiveScrollIndex = 0;
					}
				}
				break;
			}
		}
		break;
	case NMUDANG_SCROLL_RADIOBUTTON_HAVE_SCROLL_2:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButton_have_scroll_2->IsCheck() )
					{
						if(m_pParent)
							m_pParent->m_siActiveScrollIndex = 1;
					}
				}
				break;
			}
		}
		break;
	}
}

// CNMudangEvolveDlg ==============================================
CNMudangEvolveDlg::CNMudangEvolveDlg()
{
	m_pParent = NULL;

	m_pStatic_now_summon	 = NULL; 
	m_pStatic_arrow	 = NULL; 
	m_pStatic_new_summon	 = NULL; 
	m_pButton_summon_evolve	 = NULL; 
	m_pEdit_summon_evolve_explain	 = NULL; 
	m_pList_new_summon	 = NULL; 
	m_pComboBox_now_summon	 = NULL; 

	m_pRadioButton_evolution	 = NULL; 
	m_pRadioButton_devolution	 = NULL; 
	m_pRadioButton_transform	 = NULL; 

}

CNMudangEvolveDlg::~CNMudangEvolveDlg()
{
	if( 	m_pStatic_now_summon	 )  	delete 	m_pStatic_now_summon	;
	if( 	m_pStatic_arrow	 )  	delete 	m_pStatic_arrow	;
	if( 	m_pStatic_new_summon	 )  	delete 	m_pStatic_new_summon	;
	if( 	m_pButton_summon_evolve	 )  	delete 	m_pButton_summon_evolve	;
	if( 	m_pEdit_summon_evolve_explain	 )  	delete 	m_pEdit_summon_evolve_explain	;
	if( 	m_pList_new_summon	 )  	delete 	m_pList_new_summon	;
	if( 	m_pComboBox_now_summon	 )  	delete 	m_pComboBox_now_summon	;

	if( 	m_pRadioButton_evolution	 )  	delete 	m_pRadioButton_evolution	;
	if( 	m_pRadioButton_devolution	 )  	delete 	m_pRadioButton_devolution	;
	if( 	m_pRadioButton_transform	 )  	delete 	m_pRadioButton_transform	;

}

void CNMudangEvolveDlg::Create( CControllerMgr *pParent )
{
	if(pParent == NULL ) return;

	if(!IsCreate())
	{
		m_pParent = (CNMudangDlg*)pParent;

		CInterfaceFile file;

		file.LoadFile(TEXT("NInterface/Data/NMudangDlg/DLG_NMudangEvolve.ddf"));
		file.CreateChildDialog( this, NMUDANG_EVOLVE_DLG, TEXT("dialog_evolve"), NMudangEvolveStaticProc, pParent );

		m_pStatic_now_summon	 = new 	CStatic	( this )	;
		m_pStatic_arrow	 = new 	CStatic	( this )	;
		m_pStatic_new_summon	 = new 	CStatic	( this )	;
		m_pButton_summon_evolve	 = new 	CButton	( this )	;
		m_pEdit_summon_evolve_explain	 = new 	CEdit	( this )	;
		m_pList_new_summon	 = new 	CList	( this )	;
		m_pComboBox_now_summon	 = new 	CComboBox	( this )	;

		m_pRadioButton_evolution	 = new 	CRadioButton	( this )	;
		m_pRadioButton_devolution	 = new 	CRadioButton	( this )	;
		m_pRadioButton_transform	 = new 	CRadioButton	( this )	;

		file.CreateControl( 	m_pRadioButton_evolution	, 	NMUDANG_SCROLL_RADIOBUTTON_EVOLUTION	, 	TEXT("radiobutton_evolution")	 )	;
		file.CreateControl( 	m_pRadioButton_devolution	, 	NMUDANG_SCROLL_RADIOBUTTON_DEVOLUTION	, 	TEXT("radiobutton_devolution")	 )	;
		file.CreateControl( 	m_pRadioButton_transform	, 	NMUDANG_SCROLL_RADIOBUTTON_TRANSFORM	, 	TEXT("radiobutton_transform")	 )	;

		file.CreateControl( 	m_pStatic_now_summon,		NMUDANG_EVOLVE_STATICTEXT_NOW_SUMMON	, TEXT("statictext_now_summon") )	;
		file.CreateControl( 	m_pStatic_arrow,		NMUDANG_EVOLVE_STATICTEXT_ARROW	, TEXT("statictext_arrow") )	;
		file.CreateControl( 	m_pStatic_new_summon,		NMUDANG_EVOLVE_STATICTEXT_NEW_SUMMON	, TEXT("statictext_new_summon") )	;
		file.CreateControl( 	m_pButton_summon_evolve,		NMUDANG_EVOLVE_BUTTON_SUMMON_EVOLVE	, TEXT("button_summon_evolve") )	;
		file.CreateControl( 	m_pEdit_summon_evolve_explain,		NMUDANG_EVOLVE_EDITBOX_SUMMON_EVOLVE_EXPLAIN	, TEXT("editbox_summon_evolve_explain") )	;
		file.CreateControl( 	m_pList_new_summon,		NMUDANG_EVOLVE_LISTBOX_NEW_SUMMON	, TEXT("listbox_new_summon") )	;
		file.CreateControl( 	m_pComboBox_now_summon,		NMUDANG_EVOLVE_COMBOBOX_NOW_SUMMON	, TEXT("combobox_now_summon") )	;

		m_pList_new_summon->SetColumn( 0, 112, TEXT(""));
		m_pList_new_summon->SetColumn( 1, 18, TEXT(""));
		m_pList_new_summon->SetBorder( true );
		m_pList_new_summon->SetBKColorUse( true );
		m_pList_new_summon->Refresh();

		m_pRadioButton_evolution->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );

		//m_pParent->UpdateCurrentSummonInfo(TRUE);
		//m_pParent->UpdateEvolveSummonInfo();
		//m_pParent->UpdateEvolveMent();
	}
	else
	{
		DeleteDialog();
	}
}

void CNMudangEvolveDlg::Show()
{
	//SetTimerOnOff( true );
	//SetActionTimer( 2000 );

	m_bShow = true;
	CControllerMgr::Show( true );
}

void CNMudangEvolveDlg::Hide()
{
	//SetTimerOnOff( false );
	m_bShow = false;
	CControllerMgr::Show( false );
}

bool CNMudangEvolveDlg::IsShow()
{
	return m_bShow;
}

void CALLBACK CNMudangEvolveDlg::NMudangEvolveStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CNMudangEvolveDlg *pThis = (CNMudangEvolveDlg*) pControllerMgr;
	pThis->NMudangEvolveProc( nEvent, nControlID, pControl );
}

void CALLBACK CNMudangEvolveDlg::NMudangEvolveProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NMUDANG_EVOLVE_BUTTON_SUMMON_EVOLVE:
		{
			switch ( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				if(m_pParent)
				{
					switch(m_pParent->m_siSelectEvolveDlg)
					{
					case SUMMONEVOLVE_EVOLVE:
						m_pParent->SendSummonEvolveMessageToServer( 1);
						break;
					case SUMMONEVOLVE_DEVOLUTION:
						m_pParent->SendSummonDevolutionMessageToServer( 1);
						break;
					case SUMMONEVOLVE_TRANSFORM:
						m_pParent->SendSummonTransformMessageToServer( 1);
						break;
					default:
						break;
					}
				}
				break;
			}
		}
		break;
	case NMUDANG_SCROLL_RADIOBUTTON_EVOLUTION:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButton_evolution->IsCheck() == true )
					{
						m_pParent->m_siSelectEvolveDlg = SUMMONEVOLVE_EVOLVE ;
						m_pParent->UpdateCurrentSummonInfo(TRUE);
						m_pParent->UpdateEvolveSummonInfo();
                        TCHAR* pText = GetTxtFromMgr(3894);
						m_pButton_summon_evolve->SetText(pText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
					}
				}
				break;
			}
		}
		break;
	case NMUDANG_SCROLL_RADIOBUTTON_DEVOLUTION:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButton_devolution->IsCheck() == true )
					{
						m_pParent->m_siSelectEvolveDlg = SUMMONEVOLVE_DEVOLUTION ;

						m_pParent->UpdateCurrentSummonInfo(TRUE);
						m_pParent->UpdateDevolutionSummonInfo();
						 TCHAR* pText = GetTxtFromMgr(3895);
						m_pButton_summon_evolve->SetText(pText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
					}
				}
				break;
			}
		}
		break;
	case NMUDANG_SCROLL_RADIOBUTTON_TRANSFORM:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButton_transform->IsCheck() == true )
					{
						m_pParent->m_siSelectEvolveDlg = SUMMONEVOLVE_TRANSFORM ;

						m_pParent->UpdateCurrentSummonInfo(TRUE);
						m_pParent->UpdateTransformSummonInfo();
						TCHAR* pText = GetTxtFromMgr(3896);
						m_pButton_summon_evolve->SetText(pText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
					}
				}
				break;
			}
		}
		break;
	}
}

// CNMudangEquipItemDlg ==============================================
CNMudangEquipItemDlg::CNMudangEquipItemDlg()
{
	m_pParent = NULL;
	m_bShow = false;
	// ���� �ʱ�ȭ
	invennum = 0;
	matnum	  = 0;
	siWeaponestonNUM = 0 ;
	siArmorStonNUM = 0 ;
	siArmorStonUnique = 0	;
	siWeaponestonUnique =	0;
	siArmorStonUnique = ITEMUNIQUE(5415);
	siWeaponestonUnique = ITEMUNIQUE(5414);
	
	m_pStatic_now_summon		= NULL	;	// TEXT : ���� ��ȯ�� 
	m_pStaticimage_summonface	= NULL	;	// ���ո����̹���
	m_pOutline_summonface		= NULL	;	// ���ո����̹����ƿ�����
	m_pStatic_summonlevel		= NULL	;	// TEXT : ��ȯ������
	m_pStatic_weaponston		= NULL	;	// TEXT : �������뼮
	m_pStatic_armorston			= NULL	;	// TEXT : �����뼮
	m_pStatic_summonlevelNow	= NULL		;	// TEXT : ���� ��ȯ������
	m_pStatic_weaponstonNow		= NULL;	// TEXT : ���� �������뼮
	m_pStatic_armorstonNow		= NULL		;	// TEXT : ���������뼮 
	m_pOutline_summonstat		= NULL	;	// ���ո����̹����ƿ�����

	m_pStatic_weapontitle		= NULL	;	// TITLE : ���� ���뼮
	m_pStatic_armortitle		= NULL	;	// TITLE : �� ���뼮
	m_pListview_weaponston	= NULL	;	// ���� ���뼮 �̹���
	m_pOutline_weaponston		= NULL	;	// ���� ���뼺 �ƿ�����
	m_pListview_armorston	= NULL	;	// �� ���뼮 �̹���
	m_pOutline_armorston		= NULL	;	// �� ���뼺 �ƿ�����
	m_pOutline_ston				= NULL	;	// ���뼮 �̹����ƿ�����

	m_pStatic_useston			= NULL	;	// TEXT : ����� ���뼮
	m_pEdit_useston				= NULL	;	// ����� ������ ���뼮 ����
	m_pButton_weaponuseston		= NULL			;	// ���⼮��� ��ư
	m_pButton_armoruseston		= NULL	;	// ���� ��� ��ư
}

CNMudangEquipItemDlg::~CNMudangEquipItemDlg()
{
	if( 	m_pStatic_now_summon		)  	delete 	m_pStatic_now_summon	;		// TEXT : ���� ��ȯ�� 
	if( 	m_pStaticimage_summonface	)  	delete 	m_pStaticimage_summonface	;	// ���ո����̹���
	if( 	m_pOutline_summonface		)  	delete 	m_pOutline_summonface	;		// ���ո����̹����ƿ�����																					
	if( 	m_pStatic_summonlevel		)  	delete 	m_pStatic_summonlevel	;		// TEXT : ��ȯ������
	if( 	m_pStatic_weaponston		)  	delete 	m_pStatic_weaponston	;		// TEXT : �������뼮
	if( 	m_pStatic_armorston			)  	delete 	m_pStatic_armorston	;			// TEXT : �����뼮
	if( 	m_pStatic_summonlevelNow		)  	delete 	m_pStatic_summonlevelNow	;		// TEXT : ���� ��ȯ������
	if( 	m_pStatic_weaponstonNow		)  	delete 	m_pStatic_weaponstonNow	;		// TEXT : ���� �������뼮
	if( 	m_pStatic_armorstonNow			)  	delete 	m_pStatic_armorstonNow	;			// TEXT : ���� ������
	if( 	m_pOutline_summonstat		)  	delete 	m_pOutline_summonstat	;		// ���ո����̹����ƿ�����

	if( 	m_pStatic_weapontitle		)  	delete 	m_pStatic_weapontitle	;		// TITLE : ���� ���뼮
	if( 	m_pStatic_armortitle		)  	delete 	m_pStatic_armortitle	;		// TITLE : �� ���뼮
	if( 	m_pListview_weaponston	)  	delete 	m_pListview_weaponston	;	// ���� ���뼮 �̹���
	if( 	m_pOutline_weaponston		)  	delete 	m_pOutline_weaponston	;		// ���� ���뼮 �ƿ�����
	
	if( 	m_pListview_armorston	)  	delete 	m_pListview_armorston	;	// �� ���뼮 �̹���
	if( 	m_pOutline_armorston		)  	delete 	m_pOutline_armorston	;	// �� ���뼮 �ƿ�����
	if( 	m_pOutline_ston				)  	delete 	m_pOutline_ston	;				// ���뼮 �̹����ƿ�����

	if( 	m_pStatic_useston			)  	delete 	m_pStatic_useston	;			// TEXT : ����� ���뼮 
	if( 	m_pEdit_useston				)  	delete 	m_pEdit_useston	;			// ����� ������ ���뼮 ����
	if( 	m_pButton_weaponuseston			)  	delete 	m_pButton_weaponuseston	;			// ��� ��ư
	if( 	m_pButton_armoruseston			)  	delete 	m_pButton_armoruseston	;			// ��� ��ư
	
	
}

void CNMudangEquipItemDlg::Create( CControllerMgr *pParent )
{
	if(pParent == NULL ) return;
	if(!IsCreate())
	{
		m_pParent = (CNMudangDlg*)pParent;
		CInterfaceFile file;

		file.LoadFile(TEXT("NInterface/Data/NMudangDlg/DLG_NMudangEquipitem.ddf"));
		file.CreateChildDialog( this, NMUDANG_EQUIPITEM_DLG, TEXT("dialog_equipitem"), NMudangEquipItemStaticProc, pParent );

		m_pStatic_now_summon		= new 	CStatic	( this )	;				// TEXT : ���� ��ȯ�� 
		m_pStaticimage_summonface	= new 	CImageStatic	( this )	;		// ���ո����̹���
		m_pOutline_summonface		= new 	COutLine	( this )	;			// ���ո����̹����ƿ�����																				
		m_pStatic_summonlevel		= new 	CStatic	( this )	;				// TEXT : ��ȯ������
		m_pStatic_weaponston		= new 	CStatic	( this )	;				// TEXT : �������뼮
		m_pStatic_armorston			= new 	CStatic	( this )	;				// TEXT : �����뼮
		m_pStatic_summonlevelNow	= new 	CStatic	( this )	;				// TEXT : ���� ��ȯ������
		m_pStatic_weaponstonNow		= new 	CStatic	( this )	;				// TEXT : ���� �������뼮
		m_pStatic_armorstonNow		= new 	CStatic	( this )	;				// TEXT : ���� �����뼮
		m_pOutline_summonstat		= new 	COutLine	( this )	;			// ���ո����̹����ƿ�����

		m_pStatic_weapontitle		= new 	CStatic	( this )	;				// TITLE : ���� ���뼮
		m_pStatic_armortitle		= new 	CStatic	( this )	;				// TITLE : �� ���뼮
		m_pListview_weaponston		= new 	CListView	( this )	;		// ���� ���뼮 �̹���
		m_pOutline_weaponston		= new 	COutLine	( this )	;			// ���� ���뼮 �ƿ�����
		m_pListview_armorston		= new 	CListView	( this )	;		// �� ���뼮 �̹���
		m_pOutline_armorston		= new 	COutLine	( this )	;			// ���� ���뼮 �ƿ�����
		m_pOutline_ston				= new 	COutLine	( this )	;			// ���뼮 �̹����ƿ�����

		m_pStatic_useston			= new 	CStatic	( this )	;					// TEXT : ����� ���뼮 
		m_pEdit_useston				= new 	CEdit	( this )	;					// ����� ������ ���뼮 ����
		m_pButton_weaponuseston		= new 	CButton	( this )	;					// ��� ��ư
		m_pButton_armoruseston		= new 	CButton	( this )	;					// ��� ��ư


		file.CreateControl( 	m_pStatic_now_summon	 	,NMUDANG_EQUIPITEM_STATIC_NOWSUMMON	, 	TEXT("statictext_now_summon")	 )	;
		file.CreateControl( 	m_pStaticimage_summonface	, 	NMUDANG_EQUIPITEM_IMAGESTATIC_SUMMONFACE	, 	TEXT("imagestatic_summonface")	 )	;
		file.CreateControl( 	m_pOutline_summonface	, 	NMUDANG_EQUIPITEM_OUTLINE_SUMMONFACE	, 	TEXT("outline_summonface")	 )	;
		file.CreateControl( 	m_pStatic_summonlevel,		NMUDANG_EQUIPITEM_STATIC_SUMMONLEVEL	, TEXT("statictext_summonlevel") )	;
		file.CreateControl( 	m_pStatic_weaponston	 	,NMUDANG_EQUIPITEM_STATIC_WEAPONSTON	, 	TEXT("statictext_weaponston")	 )	;
		file.CreateControl( 	m_pStatic_armorston	, 	NMUDANG_EQUIPITEM_STATIC_AROMRSTON	, 	TEXT("statictext_armorston")	 )	;
		file.CreateControl( 	m_pStatic_summonlevelNow,		NMUDANG_EQUIPITEM_STATIC_SUMMONLEVELNOW	, TEXT("statictext_levelnow") )	;
		file.CreateControl( 	m_pStatic_weaponstonNow	 	,NMUDANG_EQUIPITEM_STATIC_WEAPONSTONNOW	, 	TEXT("statictext_weaponstonnow")	 )	;
		file.CreateControl( 	m_pStatic_armorstonNow	, 	NMUDANG_EQUIPITEM_STATIC_AROMRSTONNOW	, 	TEXT("statictext_armorstonnow")	 )	;
		file.CreateControl( 	m_pOutline_summonstat	, 	NMUDANG_EQUIPITEM_OUTLINE_SUMMONSTAT	, 	TEXT("outline_summonstat")	 )	;

		file.CreateControl( 	m_pStatic_weapontitle	,NMUDANG_EQUIPITEM_STATIC_WEAPONTITLE	, 	TEXT("statictext_weaponstontitle")	 )	;
		file.CreateControl( 	m_pStatic_armortitle	,NMUDANG_EQUIPITEM_STATIC_ARMORTITLE	, 	TEXT("statictext_armorstontitle")	 )	;
		file.CreateControl( 	m_pListview_weaponston	, 	NMUDANG_EQUIPITEM_LISTVIEW_WEAPONSTON	, 	TEXT("listview_weaponston")	 )	;
		file.CreateControl( 	m_pListview_armorston	, 	NMUDANG_EQUIPITEM_LISTVIEW_ARMORSTON	, 	TEXT("listview_armorston")	 )	;		
		file.CreateControl( 	m_pOutline_weaponston	, 	NMUDANG_EQUIPITEM_OUTLINE_WEAPONSTON	, 	TEXT("outline_NONAME2")	 )	;
		file.CreateControl( 	m_pOutline_armorston	, 	NMUDANG_EQUIPITEM_OUTLINE_ARMORSTON	, 	TEXT("outline_NONAME3")	 )	;
		file.CreateControl( 	m_pOutline_ston	, 	NMUDANG_EQUIPITEM_OUTLINE_STON	, 	TEXT("outline_ston")	 )	;

		file.CreateControl( 	m_pStatic_useston 	,NMUDANG_EQUIPITEM_STATIC_USESTON	, 	TEXT("statictext_useston")	 )	;
		file.CreateControl( 	m_pEdit_useston	,NMUDANG_EQUIPITEM_EDIT_USESTON	, 	TEXT("editbox_NONAME1")	 )	;
		file.CreateControl( 	m_pButton_weaponuseston 	,NMUDANG_EQUIPITEM_BUTTON_WEAPONUSESTON	, 	TEXT("button_useweaponston")	 )	;
		file.CreateControl( 	m_pButton_armoruseston 	,NMUDANG_EQUIPITEM_BUTTON_ARMORUSESTON	, 	TEXT("button_usearmornston")	 )	;
		InitTextnImage();
		m_pButton_weaponuseston->Enable( false )	;
		m_pButton_armoruseston->Enable(false)		;
	}
	else
	{
		DeleteDialog();
	}
}

void CNMudangEquipItemDlg::Show()
{
	m_bShow = true;
	CControllerMgr::Show( true );
}

void CNMudangEquipItemDlg::Hide()
{
	m_bShow = false;
	CControllerMgr::Show( false );
}

bool CNMudangEquipItemDlg::IsShow()
{
	return m_bShow;
}
// ��ȯ�� ������ �����ش�.
void CNMudangEquipItemDlg::Showsummonstatus()
{
	SI32 siPortraitFont		=	0	;
	SI32 siPortraitIndex	=	0	;
	SI32 siSummonPortrait	=	0	;
	TCHAR szPortrait[256]	=	TEXT("")	;
	cltKindInfo* pclKI		=	NULL		;

	InitTextnImage();
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[1]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;
	for ( SI16 siSummonIndex = 0 ; siSummonIndex < MAX_SUMMON_OWN; siSummonIndex++)
	{
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
		if(pclSummon == NULL) return;
		if(pclSummon)
		{
			SI32 siKind				=	pclSummon->siKind	;
			// �ش� ��ȯ���� ī�ε� ���� ���� ������ üũ.
			if( pclClient->pclKindInfoSet->IsValidKind( siKind ) == false )	continue;						
			
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate))
			{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[ siKind ];	}
			else
			{	pclKI = pclClient->pclKindInfoSet->pclKI[ siKind ];
			}			

			if ( pclKI	==	NULL )	continue	;
			if ( pclKI->siSummonEquip	==	SUMMON_EQUIPTYPE_NONE  )	continue	;// ������ ���� ������ ��ȯ�� ���� �˻�
			if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT){
				InitTextnImage();
				continue	;
			}
			siSummonPortrait	=	pclKI->siSummonPortrait	;
			siPortraitFont		=	( siSummonPortrait *2 )	;
			{
				// ��ȯ�������� �����ش�.
				m_pStaticimage_summonface->Show(true);
				pclClient->pclKindInfoSet->GetNPCImageFileAndFontsmall(siKind, szPortrait, sizeof(szPortrait), &siSummonPortrait);
				m_pStaticimage_summonface->SetFontIndex( siPortraitFont );
			}
			{
				TCHAR buffer[256];
				// ��ȯ�� ����
				TCHAR* pText = GetTxtFromMgr(624);
				StringCchPrintf(buffer, 256, pText, pclSummon->clIP.GetLevel(), MAX_CHARACTER_LEVEL, pclKI->siEvolveLevel);
				m_pStatic_summonlevelNow->SetText( buffer );
			}
			{
				TCHAR buffer[256];
				// ��ȯ�� ���⼮
				TCHAR* pText = GetTxtFromMgr(8642);
				StringCchPrintf(buffer, 256, pText, pclSummon->siAttackWearStoneNum, pclSummon->clIP.GetLevel(), pclKI->siEvolveLevel);
				m_pStatic_weaponstonNow->SetText( buffer );
			}
			{
				TCHAR buffer[256];
				// ��ȯ�� ���� 
				TCHAR* pText = GetTxtFromMgr(8642);
				StringCchPrintf(buffer, 256, pText, pclSummon->siDefenseWearStoneNum, pclSummon->clIP.GetLevel(), pclKI->siEvolveLevel);
				m_pStatic_armorstonNow->SetText( buffer );
			}			
			showitemImage();
			
			break;
		}
	}
}
bool CNMudangEquipItemDlg:: IsShowSummon(){
	return false	;
}

bool CNMudangEquipItemDlg:: CheckUseston(SI32 ItemType,  SI32 summonlevel, SI32 siStonNum, SI16 siSummonIndex ){
	cltClient* pclclient = (cltClient*)pclClient	;
	SI32 siStonUnique = 0	;
	bool Treefalse = true ;
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[1]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL)	return	false	;
	cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex)		;	// ��ȯ�� ������ ������ �´�
	if(pclSummon == NULL)		return	false	;
	SI32 siMyLevel = pclSummon->clIP.GetLevel()	;	// ���� �ڽ��� ������ ������ �´�
	//--------------------------------------------------------------------------------------------------------
	switch( ItemType )
	{
		case STON_WEAPONE:{
				siStonUnique = ITEMUNIQUE(5414);									// ���� ������
				if( siMyLevel < siStonNum + pclSummon->siAttackWearStoneNum ){	
					Treefalse = false	;
				}
			}break;
		case STON_ARMOR:{	
				siStonUnique = ITEMUNIQUE(5415);									// �� ������
				if( siMyLevel < siStonNum + pclSummon->siDefenseWearStoneNum ){
					Treefalse = false	;
				}
			}break;
	}
	//--------------------------------------------------------------------------------------------------------
	if (  true == Treefalse ){
		for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ ){
			cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
			if( pclItem == NULL )																	continue	;
			if ( pclItem->siUnique == siStonUnique && pclItem->GetItemNum() < siStonNum ){
				TCHAR * pTitle = GetTxtFromMgr(578) ;
				TCHAR * pText = GetTxtFromMgr(8615)	;
				if ( !pTitle || !pText ) return false ;
				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
				return false ;
			}
			if ( pclItem->siUnique == siStonUnique && pclItem->GetItemNum() >= siStonNum )			return true	;			
		}
	}
	else{
		//�ڽ��� ���� �̻����� ��� ���뼮�� ����Ҽ� �����ϴ�.
		TCHAR * pTitle = GetTxtFromMgr(578) ;
		TCHAR * pText = GetTxtFromMgr(8618)	;
		if ( !pTitle || !pText ) return false ;
		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
		return false ;
	}
	return false ;	
}
void CNMudangEquipItemDlg:: showitemImage(){
	cltClient* pclclient = (cltClient*)pclClient;
	stListViewItemData ListViewItemData;
	bool  bIsSealed     = false;
	SI16 StartPos = 0;
	SI32 i = 0;
	SI32 id = 1;
	SI32 GlobalImageIndex = -1;
	SI32 GlobalImageFont = -1;
	TCHAR ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = TEXT("");
	
	//�κ��丮���� �������� ã�´�.
	for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
	{
		cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
		if(pclItem == NULL)					continue;
		TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName(pclItem->siUnique);
		if( pclItem->siUnique == siWeaponestonUnique)
		{
			m_pListview_weaponston->DeleteAllItems();// �� ������
			m_pListview_weaponston->SetStartItemPos( StartPos );
			pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclItem->siUnique, &GlobalImageIndex, &GlobalImageFont );
			pclClient->pclItemManager->GetExplain( pclItem, ToolTipMsg );
			ListViewItemData.Init();
			ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0, pclItem->siItemNum, ItemName, ToolTipMsg, false, bIsSealed ); // ������ ������ ���� ���� ColorSwitch = true
			m_pListview_weaponston->InsertItem( &ListViewItemData );
			m_pButton_weaponuseston->Enable(true);
		}
		if( pclItem->siUnique == siArmorStonUnique)
		{
			m_pListview_armorston->DeleteAllItems();// ����������
			m_pListview_armorston->SetStartItemPos( StartPos );
			pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclItem->siUnique, &GlobalImageIndex, &GlobalImageFont );
			pclClient->pclItemManager->GetExplain( pclItem, ToolTipMsg );
			ListViewItemData.Init();
			ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0, pclItem->siItemNum, ItemName, ToolTipMsg, false, bIsSealed ); // ������ ������ ���� ���� ColorSwitch = true
			m_pListview_armorston->InsertItem( &ListViewItemData );
			m_pButton_armoruseston->Enable(true);
		}
	}
}
// ��ȯ�� ����, ����-�� ���뼮 �� ���� �ʱ� ��
void CNMudangEquipItemDlg::InitTextnImage(){
	m_pStaticimage_summonface->Show(false) ;	// ���ո����̹���
	m_pStatic_summonlevelNow->SetText("");		// ���� ���� ����
	m_pStatic_weaponstonNow->SetText("");		// ���� ���� ��� ���⼮
	m_pStatic_armorstonNow->SetText("");		// ���� ���� ��� �� ��
	m_pListview_armorston->DeleteAllItems();	// ����������
	m_pListview_weaponston->DeleteAllItems();	// �� ������
	m_pButton_weaponuseston->Enable(false);
	m_pButton_armoruseston->Enable(false);
}
void CALLBACK CNMudangEquipItemDlg::NMudangEquipItemStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CNMudangEquipItemDlg *pThis = (CNMudangEquipItemDlg*) pControllerMgr;
	pThis->NMudangEquipItemProc( nEvent, nControlID, pControl );
}

void CALLBACK CNMudangEquipItemDlg::NMudangEquipItemProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = ( cltClient * )pclClient;
	switch( nControlID )
	{
		case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
		case NMUDANG_EQUIPITEM_BUTTON_WEAPONUSESTON:// WeaponeSton ��� ��ư Ŭ��
			{
			switch(nEvent){
				case EVENT_BUTTON_CLICKED:
					{
						TCHAR* pTitle = GetTxtFromMgr(578);
						TCHAR* pText  = GetTxtFromMgr(8613);
						stMsgBox MsgBox;
						MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 1 );
						pclclient->SetMsgBox( &MsgBox, NULL , 0 );
					}
			}
			}break;
		case NMUDANG_EQUIPITEM_BUTTON_ARMORUSESTON:{
			switch(nEvent){
				case EVENT_BUTTON_CLICKED:{
					TCHAR* pTitle = GetTxtFromMgr(578)	;
					TCHAR* pText  = GetTxtFromMgr(8614)	;
					stMsgBox MsgBox	;
					MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 2 )	;
					pclclient->SetMsgBox( &MsgBox, NULL , 0 )	;
				}
			}break;
		}
	}
}
void CNMudangEquipItemDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient*)pclClient;
	switch( MsgIndex  ) {
	case 1:
		{
			if ( RetValue ) {
				TCHAR* usestonnum = m_pEdit_useston->GetText();
				SI32 siStonNum = _ttoi(usestonnum);// �ؽ�Ʈ�� ���ڷ� ����
				if (siStonNum <= 0 ) {
					// ��Ȯ�� ������ �Է��ϼ���
					TCHAR * pTitle = GetTxtFromMgr(512) ;
					TCHAR * pText = GetTxtFromMgr(8612) ;
					if ( !pTitle || !pText ) break ;
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
					return	;
				}
				cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[1]->pclCI->clSummonInfo	;
				if(pclSummonInfo == NULL)	return	;
				cltKindInfo* pclKI = NULL	;
				for ( SI16 siSummonIndex = 0 ; siSummonIndex < MAX_SUMMON_OWN; siSummonIndex++){
					cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
					if(pclSummon == NULL) continue;
					SI32 siKind				=	pclSummon->siKind	;
					if(pclClient->pclKindInfoSet->IsValidKind( siKind ) == false ) continue;
					if(pclSummon){
						// �ش� ��ȯ���� ī�ε� ���� ���� ������ üũ.			
						if(pclClient->IsCountrySwitch(Switch_Summon_Separate))
						{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[ siKind ];	}
						else
						{	pclKI = pclClient->pclKindInfoSet->pclKI[ siKind ];
						}					
						if (pclKI == NULL)  continue;
						if ( pclKI->siSummonEquip	==	SUMMON_EQUIPTYPE_NONE  )	continue	;// ������ ���� ������ ��ȯ�� ���� �˻�
						if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	continue;	
						if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)	continue;

						if ( CheckUseston( STON_WEAPONE, pclSummon->clIP.GetLevel(), siStonNum, siSummonIndex ) == true) 
						{
							cltGameMsgRequest_SummonEquipston clInfo( pclClient->pclCM->CR[1]->GetCharUnique(), pclSummon->siSummonID, STON_WEAPONE, siStonNum );
							cltMsg clMsg(GAMEMSG_REQUEST_SUMMONUSTON, sizeof(clInfo), (BYTE*)&clInfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							break;						
						}
				}
			}
			}
		}
		break;
	case 2:
		{
			if (RetValue) {
				TCHAR* usestonnum = m_pEdit_useston->GetText();
				SI32 siStonNum = _ttoi(usestonnum);// �ؽ�Ʈ�� ���ڷ� ����
				if (siStonNum <= 0) { 
					// ��Ȯ�� ������ �Է��ϼ���
					TCHAR * pTitle = GetTxtFromMgr(512) ;
					TCHAR * pText = GetTxtFromMgr(8612) ;
					if ( !pTitle || !pText ) break ;
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
					return;
				}
				cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[1]->pclCI->clSummonInfo;							
				if(pclSummonInfo == NULL) return;
				cltKindInfo* pclKI = NULL;				
				for ( SI16 siSummonIndex = 0 ; siSummonIndex < MAX_SUMMON_OWN; siSummonIndex++){
					cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
					if(pclSummon == NULL) continue;
					if(pclSummon){
						SI32 siKind				=	pclSummon->siKind	;
						if(pclClient->pclKindInfoSet->IsValidKind( siKind ) == false ) continue;
						// �ش� ��ȯ���� ī�ε� ���� ���� ������ üũ.			
						if(pclClient->IsCountrySwitch(Switch_Summon_Separate))
						{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[ siKind ];	}
						else
						{	pclKI = pclClient->pclKindInfoSet->pclKI[ siKind ];
						}
						if (pclKI == NULL)  continue;
						if ( pclKI->siSummonEquip	==	SUMMON_EQUIPTYPE_NONE  )	continue	;// ������ ���� ������ ��ȯ�� ���� �˻�
						if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	continue	;									
						if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)	continue	;
						if ( CheckUseston( STON_ARMOR, pclSummon->clIP.GetLevel(), siStonNum, siSummonIndex ) == true) 
						{
							cltGameMsgRequest_SummonEquipston clInfo(pclClient->pclCM->CR[1]->GetCharUnique(),pclSummon->siSummonID,STON_ARMOR,siStonNum );
							cltMsg clMsg(GAMEMSG_REQUEST_SUMMONUSTON, sizeof(clInfo), (BYTE*)&clInfo);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							break;
						}

						else{
							// ���뼮�� �����ϴٴ� �޼����� ������.
							TCHAR * pTitle = GetTxtFromMgr(578) ;
							TCHAR * pText = GetTxtFromMgr(8618);
							if ( !pTitle || !pText ) break ;
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
							return;
						}
					}
				}
			}
		}
		break;
	}
}
// CNMudangDlg ===============================+++++===============
// TIMER
CNMudangDlg::CNMudangDlg()
{
	m_bRect			= false;

	m_CurrentStatusPage	 = 0;
	m_LastSendSummonTime  = 0;

	m_siActiveScrollIndex = 0;
	m_bChangedScrollPercent = FALSE;

	m_pTabReviveDlg = NULL;
	m_pTabScrollDlg = NULL;
	m_pTabEvolveDlg = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
		m_pTabEquipitemDlg = NULL;
	}
        
	m_pImageStatic_portrait_mudang	 = NULL; 
	m_pButton_revive	 = NULL; 
	m_pButton_scroll	 = NULL; 
	m_pButton_evolve	 = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
		m_pButton_equipitem = NULL;// ������ ����	
	}
	m_pButton_close	 = NULL; 
	m_pEdit_mudang	 = NULL; 
	m_pEdit_message	 = NULL; 
	m_pOutLine_portrait_mudang	 = NULL; 

	m_siSelectEvolveDlg = 0 ;
}

CNMudangDlg::~CNMudangDlg()
{
	if( m_pTabReviveDlg) delete m_pTabReviveDlg;
	if( m_pTabScrollDlg) delete m_pTabScrollDlg;
	if( m_pTabEvolveDlg) delete m_pTabEvolveDlg;
	if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
		if( m_pTabEquipitemDlg) delete m_pTabEquipitemDlg;
	}

	m_pTabReviveDlg = NULL;
	m_pTabScrollDlg = NULL;
	m_pTabEvolveDlg = NULL;
	m_pTabEquipitemDlg = NULL;

	if( 	m_pImageStatic_portrait_mudang	 )  	delete 	m_pImageStatic_portrait_mudang	;
	if( 	m_pButton_revive	 )  	delete 	m_pButton_revive	;
	if( 	m_pButton_scroll	 )  	delete 	m_pButton_scroll	;
	if( 	m_pButton_evolve	 )  	delete 	m_pButton_evolve	;
	if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
		if( 	m_pButton_equipitem	 )  	delete 	m_pButton_equipitem	;	// ������ ����	
	}
	if( 	m_pButton_close	 )  	delete 	m_pButton_close	;
	if( 	m_pEdit_mudang	 )  	delete 	m_pEdit_mudang	;
	if( 	m_pEdit_message	 )  	delete 	m_pEdit_message	;
	if( 	m_pOutLine_portrait_mudang	 )  	delete 	m_pOutLine_portrait_mudang	;

	m_bRect = true;
}

void CNMudangDlg::Create()
{
	if(!IsCreate())
	{
		cltClient *pclclient = (cltClient*)pclClient;

		CInterfaceFile file;
		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			file.LoadFile(TEXT("NInterface/Data/NMudangDlg/DLG_NMudang_New.ddf"));
		}
		else{
			file.LoadFile(TEXT("NInterface/Data/NMudangDlg/DLG_NMudang.ddf"));
		}

		file.CreatePopupDialog( this, NMUDANG_DLG, TEXT("dialog_mudang"), NMudangStaticProc);

		SI32 siTmp = 0, siTmpWidth = 0;

		siTmp = file.GetInfoWithStringID( TEXT("dialog_mudang") );

		if(siTmp < 0 )
			siTmpWidth = DLG_BIG_POS_X;
		else
			siTmpWidth = file.m_control[ siTmp  ].width;

		if(((CNSoundOnOffDlg*)pclclient->m_pDialog[ NSOUNDONOFF_DLG ])->m_bBigDisplayMode == true )
		{
			this->MovePos(DLG_BIG_POS_X - siTmpWidth, DLG_BIG_POS_Y);
		}
		else
		{
			this->MovePos(DLG_SMALL_POS_X - siTmpWidth, DLG_SMALL_POS_Y);
		}

		m_pImageStatic_portrait_mudang	 = new 	CImageStatic	( this )	;
		m_pButton_revive	 = new 	CButton	( this )	;
		m_pButton_scroll	 = new 	CButton	( this )	;
		m_pButton_evolve	 = new 	CButton	( this )	;
		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			m_pButton_equipitem  = new	CButton ( this )	;
		}
		m_pButton_close	 = new 	CButton	( this )	;
		m_pEdit_mudang	 = new 	CEdit	( this )	;
		m_pEdit_message	 = new 	CEdit	( this )	;
		m_pOutLine_portrait_mudang	 = new 	COutLine	( this )	;

		file.CreateControl( 	m_pImageStatic_portrait_mudang	, 	NMUDANG_IMAGESTATIC_PORTRAIT_MUDANG	, TEXT("imagestatic_portrait_mudang") )	;
		file.CreateControl( 	m_pButton_revive	, 	NMUDANG_BUTTON_REVIVE	, TEXT("button_revive") )	;
		file.CreateControl( 	m_pButton_scroll	, 	NMUDANG_BUTTON_SCROLL	, TEXT("button_scroll") )	;
		file.CreateControl( 	m_pButton_evolve	, 	NMUDANG_BUTTON_EVOLVE	, TEXT("button_evolve") )	;
		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			file.CreateControl( 	m_pButton_equipitem	, 	NMUDANG_BUTTON_EQUIPITEM	, TEXT("button_equipitem") )	;// ������ ����	
		}
		file.CreateControl( 	m_pButton_close	, 	NMUDANG_BUTTON_CLOSE	, TEXT("button_close") )	;
		file.CreateControl( 	m_pEdit_mudang	, 	NMUDANG_EDITBOX_MUDANG	, TEXT("editbox_mudang") )	;
		file.CreateControl( 	m_pEdit_message	, 	NMUDANG_EDITBOX_MESSAGE	, TEXT("editbox_message") )	;
		file.CreateControl( 	m_pOutLine_portrait_mudang	, 	NMUDANG_OUTLINE_PORTRAIT_MUDANG	, TEXT("outline_portrait_mudang") )	;

		//cyj ��ȭ��ư �ӽ÷� �Ⱥ��̵���
		m_pButton_scroll->Show( false );

		m_pTabReviveDlg = new CNMudangReviveDlg();
		m_pTabScrollDlg = new CNMudangScrollDlg();
		m_pTabEvolveDlg = new CNMudangEvolveDlg();
		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			m_pTabEquipitemDlg = new CNMudangEquipItemDlg();
		}
	
		if(!m_pTabReviveDlg->IsCreate())
		{
			m_pTabReviveDlg->Create( this );
			UpdateCurrentSummonInfo(FALSE);
			UpdateReviveMent();
		}

		if(!m_pTabScrollDlg->IsCreate())
		{
			m_pTabScrollDlg->Create( this );
			UpdateCurrentSummonInfo( TRUE);
			//UpdateScrollSummonInfo();
			//UpdateScrollMent();
		}
		if(!m_pTabEvolveDlg->IsCreate())
		{
			m_pTabEvolveDlg->Create( this );
			//UpdateCurrentSummonInfo(TRUE);
			//UpdateEvolveSummonInfo();
			//UpdateEvolveMent();
		}
		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			if(!m_pTabEquipitemDlg->IsCreate())
			{
				m_pTabEquipitemDlg->Create( this );
			}
		}
		//==========================================
		// ������ �⺻ ��Ʈ 
		//==========================================
		TCHAR buffer[512]= TEXT("");
		if(pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel()< LIMIT_LEVEL_HATCH_DOLL)
		{
			TCHAR* pText = GetTxtFromMgr(2270);
			StringCchPrintf(buffer, 512, pText, LIMIT_LEVEL_HATCH_DOLL);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2271);
			StringCchCopy(buffer, 512, pText);
		}
		m_pEdit_mudang->SetText( buffer);
		//==========================================
		// �ʻ�ȭ 
		//==========================================
		TCHAR* pText = GetTxtFromMgr(2272);
		SI32 siNCPKind = pclClient->pclKindInfoSet->FindKindFromName( pText );
		if(pclClient->pclKindInfoSet->pclKI[ siNCPKind ])
		{
			TCHAR strFileName[ 128 ] = TEXT("");
			//sprintf( strFileName, TEXT("Interface/Portrait/%s.bmp"),	pclClient->pclKindInfoSet->pclKI[ siNCPKind ]->szCode );
			//m_hPortraitBitmap = (HBITMAP)LoadImage( m_hInst, strFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
			SI16 tmpSelectedIndex = pclClient->pclKindInfoSet->FindKindFromName( pText );

			TCHAR szPortrait[256];
			SI32 siPortraitFont;
			pclClient->pclKindInfoSet->GetNPCImageFileAndFont(tmpSelectedIndex, szPortrait, sizeof(szPortrait), &siPortraitFont);
			m_pImageStatic_portrait_mudang->SetFileName(szPortrait);
			m_pImageStatic_portrait_mudang->SetFontIndex( siPortraitFont );
			//m_pImageStatic_portrait_mudang->SetFontIndex( 138 );

		}
		
		//==========================================
		// TAB WINDOW
		//==========================================
		m_CurrentStatusPage	= 0;
		// ��Ȱ �� ���̱�
		ShowTabBy( m_CurrentStatusPage );


		SetTimerOnOff( true );
		SetActionTimer( 1000 );
	}
	else
	{
		DeleteDialog();
	}
}

void CNMudangDlg::Set()
{
	Create();
}

void CALLBACK CNMudangDlg::NMudangStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CNMudangDlg *pThis = (CNMudangDlg*) pControllerMgr;
	pThis->NMudangProc( nEvent, nControlID, pControl );
}

void CALLBACK CNMudangDlg::NMudangProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NMUDANG_BUTTON_CLOSE:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				DeleteDialog();
				break;
			}
		}
		break;
	case NMUDANG_BUTTON_REVIVE:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					//==========================================
					// ������ �⺻ ��Ʈ 
					//==========================================
					TCHAR buffer[512]= TEXT("");
					if(pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel()< LIMIT_LEVEL_HATCH_DOLL)
					{
						TCHAR* pText = GetTxtFromMgr(2270);
						StringCchPrintf(buffer, 512, pText, LIMIT_LEVEL_HATCH_DOLL);
					}
					else
					{
						TCHAR* pText = GetTxtFromMgr(2271);
						StringCchCopy(buffer, 512, pText);
					}
					m_pEdit_mudang->SetText( buffer);
					m_pEdit_message->Clear();
					m_CurrentStatusPage = 0;
					ShowTabBy( m_CurrentStatusPage );                    			
				}
				break;
			}
		}
		break;
	case NMUDANG_BUTTON_SCROLL:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					m_CurrentStatusPage = 1;
					ShowTabBy( m_CurrentStatusPage );                    			
				}
				break;
			}
		}
		break;
	case NMUDANG_BUTTON_EVOLVE:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					//==========================================
					// ������ �⺻ ��Ʈ 
					//==========================================
					TCHAR buffer[512]= TEXT("");
					if(pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel()< LIMIT_LEVEL_HATCH_DOLL)
					{
						TCHAR* pText = GetTxtFromMgr(2270);
						StringCchPrintf(buffer, 512, pText, LIMIT_LEVEL_HATCH_DOLL);
					}
					else
					{
						TCHAR* pText = GetTxtFromMgr(2271);
						StringCchCopy(buffer, 512, pText);
					}
					m_pEdit_mudang->SetText( buffer);
					m_pEdit_message->Clear();
					m_CurrentStatusPage = 2;
					ShowTabBy( m_CurrentStatusPage );                    			
				}
				break;
			}
		}
		break;
	case NMUDANG_BUTTON_EQUIPITEM:// ������ ����	
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					//==========================================
					// ������ �⺻ ��Ʈ 
					//==========================================
					TCHAR buffer[512]= TEXT("");
					if(pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel()< LIMIT_LEVEL_HATCH_DOLL)
					{
						TCHAR* pText = GetTxtFromMgr(2270);
						StringCchPrintf(buffer, 512, pText, LIMIT_LEVEL_HATCH_DOLL);
					}
					else
					{
						TCHAR* pText = GetTxtFromMgr(2271);
						StringCchCopy(buffer, 512, pText);
					}
					m_pEdit_mudang->SetText( buffer);
					
					SetTextBySummonEquip();
					m_CurrentStatusPage = 3;
					ShowTabBy( m_CurrentStatusPage );
				}break;
			}
		}break;
	}
}

void CNMudangDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{

}
//===================================================================
//
//===================================================================
BOOL CNMudangDlg::GetComboSummonNameIndex(TCHAR *CurrSummonName, SI16 txtSIze, SI32 *siSummonIndex)
{
	TCHAR TempSummonName[60] = TEXT("");
	TCHAR TempSummonIndex[60] = TEXT("");
	TCHAR *pTempChar = NULL;
	SI16 siComboIndex = -1;
	switch( m_CurrentStatusPage )
	{
	case 0:
		{
			if(m_pTabReviveDlg && m_pTabReviveDlg->IsCreate() && m_pTabReviveDlg->m_pComboBox_now_summon )
			{
				siComboIndex = m_pTabReviveDlg->m_pComboBox_now_summon->GetSelectedIndex();
				if( siComboIndex < 0 ) return FALSE;
				pTempChar = m_pTabReviveDlg->m_pComboBox_now_summon->GetText(siComboIndex);
				_tcscpy( TempSummonName, pTempChar );
			}
		}
		break;
	case 1:
		{
			if(m_pTabScrollDlg && m_pTabScrollDlg->IsCreate() && m_pTabScrollDlg->m_pComboBox_now_summon )
			{
				siComboIndex = m_pTabScrollDlg->m_pComboBox_now_summon->GetSelectedIndex();
				if( siComboIndex < 0 ) return FALSE;
				pTempChar = m_pTabScrollDlg->m_pComboBox_now_summon->GetText(siComboIndex);
				_tcscpy( TempSummonName, pTempChar );
			}
		}
		break;
	case 2:
		{
			if(m_pTabEvolveDlg && m_pTabEvolveDlg->IsCreate() && m_pTabEvolveDlg->m_pComboBox_now_summon )
			{
				siComboIndex = m_pTabEvolveDlg->m_pComboBox_now_summon->GetSelectedIndex();
				if( siComboIndex < 0 ) return FALSE;

				pTempChar = m_pTabEvolveDlg->m_pComboBox_now_summon->GetText(siComboIndex);
				_tcscpy( TempSummonName, pTempChar );
			}
		}
		break;
	}

	if(_tcslen(TempSummonName) >4)
	{
		StringCchCopy(CurrSummonName, txtSIze, &TempSummonName[3]);
		_tcsncpy(TempSummonIndex, TempSummonName, 1);
		SI32 siIndex = _tstoi(TempSummonIndex);
		siIndex--;
		
		*siSummonIndex = siIndex;
		return TRUE;
	}

	return FALSE;
}

//===================================================================
// ���� �����ϰ� �ִ� ��ȯ���� ����� Update�Ѵ�.
// 1�� �� ���� �ϰ��ִ� ��Ȳ������ �� �ƹ��� �
//=================================================================== 
void CNMudangDlg::UpdateCurrentSummonInfo( BOOL bALive)
{
	SI32 siCurIndex = -1;//SendDlgItemMessage( Item, CB_GETCURSEL, 0, 0);	
	//ComboDelete( Item);	

	CComboBox *pcb_Temp = NULL;
	TCHAR* pTempChar = NULL;

	switch( m_CurrentStatusPage )
	{
	case 0:
		{
			if(m_pTabReviveDlg && m_pTabReviveDlg->IsCreate() && m_pTabReviveDlg->m_pComboBox_now_summon )
			{
				siCurIndex = m_pTabReviveDlg->m_pComboBox_now_summon->GetSelectedIndex();
				//if( siCurIndex < 0 ) return ;

				pcb_Temp = m_pTabReviveDlg->m_pComboBox_now_summon;
			}
		}
		break;
	case 1:
		{
			if(m_pTabScrollDlg && m_pTabScrollDlg->IsCreate() && m_pTabScrollDlg->m_pComboBox_now_summon )
			{
				siCurIndex = m_pTabScrollDlg->m_pComboBox_now_summon->GetSelectedIndex();
				//if( siCurIndex < 0 ) return ;

				pcb_Temp = m_pTabScrollDlg->m_pComboBox_now_summon;
			}
		}
		break;
	case 2:
		{
			if(m_pTabEvolveDlg && m_pTabEvolveDlg->IsCreate() && m_pTabEvolveDlg->m_pComboBox_now_summon )
			{
				siCurIndex = m_pTabEvolveDlg->m_pComboBox_now_summon->GetSelectedIndex();
				//if( siCurIndex < 0 ) return ;

				pcb_Temp = m_pTabEvolveDlg->m_pComboBox_now_summon;
			}
		}
		break;
	case 3:
		{
		
		}
		break;
	}

	pcb_Temp->Clear();

	//===================================================================
	// bAlive ������ ����ִ� ��ȯ���� �׾� �ִ� ��ȯ����ϸ� �����Ѵ�.
	//===================================================================
	// ��ȯ���� Kind �̸��� ���´�.
	//===================================================================
	SI32 id = 1;
	TCHAR szName[128]=TEXT("");
	SI32 siSummonCount = 0;
	for(SI32 i = 0 ; i < MAX_SUMMON_OWN; ++i)
	{
		cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(i);
		if(pclSummon == NULL) return;
		//===================================================================
		// ���� �˻� 
		//===================================================================
		SI32 siKind = pclSummon->siKind;
		if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)		continue;
		
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[siKind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[siKind];
		}

		if(pclki == NULL)									continue;
		//===================================================================
		
		if(bALive)	// ����ִ� ��ȯ���� ü�µ� �ְ� TAKEOUT�Ǿ� �־���Ѵ�.
		{
			if(pclSummon->clIP.GetLife() <= 0)				continue;
			if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)continue;
		}
		if(!bALive)	// �׾��ִ� ��ȯ���� ü���� 0 �̰� DEAD�����̾���Ѵ�.
		{
			//if(pclSummon->clIP.GetLife() >  0)				continue;
			if(pclSummon->siStatus != SUMMON_STATUS_DEAD)	continue;
		}
		
		StringCchPrintf(szName, 128, TEXT("%d: %s"), i+1, pclClient->pclKindInfoSet->pclKI[siKind]->GetName());
		// ��������� �����ϴ� ��ȯ���� �߰��Ѵ�.

		stComboBoxItemData	stcb_Temp;
		stcb_Temp.Init();
		stcb_Temp.Set( szName );
		pcb_Temp->AddItem( &stcb_Temp );
		//ComboAddString( Item, (LPARAM)szName);
		siSummonCount++;
	}

	// ���� �����ΰ��� ��� ���ٸ� ��ó���� ����Ű���� �Ѵ�.
	if(siCurIndex == -1)		 siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;
	pcb_Temp->SetCursel( siCurIndex );
	pcb_Temp->Refresh();

	//SendDlgItemMessage( Item, CB_SETCURSEL, siCurIndex, 0);	
}

//===================================================================
// �������� ��ȭ�� ��ȯ�� ����� ǥ���Ѵ�. 
// ������ Kind�� Rank���� 1�� ���⸸ �ϸ� �ȴ�.
//===================================================================
void CNMudangDlg::UpdateEvolveSummonInfo()
{
	if(m_pTabEvolveDlg == NULL || m_pTabEvolveDlg->m_pList_new_summon == NULL ) return;
	//SI32 siCurIndex = SendDlgItemMessage( Item, LB_GETCURSEL, 0, 0);	
	//ListDelete( Item);

	stListBoxItemData stlb_List;

	if(m_pTabEvolveDlg->m_pList_new_summon == NULL) return;
	SI32 siCurIndex = m_pTabEvolveDlg->m_pList_new_summon->GetSelectedIndex();
	m_pTabEvolveDlg->m_pList_new_summon->Clear();
	m_pTabEvolveDlg->m_pList_new_summon->Refresh();


	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE) return;

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	
	//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	cltKindInfo* pclki = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclClient->pclKindInfoSet->pclSummonKI[siKind];
	}
	else
	{
		pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	}

	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 0)					return;
	if( pclki->bSummonMall == TRUE)					return; // �����۸����� �Ĵ� ��ȯ�����̶�� ��ȭ �ȵ�.
	SI32 siCurrentRank = pclki->siSummonRank;
	//===================================================================

	SI32 siSummonCount = 0;
	// MONSTER �����߿��� ���� ��ȯ������ 1�ܰ� ���� ��ȭ����� ã�´�.
	for ( SI32 i = 1; i < MAX_KIND_NUMBER; ++i )
	{
		if( pclClient->pclKindInfoSet->pclKI[i] &&
		    pclClient->pclKindInfoSet->pclKI[i]->siSummonRank == siCurrentRank+1 &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank <= LIMIT_SUMMON_RANK_EVOLVE &&
			pclClient->pclKindInfoSet->pclKI[i]->bSummonMall != TRUE)   // �̺κ� �� ����� ��ȯ�������� ��ȭ �ȴ�.
		{
			stlb_List.Init();
			stlb_List.Set( 0, (TCHAR*)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			m_pTabEvolveDlg->m_pList_new_summon->AddItem( &stlb_List );
			//ListAddString( Item, (LPARAM)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			siSummonCount++;
		}
	}

	m_pTabEvolveDlg->m_pList_new_summon->Refresh();

	if(siCurIndex == LB_ERR)		siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;
	
	m_pTabEvolveDlg->m_pList_new_summon->SetSelectIndex( siCurIndex );
	//SendDlgItemMessage( Item, LB_SETCURSEL, siCurIndex, 0);	
}

//===================================================================
// �������� ��ȭ�� ��ȯ�� ����� ǥ���Ѵ�. 
// ������ Kind�� Rank���� 1�� ���⸸ �ϸ� �ȴ�.
//===================================================================
void CNMudangDlg::UpdateDevolutionSummonInfo()
{
	if(m_pTabEvolveDlg == NULL || m_pTabEvolveDlg->m_pList_new_summon == NULL ) return;
	//SI32 siCurIndex = SendDlgItemMessage(Item, LB_GETCURSEL, 0, 0);	
	//ListDelete(Item);	

	stListBoxItemData stlb_List;

	if(m_pTabEvolveDlg->m_pList_new_summon == NULL) return;
	SI32 siCurIndex = m_pTabEvolveDlg->m_pList_new_summon->GetSelectedIndex();
	m_pTabEvolveDlg->m_pList_new_summon->Clear();
	m_pTabEvolveDlg->m_pList_new_summon->Refresh();

	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE) return;

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	
	//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	cltKindInfo* pclki = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclClient->pclKindInfoSet->pclSummonKI[siKind];
	}
	else
	{
		pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	}


	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 1)					return;
	if( pclki->bSummonMall == TRUE)					return; // �����۸����� �Ĵ� ��ȯ�����̶�� ��ȭ �ȵ�.
	SI32 siCurrentRank = pclki->siSummonRank;
	//===================================================================

	SI32 siSummonCount = 0;
	// MONSTER �����߿��� ���� ��ȯ������ 1�ܰ� ���� ��ȭ����� ã�´�.
	for ( SI32 i = 1; i < MAX_KIND_NUMBER; ++i )
	{
		if( pclClient->pclKindInfoSet->pclKI[i] &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank == siCurrentRank-1 &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank <= LIMIT_SUMMON_RANK_EVOLVE &&
			pclClient->pclKindInfoSet->pclKI[i]->bSummonMall != TRUE)   // �̺κ� �� ����� ��ȯ�������� ��ȭ �ȴ�.
		{
			stlb_List.Init();
			stlb_List.Set( 0, (TCHAR*)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			m_pTabEvolveDlg->m_pList_new_summon->AddItem( &stlb_List );
			//ListAddString(Item, (LPARAM)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			siSummonCount++;
		}
	}

	m_pTabEvolveDlg->m_pList_new_summon->Refresh();

	if(siCurIndex == LB_ERR)		siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;

	m_pTabEvolveDlg->m_pList_new_summon->SetSelectIndex( siCurIndex );
	//SendDlgItemMessage(Item, LB_SETCURSEL, siCurIndex, 0);	
}

//===================================================================
// ���� ������� ��ȯ�� ��ȯ�� ����� ǥ���Ѵ�. 
// ������ Kind�� Rank�� ���� �ڱ�� ���� kind�� �ƴϸ� �ȴ�.
//===================================================================
void CNMudangDlg::UpdateTransformSummonInfo()
{
	if(m_pTabEvolveDlg == NULL || m_pTabEvolveDlg->m_pList_new_summon == NULL ) return;
	//SI32 siCurIndex = SendDlgItemMessage(Item, LB_GETCURSEL, 0, 0);	
	//ListDelete(Item);	
	stListBoxItemData stlb_List;

	if(m_pTabEvolveDlg->m_pList_new_summon == NULL) return;
	SI32 siCurIndex = m_pTabEvolveDlg->m_pList_new_summon->GetSelectedIndex();
	m_pTabEvolveDlg->m_pList_new_summon->Clear();
	m_pTabEvolveDlg->m_pList_new_summon->Refresh();

	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(CurrSummonName, 60, &siSummonIndex) == FALSE) return;

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	
	//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	cltKindInfo* pclki = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclClient->pclKindInfoSet->pclSummonKI[siKind];
	}
	else
	{
		pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	}


	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 0)					return;
	SI32 siCurrentRank = pclki->siSummonRank;
	if( pclki->bSummonMall == TRUE)					return; // �����۸����� �Ĵ� ��ȯ�����̶�� ��ȭ �ȵ�.
	//===================================================================

	SI32 siSummonCount = 0;
	// MONSTER �����߿��� ���� ��ȯ������ 1�ܰ� ���� ��ȭ����� ã�´�.
	for ( SI32 i = 1; i < MAX_KIND_NUMBER; ++i )
	{
		if( i != siKind && pclClient->pclKindInfoSet->pclKI[i] &&
		    pclClient->pclKindInfoSet->pclKI[i]->siSummonRank == siCurrentRank &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank <= LIMIT_SUMMON_RANK_EVOLVE &&
			pclClient->pclKindInfoSet->pclKI[i]->bSummonMall != TRUE)   // �̺κ� �� ����� ��ȯ�������� ��ȭ �ȴ�.
		{
			stlb_List.Init();
			stlb_List.Set( 0, (TCHAR*)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			m_pTabEvolveDlg->m_pList_new_summon->AddItem( &stlb_List );
			//ListAddString(Item, (LPARAM)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			siSummonCount++;
		}
	}

	m_pTabEvolveDlg->m_pList_new_summon->Refresh();

	if(siCurIndex == LB_ERR)		siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;

	m_pTabEvolveDlg->m_pList_new_summon->SetSelectIndex( siCurIndex );
	//SendDlgItemMessage(Item, LB_SETCURSEL, siCurIndex, 0);	
}


//===================================================================
//
//===================================================================
void CNMudangDlg::UpdateScrollSummonInfo()
{
	if(m_pTabScrollDlg == NULL ) return;
	if(m_pTabScrollDlg->m_pRadioButton_have_scroll_1 == NULL ) return;
	if(m_pTabScrollDlg->m_pStatic_scroll_percent_1 == NULL ) return;
	if(m_pTabScrollDlg->m_pRadioButton_have_scroll_2 == NULL ) return;
	if(m_pTabScrollDlg->m_pStatic_scroll_percent_2 == NULL ) return;

	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		m_pTabScrollDlg->m_pRadioButton_have_scroll_1->SetText( TEXT(""), DT_LEFT | DT_VCENTER);
		m_pTabScrollDlg->m_pStatic_scroll_percent_1->SetText( TEXT(""), DT_LEFT | DT_VCENTER);
		m_pTabScrollDlg->m_pRadioButton_have_scroll_2->SetText( TEXT(""), DT_LEFT | DT_VCENTER);
		m_pTabScrollDlg->m_pStatic_scroll_percent_2->SetText( TEXT(""), DT_LEFT | DT_VCENTER);
		//CheckRadioButton(  IDC_RADIO_HAVE_SCROLL_1, IDC_RADIO_HAVE_SCROLL_2, IDC_RADIO_HAVE_SCROLL_1 );
		m_pTabScrollDlg->m_pRadioButton_have_scroll_1->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );
		m_siActiveScrollIndex   = 0;
		return;
	}

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon ->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	
	//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	cltKindInfo* pclki = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclClient->pclKindInfoSet->pclSummonKI[siKind];
	}
	else
	{
		pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	}

	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 0)					return;
	//===================================================================
	// ���� ������ �ɷ��� �����ش�.
	SI32 siUnique  = 0;
	SI32 siPercent = 0;
	TCHAR ScrollName[60] = TEXT("");
	TCHAR PercentString[30] = TEXT("");
	for(SI32 i = 0; i < MAX_SCROLL_SUMMON_PER_KIND; ++i)
	{
		siUnique  = pclSummon->clScroll.siUnique[i];
		siPercent = pclSummon->clScroll.siPercent[i];

		if(siUnique && pclClient->pclItemManager->GetName(siUnique))	
		{
			StringCchCopy(ScrollName, 60, pclClient->pclItemManager->GetName(siUnique));
			StringCchPrintf(PercentString, 30, TEXT("%0.1f%%"), (float)(siPercent/10.0)); 
		}
		else
		{
			StringCchCopy(ScrollName, 60, TEXT(""));	
			StringCchCopy(PercentString, 30, TEXT("")); 
		}
	
		switch(i)
		{
		case 0:	
			{
				//SetWindowText(GetDlgItem( IDC_RADIO_HAVE_SCROLL_1),	ScrollName); 
				//SetWindowText(GetDlgItem( IDC_STATIC_SCROLL_PERCENT_1),PercentString); 
				m_pTabScrollDlg->m_pRadioButton_have_scroll_1->SetText( ScrollName, DT_LEFT | DT_VCENTER);
				m_pTabScrollDlg->m_pStatic_scroll_percent_1->SetText( PercentString, DT_LEFT | DT_VCENTER);
			}
			break;
		case 1:	
			{
				//SetWindowText(GetDlgItem( IDC_RADIO_HAVE_SCROLL_2),	ScrollName); 
				//SetWindowText(GetDlgItem( IDC_STATIC_SCROLL_PERCENT_2),PercentString); 
				m_pTabScrollDlg->m_pRadioButton_have_scroll_2->SetText( ScrollName, DT_LEFT | DT_VCENTER);
				m_pTabScrollDlg->m_pStatic_scroll_percent_2->SetText( PercentString, DT_LEFT | DT_VCENTER);
			}
			break;
		}
	}

	m_bChangedScrollPercent = FALSE;
}

void CNMudangDlg::UpdateEquipItwmInfo()
{
	m_pTabEquipitemDlg->Showsummonstatus();
}
//--------------------------------
// ��Ȱ �޽����� �����Ѵ�.
//--------------------------------
BOOL CNMudangDlg::SendSummonReviveMessageToServer( SI32 id)
{
	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;

	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	TCHAR buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE )
		{
			TCHAR* pText = GetTxtFromMgr(2277);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2278);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];	
	if( pclSummon &&
		//pclSummon->clIP.GetLife() <= 0 &&
		pclSummon->siStatus == SUMMON_STATUS_DEAD)
	{
		//--------------------------------
		// ��Ȱ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = pclSummon->siKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[kind];
		}

		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;
		if(pclki->bSummonMall == TRUE)				return FALSE;// ��ȯ���� �����۸� ��ȯ���ϰ�쿡�� ��Ȱ�Ҽ� ����,.
		
		//--------------------------------
		// ��Ȱ��Ű������ �غ� ����
		//--------------------------------
		SI32 siSuccess = 1;
		SI32 siDollPos = 0;
		SI32 siDollUnique = pclClient->pclItemManager->GetItemDollUnique(kind);
		SI32 siDollNum   =  pclSummon->clIP.GetLevel();
		if(siDollUnique <= 0 || siDollNum	<= 0)	return FALSE;
		
		siDollPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siDollUnique);
		if( siDollPos >= PERSONITEM_INV0 && siDollPos < MAX_ITEM_PER_PERSON )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siDollPos].siItemNum >= siDollNum)
			{
				cltGameMsgRequest_SummonRevive clInfo(pclClient->pclCM->CR[id]->GetCharUnique(), pclSummon->siSummonID, SUMMON_REVIVE_DOLL);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONREVIVE, sizeof(clInfo), (BYTE*)&clInfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

				DisplayMessage(-1, TEXT(""));
				return TRUE;
			}
		}
		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(2279);
			StringCchPrintf(buffer, 256, pText,  
				pclClient->pclItemManager->GetName(siDollUnique) , siDollNum );
			DisplayMessage(FALSE, buffer);
		}
		
	}
	else
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(2280);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
	}

	return FALSE;
}



BOOL CNMudangDlg::SendSummonEvolveMessageToServer(SI32 id)
{

	if(m_pTabEvolveDlg == NULL || m_pTabEvolveDlg->m_pList_new_summon == NULL ) return FALSE;
	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;
	
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	TCHAR buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			TCHAR* pText = GetTxtFromMgr(2281);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2282);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	if ( TRUE == pclClient->pclCM->CR[id]->pclCI->clSummonInfo.IsHaveEquipItem(siSummonIndex) )
	{	
		TCHAR* pText = GetTxtFromMgr(8644);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
		return FALSE;
	}

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;
	
	//============================================
	// LIST BOX���� ���� ��ȭ�� SUMMON�� ���´�.
	//============================================
	TCHAR NewSummonName[256] = TEXT("");
	//ListGetString( IDC_LIST_NEW_SUMMON, (LPARAM)NewSummonName);
	TCHAR *pchTmp = NULL;
	SI16 siTmpRow = -1, siTmpColumn = -1;
	m_pTabEvolveDlg->m_pList_new_summon->GetSelectedIndex( &siTmpRow, &siTmpColumn );
	pchTmp = m_pTabEvolveDlg->m_pList_new_summon->GetText( siTmpRow, siTmpColumn );
	if(pchTmp == NULL ) return FALSE;
	_tcscpy( NewSummonName, pchTmp );

	if(_tcslen(NewSummonName)<=0)
	{
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[siCurrSummonKind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		}

		if(pclki != NULL && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE)
		{
			TCHAR* pText = GetTxtFromMgr(2283);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2284);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
		}
		return FALSE;
	}

	SI32 siNewSummonKind = pclClient->pclKindInfoSet->FindKindFromName( NewSummonName );
	if(siNewSummonKind <= 0 || siNewSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	if(pclClient->pclKindInfoSet->pclKI[siNewSummonKind] == NULL)	return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT)
	{
		//--------------------------------
		// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;

		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[kind];
		}

		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//============================================
		// ��ȭ LEVEL���� ���� 
		//============================================
		if(pclSummon->clIP.GetLevel() < pclki->siEvolveLevel)
		{
			TCHAR* pText = GetTxtFromMgr(2285);
			StringCchPrintf(buffer, 256, pText, pclki->siEvolveLevel);
			DisplayMessage(FALSE,  buffer);
			return FALSE;
		}

		//--------------------------------
		// ��ȭ�Ǿ��� ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 newkind = siNewSummonKind;
		if(newkind <= 0 || newkind >= MAX_KIND_NUMBER)	return FALSE;
		
		//cltKindInfo* pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		cltKindInfo* pclnewki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclnewki = pclClient->pclKindInfoSet->pclSummonKI[newkind];
		}
		else
		{
			pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		}

		if(pclnewki == NULL)									return FALSE;
		if(pclnewki->siSummonRank != pclki->siSummonRank+1)		return FALSE;
		if(pclnewki->bSummonMall == TRUE ) return FALSE; // ��ȯ�������δ� �ȵȴ�.
		if(pclnewki->siSummonRank > LIMIT_SUMMON_RANK_EVOLVE)	
		{
			TCHAR* pText = GetTxtFromMgr(2283);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		
		//--------------------------------
		// ��ȭ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siTicketPos	= 0;
		SI32 siTicketUnique = GetSummonTicketUnique(pclki->siSummonRank);		// �ູ�ǵ�


		SI32 siTicketNum    = GetSummonTicketNum(pclki->siSummonRank);
		if(siTicketUnique <= 0 || siTicketNum	<= 0)	return FALSE;
		
		SI32 itemnum = GetSummonTicketNum(pclki->siSummonRank) ;
		SI16 questtype, questunique, para1, para2;
		SI16 questclearcond =  QUEST_CLEAR_COND_SUMMONEVOLUTIONRANK;

		if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
		{
			siTicketNum = 0 ;
		}

		questclearcond =  QUEST_CLEAR_COND_SUMMONEVOLUTION;
		if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
		{
			siTicketNum = 0 ;
		}


		siTicketPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siTicketUnique);

		if ( siTicketNum )
		{
			if( siTicketPos >= PERSONITEM_INV0 && siTicketPos < MAX_ITEM_PER_PERSON )	
			{
				if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siTicketPos].siItemNum >= siTicketNum)
				{
					cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(), pclSummon->siSummonID, newkind);
					cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (BYTE*)&clInfo);
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

					DisplayMessage(-1, TEXT(""));
					return TRUE;
				}
			}
		}
		else
		{
			cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(), pclSummon->siSummonID, newkind);
			cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (BYTE*)&clInfo);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

			DisplayMessage(-1, TEXT(""));
			return TRUE;
		}

		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(2286);
			StringCchPrintf(buffer, 256, pText,  
				pclClient->pclItemManager->GetName(siTicketUnique) , siTicketNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(2287);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CNMudangDlg::SendSummonDevolutionMessageToServer( SI32 id)
{
	if(m_pTabEvolveDlg == NULL || m_pTabEvolveDlg->m_pList_new_summon == NULL ) return FALSE;
	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;

	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	TCHAR buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			TCHAR* pText = GetTxtFromMgr(2281);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2282);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	if ( TRUE == pclClient->pclCM->CR[id]->pclCI->clSummonInfo.IsHaveEquipItem(siSummonIndex) )
	{	
		TCHAR* pText = GetTxtFromMgr(8644);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
		return FALSE;
	}

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;

	//============================================
	// LIST BOX���� ���� ��ȭ�� SUMMON�� ���´�.
	//============================================
	TCHAR NewSummonName[256] = TEXT("");
	//ListGetString(IDC_LIST_NEW_SUMMON, (LPARAM)NewSummonName);
	TCHAR *pchTmp = NULL;
	SI16 siTmpRow = -1, siTmpColumn = -1;
	m_pTabEvolveDlg->m_pList_new_summon->GetSelectedIndex( &siTmpRow, &siTmpColumn );
	pchTmp = m_pTabEvolveDlg->m_pList_new_summon->GetText( siTmpRow, siTmpColumn );
	if(pchTmp == NULL ) return FALSE;
	_tcscpy( NewSummonName, pchTmp );

	if(_tcslen(NewSummonName)<=0)
	{
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[siCurrSummonKind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		}

		if(pclki != NULL && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE)
		{
			TCHAR* pText = GetTxtFromMgr(2283);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2284);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
		}
		return FALSE;
	}


	SI32 siNewSummonKind = pclClient->pclKindInfoSet->FindKindFromName( NewSummonName );
	if(siNewSummonKind <= 0 || siNewSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	if(pclClient->pclKindInfoSet->pclKI[siNewSummonKind] == NULL)	return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT)
	{
		//--------------------------------
		// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[kind];
		}

		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//--------------------------------
		// ��ȭ�Ǿ��� ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 newkind = siNewSummonKind;
		if(newkind <= 0 || newkind >= MAX_KIND_NUMBER)	return FALSE;
		
		//cltKindInfo* pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		cltKindInfo* pclnewki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclnewki = pclClient->pclKindInfoSet->pclSummonKI[newkind];
		}
		else
		{
			pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		}

		if(pclnewki == NULL)									return FALSE;
		if(pclnewki->siSummonRank != pclki->siSummonRank-1)		return FALSE;
		if(pclnewki->bSummonMall == TRUE ) return FALSE; // ��ȯ�������δ� �ȵȴ�.
		if(pclnewki->siSummonRank <= 0 ) return FALSE ;

		//--------------------------------
		// ��ȭ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siTicketPos	= 0;
		SI32 siTicketUnique = ITEMUNIQUE(5370);		// �ູ�ǵ�
		SI32 siTicketNum    = 10;
		if(siTicketUnique <= 0 || siTicketNum	<= 0)	return FALSE;

		siTicketPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siTicketUnique);

		if( siTicketPos >= PERSONITEM_INV0 && siTicketPos < MAX_ITEM_PER_PERSON )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siTicketPos].siItemNum >= siTicketNum)
			{
				cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(),
					pclSummon->siSummonID, newkind,SUMMONEVOLVE_DEVOLUTION);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (BYTE*)&clInfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

				DisplayMessage(-1, TEXT(""));
				return TRUE;
			}
		}

		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(2286);
			StringCchPrintf(buffer, 256, pText,  
				pclClient->pclItemManager->GetName(siTicketUnique) , siTicketNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(2287);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CNMudangDlg::SendSummonTransformMessageToServer( SI32 id)
{
	if(m_pTabEvolveDlg == NULL || m_pTabEvolveDlg->m_pList_new_summon == NULL ) return FALSE;
	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;

	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	TCHAR buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			TCHAR* pText = GetTxtFromMgr(2281);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2282);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	if ( TRUE == pclClient->pclCM->CR[id]->pclCI->clSummonInfo.IsHaveEquipItem(siSummonIndex) )
	{	
		TCHAR* pText = GetTxtFromMgr(8644);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
		return FALSE;
	}

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;

	//============================================
	// LIST BOX���� ���� ��ȭ�� SUMMON�� ���´�.
	//============================================
	TCHAR NewSummonName[256] = TEXT("");
	//ListGetString(IDC_LIST_NEW_SUMMON, (LPARAM)NewSummonName);
	TCHAR *pchTmp = NULL;
	SI16 siTmpRow = -1, siTmpColumn = -1;
	m_pTabEvolveDlg->m_pList_new_summon->GetSelectedIndex( &siTmpRow, &siTmpColumn );
	pchTmp = m_pTabEvolveDlg->m_pList_new_summon->GetText( siTmpRow, siTmpColumn );
	if(pchTmp == NULL ) return FALSE;
	_tcscpy( NewSummonName, pchTmp );

	if(_tcslen(NewSummonName)<=0)
	{
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[siCurrSummonKind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		}

		if(pclki != NULL && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE)
		{
			TCHAR* pText = GetTxtFromMgr(2283);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2284);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
		}
		return FALSE;
	}


	SI32 siNewSummonKind = pclClient->pclKindInfoSet->FindKindFromName( NewSummonName );
	if(siNewSummonKind <= 0 || siNewSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	if(pclClient->pclKindInfoSet->pclKI[siNewSummonKind] == NULL)	return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT)
	{
		//--------------------------------
		// ��ȯ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[kind];
		}


		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//--------------------------------
		// ��ȯ�Ǿ��� ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 newkind = siNewSummonKind;
		if(newkind <= 0 || newkind >= MAX_KIND_NUMBER)	return FALSE;
		
		//cltKindInfo* pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		cltKindInfo* pclnewki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclnewki = pclClient->pclKindInfoSet->pclSummonKI[newkind];
		}
		else
		{
			pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		}

		if(pclnewki == NULL)									return FALSE;
		if(pclnewki->siSummonRank != pclki->siSummonRank)		return FALSE;
		if(pclnewki->bSummonMall == TRUE ) return FALSE; // ��ȯ�������δ� �ȵȴ�.

		//--------------------------------
		// ��ȯ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siTicketPos	= 0;
		SI32 siTicketUnique = ITEMUNIQUE(5370);		// �ູ�ǵ�
		SI32 siTicketNum    = 10;//GetSummonTicketNum(pclki->siSummonRank);
		if(siTicketUnique <= 0 || siTicketNum	<= 0)	return FALSE;

		siTicketPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siTicketUnique);

		if( siTicketPos >= PERSONITEM_INV0 && siTicketPos < MAX_ITEM_PER_PERSON )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siTicketPos].siItemNum >= siTicketNum)
			{
				cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(),
					pclSummon->siSummonID, newkind,SUMMONEVOLVE_TRANSFORM);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (BYTE*)&clInfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

				DisplayMessage(-1, TEXT(""));
				return TRUE;
			}
		}

		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(2286);
			StringCchPrintf(buffer, 256, pText,  
				pclClient->pclItemManager->GetName(siTicketUnique) , siTicketNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(2287);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CNMudangDlg::SendSummonScrollMessageToServer( SI32 id)
{
	if(m_pTabScrollDlg == NULL ) return FALSE;
	if(m_pTabScrollDlg->m_pRadioButton_have_scroll_1 == NULL ) return FALSE;
	if(m_pTabScrollDlg->m_pStatic_scroll_percent_1 == NULL ) return FALSE;
	if(m_pTabScrollDlg->m_pRadioButton_have_scroll_2 == NULL ) return FALSE;
	if(m_pTabScrollDlg->m_pStatic_scroll_percent_2 == NULL ) return FALSE;

	// 500 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 500) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;

	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	TCHAR buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE )
		{
			TCHAR* pText = GetTxtFromMgr(2288);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2289);
			StringCchPrintf(buffer, 256, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;
	
	//============================================
	// LISTVIEW���� ���� ��ȭ��ų �ɷ��� ���´�.
	//============================================
	SI32 siCurrentCheckedIndex = -1;

	if(m_pTabScrollDlg->m_pRadioButton_have_scroll_1->IsCheck() == true)
	{
		siCurrentCheckedIndex = 0;
	}
	else if(m_pTabScrollDlg->m_pRadioButton_have_scroll_2->IsCheck() == true)
	{
		siCurrentCheckedIndex = 1;
	}
	
	if(		(m_siActiveScrollIndex<0 || m_siActiveScrollIndex>=MAX_SCROLL_SUMMON_PER_KIND)
		||	(siCurrentCheckedIndex != m_siActiveScrollIndex))
	{
		TCHAR* pText = GetTxtFromMgr(2290);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
		return FALSE;
	}
	//============================================
	// UNIQUE ���� 
	//============================================
	SI32 siScrollUnique = pclSummon->clScroll.siUnique[m_siActiveScrollIndex] ;
	SI32 siScrollPercent= pclSummon->clScroll.siPercent[m_siActiveScrollIndex];
	
	if(siScrollUnique == 0)
	{
		TCHAR* pText = GetTxtFromMgr(2290);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
		return FALSE;
	}

	// �������� �������� Ȯ���Ѵ�. 
	SI64 atb = pclClient->pclItemManager->GetItemAtb(siScrollUnique);
	if((atb & ITEMATB_SCROLL) ==0)		return FALSE;

	// ������ ������ Ȯ���Ѵ�. 
	cltItemInfo* pclscrollinfo = pclClient->pclItemManager->FindItemInfo(siScrollUnique);
	if(pclscrollinfo == NULL)			return FALSE;

	// ������ ����� Ȯ���Ѵ�. 
	SI32 function	= pclscrollinfo->siScrollFunction;
	if(function <= 0)					return FALSE;

	// ������ ���� �ɷ��� ���Ѵ�.
	SI32 ability	= pclscrollinfo->siScrollAbility;
	if(ability <= 0)					return FALSE;

	//============================================
	// ���� ��ȭ % ���� 
	//============================================
	SI32 siMaxSrollPercent = min(LIMIT_SUMMON_ADD_SCROLL_PERCENT, pclSummon->clIP.GetLevel()*10/2 );
	if(siScrollPercent >= siMaxSrollPercent)
	{
		TCHAR* pText = GetTxtFromMgr(2291);
		StringCchPrintf(buffer, 256, pText, LIMIT_SUMMON_ADD_SCROLL_PERCENT);
		DisplayMessage(FALSE,  buffer);
		return FALSE;
	}

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT )
	{
		//--------------------------------
		// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		
		//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[kind];
		}

		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//--------------------------------
		// ��ȭ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siScrollPos	= 0;
		SI32 siScrollNum    = 1;					// ���� ���� 
		if(siScrollUnique <= 0 || siScrollNum	<= 0)	return FALSE;
		
		siScrollPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siScrollUnique);
		if( siScrollPos >= PERSONITEM_INV0 && siScrollPos < MAX_ITEM_PER_PERSON )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siScrollPos].siItemNum >= siScrollNum)
			{
				cltGameMsgRequest_SummonScroll clInfo(pclClient->pclCM->CR[id]->GetCharUnique(), pclSummon->siSummonID, siScrollUnique);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONSCROLL, sizeof(clInfo), (BYTE*)&clInfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				DisplayMessage(-1, TEXT(""));
				return TRUE;
			}
		}
		
		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(2286);
			StringCchPrintf(buffer, 256, pText,  
				pclClient->pclItemManager->GetName(siScrollUnique) , siScrollNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(2292);
		StringCchPrintf(buffer, 256, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CNMudangDlg::DisplayMessage(BOOL bSuccess, TCHAR *pStr)
{
	if(m_pEdit_message)
	{
		if(bSuccess == TRUE)		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_SUCCESS")), 0, 0);
		else if(bSuccess == FALSE)	pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);	
		
		m_pEdit_message->SetText( pStr );
	}

	return TRUE;
}

void CNMudangDlg::UpdateReviveMent()
{
	if(m_pTabReviveDlg == NULL || m_pTabReviveDlg->m_pEdit_summon_revive_explain == NULL ) return;

	TCHAR buffer[512];
	
	SI32 id = 1;
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;

	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			TCHAR* pText = GetTxtFromMgr(2277);
			StringCchPrintf(buffer, 512, pText);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2293);
			StringCchPrintf(buffer, 512, pText);
		}

		m_pTabReviveDlg->m_pEdit_summon_revive_explain->SetText( buffer );
	}
	else
	{
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
		if(pclSummon)
		{
			//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[pclSummon->siKind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			}

			if(pclki && pclSummon->clIP.GetLife()<=0)
			{
				if(pclSummon->siStatus == SUMMON_STATUS_DEAD)
				{
					if ( pclki->bSummonMall == false)// �����۸� ��ȯ���� �ƴҶ���
					{
						TCHAR* pText = GetTxtFromMgr(2294);
						TCHAR num[128]= TEXT(" ") ;
						StringCchPrintf(num, 128, TEXT("%d"),pclSummon->clIP.GetLevel());
						Nsprintf(buffer,pText,TEXT("monster"),    pclki->GetName(),TEXT("num"), num   ,NULL);
						//sprintf(buffer, pText,
						//	pclki->GetName(),
						//	pclSummon->clIP.GetLevel()
						//	);
					}// �����۸� ��ȯ���� ���
					else{
						TCHAR* pText = GetTxtFromMgr(8577);
						StringCchPrintf(buffer, 512, pText);

					}

				}
				else
				{
					TCHAR* pText = GetTxtFromMgr(2295);
					StringCchPrintf(buffer, 512, pText);
				}
				
				m_pTabReviveDlg->m_pEdit_summon_revive_explain->SetText( buffer );
			}
		}
	}

}

void CNMudangDlg::UpdateEvolveMent()
{
	if(m_pTabEvolveDlg == NULL || m_pTabEvolveDlg->m_pEdit_summon_evolve_explain == NULL )
		return ;

	TCHAR buffer[512]=TEXT("");
	cltClient *pclclient = (cltClient*)pclClient;

	SI32 id = 1;
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;

	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			TCHAR* pText = GetTxtFromMgr(2277);
			StringCchPrintf(buffer, 512, pText);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2282);
			StringCchPrintf(buffer, 512, pText);
		}
		m_pTabEvolveDlg->m_pEdit_summon_evolve_explain->SetText( buffer );
	}
	else
	{
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
		if(pclSummon)
		{
			//cltKindInfo* pclki	 = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[pclSummon->siKind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			}

			if(pclki && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE && m_siSelectEvolveDlg == SUMMONEVOLVE_EVOLVE)
			{
				TCHAR* pText = GetTxtFromMgr(2296);
				StringCchPrintf(buffer, 512, pText);
				
				m_pTabEvolveDlg->m_pEdit_summon_evolve_explain->SetText( buffer );
			}
			else if(pclki && pclSummon->clIP.GetLevel() >= pclki->siEvolveLevel && m_siSelectEvolveDlg == SUMMONEVOLVE_EVOLVE)
			{
				SI32 itemnum = GetSummonTicketNum(pclki->siSummonRank) ;
		 		SI16 questtype, questunique, para1, para2;
				SI16 questclearcond =  QUEST_CLEAR_COND_SUMMONEVOLUTION;

				if(pclclient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
				{
					itemnum -= 1 ;
				}

				TCHAR* pText = NULL ;
				TCHAR* pItem = (TCHAR*)pclClient->pclItemManager->GetName(GetSummonTicketUnique(pclki->siSummonRank));
				if(pItem == NULL) return;

				if ( itemnum )
				{
					// ��ȭ
					if ( pclki->bSummonMall == false ) {
										// ��ȭ
						pText = GetTxtFromMgr(2297);
							TCHAR num[128]= TEXT(" ") ;
						StringCchPrintf(num, 128, TEXT("%d"),itemnum);

						Nsprintf(buffer,pText,TEXT("monster"),  pItem ,TEXT("num"), num   ,NULL);
						//sprintf(buffer,pText,pclClient->pclItemManager->GetName(14050),itemnum);
					}
					else{
						TCHAR* pText = GetTxtFromMgr(8578);
						StringCchPrintf(buffer, 512, pText);
					}
				}
				else
				{
					// ��ȭ
					if ( pclki->bSummonMall == false ) {

						pText = GetTxtFromMgr(3194);
						StringCchPrintf(buffer, 512, pText, pItem);
					}
					else{
						TCHAR* pText = GetTxtFromMgr(8578);
						StringCchPrintf(buffer, 512, pText);
					}
				}

				m_pTabEvolveDlg->m_pEdit_summon_evolve_explain->SetText( buffer );
			}
			else if( m_siSelectEvolveDlg == SUMMONEVOLVE_EVOLVE)
			{
				if ( pclki->bSummonMall == false ) {
					TCHAR* pText = GetTxtFromMgr(2298);
					StringCchPrintf(buffer, 512, pText, pclki->siEvolveLevel);


				}
				else{
					TCHAR* pText = GetTxtFromMgr(8578);
					StringCchPrintf(buffer, 512, pText);
				}
				
				m_pTabEvolveDlg->m_pEdit_summon_evolve_explain->SetText( buffer );
			}
			else if ( m_siSelectEvolveDlg == SUMMONEVOLVE_DEVOLUTION )
			{
			// ��ȭ
				if ( pclki->bSummonMall == false ) {
					TCHAR* pText = GetTxtFromMgr(3284);
					TCHAR num[128]= TEXT(" ");
					StringCchPrintf(num, 128, TEXT("%d"),10);
					TCHAR* pItem = GetTxtFromMgr(6236);
					Nsprintf(buffer,pText,TEXT("item"), pItem   ,TEXT("num"),  num  ,NULL);
				}
				else{
					TCHAR* pText = GetTxtFromMgr(8579);
					StringCchPrintf(buffer, 512, pText);

				}
				//sprintf(buffer,pText,pclClient->pclItemManager->GetName(ITEMUNIQUE(5370)),1);
				m_pTabEvolveDlg->m_pEdit_summon_evolve_explain->SetText( buffer );
			}
			else if ( m_siSelectEvolveDlg == SUMMONEVOLVE_TRANSFORM )
			{
				//��ȭ
				if ( pclki->bSummonMall == false ) {
					TCHAR* pText = GetTxtFromMgr(3285);
					TCHAR num[128]= TEXT(" ") ;

					StringCchPrintf(num, 128, TEXT("%d"),10);
					TCHAR* pItem = GetTxtFromMgr(6236);
					Nsprintf(buffer,pText,TEXT("item"), pItem   ,TEXT("num"),  num  ,NULL);
				}
				else
				{
					TCHAR* pText = GetTxtFromMgr(8580);
					StringCchPrintf(buffer, 512, pText);

				}

//				sprintf(buffer,pText,pclClient->pclItemManager->GetName(ITEMUNIQUE(5370)),1);


				m_pTabEvolveDlg->m_pEdit_summon_evolve_explain->SetText( buffer );
			}
		}
	}
	
}


void CNMudangDlg::UpdateScrollMent()
{
	if(m_pTabScrollDlg == NULL || m_pTabScrollDlg->m_pEdit_summon_scroll_explain == NULL )
		return;

	TCHAR buffer[512]= TEXT("");
	
	SI32 id = 1;
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;

	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	TCHAR CurrSummonName[60] = TEXT("");
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex( CurrSummonName, 60, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			TCHAR* pText = GetTxtFromMgr(2277);
			StringCchPrintf(buffer, 512, pText);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(2289);
			StringCchPrintf(buffer, 512, pText);
		}
		m_pTabScrollDlg->m_pEdit_summon_scroll_explain->SetText( buffer );
	}
	else
	{
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
		if(pclSummon)
		{
			//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[pclSummon->siKind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			}

			if(pclki)
			{
				TCHAR* pText = GetTxtFromMgr(2299);
				StringCchPrintf(buffer, 512, pText);
				
				m_pTabScrollDlg->m_pEdit_summon_scroll_explain->SetText( buffer );
			}
		}
	}
	

}

void CNMudangDlg::Show()
{
	SetTimerOnOff( true );
	SetActionTimer( 1000 );

	m_bShow = true;
	CControllerMgr::Show( true );
}

void CNMudangDlg::Hide()
{
	SetTimerOnOff( false);

	m_bShow = false;
	CControllerMgr::Show( false );
}

bool CNMudangDlg::IsShow()
{
	return m_bShow;
}

void CNMudangDlg::ShowTabBy( int i_Index )
{
	stTabTextInfo tmp_stTabTextInfo;

	switch( i_Index )
	{
	case 0:
		if(!m_pTabReviveDlg->IsShow())
		{
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_revive, CONTROLLER_BUTTONTEXT_COLOR, FW_BOLD );
			SetTabTextInfo( &tmp_stTabTextInfo );
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_scroll, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
			SetTabTextInfo( &tmp_stTabTextInfo );
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_evolve, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
			SetTabTextInfo( &tmp_stTabTextInfo );

			if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
				tmp_stTabTextInfo.Init();
				tmp_stTabTextInfo.Set( m_pButton_equipitem, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
				SetTabTextInfo( &tmp_stTabTextInfo );
			}
			
			m_pTabReviveDlg->Show();
			UpdateCurrentSummonInfo(FALSE);
			UpdateReviveMent();
		}
		m_pTabScrollDlg->Hide();
		m_pTabEvolveDlg->Hide();

		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			m_pTabEquipitemDlg->Hide();
		}

		break;
	case 1:
		m_pTabReviveDlg->Hide();

		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			m_pTabEquipitemDlg->Hide();
		}
		m_pTabEvolveDlg->Hide();
		if(!m_pTabScrollDlg->IsShow())
		{
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_revive, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
			SetTabTextInfo( &tmp_stTabTextInfo );
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_scroll, CONTROLLER_BUTTONTEXT_COLOR, FW_BOLD );
			SetTabTextInfo( &tmp_stTabTextInfo );
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_evolve, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
			SetTabTextInfo( &tmp_stTabTextInfo );
			if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
				tmp_stTabTextInfo.Init();
				tmp_stTabTextInfo.Set( m_pButton_equipitem, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
				SetTabTextInfo( &tmp_stTabTextInfo );
			}

			m_pTabScrollDlg->Show();
			UpdateCurrentSummonInfo( TRUE);
			UpdateScrollSummonInfo();
			UpdateScrollMent();
			tmp_stTabTextInfo.Init();
		}
		
		break;
	case 2:
		m_pTabReviveDlg->Hide();
		m_pTabScrollDlg->Hide();

		if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
			m_pTabEquipitemDlg->Hide();
		}
		if(!m_pTabEvolveDlg->IsShow())
		{
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_revive, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
			SetTabTextInfo( &tmp_stTabTextInfo );
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_scroll, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
			SetTabTextInfo( &tmp_stTabTextInfo );
			tmp_stTabTextInfo.Init();
			tmp_stTabTextInfo.Set( m_pButton_evolve, CONTROLLER_BUTTONTEXT_COLOR, FW_BOLD );
			SetTabTextInfo( &tmp_stTabTextInfo );
			if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������ 
				tmp_stTabTextInfo.Init();
				tmp_stTabTextInfo.Set( m_pButton_equipitem, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
				SetTabTextInfo( &tmp_stTabTextInfo );
			}


			m_pTabEvolveDlg->Show();
			UpdateCurrentSummonInfo(TRUE);
			UpdateEvolveSummonInfo();
			UpdateEvolveMent();
		}
		break;
	case 3:
		{
			if(pclClient->IsCountrySwitch(Switch_Summon_EquipSton)){// ��ȯ�� ���� ������
				m_pTabReviveDlg->Hide();
				m_pTabScrollDlg->Hide();
				m_pTabEvolveDlg->Hide();

				tmp_stTabTextInfo.Init();
				tmp_stTabTextInfo.Set( m_pButton_revive, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
				SetTabTextInfo( &tmp_stTabTextInfo );
				tmp_stTabTextInfo.Init();
				tmp_stTabTextInfo.Set( m_pButton_scroll, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
				SetTabTextInfo( &tmp_stTabTextInfo );
				tmp_stTabTextInfo.Init();
				tmp_stTabTextInfo.Set( m_pButton_evolve, CONTROLLER_BACK_BUTTONTEXT_COLOR, FW_NORMAL );
				SetTabTextInfo( &tmp_stTabTextInfo );
				tmp_stTabTextInfo.Init();
				tmp_stTabTextInfo.Set( m_pButton_equipitem, CONTROLLER_BUTTONTEXT_COLOR, FW_BOLD );
				SetTabTextInfo( &tmp_stTabTextInfo );

				m_pTabEquipitemDlg->Show();
			}
		}
		break;
	}
}

void CNMudangDlg::Action()
{
	switch( m_CurrentStatusPage )
	{
	case 0:	// ��Ȱ

		UpdateCurrentSummonInfo(FALSE);
		UpdateReviveMent();
		break;
	case 1:	// ��ȭ

		UpdateCurrentSummonInfo(TRUE);
		UpdateScrollSummonInfo();
		UpdateScrollMent();
		break;
	case 2:	// // Evolve, Devolution, Transform
		{
			switch( m_siSelectEvolveDlg)
			{
			case SUMMONEVOLVE_EVOLVE:
				{
					UpdateCurrentSummonInfo(TRUE);
					UpdateEvolveSummonInfo();
					UpdateEvolveMent();
				}
				break;
			case SUMMONEVOLVE_DEVOLUTION:
				{
					UpdateCurrentSummonInfo(TRUE);
					UpdateDevolutionSummonInfo();
					UpdateEvolveMent();
				}
				break;
			case SUMMONEVOLVE_TRANSFORM:
				{
					UpdateCurrentSummonInfo(TRUE);
					UpdateTransformSummonInfo();
					UpdateEvolveMent();
				}
				break;
			default:
				break;
			}
		}
		break;
	case 3:{
				UpdateEquipItwmInfo();			
		   }
		   break;
	}
}

void CNMudangDlg::SetTabTextInfo( stTabTextInfo* in_SelectedText )
{
	if( in_SelectedText && in_SelectedText->st_pControllerObj )
	{
		in_SelectedText->st_pControllerObj->SetFontColor( in_SelectedText->st_Color );
		in_SelectedText->st_pControllerObj->SetFontWeight( in_SelectedText->st_siWeight );
		in_SelectedText->st_pControllerObj->Refresh();
	}
}
void CNMudangDlg::SetTextBySummonEquip(){
	// �̰� ������ �����̴ϱ�..
	TCHAR* pTextExplain = GetTxtFromMgr( 8656 );
	m_pEdit_message->SetText( pTextExplain );	
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[1]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;
	cltKindInfo* pclKI = NULL;
	for ( SI16 siSummonIndex = 0 ; siSummonIndex < MAX_SUMMON_OWN; siSummonIndex++){
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex)	;
		if(pclSummon == NULL) continue;
		if(pclSummon){
			SI32 siKind				=	pclSummon->siKind	;
			if(pclClient->pclKindInfoSet->IsValidKind( siKind ) == false ) continue;
			// �ش� ��ȯ���� ī�ε� ���� ���� ������ üũ.			
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate))
			{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[ siKind ];	}
			else
			{	pclKI = pclClient->pclKindInfoSet->pclKI[ siKind ];
			}
			if (pclKI == NULL)  continue;
			if ( pclKI->siSummonEquip	==	SUMMON_EQUIPTYPE_NONE  )	continue	;	// ������ ���� ������ ��ȯ�� ���� �˻�
			if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)			continue	;	// ���� ���� �ִ� ��ȯ������ �Ѵ�.
			TCHAR* SummonName = (TCHAR*)pclKI->GetName() ;								// ��ȯ���̸��� �޾� �´�.
			if ( SummonName ) {	// �̸����� ���´�,�ϴ� ������� 
				NTCHARString256	kText(GetTxtFromMgr(8654));
				kText.Replace(TEXT("#summoned#"), SummonName )	;
				m_pEdit_mudang->SetText( kText );
			}			
		}
	}


}
void CNMudangDlg::SetMudangPresentTxt(TCHAR * Txt)
{
	TCHAR buffer[512] = TEXT("") ;

	if ( Txt != NULL && _tcslen(Txt) > 0 )
	{
		StringCchPrintf(buffer, 512, Txt);

		m_pEdit_mudang->SetText( buffer);
		m_pEdit_mudang->Refresh();		
	}	
}

//#endif
