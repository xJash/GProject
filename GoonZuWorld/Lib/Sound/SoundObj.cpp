#include "SoundObj.h"
#include "Directives.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CSoundObj::CSoundObj()
//	Desc : �� �� ��
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
CSoundObj::CSoundObj()
{
	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CSoundObj::~CSoundObj()
//	Desc : �� �� ��
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
CSoundObj::~CSoundObj()
{
	Destroy();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::Initialize()
//	Desc : �� �� ȭ
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::Initialize()
{
	ZeroMemory( m_strFileName, 64 );
	//ZeroMemory( m_strFileName, sizeof(&m_strFileName) );
	
	m_fSourcePos[ 0 ] = 0.0f;
	m_fSourcePos[ 1 ] = 0.0f;
	m_fSourcePos[ 2 ] = 1.0f;

	m_fSourceVel[ 0 ] = 0.0f;
	m_fSourceVel[ 1 ] = 0.0f;
	m_fSourceVel[ 2 ] = 0.0f;

	m_fSoundVolume = BASE_SOUND_VOLUME_RATE;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::Destroy()
//	Desc : ���� ó��
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::Destroy()
{
	DeleteBufferAndSource();
	
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::DeleteBufferAndSource()
//	Desc : �ҽ��� ���� ���� ( ���� ������ �ҽ� ������ )
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::DeleteBufferAndSource()
{
	if ( IsPlaying() )
	{
		Stop();
	}

	alDeleteSources( 1, &m_Source );
	alDeleteBuffers( 1, &m_Buffer );

	Initialize();		//SOUND_STOP �ϰ� �����̸� NULL �� �����ϰ�...

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundObj::LoadWavFile( TCHAR *strFileName )
//	Desc : wav ���� �ε�
//	Date : 2003. 06. 30
//	Update : 
//--------------------------------------------------------------------------------------------
bool CSoundObj::LoadWavFile( TCHAR *strFileName )
{
	char cloop;
	
	// create buffer
	alGetError();							/* clear */

	alGenBuffers( 1, &m_Buffer );
	
	if(alGetError() != AL_NO_ERROR) 
	{
	   return false;
	}

	// create source
	alGetError();							/* clear */

	// load data into buffer
	ALsizei size, freq;
	ALenum format;
	ALvoid *data;

	int error;
	CHAR strDest[256];
	//�Ŀ� wav ���� ������ �ٲ� ���, �Ʒ��� �Լ��� alutLoadWAVMemory �� ��ü�ϸ� ��

#ifndef _UNICODE
	StringCchCopy( strDest, 256, strFileName);
#else
	WideCharToMultiByte( CP_ACP, 0, strFileName, -1, strDest, 256 , NULL, NULL );
#endif
	
	alutLoadWAVFile( strDest , &format, &data, &size, &freq, &cloop );
	
	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf("alutLoadWAVFile error %s", strFileName );
		// Delete Buffers
		alDeleteBuffers( 1, &m_Buffer );
		return false;
	}

	alBufferData ( m_Buffer, format, data, size, freq);

	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf("alBufferData buffer error\n");
		alDeleteBuffers( 1, &m_Buffer );
		return false;
	}

	// Unload footsteps.wav
	alutUnloadWAV( format, data, size, freq );
	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf("alutUnloadWAV error\n");
		// Delete buffers
		alDeleteBuffers( 1, &m_Buffer );
		return false;
	}

	alGenSources( 1, &m_Source );
	
	if(alGetError() != AL_NO_ERROR)
	{
	   return false;
	}

	/*
	alSourcef( m_Source, AL_PITCH, 1.0f);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alSourcef 0 AL_PITCH : %d\n", error);
	}

	alSourcef( m_Source, AL_GAIN, 1.0f);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alSourcef 0 AL_GAIN : %d\n", error);
	}

	m_fSourcePos[0] = xPos;
	m_fSourcePos[1] = 0.0f;
	m_fSourcePos[2] = fNear;

	
	alSourcefv( m_Source, AL_POSITION, m_fSourcePos );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alSourcefv 0 AL_POSITION : %d\n", error);
	}
	
	alSourcefv( m_Source,AL_VELOCITY, m_fSourceVel );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alSourcefv 0 AL_VELOCITY : %d\n", error);
	}
	*/

	// setup source
	alSourcei( m_Source, AL_BUFFER, m_Buffer );
	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf("alSourcei AL_BUFFER 0 error\n");
		return false;
	}
	
	return true;
}

/*
//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundObj::PlayWavFile(TCHAR *strFileName, bool bLoop)
//	Desc : Wav ���� load �Ŀ� ���
//	Date : 2003. 06. 25
//	Update : 
//--------------------------------------------------------------------------------------------
bool CSoundObj::PlayWavFile(TCHAR *strFileName, bool bLoop, float fVolume )
{
	if ( ! LoadWavFile ( strFileName ) )
	{
		return false;
	}

	if ( strFileName == NULL )
	{
		return false;
	}

	strcpy( m_strFileName, strFileName );
	
	Play( bLoop, fVolume );

	return true;
}
*/

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundObj::PlayWavFile( TCHAR *strFileName, bool bLoop, float xPos, float yPos, float fNear = 1.0 )
//	Desc : ���� �Լ��� Ʋ�� ���� ����Ŀ ��� �ɼ� �¿� �յڰ� ���ٴ� ����.
//	Date : 2003. 06. 30
//	Update : ;	
//--------------------------------------------------------------------------------------------
bool CSoundObj::PlayPosWavFile( TCHAR *strFileName, bool bLoop, float xPos, float fVolume )
{
	if ( ! LoadWavFile ( strFileName ) )
	{
		return false;
	}

	if ( strFileName == NULL )
	{
		return false;
	}

	StringCchCopy( m_strFileName, 128, strFileName );
	
	PlayPos( bLoop, xPos, fVolume );

	return true;
}

/*
//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::Play( bool bLoop, int siVolume )
//	Desc : load �� wav ���� play
//	Date : 2003. 06. 25
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::Play( bool bLoop, float fVolume )
{
	int error;

	alSourceStop( m_Source );

	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf("alSourceStop error 1 \n");
	}
	
	if ( bLoop )
	{
		alSourcei( m_Source, AL_LOOPING, AL_TRUE );
	}
	else
	{
		alSourcei( m_Source, AL_LOOPING, AL_FALSE );
	}

	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf(  TEXT("alSourcei AL_BUFFER 0 : error\n") );
	}

	SetSoundVolume( fVolume );
	alSourcef( m_Source, AL_REFERENCE_DISTANCE, m_fSoundVolume );

	alSourcePlay( m_Source );

	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf(  TEXT("alSourcePlay 0 error\n") );
	}	

	return;
}
*/

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::ReWind()
//	Desc : ���� ��� ����
//		   xPos : �� ( ���� ), �� ( ��� ) fNear : �� ( ���� ), ��( ��� )
//	Date : 2003. 06. 30
//	Update : 2003. 07. 07 - ���� ũ�� ���� �߰�
//--------------------------------------------------------------------------------------------
void CSoundObj::PlayPos( bool bLoop, float xPos, float fVolume )
{
	int error;

	alSourceStop( m_Source );
	
	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		printf("alSourceStop error 1 \n");
	}
	
	if ( bLoop )
	{
		alSourcei( m_Source, AL_LOOPING, AL_TRUE );
	}
	else
	{
		alSourcei( m_Source, AL_LOOPING, AL_FALSE );
	}

	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		//printf(  TEXT("alSourcei AL_BUFFER 0 : error\n") );
	}
	
	/*
	playerPos[0] += distance * (float) sin(angle + playerAngle);
	playerPos[2] -= distance * (float) cos(angle + playerAngle);
	*/
	
	m_fSourcePos[ 0 ] = xPos;			// �� �� ����Ŀ ��� ��ǥ ����
	m_fSourcePos[ 1 ] = 0.0f;
	m_fSourcePos[ 2 ] = 1.0f;

	
	
	alSourcefv( m_Source, AL_POSITION, m_fSourcePos );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		printf("alSourcefv 0 AL_POSITION : %d\n", error);
	}

	SetSoundVolume( fVolume );
	alSourcef( m_Source, AL_REFERENCE_DISTANCE, m_fSoundVolume );
	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		//printf(  TEXT("alSourcePlay 0 error\n") );
	}
	
	alSourcePlay( m_Source );

	if ( ( error = alGetError()) != AL_NO_ERROR )
	{
		//printf(  TEXT("alSourcePlay 0 error\n") );
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::ReWind()
//	Desc : �̹� �ε�� wav ������ �ٽ� ���
//	Date : 2003. 06. 30
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::ReWind()
{
	alSourceRewind( m_Source );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::Pause()
//	Desc : ����
//	Date : 2003. 06. 30
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::Pause()
{
	alSourcePause( m_Source );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::Stop()
//	Desc : Play �ǰ� �ִٸ�, Stop ��Ŵ
//	Date : 2003. 06. 25
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::Stop()
{
	if ( IsPlaying() )
	{
		int error;

		alSourceStop( m_Source );

		if ((error = alGetError()) != AL_NO_ERROR)
		{
			//printf(  TEXT("Stop Error\n") );
		}
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundObj::IsSameFile( TCHAR *strFileName )
//	Desc : ���� ���ۿ� �ִ� ���� ���ϰ� ���� �������� Ȯ��
//	Date : 2003. 06. 25
//	Update : 
//--------------------------------------------------------------------------------------------
bool CSoundObj::IsSameFile( TCHAR *strFileName )
{
	if ( m_strFileName == NULL )
	{
		return false;
	}

	size_t length = 0;
	StringCchLength( m_strFileName, 128 , &length  );
	if ( length < 2 )
	{
		return false;
	}

	if ( _tcscmp( m_strFileName, strFileName ) == 0 )
	{
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundObj::IsPlaying()
//	Desc : ���� ���ۿ� �ִ� ���� ������ �÷��� ������ Ȯ��
//	Date : 2003. 06. 25
//	Update : 2003. 06. 26 - IsPlaying �Լ� ���� ( alGetSourcei �Լ� �̿��ؼ� �˾� �� �� ����. )
//--------------------------------------------------------------------------------------------
bool CSoundObj::IsPlaying()
{
	int iStatus = 0;

	alGetSourcei( m_Source, AL_SOURCE_STATE, &iStatus );

	if ( iStatus == AL_PLAYING )
	{
		return true;
	}
	
	return false;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - float CSoundObj::GetSoundVolume( int siVolumeRate )
//	Desc : ���� ���� ������ �����
//	Date : 2003. 07. 07
//	Update : 
//--------------------------------------------------------------------------------------------
float CSoundObj::GetSoundVolume()
{
	return m_fSoundVolume;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundObj::SetSoundVolume( float fVolumeRate )
//	Desc : m_fSoundVolume �� ����
//	Date : 2003. 07. 07
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundObj::SetSoundVolume( float fVolumeRate )
{	
	m_fSoundVolume = fVolumeRate;
	return;
}














//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com)
//	Desc : ���� release Mode ������ �ʿ� ���� �ڵ�.
//	Date : 2003. 06. 30
//	Update : 
//--------------------------------------------------------------------------------------------
#ifdef _DEBUG
// ���� ���ۿ� �ö� �ִ� ������ �̸��� ����
TCHAR *CSoundObj::GetFileName()
{
	return m_strFileName;
}
#endif