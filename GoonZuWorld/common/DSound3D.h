///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/// HQteam Sound Library
/// 1�� 30�� ..				������
//////////////////////////////////////////////////////////

#ifndef __DS3D_H_
#define __DS3D_H_

// Includes....
#include <dsound.h>
#include <stdio.h>
#include <wavread.h>

// Defines....
#define NUM_SOUNDS      200

#define	JDS_LEFTMAX		(-100)						//�ְ� ������ MAX ���� -100
#define	JDS_RIGHTMAX	(100)						//�ְ� �������� MAX ���� 100

#define	DSOUND3D_CD_SOUNDPRESENT	1				//CD�� Condition�� ����.
#define	DSOUND3D_UCD_SOUNDPRESENT	2				//UCD�� UnCondition�� ����.


// The following macros are used for proper error handling for DirectDraw,
// DirectSound

#define TRY_DS(exp) { { HRESULT rval = exp; if (rval != DS_OK) { TraceErrorDS(rval, __FILE__, __LINE__); return FALSE; } } }

class _MyDirectSound {
public:
	HWND Hwnd;       
	// Globals.... ��������
	LPDIRECTSOUND           g_lpDS;            // DirectSound object
    LPDIRECTSOUNDBUFFER     pDSBPrimary ;

	
	BOOL                    g_bSoundPresent;  // Do we have sound capabilites?
	
	CHAR                    g_sError[1024];
	BOOL                    g_bErrorOccured;
	
	DWORD			        g_dwMainVolume;
	
	LPDIRECTSOUNDBUFFER     g_lpSounds[NUM_SOUNDS];   // Sound buffers
	DWORD					g_StartTime[NUM_SOUNDS];
	DWORD					g_Playtime[NUM_SOUNDS];

	// ������. 
	_MyDirectSound(){Init();}
	void Init();
	BOOL  InitSounds(HWND hwnd);
	BOOL  CloseSounds();
	// primary ���� ������ �����Ѵ�. 
    BOOL SetPrimaryBuffer(SHORT channel_number, SHORT samples_per_sec, DWORD bit_per_samples, BOOL loop_switch);

	void  TraceErrorDS(HRESULT hErr, CHAR *sFile, INT nLine);
	void  RegError(CHAR *sErr);
	DWORD CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, LPWAVEFORMATEX pcmwf);
	BOOL  ReadWaveData(LPDIRECTSOUNDBUFFER lpDSB,FILE * pFile , DWORD dwSize, DWORD dwPos);
	BOOL  ReadWaveData(LPDIRECTSOUNDBUFFER lpDSB, LPBYTE lpData , DWORD dwSize);
	DWORD FindEmptyHandle();
	DWORD LoadYAVFile(CHAR* FileName, DWORD dwFlags = DSOUND3D_CD_SOUNDPRESENT, DWORD MaxDelayTime = 0);
	DWORD LoadWaveFile(CHAR* FileName, DWORD Flags);
	BOOL  StopAllSounds();
	BOOL  StopSound(DWORD dwSound);
	BOOL  PlaySound3D(DWORD dwSound, INT x, INT y, BOOL bLoop = FALSE, BOOL bStopWhilePlay = FALSE);
	BOOL  PlaySound(DWORD dwSound, BOOL bLoop = FALSE, BOOL bStopWhilePlay = FALSE);
	BOOL  FreeSound(DWORD dwSound);
	BOOL  FreeAllSounds();
	BOOL  SetSoundVolume(DWORD dwVolume);
	BOOL  Set3DSoundVolume(DWORD channel, DWORD dwVolume);
	BOOL  SetSoundVolume(DWORD channel, DWORD dwVolume);
	BOOL  SetSoundPan(long lPan);
	BOOL  SetSoundPan(DWORD channel, long lPan);
	BOOL  GetSoundVolume(DWORD* dwVolume);
	BOOL  IsPlayingSound(DWORD dwSound, BOOL bNotUsedTime = FALSE);
	DWORD	GetPlayTime(DWORD DataSize, DWORD BytePerSec);
	HRESULT FillBuffer(LPDIRECTSOUNDBUFFER lpDSBuffer, CWaveSoundRead* lpWaveSoundRead, DWORD dwBufferBytes);
	BOOL IsValidSound(DWORD dwSound);
	BOOL IsPresentSound();

	// ȿ������ ���� ��ġ�� �����Ѵ�. 
	BOOL SetCurrentPosition(DWORD dwSound, int pos);
	// ��� ȿ������ ���� ��ġ�� �����Ѵ� .
	BOOL SetAllCurrentPosition(int pos);

};


#endif



