
#include "NHongGilDongDlg.h"

#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/Tree.h"
#include "../../InterfaceMgr/Interface/ImageStatic.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../../../Common/Char/CharManager/CharManager.h"
#include "../../../Common/Skill/Skill-Manager.h"
#include "../../../Common/Skill/Skill.h"

#include "../../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../../Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../../../CommonLogic/MsgType-Person.h"

#include "../../Music/music.h"

#include "Msg/MsgType-Quest.h"

#include "../../Client.h"
extern cltCommonLogic* pclClient;

CNHongGilDongDlg::CNHongGilDongDlg() : CDialogController()
{
	m_siCurrentSkillUnique		= 0;
	m_siCurrentSkillTypeUnique	= 0;

	m_siCurrentTabControllerID	= 0;

	ZeroMemory( m_siSkillLevel, sizeof(m_siSkillLevel) );

	m_siCostMoney				= 0;

	m_siTreeClickTime			= 0;

	m_siSelectedTreeIndex		= 0;

	m_siRequestCostTime			= 0;
}

CNHongGilDongDlg::~CNHongGilDongDlg()
{
	SetTimerOnOff( false );
}

void CNHongGilDongDlg::Create()
{
	// �̹� ���̾�α׸� ������ٸ� �����
	if ( IsCreate() )
	{
		DeleteDialog();
		return;
	}

	CInterfaceFile file;
	file.LoadFile(TEXT("NInterface/Data/NHongGilDong/DLG_NHongGilDong.ddf"));
	file.CreatePopupDialog( this, NHONGGILDONG_DLG, TEXT("dialog_NHongGilDong"), StaticCallBackDialogNSkill );

	// Ʈ�� ������ ����
	m_InterfaceFactory.CreateUserInterface( TREE, NHONGGILDONG_DIALOG_TREE, this );
	m_InterfaceFactory.GetTree(NHONGGILDONG_DIALOG_TREE)->Create( NHONGGILDONG_DIALOG_TREE, TEXT("NInterface/Common/Common_24x24_00_109.Spr"), 9, true, 9, 8, 168, 352, 120, 352, 120 );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC, NHONGGILDONG_DIALOG_PORTRAIT,			this),	NHONGGILDONG_DIALOG_PORTRAIT,			TEXT("imagestatic_HongGilDong") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_TAB_SWORD,	this),	NHONGGILDONG_DIALOG_BUTTON_TAB_SWORD,	TEXT("button_Sword") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_TAB_SPEAR,	this),	NHONGGILDONG_DIALOG_BUTTON_TAB_SPEAR,	TEXT("button_Spear") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_TAB_AXE,		this),	NHONGGILDONG_DIALOG_BUTTON_TAB_AXE,		TEXT("button_Axe") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_TAB_STAFF,	this),	NHONGGILDONG_DIALOG_BUTTON_TAB_STAFF,	TEXT("button_Staff") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_TAB_BOW,		this),	NHONGGILDONG_DIALOG_BUTTON_TAB_BOW,		TEXT("button_Bow") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_TAB_GUN,		this),	NHONGGILDONG_DIALOG_BUTTON_TAB_GUN,		TEXT("button_Gun") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_SKILLPLUS,	this),	NHONGGILDONG_DIALOG_BUTTON_SKILLPLUS,	TEXT("button_SkillPlus") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		NHONGGILDONG_DIALOG_BUTTON_OK,			this),	NHONGGILDONG_DIALOG_BUTTON_OK,			TEXT("button_Ok") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC,		NHONGGILDONG_DIALOG_STATIC_1,			this),	NHONGGILDONG_DIALOG_STATIC_1,			TEXT("statictext_Static1") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC,		NHONGGILDONG_DIALOG_STATIC_2,			this),	NHONGGILDONG_DIALOG_STATIC_2,			TEXT("statictext_Static2") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC,		NHONGGILDONG_DIALOG_STATIC_SKILLLEVEL,	this),	NHONGGILDONG_DIALOG_STATIC_SKILLLEVEL,	TEXT("statictext_SkillLevel") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC,		NHONGGILDONG_DIALOG_STATIC_LEFTSKILL,	this),	NHONGGILDONG_DIALOG_STATIC_LEFTSKILL,	TEXT("statictext_LeftSkill") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT,		NHONGGILDONG_DIALOG_EDIT_SKILLSTATUS,	this),	NHONGGILDONG_DIALOG_EDIT_SKILLSTATUS,	TEXT("editbox_SkillStatus") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT,		NHONGGILDONG_DIALOG_EDIT_EXPLAIN,		this),	NHONGGILDONG_DIALOG_EDIT_EXPLAIN,		TEXT("editbox_HongGilDong") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(COMBOBOX,	NHONGGILDONG_DIALOG_COMBO_HIDDEN1,		this),	NHONGGILDONG_DIALOG_COMBO_HIDDEN1,		TEXT("combobox_hidden1") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(COMBOBOX,	NHONGGILDONG_DIALOG_COMBO_HIDDEN2,		this),	NHONGGILDONG_DIALOG_COMBO_HIDDEN2,		TEXT("combobox_hidden2") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(OUTLINE,		NHONGGILDONG_DIALOG_OUTLILE_1,			this),	NHONGGILDONG_DIALOG_OUTLILE_1,			TEXT("outline_NONAME1") );
		
	GetSkillLevel();
	SkillTabChange( NHONGGILDONG_DIALOG_BUTTON_TAB_SWORD );
	SetTimerOnOff( true );
	SetBasicInfo();

}

void CNHongGilDongDlg::SetBasicInfo( void )
{
	TCHAR	szFilePath[256]	= { '\0' };
	SI32	siFont			= 0;
	SI32	siKind			= pclClient->GetUniqueFromHash( TEXT("KIND_ALEX") );

	if ( false == pclClient->pclKindInfoSet->GetNPCImageFileAndFont(siKind, szFilePath, sizeof(szFilePath), &siFont) )
	{
		return;
	}

	CImageStatic* pctrlImage = m_InterfaceFactory.GetImageStatic( NHONGGILDONG_DIALOG_PORTRAIT );
	if ( pctrlImage )
	{
		pctrlImage->SetFileName( szFilePath );
		pctrlImage->SetFontIndex( siFont );
		pctrlImage->Refresh();
	}

	CEdit* pctrlExplain = m_InterfaceFactory.GetEdit( NHONGGILDONG_DIALOG_EDIT_EXPLAIN );
	if ( pctrlExplain )
	{
		TCHAR* pText = GetTxtFromMgr(5224);

		pctrlExplain->SetText( pText );
	}

	SI32 siTextPrintOption = DT_CENTER | DT_VCENTER | DT_SINGLELINE;

	CStatic* pctrlLeftSkill = m_InterfaceFactory.GetStatic( NHONGGILDONG_DIALOG_STATIC_LEFTSKILL );
	if ( pctrlLeftSkill )
	{
		pctrlLeftSkill->SetTextPrintOption( siTextPrintOption );
	}

	CStatic* pctrlSkillLevel = m_InterfaceFactory.GetStatic( NHONGGILDONG_DIALOG_STATIC_SKILLLEVEL );
	if ( pctrlSkillLevel )
	{
		pctrlSkillLevel->SetTextPrintOption( siTextPrintOption );
	}
	
}

void CALLBACK CNHongGilDongDlg::StaticCallBackDialogNSkill( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNHongGilDongDlg *pThis = (CNHongGilDongDlg *)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNSkill( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNHongGilDongDlg::CallBackDialogNSkill( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient *)pclClient;

	switch( nControlID )
	{	
	case NHONGGILDONG_DIALOG_BUTTON_OK:
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;

	case NHONGGILDONG_DIALOG_TREE:
		{
			switch ( nEvent )
			{
			case EVENT_TREE_SELECTION:
				{
					OnTreeSelection();
				}
				break;
			}
		}
		break;

	case NHONGGILDONG_DIALOG_BUTTON_TAB_SWORD:
	case NHONGGILDONG_DIALOG_BUTTON_TAB_SPEAR:
	case NHONGGILDONG_DIALOG_BUTTON_TAB_AXE:
	case NHONGGILDONG_DIALOG_BUTTON_TAB_STAFF:
	case NHONGGILDONG_DIALOG_BUTTON_TAB_BOW:
	case NHONGGILDONG_DIALOG_BUTTON_TAB_GUN:
		{
			// [����] �˼� ��ư Ŭ���� ����Ʈ �˻�
			if ( NHONGGILDONG_DIALOG_BUTTON_TAB_SWORD == nControlID )
			{
				pclClient->pclCM->CR[1]->DoQuestCheckAndAction( QUEST_CLEAR_COND_SWORDSKILLCLICK );
			}

			SkillTabChange( nControlID );
		}
		break;

	case NHONGGILDONG_DIALOG_BUTTON_SKILLPLUS:
		{
			OnButtonSkillPlus();
		}
		break;
	
	case NHONGGILDONG_DIALOG_COMBO_HIDDEN1:
	case NHONGGILDONG_DIALOG_COMBO_HIDDEN2:
		{
			switch ( nEvent )
			{
			case EVENT_COMBOBOX_SELECTION_CHANGED:
				{
					// ���� ��������� �����Ѱ����� ����
					OnComboBoxSelection( nControlID );
				}
				break;
			}
		}
		break;

	}
	return;
}

void CNHongGilDongDlg::Action()
{
	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	SI32 siChangedIndex = IsChanged();
	if ( (0 < siChangedIndex) && (MAX_SKILL_NUMBER > siChangedIndex) )
	{
		// ����� ��ųƮ�� ������ ����
		UpdataTreeViewItem( siChangedIndex );

		// ���罺ų
		ShowHiddenSkill();

		//
		GetSkillLevel();

		//		SendPacketGetWeaponSkillCost();
	}
	
	// ������ ��ų ����
	if ( (0 < m_siCurrentSkillUnique) && (MAX_SKILL_NUMBER > m_siCurrentSkillUnique) )
	{
		//	üũ �ð� ����
		const SI32 ConstIntervalTime = 1000;
		SI32	siTmpTime = GetTickCount();
		// ������ ��ų ����� 0����̰� �ڵ� ��û���� 1���̻� ������� �ڵ����� ����� �޾ƿ´�.
		if(siTmpTime < m_siRequestCostTime)
			m_siRequestCostTime = 0;
		if((m_siCostMoney == 0) &&
		   ((siTmpTime - m_siRequestCostTime) >= ConstIntervalTime) )
		{
			SendPacketGetWeaponSkillCost();
		}

		// ��ų ����
		SetSkillExplainText( );
	}

	// ��ų ���ʽ� ������
	CStatic* pctrlLeftSkill = m_InterfaceFactory.GetStatic( NHONGGILDONG_DIALOG_STATIC_LEFTSKILL );
	if ( NULL == pctrlLeftSkill )
	{
		return;
	}

	pctrlLeftSkill->SetText( SI32ToString(pclchar->pclCI->clIP.GetSkillBonus()) );

	return;
}

void CNHongGilDongDlg::OnButtonSkillPlus( void )
{
	if ( (0 >= m_siCurrentSkillUnique) || (MAX_SKILL_NUMBER <= m_siCurrentSkillUnique) )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	CEdit* pctrlExplain = m_InterfaceFactory.GetEdit( NHONGGILDONG_DIALOG_EDIT_EXPLAIN );
	if ( NULL == pctrlExplain )
	{
		return;
	}

	// ���� ��ų üũ
	SI32 siNowSkillLevel = pclchar->pclCI->clCharSkill.GetSkillLevel( m_siCurrentSkillUnique );
	if ( MAX_WEAPONSKILL_LEVEL <= siNowSkillLevel )
	{
		TCHAR* pText = GetTxtFromMgr(9788);

		pctrlExplain->SetText( pText );
		return;
	}

	// ���� ��ų�������� 1�ܰ� ���׷��̵� ��Ű�Ƿ� +1�� �����ش�
	SI32 siUGSkillLevel = siNowSkillLevel + 1;

	// ���� ��ų ���ʽ� üũ
	SI32 siNeedSkillPoint = 0;
	if ( false == pclClient->pclSkillManager->GetWeaponSkillNeedSkillPoint(m_siCurrentSkillUnique, siUGSkillLevel, &siNeedSkillPoint) )
	{
		// �� �̰� ��� �ұ�?..
		return;
	}

	// �̰��� 1�̻��̾�� �Ѵ�
	if ( 0 >= siNeedSkillPoint )
	{
		return;
	}

	SI32 siSkillBonus = pclchar->pclCI->clIP.GetSkillBonus();
	if ( siSkillBonus < siNeedSkillPoint )
	{
		TCHAR* pText = GetTxtFromMgr(9786);	// �޽����� ���������� �ٸ��� �и��� �� �����Ƿ� ó����ƾ�� �и� �ߴ�

		pctrlExplain->SetText( pText );
		return;
	}

	//-----------------------------------------------------------------------
	// ���� ��ų �϶�
	//-----------------------------------------------------------------------
	if ( true == m_bSelectHiddenWeaponSkill )
	{
		//-----------------------------------------------------------------------
		// �켱 ������ ��� �� �ִ��� ���� �˻�
		if ( false == pclClient->pclSkillManager->IsUpgradeHiddenWeaponSkill(m_siCurrentSkillUnique, siUGSkillLevel, 1) )
		{
			TCHAR* pText = GetTxtFromMgr(9789);

			pctrlExplain->SetText( pText );
			return;
		}

		//-----------------------------------------------------------------------
		// ���罺ų�� Ư�� �������� �Ҹ�ȴ�
		cltItem clGetItem;
		clGetItem.Init();

		if ( false == pclClient->pclSkillManager->GetHiddenWeaponSkillItem(m_siCurrentSkillUnique, siUGSkillLevel, &clGetItem) )
		{
			// �� ��� ó���ұ�
			return;
		}

		bool	bItemCheck		= false;

		SI32	siNeedItemPos	= pclchar->pclCI->clCharItem.FindItemInv(&clGetItem, false);
		if ( 0 < siNeedItemPos )
		{
			if ( clGetItem.GetItemNum() <= pclchar->pclCI->clCharItem.clItem[ siNeedItemPos ].GetItemNum() )
			{
				bItemCheck = true;
			}
		}

		if ( false == bItemCheck )
		{
			NTCHARString256 strText( GetTxtFromMgr(9790) );

			strText.Replace( TEXT("#itemname#"),	clGetItem.GetShortName(pclClient->pclItemManager) );
			strText.Replace( TEXT("#itemnum#"),		SI32ToString(clGetItem.GetItemNum()) );

			pctrlExplain->SetText( strText );
			return;
		}
	}
	//-----------------------------------------------------------------------
	// �׳� ���� ����
	//-----------------------------------------------------------------------
	else
	{
		//-----------------------------------------------------------------------
		// �켱 ������ ��� �� �ִ��� ���� �˻�
		if ( false == pclClient->pclSkillManager->IsUpgradeWeaponSkill(m_siCurrentSkillUnique, siUGSkillLevel, 1) )
		{
			TCHAR* pText = GetTxtFromMgr(9789);

			pctrlExplain->SetText( pText );
			return;
		}

		//-----------------------------------------------------------------------
		// ��ų�� ���� ���� ���� �����Ҷ�

		// ���� ������ ���� ���� ������ ���� �ʾҴ�
		if ( 0 >= m_siCostMoney )
		{
			SendPacketGetWeaponSkillCost();
			return;
		}

		GMONEY gmMyPocketMoney = pclchar->pclCI->clIP.GetMoney();
		if ( (0 < m_siCostMoney) && (m_siCostMoney > gmMyPocketMoney) )
		{
			TCHAR* pText = GetTxtFromMgr(9787);

			pctrlExplain->SetText( pText );
			return;
		}
	}

	// �޽��� ���
	ShowRegMsgBox( siUGSkillLevel );
}

void CNHongGilDongDlg::ShowRegMsgBox( SI32 siUpgradeSkillLevel )
{
	if ( (0 >= siUpgradeSkillLevel) || (MAX_WEAPONSKILL_LEVEL < siUpgradeSkillLevel) )
	{
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	SI32 siNeedSkillPoint = 0;
	if ( false == pclClient->pclSkillManager->GetWeaponSkillNeedSkillPoint(m_siCurrentSkillUnique, siUpgradeSkillLevel, &siNeedSkillPoint) )
	{
		// �� �̰� ��� �ұ�?..
		return;
	}

	// �Ҹ� ��ų����Ʈ�� 0�� ���ü��� ���� 
	if ( 0 >= siNeedSkillPoint )
	{
		return;
	}


	NTCHARString32	strTitle( GetTxtFromMgr(5138) );
	NTCHARString512	strText;

	if ( m_bSelectHiddenWeaponSkill )
	{
		cltItem clNeedItem;
		pclClient->pclSkillManager->GetHiddenWeaponSkillItem( m_siCurrentSkillUnique, siUpgradeSkillLevel, &clNeedItem );

		strText = GetTxtFromMgr(9794);

		strText.Replace( TEXT("#skillnum#"),	SI32ToString(siNeedSkillPoint) );
		strText.Replace( TEXT("#itemnum#"),		SI32ToString(clNeedItem.GetItemNum()) );
		strText.Replace( TEXT("#itemname#"),	clNeedItem.GetShortName(pclClient->pclItemManager) );
	}
	else
	{
		strText	= GetTxtFromMgr(9793);

		strText.Replace( TEXT("#skillnum#"),	SI32ToString(siNeedSkillPoint) );
		strText.Replace( TEXT("#Money#"),		SI64ToString(m_siCostMoney) );
	}

	stMsgBox msgBox;

	msgBox.Set( this, strTitle, strText, MSGBOX_TYPE_YESNO, 0 );

	stHongGilDongMsgData msgData;

	msgData.siSkillUnique	= m_siCurrentSkillUnique;
	msgData.siSkillLevel	= siUpgradeSkillLevel;

	pclclient->SetMsgBox( &msgBox, (BYTE*)&msgData, sizeof(msgData) );

}

void CNHongGilDongDlg::OnTreeSelection( void )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	CTree* pctrlTree = m_InterfaceFactory.GetTree( NHONGGILDONG_DIALOG_TREE );
	if ( NULL == pctrlTree )
	{
		return;
	}

	SI16 siSelectedIndex = pctrlTree->GetSelectedItemIndex();
	if ( 0 > siSelectedIndex )
	{
		return;
	}

	stTreeItem *pTreeItem = pctrlTree->GetTreeItemFromIndex( siSelectedIndex );
	if ( NULL == pTreeItem )
	{
		return;
	}

	if ( (0 >= pTreeItem->siParam) || (MAX_SKILL_NUMBER <= pTreeItem->siParam) )
	{
		return;
	}

	// Ʈ�� �������� �����Ҷ� ��ų ����ũ�� Param�� �־�����Ƿ� �����´�
	m_siCurrentSkillUnique = pTreeItem->siParam;

	// �⺻���� ��������� �����Ѱ����� ����
	m_bSelectHiddenWeaponSkill = false;

	// ������ ��ų�� ���罺ų�̶��
	if ( pclclient->pclSkillManager->pclSkillInfo[m_siCurrentSkillUnique] )
	{
		SI16 siSkillAtb = pclclient->pclSkillManager->pclSkillInfo[m_siCurrentSkillUnique]->siSkillAtb;
		if ( (SKILLATB_HIDDENGRADE1 & siSkillAtb) || (SKILLATB_HIDDENGRADE2 & siSkillAtb) )
		{
			m_bSelectHiddenWeaponSkill = true;
		}
	}

	// ���� ��ų�� ��� ���������� ���� �ʿ䰡 ����
	if ( true == m_bSelectHiddenWeaponSkill )
	{
		return;
	}

	// �켱 �⺻������ ��ų������ �˻��ؼ� ��ų�� ��� �� �ִٸ� ������ ���� ��û�� �Ѵ�
	SI32 siSkillLevel	= pclchar->pclCI->clCharSkill.GetSkillLevel( m_siCurrentSkillUnique );
	SI32 siUGSkillLevel	= siSkillLevel + 1; // ���� ��ų���� �Ѵܰ� ���� ��ų������ ����� ������ +1�� ���ش�
	if ( (0 >= siUGSkillLevel) || (MAX_WEAPONSKILL_LEVEL < siUGSkillLevel) )
	{
		return;
	}


	if(IsRapidlyClicked(siSelectedIndex) == FALSE)
		return;
	
	// Ʈ�� ��� ����
	m_siSelectedTreeIndex = siSelectedIndex;

	// ���� ������ �ʱ�ȭ ���� �ش�
	m_siCostMoney = 0;
	
	// ��밪 ���
	SendPacketGetWeaponSkillCost();
}

void CNHongGilDongDlg::OnComboBoxSelection( SI16 siComboBoxID )
{
	if ( (NHONGGILDONG_DIALOG_COMBO_HIDDEN1 != siComboBoxID) && (NHONGGILDONG_DIALOG_COMBO_HIDDEN2 != siComboBoxID) )
	{
		return;
	}

	CComboBox* pctrlHidden = m_InterfaceFactory.GetComboBox( siComboBoxID );
	if ( NULL == pctrlHidden )
	{
		return;
	}

	stComboBoxItemData* pComboBoxItem = pctrlHidden->GetItemData( pctrlHidden->GetSelectedIndex() );
	if ( NULL == pComboBoxItem )
	{
		return;
	}

	if ( (0 >= pComboBoxItem->siParam) || (MAX_SKILL_NUMBER <= pComboBoxItem->siParam) )
	{
		return;
	}
	
	m_siCurrentSkillUnique = pComboBoxItem->siParam;

	// ���� ��������� �����Ѱ����� ����
	m_bSelectHiddenWeaponSkill = true;
}

void CNHongGilDongDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient *)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	switch(MsgIndex)
	{
	case 0:
		{
			if ( RetValue )
			{
				stHongGilDongMsgData* pclInfo = (stHongGilDongMsgData*)pData;
				if ( NULL == pclInfo )
				{
					return;
				}

				cltGameMsgRequest_Set_WeaponSkill clinfo( pclInfo->siSkillUnique, pclInfo->siSkillLevel );
				cltMsg clMsg( GAMEMSG_REQUEST_SET_WEAPONSKILL, sizeof(clinfo), (BYTE*)&clinfo );
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}
		break;
	default:
		return ;
	}

	return;
}

void CNHongGilDongDlg::SkillTabChange( SI16 siControllerID )
{
	/*
	if ( (0 > siControllerID) || (m_siCurrentTabControllerID == siControllerID) )
	{
		return;
	}
	*/
	// ��ųŸ���� �� �����´ٸ� �ٸ� ��Ʈ�ѷ�ID�� ���� ���̴�
	SI16 siWeaponSkillType = GetWeaponSkillTypeFromControllerID( siControllerID );
	if ( 0 >= siWeaponSkillType )
	{
		return;
	}

	CTree* pctrlTree = m_InterfaceFactory.GetTree( NHONGGILDONG_DIALOG_TREE );
	if ( NULL == pctrlTree )
	{
		return;
	}

	CEdit* pctrlExplain = m_InterfaceFactory.GetEdit( NHONGGILDONG_DIALOG_EDIT_EXPLAIN );
	if ( NULL == pctrlExplain )
	{
		return;
	}

	CEdit* pctrlSkillStatus = m_InterfaceFactory.GetEdit( NHONGGILDONG_DIALOG_EDIT_SKILLSTATUS );
	if ( NULL == pctrlSkillStatus )
	{
		return;
	}

	// ������ ���´�
	m_siCurrentTabControllerID = siControllerID;
	
	// ��ư ��Ʈ ���� ����
	SetAllTabButtonFontStatus( siControllerID );

	// Ʈ�� ���� ����
	pctrlTree->Clear();

	TreeViewInsert( siWeaponSkillType, 0 );

	pctrlTree->Refresh();

	// ���� ��ų ����
	ShowHiddenSkill();

	// ���� �������� �ʱ�ȭ
	m_siCurrentSkillUnique		= 0;
	m_siCurrentSkillTypeUnique	= 0;
	m_siCostMoney				= 0;
	m_bSelectHiddenWeaponSkill	= false;

	// ���� �ؽ�Ʈ�� �ʱ⹮���� �����Ѵ�
	TCHAR* pText = GetTxtFromMgr(5224);
	pctrlExplain->SetText( pText );

	// ���� ��ų���� �ؽ�Ʈ�� �����
	pctrlSkillStatus->SetText( TEXT("") );

	return;
}

void CNHongGilDongDlg::SetAllTabButtonFontStatus( SI16 siControllerID )
{
	// Tab��ư ��Ʈ�ѷ� ID
	SI16 siTabButtonID[] = {
		NHONGGILDONG_DIALOG_BUTTON_TAB_SWORD,
		NHONGGILDONG_DIALOG_BUTTON_TAB_SPEAR,
		NHONGGILDONG_DIALOG_BUTTON_TAB_AXE,	
		NHONGGILDONG_DIALOG_BUTTON_TAB_STAFF,
		NHONGGILDONG_DIALOG_BUTTON_TAB_BOW,	
		NHONGGILDONG_DIALOG_BUTTON_TAB_GUN
	};

	SI32 siTabButtonIDCount = sizeof(siTabButtonID) / sizeof(siTabButtonID[0]);
	if ( 0 >= siTabButtonIDCount )
	{
		return;
	}

	CButton* pctrlTabButton = NULL;

	for ( SI32 siCount=0; siCount<siTabButtonIDCount; ++siCount )
	{
		pctrlTabButton = m_InterfaceFactory.GetButton( siTabButtonID[siCount] );
		if ( NULL == pctrlTabButton )
		{
			continue;
		}

		if ( siControllerID == siTabButtonID[siCount] )
		{
			pctrlTabButton->SetFontColor( CONTROLLER_BUTTONTEXT_COLOR );
			pctrlTabButton->SetFontWeight( FW_BOLD );
		}
		else
		{
			pctrlTabButton->SetFontColor( CONTROLLER_BACK_BUTTONTEXT_COLOR );
			pctrlTabButton->SetFontWeight( FW_NORMAL );
		}
		
		pctrlTabButton->Refresh();
	}

}

void CNHongGilDongDlg::SetSkillExplainText( void )
{
	if ( (0 > m_siCurrentSkillUnique) || (MAX_SKILL_NUMBER <= m_siCurrentSkillUnique) )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	CEdit* pctrlSkillStatus = m_InterfaceFactory.GetEdit( NHONGGILDONG_DIALOG_EDIT_SKILLSTATUS );
	if ( NULL == pctrlSkillStatus )
	{
		return;
	}

	CStatic* pctrlSkillLevel = m_InterfaceFactory.GetStatic( NHONGGILDONG_DIALOG_STATIC_SKILLLEVEL );
	if ( NULL == pctrlSkillLevel )
	{
		return;
	}

	//-----------------------------------------------------------------------------------------------------------------
	// ��ų ������� �ؽ�Ʈ�� �ѷ��ش� 
	//-----------------------------------------------------------------------------------------------------------------
	const	SI32	ConstBufferSize = 512;
	TCHAR	szBuffer[ConstBufferSize]	= TEXT("");
	SI32	siSkillLevel	= pclchar->pclCI->clCharSkill.GetSkillLevel( m_siCurrentSkillUnique );

	SI32	siMaxSkillLevel	= pclClient->pclSkillManager->GetMaxLevel( m_siCurrentSkillUnique );
	SI32	siUGSkillLevel	= pclClient->pclItemManager->GetUpgradeSkillLevel( &pclchar->pclCI->clCharItem.clItem[0], m_siCurrentSkillUnique, 1 );

	// �⺻ ������� �ؽ�Ʈ
	TCHAR*	pText			= GetTxtFromMgr(5202);
	StringCchPrintf( szBuffer, ConstBufferSize, pText, siSkillLevel, siMaxSkillLevel, siUGSkillLevel );

	// ����� ���� �ؽ�Ʈ
	SI32	siNextLevel		= siSkillLevel + 1;	// ���׷��̵� �Ǿ��ϴ� ������ ������ �����;� �ϹǷ� +1�� �Ѵ�
	TCHAR	szExplain[ConstBufferSize]	= TEXT("");
	pclClient->pclSkillManager->GetWeaponSkillExplain( m_siCurrentSkillUnique, siNextLevel, szExplain );

	// ��� ���ļ� �ѷ��ش�
	StringCchCat( szBuffer, ConstBufferSize, szExplain );

	//-----------------------------------------------------------------------------------------------------------------
	// ��� ������� �ؽ�Ʈ�� �ѷ��ش� 
	//-----------------------------------------------------------------------------------------------------------------
	if ( (0 < siNextLevel) && (MAX_WEAPONSKILL_LEVEL >= siNextLevel) )
	{
		TCHAR*	pszTextNeed	= GetTxtFromMgr(30265);
		TCHAR*	pszTextGold = GetTxtFromMgr(611);
		TCHAR   szBufferMoney[ConstBufferSize] ;
		ZeroMemory(szBufferMoney, ConstBufferSize * sizeof(TCHAR));
		g_JYLibFunction.SetNumUnit( m_siCostMoney, szBufferMoney, ConstBufferSize, pszTextGold );
		TCHAR	szCostBuffer[ConstBufferSize];
		ZeroMemory(szCostBuffer, ConstBufferSize * sizeof(TCHAR));
		StringCchPrintf( szCostBuffer, ConstBufferSize, TEXT("\r\n%s : %s "), pszTextNeed, szBufferMoney );

		// ��� ���ļ� �ѷ��ش�
		StringCchCat( szBuffer, ConstBufferSize, szCostBuffer );
	}

	pctrlSkillStatus->SetText( szBuffer );

	//-----------------------------------------------------------------------------------------------------------------
	// �ش� ��ų�� ������ �ѷ��ش�
	//-----------------------------------------------------------------------------------------------------------------
	NTCHARString64 strSkillLevel( TEXT("#nowlevel#/#maxlevel#") );

	strSkillLevel.Replace( TEXT("#nowlevel#"), SI32ToString(siSkillLevel) );
	strSkillLevel.Replace( TEXT("#maxlevel#"), SI32ToString(siMaxSkillLevel) );

	pctrlSkillLevel->SetText( strSkillLevel );

}

//-----------------------------------------------------------------------------------------------------------------------------
// ���� : ����ȣ�� �Լ�, �ش� ���� Ÿ���� ���� ������ �������� Tree�� �ִ´� ����ȣ��� �ڽ��� �����۵��� �־��ش�
// �μ� : SI32 siWeaponType = �߰��ϰ����ϴ� ����� Ÿ��, 
//		  SI32 siParentRef = �θ� ���۷���
// ��ȯ : void
//-----------------------------------------------------------------------------------------------------------------------------
void CNHongGilDongDlg::TreeViewInsert( SI32 siWeaponType, SI32 siParentRef, SI16 siDeeps )
{
	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	CTree* pctrlTree = m_InterfaceFactory.GetTree( NHONGGILDONG_DIALOG_TREE );
	if ( NULL == pctrlTree )
	{
		return;
	}

	stTreeItem		sTreeItem;
	cltSkillInfo*	pclGetSkillInfo = NULL;

	for ( SI32 siIndex = 0; siIndex < MAX_SKILL_NUMBER; ++siIndex )
	{
		pclGetSkillInfo = pclClient->pclSkillManager->pclSkillInfo[siIndex];
		if ( NULL == pclGetSkillInfo )
		{
			continue;
		}

		// ��������� �ƴϸ� �н�
		if ( SKILLTYPE_FIGHT != pclGetSkillInfo->siSkillType )
		{
			continue;
		}

		// ���� ���� Ÿ�԰� �޶� �н�
		if ( siWeaponType != pclGetSkillInfo->siWeaponType )
		{
			continue;
		}

		// �θ� ���۷����� �޶� �н�
		if ( siParentRef != pclGetSkillInfo->siParentRef )
		{
			//continue;
		}

		// ���� ���������� ��������� ��ųƮ���� ��Ÿ����
		if ( (pclGetSkillInfo->siSkillAtb & SKILLATB_HIDDENGRADE1) || (pclGetSkillInfo->siSkillAtb & SKILLATB_HIDDENGRADE2) )
		{
			if ( 0 >= pclchar->pclCI->clCharSkill.GetSkillLevel(siIndex) )
			{
				continue;
			}
		}

		// �� �ܰ迡 ���� �־���ϴ� siDeeps�� �ִ�
		if ( pclGetSkillInfo->siSkillAtb & SKILLATB_HIDDENGRADE1 )
		{
			if ( 4 != siDeeps )
			{
				continue;
			}
		}
		else if ( pclGetSkillInfo->siSkillAtb & SKILLATB_HIDDENGRADE2 )
		{
			if ( 5 != siDeeps )
			{
				continue;
			}
		}
		else
		{
			if ( siParentRef != pclGetSkillInfo->siParentRef )
			{
				continue;
			}
		}

		// ���������� Tree�� �� ������
		sTreeItem.Init();

		sTreeItem.siIndex		=	siIndex;
		sTreeItem.siFileIndex	=	1;
		sTreeItem.siImageIndex	=	pclGetSkillInfo->siBitMapIndex;
		sTreeItem.siParam		=	pclGetSkillInfo->siUnique;
		sTreeItem.siParentIndex =	siParentRef;

		// ����� ��� ������ ���� �´�
		pclClient->pclSkillManager->MakeWeaponSkillTitle( &pclchar->pclCI->clCharSkill, &pclchar->pclCI->clCharItem, pclGetSkillInfo->siUnique );
		StringCchCopy( sTreeItem.strText, MAX_TREE_TEXT_LEN, pclGetSkillInfo->szSkillTitle );

		// ������ Tree�� �־��ְ�
		pctrlTree->InsertItem( &sTreeItem );

		// ����ȣ���� ���� �ڽ� �����۵��� �־��ش�
		TreeViewInsert( siWeaponType, siIndex, siDeeps+1 );
		
	}

	return;
}

//-----------------------------------------------------------------------------------------------------------------------------
// ���� : �̹� ������ Tree Item�� �ϳ��� ����Ǿ� �� �������� ������ �����Ѵ�
// �μ� : SI32 siChangeItemIndex = ����� ��ų�� ����ũ
// ��ȯ : void
//-----------------------------------------------------------------------------------------------------------------------------
void CNHongGilDongDlg::UpdataTreeViewItem( SI32 siChangeItemIndex )
{
	if ( (0 >= siChangeItemIndex) || (MAX_SKILL_NUMBER <= siChangeItemIndex) )
	{
		return;
	}

	CTree* pctrlTree = m_InterfaceFactory.GetTree( NHONGGILDONG_DIALOG_TREE );
	if ( NULL == pctrlTree )
	{
		return;
	}

	stTreeItem* pTreeItem = pctrlTree->GetTreeItemFromIndex( siChangeItemIndex );
	if ( NULL == pTreeItem )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	cltSkillInfo* pclSkillInfo = pclClient->pclSkillManager->pclSkillInfo[siChangeItemIndex];
	if ( NULL == pclSkillInfo )
	{
		return;
	}

	SI32 siGetTotalSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel( pclSkillInfo->siUnique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0], 1 );

	// ��ų ���泻���� Tree Item�� �ٽ� �־��ش�
	pclClient->pclSkillManager->MakeWeaponSkillTitle( &pclchar->pclCI->clCharSkill, &pclchar->pclCI->clCharItem, pclSkillInfo->siUnique );

	StringCchCopy( pTreeItem->strText, MAX_TREE_TEXT_LEN, pclSkillInfo->szSkillTitle );

	pctrlTree->UpdateItem( pTreeItem );

}

//-----------------------------------------------------------------------------------------------------------------------------
// ���� : ĳ������ ��� ��ų�� ������ ������ �ξ��ٰ� Action()�Լ����� ��ų�� ����� ������ �˻��ϱ� ���� ��� ��ų�� ������ ������ �д�
// �μ� : void
// ��ȯ : void
//-----------------------------------------------------------------------------------------------------------------------------
void CNHongGilDongDlg::GetSkillLevel()
{
	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	cltSkillInfo* pclSkillInfo = NULL;

	for( SI32 i = 1; i < MAX_SKILL_NUMBER; ++i )
	{
		pclSkillInfo = pclClient->pclSkillManager->pclSkillInfo[i];
		if ( NULL == pclSkillInfo )
		{
			continue;
		}

		m_siSkillLevel[ i ] = pclchar->pclCI->clCharSkill.GetTotalSkillLevel( pclSkillInfo->siUnique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);
	}

	return;
}

//-----------------------------------------------------------------------------------------------------------------------------
// ���� : GetSkillLevel()���� ������ �ξ��� ������ �������� ��ų ������ ����� ���� �ִ��� �˻��Ѵ�
// �μ� : void
// ��ȯ : ������ ����� ��ų�� Unique�� ��ȯ
//-----------------------------------------------------------------------------------------------------------------------------
SI16 CNHongGilDongDlg::IsChanged()
{
	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return 0;
	}

	cltSkillInfo*	pclSkillInfo	= NULL;
	SI32			siGetSkillLevel	= 0;

	for ( SI32 i = 1; i < MAX_SKILL_NUMBER; ++i )
	{
		pclSkillInfo = pclClient->pclSkillManager->pclSkillInfo[i];
		if ( NULL == pclSkillInfo )
		{
			continue;
		}

		siGetSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel( pclSkillInfo->siUnique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0] );
		if ( m_siSkillLevel[ i ] != siGetSkillLevel )
		{
			return i;
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------
// ���� : ������ ��û�ߴ� ������ �ٷ�� �Լ� ���±ݾ�/��ų���⼺��/��ų��������� ������ �ٷ��
// �μ� : void ��������(stHongGilDongData �� ������)
// ��ȯ : void
//-----------------------------------------------------------------------------------------------------------------------------
void CNHongGilDongDlg::SetData(void *pBuffer)
{
	stHongGilDongData* pclinfo = (stHongGilDongData*)pBuffer;
	if ( NULL == pclinfo )
	{
		return;
	}

	CEdit* pctrlExplain = m_InterfaceFactory.GetEdit( NHONGGILDONG_DIALOG_EDIT_EXPLAIN );
	if ( NULL == pctrlExplain )
	{
		return;
	}

	SI32 siMsgType = pclinfo->Type;

	switch ( siMsgType )
	{
	case HONGGILDONG_SETDATATYPE_GETCOSTINFO:
		{
			/*
			TCHAR buffer[512] = TEXT("") ;
			TCHAR * pText = GetTxtFromMgr(5225);

			StringCchPrintf(buffer, 512, pText,pclinfo->SkillLevel,pclinfo->CostMoney);

			pctrlExplain->SetText(buffer);
			pctrlExplain->Refresh();
			*/
			m_siCostMoney = pclinfo->CostMoney;
		}
		break;

	case HONGGILDONG_SETDATATYPE_SUCCESSSKILLUP:
		{
			if ( pclinfo->Result )
			{
				TCHAR* pText = GetTxtFromMgr(5226);

				pctrlExplain->SetText(pText);
				pctrlExplain->Refresh();

				pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WEAPONSKILL_UP")),0,0);

				SkillTabChange( m_siCurrentTabControllerID );
			}
		}
		break;

	case HONGGILDONG_SETDATATYPE_NOTENOUGHTMONEY:
		{
			TCHAR *pText = GetTxtFromMgr(5521);
			TCHAR buffer[256] ;
			StringCchPrintf(buffer, 256, pText,pclinfo->CostMoney*10000) ;
			pctrlExplain->SetText(buffer);
			pctrlExplain->Refresh() ;
		}
		break;
	}

}

//-----------------------------------------------------------------------------------------------------------------------------
// ���� : ��Ʈ�� ���̵� �ش��ϴ� ����� Ÿ���� �����´�(�� ������ ��ư����)
// �μ� : �ܹ�ư ��Ʈ�ѷ� ID
// ��ȯ : ����� Ÿ��
//-----------------------------------------------------------------------------------------------------------------------------
SI16 CNHongGilDongDlg::GetWeaponSkillTypeFromControllerID( SI16 siControllerID )
{
	SI16 siWeaponSkillType = 0;

	switch ( siControllerID )
	{
		case NHONGGILDONG_DIALOG_BUTTON_TAB_SWORD:	{	siWeaponSkillType = WEAPONSKILLTYPE_SWORD;	}	break;
		case NHONGGILDONG_DIALOG_BUTTON_TAB_SPEAR:	{	siWeaponSkillType =	WEAPONSKILLTYPE_SPEAR;	}	break;
		case NHONGGILDONG_DIALOG_BUTTON_TAB_AXE:	{	siWeaponSkillType =	WEAPONSKILLTYPE_AXE;	}	break;
		case NHONGGILDONG_DIALOG_BUTTON_TAB_STAFF:	{	siWeaponSkillType =	WEAPONSKILLTYPE_STAFF;	}	break;
		case NHONGGILDONG_DIALOG_BUTTON_TAB_BOW:	{	siWeaponSkillType =	WEAPONSKILLTYPE_BOW;	}	break;
		case NHONGGILDONG_DIALOG_BUTTON_TAB_GUN:	{	siWeaponSkillType =	WEAPONSKILLTYPE_GUN;	}	break;
	}

	return siWeaponSkillType;
}

void CNHongGilDongDlg::ShowHiddenSkill( void )
{
	SI16 siNowWeaponSkillType = GetWeaponSkillTypeFromControllerID( m_siCurrentTabControllerID );
	if ( 0 >= siNowWeaponSkillType )
	{
		return;
	}

	SI16 siHiddenGrade1[MAX_WEAPONSKILLTYPE_NUM] = { 0, };
	SI16 siHiddenGrade2[MAX_WEAPONSKILLTYPE_NUM] = { 0, };

	// �켱 ���� ��ų ����� �����´�
	GetHiddenWeaponSkillFromWeaponSkillType( siNowWeaponSkillType, siHiddenGrade1, siHiddenGrade2 );

	// !!��Ͽ� ��Ÿ���� ���� ���� ������ �ִٸ� �װ͸� �������� �Ѵ� �Ʒ� �۾��� �װ��� ���� �͵�!! //

	// �� �ܰ� ���� ��ų ����� ��� ��ų �ε����� �����´�
	SI16 siLearndeHiddenSkill1 = IsLearnedHiddenWeaponSkill( siHiddenGrade1 );
	SI16 siLearndeHiddenSkill2 = IsLearnedHiddenWeaponSkill( siHiddenGrade2 );

	// ���� 1�ܰ�(�������� 4�ܰ�) ��ų�� ������ �ִٸ� ��� ���� ��ų�� ���� ������ ��� ��ų�θ� ä�� �ִ´�
	if ( 0 < siLearndeHiddenSkill1 )
	{
		ZeroMemory( siHiddenGrade1, sizeof(siHiddenGrade1) );

		siHiddenGrade1[0] = siLearndeHiddenSkill1;
	}

	// ���� 2�ܰ�(�������� 5�ܰ�) ��ų�� ������ �ִٸ� ��� ���� ��ų�� ���� ������ ��� ��ų�θ� ä�� �ִ´�
	if ( 0 < siLearndeHiddenSkill2 )
	{
		ZeroMemory( siHiddenGrade2, sizeof(siHiddenGrade2) );

		siHiddenGrade2[0] = siLearndeHiddenSkill2;
	}

	// ����� ��ų���� �޺� �ڽ��� �ִ´�(�� ��Ͽ� �ִ� ��ų���� ��Ͽ� ���� �� �ִ����� �Ʒ� �Լ� �ȿ��� �Ѵ�)
	AddHiddenSkillToComboBoxItem( NHONGGILDONG_DIALOG_COMBO_HIDDEN1, siNowWeaponSkillType, siHiddenGrade1 );
	AddHiddenSkillToComboBoxItem( NHONGGILDONG_DIALOG_COMBO_HIDDEN2, siNowWeaponSkillType, siHiddenGrade2 );

}

void CNHongGilDongDlg::GetHiddenWeaponSkillFromWeaponSkillType( IN SI16 siWeaponSkillType, OUT SI16* psiHiddenGrade1, OUT SI16* psiHiddenGrade2 )
{
	if ( (0 >= siWeaponSkillType) || (MAX_WEAPONSKILLTYPE_NUM < siWeaponSkillType) )
	{
		return;
	}

	if ( (NULL == psiHiddenGrade1) || (NULL == psiHiddenGrade2) )
	{
		return;
	}
	
	SI32			siHidden1Count	= 0;
	SI32			siHidden2Count	= 0;
	cltSkillInfo*	pclSkill		= NULL;

	for ( SI32 siSkillIndex=1; siSkillIndex<MAX_SKILL_NUMBER; ++siSkillIndex )
	{
		pclSkill = pclClient->pclSkillManager->pclSkillInfo[siSkillIndex];
		if ( NULL == pclSkill )
		{
			continue;
		}
		
		// ���� ��� ���� �ƴϸ�
		if ( SKILLTYPE_FIGHT != pclSkill->siSkillType )
		{
			continue;
		}
		
		// �ش� ���� Ÿ���� �ƴϸ�
		if ( siWeaponSkillType != pclSkill->siWeaponType )
		{
			continue;
		}
		
		// ��ų ���� ��޿� ���� ��Ͽ� �߰��Ѵ�
		if ( (SKILLATB_HIDDENGRADE1 & pclSkill->siSkillAtb) && (MAX_WEAPONSKILLTYPE_NUM > siHidden1Count) )
		{
			psiHiddenGrade1[siHidden1Count++] = siSkillIndex;
		}
		else if ( (SKILLATB_HIDDENGRADE2 & pclSkill->siSkillAtb) && (MAX_WEAPONSKILLTYPE_NUM > siHidden2Count) )
		{
			psiHiddenGrade2[siHidden2Count++] = siSkillIndex;
		}
	}
}

SI16 CNHongGilDongDlg::IsLearnedHiddenWeaponSkill( IN SI16 *psiHiddenSkillList )
{
	if ( NULL == psiHiddenSkillList )
	{
		return 0;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return 0;
	}

	SI16 siSkillUnique = 0;

	for ( SI32 siIndex=0; siIndex<MAX_WEAPONSKILLTYPE_NUM; ++siIndex )
	{
		siSkillUnique = psiHiddenSkillList[siIndex];
		if ( 0 >= siSkillUnique )
		{
			continue;
		}
		
		// �ش� ���罺ų������ 1 �̻��̶�� �����̴�
		if ( 0 < pclchar->pclCI->clCharSkill.GetSkillLevel(siSkillUnique) )
		{
			return siSkillUnique;
		}
	}

	return 0;
}

void CNHongGilDongDlg::AddHiddenSkillToComboBoxItem( IN SI16 siComboBoxControllerID, IN SI16 siWeaponSkillType, IN SI16 *psiHiddenSkillList )
{
	if ( (siComboBoxControllerID != NHONGGILDONG_DIALOG_COMBO_HIDDEN1) && (siComboBoxControllerID != NHONGGILDONG_DIALOG_COMBO_HIDDEN2) )
	{
		return;
	}

	if ( NULL == psiHiddenSkillList )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}
	
	CComboBox* pctrlHiddenSkill = m_InterfaceFactory.GetComboBox( siComboBoxControllerID );
	if ( NULL == pctrlHiddenSkill )
	{
		return;
	}

	SI32 siFindSkillUnique = pclClient->pclSkillManager->FindSkillUniqueFromWeaponSkillType( siWeaponSkillType );
	if ( 0 >= siFindSkillUnique )
	{
		return;
	}

	SI16 siCharLevel	= pclchar->pclCI->clIP.GetLevel();
	SI16 siSkillLevel	= pclchar->pclCI->clCharSkill.GetSkillExpLevel( siFindSkillUnique );
	SI16 siSkillUnique	= 0;
	SI16 siParentUnique	= 0;

	cltSkillInfo*		pclSkill		= NULL;
	cltSkillInfo*		pclParentSkill	= NULL;
	cltWeaponSkillInfo*	pclWeaponSkill	= NULL;

	stComboBoxItemData	comboBoxData;

	// �켱 �޺��ڽ��� ��� ����
	pctrlHiddenSkill->Clear();

	for ( SI32 siIndex=0; siIndex<MAX_WEAPONSKILLTYPE_NUM; ++siIndex )
	{
		siSkillUnique = psiHiddenSkillList[siIndex];
		if ( 0 >= siSkillUnique )
		{
			continue;
		}

		pclSkill = pclClient->pclSkillManager->pclSkillInfo[siSkillUnique];
		if ( NULL == pclSkill )
		{
			continue;
		}

		siParentUnique = pclSkill->siParentRef;
		if ( (0 >= siParentUnique) || (MAX_SKILL_NUMBER <= siParentUnique) )
		{
			continue;
		}

		pclParentSkill = pclClient->pclSkillManager->pclSkillInfo[siParentUnique];
		if ( NULL == pclParentSkill )
		{
			continue;
		}

		if ( NULL == pclParentSkill->pclWeaponSkillInfo )
		{
			continue;
		}

		// �ּ� ����(1����, �ε����� 0) ���Ǹ� ������ �߰��Ѵ�
		pclWeaponSkill = pclParentSkill->pclWeaponSkillInfo[0];
		if ( NULL == pclWeaponSkill )
		{
			continue;
		}
		
		// ������ �����Ѵٸ� �޺��ڽ��� �߰��Ѵ�
		if ( (siCharLevel >= pclWeaponSkill->siHiddenLimitLevel) && (siSkillLevel >= pclWeaponSkill->siHiddenLimitSkillLevel) )
		{
			comboBoxData.Init();

			pclClient->pclSkillManager->MakeWeaponSkillTitle( &pclchar->pclCI->clCharSkill, &pclchar->pclCI->clCharItem, siSkillUnique );
			
			// ��ų����ũ�� �ؽ�Ʈ�� ���� �ִ´�
			comboBoxData.Set( siSkillUnique, pclSkill->szSkillTitle );

			pctrlHiddenSkill->AddItem( &comboBoxData );
		}
	}

	// ���罺ų ����� �������� ��Ʈ���� �����ش�
	if ( 0 < pctrlHiddenSkill->GetItemNum() )
	{
		pctrlHiddenSkill->Show( true );
	}
	else
	{
		pctrlHiddenSkill->Show( false );
	}

}

void CNHongGilDongDlg::SendPacketGetWeaponSkillCost( void )
{
	if ( (0 >= m_siCurrentSkillUnique) || (MAX_SKILL_NUMBER <= m_siCurrentSkillUnique) )
	{
		return;
	}

	if ( true == m_bSelectHiddenWeaponSkill )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	cltClient *pclclient = (cltClient *)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	// ��� ��û �ð� 
	m_siRequestCostTime = GetTickCount();

	// �켱 �⺻������ ��ų������ �˻��ؼ� ��ų�� ��� �� �ִٸ� ������ ���� ��û�� �Ѵ�
	SI32 siSkillLevel	= pclchar->pclCI->clCharSkill.GetSkillLevel( m_siCurrentSkillUnique );
	SI32 siUGSkillLevel	= siSkillLevel + 1; // ���� ��ų���� �Ѵܰ� ���� ��ų������ ����� ������ +1�� ���ش�
	if ( (0 >= siUGSkillLevel) || (MAX_WEAPONSKILL_LEVEL < siUGSkillLevel) )
	{
		return;
	}

	cltGameMsgRequest_Get_WeaponSkillCost clinfo( m_siCurrentSkillUnique, siUGSkillLevel );
	cltMsg clMsg( GAMEMSG_REQUEST_GET_WEAPONSKILLCOST, sizeof(clinfo), (BYTE*)&clinfo );
	pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
	
}

// ���� Ʈ�� ����� ���� Ŭ�� üũ
BOOL CNHongGilDongDlg::IsRapidlyClicked(SI32 siSelectedIndex)
{
	if(siSelectedIndex < 0)
		return FALSE;

	// ���� Ŭ�� ������
	SI32 siTmpTime = GetTickCount();
	// 1��
	const SI32 ConstOneSecond = 1000;

	if( m_siTreeClickTime > siTmpTime)
	{
		m_siTreeClickTime = siTmpTime;
	}
	else
	{
		if(((siTmpTime - m_siTreeClickTime) < ConstOneSecond) && (m_siSelectedTreeIndex == siSelectedIndex))
		{
			return FALSE;
		}
		else
		{
			m_siTreeClickTime = siTmpTime;
		}
	}
	
	return TRUE;
}