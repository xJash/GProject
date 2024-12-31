//---------------------------------
// 2003/7/15 ���°�
//---------------------------------

#ifndef _MAPLAYOR_H
#define _MAPLAYOR_H

#include <Directives.h>
#include <Stdio.h>

//----------------------------------------
// Layor ���� 
//----------------------------------------
class cltMapLayer
{
public:
	cltMapLayer( SI32 xsize, SI32 ysize, SI32* yoff );
	~cltMapLayer();

public:
	BOOL		IsValid();
	BOOL		IsInArea(SI32 x, SI32 y);

	BOOL		SetUnique(SI32 six, SI32 siy, SI32 siunique);
	SI32		GetUnique(SI32 six, SI32 siy);

	BOOL		SetDrawInfo_Unique(SI32 six, SI32 siy, SI32 siunique);
	SI32		GetDrawInfo_Unique(SI32 six, SI32 siy);

	BOOL		SetDrawInfo_Ref(SI32 six, SI32 siy, SI32 siref);
	SI32		GetDrawInfo_Ref(SI32 six, SI32 siy);

	BOOL		SetDrawInfo_File(SI32 six, SI32 siy, SI32 sifileinfo);
	SI32		GetDrawInfo_File(SI32 six, SI32 siy);

	BOOL		SetDrawInfo_Font(SI32 six, SI32 siy, SI32 sifontinfo);
	SI32		GetDrawInfo_Font(SI32 six, SI32 siy);

	BOOL		Write(FILE* fp);
	BOOL		Read(FILE*fp);


public:
	SI32*		YOff;
	SI32		Xsize;
	SI32		Ysize;

	// ����� ���� ���� ���� ����. 	
	// ��¿� Unique (8��Ʈ) | Ref(8��Ʈ) | Ÿ�� ��Ʈ�� �̹��� ���� �ε���(8��Ʈ) | ���ϳ� ��Ʈ (8��Ʈ) 
	DWORD*		pDrawInfo;		
	UI08*		pUnique;		// Ÿ���� ����ũ���� ������ ����			
};


#endif