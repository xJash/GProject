//---------------------------------
// 2004/2/18 ���°�
//---------------------------------

#ifndef _HUNT_H
#define _HUNT_H

#include <Directives.h>

#include <Stdio.h>
#include "..\StructureClass\StructureClass.h"
#include "..\..\Common\Item\ItemCommon\cltitem.h"

#define	MAX_HUNT_TAB_NUMBER			4

class cltTaxPaymentListDlg;

//-----------------------------------------------
// �������� ������ 
//-----------------------------------------------
class cltHunt : public cltStructureBasic{
public:
	DWORD dwLastGiveExpClock;
	DWORD dwLastCheckClock;	
	SI32  siLeftMonNum;
	SI32  siLeftUserNum;

	clock_t m_PreClock;

	cltHunt(SI32 sivillageunique);
	~cltHunt();
	
	// ����ڸ� �� �Ѵ´�. 
	void GoOutUser();

	// ���͸� ��ġ�Ѵ�. 
	bool SetMonster();

	// �����忡 ���� ���� ������ Ȯ���Ѵ�.
	void CheckLeftMonNum(SI16* pdata);
	void AddLeftMon(SI32 kind, SI16* pdata);

	
	void Action();

};

//-----------------------------------------------
// ������  ������. 
//-----------------------------------------------
class cltHuntManager : public cltStructureMngBasic{
public:

	SI32 siHuntAddRate;			// �Ϲ� �������� �񱳸� ���� �������� ��庥Ƽ�� Ȯ��. 

	cltHuntManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltHuntManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	// �������� �ż��Ѵ�.
	BOOL CreateHunt(SI32 siunique);
	

	// �������� ���͸� ��� �����ϰ� �ٽ� �����. 
	bool SetNewMonster(SI32 villageunique);

	void Action();

	bool IsMyInventoryChanged();
	void LoadMyInventory();

	bool IsHuntStorageInventoryChanged();
	void LoadHuntStorageInventory();

	void LoadLineUpInfoList();	
	
	// ������ â���� ��� �Ҹ��Ų��. 
	void WasteStgDoll(SI32 villageunique);

	// ������ �̿� �������� ������ �����Ѵ�. 
	void Reward(SI32 VillageUnique, SI16 rewardid, GMONEY money);
	
	// ������ User ���̾�α׿��� ���� ��ġ ������ �о�´�.
	void LoadHuntUserDlgLineUpInfo( HWND hDlg );

	bool IsHuntLineUpMonsterReady( SI32 VillageUnique );
		
	void RecoverDollItem( SI32 VillageUnique, SI16 *pItemDataList );// �����忡�� ���� �����ÿ� ���� ���͸� �� ���������� �ٽ� ��ȯ����

public:
	cltItem			*m_pclMyItem;				// �� �κ��丮 üũ
	cltHuntStg		*m_pclHuntStg;

	SI16			m_siInventorySelectedIndex;
	SI16			m_siHuntStorageSelectedIndex;

	BOOL			bUpdateLineUpInfo;

	HWND			m_hHuntUserDlg;

	HWND			m_hHuntChiefDlg;
	HWND			m_hUserInventory;
	HWND			m_hHuntStorage;

	HIMAGELIST		m_hImageList;

	HWND			m_hMonsterComboList;
	HWND			m_hMonsterLevelEdit;
	HWND			m_hMonsterNumEdit;

	HWND			m_hHuntLineUpInfoList;


	TCHAR			m_strListSelectedMonsterName[ 64 ];

	// ������ ����
	SI32			m_siHuntMapIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_HUNT_MAP_NUMBER>		m_siHuntMapUnique;
#else
	SI32			m_siHuntMapUnique[ MAX_HUNT_MAP_NUMBER ];
#endif
	SI32			m_siHuntMapNumber;

};
#endif
