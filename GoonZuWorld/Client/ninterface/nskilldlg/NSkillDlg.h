#ifndef _NSKILLDLG_H_
#define _NSKILLDLG_H_

#include "../../InterfaceMgr/DialogController.h"

#include "../../../Common/Item/ItemCommon/ItemUnit.h"
#include "../../../Common/Skill/Skill.h"

class CButton;
class CComboBox;
class CStatic;
class CTree;
class CEdit;

class CNSkillDlg : public CDialogController
{
private: 
	enum SKILLDLG_SKILLTAB
	{
		SKILLTAB_USEWEAPON = 0,			//	������� Tab
		SKILLTAB_MAKEWEAPON,			//	�������ۼ� Tab
		SKILLTAB_ARMOR,					//	������ Tab
		SKILLTAB_MAKEHARVEST,			//	�������ۼ� Tab
		SKILLTAB_HARVEST,				//	������ Tab
		SKILLTAB_MAKECLOTH,				//	��ܼ��� Tab
		SKILLTAB_MAKEACCESSARY,			//	�Ǽ��縮���ۼ� Tab
		SKILLTAB_ETC,					//	��Ÿ��� Tab
		SKILLTAB_END,					
	};

public:
	CNSkillDlg();
	~CNSkillDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNSkill( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNSkill( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Action();

	void SkillTabChange( SI16 TabIndex );

	void SetSkillExplainText( SI16 CurBaseSkillLevel, SI16 MaxBaseSkillLevel, SI16 ExpSkillLevel, SI16 MaxExpSkillLevel, SI32 CurExp, SI32 NextExp );

	void TreeViewInsert( SI32 siType, SI32 siParentRef, SI32 siSkillUnique=-1, SI16 siDeeps=1, bool bWeaponType=false );
	void TreeViewSubItemInsert( void );

	SI16 IsChanged();
	void GetSkillLevel();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:
	CTree		*m_pTree;
	CButton		*m_pTabButton[SKILLTAB_END];
	CButton		*m_pSkillMinusButton;
	CButton		*m_pOKButton;
	CButton		*m_pWeaponButton;
	CStatic		*m_pStatic[ 3 ];

	CStatic		*m_pSkillLevel;
	CStatic		*m_pLeftSkill;

	CEdit		*m_pSkillExplain;
	CEdit		*m_pSkillStatus;

	SI16		m_siCurrentSkillUnique;
	SI16		m_siCurrentSkillTypeUnique;
	SI16		m_siCurrentTabIndex;

	SI32		m_siSkillLevel[ MAX_SKILL_NUMBER ];
	CButton		*m_pSkillClearButton;
};

#endif
