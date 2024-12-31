//---------------------------------
// 2004/10/27 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :

	�ۼ��� :		05/03/18
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		1. // leon todo - hWnd == NULL ? Ȯ�� �ʿ�
					2. //  leon todo - CLTNHORSETYPECHANGE_DLG  ��� �� Ȯ�� ���!

   ========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

//-----------------------------
// CommonLogic
//-----------------------------
#include "MsgType-Person.h"
#include "Msg\MsgType-Horse.h"

//-------------------------
// Common
//------------------------
#include "./NCharHorse.h"
#include "NCharStatus.h"
#include "PersonInfo.h"
#include "JWLib\IsCorrectID\IsCorrectID.h"
#include "HintDlg/HintDlg.h"
#include "Char\CharManager\CharManager.h"

//------------------------
// CLient
//------------------------
#include "Client.h"
#include "Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "NInterface/NPrivateTradeDlg/NPrivateTradeDlg.h"

#include "../../../Client/InterfaceMgr/Interface/ImageStatic.h"
#include "../../../Client/InterfaceMgr/Interface/Button.h"
#include "../../../Client/InterfaceMgr/Interface/Static.h"
#include "../../../Client/InterfaceMgr/Interface/Edit.h"
#include "../../../Client/InterfaceMgr/Interface/List.h"
#include "../../../Client/InterfaceMgr/Interface/CheckBox.h"
#include "../../../Client/InterfaceMgr/Interface/OutLine.h"
#include "NInterface/NHintDlg/NHintDlg.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "abusefilter/AbuseFilter.h"

#include "./NCharHorseTypeChange.h"

extern cltCommonLogic* pclClient;

cltNHorseStatus::cltNHorseStatus(cltCharManager* pclcm)
{
	m_pImagestatic_portrait	 = NULL; 
	m_pStatictext_horsename	 = NULL; 
	m_pEditbox_horsename	 = NULL; 
	m_pButton_changename	 = NULL; 
	m_pStatictext_horsekind	 = NULL; 
	m_pStatictext_horsekindname	 = NULL; 
	m_pStatictext_birthday	 = NULL; 
	//m_pButton_changetype	 = NULL; 
	m_pStatictext_birthdayname	 = NULL; 
	m_pStatictext_age	 = NULL; 
	m_pStatictext_agevalue	 = NULL; 
	m_pStatictext_life	 = NULL; 
	m_pStatictext_lifevalue	 = NULL; 
	m_pStatictext_sex	 = NULL; 
	m_pStatictext_sexkind	 = NULL; 
	m_pStatictext_speed	 = NULL; 
	m_pStatictext_strength	 = NULL; 
	m_pStatictext_dex	 = NULL; 
	m_pStatictext_magic	 = NULL; 
	m_pStatictext_bonus	 = NULL; 
	m_pEditbox_speed	 = NULL; 
	m_pEditbox_strength	 = NULL; 
	m_pEditbox_dex	 = NULL; 
	m_pEditbox_magic	 = NULL; 
	m_pEditbox_bonus	 = NULL; 
	m_pButton_speed	 = NULL; 
	m_pButton_strength	 = NULL; 
	m_pButton_dex	 = NULL; 
	m_pButton_magic	 = NULL; 
	m_pButton_ridehorse	 = NULL; 
	m_pButton_explain	 = NULL; 
	//m_pButton_init	 = NULL; 
	m_pButton_addstatus	 = NULL; 
	m_pCheckbox_autofood	 = NULL; 
	m_pButton_free	 = NULL; 
	m_pStatictext_free	 = NULL; 
	m_pEditbox_need	 = NULL; 

	m_pOutline_noname1	 = NULL; 
	m_pOutline_noname2	 = NULL; 
	m_pOutline_noname3	 = NULL; 

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	m_pCombobox_horse = NULL; 

	m_pButton_oilling = NULL; 

	m_bShow = false;
	pclCM	= pclcm;
	CharUnique = 0;

}

cltNHorseStatus::~cltNHorseStatus()
{
	if( 	m_pImagestatic_portrait	 )  	delete 	m_pImagestatic_portrait	;
	if( 	m_pStatictext_horsename	 )  	delete 	m_pStatictext_horsename	;
	if( 	m_pEditbox_horsename	 )  	delete 	m_pEditbox_horsename	;
	if( 	m_pButton_changename	 )  	delete 	m_pButton_changename	;
	if( 	m_pStatictext_horsekind	 )  	delete 	m_pStatictext_horsekind	;
	if( 	m_pStatictext_horsekindname	 )  	delete 	m_pStatictext_horsekindname	;
	if( 	m_pStatictext_birthday	 )  	delete 	m_pStatictext_birthday	;
	//if( 	m_pButton_changetype	 )  	delete 	m_pButton_changetype	;
	if( 	m_pStatictext_birthdayname	 )  	delete 	m_pStatictext_birthdayname	;
	if( 	m_pStatictext_age	 )  	delete 	m_pStatictext_age	;
	if( 	m_pStatictext_agevalue	 )  	delete 	m_pStatictext_agevalue	;
	if( 	m_pStatictext_life	 )  	delete 	m_pStatictext_life	;
	if( 	m_pStatictext_lifevalue	 )  	delete 	m_pStatictext_lifevalue	;
	if( 	m_pStatictext_sex	 )  	delete 	m_pStatictext_sex	;
	if( 	m_pStatictext_sexkind	 )  	delete 	m_pStatictext_sexkind	;
	if( 	m_pStatictext_speed	 )  	delete 	m_pStatictext_speed	;
	if( 	m_pStatictext_strength	 )  	delete 	m_pStatictext_strength	;
	if( 	m_pStatictext_dex	 )  	delete 	m_pStatictext_dex	;
	if( 	m_pStatictext_magic	 )  	delete 	m_pStatictext_magic	;
	if( 	m_pStatictext_bonus	 )  	delete 	m_pStatictext_bonus	;
	if( 	m_pEditbox_speed	 )  	delete 	m_pEditbox_speed	;
	if( 	m_pEditbox_strength	 )  	delete 	m_pEditbox_strength	;
	if( 	m_pEditbox_dex	 )  	delete 	m_pEditbox_dex	;
	if( 	m_pEditbox_magic	 )  	delete 	m_pEditbox_magic	;
	if( 	m_pEditbox_bonus	 )  	delete 	m_pEditbox_bonus	;
	if( 	m_pButton_speed	 )  	delete 	m_pButton_speed	;
	if( 	m_pButton_strength	 )  	delete 	m_pButton_strength	;
	if( 	m_pButton_dex	 )  	delete 	m_pButton_dex	;
	if( 	m_pButton_magic	 )  	delete 	m_pButton_magic	;
	if( 	m_pButton_ridehorse	 )  	delete 	m_pButton_ridehorse	;
	if( 	m_pButton_explain	 )  	delete 	m_pButton_explain	;
	//if( 	m_pButton_init	 )  	delete 	m_pButton_init	;
	if( 	m_pButton_addstatus	 )  	delete 	m_pButton_addstatus	;
	if( 	m_pCheckbox_autofood	 )  	delete 	m_pCheckbox_autofood	;
	if( 	m_pButton_free	 )  	delete 	m_pButton_free	;
	if( 	m_pStatictext_free	 )  	delete 	m_pStatictext_free	;
	if( 	m_pEditbox_need	 )  	delete 	m_pEditbox_need	;

	if( 	m_pOutline_noname1	 )  	delete 	m_pOutline_noname1	;
	if( 	m_pOutline_noname2	 )  	delete 	m_pOutline_noname2	;
	if( 	m_pOutline_noname3	 )  	delete 	m_pOutline_noname3	;

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	if( 	m_pCombobox_horse	 )  	delete 	m_pCombobox_horse	;

	if( 	m_pButton_oilling)  	delete 	m_pButton_oilling;

	pclCM = NULL;
	SetTimerOnOff( false );
}

void cltNHorseStatus::Create( CControllerMgr *pParent )
{
	//if ( ! IsCreate() )
	{
		cltClient *pclclient = (cltClient*)pclClient;
		CharUnique = pclclient->MyCharUnique;

		//CDialogController::Create( CLTNHORSESTATUS_DLG, CONTROLLER_KIND_CHILDDIALOG, pParent, NHorseStatusStaticProc, NULL, NULL, 0, false, 10, 40, 325, 480, false, false, false);

		CInterfaceFile file;

		file.LoadFile(TEXT("NInterface/Data/NCharStatusDlg/DLG_NCharStatus_Child_NHorse.ddf"));
		file.CreateChildDialog( this, CLTNHORSESTATUS_DLG, TEXT("dialog_horse"), NHorseStatusStaticProc, pParent );

		// ���̾�α� ��ġ ����
		SetDialogPos( ((cltNCharStatus*)pParent)->GetChildDlgXPos(), ((cltNCharStatus*)pParent)->GetChildDlgYPos(), GetWidth(), GetHeight() );

		m_pImagestatic_portrait	 = new 	CImageStatic	( this )	;
		m_pStatictext_horsename	 = new 	CStatic	( this )	;
		m_pEditbox_horsename	 = new 	CEdit	( this )	;
		m_pButton_changename	 = new 	CButton	( this )	;
		m_pStatictext_horsekind	 = new 	CStatic	( this )	;
		m_pStatictext_horsekindname	 = new 	CStatic	( this )	;
		m_pStatictext_birthday	 = new 	CStatic	( this )	;
		//m_pButton_changetype	 = new 	CButton	( this )	;
		m_pStatictext_birthdayname	 = new 	CStatic	( this )	;
		m_pStatictext_age	 = new 	CStatic	( this )	;
		m_pStatictext_agevalue	 = new 	CStatic	( this )	;
		m_pStatictext_life	 = new 	CStatic	( this )	;
		m_pStatictext_lifevalue	 = new 	CStatic	( this )	;
		m_pStatictext_sex	 = new 	CStatic	( this )	;
		m_pStatictext_sexkind	 = new 	CStatic	( this )	;
		m_pStatictext_speed	 = new 	CStatic	( this )	;
		m_pStatictext_strength	 = new 	CStatic	( this )	;
		m_pStatictext_dex	 = new 	CStatic	( this )	;
		m_pStatictext_magic	 = new 	CStatic	( this )	;
		m_pStatictext_bonus	 = new 	CStatic	( this )	;
		m_pEditbox_speed	 = new 	CEdit	( this )	;
		m_pEditbox_strength	 = new 	CEdit	( this )	;
		m_pEditbox_dex	 = new 	CEdit	( this )	;
		m_pEditbox_magic	 = new 	CEdit	( this )	;
		m_pEditbox_bonus	 = new 	CEdit	( this )	;
		m_pButton_speed	 = new 	CButton	( this )	;
		m_pButton_strength	 = new 	CButton	( this )	;
		m_pButton_dex	 = new 	CButton	( this )	;
		m_pButton_magic	 = new 	CButton	( this )	;
		m_pButton_ridehorse	 = new 	CButton	( this )	;
		m_pButton_explain	 = new 	CButton	( this )	;
		//m_pButton_init	 = new 	CButton	( this )	;
		m_pButton_addstatus	 = new 	CButton	( this )	;
		m_pCheckbox_autofood	 = new 	CCheckBox	( this )	;
		m_pButton_free	 = new 	CButton	( this )	;
		m_pStatictext_free	 = new 	CStatic	( this )	;
		m_pEditbox_need	 = new 	CEdit	( this )	;

		m_pOutline_noname1	 = new 	COutLine	( this )	;
		m_pOutline_noname2	 = new 	COutLine	( this )	;
		m_pOutline_noname3	 = new 	COutLine	( this )	;

		//KHY - 1001 - ��µ��� 5���� ���� ����.
		m_pCombobox_horse	 = new 	CComboBox	( this )	;		

		m_pButton_oilling	 = new 	CButton	( this )	;


		file.CreateControl( m_pImagestatic_portrait, CLTNHORSESTATUS_DLG_IMAGESTATIC_PORTRAIT, TEXT("imagestatic_portrait") );
		file.CreateControl( m_pStatictext_horsename, CLTNHORSESTATUS_DLG_STATICTEXT_HORSENAME, TEXT("statictext_horsename") );
		file.CreateControl( m_pEditbox_horsename, CLTNHORSESTATUS_DLG_EDITBOX_HORSENAME, TEXT("editbox_horsename") );
		file.CreateControl( m_pButton_changename, CLTNHORSESTATUS_DLG_BUTTON_CHANGENAME, TEXT("button_changename") );
		file.CreateControl( m_pStatictext_horsekind, CLTNHORSESTATUS_DLG_STATICTEXT_HORSEKIND, TEXT("statictext_horsekind") );
		file.CreateControl( m_pStatictext_horsekindname, CLTNHORSESTATUS_DLG_STATICTEXT_HORSEKINDNAME, TEXT("statictext_horsekindname") );
		file.CreateControl( m_pStatictext_birthday, CLTNHORSESTATUS_DLG_STATICTEXT_BIRTHDAY, TEXT("statictext_birthday") );
		//file.CreateControl( m_pButton_changetype, CLTNHORSESTATUS_DLG_BUTTON_CHANGETYPE, TEXT("button_changetype") );
		file.CreateControl( m_pStatictext_birthdayname, CLTNHORSESTATUS_DLG_STATICTEXT_BIRTHDAYNAME, TEXT("statictext_birthdayname") );
		file.CreateControl( m_pStatictext_age, CLTNHORSESTATUS_DLG_STATICTEXT_AGE, TEXT("statictext_age") );
		file.CreateControl( m_pStatictext_agevalue, CLTNHORSESTATUS_DLG_STATICTEXT_AGEVALUE, TEXT("statictext_agevalue") );
		file.CreateControl( m_pStatictext_life, CLTNHORSESTATUS_DLG_STATICTEXT_LIFE, TEXT("statictext_life") );
		file.CreateControl( m_pStatictext_lifevalue, CLTNHORSESTATUS_DLG_STATICTEXT_LIFEVALUE, TEXT("statictext_lifevalue") );
		file.CreateControl( m_pStatictext_sex, CLTNHORSESTATUS_DLG_STATICTEXT_SEX, TEXT("statictext_sex") );
		file.CreateControl( m_pStatictext_sexkind, CLTNHORSESTATUS_DLG_STATICTEXT_SEXKIND, TEXT("statictext_sexkind") );
		file.CreateControl( m_pStatictext_speed, CLTNHORSESTATUS_DLG_STATICTEXT_SPEED, TEXT("statictext_speed") );
		file.CreateControl( m_pStatictext_strength, CLTNHORSESTATUS_DLG_STATICTEXT_STRENGTH, TEXT("statictext_strength") );
		file.CreateControl( m_pStatictext_dex, CLTNHORSESTATUS_DLG_STATICTEXT_DEX, TEXT("statictext_dex") );
		file.CreateControl( m_pStatictext_magic, CLTNHORSESTATUS_DLG_STATICTEXT_MAGIC, TEXT("statictext_magic") );
		file.CreateControl( m_pStatictext_bonus, CLTNHORSESTATUS_DLG_STATICTEXT_BONUS, TEXT("statictext_bonus") );
		file.CreateControl( m_pEditbox_speed, CLTNHORSESTATUS_DLG_EDITBOX_SPEED, TEXT("editbox_speed") );
		file.CreateControl( m_pEditbox_strength, CLTNHORSESTATUS_DLG_EDITBOX_STRENGTH, TEXT("editbox_strength") );
		file.CreateControl( m_pEditbox_dex, CLTNHORSESTATUS_DLG_EDITBOX_DEX, TEXT("editbox_dex") );
		file.CreateControl( m_pEditbox_magic, CLTNHORSESTATUS_DLG_EDITBOX_MAGIC, TEXT("editbox_magic") );
		file.CreateControl( m_pEditbox_bonus, CLTNHORSESTATUS_DLG_EDITBOX_BONUS, TEXT("editbox_bonus") );
		file.CreateControl( m_pButton_speed, CLTNHORSESTATUS_DLG_BUTTON_SPEED, TEXT("button_speed") );
		file.CreateControl( m_pButton_strength, CLTNHORSESTATUS_DLG_BUTTON_STRENGTH, TEXT("button_strength") );
		file.CreateControl( m_pButton_dex, CLTNHORSESTATUS_DLG_BUTTON_DEX, TEXT("button_dex") );
		file.CreateControl( m_pButton_magic, CLTNHORSESTATUS_DLG_BUTTON_MAGIC, TEXT("button_magic") );
		file.CreateControl( m_pButton_ridehorse, CLTNHORSESTATUS_DLG_BUTTON_RIDEHORSE, TEXT("button_ridehorse") );
		file.CreateControl( m_pButton_explain, CLTNHORSESTATUS_DLG_BUTTON_EXPLAIN, TEXT("button_explain") );
		//file.CreateControl( m_pButton_init, CLTNHORSESTATUS_DLG_BUTTON_INIT, TEXT("button_init") );
		file.CreateControl( m_pButton_addstatus, CLTNHORSESTATUS_DLG_BUTTON_ADDSTATUS, TEXT("button_addstatus") );
		file.CreateControl( m_pCheckbox_autofood, CLTNHORSESTATUS_DLG_CHECKBOX_AUTOFOOD, TEXT("checkbox_autofood") );
		file.CreateControl( m_pButton_free, CLTNHORSESTATUS_DLG_BUTTON_FREE, TEXT("button_free") );
		file.CreateControl( m_pStatictext_free, CLTNHORSESTATUS_DLG_STATICTEXT_FREE, TEXT("statictext_free") );
		file.CreateControl( m_pEditbox_need, CLTNHORSESTATUS_DLG_EDITBOX_NEED, TEXT("editbox_need") );

		file.CreateControl( m_pButton_oilling, CLTNHORSESTATUS_DLG_BUTTON_OILLING, TEXT("button_oilling") );

		file.CreateControl( 	m_pOutline_noname1	, 	CLTNHORSESTATUS_DLG_OUTLINE_NONAME1	, 	TEXT("outline_NONAME1")	 )	;
		file.CreateControl( 	m_pOutline_noname2	, 	CLTNHORSESTATUS_DLG_OUTLINE_NONAME2	, 	TEXT("outline_NONAME2")	 )	;
		file.CreateControl( 	m_pOutline_noname3	, 	CLTNHORSESTATUS_DLG_OUTLINE_NONAME3	, 	TEXT("outline_NONAME3")	 )	;

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//KHY - 1001 - ��µ��� 5���� ���� ����.
		file.CreateControl( m_pCombobox_horse, CLTNHORSESTATUS_DLG_COMBOBOX_HORSE, TEXT("combobox_selectHorse") );
		
		m_pCombobox_horse->SetEnableWheel( false );

		m_bChangedInitHorseStatus = TRUE;
//		m_siLastHorseComboList = 0;

		InitHorseStatusInfo();
/*
		if(m_pCombobox_horse->GetItemNum() > 0 )
		{
			m_siLastHorseComboList = 0;
			m_pCombobox_horse->SetCursel( 0 );
		}
*/
//		m_pCombobox_horse->Show(false); //�ӽ�.
		


		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		SetTimerOnOff( true );
		cltHorse* pclhorse = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();

		BonusHorseButtonEnableSwitch = FALSE ;

		if ( pclhorse != NULL && pclhorse->szName != NULL && _tcslen ( pclhorse->szName ) > 0 )
		{
            m_pEditbox_horsename->SetText( pclhorse->szName );
		}
		
		m_pStatictext_age->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_agevalue->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_birthday->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_birthdayname->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_bonus->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_dex->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_horsekind->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_horsekindname->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_horsename->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_life->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_lifevalue->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_magic->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_sex->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_sexkind->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_speed->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_strength->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_free->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;

		m_pStatictext_age->Refresh();
		m_pStatictext_agevalue->Refresh();
		m_pStatictext_birthday->Refresh();
		m_pStatictext_birthdayname->Refresh();
		m_pStatictext_bonus->Refresh();
		m_pStatictext_dex->Refresh();
		m_pStatictext_horsekind->Refresh();
		m_pStatictext_horsekindname->Refresh();
		m_pStatictext_horsename->Refresh();
		m_pStatictext_life->Refresh();
		m_pStatictext_lifevalue->Refresh();
		m_pStatictext_magic->Refresh();
		m_pStatictext_sex->Refresh();
		m_pStatictext_sexkind->Refresh();
		m_pStatictext_speed->Refresh();
		m_pStatictext_strength->Refresh();
		m_pStatictext_free->Refresh();

	
		// ���ɷ� ��� �̿�� ��� ��ư�� �����. �ʿ��ϸ� ������ ��

		m_pButton_addstatus->Show(false);
		
		// [�߰� : Ȳ���� 2008. 1. 16 => �� �ɷ� ��ġ���� ��ư ��Ȱ��ȭ.]
		m_pButton_speed->Show( false );
		m_pButton_strength->Show( false );
		m_pButton_dex->Show( false );
		m_pButton_magic->Show( false );
		m_pStatictext_bonus->Show( false );
		m_pEditbox_bonus->Show( false );

		// ���� ��ư�� ������� �� ��츸 ���δ�.
		//m_pButton_oilling->Show(false);

		UpdateHorseStatusInfo();
	
		////==========================================
		//// �ʻ�ȭ 
		////==========================================
		//if(pclhorse->siHorseUnique)
		//{
		//	TCHAR strFileName[ 128 ] = TEXT("");
		//	TCHAR strPathFileName[ 128 ] = TEXT("");
		//	switch(pclhorse->siHorseUnique)
		//	{
		//	case 1:	_tcscpy(strFileName, TEXT("����������"));	break;
		//	case 2:	_tcscpy(strFileName, TEXT("���������")); break;
		//	case 3:	_tcscpy(strFileName, TEXT("���������")); break;
		//	case 4:	_tcscpy(strFileName, TEXT("���丶"));	break;
		//	case 5: _tcscpy(strFileName,	TEXT("��踶"));	break;
		//	case 6: _tcscpy(strFileName,	TEXT("�絹��"));	break;
		//	case 7: _tcscpy(strFileName,	TEXT("õ����")); break;
		//	default:_tcscpy(strFileName, TEXT("����������"));	break;
		//	//case 1:	_tcscpy(strFileName, TEXT("BROWN_HORSE"));	break;
		//	//case 2:	_tcscpy(strFileName, TEXT("BLACK_HORSE")); break;
		//	//case 3:	_tcscpy(strFileName, TEXT("WHITE_HORSE")); break;
		//	//case 4:	_tcscpy(strFileName, TEXT("RED_HORSE"));	break;
		//	//case 5: _tcscpy(strFileName, TEXT("ZEBRA_HORSE")); break;
		//	//case 6: _tcscpy(strFileName, TEXT("RUDOLF")); break;
		//	//case 7: _tcscpy(strFileName,	TEXT("THOUSAND_HORSE")); break;
		//	//default:_tcscpy(strFileName, TEXT("BROWN_HORSE"));	break;
		//	}
		//	// leon - todo strFileName ���� �ϴ� ���ڿ� �׽�Ʈ �ʿ�!
		//	m_pImagestatic_portrait->SetFileName( TEXT("Interface/Portrait/PortraitIcon.SPR") );
		//	SI16 tmpSelectedIndex = pclClient->pclKindInfoSet->FindKindFromName( strFileName );
		//	m_pImagestatic_portrait->SetFontIndex( tmpSelectedIndex  -1 );

			//sprintf( strPathFileName, TEXT("Interface/Portrait/%s.bmp"),	strFileName );
			//m_hHorsePortraitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), strPathFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		//}
		//if ( m_hHorsePortraitBitmap != NULL )
		//{
		//	SendDlgItemMessage( hDlg, IDC_STATIC_HORSE_PORTRAIT, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHorsePortraitBitmap );
		//}
		
		//==========================================
		// HORSE HINT
		//==========================================
		//m_pButton_explain->SetFileName(...);

		//---------------------------------------------
		// HORSE INIT
		//-----------------------------
		//m_pButton_init->SetFileName(..);

		//---------------------------------------------
		// HORSE ADD STATUS
		//-----------------------------
		//m_pButton_addstatus->SetFileName(..);


		//---------------------------------
		// HORSE TYPE
		//---------------------------------
		//sm_pButton_changetype->SetFileName(..);


		Hide();

	}
	//else
	//{
	//	DeleteDialog();
	//}
}

void CALLBACK cltNHorseStatus::NHorseStatusStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltNHorseStatus *pThis = (cltNHorseStatus*)pControllerMgr;
	pThis->NHorseStatusProc( nEvent, nControlID, pControl );
}


void CALLBACK cltNHorseStatus::NHorseStatusProc( UINT nEvent, int nControlID, CControllerObj* pControl)
{
	//SI32 i;
	cltClient* pclclient = (cltClient*)pclClient;
	cltHorse* pclhorse = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[1];


	switch( nControlID )
	{

	case CLTNHORSESTATUS_DLG_CHECKBOX_AUTOFOOD:
		{
			switch( nEvent )
			{
			case EVENT_CHECKBOX_CHANGED:
				{
					cltCharChangeStatusInfo clchangeinfo(CHANGETYPE_AUTOFOOD, true);
					cltGameMsgRequest_StatusInfo clinfo(&clchangeinfo);
					if(m_pCheckbox_autofood->IsCheck() == false )
					{
						clinfo.ChangeInfo.bChangeSwitch = false;
						
					}
					else
					{
						clinfo.ChangeInfo.bChangeSwitch = true;
					}

					// ������ ���� ������ ������. 
					cltMsg clMsg( GAMEMSG_REQUEST_CHANGESTATUSINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

					//InvalidateRect(hDlg, NULL, TRUE);

				}
				break;
			}
		}
	case CLTNHORSESTATUS_DLG_BUTTON_CHANGENAME:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					TCHAR ChangeHorseName[ MAX_HORSE_NAME ] = TEXT("");
					TCHAR *tmpChar = NULL;
					tmpChar = m_pEditbox_horsename->GetText();
					if ( !tmpChar || _tcslen(tmpChar) > MAX_HORSE_NAME - 1 )
					{
						TCHAR buffer[256] = TEXT("") ;
						TCHAR* pText = GetTxtFromMgr(566);
						StringCchPrintf(buffer, 256, pText,(MAX_HORSE_NAME-1)/2);
						
						pText = GetTxtFromMgr(567);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText,buffer);
						return ;
					}

					StringCchCopy( ChangeHorseName, MAX_HORSE_NAME, tmpChar );

					if ( pclhorse != NULL && pclhorse->szName != NULL && _tcslen( pclhorse->szName ) > 0 && _tcscmp( pclhorse->szName, ChangeHorseName ) == 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(569);
						TCHAR* pText = GetTxtFromMgr(570);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
						return ;
					}

					//cyj ���̸����� �弳���� ����
					TCHAR buf[ MAX_HORSE_NAME ];
					StringCchPrintf(buf, MAX_HORSE_NAME, ChangeHorseName);
#ifdef _IAF_EXPORT
					if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
					{
						TCHAR ResultBuf[1024] = "";
						IAF::Filtering( buf, ResultBuf, sizeof(ResultBuf), IAF::FILTER_CHARACTER );
						memcpy( buf, ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
					}
#else
					pclclient->m_pCAbuseFilter->CheckAbuse(buf);
#endif

					if ( IsCorrectID( buf ) == FALSE )
					{
						TCHAR* pTitle = GetTxtFromMgr(571);
						TCHAR* pText = GetTxtFromMgr(572);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
						return ;
					}
					
					cltGameMsgRequest_HorseNameChange clinfo( pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorseIndex(), buf );
					cltMsg clMsg( GAMEMSG_REQUEST_HORSENAMECHANGE, sizeof(clinfo), (BYTE*)&clinfo);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_RIDEHORSE:
		{	
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					//KHY - 1001 - ��µ��� 5���� ���� ����.
					SI32 siHorseIndex = pclChar->pclCI->clHorseInfo.GetCurrentShowHorseIndex();

					// ���� ������ ���� �¿��. 
					if(pclChar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == false)
					{
						if(pclhorse != NULL && pclhorse->siHorseUnique)
						{	
							if(pclChar->pclCI->clHorseInfo.CanRide(siHorseIndex, &pclclient->clClientDate) == true)
							{
								// �ŷ� ���̶�� Ż �� ����.
								if ( pclclient->m_pDialog[ NPRIVATETRADE_DLG ] )
								{
									TCHAR* pTitle = GetTxtFromMgr(573);
									TCHAR* pText = GetTxtFromMgr(574);
									pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
								}
								else
								{
									cltGameMsgRequest_RideOrUnrideHorse clinfo(siHorseIndex);
									cltMsg clMsg(GAMEMSG_REQUEST_RIDEHORSE, sizeof(clinfo), (BYTE*)&clinfo);
									pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
								}
							}
							else
							{
								break;
							}
						}
					}
					else
					{
						cltGameMsgRequest_RideOrUnrideHorse clinfo(siHorseIndex);
						cltMsg clMsg(GAMEMSG_REQUEST_UNRIDEHORSE, sizeof(clinfo), (BYTE*)&clinfo);
						pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
					}
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_FREE:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = 1;
					if(pclCM->IsAlive(id) == false)return;

					// ���� ������ ����. 
					if(pclhorse == NULL || pclhorse->siHorseUnique <= 0)
					{
						TCHAR* pTitle = GetTxtFromMgr(575);
						TCHAR* pText = GetTxtFromMgr(576);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						return;
					}

					TCHAR* pText = GetTxtFromMgr(578);
					TCHAR* pTitle = GetTxtFromMgr(577);

					// leon todo - hWnd == NULL ? Ȯ�� �ʿ�
					stMsgBox MsgBox;
					// ���� dialog�� �� â ���� Child Dialog�϶�
                    CControllerMgr *pParent = NULL;
					pParent = this->GetParentDialog();
					if(pParent == NULL ) return;
					MsgBox.Set( pParent,  pText, pTitle, MSGBOX_TYPE_YESNO, 12 );
					BYTE TempBuffer[ 128 ];
					SI16 Size = sizeof( id );
					memcpy( TempBuffer, &id, Size );
					pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

					//if(MessageBox(NULL, pTitle, pText, MB_TOPMOST|MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2) == IDYES)
					//{
					//	// ���� Ÿ�� ������ ����. 
					//	if(pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseIndex >= 0)
					//	{
					//		pTitle = GetTxtFromMgr(575);
					//		pText = GetTxtFromMgr(579);

					//		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					//		return;
					//	}
					//	
					//	// �� �κ��� ��ǰ�� ������ Ǯ���� �� ����. 
					//	if(pclCM->CR[id]->pclCI->clCharItem.IsHorseHaveItem() == true)
					//	{
					//		pTitle = GetTxtFromMgr(575);
					//		pText = GetTxtFromMgr(580);

					//		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					//		return;
					//	}
					//											
					//	cltMsg clMsg(GAMEMSG_REQUEST_HORSEFREE, 0, NULL);
					//	pclclient->SendMsgToServer((sPacketHeader*)&clMsg);					
					//}
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_EXPLAIN:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					
				//if ( g_SoundOnOffDlg.m_bFullScreenMode )
				//{
					pclclient->ShowHelpWindow(TEXT("horsebreed"));
					//if((pclclient->m_pDialog[ NHINT_DLG ])==NULL)
					//{
					//	pclclient->CreateInterface( NHINT_DLG );
					//}
					//((NHintDlgExplain*)pclclient->m_pDialog[ NHINT_DLG])->Show(TEXT("horsebreed"));

				//}
				//else
				//	pclclient->m_pHintDlg->Show(TEXT("horsebreed"));
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_ADDSTATUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if ( !id ) return  ;

					TCHAR buffer[256] = TEXT("") ;

					if ( pclhorse == NULL || pclhorse->siHorseUnique <= 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(3170);
						TCHAR* pText = GetTxtFromMgr(581);

						StringCchPrintf(buffer, 256, pText);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
						return  ;
					}

					SI32 itemunique = ITEMUNIQUE(24050) ;  // ���ɷ�����̿��
					if ( pclclient->pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(3170);
						TCHAR* pText = GetTxtFromMgr(3171);

						StringCchPrintf(buffer, 256, pText);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
						return ;
					}

					TCHAR* pText = GetTxtFromMgr(3170);
					TCHAR* pTitle = GetTxtFromMgr(3172);

					StringCchPrintf(buffer, 256, pText);

					stMsgBox MsgBox;
					// ���� dialog�� �� â ���� Child Dialog�϶�
                    CControllerMgr *pParent = NULL;
					pParent = this->GetParentDialog();
					if(pParent == NULL ) return;
					MsgBox.Set( pParent, buffer, pTitle, MSGBOX_TYPE_YESNO, 11 );
					TCHAR TempBuffer[ 128 ] = TEXT("");
					pclclient->SetMsgBox( &MsgBox, NULL, 0 );

					//if (  MessageBox(NULL, pTitle,buffer,
					//	MB_ICONQUESTION | MB_YESNO) == IDNO )
					//{
					//	return ;
					//}

					//cltMsg clMsg(GAMEMSG_REQUEST_HORSE_ADDSTATUS,0);
					//pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_INIT:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if ( !id ) return  ;

					TCHAR buffer[256] = TEXT("") ;

					if ( pclhorse == NULL || pclhorse->siHorseUnique <= 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(582);
						TCHAR* pText = GetTxtFromMgr(581);

						StringCchPrintf(buffer, 256, pText);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
						return  ;
					}

					SI32 itemunique = 14070 ;  // �������ʱ�ȭ�̿��
					if ( pclclient->pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(582);
						TCHAR* pText = GetTxtFromMgr(583);

						StringCchPrintf(buffer, 256, pText);
						//MsgBox(TEXT("���� �ʱ�ȭ"), buffer);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
						return ;
					}

					TCHAR* pText = GetTxtFromMgr(582);
					TCHAR* pTitle = GetTxtFromMgr(584);

					StringCchPrintf(buffer, 256, pText);

					stMsgBox MsgBox;
					// ���� dialog�� �� â ���� Child Dialog�϶�
                    CControllerMgr *pParent = NULL;
					pParent = this->GetParentDialog();
					if(pParent == NULL ) return;
					MsgBox.Set( pParent, buffer, pTitle, MSGBOX_TYPE_YESNO, 10 );
					TCHAR TempBuffer[ 128 ] = TEXT("");
					pclclient->SetMsgBox( &MsgBox, NULL, 0 );

					//if (  MessageBox(NULL, pTitle,buffer,
					//	MB_ICONQUESTION | MB_YESNO) == IDNO )
					//{
					//	return ;
					//}

					//cltMsg clMsg(GAMEMSG_REQUEST_HORSEINIT,0);
					//pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_SPEED:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if( !id ) return  ;

					if(pclhorse != NULL && pclhorse->siMoveSpeed >= pclClient->pclHorseManager->GetFullSpeed( pclhorse->siHorseUnique) )
					{
						TCHAR buffer[256] = TEXT("") ;
						TCHAR* pTitle = GetTxtFromMgr(586);
						TCHAR* pText = GetTxtFromMgr(585);
						StringCchPrintf(buffer, 256, pText, 
							pclClient->pclHorseManager->GetFullSpeed( pclhorse->siHorseUnique)/100);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
						return ;
					}

					SendUseHorseBonusMessageToServer(0);
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_STRENGTH:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if ( !id ) return ;

					if( pclhorse != NULL && pclhorse->siStr >= pclClient->pclHorseManager->GetFullStr( pclhorse->siHorseUnique)  )
					{
						TCHAR buffer[256] = TEXT("") ;
						TCHAR* pTitle = GetTxtFromMgr(588);
						TCHAR* pText = GetTxtFromMgr(587);
						StringCchPrintf(buffer, 256, pText, 
							pclClient->pclHorseManager->GetFullStr( pclhorse->siHorseUnique) / 100);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
						return;
					}

					SendUseHorseBonusMessageToServer(1);
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_DEX:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if ( !id ) return ;

					if( pclhorse != NULL && pclhorse->siDex >= pclClient->pclHorseManager->GetFullDex( pclhorse->siHorseUnique) )
					{
						TCHAR buffer[256] = TEXT("") ;
						TCHAR* pTitle = GetTxtFromMgr(590);
						TCHAR* pText = GetTxtFromMgr(589);
						StringCchPrintf(buffer, 256, pText, 
							pclClient->pclHorseManager->GetFullDex( pclhorse->siHorseUnique)/100);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
						return;
					}

					SendUseHorseBonusMessageToServer(2);
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_MAGIC:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if ( !id ) return ;

					if( pclhorse != NULL && pclhorse->siMag >= pclClient->pclHorseManager->GetFullMag( pclhorse->siHorseUnique) )
					{
						TCHAR buffer[256] = TEXT("") ;
						TCHAR* pTitle = GetTxtFromMgr(592);
						TCHAR* pText = GetTxtFromMgr(591);
						StringCchPrintf(buffer, 256, pText, 
							pclClient->pclHorseManager->GetFullMag( pclhorse->siHorseUnique)/100);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
						return;
					}

					SendUseHorseBonusMessageToServer(3);
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_CHANGETYPE:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{

					/*cyj ���� �������� ������ �ٸ����� ItemUnique�� �������� �������� ���� �Ұ���

					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if ( !id ) return ;

					SI16 horseunique = pclhorse->siHorseUnique ;

					TCHAR buffer[256] = TEXT("") ;

					if ( horseunique <= 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(593);
						TCHAR* pText = GetTxtFromMgr(581);
						sprintf(buffer, pText);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
						return ;
					}

					//if ( !pclHorseTypeChange->CreateDlg(pclClient->GetInstance(), pclClient->GetHwnd(),horseunique) )
					//	pclHorseTypeChange->Close();
					//  leon todo - CLTNHORSETYPECHANGE_DLG  ��� �� Ȯ�� ���!
					pclclient->CreateInterface( CLTNHORSETYPECHANGE_DLG );
					if(pclclient->m_pDialog[ CLTNHORSETYPECHANGE_DLG ])
						((cltNHorseTypeChange*)pclclient->m_pDialog[ CLTNHORSETYPECHANGE_DLG ])->SetOriUnique( horseunique );

					*/

				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_COMBOBOX_HORSE:
		{
			// [����] ��Ʋ�ξ� �ʿ� �ִٸ� ���� �Ұ���
			cltCharClient* pclChar = ((cltClient*)pclClient)->pclCM->GetCharClient(1);
			if( NULL == pclChar)
				break;

			if( pclChar->GetMapIndex() == MAPINDEX_BATTLEROYAL_GRANDMABRIUM || pclChar->GetMapIndex() == MAPINDEX_BATTLEROYAL_MABRIUM)
			{
				break;
			}

			switch( nEvent )
			{
			case EVENT_COMBOBOX_SELECTION_CHANGED:
				{
					if(m_pCombobox_horse && m_pCombobox_horse->GetItemNum() > 0)
					{
							m_siLastHorseComboList = m_pCombobox_horse->GetSelectedIndex(); 

							cltGameMsgRequest_ChangeHorse clInfo( m_siLastHorseComboList );
							cltMsg clMsg( GAMEMSG_REQUEST_CHANGEHORSE, sizeof( clInfo ), (BYTE*)&clInfo );
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);


//						pclCM->CR[1]->pclCI->clHorseInfo.SetCurrentShowHorse(m_siLastHorseComboList);

//						UpdateHorseStatusInfo();
//						UpdateHorsePortrait();
/*
						//=======================================================
						// ��ȯ�� �̸� �� ���� 
						//=======================================================
						TCHAR SummonName[256]= TEXT("");
						SI32 SummonIndex = 0;

						//pTmpChar = m_pCombobox_summons->GetText(m_siLastSummonComboList);
						//if(pTmpChar)
						//{
						//	strcpy( SummonName, pTmpchar );
						//	m_pEditbox_name->SetText( SummonName );
						//}
						if(GetComboSummonNameIndex( SummonName, 256, &SummonIndex))
						{
							m_pEditbox_name->SetText( SummonName );
						}
*/
					}
				}
				break;
			}
		}
		break;
	case CLTNHORSESTATUS_DLG_BUTTON_OILLING: // �����ϱ�.
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if ( !id ) return  ;

					TCHAR buffer[256] = TEXT("") ;

					SI32 itemunique = ITEMUNIQUE(13631) ;  // �ֹ���.
					if ( pclclient->pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(9629);
						TCHAR* pText = GetTxtFromMgr(9630);

						StringCchPrintf(buffer, 256, pText);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
						return ;
					}

					TCHAR* pText = GetTxtFromMgr(9629);
					TCHAR* pTitle = GetTxtFromMgr(9631);

					StringCchPrintf(buffer, 256, pText);

					stMsgBox MsgBox;
					// ���� dialog�� �� â ���� Child Dialog�϶�
                    			CControllerMgr *pParent = NULL;
					pParent = this->GetParentDialog();
					if(pParent == NULL ) return;

					MsgBox.Set( pParent, buffer, pTitle, MSGBOX_TYPE_YESNO, 13 );
					BYTE TempBuffer[ 128 ];
					SI16 Size = sizeof( itemunique );
					memcpy( TempBuffer, &itemunique, Size );
					pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );


					//if (  MessageBox(NULL, pTitle,buffer,
					//	MB_ICONQUESTION | MB_YESNO) == IDNO )
					//{
					//	return ;
					//}

					//cltMsg clMsg(GAMEMSG_REQUEST_HORSE_ADDSTATUS,0);
					//pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
					
				}
				break;
			}
		}
		break;
	}
}

//KHY - 1001 - ��µ��� 5���� ���� ����.
//void cltNSummonStatus::InitSummonStatusInfo()
void cltNHorseStatus::InitHorseStatusInfo()
{
	stComboBoxItemData tmpComboBoxItemData;

	if(m_bChangedInitHorseStatus)
	{
		//==============================================
		// COMBO LIST�� ��µ��� �̸��� �����Ѵ�.
		//==============================================
		SI32 siIndex = m_pCombobox_horse->GetSelectedIndex();
		
		m_pCombobox_horse->Clear();

//		SI32 siHorseCount = 0;
		TCHAR HorseName[256]=TEXT("");
		for(SI32 i=0; i < MAX_HORSE_PER_PERSON; ++i)
		{
			//cltSummon *pclSummon = pclCM->CR[1]->pclCI->clSummonInfo.GetSummon(i);

			cltHorse* pclhorse = pclCM->CR[1]->pclCI->clHorseInfo.GetHorse(i);

			if(pclhorse && pclhorse->siHorseUnique )
			{
				StringCchPrintf(HorseName, 256, TEXT("%d: %s"), i+1, pclhorse->szName);
				tmpComboBoxItemData.Init();
				tmpComboBoxItemData.Set( HorseName );
				m_pCombobox_horse->AddItem( &tmpComboBoxItemData );
//				siHorseCount++;
			}
			else
			{
				TCHAR* pText= GetTxtFromMgr(7196); //�̻��.
				StringCchPrintf(HorseName, 256, TEXT("%d: %s"), i+1, pText);

				tmpComboBoxItemData.Init();
				tmpComboBoxItemData.Set( HorseName );
				m_pCombobox_horse->AddItem( &tmpComboBoxItemData );				
			}
		}
		if(siIndex == CB_ERR)			siIndex = 0;
//		if(siIndex >= siHorseCount)	siIndex = 0;


		siIndex = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorseIndex();
		m_pCombobox_horse->SetCursel( siIndex );


		// Combo List���� ���õ� ��ȯ���� �̸��� �����Ѵ�.
/*
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex( SummonName, 256,  &SummonIndex))
		{
			cltSummon *pclSummon = pclCM->CR[1]->pclCI->clSummonInfo.GetSummon(SummonIndex);
			if(pclSummon)
			{
				m_pEditbox_health_explain->SetText( pclSummon->szName );
			}
		}
*/

	}
	//==============================================
	m_bChangedInitHorseStatus = FALSE;
}




// ���� ���¸� ������Ʈ �Ѵ�.
void cltNHorseStatus::UpdateHorseStatusInfo()
{
	TCHAR buffer[256];

	cltHorse* pclhorse = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();
	if(pclhorse == NULL)			return;

	//==========================================
	// �ʻ�ȭ 
	//==========================================
	if(pclhorse->siHorseUnique)
	{
		TCHAR strFileName[ 128 ] = TEXT("");
		TCHAR strPathFileName[ 128 ] = TEXT("");
		TCHAR* pText= GetTxtFromMgr(2609);
		switch(pclhorse->siHorseUnique)
		{
		case HORSEUNIQUE_BROWN:	
			{
				StringCchCopy(strFileName, 128, pText);	
			}
			break;
		case HORSEUNIQUE_BLACK:
			{
				pText= GetTxtFromMgr(3366);
				StringCchCopy(strFileName, 128, pText); 
			}
			break;
		case HORSEUNIQUE_WHITE:
			{
				pText= GetTxtFromMgr(3367);
				StringCchCopy(strFileName, 128, pText); 
			}break;
		case HORSEUNIQUE_RED:	
			{
				pText= GetTxtFromMgr(2753);
				StringCchCopy(strFileName, 128, pText);	
			}break;
		case HORSEUNIQUE_RUDOLF: 
			{
				 pText= GetTxtFromMgr(3370);
				StringCchCopy(strFileName, 128, pText);	
			}break;
		//KHY - 0911 - ȣ���� �߰�.
		case HORSEUNIQUE_TIGER:
			{
				pText= GetTxtFromMgr(5394);
				StringCchCopy(strFileName,	128, pText);	
			}break;
		case HORSEUNIQUE_THOUSAND: 
			{
				pText= GetTxtFromMgr(3371);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		case HORSEUNIQUE_STEEL:
			{
				pText= GetTxtFromMgr(5174);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		case HORSEUNIQUE_WOLF:
			{
				pText= GetTxtFromMgr(5622);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		case HORSEUNIQUE_ZEBRA:
			{
				pText = GetTxtFromMgr(3369);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		case HORSEUNIQUE_BEAST:
			{
				pText = GetTxtFromMgr(6418);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
		case HORSEUNIQUE_FOAL:
			{
				pText = GetTxtFromMgr(7505);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		//PCK - 08/02/18 - ��Ÿ�߰�
		case HORSEUNIQUE_CAMEL:
			{
				pText = GetTxtFromMgr(7936);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		//PCK - 08/04/01 - ����S�� �̺�Ʈ ȣ�����߰�
		case HORSEUNIQUE_TIGER2:
			{
				pText = GetTxtFromMgr(5394);
				StringCchCopy(strFileName,	128, pText); 
			}break;
		//PCK - 08/06/12 - �ڳ��� �߰�
		case HORSEUNIQUE_ELEPHANT:
			{
				pText = GetTxtFromMgr(8460);
				StringCchCopy(strFileName, 128, pText);
			}break;
		//PCK - 08/08/14 - ��ȣ �߰�
		case HORSEUNIQUE_WHITETIGER:
			{
				pText = GetTxtFromMgr(8752);
				StringCchCopy(strFileName, 128, pText);
			}break;
		//PCK - 08/09/02 - ������� �߰�
		case HORSEUNIQUE_MOTORCYCLE:
			{
				pText = GetTxtFromMgr(8795);
				StringCchCopy(strFileName, 128, pText);
			}break;
		//PCK - 08/12/10 - ����ġ �߰�
		case HORSEUNIQUE_FIREHATCH:
			{
				pText = GetTxtFromMgr(2788);
				StringCchCopy(strFileName, 128, pText);
			}break;
		// ü��� �鸶 : �ռ���-2009.03.17
		case HORSEUNIQUE_WHITE_TEST:
			{
				pText = GetTxtFromMgr(9897);
				StringCchCopy(strFileName, 128, pText);
			}break;
		//PCK - 09/07/30 - ������Ʈ �߰�
		case HORSEUNIQUE_BAPHOMET:
			{
				pText = GetTxtFromMgr(30304);
				StringCchCopy(strFileName, 128, pText);
			}break;
		//���� - 09/08/30 - ȸ�� ���� �߰�
		case HORSEUNIQUE_GRAYWOLF:
			{
				pText = GetTxtFromMgr(5622);
				StringCchCopy(strFileName, 128, pText);
			}break;
		//���� - 09/12/31 - ����� �߰�
		case HORSEUNIQUE_SASURI:
			{
				pText = GetTxtFromMgr(14035);
				StringCchCopy(strFileName, 128, pText);
			}break;
		default:
			{
				pText= GetTxtFromMgr(3372);
				StringCchCopy(strFileName, 128, pText);	
			}break;
		}
		// leon - todo strFileName ���� �ϴ� ���ڿ� �׽�Ʈ �ʿ�!
		SI16 tmpSelectedIndex = 0;

		if(pclhorse->siHorseUnique == 12)		//KHY - 0717 - �������� 
			tmpSelectedIndex = 49;
		else
			tmpSelectedIndex = pclClient->pclKindInfoSet->FindKindFromName( strFileName );			

		TCHAR szPortrait[256];
		SI32 siPortraitFont;
		pclClient->pclKindInfoSet->GetNPCImageFileAndFont(tmpSelectedIndex, szPortrait, sizeof(szPortrait), &siPortraitFont);

		m_pImagestatic_portrait->SetFileName( szPortrait );
		m_pImagestatic_portrait->SetFontIndex( siPortraitFont );


		// ���� ��ư�� ������� �� ��츸 ���δ�.
		if(pclhorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE)
		{
			m_pButton_oilling->Show(true);
		}
		else
		{
			m_pButton_oilling->Show(false);			
		}

	}

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		return ;
	}

	//if(pclhorse == NULL ) return ;
	//if(pclhorse->siHorseUnique <= 0)return ;

	if(pclhorse == NULL || (pclhorse != NULL && pclhorse->siHorseUnique <= 0))
	{
		m_pImagestatic_portrait->SetFileName(TEXT(""));
        m_pEditbox_horsename->SetText( TEXT("") );
		//m_pStatictext_horsekindname->SetText(TEXT(""), DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		//m_pStatictext_birthdayname->SetText(TEXT(""), DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		//m_pStatictext_agevalue->SetText(TEXT(""), DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		//m_pStatictext_lifevalue->SetText(TEXT(""), DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		//m_pStatictext_sexkind->SetText(TEXT(""), DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		m_pStatictext_horsekindname->SetText(TEXT(""), DT_LEFT|DT_VCENTER|DT_SINGLELINE );
		m_pStatictext_birthdayname->SetText(TEXT(""), DT_LEFT|DT_VCENTER|DT_SINGLELINE );
		m_pStatictext_agevalue->SetText(TEXT(""), DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		m_pStatictext_lifevalue->SetText(TEXT(""), DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		m_pStatictext_sexkind->SetText(TEXT(""), DT_LEFT|DT_VCENTER|DT_SINGLELINE);

		m_pEditbox_strength->SetText(TEXT(""));
		m_pEditbox_dex->SetText(TEXT(""));
		m_pEditbox_magic->SetText(TEXT(""));
		m_pEditbox_speed->SetText(TEXT(""));
		m_pEditbox_bonus->SetText(TEXT(""));
		m_pEditbox_need->SetText(TEXT(""));
	}

	// �� �̸� ����
	if( pclhorse->szName == NULL || _tcslen( pclhorse->szName ) < 1 )
	{
		return;
	}

	// �� ������ ó�� ���� ���
	if ( strHorseName != NULL && _tcslen ( strHorseName) == 0 )
	{
		StringCchCopy( strHorseName, MAX_HORSE_NAME, pclhorse->szName );
		m_pEditbox_horsename->SetText( pclhorse->szName );
	}
	
	// �����κ��� �̸��� �ٲ���ٰ� �뺸�� �� ���
	if ( strHorseName != NULL && _tcslen ( strHorseName) > 0 && _tcscmp( strHorseName, pclhorse->szName ) != 0 )
	{
		StringCchCopy( strHorseName, MAX_HORSE_NAME, pclhorse->szName );
		m_pEditbox_horsename->SetText( pclhorse->szName );
	}


	// ǰ�� ǥ�� 
	SI32 horseunique = pclhorse->siHorseUnique;
	if(horseunique)
	{
		m_pStatictext_horsekindname->SetText( pclClient->pclHorseManager->pclHorseTypeInfo[horseunique]->szSpecies, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	
	// ���� ����. 
	if(pclhorse->clBirthDate.GetDateText(buffer) == TRUE)
	{
		//m_pStatictext_birthdayname->SetText(buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		m_pStatictext_birthdayname->SetText(buffer, DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}

	// ���� ����. 
	cltClient* pclclient = (cltClient*)pclClient;

	SI32 age = pclhorse->GetAge(pclclient->clClientDate.GetDateVary());

	TCHAR* pText = GetTxtFromMgr(594);
	StringCchPrintf(buffer, 256, pText, age);
	//m_pStatictext_agevalue->SetText(buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	m_pStatictext_agevalue->SetText(buffer, DT_LEFT|DT_VCENTER|DT_SINGLELINE );

	// ���� ���� ����. 
	SI32 siLife = pclclient->pclHorseManager->GetLife(pclhorse, pclclient->clClientDate.GetDateVary());
	SI32 siFullLife = pclclient->pclHorseManager->GetFullLife(pclhorse->siHorseUnique);

	//KHY - 1111 - ������� �߰�.
	if(pclhorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE )
	{
		TCHAR life_L[128];
		SI32 siLife_L = pclClient->pclCM->CR[1]->pclCI->clBI.clTimeMeterRateInfo.GetLeftTime( TIMEMETERRATE_MOTORCYCLE );

		if( siLife_L > 0)
		{
			// ���ʹ� �ð������� 2 :1 �̴�.
			siLife_L = siLife_L / (60*2);
		}
		
		g_JYLibFunction.SetNumUnit( siLife_L, life_L, 128);

		StringCchPrintf(buffer, 256, "%s L", life_L);
		m_pStatictext_lifevalue->SetText(buffer, DT_LEFT|DT_VCENTER|DT_SINGLELINE );		
	}
	else
	{
		if(siLife == MAX_UNLIMITEDHORSE_LIFE)
		{
			m_pStatictext_lifevalue->SetText(GetTxtFromMgr(1287));
		}
		else
		{
			TCHAR life[128];
			TCHAR fullLife[128];

			g_JYLibFunction.SetNumUnit( siLife, life, 128);
			g_JYLibFunction.SetNumUnit( siFullLife, fullLife, 128);

			pText = GetTxtFromMgr(595);
			StringCchPrintf(buffer, 256, pText, life, fullLife);
			//m_pStatictext_lifevalue->SetText(buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
			m_pStatictext_lifevalue->SetText(buffer, DT_LEFT|DT_VCENTER|DT_SINGLELINE );
		}
	}

	// ���� ����. 
	if(pclhorse->siSex == ANIMAL_MALE)
	{
		pText = GetTxtFromMgr(596);
		StringCchPrintf(buffer, 256, pText);
	}
	else
	{
		pText = GetTxtFromMgr(597);
		StringCchPrintf(buffer, 256, pText);
	}
	//m_pStatictext_sexkind->SetText(buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	m_pStatictext_sexkind->SetText(buffer, DT_LEFT|DT_VCENTER|DT_SINGLELINE );

	// �ڵ� �Ա� ��� üũ. 
	if(pclCM->CR[id]->pclCI->clHorseInfo.bAutoFoodSwitch)
	{
		if(m_pCheckbox_autofood->IsCheck() == false )
		{
			m_pCheckbox_autofood->SetCheck( true );			
		}
		
	}
	else
	{
		if(m_pCheckbox_autofood->IsCheck() == true )
		{
			m_pCheckbox_autofood->SetCheck( false );			
		}
	}

	SI32 addstatus = 0 ;
	// �����̾� ���� �߰� �ɷ�
	SI32 addstatus_Str = 0 ;
	SI32 addstatus_Agi = 0 ;
	SI32 addstatus_Wis = 0 ;
	// �����̾� ���� ���̾�α� ���� 
	if ( pclClient->pclHorseManager->GetAddStatusLimitDateVary(pclhorse) > 0 
		&& pclhorse->siStatusTicketNum > 0 
		&& pclclient->clClientDate.GetDateVary() < pclClient->pclHorseManager->GetAddStatusLimitDateVary(pclhorse) ) addstatus += MAX_HORSE_ADDSTATUS ;
	SI32 siPremiumStatus_Slot1 = pclhorse->GetPremiumUnique_Slot1()	;
	SI32 siPremiumStatus_Slot2 = pclhorse->GetPremiumUnique_Slot2()	;
	SI32 siPremiumStatus_Slot3 = pclhorse->GetPremiumUnique_Slot3()	;

	addstatus_Str += GetPremiumStatusHorse_STR( siPremiumStatus_Slot1 ) + GetPremiumStatusHorse_STR( siPremiumStatus_Slot2 ) + GetPremiumStatusHorse_STR( siPremiumStatus_Slot3 )	;
	addstatus_Agi += GetPremiumStatusHorse_AGI( siPremiumStatus_Slot1 ) + GetPremiumStatusHorse_AGI( siPremiumStatus_Slot2 ) + GetPremiumStatusHorse_AGI( siPremiumStatus_Slot3 )	;
	addstatus_Wis += GetPremiumStatusHorse_WIS( siPremiumStatus_Slot1 ) + GetPremiumStatusHorse_WIS( siPremiumStatus_Slot2 ) + GetPremiumStatusHorse_WIS( siPremiumStatus_Slot3 )	;

	// ũ�������� ��� ���� ���̾�α� ����


	
	StringCchPrintf(buffer, 256, TEXT("%3.2f/%3.2f"), (float)pclhorse->siStr/100.0 + addstatus+addstatus_Str , 
		pclClient->pclHorseManager->GetFullStr(pclhorse->siHorseUnique) / 100.0+ addstatus+addstatus_Str);
	m_pEditbox_strength->SetText( buffer );

	// ���߷�  
	StringCchPrintf(buffer, 256, TEXT("%3.2f/%3.2f"), (float)pclhorse->siDex/100.0 + addstatus+addstatus_Agi, 
		pclClient->pclHorseManager->GetFullDex(pclhorse->siHorseUnique) / 100.0+ addstatus+addstatus_Agi);
	m_pEditbox_dex->SetText( buffer );
	
	// ����  
	StringCchPrintf(buffer, 256, TEXT("%3.2f/%3.2f"), (float)pclhorse->siMag/100.0 + addstatus+addstatus_Wis, 
		pclClient->pclHorseManager->GetFullMag(pclhorse->siHorseUnique) / 100.0+ addstatus+addstatus_Wis);
	m_pEditbox_magic->SetText( buffer );
	
	// �ӵ�. 
	StringCchPrintf(buffer, 256, TEXT("%3.2f/%3.2f"), (float)pclhorse->siMoveSpeed/100.0, 
		pclClient->pclHorseManager->GetFullSpeed(pclhorse->siHorseUnique) / 100.0);
	m_pEditbox_speed->SetText( buffer );

	// ���ʽ�.
	StringCchPrintf(buffer, 256, TEXT("%d"), pclhorse->siStatusBonus);
	m_pEditbox_bonus->SetText( buffer );

	// ���� �߰��ɷ��� ���ѳ��ڶ� �䱸������ ǥ���Ѵ�.
	TCHAR text[2048]=TEXT("");
	TCHAR ticketAdddate[256] = TEXT("");
	TCHAR needtext[256] = TEXT("");
	TCHAR tempbuffer_slot1[256] = TEXT("");
	TCHAR tempbuffer_slot2[256] = TEXT("");
	TCHAR tempbuffer_slot3[256] = TEXT("");
	pclClient->pclHorseManager->GetAddStatusLimitDateText(pclhorse,ticketAdddate, sizeof(ticketAdddate));

	if(pclhorse->siNeed)
	{
		pclClient->pclHorseManager->GetNeedText(pclhorse, needtext, sizeof(needtext));
	}
	if( pclhorse != NULL &&
		pclhorse->GetPremiumPartsNum() > 0)
	{
		if(pclhorse->GetPremiumUnique_Slot1() > 0)
		{
			pclClient->pclHorseManager->GetPremiumPartsDateText_Slot1(pclhorse, tempbuffer_slot1, sizeof(tempbuffer_slot1));
		}
		if(pclhorse->GetPremiumUnique_Slot2() > 0)
		{
			pclClient->pclHorseManager->GetPremiumPartsDateText_Slot2(pclhorse, tempbuffer_slot2, sizeof(tempbuffer_slot2));
		}
		if(pclhorse->GetPremiumUnique_Slot3() > 0)
		{
			pclClient->pclHorseManager->GetPremiumPartsDateText_Slot3(pclhorse, tempbuffer_slot3, sizeof(tempbuffer_slot3));
		}
	}
	sprintf( text,"%s%S%s%s%s",ticketAdddate,needtext,tempbuffer_slot1,tempbuffer_slot2,tempbuffer_slot3);
	m_pEditbox_need->SetText(text);

	//SI32 ButtonDlg[] = {
	//	IDC_BUTTON_HORSE_SPEED,
	//	IDC_BUTTON_HORSE_STR, 
	//	IDC_BUTTON_HORSE_DEX,
	//	IDC_BUTTON_HORSE_MAG,
	//	-1
	//};

	//SI32 index = 0 ;
	// ���ʽ� ��ġ ������ ��ư�� �����Ѵ�. 
	if( pclhorse->siStatusBonus > 0 )
	{
		if(BonusHorseButtonEnableSwitch == FALSE)
		{
			BonusHorseButtonEnableSwitch = TRUE;

			//index = 0;
			//while(ButtonDlg[index] >0)
			//{
			//	hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
			//	EnableWindow(hwnd, TRUE);

			//	index++;
			//}
		}
		m_pButton_speed->Enable( true );
		m_pButton_strength->Enable( true );
		m_pButton_dex->Enable( true );
		m_pButton_magic->Enable( true );
	}
	else
	{
		if(BonusHorseButtonEnableSwitch == TRUE)
		{
			BonusHorseButtonEnableSwitch = FALSE;

			//index = 0;
			//while(ButtonDlg[index] >0)
			//{
			//	hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
			//	EnableWindow(hwnd, FALSE);

			//	index++;
			//}
		}
		m_pButton_speed->Enable( false );
		m_pButton_strength->Enable( false );
		m_pButton_dex->Enable( false );
		m_pButton_magic->Enable( false );
	}
}

void cltNHorseStatus::SendUseHorseBonusMessageToServer(SI08 data)
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id)
	{
		cltMsg clMsg(GAMEMSG_REQUEST_USEHORSE_BONUS, 1, (BYTE*)&data);
		cltClient* pclclient = (cltClient*)pclClient;
		pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
	}
}

void cltNHorseStatus::Action()
{
	UpdateHorseStatusInfo();
}

void cltNHorseStatus::Hide()
{
	m_bShow = false;
	CControllerMgr::Show( false );
}

void cltNHorseStatus::Show()
{
	m_bShow = true;
	CControllerMgr::Show( true );
}

bool cltNHorseStatus::IsShow()
{
    return m_bShow;
}

void cltNHorseStatus::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient*)pclClient;

	switch( MsgIndex )
	{
	case 10: // �� �ɷ� �ʱ�ȭ
		{
			if( RetValue )
			{
				cltMsg clMsg(GAMEMSG_REQUEST_HORSEINIT,0);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		break;
	case 11: // �� �ɷ� �⼧
		{
			if( RetValue )
			{
				cltMsg clMsg(GAMEMSG_REQUEST_HORSE_ADDSTATUS,0);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		break;
	case 12:	// ��Ǯ���ֱ�
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				TCHAR *pTitle = NULL;
				TCHAR *pText = NULL;
				// ���� Ÿ�� ������ ����. 
				//KHY - 1001 - ��µ��� 5���� ���� ����.
				//if(pclCM->CR[*((SI32*)pData)]->pclCI->clHorseInfo.siCurrentHorseIndex >= 0)
				if(pclCM->CR[*((SI32*)pData)]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
				{
					pTitle = GetTxtFromMgr(575);
					pText = GetTxtFromMgr(579);

					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					return;
				}
				
				// �� �κ��� ��ǰ�� ������ Ǯ���� �� ����. 
				if(pclCM->CR[*((SI32*)pData)]->pclCI->clCharItem.IsHorseHaveItem() == true)
				{
					pTitle = GetTxtFromMgr(575);
					pText = GetTxtFromMgr(580);

					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					return;
				}
														
				cltMsg clMsg(GAMEMSG_REQUEST_HORSEFREE, 0, NULL);
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);					
			}
		}
		break;
	case 13: // �����ϱ�.
		{
			if( RetValue )
			{
				SI32 itemunique = *((SI32*)pData);
			
				cltGameMsgRequest_UseOillingItem clinfo( itemunique );
				cltMsg clMsg( GAMEMSG_REQUEST_OILLING_USEITEM , sizeof(clinfo), (BYTE*)&clinfo );
				pclclient->SendMsgToServer( (sPacketHeader*)&clMsg );
			}
		}
		break;
	}
	return;
}

//#endif
SI32 cltNHorseStatus::GetPremiumStatusHorse_AGI( SI32 siSlotUnique )	// �����̾� ������ ���ؼ� ��� ����
{
	SI32 addstatus_Agi = 0	;
	switch ( siSlotUnique )
	{
	case ITEMUNIQUE(13635) :
	case ITEMUNIQUE(13638) :
		{
			addstatus_Agi += MAX_HORSE_PREMIUMPARTS	;
		}
		break ;
	}
	return addstatus_Agi	;
}
SI32 cltNHorseStatus::GetPremiumStatusHorse_STR( SI32 siSlotUnique )	// �����̾� ������ ���ؼ� ��� ����
{
	SI32 addstatus_Str = 0	;
	switch ( siSlotUnique )
	{
	case ITEMUNIQUE(13636):
	case ITEMUNIQUE(13639):
		{
			addstatus_Str += MAX_HORSE_PREMIUMPARTS	;
		}break ;
	}
	return addstatus_Str	;
}
SI32 cltNHorseStatus::GetPremiumStatusHorse_WIS( SI32 siSlotUnique )	// �����̾� ������ ���ؼ� ��� ����
{
	SI32 addstatus_Wis = 0	;
	switch ( siSlotUnique )
	{
	case ITEMUNIQUE(13637):
	case ITEMUNIQUE(13640):
		{
			addstatus_Wis += MAX_HORSE_PREMIUMPARTS	;
		}break ;
	}
	return addstatus_Wis	;
}