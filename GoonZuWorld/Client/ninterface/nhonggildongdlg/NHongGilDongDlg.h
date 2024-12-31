#ifndef _NHONGGILDONGDLG_H_
#define _NHONGGILDONGDLG_H_

#include "../../InterfaceMgr/DialogController.h"

#include "../../../Common/Item/ItemCommon/ItemUnit.h"
#include "../../../Common/Skill/Skill.h"


struct stHongGilDongMsgData
{
	SI32 siSkillUnique;
	SI32 siSkillLevel;
};

struct stHongGilDongData
{
	SI32	SkillUnique;
	SI32	SkillLevel;
	GMONEY	CostMoney;
	SI32	Result;
	SI32	Type;
};

enum HONGGILDONG_SETDATATYPE
{
	HONGGILDONG_SETDATATYPE_GETCOSTINFO = 0,	//	��ų ���ұ� ������ ������
	HONGGILDONG_SETDATATYPE_SUCCESSSKILLUP,		//	��ų�� ���������� �ø�
	HONGGILDONG_SETDATATYPE_NOTENOUGHTMONEY,	//	���� ������ ��ų�� �ø� �� ����
};


class CNHongGilDongDlg : public CDialogController
{
public:
	CNHongGilDongDlg();
	~CNHongGilDongDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNSkill( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNSkill( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetBasicInfo( void );	// ���۽� �⺻������ ���õǾ���� ������

	void Action();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void SkillTabChange( SI16 siControllerID );
	void SetAllTabButtonFontStatus( SI16 siControllerID );

	void SetSkillExplainText( void );

	void TreeViewInsert( SI32 siWeaponType, SI32 siParentRef, SI16 siDeeps=1 );
	void UpdataTreeViewItem( SI32 siChangeItemIndex );

	SI16 IsChanged();
	void GetSkillLevel();
	
	void SetData(void *pBuffer);

	SI16 GetWeaponSkillTypeFromControllerID( SI16 siControllerID );
	
	void OnButtonSkillPlus( void );
	void OnTreeSelection( void );
	void OnComboBoxSelection( SI16 siComboBoxID );

	void ShowRegMsgBox( SI32 siUpgradeSkillLevel );
	void ShowHiddenSkill( void );

	void GetHiddenWeaponSkillFromWeaponSkillType( IN SI16 siWeaponSkillType, OUT SI16* psiHiddenGrade1, OUT SI16* psiHiddenGrade2 );
	// ������� ���� ���罺ų �߿� ������ �ִٸ� �� ��ų ����ũ�� �����Ѵ�.
	SI16 IsLearnedHiddenWeaponSkill( IN SI16 *psiHiddenSkillList );

	// ������� ���� ���罺ų�� �޺� �ڽ��� �ִ´�
	void AddHiddenSkillToComboBoxItem( IN SI16 siComboBoxControllerID, IN SI16 siWeaponSkillType, IN SI16 *psiHiddenSkillList );

	// ���� Ʈ�� ����� ���� Ŭ�� üũ
	BOOL IsRapidlyClicked(SI32 siSelectedIndex);
private:
	void SendPacketGetWeaponSkillCost( void );

private:
	InterfaceFactory	m_InterfaceFactory;

	SI16				m_siCurrentSkillUnique;
	SI16				m_siCurrentSkillTypeUnique;

	SI16				m_siCurrentTabControllerID;

	SI32				m_siSkillLevel[ MAX_SKILL_NUMBER ];

	GMONEY				m_siCostMoney;

	SI32				m_siSelectedTreeIndex;		// ���� �Ǿ��� Ʈ�� �ε���

	SI32				m_siTreeClickTime;		// Ʈ�� ���� �ð�(��ӵ� ���� Ŭ���� ���� �ϱ� ����) 

	SI32				m_siRequestCostTime;		// ��� ��û �ð�( ǥ�õǴ� �ݾ��� 0�� ��츦 �����ϱ� ����)

	bool				m_bSelectHiddenWeaponSkill; // ����(4,5�ܰ�) ��ų ���� ����
};

#endif
