#ifndef _COMMON_H
#define _COMMON_H


#include "Directives.h"
#include <windows.h>

///////////////////////////
// PCX ���� 
///////////////////////////
struct PCXPAL {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class _head
 {
   public:
   char maker;
   char  ver;
   char encode;
   char bpp;

   short int xmin,ymin;
   short int xmax,ymax;		//!!���� ���� �ִ밪
   short int hres,vres;		//!!���� ���� �ػ�

   char palette[48];

   char  vmode;
   char  nplanes;

   short int bpl;			//!!�� �ٴ� �� ����Ʈ ..
   short int palette_type;
   short int shres;			//!!�ػ�  ���� hres
   short int svres;			//!!�ػ�  ���� vres

   char unused[54];
};

class _tail 
{
public:
	char identification;          
	unsigned char palette[768];    //!!�ȷ�Ʈ..
};

struct PCX 
{
	 _head Head;
	 _tail Tail;
	 
	 unsigned char *Image;
};


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
	   siVersion		= TSPR_VERSION;
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

	   cltTSpr(){Image = NULL;}
	   ~cltTSpr()
	   {
		   if(Image)
		   {
			   delete [] Image;
			   Image = NULL;
		   }
	   }
};

#define RGB16_565_RMASK		0xF800	
#define RGB16_565_GMASK		0x07E0
#define RGB16_565_BMASK		0x001F

#define RGB16_555_RMASK		0x7C00
#define RGB16_555_GMASK		0x03E0
#define RGB16_555_BMASK		0x001F

#endif