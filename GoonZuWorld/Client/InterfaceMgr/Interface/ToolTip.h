#ifndef _TOOLTIP_H_
#define _TOOLTIP_H_

#include "../ControllerBaseDefinition.h"
#include <ddraw.h>



class CToolTip
{
public:
	CToolTip();
	~CToolTip();

	LPDIRECTDRAWSURFACE7 GetSurface()
	{
		return m_lpSurface;
	}
	
	void Create( SI16 SurfaceWidth, SI16 SurfaceHeight );

	void SetToolTip( TCHAR *Text ,bool bColor = true );	// ���� ���ԵǾ� �ִٸ� ���ο��� MakeTextImgEncBuffer �� ȣ��
		
	void MakeTextImgEncBuffer();	// �ܻ� �ؽ�Ʈ �̹��� ����
	void MakeColorTextImgEncBuffer();	// �߰��߰� ���� �� �ؽ�Ʈ �̹��� ����
	
	SI16 ChangeText( HDC hDC, SI32 nPos );

	void Draw( SI16 DrawXPos, SI16 DrawYPos );

private:
	LPDIRECTDRAWSURFACE7 m_lpSurface;

	TCHAR m_strText[ MAX_TOOLTIP_MSG_SIZE ];
	bool m_bSetText;

	RGB16* m_ImgEncBuffer;

	SI16 m_siWidth;
	SI16 m_siHeight;

	RECT m_rcToolTip;
	SI32 m_siDrawHeight;
	SI32 m_siDrawWidth;

	SI16	m_siFontWeight;		// ���� ���� ( FW_BOLD )
	SI16	m_siFontHeight;
	SI16	m_siFontWidth;
	COLORREF m_FontColor;

	SI16	m_siOffSet;

	BOOL	m_bColorSwitch;

	HFONT	m_hFont;
	HFONT	m_hOldFont;

};

#endif