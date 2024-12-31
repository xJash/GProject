//---------------------------------
// 2003/6/9 ���°�
//---------------------------------

#ifndef _HELP_H
#define _HELP_H


#include <Directives.h>

#include <ddraw.h>

#define MAX_HELP_NUMBER  10
#define MAX_HELP_TILE_LENGTH   64

#define HELP_SURFACE_XSIZE	400
#define HELP_SURFACE_YSIZE	100

#define HELP_OFFSETX	15
#define HELP_OFFSETY	-40

//-----------------------------------
// cltHelp
//-----------------------------------
class cltHelp{
public:
	LPDIRECTDRAWSURFACE7		lpSurface;
	SIZE						ShowSize;
	SI32						siX, siY;

	DWORD						LastUpdateFrame;

	TCHAR szTitle[MAX_HELP_TILE_LENGTH];

	cltHelp(TCHAR* sztitle, SI32 x, SI32 y);
	~cltHelp();

	BOOL Draw(LPDIRECTDRAWSURFACE7 lpdstsurface);

};

//-----------------------------------
// cltHelpManager
//-----------------------------------
class cltHelpManager{
public:
	cltHelp* pclHelp[MAX_HELP_NUMBER];

	cltHelpManager();
	~cltHelpManager();

	// Help��ü�� �����. 
	BOOL Add(TCHAR* sztitle, SI32 x, SI32 y);
	// sztitle�� ���� Help�� �̹� �����ϴ��� Ȯ���Ѵ�.
	SI32 GetHelp(TCHAR* sztitle);

	void SetPos(SI32 ref, SI32 x, SI32 y);

	void DeleteAll();

	// ȭ�鿡 ����Ѵ�.
	BOOL Draw(LPDIRECTDRAWSURFACE7 lpdstsurface);


};

#endif
