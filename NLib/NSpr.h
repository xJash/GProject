//-----------------------------------------------------------------------------
// 2005/09/20 ������
//-----------------------------------------------------------------------------

#ifndef _NSPR_H
#define _NSPR_H

#include "NDraw.h"

#define NSPRLOAD_PAL_RGB565		1
#define NSPRLOAD_PAL_RGB555		2
#define NSPRLOAD_PAL_BOTH		3

#define NSPR_ENCODETYPE_NONE	0
#define NSPR_ENCODETYPE_NPR1	1

#define NSPR_VERSION			100

struct NSprHeader
{
	char	id[ 4 ];			// "NPR"	
	
	short	version;			// ����
	short	encodeType;			// 0:none	1:npr1

	int		fileSize;			// ���� ũ��

	short	canvasWidth;		// ĵ���� �ʺ�
	short	canvasHeight;		// ĵ���� ����

	short	rowNum;				// �� ����
	short	colNum;				// �� ����

	short	imageNum;			// �̹��� ����
	short	colorNum;			// �ȷ�Ʈ ���� ����

	int		offsetImageInfo;	// �̹��� ������ ������
	int		offsetImageData;	// �̹��� �������� ������

	int		offsetPal565;		// 16��Ʈ 565�ȷ�Ʈ�� ������
	int		offsetPal555;		// 16��Ʈ 555�ȷ�Ʈ�� ������

	char	reserved[ 24 ];		// ����

};

struct NSprImageInfo
{
	int		offset;				// �̹��� ������ ���� ��ġ�� ������ ������
	int		size;				// �̹��� ũ��
	short	x;					// ĵ�������� x ��ġ
	short	y;					// ĵ�������� y ��ġ
	short	width;				// �̹��� �ʺ�
	short	height;				// �̹��� ����
};

class NSpr
{
public:
	NSpr();
	~NSpr();

	void				CreateSpr( int width, int height, int imageNum );
	void				LoadSprFromFile( char *filename );


public:
	NSprHeader*			pHeader;

	NSprImageInfo*		pImageInfo;
	unsigned char*		pImageData;

	RGB16*				pPal565;
	RGB16*				pPal555;

	unsigned char*		m_pBuffer;

};

#endif