#ifndef _MINE_H
#define _MINE_H

#include <Directives.h>

#include "..\..\Common\CommonHeader.h"
#include "..\StructureClass\StructureClass.h"
#include "..\..\Server\Time\MyTime.h"

#include "..\..\Common\Item\ItemCommon\ItemUnit.h"
#include "../../commonlogic/house/house.h"

#define MAX_MINE_TAB_NUMBER								5
#define MAX_MINEUNIT_NUMBER								50		// �� ������ ������ ����
#define MAX_APPLY_PER_MINE								50		// ���� ���� ��û���� ��. (�� ������. ) 
#define MAX_RENT_PERIOD_YEAR							2		// �ִ� �Ӵ� ���� ���.

#define LEVELLIMIT_USE_MINE								30		// ���� ����� �����ϰ� �ϴ� �ּ� ����.

#define MIN_MINE_RENT_FEE								10000	// ���� �Ӵ�� ��������. 	
#define MAX_MINE_RENT_FEE								200000	// ���� �Ӵ�� �ְ� ����. 

class cltTaxPaymentListDlg;

//--------------------------------------
// ���� ����Ʈ 
//--------------------------------------
class cltMineUnit {
public:
	cltSimplePerson clPerson;									// ������. 
	cltRentContract	clContract;									// ü��Ǿ� �ִ� �Ӵ����� ����. 

	cltMineUnit() { Init(); }
	~cltMineUnit() { }

	void Set(const cltMineUnit* punit)
	{
		if( punit == NULL )return ;

		clPerson.Set(&punit->clPerson);
		clContract.Set(&punit->clContract);
	}

	void Init()
	{
		clPerson.Init();
		clContract.Init();
	}

};

//--------------------------------------
// �� �������� �����ϴ� ���� ��ü 
//--------------------------------------
class cltMine : public cltStructureBasic{
public:
	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltMineUnit, MAX_MINEUNIT_NUMBER>		clUnit;
	NSafeTArray<cltRentApplyer, MAX_APPLY_PER_MINE>		clApplyer;
#else
	cltMineUnit		clUnit[ MAX_MINEUNIT_NUMBER ];
	cltRentApplyer	clApplyer[ MAX_APPLY_PER_MINE ];
#endif

	cltMine(SI32 sivillageunique);
	~cltMine();


	// ������ ��������� �����Ѵ�. 
	BOOL SetRentContract(const cltRentContract* pclcontract )
	{
		clStrInfo.clMineStrInfo.clRentContract.Set( pclcontract );
		return TRUE;
	}

	// ���� ������ �����Ѵ� 
	void SetMineUnit( SI32 index, cltMineUnit* pclunit )
	{
		clUnit[ index ].Set(pclunit);
	}

	// ���� ������ ���´� 
	cltMineUnit* GetMineUnit( SI32 index )
	{
		return &clUnit[ index ];
	}

	// ���� ��û�ڸ� �����Ѵ� 
	void SetRentApplyer( SI32 index, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract )
	{
		clApplyer[ index ].Set( pclapplyer, pclcontract );
	}

	// ���� ��û�ڸ� ���´� 
	cltRentApplyer* GetRentApplyer(SI32 index)
	{
		return &clApplyer[ index ];
	}

	// ��� ���� ��û�ڸ� �����Ѵ�.
	void InitRentApplyer()
	{
		for( SI32 i = 0; i < MAX_APPLY_PER_MINE; i++ )
		{
			clApplyer[i].Init();
		}
	}

	// ��� ���������� �ʱ�ȭ�Ѵ�.
	void InitMineUnits()
	{
		for( int i = 0; i < MAX_MINEUNIT_NUMBER; ++i ) {
			clUnit[ i ].Init();
		}
	}

	//PersonID�� ������ ������� ������ ���Ѵ�. 
	cltRentApplyer* GetMineApplyerFromPersonID(SI32 personid);

	// ���� ����������� Ȯ���Ѵ�. 
	BOOL IsSameContract(const cltRentContract* pclcontract);

	// ���� ��û�Ѵ�. 
	BOOL AddApplyer(const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract );

	// ���� ��û�ڸ� �����Ѵ�. 
	BOOL DeleteApplyer(SI32 personid);

	// �������� ���θ� Ȯ���Ѵ�. 
	BOOL IsEmpty(SI32 index);

	// �������� ���꿡 ����Ѵ�.
	BOOL SetRent(SI32 index, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract);

	// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
	bool IsMineHost(SI32 personid, SI32 Mineunitslot);

	// �� ������ �Ӵ�Ḧ ¡���Ѵ�.
	void GetRentFee();

};



//--------------------------------------
// ���� ������. 
//--------------------------------------
class cltMineManager : public cltStructureMngBasic{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltMineUnit, MAX_MINEUNIT_NUMBER>	clClientUnit;
	NSafeTArray<cltRentApplyer, MAX_APPLY_PER_MINE>	clClientApplyer;
#else
	cltMineUnit		clClientUnit[ MAX_MINEUNIT_NUMBER ];
	cltRentApplyer	clClientApplyer[ MAX_APPLY_PER_MINE ];
#endif

	BOOL	UpdateRentContractShowSwitch;				// ��� ������ ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. 
	bool	bUpdateMineUnitListShowChiefSwitch;			// ����Ʈ�� ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. (�����.) 
	bool	bUpdateMineUnitListShowSwitch;				// ��������Ʈ�� ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. 
	BOOL	UpdateMineApplyerListShowSwitch;			// ���� ����� ����Ʈ�� ȭ�鿡 ������ �� �ֵ��� �Ѵ�. 
	BOOL	UpdateMineVarySwitch;						// ���� ������ ������Ʈ �ǵ��� �Ѵ�. 


	SI32 CurrentSelectedMineUnitSlot;
	SI32 CurrentSelectedApplyerSlot;
	SI32 siSelectedMineUnitNumber;						// ���õ� ���������ǹ�ȣ. 

	HIMAGELIST	hImageList;


	cltMineManager( cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltMineManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	void Action( cltTime* pcltime, clock_t CurrentClock );

	// ������ �ż��Ѵ�.
	SI32 CreateMine(SI32 siunique);


	//��� ������ �����ش�. 
	BOOL ShowRentContractInUser(HWND hDlg);

	// ���긮��Ʈ�� �����.
	BOOL MakeMineUnitList(HWND hDlg);

	// ���긮��Ʈ�� �����ش�. 
	BOOL ShowMineUnitList(HWND hDlg);



	// ���Ӽ����� ���������� ����Ʈ�� ��û�Ѵ�. 
	void RequestMineUnitList();
	// ���Ӽ����� ���������� �� ���� ����Ʈ�� ��û�Ѵ�. 
	void RequestMineUnitListDetail();	
	// ���Ӽ����� ��������� ����Ʈ�� ��û�Ѵ�. 
	void RequestMineRentApplyerList();

	// ��� ������ �����ش�. 
	BOOL ShowRentContract(HWND hDlg);
	// ���� ����Ʈ ������ �����ش�. 
	BOOL ShowMineUnitListInChief(HWND hDlg);
	// ���� ���� ������� ����Ʈ�� �����ش�. 
	BOOL ShowMineApplyerListInChief(HWND hDlg);
	// ���õ� ���� ����Ʈ�� ������ �����ش�. 
	BOOL ShowSelectedMineUnitExplain(HWND hDlg, SI32 index);

	// Ư�� ����ڰ� ������ ������ ������ �ִ��� ���θ� �˷��ش� 
	BOOL IsMiner( SI32 villageunique, SI32 personid );


};

#endif