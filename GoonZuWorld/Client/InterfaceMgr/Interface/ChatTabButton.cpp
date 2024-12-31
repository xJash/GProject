#include "Button.h"
#include "Static.h"
#include "ChatTabButton.h"

#include "../InterfaceMgr.h"
#include "../ControllerMgr.h"
#include "../InterfaceImgMgr/InterfaceImgMgr.h"

#include <Graphic.h>
#include <Graphic_Capsule.h>

#include <Client.h>
extern cltCommonLogic *pclClient;

CChatTabButton::CChatTabButton( CControllerMgr *pParent ) : CButton( pParent )
{
	m_bSelected = FALSE;
}

CChatTabButton::~CChatTabButton()
{
}

void CChatTabButton::Create( SI16 ControllerID, TCHAR* Text, TCHAR *FileName, SI16 FontIndex, bool BKTileImg, SI16 BKTileImgNum, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, SI16 SurfaceWidth, SI16 SurfaceHeight )
{
	CControllerObj::Create( ControllerID, CONTROLLER_KIND_BUTTON, FileName, FontIndex, BKTileImg, BKTileImgNum, XPos, YPos, Width, Height, SurfaceWidth, SurfaceHeight );

	SetText( Text, GetTextPrintOption() );

	return;
}

void CChatTabButton::DrawController( SI16 BaseXPos, SI16 BaseYPos, SI32 LeftTime )
{
	cltClient *pclclient = (cltClient*)pclClient;

	int nOffsetX = 0;
	int nOffsetY = 0;

	int iState = CONTROLLER_STATE_NORMAL;


	//�ϴ� ���õ� ��ư�̸� ������ �ִ� ���·� ������
	// SetSelect�� �ܺο��� Ŭ�� �޽����� ������ True�� ��������. 

	if( IsSelected() == TRUE)
	{
		iState = CONTROLLER_STATE_PRESSED;
	}

	
	if( ! IsShow() )	// �Ⱥ��̴°Ÿ� ����.
	{		
		return;
	}
	else if( IsAvailable() == false )  
	{
		iState = CONTROLLER_STATE_DISABLED;
		if( IsMouseOver() )	// Disable ���¶� ������ ǥ�����ش�
		{
			if ( m_bUseToolTip )
			{
				if ( m_strToolTipMsg )
				{
					pclclient->m_pInterfaceMgr->SetDrawToolTip( true );
				}
			}
		}

	}
	else if( m_bLPressed )
	{
		iState = CONTROLLER_STATE_PRESSED;
	}
	else if( IsMouseOver() )
	{
		if ( m_bUseToolTip )
		{
			if ( m_strToolTipMsg )
			{
				pclclient->m_pInterfaceMgr->SetDrawToolTip( true );
			}
		}
	}

	UI16 AddFontIndex = 0;

	if ( IsBKTileImg() )
	{
		
	}
	else
	{
		TSpr *pBkImg = pclclient->m_pInterfaceMgr->GetInterfaceImgrMgr()->LoadInterfaceImg( GetFileName() );

		if ( m_bAniType )
		{
		
		}
		else
		{
			if ( pBkImg )
			{
				switch( iState )
				{
				case CONTROLLER_STATE_NORMAL:
					GP.PutSpr( pBkImg,BaseXPos + GetX() + nOffsetX, BaseYPos + GetY() + nOffsetY, GetFontIndex() + 1 );
					break;
				case CONTROLLER_STATE_PRESSED:
					GP.PutSpr( pBkImg,BaseXPos + GetX() + nOffsetX, BaseYPos + GetY() + nOffsetY, GetFontIndex() + 0 );
					break;
				case CONTROLLER_STATE_DISABLED:
					GP.PutSpr( pBkImg,BaseXPos + GetX() + nOffsetX, BaseYPos + GetY() + nOffsetY, GetFontIndex() + 3 );
					break;
				}
			}
		}
	}

	DrawStaticText( BaseXPos + nOffsetX, BaseYPos + nOffsetY );

	return;
}
