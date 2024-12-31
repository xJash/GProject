
#include "..\..\CommonLogic\CommonLogic.h"
#include "SystemNPC.h"
#include "..\Char\KindInfo\kindinfo.h"

//--------------------------------------
// Common
//------------------------------------- 
#include "..\Quest\Quest.h"

extern cltCommonLogic* pclClient;

cltSystemNPC::cltSystemNPC()
{
	Init();
}

cltSystemNPC::cltSystemNPC( cltSystemNPC* pclSystemNPC )
{
	if ( NULL == pclSystemNPC )
	{
		Init();
		return;
	}

	memcpy( this, pclSystemNPC, sizeof(cltSystemNPC) );
}

cltSystemNPC::~cltSystemNPC()
{

}


void cltSystemNPC::Init()
{
	ZeroMemory( this, sizeof(cltSystemNPC) );
}

void cltSystemNPC::Set( cltSystemNPC* pclSystemNPC )
{
	if ( NULL == pclSystemNPC )
	{
		Init();
		return;
	}

	memcpy( this, pclSystemNPC, sizeof(cltSystemNPC) );
}

void cltSystemNPC::Set( SI32 siKind, SI16 siQuestType, SI32 siExplainNum, SI32 siLocationNum, SI16 siCategory, SI32 siSimpleExplainNum, SI16 siShowNotice, SI32 siNoticeExplainNum, SI32 siNoticeLocationNum, SI16 siMapIndex, SI16 siImageDisplayMode )
{
	m_siKind				= siKind;
	m_siQuestType			= siQuestType;
	m_siExplainNum			= siExplainNum;
	m_siLocationNum			= siLocationNum;
	m_siCategory			= siCategory;
	m_siSimpleExplainNum	= siSimpleExplainNum;
	m_siShowNotice			= siShowNotice;
	m_siNoticeExplainNum	= siNoticeExplainNum;
	m_siNoticeLocationNum	= siNoticeLocationNum;
	m_siMapIndex			= siMapIndex;
	m_siImageDisplayMode	= siImageDisplayMode;

}

bool cltSystemNPC::GetExplainText( TCHAR* pszBuffer, SI32 siBufferSize )
{
	if ( (NULL == pszBuffer) || (0 >= siBufferSize) )
	{
		return false;
	}


	bool	bBufCopy		= false; // �Ʒ��ִ� ���ۿ��� �����Ұ����� �ƴϸ� �׳� �ؽ�Ʈ �޴������� �����Ұ�����
	TCHAR	szTempBuf[512]	= { '\0', };


	if ( pclClient->GetUniqueFromHash(TEXT( "KIND_HONGILDONG" )) == m_siKind 
		|| pclClient->GetUniqueFromHash(TEXT( "KIND_WAITINGWOMAN" )) == m_siKind 
		|| pclClient->GetUniqueFromHash(TEXT( "KIND_CHINAMERCHANT" )) == m_siKind 
		|| pclClient->GetUniqueFromHash(TEXT( "KIND_DAILYQUEST" )) == m_siKind 
		
	)
	{
		TCHAR* pszText = GetTxtFromMgr( m_siExplainNum );

		StringCchPrintf( szTempBuf, 512, pszText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%' );

		bBufCopy = true;
	}
	else if ( pclClient->GetUniqueFromHash(TEXT( "KIND_WENNYOLDMAN" )) == m_siKind )
	{
		TCHAR	szTempBuf2[128]	= { '\0', };
		TCHAR*	pszText			= GetTxtFromMgr( m_siExplainNum );

		g_JYLibFunction.SetNumUnit( VILLAGE_PROFIT_FOR_WENNYOLDMAN, szTempBuf2, 128 );
		StringCchPrintf( szTempBuf, 512, pszText, szTempBuf2 );

		bBufCopy = true;
	}
	else if ( pclClient->GetUniqueFromHash(TEXT( "KIND_INVESTMENT" )) == m_siKind )
	{
		TCHAR	szTempBuf2[128]	= { '\0', };
		TCHAR*	pszText			= GetTxtFromMgr( m_siExplainNum );

		g_JYLibFunction.SetNumUnit( VILLAGE_PROFIT_FOR_INVESTMENT, szTempBuf2, 128 );
		StringCchPrintf( szTempBuf, 512, pszText, szTempBuf2 );

		bBufCopy = true;
	}


	if ( true == bBufCopy )
	{
		StringCchCopy( pszBuffer, siBufferSize, szTempBuf );
	}
	else
	{
		StringCchCopy( pszBuffer, siBufferSize, GetTxtFromMgr(m_siExplainNum) );
	}

	return true;
}

//==============================================================================================================================================
// ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 ��輱 
//==============================================================================================================================================

cltSystemNPCManager::cltSystemNPCManager()
{
	Init();

	LoadSystemNPCInfo();
}

cltSystemNPCManager::~cltSystemNPCManager()
{

}

void cltSystemNPCManager::Init()
{
	ZeroMemory( this, sizeof(cltSystemNPCManager) );
}

bool cltSystemNPCManager::LoadSystemNPCInfo()
{
	NDataLoader		clDataLoader;
	BOOL			bLoadFile	= false;
	NTCHARString64	strFile("Data\\SystemNPCInfo.txt");


	//KHY - 0809 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = clDataLoader.LoadDataFromCryptFile( strFile );
	}
	else
	{
		bLoadFile = clDataLoader.LoadDataFromFile( strFile );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("LoadSystemNPCInfo()"), TEXT("LoadError:[%s]"), (TCHAR*)strFile);
		return false;
	}	

	TCHAR	szKind[128]			= { '\0', };
	TCHAR	szQuestType[128]	= { '\0', };
	SI32	siExplainNum		= 0;
	SI32	siLocationNum		= 0;
	TCHAR	szCategory[64]		= { '\0', };
	SI32	siSimpleExplainNum	= 0;
	SI32	siShowNotice		= 0;
	SI32	siNoticeExplainNum	= 0;
	SI32	siNoticeLocationNum	= 0;
	SI32	siMapIndex			= 0;
	SI32	siImageDisplayMode	= 0;

	NDataTypeInfo pDataTypeInfo[] = 
	{
		NDATA_MBSTRING,	szKind,					128,
		NDATA_MBSTRING,	szQuestType,			128,
		NDATA_INT32,	&siExplainNum,			4,
		NDATA_INT32,	&siLocationNum,			4,
		NDATA_MBSTRING,	szCategory,				64,
		NDATA_INT32,	&siSimpleExplainNum,	4,
		NDATA_INT32,	&siShowNotice,			4,
		NDATA_INT32,	&siNoticeExplainNum,	4,
		NDATA_INT32,	&siNoticeLocationNum,	4,
		NDATA_INT32,	&siMapIndex,			4,
		NDATA_INT32,	&siImageDisplayMode,	4,
		0,0,0
	};

	clDataLoader.RegDataType(pDataTypeInfo);

	while( !clDataLoader.IsEndOfData() ) 
	{
		if( clDataLoader.ReadData())
		{
			cltSystemNPC clSystemNPC;

			clSystemNPC.m_siKind				= pclClient->GetUniqueFromHash( szKind );
			clSystemNPC.m_siQuestType			= pclClient->pclQuestManager->ConvertQuestTypeTextToNum( szQuestType );
			clSystemNPC.m_siExplainNum			= siExplainNum;
			clSystemNPC.m_siLocationNum			= siLocationNum;
			clSystemNPC.m_siCategory			= ConvertCategoryTextToNum( szCategory );
			clSystemNPC.m_siSimpleExplainNum	= siSimpleExplainNum;
			clSystemNPC.m_siShowNotice			= siShowNotice;
			clSystemNPC.m_siNoticeExplainNum	= siNoticeExplainNum;
			clSystemNPC.m_siNoticeLocationNum	= siNoticeLocationNum;
			clSystemNPC.m_siMapIndex			= siMapIndex;
			clSystemNPC.m_siImageDisplayMode	= siImageDisplayMode;

			Add( &clSystemNPC );
		}
	}


	return true;
}

bool cltSystemNPCManager::Add( cltSystemNPC* pclSystemNPC )
{
	for ( SI32 siIndex=0; siIndex<MAX_SYSTEM_NPC_NUMBER; ++siIndex )
	{
		if ( 0 == clSystemNPC[siIndex].m_siKind )
		{
			clSystemNPC[ siIndex ].Set( pclSystemNPC );
			return true;
		}
	}

#ifdef _DEBUG
	NTCHARString64	strCaption( TEXT("��������") );
	NTCHARString256 strText( TEXT("MAX_SYSTEM_NPC_NUMBER ������ �ʰ��Ͽ����ϴ�") );

	MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
#endif

	return false;
}

SI16 cltSystemNPCManager::ConvertCategoryTextToNum( TCHAR* pszCategory )
{
	if ( NULL == pszCategory )
	{
		return CATEGORY_NONE;
	}

	if     ( _tcscmp(pszCategory, "CATEGORY_NONE")			== 0 )	return CATEGORY_NONE;
	else if( _tcscmp(pszCategory, "CATEGORY_BEGINNER")		== 0 )	return CATEGORY_BEGINNER;
	else if( _tcscmp(pszCategory, "CATEGORY_MANUFACTURE")	== 0 )	return CATEGORY_MANUFACTURE;
	else if( _tcscmp(pszCategory, "CATEGORY_WORLD")			== 0 )	return CATEGORY_WORLD;

#ifdef _DEBUG
	else
	{
		NTCHARString256 strText( pszCategory );
		NTCHARString64	strCaption( TEXT("Error SystemNPCInfo.txt") );

		strText += TEXT(" Type Not Found");

		MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
	}
#endif

	return CATEGORY_NONE;

}

bool cltSystemNPCManager::GetSystemNPCListFormCategory( SI16 siCategory, cltSystemNPC* pclSystemNPCList, SI32 siListCount )
{
	if ( (CATEGORY_NONE > siCategory) || (CATEGORY_MAX <= siCategory) )
	{
		return false;
	}

	if ( (NULL == pclSystemNPCList) || (0 >= siListCount) )
	{
		return false;
	}


	SI32 siCount = 0;

	for ( SI32 siIndex=0; siIndex<MAX_SYSTEM_NPC_NUMBER; ++siIndex )
	{
		if ( siCategory == clSystemNPC[siIndex].m_siCategory )
		{
			pclSystemNPCList[ siCount++ ].Set( &clSystemNPC[siIndex] );
		}

		if ( siListCount <= siCount )
		{
			break;
		}
	}

	return true;
}

bool cltSystemNPCManager::GetSystemNPCListForShowNotice( OUT cltSystemNPC* pclSystemNPCList, IN SI32 siListCount )
{
	if ( (NULL == pclSystemNPCList) || (0 >= siListCount) )
	{
		return false;
	}

	SI32 siCount = 0;

	for ( SI32 siIndex=0; siIndex<MAX_SYSTEM_NPC_NUMBER; ++siIndex )
	{
		if ( 0 < clSystemNPC[siIndex].m_siShowNotice )
		{
			pclSystemNPCList[ siCount++ ].Set( &clSystemNPC[siIndex] );
		}

		if ( siListCount <= siCount )
		{
			break;
		}
	}

	return true;

}

bool cltSystemNPCManager::FindSystemNPCInfoFromNPCKind( IN SI32 siKind, OUT cltSystemNPC* pclSystemNPC )
{
	if ( (0 >= siKind) || (NULL == pclSystemNPC) )
	{
		return false;
	}

	for ( SI32 siIndex=0; siIndex< MAX_SYSTEM_NPC_NUMBER; ++siIndex )
	{
		if ( clSystemNPC[ siIndex ].m_siKind == siKind )
		{
			pclSystemNPC->Set( &clSystemNPC[ siIndex ] );
			return true;
		}
	}

	return false;

}

bool cltSystemNPCManager::FindSystemNPCInfoFromQuestType( IN SI32 siQuestType, OUT cltSystemNPC* pclSystemNPC )
{
	if ( (QUEST_TYPE_NONE >= siQuestType) || (MAX_QUEST_TYPE <= siQuestType) )
	{
		return false;
	}

	if ( NULL == pclSystemNPC )
	{
		return false;
	}


	for ( SI32 siIndex=0; siIndex< MAX_SYSTEM_NPC_NUMBER; ++siIndex )
	{
		if ( clSystemNPC[ siIndex ].m_siQuestType == siQuestType )
		{
			pclSystemNPC->Set( &clSystemNPC[ siIndex ] );
			return true;
		}
	}

	return false;

}
/*
cltSystemNPCManager::cltSystemNPCManager()
{
	TCHAR buffer[1024];

	TCHAR* pText = GetTxtFromMgr(2955);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_WAITINGMAN") ),	QUEST_TYPE_BEGINNER2,			pText);
	pText = GetTxtFromMgr(2956);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_JANGGUMI")),		QUEST_TYPE_BASIC1,				pText);
	pText = GetTxtFromMgr(2961);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_ROYALGUARD") ),	QUEST_TYPE_BATTLE1,				pText);
	pText = GetTxtFromMgr(2957);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BONG")),			QUEST_TYPE_MAKESWORD1,			pText);
	pText = GetTxtFromMgr(2958);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_DOCTOR")),			QUEST_TYPE_MAKEHEAL1,			pText);
	pText = GetTxtFromMgr(2959);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_YONGPAL")),		QUEST_TYPE_MAKEHELMET1,			pText);
	pText = GetTxtFromMgr(2960);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BONGDAL")),		QUEST_TYPE_MAKEBOW1,			pText);
	pText = GetTxtFromMgr(2962);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BONGTAGI")),		QUEST_TYPE_MAKESPEAR1,			pText);
	pText = GetTxtFromMgr(2963);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_YONGCHUNI")),		QUEST_TYPE_MAKEARMOUR1,			pText);
	pText = GetTxtFromMgr(2964);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BONGSUNI")),		QUEST_TYPE_MAKEAX1,				pText);
	pText = GetTxtFromMgr(2965);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BONGSAMI")),		QUEST_TYPE_MAKEGUN1,			pText);
	pText = GetTxtFromMgr(2966);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_SEOSANSAINT")),	QUEST_TYPE_MAKESTAFF1,			pText);
	pText = GetTxtFromMgr(2967);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_YONGTAGI")),		QUEST_TYPE_MAKEBELT1,			pText);
	pText = GetTxtFromMgr(2968);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_YONGSAMI")),		QUEST_TYPE_MAKESHOES1,			pText);
	pText = GetTxtFromMgr(2969);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_JANGGILSAN")),		QUEST_TYPE_BATTLE2,				pText);
	pText = GetTxtFromMgr(2970);		// �念��
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_JANGYOUNGSIL")),	QUEST_TYPE_MAKEBEGINNER1,		pText);

	pText = GetTxtFromMgr(2969);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC1")),	QUEST_TYPE_HAPPYBEAN,			pText);//���Ǻ� ����Ʈ [2007.08.22 �ռ���]

	// ����Ʈ �߰�
	pText = GetTxtFromMgr(7617);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_SOPHIA")),			QUEST_TYPE_HUNTINGGROUND01,		pText);
	pText = GetTxtFromMgr(7618);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_SPARKY")),			QUEST_TYPE_HUNTINGGROUND02,		pText);
	pText = GetTxtFromMgr(2969);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_QUESTETC1")),		QUEST_TYPE_HUNTINGETC01,		pText);
	pText = GetTxtFromMgr(7650);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERIEL")),			QUEST_TYPE_HUNTINGGROUND03,		pText);
	pText = GetTxtFromMgr(7672);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BRAI")),			QUEST_TYPE_HUNTINGGROUND04,		pText);
	pText = GetTxtFromMgr(7723);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BELITA")),			QUEST_TYPE_HUNTINGGROUND05,		pText);
	pText = GetTxtFromMgr(7728);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_HINEAS")),			QUEST_TYPE_HUNTINGGROUND06,		pText);
	pText = GetTxtFromMgr(7733);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_KELAN")),			QUEST_TYPE_HUNTINGGROUND07,		pText);
	pText = GetTxtFromMgr(7862);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_JEFFREY")),		QUEST_TYPE_HUNTINGGROUND08,		pText);
	pText = GetTxtFromMgr(7947);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_MOLDA")),			QUEST_TYPE_HUNTINGGROUND09,		pText);
	pText = GetTxtFromMgr(7963);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_SEBRINO")),		QUEST_TYPE_HUNTINGGROUND10,		pText);
	pText = GetTxtFromMgr(7967);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_ELIANA")),			QUEST_TYPE_HUNTINGGROUND11,		pText);
	pText = GetTxtFromMgr(8030);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_FREESIA")),		QUEST_TYPE_MAKEFOOD1,			pText);
	pText = GetTxtFromMgr(8159);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_AIRIN")),			QUEST_TYPE_BEGINNER1,			pText);
	pText = GetTxtFromMgr(8354);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_DAILYQUEST2")),	QUEST_TYPE_DAILYQUEST2,			pText);
	pText = GetTxtFromMgr(8355);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_DAILYQUEST3")),	QUEST_TYPE_DAILYQUEST3,			pText);
	
	//���Ǻ�����Ʈ[2007.08.22 �ռ���]
	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	if( pclClient->IsCountrySwitch( Switch_HappyBeanQuest ) )
	{
		pText = GetTxtFromMgr(7156);
		Add(pclClient->GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC1")),	QUEST_TYPE_HAPPYBEAN,		pText);//���Ǻ� ����Ʈ [2007.08.22 �ռ���]
		pText = GetTxtFromMgr(7156);
		Add(pclClient->GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC2")),	QUEST_TYPE_HAPPYBEAN,		pText);//���Ǻ� ����Ʈ [2007.08.22 �ռ���]
		pText = GetTxtFromMgr(7156);
		Add(pclClient->GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC3")),	QUEST_TYPE_HAPPYBEAN,		pText);//���Ǻ� ����Ʈ [2007.08.22 �ռ���]
	}

	//pText = GetTxtFromMgr(5236);
	//// ����
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_WANGCHO")),		-1,						buffer);

	//pText = GetTxtFromMgr(5237);
	//// ���λ�
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_BOBUSANG")),		-1,						buffer);

	pText = GetTxtFromMgr(5238);
	// ȫ�浿
	StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_HONGILDONG")),		-1,						buffer);

	pText = GetTxtFromMgr(2971);
	// ������ 
	StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_WAITINGWOMAN")),		-1,						buffer);

	pText = GetTxtFromMgr(2972);
	// ���󱳿����� 
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_CHINATRADER")),		-1,						buffer);

	pText = GetTxtFromMgr(2973);
	// �ֱ������� 
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_JAPANTRADER")),		-1,						buffer);

	pText = GetTxtFromMgr(2974);
	// ���þƱ������� 
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_RUSSIATRADER")),		-1,						buffer);

	//cyj �ջ�� �߰�
	pText = GetTxtFromMgr(2976);
	// �ջ��
	sprintf(buffer, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_BATTLEZONE")),		-1,						buffer);

	pText = GetTxtFromMgr(2977);
	// ������� 
	StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_CHINAMERCHANT") ),		-1,						buffer);

	pText = GetTxtFromMgr(2978);
	// ��ȯ������
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_SUMMONMERCHANT") ),		-1,						buffer);

	//pText = GetTxtFromMgr(2979);
	//// Ȱ���� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTBOW")),		-1,						buffer);

	pText = GetTxtFromMgr(2980);
	// ������ 
	StringCchPrintf(buffer, 1024, pText );
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTHORSE")),		-1,						buffer);

	//pText = GetTxtFromMgr(2981);
	//// ���Ļ��� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTFOOD")),		-1,						buffer);

	//pText = GetTxtFromMgr(2982);
	//// �Ź߻��� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTSHOES")),		-1,						buffer);

	//pText = GetTxtFromMgr(2983);
	//// ������ 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTBELT")),		-1,						buffer);

	//pText = GetTxtFromMgr(2984);
	//// ����� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTHEAL")),		-1,						buffer);

	pText = GetTxtFromMgr(2985);
	// ��ǰ���� 
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTPORTER")),	-1,						buffer);

	//pText = GetTxtFromMgr(2986);
	//// ö������ 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTHARDWARE")),	-1,						buffer);

	//pText = GetTxtFromMgr(2987);
	//// �������� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTRING")),		-1,						buffer);

	//pText = GetTxtFromMgr(2988);
	//// �Ƿ����� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTCLOTHES")),	-1,						buffer);

	//pText = GetTxtFromMgr(2989);
	//// ���ڻ��� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTHAT")),		-1,						buffer);

	//pText = GetTxtFromMgr(2990);
	//// ����̻��� 
	//StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_MERCHANTNECKLACE")),	-1,						buffer);

	pText = GetTxtFromMgr(2991);
	// �𺴰� 
	StringCchPrintf(buffer, 1024, pText, VILLAGE_PROFIT_RATE_FOR_MERCHANT, '%');
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_DAILYQUEST")),		-1,						buffer);

	//pText = GetTxtFromMgr(2992);
	//// ��ä����
	TCHAR buf2[128];
	//g_JYLibFunction.SetNumUnit( VILLAGE_PROFIT_FOR_FANPRIEST, buf2, 128 );
	//StringCchPrintf(buffer, 1024,  pText, buf2 );
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_FANPRIEST")),			-1,						buffer);

	pText = GetTxtFromMgr(2993);
	// Ȥ�θ�����. 
	g_JYLibFunction.SetNumUnit( VILLAGE_PROFIT_FOR_WENNYOLDMAN, buf2, 128 );
	StringCchPrintf(buffer, 1024,  pText, buf2);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_WENNYOLDMAN")),		-1,						buffer);

	pText = GetTxtFromMgr(2994);
	// ������
	StringCchPrintf(buffer, 1024,  pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_MUDANG")),			-1,						buffer);

	pText = GetTxtFromMgr(2995);
	// ���̱輱��
	g_JYLibFunction.SetNumUnit( VILLAGE_PROFIT_FOR_INVESTMENT, buf2, 128 );
	StringCchPrintf(buffer, 1024,  pText, buf2);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_INVESTMENT")),		-1,						buffer);

	pText = GetTxtFromMgr(2996);
	// ����ȣ
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_WAITINGMAN2") ),	QUEST_TYPE_BEGINNER3,
		pText);

	pText = GetTxtFromMgr(8363);
	// ���˼�
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_PRISONER")),		QUEST_TYPE_BEGINNER4,	pText);

	// ������
	//pText = GetTxtFromMgr(2955);
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_WAITINGMAN3") ),	QUEST_TYPE_BEGINNER5,
	//	pText);
	//pText = GetTxtFromMgr(2955);
	//Add(pclClient->GetUniqueFromHash( TEXT("KIND_WAITINGMAN4") ),	QUEST_TYPE_BEGINNER5,
	//	pText);

	// �߱������� ����ϴ� NPC - LEEKH : 2007.04.02
	if(pclClient->siServiceArea == ConstServiceArea_China)
	{
		pText = GetTxtFromMgr(10000);
		Add(pclClient->GetUniqueFromHash( TEXT("KIND_GUYAJA")),	-1,	pText );
	}
	//���Ǻ�����Ʈ[2007.08.22 �ռ���]
	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	if( pclClient->IsCountrySwitch( Switch_HappyBeanQuest ) )
	{
		pText = GetTxtFromMgr(10000);
		Add(pclClient->GetUniqueFromHash( TEXT("KIND_HAPPYBEAN_NPC1")),QUEST_TYPE_HAPPYBEAN,	pText );
	}

	pText = GetTxtFromMgr(180);
	//[�߰� : Ȳ���� 2007. 11. 20 ũ�������� ����Ʈâ�� �絹���� ����.]
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_RUDOLPH")), QUEST_TYPE_MAKESANTAHAT,	pText);

	//[�߰� : Ȳ���� 2007. 11. 20 ũ�������� ����Ʈâ�� �絹���� ����.]
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_RUDOLPH")), QUEST_TYPE_MAKECAKE,		pText);

	//[�߰� : Ȳ���� 2007. 11. 20 ũ�������� ����Ʈâ�� �絹���� ����.]
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_RUDOLPH")), QUEST_TYPE_PLAYCHRISTMAS,	pText);

	//[�߰� : Ȳ���� 2008. 1. 24 => NPC ���� < NPC Devorah >]
	pText = GetTxtFromMgr(7888);
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_MAGICALRACCOON_NPC")),	-1,	buffer);

	//[�߰� : Ȳ���� 2008. 1. 24 => NPC ���� < NPC Antonio >]
	pText = GetTxtFromMgr(7889);
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_ZORRORACCOON_NPC")),	-1,	buffer);

	//[�߰� : Ȳ���� 2008. 1. 24 => NPC ���� < NPC Gonzales >]
	pText = GetTxtFromMgr(7890);
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_RACCOONLORD_NPC1")),	-1,	buffer);

	//[�߰� : Ȳ���� 2008. 1. 24 => NPC ���� < NPC Ting Ting >]
	pText = GetTxtFromMgr(7891);
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_REWARD")),				-1,	buffer);

	//[�߰� : Ȳ���� 2008. 1. 24 => NPC ���� < NPC Reco >]
	pText = GetTxtFromMgr(7892);
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_RECOMMENDER")),		-1,	buffer);

	//[�߰� : Ȳ���� 2008. 1. 24 => NPC ���� < NPC floria >]
	pText = GetTxtFromMgr(7896);
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_TITLENPC")),		-1,	buffer);

	// ũ����Ż NPC �߰�
	pText = GetTxtFromMgr(8356);
	StringCchPrintf(buffer, 1024, pText);
	Add(pclClient->GetUniqueFromHash( TEXT("KIND_ARTIFACTNPC")),		-1,	buffer);
}

cltSystemNPCManager::~cltSystemNPCManager()
{
}

bool cltSystemNPCManager::Add(SI32 kind, SI32 questtype, TCHAR* explain)
{
	SI32 i;

	for(i = 0;i < MAX_SYSTEM_NPC_NUMBER;i++)
	{
		if(clSystemNPC[i].siKind == 0)
		{
			
			clSystemNPC[i].Set(kind, questtype, explain);
			return true;
		}
	}

	return false;
}

bool cltSystemNPCManager::FindSystemNPCInfo(SI32 kind, cltSystemNPC* pclinfo)
{
	SI32 i;

	if(kind <= 0)return false;

	for(i = 0;i < MAX_SYSTEM_NPC_NUMBER;i++)
	{
		if(clSystemNPC[i].siKind == kind)
		{
			pclinfo->Set(&clSystemNPC[i]);
			return true;
		}
	}

	return false;

}

bool cltSystemNPCManager::FindSystemNPCInfoFromQuestType(SI32 questtype, cltSystemNPC* pclinfo)
{
	SI32 i;

	if(questtype <= 0)return false;

	for(i = 0;i < MAX_SYSTEM_NPC_NUMBER;i++)
	{
		if(clSystemNPC[i].siQuestType == questtype)
		{
			pclinfo->Set(&clSystemNPC[i]);
			return true;
		}
	}

	return false;

}
*/