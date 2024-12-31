#include "SoundMgr.h"
#include "SoundObj.h"

#include "OggObj.h"

/*
#ifdef AC3BACKGROUND
#include "eaxac3.h"

LPEAXAC3FNTABLE g_lpEAXAC3FnTable;
bool g_bEAXAC3DeviceOpen;
bool g_bPlayingAC3;
AC3STREAM ac3Stream;
#endif
*/

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CSoundMgr::CSoundMgr()
//	Desc : �� �� ��
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
CSoundMgr::CSoundMgr()
{

	m_bEffectSoundOn = true;
	m_bBackGroundSoundOn = true;

	m_cSoundIndexLoop = 0;
	m_cBackGroundSoundIndexLoop = 0;

	m_pSoundObjList = NULL;

	m_srEffSoundVolumeLate = 1.0f;
	m_siBGMSoundVolume = BASE_BACKGROUND_SOUND_VOLUME;
    
	m_fListenerPos[ 0 ] = 0.0f;
	m_fListenerPos[ 1 ] = 0.0f;
	m_fListenerPos[ 2 ] = 0.0f;

	m_fListenerVelocity[ 0 ] = 0.0f;
	m_fListenerVelocity[ 1 ] = 0.0f;
	m_fListenerVelocity[ 2 ] = 0.0f;

	m_fListenerOrientation[ 0 ] = 0.0f;
	m_fListenerOrientation[ 1 ] = 0.0f;
	m_fListenerOrientation[ 2 ] = -1.0f;
	m_fListenerOrientation[ 3 ] = 0.0f;
	m_fListenerOrientation[ 4 ] = 1.0f;	
	m_fListenerOrientation[ 5 ] = 0.0f;

	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CSoundMgr::~CSoundMgr()
//	Desc : �� �� ��
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
CSoundMgr::~CSoundMgr()
{
	Destroy();

	alutExit();	
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundMgr::Initialize()
//	Desc : �� �� ȭ
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundMgr::Initialize()
{	

	m_hSrch = INVALID_HANDLE_VALUE;

	if ( m_pSoundObjList )
	{
		delete [] m_pSoundObjList;
		m_pSoundObjList = NULL;
	}

	m_srEffSoundVolumeLate = 1.0f;
	m_siBGMSoundVolume = BASE_BACKGROUND_SOUND_VOLUME;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundMgr::Destroy()
//	Desc : ���� ó��
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundMgr::Destroy()
{
	m_hSrch = INVALID_HANDLE_VALUE;

	AllSoundStop();

	if ( m_pSoundObjList )
	{
		delete [] m_pSoundObjList;
		m_pSoundObjList = NULL;
	}

	if ( m_pOggObjList )
	{
		delete [] m_pOggObjList;
		m_pOggObjList = NULL;
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundMgr::Create( HWND hWnd )
//	Desc : �ʱ�ȭ���� ������ �� ������ ��ü ���� ���� ������ ���ؼ�
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
bool CSoundMgr::Create( HWND hWnd )
{
	m_pOggObjList = new COggObj[ MAX_BACKGROUND_SOUND_NUM ];

	for ( int j = 0; j < MAX_BACKGROUND_SOUND_NUM; ++j )
	{
		m_pOggObjList [ j ].InitDirectSound( hWnd );
	}

	m_pSoundObjList = new CSoundObj[ MAX_SOUND_BUFFER_NUM ];

	if( ! SoundDeviceInitialize() )
	{
		//::MessageBox( NULL, "���� ��ġ �ʱ�ȭ ����", "���� ��ġ �ʱ�ȭ ����", MB_OK|MB_TOPMOST );
		printf("���� ��ġ �ʱ�ȭ ����\n");
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundMgr::SoundDeviceInitialize()
//	Desc : ���� ��ġ �ʱ�ȭ
//	Date : 2003. 06. 24
//	Update : 
//--------------------------------------------------------------------------------------------
bool CSoundMgr::SoundDeviceInitialize()
{
	int error;
	alutInit (NULL, 0);							// init OpenAL

	// Clear Error Code
	alGetError();

	alListenerf(AL_GAIN, 1.0);
	alDopplerFactor(1.0); // don't exaggerate doppler shift
	//alDopplerVelocity(343); // using meters/second

	alListenerfv( AL_POSITION, m_fListenerPos );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		//printf( "alListenerfv POSITION : %d", error);
		return false;
	}

	// Velocity ...
	alListenerfv( AL_VELOCITY, m_fListenerVelocity );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		//printf("alListenerfv VELOCITY : %d", error);
		return false;
	}

	// Orientation ...
	alListenerfv( AL_ORIENTATION, m_fListenerOrientation );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		//printf("alListenerfv ORIENTATION : %d", error);
		return false;
	}



	/*
	#ifdef AC3BACKGROUND
	ALboolean bEAXAC3ExtPresent;
	ALubyte szAC3[] = "EAX-AC3";
	LPALEAXAC3GETFUNCTIONTABLE ALEAXAC3GetFunctionTable;
	HRESULT hr;

	g_bEAXAC3DeviceOpen = false;

	// Allocate memory for EAXAC3 Function table
	g_lpEAXAC3FnTable = new EAXAC3FNTABLE;

	bEAXAC3ExtPresent = alIsExtensionPresent(szAC3);

	if (bEAXAC3ExtPresent)
	{
	// Retrieve the address of the alEAXAC3GetFunctionTable() function

	ALubyte szFnName[] = "alEAXAC3GetFunctionTable";
	ALEAXAC3GetFunctionTable = (LPALEAXAC3GETFUNCTIONTABLE)alGetProcAddress(szFnName);

	if (ALEAXAC3GetFunctionTable != NULL)
	{
	// Use the ALEAXAC3GetFunctionTable() function to retrieve a function table containing all of the
	// EAX-AC3 Functions
	if (ALEAXAC3GetFunctionTable(g_lpEAXAC3FnTable))
	{
	if (SUCCEEDED(hr = g_lpEAXAC3FnTable->EAXAC3OpenPlaybackDevice(DEFAULTEAXAC3DEVICE)))
	{
	g_bEAXAC3DeviceOpen = true;
	}
	}
	}
	}

	if (g_bEAXAC3DeviceOpen)
	{
	if (SUCCEEDED(hr = g_lpEAXAC3FnTable->EAXAC3OpenStream(DEFAULTEAXAC3DEVICE, &ac3Stream, NULL,
	"test1.ac3", AC3FILE)))
	{
	if (SUCCEEDED(hr = g_lpEAXAC3FnTable->EAXAC3PlayStream(ac3Stream, true)))
	{
	g_bPlayingAC3 = true;
	}
	}
	}
	#endif // AC3BACKGROUND
	*/


	/*
	// EAX test -- set EAX environment if EAX is available
	EAXSet pfPropSet;

	//EAXGet pfPropGet;
	unsigned long ulEAXVal;
	long lGlobalReverb;

	if (alIsExtensionPresent((ALubyte *)"EAX") == AL_TRUE)
	{
	pfPropSet = (EAXSet) alGetProcAddress((ALubyte *)"EAXSet");
	if (pfPropSet != NULL)
	{
	lGlobalReverb = 0;
	pfPropSet(&DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOM, 0, &lGlobalReverb, sizeof(unsigned long));
	ulEAXVal = EAX_ENVIRONMENT_GENERIC;
	pfPropSet(&DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, 0, &ulEAXVal, sizeof(unsigned long));
	}
	}
	*/

	return true;
}


/*
// IncrementEnv
int CSoundMgr::IncrementEnv()
{
// increment EAX environment if EAX is available
EAXSet pfPropSet;
//EAXGet pfPropGet;
unsigned long ulEAXVal;
static unsigned long ulEAXEnv = 0;
if (alIsExtensionPresent((ALubyte *)"EAX") == AL_TRUE)
{
pfPropSet = (EAXSet) alGetProcAddress((ALubyte *)"EAXSet");
if (pfPropSet != NULL)
{
ulEAXVal = 65535;
pfPropSet(&DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOM, 0, &ulEAXVal, sizeof(unsigned long));
ulEAXEnv += 1;
if (ulEAXEnv >= EAX_ENVIRONMENT_COUNT) { ulEAXEnv = EAX_ENVIRONMENT_GENERIC; }
pfPropSet(&DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, 0, &ulEAXEnv, sizeof(unsigned long));
}
}

return (int) ulEAXEnv;
}
*/

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundMgr::PlayFile( char *strFileName, bool bLoop, bool bForceSoundPlay, float xPos, float fNear, int fVolume, bool bSameSoundPlaying )
//	Desc : ���� ���� �ִ� ���� ��ü�� ���� ���� �Ҵ��ϰ� ����ϰ� ��.
//	Date : 2003. 06. 25
//	Update : 2003. 06. 26 - �Ķ���� �߰�
//							bForceSoundPlay : true - ������ ���尡 ������̸� ���߰� �ٽ� ��� false : ������ ���尡 ������̸� �װ� ��� ���
//							xPos : �� ( ���� ), �� ( ��� )
//			 2003. 07. 07 - fVolume : ���� ũ�� ���� �߰�
//							bSameSoundPlaying : ���� true �̶�� ���ۿ� ���尡 ������, �װ��� play �ǰ� �ִ� ���̶��, �Ȱ��� ���� �ϳ� �� ���� play ��Ű�� ��. ( temp )
//--------------------------------------------------------------------------------------------
bool CSoundMgr::PlayFile( char *strFileName, bool bLoop, bool bForceSoundPlay, float xPos, float fVolume, bool bSameSoundPlaying )
{
	if ( ! m_bEffectSoundOn )
	{
		return false;
	}

	fVolume = fVolume * m_srEffSoundVolumeLate;

	m_hSrch = ::FindFirstFile( strFileName, &m_wfd );

	if ( m_hSrch == INVALID_HANDLE_VALUE )
	{
		MessageBox( NULL, strFileName, strFileName, MB_OK|MB_TOPMOST );
		return false;
	}

	::FindClose( m_hSrch );

	char ExistFileIndex = IsFileAlreadyExist( strFileName );

	char cCount = 0;

	if ( ExistFileIndex != -1 )
	{
		if ( bForceSoundPlay )												// ���� ���� ��� ���̸� ���� �����Ű��, ���� ��� ( CSoiundObj Ŭ������ play �Լ� ���� ������ �⺻������ �׷��� �Ǿ� ����. )
		{
			m_pSoundObjList[ ExistFileIndex ].PlayPos( bLoop, xPos, fVolume );		//play �Լ��� ����Ǹ� ���ο��� ���� ���� ���� �ϰ� �ٽ� play �ϰԲ� �Ǿ� ����.
		}
		else
		{  

			if ( ! m_pSoundObjList[ ExistFileIndex ].IsPlaying() )			//���尡 ��������� ����.
			{
				m_pSoundObjList[ ExistFileIndex ].PlayPos( bLoop, xPos, fVolume );		//play �Լ��� ����Ǹ� ���ο��� ���� ���� ���� �ϰ� �ٽ� play �ϰԲ� �Ǿ� ����.
			}
			else if ( bSameSoundPlaying )
			{
				bool loop = true;
				while ( loop ) 
				{
					if ( ! m_pSoundObjList[ m_cSoundIndexLoop ].IsPlaying() )
					{
						m_pSoundObjList[ m_cSoundIndexLoop ].DeleteBufferAndSource();			
						m_pSoundObjList[ m_cSoundIndexLoop ].PlayPosWavFile( strFileName, bLoop, xPos, fVolume );

						if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
						{
							m_cSoundIndexLoop = 0;
						}

						break;
					}

					if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
					{
						m_cSoundIndexLoop = 0;
					}

					if ( ++cCount == MAX_SOUND_BUFFER_NUM )
					{
						// printf( "Play �� �� �ִ� ���� �����ϴ�.\n�ֳ��ϸ�, ��� play ���̶�...");

						return false;
					}

				}

			}
		}

		return true;
	}

	cCount = 0;

	bool loop = true;
	while ( loop ) 
	{
		if ( ! m_pSoundObjList[ m_cSoundIndexLoop ].IsPlaying() )
		{
			m_pSoundObjList[ m_cSoundIndexLoop ].DeleteBufferAndSource();			
			m_pSoundObjList[ m_cSoundIndexLoop ].PlayPosWavFile( strFileName, bLoop, xPos, fVolume );

			if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
			{
				m_cSoundIndexLoop = 0;
			}

			break;
		}

		if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
		{
			m_cSoundIndexLoop = 0;
		}

		if ( ++cCount == MAX_SOUND_BUFFER_NUM )
		{
			//printf( "Play �� �� �ִ� ���� �����ϴ�.\n�ֳ��ϸ�, ��� play ���̶�...");			
			return false;
		}

	}


	return true;
}

bool CSoundMgr::PlayBackGroundFile( char *strFileName, bool bLoop, bool bForceSoundPlay )
{
	int siVolume = m_siBGMSoundVolume;

	if ( ! m_bBackGroundSoundOn )
	{
		return false;
	}

	m_hSrch = ::FindFirstFile( strFileName, &m_wfd );

	if ( m_hSrch == INVALID_HANDLE_VALUE )
	{
		return false;
	}

	::FindClose( m_hSrch );

	char ExistFileIndex = IsBackGroundFileAlreadyExist( strFileName );


	if ( ExistFileIndex != -1 )
	{
		if ( bForceSoundPlay )														// ���� ���� ��� ���̸� ���� �����Ű��, ���� ��� ( CSoiundObj Ŭ������ play �Լ� ���� ������ �⺻������ �׷��� �Ǿ� ����. )
		{
			m_pOggObjList[ ExistFileIndex ].Stop();
			m_pOggObjList[ ExistFileIndex ].Play( siVolume, bLoop );					//play �Լ��� ����Ǹ� ���ο��� ���� ���� ���� �ϰ� �ٽ� play �ϰԲ� �Ǿ� ����.
		}

		else
		{			
			if ( ! m_pOggObjList[ ExistFileIndex ].IsPlaying() )					//���尡 ��������� ����.
			{
				m_pOggObjList[ ExistFileIndex ].Play( siVolume, bLoop );			
			}
		}

		return true;
	}

	char cCount = 0;

	bool loop = true;
	while ( loop ) 
	{
		if ( ! m_pOggObjList[ m_cBackGroundSoundIndexLoop ].IsPlaying() )
		{
			//m_pOggObjList[ m_cBackGroundSoundIndexLoop ].Close();
			m_pOggObjList[ m_cBackGroundSoundIndexLoop ].OpenOgg( strFileName );
			m_pOggObjList[ m_cBackGroundSoundIndexLoop ].Play( siVolume, bLoop );

			if ( ++m_cBackGroundSoundIndexLoop == MAX_BACKGROUND_SOUND_NUM )
			{
				m_cBackGroundSoundIndexLoop = 0;
			}

			break;
		}

		if ( ++m_cBackGroundSoundIndexLoop == MAX_BACKGROUND_SOUND_NUM )
		{
			m_cBackGroundSoundIndexLoop = 0;
		}

		if ( ++cCount == MAX_BACKGROUND_SOUND_NUM )
		{
			//printf( "Play �� �� �ִ� ���� �����ϴ�.\n�ֳ��ϸ�, ��� play ���̶�...");

			return false;
		}
	}

	return true;
}

bool CSoundMgr::GetSoundVolume( char* strFileName, float *pfOutSoundVolume )
{
	char ExistFileIndex = IsFileAlreadyExist( strFileName );

	if ( ExistFileIndex != -1 )
	{
		*pfOutSoundVolume = m_pSoundObjList[ ExistFileIndex ].GetSoundVolume();
		return true;	
	}

	*pfOutSoundVolume = 0.0f;

	return false;
}

bool CSoundMgr::GetBackGroundSoundVolume( char *strFileName, long *pOutSoundVolume )
{
	char ExistFileIndex = IsBackGroundFileAlreadyExist( strFileName );

	if ( ExistFileIndex != -1 )
	{
		*pOutSoundVolume = m_pOggObjList[ ExistFileIndex ].GetSoundVolume();
		return true;	
	}

	*pOutSoundVolume = BASE_BACKGROUND_SOUND_VOLUME;

	return false;
}


/*
//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundMgr::PlayFile( char *strFileName, bool bLoop, bool bForceSoundPlay, int fVolume )
//	Desc : ���� ���� �ִ� ���� ��ü�� ���� ���� �Ҵ��ϰ� ����ϰ� ��.
//	Date : 2003. 06. 25
//	Update : 2003. 06. 26 - �Ķ���� �߰�
//			 2003. 07. 07 - ���� ũ�� ���� �߰�
//							���ۿ� ���尡 ������, �װ��� play �ǰ� �ִ� ���̶��, �Ȱ��� ���� �ϳ� �� ���� play ��Ű�� ��. ( temp )
//--------------------------------------------------------------------------------------------
bool CSoundMgr::PlayFile( char *strFileName, bool bLoop, bool bForceSoundPlay, float fVolume, bool bSameSoundPlaying )
{
m_hSrch = ::FindFirstFile( strFileName, &m_wfd );

if ( m_hSrch == INVALID_HANDLE_VALUE )
{
return false;
}

::FindClose( m_hSrch );


char cCount = 0;

char ExistFileIndex = IsFileAlreadyExist( strFileName );

if ( ExistFileIndex != -1 )
{
if ( bForceSoundPlay )												// ���� ���� ��� ���̸� ���� �����Ű��, ���� ��� ( CSoiundObj Ŭ������ play �Լ� ���� ������ �⺻������ �׷��� �Ǿ� ����. )
{
m_pSoundObjList[ ExistFileIndex ].Play( bLoop, fVolume );		//play �Լ��� ����Ǹ� ���ο��� ���� ���� ���� �ϰ� �ٽ� play �ϰԲ� �Ǿ� ����.
}
else
{
if ( bSameSoundPlaying )
{
while ( true ) 
{
if ( ! m_pSoundObjList[ m_cSoundIndexLoop ].IsPlaying() )
{
m_pSoundObjList[ m_cSoundIndexLoop ].DeleteBufferAndSource();			
m_pSoundObjList[ m_cSoundIndexLoop ].PlayWavFile( strFileName, bLoop, fVolume );

if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
{
m_cSoundIndexLoop = 0;
}

break;
}

if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
{
m_cSoundIndexLoop = 0;
}

if ( ++cCount == MAX_SOUND_BUFFER_NUM )
{
printf( "Play �� �� �ִ� ���� �����ϴ�.\n�ֳ��ϸ�, ��� play ���̶�...");

return false;
}

}

}
else if ( ! m_pSoundObjList[ ExistFileIndex ].IsPlaying() )			//���尡 ��������� ����.
{
m_pSoundObjList[ ExistFileIndex ].Play( bLoop, fVolume );		//play �Լ��� ����Ǹ� ���ο��� ���� ���� ���� �ϰ� �ٽ� play �ϰԲ� �Ǿ� ����.
}
}

return true;
}

bool bPlayCheck = false;


cCount = 0;

while ( ! bPlayCheck ) 
{
if ( ! m_pSoundObjList[ m_cSoundIndexLoop ].IsPlaying() )
{
m_pSoundObjList[ m_cSoundIndexLoop ].DeleteBufferAndSource();			
m_pSoundObjList[ m_cSoundIndexLoop ].PlayWavFile( strFileName, bLoop, fVolume );

if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
{
m_cSoundIndexLoop = 0;
}

bPlayCheck = true;

break;
}

if ( ++m_cSoundIndexLoop == MAX_SOUND_BUFFER_NUM )
{
m_cSoundIndexLoop = 0;
}

if ( ++cCount == MAX_SOUND_BUFFER_NUM )
{
printf( "Play �� �� �ִ� ���� �����ϴ�.\n�ֳ��ϸ�, ��� play ���̶�...");

return false;
}

}

if ( ! bPlayCheck )					//���� ��� ������ ������� play �ǰ� �ִ� ��Ȳ�̶��... ��ü �ϳ��� �ӽ÷� �����ؼ� play ��Ų�Ŀ� ���� ����
{
}

return true;
}
*/

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - char IsFileAlreadyExist( char *strFileName )
//	Desc : ���� ������ �����ϴ��� �˻��ϰ�, �����Ѵٸ� index�� �������� �ʴ´ٸ� -1�� �����Ѵ�.
//	Date : 2003. 06. 25
//	Update : 
//--------------------------------------------------------------------------------------------
char CSoundMgr::IsFileAlreadyExist( char *strFileName )
{
	if( strFileName == NULL )		return -1;
	if( m_pSoundObjList == NULL )	return -1;

	char i;

	for ( i = 0; i < MAX_SOUND_BUFFER_NUM; ++i )
	{
		if ( m_pSoundObjList[i].IsSameFile( strFileName ) )
		{
			return i;
		}		
	}

	return -1;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - char CSoundMgr::IsBackGroundFileAlreadyExist( char *strFileName )
//	Desc : ���� ������ �����ϴ��� �˻��ϰ�, �����Ѵٸ� index�� �������� �ʴ´ٸ� -1�� �����Ѵ�.
//		   ��� ���ǿ�
//	Date : 2003. 07. 28
//	Update : 
//--------------------------------------------------------------------------------------------
char CSoundMgr::IsBackGroundFileAlreadyExist( char *strFileName )
{
	char i;

	for ( i = 0; i < MAX_BACKGROUND_SOUND_NUM; ++i )
	{
		if ( m_pOggObjList[i].IsSameFile( strFileName ) )
		{
			return i;
		}		
	}

	return -1;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CSoundMgr::IsBackGroundFilePlaying()
//	Desc : ��������� ��������� Ȯ���Ѵ�.
//	Date : 2003. 11. 18
//	Update : 
//--------------------------------------------------------------------------------------------
bool CSoundMgr::IsBackGroundFilePlaying()
{
	for ( int i = 0; i < MAX_BACKGROUND_SOUND_NUM; ++i )
	{
		if ( m_pOggObjList[i].IsPlaying() )
		{
			return true;
		}		
	}

	return false;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundMgr::SoundStop( char index )
//	Desc : �ϳ��� ���带 ���� ��Ų��.
//	Date : 2003. 06. 30
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundMgr::SoundStop( char index )
{
	m_pSoundObjList[ index ].Stop();
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundMgr::AllSoundStop()
//	Desc : ��� ���带 ���� ��Ų��.
//	Date : 2003. 06. 30
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundMgr::AllSoundStop()
{
	for ( int i = 0; i < MAX_SOUND_BUFFER_NUM; ++i )
	{
		m_pSoundObjList[ i ].Stop();
	}

	for ( i = 0; i < MAX_BACKGROUND_SOUND_NUM; ++i )
	{
		m_pOggObjList[ i ].Stop();
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CSoundMgr::BackGroundSoundStop( char *strFileName )
//	Desc : ��� ���� ���常 ���� ��Ų��.
//	Date : 2003. 07. 28
//	Update : 
//--------------------------------------------------------------------------------------------
void CSoundMgr::BackGroundSoundStop()
{
	for ( int i = 0; i < MAX_BACKGROUND_SOUND_NUM; ++i )
	{
		m_pOggObjList[ i ].Stop();
	}

	return;
}


void CSoundMgr::EffectSoundOn( bool bEffectSoundOn )
{
	m_bEffectSoundOn = bEffectSoundOn;

	if ( ! m_bEffectSoundOn )
	{
		for ( int i = 0; i < MAX_SOUND_BUFFER_NUM; ++i )
		{
			m_pSoundObjList[ i ].Stop();
		}
	}

	return;
}

void CSoundMgr::BackGroundSoundOn( bool bBackGroundSoundOn )
{
	m_bBackGroundSoundOn = bBackGroundSoundOn;

	if ( ! m_bBackGroundSoundOn )
	{
		for ( int i = 0; i < MAX_BACKGROUND_SOUND_NUM; ++i )
		{
			m_pOggObjList[ i ].Stop();
		}
	}


	return;
}

void CSoundMgr::SetSoundVolume( float soundvolume )
{
	m_srEffSoundVolumeLate = soundvolume;
}

void CSoundMgr::SetBackGroundSoundVolume( int soundvolume )
{
	m_siBGMSoundVolume = soundvolume;

	for ( int i=0; i < MAX_BACKGROUND_SOUND_NUM ; i++ )
	{
		m_pOggObjList[i].SetSoundVolume(soundvolume);
	}

}







//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com)
//	Desc : ���� release Mode ������ �ʿ� ���� �ڵ�.
//	Date : 2003. 06. 30
//	Update : 
//--------------------------------------------------------------------------------------------
#ifdef _DEBUG
bool CSoundMgr::IsPlaying( int num )
{
	return m_pSoundObjList[num].IsPlaying();
}

//����Ʈ�� �ִ� ��� wav ���� �̸� ���
void CSoundMgr::PrintAllFileName()
{
	for ( int i = 0; i < MAX_SOUND_BUFFER_NUM; ++i )
	{
		//printf("Index = %d, FileName = %s\n", i, m_pSoundObjList[i].GetFileName() );
	}
}

#endif