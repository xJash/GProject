#ifndef _SOUNDMGR_H_
#define _SOUNDMGR_H_

#include <Windows.h>

#include <stdio.h>
#include <Conio.h>
#include "BaseDefineSoundLibInfo.h"

/*
#ifndef OPENAL
#define OPENAL
#include <initguid.h>
#include "eax.h"
#endif
*/
//MAX_REFERENCE_DISTANCE : 4131

#pragma comment( lib, "dsound" )

#pragma comment( lib, "ALut" )
#pragma comment( lib, "OpenAL32" )

#pragma comment( lib, "ogg_static" )
#pragma comment( lib, "vorbis_static" )
#pragma comment( lib, "vorbisfile_static" )

class CSoundObj;
class COggObj;

class CSoundMgr  
{
public:
	enum { FILE_NOT_EXIST };								// ���� �ڵ� ����
	CSoundMgr();											// �� �� ��
	~CSoundMgr();											// �� �� ��
	
	void Initialize();										// �� �� ȭ
	void Destroy();											// ����ó��

	bool Create( HWND hWnd );								// �ʱ�ȭ���� ������ �� ������ ��ü ���� ���� ������ ���ؼ�

	bool SoundDeviceInitialize();							// ���� ��ġ �ʱ�ȭ
	int  IncrementEnv();

	
	bool PlayFile( char *strFileName, bool bLoop = false, bool bForceSoundPlay = false, float xPos = 0.0f, float fVolume = BASE_SOUND_VOLUME_RATE, bool bSameSoundPlaying = false );	// ���� �Լ��� Ʋ�� ���� ��ǥ�� �߰� �Ǿ� �ִٴ� ����. ( xPos : �� ( ���� ), �� ( ��� ) ) , ������ ũ��( 100 �̸� �ִ� ���� ũ�� ), ���� ���� �ٸ� ���ۿ��� �� �����ؼ� ��� ����	
	bool PlayBackGroundFile( char *strFileName, bool bLoop = false, bool bForceSoundPlay = false );

	bool GetSoundVolume( char* strFileName, float *pfOutSoundVolume );	// Ư�� ������ ���� ���� ũ�⸦ ��� ��
	bool GetBackGroundSoundVolume( char *strFileName, long *pOutSoundVolume );	// ���� ���� ( ��� ���ǿ� )

	char IsFileAlreadyExist( char *strFileName );			// ������ ��ü�� �ִ� ������ Ȯ���ϴ� ��.
	char IsBackGroundFileAlreadyExist( char *strFileName );	// ���� ���� ( ��� ���ǿ� )

	bool IsBackGroundFilePlaying();							// ��������� ������̳�?
	
	void SoundStop( char index );							// �ϳ��� ���带 ���� ��Ų��.
	void AllSoundStop();									// ��� ���带 ���� ��Ų��.	
	void BackGroundSoundStop();								// ���� ���� ���� ���� ��Ų��.
	

	void EffectSoundOn( bool bEffectSoundOn );
	void BackGroundSoundOn( bool bBackGroundSoundOn );

	void SetSoundVolume( float soundvolumepercent  );
	void SetBackGroundSoundVolume( int soundvolume );

	
#ifdef _DEBUG
	// �׽�Ʈ�� �Լ���
	bool IsPlaying( int );									// ����Ʈ�� �ִ� �� ��° ��ü�� ���� ����������� ���� ( �Ķ���ʹ� �Է°��� )
	void PrintAllFileName();								// ����Ʈ�� �ִ� ��� wav ���� �̸� ���
#endif



private:	
	HANDLE			m_hSrch;								// ���� ���� ���� üũ �ϱ� ���� �ڵ�
	WIN32_FIND_DATA m_wfd;

	char			m_cSoundIndexLoop;						// MAX_SOUND_BUFFER_NUM �� ��ŭ ���� �ְ� ������ �� ���� ���ϵ� ������ �����鼭, �ֱٿ����� �� ����� ������� �ؾ� �ǹǷ�... ���� ��Ű�� ����� ���� ������... MAX_SOUND_BUFFER_NUM ���� ���� ���� 0���� �ٽ� ���� ����ť ���� ����... �ּ��� ����...
	char			m_cBackGroundSoundIndexLoop;			// ���� ���� ( ��� ���ǿ� )
	
	bool			m_bEffectSoundOn;
	bool			m_bBackGroundSoundOn;


	float			m_fListenerPos[3];
	float			m_fListenerVelocity[3];
	float			m_fListenerOrientation[6];
	
	COggObj			*m_pOggObjList;							// ��� ���� ��ü ����Ʈ
	CSoundObj		*m_pSoundObjList;						// ���� ��ü ����Ʈ

	float m_srEffSoundVolumeLate;
	int m_siBGMSoundVolume;
	
	CRITICAL_SECTION m_SoundListCrit;						// ���� �ε��ҷ��� �ϴµ�, �� �ε��ϴ� �� �׷� �ߺ� �Ǵ� ��츦 ���� ���ؼ�... �Ϲ������� ����Ʈ�� �� ���ִ� ������...
};

#endif