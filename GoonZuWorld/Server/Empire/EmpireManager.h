#ifndef _EMPIREMANAGER_H
#define _EMPIREMANAGER_H

#include "../Lib/Directives.h"

/// ������ �ִ�� - �۷ι� ������ ������ 42�����̶� �׳� �ִ� 45����
const SI32 MAX_EMPIRENUMBER = 45;
/// ������ �Ҽӵ� �� �ִ� �ִ� ������ ��
const SI32 MAX_EMPIRE_IN_VILLAGE = 5;
/// ������ �Ҽӵ� �� �ִ� �ִ� ����� ��
const SI32 MAX_EMPIRE_IN_GUILD = 3;
/// ������ �Ǽ��ϴµ� �ʿ��� ��
#ifdef _DEBUG
	const SI64 NEED_CREATEEMPIRE_MONEY = 1000;
#else
	const SI64 NEED_CREATEEMPIRE_MONEY = 1000000000;
#endif

class CEmpireUnitInfo
{
public:

	/// ���� ����ũ
	SI32 m_siEmpireUnique;
	/// ������ ���� ���� ����ũ
	SI32 m_siVillageUnique[MAX_EMPIRE_IN_VILLAGE];
	/// ������ ���� ������ �� ���� �ں���( ���� ���� �ε����� ��ġ )
	SI64 m_siInputTotalEmpireBaseMoney[MAX_EMPIRE_IN_VILLAGE];
	/// ������ ���� ��� �ε���
	SI32 m_siGuildUnique[MAX_EMPIRE_IN_GUILD];
	/// ������ �ں���
	SI64 m_siEmpireBaseMoney;

public:

	void InitEmpireUnitInfo()
	{
		m_siEmpireUnique = 0;
		SI32 i;
		for( i = 0; i < MAX_EMPIRE_IN_VILLAGE; ++i )
		{
			m_siVillageUnique[i] = 0;
			m_siInputTotalEmpireBaseMoney[i] = 0;
		}

		for( i = 0; i < MAX_EMPIRE_IN_GUILD; ++i )
		{
			m_siGuildUnique[i] = 0;
		}
		m_siEmpireBaseMoney = 0;
	}

	void SetEmpireUnitInfo( SI32 EmpireUnique, SI32 VillageUnique )
	{
		m_siEmpireUnique = EmpireUnique;
		m_siVillageUnique[0] = VillageUnique;
	}

	void SetEmpireUnitInfo( SI32 EmpireUnique, SI32* VillageUnique, SI64* InputTotalEmpireBaseMoney, SI32* GuildUnique, SI64 EmpireBaseMoney )
	{
		m_siEmpireUnique = EmpireUnique;
		SI32 i;
		for( i = 0; i < MAX_EMPIRE_IN_VILLAGE; ++i )
		{
			m_siVillageUnique[i] = VillageUnique[i];
			m_siInputTotalEmpireBaseMoney[i] = InputTotalEmpireBaseMoney[i];
		}

		for( i = 0; i < MAX_EMPIRE_IN_GUILD; ++i )
		{
			m_siGuildUnique[i] = GuildUnique[i] ;
		}

		m_siEmpireBaseMoney = EmpireBaseMoney;
	}

	void SetEmpireUnitInfo( CEmpireUnitInfo* EmpireUnitInfo )
	{
		m_siEmpireUnique = EmpireUnitInfo->GetEmpireUnique();
		SI32 i;
		for( i = 0; i < MAX_EMPIRE_IN_VILLAGE; ++i )
		{
			m_siVillageUnique[i] = EmpireUnitInfo->GetVillageUnique(i);
			m_siInputTotalEmpireBaseMoney[i] = EmpireUnitInfo->GetInputTotalEmpireBaseMoney(i);
		}

		for( i = 0; i < MAX_EMPIRE_IN_GUILD; ++i )
		{
			m_siGuildUnique[i] = EmpireUnitInfo->GetGuildUnique(i);
		}

		m_siEmpireBaseMoney = EmpireUnitInfo->GetEmpireBaseMoney();
	}

	CEmpireUnitInfo()
	{
		InitEmpireUnitInfo();
	}

	~CEmpireUnitInfo()
	{
	}

	SI32 GetEmpireUnique()
	{
		return m_siEmpireUnique;
	}

	SI32 GetVillageUnique( SI32 Index )
	{
		if( Index >= MAX_EMPIRE_IN_VILLAGE )
			return 0;
		return m_siVillageUnique[Index];
	}

	SI64 GetInputTotalEmpireBaseMoney( SI32 Index )
	{
		if( Index >= MAX_EMPIRE_IN_VILLAGE )
			return 0;
		return m_siInputTotalEmpireBaseMoney[Index];
	}

	SI32 GetGuildUnique( SI32 Index )
	{
		if( Index >= MAX_EMPIRE_IN_GUILD )
			return 0;
		return m_siGuildUnique[Index];
	}

	SI32 GetEmperorVillageUnique()
	{
		return m_siVillageUnique[0];
	}

	void SetEmpireBaseMoney( SI64 EmpireBaseMoney)
	{
		m_siEmpireBaseMoney = EmpireBaseMoney;
	}

	SI64 GetEmpireBaseMoney()
	{
		return m_siEmpireBaseMoney;
	}

	void SetVillageUnique( SI32 Index, SI32 VillageUnique )
	{
		if( Index >= MAX_EMPIRE_IN_VILLAGE )
			return;
		m_siVillageUnique[Index] = VillageUnique;
	}

	void SetInputTotalEmpireMoney( SI32 Index, SI64 EmpireMoney )
	{
		if( Index >= MAX_EMPIRE_IN_VILLAGE )
			return;
		m_siInputTotalEmpireBaseMoney[Index] = EmpireMoney;
	}

	void SetGuildUnique( SI32 Index, SI32 GuildUnique )
	{
		if( Index >= MAX_EMPIRE_IN_GUILD )
			return;
		m_siGuildUnique[Index] = GuildUnique;
	}

	
};

class CEmpireManager
{
private:
	
	CEmpireUnitInfo m_EmpireUnitInfo[MAX_EMPIRENUMBER];

public:

	CEmpireManager();
	~CEmpireManager();

	void AddEmpireUnit( CEmpireUnitInfo* EmpireUnitInfo );
	void DeleteEmpireUnit( SI32 EmpireUnique );
	void DeleteEmpireUnit( CEmpireUnitInfo* EmpireUnitInfo );
	void UpdateAddEmpireUnit( SI32 EmpireUnique, SI32 VillageUnique, SI32 GuildUnique );
	void UpdateDeleteEmpireUnit( SI32 EmpireUnique, SI32 VillageUnique, SI32 GuildUnique );
	void UpdateEmpireBaseMoney( SI32 EmpireUnique, SI64 LeftEmpireBaseMoney, SI32 VillageUnique, SI64 TotalInputEmpireBaseMoney );
	SI32 GetEmperorVillageUniqueByIndex( SI32 Index );
	SI32 GetEmperorVillageUniqueByEmpireUnique( SI32 EmpireUnique );
	SI32 FindEmpireUnique( SI32 VillageUnique );
    CEmpireUnitInfo* FindEmpire( SI32 EmpireUnique );
	CEmpireUnitInfo* FirstEmpire();
	bool IsInVillageUnique( SI32 EmpireUnique, SI32 VillageUnique );
	bool IsInGuildUnique( SI32 EmpireUnique, SI32 GuildUnique );
};

#endif