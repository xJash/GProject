#ifndef __MSGTYPEGAWIBAWIBO_H__
#define __MSGTYPEGAWIBAWIBO_H__


//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"

#pragma once 


//	[8/12/2009 ��ȣ_GAWIBAWIBO] Client -> Server	�ݾ��� ����
class cltGameRequest_GawiBawiBo_ChargedMoney
{
public:
	cltGameRequest_GawiBawiBo_ChargedMoney()
	{
		ZeroMemory(this, sizeof(cltGameRequest_GawiBawiBo_ChargedMoney));
	}
};


//  [8/12/2009 ��ȣ_GAWIBAWIBO] �¹��� ����
class cltGameRequest_GawiBawiBo_CalculateResult
{
public:
	cltGameRequest_GawiBawiBo_CalculateResult()
	{
		ZeroMemory(this, sizeof(cltGameRequest_GawiBawiBo_CalculateResult));
	}
};

class cltGameResponse_GawiBawiBo_CalculateResult
{
public:
	SI08 m_siResult;		//  ���� ���
	SI08 m_siCount;			//	���� ����
	SI08 m_siValidCount;	//	���� ���� ��ȿ�Ѱ��ΰ�.

	cltGameResponse_GawiBawiBo_CalculateResult(SI08 siResult, SI08 siCount = 0, SI08 siValidCount = 0)
	{
		ZeroMemory(this, sizeof(cltGameResponse_GawiBawiBo_CalculateResult));

		m_siResult		= siResult;
		m_siCount		= siCount;
		m_siValidCount	= siValidCount;
	}
};

////	���������� ���� ī��Ʈ ����
//class cltGameRequest_GawiBawiBo_GawiBawiBoCount_Increase
//{
//public:
//	SI08 m_siCount;	//	 ���� ������ ������
//
//	cltGameRequest_GawiBawiBo_GawiBawiBoCount_Increase(SI08 siCount)
//	{
//		ZeroMemory(this, sizeof(cltGameRequest_GawiBawiBo_GawiBawiBoCount_Increase));
//		m_siCount = siCount;
//	}
//};
//
////	���������� ���� ī��Ʈ ����
//class cltGameResponse_GawiBawiBo_GawiBawiBoCount_Increase
//{
//public:
//	SI08 m_siCount;	//	 ���� ������ ������
//
//	cltGameResponse_GawiBawiBo_GawiBawiBoCount_Increase(SI08 siCount)
//	{
//		ZeroMemory(this, sizeof(cltGameResponse_GawiBawiBo_GawiBawiBoCount_Increase));
//		m_siCount = siCount;
//	}
//};


//	���� ��Ŷ
class cltGameRequest_GawiBawiBo_Reward
{
public:
	GMONEY m_siMoney;	//	���� �Ӵ� ������ ������
    
	cltGameRequest_GawiBawiBo_Reward(GMONEY siMoney)
	{
		ZeroMemory(this, sizeof(cltGameRequest_GawiBawiBo_Reward));
		m_siMoney = siMoney;
	}
};

//	���� ��Ŷ
class cltGameResponse_GawiBawiBo_Reward
{
public:
	GMONEY m_siMoney;	//	���� �Ӵ� ������ ������

	cltGameResponse_GawiBawiBo_Reward(GMONEY siMoney)
	{
		ZeroMemory(this, sizeof(cltGameResponse_GawiBawiBo_Reward));
		m_siMoney = siMoney;
	}
};


//	8���� �̻� �˸� ��Ŷ
class cltGameResponse_GawiBawiBo_Notice_Reward
{
public:
	TCHAR	m_szName[256];	//	�̸�
	SI08	m_siCount;	//	����
	GMONEY	m_siMoney;	//	���� �Ӵ� ������ ������

	cltGameResponse_GawiBawiBo_Notice_Reward(TCHAR* szName, SI08 siCount, GMONEY siMoney)
	{
		ZeroMemory(this, sizeof(cltGameResponse_GawiBawiBo_Notice_Reward));
		StringCchCopy(m_szName, 256, szName);
		m_siCount	= siCount;
		m_siMoney	= siMoney;
	}
};
	
#endif

