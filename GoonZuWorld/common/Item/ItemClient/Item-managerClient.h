//---------------------------------
// 2003/8/7 ���°�
//---------------------------------

#ifndef _ITEMMANAGERCLIENT_H
#define _ITEMMANAGERCLIENT_H

#define MAX_ITEM_IMAGE_NUM		2000		// ������ �̹����� �ִ� ����. 

#include "..\ItemCommon\cltItem.h"

//---------------------------------------------
// MAKE ITEM ������ ���������� ����ü //JAYCEE
//---------------------------------------------
class cltMakeItem{
public:
	TCHAR szName[MAX_ITEM_NAME_LENGTH];
	TCHAR szItemNum[20];

	cltMakeItem()
	{
		memset(szName,	  0, sizeof(szName));
		memset(szItemNum, 0, sizeof(szItemNum));
	}	
};


class cltMaterialExplain
{
public:
	SI32	siUnique;
	TCHAR	szName[MAX_ITEM_NAME_LENGTH];		// ����� �̸�  
	TCHAR	szCount[20];						// ����� �ʿ� ����. 

	cltMaterialExplain()
	{
		siUnique = 0;
		memset(szName, 0, sizeof(szName));
		memset(szCount, 0, sizeof(szCount));
	}
};

class cltCharManager;


class cltItemManagerClient : public cltItemManagerCommon{
public :

	// Ŭ���̾�Ʈ������ �ʿ��� �κ�. 
	SI32 CharUnique;
	TCHAR BitmapFileName[MAX_ITEM_IMAGE_NUM][64]; 

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_ITEM_IMAGE_NUM>		m_ItemImageBigUnique;
#else
	SI16  m_ItemImageBigUnique[MAX_ITEM_IMAGE_NUM];	//[����] �������� ū �̹����� ����ũ ����. => 2008-9-23
#endif

	cltItemManagerClient(HWND hwnd, SI32 gamemode);
	~cltItemManagerClient();

	
	void SetItemImageBigList(void);																		//[����] �ƾ��� ū �̹��� ����.		 => 2008-9-23
	bool GetItemImageBigFileName( SI16 _ItemUnique, TCHAR** _FileName, SI32* _ImageIndex);				//[����] �ƾ��� ū �̹��� �̸� ���. => 2008-9-23

	// �������� ��Ʈ�� �̹��� ������ �����Ѵ�. (Ŭ���̾�Ʈ ����) 
	void SetBitmapImage();

	// �������� ������ ������ ������ �� �������� �����͸� ���Ѵ�.
	cltItem* GetItemPointerFromPosInfo(SI32 id, SI32 siDragFrom);

	SI32 GetBitmapIndexFromBitmapName(TCHAR* bitmapname);

	TCHAR* GetBitMapImageFileNamePointer(SI32 index){return BitmapFileName[index];}

	HBITMAP MakeDDBFromDIB(HDC hdc, SI32 imageindex);
	HBITMAP MakeDDBFromDIB(HDC hdc, TCHAR* path);
	
	SI32 GetBitmapIndexFromFileName(const TCHAR* filename);

	// ������ ������ �����ش�. 
	BOOL SetItemTypeInCombo(HWND hDlg, SI32 dlgitem, bool bshowall);

	// ���� ���� ���� ������ ������ �����ش�. (�������� ���ؼ�)
	BOOL SetItemTypeInComboPersonalShop(HWND hDlg, SI32 dlgitem, bool bshowall);

	// itemtypeunique�� �ش��ϴ� ������ ����Ʈ�� �����ش�. 
	BOOL ShowItemListInCombo(HWND hDlg, SI32 dlgitem, SI32 itemtypeunique, bool btradeinterface);

	//------------------------------------------------
	// ȿ����. 
	//------------------------------------------------
	//  ������ ���� ȿ������ �����Ѵ�. 
	void PushEffect(SI32 effect);

	// ȿ������ �����Ѵ�. 
	void PlaySound(SI32 itemunique, SI32 type);

	// �������� �̸��� ������
	bool GetMadePersonName(SI32 ID, TCHAR* PersonName, SI32 namesize);
	bool GetMadePersonNameNew(SI32 ID, cltPersonNameInfo* _pclPersonInfo, SI32 namesize);

	
	//---------------------------------------------------
	// Explain
	//---------------------------------------------------
	// �����ۿ� ���� ������ ���´�. 
	// numswitch : ������ ǥ���ϴ��� ����. 
	BOOL GetExplain(cltItem* pclitem, TCHAR* ptext, bool numswitch = true, bool basicswitch = false , bool bcolorwitch = false , SI32 siKind = 0,bool bweightswitch= true);

	// �������� ���� ������ ���´�. (unique�� �ٰŷ�.) 
	BOOL cltItemManagerClient::GetExplain(SI32 itemunique, TCHAR* ptext);

	// �������� ���� ������ ���� ������ ���´�. 
	BOOL GetProductionExplain(SI32 siunique, cltPSkillInfo* pclskillinfo, cltPItemInfo* pclcharitem, TCHAR* ptext, SI16 txtSize);
	
	// �������� ���� ������ ���� ��ǰ ������ ���´�.
	BOOL GetProductionItemExplain(SI32 siunique, cltPSkillInfo* pclskillinfo, cltPItemInfo* pclcharitem, cltMaterialExplain* pMaterial, SI32 *totalcount);
	
	// �������� �̿��� ���� ���� ��ǰ ������ ���´�.
	BOOL GetProductionMakeItemExplain(SI32 siunique, cltMakeItem* pMakeItem, SI32 *totalcount);
	
	//��æƮ�� ���ڿ� �ش��ϴ� �Ӽ��̸��� �ҷ��´�.
	TCHAR* GetEnchantTypeName(TCHAR* szEnchantName, SI32 siEnchantType);

	COLORREF GetItemNameColor(cltItem * pclItem);


	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	void GetCrystalAbilityTypeName(TCHAR* szCrystalAbilityName, SI16 siCrystalAbilityType ,SI16 cAbliltyTypeNum,TCHAR* szCrystalReturnString);
	bool GetExplainCrystalClient(SI32 itemunique, TCHAR* ptext);

	void GetCrystalAbilityTypeCondition(SI16 siCrystalAbilityType ,SI16 conditionLevel ,TCHAR* szCrystalReturnString);

protected:
	//�ڱ��� - 20090615 - �ƹ�Ÿ ����ü ���� ���ڿ�( ���� ���ڿ� ��ü ���� ������, ���� ���ڿ� ũ��, ������ Ÿ��, ������ ���� ��)
	BOOL	GetExplainEnhanceAvatarItem(TCHAR* pBuffer,SI32 siBufferSize, SI32 siItemType, cltItem* pclitem);
	//�ڱ��� - 20090615 - �ƹ�Ÿ ����ü ���� ��ȭ ���� ���ڿ�(����ü�� �ִ� ���� �� �� �ִ� ��, ����ü �ɷ� Ÿ��, ������ �ɷ�ġ ��ġ, ���� ���� ����, ���� ���� ���� ũ��)
	BOOL	GetAvatarCrystalAbilityTypeName(SI16 siMaxCrystalAbility, SI16 siCrystalAbilityType ,SI16 siAbliltyTypeNum,TCHAR* pszCrystalReturnString,SI32 siCrystalReturnStringSize);

	void	GetDurabilityExplain( UI16 curdur, UI16 maxdur, NTCHARString64& kDurExplain, bool bcolorwitch );

	//SI32 GetEnchantGrade(SI32 siEnchantDamage);
};

#endif
