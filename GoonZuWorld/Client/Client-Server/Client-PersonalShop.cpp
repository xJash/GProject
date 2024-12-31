#include "../Client.h"
#include "../Music/Music.h"
#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/Msg/MsgType-PersonalShop.h"

#include "../Common/Map/MapManager/MapManager.h"
#include "../Common/Map/MapManager/MapManager.h"
#include "Char/CharManager/CharManager.h"


#include "../Interface/DrawChat/DrawChat.h"
#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"
//#include "../Interface/PersonalShop/PersonalShopDlg.h"
#include "../Interface/PersonalShopSearchDlg/PersonalShopSearchDlg.h"
#include "../Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "../NInterface/NPersonalShopDlg/NPersonalShopDlg.h"
#include "../NInterface/NPersonalShopSearchDlg/NPersonalShopSearchDlg.h"
#include "../ninterface/NManufactureDlg/NManufactureDlg.h"
#include "../NInterface/NLetterDlg/NLetterDlg.h"
#include "../ninterface/NManufactureDlg_New/NManufactureDlg_New.h"
#include "../ninterface/NManufactureSerchDlg/NManufactureSerchDlg.h"

// Ư���� ������� ���λ��� ��ʸ� �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONALSHOPBANNER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PersonalShopBanner* pclinfo = (cltGameMsgResponse_PersonalShopBanner*)pclMsg->cData;

	// ��ǳ���� ����. 
	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];

		if(pclinfo->siResult > 0)
		{
			//=========================================
			// Personal Shop�� �����Ѵ�.
			//=========================================
			pclChar->bPersonalShopSwitch = true; 
			pclChar->bPremiumPersonalShop = pclinfo->clShopBanner.m_bPremium;
			pclChar->siShopMode			 = pclinfo->clShopBanner.m_siShopMode;
		

			pclinfo->clShopBanner.MakeBannerText(pclItemManager, pclChar->szPersonalShopText, pclChar->szPersonalShopTitle);

			SI16 BannerType = PERSONALSHOP_BANNER;

			if(pclChar->bPremiumPersonalShop)	
			{
				pclChar->pclDrawChat->Set(pclDrawChatSurface, pclChar->szPersonalShopText, true
					, PERSONALSHOP_BANNER_PREMIUM , pclChar->siShopMode, pclChar->szPersonalShopTitle);
			}
			else
			{
				pclChar->pclDrawChat->Set(pclDrawChatSurface, pclChar->szPersonalShopText, true
					, PERSONALSHOP_BANNER, pclChar->siShopMode);				
			}
			
		}
		else
		{
			pclChar->pclDrawChat->StopDraw();
			pclChar->bPersonalShopSwitch = false; 
			pclChar->bPremiumPersonalShop = false;
			StringCchCopy(pclChar->szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
			StringCchCopy(pclChar->szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));

		}
	}
}

// Ư���� ������� ���λ��� ������ �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONALSHOPDATA(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PersonalShopData* pclinfo = (cltGameMsgResponse_PersonalShopData*)pclMsg->cData;

	// ShopData�� �����Ѵ�.

	if( pclinfo->clShopData.m_siShopMode == PSHOP_MODE_SELL || pclinfo->clShopData.m_siShopMode == PSHOP_MODE_BUY  )
	{
		if( m_pDialog[ NMANUFACTURE_DLG ] )
			m_pDialog[ NMANUFACTURE_DLG ]->DeleteDialog();	

		if( m_pDialog[ NPERSONALSHOP_DLG ] == NULL )
			CreateInterface( NPERSONALSHOP_DLG );
		((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
		((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_bShopDataChanged = true;
		id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
		if(pclCM->IsValidID(id))
		{
			cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
			StringCchCopy(((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szShopBanner, MAX_PERSONAL_SHOP_TEXT_SIZE, pclChar->szPersonalShopText);
			((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->Show( pclinfo->siCharUnique, pclinfo->clShopData.m_siPersonID, pclinfo->clShopData.m_siShopMode, (TCHAR*)pclCM->CR[id]->GetName(), pclinfo->clShopData.m_szAccountID, pclChar->bPersonalShopSwitch );
		}
	}
	else if(pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM 
		|| pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
	{
		if ( IsCountrySwitch( Switch_Change_manufacture_request_interface )) 
		{
			if( m_pDialog[ NMANUFACTURE_NEW_DLG ] )
				m_pDialog[ NMANUFACTURE_NEW_DLG ]->DeleteDialog();

			if( m_pDialog[ NMANUFACTURE_NEW_DLG ] == NULL )
				CreateInterface( NMANUFACTURE_NEW_DLG );
			((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
			((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->m_bShopDataChanged = true;
			id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];

			if(pclCM->IsValidID(id))
			{
				cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
				StringCchCopy(((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->m_szShopBanner, MAX_PERSONAL_SHOP_TEXT_SIZE, pclChar->szPersonalShopText);
				((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->Show( pclinfo->siCharUnique, pclinfo->clShopData.m_siPersonID, pclinfo->clShopData.m_siShopMode, 
					(TCHAR*)pclCM->CR[id]->GetName(), pclinfo->clShopData.m_szAccountID, pclChar->bPersonalShopSwitch );
			}

		}
		else
		{
			if( m_pDialog[ NPERSONALSHOP_DLG ] )
				m_pDialog[ NPERSONALSHOP_DLG ]->DeleteDialog();

			if( m_pDialog[ NMANUFACTURE_DLG ] == NULL )
				CreateInterface( NMANUFACTURE_DLG );
			((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
			((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_bShopDataChanged = true;
			id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
			if(pclCM->IsValidID(id))
			{
				cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
				StringCchCopy(((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_szShopBanner, MAX_PERSONAL_SHOP_TEXT_SIZE, pclChar->szPersonalShopText);
				((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->Show( pclinfo->siCharUnique, pclinfo->clShopData.m_siPersonID, pclinfo->clShopData.m_siShopMode, 
					(TCHAR*)pclCM->CR[id]->GetName(), pclinfo->clShopData.m_szAccountID, pclChar->bPersonalShopSwitch );
			}
		}

	}
}
// ���λ����� ���� �ϴ°��� �����Ѵ�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_STARTPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_StartPersonalShop* pclinfo = (cltGameMsgResponse_StartPersonalShop*)pclMsg->cData;

	// ��ǳ���� �����ϵ��� �Ѵ�.
	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	// �ڱ��ڽſ� ���� ������� 
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];

		if(pclinfo->siResult > 0)	
		{
			pclChar->bPersonalShopSwitch = true;

			TCHAR* pTitle = GetTxtFromMgr(1343);
			TCHAR* pText	=	NULL	;
			// ����- ���� �Ƿ� �ϰ��� ������ �ٸ��� 
			if( pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM )// �����Ƿ�
			{
				pText = GetTxtFromMgr(40835);
			}
			else if( pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )	// �����Ƿ� 
			{
				pText = GetTxtFromMgr(40836);
			}
			else
			{
				pText = GetTxtFromMgr(1344);
			}		
            if(pclinfo->bPremium)
			{
				pText = GetTxtFromMgr(6631);
			}

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		}
		else if(pclinfo->siResult == 0)	
		{
			//=========================================
			// Personal Shop�� �����Ѵ�.
			//=========================================
			pclChar->bPersonalShopSwitch = false; 
			StringCchCopy(pclChar->szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
			StringCchCopy(pclChar->szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));

			TCHAR* pTitle = GetTxtFromMgr(1345);
			TCHAR* pText = GetTxtFromMgr(1346);

			if( pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM || pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
			{
				pText = GetTxtFromMgr(40871);
			}

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		}
		else if(pclinfo->siResult == -1)	
		{
			//=========================================
			// Personal Shop�� �����Ѵ�.
			//=========================================
			pclChar->bPersonalShopSwitch = false; 
			StringCchCopy(pclChar->szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
			StringCchCopy(pclChar->szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));

			TCHAR* pTitle = GetTxtFromMgr(1345);
			TCHAR* pText = GetTxtFromMgr(1347);
			if( pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM || pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
			{
				pText = GetTxtFromMgr(40872);
			}

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		}
		else if(pclinfo->siResult == -2)	
		{
			//=========================================
			// Personal Shop�� �����Ѵ�.
			//=========================================
			pclChar->bPersonalShopSwitch = false; 
			StringCchCopy(pclChar->szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
			StringCchCopy(pclChar->szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));

			TCHAR* pTitle = GetTxtFromMgr(1345);
			TCHAR* pText = GetTxtFromMgr(1348);

			if( pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM || pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
			{
				pText = GetTxtFromMgr(40873);
			}

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		}
		else if(pclinfo->siResult == -3)	
		{
			//=========================================
			// Personal Shop�� �����Ѵ�.
			//=========================================
			pclChar->bPersonalShopSwitch = false; 
			StringCchCopy(pclChar->szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
			StringCchCopy(pclChar->szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));

			TCHAR* pTitle = GetTxtFromMgr(1345);
			TCHAR* pText = GetTxtFromMgr(1349);

			if( pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM || pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
			{
				pText = GetTxtFromMgr(40874);
			}

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		}
		else if(pclinfo->siResult == -4)	
		{
			//=========================================
			// Personal Shop�� �����Ѵ�.
			//=========================================
			pclChar->bPersonalShopSwitch = false; 
			StringCchCopy(pclChar->szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
			StringCchCopy(pclChar->szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));

			TCHAR* pTitle = GetTxtFromMgr(1345);
			TCHAR* pText = GetTxtFromMgr(1350);
			
			if( pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM || pclinfo->m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
			{
				pText = GetTxtFromMgr(40875);
			}

			m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
		}
	}

}


// ���λ����� ������Ų��.
void cltClient::DoMsg_GAMEMSG_RESPONSE_STOPPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_StopPersonalShop* pclinfo = (cltGameMsgResponse_StopPersonalShop*)pclMsg->cData;

	// ��ǳ���� �����ϵ��� �Ѵ�.
	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	//
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];

		if(pclinfo->siResult > 0)
		{
			switch(pclinfo->siResult)
			{
			case 1:	// ����ڰ� ��������� 
				{
					if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ])))
					{
						if(id == 1)
						{
						}
						else if(pclinfo->siPersonID == ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_siShopperPersonID) // ���� ���� �ִ� â�� ���ٸ� 
						{		
							TCHAR* pTitle = GetTxtFromMgr(1351);
							TCHAR* pText = GetTxtFromMgr(1352);

							m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						}
					}
				}
				break;
			case 2:	// ������ �� �ȷ��� ���� ������ 
				{
					if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ])))
					{
						if(id == 1)
						{
							if(pclChar->siShopMode == PSHOP_MODE_SELL)
							{
								TCHAR* pText = GetTxtFromMgr(5766);

								//m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
								PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

								if((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ]==NULL)
								{
									CreateInterface( NPERSONALSHOP_POP_DLG);	
								}
								
								
								((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->Push(pText,5765);
								
							}
							if(pclChar->siShopMode == PSHOP_MODE_BUY)	
							{
								
								TCHAR* pText = GetTxtFromMgr(5768);

								PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

								if((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ]==NULL)
								{
									CreateInterface( NPERSONALSHOP_POP_DLG);	
							
								}
								
								((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->Push(pText,5767);
								
							}
						}
						else if(pclinfo->siPersonID == ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_siShopperPersonID) // ���� ���� �ִ� â�� ���ٸ� 
						{			
							if(pclChar->siShopMode == PSHOP_MODE_SELL)
							{
								//TCHAR* pTitle = GetTxtFromMgr(5767);
								TCHAR* pText = GetTxtFromMgr(5768);

								PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

								if((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ]==NULL)
								{
									CreateInterface( NPERSONALSHOP_POP_DLG);		
									
								}
								
								((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->Push(pText,5767);
							}
							if(pclChar->siShopMode == PSHOP_MODE_BUY)
							{

								//TCHAR* pTitle = GetTxtFromMgr(5765);
								TCHAR* pText = GetTxtFromMgr(5766);
								PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

								if((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ]==NULL)
								{
									CreateInterface( NPERSONALSHOP_POP_DLG);			
									
								}
								
								((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->Push(pText,5765);
								
							}
						}
					}
				}
				break;
			case 3: // ���̻� �����Ҽ� ��� ��������� 
				{
					if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ])))
					{
						if(id == 1)
						{
							if(pclChar->siShopMode == PSHOP_MODE_SELL)	
							{
								TCHAR* pTitle = GetTxtFromMgr(1351);
								TCHAR* pText = GetTxtFromMgr(1359);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							if(pclChar->siShopMode == PSHOP_MODE_BUY)
							{
								TCHAR* pTitle = GetTxtFromMgr(1351);
								TCHAR* pText = GetTxtFromMgr(1360);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
						}
						else if(pclinfo->siPersonID == ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_siShopperPersonID) // ���� ���� �ִ� â�� ���ٸ� 
						{			
							if(pclChar->siShopMode == PSHOP_MODE_SELL)
							{
								TCHAR* pTitle = GetTxtFromMgr(1351);
								TCHAR* pText = GetTxtFromMgr(1359);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							if(pclChar->siShopMode == PSHOP_MODE_BUY)
							{
								TCHAR* pTitle = GetTxtFromMgr(1351);
								TCHAR* pText = GetTxtFromMgr(1360);

								m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
						}
					}
				}
				break;
			}

			pclChar->pclDrawChat->StopDraw();
			//=========================================
			// Personal Shop�� �����Ѵ�.
			//=========================================
			pclChar->bPersonalShopSwitch = false; 
			pclChar->bPremiumPersonalShop = false;
			StringCchCopy(pclChar->szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
			StringCchCopy(pclChar->szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));

			if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ])))
			{
				// ���� ����� ������� â�� �ݴ´�.
				if(pclinfo->siPersonID == ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_siShopperPersonID)
				{
					if(((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->IsCreate())
					{
						m_pDialog[ NPERSONALSHOP_DLG ]->DeleteDialog();
					//	CreateInterface( NPERSONALSHOP_DLG );
					}
				}
			}
			if(IsCountrySwitch(Switch_Change_manufacture_request_interface) )	// ������ ���� �ϸ鼭 ����/���� �Ƿ� â�� �������� ���� ��Ų��
			{
				if (m_pDialog[ NMANUFACTURE_NEW_DLG ] != NULL )
				{
					if (m_pDialog[ NMANUFACTURE_NEW_DLG ]->IsCreate() )
					{
						m_pDialog[ NMANUFACTURE_NEW_DLG ]->DeleteDialog();
					}
				}
			}

			pclChar->siShopMode = 0;
		}
	}

}

// ���� ���ŵ� ���λ��� ��� ������ �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_UPDATEPERSONALSHOPBANNER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UpdatePersonalShopBanner* pclinfo = (cltGameMsgResponse_UpdatePersonalShopBanner*)pclMsg->cData;


	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];

		if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ])))
		{
			if(pclinfo->siResult == 0)	CreateInterface( NPERSONALSHOP_DLG );//((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->Hide();
		}

		/*
		if(pclinfo->siResult > 0)
		{
		//=========================================
		// Personal Shop�� �����Ѵ�.
		//=========================================
		pclChar->bPersonalShopSwitch = true; 
		pclChar->siShopMode			 = pclinfo->clShopBanner.m_siShopMode;
		pclinfo->clShopBanner.MakeBannerText(pclItemManager, pclChar->szPersonalShopText);

		pclChar->pclDrawChat->Set(pclDrawChatSurface, pclChar->szPersonalShopText, true, PERSONALSHOP_BANNER, pclChar->siShopMode);
		}
		else
		{
		pclChar->pclDrawChat->StopDraw();
		pclChar->bPersonalShopSwitch = false; 
		strcpy(pclChar->szPersonalShopText, TEXT(""));
		}
		*/
	}
}

// Ư���� ������� ���ŵ� ���λ��� ������ �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UpdatePersonalShopData* pclinfo = (cltGameMsgResponse_UpdatePersonalShopData*)pclMsg->cData;

	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];

	TCHAR itemname[128] = TEXT("NULL") ;
	if(pclinfo->siItemUnique)
	{
		cltItem clitem;
		clitem.Init();
		clitem.siUnique = pclinfo->siItemUnique;
		clitem.siItemNum= pclinfo->siItemNum;
		if(clitem.GetFullName(pclItemManager, itemname, 128) == false) StringCchCopy(itemname, 128, TEXT(""));
	}



	if ( g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if(pclCM->IsValidID(id))
		{
			if( pclinfo->clShopData.m_siShopMode == PSHOP_MODE_SELL ||  pclinfo->clShopData.m_siShopMode == PSHOP_MODE_BUY )
			{
				if( m_pDialog[ NPERSONALSHOP_DLG ] == NULL)
					CreateInterface( NPERSONALSHOP_DLG );

				((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
				((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_bShopDataChanged = true;
				id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];

				cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
				StringCchCopy(((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szShopBanner, MAX_PERSONAL_SHOP_TEXT_SIZE, pclChar->szPersonalShopText);
				((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->Show( pclinfo->siCharUnique, pclinfo->clShopData.m_siPersonID, pclinfo->clShopData.m_siShopMode, (TCHAR*)pclCM->CR[id]->GetName(), pclinfo->clShopData.m_szAccountID, pclChar->bPersonalShopSwitch );


				// ���� ����� ������� ShopData�� �����Ѵ�.
				if(pclinfo->clShopData.m_siPersonID == ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_siShopperPersonID)
				{
					// ���� ������ �̻��ϸ� �ݾƹ�����. => ���ֹ�����.
					if(pclinfo->clShopData.m_siShopMode == PSHOP_MODE_NONE)
					{
						//((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->Hide();
						if(((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->IsCreate())
							CreateInterface( NPERSONALSHOP_DLG );
					}
					else
					{


						((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
						((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_bShopDataChanged = true;

						pclChar->clMyShopData.Set(&pclinfo->clShopData);

					}

					// ���� ����, �Ǹ� ���� ������Ʈ
					
					// ���� �Ƿ� �����̸� �޽��� ���� �׳ɳ���
					if( pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM || pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
						return;
		

					if(pclinfo->bBuyer)
					{
						TCHAR szMoney[128]= { '\0', };
						g_JYLibFunction.SetNumUnit( pclinfo->siItemCoast, szMoney, sizeof(szMoney) );

						NTCHARString128 strMessage( GetTxtFromMgr(5763) );

						strMessage.Replace( TEXT("#itemname#"), itemname );
						strMessage.Replace( TEXT("#itemnum#"), SI32ToString(pclinfo->siItemNum) );
						strMessage.Replace( TEXT("#money#"), szMoney );

						{
							PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

							if((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ]==NULL)
							{
								CreateInterface( NPERSONALSHOP_POP_DLG);
								((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->MoveDialog(5,20);
							}
							//((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->SetTitle(pTitle);
							
							((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->Push(strMessage,5764);
						}
					}
					else
					{
						TCHAR szMoney[128]= { '\0', };
						g_JYLibFunction.SetNumUnit( pclinfo->siItemCoast, szMoney, sizeof(szMoney) );

						NTCHARString128 strMessage( GetTxtFromMgr(5761) );
						
						strMessage.Replace( TEXT("#itemname#"), itemname );
						strMessage.Replace( TEXT("#itemnum#"), SI32ToString(pclinfo->siItemNum) );
						strMessage.Replace( TEXT("#money#"), szMoney );

						{
							PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

							if((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ]==NULL)
							{
								CreateInterface( NPERSONALSHOP_POP_DLG);	
								((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->MoveDialog(5,20);
							}
							((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->Push(strMessage,5762);
						}

						//m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
					}

				}
			}
			else if( pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM )
			{
				if(IsCountrySwitch(Switch_Change_manufacture_request_interface) )
				{	
					if( pclinfo->clShopData.m_clItem[0].siItemNum	>	0	)
					{
						if( m_pDialog[ NMANUFACTURE_NEW_DLG ] == NULL)
						{
							CreateInterface( NMANUFACTURE_NEW_DLG );						
						}

						((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
						((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->RefreshShowData();
						id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];

						cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
						StringCchCopy(((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->m_szShopBanner, MAX_PERSONAL_SHOP_TEXT_SIZE, pclChar->szPersonalShopText);
						((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->Show( pclinfo->siCharUnique, pclinfo->clShopData.m_siPersonID, pclinfo->clShopData.m_siShopMode, 
							(TCHAR*)pclCM->CR[id]->GetName(), pclinfo->clShopData.m_szAccountID, pclChar->bPersonalShopSwitch );
						// ���� ����� ������� ShopData�� �����Ѵ�.
						if(pclinfo->clShopData.m_siPersonID == ((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->m_siShopperPersonID)
						{
							// ���� ������ �̻��ϸ� �ݾƹ�����. => ���ֹ�����.
							if(pclinfo->clShopData.m_siShopMode == PSHOP_MODE_NONE)
							{
								if(((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->IsCreate())
									CreateInterface( NMANUFACTURE_NEW_DLG );
							}
							else
							{
								((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
								((CNManufactureDlg_New*)(m_pDialog[ NMANUFACTURE_NEW_DLG ]))->RefreshShowData();
								pclChar->clMyShopData.Set(&pclinfo->clShopData);
							}
							// ���� ����, �Ǹ� ���� ������Ʈ
						}

					}
				}
				else
				{
					if( m_pDialog[ NMANUFACTURE_DLG ] == NULL)
						CreateInterface( NMANUFACTURE_DLG );

					((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
					((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->RefreshShowData();
					id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];

					cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
					StringCchCopy(((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_szShopBanner, MAX_PERSONAL_SHOP_TEXT_SIZE, pclChar->szPersonalShopText);
					((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->Show( pclinfo->siCharUnique, pclinfo->clShopData.m_siPersonID, pclinfo->clShopData.m_siShopMode, (TCHAR*)pclCM->CR[id]->GetName(), pclinfo->clShopData.m_szAccountID, pclChar->bPersonalShopSwitch );


					// ���� ����� ������� ShopData�� �����Ѵ�.
					if(pclinfo->clShopData.m_siPersonID == ((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_siShopperPersonID)
					{
						// ���� ������ �̻��ϸ� �ݾƹ�����. => ���ֹ�����.
						if(pclinfo->clShopData.m_siShopMode == PSHOP_MODE_NONE)
						{
							//((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->Hide();
							if(((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->IsCreate())
								CreateInterface( NMANUFACTURE_DLG );
						}
						else
						{
							((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_clShopData.Set(&pclinfo->clShopData);
							((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->RefreshShowData();
							pclChar->clMyShopData.Set(&pclinfo->clShopData);
						}

						// ���� ����, �Ǹ� ���� ������Ʈ
					}

				}
			}
			else if( pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM_WANT ) //
			{
				if(IsCountrySwitch(Switch_Change_manufacture_request_interface) )
				{	
					cltClient *pclclient = ( cltClient * )pclClient;

					cltGameMsgRequest_StopPersonalShop clshopdata( pclinfo->siCharUnique);
					cltMsg clMsg( GAMEMSG_REQUEST_STOPPERSONALSHOP, sizeof( clshopdata ), (BYTE*)&clshopdata );
					
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
				else
				{
					// �����ڵ� �ȿ������� �Ϸ� ������ �ȵ� 
				}
			}
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BUYPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BuyPersonalShop* pclinfo = (cltGameMsgResponse_BuyPersonalShop*)pclMsg->cData;

	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
		TCHAR itemname[128] = TEXT("") ;
		if(pclinfo->siitemUnique)
		{
			cltItem clitem;
			clitem.Init();
			clitem.siUnique = pclinfo->siitemUnique;
			clitem.siItemNum= pclinfo->siItemNum;
			if(clitem.GetFullName(pclItemManager, itemname, 128) == false) StringCchCopy(itemname, 128, TEXT(""));
		}

		if(pclChar)
		{
			TCHAR buffer[128];			
			TCHAR* pText = NULL;

			if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ])))
			{
				TCHAR item[128]=TEXT("");
				TCHAR num[128]=TEXT("");
				StringCchPrintf(num, 128, TEXT("%d"),pclinfo->siItemNum);

				switch(pclinfo->siResult )
				{
				case BUYPERSONALSHOP_SUCCESS_BUY:			pText = GetTxtFromMgr(1361); Nsprintf(buffer, pText, TEXT("#item#"), itemname, TEXT("#num#"), num, NULL);	break;
				case BUYPERSONALSHOP_FAIL_UNKNOWN:			pText = GetTxtFromMgr(1362); StringCchPrintf(buffer, 128, pText);										break;
				case BUYPERSONALSHOP_FAIL_SHOPPERSTATUS:	pText = GetTxtFromMgr(1363); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);break;
				case BUYPERSONALSHOP_FAIL_BUYERSTATUS:		pText = GetTxtFromMgr(1364); StringCchPrintf(buffer, 128, pText);										break;	
				case BUYPERSONALSHOP_FAIL_SHOWCASESTATUS:	pText = GetTxtFromMgr(1365); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);	break;
				case BUYPERSONALSHOP_FAIL_BUY_NOITEM:		pText = GetTxtFromMgr(1366); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);	break;	
				case BUYPERSONALSHOP_FAIL_BUY_NOMONEY:		pText = GetTxtFromMgr(1367); StringCchPrintf(buffer, 128, pText);			break;
				case BUYPERSONALSHOP_FAIL_BUY_NOINVSPACE:	pText = GetTxtFromMgr(1368); StringCchPrintf(buffer, 128, pText);		break;	
				default:									StringCchPrintf(buffer, 128, TEXT("")); break;
				}
			}

			//TODO: ������ ���� ���� �޽��� ��

			//TCHAR buffer[255];


		}
	}
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_SELLPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SellPersonalShop* pclinfo = (cltGameMsgResponse_SellPersonalShop*)pclMsg->cData;

	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
		TCHAR itemname[128] = TEXT("") ;
		if(pclinfo->siitemUnique)
		{
			cltItem clitem;
			clitem.Init();
			clitem.siUnique = pclinfo->siitemUnique;
			clitem.siItemNum= pclinfo->siItemNum;
			if(clitem.GetFullName(pclItemManager, itemname, 128) == false) StringCchCopy(itemname, 128, TEXT(""));
		}

		if(pclChar)
		{
			TCHAR buffer[128];
			TCHAR* pText = NULL;

			if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ])))
			{
				switch(pclinfo->siResult )
				{
				case SELLPERSONALSHOP_SUCCESS_SELL:			
					{
						pText = GetTxtFromMgr(/*1361*/3771); 
						TCHAR Nbuffer[512] = TEXT("");

						TCHAR num[128] = TEXT("") ;

						StringCchPrintf( num, 128, TEXT("%d"), pclinfo->siItemNum );
						Nsprintf( buffer,pText, TEXT("item"),  itemname, TEXT("num"), num, NULL );
						

					}
					break;
				case SELLPERSONALSHOP_FAIL_UNKNOWN:			pText = GetTxtFromMgr(1362); StringCchPrintf(buffer, 128, pText);										break;
				case SELLPERSONALSHOP_FAIL_SHOPPERSTATUS:	pText = GetTxtFromMgr(1363); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);break;
				case SELLPERSONALSHOP_FAIL_SELLERSTATUS:	pText = GetTxtFromMgr(1364); StringCchPrintf(buffer, 128, pText);										break;	
				case SELLPERSONALSHOP_FAIL_SHOWCASESTATUS:	pText = GetTxtFromMgr(1365); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);	break;
				case SELLPERSONALSHOP_FAIL_SELL_NOITEM:		pText = GetTxtFromMgr(1366); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);	break;	
				case SELLPERSONALSHOP_FAIL_SELL_NOMONEY:	pText = GetTxtFromMgr(1367); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);		break;
				case SELLPERSONALSHOP_FAIL_SELL_NOINVSPACE:	pText = GetTxtFromMgr(1368); StringCchPrintf(buffer, 128, pText, ((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->m_szCharName);	break;	
				default:									StringCchPrintf(buffer, 128, TEXT("")); break;
				}

				((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->DisplayMessage(pclinfo->siResult, buffer);
			}
		}
	}
}



void cltClient::DoMsg_GAMEMSG_RESPONSE_SEARCHPERSONALSHOPITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SearchPersonalShopItem* pclinfo = (cltGameMsgResponse_SearchPersonalShopItem*)pclMsg->cData;

	if(pclCM->IsValidID(1))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[1];
		if(pclinfo->siResult > 0)
		{
			if ( g_SoundOnOffDlg.m_bFullScreenMode )
			{
				// Data�� �����ϰ� Data�� ���ŵǾ��ٴ� ���� �˷��� 
				((CNPersonalShopSearchDlg*)(m_pDialog[ NPERSONALSHOPSEARCH_DLG ]))->m_clSearhShopData.Set(&pclinfo->clSearchShopData);
				((CNPersonalShopSearchDlg*)(m_pDialog[ NPERSONALSHOPSEARCH_DLG ]))->m_bShopDataChanged = true;
			}
		}
	}
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_SEARCHMANUFACTURE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SearchManufacture* pclinfo = (cltGameMsgResponse_SearchManufacture*)pclMsg->cData;

	if(pclCM->IsValidID(1))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[1];
		if(pclinfo->siResult > 0)
		{
			if ( g_SoundOnOffDlg.m_bFullScreenMode )
			{
				// Data�� �����ϰ� Data�� ���ŵǾ��ٴ� ���� �˷��� 
				((CNManufactureSearchDlg*)(m_pDialog[ MANUFACTURESEARCH_DLG ]))->m_clSearhShopData.Set(&pclinfo->clSearchShopData);
				((CNManufactureSearchDlg*)(m_pDialog[ MANUFACTURESEARCH_DLG ]))->m_bShopDataChanged = true;
			}
		}
	}
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_MAKEPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
 	cltGameMsgResponse_MakePersonalShop* pclinfo = (cltGameMsgResponse_MakePersonalShop *)pclMsg->cData;
	id = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
		TCHAR itemname[128] = TEXT("") ;
		if(pclinfo->siitemUnique)
		{
			cltItem clitem;
			clitem.Init();
			clitem.siUnique = pclinfo->siitemUnique;
			clitem.siItemNum= pclinfo->siItemNum;
			if(clitem.GetFullName(pclItemManager, itemname, 128) == false) StringCchCopy(itemname, 128, TEXT(""));
		}

		if(pclChar)
		{
			TCHAR buffer[128];
			TCHAR* pText = NULL;
			TCHAR* pTitle =	NULL	;
			if ( pclClient->IsCountrySwitch( Switch_Change_manufacture_request_interface ) ) //���� �������̽� ������ ���� ����â�� ������ ���� �׷��� �޼��� â���� ���� 
			{
				pTitle = GetTxtFromMgr(416);	// �⺻������ ���� �޼��� 

				switch( pclinfo->siResult  ) 
				{
				case MAKEPERSONALSHOP_SUCCESS_MAKE :
					{
						pTitle	=	GetTxtFromMgr(389)	;//[%s] %d���� ���۵Ǿ����ϴ�.
						pText	=	GetTxtFromMgr(1369); 
						StringCchPrintf(buffer, 128, pText,itemname, pclinfo->siItemNum);
					}
					break;
				case MAKEPERSONALSHOP_FAIL_UNKNOWN://��ǰ�� �������� ���Ͽ����ϴ�.
					{
						pText = GetTxtFromMgr(1370); 
						StringCchPrintf(buffer, 128, pText);
					}break;
				case MAKEPERSONALSHOP_FAIL_SHOPPERSTATUS:// ����/���� �Ƿ����� �Ƿ������� ����Ǿ����ϴ�
				case MAKEPERSONALSHOP_FAIL_SHOWCASESTATUS:
					{
						pText = GetTxtFromMgr(40844); 
						StringCchPrintf(buffer, 128, pText);			

					}break;
				case MAKEPERSONALSHOP_FAIL_MAKERSTATUS:
					{
						pText = GetTxtFromMgr(1371); 
						StringCchPrintf(buffer, 128, pText);

					}break;
				case MAKEPERSONALSHOP_FAIL_MAKE_NOITEM:
					{
						pText = GetTxtFromMgr(40845); 
						StringCchPrintf(buffer, 128, pText);
					}break;
				case MAKEPERSONALSHOP_FAIL_MAKE_NOMONEY:
					{
						pText = GetTxtFromMgr(40846); 
						StringCchPrintf(buffer, 128, pText);
					}break;
				case MAKEPERSONALSHOP_FAIL_MAKE_NEEDABILITY:
					{
						pText = GetTxtFromMgr(40847); 
						StringCchPrintf(buffer, 128, pText);
					}break;
				case MAKEPERSONALSHOP_FAIL_NOWMAKINGSTATUS:
					{
						pText = GetTxtFromMgr(40839); 
						StringCchPrintf(buffer, 128, pText);

					}break;

				}
				m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle,buffer)	;
			}
			else
			{
				if ( g_SoundOnOffDlg.m_bFullScreenMode && ((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ])))
				{
					switch(pclinfo->siResult )
					{
					case MAKEPERSONALSHOP_SUCCESS_MAKE:			pText = GetTxtFromMgr(1369); StringCchPrintf(buffer, 128, pText,				itemname, pclinfo->siItemNum);		break;
					case MAKEPERSONALSHOP_FAIL_UNKNOWN:			pText = GetTxtFromMgr(1370); StringCchPrintf(buffer, 128, pText);												break;
					case MAKEPERSONALSHOP_FAIL_SHOPPERSTATUS:	pText = GetTxtFromMgr(1363); StringCchPrintf(buffer, 128, pText,		((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_szCharName);	break;
					case MAKEPERSONALSHOP_FAIL_MAKERSTATUS:		pText = GetTxtFromMgr(1371); StringCchPrintf(buffer, 128, pText);											break;	
					case MAKEPERSONALSHOP_FAIL_SHOWCASESTATUS:	pText = GetTxtFromMgr(1365); StringCchPrintf(buffer, 128, pText,((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_szCharName);	break;
					case MAKEPERSONALSHOP_FAIL_MAKE_NOITEM:		pText = GetTxtFromMgr(1372); StringCchPrintf(buffer, 128, pText, ((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->m_szCharName);	break;	
					case MAKEPERSONALSHOP_FAIL_MAKE_NOMONEY:	pText = GetTxtFromMgr(1373); StringCchPrintf(buffer, 128, pText);		break;
					case MAKEPERSONALSHOP_FAIL_MAKE_NEEDABILITY:pText = GetTxtFromMgr(1374); StringCchPrintf(buffer, 128, pText);	break;					
					default:									StringCchPrintf(buffer, 128, TEXT("")); break;
					}				
					//m_pDialog[NOTIFYMSG_DLG]->SetText()
					bool bSuccess = true;

					if(pclinfo->siResult < 1)
					{
						bSuccess = false;
					}				

					((CNManufactureDlg*)(m_pDialog[ NMANUFACTURE_DLG ]))->DisplayMessage(bSuccess,buffer);
					//((CNPersonalShopDlg*)(m_pDialog[ NPERSONALSHOP_DLG ]))->DisplayMessage(pclinfo->siResult, buffer);
				}
				else
				{
					if(pclinfo->siResult ==MAKEPERSONALSHOP_FAIL_NOWMAKINGSTATUS )// �����Ƿڽô� ���̾�αװ� ������ �ʴ� . �׷��Ƿ� �޼����� ����ش� 
					{
						pTitle = GetTxtFromMgr(416);
						pText = GetTxtFromMgr(40839); 
						m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle,pText)	;
					}
				}
			}
		}
	}
}


