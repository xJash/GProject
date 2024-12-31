#ifndef _LAND_H
#define _LAND_H

#include <Directives.h>

#include "..\..\Common\CommonHeader.h"
#include "..\StructureClass\StructureClass.h"
#include "..\..\Server\Time\MyTime.h"

#include "..\..\Common\Item\ItemCommon\ItemUnit.h"
#include "../../commonlogic/house/house.h"

#define MAX_LAND_TAB_NUMBER								5
#define MAX_LANDUNIT_NUMBER								50		// �� ������ ������ ����
#define MAX_APPLY_PER_LAND								50		// ���� ���� ��û���� ��. (�� ������. ) 
#define MAX_RENT_PERIOD_YEAR							2		// �ִ� �Ӵ� ���� ���.

#define LEVELLIMIT_USE_LAND								30		// ���� ����� �����ϰ� �ϴ� �ּ� ����.

#define MIN_LAND_RENT_FEE								5000	// ���� �Ӵ�� ��������. 	
#define MAX_LAND_RENT_FEE								200000	// ���� �Ӵ�� �ְ� ����. 

class cltTaxPaymentListDlg;

//--------------------------------------
// ���� ����Ʈ 
//--------------------------------------
class cltLandUnit {
public:
	cltSimplePerson clPerson;										// ������. 
	cltRentContract	clContract;										// ü��Ǿ� �ִ� �Ӵ����� ����. 

	cltLandUnit() { Init(); }
	~cltLandUnit() { }

	void Set(const cltLandUnit* punit)
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
class cltLand : public cltStructureBasic{
public:
	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltLandUnit, MAX_LANDUNIT_NUMBER>	clUnit;
	NSafeTArray<cltRentApplyer, MAX_APPLY_PER_LAND>	clApplyer;
#else
	cltLandUnit		clUnit[ MAX_LANDUNIT_NUMBER ];
	cltRentApplyer	clApplyer[ MAX_APPLY_PER_LAND ];
#endif

	cltLand(SI32 sivillageunique);
	~cltLand();


	// ������ ��������� �����Ѵ�. 
	BOOL SetRentContract(const cltRentContract* pclcontract )
	{
		clStrInfo.clLandStrInfo.clRentContract.Set( pclcontract );
		return TRUE;
	}

	// ���� ������ �����Ѵ� 
	void SetLandUnit( SI32 index, cltLandUnit* pclunit )
	{
		clUnit[ index ].Set(pclunit);
	}

	// ���� ������ ���´� 
	cltLandUnit* GetLandUnit( SI32 index )
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
		for( SI32 i = 0; i < MAX_APPLY_PER_LAND; i++ )
		{
			clApplyer[i].Init();
		}

	}

	// ��� ���� ������ �ʱ�ȭ�Ѵ�.
	void InitLandUnits()
	{
		for( SI32 i = 0; i < MAX_LANDUNIT_NUMBER; i++ )
		{
			clUnit[i].Init();
		}

	}

	//PersonID�� ������ ������� ������ ���Ѵ�. 
	cltRentApplyer* GetLandApplyerFromPersonID(SI32 personid);

	// ���� ����������� Ȯ���Ѵ�. 
	BOOL IsSameContract(const cltRentContract* pclcontract);

	// ���� ��û�Ѵ�. 
	BOOL AddApplyer(const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract );

	// ���� ��û�ڸ� �����Ѵ�. 
	BOOL DeleteApplyer(SI32 personid);

	// �������� ���θ� Ȯ���Ѵ�. 
	BOOL IsEmpty(SI32 index);

	// �������� ���忡 ����Ѵ�.
	BOOL SetRent(SI32 index, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract);

	// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
	bool IsLandHost(SI32 personid, SI32 landunitslot);

	// �� ������ �Ӵ�Ḧ ¡���Ѵ�.
	void GetRentFee();

};



//--------------------------------------
// ���� ������. 
//--------------------------------------
class cltLandManager : public cltStructureMngBasic{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltLandUnit, MAX_LANDUNIT_NUMBER>		clClientUnit;
	NSafeTArray<cltRentApplyer, MAX_APPLY_PER_LAND>		clClientApplyer;
#else
	cltLandUnit		clClientUnit[ MAX_LANDUNIT_NUMBER ];
	cltRentApplyer	clClientApplyer[ MAX_APPLY_PER_LAND ];
#endif

	BOOL	UpdateRentContractShowSwitch;				// ��� ������ ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. 
	bool	bUpdateLandUnitListShowChiefSwitch;			// ����Ʈ�� ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. (�����.) 
	bool	bUpdateLandUnitListShowSwitch;				// ��������Ʈ�� ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. 
	BOOL	UpdateLandApplyerListShowSwitch;			// ���� ����� ����Ʈ�� ȭ�鿡 ������ �� �ֵ��� �Ѵ�. 
	BOOL	UpdateLandVarySwitch;						// ���� ������ ������Ʈ �ǵ��� �Ѵ�. 


	SI32 CurrentSelectedLandUnitSlot;
	SI32 CurrentSelectedApplyerSlot;
	SI32 siSelectedLandUnitNumber;						// ���õ� ���������ǹ�ȣ. 

	HIMAGELIST	hImageList;


	cltLandManager( cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltLandManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	void Action( cltTime* pcltime, clock_t CurrentClock );

	// ������ �ż��Ѵ�.
	SI32 CreateLand(SI32 siunique);


	//��� ������ �����ش�. 
	BOOL ShowRentContractInUser(HWND hDlg);

	// ���帮��Ʈ�� �����.
	BOOL MakeLandUnitList(HWND hDlg);

	// ���帮��Ʈ�� �����ش�. 
	BOOL ShowLandUnitList(HWND hDlg);



	// ���Ӽ����� ���������� ����Ʈ�� ��û�Ѵ�. 
	void RequestLandUnitList();
	// ���Ӽ����� ���������� �� ���� ����Ʈ�� ��û�Ѵ�. 
	void RequestLandUnitListDetail();	
	// ���Ӽ����� ��������� ����Ʈ�� ��û�Ѵ�. 
	void RequestLandRentApplyerList();

	// ��� ������ �����ش�. 
	BOOL ShowRentContract(HWND hDlg);
	// ���� ����Ʈ ������ �����ش�. 
	BOOL ShowLandUnitListInChief(HWND hDlg);
	// ���� ���� ������� ����Ʈ�� �����ش�. 
	BOOL ShowLandApplyerListInChief(HWND hDlg);
	// ���õ� ���� ����Ʈ�� ������ �����ش�. 
	BOOL ShowSelectedLandUnitExplain(HWND hDlg, SI32 index);

	// Ư�� ����ڰ� ������ ������ ������ �ִ��� ���θ� �˷��ش� 
	BOOL IsFarmer( SI32 villageunique, SI32 personid );


};

#endif