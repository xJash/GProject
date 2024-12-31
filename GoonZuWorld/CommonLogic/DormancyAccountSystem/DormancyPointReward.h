#pragma once

#include "../CommonLogic/CommonLogic.h"

#include "DormancyPointItem.h"
#include "DormancyPointProcess.h"

class CDormancyPointItemMgr;
class CDormancyPointProcess;
class cltClient;
class cltServer;

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.4
// Ŭ������ : CDormancyPointReward
// ���� : �޸� ���� �ý����� ����Ʈ ���� ���� ��Ʈ�ѷ� Ŭ����
//================================================================================
class CDormancyPointReward
{
	// �ɹ� ����
public:
	// ����Ʈ ������ ���� Ŭ����
	CDormancyPointItemMgr*	m_pclDormancyPointItemMgr;
	// �޸� ���� �Ⱓ
	const static SI32 DURATIONDATE = 30;
	// �޸� ���� ���� ��� �÷��� ��
	const static SI32 WARING_EXPIRATION_FLAG = 5;

private:
	// Ŭ���̾�Ʈ ��ü
	cltCommonLogic*	m_pclCommon;

	// �ɹ� �޼ҵ�
public:
	// ������
	CDormancyPointReward();
	// �Ҹ���
	virtual ~CDormancyPointReward(void);

	//����
	BOOL		Create();

	//����Ʈ ������ ������ �Ŵ����� �ε����� �˾Ƴ���.
	cltItemInfo	*GetItemInfo(SI32 siIndex);
	//����Ʈ ������ ����ũ�� �Ŵ����� �ε����� �˾Ƴ���.
	SI32		GetItemUnique(SI32 siIndex);
	//�������� �޸� ����Ʈ�� �Ŵ����� �ε����� �˾Ƴ���.
	SI32		GetItemPoint(SI32 siIndex);

	//����Ʈ ������ ���� ����
	SI32		GetItemCount();
};


//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.4
// Ŭ������ : CDormancyPointRewardClient
// ���� : �޸� ���� �ý����� ����Ʈ ���� ���� ��Ʈ�ѷ� Ŭ����(Ŭ���̾�Ʈ��)
//================================================================================
class CDormancyPointRewardClient : public CDormancyPointReward
{
	// �ɹ� ����
public:

private:
	// Ŭ���̾�Ʈ ��ü
	cltClient*	m_pclClient;

	// �ɹ� �޼ҵ�
public:
	//	������
	CDormancyPointRewardClient(void);
	// �Ҹ���
	virtual ~CDormancyPointRewardClient(void);

	// �޸�������� �� ��� �޸� ����Ʈ ���̾�α׸� �����Ѵ�.
	BOOL	CreatePointDlg();

	// ����Ʈ ������ ���� ���Ӽ����� ��û
	BOOL	BuyPointItemRequest(SI32 siItemUnique);
	
	// ����Ʈ ������ ���� ���Ӽ����� ���� ����
	//	BuyPointItemResponse(cltCharServer *pclChar, SI32 siItemUnique);

	// �޸� ����Ʈ ���� ����
	BOOL	RecvDormancyInfo(cltCharClient*	pclChar, SI32 siPoint, SI32 siReaminedPlayTime, BOOL bDormancyState, SI16 siStartedYear, SI16 siStartedMonth, SI16 m_siStartedDay);
};

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.2
// Ŭ������ : CDormancyPointRewardServer
// ���� : �޸� ���� �ý����� ����Ʈ ���� ���� ��Ʈ�ѷ� Ŭ����(������)
//================================================================================
class CDormancyPointRewardServer : public CDormancyPointReward
{
	// �ɹ� ����
public:

	// �ɹ� �޼ҵ�
private:
	CDormancyPointProcess m_PointProcess;
	// Ŭ���̾�Ʈ ��ü
	cltServer*	m_pclServer;
public:
	//	������
	CDormancyPointRewardServer(void);
	// �Ҹ���
	virtual ~CDormancyPointRewardServer(void);

	// �޸� ���� ���� �����ϱ� ��û
	BOOL	SendDBChangeDormancyState(cltCharServer *pclServer, bool bDormancyState);

	// �޸� ���� ���� �����ϱ� ����
	BOOL	RecvDBChangeDormancyState(cltCharServer *pclServer, bool bDormancyState);

	// ����Ʈ ���
	BOOL	CalcPoint(cltCharServer *pclServer);

	// ó�� ���� ���� ����
	BOOL	DeterminProcessing(SI32	siCurrentime);
	
	// ����Ʈ ������ ����
	BOOL	SelectPointItem(cltCharServer *pclChar, SI32 siItemUnique);

	// ����Ʈ ������ ���� DB�� ��û
	BOOL	BuyPointItemRequest(SI32 siCharId , cltCharServer *pclChar, SI32 siItemUnique);
	// ����Ʈ ������ ���� DB�� ���� ����
	BOOL	BuyPointItemResponse(cltCharServer*	pclChar, cltItem *pclItem, SI32 siItempos, SI32 siItemPoint);

	// �޸� ����Ʈ ���� ����
	BOOL	SendClientDormancyInfo(cltCharServer*	pclChar);

	// DB�� �޸� ����Ʈ ���� ����
	BOOL	RecvDBDormancyInfo(cltCharServer*	pclChar, SI32 siPoint);
	// DB�� �޸� ����Ʈ ���� ����
	BOOL	SendDBDormancyInfo(cltCharServer*	pclChar, SI32 siDPoint);

	// �Ⱓ�� ���� �Ǿ�����
	BOOL	IsExpiration(cltCharServer *pclServer, _SYSTEMTIME &rclCurrentDate);

	// �޸� ���� ���Ḧ ��� �Ѵ�.
	BOOL	WaringExpiration(cltCharServer *pclServer);
	// �޸� ���� ���¸� ������ �Ⱓ
	SI32	GetDateFromExpiration(cltCharServer *pclServer, _SYSTEMTIME &rclCurrentDate);
};