#include "CharacterDrawing.h"

#include "XSPRMgr.h"
#include "MinDataMgr.h"
#include "MinDataObj.h"
#include "DataLoading.h"
#include "Graphic_Capsule.h"

#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"
#include "../common/Char/ParametaBox/parametabox.h"
#include "../common/Char/CharManager/CharManager.h"

extern cltCommonLogic* pclClient;



CCharacterDrawing::CCharacterDrawing()
{
	TMemSet( m_strHelmet,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strArmor,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strWeapon,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strMantle,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEquipment,	0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strHorse,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEffect,		0, MAX_ITEMCODE_LENGTH );

	memset( m_strFileName,		0, sizeof( m_strFileName ) );

	TMemSet( m_strCharacterKind,		0, 4 );
	TMemSet( m_strTempCharacterKind,	0, 4 );

	m_siCharacterKind		= KIND_HERO1;
	m_siTempCharacterKind	= KIND_HERO1;

	m_bReverse			= false;
	m_bIsTakeHorse		= false;
	m_bIsTakeMantle		= false;
	m_bIsTakeEquipment	= false;
	m_bIsEffect			= false;

	Initialize();
}

CCharacterDrawing::CCharacterDrawing( char cGameMode )
{
	m_cGameMode = cGameMode;

	TMemSet( m_strHelmet,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strArmor,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strWeapon,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strMantle,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEquipment,	0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strHorse,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEffect,		0, MAX_ITEMCODE_LENGTH );
	m_siEffectKind = 0;

	memset( m_strFileName, 0, sizeof( m_strFileName ) );

	TMemSet( m_strCharacterKind,		0, 4 );
	TMemSet( m_strTempCharacterKind,	0, 4 );


	m_siCharacterKind	  = KIND_HERO1;
	m_siTempCharacterKind = KIND_HERO1;

	m_bReverse			= false;
	m_bIsTakeMantle		= false;
	m_bIsTakeEquipment	= false;
	m_bIsTakeHorse		= false;
	m_bIsEffect			= false;

	m_cCurrentActionIndex = 0;

	Initialize();
}

CCharacterDrawing::~CCharacterDrawing()
{
	Destroy();
}

void CCharacterDrawing::Initialize()
{
	TMemSet( m_strHelmet,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strArmor,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strWeapon,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strMantle,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEquipment,	0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strHorse,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEffect,		0, MAX_ITEMCODE_LENGTH );;
	m_siEffectKind = 0;

	memset( m_strFileName, 0, sizeof( m_strFileName ) );

	m_ssAnimationNum = 0;
	m_cCurrentDirection = CCD_SOUTH_EAST;

	m_ssAnimationStartIndex = 0;
	m_ssAnimationEndIndex = 0;

	m_ssCurrentAnimationIndex = 0;

	memset( m_siDrawingSequence, 0, sizeof( m_siDrawingSequence ));

	TMemSet( m_strCharacterKind,	 0, 4 );
	TMemSet( m_strTempCharacterKind, 0, 4 );


	m_siCharacterKind = KIND_HERO1;
	m_siTempCharacterKind = KIND_HERO1;

	m_bReverse = false;
	m_bIsTakeMantle = false;
	m_bIsTakeEquipment = false;
	m_bIsTakeHorse = false;	
	m_bIsEffect = false;

}

void CCharacterDrawing::Destroy()
{
	TMemSet( m_strHelmet,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strArmor,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strWeapon,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strMantle,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEquipment,	0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strHorse,		0, MAX_ITEMCODE_LENGTH );
	TMemSet( m_strEffect,		0, MAX_ITEMCODE_LENGTH );

	m_siEffectKind = 0;


	memset( m_strFileName, 0, sizeof( m_strFileName ) );	

	m_ssAnimationNum = 0;
	m_cCurrentDirection = CCD_SOUTH_EAST;

	m_ssAnimationStartIndex = 0;
	m_ssAnimationEndIndex = 0;

	m_ssCurrentAnimationIndex = 0;

	memset( m_siDrawingSequence, 0, sizeof( m_siDrawingSequence ) );

	TMemSet( m_strCharacterKind,	 0, 4 );
	TMemSet( m_strTempCharacterKind, 0, 4 );


	m_siCharacterKind	  = KIND_HERO1;
	m_siTempCharacterKind = KIND_HERO1;

	m_bReverse			= false;
	m_bIsTakeMantle		= false;
	m_bIsTakeEquipment	= false;
	m_bIsTakeHorse		= false;
	m_bIsEffect			= false;

}

TCHAR *CCharacterDrawing::GetHelmetCode()
{
	return m_strHelmet;
}

TCHAR *CCharacterDrawing::GetArmorCode()
{
	return m_strArmor;
}

TCHAR *CCharacterDrawing::GetWeaponCode()
{
	return m_strWeapon;
}

TCHAR *CCharacterDrawing::GetMantleCode()
{
	return m_strMantle;
}

TCHAR *CCharacterDrawing::GetEquipmentCode()
{
	return m_strEquipment;
}

TCHAR *CCharacterDrawing::GetHorseCode()
{
	return m_strHorse;
}

TCHAR *CCharacterDrawing::GetEffectCode()
{
	return m_strEffect;
}

void CCharacterDrawing::LoadItemCodeData( SI16 CharacterKind, TCHAR *strHelmet, TCHAR *strArmor, TCHAR *strWeapon, TCHAR *strMantleOrEquipment, TCHAR *strHorse, SI32 EffectKind, void *pEffectParam )
{
	m_siCharacterKind = CharacterKind;
	m_siTempCharacterKind = CharacterKind;

	switch( m_siCharacterKind )
	{
	case KIND_HERO1:
		{
			StringCchCopy( m_strCharacterKind,		4, TEXT("TP1") );
			StringCchCopy( m_strTempCharacterKind,	4, TEXT("TP1") );
		}
		break;
	case KIND_HEROINE1:
		{
			StringCchCopy( m_strCharacterKind,		4, TEXT("TP2") );
			StringCchCopy( m_strTempCharacterKind,	4, TEXT("TP2") );
		}
		break;
	case KIND_HERO2:
		{
			StringCchCopy( m_strCharacterKind,		4, TEXT("TP3") );
			StringCchCopy( m_strTempCharacterKind,	4, TEXT("TP1") );

			m_siTempCharacterKind = KIND_HERO1;
		}
		break;
	case KIND_HEROINE2:
		{
			StringCchCopy( m_strCharacterKind,		4, TEXT("TP4") );
			StringCchCopy( m_strTempCharacterKind,	4, TEXT("TP2") );

			m_siTempCharacterKind = KIND_HEROINE1;
		}
		break;
	case KIND_HERO3:
		{
			StringCchCopy( m_strCharacterKind,		4, TEXT("TP5") );
			StringCchCopy( m_strTempCharacterKind,	4, TEXT("TP1") );

			m_siTempCharacterKind = KIND_HERO1;
		}
		break;
	case KIND_HEROINE3:
		{
			StringCchCopy( m_strCharacterKind,		4, TEXT("TP6") );
			StringCchCopy( m_strTempCharacterKind,	4, TEXT("TP2") );

			m_siTempCharacterKind = KIND_HEROINE1;
		}
		break;
	case KIND_HERO4:
		{
			StringCchCopy( m_strCharacterKind, 4, TEXT("TP7") );
			StringCchCopy( m_strTempCharacterKind, 4, TEXT("TP3") );

			m_siTempCharacterKind = KIND_HERO1;
		}
		break;
	case KIND_HEROINE4:
		{
			StringCchCopy( m_strCharacterKind,		4, TEXT("TP8") );
			StringCchCopy( m_strTempCharacterKind,	4, TEXT("TP4") );

			m_siTempCharacterKind = KIND_HEROINE1;
		}
		break;
	default:
		{
			//MessageBox( NULL, TEXT("m_siCharacterKind Error"), TEXT("m_siCharacterKind Error"), MB_OK );
			return;
		}
		break;
	}

	TCHAR *strHelmet1	= tcsupr( strHelmet );
	TCHAR *strArmor1	= tcsupr( strArmor );
	TCHAR *strWeapon1	= tcsupr( strWeapon );

	MStrCpy( m_strHelmet,	strHelmet1, MAX_ITEMCODE_LENGTH );
	MStrCpy( m_strArmor,	strArmor1,	MAX_ITEMCODE_LENGTH );
	MStrCpy( m_strWeapon,	strWeapon1, MAX_ITEMCODE_LENGTH );


	if ( strMantleOrEquipment == NULL || _tcslen( strMantleOrEquipment ) < 1 )
	{
		m_bIsTakeMantle = false;
		memset( m_strMantle, 0, MAX_ITEMCODE_LENGTH );

		m_bIsTakeEquipment = false;
		memset( m_strEquipment, 0, MAX_ITEMCODE_LENGTH );
	}
	else
	{
		// ������ ���.
		if ( strMantleOrEquipment[0] == 'M' || strMantleOrEquipment[0] == 'm' )
		{
			TCHAR *strMantle1 = tcsupr( strMantleOrEquipment );

			m_bIsTakeMantle = true;
			StringCchCopy( m_strMantle, MAX_ITEMCODE_LENGTH, strMantle1 );
			m_bIsTakeEquipment = false;
			memset( m_strEquipment, 0, MAX_ITEMCODE_LENGTH );
		}
		// ����� ���.
		else if ( strMantleOrEquipment[0] == 'E' || strMantleOrEquipment[0] == 'e' )
		{
			TCHAR *strEquipment1 = tcsupr( strMantleOrEquipment );

			m_bIsTakeEquipment = true;
			StringCchCopy( m_strEquipment, MAX_ITEMCODE_LENGTH, strEquipment1 );
			m_bIsTakeMantle = false;
			memset( m_strMantle, 0, MAX_ITEMCODE_LENGTH );
		}
		else
		{
			// ������ �ִ� ����̴�.	// �� ���� �켱 ��� ���ϰ� ��.
			m_bIsTakeMantle = false;
			memset( m_strMantle,	0, MAX_ITEMCODE_LENGTH );

			m_bIsTakeEquipment = false;
			memset( m_strEquipment, 0, MAX_ITEMCODE_LENGTH );
		}
	}

	if( strHorse == NULL || _tcslen(strHorse) < 1 )
	{
		m_bIsTakeHorse = false;
		memset( m_strHorse, 0, MAX_ITEMCODE_LENGTH );
	}
	else
	{
		TCHAR *strHorse1 = tcsupr( strHorse );

		m_bIsTakeHorse = true;
		StringCchCopy( m_strHorse, MAX_ITEMCODE_LENGTH, strHorse1 );
	}

	m_siEffectKind = EffectKind;

	switch ( EffectKind )
	{
	case 1:
		{
			m_bIsEffect = true;
			StringCchCopy( m_strEffect, MAX_ITEMCODE_LENGTH, m_strWeapon );
			StringCchCopy( &m_strEffect[2], MAX_ITEMCODE_LENGTH - 2, TEXT("Z01") );
		}
		break;
	case 2:
		{
			m_bIsEffect = true;
			StringCchCopy( m_strEffect, MAX_ITEMCODE_LENGTH, m_strWeapon );
			StringCchCopy( &m_strEffect[2], MAX_ITEMCODE_LENGTH - 2, TEXT("Z02") );
		}
		break;
	default:
		{
			m_bIsEffect = false;
			memset( m_strEffect, 0, MAX_ITEMCODE_LENGTH );
		}
		break;
	}

	return;
}

void CCharacterDrawing::DrawCharacter(	short ssActionIndex, 
										char cDirection, 
										short ssAnimationIndex,
										short ssBottomX, 
										short ssBottomY, 
										SI32 JewelWeapon, 
										SI32 JewelHelmet,
										SI32 JewelArmor, 
										SI32 JewelMantle,
										bool JewelHorse,
										bool AttackScroll,
										SI08 AttackScrollNum, 
										bool* Reverse,
										SI32* EffectX,
										SI32* EffectY,
										SI32* EffectFont,
										SI32* AttackImg,
									    SI32 siPremiumpartsUnique_Slot1, 
										SI32 siPremiumpartsUnique_Slot2, 
										SI32 siPremiumpartsUnique_Slot3, 
										SI16 siHorseUnique )
{
	if ( ssActionIndex < HITU || ( ssActionIndex > SPCU && ssActionIndex < HITR ) )
	{
		g_BaseDataMgr.GetWeaponInfo( m_strWeapon, ssActionIndex );

		if ( m_bIsTakeHorse )
		{
			ssActionIndex += HSR1;
		}
	}

	TCHAR temp[256] = TEXT("");
	StringCchCopy( temp, 256, m_strTempCharacterKind );
	StringCchCat( temp, 256, g_BaseDataMgr.m_pstAction[ssActionIndex].strActionCode );
	CMinDataObj *pTemp = g_MinDataMgr.GetSameMinDataObjPtr( temp );

	if ( pTemp == NULL )
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, temp, TEXT("Min File is Not Exist"), MB_OK|MB_TOPMOST );
		return;
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Min ������ ������ �о���� �κ�
	m_ssAnimationNum = pTemp->GetFrameNum();	
	m_cCurrentActionIndex = pTemp->GetActionIndex();
	pTemp->CopySequence( (int**)m_siDrawingSequence );
	//////////////////////////////////////////////////////////////////////////////////
	m_bReverse = false;

	// ���� ó��... ������ �ѹ��� ¥���ε�, �ٸ� ������ ���� ��쿡 ����...
	if ( pTemp->GetDirectionNum() < 2 )
	{
		if ( pTemp->GetDirectionNum() - 1 < cDirection )
		{
			cDirection = 0;
			m_cCurrentDirection = 0;
		}
	}

	m_cCurrentDirection = cDirection;
	char cTempDirection = m_cCurrentDirection;

	if ( cDirection > CCD_NORTH_WEST )
	{
		cTempDirection = CCD_NORTH_WEST - ( cTempDirection - CCD_NORTH_WEST );

		m_ssAnimationStartIndex = m_ssAnimationNum * cTempDirection;
		m_bReverse = true;
	}
	else
	{
		m_ssAnimationStartIndex = m_ssAnimationNum * cTempDirection;
		m_bReverse = false;
	}

	m_ssAnimationEndIndex = m_ssAnimationStartIndex + m_ssAnimationNum;
	m_ssCurrentAnimationIndex = m_ssAnimationStartIndex + ssAnimationIndex;

	if ( m_ssCurrentAnimationIndex > m_ssAnimationEndIndex - 1 )
	{

#ifdef _DEBUG
		TCHAR ErrorLog[256];
		TCHAR* pText = GetTxtFromMgr(3882);
		StringCchPrintf( ErrorLog, 256, pText, ssAnimationIndex );
		//MessageBox( NULL, ErrorLog, TEXT("�Է°� Ȯ���� �ּ���.\n�� �޽��� �ڽ� �߸� �ȵǿ�..."), MB_OK|MB_TOPMOST );
#endif

		m_ssCurrentAnimationIndex = m_ssAnimationStartIndex;
	}

	/*
	if ( m_cGameMode == CCD_GAMEMODE_SERVER )
	{
		return;
	}
	*/

		ZeroMemory( m_strFileName[ cTempDirection ], sizeof( m_strFileName[ cTempDirection ] ) );

	if ( m_cCurrentActionIndex == DTHU || m_cCurrentActionIndex == DTHR )
	{		
		switch ( m_cCurrentActionIndex )
		{
		case DTHU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sDTHU.Spr"), m_strTempCharacterKind );
			}
			break;
		case DTHR:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\%sTOR%sDTHR.Spr"), m_strHorse, m_strTempCharacterKind );
			}
			break;
		}

		g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
	}
	else if ( m_cCurrentActionIndex > SITU )		// ���� ��� 
	{
		switch( m_cCurrentActionIndex )
		{
		case FSHU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sFSHU.Spr"), m_strTempCharacterKind );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX - 55, ssBottomY - 50, 430, 279, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX - 55, ssBottomY - 50, 430, 279, m_ssCurrentAnimationIndex );
				}
			}
			break;
		//KHY - 1014 - �漮 �߰�.
		case SLEP:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSLEP.Spr"), m_strTempCharacterKind );

				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+5 , ssBottomY+35 , 130, 279, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+5, ssBottomY+35 , 130, 279, m_ssCurrentAnimationIndex );
				}
			}
			break;
		// PCK : ���ڴ� �Ŀ��� �漮 �߰�(09.06.16)
		case SLEC:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSLEC.Spr"), m_strTempCharacterKind );

				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+55 , ssBottomY+65 , 130, 279, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+55, ssBottomY+65 , 130, 279, m_ssCurrentAnimationIndex );
				}
			}
			break;
		case FAMU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sFAMU.Spr"), m_strTempCharacterKind  );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 99, ssBottomY + 100, 122, 117, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 99, ssBottomY + 100, 122, 117, m_ssCurrentAnimationIndex );
				}
			}
			break;
		case MINU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMINU.Spr"), m_strTempCharacterKind  );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 30, ssBottomY + 40, 220, 200, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 30, ssBottomY + 40, 220, 200, m_ssCurrentAnimationIndex );
				}
			}
			break;
		case MAMU:
			{
				if( _tcscmp( m_strTempCharacterKind,TEXT("TP1")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 95 , 88, 111, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 95, 88, 111, m_ssCurrentAnimationIndex );
					}
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP2")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3 , 98, 102, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3, 98, 102, m_ssCurrentAnimationIndex );
					}
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP3")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 98 , 88, 107, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 98, 88, 107, m_ssCurrentAnimationIndex );
					}
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP4")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3 , 98, 102, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3 , 320, 240, m_ssCurrentAnimationIndex );

					}
				}
			}
			break;
		case MHEU:
			{
				// ������ �̹���
				if( _tcscmp( m_strTempCharacterKind,TEXT("TP1")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 85, 105, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 113, ssBottomY+ 95, 85, 105, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP2")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 105, 109, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 105, 109, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP3")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 80, 105, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 113, ssBottomY+ 95, 80, 105, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP4")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 105, 109, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 113, ssBottomY+ 95, 105, 109, m_ssCurrentAnimationIndex );
					}	
				}
			}
			break;
		case MFOU:
			{
				// �������� �̹���
				if( _tcscmp( m_strTempCharacterKind,TEXT("TP1")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ],  ssBottomX + 105, ssBottomY + 80, 96, 133, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 105, ssBottomY + 80, 96, 133, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP2")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 96, 120, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 96, 120, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP3")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 105, ssBottomY + 80, 96, 133, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 105, ssBottomY + 80, 96, 133, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP4")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 96, 119, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 95, 96, 119, m_ssCurrentAnimationIndex );
					}	
				}
			}
			break;
		case SOPU:
			{
				// ���� ���� ���� �̹���
				if( _tcscmp( m_strTempCharacterKind,TEXT("TP1")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ],  ssBottomX + 113, ssBottomY + 100, 81, 107, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 81, 107, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP2")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 103, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 103, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP3")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 80, 101, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 80, 101, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP4")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 102, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 102, m_ssCurrentAnimationIndex );
					}	
				}
			}
			break;
			/*
		case SITU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSITU.Spr"), m_strTempCharacterKind  );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, 220, 200, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, 220, 200, m_ssCurrentAnimationIndex );
				}
			}
			break;
			*/
		}
	}
	else
	{		
		for ( int i = 0; i < MAX_DRAWING_SEQUENCE_NUM; ++i )
		{
			if ( m_bReverse )
			{
				switch ( m_siDrawingSequence[ cTempDirection ] [ i ] )
				{
				case 0:			//�� ����.
					break;
				case 1:			// ����
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHelmet, TEXT("HED"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						if ( pImgSpr && JewelHelmet )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelHelmet);
						}
					}
					break;
				case 2:			// ����
					{
						if (ssActionIndex == SITU )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						else
						{
							if( _tcscmp( m_strArmor, TEXT("KOR01") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
							else if( _tcscmp( m_strArmor, TEXT("DRE36") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE35") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
							else if( _tcscmp( m_strArmor, TEXT("DRE39") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE40") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// ������ ���� �׸� ����?
							else if( _tcscmp( m_strArmor, TEXT("DRE58") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE57") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// PCK : ������ �ǻ� �߰�
							else if( _tcscmp( m_strArmor, TEXT("DRE64") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE65") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// PCK : ��ȥ���� �߰� (09.05.20)
							else if( _tcscmp( m_strArmor, TEXT("DRE66") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE67") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							else if( _tcscmp( m_strArmor, TEXT("DRE19") ) == 0  )
							{	
								TCHAR exeptCharKind[4] = {'\0',};

								StringCchPrintf(exeptCharKind,4,m_strTempCharacterKind);


								if( _tcscmp( exeptCharKind, TEXT("TP3") ) == 0  )
								{	
									StringCchPrintf( exeptCharKind , 4 , TEXT("TP1") );
								}
								else if( _tcscmp( exeptCharKind, TEXT("TP4") ) == 0  )
								{
									StringCchPrintf( exeptCharKind , 4 , TEXT("TP2") );
								}

								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), exeptCharKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							else
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}

						}

						//StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 1 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						if ( pImgSpr && JewelArmor )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelArmor);
						}
					}
					break;
				case 3:			// ������ ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 2 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("RHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 2 ], TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 2 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						// ��æƮ ����Ʈ ���ϸ� �̾ƿ���
						TCHAR szTempEnchantEffectFileName[256];
						ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
						GetEnchantEffectFileName(m_strWeapon, JewelWeapon ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);

						if ( pImgSpr && JewelWeapon )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						}

						if (strlen(szTempEnchantEffectFileName) > 0)
						{
							TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
						}
					}
					break;
				case 4:			// ���� ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 3 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("LHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 3], TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 3 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						// ��æƮ ����Ʈ ���ϸ� �̾ƿ���
						TCHAR szTempEnchantEffectFileName[256];
						ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
						GetEnchantEffectFileName(m_strWeapon, JewelWeapon ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);

						if ( pImgSpr && JewelWeapon )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						}

						if (strlen(szTempEnchantEffectFileName) > 0)
						{
							TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
						}
					}
					break;
				case 5:			// ���� �̹���
					{
						if ( m_bIsTakeMantle )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							if ( pImgSpr && JewelMantle )
							{
								cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
								pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							}
						}
					}
					break;
				case 6:			// ��� �̹���
					{
						if ( m_bIsTakeEquipment )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							if ( pImgSpr && JewelMantle )
							{
								cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
								pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							}
						}
					}
					break;
				case 7:			// �� �̹��� ( �� �̹����� ���� �������� "TP1" �� ��� )
					{
						if ( m_bIsTakeHorse )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 5 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHorse, TEXT("HRSTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 5 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							if ( siHorseUnique != HORSEUNIQUE_MOTORCYCLE // ������̰� �ƴϰ�.
								&& 0 <= ssActionIndex - HSR1 && 8 > ssActionIndex - HSR1 && JewelHorse )
							{
								TSpr * pSpr = pclClient->GetGlobalSpr( GIMG_HORSEWING1 + (ssActionIndex - HSR1) );
								if( pSpr )								
								{
									GP.PutSprScreen(pSpr , ssBottomX, ssBottomY, m_ssCurrentAnimationIndex, m_bReverse );
								}
							}
							if( siPremiumpartsUnique_Slot1 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Motor(m_strWeapon, siPremiumpartsUnique_Slot1 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot2 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Motor(m_strWeapon, siPremiumpartsUnique_Slot2 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot3 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Motor(m_strWeapon, siPremiumpartsUnique_Slot3 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
						}
					}
					break;   
				case 8:						// Effect Image
					{
						if ( m_bIsEffect )
						{
							switch( m_siEffectKind )
							{
							case 1:
							case 2:
								{
									if ( ssActionIndex < HBU2 || 
										ssActionIndex == HSR1 ||
										ssActionIndex == HTR2
										)
									{
										StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

										TSpr *pImgSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX - 110 , ssBottomY - 100, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

									}
								}
								break;
							default:
								{
									StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), m_strCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

									TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
								break;
							}
						}
                        if ( m_bIsTakeHorse )
						{
							if( siPremiumpartsUnique_Slot1 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Horse(m_strWeapon, siPremiumpartsUnique_Slot1 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot2 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Horse(m_strWeapon, siPremiumpartsUnique_Slot2 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot3 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Horse(m_strWeapon, siPremiumpartsUnique_Slot3 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							////Ǯ���� �϶� 
							//if( siPremiumpartsUnique_Slot1 > 0 && siPremiumpartsUnique_Slot2 > 0 && siPremiumpartsUnique_Slot3 > 0 )
							//{
							//	TCHAR szTempEnchantEffectFileName[256];
							//	ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
							//	GetPremiumPartsFullEffectFileName(m_strWeapon, siPremiumpartsUnique_Slot1 ,siPremiumpartsUnique_Slot2 ,siPremiumpartsUnique_Slot3 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
							//	if (strlen(szTempEnchantEffectFileName) > 0)
							//	{
							//		TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
							//	}
							//}

						}
					}
					break;
				default:		// �� ����
					break;
				}
			}
			else
			{
				switch ( m_siDrawingSequence[ cTempDirection ] [ i ] )
				{
				case 0:			//�� ����.
					break;
				case 1:			// ����					
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHelmet, TEXT("HED"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						if ( pImgSpr && JewelHelmet )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelHelmet);
						}
					}
					break;
				case 2:			// ����	
					{
						if (ssActionIndex == SITU )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						else
						{
							if( _tcscmp( m_strArmor, TEXT("KOR01") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
							else if( _tcscmp( m_strArmor, TEXT("DRE36") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE35") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
							else if( _tcscmp( m_strArmor, TEXT("DRE39") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE40") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// ������ ���� �׸� ����?
							else if( _tcscmp( m_strArmor, TEXT("DRE58") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE57") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// PCK : ������ �ǻ� �߰�
							else if( _tcscmp( m_strArmor, TEXT("DRE64") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE65") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							// PCK : ��ȥ���� �߰� (09.05.20)
							else if( _tcscmp( m_strArmor, TEXT("DRE66") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE67") ) == 0 )
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							else if( _tcscmp( m_strArmor, TEXT("DRE19") ) == 0  )
							{
								TCHAR exeptCharKind[4] = {'\0',};

								StringCchPrintf(exeptCharKind,4,m_strTempCharacterKind);


								if( _tcscmp( exeptCharKind, TEXT("TP3") ) == 0  )
								{	
									StringCchPrintf( exeptCharKind , 4 , TEXT("TP1") );
								}
								else if( _tcscmp( exeptCharKind, TEXT("TP4") ) == 0  )
								{
									StringCchPrintf( exeptCharKind , 4 , TEXT("TP2") );
								}

								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), exeptCharKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
							else
							{
								StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							}
						}

						//StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 1 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						if ( pImgSpr && JewelArmor )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelArmor);
						}
					}

					break;
				case 3:			// ������ ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 2 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("RHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 2 ], TEXT(".Spr") );
						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 2 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						// ��æƮ ����Ʈ ���ϸ� �̾ƿ���
						TCHAR szTempEnchantEffectFileName[256];
						ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
						GetEnchantEffectFileName(m_strWeapon, JewelWeapon ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);

						if ( pImgSpr && JewelWeapon )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						}

						if (strlen(szTempEnchantEffectFileName) > 0)
						{
							TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
						}
					}
					break;
				case 4:			// ���� ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 3 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("LHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 3 ], TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 3 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						// ��æƮ ����Ʈ ���ϸ� �̾ƿ���
						TCHAR szTempEnchantEffectFileName[256];
						ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
						GetEnchantEffectFileName(m_strWeapon, JewelWeapon ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);

						if ( pImgSpr && JewelWeapon )
						{
							cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						}

						if (strlen(szTempEnchantEffectFileName) > 0)
						{
							TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
						}
					}
					break;
				case 5:			// ���� �̹���
					{
						if ( m_bIsTakeMantle )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							if ( pImgSpr && JewelMantle )
							{
								cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
								pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							}
						}
					}
					break;
				case 6:			// ��� �̹���
					{
						if ( m_bIsTakeEquipment )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							if ( pImgSpr && JewelMantle )
							{
								cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
								pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							}
						}
					}
					break;
				case 7:			// �� �̹��� ( �� �̹����� ���� �������� "TP1" �� ��� )
					{
						if ( m_bIsTakeHorse )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 5 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHorse, TEXT("HRSTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 5 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							if ( siHorseUnique != HORSEUNIQUE_MOTORCYCLE // ������̰� �ƴϰ�
								&& 0 <= ssActionIndex - HSR1 && 8 > ssActionIndex - HSR1 	&& JewelHorse )
							{
								TSpr * pSpr = pclClient->GetGlobalSpr( GIMG_HORSEWING1 + (ssActionIndex - HSR1) );
								if( pSpr )								
								{
									GP.PutSprScreen( pSpr , ssBottomX, ssBottomY, m_ssCurrentAnimationIndex, m_bReverse );
								}
							}
							if( siPremiumpartsUnique_Slot1 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Motor(m_strWeapon, siPremiumpartsUnique_Slot1 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot2 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Motor(m_strWeapon, siPremiumpartsUnique_Slot2 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot3 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Motor(m_strWeapon, siPremiumpartsUnique_Slot3 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							

						}
					}
					break;
				case 8:						// Effect Image
					{
						if ( m_bIsEffect )
						{
							switch( m_siEffectKind )
							{
							case 1:
							case 2:
								{
									if ( ssActionIndex < HBU2 || 
										ssActionIndex == HSR1 ||
										ssActionIndex == HTR2
										)
									{
										StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

										TSpr *pImgSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX - 110, ssBottomY - 100, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, 										m_ssCurrentAnimationIndex );

									}
								}
								break;
							default:
								{
									StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), m_strCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

									TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
								break;
							}
						}
						if ( m_bIsTakeHorse)
						{
							if( siPremiumpartsUnique_Slot1 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Horse(m_strWeapon, siPremiumpartsUnique_Slot1 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot2 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Horse(m_strWeapon, siPremiumpartsUnique_Slot2 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							if( siPremiumpartsUnique_Slot3 > 0)
							{
								TCHAR szTempEnchantEffectFileName[256];
								ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
								GetPremiumPartsEffectFileName_Horse(m_strWeapon, siPremiumpartsUnique_Slot3 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
								if (strlen(szTempEnchantEffectFileName) > 0)
								{
									TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
							}
							////Ǯ���� �϶� 
							//if( siPremiumpartsUnique_Slot1 > 0 && siPremiumpartsUnique_Slot2 > 0 && siPremiumpartsUnique_Slot3 > 0 )
							//{
							//	TCHAR szTempEnchantEffectFileName[256];
							//	ZeroMemory(szTempEnchantEffectFileName, sizeof(szTempEnchantEffectFileName));
							//	GetPremiumPartsFullEffectFileName(m_strWeapon, siPremiumpartsUnique_Slot1 ,siPremiumpartsUnique_Slot2 ,siPremiumpartsUnique_Slot3 ,g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, szTempEnchantEffectFileName, 256);
							//	if (strlen(szTempEnchantEffectFileName) > 0)
							//	{
							//		TSpr *pImgEnhantSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, szTempEnchantEffectFileName, ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
							//	}
							//}

						}
					}
					break;
				default:		// �� ������ ��.
					break;
				}
			}
		}
	}

	return;
}

void CCharacterDrawing::DrawCharacterSelectMode( short ssActionIndex, char cDirection, short ssAnimationIndex,
												short ssBottomX, short ssBottomY, SI32 JewelWeapon, SI32 JewelHelmet,
												SI32 JewelArmor, SI32 JewelMantle,bool JewelHorse,
												bool AttackScroll,SI08 AttackScrollNum, bool* Reverse,SI32* EffectX,
												SI32* EffectY,SI32* EffectFont,SI32* AttackImg )
{
	if ( ssActionIndex < HITU || ( ssActionIndex > SPCU && ssActionIndex < HITR ) )
	{
		g_BaseDataMgr.GetWeaponInfo( m_strWeapon, ssActionIndex );

		if ( m_bIsTakeHorse )
		{
			ssActionIndex += HSR1;
		}
	}

	TCHAR temp[256] = TEXT("");
	StringCchCopy( temp, 256, m_strTempCharacterKind );
	StringCchCat( temp, 256, g_BaseDataMgr.m_pstAction[ssActionIndex].strActionCode );
	CMinDataObj *pTemp = g_MinDataMgr.GetSameMinDataObjPtr( temp );

	if ( pTemp == NULL )
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, temp, TEXT("Min File is Not Exist"), MB_OK|MB_TOPMOST );
		return;
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Min ������ ������ �о���� �κ�
	m_ssAnimationNum = pTemp->GetFrameNum();	
	m_cCurrentActionIndex = pTemp->GetActionIndex();



	pTemp->CopySequence( (int**)m_siDrawingSequence );

	//////////////////////////////////////////////////////////////////////////////////
	m_bReverse = false;

	// ���� ó��... ������ �ѹ��� ¥���ε�, �ٸ� ������ ���� ��쿡 ����...
	if ( pTemp->GetDirectionNum() < 2 )
	{
		if ( pTemp->GetDirectionNum() - 1 < cDirection )
		{
			cDirection = 0;
			m_cCurrentDirection = 0;
		}
	}

	m_cCurrentDirection = cDirection;
	char cTempDirection = m_cCurrentDirection;

	if ( cDirection > CCD_NORTH_WEST )
	{
		cTempDirection = CCD_NORTH_WEST - ( cTempDirection - CCD_NORTH_WEST );

		m_ssAnimationStartIndex = m_ssAnimationNum * cTempDirection;
		m_bReverse = true;
	}
	else
	{
		m_ssAnimationStartIndex = m_ssAnimationNum * cTempDirection;
		m_bReverse = false;
	}

	m_ssAnimationEndIndex = m_ssAnimationStartIndex + m_ssAnimationNum;
	m_ssCurrentAnimationIndex = m_ssAnimationStartIndex + ssAnimationIndex;

	if ( m_ssCurrentAnimationIndex > m_ssAnimationEndIndex - 1 )
	{

#ifdef _DEBUG
		TCHAR ErrorLog[256];
		TCHAR* pText = GetTxtFromMgr(3882);
		StringCchPrintf( ErrorLog, 256, pText, ssAnimationIndex );
		//MessageBox( NULL, ErrorLog, TEXT("�Է°� Ȯ���� �ּ���.\n�� �޽��� �ڽ� �߸� �ȵǿ�..."), MB_OK|MB_TOPMOST );
#endif

		m_ssCurrentAnimationIndex = m_ssAnimationStartIndex;
	}

	/*
	if ( m_cGameMode == CCD_GAMEMODE_SERVER )
	{
		return;
	}
	*/

		ZeroMemory( m_strFileName[ cTempDirection ], sizeof( m_strFileName[ cTempDirection ] ) );

	if ( m_cCurrentActionIndex == DTHU || m_cCurrentActionIndex == DTHR )
	{		
		switch ( m_cCurrentActionIndex )
		{
		case DTHU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sDTHU.Spr"), m_strTempCharacterKind );
			}
			break;
		case DTHR:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\%sTOR%sDTHR.Spr"), m_strHorse, m_strTempCharacterKind );
			}
			break;
		}

		g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
	}
	else if ( m_cCurrentActionIndex > SPCR )		// ���� ��� 
	{
		switch( m_cCurrentActionIndex )
		{
		case FSHU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sFSHU.Spr"), m_strTempCharacterKind );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX - 55, ssBottomY - 50, 430, 279, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX - 55, ssBottomY - 50, 430, 279, m_ssCurrentAnimationIndex );
				}
			}
			break;
		case FAMU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sFAMU.Spr"), m_strTempCharacterKind  );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 99, ssBottomY + 100, 122, 117, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 99, ssBottomY + 100, 122, 117, m_ssCurrentAnimationIndex );
				}
			}
			break;
		//KHY - 1014 - �漮 �߰�.
		case SLEP:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSLEP.Spr"), m_strTempCharacterKind );

				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 5, ssBottomY + 35, 122, 117, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 5, ssBottomY + 35, 122, 117, m_ssCurrentAnimationIndex );
				}
			}
			break;
		// PCK : ���ڴ� �Ŀ��� �漮 �߰�(09.06.16)
		case SLEC:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSLEC.Spr"), m_strTempCharacterKind );

				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 65 , 122, 117, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 65, 122, 117, m_ssCurrentAnimationIndex );
				}
			}
			break;
		case MINU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMINU.Spr"), m_strTempCharacterKind  );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, 220, 200, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, 220, 200, m_ssCurrentAnimationIndex );
				}
			}
			break;
		case MAMU:
			{
				if( _tcscmp( m_strTempCharacterKind,TEXT("TP1")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 95 , 88, 111, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 95, 88, 111, m_ssCurrentAnimationIndex );
					}
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP2")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3 , 98, 102, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3, 98, 102, m_ssCurrentAnimationIndex );
					}
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP3")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 95 , 88, 107, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113  , ssBottomY + 95, 88, 107, m_ssCurrentAnimationIndex );
					}
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP4")) == 0 )
				{
					// �������� �̹���
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMAMU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3 , 98, 102, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX +5  , ssBottomY -3 , 320, 240, m_ssCurrentAnimationIndex );

					}
				}
			}
			break;
		case MHEU:
			{
				// ������ �̹���
				if( _tcscmp( m_strCharacterKind,TEXT("TP1")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strCharacterKind,TEXT("TP2")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strCharacterKind,TEXT("TP3")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strCharacterKind,TEXT("TP4")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMHEU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
			}
			break;
		case MFOU:
			{
				// �������� �̹���
				if( _tcscmp( m_strCharacterKind,TEXT("TP1")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strCharacterKind,TEXT("TP2")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strCharacterKind,TEXT("TP3")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strCharacterKind,TEXT("TP4")) == 0 )
				{
					StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sMFOU.Spr"), m_strTempCharacterKind  );				

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 55, ssBottomY + 45, 104, 96, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX+ 55, ssBottomY+ 45, 104, 96, m_ssCurrentAnimationIndex );
					}	
				}
			}
			break;
		case SITU:
			{
				StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSITU.Spr"), m_strTempCharacterKind  );
				if ( m_bReverse )
				{
					g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, 220, 200, m_ssCurrentAnimationIndex );
				}
				else
				{
					g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, 220, 200, m_ssCurrentAnimationIndex );
				}
			}
			break;
		case SOPU:
			{
				// ���� ���� ���� �̹���
				if( _tcscmp( m_strTempCharacterKind,TEXT("TP1")) == 0 )
				{
					// [����] ���Ű��� ���Ž� �̹��� ����
					if ( pclClient->pclCM->CR[1]->bIsElectionStump == true )
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sEP.Spr"), m_strTempCharacterKind  );
					}
					else
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );
					}

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ],  ssBottomX + 113, ssBottomY + 100, 81, 107, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 81, 107, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP2")) == 0 )
				{
					// [����] ���Ű��� ���Ž� �̹��� ����
					if ( pclClient->pclCM->CR[1]->bIsElectionStump == true )
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sEP.Spr"), m_strTempCharacterKind  );
					}
					else
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );
					}

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 103, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 103, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP3")) == 0 )
				{
					// [����] ���Ű��� ���Ž� �̹��� ����
					if ( pclClient->pclCM->CR[1]->bIsElectionStump == true )
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sEP.Spr"), m_strTempCharacterKind  );
					}
					else
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );
					}

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 80, 101, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 80, 101, m_ssCurrentAnimationIndex );
					}	
				}
				else if( _tcscmp( m_strTempCharacterKind,TEXT("TP4")) == 0 )
				{
					// [����] ���Ű��� ���Ž� �̹��� ����
					if ( pclClient->pclCM->CR[1]->bIsElectionStump == true )
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sEP.Spr"), m_strTempCharacterKind  );
					}
					else
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("CCD\\ImageData\\KOR01TOR%sSOPU.Spr"), m_strTempCharacterKind  );
					}

					if ( m_bReverse )
					{
						g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 102, m_ssCurrentAnimationIndex );
					}
					else
					{
						g_XSPRMgr.PutSprT(  ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX + 113, ssBottomY + 100, 79, 102, m_ssCurrentAnimationIndex );
					}	
				}
			}
			break;
		}

	}
	else
	{		
		for ( int i = 0; i < MAX_DRAWING_SEQUENCE_NUM; ++i )
		{
			if ( m_bReverse )
			{
				switch ( m_siDrawingSequence[ cTempDirection ] [ i ] )
				{
				case 0:			//�� ����.
					break;
				case 1:			// ����
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHelmet, TEXT("HED"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelHelmet )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelHelmet);
						//}
					}
					break;
				case 2:			// ����
					{
						if( _tcscmp( m_strArmor, TEXT("KOR01") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
						else if( _tcscmp( m_strArmor, TEXT("DRE36") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE35") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
						else if( _tcscmp( m_strArmor, TEXT("DRE39") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE40") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// ������ ���� �׸� ����?
						else if( _tcscmp( m_strArmor, TEXT("DRE58") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE57") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// PCK : ������ �ǻ� �߰�
						else if( _tcscmp( m_strArmor, TEXT("DRE64") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE65") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// PCK : ��ȥ���� �߰� (09.05.20)
						else if( _tcscmp( m_strArmor, TEXT("DRE66") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE67") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						else if( _tcscmp( m_strArmor, TEXT("DRE19") ) == 0  )
						{
							TCHAR exeptCharKind[4] = {'\0',};

							StringCchPrintf(exeptCharKind,4,m_strTempCharacterKind);


							if( _tcscmp( exeptCharKind, TEXT("TP3") ) == 0  )
							{	
								StringCchPrintf( exeptCharKind , 4 , TEXT("TP1") );
							}
							else if( _tcscmp( exeptCharKind, TEXT("TP4") ) == 0  )
							{
								StringCchPrintf( exeptCharKind , 4 , TEXT("TP2") );
							}

							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), exeptCharKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						else
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}

						//sprintf( m_strFileName[ cTempDirection ][ 1 ], TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 1 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelArmor )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelArmor);
						//}
					}
					break;
				case 3:			// ������ ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 2 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("RHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 2 ], TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 2 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelWeapon )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						//}
					}
					break;
				case 4:			// ���� ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 3 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("LHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 3], TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 3 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelWeapon )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						//}
					}
					break;
				case 5:			// ���� �̹���
					{
						if ( m_bIsTakeMantle )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							//if ( pImgSpr && JewelMantle )
							//{
							//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							//	pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							//}
						}
					}
					break;
				case 6:			// ��� �̹���
					{
						if ( m_bIsTakeEquipment )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							//if ( pImgSpr && JewelMantle )
							//{
							//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							//	pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							//}
						}
					}
					break;
				case 7:			// �� �̹��� ( �� �̹����� ���� �������� "TP1" �� ��� )
					{
						if ( m_bIsTakeHorse )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 5 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHorse, TEXT("HRSTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 5 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						}
					}
					break;
				case 8:						// Effect Image
					{
						if ( m_bIsEffect )
						{
							switch( m_siEffectKind )
							{
							case 1:
							case 2:
								{
									if ( ssActionIndex < HBU2 || 
										ssActionIndex == HSR1 ||
										ssActionIndex == HTR2
										)
									{
										StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

										TSpr *pImgSpr = g_XSPRMgr.PutSprScreenRT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX - 110 , ssBottomY - 100, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

									}
								}
								break;
							default:
								{
									StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), m_strCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

									TSpr *pImgSpr = g_XSPRMgr.PutSprRT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
								break;
							}
						}
					}
					break;
				default:		// �� ����
					break;
				}
			}
			else
			{
				switch ( m_siDrawingSequence[ cTempDirection ] [ i ] )
				{
				case 0:			//�� ����.
					break;
				case 1:			// ����					
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 0 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHelmet, TEXT("HED"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 0 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelHelmet )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelHelmet);
						//}
					}
					break;
				case 2:			// ����	
					{
						if( _tcscmp( m_strArmor, TEXT("KOR01") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
						else if( _tcscmp( m_strArmor, TEXT("DRE36") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE35") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// ĳ���� 4���� �Ǻ��� ���� �ٸ���.
						else if( _tcscmp( m_strArmor, TEXT("DRE39") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE40") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// ������ ���� �׸� ����?
						else if( _tcscmp( m_strArmor, TEXT("DRE58") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE57") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// PCK : ������ �ǻ� �߰�
						else if( _tcscmp( m_strArmor, TEXT("DRE64") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE65") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						// PCK : ��ȥ���� �߰� (09.05.20)
						else if( _tcscmp( m_strArmor, TEXT("DRE66") ) == 0  || _tcscmp( m_strArmor, TEXT("DRE67") ) == 0 )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						else if( _tcscmp( m_strArmor, TEXT("DRE19") ) == 0  )
						{
							TCHAR exeptCharKind[4] = {'\0',};

							StringCchPrintf(exeptCharKind,4,m_strTempCharacterKind);


							if( _tcscmp( exeptCharKind, TEXT("TP3") ) == 0  )
							{	
								StringCchPrintf( exeptCharKind , 4 , TEXT("TP1") );
							}
							else if( _tcscmp( exeptCharKind, TEXT("TP4") ) == 0  )
							{
								StringCchPrintf( exeptCharKind , 4 , TEXT("TP2") );
							}

							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TOR"), exeptCharKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}
						else
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 1 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						}

						//sprintf( m_strFileName[ cTempDirection ][ 1 ], TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strArmor, TEXT("TORTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 1 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelArmor )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelArmor);
						//}
					}

					break;
				case 3:			// ������ ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 2 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("RHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 2 ], TEXT(".Spr") );
						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 2 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelWeapon )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						//}
					}
					break;
				case 4:			// ���� ��
					{
						StringCchPrintf( m_strFileName[ cTempDirection ][ 3 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strWeapon, TEXT("LHDTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
						//strcat( m_strFileName[ cTempDirection ][ 3 ], TEXT(".Spr") );

						TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 3 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

						//if ( pImgSpr && JewelWeapon )
						//{
						//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
						//	pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelWeapon);
						//}
					}
					break;
				case 5:			// ���� �̹���
					{
						if ( m_bIsTakeMantle )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strMantle, TEXT("ACC"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							//if ( pImgSpr && JewelMantle )
							//{
							//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							//	pclmap->MakeRareItemSmoke(true, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							//}
						}
					}
					break;
				case 6:			// ��� �̹���
					{
						if ( m_bIsTakeEquipment )
						{
							if (m_cCurrentActionIndex == SITU)
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), m_strTempCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );
							else
								StringCchPrintf( m_strFileName[ cTempDirection ][ 4 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEquipment, TEXT("ACO"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							//strcat( m_strFileName[ cTempDirection ][ 4], TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 4 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );

							//if ( pImgSpr && JewelMantle )
							//{
							//	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
							//	pclmap->MakeRareItemSmoke(false, ssBottomX, ssBottomY, pImgSpr->GetXSize(), pImgSpr->GetYSize(), &pImgSpr->pImage[pImgSpr->header.ImageInfo[m_ssCurrentAnimationIndex].iStartPos], JewelMantle );
							//}
						}
					}
					break;
				case 7:			// �� �̹��� ( �� �̹����� ���� �������� "TP1" �� ��� )
					{
						if ( m_bIsTakeHorse )
						{
							StringCchPrintf( m_strFileName[ cTempDirection ][ 5 ], _MAX_PATH, TEXT("%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strHorse, TEXT("HRSTP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

							TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 5 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
						}
					}
					break;
				case 8:						// Effect Image
					{
						if ( m_bIsEffect )
						{
							switch( m_siEffectKind )
							{
							case 1:
							case 2:
								{
									if ( ssActionIndex < HBU2 || 
										ssActionIndex == HSR1 ||
										ssActionIndex == HTR2
										)
									{
										StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), TEXT("TP1"), g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

										TSpr *pImgSpr = g_XSPRMgr.PutSprScreenT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX - 110, ssBottomY - 100, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, 										m_ssCurrentAnimationIndex );

									}
								}
								break;
							default:
								{
									StringCchPrintf( m_strFileName[ cTempDirection ][ 6 ], _MAX_PATH, TEXT("%s%s%s%s%s%s"), TEXT("CCD\\ImageData\\"), m_strEffect, TEXT("EFF"), m_strCharacterKind, g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT(".Spr") );

									TSpr *pImgSpr = g_XSPRMgr.PutSprT( ssActionIndex, m_strFileName[ cTempDirection ][ 6 ], ssBottomX, ssBottomY, CHARACTER_TILE_WIDTH, CHARACTER_TILE_HEIGHT, m_ssCurrentAnimationIndex );
								}
								break;
							}
						}
					}
					break;
				default:		// �� ������ ��.
					break;
				}
			}
		}
	}

	return;
}



char CCharacterDrawing::GetFrameNum( int siActionIndex )
{
	return g_BaseDataMgr.m_pstAction[ siActionIndex ].cFrameNum;
}

char CCharacterDrawing::GetAttackFrameNum( int siActionIndex )
{
	return g_BaseDataMgr.m_pstAction[ siActionIndex ].cAttackFrameNum;
}

short CCharacterDrawing::GetCurrentFrameIndex()
{
	return m_ssCurrentAnimationIndex - m_ssAnimationStartIndex;
}

char CCharacterDrawing::GetDelayTime( int siActionIndex, int CharacterKind )
{
	return g_MinDataMgr.GetDelayTimeIndex( siActionIndex, (CharacterKind%2)?1:2 );
}

short CCharacterDrawing::GetCharacterXSize()
{
	return CHARACTER_TILE_WIDTH;
}

short CCharacterDrawing::GetCharacterYSize()
{
	return CHARACTER_TILE_HEIGHT;
}

int CCharacterDrawing::GetLoadedImageNum()
{
	return g_XSPRMgr.GetLoadedImageNum();
}

void CCharacterDrawing::SetScrollEffect( TSpr *pImgSpr, short ssBottomX, short ssBottomY, SI08 siNum, bool bHaveHorse, bool* Reverse, SI32* EffectX, SI32* EffectY,SI32* EffectFont,SI32* AttackImg)
{
	return;
	/*	if( bHaveHorse )
	{
	// ���� �����϶�
	if( siNum < EFFECT_SCROLL_NUM )
	{
	SI32 attackimg = GIMG_SPECIAL_SWORD_HORSE ;

	if ( _tcsstr(m_strWeapon, TEXT("AXE")) )
	{
	attackimg = GIMG_SPECIAL_AXE_HORSE ;
	}
	else if ( _tcsstr(m_strWeapon, TEXT("SPE")) )
	{
	if ( _tcsstr(g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT("2HT")) )
	{
	attackimg = GIMG_SPECIAL_SPEAR_JAB_HORSE ;
	}
	else
	{
	attackimg = GIMG_SPECIAL_SPEAR_BRANDISH_HORSE ;
	}
	}
	TSpr* pspr	= pclClient->GetGImgPointer(attackimg);
	if ( pspr )
	{
	SI32 startx		= ssBottomX + pImgSpr->clHeader.siXsize/2 - pspr->clHeader.siXsize/2;
	SI32 starty		= ssBottomY + pImgSpr->clHeader.siYsize/2 - pspr->clHeader.siYsize/2;

	*Reverse = m_bReverse ;
	*EffectX = startx ;
	*EffectY = starty ;
	*EffectFont = m_ssCurrentAnimationIndex ;
	*AttackImg = attackimg ;
	//								pspr->PutSprScreenT(startx , starty, m_ssCurrentAnimationIndex,m_bReverse);
	}
	}
	else if( siNum >= EFFECT_SCROLL_NUM )	// ���� 4���϶�
	{
	SI32 attackimg = GIMG_SPECIAL_NEW_SWORD_HORSE ;
	if ( _tcsstr(m_strWeapon, TEXT("AXE")) )
	{
	attackimg = GIMG_SPECIAL_NEW_AXE_HORSE ;
	}
	else if ( _tcsstr(m_strWeapon, TEXT("SPE")) )
	{
	if ( _tcsstr(g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT("2HT")) )
	{
	attackimg = GIMG_SPECIAL_NEW_SPEAR_JAB_HORSE ;
	}
	else
	{
	attackimg = GIMG_SPECIAL_NEW_SPEAR_BRANDISH_HORSE ;
	}
	}
	TSpr* pspr	= pclClient->GetGImgPointer(attackimg);
	if ( pspr )
	{
	SI32 startx		= ssBottomX + pImgSpr->clHeader.siXsize/2 - pspr->clHeader.siXsize/2;
	SI32 starty		= ssBottomY + pImgSpr->clHeader.siYsize/2 - pspr->clHeader.siYsize/2;

	*Reverse = m_bReverse ;
	*EffectX = startx ;
	*EffectY = starty ;
	*EffectFont = m_ssCurrentAnimationIndex ;
	*AttackImg = attackimg ;
	//								pspr->PutSprScreenT(startx , starty, m_ssCurrentAnimationIndex,m_bReverse);
	}
	}
	}
	else
	{
	// ���� �����϶�
	if( siNum < EFFECT_SCROLL_NUM )
	{
	SI32 attackimg = GIMG_SPECIAL_SWORD ;

	if ( _tcsstr(m_strWeapon, TEXT("AXE")) )
	{
	attackimg = GIMG_SPECIAL_AXE ;
	}
	else if ( _tcsstr(m_strWeapon, TEXT("SPE")) )
	{
	if ( _tcsstr(g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT("2HT")) )
	{
	attackimg = GIMG_SPECIAL_SPEAR_JAB ;
	}
	else
	{
	attackimg = GIMG_SPECIAL_SPEAR_BRANDISH ;
	}
	}
	TSpr* pspr	= pclClient->GetGImgPointer(attackimg);
	if ( pspr )
	{
	SI32 startx		= ssBottomX + pImgSpr->clHeader.siXsize/2 - pspr->clHeader.siXsize/2;
	SI32 starty		= ssBottomY + pImgSpr->clHeader.siYsize/2 - pspr->clHeader.siYsize/2;

	*Reverse = m_bReverse ;
	*EffectX = startx ;
	*EffectY = starty ;
	*EffectFont = m_ssCurrentAnimationIndex ;
	*AttackImg = attackimg ;
	//								pspr->PutSprScreenT(startx , starty, m_ssCurrentAnimationIndex,m_bReverse);
	}
	}
	else if( siNum >= EFFECT_SCROLL_NUM )	// ���� 2���϶�
	{
	SI32 attackimg = GIMG_SPECIAL_NEW_SWORD ;
	if ( _tcsstr(m_strWeapon, TEXT("AXE")) )
	{
	attackimg = GIMG_SPECIAL_NEW_AXE ;
	}
	else if ( _tcsstr(m_strWeapon, TEXT("SPE")) )
	{
	if ( _tcsstr(g_BaseDataMgr.m_pstAction[m_cCurrentActionIndex].strActionCode, TEXT("2HT")) )
	{
	attackimg = GIMG_SPECIAL_NEW_SPEAR_JAB ;
	}
	else
	{
	attackimg = GIMG_SPECIAL_NEW_SPEAR_BRANDISH ;
	}
	}
	TSpr* pspr	= pclClient->GetGImgPointer(attackimg);
	if ( pspr )
	{
	SI32 startx		= ssBottomX + pImgSpr->clHeader.siXsize/2 - pspr->clHeader.siXsize/2;
	SI32 starty		= ssBottomY + pImgSpr->clHeader.siYsize/2 - pspr->clHeader.siYsize/2;

	*Reverse = m_bReverse ;
	*EffectX = startx ;
	*EffectY = starty ;
	*EffectFont = m_ssCurrentAnimationIndex ;
	*AttackImg = attackimg ;
	//								pspr->PutSprScreenT(startx , starty, m_ssCurrentAnimationIndex,m_bReverse);
	}
	}
	}*/
}
void CCharacterDrawing::GetEnchantEffectFileName(TCHAR* pszWeaponCode, UI32 uiJewelEffect, TCHAR* pszActionCode, TCHAR* pszFileName, SI32 siFileNameLen)
{
	// Weaponcode�� ���� 3�ڸ��� �����Ѵ�.
	TCHAR TempWeaponCode[8];
	strncpy(TempWeaponCode, pszWeaponCode, 3);
	TempWeaponCode[3] = '\0';

	// Actioncode�� 4�ڸ��� �����Ѵ�.
	TCHAR TempActionCode[8];
	strncpy(TempActionCode, pszActionCode, 4);
	TempActionCode[4] = '\0';

	//���� ������ ���� ������ �ٲ۴�.
	if(strncmp(TempWeaponCode, "AXE", 3) == 0)
	{
		strncpy(TempWeaponCode, "SWD", 3);
	}

	// ActionCode�� 2HGU, 2HGR�̰�, WeaponCode�� BOW�ϰ��� �����̹Ƿ�, WeaponCode�� "CBW"��, ActionCode�� 2HBU, 2HBR�� �����Ѵ�.
	if ((strncmp(TempActionCode, "2HGU", 4) == 0) && (strncmp(TempWeaponCode, "BOW", 3) == 0))
	{
		strncpy(TempWeaponCode, "CBW", 3);
		strncpy(TempActionCode, "2HBU", 4);
	}
	else if ((strncmp(TempActionCode, "2HGR", 4) == 0) && (strncmp(TempWeaponCode, "BOW", 3) == 0))
	{
		strncpy(TempWeaponCode, "CBW", 3);
		strncpy(TempActionCode, "2HBR", 4);
	}

	// ActionCode�� HIT(�ǰ�), MOV(�̵�), WT1(���1), WT2(���2) �̸� WeaponCode�� "KOR"�� �����Ѵ�.
	if((strncmp(pszActionCode, "HIT", 3) == 0) || (strncmp(pszActionCode, "MOV", 3) == 0) || (strncmp(pszActionCode, "WT1", 3) == 0) || (strncmp(pszActionCode, "WT2", 3) == 0) )
	{
		strncpy(TempWeaponCode, "KOR", 3);
	}

	// ��æƮ ����Ʈ �ڵ�
	TCHAR szTempEffectCode[8];
	ZeroMemory(szTempEffectCode, sizeof(szTempEffectCode));

	if      ((uiJewelEffect & JEWELEFFECT_WATER1) )	{	strncpy(szTempEffectCode, "WAT01", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_WATER2) )	{	strncpy(szTempEffectCode, "WAT02", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_WATER3) )	{	strncpy(szTempEffectCode, "WAT03", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_GROUND1))	{	strncpy(szTempEffectCode, "GRD01", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_GROUND2))	{	strncpy(szTempEffectCode, "GRD02", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_GROUND3))	{	strncpy(szTempEffectCode, "GRD03", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_WIND1)  )	{	strncpy(szTempEffectCode, "WND01", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_WIND2)  )	{	strncpy(szTempEffectCode, "WND02", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_WIND3)  )	{	strncpy(szTempEffectCode, "WND03", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_FIRE1)  )	{	strncpy(szTempEffectCode, "FIR01", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_FIRE2)  )	{	strncpy(szTempEffectCode, "FIR02", sizeof(szTempEffectCode));	}
	else if ((uiJewelEffect & JEWELEFFECT_FIRE3)  )	{	strncpy(szTempEffectCode, "FIR03", sizeof(szTempEffectCode));	}
	else
	{
		return;
	}

	// ��æƮ ����Ʈ ���ϸ��� ��ȯ�Ѵ�.
	StringCchPrintf( pszFileName, siFileNameLen, TEXT("%s%s%s%s%s"), TEXT("CCD\\EnchantEffectData\\EEff"),  TempWeaponCode, szTempEffectCode, TempActionCode, TEXT(".Spr"));
}
void CCharacterDrawing::GetPremiumPartsEffectFileName_Motor(TCHAR* pszWeaponCode, SI32 siPremiumpartsUnique, TCHAR* pszActionCode, TCHAR* pszFileName, SI32 siFileNameLen)
{
	// Weaponcode�� ���� 3�ڸ��� �����Ѵ�.
	TCHAR TempWeaponCode[8];
	strncpy(TempWeaponCode, pszWeaponCode, 3);
	TempWeaponCode[3] = '\0';

	// Actioncode�� 4�ڸ��� �����Ѵ�.
	TCHAR TempActionCode[8];
	strncpy(TempActionCode, pszActionCode, 4);
	TempActionCode[4] = '\0';

	//����/��/���ô�/��� ������ ���� ������ �ٲ۴�.
	if( strncmp(TempWeaponCode, "AXE", 3) == 0 
		|| strncmp(TempWeaponCode, "ROD", 3) == 0 
		|| strncmp(TempWeaponCode, "SIK", 3) == 0 
		|| strncmp(TempWeaponCode, "HOE", 3) == 0)
	{
		strncpy(TempWeaponCode, "SWD", 3);
	}
	// ��������  �׸��� ������
	if ( (strncmp(TempActionCode, "SITU", 4) == 0)  || (strncmp(TempActionCode, "SITR", 4) == 0) ) return ;

	// ActionCode�� HIT(�ǰ�), MOV(�̵�), WT1(���1), WT2(���2) �̸� WeaponCode�� "OTH"�� �����Ѵ�.
	if((strncmp(pszActionCode, "HIT", 3) == 0) || (strncmp(pszActionCode, "MOV", 3) == 0) 
		|| (strncmp(pszActionCode, "WT1", 3) == 0) || (strncmp(pszActionCode, "WT2", 3) == 0) 
		|| (strncmp(TempActionCode, "SPCR", 4) == 0) || (strncmp(TempActionCode, "SPCU", 4) == 0) )
	{
		strncpy(TempWeaponCode, "OTH", 3);
	}

	// ��æƮ ����Ʈ �ڵ�
	TCHAR szTempEffectCode[8];
	ZeroMemory(szTempEffectCode, sizeof(szTempEffectCode));

	// ����ũ�� ���� .������ ����Ʈ�̸��� ���Ѵ�.��� ��� ���� ������Ʈ, �Ҳ��� ���׳� 
	//if      ( siPremiumpartsUnique == ITEMUNIQUE(13640) )	{	strncpy(szTempEffectCode, "GGLE", sizeof(szTempEffectCode));	}	// ���
	//else if ( siPremiumpartsUnique == ITEMUNIQUE(13639) )	{	strncpy(szTempEffectCode, "REIN", sizeof(szTempEffectCode));	}	// ���
	//else if ( siPremiumpartsUnique == ITEMUNIQUE(13638) )	{	strncpy(szTempEffectCode, "STIR", sizeof(szTempEffectCode));	}	// ����
	//else 
	if ( siPremiumpartsUnique == ITEMUNIQUE(13635) )	{	strncpy(szTempEffectCode, "HEAD", sizeof(szTempEffectCode));	}	// ������Ʈ
	else if ( siPremiumpartsUnique == ITEMUNIQUE(13636) )	{	strncpy(szTempEffectCode, "WHEL", sizeof(szTempEffectCode));	}	// �Ҳ���
	else if ( siPremiumpartsUnique == ITEMUNIQUE(13637) )	{	strncpy(szTempEffectCode, "ANTE", sizeof(szTempEffectCode));	}	// ���׳�
	else
	{
		return;
	}

	// ��æƮ ����Ʈ ���ϸ��� ��ȯ�Ѵ�.
	StringCchPrintf( pszFileName, siFileNameLen, TEXT("%s%s%s%s%s"), TEXT("CCD\\HorsePremiumItemEffectData\\EFT"),  TempWeaponCode, szTempEffectCode, TempActionCode, TEXT(".Spr"));
}
void CCharacterDrawing::GetPremiumPartsEffectFileName_Horse(TCHAR* pszWeaponCode, SI32 siPremiumpartsUnique, TCHAR* pszActionCode, TCHAR* pszFileName, SI32 siFileNameLen)
{
	// Weaponcode�� ���� 3�ڸ��� �����Ѵ�.
	TCHAR TempWeaponCode[8];
	strncpy(TempWeaponCode, pszWeaponCode, 3);
	TempWeaponCode[3] = '\0';

	// Actioncode�� 4�ڸ��� �����Ѵ�.
	TCHAR TempActionCode[8];
	strncpy(TempActionCode, pszActionCode, 4);
	TempActionCode[4] = '\0';

	//����/��/���ô�/��� ������ ���� ������ �ٲ۴�.
	if( strncmp(TempWeaponCode, "AXE", 3) == 0 
		|| strncmp(TempWeaponCode, "ROD", 3) == 0 
		|| strncmp(TempWeaponCode, "SIK", 3) == 0 
		|| strncmp(TempWeaponCode, "HOE", 3) == 0)
	{
		strncpy(TempWeaponCode, "SWD", 3);
	}
	// ��������  �׸��� ������
	if ( (strncmp(TempActionCode, "SITU", 4) == 0)  || (strncmp(TempActionCode, "SITR", 4) == 0) ) return ;

	// ActionCode�� HIT(�ǰ�), MOV(�̵�), WT1(���1), WT2(���2) �̸� WeaponCode�� "OTH"�� �����Ѵ�.
	if((strncmp(pszActionCode, "HIT", 3) == 0) || (strncmp(pszActionCode, "MOV", 3) == 0) 
		|| (strncmp(pszActionCode, "WT1", 3) == 0) || (strncmp(pszActionCode, "WT2", 3) == 0) 
		|| (strncmp(TempActionCode, "SPCR", 4) == 0) || (strncmp(TempActionCode, "SPCU", 4) == 0) )
	{
		strncpy(TempWeaponCode, "OTH", 3);
	}

	// ��æƮ ����Ʈ �ڵ�
	TCHAR szTempEffectCode[8];
	ZeroMemory(szTempEffectCode, sizeof(szTempEffectCode));

	// ����ũ�� ���� .������ ����Ʈ�̸��� ���Ѵ�.��� ��� ���� ������Ʈ, �Ҳ��� ���׳� 
	if      ( siPremiumpartsUnique == ITEMUNIQUE(13640) )	{	strncpy(szTempEffectCode, "GGLE", sizeof(szTempEffectCode));	}	// ���
	else if ( siPremiumpartsUnique == ITEMUNIQUE(13639) )	{	strncpy(szTempEffectCode, "REIN", sizeof(szTempEffectCode));	}	// ���
	else if ( siPremiumpartsUnique == ITEMUNIQUE(13638) )	{	strncpy(szTempEffectCode, "STIR", sizeof(szTempEffectCode));	}	// ����
	else
	{
		return;
	}

	// ��æƮ ����Ʈ ���ϸ��� ��ȯ�Ѵ�.
	StringCchPrintf( pszFileName, siFileNameLen, TEXT("%s%s%s%s%s"), TEXT("CCD\\HorsePremiumItemEffectData\\EFT"),  TempWeaponCode, szTempEffectCode, TempActionCode, TEXT(".Spr"));
}
void CCharacterDrawing::GetPremiumPartsFullEffectFileName(TCHAR* pszWeaponCode, SI32 siPremiumpartsUnique1,SI32 siPremiumpartsUnique2,SI32 siPremiumpartsUnique3, TCHAR* pszActionCode, TCHAR* pszFileName, SI32 siFileNameLen)
{
	// Weaponcode�� ���� 3�ڸ��� �����Ѵ�.
	TCHAR TempWeaponCode[8];
	strncpy(TempWeaponCode, pszWeaponCode, 3);
	TempWeaponCode[3] = '\0';

	// Actioncode�� 4�ڸ��� �����Ѵ�.
	TCHAR TempActionCode[8];
	strncpy(TempActionCode, pszActionCode, 4);
	TempActionCode[4] = '\0';

	// ActionCode�� 2HGU, 2HGR�̰�, WeaponCode�� BOW�ϰ��� �����̹Ƿ�, WeaponCode�� "CBW"��, ActionCode�� 2HBU, 2HBR�� �����Ѵ�.
	if ((strncmp(TempActionCode, "2HGU", 4) == 0) && (strncmp(TempWeaponCode, "BOW", 3) == 0))
	{
		strncpy(TempActionCode, "2HBU", 4);
	}
	else if ((strncmp(TempActionCode, "2HGR", 4) == 0) && (strncmp(TempWeaponCode, "BOW", 3) == 0))
	{
		strncpy(TempActionCode, "2HBR", 4);
	}
	strncpy(TempWeaponCode, "OTH", 3);

	// ��æƮ ����Ʈ �ڵ�
	TCHAR szTempEffectCode[8];
	ZeroMemory(szTempEffectCode, sizeof(szTempEffectCode));

	if      ( siPremiumpartsUnique1 == ITEMUNIQUE(13640) 
		||	siPremiumpartsUnique2 == ITEMUNIQUE(13640)
		||	siPremiumpartsUnique3 == ITEMUNIQUE(13640))	
	{	
		strncpy(szTempEffectCode, "HOR", sizeof(szTempEffectCode));	
	}
	else if ( siPremiumpartsUnique1 == ITEMUNIQUE(13635) 
		|| siPremiumpartsUnique2 == ITEMUNIQUE(13635)
		|| siPremiumpartsUnique3 == ITEMUNIQUE(13635))	
	{	
		strncpy(szTempEffectCode, "MOT", sizeof(szTempEffectCode));	
	}
	else
	{
		return;
	}

	// ��æƮ ����Ʈ ���ϸ��� ��ȯ�Ѵ�.
	StringCchPrintf( pszFileName, siFileNameLen, TEXT("%s%s%s%s%s"), TEXT("CCD\\HorsePremiumItemEffectData\\EFT"),  TempWeaponCode, szTempEffectCode, TempActionCode, TEXT(".Spr"));
}