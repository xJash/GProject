#pragma once

#include "../CommonLogic/CommonLogic.h"

namespace REWARDTYPE
{
	enum ENUM 
	{
		START = 0,
		//==================================================================
		BATTLEROYAL_WINNER,				// ��Ʋ�ξ� - �����
		BATTLEROYAL_KILLPLAYER,			// ��Ʋ�ξ� - �÷��̾� ���̱�
		//==================================================================
		END,
		COUNT = END -1
	};
}

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.09.28
// Ŭ������ : CRewardItemByProb
// ���� : Ȯ�� ���� ������ 
//================================================================================
class CRewardItemByProb
{	 
	// �ɹ� �޼ҵ�
public:
	CRewardItemByProb()
	{
		m_uiUnique = 0;
		m_uiProb = 0;
		m_uiNum = 0;
		m_uiMinNum = 0;
	}
	~CRewardItemByProb()
	{};

	void	SetMinNum(UI32 uiMinNum) { m_uiMinNum = uiMinNum; }
	void	SetNum(UI32 uiNum) { m_uiNum = uiNum; }
	void	SetProb(UI32 uiProb) { m_uiProb = uiProb; }
	void	SetUnique(UI32 uiUnique) { m_uiUnique = uiUnique; }

	UI32	GetMinNum() { return m_uiMinNum; }
	UI32	GetNum() { return m_uiNum; }
	UI32	GetProb() { return m_uiProb; }
	UI32	GetUnique() { return m_uiUnique; }

protected:
	UI32	m_uiUnique;				// ����ũ
	UI32	m_uiProb;				// Ȯ��
	UI32	m_uiNum;				// ����
	UI32	m_uiMinNum;				// �ּ� ����
};

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.09.28
// Ŭ������ : CRewardTypeItemByProbMgr
// ���� : Ȯ�� ���� ������ ������ 
//================================================================================
class CRewardTypeItemByProbMgr
{	 
// �ɹ� �޼ҵ�
public:
	CRewardTypeItemByProbMgr();
	~CRewardTypeItemByProbMgr();
	
	BOOL	Create(UI32 uiRewardType, UI32 uiCount);	// ����
	BOOL	Destroy();													// ����
	BOOL	GetRandItemUnique(UI32* puiUnique,UI32* puiNum);			// ������ ����
	UI32	GetType();
	BOOL	AnalyzeItemInfo(TCHAR* pszData);

	const static SI32	INIT_ITEMCOUNT = 20;
protected:
	const static SI32	MAX_RANDVALUE = 10000;
		
	UI32							m_uiRewardType;		// ���� ����
	UI32							m_uiItemCount;		// ������ ��
	NkVector<CRewardItemByProb>*	m_pVecRewardItem;	// ���� ������ ����Ʈ
};

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.10.14
// Ŭ������ : CRewardItemByProbMgr
// ���� : Ȯ�� ���� Ÿ�Ժ� ������ ����Ʈ ������ 
//================================================================================
class CRewardItemByProbMgr
{	 
	// �ɹ� �޼ҵ�
public:
	CRewardItemByProbMgr();
	~CRewardItemByProbMgr();

	BOOL	Create();			// ����
	BOOL	Destroy();			// ����
	CRewardTypeItemByProbMgr*	GetRewardTypeItemByProbMgr(UI32 uiRewardType);

protected:
	// ���� ������ �ε�
	BOOL	LoadFileData();

	NkVector<CRewardTypeItemByProbMgr>	m_pVecRewardItemMgr;	// ���� Ÿ�� ������ �Ŵ��� ����Ʈ
	
};

