#include "MarriageManager.h"

#include "Char/CharManager/CharManager.h"

#include "../../CommonLogic/CommonLogic.h"
#include "../../CommonLogic/MsgType-System.h"
#include "../../CommonLogic/MsgRval-Define.h"
#include "../../CommonLogic/Msg/MsgType-Feast.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"

#include "../../Lib/dxutil.h"

#include "../../Server/Server.h"


cltMarriageAbilityManager::cltMarriageAbilityManager() : m_pclMarriageAbilityItem(NULL)
{
	m_pclMarriageAbilityItem = new cltMarriageAbilityItem[MARRIAGE_LOVE_LEVEL_MAX];
	if ( NULL == m_pclMarriageAbilityItem )
	{
		return;
	}

	for ( SI32 siIndex=0; siIndex<MARRIAGE_LOVE_LEVEL_MAX; siIndex++ )
	{
		m_pclMarriageAbilityItem[siIndex].Init();
	}
}

cltMarriageAbilityManager::~cltMarriageAbilityManager()
{
	if ( m_pclMarriageAbilityItem )
	{
		SAFE_DELETE_ARRAY( m_pclMarriageAbilityItem );
	}
}

BOOL cltMarriageAbilityManager::LoadMarriageAbilityInfo( void )
{
	TCHAR		szFileName[MAX_PATH]	= { "Data\\MarriageAbilityInfo.txt" };

	NDataLoader	dataloader;
	BOOL		bLoadFile				= FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("cltMarriageAbilityManager::LoadMarriageAbilityInfo()"), TEXT("LoadError:[%s]"), szFileName);
		return false;
	}


	SI32	siLoveLevel			= 0;
	TCHAR	szAbilityType[64]	= TEXT("");
	SI32	siAbilityValue		= 0;
	TCHAR	szEffectType[64]	= TEXT("");

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siLoveLevel,		4,
		NDATA_MBSTRING,	&szAbilityType,		64,
		NDATA_INT32,	&siAbilityValue,	4,
		NDATA_MBSTRING,	&szEffectType,		64,
		0,0,0
	};
	
	SI32 siAbilityType	= 0;
	SI32 siEffectType	= 0;

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			siAbilityType	= ConvertAbilityTypeFromText( szAbilityType );
			siEffectType	= ConvertEffectTypeFromText( szEffectType );

			AddMarriageAbilityItem( siLoveLevel, siAbilityType, siAbilityValue, siEffectType );
		}
	}

	return true;
}

SI32 cltMarriageAbilityManager::ConvertAbilityTypeFromText( TCHAR* pszAbilityTypeText )
{
	if ( NULL == pszAbilityTypeText )
	{
		MsgBox( TEXT("MarriageAbility Type Text Error"), TEXT("Incorrect Type Text[NULL]") );
		return 0;
	}

	COMPARE_TEXT_WITH_VALUE( pszAbilityTypeText, MARRIAGE_ABILITY_TYPE_ATTACK );
	COMPARE_TEXT_WITH_VALUE( pszAbilityTypeText, MARRIAGE_ABILITY_TYPE_DEFENSE );
	COMPARE_TEXT_WITH_VALUE( pszAbilityTypeText, MARRIAGE_ABILITY_TYPE_LIFE );
	COMPARE_TEXT_WITH_VALUE( pszAbilityTypeText, MARRIAGE_ABILITY_TYPE_EXP );

	MsgBox( TEXT("MarriageAbility Type Text Error"), TEXT("Incorrect Type Text[%s]"), pszAbilityTypeText );

	return 0;
}

SI32 cltMarriageAbilityManager::ConvertEffectTypeFromText( TCHAR* pszEffectTypeText )
{
	if ( NULL == pszEffectTypeText )
	{
		MsgBox( TEXT("MarriageEffect Type Text Error"), TEXT("Incorrect Type Text[NULL]") );
		return 0;
	}

	COMPARE_TEXT_WITH_VALUE( pszEffectTypeText, MARRIAGE_EFFECT_TYPE_NONE );
	COMPARE_TEXT_WITH_VALUE( pszEffectTypeText, MARRIAGE_EFFECT_TYPE_SMALL );
	COMPARE_TEXT_WITH_VALUE( pszEffectTypeText, MARRIAGE_EFFECT_TYPE_MEDIUM );
	COMPARE_TEXT_WITH_VALUE( pszEffectTypeText, MARRIAGE_EFFECT_TYPE_LARGE );

	MsgBox( TEXT("MarriageEffect Type Text Error"), TEXT("Incorrect Type Text[%s]"), pszEffectTypeText );

	return 0;
}

void cltMarriageAbilityManager::AddMarriageAbilityItem( SI32 siLoveLevel, SI32 siAbilityType, SI32 siAbilityValue, SI32 siEffectType )
{
	if ( (MARRIAGE_LOVE_LEVEL_NONE >= siLoveLevel) || (MARRIAGE_LOVE_LEVEL_MAX <= siLoveLevel) )
	{
		MsgBox(TEXT("Add MarriageAbility Error"), TEXT("Incorrect LoveLevel:[%d]"), siLoveLevel);
		return;
	}

	if ( (MARRIAGE_ABILITY_TYPE_NONE >= siAbilityType) || (MARRIAGE_ABILITY_TYPE_MAX <= siAbilityType) )
	{
		MsgBox(TEXT("Add MarriageAbility Error"), TEXT("Incorrect Ability Type:[%d]"), siAbilityType);
		return;
	}

	if ( (MARRIAGE_EFFECT_TYPE_NONE > siEffectType) || (MARRIAGE_EFFECT_TYPE_MAX <= siEffectType) )
	{
		MsgBox(TEXT("Add MarriageAbility Error"), TEXT("Incorrect Effect Type:[%d]"), siEffectType);
		return;
	}

	if ( FALSE == m_pclMarriageAbilityItem[siLoveLevel].IsEmpty() )
	{
		MsgBox(TEXT("Add MarriageAbility Error"), TEXT("�ߺ��� ���Դϴ�") );
		return;
	}

	m_pclMarriageAbilityItem[siLoveLevel].Set( siAbilityType, siAbilityValue, siEffectType );

}

SI32 cltMarriageAbilityManager::GetTotalAbilityValue( SI32 siAbilityType, SI32 siLoveLevel )
{
	if ( NULL == m_pclMarriageAbilityItem )
	{
		return 0;
	}

	if ( (MARRIAGE_ABILITY_TYPE_NONE >= siAbilityType) || (MARRIAGE_ABILITY_TYPE_MAX <= siAbilityType) )
	{
		return 0;
	}

	if ( (MARRIAGE_LOVE_LEVEL_NONE >= siLoveLevel) || (MARRIAGE_LOVE_LEVEL_MAX <= siLoveLevel) )
	{
		return 0;
	}

	SI32 siTotalAbilityValue = 0;

	// �ش� ���������� �����Ҽ��ִ� ���� �̾ƿ´�
	for ( SI32 siIndex=MARRIAGE_LOVE_LEVEL_01; siIndex<=siLoveLevel; siIndex++ )
	{
		if ( m_pclMarriageAbilityItem[siIndex].GetAbilityType() == siAbilityType )
		{
			siTotalAbilityValue += m_pclMarriageAbilityItem[siIndex].GetAbilityValue();
		}
	}

	return siTotalAbilityValue;
}

SI32 cltMarriageAbilityManager::GetEffectType( SI32 siLoveLevel )
{
	if ( (MARRIAGE_LOVE_LEVEL_NONE >= siLoveLevel) || (MARRIAGE_LOVE_LEVEL_MAX <= siLoveLevel) )
	{
		return 0;
	}

	if ( NULL == m_pclMarriageAbilityItem )
	{
		return 0;
	}

	return m_pclMarriageAbilityItem[siLoveLevel].GetEffectType();
}


//#############################################################################################################
// ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 
//#############################################################################################################

cltMarriageManager::cltMarriageManager() : m_clAbilityMgr()
{
	m_clAbilityMgr.LoadMarriageAbilityInfo();

	// ������ 1�ʿ� �ѹ��� ������
	m_UpdateTimerWeddingAction.Init( 1 * 1000 );

	m_siWeddingMessage			= 0;
	m_siWeddingStatus			= 0;
	m_siOfficiatorID			= 0;
	m_siWeddintProgressCount	= 0;
}

cltMarriageManager::~cltMarriageManager()
{

}

void cltMarriageManager::Init( void )
{
	m_clWeddingList.RequestListProcess( true );

	m_UpdateTimerWeddingAction.SetActive( true, GetTickCount() );
}

void cltMarriageManager::InitForWeddingVariable( void )
{
	m_siWeddingMessage			= 0;
	m_siWeddingStatus			= 0;
	m_siOfficiatorID			= 0;
	m_siWeddintProgressCount	= 0;
}

void cltMarriageManager::ActionForWedding( void )
{
//----------------------
#ifdef _SERVER
//----------------------
	// �����ð��� �Ǿ�� �����Ѵ�.
	if ( false == m_UpdateTimerWeddingAction.IsTimed(GetTickCount()) )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	// ���� �ð��� ���� ���� ó���� �Ѵ�
	SI16 siCurrentYear		= pclserver->sTime.wYear;
	SI16 siCurrentMonth		= pclserver->sTime.wMonth;
	SI16 siCurrentDay		= pclserver->sTime.wDay;
	SI16 siCurrentHour		= pclserver->sTime.wHour;
	SI16 siCurrentMinute	= pclserver->sTime.wMinute;

	cltWeddingReserveUnit* pclCurrentUnit = m_clWeddingList.GetReserveUnitPtr( siCurrentYear, siCurrentMonth, siCurrentDay, siCurrentHour );
	if ( (pclCurrentUnit) && (TRUE == pclCurrentUnit->IsReserved()) )
	{
		// ������ ����
		if ( TRUE == CheckAndSetForProgressMessage(siCurrentMinute) )
		{
			PushWeddingMessage( pclCurrentUnit->m_szMate1_Name, pclCurrentUnit->m_szMate2_Name );
		}

		// 0~1�л��̿� ������ ������� �ʾҴٸ� �����Ų��
		if ( (0 <= siCurrentMinute) && (3 > siCurrentMinute) )
		{
			if ( MARRIAGE_WEDDING_STATUS_NONE == m_siWeddingStatus )
			{
				m_siWeddingStatus = MARRIAGE_WEDDING_STATUS_READY;
			}
		}

		// 30���� ������ ������ �����Ѵ�
		if ( (30 <= siCurrentMinute) && (35 > siCurrentMinute) )
		{
			if ( (MARRIAGE_WEDDING_STATUS_NONE != m_siWeddingStatus) && (MARRIAGE_WEDDING_STATUS_END != m_siWeddingStatus) )
			{
				m_siWeddingStatus = MARRIAGE_WEDDING_STATUS_END;
			}
		}

		WeddingProcess( pclCurrentUnit );
	
	}

	// 1�ð� ���� ���� ���� ó���� �Ѵ�
	SYSTEMTIME stAddTime;
	ZeroMemory( &stAddTime, sizeof(stAddTime) );

	stAddTime.wYear		= siCurrentYear;
	stAddTime.wMonth	= siCurrentMonth;
	stAddTime.wDay		= siCurrentDay;
	stAddTime.wHour		= siCurrentHour;

	TimeAddHour( &stAddTime, 1, &stAddTime );

	cltWeddingReserveUnit* pclAddUnit = m_clWeddingList.GetReserveUnitPtr( stAddTime.wYear, stAddTime.wMonth, stAddTime.wDay, stAddTime.wHour );
	if ( (pclAddUnit) && (TRUE == pclAddUnit->IsReserved()) )
	{
		// ������ ����
		if ( TRUE == CheckAndSetForFutureMessage(siCurrentMinute) )
		{
			PushWeddingMessage( pclAddUnit->m_szMate1_Name, pclAddUnit->m_szMate2_Name, true, stAddTime.wHour );
		}
	}

	// �ð��� �Ǹ� ����Ʈ ����� ���Ž�Ų��
	if ( TRUE == m_clWeddingList.IsRequestHour() )
	{
		m_clWeddingList.RequestListProcess();
	}


#endif
}

SI32 cltMarriageManager::GetTotalAttackAbilityValue( SI32 siLoveLevel )
{
	return m_clAbilityMgr.GetTotalAbilityValue( MARRIAGE_ABILITY_TYPE_ATTACK, siLoveLevel );
}

SI32 cltMarriageManager::GetTotalDefenseAbilityValue( SI32 siLoveLevel )
{
	return m_clAbilityMgr.GetTotalAbilityValue( MARRIAGE_ABILITY_TYPE_DEFENSE, siLoveLevel );
}

SI32 cltMarriageManager::GetTotalLifeAbilityValue( SI32 siLoveLevel )
{
	return m_clAbilityMgr.GetTotalAbilityValue( MARRIAGE_ABILITY_TYPE_LIFE, siLoveLevel );
}

SI32 cltMarriageManager::GetTotalExpAbilityValue( SI32 siLoveLevel )
{
	return m_clAbilityMgr.GetTotalAbilityValue( MARRIAGE_ABILITY_TYPE_EXP, siLoveLevel );
}

SI32 cltMarriageManager::GetEffectTypeFromLoveLevel( SI32 siLoveLevel )
{
	return m_clAbilityMgr.GetEffectType( siLoveLevel );
}

void cltMarriageManager::PushWeddingMessage( TCHAR* pszName1, TCHAR* pszName2, bool bFuture/* =false */, SI16 siHour/* =0  */)
{
	if ( (NULL == pszName1) || (NULL == pszName2) )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	NTCHARString128 strMessage;

	// �������� �˸��� �ؽ�Ʈ
	if ( false == bFuture )
	{
		strMessage = GetTxtFromMgr( 30070 );

		strMessage.Replace( TEXT("#name1#"), pszName1 );
		strMessage.Replace( TEXT("#name2#"), pszName2 );
	}
	// ����Ǿ��ִ� ���� �˸��� �ؽ�Ʈ
	else
	{
		NTCHARString32 strTime;
		strTime.FormatString( TEXT("%d:00"), siHour );

		strMessage = GetTxtFromMgr( 30071 );

		strMessage.Replace( TEXT("#time#"), strTime );
		strMessage.Replace( TEXT("#name1#"), pszName1 );
		strMessage.Replace( TEXT("#name2#"), pszName2 );
	}

	NTCHARString32 strTitle = GetTxtFromMgr(5482);

	pclserver->PushSpecialNews( strMessage, strTitle, NULL, CAPTIONKIND_NEWS, CAPTIONKIND_NEWSCHAT );
}

BOOL cltMarriageManager::IsWeddingMessage( SI32 siWeddingMessage )
{
	return (m_siWeddingMessage & siWeddingMessage);
}

BOOL cltMarriageManager::CheckAndSetForProgressMessage( SI16 siMinute )
{
	if ( (5 <= siMinute) && (15 > siMinute) && (FALSE == IsWeddingMessage(MARRIAGE_WEDDING_MESSAGE_05)) )
	{
		m_siWeddingMessage |= MARRIAGE_WEDDING_MESSAGE_05;
		return TRUE;
	}
	else if ( (15 <= siMinute) && (25 > siMinute) && (FALSE == IsWeddingMessage(MARRIAGE_WEDDING_MESSAGE_15)) )
	{
		m_siWeddingMessage |= MARRIAGE_WEDDING_MESSAGE_15;
		return TRUE;
	}
	else if ( (25 <= siMinute) && (30 > siMinute) && (FALSE == IsWeddingMessage(MARRIAGE_WEDDING_MESSAGE_25)) )
	{
		m_siWeddingMessage |= MARRIAGE_WEDDING_MESSAGE_25;
		return TRUE;
	}

	return FALSE;

}

BOOL cltMarriageManager::CheckAndSetForFutureMessage( SI16 siMinute )
{
	if ( (35 <= siMinute) && (45 > siMinute) && (FALSE == IsWeddingMessage(MARRIAGE_WEDDING_MESSAGE_35)) )
	{
		m_siWeddingMessage |= MARRIAGE_WEDDING_MESSAGE_35;
		return TRUE;
	}
	else if ( (45 <= siMinute) && (55 > siMinute) && (FALSE == IsWeddingMessage(MARRIAGE_WEDDING_MESSAGE_45)) )
	{
		m_siWeddingMessage |= MARRIAGE_WEDDING_MESSAGE_45;
		return TRUE;
	}
	else if ( (55 <= siMinute) && (60 > siMinute) && (FALSE == IsWeddingMessage(MARRIAGE_WEDDING_MESSAGE_55)) )
	{
		m_siWeddingMessage |= MARRIAGE_WEDDING_MESSAGE_55;
		return TRUE;
	}

	return FALSE;
}

BOOL cltMarriageManager::IsInHearMapWeddingPersons( IN SI32 siMate1_PersonID, IN SI32 siMate2_PersonID, OUT SI32* psiMate1CharUnique, OUT SI32* psiMate2CharUnique )
{
	SI32			siMate1_CharID	= pclClient->pclCM->GetIDFromPersonID(siMate1_PersonID);
	cltCharServer*	pclMate1Char	= pclClient->pclCM->GetCharServer( siMate1_CharID );
	if ( NULL == pclMate1Char )
	{
		return FALSE;
	}

	if ( MAPINDEX_WEDDINGHALL != pclMate1Char->GetMapIndex() )
	{
		return FALSE;
	}

	SI32			siMate2_CharID	= pclClient->pclCM->GetIDFromPersonID(siMate2_PersonID);
	cltCharServer*	pclMate2Char	= pclClient->pclCM->GetCharServer( siMate2_CharID );
	if ( NULL == pclMate2Char )
	{
		return FALSE;
	}

	if ( MAPINDEX_WEDDINGHALL != pclMate2Char->GetMapIndex() )
	{
		return FALSE;
	}

	if ( (NULL != psiMate1CharUnique) && (NULL != psiMate2CharUnique) )
	{
		*psiMate1CharUnique = pclMate1Char->GetCharUnique();
		*psiMate2CharUnique = pclMate2Char->GetCharUnique();
	}

	return TRUE;
}

BOOL cltMarriageManager::ComeInMarriagePersons( SI32 siMate1_PersonID, SI32 siMate2_PersonID )
{
	// �������ѿ� ����
	cltWarpInfo clWarpInfo( 1, MAPINDEX_WEDDINGHALL, true, false, MARRIAGE_WEDDING_COMEIN_MARRIAGE_PERSON_X, MARRIAGE_WEDDING_COMEIN_MARRIAGE_PERSON_Y, -1,-1 );

	SI32			siMate1_CharID	= pclClient->pclCM->GetIDFromPersonID(siMate1_PersonID);
	cltCharServer*	pclMate1Char	= pclClient->pclCM->GetCharServer( siMate1_CharID );
	if ( NULL == pclMate1Char )
	{
		return FALSE;
	}

	if ( MAPINDEX_WEDDINGHALL != pclMate1Char->GetMapIndex() )
	{
		pclMate1Char->SetWarpInfo( &clWarpInfo, 3102 );
		pclMate1Char->Warp();
	}

	SI32			siMate2_CharID	= pclClient->pclCM->GetIDFromPersonID(siMate2_PersonID);
	cltCharServer*	pclMate2Char	= pclClient->pclCM->GetCharServer( siMate2_CharID );
	if ( NULL == pclMate2Char )
	{
		return FALSE;
	}

	if ( MAPINDEX_WEDDINGHALL != pclMate2Char->GetMapIndex() )
	{
		pclMate2Char->SetWarpInfo( &clWarpInfo, 3102 );
		pclMate1Char->Warp();
	}

	if ( (MAPINDEX_WEDDINGHALL != pclMate1Char->GetMapIndex()) || (MAPINDEX_WEDDINGHALL != pclMate2Char->GetMapIndex()) )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL cltMarriageManager::IsComeInMarriagePerson( SI32 siPersonID )
{
	SI32			siCharID	= pclClient->pclCM->GetIDFromPersonID(siPersonID);
	cltCharServer*	pclChar		= pclClient->pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return FALSE;
	}

	if ( MAPINDEX_WEDDINGHALL != pclChar->GetMapIndex() )
	{
		return FALSE;
	}

	SI32 siX1	= 14;
	SI32 siY1	= 10;
	SI32 siX2	= 16; 
	SI32 siY2	= 16;

	SI32 siMyX	= pclChar->GetX();
	SI32 siMyY	= pclChar->GetY();
	if ( (siX1 > siMyX) || (siY1 > siMyY) || (siX2 < siMyX) || (siY2 < siMyY) )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL cltMarriageManager::CreateOfficiatorNPC( void )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return FALSE;
	}

	// �����Ҷ� �̹� �����Ѵٸ� ���� ������
	if ( 0 < m_siOfficiatorID )
	{
		DeleteOfficiatorNPC();
	}

	SI32 siOfficiatorKind = pclClient->GetUniqueFromHash("KIND_OFFICIATOR");
	if ( 0 >= siOfficiatorKind )
	{
		return FALSE;
	}

	SI32 siMapIndex = MAPINDEX_WEDDINGHALL;
	SI32 siMapX		= MARRIAGE_WEDDING_CREATE_NPC_X;
	SI32 siMapY		= MARRIAGE_WEDDING_CREATE_NPC_Y;

	m_siOfficiatorID = pclserver->SetNPCChar(siOfficiatorKind, VILLAGE_NONE, NULL, 1, 1, siMapX, siMapY, siMapIndex, NPCITEMMODE_NONE, NULL );
	if ( 0 < m_siOfficiatorID )
	{
		return TRUE;
	}

	return FALSE;

}

void cltMarriageManager::DeleteOfficiatorNPC()
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	SI32 siOfficiatorKind = pclClient->GetUniqueFromHash("KIND_OFFICIATOR");
	if ( 0 >= siOfficiatorKind )
	{
		return;
	}

	// ��ȿ�� ID�� �ƴҰ��
	if ( false == pclserver->pclCM->IsValidID(m_siOfficiatorID) )
	{
		m_siOfficiatorID = 0;
		return;
	}

	cltCharServer* pclOfficiatorChar = pclserver->pclCM->GetCharServer( m_siOfficiatorID );
	if ( NULL == pclOfficiatorChar )
	{
		m_siOfficiatorID = 0;
		return;
	}

	if ( pclOfficiatorChar->GetKind() != siOfficiatorKind )
	{
		m_siOfficiatorID = 0;
		return;
	}

	pclOfficiatorChar->DeleteInCell();

	if ( TRUE == pclserver->pclCM->DeleteChar(m_siOfficiatorID)  )
	{
		m_siOfficiatorID = 0;
	}
}

void cltMarriageManager::WeddingProcess( cltWeddingReserveUnit* pclUnit )
{
	if ( MARRIAGE_WEDDING_STATUS_NONE == m_siWeddingStatus )
	{
		return;
	}

	if ( NULL == pclUnit )
	{
		return;
	}

	if ( FALSE == pclUnit->IsReserved() )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	SI32 siMate1CharUnique = 0;
	SI32 siMate2CharUnique = 0;

	BOOL bIsInMap = IsInHearMapWeddingPersons( pclUnit->m_siMate1_PersonID, pclUnit->m_siMate2_PersonID, &siMate1CharUnique, &siMate2CharUnique );
	if ( (MARRIAGE_WEDDING_STATUS_READY		!= m_siWeddingStatus) &&	// �غ��϶��� �ҷ��ü��� �����Ƿ�
		(MARRIAGE_WEDDING_STATUS_END		!= m_siWeddingStatus) &&	// �������� ��¥�� ������ ���̹Ƿ�
		(FALSE == bIsInMap) )
	{
		return;
	}

	switch ( m_siWeddingStatus )
	{
	// ���� �غ�
	case MARRIAGE_WEDDING_STATUS_READY:
		{
			// ������ ġ�� ����� �ҷ��´�
			if ( FALSE == ComeInMarriagePersons(pclUnit->m_siMate1_PersonID, pclUnit->m_siMate2_PersonID) )
			{
				break;
			}

			// NPC�� ����
			if ( FALSE == CreateOfficiatorNPC() )
			{
				break;
			}

			// ������ �����Ѵٴ� �޽���
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_START );

			m_siWeddintProgressCount = 0;
		}
		break;
	// ������ ���۵�
	case MARRIAGE_WEDDING_STATUS_START:
		{
			switch ( m_siWeddintProgressCount )
			{
			case 0:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_READY1, pclUnit->m_szMate1_Name );	break;
			case 3:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_READY2, pclUnit->m_szMate2_Name );	break;
			case 6:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_READY3 );								break;
			case 9:	
				{
					m_siWeddintProgressCount = 0;
					// ���� ����
					ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_COMEIN_WAIT );

					return;
				}
				break;
			}

			m_siWeddintProgressCount++;
			
		}
		break;

	case MARRIAGE_WEDDING_STATUS_COMEIN_WAIT:
		{
			switch ( m_siWeddintProgressCount )
			{
			case 0:		SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_SAY1 );	break;
			case 3:		SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_SAY2 );	break;
			case 6:		SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_SAY3 );	break;
			case 9:		SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_SAY4 );	break;
			case 12:
				{
					m_siWeddintProgressCount = 0;

					ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_MATE1_COMEIN );

					return;
				}
				break;
			}

			m_siWeddintProgressCount++;
		}
		break;

	case MARRIAGE_WEDDING_STATUS_MATE1_COMEIN:
		{
			// 1ĳ���� ����
			SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_COMEIN, pclUnit->m_szMate1_Name );

			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_MATE1_COMEIN_WAIT );
		}
		break;

	case MARRIAGE_WEDDING_STATUS_MATE1_COMEIN_WAIT:
		{
			if ( FALSE == IsComeInMarriagePerson(pclUnit->m_siMate1_PersonID) )
			{
				break;
			}

			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_MATE2_COMEIN );
		}
		break;

	case MARRIAGE_WEDDING_STATUS_MATE2_COMEIN:
		{
			// 1ĳ���� ����
			SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_COMEIN, pclUnit->m_szMate2_Name );

			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_MATE2_COMEIN_WAIT );
		}
		break;

	case MARRIAGE_WEDDING_STATUS_MATE2_COMEIN_WAIT:
		{
			if ( FALSE == IsComeInMarriagePerson(pclUnit->m_siMate2_PersonID) )
			{
				break;
			}

			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_MATE1_QUESTION );

		}
		break;
		
	case MARRIAGE_WEDDING_STATUS_MATE1_QUESTION:
		{
			switch ( m_siWeddintProgressCount )
			{
			case 0:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION1, pclUnit->m_szMate1_Name );	break;
			case 3:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION2 );							break;
			case 6:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION3, pclUnit->m_szMate2_Name );	break;
			case 9:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION4 );							break;
			case 12:
				{
					m_siWeddintProgressCount = 0;

					// �����1���� ���� ����
					pclserver->SendServerResponseCharMsg( 0, SRVAL_WEDDING_MATE1_QUESTION, pclUnit->m_szMate1_Name, pclUnit->m_szMate2_Name, siMate1CharUnique );

					// ���� ����
					ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_MATE1_QUESTION_WAIT );

					return;
				}
				break;
			}

			m_siWeddintProgressCount++;
		}
		break;

	case MARRIAGE_WEDDING_STATUS_MATE2_QUESTION:
		{
			switch ( m_siWeddintProgressCount )
			{
			case 0:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION1, pclUnit->m_szMate2_Name );	break;
			case 3:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION2 );							break;
			case 6:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION3, pclUnit->m_szMate1_Name );	break;
			case 9:	SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION4 );							break;
			case 12:
				{
					m_siWeddintProgressCount = 0;

					// �����2���� ���� ����
					pclserver->SendServerResponseCharMsg( 0, SRVAL_WEDDING_MATE2_QUESTION, pclUnit->m_szMate2_Name, pclUnit->m_szMate1_Name, siMate2CharUnique );

					// ���� ����
					ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_MATE2_QUESTION_WAIT );

					return;
				}
				break;
			}

			m_siWeddintProgressCount++;
		}
		break;

	case MARRIAGE_WEDDING_STATUS_WEDDING_END:
		{
			// ��ȥ�� ���� �Ǿ��ٴ� �޽���
			SendWeddingChatMessage( MARRIAGE_WEDDING_CHAT_MESSAGE_END );

			// ��ȥ ���� ����Ʈ�� �ѷ��ش�
			//cltServerResponseValue clreturn( 0, SRVAL_WEDDING_END, 0, 0 );
			//cltMsg clMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);

			SI16 siFeastKind[4] = {3,5,6,7};

			cltGameMsgResponse_FeastUseEffect sendMsg( siFeastKind, cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE, 30, 30);
			cltMsg clMsg( GAMEMSG_RESPONSE_FEAST_USEEFFECT, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclserver->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg, MAPINDEX_WEDDINGHALL );

			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_GIVEITEM_QUESTION );
		}
		break;

	case MARRIAGE_WEDDING_STATUS_GIVEITEM_QUESTION:
		{
			// ���� ȭ�� ���� �޽����� ������ �ִ� ĳ���͸� �����ؼ� ������
			if ( FALSE == QuestionDropWeddingFlower(pclUnit->m_siMate1_PersonID, pclUnit->m_siMate2_PersonID) )
			{
				break;
			}

			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_GIVEITEM_WAIT );
		}
		break;

	case MARRIAGE_WEDDING_STATUS_GIVEITEM:
		{
			GiveWeddingFlowerItem( pclUnit->m_siMate1_PersonID, pclUnit->m_siMate2_PersonID );
			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_END_READY );
		}
		break;

	case MARRIAGE_WEDDING_STATUS_END:
		{
			// �ַ�NPC ����
			DeleteOfficiatorNPC();

			// �����忡 �ִ� ����� ��� ������
			OutInHearMapAllPerson();

			// ���������� ��� ���� �ʱ�ȭ
			InitForWeddingVariable();

			// ���� ����
			ChangeWeddingStatus( MARRIAGE_WEDDING_STATUS_NONE );
		}
		break;

	default:
		{
			return;
		}
		break;

	}
}

void cltMarriageManager::SendWeddingChatMessage( SI32 siMessageMode, TCHAR* pszName1/* =NULL */, TCHAR* pszName2/* =NULL  */)
{
	if ( MARRIAGE_WEDDING_CHAT_MESSAGE_NONE == siMessageMode )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	cltCharServer* pclOfficiatorChar = pclserver->pclCM->GetCharServer( m_siOfficiatorID );
	if ( NULL == pclOfficiatorChar )
	{
		return;
	}

	TCHAR*			szName = (TCHAR*)pclOfficiatorChar->GetName();

	NTCHARString64	strText1;
	NTCHARString64	strText2;

	switch ( siMessageMode )
	{
	case MARRIAGE_WEDDING_CHAT_MESSAGE_READY1:
		{
			if ( NULL == pszName1 )
			{
				return;
			}

			strText1 = GetTxtFromMgr( 30072 );

			strText1.Replace( TEXT("#name1#"), pszName1 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_READY2:
		{
			if ( NULL == pszName1 )
			{
				return;
			}

			strText1 = GetTxtFromMgr( 30147 );

			strText1.Replace( TEXT("#name2#"), pszName1 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_READY3:
		{
			strText1 = GetTxtFromMgr( 30148 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_SAY1:
		{
			strText1 = GetTxtFromMgr( 30073 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_SAY2:
		{
			strText1 = GetTxtFromMgr( 30074 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_SAY3:
		{
			strText1 = GetTxtFromMgr( 30094 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_SAY4:
		{
			strText1 = GetTxtFromMgr( 30095 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_COMEIN:
		{
			if ( NULL == pszName1 )
			{
				return;
			}

			strText1 = GetTxtFromMgr(30093);

			strText1.Replace( TEXT("#name#"), pszName1 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION1:
		{
			if ( NULL == pszName1 )
			{
				return;
			}

			strText1 = GetTxtFromMgr( 30075 );

			strText1.Replace( TEXT("#name1#"), pszName1 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION2:
		{
			strText1 = GetTxtFromMgr( 30092 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION3:
		{
			if ( NULL == pszName1 )
			{
				return;
			}

			strText1 = GetTxtFromMgr( 30096 );

			strText1.Replace( TEXT("#name2#"), pszName1 );
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION4:
		{
			strText1 = GetTxtFromMgr( 30097 );		
		}
		break;

	case MARRIAGE_WEDDING_CHAT_MESSAGE_END:
		{
			strText1 = GetTxtFromMgr( 30076 );
		}
		break;
	}

	// ä�� ��Ŷ ����
	cltGameMsgResponse_Chat clChat( pclOfficiatorChar->GetCharUnique(), CHATMODE_NORMAL, szName, strText1);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHAT, clChat.siDataSize, (BYTE*)&clChat);

	// ���� �ʿ� �ִ� ��� ĳ���� �鿡�� �޽����� ������
	pclserver->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg, MAPINDEX_WEDDINGHALL );

	// 2��° �ؽ�Ʈ�� ������ �������� �� ��Ŷ �����ش�
	if ( FALSE == strText2.IsEmpty() )
	{
		cltGameMsgResponse_Chat clChat2( pclOfficiatorChar->GetCharUnique(), CHATMODE_NORMAL, szName, strText2);
		cltMsg clMsg2(GAMEMSG_RESPONSE_CHAT, clChat2.siDataSize, (BYTE*)&clChat2);

		// ���� �ʿ� �ִ� ��� ĳ���� �鿡�� �޽����� ������
		pclserver->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg2, MAPINDEX_WEDDINGHALL );

	}

}

void cltMarriageManager::ChangeWeddingStatus( SI32 siChangeWeddingStatus )
{
	if ( (MARRIAGE_WEDDING_STATUS_NONE > siChangeWeddingStatus) || (MARRIAGE_WEDDING_STATUS_MAX <= siChangeWeddingStatus) )
	{
		return;
	}

	m_siWeddingStatus = siChangeWeddingStatus;
}

void cltMarriageManager::OutInHearMapAllPerson( void )
{
	// �����忡 �ִ� ��� ������� ��������
	SI32			siId	= 0;
	SI32			siIndex	= 0;

	cltCharServer*	pclchar	= NULL;

	cltWarpInfo		clWarpInfo( 1, MAPINDEX_MAINFIELD, true, false, 156, 363, -1,-1 );

	while ( siId = pclClient->pclCM->GetCharOrder(siIndex) )
	{
		siIndex++;

		if ( !IsPC(siId) )
		{
			continue;
		}

		pclchar = pclClient->pclCM->GetCharServer( siId );
		if ( NULL == pclchar )
		{
			continue;
		}

		if ( MAPINDEX_WEDDINGHALL != pclchar->GetMapIndex() )
		{
			continue;
		}

		pclchar->SetWarpInfo( &clWarpInfo, 3101 );
		pclchar->Warp();
	}

}

BOOL cltMarriageManager::QuestionDropWeddingFlower( SI32 siMate1_PersonID, SI32 siMate2_PersonID )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return FALSE;
	}

	// ó�� ĳ���Ͱ� �����ϰ��(�� ĳ���Ͱ� ������ ��� �����ڿ��� �����Ƿ� ó���� �ٷ� ������ �ȴ�)
	SI32			siMate1CharID	= pclserver->pclCM->GetIDFromPersonID( siMate1_PersonID );
	cltCharServer*	pclMate1Char	= pclserver->pclCM->GetCharServer( siMate1CharID );
	if ( NULL == pclMate1Char )
	{
		return FALSE;
	}

	if ( (KIND_HEROINE3 == pclMate1Char->GetKind()) || (KIND_HEROINE4 == pclMate1Char->GetKind()) )
	{
		pclserver->SendServerResponseMsg( 0, SRVAL_WEDDING_GIVEITEM_QUESTION, 0, 0, pclMate1Char->GetCharUnique() );
		return TRUE;
	}

	// �ι�° ĳ���Ͱ� �����ϰ��
	SI32			siMate2CharID	= pclserver->pclCM->GetIDFromPersonID( siMate2_PersonID );
	cltCharServer*	pclMate2Char	= pclserver->pclCM->GetCharServer( siMate2CharID );
	if ( NULL == pclMate2Char )
	{
		return FALSE;
	}

	if ( (KIND_HEROINE3 == pclMate2Char->GetKind()) || (KIND_HEROINE4 == pclMate2Char->GetKind()) )
	{
		pclserver->SendServerResponseMsg( 0, SRVAL_WEDDING_GIVEITEM_QUESTION, 0, 0, pclMate2Char->GetCharUnique() );
		return TRUE;
	}

	// �̵� ���� �ƴϸ� �׳� ó�� ĳ����
	pclserver->SendServerResponseMsg( 0, SRVAL_WEDDING_GIVEITEM_QUESTION, 0, 0, pclMate1Char->GetCharUnique() );

	return TRUE;
}

void cltMarriageManager::GiveWeddingFlowerItem( SI32 siMate1_PersonID, SI32 siMate2_PersonID )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	const SI32 Const_FlowerItem_Unique		= 23497;
	const SI32 Const_FlowerItem_Num			= 1;

	const SI32 Const_FlowerItem_Max_Char	= 20;
	const SI16 Const_FlowerItem_UseDate		= 3;
	

	// ���� �ʿ� �ִ� ����� �ִ� 20���� �߷����� �׻���鿡�� �ش�
	SI32			siGiveCharID[Const_FlowerItem_Max_Char]	= {0,};
	SI32			siGiveCharCount	= 0;

	SI32			siId	= 0;
	SI32			siIndex	= 0;

	cltCharServer*	pclchar	= NULL;

	// ĳ���� �̸�
	NTCHARString32	strName;

	// ����Ȧ�� �ִ� �ϰ� ĳ���͵��� �����´�
	while ( siId = pclClient->pclCM->GetCharOrder(siIndex) )
	{
		siIndex++;

		if ( !IsPC(siId) )
		{
			continue;
		}

		pclchar = pclClient->pclCM->GetCharServer( siId );
		if ( NULL == pclchar )
		{
			continue;
		}

		if ( MAPINDEX_WEDDINGHALL != pclchar->GetMapIndex() )
		{
			continue;
		}

		if ( (pclchar->pclCI->GetPersonID() == siMate1_PersonID) || (pclchar->pclCI->GetPersonID() == siMate2_PersonID) )
		{
			continue;
		}

		siGiveCharID[siGiveCharCount++] = siId;
		if ( Const_FlowerItem_Max_Char <= siGiveCharCount )
		{
			break;
		}
	}

	BOOL bGiveItem = FALSE;

	// �ϰ� ĳ������ �����ϰ� 1������ �������� �ش�
	if ( 0 < siGiveCharCount )
	{
		SI32 siRandNumber	= rand() % siGiveCharCount;
		SI32 siRealIndex	= 0;

		for ( SI32 siIndex=0; siIndex<siGiveCharCount; siIndex++ )
		{
			siRealIndex = (siIndex + siRandNumber) % siGiveCharCount;

			if ( Const_FlowerItem_Max_Char <= siRealIndex )
			{
				continue;
			}

			pclchar = pclClient->pclCM->GetCharServer( siGiveCharID[siRealIndex] );
			if ( NULL == pclchar )
			{
				continue;
			}

			if ( GIVEITEM_RESULT_SUCCESS == pclchar->GiveItem(Const_FlowerItem_Unique, Const_FlowerItem_Num, INPUTITEMPERSON_OPTION_WEDDINGHALL_FLOWER, Const_FlowerItem_UseDate, GIVEITEM_SEAL_MODE_CANCEL) )
			{
				strName		= (TCHAR*)pclchar->GetName();
				bGiveItem	= TRUE;
				break;
			}
		}
	}

	// ó�� ĳ���Ͱ� �����ϰ��(�� ĳ���Ͱ� ������ ��� �����ڿ��� �����Ƿ� ó���� �ٷ� ������ �ȴ�)
	SI32			siMate1CharID	= pclserver->pclCM->GetIDFromPersonID( siMate1_PersonID );
	cltCharServer*	pclMate1Char	= pclserver->pclCM->GetCharServer( siMate1CharID );

	// �ϰ��߿� ���� ����� ���ٸ� ĳ���͸� �������� �ش�
	if ( (FALSE == bGiveItem) && (pclMate1Char) )
	{
		if ( (KIND_HEROINE3 == pclMate1Char->GetKind()) || (KIND_HEROINE4 == pclMate1Char->GetKind()) )
		{
			if ( GIVEITEM_RESULT_SUCCESS == pclMate1Char->GiveItem(Const_FlowerItem_Unique, Const_FlowerItem_Num, INPUTITEMPERSON_OPTION_WEDDINGHALL_FLOWER, Const_FlowerItem_UseDate, GIVEITEM_SEAL_MODE_CANCEL) )
			{
				strName		= (TCHAR*)pclMate1Char->GetName();
				bGiveItem	= TRUE;
			}
		}
	}

	// �ι�° ĳ���Ͱ� �����ϰ��
	SI32			siMate2CharID	= pclserver->pclCM->GetIDFromPersonID( siMate2_PersonID );
	cltCharServer*	pclMate2Char	= pclserver->pclCM->GetCharServer( siMate2CharID );

	if ( (FALSE == bGiveItem) && (pclMate2Char) )
	{
		if ( (KIND_HEROINE3 == pclMate2Char->GetKind()) || (KIND_HEROINE4 == pclMate2Char->GetKind()) )
		{
			if ( GIVEITEM_RESULT_SUCCESS == pclMate2Char->GiveItem(Const_FlowerItem_Unique, Const_FlowerItem_Num, INPUTITEMPERSON_OPTION_WEDDINGHALL_FLOWER, Const_FlowerItem_UseDate, GIVEITEM_SEAL_MODE_CANCEL) )
			{
				strName		= (TCHAR*)pclMate2Char->GetName();
				bGiveItem	= TRUE;
			}
		}
	}

	// �̵� ���� �ƴϸ� �׳� ó�� ĳ����
	if ( (FALSE == bGiveItem) && (pclMate1Char) )
	{
		if ( GIVEITEM_RESULT_SUCCESS == pclMate1Char->GiveItem(Const_FlowerItem_Unique, Const_FlowerItem_Num, INPUTITEMPERSON_OPTION_WEDDINGHALL_FLOWER, Const_FlowerItem_UseDate, GIVEITEM_SEAL_MODE_CANCEL) )
		{
			strName		= (TCHAR*)pclMate1Char->GetName();
			bGiveItem	= TRUE;
		}
	}

	if ( TRUE == bGiveItem )
	{
		cltServerResponseCharValue clInfo( 0, SRVAL_WEDDING_GIVEITEM, strName, TEXT("") );
		cltMsg clMsg( GAMEMSG_RESPONSE_CHARSERVERRTN, sizeof(cltServerResponseCharValue), (BYTE*)&clInfo );

		pclserver->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg, MAPINDEX_WEDDINGHALL );
	}
}
