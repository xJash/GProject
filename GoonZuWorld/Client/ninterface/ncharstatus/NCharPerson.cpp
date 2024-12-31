//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
/* ==========================================================================
Ŭ���� :

�ۼ��� :		05/03/14
�ۼ��� :		���뷡

������� :		����

�����۾� :		1. CharUnique�� ���� ����?
2. // leon todo - Ȯ�� �ʿ� wParan == ��������Ʈ��ID������ ������!! nControlID ?

========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#include "..\Client\Client.h"
#include "./NCharPerson.h"
#include "NCharStatus.h"
#include "../../../Common/Father/Father.h"

#include "../../../../NLib/NTCHARString.h"

#include "..\resource.h"
#include "..\Server\Rank\Rank.h"
#include "..\..\Client\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\..\Client\Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "../../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "Msg\MsgType-Horse.h"
#include "Msg\MsgType-Summon.h"
#include "../../../Common/JWLib/IsCorrectID/IsCorrectID.h"
#include "../../lib/WebHTML/WebHTML.h"
#include "..\..\Client\Music\Music.h"
#include "../common/Event/event.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "HintDlg/HintDlg.h"
#include "Char\CharManager\CharManager.h"
#include "Skill/Skill-Manager.h"

//-----------------------------
// CommonLogic
//-----------------------------
#include "..\CommonLogic\msgType-Person.h"

#include "../../Client/InterfaceMgr/Interface/Button.h"
#include "../../Client/InterfaceMgr/Interface/ImageStatic.h"
#include "../../Client/InterfaceMgr/Interface/Static.h"
#include "../../Client/InterfaceMgr/Interface/Edit.h"
#include "../../Client/InterfaceMgr/Interface/ComboBox.h"
#include "../../../Client/InterfaceMgr/Interface/OutLine.h"


#include "../../Client/InterfaceMgr/InterfaceMgr.h"
#include "../../Client/InterfaceMgr/InterfaceFile.h"
#include "NInterface/NHintDlg/NHintDlg.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "ninterface/ncharstatus/NCharAbilityDatailDlg.h"


extern cltCommonLogic* pclClient;

cltNPersonStatus::cltNPersonStatus(cltCharManager* pclcm)
{
	m_pImagestatic_portrait			= NULL; 
	m_pStatictext_level				= NULL; 
	m_pButton_changename			= NULL; 
	m_pStatictext_exp				= NULL; 
	m_pStatictext_expvalue			= NULL; 
	m_pStatictext_magic1			= NULL; 
	m_pStatictext_magic1value		= NULL; 
	m_pStatictext_health			= NULL; 
	m_pStatictext_healthvalue		= NULL; 
	m_pStatictext_life				= NULL; 
	m_pStatictext_lifevalue			= NULL; 
	m_pStatictext_fame				= NULL; 
	m_pStatictext_famevalue			= NULL; 
	m_pStatictext_country			= NULL;
	m_pStatictext_countryex			= NULL;
	m_pStatictext_life2				= NULL; 
	m_pStatictext_strength			= NULL; 
	m_pStatictext_dex	 			= NULL; 
	m_pStatictext_magic	 			= NULL; 
	m_pStatictext_bonus	 			= NULL; 
	m_pEditbox_life2	 			= NULL; 
	m_pEditbox_strength	 			= NULL; 
	m_pEditbox_dex					= NULL; 
	m_pEditbox_magic				= NULL; 
	m_pEditbox_bonus				= NULL; 
	m_pButton_life2_plus			= NULL; 
	m_pButton_strength_plus			= NULL; 
	m_pButton_dex_plus				= NULL; 
	m_pButton_magic_plus			= NULL; 
	m_pButton_changekind			= NULL; 
	m_pButton_greeting				= NULL;
	m_pButton_naming				= NULL;
	m_pButton_explain				= NULL; 
	m_pButton_init					= NULL; 
	m_pEditbox_health_explain	 	= NULL; 
	m_pStatictext_levelvalue	 	= NULL; 
	m_pStatictext_hand				= NULL; 
	m_pEditbox_hand					= NULL; 
	m_pButton_hand_plus				= NULL; 

	m_pStatictext_luk				= NULL; 
	m_pEditbox_luk					= NULL; 
	m_pButton_luk_plus	 			= NULL; 
	m_pButton_luk_minus	 			= NULL; 
	m_pCombobox_luk					= NULL;

	m_pButton_strength_minus		= NULL; 
	m_pButton_dex_minus				= NULL; 
	m_pButton_magic_minus	 		= NULL; 
	m_pButton_life2_minus	 		= NULL; 
	m_pButton_hand_minus	 		= NULL;  
	m_pCombobox_strength	 		= NULL; 
	m_pCombobox_dex	 				= NULL; 
	m_pCombobox_magic				= NULL; 
	m_pCombobox_life2				= NULL; 
	m_pCombobox_hand				= NULL; 
	m_pStatictext_totalspeed	 	= NULL; 
	m_pStatictext_totaldamage	 	= NULL; 
	m_pStatictext_armourdefense	 	= NULL; 
	m_pEditbox_totalspeed		 	= NULL; 
	m_pEditbox_totaldamage			= NULL; 
	m_pEditbox_armourdefense		= NULL; 
	m_pCombobox_detail_speed		= NULL; 
	m_pCombobox_apowername	 		= NULL; 
	m_pCombobox_dpowername	 		= NULL; 
	m_pStatictext_rank	 			= NULL;
	m_pStatictext_rank2	 			= NULL;
	m_pButton_nolimitwarp			= NULL; 

	m_pOutline_noname1	 			= NULL; 
	m_pOutline_noname2	 			= NULL; 

	m_pButton_StatusClear			= NULL;
	m_pButton_StatusApply			= NULL;

	
	m_pEditbox_Wisdom		 			=  NULL;
	m_pStatictext_name		 			=  NULL;
	m_pStatictext_namevalue  			=  NULL;
	m_pOutline_NONAME3		 			=  NULL;
	m_pOutline_NONAME4					=  NULL;
	m_pButton_ability_detail 			=  NULL;
	m_pButton_Wisdom_plus	 			=  NULL;
	m_pButton_Wisdom_minus	 			=  NULL;
	m_pButton_Elixir					=  NULL;
	m_pStatictext_physical_attack		=  NULL;
	m_pEditbox_physical_attack			=  NULL;
	m_pStatictext_pysical_defense		=  NULL;
	m_pEditbox_pysical_defense			=  NULL;
	m_pStatictext_masic_attack			=  NULL;
	m_pEditbox_magic_attack				=  NULL;
	m_pStatictext_magic_defense			=  NULL;
	m_pEditbox_magic_defense			=  NULL;
	m_pStatictext_pysical_hit_rank		=  NULL;
	m_pEditbox_pysical_hit_rank			=  NULL;
	m_pStatictext_pysical_dodge_rank	=  NULL;
	m_pEditbox_pysical_dodge_rank		=  NULL;
	m_pStatictext_magic_hit_rank		=  NULL;
	m_pEditbox_magic_hit_rank			=  NULL;
	m_pStatictext_magic_dodge_rank		=  NULL;
	m_pEditbox_magic_dodge_rank			=  NULL;
	m_pStatictext_move_speed			=  NULL;
	m_pEditbox_move_speed				=  NULL;
	m_pImageStatic_bonus				=  NULL;
	m_pStatictext_HP 					=  NULL;
	m_pStatictext_MP 					=  NULL;
	m_pStatictext_EXP					=  NULL;
	m_pStatictext_FULL_EXP				=  NULL;

	m_pStaticEditbox_strength			= NULL;	
	m_pStaticEditbox_hand				= NULL;
	m_pStaticEditbox_dex				= NULL;		 
	m_pStaticEditbox_magic				= NULL;	
	m_pStaticEditbox_Wisdom				= NULL;	
	m_pStaticEditbox_life2				= NULL;	
	m_pStaticEditbox_luk				= NULL;		




	m_bShow			= false;
	pclCM			= pclcm;

	CharUnique		= 0;

	m_siTempStr 	= 0;
	m_siTempDex 	= 0;
	m_siTempMag 	= 0;
	m_siTempVit 	= 0;
	m_siTempHnd 	= 0;
	m_siTempLuk 	= 0;
	m_siTempWisdom	= 0;

	//[����] �������� ����� �̹��� �ε�.
	GP.LoadSprFromFile( TEXT("gimg/StatusGaugeBack2.SPR"),				&m_sprGageBack );
	GP.LoadSprFromFile( TEXT("Interface/Pannel/IMAGE_2x10_00_000.SPR"), &m_sprGage );
}

cltNPersonStatus::~cltNPersonStatus()
{
	if( 	m_pImagestatic_portrait	 )  	delete 	m_pImagestatic_portrait	;
	if( 	m_pStatictext_level	 )  		delete 	m_pStatictext_level	;
	if( 	m_pButton_changename	 )  	delete 	m_pButton_changename	;
	if( 	m_pStatictext_exp	 )  		delete 	m_pStatictext_exp	;
	if( 	m_pStatictext_expvalue	 )  	delete 	m_pStatictext_expvalue	;
	if( 	m_pStatictext_magic1	 )  	delete 	m_pStatictext_magic1	;
	if( 	m_pStatictext_magic1value	 )  delete 	m_pStatictext_magic1value	;
	if( 	m_pStatictext_health	 )  	delete 	m_pStatictext_health	;
	if( 	m_pStatictext_healthvalue	 )  delete 	m_pStatictext_healthvalue	;
	if( 	m_pStatictext_life	 )  		delete 	m_pStatictext_life	;
	if( 	m_pStatictext_lifevalue	 )  	delete 	m_pStatictext_lifevalue	;
	if( 	m_pStatictext_fame	 )  		delete 	m_pStatictext_fame	;
	if( 	m_pStatictext_famevalue	 )  	delete 	m_pStatictext_famevalue	;
	if( 	m_pStatictext_life2	 )  		delete 	m_pStatictext_life2	;
	if( 	m_pStatictext_strength	 )  	delete 	m_pStatictext_strength	;
	if( 	m_pStatictext_dex	 )  		delete 	m_pStatictext_dex	;
	if( 	m_pStatictext_magic	 )  		delete 	m_pStatictext_magic	;
	if( 	m_pStatictext_bonus	 )  		delete 	m_pStatictext_bonus	;
	if( 	m_pEditbox_life2	 )  		delete 	m_pEditbox_life2	;
	if( 	m_pEditbox_strength	 )  		delete 	m_pEditbox_strength	;
	if( 	m_pEditbox_dex	 )  			delete 	m_pEditbox_dex	;
	if( 	m_pEditbox_magic	 )  		delete 	m_pEditbox_magic	;
	if( 	m_pEditbox_bonus	 )  		delete 	m_pEditbox_bonus	;
	if( 	m_pButton_life2_plus	 )  	delete 	m_pButton_life2_plus	;
	if( 	m_pButton_strength_plus	 )  	delete 	m_pButton_strength_plus	;
	if( 	m_pButton_dex_plus	 )  		delete 	m_pButton_dex_plus	;
	if( 	m_pButton_magic_plus	 )  	delete 	m_pButton_magic_plus	;
	if( 	m_pButton_changekind	 )  	delete 	m_pButton_changekind	;
	if(		m_pButton_greeting	)			delete m_pButton_greeting;
	if( 	m_pButton_explain	 )  		delete 	m_pButton_explain	;
	if( 	m_pButton_init	 )  			delete 	m_pButton_init	;
	if( 	m_pEditbox_health_explain	 )  delete 	m_pEditbox_health_explain	;
	if( 	m_pStatictext_levelvalue	 )  delete 	m_pStatictext_levelvalue	;
	if( 	m_pStatictext_hand	 )  		delete 	m_pStatictext_hand	;
	if( 	m_pEditbox_hand	 )  			delete 	m_pEditbox_hand	;
	if( 	m_pButton_hand_plus	 )  		delete 	m_pButton_hand_plus	;
	if(		m_pStatictext_luk	)  			delete 	m_pStatictext_luk;
	if(		m_pEditbox_luk	)  				delete 	m_pEditbox_luk;
	if(		m_pButton_luk_plus	)  			delete 	m_pButton_luk_plus;
	if(		m_pButton_luk_minus	)  			delete 	m_pButton_luk_minus;
	if(		m_pCombobox_luk		)			delete	m_pCombobox_luk;
	if( 	m_pButton_strength_minus	 )  delete 	m_pButton_strength_minus	;
	if( 	m_pButton_dex_minus	 )  		delete 	m_pButton_dex_minus	;
	if( 	m_pButton_magic_minus	 )  	delete 	m_pButton_magic_minus	;
	if( 	m_pButton_life2_minus	 )  	delete 	m_pButton_life2_minus	;
	if( 	m_pButton_hand_minus	 )  	delete 	m_pButton_hand_minus	;
	if( 	m_pCombobox_strength	 )  	delete 	m_pCombobox_strength	;
	if( 	m_pCombobox_dex	 )  			delete 	m_pCombobox_dex	;
	if( 	m_pCombobox_magic	 )  		delete 	m_pCombobox_magic	;
	if( 	m_pCombobox_life2	 )  		delete 	m_pCombobox_life2	;
	if( 	m_pCombobox_hand	 )  		delete 	m_pCombobox_hand	;
	if( 	m_pStatictext_totalspeed	 )  delete 	m_pStatictext_totalspeed	;
	if( 	m_pStatictext_totaldamage	 )  delete 	m_pStatictext_totaldamage	;
	if( 	m_pStatictext_armourdefense	 )  delete 	m_pStatictext_armourdefense	;
	if( 	m_pEditbox_totalspeed	 )  	delete 	m_pEditbox_totalspeed	;
	if( 	m_pEditbox_totaldamage	 )  	delete 	m_pEditbox_totaldamage	;
	if( 	m_pEditbox_armourdefense	 )  delete 	m_pEditbox_armourdefense	;
	if( 	m_pCombobox_detail_speed	 )  delete 	m_pCombobox_detail_speed	;
	if( 	m_pCombobox_apowername	 )  	delete 	m_pCombobox_apowername	;
	if( 	m_pCombobox_dpowername	 )  	delete 	m_pCombobox_dpowername	;
	if( 	m_pStatictext_rank	 )  		delete 	m_pStatictext_rank	;
	if(		m_pStatictext_rank2  )			delete	m_pStatictext_rank2	;
	if( 	m_pButton_nolimitwarp	 )  	delete 	m_pButton_nolimitwarp	;
	if( 	m_pOutline_noname1	 )  		delete 	m_pOutline_noname1	;
	if( 	m_pOutline_noname2	 )  		delete 	m_pOutline_noname2	;

	SAFE_DELETE( m_pButton_naming				);
	SAFE_DELETE( m_pStatictext_country			);
	SAFE_DELETE( m_pStatictext_countryex		);
	SAFE_DELETE(m_pButton_StatusClear			);
	SAFE_DELETE(m_pButton_StatusApply			);
	
	SAFE_DELETE(m_pEditbox_Wisdom		 		);
	SAFE_DELETE(m_pStatictext_name		 		);
	SAFE_DELETE(m_pStatictext_namevalue  		);
	SAFE_DELETE(m_pOutline_NONAME3		 		);
	SAFE_DELETE(m_pOutline_NONAME4		 		);
	SAFE_DELETE(m_pButton_ability_detail 		);
	SAFE_DELETE(m_pButton_Wisdom_plus	 		);
	SAFE_DELETE(m_pButton_Wisdom_minus	 		);
	SAFE_DELETE(m_pButton_Elixir				);
	SAFE_DELETE(m_pStatictext_physical_attack	);
	SAFE_DELETE(m_pEditbox_physical_attack		);
	SAFE_DELETE(m_pStatictext_pysical_defense	);
	SAFE_DELETE(m_pEditbox_pysical_defense		);
	SAFE_DELETE(m_pStatictext_masic_attack		);
	SAFE_DELETE(m_pEditbox_magic_attack			);
	SAFE_DELETE(m_pStatictext_magic_defense		);
	SAFE_DELETE(m_pEditbox_magic_defense		);
	SAFE_DELETE(m_pStatictext_pysical_hit_rank	);
	SAFE_DELETE(m_pEditbox_pysical_hit_rank		);
	SAFE_DELETE(m_pStatictext_pysical_dodge_rank);
	SAFE_DELETE(m_pEditbox_pysical_dodge_rank	);
	SAFE_DELETE(m_pStatictext_magic_hit_rank	);
	SAFE_DELETE(m_pEditbox_magic_hit_rank		);
	SAFE_DELETE(m_pStatictext_magic_dodge_rank	);
	SAFE_DELETE(m_pEditbox_magic_dodge_rank		);
	SAFE_DELETE(m_pStatictext_move_speed		);
	SAFE_DELETE(m_pEditbox_move_speed			);
	SAFE_DELETE(m_pImageStatic_bonus			);
	SAFE_DELETE(m_pStatictext_HP 				);
	SAFE_DELETE(m_pStatictext_MP 				);
	SAFE_DELETE(m_pStatictext_EXP				);
	SAFE_DELETE(m_pStatictext_FULL_EXP			);

	SAFE_DELETE(m_pStaticEditbox_strength		);
	SAFE_DELETE(m_pStaticEditbox_hand			);
	SAFE_DELETE(m_pStaticEditbox_dex			);
	SAFE_DELETE(m_pStaticEditbox_magic			);
	SAFE_DELETE(m_pStaticEditbox_Wisdom			);
	SAFE_DELETE(m_pStaticEditbox_life2			);
	SAFE_DELETE(m_pStaticEditbox_luk			);
	

	SetTimerOnOff( false );
}

void cltNPersonStatus::Create( CControllerMgr *pParent )
{
	//if ( ! IsCreate() )
	{
		cltClient *pclclient = (cltClient*)pclClient;
		CharUnique = pclclient->MyCharUnique;

		//CDialogController::Create( CLTNPERSONSTATUS_DLG, CONTROLLER_KIND_CHILDDIALOG, pParent, NPersonStatusStaticProc, NULL, NULL, 0, false, 10, 40, 325, 480, false, false, false);

		CInterfaceFile file;

		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			file.LoadFile(TEXT("NInterface/Data/NCharStatusDlg/DLG_NCharStatus_Child_NPerson_New.ddf"));
		}
		else
		{
			file.LoadFile(TEXT("NInterface/Data/NCharStatusDlg/DLG_NCharStatus_Child_NPerson.ddf"));
		}
				
		file.CreateChildDialog( this, CLTNPERSONSTATUS_DLG, TEXT("dialog_person"), NPersonStatusStaticProc, pParent );

		// ���̾�α� ��ġ ����
		SetDialogPos( ((cltNCharStatus*)pParent)->GetChildDlgXPos(), ((cltNCharStatus*)pParent)->GetChildDlgYPos(), GetWidth(), GetHeight() );

		m_pImagestatic_portrait		= new 	CImageStatic ( this )	;
		m_pStatictext_level			= new 	CStatic	( this )	;
		m_pButton_changename		= new 	CButton	( this )	;
		m_pStatictext_exp			= new 	CStatic	( this )	;
		m_pStatictext_expvalue		= new 	CStatic	( this )	;
		m_pStatictext_magic1		= new 	CStatic	( this )	;
		m_pStatictext_magic1value	= new 	CStatic	( this )	;
		m_pStatictext_health		= new 	CStatic	( this )	;
		m_pStatictext_healthvalue	= new 	CStatic	( this )	;
		m_pStatictext_life			= new 	CStatic	( this )	;
		m_pStatictext_lifevalue		= new 	CStatic	( this )	;
		m_pStatictext_fame			= new 	CStatic	( this )	;
		m_pStatictext_famevalue		= new 	CStatic	( this )	;
		m_pStatictext_country		= new	CStatic ( this )	;
		m_pStatictext_countryex		= new	CStatic ( this )	;
		m_pStatictext_life2			= new 	CStatic	( this )	;
		m_pStatictext_strength		= new 	CStatic	( this )	;
		m_pStatictext_dex	 		= new 	CStatic	( this )	;
		m_pStatictext_magic	 		= new 	CStatic	( this )	;
		m_pStatictext_bonus	 		= new 	CStatic	( this )	;
		m_pEditbox_life2	 		= new 	CEdit	( this )	;
		m_pEditbox_strength	 		= new 	CEdit	( this )	;
		m_pEditbox_dex				= new 	CEdit	( this )	;
		m_pEditbox_magic	 		= new 	CEdit	( this )	;
		m_pEditbox_bonus	 		= new 	CEdit	( this )	;
		m_pButton_life2_plus	 	= new 	CButton	( this )	;
		m_pButton_strength_plus	 	= new 	CButton	( this )	;
		m_pButton_dex_plus			= new 	CButton	( this )	;
		m_pButton_magic_plus		= new 	CButton	( this )	;
		m_pButton_changekind		= new 	CButton	( this )	;
		m_pButton_greeting			= new   CButton ( this )	;
		NEWCBUTTON( m_pButton_naming )
		m_pButton_explain			= new 	CButton	( this )	;
		m_pButton_init				= new 	CButton	( this )	;
		m_pEditbox_health_explain	= new 	CEdit	( this )	;
		m_pStatictext_levelvalue	= new 	CStatic	( this )	;
		m_pStatictext_hand			= new 	CStatic	( this )	;
		m_pEditbox_hand				= new 	CEdit	( this )	;
		m_pButton_hand_plus			= new 	CButton	( this )	;

		m_pStatictext_luk			= new CStatic(this);
		m_pEditbox_luk				= new CEdit(this);
		m_pButton_luk_plus			= new CButton(this);
		m_pButton_luk_minus			= new CButton(this);
		m_pCombobox_luk				= new CComboBox(this);

		m_pButton_strength_minus	= new 	CButton	( this )	;
		m_pButton_dex_minus			= new 	CButton	( this )	;
		m_pButton_magic_minus		= new 	CButton	( this )	;
		m_pButton_life2_minus		= new 	CButton	( this )	;
		m_pButton_hand_minus		= new 	CButton	( this )	;
		m_pStatictext_totalspeed	= new 	CStatic	( this )	;
		m_pStatictext_totaldamage	= new 	CStatic	( this )	;
		m_pStatictext_armourdefense	= new 	CStatic	( this )	;
		m_pEditbox_totalspeed		= new 	CEdit	( this )	;
		m_pEditbox_totaldamage		= new 	CEdit	( this )	;
		m_pEditbox_armourdefense	= new 	CEdit	( this )	;
		m_pStatictext_rank			= new 	CStatic	( this )	;
		m_pStatictext_rank2			= new	CStatic	( this )	;
		m_pButton_nolimitwarp		= new 	CButton	( this )	;

		m_pCombobox_dpowername		= new 	CComboBox	( this )	;
		m_pCombobox_apowername		= new 	CComboBox	( this )	;
		m_pCombobox_detail_speed	= new 	CComboBox	( this )	;

		m_pCombobox_hand			= new 	CComboBox	( this )	;
		m_pCombobox_life2			= new 	CComboBox	( this )	;
		m_pCombobox_magic			= new 	CComboBox	( this )	;
		m_pCombobox_dex				= new 	CComboBox	( this )	;
		m_pCombobox_strength		= new 	CComboBox	( this )	;

		m_pOutline_noname1	 		= new 	COutLine	( this )	;
		m_pOutline_noname2	 		= new 	COutLine	( this )	;

		m_pButton_StatusApply 		= new CButton ( this ) ;
		m_pButton_StatusClear 		= new CButton ( this ) ;

		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		//if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			m_pStaticEditbox_strength			= new 	CEdit( this );
			m_pStaticEditbox_hand				= new 	CEdit( this );
			m_pStaticEditbox_dex				= new 	CEdit( this );
			m_pStaticEditbox_magic				= new 	CEdit( this );
			m_pStaticEditbox_Wisdom				= new 	CEdit( this );
			m_pStaticEditbox_life2				= new 	CEdit( this );
			m_pStaticEditbox_luk				= new 	CEdit( this );
					
			m_pEditbox_Wisdom		 			= new 	CEdit( this );
			m_pStatictext_name		 			= new	CStatic	( this );	
			m_pStatictext_namevalue  			= new	CStatic	( this );
			m_pOutline_NONAME3		 			= new	COutLine ( this );
			m_pOutline_NONAME4		 			= new	COutLine ( this );
			m_pButton_ability_detail 			= new 	CButton ( this ) ;
			m_pButton_Wisdom_plus	 			= new 	CButton ( this ) ;
			m_pButton_Wisdom_minus	 			= new 	CButton ( this ) ;
			m_pButton_Elixir					= new 	CButton ( this ) ;
			m_pStatictext_physical_attack		= new	CStatic	( this ); 		
			m_pEditbox_physical_attack			= new 	CEdit( this );		
			m_pStatictext_pysical_defense		= new	CStatic	( this );		
			m_pEditbox_pysical_defense			= new 	CEdit( this );		
			m_pStatictext_masic_attack			= new	CStatic	( this );			
			m_pEditbox_magic_attack				= new 	CEdit( this );			
			m_pStatictext_magic_defense			= new	CStatic	( this );		
			m_pEditbox_magic_defense			= new 	CEdit( this );			
			m_pStatictext_pysical_hit_rank		= new	CStatic	( this );		
			m_pEditbox_pysical_hit_rank			= new 	CEdit( this );		
			m_pStatictext_pysical_dodge_rank	= new	CStatic	( this );	
			m_pEditbox_pysical_dodge_rank		= new 	CEdit( this );	
			m_pStatictext_magic_hit_rank		= new	CStatic	( this );		
			m_pEditbox_magic_hit_rank			= new 	CEdit( this );		
			m_pStatictext_magic_dodge_rank		= new	CStatic	( this );		
			m_pEditbox_magic_dodge_rank			= new 	CEdit( this );		
			m_pStatictext_move_speed			= new	CStatic	( this );			
			m_pEditbox_move_speed				= new 	CEdit( this );				
			m_pImageStatic_bonus				= new   CImageStatic( this );
			m_pStatictext_HP					= new	CStatic( this );	
			m_pStatictext_MP					= new 	CStatic( this );		
			m_pStatictext_EXP					= new   CStatic( this );
			m_pStatictext_FULL_EXP				= new   CStatic( this );
		}
				


		file.CreateControl( m_pImagestatic_portrait, CLTNPERSONSTATUS_DLG_IMAGESTATIC_PORTRAIT, TEXT("imagestatic_portrait") );
		file.CreateControl( m_pStatictext_level, CLTNPERSONSTATUS_DLG_STATICTEXT_LEVEL, TEXT("statictext_level") );
		file.CreateControl( m_pButton_changename, CLTNPERSONSTATUS_DLG_BUTTON_CHANGENAME, TEXT("button_changename") );
		
		file.CreateControl( m_pStatictext_bonus, CLTNPERSONSTATUS_DLG_STATICTEXT_BONUS, TEXT("statictext_bonus") );
		file.CreateControl( m_pEditbox_life2, CLTNPERSONSTATUS_DLG_EDITBOX_LIFE2, TEXT("editbox_life2") );
		file.CreateControl( m_pEditbox_strength, CLTNPERSONSTATUS_DLG_EDITBOX_STRENGTH, TEXT("editbox_strength") );
		file.CreateControl( m_pEditbox_dex, CLTNPERSONSTATUS_DLG_EDITBOX_DEX, TEXT("editbox_dex") );
		file.CreateControl( m_pEditbox_magic, CLTNPERSONSTATUS_DLG_EDITBOX_MAGIC, TEXT("editbox_magic") );
		file.CreateControl( m_pEditbox_bonus, CLTNPERSONSTATUS_DLG_EDITBOX_BONUS, TEXT("editbox_bonus") );
		file.CreateControl( m_pButton_life2_plus, CLTNPERSONSTATUS_DLG_BUTTON_LIFE2_PLUS, TEXT("button_life2_plus") );
		file.CreateControl( m_pButton_strength_plus, CLTNPERSONSTATUS_DLG_BUTTON_STRENGTH_PLUS, TEXT("button_strength_plus") );
		file.CreateControl( m_pButton_dex_plus, CLTNPERSONSTATUS_DLG_BUTTON_DEX_PLUS, TEXT("button_dex_plus") );
		file.CreateControl( m_pButton_magic_plus, CLTNPERSONSTATUS_DLG_BUTTON_MAGIC_PLUS, TEXT("button_magic_plus") );
				
		file.CreateControl( m_pEditbox_health_explain, CLTNPERSONSTATUS_DLG_EDITBOX_HEALTH_EXPLAIN, TEXT("editbox_health_explain") );
		file.CreateControl( m_pStatictext_levelvalue, CLTNPERSONSTATUS_DLG_STATICTEXT_LEVELVALUE, TEXT("statictext_levelvalue") );
		file.CreateControl( m_pEditbox_hand, CLTNPERSONSTATUS_DLG_EDITBOX_HAND, TEXT("editbox_hand") );
		file.CreateControl( m_pButton_hand_plus, CLTNPERSONSTATUS_DLG_BUTTON_HAND_PLUS, TEXT("button_hand_plus") );

		file.CreateControl( m_pEditbox_luk, CLTNPERSONSTATUS_DLG_EDITBOX_LUK, TEXT("editbox_luk") );
	
		file.CreateControl( m_pButton_strength_minus, CLTNPERSONSTATUS_DLG_BUTTON_STRENGTH_MINUS, TEXT("button_strength_minus") );
		file.CreateControl( m_pButton_dex_minus, CLTNPERSONSTATUS_DLG_BUTTON_DEX_MINUS, TEXT("button_dex_minus") );
		file.CreateControl( m_pButton_magic_minus, CLTNPERSONSTATUS_DLG_BUTTON_MAGIC_MINUS, TEXT("button_magic_minus") );
		file.CreateControl( m_pButton_life2_minus, CLTNPERSONSTATUS_DLG_BUTTON_LIFE2_MINUS, TEXT("button_life2_minus") );
		file.CreateControl( m_pButton_hand_minus, CLTNPERSONSTATUS_DLG_BUTTON_HAND_MINUS, TEXT("button_hand_minus") );
		
		file.CreateControl( 	m_pButton_nolimitwarp	, 	CLTNPERSONSTATUS_DLG_BUTTON_NOLIMITWARP	, 	TEXT("button_nolimitwarp")	 )	;
	
		file.CreateControl( m_pButton_StatusClear, CLTNPERSONSTATUS_DLG_BUTTON_STATUSCLEAR , TEXT("button_statusclear") );
		file.CreateControl( m_pButton_StatusApply, CLTNPERSONSTATUS_DLG_BUTTON_STATUSAPPLY , TEXT("button_statusapply") );

		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			file.CreateControl( m_pStaticEditbox_strength,	CLTNPERSONSTATUS_DLG_STATICTEXT_STRENGTH,	TEXT("statictext_strength"));
			file.CreateControl( m_pStaticEditbox_hand,		CLTNPERSONSTATUS_DLG_STATICTEXT_HAND,		TEXT("statictext_hand"));
			file.CreateControl( m_pStaticEditbox_dex,		CLTNPERSONSTATUS_DLG_STATICTEXT_DEX,		TEXT("statictext_dex"));
			file.CreateControl( m_pStaticEditbox_magic,		CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC,		TEXT("statictext_magic"));
			file.CreateControl(	m_pStaticEditbox_Wisdom, 	CLTNPERSONSTATUS_DLG_STATICTEXT_WISDOM,		TEXT("statictext_wisdom"));		
			file.CreateControl( m_pStaticEditbox_life2,		CLTNPERSONSTATUS_DLG_STATICTEXT_LIFE2,		TEXT("statictext_life2"));
			file.CreateControl( m_pStaticEditbox_luk,		CLTNPERSONSTATUS_DLG_STATICTEXT_LUK,		TEXT("statictext_luk"));
			SetBaseStatusToolTip();
		
			file.CreateControl( 	m_pEditbox_Wisdom, 			CLTNPERSONSTATUS_DLG_EDITBOX_WISDOM,		TEXT("editbox_wisdom")			);
			
			file.CreateControl( 	m_pStatictext_name, 		CLTNPERSONSTATUS_DLG_STATICTEXT_NAME,		TEXT("statictext_name")			);
			file.CreateControl( 	m_pStatictext_namevalue, 	CLTNPERSONSTATUS_DLG_STATICTEXT_NAMEVALUE,	TEXT("statictext_namevalue")	);
			
			file.CreateControl( 	m_pButton_ability_detail, 	CLTNPERSONSTATUS_DLG_BUTTON_ABILITY_DETAIL,	TEXT("button_ability_detail")	);
			file.CreateControl( 	m_pButton_Wisdom_plus,		CLTNPERSONSTATUS_DLG_BUTTON_WISDOM_PLUS,	TEXT("button_wisdom_plus")		);
			file.CreateControl( 	m_pButton_Wisdom_minus, 	CLTNPERSONSTATUS_DLG_BUTTON_WISDOM_MINUS,	TEXT("button_wisdom_minus")		);
			file.CreateControl( 	m_pButton_Elixir, 			CLTNPERSONSTATUS_DLG_BUTTON_ELIXIR,			TEXT("button_elixir")			);
			file.CreateControl( m_pButton_luk_plus,		CLTNPERSONSTATUS_DLG_BUTTON_LUK_PLUS,	TEXT("button_luk_plus") );
			file.CreateControl( m_pButton_luk_minus,	CLTNPERSONSTATUS_DLG_BUTTON_LUK_MINUS,	TEXT("button_luk_minus") );
			file.CreateControl( 	m_pStatictext_physical_attack,		CLTNPERSONSTATUS_DLG_STATICTEXT_PHYSICAL_ATTACK,		TEXT("statictext_NONAME6"));
			file.CreateControl( 	m_pEditbox_physical_attack,		 	CLTNPERSONSTATUS_DLG_EDIT_PHYSICAL_ATTACK,				TEXT("editbox_physical_attack"));
			file.CreateControl( 	m_pStatictext_pysical_defense,		CLTNPERSONSTATUS_DLG_STATICTEXT_PHYSICAL_DEFENSE,		TEXT("statictext_NONAME7"));
			file.CreateControl( 	m_pEditbox_pysical_defense,			CLTNPERSONSTATUS_DLG_EDIT_PHYSICAL_DEFENSE,				TEXT("editbox_pysical_defense"));
			file.CreateControl( 	m_pStatictext_masic_attack,			CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC_ATTACK,			TEXT("statictext_NONAME8"));
			file.CreateControl( 	m_pEditbox_magic_attack,			CLTNPERSONSTATUS_DLG_EDIT_MAGIC_ATTACK,					TEXT("editbox_magic_attack"));
			file.CreateControl( 	m_pStatictext_magic_defense,		CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC_DEFENSE,			TEXT("statictext_NONAME9"));
			file.CreateControl( 	m_pEditbox_magic_defense,			CLTNPERSONSTATUS_DLG_EDIT_MAGIC_DEFENSE,				TEXT("editbox_magic_defense"));
			file.CreateControl( 	m_pStatictext_pysical_hit_rank,		CLTNPERSONSTATUS_DLG_STATICTEXT_PHYSICAL_HIT_RANK,		TEXT("statictext_NONAME10"));
			file.CreateControl( 	m_pEditbox_pysical_hit_rank	,	 	CLTNPERSONSTATUS_DLG_EDIT_PHYSICAL_HIT_RANK,			TEXT("editbox_pysical_hit_rank"));
			file.CreateControl( 	m_pStatictext_pysical_dodge_rank,	CLTNPERSONSTATUS_DLG_STATICTEXT_PHYSICAL_DODGE_RANK,	TEXT("statictext_NONAME11"));
			file.CreateControl( 	m_pEditbox_pysical_dodge_rank,		CLTNPERSONSTATUS_DLG_EDIT_PHYSICAL_DODGE_RANK,			TEXT("editbox_pysical_dodge_rank"));
			file.CreateControl( 	m_pStatictext_magic_hit_rank,		CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC_HIT_RANK,			TEXT("statictext_NONAME12"));
			file.CreateControl( 	m_pEditbox_magic_hit_rank,		 	CLTNPERSONSTATUS_DLG_EDIT_MAGIC_HIT_RANK,				TEXT("editbox_magic_hit_rank"));
			file.CreateControl( 	m_pStatictext_magic_dodge_rank,		CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC_DODGE_RANK,		TEXT("statictext_NONAME13"));
			file.CreateControl( 	m_pEditbox_magic_dodge_rank,		CLTNPERSONSTATUS_DLG_EDIT_MAGIC_DODGE_RANK,				TEXT("editbox_magic_dodge_rank"));
			file.CreateControl( 	m_pStatictext_move_speed,			CLTNPERSONSTATUS_DLG_STATICTEXT_MOVE_SPEED,				TEXT("statictext_NONAME14"));
			file.CreateControl( 	m_pEditbox_move_speed,			 	CLTNPERSONSTATUS_DLG_EDIT_MOVE_SPEED,					TEXT("editbox_move_speed"));
			file.CreateControl( 	m_pImageStatic_bonus,			 	CLTNPERSONSTATUS_DLG_IMAGESTATIC_BONUS,					TEXT("imagestatic_bonus"));
			file.CreateControl( 	m_pStatictext_HP,					CLTNPERSONSTATUS_DLG_STATICTEXT_HP_NEW,					TEXT("statictext_NONAME1"));
			file.CreateControl( 	m_pStatictext_MP,		 			CLTNPERSONSTATUS_DLG_STATICTEXT_MP_NEW,					TEXT("statictext_NONAME2"));
			file.CreateControl( 	m_pStatictext_EXP,		 			CLTNPERSONSTATUS_DLG_STATICTEXT_EXP_NEW,				TEXT("statictext_NONAME3"));
			file.CreateControl( 	m_pStatictext_FULL_EXP,		 		CLTNPERSONSTATUS_DLG_STATICTEXT_FULL_EXP_NEW,			TEXT("statictext_full_exp"));
			
			file.CreateControl( 	m_pOutline_NONAME3, 				CLTNPERSONSTATUS_DLG_OUTLINE_NONAME3,					TEXT("outline_NONAME3"));
			file.CreateControl( 	m_pOutline_NONAME4, 				CLTNPERSONSTATUS_DLG_OUTLINE_NONAME4,					TEXT("outline_NONAME4"));

			m_pStatictext_HP->SetFontSize(11); 
			m_pStatictext_HP->SetFontColor(RGB(255,255,255));
			m_pStatictext_HP->Refresh();
			m_pStatictext_MP->SetFontSize(11);  
			m_pStatictext_MP->SetFontColor(RGB(255,255,255));
			m_pStatictext_MP->Refresh();  
			m_pStatictext_EXP->SetFontSize(11);   
			m_pStatictext_EXP->SetFontColor(RGB(255,255,255));
			m_pStatictext_EXP->Refresh(); 
			m_pStatictext_FULL_EXP->SetFontSize(11);   
			m_pStatictext_FULL_EXP->SetFontColor(RGB(255,255,255));
			m_pStatictext_FULL_EXP->Refresh(); 

			m_pButton_Elixir->Show( pclClient->IsCountrySwitch( Switch_Elixir ) );
			 
		}
		else
		{
			file.CreateControl( m_pStatictext_life2,	CLTNPERSONSTATUS_DLG_STATICTEXT_LIFE2, TEXT("statictext_life2") );
			file.CreateControl( m_pStatictext_strength, CLTNPERSONSTATUS_DLG_STATICTEXT_STRENGTH, TEXT("statictext_strength") );
			file.CreateControl( m_pStatictext_dex,		CLTNPERSONSTATUS_DLG_STATICTEXT_DEX, TEXT("statictext_dex") );
			file.CreateControl( m_pStatictext_magic,	CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC, TEXT("statictext_magic") );
			file.CreateControl( m_pStatictext_hand,		CLTNPERSONSTATUS_DLG_STATICTEXT_HAND, TEXT("statictext_hand") );
			file.CreateControl( m_pStatictext_luk,		CLTNPERSONSTATUS_DLG_STATICTEXT_LUK, TEXT("statictext_luk") );


			file.CreateControl( m_pStatictext_exp,			CLTNPERSONSTATUS_DLG_STATICTEXT_EXP,			TEXT("statictext_exp") );
			file.CreateControl( m_pStatictext_expvalue,		CLTNPERSONSTATUS_DLG_STATICTEXT_EXPVALUE,		TEXT("statictext_expvalue") );
			file.CreateControl( m_pStatictext_magic1,		CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC1,			TEXT("statictext_magic1") );
			file.CreateControl( m_pStatictext_magic1value,	CLTNPERSONSTATUS_DLG_STATICTEXT_MAGIC1VALUE,	TEXT("statictext_magic1value") );
			file.CreateControl( m_pStatictext_health,		CLTNPERSONSTATUS_DLG_STATICTEXT_HEALTH,			TEXT("statictext_health") );
			file.CreateControl( m_pStatictext_healthvalue,	CLTNPERSONSTATUS_DLG_STATICTEXT_HEALTHVALUE,	TEXT("statictext_healthvalue") );
			file.CreateControl( m_pStatictext_life,			CLTNPERSONSTATUS_DLG_STATICTEXT_LIFE,			TEXT("statictext_life") );
			file.CreateControl( m_pStatictext_lifevalue,	CLTNPERSONSTATUS_DLG_STATICTEXT_LIFEVALUE,		TEXT("statictext_lifevalue") );
			file.CreateControl( m_pStatictext_fame,			CLTNPERSONSTATUS_DLG_STATICTEXT_FAME,			TEXT("statictext_fame") );
			file.CreateControl( m_pStatictext_famevalue,	CLTNPERSONSTATUS_DLG_STATICTEXT_FAMEVALUE,		TEXT("statictext_famevalue") );
			file.CreateControl( m_pStatictext_country,		CLTNPERSONSTATUS_DLG_STATICTEXT_COUNTRY,		TEXT("statictext_counrty") );
			file.CreateControl( m_pStatictext_countryex,	CLTNPERSONSTATUS_DLG_STATICTEXT_COUNTRYEX,		TEXT("statictext_countryex") );

			file.CreateControl( m_pButton_changekind,		CLTNPERSONSTATUS_DLG_BUTTON_CHANGEKIND, TEXT("button_changekind") );
			file.CreateControl( m_pButton_greeting,			CLTNPERSONSTATUS_DLG_BUTTON_GREETING,	TEXT("button_greeting") );

			if(pclClient->IsCountrySwitch(Switch_NamingQuest))
			{
				file.CreateControl( m_pButton_naming, CLTNPERSONSTATUS_DLG_BUTTON_NAMING, TEXT("button_naming"));
			}

			file.CreateControl( m_pButton_init, CLTNPERSONSTATUS_DLG_BUTTON_INIT, TEXT("button_init") );

			file.CreateControl( m_pCombobox_hand,		CLTNPERSONSTATUS_DLG_COMBOBOX_HAND,		TEXT("combobox_hand") );
			file.CreateControl( m_pCombobox_life2,		CLTNPERSONSTATUS_DLG_COMBOBOX_LIFE2,	TEXT("combobox_life2") );
			file.CreateControl( m_pCombobox_magic,		CLTNPERSONSTATUS_DLG_COMBOBOX_MAGIC,	TEXT("combobox_magic") );
			file.CreateControl( m_pCombobox_dex,		CLTNPERSONSTATUS_DLG_COMBOBOX_DEX,		TEXT("combobox_dex") );
			file.CreateControl( m_pCombobox_strength,	CLTNPERSONSTATUS_DLG_COMBOBOX_STRENGTH, TEXT("combobox_strength") );
			file.CreateControl( m_pCombobox_luk,		CLTNPERSONSTATUS_DLG_COMBOBOX_LUK,		TEXT("combobox_luk") );

			file.CreateControl( m_pButton_explain,		CLTNPERSONSTATUS_DLG_BUTTON_EXPLAIN,	TEXT("button_explain") );
			file.CreateControl( m_pButton_luk_plus,		CLTNPERSONSTATUS_DLG_BUTTON_LUK_PLUS,	TEXT("button_luk_plus") );
			file.CreateControl( m_pButton_luk_minus,	CLTNPERSONSTATUS_DLG_BUTTON_LUK_MINUS,	TEXT("button_luk_minus") );

			file.CreateControl( m_pCombobox_dpowername,		CLTNPERSONSTATUS_DLG_COMBOBOX_DPOWERNAME,	TEXT("combobox_dpowername") );
			file.CreateControl( m_pCombobox_apowername,		CLTNPERSONSTATUS_DLG_COMBOBOX_APOWERNAME,	TEXT("combobox_apowername") );
			file.CreateControl( m_pCombobox_detail_speed,	CLTNPERSONSTATUS_DLG_COMBOBOX_DETAIL_SPEED, TEXT("combobox_detail_speed") );

			file.CreateControl( m_pStatictext_totalspeed,	 CLTNPERSONSTATUS_DLG_STATICTEXT_TOTALSPEED,	TEXT("statictext_totalspeed") );
			file.CreateControl( m_pStatictext_totaldamage,	 CLTNPERSONSTATUS_DLG_STATICTEXT_TOTALDAMAGE,	TEXT("statictext_totaldamage") );
			file.CreateControl( m_pStatictext_armourdefense, CLTNPERSONSTATUS_DLG_STATICTEXT_ARMOURDEFENSE, TEXT("statictext_armourdefense") );

			file.CreateControl( m_pEditbox_totalspeed,		CLTNPERSONSTATUS_DLG_EDITBOX_TOTALSPEED,	TEXT("editbox_totalspeed") );
			file.CreateControl( m_pEditbox_totaldamage,		CLTNPERSONSTATUS_DLG_EDITBOX_TOTALDAMAGE,	TEXT("editbox_totaldamage") );
			file.CreateControl( m_pEditbox_armourdefense,	CLTNPERSONSTATUS_DLG_EDITBOX_ARMOURDEFENSE, TEXT("editbox_armourdefense") );

			file.CreateControl( 	m_pStatictext_rank, 	CLTNPERSONSTATUS_DLG_STATICTEXT_RANK, 	TEXT("statictext_rank")	 )	;
			file.CreateControl( 	m_pStatictext_rank2, 	CLTNPERSONSTATUS_DLG_STATICTEXT_RANK, 	TEXT("statictext_rank2")	 )	;
		}

		file.CreateControl( 	m_pOutline_noname1	, 	CLTNPERSONSTATUS_DLG_OUTLINE_NONAME1	, 	TEXT("outline_NONAME1")	 )	;
		file.CreateControl( 	m_pOutline_noname2	, 	CLTNPERSONSTATUS_DLG_OUTLINE_NONAME2	, 	TEXT("outline_NONAME2")	 )	;

		
		
		// Ÿ�̸Ӹ� �����Ѵ�. 
		SetActionTimer( 1 );
		SetTimerOnOff( true );  

		bBonusButtonEnableSwitch		= false;
		bBonusButton2EnableSwitch		= false;

		m_pStatictext_armourdefense->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		
		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			m_pStatictext_bonus->SetTextPrintOption(DT_CENTER);
		}
		else
		{
			m_pStatictext_bonus->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
		
		
		m_pStatictext_dex->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_exp->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_expvalue->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_fame->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_famevalue->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_hand->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_health->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_healthvalue->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_level->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_levelvalue->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_life->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_life2->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_luk->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_lifevalue->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_magic->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_magic1->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_magic1value->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_rank->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_rank2->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_strength->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_totaldamage->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;
		m_pStatictext_totalspeed->SetTextPrintOption(DT_LEFT | DT_VCENTER | DT_SINGLELINE)	;

		m_pStatictext_armourdefense->Refresh();
		m_pStatictext_bonus->Refresh();
		m_pStatictext_dex->Refresh();
		m_pStatictext_exp->Refresh();
		m_pStatictext_expvalue->Refresh();
		m_pStatictext_fame->Refresh();
		m_pStatictext_famevalue->Refresh();
		m_pStatictext_hand->Refresh();
		m_pStatictext_health->Refresh();
		m_pStatictext_healthvalue->Refresh();
		m_pStatictext_level->Refresh();
		m_pStatictext_levelvalue->Refresh();
		m_pStatictext_life->Refresh();
		m_pStatictext_life2->Refresh();
		m_pStatictext_luk->Refresh();
		m_pStatictext_lifevalue->Refresh();
		m_pStatictext_magic->Refresh();
		m_pStatictext_magic1->Refresh();
		m_pStatictext_magic1value->Refresh();
		m_pStatictext_rank->Refresh();
		m_pStatictext_rank2->Refresh();
		m_pStatictext_strength->Refresh();
		m_pStatictext_totaldamage->Refresh();
		m_pStatictext_totalspeed->Refresh();
	

		 
		TCHAR* buffer = GetTxtFromMgr(6823);
		m_pEditbox_strength->SetUseToolTip(buffer);
		buffer = GetTxtFromMgr(6824);
		m_pEditbox_dex->SetUseToolTip(buffer);
		buffer = GetTxtFromMgr(6825);
		m_pEditbox_magic->SetUseToolTip(buffer);
		buffer = GetTxtFromMgr(6826);
		m_pEditbox_life2->SetUseToolTip(buffer);
		buffer = GetTxtFromMgr(6827);
		m_pEditbox_hand->SetUseToolTip(buffer);
		buffer = GetTxtFromMgr(6828);
		m_pEditbox_luk->SetUseToolTip(buffer);
		
		m_pEditbox_strength->SetChangeTextDrawMode(true);
		m_pEditbox_dex->SetChangeTextDrawMode(true);
		m_pEditbox_magic->SetChangeTextDrawMode(true);
		m_pEditbox_life2->SetChangeTextDrawMode(true);
		m_pEditbox_hand->SetChangeTextDrawMode(true);
		m_pEditbox_luk->SetChangeTextDrawMode(true);
		m_pEditbox_bonus->SetChangeTextDrawMode(true);
		m_pEditbox_bonus->Refresh();

		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{	
			//[����] ������ ���� �߰� => 2008-3-24
			m_pEditbox_Wisdom->SetUseToolTip(buffer);
			m_pEditbox_Wisdom->SetChangeTextDrawMode(true);
			m_pEditbox_bonus->SetTextPrintOption(DT_CENTER);
		}

		//cyj �����̵��̿�� �����
		m_pButton_nolimitwarp->Show(FALSE);

		//KHY - 0912 - ����� + - ��ư����.
		if(pclClient->IsCountrySwitch(Switch_DeleteLuckButton))
		{
			m_pButton_luk_plus->Show(FALSE);
			m_pButton_luk_minus->Show(FALSE);
		}
		else
		{
			m_pButton_luk_plus->Show(true);
			m_pButton_luk_minus->Show(true);
		}

		//KHY - 0912 - ������ + - ��ư����.
		if(pclClient->IsCountrySwitch(Switch_DeleteHandButton))
		{
			m_pButton_hand_plus->Show(FALSE);
			m_pButton_hand_minus->Show(FALSE);
		}
		//		//------------------------------
		//		// ĳ������ �ʻ�ȭ�� �����ش�. 
		//		//------------------------------
		//		//---------------------------------
		//		// HTML �� �ʱ�ȭ�Ѵ�.
		//		//---------------------------------
		//		HWND hwnd = GetDlgItem(hDlg, IDC_STATIC_CHARSTATUS_PORT);
		//		if ( hwnd )
		//		{
		//			EmbedBrowserObject(hwnd);
		//		}
		//
		//		SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
		///*			if(id)
		//		{
		//			cltClient* pclclient = (cltClient *)pclClient;
		//			TCHAR GomziURL[MAX_PATH] = TEXT("") ;
		//
		//			pclClient->GetCZProfileUrl( GomziURL, pclclient->szID );
		//
		//			// PROFILE
		//			hwnd = GetDlgItem(hDlg, IDC_STATIC_CHARSTATUS_PORT);
		//			DisplayHTMLPage(hwnd, GomziURL);
		//		}*/


		UpdateCharStatusInfo();

		Hide();

	}
	//else
	//{
	//	DeleteDialog();
	//}

	m_siTempStr = 0;
	m_siTempDex = 0;
	m_siTempMag = 0;
	m_siTempVit = 0;
	m_siTempHnd = 0;
	m_siTempLuk = 0;
	m_siTempWisdom = 0;

}

void CALLBACK cltNPersonStatus::NPersonStatusStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	cltNPersonStatus* pThis = (cltNPersonStatus*)pControllerMgr;
	pThis->NPersonStatusProc( nEvent, nControlID, pControl);
}


void CALLBACK cltNPersonStatus::NPersonStatusProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient*)pclClient;
	SI16 siTmp = 0;

	switch( nControlID )
	{
		//case WM_SIZE:
		//	//============================
		//	// HTML Resize �� �Ѵ�.
		//	//==================================
		//	hwnd = GetDlgItem(hDlg, IDC_STATIC_CHARSTATUS_PORT);
		//	if( hwnd )
		//	{
		//		ResizeBrowser(hwnd, LOWORD(lParam), HIWORD(lParam));		
		//	}
		//	return TRUE;
	//[����] �� �ɷ�ġ â ���̱�.
	case CLTNPERSONSTATUS_DLG_BUTTON_ABILITY_DETAIL:
		{
			cltClient *pclclient = ( cltClient *) pclClient;
			if ( pclclient->m_pDialog[CHARSTATUS_ABILITY_DETAIL_DLG] == NULL )
			{							
				pclclient->CreateInterface( CHARSTATUS_ABILITY_DETAIL_DLG );
			}
			else
			{
				pclclient->DestroyInterface( pclclient->m_pDialog[CHARSTATUS_ABILITY_DETAIL_DLG] );
			}
		}
		break;
	case CLTNPERSONSTATUS_DLG_BUTTON_WISDOM_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					TCHAR *BonusStatus = m_pEditbox_bonus->GetText();
					SI32 sBonusStatus = atoi(BonusStatus);

					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						if (sBonusStatus < 10 ) {
							SetTempStatusPoint(6, sBonusStatus);
						}
						else
						{
							SetTempStatusPoint(6, 10);
						}

					}
					else
					{
						SetTempStatusPoint(6, 1);
					}
					UpdateCharStatusInfo(); 
					return;
					//SendUseBonusMessageToServer(0, 1);	return ;
				}
				break;
			}
		}
		break;
	case CLTNPERSONSTATUS_DLG_BUTTON_WISDOM_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					TCHAR *BonusStatus = m_pEditbox_bonus->GetText();
					SI32 sBonusStatus = atoi(BonusStatus);

					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						if (sBonusStatus < 10 ) {
							SetTempStatusPoint(6, sBonusStatus);
						}
						else
						{
							SetTempStatusPoint(6, -10);
						}

					}
					else
					{
						SetTempStatusPoint(6, -1);
					}
					UpdateCharStatusInfo(); 
					return;
					//SendUseBonusMessageToServer(0, 1);	return ;
				}
				break;
			}
		}
		break;
	//[����] ������ �������ͽ� ���� â ����.
	case CLTNPERSONSTATUS_DLG_BUTTON_ELIXIR:
		{
			pclclient->CreateInterface( NELIXIR_STATUS_DLG );
		}
		break;

	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;

	case CLTNPERSONSTATUS_DLG_BUTTON_STRENGTH_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					TCHAR *BonusStatus = m_pEditbox_bonus->GetText();
					SI32 sBonusStatus = atoi(BonusStatus);

                    // ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						if (sBonusStatus < 10 ) {
							SetTempStatusPoint(0, sBonusStatus);
						}
						else
						{
							SetTempStatusPoint(0, 10);
						}
						
					}
					else
					{
						SetTempStatusPoint(0, 1);
					}
					UpdateCharStatusInfo(); 
					return;
					//SendUseBonusMessageToServer(0, 1);	return ;
				}
				break;
			}
		}
		break;

	case CLTNPERSONSTATUS_DLG_BUTTON_NOLIMITWARP:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					pclclient->CreateInterface(NSELECTNOLIMITWARPTICKET_DLG);
				}
				break;
			}
		}
		break;
  
	case CLTNPERSONSTATUS_DLG_BUTTON_DEX_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					//cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[10000];

					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(1, 10);
					}
					else
					{
						SetTempStatusPoint(1, 1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				break;
			}
		}
		break;

	case CLTNPERSONSTATUS_DLG_BUTTON_MAGIC_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if (GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(2, 10);
					}
					else
					{
						SetTempStatusPoint(2, 1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				break;
			}
		}
		break;

	case CLTNPERSONSTATUS_DLG_BUTTON_LIFE2_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if (GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(3, 10);
					}
					else
					{
						SetTempStatusPoint(3, 1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				break;
			}
		}
		break;

	case CLTNPERSONSTATUS_DLG_BUTTON_HAND_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
					if(id)
					{
						// �����ִ� ���� * 2 ������ ����Ѵ�. - ����
						/*if(pclCM->CR[id]->pclCI->clIP.GetHnd() + m_siTempHnd >= pclCM->CR[id]->pclCI->clIP.GetLevel()*2)
						{
							TCHAR* pTitle = GetTxtFromMgr(602);
							TCHAR* pText = GetTxtFromMgr(603);
							((CNotifyMsgDlg *)pclclient->m_pDialog[ NOTIFYMSG_DLG ])->m_pTextStatic->SetFontColor( RGB( 255, 0, 0 ) );
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							((CNotifyMsgDlg *)pclclient->m_pDialog[ NOTIFYMSG_DLG ])->m_pTextStatic->SetFontColor( RGB( 0, 0, 0 ) );
							return ;
						}
						*/
						// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
						if (GetKeyState(VK_SHIFT) & 0x8000)
						{
							SetTempStatusPoint(4, 10);
						}
						else
						{
							SetTempStatusPoint(4, 1);
						}
						UpdateCharStatusInfo(); 
						return;
					}
				}
				break;
			}
		}
		break;

	case CLTNPERSONSTATUS_DLG_BUTTON_LUK_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(5, 10);
					}
					else
					{
						SetTempStatusPoint(5, 1);
					}
					UpdateCharStatusInfo(); 
					return;
					//SendUseBonusMessageToServer(5, 1);	return ;
				}
				break;
			}
		}
		break;

	case CLTNPERSONSTATUS_DLG_BUTTON_STRENGTH_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(0, -10);
					}
					else
					{
						SetTempStatusPoint(0, -1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				return ;
			default:
				return;
			}
		}
		return;
	case CLTNPERSONSTATUS_DLG_BUTTON_DEX_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(1, -10);
					}
					else
					{
						SetTempStatusPoint(1, -1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				return ;
			default:
				return;
			}
		}
		return;
	case CLTNPERSONSTATUS_DLG_BUTTON_MAGIC_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(2, -10);
					}
					else
					{
						SetTempStatusPoint(2, -1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				return ;
			default:
				return;
			}
		}
		return;
	case CLTNPERSONSTATUS_DLG_BUTTON_LIFE2_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(3, -10);
					}
					else
					{
						SetTempStatusPoint(3, -1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				return ;
			default:
				return;
			}
		}
		return;
	case CLTNPERSONSTATUS_DLG_BUTTON_HAND_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(4, -10);
					}
					else
					{
						SetTempStatusPoint(4, -1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				return ;
			default:
				return;
			}
		}
		return;

	case CLTNPERSONSTATUS_DLG_BUTTON_LUK_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// ShiftŰ�� �������¿��� ���� �й��ư�� ������ 10�� �����Ѵ�.
					if(GetKeyState(VK_SHIFT) & 0x8000)
					{
						SetTempStatusPoint(5, -10);
					}
					else
					{
						SetTempStatusPoint(5, -1);
					}
					UpdateCharStatusInfo(); 
					return;
				}
				return ;
			default:
				return;
			}
		}
		return;

	case CLTNPERSONSTATUS_DLG_BUTTON_EXPLAIN:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{			

					//if ( g_SoundOnOffDlg.m_bFullScreenMode )
					//{
					pclclient->ShowHelpWindow(TEXT("charstatus"));
					//if((pclclient->m_pDialog[ NHINT_DLG ])==NULL)
					//{
					//	pclclient->CreateInterface( NHINT_DLG );
					//}
					//((NHintDlgExplain*)pclclient->m_pDialog[ NHINT_DLG])->Show(TEXT("charstatus"));

					//}
					//else
					//pclclient->m_pHintDlg->Show(TEXT("charstatus"));
				}
				break;
			}
		}
		return ;

	case CLTNPERSONSTATUS_DLG_BUTTON_INIT:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if( pclClient->IsWhereServiceArea(ConstServiceArea_China | ConstServiceArea_Taiwan) )
					{
						TCHAR buffer[256] = TEXT("") ;

						//cyj �����ʱ�ȭ�̿�� ����ũ���� 14090->24030
						//SI32 itemunique = 14090 ;  // �����ʱ�ȭ�̿��
						SI32 itemunique1 = ITEMUNIQUE(24030) ;  // �����ʱ�ȭ�̿��
						SI32 itemunique2 = ITEMUNIQUE(24031) ;  // �߱��̺�Ʈ �����ʱ�ȭ�̿��
						if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique1) <= 0 &&
							pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique2) <= 0 )
						{
							TCHAR* pTitle = GetTxtFromMgr(605);
							TCHAR* pText = GetTxtFromMgr(608);

							StringCchPrintf(buffer, 256, pText);

							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
							return ;
						}

						if ( pclclient->pclCM->CR[1]->clInnerStatus.IsStatus(INNERSTATUS_PRISON))
						{
							TCHAR* pTitle = GetTxtFromMgr(836);
							TCHAR* pText = GetTxtFromMgr(6033);

							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,pText);
							return ;
						}


						// ��� �����Ǿ��ִ��� �˻��Ѵ�.
						for ( SI16 i=0 ; i<PERSONITEM_RESERVED1 ; i++ )
						{
							if ( i == PERSONITEM_BAG || i == PERSONITEM_BAG_SUB )
								continue;

							if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.clItem[i].siUnique != 0 )
							{
								TCHAR* pText = GetTxtFromMgr(6572);
								StringCchPrintf(buffer, 256, pText);

								pText = GetTxtFromMgr(605);
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText,buffer);
								return;
							}
						}

						TCHAR* pText = GetTxtFromMgr(609);
						TCHAR* pTitle = GetTxtFromMgr(605);

						stMsgBox MsgBox;
						// ���� dialog�� �� â ���� Child Dialog�϶�
						CControllerMgr *pParent = NULL;
						pParent = this->GetParentDialog();
						if(pParent == NULL ) return;
						MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_OKCANCEL, 6 );

						pclclient->SetMsgBox( &MsgBox, NULL, 0 );
					}
					else
					{
						TCHAR buffer[256] = TEXT("") ;

						//cyj �����ʱ�ȭ�̿�� ����ũ���� 14090->24030
						//SI32 itemunique = 14090 ;  // �����ʱ�ȭ�̿��
						SI32 itemunique			= ITEMUNIQUE(24030) ;  // �����ʱ�ȭ�̿��
						SI32 siEventItemUnique	= ITEMUNIQUE(24125) ;  // �����ʱ�ȭ�̿��

						// �����ʱ�ȭ �̿���� ���°��
						if (	pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 && 
								pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(siEventItemUnique) <= 0)
						{
							TCHAR* pTitle = GetTxtFromMgr(605);
							TCHAR* pText = GetTxtFromMgr(608);

							StringCchPrintf(buffer, 256, pText);

							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
							return ;
						}

						if ( pclclient->pclCM->CR[1]->clInnerStatus.IsStatus(INNERSTATUS_PRISON))
						{
							TCHAR* pTitle = GetTxtFromMgr(836);
							TCHAR* pText = GetTxtFromMgr(6033);

							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,pText);
							return ;
						}


						// ��� �����Ǿ��ִ��� �˻��Ѵ�.
						for ( SI16 i=0 ; i<PERSONITEM_RESERVED1 ; i++ )
						{
							if ( i == PERSONITEM_BAG || i == PERSONITEM_BAG_SUB )
								continue;

							if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.clItem[i].siUnique != 0 )
							{
								TCHAR* pText = GetTxtFromMgr(6572);
								StringCchPrintf(buffer, 256, pText);

								pText = GetTxtFromMgr(605);
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText,buffer);
								return;
							}
						}

						TCHAR* pText = GetTxtFromMgr(609);
						TCHAR* pTitle = GetTxtFromMgr(605);

						stMsgBox MsgBox;
						// ���� dialog�� �� â ���� Child Dialog�϶�
						CControllerMgr *pParent = NULL;
						pParent = this->GetParentDialog();
						if(pParent == NULL ) return;
						MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_OKCANCEL, 6 );

						pclclient->SetMsgBox( &MsgBox, NULL, 0 );
					}
				}
				break;
			}
		}
		return ;

	//cyj �̸����� ������� ����
	case CLTNPERSONSTATUS_DLG_BUTTON_CHANGENAME:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					//if ( !pclCharNameChange->CreateDlg(pclClient->GetInstance(), pclClient->GetHwnd()) )
					//	pclCharNameChange->Close();
					pclclient->CreateInterface( CLTNCHARNAMECHANGE_DLG );
				}
				break;
			}
		}
		return ;
		
	case CLTNPERSONSTATUS_DLG_BUTTON_CHANGEKIND:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if ( pclclient->pclCM->CR[1]->pclCI->clBI.GetKind() <= 0 ||
						pclclient->pclCM->CR[1]->pclCI->clBI.GetKind() >= KIND_SYSTEM )
						return ;

					//if ( !pclCharKindChange->CreateDlg(pclClient->GetInstance(),pclClient->GetHwnd()) )
					//	pclCharKindChange->Close();
					pclclient->CreateInterface( CLTNCHARKINDCHANGE_DLG );
				}
				break;
			}
		}
		return ;
	case CLTNPERSONSTATUS_DLG_BUTTON_GREETING:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if ( pclclient->m_pDialog[CLTNCHARGREETINGCHANGE_DLG] )
						break;

					pclclient->CreateInterface( CLTNCHARGREETINGCHANGE_DLG );
				}
				break;
			}
		}
		return ;
	case CLTNPERSONSTATUS_DLG_BUTTON_NAMING:
		{
			if ( EVENT_BUTTON_CLICKED == nEvent )
			{
				if ( pclclient->m_pDialog[NSELECTNAMING_DLG] == NULL)
					pclclient->CreateInterface( NSELECTNAMING_DLG );
			}
		}
		return ;
	case CLTNPERSONSTATUS_DLG_BUTTON_STATUSCLEAR:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					ClearTempStatusPoint();
				}
				break;
			}
		}
		return ;
	case CLTNPERSONSTATUS_DLG_BUTTON_STATUSAPPLY:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if(  ( m_siTempStr == 0 && m_siTempMag == 0  && m_siTempVit  == 0
						&& m_siTempDex  == 0 && m_siTempHnd  == 0 && m_siTempLuk  == 0 && m_siTempWisdom == 0) ) return;

					TCHAR* pText = GetTxtFromMgr(6437);
					TCHAR* pTitle = GetTxtFromMgr(6438);

					stMsgBox MsgBox;
					CControllerMgr *pParent = NULL;
					pParent = this->GetParentDialog();
					if(pParent == NULL ) return;
					MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_OKCANCEL, 7 );
					pclclient->SetMsgBox( &MsgBox, NULL, 0 );					
				}
				break;
			}
		}
		return ;
	}
	return ;
}

void cltNPersonStatus::UpdateCharStatusInfo()
{
	TCHAR buffer[256];
	SI32 index = 0;
	SI32 siTmp = 0;

	cltClient *pclclient = (cltClient*)pclClient;

	for ( int i = 0 ; i < KIND_SYSTEM ; i ++ )
	{
		if ( i != pclclient->pclCM->CR[1]->pclCI->clBI.GetKind() ) continue;
		cltKindInfo *pclKindInfo = pclClient->pclKindInfoSet->pclKI[i];
		if ( pclKindInfo == NULL ) continue ;

		siTmp = i ;
		break ;
	}

	TCHAR szPortrait[256];
	SI32 siPortraitFont;
	pclClient->pclKindInfoSet->GetNPCImageFileAndFont(siTmp, szPortrait, sizeof(szPortrait), &siPortraitFont);
	m_pImagestatic_portrait->SetFileName(szPortrait);

	/*cyj ĳ���� Portrait  ����
	switch(siTmp)
	{
	case 1:	m_pImagestatic_portrait->SetFontIndex( 0 ); break;//strcpy(strFileName, TEXT("KIND_HERO1"));	break;
	case 2:	m_pImagestatic_portrait->SetFontIndex( 1 ); break;//strcpy(strFileName, TEXT("KIND_HEROINE1")); break;
	//#if _DEBUG
	case 3:	m_pImagestatic_portrait->SetFontIndex( 2 ); break;

	//#endif
	}
	*/
	m_pImagestatic_portrait->SetFontIndex( siPortraitFont );

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		return ;
	}

	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

	// ĳ���� �ź�
	cltSimpleRank* pclrank = &pclCM->CR[id]->pclCI->clCharRank;
	UI08 grank = pclCM->CR[id]->pclCI->clBI.uiGRank ;
	if(GetRankName(pclrank, buffer, 256, grank) == TRUE)
	{
		TCHAR FameLevelName[256] = TEXT("");
		if ( ((cltClient *)pclClient)->GetFameLevelName( pclCM->CR[id]->pclCI->clIP.siFameLevel, FameLevelName ) )
		{
			StringCchCat( buffer, 256, TEXT("-") );
			StringCchCat( buffer, 256, FameLevelName );
		}

		// ������� ���޸��� �и��Ѵ�.
		// ���� : �������� ������ ���� �ȵȴ�.

		TCHAR* pVillageName = buffer;
		TCHAR* pRank = buffer;

		SI32 siSpace = -1;
		TCHAR* pFirstSpace = _tcsstr(buffer, " ");
		if(pFirstSpace != NULL)
		{
			siSpace = pFirstSpace - buffer;
		}
		if(siSpace > 0)
		{
			buffer[siSpace] = '\0';

			pVillageName = buffer;
			pRank = &buffer[siSpace+1];
		}

		if(pVillageName)	m_pStatictext_rank->SetText( pVillageName, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		if(pRank)			m_pStatictext_rank2->SetText( pRank, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		
	}

	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		//[����] ĳ���� �̸�. => 2008-3-24
		m_pStatictext_namevalue->SetText((TCHAR*)pclCM->CR[id]->GetName(), DT_CENTER|DT_VCENTER|DT_SINGLELINE );  
	}
	
	StringCchPrintf(buffer, 256, TEXT("%d / %d"), pclCM->CR[id]->pclCI->clIP.GetLevel(), MAX_CHARACTER_LEVEL);
	m_pStatictext_levelvalue->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	 
	
	// ����ġ
	SI64 siCurExp = pclCM->CR[id]->pclCI->clIP.GetCurExp();// SI32->SI64 ����ġ �����÷ο춧���� ����
	SI64 siNextExp = pclCM->CR[id]->clPB.GetNextExp();// SI32->SI64 ����ġ �����÷ο춧���� ����

	TCHAR curExp[128];
	TCHAR nextExp[128];

	g_JYLibFunction.SetNumUnit( siCurExp, curExp, 128 );
	g_JYLibFunction.SetNumUnit( siNextExp, nextExp, 128 );

	StringCchPrintf(buffer, 256, TEXT("%s / %s"), curExp, nextExp );
	m_pStatictext_expvalue->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

	// ü��
	SI32 life = pclCM->CR[id]->GetLife();
	SI32 maxLife = pclCM->CR[id]->clPB.GetMaxLife() + m_siTempVit * 4; 
	if( life > maxLife )
		life = maxLife;
	StringCchPrintf(buffer, 256, TEXT("%d / %d"), life, maxLife);
	m_pStatictext_lifevalue->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

	// ������ 
	StringCchPrintf(buffer, 256, TEXT("%d / %d"), pclCM->CR[id]->GetMana(), pclCM->CR[id]->clPB.GetMaxMana()  + m_siTempMag * 4);
	m_pStatictext_magic1value->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

	// �ǰ� 
	SI32 healthpoint = pclCM->CR[id]->pclCI->clHealthInfo.uiHealthPoint;
	StringCchPrintf(buffer, 256, TEXT("%d"), healthpoint);
	m_pStatictext_healthvalue->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

	// �������ʽ�  
	//StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->pclCI->clIP.GetBonus() );
	//m_pEditbox_bonus->SetText( buffer );
  
	if( m_siTempStr || m_siTempDex || m_siTempMag || m_siTempVit || m_siTempHnd || m_siTempLuk || m_siTempWisdom)
	{//"%d ><C05> %d</C>"
		StringCchPrintf(buffer, 256, TEXT("%d > %d"), pclCM->CR[id]->pclCI->clIP.GetBonus() 
			, pclCM->CR[id]->pclCI->clIP.GetBonus() - m_siTempStr - m_siTempDex - m_siTempMag - m_siTempVit - m_siTempHnd - m_siTempLuk - m_siTempWisdom );
		m_pEditbox_bonus->SetText( buffer );        
	}  
	else
	{
		StringCchPrintf(buffer, 256, TEXT("%d "), pclCM->CR[id]->pclCI->clIP.GetBonus() );
		m_pEditbox_bonus->SetText( buffer );
	}


	// �����
	StringCchPrintf(buffer, 256, TEXT("%d/%d(%d / %d)"), pclCM->CR[id]->pclCI->clIP.siFameLevel, MAX_FAME_LEVEL, 
		pclCM->CR[id]->pclCI->clIP.siFameExp, 
		GetRequiredFameExpForLevel(pclCM->CR[id]->pclCI->clIP.siFameLevel + 1));
	m_pStatictext_famevalue->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

	// ����
	TCHAR buf[128] = TEXT("");
	if ( pclClient->siServiceArea ==  ConstServiceArea_English )
	{
		TCHAR* country = pclClient->pclCountryManager->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		StringCchPrintf( buf, 128, country );

	}
	else if ( pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		TCHAR* country = pclClient->pclCountryManagerJapan->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		StringCchPrintf( buf, 128, country );
	}
	else if ( pclClient->siServiceArea ==  ConstServiceArea_NHNChina )
	{
		TCHAR* country = pclClient->pclCountryManager->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		StringCchPrintf( buf, 128, country );

	}
	else if ( pclClient->siServiceArea ==  ConstServiceArea_EUROPE )
	{
		TCHAR* country = pclClient->pclCountryManager->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		StringCchPrintf( buf, 128, country );

	}

	m_pStatictext_countryex->SetText( buf, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

	// �ٷ�
	/*
	StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.clTotalBA.GetStr() );
	m_pEditbox_strength->SetText( buffer );
	*/
	TCHAR szBuffer[256] = {'\0',}; 

	if( m_siTempStr > 0 )
	{				
		StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"), pclCM->CR[id]->clPB.clTotalBA.GetStr(), pclCM->CR[id]->clPB.clTotalBA.GetStr() + m_siTempStr )	;
		//m_pEditbox_strength->SetChangeTextDrawMode(true);
	}
	else
	{
		StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetStr() )	;
		//m_pEditbox_strength->SetChangeTextDrawMode(false);
	}

	m_pEditbox_strength->SetText(szBuffer);

	// �ٷ·� �� ������ �����Ѵ�. 
	ShowDetailStrInfo( &pclchar->clPB);

	//  ���߷�
	//	StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.clTotalBA.GetDex() );
	//	m_pEditbox_dex->SetText( buffer );

	//KHY - 0611 - �ӽ�. ĭ ����.
	if( m_siTempDex > 0 )
	{				
		StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"),  pclCM->CR[id]->clPB.clTotalBA.GetDex(),  pclCM->CR[id]->clPB.clTotalBA.GetDex() + m_siTempDex )	;
		//m_pEditbox_dex->SetChangeTextDrawMode(true);
	}
	else
	{
		StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetDex() )	;
		//m_pEditbox_dex->SetChangeTextDrawMode(false);
	}
	m_pEditbox_dex->SetText(szBuffer);

	// ���߷� �� ������ �����Ѵ�. 
	ShowDetailDexInfo( &pclchar->clPB);

	// ����
	//StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.clTotalBA.GetMag() );
	//m_pEditbox_magic->SetText( buffer );

	if( m_siTempMag > 0 )
	{				
		StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"),  pclCM->CR[id]->clPB.clTotalBA.GetMag(),  pclCM->CR[id]->clPB.clTotalBA.GetMag() + m_siTempMag )	;
		//m_pEditbox_magic->SetChangeTextDrawMode(true);
	}
	else
	{
		StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetMag() )	;
		//m_pEditbox_magic->SetChangeTextDrawMode(false);
	}
	m_pEditbox_magic->SetText(szBuffer);

	// ���� �� ������ �����Ѵ�. 
	ShowDetailMagInfo( &pclchar->clPB);

	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		if( m_siTempWisdom > 0 )
		{				
			StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"),  pclCM->CR[id]->clPB.clTotalBA.GetWis(),  pclCM->CR[id]->clPB.clTotalBA.GetWis() + m_siTempWisdom )	;
			//m_pEditbox_magic->SetChangeTextDrawMode(true);
		}
		else
		{
			StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetWis() )	;
			//m_pEditbox_magic->SetChangeTextDrawMode(false);
		}
		m_pEditbox_Wisdom->SetText(szBuffer); 
	}


	// ����� 
	//	StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.clTotalBA.GetVit() );
	//m_pEditbox_life2->SetText( buffer );

	if( m_siTempVit > 0 )
	{				
		StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"),  pclCM->CR[id]->clPB.clTotalBA.GetVit(),  pclCM->CR[id]->clPB.clTotalBA.GetVit() + m_siTempVit )	;
		//m_pEditbox_life2->SetChangeTextDrawMode(true);
	}
	else
	{
		StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetVit() )	;
		//m_pEditbox_life2->SetChangeTextDrawMode(false);
	}
	m_pEditbox_life2->SetText(szBuffer);

	// ����� �� ������ �����Ѵ�. 
	ShowDetailVitInfo( &pclchar->clPB);

	// ������ 
	//	StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.clTotalBA.GetHnd() );
	//	m_pEditbox_hand->SetText( buffer );

	if( m_siTempHnd > 0 )
	{				
		StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"),  pclCM->CR[id]->clPB.clTotalBA.GetHnd(),  pclCM->CR[id]->clPB.clTotalBA.GetHnd() + m_siTempHnd)	;
		//	m_pEditbox_hand->SetChangeTextDrawMode(true);
	}
	else
	{
		StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetHnd() )	;
		//m_pEditbox_hand->SetChangeTextDrawMode(false);
	}
	m_pEditbox_hand->SetText(szBuffer);

	// ������ �� ������ �����Ѵ�. 
	ShowDetailHndInfo( &pclchar->clPB );

	// ��� 
	//	StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.clTotalBA.GetLuk() );
	//	m_pEditbox_luk->SetText( buffer );


	if( m_siTempLuk > 0 )
	{				
		StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"),  pclCM->CR[id]->clPB.clTotalBA.GetLuk(),  pclCM->CR[id]->clPB.clTotalBA.GetLuk() + m_siTempLuk )	;
		//m_pEditbox_luk->SetChangeTextDrawMode(true);
	}
	else
	{
		StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetLuk() )	;
		//m_pEditbox_luk->SetChangeTextDrawMode(false);
	}
	m_pEditbox_luk->SetText(szBuffer);
    
	// ��� �� ������ �����Ѵ�. 
	ShowDetailLukInfo( &pclchar->clPB );

	
	// �̵��ӵ� 
	StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.GetTotalMoveSpeed());
	m_pEditbox_totalspeed->SetText( buffer );

	////	[��ȣ] CharTransformDlg.cpp�� IncreaseWis()�ʿ��� ������Ų Wis���� �̰��� ������ �ȵǹǷ� ���� ���� �� ������ ��ġ ���� �մϴ�.
	//cltTransFormInfo* pTransformInfo = &pclClient->pclCM->CR[id]->clTransFormInfo;
	//SI32 siTransFormSyc = (SI32)pTransformInfo->GetSynchroTransForm(pTransformInfo->uiNowTransFormKind);
	//SI32 temState = pclCM->CR[id]->clPB.clTransFormBA.GetWis() * (siTransFormSyc/2) / 100;

	////	�� ���� =�⺻���� + �������� + ��ũ��
	//pclCM->CR[id]->clPB.clTotalBA.SetWis(pclCM->CR[id]->clPB.clBasicBA.GetWis() + pclCM->CR[id]->clPB.clTransFormBA.GetWis() + temState); 
	

	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		if( m_siTempWisdom > 0 )
		{				
			StringCchPrintf(szBuffer,256,TEXT("%d ><C08>%d</C>"),  pclCM->CR[id]->clPB.clTotalBA.GetWis(),  pclCM->CR[id]->clPB.clTotalBA.GetWis() + m_siTempWisdom )	;
			//m_pEditbox_luk->SetChangeTextDrawMode(true);
		}
		else
		{
			StringCchPrintf(szBuffer,256,TEXT("%d "),  pclCM->CR[id]->clPB.clTotalBA.GetWis() )	;
			//m_pEditbox_luk->SetChangeTextDrawMode(false);
		}
		m_pEditbox_Wisdom->SetText(szBuffer);

		//[����] ���� �� ������ �����Ѵ�. => 2008-3-26
		ShowDetailWisdomInfo( &pclchar->clPB );  

		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			m_pEditbox_move_speed->SetText( buffer, RGB(128,0,0) );
		}
		else
		{
			m_pEditbox_move_speed->SetText( buffer );
		}
	}

	// �̵��ӵ� �� ������ �����Ѵ�. 
	ShowDetailSpeedInfo( &pclchar->clPB, pclchar );

	// ���ݷ�  
	//StringCchPrintf(buffer, 256, TEXT("%d - %d"), pclCM->CR[id]->clPB.GetTotalMinDamage(),  pclCM->CR[id]->clPB.GetTotalMaxDamage());



	StringCchPrintf(buffer, 256, TEXT("%d - %d"), GetTotalMinDamage( &pclchar->clPB, pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON), pclchar->ActiveWeapon),  GetTotalMaxDamage( &pclchar->clPB, pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON), pclchar->ActiveWeapon));
	m_pEditbox_totaldamage->SetText( buffer );




	// ���ݷ� �� ������ �����Ѵ�. 
	ShowDetailDamageInfo( &pclchar->clPB, pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON), pclchar->ActiveWeapon, pclchar);

	// ����  
	StringCchPrintf(buffer, 256, TEXT("%d"), pclCM->CR[id]->clPB.GetTotalAC());
	m_pEditbox_armourdefense->SetText( buffer );

	// ���� �� ������ �����Ѵ�. 
	ShowDetailArmourInfo( &pclchar->clPB );

	/*
	// �������׷�. 
	hwnd = GetDlgItem(hDlg, IDC_EDIT_DAMAGERESIST); 
	sprintf(buffer, TEXT("%d"), pclCM->CR[id]->clPB.GetTotalDamageResist());
	SetWindowText(hwnd, buffer);

	// ���� ���׷�. 
	hwnd = GetDlgItem(hDlg, IDC_EDIT_MAGICRESIST); 
	sprintf(buffer, TEXT("%d"), pclCM->CR[id]->clPB.GetTotalMagicResist());
	SetWindowText(hwnd, buffer);
	*/

	//SI32 ButtonDlg[] = {
	//	IDC_BUTTON_STR, 
	//	IDC_BUTTON_DEX,
	//	IDC_BUTTON_INT,
	//	IDC_BUTTON_VIT,
	//	IDC_BUTTON_HND,
	//	-1
	//};

	// ���ʽ� ��ġ ������ ��ư�� �����Ѵ�. 
	if(pclCM->CR[id]->pclCI->clIP.GetBonus())
	{
		if(bBonusButtonEnableSwitch == false)
		{
			bBonusButtonEnableSwitch = true;

			//index = 0;
			//while(ButtonDlg[index] >0)
			//{
			//	hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
			//	EnableWindow(hwnd, TRUE);

			//	index++;
			//}
		}
		m_pButton_strength_plus->Enable( true );
		m_pButton_dex_plus->Enable( true );
		m_pButton_magic_plus->Enable( true );
		m_pButton_life2_plus->Enable( true );
		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			m_pButton_Wisdom_plus->Enable( true );
		}
		m_pButton_hand_plus->Enable( true );
		m_pButton_luk_plus->Enable( true );
	}
	else
	{
		if(bBonusButtonEnableSwitch == true)
		{
			bBonusButtonEnableSwitch = false;

			//index = 0;
			//while(ButtonDlg[index] >0)
			//{
			//	hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
			//	EnableWindow(hwnd, FALSE);

			//	index++;
			//}
		}
		m_pButton_strength_plus->Enable( false );
		m_pButton_dex_plus->Enable( false );
		m_pButton_magic_plus->Enable( false );
		m_pButton_life2_plus->Enable( false );
		m_pButton_hand_plus->Enable( false );
		m_pButton_luk_plus->Enable( false );
		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
            m_pButton_Wisdom_plus->Enable( false );
		}
	}

	// �ǰ� ���� 
	TCHAR healthtext[2048];
	
	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		const SI32 SiBufferSize = 2048;

		TCHAR	szExplain[SiBufferSize]	= TEXT("");
		SetStatusExplain(szExplain, sizeof(szExplain));

		SI32 myLevel = pclchar->pclCI->clIP.GetLevel();
		
		if(pclchar->clPB.clHealth.GetHealthText(myLevel, healthtext, SiBufferSize) == true)
		{
			SI32 StringLenth = strlen(szExplain);
			SI32 RemainSize  = sizeof(szExplain[0]) * (SiBufferSize - StringLenth);
			StringCchPrintf(&szExplain[StringLenth], RemainSize, TEXT("%s \r\n"), healthtext);

			m_pEditbox_health_explain->SetText( szExplain );
		}  
		

		SI32 life = pclCM->CR[id]->GetLife();

		SI32 maxLife = pclCM->CR[id]->clPB.GetMaxLife() 
			           + (m_siTempVit * (8000 + (myLevel*5)))/1000; // ���ĺ���

		if( life > maxLife )
			  life = maxLife;
		StringCchPrintf(buffer, 256, TEXT("%d / %d"), life, maxLife);
		m_pStatictext_HP->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	
		
		SI32 mana = pclCM->CR[id]->GetMana();

		SI32 maxMana = pclCM->CR[id]->clPB.GetMaxMana() 
			+ (m_siTempMag * (3000 + (myLevel*5)))/1000;  // ���ĺ���
		
		if( mana > maxMana )
			mana = maxMana;

		StringCchPrintf(buffer, 256, TEXT("%d / %d"), pclCM->CR[id]->GetMana(), maxMana);
		m_pStatictext_MP->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		
		
		SI64 siCurExp = pclCM->CR[id]->pclCI->clIP.GetCurExp();// SI32->SI64 ����ġ �����÷ο춧���� ����
		SI64 siNextExp = pclCM->CR[id]->clPB.GetNextExp();// SI32->SI64 ����ġ �����÷ο춧���� ����

		TCHAR curExp[128];
		TCHAR nextExp[128];

		g_JYLibFunction.SetNumUnit( siCurExp, curExp, 128 );
		g_JYLibFunction.SetNumUnit( siNextExp, nextExp, 128 );

		StringCchPrintf(buffer, 256, TEXT("%s"), curExp);
		m_pStatictext_EXP->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );			
		
		StringCchPrintf(buffer, 256, TEXT("%s"), nextExp );
		m_pStatictext_FULL_EXP->SetText( buffer, DT_CENTER|DT_VCENTER|DT_SINGLELINE );			
		
		
		// �ű� �ɷ�ġ ����. 
		SetNewAbility(&pclchar->clPB);
	}
	else
	{
		if(pclCM->CR[id]->clPB.clHealth.GetHealthText(pclCM->CR[id]->pclCI->clIP.GetLevel(), healthtext, 2048) == true)
		{
			m_pEditbox_health_explain->SetText( healthtext );
		}
	}

	if ( pclclient->m_pDialog[CHARSTATUS_ABILITY_DETAIL_DLG] )
	{							
		((NCharAbilityDatailDlg*)pclclient->m_pDialog[CHARSTATUS_ABILITY_DETAIL_DLG])->SetAbilityInfo();
	}
}


void cltNPersonStatus::SetTempStatusPoint(SI32 pos, SI32 amount)
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		return ;
	}


	//	if( pclCM->CR[id]->pclCI->clIP.GetBonus() 
	//	- m_siTempStr - m_siTempDex - m_siTempMag - m_siTempVit - m_siTempHnd - m_siTempLuk <= 0  ) return;

	if( pclCM->CR[id]->pclCI->clIP.GetBonus() // ����Ʈ ������ ���� �ø��� ���� 10�����ϰ�쿡 ���� ���� ��� ����
		- m_siTempStr - m_siTempDex - m_siTempMag - m_siTempVit - m_siTempHnd - m_siTempLuk - m_siTempWisdom - amount < 0  )
	{
		SI32 sbonus = pclCM->CR[id]->pclCI->clIP.GetBonus() - m_siTempStr - m_siTempDex - m_siTempMag - m_siTempVit - m_siTempHnd - m_siTempLuk - m_siTempWisdom;
		if ( sbonus> 0) {
			amount = sbonus;
		}
		else
		{
			return;
		}
		
	}
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

	switch (pos)
	{
	case 0 :
		{
			if( m_siTempStr + amount < 0 ) return;

			m_siTempStr += amount;   
			
		}
		break;
	case 1 :
		{
			if( m_siTempDex + amount < 0 ) return;

			m_siTempDex += amount;
			
		}
		break;
	case 2 :
		{
			if( m_siTempMag + amount < 0 ) return;

			m_siTempMag += amount;
			
		}
		break;
	case 3 :
		{
			if( m_siTempVit + amount < 0 ) return;

			m_siTempVit += amount;
			
		}
		break;
	case 4 :
		{
			if( m_siTempHnd + amount < 0 ) return;

			m_siTempHnd += amount;
		}
		break;
	case 5 :
		{
			if( m_siTempLuk + amount < 0 ) return;

			m_siTempLuk += amount;
		}
		break;
	case 6 :
		{
			if( m_siTempWisdom + amount < 0 ) return;

			m_siTempWisdom += amount;
		}
		break;
	}
}

void cltNPersonStatus::ClearTempStatusPoint()
{
	m_siTempStr = 0;
	m_siTempDex = 0;
	m_siTempVit = 0;
	m_siTempMag = 0;
	m_siTempHnd = 0;
	m_siTempLuk = 0;
	m_siTempWisdom = 0;
}

void cltNPersonStatus::ApplyTempStatusPoint()
{
	if(m_siTempStr)
	{
		SendUseBonusMessageToServer(0,m_siTempStr);
	}
	if(m_siTempDex)
	{
		SendUseBonusMessageToServer(1,m_siTempDex);
	}
	if(m_siTempMag)
	{
		SendUseBonusMessageToServer(2,m_siTempMag);
	}
	if(m_siTempVit)
	{
		SendUseBonusMessageToServer(3,m_siTempVit);
	}
	if(m_siTempHnd)
	{
		SendUseBonusMessageToServer(4,m_siTempHnd);
	}
	if(m_siTempLuk)
	{
		SendUseBonusMessageToServer(5,m_siTempLuk);
	}
	if(m_siTempWisdom)
	{
		SendUseBonusMessageToServer(6,m_siTempWisdom);
	}
	 

	ClearTempStatusPoint();

} 

void cltNPersonStatus::SendUseBonusMessageToServer(SI32 pos, SI32 amount)
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id)
	{
		cltGameMsgResponse_UseBonus clinfo(pos, amount);
		cltMsg clMsg(GAMEMSG_REQUEST_USEBONUS, sizeof(clinfo), (BYTE*)&clinfo);
		cltClient* pclclient = (cltClient*)pclClient;
		pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
	}
}

// ���ݷ� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailDamageInfo( cltParametaBox* pclPB, cltItem* pclitemlist, SI32 activesweapon, cltCharCommon* pclchar )
{
	TCHAR buffer[256];
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_apowername->Clear();

	// ������ ���� ���ݷ�. 
	TCHAR* pText = GetTxtFromMgr(649);
	StringCchPrintf(buffer, 256, pText, pclPB->siLevelDamage);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );

	if(pclitemlist && pclClient->pclItemManager->GetWeaponMinDamage(pclitemlist, activesweapon, pclchar) )
	{
		pText = GetTxtFromMgr(650);
		if ( pclPB->siAttackType == ATTACKTYPE_STAFFWIND )
			StringCchPrintf(buffer, 256, pText, pclPB->TotalEquipMinDamage*2, pclPB->TotalEquipMaxDamage*2);
		else
			StringCchPrintf(buffer, 256, pText, pclPB->TotalEquipMinDamage, pclPB->TotalEquipMaxDamage);
	}
	else
	{
		pText = GetTxtFromMgr(651);
		StringCchPrintf(buffer, 256, pText, pclPB->TotalEquipMinDamage, pclPB->TotalEquipMaxDamage);
	}

	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );

	// ��ȭ 
	if(pclPB->siEvolveDamage)
	{
		pText = GetTxtFromMgr(652);
		StringCchPrintf(buffer, 256, pText, pclPB->siEvolveDamage );
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}
	
	if(pclPB->siAttackType == ATTACKTYPE_STAFF1 || pclPB->siAttackType == ATTACKTYPE_STAFF2 || pclPB->siAttackType == ATTACKTYPE_NEW_STAFF2)
	{
		// ���¿� ���� ���ݷ�. 
		pText = GetTxtFromMgr(653);
		StringCchPrintf(buffer, 256, pText, pclPB->GetMagDamageIfChange(m_siTempMag));
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );

		// �����̼��� ���� ���ݷ�. 
		pText = GetTxtFromMgr(654);
		StringCchPrintf(buffer, 256, pText, pclPB->siStaffSkillDamage);
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}
	else if ( pclPB->siAttackType == ATTACKTYPE_STAFFWIND ) // ������� ���
	{
		// ���¿� ���� ���ݷ�. 
		pText = GetTxtFromMgr(653);
		StringCchPrintf(buffer, 256, pText, pclPB->GetMagDamageIfChange(m_siTempMag));
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}
	else
	{
		// �ٷ¿� ���� ���ݷ�. 
		pText = GetTxtFromMgr(655);
		bool flag = false;
		// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
		//if( pclClient->IsWhereServiceArea( ConstSwitch_PVP ) )
		if(pclClient->siEnablePVP == 1)
		{
			flag = true;
		}
		else
			flag = false;

		StringCchPrintf(buffer, 256, pText,  pclPB->GetStrDamageIfChange( m_siTempStr, flag));  //pclPB->siStrDamage);
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}

	/*	// ��Ʈ �����ۿ� ���� ���ݷ�
	if ( ((cltCharClient*)pclClient->pclCM->CR[1])->m_siSetItemType > 0 )
	{
	pText = GetTxtFromMgr(5416);
	StringCchPrintf(buffer, 256, pText, 20, '%');
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}*/

	// ����ȿ��
	if ( pclPB->siGeneralDamage )
	{
		pText = GetTxtFromMgr(656);
		StringCchPrintf(buffer, 256, pText, pclPB->siGeneralDamage, '%');
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}

	if ( pclPB->siBufDamage )
	{
		pText = GetTxtFromMgr(6490);
		StringCchPrintf(buffer, 256, pText, pclPB->siBufDamage, '%' );
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}

	if( pclClient->IsCountrySwitch(Switch_NamingQuest) )
	{
		if ( pclPB->siNamingDamage )
		{
			pText = GetTxtFromMgr(10088);
			StringCchPrintf(buffer, 256, pText, pclPB->siNamingDamage, '%' );
			tmpComboBoxItemData.Init();
			tmpComboBoxItemData.Set( buffer );
			m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
		}
	}

	// [�߰� : Ȳ���� 2008. 2. 22 => �����ϸ� �����Ǵ� ���ݷ��� �޺��ڽ��� ����Ѵ�.]
	if( SI32 AddAttackDamage = AddTransformAttackDamage() )
	{
		// ���ſ� ���� �ɷ����
		NTCHARString256	kBuf(GetTxtFromMgr(7794));
		kBuf.Replace("#value#", SI32ToString(AddAttackDamage));  
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( kBuf );
		m_pCombobox_apowername->AddItem( &tmpComboBoxItemData );
	}
}

SI32 cltNPersonStatus::GetTotalMinDamage(cltParametaBox* pclPB, cltItem* pclitemlist, SI32 activesweapon )
{
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
	SI32 siRetTotalMinDamage = 0;

	if(pclPB->siAttackType == ATTACKTYPE_STAFF1 || pclPB->siAttackType == ATTACKTYPE_STAFF2 || pclPB->siAttackType == ATTACKTYPE_NEW_STAFF2)
	{
		// ���¿� ���� ���ݷ�. 

		siRetTotalMinDamage += pclPB->GetMagDamageIfChange(m_siTempMag);

		// �����̼��� ���� ���ݷ�. 
		siRetTotalMinDamage +=  pclPB->siStaffSkillDamage;

	}
	else if ( pclPB->siAttackType == ATTACKTYPE_STAFFWIND ) // ������� ���
	{
		// ���¿� ���� ���ݷ�. 

		siRetTotalMinDamage += pclPB->GetMagDamageIfChange(m_siTempMag);

	}
	else
	{
		//�ٷ¿� ���� ���ݷ�.
		bool flag = false;
		// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
		//if( pclClient->IsWhereServiceArea( ConstSwitch_PVP ) )
		if(pclClient->siEnablePVP == 1)
		{
			flag = true;
		}
		else
			flag = false;

		siRetTotalMinDamage += pclPB->GetStrDamageIfChange(m_siTempStr, flag);
	}


	siRetTotalMinDamage += 	pclPB->TotalEquipMinDamage + pclPB->siLevelDamage;

	/*	// ��Ʈ �����ۿ� ���� ������ ���
	if ( pclchar &&  pclchar->m_siSetItemType > 0 )
	{
	siRetTotalMinDamage = siRetTotalMinDamage * 120 / 100;
	}	*/	

	// ���� ȿ���� ���� ������ ���
	if( pclPB->siGeneralDamage )
	{

		siRetTotalMinDamage = siRetTotalMinDamage * (100 + pclPB->siGeneralDamage) / 100;
	}

	/*
	// �������� �� ���� ������ ���

	SI32 itemtype = 0 ;
	if ( pclitemlist )
		itemtype = pclClient->pclItemManager->GetItemType(pclitemlist[activesweapon].siUnique) ;
	SI32 skilllevel = 0 ;

	switch ( itemtype )
	{
	case ITEMTYPE_SWORD:
		{
			//skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_SWORD_INCWEAAT, 0, 0, pclitemlist);//
		}
		break;
	case ITEMTYPE_GUN:
		{
			skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_GUN_INCWEAAT, 0, 0, pclitemlist);
		}
		break;
	}

	if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
	{
		// SJY DEBUG
		SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW2,skilllevel) ;

		siRetTotalMinDamage = siRetTotalMinDamage + siRetTotalMinDamage * rate / 100 ;

	}
	*/

	//Ȱ������ ���� ������ ���

	if ( pclchar && pclchar->pclCI->clBI.bCombatService )
	{
		siRetTotalMinDamage = siRetTotalMinDamage + siRetTotalMinDamage * 30 / 100 ;
	}

	//������ ���� ������ ���
	cltBufInfo clBuf;
	clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
	SI16 percent = 0 ;
	SI16 add = 0;

	for( SI16 i=0 ; i < MAX_BUF_COUNT ; i++ )
	{
		if ( clBuf.m_stBuf[i].siBufType == BUF_FRIENDSHIP ) 
		{
			percent += 20 ;
		}

		if ( clBuf.m_stBuf[i].siBufType == BUF_HINAMOCHI ) 
		{
			percent += 20 ;
		}
	}

	for ( SI16 i=0 ; i < MAX_BUF_COUNT ; i++ )
	{
		if ( clBuf.m_stBuf[i].siBufType == BUF_ATTACKUP) 
		{
			percent = max( percent , clBuf.m_stBuf[i].siPercent );
		}
	}
	for ( SI16 i=0 ; i < MAX_BUF_COUNT ; i++ )
	{
		if ( clBuf.m_stBuf[i].siBufType == BUF_ATTACKUP30) //������ ������ 30�ϰ�[2007.08.30 �ռ���]
		{
			percent = max( percent , clBuf.m_stBuf[i].siPercent );
		}
	}

	for (  i=0 ; i < MAX_BUF_COUNT ; i++ )
	{
		if ( clBuf.m_stBuf[i].siBufType == BUF_HAPPYBEAN ) //���Ǻ� �̺�Ʈ [2007.08.24 �ռ���]
		{
			percent += 10;
		}

		if ( clBuf.m_stBuf[i].siBufType == BUF_THANKSGIVING_DAY ) //[�߰� : Ȳ���� 2007. 11. 12 �߼� ������ �̺�Ʈ. ���� ����]
		{
			percent += 10;
		}

		if ( clBuf.m_stBuf[i].siBufType == BUF_MENTOR ) //[����] ����, ���� ����.
		{
			percent += 10;
		}

		if ( clBuf.m_stBuf[i].siBufType == BUF_EVENT_EGGMOONCAKE ) //[����] ���׿���.	=> 2008-8-14
		{
			SI32 AddPercent = 0;
			SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
			if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				AddPercent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );

			percent += AddPercent;
		}
		//// �����̾� ������ ��� ������ Ǯ���� ��µ����� Ÿ�� ���ݷ� 5% ����
		//if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
		//{
		//	cltHorse* pclHorse = pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()	;
		//	SI16 siHorseunique = pclHorse->siHorseUnique	;
		//	if ( pclHorse != NULL &&
		//		pclHorse->GetPremiumPartsNum() == 3 )
		//	{
		//		switch (siHorseunique )
		//		{
		//		case HORSEUNIQUE_BROWN:	// ������
		//		case HORSEUNIQUE_BLACK:// �渶
		//		case HORSEUNIQUE_WHITE:// �鸶
		//		case HORSEUNIQUE_RED://���丶
		//		case HORSEUNIQUE_RUDOLF ://�絹��
		//		case HORSEUNIQUE_STEEL ://ö�⸶
		//		case HORSEUNIQUE_BEAST ://����ȣ
		//		case HORSEUNIQUE_THOUSAND ://õ����
		//		case HORSEUNIQUE_ZEBRA ://��踶
		//			{
		//				percent += 5;
		//			}
		//			break;
		//		}
		//	}	
		//}
	}

	for (SI32 i = 0; i < MAX_HIRED_EVENTNPC_NUM; i++) 
	{
		if( pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
			pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")) ||
			pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))	||	
			pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))		)
		{
			percent += 10;
		}
	}
	
	siRetTotalMinDamage += siRetTotalMinDamage * percent / 100;
	siRetTotalMinDamage += add;

	if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
	{
		cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
		if ( pclunit )
		{
			siRetTotalMinDamage += siRetTotalMinDamage * pclunit->GetAttack() / 100;
		}

	}

	//[�߰� : Ȳ���� 2008. 2. 22 => ���Ž� ��ũ�ο� ���� ���ݷ��� �����ǰ� C]
	siRetTotalMinDamage += AddTransformAttackDamage();	
	
	// PCK : ����ġ�� Ÿ�� ������ ���ݷ� �����ǰ� �߰�
	// PCK : ������Ʈ �߰� (09.07.30)
	// PCK : ����� �߰� (09.12.31)
	if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
	{
		if( pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_FIREHATCH ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_BAPHOMET ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_SASURI )
		{
			siRetTotalMinDamage += 100;
		}
	}

	return     siRetTotalMinDamage;
}

SI32 cltNPersonStatus::GetTotalMaxDamage(cltParametaBox* pclPB, cltItem* pclitemlist, SI32 activesweapon )
{

	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
	SI32 siRetTotalMaxDamage = 0;

	if(pclPB->siAttackType == ATTACKTYPE_STAFF1 || pclPB->siAttackType == ATTACKTYPE_STAFF2 || pclPB->siAttackType == ATTACKTYPE_NEW_STAFF2)
	{
		// ���¿� ���� ���ݷ�. 

		siRetTotalMaxDamage += pclPB->GetMagDamageIfChange(m_siTempMag);

		// �����̼��� ���� ���ݷ�. 
		siRetTotalMaxDamage +=  pclPB->siStaffSkillDamage;

	}
	else if ( pclPB->siAttackType == ATTACKTYPE_STAFFWIND ) // ������� ���
	{
		// ���¿� ���� ���ݷ�. 

		siRetTotalMaxDamage += pclPB->GetMagDamageIfChange(m_siTempMag);

	}
	else
	{
		//�ٷ¿� ���� ���ݷ�.
		bool flag = false;
		// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
		//if( pclClient->IsWhereServiceArea( ConstSwitch_PVP ) )
		if(pclClient->siEnablePVP == 1)
		{
			flag = true;
		}
		else
			flag = false;

		siRetTotalMaxDamage += pclPB->GetStrDamageIfChange(m_siTempStr, flag);
	}

	siRetTotalMaxDamage += 	pclPB->TotalEquipMaxDamage + pclPB->siLevelDamage;

	// ��Ʈ �����ۿ� ���� ������ ���
	/*	if ( pclchar &&  pclchar->m_siSetItemType > 0 )
	{
	siRetTotalMaxDamage = siRetTotalMaxDamage * 120 / 100;
	}		*/

	// ���� ȿ���� ���� ������ ���
	if( pclPB->siGeneralDamage )
	{

		siRetTotalMaxDamage = siRetTotalMaxDamage * (100 + pclPB->siGeneralDamage) / 100;
	}

	/*
	// �������� �� ���� ������ ���

	SI32 itemtype = 0 ;
	if ( pclitemlist )
		itemtype = pclClient->pclItemManager->GetItemType(pclitemlist[activesweapon].siUnique) ;
	SI32 skilllevel = 0 ;

	switch ( itemtype )
	{
	case ITEMTYPE_SWORD:
		{
			//skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_SWORD_INCWEAAT, 0, 0, pclitemlist);//
		}
		break;
	case ITEMTYPE_GUN:
		{
			skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_GUN_INCWEAAT, 0, 0, pclitemlist);
		}
		break;
	}

	if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
	{
		// SJY DEBUG
		SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW2,skilllevel) ;

		siRetTotalMaxDamage = siRetTotalMaxDamage + siRetTotalMaxDamage * rate / 100 ;

	}
	*/

	//Ȱ������ ���� ������ ���

	if ( pclchar && pclchar->pclCI->clBI.bCombatService )
	{
		siRetTotalMaxDamage = siRetTotalMaxDamage + siRetTotalMaxDamage * 30 / 100 ;
	}

	//������ ���� ������ ���
	cltBufInfo clBuf;
	clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
	SI16 percent = 0 ;
	SI16 add = 0;

	for ( SI16 i=0 ; i < MAX_BUF_COUNT ; i++ )
	{		
		if ( clBuf.m_stBuf[i].siBufType == BUF_FRIENDSHIP ) 
		{
			percent += 20 ;
		}
		if ( clBuf.m_stBuf[i].siBufType == BUF_HINAMOCHI ) 
		{
			percent += 20 ;
		}
	}
	
	for( i = 0 ; i < MAX_BUF_COUNT ; i ++ )
	{
		if ( clBuf.m_stBuf[i].siBufType == BUF_ATTACKUP) 
		{
			percent = max( percent , clBuf.m_stBuf[i].siPercent );
		}
	}
	for( i = 0 ; i < MAX_BUF_COUNT ; i ++ )
	{
		if ( clBuf.m_stBuf[i].siBufType == BUF_ATTACKUP30) //������ ������ 30�ϰ�[2007.08.30 �ռ���]
		{
			percent = max( percent , clBuf.m_stBuf[i].siPercent );
		}
	}

	for (  i=0 ; i < MAX_BUF_COUNT ; i++ )
	{
		if ( clBuf.m_stBuf[i].siBufType == BUF_HAPPYBEAN ) //���Ǻ� �̺�Ʈ [2007.08.24 �ռ���]
		{
			percent += 10;
		}
		
		if ( clBuf.m_stBuf[i].siBufType == BUF_THANKSGIVING_DAY ) //[�߰� : Ȳ���� 2007. 11. 12 �߼� ������ �̺�Ʈ. ���� ����]
		{
			percent += 10;
		}
		
		if ( clBuf.m_stBuf[i].siBufType == BUF_MENTOR ) //[����] ����, ���� ����.
		{
			percent += 10;
		}
		
		if ( clBuf.m_stBuf[i].siBufType == BUF_EVENT_EGGMOONCAKE ) //[����] ���׿���.	=> 2008-8-14
		{
			SI32 AddPercent = 0;
			SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
			if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				AddPercent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );

			percent += AddPercent;
		}
	}
    
	for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) 
	{
		if( pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
			pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")) ||
			pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))	||	
			pclchar->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))		)
		{  
			percent += 10;
		}

	}
	//// �����̾� ������ ��� ������ Ǯ���� ��µ����� Ÿ�� ���ݷ� 5% ����
	//if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
	//{
	//	cltHorse* pclHorse = pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()	;
	//	SI16 siHorseunique = pclHorse->siHorseUnique	;
	//	if ( pclHorse != NULL &&
	//		pclHorse->GetPremiumPartsNum() == 3 )
	//	{
	//		switch (siHorseunique )
	//		{
	//		case HORSEUNIQUE_BROWN:	// ������
	//		case HORSEUNIQUE_BLACK:// �渶
	//		case HORSEUNIQUE_WHITE:// �鸶
	//		case HORSEUNIQUE_RED://���丶
	//		case HORSEUNIQUE_RUDOLF ://�絹��
	//		case HORSEUNIQUE_STEEL ://ö�⸶
	//		case HORSEUNIQUE_BEAST ://����ȣ
	//		case HORSEUNIQUE_THOUSAND ://õ����
	//		case HORSEUNIQUE_ZEBRA ://��踶
	//			{
	//				percent += 5;
	//			}
	//			break;
	//		}
	//	}	
	//}
	
	if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
	{
		cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
		if ( pclunit )
		{
			siRetTotalMaxDamage += siRetTotalMaxDamage * pclunit->GetAttack() / 100;
		}

	}
	siRetTotalMaxDamage += siRetTotalMaxDamage * percent / 100;
	siRetTotalMaxDamage += add;

	//[�߰� : Ȳ���� 2008. 2. 22 => ���Ž� ��ũ�ο� ���� ���ݷ��� �����ǰ� C]
	siRetTotalMaxDamage += AddTransformAttackDamage();

	// PCK : ����ġ�� Ÿ�� ������ ���ݷ� �����ǰ� �߰�
	// PCK : ������Ʈ �߰� (09.07.30)
	// PCK : ����� �߰� (09.12.31)
	if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
	{
		if( pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_FIREHATCH ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_BAPHOMET ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_SASURI )
		{
			siRetTotalMaxDamage += 100;
		}
	}
	return     siRetTotalMaxDamage;
}

// �ٷ� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailStrInfo( cltParametaBox* pclPB)
{
	TCHAR buffer[256]		= "";
	TCHAR bufferNew[256]	= "";
	TCHAR szTemp[32]		= "";
	SI32  Lenth				= 0; 
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_strength->Clear();

	// �⺻ �ٷ� 
	TCHAR* pText = GetTxtFromMgr(657);
	StringCchPrintf(buffer, 256, pText, pclPB->pclIP->GetStr() + m_siTempStr);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->pclIP->GetStr() + m_siTempStr);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew );
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��� ���� �ٷ�
	SI32 siSetItemStr = 0;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

		cltSetItemAbility* pcltSetItemAbility1 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_1 );
		cltSetItemAbility* pcltSetItemAbility2 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_2 );
		cltSetItemAbility* pcltSetItemAbility3 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_3 );
		cltSetItemAbility* pcltSetItemAbility4 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_4 );
		cltSetItemAbility* pcltSetItemAbility5 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_5 );

		if(pcltSetItemAbility1 != NULL && pcltSetItemAbility2 != NULL && pcltSetItemAbility3 != NULL && pcltSetItemAbility4 != NULL && pcltSetItemAbility5 != NULL) 
		{
			if((pcltSetItemAbility1->m_siStr > 0) || (pcltSetItemAbility2->m_siStr > 0) || (pcltSetItemAbility3->m_siStr > 0) || (pcltSetItemAbility4->m_siStr > 0) || (pcltSetItemAbility5->m_siStr > 0))
				siSetItemStr = pcltSetItemAbility1->m_siStr + pcltSetItemAbility2->m_siStr + pcltSetItemAbility3->m_siStr + pcltSetItemAbility4->m_siStr + pcltSetItemAbility5->m_siStr;
		}	
	}

	pText = GetTxtFromMgr(658);
	StringCchPrintf(buffer, 256, pText, pclPB->clEquipBA.GetStr() + siSetItemStr);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clEquipBA.GetStr() + siSetItemStr);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���� ���� �ٷ� 
	pText = GetTxtFromMgr(659);
	StringCchPrintf(buffer, 256, pText, pclPB->clHorseBA.GetStr());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clHorseBA.GetStr());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// �ǰ��� ���� �ٷ� 
	pText = GetTxtFromMgr(660);
	StringCchPrintf(buffer, 256, pText, pclPB->siHealthStrRate );      
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->siHealthStrRate);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��忡 ���� �ٷ� 
	pText = GetTxtFromMgr(6577);
	StringCchPrintf(buffer, 256, pText, pclPB->clGuildBA.GetStr());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clGuildBA.GetStr());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���ſ� ���� �ɷ����
	NTCHARString256	kBuf(GetTxtFromMgr(7794));
	kBuf.Replace("#value#", SI32ToString(pclPB->clTransFormBA.GetStr()));
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( kBuf );
	m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

	_tcscat( bufferNew, kBuf );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		kBuf.FormatString(GetTxtFromMgr(9771));
		kBuf.Replace("#value#", SI32ToString(pclClient->pclCM->CR[1]->pcltElixir->GetStr()));
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( kBuf );
		m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

		_tcscat( bufferNew, kBuf );
		Lenth = strlen( bufferNew ); 
		bufferNew[Lenth] = '\r';
		bufferNew[Lenth+1] = ' ';
	}


	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		m_pEditbox_strength->SetUseToolTip( bufferNew );  
	}
}

// ���߷� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailDexInfo( cltParametaBox* pclPB )
{
	TCHAR buffer[256]		= "";
	TCHAR bufferNew[256]	= "";
	TCHAR szTemp[32]		= "";
	SI32  Lenth				= 0; 
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_dex->Clear();

	// �⺻ DEX
	TCHAR* pText = GetTxtFromMgr(657);
	StringCchPrintf(buffer, 256, pText, pclPB->pclIP->GetDex() + m_siTempDex);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dex->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->pclIP->GetDex() + m_siTempDex);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew );
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��� ���� DEX
	SI32 siSetItemDex = 0;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		if(pclClient->GameMode == GAMEMODE_CLIENT)
		{
			SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
			cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

			cltSetItemAbility* pcltSetItemAbility1 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_1 );
			cltSetItemAbility* pcltSetItemAbility2 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_2 );
			cltSetItemAbility* pcltSetItemAbility3 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_3 );
			cltSetItemAbility* pcltSetItemAbility4 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_4 );
			cltSetItemAbility* pcltSetItemAbility5 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_5 );

			if(pcltSetItemAbility1 != NULL && pcltSetItemAbility2 != NULL && pcltSetItemAbility3 != NULL && pcltSetItemAbility4 != NULL && pcltSetItemAbility5 != NULL) 
			{
				if((pcltSetItemAbility1->m_siDex > 0) || (pcltSetItemAbility2->m_siDex > 0) || (pcltSetItemAbility3->m_siDex > 0) || (pcltSetItemAbility4->m_siDex > 0) || (pcltSetItemAbility5->m_siDex > 0))
					siSetItemDex = pcltSetItemAbility1->m_siDex + pcltSetItemAbility2->m_siDex + pcltSetItemAbility3->m_siDex + pcltSetItemAbility4->m_siDex + pcltSetItemAbility5->m_siDex;
			}	
		}
	}

	pText = GetTxtFromMgr(658);
	StringCchPrintf(buffer, 256, pText, pclPB->clEquipBA.GetDex() + siSetItemDex);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dex->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clEquipBA.GetDex() + siSetItemDex);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���� ���� DEX
	pText = GetTxtFromMgr(659);
	StringCchPrintf(buffer, 256, pText, pclPB->clHorseBA.GetDex());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dex->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clHorseBA.GetDex());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// �ǰ��� ���� Dex
	pText = GetTxtFromMgr(660);
	StringCchPrintf(buffer, 256, pText, pclPB->siHealthDexRate );      
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dex->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->siHealthDexRate);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��忡 ���� DEX
	pText = GetTxtFromMgr(6577);
	StringCchPrintf(buffer, 256, pText, pclPB->clGuildBA.GetDex());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dex->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clGuildBA.GetDex());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���ſ� ���� �ɷ����
	NTCHARString256	kBuf(GetTxtFromMgr(7794));
	kBuf.Replace("#value#", SI32ToString(pclPB->clTransFormBA.GetDex()));
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( kBuf );
	m_pCombobox_dex->AddItem( &tmpComboBoxItemData );

	_tcscat( bufferNew, kBuf );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		kBuf.FormatString(GetTxtFromMgr(9771));
		kBuf.Replace("#value#", SI32ToString(pclClient->pclCM->CR[1]->pcltElixir->GetDex()));
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( kBuf );
		m_pCombobox_dex->AddItem( &tmpComboBoxItemData );

		_tcscat( bufferNew, kBuf );
		Lenth = strlen( bufferNew ); 
		bufferNew[Lenth] = '\r';
		bufferNew[Lenth+1] = ' ';
	}
	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		m_pEditbox_dex->SetUseToolTip( bufferNew );  
	}
}

// ���� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailMagInfo( cltParametaBox* pclPB)
{
	TCHAR buffer[256];
	TCHAR bufferNew[256]	= "";
	TCHAR szTemp[32]		= "";
	SI32  Lenth				= 0;
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_magic->Clear();

	// �⺻ ����
	TCHAR* pText = GetTxtFromMgr(657);
	StringCchPrintf(buffer, 256, pText, pclPB->pclIP->GetMag() + m_siTempMag );
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_magic->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->pclIP->GetMag() + m_siTempMag);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��� ���� ���� 
	SI32 siSetItemMag = 0;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

		cltSetItemAbility* pcltSetItemAbility1 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_1 );
		cltSetItemAbility* pcltSetItemAbility2 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_2 );
		cltSetItemAbility* pcltSetItemAbility3 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_3 );
		cltSetItemAbility* pcltSetItemAbility4 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_4 );
		cltSetItemAbility* pcltSetItemAbility5 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_5 );

		if(pcltSetItemAbility1 != NULL && pcltSetItemAbility2 != NULL && pcltSetItemAbility3 != NULL && pcltSetItemAbility4 != NULL && pcltSetItemAbility5 != NULL) 
		{
			if((pcltSetItemAbility1->m_siMag > 0) || (pcltSetItemAbility2->m_siMag > 0) || (pcltSetItemAbility3->m_siMag > 0) || (pcltSetItemAbility4->m_siMag > 0) || (pcltSetItemAbility5->m_siMag > 0))
				siSetItemMag = pcltSetItemAbility1->m_siMag + pcltSetItemAbility2->m_siMag + pcltSetItemAbility3->m_siMag + pcltSetItemAbility4->m_siMag + pcltSetItemAbility5->m_siMag;
		}	
	}

	pText = GetTxtFromMgr(658);
	StringCchPrintf(buffer, 256, pText, pclPB->clEquipBA.GetMag() + siSetItemMag);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_magic->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clEquipBA.GetMag() + siSetItemMag);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���� ���� ���� 
	pText = GetTxtFromMgr(659);
	StringCchPrintf(buffer, 256, pText, pclPB->clHorseBA.GetMag());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_magic->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clHorseBA.GetMag());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// �ǰ��� ���� ���� 
	pText = GetTxtFromMgr(660);
	StringCchPrintf(buffer, 256, pText, pclPB->siHealthMagRate);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_magic->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->siHealthMagRate);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��忡 ���� ���� 
	pText = GetTxtFromMgr(6577);
	StringCchPrintf(buffer, 256, pText, pclPB->clGuildBA.GetMag(), '%');
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_magic->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clGuildBA.GetMag());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���ſ� ���� �ɷ����
	NTCHARString256	kBuf(GetTxtFromMgr(7794));
	kBuf.Replace("#value#", SI32ToString(pclPB->clTransFormBA.GetMag()));
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( kBuf );
	m_pCombobox_magic->AddItem( &tmpComboBoxItemData );

	_tcscat( bufferNew, kBuf );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		kBuf.FormatString(GetTxtFromMgr(9771));
		kBuf.Replace("#value#", SI32ToString(pclClient->pclCM->CR[1]->pcltElixir->GetMag()));
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( kBuf );
		m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

		_tcscat( bufferNew, kBuf );
		Lenth = strlen( bufferNew ); 
		bufferNew[Lenth] = '\r';
		bufferNew[Lenth+1] = ' ';
	}

	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		m_pEditbox_magic->SetUseToolTip( bufferNew );  
	}
}

// ����� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailVitInfo( cltParametaBox* pclPB )
{
	TCHAR buffer[256];
	TCHAR bufferNew[256]	= "";
	TCHAR szTemp[32]		= "";
	SI32  Lenth				= 0;
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_life2->Clear();

	// �⺻ ü�� 
	TCHAR* pText = GetTxtFromMgr(657);
	StringCchPrintf(buffer, 256, pText, pclPB->pclIP->GetVit() + m_siTempVit );
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_life2->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->pclIP->GetVit() + m_siTempVit);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��� ���� ü�� 
	SI32 siSetItemVit = 0;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

		cltSetItemAbility* pcltSetItemAbility1 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_1 );
		cltSetItemAbility* pcltSetItemAbility2 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_2 );
		cltSetItemAbility* pcltSetItemAbility3 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_3 );
		cltSetItemAbility* pcltSetItemAbility4 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_4 );
		cltSetItemAbility* pcltSetItemAbility5 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_5 );

		if(pcltSetItemAbility1 != NULL && pcltSetItemAbility2 != NULL && pcltSetItemAbility3 != NULL && pcltSetItemAbility4 != NULL && pcltSetItemAbility5 != NULL) 
		{
			if((pcltSetItemAbility1->m_siVit > 0) || (pcltSetItemAbility2->m_siVit > 0) || (pcltSetItemAbility3->m_siVit > 0) || (pcltSetItemAbility4->m_siVit > 0) || (pcltSetItemAbility5->m_siVit > 0))
				siSetItemVit = pcltSetItemAbility1->m_siVit + pcltSetItemAbility2->m_siVit + pcltSetItemAbility3->m_siVit + pcltSetItemAbility4->m_siVit + pcltSetItemAbility5->m_siVit;
		}	
	}

	pText = GetTxtFromMgr(658);
	StringCchPrintf(buffer, 256, pText, pclPB->clEquipBA.GetVit() + siSetItemVit);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_life2->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clEquipBA.GetVit() + siSetItemVit);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���� ���� ü��
	pText = GetTxtFromMgr(659);
	StringCchPrintf(buffer, 256, pText, pclPB->clHorseBA.GetVit());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_life2->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clHorseBA.GetVit());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';
	
	// ��忡 ���� ü�� 
	pText = GetTxtFromMgr(6577);
	StringCchPrintf(buffer, 256, pText, pclPB->clGuildBA.GetVit(), '%');
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_life2->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clGuildBA.GetVit());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���ſ� ���� �ɷ����
	NTCHARString256	kBuf(GetTxtFromMgr(7794));  
	kBuf.Replace("#value#", SI32ToString(pclPB->clTransFormBA.GetVit()));
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( kBuf );
	m_pCombobox_life2->AddItem( &tmpComboBoxItemData );

	_tcscat( bufferNew, kBuf ); 
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';
 
	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		kBuf.FormatString(GetTxtFromMgr(9771));
		kBuf.Replace("#value#", SI32ToString(pclClient->pclCM->CR[1]->pcltElixir->GetVit()));
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( kBuf );
		m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

		_tcscat( bufferNew, kBuf );
		Lenth = strlen( bufferNew ); 
		bufferNew[Lenth] = '\r';
		bufferNew[Lenth+1] = ' ';
	}

	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		m_pEditbox_life2->SetUseToolTip( bufferNew );  
	}
}

// ������ �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailHndInfo( cltParametaBox* pclPB )
{
	TCHAR buffer[256];
	TCHAR bufferNew[256]	= "";
	TCHAR szTemp[32]		= "";
	SI32  Lenth				= 0;
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_hand->Clear();

	// �⺻ ������
	TCHAR* pText = GetTxtFromMgr(657);
	StringCchPrintf(buffer, 256, pText, pclPB->pclIP->GetHnd() + m_siTempHnd);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_hand->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->pclIP->GetHnd() + m_siTempHnd);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��� ���� ������
	SI32 siSetItemHnd = 0;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

		cltSetItemAbility* pcltSetItemAbility1 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_1 );
		cltSetItemAbility* pcltSetItemAbility2 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_2 );
		cltSetItemAbility* pcltSetItemAbility3 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_3 );
		cltSetItemAbility* pcltSetItemAbility4 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_4 );
		cltSetItemAbility* pcltSetItemAbility5 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_5 );

		if(pcltSetItemAbility1 != NULL && pcltSetItemAbility2 != NULL && pcltSetItemAbility3 != NULL && pcltSetItemAbility4 != NULL && pcltSetItemAbility5 != NULL) 
		{
			if((pcltSetItemAbility1->m_siHnd > 0) || (pcltSetItemAbility2->m_siHnd > 0) || (pcltSetItemAbility3->m_siHnd > 0) || (pcltSetItemAbility4->m_siHnd > 0) || (pcltSetItemAbility5->m_siHnd > 0))
				siSetItemHnd = pcltSetItemAbility1->m_siHnd + pcltSetItemAbility2->m_siHnd + pcltSetItemAbility3->m_siHnd + pcltSetItemAbility4->m_siHnd + pcltSetItemAbility5->m_siHnd;
		}	
	}

	pText = GetTxtFromMgr(658);
	StringCchPrintf(buffer, 256, pText, pclPB->clEquipBA.GetHnd() + siSetItemHnd);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_hand->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clEquipBA.GetHnd() + siSetItemHnd);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���� ���� ������.
	pText = GetTxtFromMgr(659);
	StringCchPrintf(buffer, 256, pText, pclPB->clHorseBA.GetHnd());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_hand->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clHorseBA.GetHnd());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��忡 ���� ������
	pText = GetTxtFromMgr(6577);
	StringCchPrintf(buffer, 256, pText, pclPB->clGuildBA.GetHnd(), '%');
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_hand->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clGuildBA.GetHnd());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	pText = GetTxtFromMgr(660);
	StringCchPrintf(buffer, 256, pText, pclPB->siHealthHndRate);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_hand->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->siHealthHndRate);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���ſ� ���� �ɷ����
	NTCHARString256	kBuf(GetTxtFromMgr(7794));
	kBuf.Replace("#value#", SI32ToString(pclPB->clTransFormBA.GetHnd()));
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( kBuf );
	m_pCombobox_hand->AddItem( &tmpComboBoxItemData );

	_tcscat( bufferNew, kBuf );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		kBuf.FormatString(GetTxtFromMgr(9771));
		kBuf.Replace("#value#", SI32ToString(pclClient->pclCM->CR[1]->pcltElixir->GetHnd()));
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( kBuf );
		m_pCombobox_strength->AddItem( &tmpComboBoxItemData );

		_tcscat( bufferNew, kBuf );
		Lenth = strlen( bufferNew ); 
		bufferNew[Lenth] = '\r';
		bufferNew[Lenth+1] = ' ';
	}

	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		m_pEditbox_hand->SetUseToolTip( bufferNew );  
	}
}
// ��� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailLukInfo( cltParametaBox* pclPB )
{
	TCHAR buffer[256];
	TCHAR bufferNew[256]	= "";
	TCHAR szTemp[32]		= "";
	SI32  Lenth				= 0;
	stComboBoxItemData tmpComboBoxItemData;  

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_luk->Clear();

	// �⺻ ���
	TCHAR* pText = GetTxtFromMgr(657);
	sprintf(buffer, pText, pclPB->pclIP->GetLuk());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_luk->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->pclIP->GetLuk());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��� ���� ��� 
	SI32 siSetItemLuk = 0;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

		cltSetItemAbility* pcltSetItemAbility1 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_1 );
		cltSetItemAbility* pcltSetItemAbility2 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_2 );
		cltSetItemAbility* pcltSetItemAbility3 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_3 );
		cltSetItemAbility* pcltSetItemAbility4 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_4 );
		cltSetItemAbility* pcltSetItemAbility5 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_5 );

		if(pcltSetItemAbility1 != NULL && pcltSetItemAbility2 != NULL && pcltSetItemAbility3 != NULL && pcltSetItemAbility4 != NULL && pcltSetItemAbility5 != NULL) 
		{
			if((pcltSetItemAbility1->m_siLuk > 0) || (pcltSetItemAbility2->m_siLuk > 0) || (pcltSetItemAbility3->m_siLuk > 0) || (pcltSetItemAbility4->m_siLuk > 0) || (pcltSetItemAbility5->m_siLuk > 0))
				siSetItemLuk = pcltSetItemAbility1->m_siLuk + pcltSetItemAbility2->m_siLuk + pcltSetItemAbility3->m_siLuk + pcltSetItemAbility4->m_siLuk + pcltSetItemAbility5->m_siLuk;
		}	
	}

	pText = GetTxtFromMgr(658);
	sprintf(buffer, pText, pclPB->clEquipBA.GetLuk() + siSetItemLuk);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_luk->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clEquipBA.GetLuk() + siSetItemLuk);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���� ���� ���.
	pText = GetTxtFromMgr(659);
	StringCchPrintf(buffer, 256, pText, pclPB->clHorseBA.GetLuk());
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_luk->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clHorseBA.GetLuk());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��忡 ���� ���
	pText = GetTxtFromMgr(6577);  
	StringCchPrintf(buffer, 256, pText, pclPB->clGuildBA.GetLuk(), '%');
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_luk->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clGuildBA.GetLuk());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';
	
	pText = GetTxtFromMgr(660);
	StringCchPrintf(buffer, 256, pText, pclPB->siHealthLukRate);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_hand->AddItem( &tmpComboBoxItemData );

	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->siHealthLukRate);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ���ſ� ���� �ɷ����
	NTCHARString256	kBuf(GetTxtFromMgr(7794));
	kBuf.Replace("#value#", SI32ToString(pclPB->clTransFormBA.GetLuk()));
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( kBuf );
	m_pCombobox_luk->AddItem( &tmpComboBoxItemData );
	
	_tcscat( bufferNew, kBuf );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		m_pEditbox_luk->SetUseToolTip( bufferNew );  
	}
}

// ���� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailWisdomInfo( cltParametaBox* pclPB )
{
	TCHAR bufferNew[256]	= "";
	TCHAR szTemp[32]		= "";
	SI32  Lenth				= 0;
	
	// �⺻ ����
	TCHAR* pText = GetTxtFromMgr(657);
	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->pclIP->GetWis());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��� ���� ����
	SI32 siSetItemWis = 0;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

		cltSetItemAbility* pcltSetItemAbility1 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_1 );
		cltSetItemAbility* pcltSetItemAbility2 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_2 );
		cltSetItemAbility* pcltSetItemAbility3 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_3 );
		cltSetItemAbility* pcltSetItemAbility4 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_4 );
		cltSetItemAbility* pcltSetItemAbility5 = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityData( pclchar, USE_SETITEM_5 );

		if(pcltSetItemAbility1 != NULL && pcltSetItemAbility2 != NULL && pcltSetItemAbility3 != NULL && pcltSetItemAbility4 != NULL && pcltSetItemAbility5 != NULL) 
		{
			if((pcltSetItemAbility1->m_siWis > 0) || (pcltSetItemAbility2->m_siWis > 0) || (pcltSetItemAbility3->m_siWis > 0) || (pcltSetItemAbility4->m_siWis > 0) || (pcltSetItemAbility5->m_siWis > 0))
				siSetItemWis = pcltSetItemAbility1->m_siWis + pcltSetItemAbility2->m_siWis + pcltSetItemAbility3->m_siWis + pcltSetItemAbility4->m_siWis + pcltSetItemAbility5->m_siWis;
		}	
	}

	pText = GetTxtFromMgr(658);
	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clEquipBA.GetWis() + siSetItemWis);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' '; 

	// �ǰ��� ���� ����
	pText = GetTxtFromMgr(660);
	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->siHealthWisRate);
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// ��忡 ���� ����
	pText = GetTxtFromMgr(6577);
	StringCchPrintf(szTemp, sizeof(szTemp), pText, pclPB->clGuildBA.GetWis());
	_tcscat( bufferNew, szTemp );
	Lenth = strlen( bufferNew );
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' ';

	// [��ȣ] ���ſ� ���� �ɷ����
	NTCHARString256	kBuf(GetTxtFromMgr(7794));
	kBuf.Replace("#value#", SI32ToString(pclPB->clTransFormBA.GetWis()));
	_tcscat( bufferNew, kBuf );
	Lenth = strlen( bufferNew ); 
	bufferNew[Lenth] = '\r';
	bufferNew[Lenth+1] = ' '; 

	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		kBuf.FormatString(GetTxtFromMgr(9771));
		kBuf.Replace("#value#", SI32ToString(pclClient->pclCM->CR[1]->pcltElixir->GetWis()));
	
		_tcscat( bufferNew, kBuf );
		Lenth = strlen( bufferNew ); 
		bufferNew[Lenth] = '\r';
		bufferNew[Lenth+1] = ' ';
	}

	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		m_pEditbox_Wisdom->SetUseToolTip( bufferNew );  
	}
}

// ���� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailArmourInfo( cltParametaBox* pclPB )
{
	TCHAR buffer[256];
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_dpowername->Clear();

	// ������ ���� ����. 
	TCHAR* pText = GetTxtFromMgr(649);
	StringCchPrintf(buffer, 256, pText, pclPB->siLevelAC);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );

	// �⺻ ���� 
	pText = GetTxtFromMgr(657);
	StringCchPrintf(buffer, 256, pText, pclPB->siDefaultAC );
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );

	// ��ȭ 
	if(pclPB->siEvolveAC)
	{
		pText = GetTxtFromMgr(652);
		StringCchPrintf(buffer, 256, pText, pclPB->siEvolveAC );
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );
	}

	// ���� ���� 
	pText = GetTxtFromMgr(809);
	StringCchPrintf(buffer, 256, pText, pclPB->siEquipAC);
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );

	// ��Ʈ �����ۿ� ���� ����
	/*	if ( ((cltCharClient*)pclClient->pclCM->CR[1])->m_siSetItemType > 0 )
	{
	pText = GetTxtFromMgr(5416);
	StringCchPrintf(buffer, 256, pText, 30, '%');
	tmpComboBoxItemData.Init();
	tmpComboBoxItemData.Set( buffer );
	m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );
	}*/

	// ����ȿ��
	if( pclPB->siGeneralAC )
	{
		pText = GetTxtFromMgr(656);
		StringCchPrintf(buffer, 256, pText, pclPB->siGeneralAC, '%');
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );
	}

	// ����ȿ��
	if ( pclPB->siBufAC )
	{
		pText = GetTxtFromMgr(6490);
		StringCchPrintf(buffer, 256, pText, pclPB->siBufAC, '%');
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );
	}

	// ��Ī
	if ( pclPB->siNamingAC )
	{
		pText = GetTxtFromMgr(10088);
		StringCchPrintf(buffer, 256, pText, pclPB->siNamingAC, '%');
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );
	}

	// [�߰� : Ȳ���� 2008. 2. 22 => �����ϸ� �����Ǵ� ������ �޺��ڽ��� ����Ѵ�.]
	if( SI32 siAddTransformDeffense = AddTransformDeffense() )
	{
		// ���ſ� ���� �ɷ����
		NTCHARString256	kBuf(GetTxtFromMgr(7794));
		kBuf.Replace("#value#", SI32ToString(siAddTransformDeffense));  
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( kBuf );
		m_pCombobox_dpowername->AddItem( &tmpComboBoxItemData );
	}
}


// �̵��ӵ� �� ������ �����Ѵ�. 
void cltNPersonStatus::ShowDetailSpeedInfo( cltParametaBox* pclPB, cltCharClient* pclchar)
{
	TCHAR buffer[256];
	stComboBoxItemData tmpComboBoxItemData;

	// ��� �׸��� �����Ѵ�. 
	m_pCombobox_detail_speed->Clear();

	// ���� Ÿ�� �ִ� ���, //KHY - 1001 - ��µ��� 5���� ���� ����.
	//if(pclchar && pclchar->pclCI->clHorseInfo.siCurrentHorseIndex >= 0)
	if(pclchar && pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
	{
		// ���� �̵��ӵ�. 
		TCHAR* pText = GetTxtFromMgr(659);
		StringCchPrintf(buffer, 256, pText, pclPB->TotalMoveSpeed);
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_detail_speed->AddItem( &tmpComboBoxItemData );

		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			//m_pEditbox_move_speed->SetUseToolTip( buffer);
		}
	}
	// ���� Ÿ�� ���� ���� ���, 
	else
	{
		// �⺻ �̵��ӵ� 
		TCHAR* pText = GetTxtFromMgr(657);
		StringCchPrintf(buffer, 256, pText, pclPB->BasicMoveSpeed);
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_detail_speed->AddItem( &tmpComboBoxItemData );

		// �Ź� �̵��ӵ�.  
		pText = GetTxtFromMgr(661);
		StringCchPrintf(buffer, 256, pText, pclPB->ShoesMoveSpeed);
		tmpComboBoxItemData.Init();
		tmpComboBoxItemData.Set( buffer );
		m_pCombobox_detail_speed->AddItem( &tmpComboBoxItemData );

		if (pclchar->clInnerStatus.IsStatus(INNERSTATUS_INCREASEMOVESPEED))
		{
			pText = GetTxtFromMgr(6414);
			StringCchPrintf(buffer, 256, pText, INCREASEMOVESPEED_POWER);
			tmpComboBoxItemData.Init();
			tmpComboBoxItemData.Set( buffer );
			m_pCombobox_detail_speed->AddItem( &tmpComboBoxItemData );
		}

		//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
		if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
		{
			m_pEditbox_move_speed->SetUseToolTip( buffer );
		}
	}

}

void cltNPersonStatus::Action()
{
	UpdateCharStatusInfo();
}

void cltNPersonStatus::Hide()
{
	m_bShow = false;
	CControllerMgr::Show( false );
}

void cltNPersonStatus::Show()
{
	m_bShow = true;
	CControllerMgr::Show( true );
}

bool cltNPersonStatus::IsShow()
{
	return m_bShow;
}

void cltNPersonStatus::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient*)pclClient;

	switch( MsgIndex )
	{
	case 0:	// Person Tab => Strength Minus
	case 1:	// Person Tab => Dex Minus
	case 2:	// Person Tab => Maic Minus
	case 3:	// Person Tab => Life Minus
	case 4: // Person Tab => HandSkill Minus
	case 5: // Person Tab => Luk Minus
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				// leon todo - Ȯ�� �ʿ� wParan == nControlID ?
				SendUseBonusMessageToServer(*((SI16*)pData), -1);	
			}
		}
		break;
	case 6: // Person Tab => Init Button
		{
			if( RetValue )
			{
				cltMsg clMsg(GAMEMSG_REQUEST_INITSTATUS,0);
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		break;
		// Apply Button Press
	case 7:
		{
			if( RetValue )
			{
				ApplyTempStatusPoint();
			}	
		}
		break;
	}
	return;
}
SI32 cltNPersonStatus::AddTransformAttackDamage(void)
{
	SI32 siRetTotalDamage = 0;

	SI32 siAttackType = pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ pclClient->pclCM->CR[1]->ActiveWeapon ].GetAttackType(pclClient->pclItemManager);
	cltTransFormInfo* pTransformInfo = &pclClient->pclCM->CR[1]->clTransFormInfo;

	SI32 siTransFormSyc = (SI32)pTransformInfo->GetSynchroTransForm(pTransformInfo->uiNowTransFormKind);

	if((pTransformInfo) && (pTransformInfo->bTransFormMode == true))
	{
		switch(siAttackType)
		{ 
		case ATTACKTYPE_SWORD:
		case ATTACKTYPE_SPEAR:   
			{  
				if(siTransFormSyc >= 100) // ��ũ�� 100% ���ʽ�.
				{
					siRetTotalDamage += 20;
				}
			}  
			break;
		case ATTACKTYPE_AXE:
			{
				siRetTotalDamage += (SI32)(siTransFormSyc/2);
			}
			break;					
		case ATTACKTYPE_GUN:
			{				
				siRetTotalDamage += (SI32)((REAL32)siTransFormSyc*(REAL32)0.4);
			}
			break;					
		}
	}

	return siRetTotalDamage;
}

SI32 cltNPersonStatus::AddTransformDeffense(void)
{
	cltTransFormInfo* pTransformInfo = &pclClient->pclCM->CR[1]->clTransFormInfo;
	
	if((pTransformInfo) && (pTransformInfo->bTransFormMode == true))
	{
		if( pclClient->GetUniqueFromHash("KIND_NINJAMAN")  == pTransformInfo->uiNowTransFormKind		|| 
			pclClient->GetUniqueFromHash("KIND_NINJAGIRL") == pTransformInfo->uiNowTransFormKind		||			
			pclClient->GetUniqueFromHash("KIND_CATMELEE") == pTransformInfo->uiNowTransFormKind			||
			pclClient->GetUniqueFromHash("KIND_CATRANGE") == pTransformInfo->uiNowTransFormKind			||			
			pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN") == pTransformInfo->uiNowTransFormKind ||
			pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST") == pTransformInfo->uiNowTransFormKind	||
			pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE") == pTransformInfo->uiNowTransFormKind	||
			pclClient->GetUniqueFromHash("KIND_CHRISTMASRANGE") == pTransformInfo->uiNowTransFormKind	||
			pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE")	== pTransformInfo->uiNowTransFormKind	||	// �˻罺�Ǹ�(��)
			pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE")	== pTransformInfo->uiNowTransFormKind 	||	// �ųʽ��Ǹ�(��)
			pclClient->GetUniqueFromHash("KIND_FAIRYMELEE")	== pTransformInfo->uiNowTransFormKind			||	// �������Ǹ�(��)
			pclClient->GetUniqueFromHash("KIND_FAIRYRANGE")	== pTransformInfo->uiNowTransFormKind 			||	// �������Ǹ�(��)
			// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
			pclClient->GetUniqueFromHash("KIND_ICERANGE")	== pTransformInfo->uiNowTransFormKind			||	// ���� ����
			pclClient->GetUniqueFromHash("KIND_ICEMELEE")	== pTransformInfo->uiNowTransFormKind 				// �罺��ġ
		  )
		{
			SI32 siTransFormSyc = (SI32)pTransformInfo->GetSynchroTransForm(pTransformInfo->uiNowTransFormKind);
 
			SI32 siTransFormAC = 80; // �⺻ ����.
			SI32 temState	   = 0;
			temState		   = siTransFormAC * (siTransFormSyc / 2) / 100;
			siTransFormAC	   = siTransFormAC + temState;					
			
			return siTransFormAC;
		}
	}
	return 0;
}
void cltNPersonStatus::DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY )
{

}
void cltNPersonStatus::DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY )
{
	//[����] ĳ���� ���ο� ����â���� ����. => 2008-3-24	
	if(pclClient->IsCountrySwitch(Switch_CharStatusReform))
	{
		GP.PutSpr( &m_sprGageBack, GetX()+ScreenRX+98, GetY()+ScreenRY+43, 0 );
		DrawCharStatus( ScreenRX, ScreenRY-2 );         
	}    
}

void cltNPersonStatus::DrawCharStatus( SI32 ScreenRX, SI32 ScreenRY )
{ 	
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[1];
	if ( pclChar == NULL )
	{
		return;
	}

	SI32 i;

	SI32 siNowX				= GetX();
	SI32 siNowY				= GetY();

	SI32 siRealHPStartX		= siNowX + ScreenRX + CHARSTATUS_HP_START_X;
	SI32 siRealHPStartY		= siNowY + ScreenRY + CHARSTATUS_HP_START_Y;

	SI32 siRealMPStartX		= siNowX + ScreenRX + CHARSTATUS_MP_START_X;
	SI32 siRealMPStartY		= siNowY + ScreenRY + CHARSTATUS_MP_START_Y;

	SI32 siRealEXPStartX	= siNowX + ScreenRX + CHARSTATUS_EXP_START_X;
	SI32 siRealEXPStartY	= siNowY + ScreenRY + CHARSTATUS_EXP_START_Y;

	//-----------------------------------------------------------------------------
	//	HP ǥ�� [����]
	//-----------------------------------------------------------------------------
	SI32	siNowHp			= pclChar->pclCI->clIP.GetLife();
	SI32	siMaxHp			= pclChar->clPB.GetMaxLife();
	SI32	siHealHp		= pclChar->pclCI->clIP.Life + pclChar->clPB.siReservedLife;

	REAL32	f32LifeRate		= 1.0f;
	REAL32	f32HealLifeRate = 1.0f;


	if ( (siNowHp > siMaxHp) && (siMaxHp > 0) )
	{
		siNowHp = siMaxHp;
		f32LifeRate =	siNowHp / ( siMaxHp * 1.0f );
	}
	else if ( siMaxHp > 0 )
	{
		f32LifeRate	=	siNowHp / ( siMaxHp * 1.0f );
	}

	if ( (siHealHp > siMaxHp) && (siMaxHp > 0) )
	{
		siHealHp = siMaxHp ;
		f32HealLifeRate =	siHealHp / ( siMaxHp * 1.0f );
	}
	else if ( siHealHp > 0 )
	{
		f32HealLifeRate	=	siHealHp / ( siMaxHp * 1.0f );
	}

	SI32 siHpWidth		= (SI32)(CHARSTATUS_BAR_WIDTH * f32LifeRate);
	SI32 siHealWidth	= (SI32)(CHARSTATUS_BAR_WIDTH * f32HealLifeRate) ;

	if ( siHpWidth > 2 )
	{
		GP.PutSprScreen( &m_sprGage, siRealHPStartX , siRealHPStartY, CHARSTATUS_HP_NUM );
		for ( i = 2; i < siHealWidth - 2; i+=2 )
		{
			GP.PutSprScreen( &m_sprGage, siRealHPStartX + i, siRealHPStartY, CHARSTATUS_HP_NUM + 1 );
		}
		GP.PutSprScreen( &m_sprGage, siRealHPStartX + i, siRealHPStartY, CHARSTATUS_HP_NUM + 2 );

		GP.PutSpr( &m_sprGage, siRealHPStartX , siRealHPStartY, CHARSTATUS_HP_NUM );
		for ( i = 2; i < siHpWidth - 2; i+=2 )
		{
			GP.PutSpr( &m_sprGage, siRealHPStartX + i, siRealHPStartY, CHARSTATUS_HP_NUM + 1 );
		}
		GP.PutSpr( &m_sprGage, siRealHPStartX + i, siRealHPStartY, CHARSTATUS_HP_NUM + 2 );
	}
	else if ( siHpWidth > 0 )
	{
		GP.PutSprScreen( &m_sprGage, siRealHPStartX , siRealHPStartY, CHARSTATUS_HP_NUM + 2 );
		GP.PutSpr( &m_sprGage, siRealHPStartX , siRealHPStartY, CHARSTATUS_HP_NUM + 2 );
	}
	//-----------------------------------------------------------------------------
	//	HP ǥ�� [����]
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	//	MP ǥ�� [����]
	//-----------------------------------------------------------------------------
	SI32	siNowMp	= pclChar->pclCI->clIP.GetMana();
	SI32	siMaxMP	= pclChar->clPB.GetMaxMana();

	REAL32	f32ManaRate	= 1.0f; 


	if ( (siNowMp > siMaxMP) && (siMaxMP > 0) )
	{
		siNowMp = siMaxMP;
		f32ManaRate = siNowMp / ( siMaxMP * 1.0f );
	}
	else if ( siMaxMP > 0 )
	{
		f32ManaRate = siNowMp / ( siMaxMP * 1.0f );
	}

	SI32 siMpWidth = (SI32)(CHARSTATUS_BAR_WIDTH * f32ManaRate);

	if ( siMpWidth > 2 )
	{
		GP.PutSpr( &m_sprGage, siRealMPStartX , siRealMPStartY, CHARSTATUS_MP_NUM );
		for ( i = 2; i < siMpWidth - 2 ; i+=2 )
		{
			GP.PutSpr( &m_sprGage, siRealMPStartX + i, siRealMPStartY, CHARSTATUS_MP_NUM + 1 );
		}
		GP.PutSpr( &m_sprGage, siRealMPStartX + i, siRealMPStartY, CHARSTATUS_MP_NUM + 2 );
	}
	else if ( siMpWidth > 0 )
	{
		GP.PutSpr( &m_sprGage, siRealMPStartX , siRealMPStartY, CHARSTATUS_MP_NUM + 2 );
	}
	//-----------------------------------------------------------------------------
	//	MP ǥ�� [����]
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	//	EXP ǥ�� [����]
	//-----------------------------------------------------------------------------
	SI64	siCurExp	= pclChar->pclCI->clIP.GetCurExp();// SI32->SI64 ����ġ �����÷ο춧���� ����
	SI64	siPreExp	= pclChar->clPB.GetPrevExp();// SI32->SI64 ����ġ �����÷ο춧���� ����
	SI64	siNextExp	= pclChar->clPB.GetNextExp();// SI32->SI64 ����ġ �����÷ο춧���� ����

	REAL32	f32ExpRate	= 1.0f;


	if ( siNextExp == siPreExp )
	{
		f32ExpRate = 1.0f;
	}
	else
	{
		f32ExpRate = ( siCurExp - siPreExp ) / ( ( siNextExp - siPreExp ) * 1.0f );
	}

	if ( f32ExpRate > 1.0f )
	{
		f32ExpRate = 1.0f;
	}
	else if ( f32ExpRate < 0.0f )
	{
		f32ExpRate = 0.0f;
	}

	SI32 siExpWidth = (SI32)(CHARSTATUS_BAR_WIDTH * f32ExpRate);

	if ( siExpWidth > 2 )
	{
		GP.PutSpr( &m_sprGage, siRealEXPStartX , siRealEXPStartY, CHARSTATUS_EXP_NUM );
		for ( i = 2; i < siExpWidth - 2 ; i+=2 )
		{
			GP.PutSpr( &m_sprGage, siRealEXPStartX + i, siRealEXPStartY, CHARSTATUS_EXP_NUM + 1 );
		}
		GP.PutSpr( &m_sprGage, siRealEXPStartX + i, siRealEXPStartY, CHARSTATUS_EXP_NUM + 2 );
	}
	else if ( siExpWidth > 0 )
	{
		GP.PutSpr( &m_sprGage, siRealEXPStartX , siRealEXPStartY, CHARSTATUS_EXP_NUM + 2 );
	}
	//-----------------------------------------------------------------------------
	//	EXP ǥ�� [����]
	//-----------------------------------------------------------------------------


}

void cltNPersonStatus::SetNewAbility( cltParametaBox* pclPB )
{
	TCHAR buffer[64];

	StringCchPrintf(buffer, sizeof(buffer), "%d-%d",	pclPB->GetTotalPHysicalMinAttackDmg(),
														pclPB->GetTotalPHysicalMaxAttackDmg());
	m_pEditbox_physical_attack->SetText(buffer, RGB(128,0,0));			

	StringCchPrintf(buffer, sizeof(buffer), "%d",		pclPB->GetPHysicalDefensive());
	m_pEditbox_pysical_defense->SetText(buffer, RGB(128,0,0));			

	StringCchPrintf(buffer, sizeof(buffer), "%d-%d",    pclPB->GetTotalMagicalMinAttackDmg(), 
														pclPB->GetTotalMagicalMaxAttackDmg());
	m_pEditbox_magic_attack->SetText(buffer,	RGB(128,0,0));			
	
	StringCchPrintf(buffer, sizeof(buffer), "%d",		pclPB->GetMagicalDefensive()); 
	m_pEditbox_magic_defense->SetText(buffer,	RGB(128,0,0));			
	
	StringCchPrintf(buffer, sizeof(buffer), "%d",		pclPB->GetPHysicalHitRate()); 
	m_pEditbox_pysical_hit_rank->SetText(buffer, RGB(128,0,0));			
  
	StringCchPrintf(buffer, sizeof(buffer), "%d",		pclPB->GetPHysicalDodgeRateRank()); 
	m_pEditbox_pysical_dodge_rank->SetText(buffer, RGB(128,0,0));			
		
	StringCchPrintf(buffer, sizeof(buffer), "%d",		pclPB->GetMagicalHitRate()); 
	m_pEditbox_magic_hit_rank->SetText(buffer,	RGB(128,0,0));			
	
	StringCchPrintf(buffer, sizeof(buffer), "%d",		pclPB->GetMagicalDodgeRateRank()); 
	m_pEditbox_magic_dodge_rank->SetText(buffer, RGB(128,0,0));			
}
//#endif
void cltNPersonStatus::SetStatusExplain( TCHAR* _pExplain, SI32 _siSize )
{
	enum { EXPLAIN_BUFFER_NUM = 2048, BUFFER_NUM = 256 };
	TCHAR szbuffer[BUFFER_NUM]	= "";
	SI32  StringLenth			=  0;
	SI32  RemainSize			=  0;

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		return ;
	}
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];
	
	// ���� �̸�.
	cltClient*   pclclient = (cltClient*)pclClient;
	TCHAR buf[128] = TEXT("");
	if ( pclClient->siServiceArea ==  ConstServiceArea_English )
	{
		TCHAR* country = pclClient->pclCountryManager->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		if( pclClient->pclEventTimeManager->InEventTime("AprilFoolEvent", &pclclient->sTime) )
		{
			StringCchPrintf( buf, sizeof(buf), GetTxtFromMgr(9873) );
		}
		else
		{
			StringCchPrintf( buf, sizeof(buf), country );
		}
	}
	else if ( pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		TCHAR* country = pclClient->pclCountryManagerJapan->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		if( pclClient->pclEventTimeManager->InEventTime("AprilFoolEvent", &pclclient->sTime) )
		{
			StringCchPrintf( buf, sizeof(buf), GetTxtFromMgr(9873) );
		}
		else
		{
			StringCchPrintf( buf, sizeof(buf), country );
		}
	}
	else if ( pclClient->siServiceArea ==  ConstServiceArea_NHNChina )
	{
		TCHAR* country = pclClient->pclCountryManager->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		if( pclClient->pclEventTimeManager->InEventTime("AprilFoolEvent", &pclclient->sTime) )
		{
			StringCchPrintf( buf, sizeof(buf), GetTxtFromMgr(9873) );
		}
		else
		{
			StringCchPrintf( buf, sizeof(buf), country );
		}

	}
	else if ( pclClient->siServiceArea ==  ConstServiceArea_EUROPE ) 
	{
		TCHAR* country = pclClient->pclCountryManager->GetCountryFromUnique( pclCM->CR[id]->pclCI->clBI.siCountryID );
		if( pclClient->pclEventTimeManager->InEventTime("AprilFoolEvent", &pclclient->sTime) )
		{
			StringCchPrintf( buf, sizeof(buf), GetTxtFromMgr(9873) );
		}
		else
		{
			StringCchPrintf( buf, sizeof(buf), country );
		}
	}

	StringLenth = strlen(_pExplain);
	RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth);
	StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("%s %s \r\n"), GetTxtFromMgr(6288), buf);

	//-- ����� ----------------------------------------------------------------------------------------
	StringCchPrintf(szbuffer, sizeof(szbuffer), TEXT("%d/%d (%d/%d)"), pclchar->pclCI->clIP.siFameLevel, MAX_FAME_LEVEL, 
					pclchar->pclCI->clIP.siFameExp, 
					GetRequiredFameExpForLevel(pclchar->pclCI->clIP.siFameLevel + 1));
 
	StringLenth = strlen(_pExplain);
	RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth);
	StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("%s %s \r\n"), GetTxtFromMgr(4367), szbuffer);
 
	//----------------------------------------------------------------------------------------------------


	// ĳ���� �ź�
	cltSimpleRank* pclrank	= &pclCM->CR[id]->pclCI->clCharRank;
	UI08			grank	= pclCM->CR[id]->pclCI->clBI.uiGRank; 
	//if(GetRankName(pclrank, szbuffer, BUFFER_NUM, grank) == TRUE)
	 
	if(true == GetMisterRankName(grank, szbuffer, BUFFER_NUM))
	{
		StringLenth = strlen(_pExplain);
		RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth);
		StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("%s     %s \r\n"), GetTxtFromMgr(8253), szbuffer);
	}

	if(true == GetVillageRankName(pclrank, szbuffer, BUFFER_NUM))
	{
		StringLenth = strlen(_pExplain);
		RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth);
		StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("          %s \r\n"), szbuffer);
	}

	if( pclCM->CR[id]->pclCI->clBI.clGuildRank.siType == GUILDRANKTYPE_MASTER )
	{
		StringLenth = strlen(_pExplain);
		RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth); 
		StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("          %s %s\r\n"), pclCM->CR[id]->pclCI->clBI.clGuildRank.szGuildName, GetTxtFromMgr(5267));
	}  
	if( pclCM->CR[id]->pclCI->clBI.clGuildRank.siType == GUILDRANKTYPE_SECONDMASTER )
	{
		StringLenth = strlen(_pExplain);
		RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth); 
		StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("          %s %s\r\n"), pclCM->CR[id]->pclCI->clBI.clGuildRank.szGuildName, GetTxtFromMgr(6541));
	}  

	
	
	// �ǰ� 	
	TCHAR*	pHealthStatue		= NULL;
	TCHAR*	AbilityStatusText	= NULL;
	SI32	healthpoint			= pclClient->pclCM->CR[1]->pclCI->clHealthInfo.uiHealthPoint;
	
	bool Color = false;

		 if(-95 >  healthpoint)	{ pHealthStatue = GetTxtFromMgr(8258); AbilityStatusText = GetTxtFromMgr(8263);  Color = true;}
	else if(100 >  healthpoint)	{ pHealthStatue = GetTxtFromMgr(8259); AbilityStatusText = GetTxtFromMgr(8263);  Color = true;}
	else if(100 == healthpoint)	{ pHealthStatue = GetTxtFromMgr(8260); AbilityStatusText = GetTxtFromMgr(8264);  }
	else if(105 <  healthpoint)	{ pHealthStatue = GetTxtFromMgr(8262); AbilityStatusText = GetTxtFromMgr(10154); }
	else if(100 <  healthpoint) { pHealthStatue = GetTxtFromMgr(8261); AbilityStatusText = GetTxtFromMgr(10154); }
	

	SI32 AddAbility = healthpoint - 100;
		
	if(100 == healthpoint)
	{
		StringLenth = strlen(_pExplain);
		RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth);
				
		StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("%s     %s (%s) \r\n \r\n"), GetTxtFromMgr(4365), 
																							   pHealthStatue, 
																							   AbilityStatusText);
	}
	else
	{
		StringLenth = strlen(_pExplain);
		RemainSize  = sizeof(_pExplain[0]) * (EXPLAIN_BUFFER_NUM - StringLenth);
		
		if(true == Color)
		{
			StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("%s          %s (%d%% %s) \r\n \r\n"), GetTxtFromMgr(4365), 
																												 pHealthStatue, 
																												 AddAbility, 
																												 AbilityStatusText);
		}
		else
		{
			StringCchPrintf(&_pExplain[StringLenth], RemainSize, TEXT("%s     %s (%d%% %s) \r\n \r\n"), GetTxtFromMgr(4365), 
																										pHealthStatue, 
																										AddAbility, 
																										AbilityStatusText);
		}
		
	}
}         

void cltNPersonStatus::SetBaseStatusToolTip(void)
{
	TCHAR szBuffer[256] = "";
	m_pStaticEditbox_strength->SetText(GetTxtFromMgr(4369));	
	m_pStaticEditbox_strength->SetUseToolTip(GetTxtFromMgr(8269));

	m_pStaticEditbox_hand->SetText(GetTxtFromMgr(4373));		
	m_pStaticEditbox_hand->SetUseToolTip(GetTxtFromMgr(8270));

	m_pStaticEditbox_dex->SetText(GetTxtFromMgr(4370));			
	m_pStaticEditbox_dex->SetUseToolTip(GetTxtFromMgr(8271));

	m_pStaticEditbox_magic->SetText(GetTxtFromMgr(4371));		
	m_pStaticEditbox_magic->SetUseToolTip(GetTxtFromMgr(8272));

	m_pStaticEditbox_Wisdom->SetText(GetTxtFromMgr(8000));	 	 
	m_pStaticEditbox_Wisdom->SetUseToolTip(GetTxtFromMgr(8273));

	m_pStaticEditbox_life2->SetText(GetTxtFromMgr(4368));		
	m_pStaticEditbox_life2->SetUseToolTip(GetTxtFromMgr(8274));

	m_pStaticEditbox_luk->SetText(GetTxtFromMgr(5773));			
	m_pStaticEditbox_luk->SetUseToolTip(GetTxtFromMgr(8275));
}
