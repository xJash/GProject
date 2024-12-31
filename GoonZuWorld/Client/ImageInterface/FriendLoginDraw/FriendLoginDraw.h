#ifndef _FRIENDLOGINDRAW_H_
#define _FRIENDLOGINDRAW_H_

#include <Graphic.h>
#include <Graphic_Capsule.h>

#define MAX_FRIENDLOGIN_WIDTH			200
#define MAX_FRIENDLOGIN_HEIGHT			200



class CFriendLoginDraw
{
public:
	CFriendLoginDraw();
	~CFriendLoginDraw();

	void Initialize();	

	void Set( TCHAR *CharName );
	void Action();
	void Draw( SI32 XMovePos, SI32 YMovePos );

private:


	RGB16*					m_pImageBuffer;
	
	LPDIRECTDRAWSURFACE7	m_lpSurface;
	TSpr					*m_pLoginSpr;
	


	bool					m_bShow;
	SI32					m_siFrameCount;
	
	SI32					m_siContinueCount;
	
	SI32					m_siCurrentImageYPos;

};

#endif
