#include "GawiBawiBoMgr_Client.h"

#include "Char/CharManager/CharManager.h"
#include "../CommonLogic/CommonLogic.h"
#include "../Lib/dxutil.h"
#include "../Client/Client.h"

#include "../InterfaceMgr/InterfaceFile.h"
#include "../InterfaceMgr/InterfaceMgr.h"
#include "../../common/CommonHeader.h"
#include "../ninterface/NGawiBawiBoDlg/NGawiBawiBoDlg.h"
#include "../../CommonLogic/MsgType-GawiBawiBo.h"


extern cltCommonLogic* pclClient;

CGawiBawiBoMgr_Client::CGawiBawiBoMgr_Client()
{
	m_siStatus			= GAWIBAWIBO_NONE;	
	m_siResult			= GAWIBAWIBO_RESULT_NONE;
	m_siCumulativeMoney	= 0;
	m_siGawiBawiBoCount	= 0;

	ZeroMemory(&m_Timer, sizeof(clock_t));
	ZeroMemory(m_siWInPercentage, sizeof(m_siWInPercentage));
}

CGawiBawiBoMgr_Client::~CGawiBawiBoMgr_Client()
{
	
}


bool	CGawiBawiBoMgr_Client::Initialize()			//	�Ŵ��� �ʱ�ȭ
{
	//	�Ŵ��� �ʱ�ȭ �۾�.. ���Ϸε� ���
	bool bResult = false;

	//	�Ŵ��� �ʱ�ȭ �۾�.. ���Ϸε� ���
	bResult = LoadGawiBawiBoFiles();

	InitTimer();

	return bResult;
}

bool CGawiBawiBoMgr_Client::LoadGawiBawiBoFiles()
{
	NDataLoader	dataloader;

	bool bResult = false;

	if( pclClient->IsWhereServiceArea(ConstSwitch_TextEncryption))
		bResult = dataloader.LoadDataFromCryptFile(TEXT("Data/SRPInfo.txt"));
	else
		bResult = dataloader.LoadDataFromFile(TEXT("Data/SRPInfo.txt"));

	if (bResult == false)
		return false;

	TCHAR	szName[MAX_PATH] = TEXT("");
	SI32	siValue = 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	szName,		MAX_PATH,
		NDATA_INT32,	&siValue,	4,
		0,				0,			0
	};

	dataloader.RegDataType(pDataTypeInfo);

	SI16 siCount = 1;

	while(dataloader.IsEndOfData() != true) 
	{
		if (dataloader.ReadData() == true)	
		{
			if(siCount <= 4)		//	������������ 3�� �ε��������� �·� ������
				m_siWInPercentage[siCount] = siValue;
			else				//	������������ 3���ε��� ���ʹ� ��������Ʈ ������ (��������Ʈ�� ����ī��Ʈ�� ��ȹ�� �� �þ�� �����Ƿ� ���ͷ�)
				m_vecStraightWins.push_back(siValue);				

			siCount++;
		}
		else
			return true;
	}
	return false;	
}


bool CGawiBawiBoMgr_Client::StartGame()		//	���������� �Ŵ��� �۵�
{
	cltClient *pClient = (cltClient*)pclClient;

	if(pClient != NULL)
		pClient->CreateInterface(NGAWIBAWIBO_DLG);
	else
		return false;


	//	�÷��̾� ��ٸ����� ���¿��ٸ� �÷��̾ ���� �����Ƿ� �÷��� �������� �ݾ� üũ
	if(GetStatus() == GAWIBAWIBO_WAIT_PLAYER)
		SetStatus(GAWIBAWIBO_DO_CHECK_MONEY);

	return true;
}

void	CGawiBawiBoMgr_Client::Action()
{
	cltClient *pClient = (cltClient*)pclClient;
	if(pClient == NULL)
		return;

	// ���� ���� �̺�Ʈ���� ����ٸ� ���
	if(((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG]) != NULL)
	{
		if(pClient->pclCM->CR[1]->GetMapIndex() != MAPINDEX_FESTIVAL)
		{
			if(m_siStatus >= GAWIBAWIBO_WAIT_PLAYER)
			{
				GiveUp();

				if((CControllerMgr*)pClient->m_pDialog[NMSGBOX_DLG] != NULL)
					((CControllerMgr*)pClient->m_pDialog[NMSGBOX_DLG])->DeleteDialog();
			}
		}
	}

	switch(m_siStatus)
	{
	case GAWIBAWIBO_NONE:
		SetStatus(GAWIBAWIBO_INIT);
		break;

	case GAWIBAWIBO_INIT:
		{
			if(Initialize() == true)
				NextSteps();	//	�Ŵ��� �ʱ�ȭ �Ϸ�.
			else
				MsgBox("Error", "GawiBawiBo::Initialize is Failed");	
		}
		break;

	case GAWIBAWIBO_WAIT_PLAYER:	// ������ ��ٸ�����	
		break;

	case GAWIBAWIBO_DO_CHECK_MONEY:
		{
			//	������ ���Դ�. ������ �Ҽ� �ִ��� �ݾ��� üũ
			SI32 siNpcrate		= pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			GMONEY siNeedMoney	= siNpcrate * 200;	//	 ����� �ü� * 10

			TCHAR* pTitle	= GetTxtFromMgr(10344);
			NTCHARString256	pBody(GetTxtFromMgr(10343));

			NTCHARString256 strMoney;
			g_JYLibFunction.SetNumUnit(siNeedMoney, strMoney, 256);

			pBody.Replace("#money#", strMoney);

			stMsgBox MsgBox;
			MsgBox.Set((CControllerMgr*)pClient->m_pDialog[NGAWIBAWIBO_DLG], pTitle, pBody, MSGBOX_TYPE_YESNO, 0);
			pClient->SetMsgBox(&MsgBox, NULL, 0);

			NextSteps();
			SetTimer(GAWIBAWIBO_MAX_TIME);
		}
		break;

	case GAWIBAWIBO_NOW_CHECKING:		//	�ݾ� üũ���̴� ���~
		{
			// Ÿ�Ӿƿ�
			if(IsTimePassed() == true)
			{
				((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->EndCount();	// �ð����� ������ �������Ƿ� ���ó��
				GiveUp();
			}
			else
			{
				// ������ ��� ���� ���� ��� ���̴� ī��Ʈ
				SI32 siNpcrate		= pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
				GMONEY siNeedMoney	= siNpcrate * 200;	//	 ����� �ü� * 10

				TCHAR* pTitle	= GetTxtFromMgr(10344);
				NTCHARString256	pBody(GetTxtFromMgr(10343));

				NTCHARString256 strMoney;
				g_JYLibFunction.SetNumUnit(siNeedMoney, strMoney, 256);

				pBody.Replace("#money#", strMoney);
				pBody.Replace("#time#", SI32ToString(((GetTimePassed()+1000)/1000)));

				stMsgBox MsgBox;
				MsgBox.Set((CControllerMgr*)pClient->m_pDialog[NGAWIBAWIBO_DLG], pTitle, pBody, MSGBOX_TYPE_YESNO, 0);
				pClient->SetMsgBox(&MsgBox, NULL, 0);

				//((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->Counting(GetTimePassed()+1000);
			}
		}
		break;

	case GAWIBAWIBO_DO_CHARGEDMONEY:
		{
			((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->EndCount();

			//	�����÷��̰� ������ �÷��̾� �̹Ƿ� �ݾ� ����
			cltGameRequest_GawiBawiBo_ChargedMoney ChargedMoney;
			cltMsg clMsg(GAMEMSG_REQUEST_GAWIBAWIBO_CHARGED_MONEY, sizeof(cltGameRequest_GawiBawiBo_ChargedMoney), (BYTE*)&ChargedMoney);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			
			NextSteps();
		}
		break;

	case GAWIBAWIBO_NOW_CHARGINGMONEY:	// �������� �ݾ� ������..
		break;

	case GAWIBAWIBO_WAIT_SELECT:
		{
			//	���¸� ���������� ���� ��� ���·�
			((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->WaitForSelect();

			NextSteps();
			SetTimer(GAWIBAWIBO_MIN_TIME);
		}
		break;

	case GAWIBAWIBO_NOW_WAIT_SELECT:	//	�÷��̾ �и� �������� ��ٸ�����...		
		{
			// �ð����� �и� �����ʴ´ٸ� �������� �и� �����ϰ� ��.

			// time out
			if(IsTimePassed() == true)
			{
				// �������� ����
				SI08 siRand = rand() % 3;

				((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->RandomSelect(siRand+1);	// ���������� ��ư �ε����� 1~3 
				((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->EndCount();	// �ð����� ������ �������Ƿ� ���ó��
			}
			else
			{
				// �а��� ��....
				((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->Counting(GetTimePassed()+1000);
			}
		}
		break;

	case GAWIBAWIBO_SELECT:
		{
			//	�÷��̾ �и� �����ߴ�. �·� ������ ���� ����� ����

			((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->EndCount();

			cltGameRequest_GawiBawiBo_CalculateResult CalculateResult;
			cltMsg clMsg(GAMEMSG_REQUEST_GAWIBAWIBO_CALCULATE_RESULT, sizeof(cltGameRequest_GawiBawiBo_CalculateResult), (BYTE*)&CalculateResult);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

			NextSteps();
		}
		break;

	case GAWIBAWIBO_NOW_CALCULATE_SELECT:	//	�����κ��� ���������� ��� ��ٸ�����...
		break;

	case GAWIBAWIBO_CALCULATE_SELECT_COMPLETE:
		{
			//	��� ������ �Ϸ� �ƴ�.
			
			// ������ ����� �����ش�.
			((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->SeleceComplete();
			
			SetTimer(GAWIBAWIBO_NEXTSTEP_TIME);
			NextSteps();	
		}
		break;

	case GAWIBAWIBO_SHOW_CALCULATE_SELECT:
		{
			//	������ �ð����� ������ ��� �����ִ� ��
			if(IsTimePassed() == true)
				NextSteps();

			//	NPC�� ���������� ���� �¸�!
			if(m_siResult == GAWIBAWIBO_RESULT_ABUSE_WIN)
			{
				TCHAR*	pTitle	= GetTxtFromMgr(40055);
				TCHAR*	pBody	= GetTxtFromMgr(40056);
				pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);
			}
		}
		break;
	
	case GAWIBAWIBO_RESULT:
		{
			//	��� ������ �Ϸ� �ƴ�. ����� ���� �ִϸ��̼��� ������ �� �����ؼ� ������ ���� üũ
			//	3�� �� ���� ����
			((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->ResultComplete();

			SetTimer(GAWIBAWIBO_MIN_TIME);
			NextSteps();
		}

	case GAWIBAWIBO_SHOW_CEREMONY:
		{
			//	����� ���� �ִϸ��̼� ��~
			if(IsTimePassed() == true)
			{
				NextSteps();
				pClient->m_pDialog[NOTIFYMSG_DLG]->Show(false);

				// �й��� ��쿡�� �ִϸ��̼��� ����
				if(m_siResult != GAWIBAWIBO_RESULT_LOSE)	
					((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->WaitForSelect();
			}
		}
		break;

	case GAWIBAWIBO_RESULT_PROCESS:
		{
			//	����� ���� ����
			switch(m_siResult)
			{
			case GAWIBAWIBO_RESULT_WIN:
			case GAWIBAWIBO_RESULT_ABUSE_WIN:
				{
					// �¸�~
					// ���� �ְ����� �ߴٸ� �ٷ� ���ϸ޼����� �Բ� ����
					if(GetMaximumWins() == true)
					{
						m_siCumulativeMoney = GetCalculateCumulativeMoney(m_siGawiBawiBoCount);	
						GiveUp();
					}
					else
					{
						//	�����ǿ� ���� �����ݾ��� �����ݴϴ�.
						m_siCumulativeMoney = GetCalculateCumulativeMoney(m_siGawiBawiBoCount);	

						((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->SetCumulativeMoneyText(m_siCumulativeMoney);

						TCHAR* pTitle	= GetTxtFromMgr(40055);
						NTCHARString256	pBody(GetTxtFromMgr(40053));

						NTCHARString256 strMoney;
						g_JYLibFunction.SetNumUnit(GetCalculateCumulativeMoney(m_siGawiBawiBoCount+1), strMoney, 256);

						pBody.Replace("#money#", strMoney);

						stMsgBox MsgBox;
						MsgBox.Set((CControllerMgr*)pClient->m_pDialog[NGAWIBAWIBO_DLG], pTitle, pBody, MSGBOX_TYPE_YESNO, 2);
						pClient->SetMsgBox(&MsgBox, NULL, 0);

						SetTimer(GAWIBAWIBO_MAX_TIME);

						NextSteps();
					}
					//NextSteps();
				}
				break;

			case GAWIBAWIBO_RESULT_DRAW:
				{
					// ��� ��� �� ����
					DrawGame();					
				}
				break;

			case GAWIBAWIBO_RESULT_LOSE:
				{
					//	�������������� ����.
					//((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->DeleteDialog();

					TCHAR* pTitle	= GetTxtFromMgr(40050);
					NTCHARString256	pBody(GetTxtFromMgr(40052));

					stMsgBox MsgBox;
					MsgBox.Set((CControllerMgr*)pClient->m_pDialog[NGAWIBAWIBO_DLG], pTitle, pBody, MSGBOX_TYPE_OK, 3);
					pClient->SetMsgBox(&MsgBox, NULL, 0);
				}
				break;

			default:
				assert(0);
				break;
			}
		}
		break;

	case GAWIBAWIBO_NOW_RESULT_PROCESS:
		{
			//	���� ������ �� ������ ���� �����ݾ� �޾ư��� ������...
			
			// Ÿ�Ӿƿ�
			if(IsTimePassed() == true)
			{
				((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->EndCount();	// �ð����� ������ �������Ƿ� ���ó��
				GiveUp();
			}
			else
			{
				// ������ ��� ���� ���� ��� ���̴� ī��Ʈ

				TCHAR* pTitle	= GetTxtFromMgr(40055);
				NTCHARString256	pBody(GetTxtFromMgr(40053));

				NTCHARString256 strMoney;
				g_JYLibFunction.SetNumUnit(GetCalculateCumulativeMoney(m_siGawiBawiBoCount+1), strMoney, 256);

				pBody.Replace("#money#", strMoney);
				pBody.Replace("#time#", SI32ToString(((GetTimePassed()+1000)/1000)));

				stMsgBox MsgBox;
				MsgBox.Set((CControllerMgr*)pClient->m_pDialog[NGAWIBAWIBO_DLG], pTitle, pBody, MSGBOX_TYPE_YESNO, 2);
				pClient->SetMsgBox(&MsgBox, NULL, 0);

				//((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->Counting(GetTimePassed()+1000);
			}
		}
		break;

	default:
		assert(0);
		break;
	}
}

//  [8/11/2009 ��ȣ_GAWIBAWIBO] ���°� ����(�� ���°����� ������ ���ܵ��� ���� �մϴ�.)
void CGawiBawiBoMgr_Client::SetStatus(SI16 siStatus)
{
	if(siStatus < GAWIBAWIBO_NONE || siStatus >= GAWIBAWIBO_END)
	{
		assert(0);
		return;
	}

	m_siStatus = siStatus;
}

SI08 CGawiBawiBoMgr_Client::GetCount()
{
	if(m_siGawiBawiBoCount < 0 || m_siGawiBawiBoCount >= (SI08)m_vecStraightWins.size())
	{
		assert(0);
		return -1;
	}
	else
		return m_siGawiBawiBoCount;
}

// �Ѿ�� ���ڰ��� ���¼�. �ش� ���½� ���� ���ִ� �����ݾ���  ���Ѵ�.
GMONEY CGawiBawiBoMgr_Client::GetCalculateCumulativeMoney(SI08 siCount)						//	�����ݾ� ���
{
	GMONEY siMoneyCumulativeMoney = 0;

	//	siCount ������ ������ ���� �ݾ��� ����
	SI32	siNpcrate	= pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
	GMONEY	siUnitMoney	= siNpcrate * 200;	//	 ����� �ü� * 10			

	////	 siIndex�� �ʱⰪ�� 1�� ������ ������ ���ҽ��󿡼� 1���� index �� 1�̴�.
	//for(SI08 siIndex = 1; siIndex <= siCount; siIndex++)
	//{
	//	if(siIndex == 1)	// ���� �����ݾ��� ���� ���.
	//		siMoneyCumulativeMoney = (siUnitMoney * m_vecStraightWins.at(siIndex)) / 100;	
	//	else
	//		siMoneyCumulativeMoney = (siMoneyCumulativeMoney * m_vecStraightWins.at(siIndex)) / 100;
	//}

	// ����ݾ� ������ ����
	siMoneyCumulativeMoney = (siUnitMoney * m_vecStraightWins.at(siCount)) / 100;	

	return siMoneyCumulativeMoney;
}

void CGawiBawiBoMgr_Client::SetResult(SI08 siResult)		// ���������� ���� ���
{
	if(siResult <= GAWIBAWIBO_RESULT_NONE || siResult >= GAWIBAWIBO_RESULT_END)
	{
		assert(0);
		return;
	}

	m_siResult = siResult;
}

void CGawiBawiBoMgr_Client::InitTimer()
{
	m_Timer = pclClient->CurrentClock;
}

void CGawiBawiBoMgr_Client::SetTimer(clock_t lnTime)
{
	m_Timer = pclClient->CurrentClock + lnTime;
}

clock_t CGawiBawiBoMgr_Client::GetTimePassed()
{
	return m_Timer - pclClient->CurrentClock;
}

bool CGawiBawiBoMgr_Client::IsTimePassed()
{
	if(m_Timer <= pclClient->CurrentClock)
		return true;
	else
		return false;
}

//	���
void CGawiBawiBoMgr_Client::GiveUp()
{
	// ����
	if(m_siGawiBawiBoCount <= 0)
		EndGame();
	else
	{
		cltGameRequest_GawiBawiBo_Reward Reward(m_siCumulativeMoney);
		cltMsg clMsg(GAMEMSG_REQUEST_GAWIBAWIBO_REWARD, sizeof(cltGameRequest_GawiBawiBo_Reward), (BYTE*)&Reward);
		pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

		SetStatus(GAWIBAWIBO_WAIT_PLAYER);
	}


	cltClient* pClient = (cltClient*)pclClient;
	((NGawiBawiBoDlg*)pClient->m_pDialog[NGAWIBAWIBO_DLG])->DeleteDialog();

	if((CControllerMgr*)pClient->m_pDialog[NMSGBOX_DLG] != NULL)
		((CControllerMgr*)pClient->m_pDialog[NMSGBOX_DLG])->DeleteDialog();
}
