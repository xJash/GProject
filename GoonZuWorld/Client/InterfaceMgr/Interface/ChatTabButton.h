#ifndef _IMAGEBUTTON_H_
#define _IMAGEBUTTON_H_

#include "Static.h"
#include "Button.h"

class CControllerMgr;


// [����] 2006.01.12 ���� ����. ä�ù� ���̾�α׸� ���� ������ �������̽�. ����� �����ʿ�.
class CChatTabButton : public CButton
{
public:
	CChatTabButton( CControllerMgr *pParent );
	~CChatTabButton();

	void Create( SI16 ControllerID, TCHAR *Text, TCHAR *FileName, SI16 FontIndex, bool BKTileImg, SI16 BKTileImgNum, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, SI16 SurfaceWidth, SI16 SurfaceHeight );
	void DrawController( SI16 BaseXPos, SI16 BaseYPos, int LeftTime = 0 );
	//void SetInImageFontIndex( SI16 InImageFontIndex );
	void SetSelect(BOOL select){	m_bSelected = select;  };
	BOOL IsSelected(){	return m_bSelected;	};

protected:
	
	BOOL m_bSelected;
};

#endif
