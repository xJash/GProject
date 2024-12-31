#include "stdafx.h"
#include "common.h"

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

// spr������ �ҷ��´� 
BOOL cltTSpr::LoadSpr( char* szfilename )
{
	FILE *fp;

	fp = fopen(szfilename, "rb");

	if( !fp ) return FALSE;
	
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

XSpr::XSpr()
{
	m_pBody = NULL;
	m_pImageTag = NULL;
	m_pImage = NULL;
	m_pPal = NULL;
}

XSpr::~XSpr()
{
	if( m_pBody ) delete [] m_pBody;

	m_pImageTag = NULL;
	m_pImage = NULL;
	m_pPal = NULL;
}

