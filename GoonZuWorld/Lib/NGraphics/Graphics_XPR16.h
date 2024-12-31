#ifndef _GRAPHICS_XPR16_H
#define _GRAPHICS_XPR16_H

class XPR16
{
public:
	XPR16();
	~XPR16();

	void		Destroy();
	bool		LoadFromSpr16( TCHAR *szFilename );		

	void		PutXpr16( int x, int y, int font );
	void		PutXpr16A( int x, int y, int font, int alpha );

public:
	SI32		m_siFontNum;			// ��Ʈ ����
	SI32		m_siXSize;				// x size
	SI32		m_siYSize;				// y size

	RGB16**		m_ppImage;				// �̹��� 

	RGB16		m_colorkey;				// �����
};

#endif