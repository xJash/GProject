#include "NMarriageLoveLevelDlg.h"

#include "../../Client.h"

#include "../../common/Family/Marriage.h"
#include "../../common/Char/CharManager/CharManager.h"

#include "../../CommonLogic/Marriage/MarriageManager.h"

#include "../nletterdlg/NLetterDlg.h"
#include "../npartydlg/NPartyDlg.h"
#include "../nprivatechatdlg/NPrivateChatDlgMgr.h"
#include "../NHelpButton/NHelpButtonDlg.h"
#include "../NFamilyCookieDlg/NFamilyCookieDlg.h"
#include "../NFamilyInfoDlg/NFamilyInfoDlg.h"
#include "../NDormancyAccount/NDormancyPointDlg.h"

extern cltCommonLogic* pclClient;

CNMarriageLoveLevelDlg::CNMarriageLoveLevelDlg() : CDialogController()
{
	m_siMinimizedSlot	= 0;

	m_pclBackGround		= NULL;
}

CNMarriageLoveLevelDlg::~CNMarriageLoveLevelDlg()
{
	SAFE_DELETE( m_pclBackGround );
}

void CNMarriageLoveLevelDlg::Init()
{

}

void CNMarriageLoveLevelDlg::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	cltClient *pclclient = (cltClient *)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	SI16 siDialogWidth	= 34;
	SI16 siDialogHeight	= 34;

	// ���̾�α� ����
	CDialogController::Create( NMARRIAGELOVELEVEL_DLG, CONTROLLER_KIND_POPUPDIALOG, NULL, StaticCallBackDialogNMarriageLoveLevel, NULL, NULL, 0, false, 0, 0, 0, siDialogWidth, siDialogHeight, false, false, false );

	// ��� �׸�&����
	NEWCIMAGESTATIC( m_pclBackGround );
	m_pclBackGround->Create( 0, TEXT("NInterface/image/IMAGE_34x34_00_001.SPR"), 0, false, 0, 0, 0, siDialogWidth, siDialogHeight, siDialogWidth, siDialogHeight );


	// �ּ�ȭ�� ���̾�α��� ��ġ�� �ٸ� �ּ�ȭ���̾�α��� ��ġ�� ���� �����Ѵ�.
	SI16 LetterMinimizedSlot = 0, PrivateChatMinimizedSlot = 0, PartyMinimizedSlot = 0, HelpButtonMiniMizedSlot = 0, FamilyCookieEffect = 0 ,FamilyMini = 0 , siDormancyMiniMizedSlot = 0;

	if( pclclient->m_pDialog[NLETTER_DLG])
		LetterMinimizedSlot = ((CNLetterDlg*)pclclient->m_pDialog[NLETTER_DLG])->GetMinimizedSlot();

	if( pclclient->m_pNPrivateChatDlgMgr)
		PrivateChatMinimizedSlot = pclclient->m_pNPrivateChatDlgMgr->GetMinimizedSlot();

	if( pclclient->m_pDialog[NPARTY_DLG])
		PartyMinimizedSlot = ((CNPartyDlg*)pclclient->m_pDialog[NPARTY_DLG])->GetMinimizedSlot();

	if(pclClient->IsCountrySwitch(Switch_FreshManHelpDialog))
	{
		if( pclclient->m_pDialog[NHELPBUTTON_DLG])
			HelpButtonMiniMizedSlot = ((CNHelpButtonDlg*)pclclient->m_pDialog[NHELPBUTTON_DLG])->GetMinimizedSlot();
	}
	if ( pclclient->m_pDialog[NFAMILYCOOKIELEVEL_DLG] )
		FamilyCookieEffect = ((CNFamilyCookieDlg*)pclclient->m_pDialog[NFAMILYCOOKIELEVEL_DLG])->GetMinimizedSlot();

	if ( pclclient->m_pDialog[NFAMILYINFO_DLG] )
		FamilyMini = ((CNFamilyInfoDlg*)pclclient->m_pDialog[NFAMILYINFO_DLG])->GetMinimizedSlot();

	if ( pclclient->m_pDialog[NDORMANCYPOINT_DLG] )
		siDormancyMiniMizedSlot = ((CNDormancyPointDlg*)pclclient->m_pDialog[NDORMANCYPOINT_DLG])->GetMinimizedSlot();


	// �� ������ ã�´�.
	for ( SI16 i = 1; i <= MAX_MINIMIZE_SLOT; i++ )
	{
		if( i == LetterMinimizedSlot || i == PrivateChatMinimizedSlot || i==PartyMinimizedSlot || i == HelpButtonMiniMizedSlot || i == FamilyCookieEffect || i == FamilyMini || i == siDormancyMiniMizedSlot)
			continue;

		m_siMinimizedSlot = i;
		break;
	}

	SetDialogPos( pclclient->GetScreenXSize() - 40 - (m_siMinimizedSlot-1) * 45 , 215, 34, 34 );

	SetActionTimer( 1000 );
	SetTimerOnOff( true );
}

void CNMarriageLoveLevelDlg::Action()
{
	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// ��ȥ ���ѻ��¿��� �� â�� �����ٸ� ���̾� �α׸� �����Ѵ�
	if ( FALSE == pclChar->IsMarried() )
	{
		DeleteDialog();
		return;
	}

	// ���� ��λ� ���ٸ�
	if ( MARRIAGE_MATE_CONNECT_MODE_SAMEMAP != pclChar->pclMarriage->GetConnectMode() )
	{
		DeleteDialog();
		return;
	}

	// �߸��� ������ ���
	SI16 siLoveLevel = pclChar->pclMarriage->GetLoveLevel();
	if ( (MARRIAGE_LOVE_LEVEL_NONE >= siLoveLevel) || (MARRIAGE_LOVE_LEVEL_MAX <= siLoveLevel) )
	{
		DeleteDialog();
		return;
	}

	//============================================================
	// ������ ����
	//============================================================
	if ( m_pclBackGround )
	{
		// �ε����� 0�� ������ 1���� ����
		m_pclBackGround->SetFontIndex( (siLoveLevel-1) );
	}

	//============================================================
	// ���� ����
	//============================================================
	NTCHARString512 strToolTip = GetTxtFromMgr( 30037 );

	// �ɷ�ġ ��������
	SI32 siAttackValue	= 0, siAddAttackValue	= 0;
	SI32 siDefenseValue = 0, siAddDefenseValue	= 0;
	SI32 siLifeValue	= 0, siAddLifeValue		= 0;
	SI32 siExpValue		= 0, siAddExpValue		= 0;

	siAttackValue	= pclClient->m_pclMarriageMgr->GetTotalAttackAbilityValue( siLoveLevel );
	siDefenseValue	= pclClient->m_pclMarriageMgr->GetTotalDefenseAbilityValue( siLoveLevel );
	siLifeValue		= pclClient->m_pclMarriageMgr->GetTotalLifeAbilityValue( siLoveLevel );
	siExpValue		= pclClient->m_pclMarriageMgr->GetTotalExpAbilityValue( siLoveLevel );

	// ���� �ð� ��������
	SI32 siNowHourVary	= ((cltClient*)pclClient)->clClientDate.GetHourVary();
	SI32 siRemainHour	= pclChar->pclMarriage->GetRemainHourVary( siNowHourVary ) * 2; // *2�� ���ǽð����� �����ϱ� ���ؼ�
	
	/*
	if ( 48 < siRemainHour )
	{
		siRemainHour = 48;
	}
	*/

	strToolTip.Replace( TEXT("#attack#"),		SI32ToString(siAttackValue) );
	strToolTip.Replace( TEXT("#addattack#"),	SI32ToString(siAddAttackValue) );
	strToolTip.Replace( TEXT("#defense#"),		SI32ToString(siDefenseValue) );
	strToolTip.Replace( TEXT("#adddefense#"),	SI32ToString(siAddDefenseValue) );
	strToolTip.Replace( TEXT("#life#"),			SI32ToString(siLifeValue) );
	strToolTip.Replace( TEXT("#addlife#"),		SI32ToString(siAddLifeValue) );
	strToolTip.Replace( TEXT("#exp#"),			SI32ToString(siExpValue) );
	strToolTip.Replace( TEXT("#addexp#"),		SI32ToString(siAddExpValue) );

	strToolTip.Replace( TEXT("#time#"),			SI32ToString(siRemainHour) );

	if ( m_pclBackGround )
	{
		m_pclBackGround->SetUseToolTip( strToolTip );
	}
}

void CALLBACK CNMarriageLoveLevelDlg::StaticCallBackDialogNMarriageLoveLevel( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNMarriageLoveLevelDlg* pThis = (CNMarriageLoveLevelDlg*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNMarriageLoveLevel( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNMarriageLoveLevelDlg::CallBackDialogNMarriageLoveLevel( UINT nEvent, int nControlID, CControllerObj* pControl )
{
}