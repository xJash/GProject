#ifndef _SOUNDOBJ_H_
#define _SOUNDOBJ_H_

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CSoundObj
//	Desc : CSoundObj Ŭ����
//		   ���� �� ���Ϻ� ��ü
//		   �� ����� wav ���� load �� wav ���� play ���
//	Date : 2003. 06. 24
//	Update : 2003. 06. 26 - m_bLoopStatus �߰�
//							IsPlaying �Լ� ���� ( alGetSourcei �Լ� �̿��ؼ� �˾� �� �� ����. )
//--------------------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "BaseDefineSoundLibInfo.h"

#include "alc.h"
#include "alut.h"

class CSoundObj  
{
public:
	CSoundObj();										// �� �� ��
	~CSoundObj();										// �� �� ��

	void Initialize();									// �� �� ȭ
	void Destroy();										// ����ó��

	void GenerateBuffer();								// ���� ����
	void DeleteBuffer();								// ���� ����

	void DeleteBufferAndSource();						// �ҽ��� ���� ���� ( ���� ������ �ҽ� ������ )
	
	bool LoadWavFile( TCHAR *strFileName );				// Wav ���� �ε�
	//bool PlayWavFile( TCHAR *strFileName, bool bLoop, float fVolume = BASE_SOUND_VOLUME_RATE );									// Wav ���� �о play
	bool PlayPosWavFile( TCHAR *strFileName, bool bLoop, float xPos = 0.0f, float fVolume = BASE_SOUND_VOLUME_RATE );	// ���� �Լ��� Ʋ�� ���� ����Ŀ ��� �ɼ� �¿� �յڰ� ���ٴ� ����
	
	//void Play( bool bLoop, float fVolume = BASE_SOUND_VOLUME_RATE );							// load �� wav ���� play
	void PlayPos( bool bLoop, float xPos = 0.0f, float fVolume =BASE_SOUND_VOLUME_RATE );	// ���� ��� ����(�¿�, �յ�)
	void ReWind();										// �̹� �ε�� wav ������ �ٽ� ���
	void Pause();										// ����
	void Stop();										// play �ǰ� �ִٸ�, �ߴ� ��Ŵ

	bool IsPlaying();									// ���尡 play �ǰ� �ִ��� Ȯ��
	bool IsSameFile( TCHAR *strFileName );				// ���� �������� Ȯ��					

	
	
	
	float GetSoundVolume();								// ���� ���� ũ�⸦ �����
	void SetSoundVolume( float fVolumeRate );			// ���� ���� ũ�� ����
	
	

#ifdef _DEBUG
	TCHAR *GetFileName();								// ���� ���ۿ� �ö� �ִ� ������ �̸��� ����
#endif

private:
	TCHAR			m_strFileName[128];					// wav ���� �̸�

	unsigned int	m_Source;
	unsigned int	m_Buffer;

	float			m_fSourcePos[3];					// ��ǥ ( X, Y, Z ) X �� ����(-) ����(+) ���� ����, Y �� 0.0, Z �� ����( 1.0 �������� ������ �հŸ� ũ�� ����� �Ÿ�, Default = 1.0 )
	float			m_fSourceVel[3];					// �ӵ� -- ���� ��Ȯ�� �������� ������. �ķ� �̷�. �⺻ �V������ 0.0 ���� ��

	float			m_fSoundVolume;						// ���� ũ��
	
};

#endif