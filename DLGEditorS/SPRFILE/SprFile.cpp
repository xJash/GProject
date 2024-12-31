#include "stdafx.h"
#include "SprFile.h"


cltTSpr::cltTSpr()
{
	Image = NULL;
}

cltTSpr::~cltTSpr()
{
	if(Image)
	{
		delete [] Image;
		Image = NULL;
	}
}

void cltTSpr::ClearImageData()
{
    if(Image)
	{
		delete [] Image;
		Image = NULL;
		clHeader.siVersion		= NSPR_VERSION;
		clHeader.siSprType		= SPRTYPE_SPR;
		clHeader.siXsize			= 0;
		clHeader.siYsize			= 0;	
		clHeader.siHRes			= 0;
		clHeader.siVRes			= 0;

		clHeader.siTotalLength	= 0;
		clHeader.siFontNum		= 0;
	}
}

// spr������ �ҷ��´� 
BOOL cltTSpr::LoadSpr( char* szfilename )
{
	FILE *fp;

	if(szfilename == NULL || strcmp(szfilename, "") == 0)
	{
		return FALSE;
	}
		
	fp = fopen(szfilename, "rb");

	if( !fp )
	{
		CString strTmp = szfilename;
		strTmp += " ������ �����ϴ�..! ���α׷��� ������ Ȯ���ϰ� �ٽ� �����ϼ���!!";
		AfxMessageBox(strTmp);
		return FALSE;
	}
	
	//-------------------------------
	// ����� �д´�. 
	//-------------------------------
	fread( &clHeader, sizeof(cltTSprHeader), 1, fp );
	
	//----------------------------------
	// �ʿ��� ���� �̹��� ���۸� �����.
	//----------------------------------
	if( Image ) delete [] Image;
	Image = new unsigned char[ clHeader.siTotalLength ];
	
	//-----------------------------------
	// �̹����� �ҷ��´�.
	//-----------------------------------
	fread( Image, clHeader.siTotalLength, 1, fp );

	// ���� ������ ���� spr������ �о� ���°Ͱ� ����..


	//--------------------------------------------
	// ������ 400�ΰ�� 16bit�����ȷ�Ʈ�� �ҷ��´� 
	//--------------------------------------------

	// ���� �׷��� ���( 565 or 555 )�� ���� ������ �ȷ�Ʈ�� �ҷ��´� 
	// spr���Ͽ� 565�ȷ�Ʈ( 2 * 256 = 512 byte ), 555�ȷ�Ʈ( 2 * 256 = 512 byte ) ������ ����Ǿ��ִ�

	// ��������Ʈ �� ���������� �ϳ��� ��带 ���ؼ� �о���� �ȴ�. 
	// �����Ҷ��� ���� 565, 555 �ȷ�Ʈ �Ѵ� �����ؾߵȴ� 
	
	// (���⼭�� 565���� ���ؼ� �о���� ������ �ߴ�)
	int mode = 1;

	if( clHeader.siVersion == 400 ) {

		if( mode == 1 ) {
			// 565 ����̸�,
			fread( pal, 512, 1, fp);

		} else {
			// 555 ����̸�, 565�ȷ�Ʈ ��ŵ�ϰ�, 555�ȷ�Ʈ�� �д´� 
			fseek( fp, 512, SEEK_CUR );
			fread( pal, 512, 1, fp);
		}

	}
	
	fclose(fp);

    return TRUE;
}
