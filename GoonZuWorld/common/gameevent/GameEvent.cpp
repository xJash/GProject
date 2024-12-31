//---------------------------------
// 2005/3/17 ���ؿ�
//---------------------------------

#include "CommonLogic.h"
#include "../../Server/Server.h"

#include "../../lib/WebHTML/WebHTML.h"

#include "GameEvent.h"

#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "MsgType-Item.h"

#include "Char/CharManager/CharManager.h"
#include "Char/CharServer/Char-Server.h"

#include "../../DBManager/GameDBManager_World/DBMsg-item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"

extern cltCommonLogic* pclClient;


cltGameEvent::cltGameEvent()
{
	Init();
}

cltGameEvent::~cltGameEvent()
{
}


void cltGameEvent::Init()
{
	//m_siWinPrizeMemebers = 0 ;
	//m_siTotalCheckMemebers = 0 ;

	m_siPara1 = 0 ;
	m_siPara2 = 0 ;
}

bool cltGameEvent::CheckPrizeEvent(SI32 id,SI32 ticket)
{
/*	if ( m_siWinPrizeMemebers >= MAX_WINPRIZE_MEMBER ) return false ;
	if ( IsPC(id) == false ) return false ;

	cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
	if ( pclchar == NULL ) return false ;
	if ( pclchar->pclCI->clBI.bNewAccount == false ) return false ; // �ű� �������ΰ�?
	if ( pclchar->pclCI->clBI.bGameEvent == true ) return false ; // �̹� �ٸ� ĳ�����ζ� �߾��°� �� �߾��°�?
	if ( pclchar->pclCI->clBI.bWinPrizeEvent == true ) return false ; // �̹� ��÷�Ǿ��°�?

	m_siTotalCheckMemebers ++ ;

	if ( m_siTotalCheckMemebers % 4 == 0 )
	{
		return true ;
	}*/

/*	if ( rand() % 100 == 0 )
	{
		if ( !pclClient->pclCM->CR[id]->pclCI->clBI.bGameEvent )
		{
			sDBRequest_Prize_GameEvent clevent(pclClient->pclCM->CR[id]->pclCI->GetPersonID(), id, 1, false);
			((cltServer*)pclClient)->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clevent);
			((cltServer*)pclClient)->SendPostOfficeItemToPerson(pclClient->pclCM->CR[id]->pclCI->GetPersonID(), NULL,
																"�溹���� ���λ��� Ȯ�����ּ���.");
			return true ;
		}
	}*/

	/*cyj  �� �̺�Ʈ �ӽ� ����	
	SI32 itemunique = 0 ;
	SI32 itemnum	= 0 ;
	cltItem clitem;
	clitem.Init();

	SI32 index = rand() % 8 ;
	BOOL bRareitem = FALSE ;

	if ( ticket == ITEMUNIQUE(14500) ) // ��»�
	{
		if ( (pclClient->siServiceArea == ConstServiceArea_Korea && rand() % 1000 == 0 ) )
		{
			bRareitem = TRUE ;
			index = rand() % 100 ;

			if ( index > 85 )
			{
				itemunique = ITEMUNIQUE(14165);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����̵�[1��]���ױ�"));
				itemnum = 1 ;
			}
			else if ( index > 70 )
			{
				itemunique = ITEMUNIQUE(18110);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�Ķ�����"));
				itemnum = 1 ;
			}
			else if ( index > 55 )
			{
				itemunique = ITEMUNIQUE(24015);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��ȯ��[��ȭ]�̿��"));
				itemnum = 1 ;
			}
			else if ( index > 40 )
			{
				itemunique = ITEMUNIQUE(15100);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("����"));
				itemnum = 1 ;
			}
			else if ( index > 25 )
			{
				itemunique = ITEMUNIQUE(13390);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("���ø�"));
				itemnum = 1 ;
			}
			else if ( index > 20 )
			{
				itemunique = ITEMUNIQUE(5506);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�鸶������"));
				itemnum = 1 ;
			}
			else if ( index > 5 )
			{
				itemunique = ITEMUNIQUE(3500);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("���»��"));
				itemnum = 100 ;
			}
			else if ( index >= 0 )
			{
				itemunique = ITEMUNIQUE(11760);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��ù�"));
				itemnum = 1 ;
			}
		}
		else
		{
			switch(index) {
			case 0:
				{
					itemunique = ITEMUNIQUE(2565);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��ȭ��"));
					itemnum = 20 ;
				}
				break;
			case 1:
				{
					itemunique = ITEMUNIQUE(2590);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�籺����"));
					itemnum = 20 ;
				}
				break;
			case 2:
				{
					itemunique = ITEMUNIQUE(3265);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��ġ����"));
					itemnum = 10 ;
				}
				break;
			case 3:
				{
					itemunique = ITEMUNIQUE(5000);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��ź"));
					itemnum = 10 ;
				}
				break;
			case 4:
				{
					itemunique = ITEMUNIQUE(6105);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�볪��"));
					itemnum = 10 ;
				}
				break;
			case 5:
				{
					itemunique= ITEMUNIQUE(7000);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�谡��"));
					itemnum = 10 ;
				}
				break;
			case 6:
				{
					itemunique = ITEMUNIQUE(13305);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("ö����"));
					itemnum = 10 ;
				}
				break;
			case 7:
				{
					itemunique = ITEMUNIQUE(8660);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�ִ볻����º���"));
					itemnum = 1 ;
				}
				break;
			default:
				return false ;
			}
		}
	}
	else if ( ticket == ITEMUNIQUE(14400) ) // ����
	{
		if ( (pclClient->siServiceArea == ConstServiceArea_Korea && rand() % 500 == 0 ) )
		{
			bRareitem = TRUE ;
			index = rand() % 100 ;

			if ( index > 85 )
			{
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����̵�[1��]���ױ�"));
				itemunique = ITEMUNIQUE(14170);
				itemnum = 1 ;
			}
			else if ( index > 70 )
			{
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����Ȱ��"));
				itemunique = ITEMUNIQUE(18400);
				itemnum = 1 ;
			}
			else if ( index > 55 )
			{
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��ȯ��[��ȭ]�̿��"));
				itemunique= ITEMUNIQUE(24015);
				itemnum = 2 ;
			}
			else if ( index > 40 )
			{
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����ǰ���"));
				itemunique = ITEMUNIQUE(15300);
				itemnum = 1 ;
			}
			else if ( index > 25 )
			{
				itemunique = ITEMUNIQUE(13380);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����Ÿ�"));
				itemnum = 1 ;
			}
			else if ( index > 20 )
			{
				itemunique = ITEMUNIQUE(5540); 
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("õ����������"));
				itemnum = 1 ;
			}
			else if ( index > 5 )
			{
				itemunique = ITEMUNIQUE(3500);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("���»��"));
				itemnum = 300 ;
			}
			else if ( index >= 0 )
			{
				itemunique = ITEMUNIQUE(11730);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�庸��"));
				itemnum = 1 ;
			}
		}
		else
		{
			switch(index) {
			case 0:
				{
					itemunique = ITEMUNIQUE(2575);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����뺸��"));
					itemnum = 50;
				}
				break;
			case 1:
				{
					itemunique = ITEMUNIQUE(2595);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("������"));
					itemnum = 50 ;
				}
				break;
			case 2:
				{
					itemunique = ITEMUNIQUE(3295); 
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("������"));
					itemnum = 20 ;
				}
				break;
			case 3:
				{
					itemunique = ITEMUNIQUE(5015);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("ö��"));
					itemnum = 20 ;
				}
				break;
			case 4:
				{
					itemunique = ITEMUNIQUE(6100);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�ڳ���"));
					itemnum = 20 ;
				}
				break;
			case 5:
				{
					itemunique = ITEMUNIQUE(7050); 
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��"));
					itemnum = 20 ;
				}
				break;
			case 6:
				{
					itemunique = ITEMUNIQUE(8055);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("������ȸ�ʸ�"));
					itemnum = 20 ;
				}
				break;
			case 7:
				{
					itemunique = ITEMUNIQUE(8660);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�ִ볻����º���"));
					itemnum = 3 ;
				}
				break;
			default:
				return false ;
			}
		}
	}
	else if ( ticket == ITEMUNIQUE(14300) ) // �����
	{
		if ( (pclClient->siServiceArea == ConstServiceArea_Korea && rand() % 333 == 0 ) )
		{
			bRareitem = TRUE ;
			index = rand() % 100 ;

			if ( index > 85 )
			{
				itemunique = ITEMUNIQUE(14190);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����̵�[1��]���ױ�"));
				itemnum = 1 ;
			}
			else if ( index > 70 )
			{
				itemunique = ITEMUNIQUE(18800);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("Ÿ��õ�糯��"));
				itemnum = 1 ;
			}
			else if ( index > 55 )
			{
				itemunique = ITEMUNIQUE(24015);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��ȯ��[��ȭ]�̿��"));
				itemnum = 4 ;
			}
			else if ( index > 40 )
			{
				//cyj �����ʱ�ȭ�̿�� ����ũ���� 14090->24030
				//itemunique = 14090 ;  // �����ʱ�ȭ�̿��
				itemunique = ITEMUNIQUE(24030) ;  // �����ʱ�ȭ�̿��
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�����ʱ�ȭ�̿��"));
				itemnum = 1 ;
			}
			else if ( index > 25 )
			{
				itemunique = ITEMUNIQUE(13400);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�߿������"));
				itemnum = 1 ;
			}
			else if ( index > 20 )
			{
				itemunique = ITEMUNIQUE(5560);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�Ʊ�ȣ����"));
				itemnum = 1 ;
			}
			else if ( index > 5 )
			{
				itemunique = ITEMUNIQUE(3500);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("���»��"));
				itemnum = 500 ;
			}
			else if ( index >= 0 )
			{
				itemunique = ITEMUNIQUE(11750);
				//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�ٸ�"));
				itemnum = 1 ;
			}
		}
		else
		{
			switch(index) {
			case 0:
				{
					itemunique = ITEMUNIQUE(2595);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("��Ȳû�ɿ�"));
					itemnum = 100 ;
				}
				break;
			case 1:
				{
					itemunique = ITEMUNIQUE(2090);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("���뺸��"));
					itemnum = 100 ;
				}
				break;
			case 2:
				{
					itemunique = ITEMUNIQUE(3315); 
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("������"));
					itemnum = 50 ;
				}
				break;
			case 3:
				{
					itemunique =  ITEMUNIQUE(5045);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�ݱ�"));
					itemnum = 30 ;
				}
				break;
			case 4:
				{
					itemunique = ITEMUNIQUE(6125);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�ҳ���"));
					itemnum = 50 ;
				}
				break;
			case 5:
				{
					itemunique = ITEMUNIQUE(7070);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�ݻ�"));
					itemnum = 30 ;
				}
				break;
			case 6:
				{
					itemunique= ITEMUNIQUE(13306);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("�������Ǵ�"));
					itemnum = 50 ;
				}
				break;
			case 7:
				{
					itemunique = ITEMUNIQUE(8100);
					//itemunique = pclClient->pclItemManager->FindUniqueFromName(TEXT("���ڼ�������"));
					itemnum = 5 ;
				}
				break;
			default:
				return false ;
			}
		}
	}
	else return false ;

	bool brareswitch = false;
	if(pclClient->pclItemManager->MakeRandItemUnique( itemunique, &clitem, 0, &brareswitch) == true)
	{
		clitem.SetItemNum(itemnum);

		SI32 rtnvalue = 0;
		SI32 inputreason = INPUTITEMPERSON_OPTION_WAR ;
		if ( bRareitem )
			inputreason = INPUTITEMPERSON_OPTION_CRAZYEVENT ;
		if(((cltCharServer*)pclClient->pclCM->CR[id])->InputItem(pclClient->pclItemManager, &clitem,
			inputreason, &rtnvalue) == false)
		{
			((cltServer*)pclClient)->SendLog_InventoryFull( pclClient->pclCM->CR[id]->pclCI->GetPersonID(),itemunique,itemnum,
				inputreason);
		}

		bool setitem = false ;
		// ���ø��̸�
		if ( itemunique == ITEMUNIQUE(13390) )
		{
			setitem = true ;
			itemunique = ITEMUNIQUE(9440) ;
			itemnum = 1 ;
		}
		// �����Ÿ���
		else if ( itemunique == ITEMUNIQUE(13380))
		{
			setitem = true ;
			itemunique = ITEMUNIQUE(9430) ;
			itemnum = 1 ;
		}
		// �߿��������
		else if (itemunique == ITEMUNIQUE(13400) )
		{
			setitem = true ;
			itemunique = ITEMUNIQUE(9450) ;
			itemnum = 1 ;
		}

		if ( setitem )
		{
			clitem.Init() ;
			if(pclClient->pclItemManager->MakeRandItemUnique( itemunique, &clitem, 0, &brareswitch) == true)
			{
				clitem.SetItemNum(itemnum);

				if(((cltCharServer*)pclClient->pclCM->CR[id])->InputItem(pclClient->pclItemManager, &clitem,
					inputreason, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendLog_InventoryFull( pclClient->pclCM->CR[id]->pclCI->GetPersonID(),itemunique,itemnum,
						inputreason);
				}
			}
		}
	}
	*/

	return true ;
}

void cltGameEvent::GetItemUniqueAndNumRamdomSelect(SI32 * unique , SI32 * num)
{
/*	if ( m_siWinPrizeMemebers >= MAX_WINPRIZE_MEMBER ) return ;

	if ( m_siPara1 > MAX_PARA_1 && m_siPara2 > MAX_PARA_2 ) return ;

	m_siWinPrizeMemebers ++ ;

	if ( m_siPara1 > MAX_PARA_1 )
	{
		m_siPara2 ++ ;

		*unique = ITEMUNIQUE(2040) ;
		*num = 400 ;

		return ;
	}
	else if ( m_siPara2 > MAX_PARA_2 )
	{
		m_siPara1 ++ ;

		*unique = 14005 ;
		*num = 15 ;

		return ;
	}
	else
	{
		if ( rand() % 2 )
		{
			m_siPara2 ++ ;

			*unique = ITEMUNIQUE(2040);
			*num = 400 ;

			return ;
		}
		else
		{
			m_siPara1 ++ ;

			*unique = 14005 ;
			*num = 15 ;

			return ;
		}
	}*/
}