#pragma once

#ifndef _COMMON_H
#define _COMMON_H

#include "stdafx.h"

#include "directives.h"

//-------------------------------------------------
// Spr ���� 
//-------------------------------------------------
#define SPRTYPE_SPR				0	// �Ϲ� ��������Ʈ (0�� ����. ) 
#define SPRTYPE_TLE				1	// Ÿ�Ͽ� ��������Ʈ (0�� ����.) 

//-------------------------------------------------
// ��� �Ӽ�. 
//-------------------------------------------------
#define SPRATB_DOT				1

//-------------------------------------------------
// cltTSprImgInfo
//-------------------------------------------------
class cltTSprImgInfo{
public:
	SI32 siCollInfo;
	SI32 siStartPos;
	SI32 siLength;

	cltTSprImgInfo()
	{
		siCollInfo	= 0;
		siStartPos	= 0;
		siLength	= 0;
	}

};

//-------------------------------------------------
// cltTSprHeader
//-------------------------------------------------
#define TSPR_VERSION			10
#define NSPR_VERSION			400

#define MAX_IMG_PER_TSPR		256	// Spr ���� �ϳ��� �̹����� ����.

class cltTSprHeader
{
public:
   SI32 siVersion;
   SI32	siSprType;		// � Ÿ���� Spr�ΰ� ?
   SI32 siXsize;
   SI32 siYsize;
   SI32 siHRes;
   SI32 siVRes;
   SI32 siTotalLength;

   SI32 Reserved[8];
   
   SI32 siFontNum;
   cltTSprImgInfo clImgInfo[MAX_IMG_PER_TSPR];
   
   cltTSprHeader()
   {
	   //siVersion		= TSPR_VERSION;
	   siVersion		= NSPR_VERSION;
	   siSprType		= SPRTYPE_SPR;
	   siXsize			= 0;
	   siYsize			= 0;	
	   siHRes			= 0;
	   siVRes			= 0;
	   
	   siTotalLength	= 0;
	   siFontNum		= 0;
   }
   
};



//-----------------------------------------------
// cltTSpr
//-----------------------------------------------
class	cltTSpr
{     
public:
	cltTSprHeader	clHeader;
	UI08			*Image;

	UI16			pal[ 256 ];

	cltTSpr();
	~cltTSpr();

	BOOL			LoadSpr( char *filename );
};

#define RGB16_565_RMASK		0xF800	
#define RGB16_565_GMASK		0x07E0
#define RGB16_565_BMASK		0x001F

#define RGB16_555_RMASK		0x7C00
#define RGB16_555_GMASK		0x03E0
#define RGB16_555_BMASK		0x001F



// Standard PCX header
struct PCXHEADER {
	char	id;
	char	version;
	char	encoding;
	char	bitPerPixel;
	short	x1;
	short	y1;
	short	x2;
	short	y2;
	short	hRes;
	short	vRes;
	char	clrMap[16*3];
	char	reserved1;
	char	numPlanes;
	short	BPL;
	short	pal_type;
	char	filler[58];
};

struct XSPRFileHeader
{
	char	id[ 4 ];					// "XPR"
	int		filesize;					// ������üũ��
	char	version;					// 1
	char	encodetype;					// 1: spr  2: mpr  3: zpr
	char	pixelformat;				// 0: 8bit indexed  1: 16bit 565  2: 16bit 555
	char	pal_type;					// 0: no palette  16: (565, 555)  24:(888)
	short	canvasWidth;				// ĵ���� �ʺ�
	short	canvasHeight;				// ĵ���� ���� 
	short	xnum;						// ���� ����
	short	ynum;						// ���� ����

	char	reserved1[ 20 ];			// ����1

	// body info 
	int		bodysize;					// �̹��� �±� + �̹��� ������ ũ��
	int		imagenum;					// �̹��� ���� 

	char	reserved2[ 16 ];			// ����2
};

struct XSPRImgTag
{
	int				offset;
	int				size;
	short			x;
	short			y;
	short			width;
	short			height;
};

struct XSPRFilePalette
{
	unsigned short pal565[ 256 ];
	unsigned short pal555[ 256 ];
};

class XSpr
{
public:
	XSpr();
	~XSpr();

	BOOL LoadXSpr( char *filename );

public:
	XSPRFileHeader		m_header;
	
	unsigned char*		m_pBody;

	XSPRImgTag*			m_pImageTag;
	unsigned char*		m_pImage;
	unsigned short*		m_pPal;
};

struct PCXPAL {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

#endif