//---------------------------------
// 2003/7/30 ���°�
//---------------------------------

#ifndef _MUSIC_H
#define _MUSIC_H

#include "..\..\Common\Map\Map.h"
#include "..\..\Lib\Sound\SoundMgr.h"

#define MAX_SOUND_EFFECT_TYPE_NUMBER			1000

//-------------------------------------------------
#define MAX_SOUND_EFFECT_FILE_NAME_PER_SOUND	5
#define MAX_SOUND_EFFECT_NUMBER					800
#define MAX_SOUND_EFFECT_BUFFER_NUMBER			10

#define MAX_SOUND_EFFECT_FILE_NAME_LENGTH		128

class cltClient;

//--------------------------------------
// ȿ���� ����
//--------------------------------------
class cltEffectFile{
public:
	TCHAR szFileName[MAX_SOUND_EFFECT_FILE_NAME_LENGTH];
	DWORD EffectPlayClock;

	cltEffectFile()
	{
		Init();
	}

	void Init()
	{
		StringCchCopy(szFileName, MAX_SOUND_EFFECT_FILE_NAME_LENGTH, TEXT(""));
		EffectPlayClock	= 0;
	}
	
	void Set(TCHAR* name);
};


class _EffectData {
public:
	SI32 EffectNumber;   // ȿ������ ��� �غ�Ǿ� �ִ°�?

	cltEffectFile clEffectFile[MAX_SOUND_EFFECT_FILE_NAME_PER_SOUND];


	_EffectData()
	{
		EffectNumber = 0;
	}

	void Init()
	{
		EffectNumber = 0;
		
		for(SI32 i = 0;i < MAX_SOUND_EFFECT_FILE_NAME_PER_SOUND;i++)
		{
			clEffectFile[i].Init();
		}

	}
	//cyj void Set(TCHAR* szname1, TCHAR* szname2 = NULL, TCHAR* szname3 = NULL, TCHAR* szname4 = NULL, TCHAR* szname5 = NULL);
	void Set(TCHAR* szname);

	void Free();
	TCHAR* Play(SI32 x, SI32 y, cltMapClient* pclMap, bool bgamemode);
};


class _EffectBuffer {
public:
	SI32 Effect;
	SI32 X, Y;
	
	_EffectBuffer()
	{
		Effect = 0;
		X = 0;
		Y = 0;
	}

	void Set(SHORT effect, SHORT x, SHORT y);
};


//--------------------------------------
// cltMusic
//--------------------------------------
class cltMusic{
public:
	cltClient*	pclGame;

	CSoundMgr *pclSoundManager;  // ���� ������. 

	_EffectData		ED[MAX_SOUND_EFFECT_TYPE_NUMBER];

	SI32			EffectBufferIndex;
	_EffectBuffer	EffectBuffer[MAX_SOUND_EFFECT_BUFFER_NUMBER];


	cltMusic(cltClient* pclgame);
	~cltMusic();

	void InitEffectFile();
	void FreeEffect();

	// ���ۿ� ����� �Ҹ��� �ϳ� ������ �����Ѵ�. 
	void PopEffect(cltMapClient* pclMap);
	BOOL PushEffect(SHORT effect, SHORT x, SHORT y);

};


#endif