#include "..\..\Client\Client.h"

#include "..\..\Client\Music\Music.h"

#include "..\Map\Map.h"
#include "Char\CharManager\CharManager.h"
#include "Char/CharAni/CharAni.h"

#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "Item/ItemCommon/ItemUnit.h"

#include "../Client/ninterface/NBlackWarReformDlg/NBlackWarReformRunDlg.h"
#include "../Client/ninterface/NBlackWarReformDlg/NBlackWarReformRewardDlg.h"

#include "../common/Main.h"

extern cltCommonLogic* pclClient;
bool bShowWarMessageSwitch;

cltMessage::cltMessage()
{
	init();
}

cltMessage::~cltMessage()
{
	if(hFont)
	{
		DeleteObject(hFont);
	}

}

void cltMessage::init()
{
	MessageIndex		 = 0;
	
	//[����] �������� �޽��� ��� ��ġ ���� ���� �ʱ�ȭ. => 2008-6-2
	PersonalMessageIndex = 0;
	ZeroMemory(PersonalMessage, sizeof(PersonalMessage));
	
	cltClient *pclclient = (cltClient *)pclClient;

	if ( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
			hFont =	CreateFont(12, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("����"));
			m_hFontBattleRoyal = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("����"));
		}
		else {
			if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
				hFont =	CreateFont(12, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("����"));
				m_hFontBattleRoyal = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("����"));
			}
			else {
				hFont =	CreateFont(12, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("����"));
				m_hFontBattleRoyal =	CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("����"));
			}			
		}
		
	}
	else
	{
		if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
			hFont =	CreateFont(13, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("Tahoma"));
			m_hFontBattleRoyal =	CreateFont(29, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("Tahoma"));
		}
		else {
			hFont =	CreateFont(13, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("Tahoma"));
			m_hFontBattleRoyal =	CreateFont(29, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("Tahoma"));
		}
		
	}

	
	//hFont = 	CreateFont(11, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����"));
	if(hFont == NULL)
	{
		MsgBox(TEXT("dfjiw"), TEXT("dfjwkd"));
	}
	if(m_hFontBattleRoyal == NULL)
	{
		MsgBox(TEXT("dfjiw"), TEXT("dfjwkd"));
	}

	dwLastWarMsgFrame	= 0;

	StringCchCopy(szWarMsg, MAX_WAR_MSG_SIZE, TEXT(""));

	// ������ �޽��� 
	StringCchCopy(szHuntMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bHuntMsgSwitch			= false;
	dwLastHuntMsgClock		= 0;

	// ���� �޽��� 
	StringCchCopy(szPrisonMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bPrisonMsgSwitch		= false;
	dwLastPrisonMsgClock	= 0;

	// �Ұ��縮 ��� �̺�Ʈ  �޽��� 
	StringCchCopy(szHuntEventMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bMofuMofuEventMsgSwitch		= false;
	dwLastMofuMofuEventMsgClock	= 0;

	// ���ĸ��� �̺�Ʈ  �޽��� 
	StringCchCopy(szMofuMofuEventMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bHuntEventMsgSwitch		= false;
	dwLastHuntEventMsgClock	= 0;
	

	// ���� ���� ��� �̺�Ʈ  �޽��� 
	StringCchCopy(szGoguEventMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bGoguEventMsgSwitch		= false;
	dwLastGoguEventMsgClock	= 0;

	// ����ī�� �̺�Ʈ  �޽��� 
	StringCchCopy(szOsakaEventMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bOsakaEventMsgSwitch		= false;
	dwLastOsakaEventMsgClock	= 0;

	// ��ȭ�� �̺�Ʈ  �޽��� 
	StringCchCopy(szKanghwadoEventMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bKanghwadoEventMsgSwitch		= false;
	dwLastKanghwadoEventMsgClock	= 0;

	// Daily Quest �޽��� 
	StringCchCopy ( szDailyQuestMsg, MAX_MESSAGE_LENGTH, TEXT("") );
	bDailyQuestMsgSwitch		= false;
	dwLastDailyQuestMsgClock	= 0;

	// ���� �ֹ� ä�� �޽���. 
	StringCchCopy(szVillageChatMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bVillageChatMsgSwitch		= false;
	dwLastVillageChatMsgClock	= 0;

	// �ν��Ͻ� ���� �޽���
	StringCchCopy(szInstanceMapMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bInstanceMapMsgSwitch		= false;
	dwLastInstanceMapMsgClock	= 0;

	// ��Ʋ�ξ�
	StringCchCopy(szBattleRoyalGameModeMsg, MAX_MESSAGE_LENGTH, TEXT(""));
	bBattleRoyalGameModeMsgSwitch		= false;
	dwLastBattleRoyalGameModeMsgClock	= 0;

	// ��Ƽ����Ʈ
	StringCchCopy(m_szPartyQuestMessage[0], MAX_MESSAGE_LENGTH*2, TEXT(""));
	m_bPartyQuestGameModeMsgSwitch		= false;
	m_dwLastPartyQuestGameModeMsgClock	= 0;

	// ����Ʈ ���� �޼���
	for( SI32 i=0; i<MAX_QUEST_TYPE ; i++ )
	{
		StringCchCopy(szCurQuestInfoMsgBuffer[i], MAX_MESSAGE_LENGTH, TEXT(""));
		StringCchCopy(szQuestPrintBuffer[i], MAX_MESSAGE_LENGTH, TEXT(""));
		dwCurQuestInfoMsgClock[i] = 0;
		bQuestClearSwitch[i]= false;
	}
	bCurQuestInfoMsgSwitch = false;
	bFullscreen	=	FALSE	;
	GetFullScreenInFile( &bFullscreen)	;
}

void cltMessage::SetPersonalMsg(TCHAR* szmessage)
{
	if(szmessage == NULL)return ;

	if(PersonalMessageIndex < MAX_PERSONAL_MESSAGE_NUMBER)
	{
		if(PersonalMessageIndex < 0 || PersonalMessageIndex >= MAX_PERSONAL_MESSAGE_NUMBER)
		{
			MsgBox(TEXT("SetMsg"), TEXT("ZZZ:%d"), MessageIndex);
		}
		else
		{
			if(lstrlen(szmessage) > MAX_MESSAGE_LENGTH-1)
			{
				MsgBox(TEXT("SetMsg"), TEXT("SSSS:%d"), lstrlen(szmessage));
			}
			else
			{
				MStrCpy(PersonalMessage[PersonalMessageIndex], szmessage, MAX_MESSAGE_LENGTH );
				PersonalMessageDelay = MAX_MESSAGE_DELAY;
				PersonalMessageIndex++;
			}
		}
	}
	else
	{
		PersonalScroll();
		if(PersonalMessageIndex < 0 || PersonalMessageIndex >= MAX_PERSONAL_MESSAGE_NUMBER)
		{
			MsgBox(TEXT("SetPersonalMsg()"), TEXT("777777"));
		}
		else
		{
			MStrCpy(PersonalMessage[PersonalMessageIndex], szmessage, MAX_MESSAGE_LENGTH );
			PersonalMessageDelay = MAX_MESSAGE_DELAY;
			PersonalMessageIndex++;
		}
	}
}

void cltMessage::SetMsg(TCHAR* szmessage, SI32 sieffect, COLORREF rgb, COLORREF shadowrgb)
{

	if(szmessage == NULL)return ;

	if(MessageIndex < MAX_MESSAGE_NUMBER)
	{
		if(MessageIndex<0 || MessageIndex>=MAX_MESSAGE_NUMBER)
		{
			MsgBox(TEXT("SetMsg"), TEXT("abc:%d"), MessageIndex);
		}
		else
		{
			if(lstrlen(szmessage) > MAX_MESSAGE_LENGTH-1)
			{
				MsgBox(TEXT("SetMsg"), TEXT("def:%d"), lstrlen(szmessage));
			}
			else
			{
			   MStrCpy(Message[MessageIndex], szmessage, MAX_MESSAGE_LENGTH );
			   MessageColor[MessageIndex]	=	rgb;
			   MessageShdowColor[MessageIndex]	= shadowrgb;
	           MessageDelay					=	MAX_MESSAGE_DELAY;
	           MessageIndex++;
			}
		}
	}
	else
	{
		Scroll();
		if(MessageIndex < 0 || MessageIndex >= MAX_MESSAGE_NUMBER)
		{
			MsgBox(TEXT("SetMsg()"), TEXT("478932"));
		}
		else
		{
			MStrCpy(Message[MessageIndex], szmessage, MAX_MESSAGE_LENGTH );
			MessageColor[MessageIndex] = rgb;
			MessageShdowColor[MessageIndex]	= shadowrgb;
			MessageDelay = MAX_MESSAGE_DELAY;
			MessageIndex++;
		}
	}
}

void cltMessage::Scroll()
{
	int i;

	for(i=0;i<MessageIndex;i++)
	{
		if(i>0)
		{
           StringCchCopy(Message[i-1], 256, Message[i]);
		   MessageColor[i-1] = MessageColor[i];
		   MessageShdowColor[i - 1]	= MessageShdowColor[i];

		}
    }
	if(MessageIndex>0)MessageIndex--;

}


void cltMessage::PersonalScroll()
{
	int i;

	for(i=0; i < PersonalMessageIndex; i++)
	{
		if(i > 0)
		{
			StringCchCopy(PersonalMessage[i-1], 256, PersonalMessage[i]);
		}
	}
	if(PersonalMessageIndex > 0)
		PersonalMessageIndex--;

}

void cltMessage::Show(cltClient* pclclient, SI32 main_message_start_x, SI32 main_message_start_y, LPDIRECTDRAWSURFACE7 surface, SI32 rx, SI32 ry)
{
	int i;
	SHORT index=0;
	HDC hdc;
	HDC hdcBattleRoyal;
	TCHAR* text=NULL;

	// ������忡���� �޽����� �������� �ʴ´�. 
	if(pclclient->GameMode == GAMEMODE_CLIENT)
	{
		if(pclclient->bWatchModeSwitch == true)
		{
			return ;
		}
	}
	// ��ũ�ѵǴ� �޽����� ó�� 

	  if(MessageDelay>0)
	  {
		  MessageDelay--;
		  if(MessageDelay==0)
		  {
			  Scroll();
			  MessageDelay=MAX_MESSAGE_DELAY;
		  }
	  }

	  if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
	  {
			if(PersonalMessageDelay > 0)
			{
				PersonalMessageDelay--;
				if(PersonalMessageDelay == 0)
				{
					PersonalScroll();
					PersonalMessageDelay = MAX_MESSAGE_DELAY;
				}
			}
	  }

	  if(surface->GetDC(&hdcBattleRoyal)==DD_OK)
	  {
		  HFONT hOldFontBattleRoyal = (HFONT)SelectObject(hdcBattleRoyal, m_hFontBattleRoyal); 
		  SetBkMode(hdcBattleRoyal, TRANSPARENT);
		  ShowBattleRoyalGameModeMessage(hdcBattleRoyal, rx, ry); 
		
		  SelectObject( hdcBattleRoyal, hOldFontBattleRoyal );
		  surface->ReleaseDC(hdcBattleRoyal);
	  }
	  
	  if(surface->GetDC(&hdc)==DD_OK)
	  {
		  HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
		  SetBkMode(hdc, TRANSPARENT);
		  
		  if(ShowPrisonMessage(hdc, rx, ry) == false)
		  {
			  // ������ �޽����� ǥ���Ѵ�. 
			  ShowHuntMessage(hdc, rx, ry);
		  }

		  if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
		  {
			  if ( bFullscreen == TRUE ) 
			  {

				  ShowPersonalMsg(hdc, rx - 40 , ry );//Ǯ��ũ���ϰ�� �����α��� �ణ �̵��Ѵ�.
			  }
			  else
			  {
				  ShowPersonalMsg(hdc, rx, ry);
			  }		  	  
		  }
          
		  // �Ұ��縮 ��� �̺�Ʈ �޽����� ǥ���Ѵ�. 
		  ShowHuntEventMessage(hdc, rx, ry);

		  // ���ĸ��� �̺�Ʈ �޽����� ǥ���Ѵ�. 
		  ShowMofuMofuEventMessage(hdc, rx, ry);

		  // ���� ���� ��� �̺�Ʈ �޽����� ǥ���Ѵ�. 
		  ShowGoguEventMessage(hdc, rx, ry);

		  // ����ī�� �̺�Ʈ �޽����� ǥ���Ѵ�. 
		  ShowOsakaEventMessage(hdc, rx, ry);

		  // ��ȭ�� �̺�Ʈ �޽����� ǥ���Ѵ�. 
		  ShowKanghwadoEventMessage(hdc, rx, ry);


		  // Daily Quest �޽����� ǥ���Ѵ�.
		  ShowDailyQuestMessage(hdc, rx, ry);

		  // �ֹ� ä�� �޽����� ǥ���Ѵ�.
		  // ShowVillageChatMessage(hdc, rx, ry);

		  // ���� �޽����� ǥ���Ѵ�. 
		  ShowWarMessage(hdc, rx, ry);

		  ShowInstanceMapMsg(hdc,rx,ry);

		  // ��Ƽ����Ʈ �޼���
		  ShowPartyQuestMsg(hdc,rx,ry);

		  if(MessageIndex > 0)
		  {
			  for(i=0;i<MessageIndex;i++)
			  {	
								  
				  // �׸��� ���. 
				 // SetTextColor( hdc, MessageShdowColor[i]);
				 // TextOut(hdc, main_message_start_x + rx+ 1, main_message_start_y + i*20 + ry + 1, 
					//  Message[i], lstrlen(Message[i]));
				  
				  // �� �ؽ�Ʈ ���. 
				  SetTextColor( hdc, MessageColor[i]);				
				  DrawMultyColorText( hdc, main_message_start_x + rx , 
 					  main_message_start_y + i*20 + ry, Message[i] ,MessageShdowColor[i] );
				  
			  }
		  }

		  //cyj ����Ʈ ��Ȳ �Լ� �ϴ� ����(�Ϻ���)
		  if( pclClient->siServiceArea != ConstServiceArea_Japan )
			  ShowCurQuestInfo(hdc, rx, ry);
			

		  // ȭ�� ��ǥ�� ����Ѵ�. 
#ifdef _DEBUG
		  TCHAR buffer[256];
		  SI32 x = ((cltClient*)pclClient)->siClientScreenXsize - 320 + rx;
		  SI32 y = 70 + ry;

		  SetTextColor( hdc, RGB(0, 0, 0));
		  StringCchPrintf(buffer, 256, TEXT("(%d %d)"),
			  pclclient->GetScreenMouseX(), pclclient->GetScreenMouseY()
			  );

		  TextOut(hdc, x, y, buffer, lstrlen(buffer));
		  // �޸� ��뷮ǥ��
		  StringCchPrintf( buffer, 256, TEXT("LoadedTileSetSize : %dKB"), pclClient->pclTileManager->siLoadedTileSetImageSize / 1024 );
		  TextOut(hdc, rx + 100, ry + 340, buffer, lstrlen(buffer)  );
		  StringCchPrintf( buffer, 256, TEXT("LoadedFOSize : %dKB"), pclClient->pclFieldObjectManager->siLoadedSize / 1024 );
		  TextOut(hdc, rx + 100, ry + 355, buffer, lstrlen(buffer)  );
		  StringCchPrintf( buffer, 256, TEXT("CharAniSize : %dKB"), cltCharAnimationManager::siLodedSize/1024 );
		  TextOut(hdc, rx + 100, ry + 370, buffer, lstrlen(buffer)  );

#endif


		  SelectObject( hdc, hOldFont );
		  surface->ReleaseDC(hdc);
	  }

	  // ���� ������ ǥ���Ѵ�. 
	  ShowWarKill(surface, rx, ry);

}


//----------------------------------------------
// �پ��� ���� �ڵ尡 �� ���ڿ��� ����Ѵ�
//----------------------------------------------
void cltMessage::DrawMultyColorText(HDC hdc, SI32 rx , SI32 ry, TCHAR * szmessage , COLORREF shadowrgb )
{

	if( szmessage == NULL ) return;

	SI16 StartPos = 0;  // ���ڿ��� ���� ��ġ
	SI16 Counter = 0;  
	SI16 CurrentDrawXPos = rx;
	SI16 CurrentDrawYPos = ry+50;// ���ο� �������̽� �������� 50��ŭ ���ȴ� show�Լ� �ҷ����� �ٲ��� �ʴ´�.

	for (SI16 i = StartPos; i <  (SI16)(_tcslen( szmessage )) ; i++ )
	{
		if ( szmessage[ i ] == '<' )
		{  

 			if ( Counter > 0 )
			{	
				SI32 oldColor =	SetTextColor( hdc, shadowrgb );
				TextOut( hdc, CurrentDrawXPos + 1, CurrentDrawYPos + 1, &szmessage[ StartPos ], i - StartPos );				
				SetTextColor(hdc , oldColor );

				TextOut( hdc, CurrentDrawXPos, CurrentDrawYPos, &szmessage[ StartPos ], i - StartPos );

				CurrentDrawXPos += GetTextExtent( hdc, &szmessage[ StartPos ], i - StartPos );
			}

			int ConditionTextLen = ChangeText( hdc, i , szmessage );

			i += ConditionTextLen;
			StartPos = i + 1;
			Counter = 0;
		}
		else
		{
			++Counter;
		}
	}

	if ( Counter > 0 )
	{	
		// �۾� �׸��ڸ� ������ش�
		SI32 oldColor =	SetTextColor( hdc, shadowrgb );
		TextOut( hdc, CurrentDrawXPos + 1, CurrentDrawYPos + 1, &szmessage[ StartPos ], i - StartPos   );				
		SetTextColor(hdc , oldColor );
		
        // ���� �۾��� ����Ѵ�.
		TextOut( hdc, CurrentDrawXPos, CurrentDrawYPos, &szmessage[ StartPos ], i - StartPos  );					
	}
	
}


SI16 cltMessage::ChangeText( HDC hDC, SI32 nPos , TCHAR * szmessage )
{
	static COLORREF oldColor = RGB( 0, 0, 0 );

	switch ( szmessage[ nPos + 1 ] )
	{	
	case 'C':
	case 'c':
		{
			TCHAR strNumber[ 3 ] = TEXT("");
			strNumber[ 0 ] = szmessage[ nPos + 2 ];
			strNumber[ 1 ] = szmessage[ nPos + 3 ];
			strNumber[ 2 ] = NULL;

			SI32 ColorIndex = _tstoi( strNumber );
			SI32 fontColor =  GetChatEditColor( ColorIndex ) ;
			oldColor =	SetTextColor( hDC, fontColor );
		}
		break;
	case '/':
		{
			switch( szmessage[ nPos + 2 ] )
			{			
			case 'C':				 
			case 'c':
				{					
					SetTextColor( hDC, oldColor );
				}				
				break;
			default:
				OutputDebugString(  TEXT("Edit : No Command Error2\r\n") );
				break;
			}

			return EDIT_CHANGETEXTDRAW_CONDITION_UNINSTALL_TEXT_LEN;
		}
		break;
	default:
		{
			OutputDebugString(  TEXT("Edit : No Command Error1\r\n") );

			return 0;
		}
		break;
	}

	return EDIT_CHANGETEXTDRAW_CONDITION_INSTALL_TEXT_LEN;
}

//----------------------------------------------
// ������ ȹ�� �޽���. 
//----------------------------------------------
void cltMessage::SetGetItemMsg(TCHAR* itemName, cltItem* pclItem,GMONEY price)
{
		
	TCHAR buffer[ 512 ] = TEXT("");
	TCHAR moneybuf[256] = TEXT("");
	int itemCnt= 0;
		
	itemCnt = pclItem->siItemNum;
	
	bool bPrice = DATA_TO_BOOL(price);
	if(bPrice)
	{
		TCHAR* pText = GetTxtFromMgr(611);
		g_JYLibFunction.SetNumUnit(price,moneybuf,256, pText );
		pText  = GetTxtFromMgr(2393);
		StringCchPrintf(buffer, 512, pText, itemName,itemCnt,moneybuf);
	}
	else
	{
		TCHAR* pText  = GetTxtFromMgr(2394);
		StringCchPrintf(buffer, 512, pText, itemName,itemCnt);
	}

	SetMsg(buffer,0, RGB(220,220,220),RGB(0,0,0) );

}


//----------------------------------------------
// ������ �޽���. 
//----------------------------------------------
void cltMessage::SetHuntMsg(TCHAR* szmessage)
{
	StringCchCopy(szHuntMsg, MAX_MESSAGE_LENGTH, szmessage);
	bHuntMsgSwitch	= true;
	dwLastHuntMsgClock = pclClient->CurrentClock;

}

//----------------------------------------------
// ���� �޽���. 
//----------------------------------------------
void cltMessage::SetPrisonMsg(TCHAR* szmessage)
{
	StringCchCopy(szPrisonMsg, MAX_MESSAGE_LENGTH, szmessage);
	bPrisonMsgSwitch	= true;
	dwLastPrisonMsgClock = pclClient->CurrentClock;

}


//----------------------------------------------
// �Ұ��縮 ��� �̺�Ʈ �޽���. 
//----------------------------------------------
void cltMessage::SetHuntEventMsg(SI32 leftsecond)
{
	TCHAR* pText = GetTxtFromMgr(808);
	StringCchPrintf(szHuntEventMsg, MAX_MESSAGE_LENGTH, pText, leftsecond);
	bHuntEventMsgSwitch	= true;
	dwLastHuntEventMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// ���ĸ��� �̺�Ʈ �޽���. 
//----------------------------------------------
void cltMessage::SetMofuMofuEventMsg(SI32 leftsecond, SI32 siMaMaMofuMofu, SI32 siKilledMofuMofu, SI32 siTotalMofuMofu)
{
	TCHAR* pText = GetTxtFromMgr(7067);
	StringCchPrintf(szMofuMofuEventMsg, MAX_MESSAGE_LENGTH, pText, leftsecond, siMaMaMofuMofu, 1, siKilledMofuMofu, siTotalMofuMofu);
	bMofuMofuEventMsgSwitch	= true;
	dwLastMofuMofuEventMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// ���� ���� ��� �̺�Ʈ �޽���. 
//----------------------------------------------
void cltMessage::SetGoguEventMsg(SI32 leftsecond)
{
	TCHAR* pText = GetTxtFromMgr(808);
	StringCchPrintf(szGoguEventMsg, MAX_MESSAGE_LENGTH, pText, leftsecond);
	bGoguEventMsgSwitch	= true;
	dwLastGoguEventMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// ����ī�� �̺�Ʈ �޽���. 
//----------------------------------------------
void cltMessage::SetOsakaEventMsg(SI32 leftsecond)
{
	TCHAR* pText = GetTxtFromMgr(808);
	StringCchPrintf(szOsakaEventMsg, MAX_MESSAGE_LENGTH, pText, leftsecond);
	bOsakaEventMsgSwitch	= true;
	dwLastOsakaEventMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// ��ȭ�� �̺�Ʈ �޽���. 
//----------------------------------------------
void cltMessage::SetKanghwadoEventMsg(SI32 leftsecond)
{
	TCHAR* pText = GetTxtFromMgr(808);
	StringCchPrintf(szKanghwadoEventMsg, MAX_MESSAGE_LENGTH, pText, leftsecond);
	bKanghwadoEventMsgSwitch	= true;
	dwLastKanghwadoEventMsgClock = pclClient->CurrentClock;
}


//----------------------------------------------
// ��Ʋ�ξ� ���� ��� 
//----------------------------------------------
void cltMessage::SetBattleRoyalGameModeMsg(TCHAR* pszMessage)
{
	StringCchPrintf(szBattleRoyalGameModeMsg, MAX_MESSAGE_LENGTH, pszMessage);
	bBattleRoyalGameModeMsgSwitch	= true;
	dwLastBattleRoyalGameModeMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// ��Ƽ����Ʈ ���� ��� 
//----------------------------------------------
void cltMessage::SetPartyQuestGameModeMsg(TCHAR* pszMessage, bool bClear)
{
	if(bClear == true)
		StringCchPrintf(m_szPartyQuestMessage[0], MAX_MESSAGE_LENGTH, pszMessage);
	else
		StringCchPrintf(m_szPartyQuestMessage[1], MAX_MESSAGE_LENGTH, pszMessage);

	m_bPartyQuestGameModeMsgSwitch	= true;
	m_dwLastPartyQuestGameModeMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// DailyQuest �޽���. 
//----------------------------------------------
void cltMessage::SetDailyQuestMsg(TCHAR* szmessage)
{
	StringCchCopy(szDailyQuestMsg, MAX_MESSAGE_LENGTH, szmessage);
	bDailyQuestMsgSwitch	= true;
	dwLastDailyQuestMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// �ν��Ͻ� ���� �޽���
//----------------------------------------------
void cltMessage::SetInstanceMapMsg(TCHAR* szmessage)
{
	StringCchCopy(szInstanceMapMsg, MAX_MESSAGE_LENGTH, szmessage);
	bInstanceMapMsgSwitch	= true;
	dwLastInstanceMapMsgClock = pclClient->CurrentClock;
}

//----------------------------------------------
// ���� �ֹ� ä�� �޽���. 
//----------------------------------------------
void cltMessage::SetVillageChatMsg(TCHAR* szmessage)
{
	StringCchCopy(szVillageChatMsg, MAX_MESSAGE_LENGTH, szmessage);
	bVillageChatMsgSwitch	= true;
	dwLastVillageChatMsgClock = pclClient->CurrentClock;
}



//-----------------------------------------------
// ���� �޽��� 
//-----------------------------------------------

// ���� �޽����� �����Ѵ�. 
void cltMessage::SetBlackArmyWarMsg(TCHAR* szmsg, TCHAR** sortplayernames, SI32 *playerscores  )
{
	dwLastWarMsgFrame = pclClient->GetFrame();

	TCHAR WarPlayers[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];

	if(szmsg)
	{
		MStrCpy(szWarMsg,		szmsg, MAX_WAR_MSG_SIZE );
	}
	else
	{
		StringCchCopy(szWarMsg, MAX_WAR_MSG_SIZE, TEXT(""));
	}

	memcpy(WarPlayers, sortplayernames, MAX_PLAYER_NAME * 5 * sizeof(TCHAR));

	for (SI32 i = 0; i < MAX_WARRANK_PERSON_PER_MAP; i++)
	{
		if (_tcscmp(WarPlayers[i], TEXT("")) == 0)
		{
			StringCchPrintf(szWarPlayersMsg[i], MAX_WAR_MSG_SIZE, TEXT(""));
		}
		else
		{    
			StringCchPrintf(szWarPlayersMsg[i], MAX_WAR_MSG_SIZE, TEXT("%s (%dP)"), WarPlayers[i], playerscores[i]);
		}
	}
}

// ���� �޽����� �����Ѵ�. 
void cltMessage::SetWarMsg(TCHAR* szmsg, TCHAR** sortplayernames, SI32 *playerscores, TCHAR** SortVillageNames, SI32* WarVillageScores )
{
	dwLastWarMsgFrame = pclClient->GetFrame();
	
	TCHAR WarPlayers[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];
	TCHAR WarVillage[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];

	if(szmsg)
	{
		MStrCpy(szWarMsg,		szmsg, MAX_WAR_MSG_SIZE );
	}
	else
	{
		StringCchCopy(szWarMsg, MAX_WAR_MSG_SIZE, TEXT(""));
	}

	memcpy(WarPlayers, sortplayernames,  MAX_PLAYER_NAME * 5 * sizeof(TCHAR));
	
	//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� ���� �̸� �����ϱ�.]
	if( pclClient->IsCountrySwitch(Switch_BlackWarReform) 	&&
	   (true == pclClient->pclBlackWarManager->IsBlackWar())	)
	{
		if(NULL != SortVillageNames)
		{
			memcpy(WarVillage, SortVillageNames, MAX_PLAYER_NAME * 5 * sizeof(TCHAR));
		}
	}
	

	for (SI32 i = 0; i < MAX_WARRANK_PERSON_PER_MAP; i++)
	{
		if (_tcscmp(WarPlayers[i], TEXT("")) == 0)
		{
			StringCchPrintf(szWarPlayersMsg[i], MAX_WAR_MSG_SIZE, TEXT(""));
		}
		else
		{    
			StringCchPrintf(szWarPlayersMsg[i], MAX_WAR_MSG_SIZE, TEXT("%s (%dP)"), WarPlayers[i], playerscores[i]);
		}
		//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� ���� ���� �̸��� ���� �����ϱ�.]
		if( pclClient->IsCountrySwitch( Switch_BlackWarReform )		&&
			(true == pclClient->pclBlackWarManager->IsBlackWar())		)
		{
			if (_tcscmp(WarVillage[i], TEXT("")) == 0 )
			{
				StringCchPrintf(szWarVillageMsg[i], MAX_WAR_MSG_SIZE, TEXT(""));
			}
			else
			{    
				StringCchPrintf(szWarVillageMsg[i], MAX_WAR_MSG_SIZE, TEXT("%s (%dP)"), WarVillage[i], WarVillageScores[i]);
			}
		}
	}


}

// ���� ������ ǥ���Ѵ�. 
void cltMessage::ShowWarKill(LPDIRECTDRAWSURFACE7 surface, SI32 rx, SI32 ry)
{
	// [�߰� : Ȳ���� 2008. 1. 23 => �ν��Ͻ� �ʿ����� �׸��� �ʰ�.]
	SI32 MapIndex  = pclClient->pclCM->CR[1]->GetMapIndex();
	if(true == pclClient->pclMapManager->IsInstanceMap(MapIndex))
	{
		return;
	}

	if( pclClient->IsCountrySwitch( Switch_BlackWarReform ) 			&&
		(true == pclClient->pclBlackWarManager->IsBlackWar())			&&			
		(BLACKARMY_MAP_STARTINDEX > MapIndex || BLACKARMY_MAP_STARTINDEX+MAX_BLACKARMY_MAP_CNT < MapIndex)	)
	{
			
	}
	else
	{
		// ���� ���� â�� �ݴ´�.
		if(pclClient->IsCountrySwitch(Switch_BlackWarReform))
		{	
			// [�߰� : Ȳ���� 2008. 1. 23 => ���� ���� â�ݱ�.]
			cltClient *pclclient = (cltClient *)pclClient;
			pclclient->DestroyInterface( pclclient->m_pDialog[NBLACK_WAR_RUN_DLG] );
		}

		SI32 x = 400;
		SI32 y = 160;

		SI32 yindent = 60 ;

		if(bShowWarMessageSwitch == false)return ;
		bShowWarMessageSwitch = false;

		// ǥ���ؾ� �� ����. 
		SI32 num = 0;

		if( true == pclClient->pclBlackWarManager->IsBlackWar() )
			num = pclClient->pclCM->CR[1]->siBlackWarEnemyKillNumber;
		else
			num = pclClient->pclCM->CR[1]->siWarEnemyKillNumber;

		if(GP.LockSurface(surface) == TRUE)
		{
			// ���� �̹���. 
			TSpr* pspr1 = pclClient->GetGlobalSpr(GIMG_WARKILL);
			if(pspr1)
			{
				GP.PutSpr(pspr1, x + rx, y + ry+yindent, 3);
			}

			TSpr* pspr2	= pclClient->GetGlobalSpr(GIMG_WARKILLNUM);
			if(pspr2)
			{
				// X �̹���. 
				GP.PutSpr(pspr2,	x + rx + pspr1->GetXSize(), 
					y + ry + (pspr1->GetYSize() - pspr2->GetYSize())+yindent, 10);

				// ����. 
				GP.DrawNumber(pspr2,	x + rx + pspr1->GetXSize() + pspr2->GetXSize(), 
					y + ry + (pspr1->GetYSize() - pspr2->GetYSize())+yindent, 0, num);
			}

			// ����� �̹���. 
			x = x + 130;
			SI32 font=0;

			switch (pclClient->pclCM->CR[1]->GetKind())
			{
			case KIND_HERO1 :
				font = 1;
				break;
			case KIND_HEROINE1 :
				font = 2;
				break;
			case KIND_HERO3 :
				font = 4;
				break;
			case KIND_HEROINE3 :
				font = 5;
				break;
			case KIND_HERO4 :
				font = 6;
				break;
			case KIND_HEROINE4 :
				font = 7;
				break;
			}

			GP.PutSpr(pspr1, x + rx, y + ry+yindent, font);

			if( true == pclClient->pclBlackWarManager->IsBlackWar() )
				num = pclClient->pclCM->CR[1]->siBlackWarKilledNumber;
			else
				num = pclClient->pclCM->CR[1]->siWarKilledNumber;

			if(pspr2)
			{
				// X �̹���. 
				GP.PutSpr(pspr2,	x + rx + pspr1->GetXSize(), 
					y + ry + (pspr1->GetYSize() - pspr2->GetYSize())+yindent, 10);

				// ����. 
				GP.DrawNumber(pspr2,	x + rx + pspr1->GetXSize() + pspr2->GetXSize(), 
					y + ry + (pspr1->GetYSize() - pspr2->GetYSize())+yindent, 0, num);
			}


			for(SI32 i = 0; i < 5; i++)
			{
				// ��ŷ�̹���
				TSpr* pspr1 = pclClient->GetGlobalSpr(GIMG_RANKING);
				if(pspr1)
				{              
					GP.PutSpr(pspr1, x + rx - 140, y - 70 + i * 25 + ry, i);
				}
			}

			GP.UnlockSurface(surface);
		}
	}
}

// ����  �޽����� �����ش�. 
bool cltMessage::ShowPrisonMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = 290;
	SI32 y = 50;

	if(bPrisonMsgSwitch == false)return false;

	// �ʹ� �������� �޽������������� ������ �ʴ´�. 
	if( dwLastPrisonMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastPrisonMsgClock) > 15000 )
	{
		bPrisonMsgSwitch = false;
		return false;
	}

	SI32 yindent = 0 ;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		yindent = 30 ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1 + yindent , szPrisonMsg, lstrlen(szPrisonMsg));
	
	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry + yindent , szPrisonMsg, lstrlen(szPrisonMsg));

	return true;


}

// ������ �޽����� �����ش�. 
void cltMessage::ShowHuntMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = 290;
	SI32 y = 50;

	// �ʹ� �������� �޽������������� ������ �ʴ´�. 
	if( dwLastHuntMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastHuntMsgClock) > 30000 )
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szHuntMsg, lstrlen(szHuntMsg));
	
	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szHuntMsg, lstrlen(szHuntMsg));


}


// Ű�޶�(��Ƽ�콺) ��� �̺�Ʈ �޽����� �����ش�. 
void cltMessage::ShowHuntEventMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = 340;
	SI32 y = 120; 

	// �ʹ� �������� �޽����� �������� ������ �ʴ´�. 
	if( dwLastHuntEventMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastHuntEventMsgClock) > 10000 )
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szHuntEventMsg, lstrlen(szHuntEventMsg));
	
	// �� �ؽ�Ʈ ���.  
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szHuntEventMsg, lstrlen(szHuntEventMsg));
}

// ���ĸ��� �̺�Ʈ �޽����� �����ش�. 
void cltMessage::ShowMofuMofuEventMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = 340;
	SI32 y = 120;

	// �ʹ� �������� �޽����� �������� ������ �ʴ´�. 
	if( dwLastMofuMofuEventMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastMofuMofuEventMsgClock) > 10000 )
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szMofuMofuEventMsg, lstrlen(szMofuMofuEventMsg));

	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szMofuMofuEventMsg, lstrlen(szMofuMofuEventMsg));
}

// ���� ���� ��� �̺�Ʈ �޽����� �����ش�. 
void cltMessage::ShowGoguEventMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = ((cltClient*)pclClient)->siClientScreenXsize - 230;
	SI32 y = 86;

	// �ʹ� �������� �޽����� �������� ������ �ʴ´�. 
	if( dwLastGoguEventMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastGoguEventMsgClock) > 10000 )
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szGoguEventMsg, lstrlen(szGoguEventMsg));
	
	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szGoguEventMsg, lstrlen(szGoguEventMsg));


}

// ����ī�� �̺�Ʈ �޽����� �����ش�. 
void cltMessage::ShowOsakaEventMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = ((cltClient*)pclClient)->siClientScreenXsize - 230;
	SI32 y = 150;

	// �ʹ� �������� �޽����� �������� ������ �ʴ´�. 
	if( dwLastOsakaEventMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastOsakaEventMsgClock) > 20000 )
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szOsakaEventMsg, lstrlen(szOsakaEventMsg));

	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szOsakaEventMsg, lstrlen(szOsakaEventMsg));
}

// ��ȭ�� ��� �̺�Ʈ �޽����� �����ش�. 
void cltMessage::ShowKanghwadoEventMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = ((cltClient*)pclClient)->siClientScreenXsize - 230;
	SI32 y = 150;

	// �ʹ� �������� �޽����� �������� ������ �ʴ´�. 
	if( dwLastKanghwadoEventMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastKanghwadoEventMsgClock) > 10000 )
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szKanghwadoEventMsg, lstrlen(szKanghwadoEventMsg));

	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szKanghwadoEventMsg, lstrlen(szKanghwadoEventMsg));


}

//��Ʋ�ξ� ���� ��� �޽����� �����ش�. 
void cltMessage::ShowBattleRoyalGameModeMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = (((cltClient*)pclClient)->siClientScreenXsize - lstrlen(szBattleRoyalGameModeMsg) * 11)/2  ;
	SI32 y = 200;

	// �ʹ� �������� �޽����� �������� ������ �ʴ´�. 
	if( dwLastBattleRoyalGameModeMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastBattleRoyalGameModeMsgClock) > 20000 )
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szBattleRoyalGameModeMsg, lstrlen(szBattleRoyalGameModeMsg));

	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(255, 0, 0));
	TextOut(hdc, x + rx, y + ry, szBattleRoyalGameModeMsg, lstrlen(szBattleRoyalGameModeMsg));
}

// DailyQuest �޽����� �����ش�. 
void cltMessage::ShowDailyQuestMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = 350;
	SI32 y = 116;

	// �ʹ� �������� �޽������������� ������ �ʴ´�. 
	if(dwLastDailyQuestMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastDailyQuestMsgClock) > 10000)
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szDailyQuestMsg, lstrlen(szDailyQuestMsg));
	
	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szDailyQuestMsg, lstrlen(szDailyQuestMsg));


}

//[����] �������� �޽��� ��� ��ġ ���� �߰�. => 2008-6-2
void cltMessage::ShowPersonalMsg(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = ((cltClient*)pclClient)->siClientScreenXsize - 1030;     
	SI32 y = 500;

	SI32 siMsgCount = 0; 
	
	if(MAX_PERSONAL_MESSAGE_NUMBER <= PersonalMessageIndex)
		PersonalMessageIndex = MAX_PERSONAL_MESSAGE_NUMBER-1;

	for(SI32 Count = 0; Count < PersonalMessageIndex; Count++)
	{
		if(_tcscmp(PersonalMessage[Count], TEXT("")) == 0)continue;

		//// �׸��� ���.   
		SetTextColor( hdc, RGB(0, 0, 0));
		TextOut(hdc, x + rx - 9, y + 20 + siMsgCount * 20 + ry + 1, PersonalMessage[siMsgCount], lstrlen(PersonalMessage[siMsgCount]));

		// �� �ؽ�Ʈ ���. 
		SetTextColor( hdc, RGB(200, 200, 200));  
		TextOut(hdc, x + rx - 10,	y + 20 + siMsgCount * 20 + ry, PersonalMessage[siMsgCount], lstrlen(PersonalMessage[siMsgCount]));

		siMsgCount++;
	}	
}

// DailyQuest �޽����� �����ش�. 
void cltMessage::ShowInstanceMapMsg(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = 350;
	SI32 y = 86;

	// �ʹ� �������� �޽������������� ������ �ʴ´�. 
	if(dwLastInstanceMapMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastInstanceMapMsgClock) > 10000)
	{
		return ;
	}

	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szInstanceMapMsg, lstrlen(szInstanceMapMsg));

	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szInstanceMapMsg, lstrlen(szInstanceMapMsg));


}

// �ֹ� ä�� �޽����� �����ش�. 
void cltMessage::ShowVillageChatMessage(HDC hdc, SI32 rx, SI32 ry)
{
	SI32 x = 90;
	SI32 y = 0;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		y= ((cltClient*)pclClient)->siScreenMode800X600YSize + ((cltClient*)pclClient)->siScreenModeYOffSet  - 110;
	}
	else
	{
		y= ((cltClient*)pclClient)->siScreenMode800X600YSize + ((cltClient*)pclClient)->siScreenModeYOffSet  - 50;
	}

	// �ʹ� �������� �޽������������� ������ �ʴ´�. 
	if(dwLastVillageChatMsgClock == 0 || TABS(pclClient->CurrentClock - dwLastVillageChatMsgClock) > 10000)
	{
		return ;
	}


	// �׸��� ���. 
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x + rx+ 1, y + ry + 1, szVillageChatMsg, lstrlen(szVillageChatMsg));

	// �� �ؽ�Ʈ ���. 
	SetTextColor( hdc, RGB(220, 220, 220));
	TextOut(hdc, x + rx, y + ry, szVillageChatMsg, lstrlen(szVillageChatMsg));
	
}


// ���� �޽����� �����ش�. 
void cltMessage::ShowWarMessage(HDC hdc, SI32 rx, SI32 ry)
{
	// [�߰� : Ȳ���� 2008. 1. 23 => �ν��Ͻ� �ʿ����� �׸��� �ʰ�.]
	SI32 MapIndex  = pclClient->pclCM->CR[1]->GetMapIndex();
	if(true == pclClient->pclMapManager->IsInstanceMap(MapIndex))
	{
		return;
	}

	// �ʹ� �������� �޽������������� ������ �ʴ´�. 
	if(dwLastWarMsgFrame == 0 || TABS(pclClient->GetFrame() - dwLastWarMsgFrame) > 1000)
	{
		if(pclClient->IsCountrySwitch(Switch_BlackWarReform))
		{	
			// [�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �� â�ݱ�.]
			cltClient *pclclient = (cltClient *)pclClient;
			pclclient->DestroyInterface( pclclient->m_pDialog[NBLACK_WAR_RUN_DLG] );
		}
		return ;
	}

	// ���� �޽����� ǥ���Ѵٴ� ���� ����.
	bShowWarMessageSwitch = true;

	

	//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� ���� ���� �̸��� ���� �׸���. ]
	if(pclClient->IsCountrySwitch(Switch_BlackWarReform)				&&
		( BLACKARMY_MAP_STARTINDEX > MapIndex							||
		  BLACKARMY_MAP_STARTINDEX+MAX_BLACKARMY_MAP_CNT < MapIndex)			)
	{	
		if(false == pclClient->pclBlackWarManager->IsBlackWar())
			return;

		cltClient* pclclient = (cltClient *)pclClient;

		CNBlackWarReformReward* pStatusDlg1 = (CNBlackWarReformReward*)pclclient->m_pDialog[ NBLACK_WAR_REWARD_DLG ];
		if(NULL == pStatusDlg1)
		{
			//return;
		}
		
		// [�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� ���� â ����� �����ִ� �ɷ� ����.]
		pclclient->CreateInterface(NBLACK_WAR_RUN_DLG);

		CNBlackWarReformRun* pStatusDlg2 = (CNBlackWarReformRun*)pclclient->m_pDialog[ NBLACK_WAR_RUN_DLG ];
		pStatusDlg2->SetRunStatus(szWarMsg, (TCHAR**)szWarPlayersMsg, (TCHAR**)szWarVillageMsg);
	}
	else
	{
		SI32 x = 430;
		SI32 y = 85;

		// �׸��� ���. 
		SetTextColor( hdc, RGB(0, 0, 0));
		TextOut(hdc, x + rx+ 1 - 32, y + ry - 5, szWarMsg, lstrlen(szWarMsg));

		// �� �ؽ�Ʈ ���. 
		SetTextColor( hdc, RGB(180, 180, 180));
		TextOut(hdc, x + rx - 32, y + ry - 6, szWarMsg, lstrlen(szWarMsg));

		for(SI32 i = 0;i < 5;i++)
		{
			if(_tcscmp(szWarPlayersMsg[i], TEXT("")) == 0)continue;

			// �׸��� ���. 
			SetTextColor( hdc, RGB(0, 0, 0));
			TextOut(hdc, x + rx+ 1, y + 20 + i * 25 + ry + 1, szWarPlayersMsg[i], lstrlen(szWarPlayersMsg[i]));

			// �� �ؽ�Ʈ ���. 
			SetTextColor( hdc, RGB(180, 180, 180));
			TextOut(hdc, x + rx,	y + 20 + i * 25 + ry, szWarPlayersMsg[i], lstrlen(szWarPlayersMsg[i]));
		}
	}
}


// ��Ƽ����Ʈ ���� �޼����� ����մϴ�.
void cltMessage::ShowPartyQuestMsg(HDC hdc, SI32 rx, SI32 ry)
{
	cltClient* pclclient = (cltClient*)pclClient;

	if(m_dwLastPartyQuestGameModeMsgClock == 0 || TABS(pclClient->CurrentClock - m_dwLastPartyQuestGameModeMsgClock) > 10000)
	{
		ZeroMemory(m_szPartyQuestMessage, MAX_MESSAGE_LENGTH*2);
		return ;
	}

	SI32 yindext = 15;
	COLORREF color;

	for(SI32 i = 0; i < 2; i++)
	{
		if ( _tcscmp( m_szPartyQuestMessage[i], TEXT("")) == 0 )
			continue;

		SetTextAlign(hdc, TA_CENTER);

		SI32 drawx = pclclient->siClientScreenXsize/2 + rx;
		SI32 drawy = 160 + ry;

		// �׸��� ���
		SetTextColor( hdc, RGB(50, 50, 50) );
		TextOut(hdc, drawx+1, drawy+(yindext*i), m_szPartyQuestMessage[i], lstrlen(m_szPartyQuestMessage[i]));
		TextOut(hdc, drawx-1, drawy+(yindext*i), m_szPartyQuestMessage[i], lstrlen(m_szPartyQuestMessage[i]));
		TextOut(hdc, drawx, drawy-1+(yindext*i), m_szPartyQuestMessage[i], lstrlen(m_szPartyQuestMessage[i]));
		TextOut(hdc, drawx, drawy+1+(yindext*i), m_szPartyQuestMessage[i], lstrlen(m_szPartyQuestMessage[i]));

		color = RGB(250, 250, 0);

		// �ؽ�Ʈ ���
		SetTextColor( hdc, color);
		TextOut(hdc, drawx, drawy+(yindext*i), m_szPartyQuestMessage[i], lstrlen(m_szPartyQuestMessage[i]));
		TextOut(hdc, drawx, drawy+(yindext*i), m_szPartyQuestMessage[i], lstrlen(m_szPartyQuestMessage[i]));
	}
}

void cltMessage::ShowCurQuestInfo(HDC hdc, SI32 rx, SI32 ry)
{
	cltClient* pclclient = (cltClient*)pclClient;


	SI32 i, j;
	SI32 id = 1;
	TCHAR text[1024]    = "";
	TCHAR name[1024]    = "";

	cltQuestInfoCommon* pclspecialinfo = NULL;
	SI32 yindext = 0;
	for(i = 0;i < MAX_QUEST_TYPE;i++)
	{
		TCHAR buffer[2048]   = "";

		cltPersonQuestUnitInfo* pclunit = NULL;
		pclunit = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clUnit[i];

		// �������� ����Ʈ�� ���ٸ�, 
		if(pclunit->siCurQuestUnique == 0)
		{
			StringCchCopy( szQuestPrintBuffer[i], 2048, TEXT("") );
			continue;
		}


		memset(name, 0, sizeof(name));
		memset(text, 0, sizeof(text));

		TCHAR szreward[256] = "";

		// ������ ���ؼ� ���ۿ� �����Ѵ�.
		if(pclClient->pclQuestManager->GetCurStatusText(id, i, pclunit->siCurQuestUnique, text, 1024) == true)
		{
			SI32 npckind = pclClient->pclQuestManager->GetNPCKindFromQuestType(i);
			if(npckind)
			{
				const TCHAR* pname = pclClient->pclKindInfoSet->GetName(npckind);
				if(pname)
				{
					sprintf(name, "[%s]", pname);
				}
			}

			// �����߿� ���ʿ��� �ܾ�� �����Ѵ�.
			for(j = 0;j < lstrlen(text);j++)
			{
				if(text[j] == ' ' || text[j] == ' ')
				{
					text[j] = ' ';
				}
			}

			StringCchCopy(buffer, 2048, "");
			StringCchCat(buffer, 2048, name);
			StringCchCat(buffer, 2048, text);


			// ����Ʈ�� ������ ��Ȳ�̶��, 

			// Ư�� ����Ʈ�̸�, 
			cltQuestInfo* pclinfo = NULL;
			switch( i )
			{
			case QUEST_TYPE_SPECIAL:	pclinfo = (cltQuestInfo*)&pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clSpecialQuestInfo;	break;
			case QUEST_TYPE_NAMING:		pclinfo = (cltQuestInfo*)&pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clNamingQuestInfo;	break;
			case QUEST_TYPE_MISSION1:	pclinfo = (cltQuestInfo*)&pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clMissionQuestInfo;	break;
			default:					pclinfo = pclClient->pclQuestManager->GetQuestInfo( pclunit->siCurQuestUnique );			break;
			}

			if(pclinfo)
			{
				if(pclClient->pclCM->CR[id]->IsClearCondition(i, &pclinfo->clQuestClearConditionInfo) == true)
				{
					if (bQuestClearSwitch[i] != true)
					{
						TCHAR* pText = GetTxtFromMgr(6141);
						StringCchCat( buffer, 2048, pText );
					}
					else
					{
						StringCchCopy( buffer, 2048, szCurQuestInfoMsgBuffer[i]);
					}
					bQuestClearSwitch[i] = true;

					if ( pclClient->pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear(pclClient->pclQuestManager, pclinfo->siType) ) 
					{
						StringCchCopy( buffer, 2048, TEXT("") );	
					}
					//�����뿡[ ȭ���� ������Ʈ �ϴ��� ���� ���� �ؽ�Ʈ�� �����ָ�?
				}
			}

			if ( _tcscmp( buffer, szCurQuestInfoMsgBuffer[i] ) != 0  )
			{
				StringCchCopy( szQuestPrintBuffer[i], 2048, buffer ) ;
				dwCurQuestInfoMsgClock[i] = pclClient->CurrentClock;
			}
			else if ( pclClient->CurrentClock - dwCurQuestInfoMsgClock[i] < 6000 )
			{
				StringCchCopy( szQuestPrintBuffer[i], 2048, buffer ) ;
			}
			else
			{
				StringCchCopy( szQuestPrintBuffer[i], 2048, TEXT("") );
			}

			StringCchCopy( szCurQuestInfoMsgBuffer[i], 2048, buffer );


		}
	}

	COLORREF color;

	// ���� ��� ��ƾ
	for ( i=0; i<MAX_QUEST_TYPE; i++)
	{

		// ����Ʈ ������ �ٲ��� ������� ������� �ʴ´�.
		if ( _tcscmp( szQuestPrintBuffer[i] , TEXT("")) == 0 )
			continue;



		SetTextAlign(hdc, TA_CENTER);

		SI32 drawx = pclclient->siClientScreenXsize/2 + rx;
		SI32 drawy = 160 + ry;

		// �׸��� ���
		SetTextColor( hdc, RGB(50, 50, 50) );
		TextOut(hdc, drawx+1, drawy+yindext, szQuestPrintBuffer[i], lstrlen(szQuestPrintBuffer[i]));
		TextOut(hdc, drawx-1, drawy+yindext, szQuestPrintBuffer[i], lstrlen(szQuestPrintBuffer[i]));
		TextOut(hdc, drawx, drawy-1+yindext, szQuestPrintBuffer[i], lstrlen(szQuestPrintBuffer[i]));
		TextOut(hdc, drawx, drawy+1+yindext, szQuestPrintBuffer[i], lstrlen(szQuestPrintBuffer[i]));
		//-

		if(bQuestClearSwitch[i])
		{
			color = RGB(250, 250, 0);
			bQuestClearSwitch[i] = false;
		}
		else
		{
			color = RGB(235, 235, 235);
		}

        // �ؽ�Ʈ ���
		SetTextColor( hdc, color);
		TextOut(hdc, drawx, drawy+yindext, szQuestPrintBuffer[i], lstrlen(szQuestPrintBuffer[i]));

		yindext+=15;
	}
}

