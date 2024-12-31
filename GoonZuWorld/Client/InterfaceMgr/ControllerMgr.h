#ifndef _CONTROLLERMGR_H_
#define _CONTROLLERMGR_H_

#include "ControllerBaseDefinition.h"
#include "ControllerResource.h"
#include "DialogResource.h"
#include "../../Common/SMLib/LibList/LibListMgr.h"

#include "../../Lib/NGraphics/Graphics.h"

class CControllerObj;
class CControllerMgr;
class CControllerSurfaceObj;
class CButton;
class cltClickAndDrop;

#define MAX_HAVE_CHILD_DIALOG_NUM			15				// Child Dialog ���� = �ǹ�ư ������� ���� �����ϰ���...

typedef void (CALLBACK *GUICallBackEvent) ( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
typedef void (CALLBACK *GUIChildCallBackEvent) ( CControllerMgr *pControllerMgr, UINT nEvent );

class CControllerMgr : public CLibListMgr  
{
public:
	CControllerMgr();
	virtual ~CControllerMgr();								// CLibListMgr �� virtual �� ����Ǿ� �־ ������ �ʾƵ� ȣ��Ǵ°��� Ȯ��������, �׷��� ���ִ°� �����ϴϱ�... virtual �� �ٿ�����.

	void SetPre( CControllerMgr *pNode )
	{
		m_pPre = pNode;
		return;
	}

	CControllerMgr *GetPre()
	{
		return m_pPre;
	}

	void SetNext( CControllerMgr *pNode )
	{
		m_pNext = pNode;
		return;
	}

	CControllerMgr *GetNext()
	{
		return m_pNext;
	}

	void SetDialogControllerID( SI16 DialogControllerID )
	{
		m_siDialogControllerID = DialogControllerID;
	}

	SI16 GetDialogControllerID()
	{
		return m_siDialogControllerID;
	}

	SI16 GetDialogControllerKind()
	{
		return m_siDialogControllerKind;
	}
	/*
	void SetParentID( SI16 ParentID )
	{
		m_siParentID = ParentID;
		return;
	}

	SI16 GetParentID()
	{
		return m_siParentID;
	}
	*/

	CControllerMgr *GetParentDialog()
	{
		return m_pParentDialog;
	}

	// �ڽ�â ���.
	CControllerMgr* GetChildDialog(SI16 _Kind)
	{
		return m_pChildDialog[_Kind];
	}
	
	TCHAR *GetFileName()
	{
		return m_strFileName;
	}

	void SetFileName( TCHAR *FileName )
	{
		if ( FileName )
		{
			StringCchCopy( m_strFileName, MAX_PATH, FileName );
		}
		else
		{
			m_strFileName[ 0 ] = NULL;
		}
	}

	SI16 GetFontIndex()
	{
		return m_siFontIndex;
	}
    
	void SetFontIndex( SI16 FontIndex )
	{
		m_siFontIndex = FontIndex;
	}

	bool IsBKTileImg()
	{
		return m_bBKTileImg;
	}

	void SetBKTileImgNum( SI16 BKTileImgNum )
	{
		m_siBKTileNum = BKTileImgNum;
	}

	SI16 GetX()
	{
		return m_siXPos;
	}

	void SetX( SI16 siX )
	{
		m_siXPos = siX;
		return;
	}

	SI16 GetY()
	{
		return m_siYPos;
	}

	void SetY( SI16 siY )
	{
		m_siYPos = siY;
		return;
	}

	SI16 GetWidth()
	{
		return m_siWidth;
	}

	void SetWidth( SI16 siWidth )
	{
		m_siWidth = siWidth;
		return;
	}

	SI16 GetHeight()
	{
		return m_siHeight;
	}

	void SetHeight( SI16 siHeight )
	{
		m_siHeight = siHeight;
		return;
	}

	/*
	cltTSpr *GetBKImg()
	{
		return &m_BKImg;
	}
	*/

	void Create( SI16 DialogControllerID, SI16 DialogControllerKind, CControllerMgr *pParentDialog, 
		GUICallBackEvent pCallBack, TCHAR *Title, 
		TCHAR *FileName, SI16 FontIndex,
		bool BKTileImg, SI16 BKTileNum,
		SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, 
		bool Movable, bool HaveCaption, bool HaveCloseButton//, bool HaveMinimizeButton 
		);

	void DeleteDialog();

	bool Add( CControllerObj *pObj );
	void Del( CControllerObj *pObj );
	void DelAll();

	bool AddChildDialog( CControllerMgr *pChild );
	void DelChildDialog( CControllerMgr *pChild );

	CControllerObj *GetControl( SI16 ControllerID );
	CControllerObj *GetControlAtPoint( POINT pt );
	CControllerObj *GetControlAtPointFromInterfaceMgr( POINT pt );

	void SetMouseOverObj( CControllerObj *pObj )
	{
		m_pMouseOverObj = pObj;
		return;
	}
	CControllerObj *GetMouseOverObj()
	{
		return m_pMouseOverObj;
	}

	void SetTitle( TCHAR *Title,COLORREF rgb  = CONTROLLER_TITLE_COLOR , SI32 size = BASE_FONT_HEIGHT , SI16 OffsetX = 0, SI16 OffsetY = 0 );
	TCHAR* GetTitle(){ return m_strTitle; }
	bool IsTimerOn()
	{
		return m_bTimerOnOff;
	}

	void SetTimerOnOff( bool TimerOnOff )
	{
		m_bTimerOnOff = TimerOnOff;
	}

	void SetActionTimer( SI32 ActionTimer )
	{
		m_siActionTimer = ActionTimer;
	}

	// [����] ����ð��� ���� �����ϰ� �����Ѵ�. �ֳĸ� ���� 30�ʿ� �ѹ� ȣ���� �ǰ� �ϰ� ������
	// m_PreClock �̰Ϳ� ������ �ȵ��־ ���� �ѹ��� ���� ���� �ð��� 30�ʿ� ������� ȣ��ǰ� �ǹǷ�.
	void SetActionTimer( SI32 ActionTimer, clock_t CurrentClock )
	{
		m_siActionTimer = ActionTimer;
		m_PreClock		= CurrentClock;
	}

	
	void ControllerMgrAction( clock_t CurrentClock );
	virtual void Action(){};
	
	
	void Draw( SI32 ScreenRX, SI32 ScreenRY );
	void DrawTransparent( SI32 ScreenRX, SI32 ScreenRY, SI32 Percent );
	void DrawLater( SI32 ScreenRX, SI32 ScreenRY );
	void DrawTitle( SI32 ScreenRX, SI32 ScreenRY );
	virtual void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY ) {};
	virtual void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY ) {};

	void DirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackSurface, SI32 ScreenRX, SI32 ScreenRY );
	virtual void VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackSurface, SI32 ScreenRX, SI32 ScreenRY ) {};

	bool IsInArea( SI16 XPos, SI16 YPos );
	void MoveDialog( SI16 OffsetX, SI16 OffsetY );
	void MovePos( SI16 XPos, SI16 YPos )
	{
		m_siXPos = XPos;
		m_siYPos = YPos;
	}

	void SetDialogPos( SI16 XPos, SI16 YPos, SI16 Width, SI16 Height )
	{
		m_siXPos = XPos;
		m_siYPos = YPos;

		m_siWidth = Width;
		m_siHeight = Height;
	}
	
	bool IsShow()
	{
		return m_bShow;
	}

	void Show( bool ShowOption );
	void Show( SI16 ControllerID, bool ShowOption );

	bool IsMoveable()
	{
		return m_bMoveable;
	}

	void SetMoveable( bool Moveable )
	{
		m_bMoveable = Moveable;
	}

	bool IsKeyboardInput()
	{
		return m_bKeyboardInput;
	}

	bool MsgProc( UINT iMsg, WPARAM &wParam, LPARAM &lParam, bool MouseOverSet );
	void SendEvent( UINT nEvent, bool bTriggeredByUser, CControllerObj* pController );
	void RequestFocus( CControllerObj *pController );
	virtual void ClearFocus();
	virtual void SetFocus( bool Focus );
	virtual void SetFocus( CControllerObj *pControllerObj );

	bool LButtonDown( SI16 XPos, SI16 YPos, SI16 *pParentID, SI16 *pControllerID, SI16 *pKind );
	virtual void Mouse_LButtonDown() {};
	bool LButtonUp( SI16 XPos, SI16 YPos, SI16 *pParentID, SI16 *pControllerID, SI16 *pKind );
	virtual void Mouse_LButtonUp() {};
	
	bool RButtonDown( SI16 XPos, SI16 YPos, SI16 *pParentID, SI16 *pControllerID, SI16 *pKind );
	virtual void Mouse_RButtonDown() {};
	bool RButtonUp( SI16 XPos, SI16 YPos, SI16 *pParentID, SI16 *pControllerID, SI16 *pKind );
	virtual void Mouse_RButtonUp() {};

	bool MouseMove( SI16 XPos, SI16 YPos, SI16 PreXPos, SI16 PreYPos, SI16 *pParentID, SI16 *pControllerID, SI16 *pKind );
	virtual void Mouse_MouseMove() {};

	void OnMouseMove( POINT pt, bool MouseOverSet );

	void SetRadioButtonCheck( SI16 RadioButtonControllerID, SI16 GroupID );
	
	void SetNonEventRadioButtonCheck( SI16 RadioButtonControllerID, SI16 GroupID );

	bool IsCreate()
	{
		return m_bCreate;
	}

	CControllerObj *GetFocusObj()
	{
		return m_pFocusObj;
	}

	void SetTopMostWindow( bool TopMostWindow );
	bool IsTopMostWindow()
	{
		return m_bTopMostWindow;
	}

	void SetModalDialog( bool ModalDialog )	;
	bool IsModalDialog()
	{
		return m_bModalDialog;
	}

	bool HaveCloseButton()
	{
		return m_bHaveCloseButton;
	}

	void SetHaveCloseButton( bool CloseButton )
	{
		m_bHaveCloseButton = CloseButton;
	}
/*
	bool HaveMinimizeButton()
	{
		return m_bHaveMinimizeButton;
	}
	void SetHaveMinimizeButton( bool MinimizeButton)
	{
		m_bHaveMinimizeButton = MinimizeButton;
	}
*/
	void SetHaveCaption( bool HaveCaption )
	{
		m_bHaveCaption = HaveCaption;
	}

	bool IsShowHideMethod()
	{
		return m_bShowHideMethod;
	}

	void SetShowHideMethod( bool ShowHideMethod )
	{
		m_bShowHideMethod = ShowHideMethod;
	}
	
	virtual void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen ) {};

	// CLICK AND DROP - ó���� �Ǹ� true�� ��ȯ�Ѵ�.
	virtual bool EndClickAndDrop( cltClickAndDrop* pclClickAndDrop ) {		return false;	 }

	void SetDrawOption( SI16 DrawOption )
	{
		m_siDrawOption = DrawOption;
	}

	SI16 GetDrawOption()
	{
		return m_siDrawOption;
	}

	void SetAlphaValue( SI16 AlphaValue )
	{
		m_siAlphaValue = ( (AlphaValue>=MAX_ALPHA_LEVEL) ? (MAX_ALPHA_LEVEL-1) : AlphaValue );
	}

	SI16 GetAlphaValue()
	{
		return m_siAlphaValue;
	}
	
	//�迵�� �߰� 2007.12.12 - ���ĸ�� ������ ���ÿ� ���İ� ����
	void SetAlphaMode( SI16 siAlphaValue )
	{
		SetDrawOption( SPR_PUTSPRALPHAT );
		SetAlphaValue( siAlphaValue );

		//m_siDrawOption = SPR_PUTSPRALPHAT;
		//m_siAlphaValue = ( (AlphaValue>=MAX_ALPHA_LEVEL) ? (MAX_ALPHA_LEVEL-1) : AlphaValue );
	}

	// ��� ��Ʈ���� ����� ��� ���� - by LEEKH 2008-03-11
	void SetDrawOptionAllControl( SI16 DrawOption );
	void SetAlphaValueAllControl( SI16 AlphaValue );

	void SetFadeIn( SI32 siFadeInTime )			{	m_siFadeInTime = siFadeInTime;	}
	SI32 GetFadeInTime()						{	return m_siFadeInTime;			}

	DWORD GetShowStartTime()					{	return m_dwShowStartTime;		}
	
private:
	CControllerMgr *m_pPre;
	CControllerMgr *m_pNext;
	
	GUICallBackEvent m_pGUICallBackEvent;

	// �θ� Controller ID
	SI16 m_siDialogControllerID;			// Dialog Controller ID
	SI16 m_siDialogControllerKind;			// Controller Kind ( Popup Dialog, Child Dialog )
	//SI16 m_siParentID;					// If Controller Kind == Child Dialog
	
	CControllerMgr *m_pChildDialog[ MAX_HAVE_CHILD_DIALOG_NUM ];	// If Controller Have Child Dialog
	CControllerMgr *m_pParentDialog;		// If Controller Kind == Child Dialog

	bool m_bHaveCaption;
	bool m_bHaveCloseButton;
//	bool m_bHaveMinimizeButton;
	bool m_bTopMostWindow;
    
	SI16 m_siXPos;
	SI16 m_siYPos;

	SI16 m_siWidth;
	SI16 m_siHeight;

	bool m_bHasFocus;						// Focus or DisFocus

	bool m_bShow;

	bool m_bMoveable;
	
	SI16 m_siTitleOffsetX;
	SI16 m_siTitleOffsetY;

	bool m_bKeyboardInput;
	bool m_bMouseInput;
	
	bool m_bHasTitle;

	TCHAR m_strTitle[ MAX_PATH ];
	RGB16*	m_TitleEncBuffer;
	CControllerSurfaceObj *m_pTitleSurfaceObj;	// Title Surface

	TCHAR m_strFileName[ MAX_PATH ];			// ��� �̹��� ���
	SI16 m_siFontIndex;						// ��� �̹����� ���� ���° �ִ���...
	//cltTSpr	m_BKImg;					// ��� �̹���
	bool m_bBKTileImg;						// ��� �̹����� Tile �̹������� ���̹��� ���� ����
	SI16 m_siBKTileNum;

	CControllerObj *m_pFocusObj;			// ��Ŀ���� ���� Controller
	CControllerObj *m_pMouseOverObj;		// ��Ŀ���� ���� Controller

	bool m_bTimerOnOff;						// Ÿ�̸� �V�� ����
	SI32 m_siActionTimer;					// Action Timer
	clock_t m_PreClock;						// �ֱٿ� Timer �� �����ߴ� �ð��� ������ ����.
	
	bool m_bHaveComboBox;					// ComboBox �� ���� ��쿡�� �������̽��� ���ΰ� ��������� �װ� ������ �̷��� ��.

	bool m_bCreate;
	
	bool m_bModalDialog;

	bool m_bShowHideMethod;

	SI16 m_siDrawOption;
	SI16 m_siAlphaValue;

	SI32 m_siFadeInTime;
	DWORD m_dwShowStartTime;
};

#endif