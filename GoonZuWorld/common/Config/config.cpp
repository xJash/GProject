//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"

#include "..\Client\Client.h"

#include "config.h"
#include "..\Lib\Sound\SoundMgr.h"

extern cltCommonLogic* pclClient;

cltConfig::cltConfig(TCHAR* filename)
{
	ZeroMemory(this, sizeof(cltConfig));     

	StringCchCopy(FileName, FILE_NAME_SIZE, filename);

	siGameSpeed   = 2;                      
	siSoundVolume = 80;                     

	siGamma       = 10;                 
    
	Load();
}

cltConfig::~cltConfig()
{
	Save();
}

void cltConfig::SetSoundVolume(SI32 volume)
{
	siSoundVolume = volume;
	SetSoundVolume();
}

void cltConfig::SetSoundVolume()
{
	//g_pSoundManager->SetAllSoundVolume((UI16)(siSoundVolume  * 10));
}



BOOL cltConfig::Save()
{
	FILE* fp;

	fp=_tfopen(FileName, TEXT("wb"));
	if(fp==NULL)	return FALSE;
	
	fwrite(this, sizeof(cltConfig), 1, fp);

	fclose(fp);

	return TRUE;
}


BOOL cltConfig::Load()
{
	FILE* fp;

	fp=_tfopen(FileName, TEXT("rb"));
	if(fp==NULL)	return FALSE;

	fread(this, sizeof(cltConfig), 1, fp);

	fclose(fp);


	return TRUE;
}

BOOL cltConfig::GammaFunction(SI32 mount)
{

	// �־��� ����ŭ �ȷ�Ʈ�� ���� �����Ѵ�.
	siGamma = mount;

	//cyj ������ ����.
	//pclClient->GammaFunction(mount);


	return TRUE;

}




