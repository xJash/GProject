//---------------------------------
// 2003/8/1 ���°�
//---------------------------------

#ifndef _SKILLMANAGER_H
#define _SKILLMANAGER_H

#include <Directives.h>

#include "Skill.h"

class cltSkillManager
{
public:
	HWND m_hDlg;
#ifdef _SAFE_MEMORY
	NSafeTArray<HWND, MAX_SKILL_TYPE_NUMBER>	TabDlg;
#else
	HWND TabDlg[MAX_SKILL_TYPE_NUMBER];
#endif

	BOOL DlgRectInitSwitch;
	RECT DlgRect;

	SI32 CharUnique;					// ����� �Ǵ� ĳ����. 

	BOOL BonusButtonEnableSwitch;			// ���ʽ� �÷��ִ� ��ư�� Ȱ��ȭ �Ǿ� �ִ��� Ȯ���ϴ� ����. 

	SI32 CurrentSkillTypeUnique;		// ���� ���õ� ��ų Ÿ��. 
	SI32 CurrentSkillUnique;			// ���� ���õ�  ��ų ����ũ

#ifdef _SAFE_MEMORY
	NSafeTArray<cltSkillTypeInfo*, MAX_SKILL_TYPE_NUMBER>	pclSkillTypeInfo;
	NSafeTArray<cltSkillInfo*, MAX_SKILL_NUMBER>			pclSkillInfo;
#else
	cltSkillTypeInfo* pclSkillTypeInfo[MAX_SKILL_TYPE_NUMBER];
	cltSkillInfo* pclSkillInfo[MAX_SKILL_NUMBER];
#endif

	HIMAGELIST hImageList;

	cltWeaponSkillMasterManager m_clMasterManager;	// ������� ����

	cltSkillManager();
	~cltSkillManager();

	// ��ų Ÿ���� �߰��Ѵ�. 
	SI32 AddSkillType(SI32 skilltype, TCHAR* pskillcode, TCHAR* name,BOOL bshow = TRUE );
	SI32 FindTypeRefFromUnique(SI32 unique);
	// �ڵ带 �ٰŷ� ��ųŸ���� ���Ѵ�. 
	SI32 FindSkillTypeFromCode(TCHAR* pcode);


	// ��ų�� �߰��Ѵ�. 
	SI32 AddSkill(SI32 unique, SI32 skilltype, SI32 skillatb, TCHAR *code, TCHAR* name, SI32 maxskilllevel,
				  SI32 parentref, SI32 bitmapindex, SI32 explainunique,SI32 weapontype = 0 );

	bool LoadSkillLimitFile(TCHAR* szFileName);

	SI32 FindUniqueFromSkillCode( TCHAR *strSkillCode );
	SI32 FindUniqueFromSkillName( TCHAR *strSkillName );

	SI32 FindSkillTypeFromUnique( SI32 siUnique );
	SI32 FindSkillUniqueFromWeaponSkillType( SI32 siWeaponSkillType );

	BOOL TreeViewInsert(SI32 skilltypeunique);
	// Ʈ��������  �߰��Ѵ�.
	BOOL TreeViewInsert(HWND hwnd, SI32 type, SI32 parentref, HTREEITEM node);

	void MakeSkillTitle(cltPSkillInfo* pclskillmanager, cltPItemInfo* pclcharitem, SI32 skillunique,bool bWeapon = false);
	void MakeWeaponSkillTitle(cltPSkillInfo* pclskillmanager, cltPItemInfo* pclcharitem, SI32 skillunique);

	// ��ų�� ���ʷ� �����Ѵ�. 
	BOOL DevelopSkill(SI32 skillunique);

	// skillunique�� �ٰŷ� ��ų�� �̸��� ���´�.
	bool GetSkillName(SI32 skillunique, TCHAR* buffer);
	bool GetWeaponSkillNeedSkillPoint( IN SI32 siSkillUnique, IN SI32 siSkillLevel, OUT SI32* psiNeedSkillPoint );

	//--------------------------------
	// Skill-Set.cpp
	//--------------------------------
	void SetSkillType();
	void SetSkill();

	void	GetSkillLevel();


	SI32	IsChanged();

	bool	FindTreeData( HWND hDlg, HTREEITEM, TV_ITEM *, SI32 Param );
	bool	FindChildTreeData( HWND hDlg, HTREEITEM, TV_ITEM *, SI32 Param );

	// skillunique�� �ٰŷ� �ִ� ��ų ������ ���Ѵ�. 
	SI32 GetMaxLevel(SI32 skillunique);
	// skillunique�� �ٰŷ� �ִ� ���轺ų ������ ���Ѵ�. 
	SI32 GetMaxExpLevel(SI32 skillunique);

	SI32 GetTotalMaxLevel(SI32 skillunique)
	{
		return GetMaxLevel(skillunique) + GetMaxExpLevel(skillunique);
	}

	// �θ� ����� ���۷����� ���Ѵ�. 
	SI32 GetParentSkillRef(SI32 skillunique);

	// ��ų�� ������ ���õ� ��ų�ΰ�?
	bool IsManufactureSkill(SI32 skillunique);

	void SetSkillExplainText( SI16 CurBaseSkillLevel, SI16 MaxBaseSkillLevel, SI16 ExpSkillLevel, SI16 MaxExpSkillLevel, SI32 CurExp, SI32 NextExp );

	// �������� �ø� �� �ֳ� ����
	bool IsUpgradeWeaponSkill(SI32 unique,SI32 level,SI32 id);

	// ���� ���� ������ �ø� �� �ֳ� ����
	bool IsUpgradeHiddenWeaponSkill( SI32 siSkillUnique, SI32 siLevel, SI32 siCharID );

	// �ش� ���� ���������� �ʿ��� �������� ���� �´�
	bool GetHiddenWeaponSkillItem( IN SI32 siSkillUnique, IN SI32 siLevel, OUT cltItem* pclGetItem );

	// siNextLevel�� �������� ��� ������ �ִ��� �����´�
	void GetWeaponSkillExplain( IN SI32 siSkillUnique, IN SI32 siSkillLevel, OUT TCHAR * pszExplain );
	SI32 GetWeaponSkillRate( IN SI32 siSkillUnique, IN SI32 siSkillLevel );

private:	
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_SKILL_NUMBER>		m_si32SkillLevel;
#else
	SI32		m_si32SkillLevel[ MAX_SKILL_NUMBER ];
#endif

	HTREEITEM	m_hNow;
	HBITMAP		m_hDecreaseSkillHitBitmap;
};


#endif