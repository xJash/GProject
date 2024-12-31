#pragma once

#include "../common/item/ItemCommon/ItemUnit.h"
#include "../../NGameDataManager/NGameDataManager.h"
#include "../../NLib/NDataLoader.h"

#define MAX_ITEMINFO_NUMBER		30000

class cltItemManagerClient{
private:
	NGameDataManager*	m_pclGameDataManager;
public :

	int m_siItemType[MAX_ITEMINFO_NUMBER];

	// Ŭ���̾�Ʈ������ �ʿ��� �κ�. 
//	SI32 CharUnique;
//
	cltItemManagerClient();
	~cltItemManagerClient();

	VOID InIt(NGameDataManager& gameDataManager);
	
	void SetItemData(int siServiceArea);

	int GetType(int siItemUnique);

	// ���� �������� �߰��Ѵ�. 
	void AddFoodItem(TCHAR* datfilename);
	// ���깰�������� �߰��Ѵ�. 
	void AddSeaFoodItem(TCHAR* datfilename);
	// �� �������� �߰��Ѵ�. 
	void AddHealItem(TCHAR* datfilename);
	// Į �������� �߰��Ѵ�. 
	void AddSwordItem(TCHAR* datfilename);
	// â �������� �߰��Ѵ�. 
	void AddSpearItem(TCHAR* datfilename);
	// ������ �������� �߰��Ѵ�. 
	void AddStaffItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�. 
	void AddAxeItem(TCHAR* datfilename);
	// Ȱ �������� �߰��Ѵ�. 
	void AddBowItem(TCHAR* datfilename);
	// chd �������� �߰��Ѵ�. 
	void AddGunItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�. 
	void AddArmourItem(TCHAR* datfilename);
	// �Ǻ� �������� �߰��Ѵ�. 
	void AddDressItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�. 
	void AddHelmetItem(TCHAR* datfilename);
	// ��� �������� �߰��Ѵ�. 
	void AddBeltItem(TCHAR* datfilename);
	// ����� �������� �߰��Ѵ�. 
	void AddNeckItem(TCHAR* datfilename);
	// �Ź� �������� �߰��Ѵ�. 
	void AddShoesItem(TCHAR* datfilename);
	// å �������� �߰��Ѵ�. 
	void AddBookItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�. 
	void AddAnimalItem(TCHAR* datfilename);
	// ��Ÿ �������� �߰��Ѵ�. 
	void AddEtcItem(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	// �Ϲ� �������� �߰��Ѵ�. 
	void AddItem(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	// ���� �������� �߰��Ѵ�. 
	void AddRingItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�. 
	void AddScrollItem(TCHAR* datfilename);
	// ö��  �������� �߰��Ѵ�. 
	void AddIronItem(TCHAR* datfilename);
	// ����  �������� �߰��Ѵ�. 
	void AddDishItem(TCHAR* datfilename);
	// �  �������� �߰��Ѵ�. 
	void AddFishingRodItem(TCHAR* datfilename);
	// ��ȯ���� �������� �߰��Ѵ�. 
	void AddDollItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�. 
	void AddHatItem(TCHAR* datfilename);
	// ǥ�������� �߰��Ѵ�. 
	void AddTicketItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�.
	void AddBagItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�.
	void AddMantleItem(TCHAR* datfilename);

	// [����] �ƹ�Ÿ ���� �������� �߰��Ѵ�.
	void AddAvatarMantleItem(TCHAR* datfilename);
	// [����] �ƹ�Ÿ �Ǻ� �������� �߰��Ѵ�.
	void AddAvatarDressItem(TCHAR* datfilename);
	// [����] �ƹ�Ÿ ���� �������� �߰��Ѵ�.
	void AddAvatarHatItem(TCHAR* datfilename);
	// [����] �ƹ�Ÿ ����� �������� �߰��Ѵ�.
	void AddAvatarNeckItem(TCHAR* datfilename);
	// [����] �ƹ�Ÿ ���� �������� �߰��Ѵ�.
	void AddAvatarRingItem(TCHAR* datfilename);

	// ���� �������� �߰��Ѵ�. 
	void AddPaperItem(TCHAR* datfilename);
	// ���� �������� �߰��Ѵ�. 
	void AddCannonItem(TCHAR* datfilename);
	// ��� �������� �߰��Ѵ�. 
	void AddTorpedoItem(TCHAR* datfilename);
	// ����ü �������� �߰��Ѵ�. 
	void AddCrystalItem(TCHAR* datfilename);
	//�ռ� ��� �������� �߰��Ѵ�
	void AddCompositionManterial(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//�̺�Ʈ �������� �߰��Ѵ�
	void AddEventitem(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//���� �������� �߰��Ѵ�
	void AddBox(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//�����̾� �������� �߰��Ѵ�
	void AddPremium(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//���� �������� �߰��Ѵ�
	void AddMineralItem(TCHAR* datfilename);

	void AddQuestItem(TCHAR* datfilename);


//
//	//---------------------------------------------------
//	// Explain
//	//---------------------------------------------------
//	// �����ۿ� ���� ������ ���´�. 
//	// numswitch : ������ ǥ���ϴ��� ����. 
	BOOL GetExplain(cltItem* pclitem, TCHAR* ptext);

	TCHAR* GetEnchantTypeName( SI32 siEnchantType);
	VOID GetCrystalAbilityTypeName(SI16 siCrystalAbilityType ,SI16 cAbliltyTypeNum,TCHAR* szCrystalReturnString);

	TCHAR* GetSkillNameByUnique( SI32 siSkillUnique);
//
//	// �������� ���� ������ ���´�. (unique�� �ٰŷ�.) 
//	BOOL GetExplain(SI32 itemunique, TCHAR* ptext);
//
//	// �������� ���� ������ ���� ������ ���´�. 
//	BOOL GetProductionExplain(SI32 siunique, cltPSkillInfo* pclskillinfo, cltPItemInfo* pclcharitem, TCHAR* ptext, SI16 txtSize);
//
//	// �������� ���� ������ ���� ��ǰ ������ ���´�.
//	//BOOL GetProductionItemExplain(SI32 siunique, cltPSkillInfo* pclskillinfo, cltPItemInfo* pclcharitem, cltMaterialExplain* pMaterial, SI32 *totalcount);
//
//	// �������� �̿��� ���� ���� ��ǰ ������ ���´�.
//	//BOOL GetProductionMakeItemExplain(SI32 siunique, cltMakeItem* pMakeItem, SI32 *totalcount);
//
//	//��æƮ�� ���ڿ� �ش��ϴ� �Ӽ��̸��� �ҷ��´�.
//	TCHAR* GetEnchantTypeName(TCHAR* szEnchantName, SI32 siEnchantType);
//
//	COLORREF GetItemNameColor(cltItem * pclItem);
//
//
//	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
//	void GetCrystalAbilityTypeName(TCHAR* szCrystalAbilityName, SI16 siCrystalAbilityType ,SI16 cAbliltyTypeNum,TCHAR* szCrystalReturnString);
//	bool GetExplainCrystalClient(SI32 itemunique, TCHAR* ptext);
//
//	void GetCrystalAbilityTypeCondition(SI16 siCrystalAbilityType ,SI16 conditionLevel ,TCHAR* szCrystalReturnString);
//
//protected:
//	//�ڱ��� - 20090615 - �ƹ�Ÿ ����ü ���� ���ڿ�( ���� ���ڿ� ��ü ���� ������, ���� ���ڿ� ũ��, ������ Ÿ��, ������ ���� ��)
//	BOOL	GetExplainEnhanceAvatarItem(TCHAR* pBuffer,SI32 siBufferSize, SI32 siItemType, cltItem* pclitem);
//	//�ڱ��� - 20090615 - �ƹ�Ÿ ����ü ���� ��ȭ ���� ���ڿ�(����ü�� �ִ� ���� �� �� �ִ� ��, ����ü �ɷ� Ÿ��, ������ �ɷ�ġ ��ġ, ���� ���� ����, ���� ���� ���� ũ��)
//	BOOL	GetAvatarCrystalAbilityTypeName(SI16 siMaxCrystalAbility, SI16 siCrystalAbilityType ,SI16 siAbliltyTypeNum,TCHAR* pszCrystalReturnString,SI32 siCrystalReturnStringSize);
//
//	void	GetDurabilityExplain( UI16 curdur, UI16 maxdur, NTCHARString64& kDurExplain, bool bcolorwitch );

	//SI32 GetEnchantGrade(SI32 siEnchantDamage);
};