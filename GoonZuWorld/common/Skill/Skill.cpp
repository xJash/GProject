//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Client\Client.h"
#include "Skill-Manager.h"
#include "..\Resource.h"
#include "..\Client\Interface\ErrorMsgDlg\ErrorMsgDlg.h"

extern cltCommonLogic* pclClient;

//------------------------------------------------
// cltPSkillInfo
//------------------------------------------------


void cltPSkillInfo::Set(cltPSkillInfo* pskill)
{
	if(pskill == NULL)return ;

	memcpy(this, pskill, sizeof(cltPSkillInfo));					//ok
}

// �θ� ����� ������ ���Ѵ�. 
UI32 cltPSkillInfo::GetParentSkillLevel(SI32 skillunique, cltItem* pclitemlist)
{

	// �θ� ����� ���۷����� ���Ѵ�. 
	SI32 parentref = pclClient->pclSkillManager->GetParentSkillRef(skillunique);

	if(parentref)
	{
		SI32 parentskill = pclClient->pclSkillManager->pclSkillInfo[parentref]->siUnique;

		return GetTotalSkillLevel(parentskill, 0, 0, pclitemlist);
	}

	return 0;
}


// ���� �������� ���� ��ų�� �����. 
BOOL cltPSkillInfo::MakeSkill(SI32 skillunique)
{
	if(clSkill[skillunique].uiLevel)
	{
		return FALSE;
	}
	
	clSkill[skillunique].uiSkillUnique	= skillunique;
	clSkill[skillunique].uiLevel		= 1;
	
	return TRUE;

}

// ��ų�� �����ش�.
BOOL cltPSkillInfo::IncreaseSkillLevel(SI32 skillunique, SI32 level)
{
	clSkill[skillunique].uiLevel += level;
	return TRUE;
}
//// ��ų ���跹���� �����ش�.
//BOOL cltPSkillInfo::IncreaseSkillExpLevel(SI32 skillunique, SI32 level)
//{
//	SI32 skillexp = GetRequiredExpForLevel( level )
//	clSkill[skillunique].siSkillExp = skillexp + 1;
//	return TRUE;
//}

// Ư�� ��ų�� ������ ���Ѵ�. 
SI32 cltPSkillInfo::GetSkillLevel(SI32 skillunique)
{
	return clSkill[skillunique].uiLevel;
}

// Ư�� ��ų�� ���跹���� ���Ѵ�. 
SI32 cltPSkillInfo::GetSkillExpLevel(SI32 skillunique)
{
	return GetSkillLevelFromExp(clSkill[skillunique].siSkillExp);
}

// Ư�� ��ų�� �ѷ����� ���Ѵ�. 
SI32 cltPSkillInfo::GetTotalSkillLevel(SI32 skillunique, SI32 sikind, SI32 level, cltItem* pclitemlist, SI32 id )
{
	SI32 equipskilllevel = 0;
	if(pclitemlist)
	{
		//KHY - 0320 - ��ȸ�� ����.
		//if(pclitemlist->siUnique != 0 ) // �ش� �������� ������ �˻����� �ʴ´�. 

		equipskilllevel = pclClient->pclItemManager->GetUpgradeSkillLevel( pclitemlist, skillunique, id );
	}
	
	if(sikind == 0)
	{
		return equipskilllevel + GetSkillLevel(skillunique) + GetSkillExpLevel(skillunique);
	}
	else
	{
		return min(100, pclClient->pclKindInfoSet->pclKI[sikind]->siSkillLevel + (level / 10));	//������ ���� ȿ���� �߰��Ѵ�. 
	}

//	return 0;
}

// Ư�� ��ų�� �� ����ġ�� ���Ѵ�.
SI32 cltPSkillInfo::GetTotalSkillExp( SI32 skilluinque )
{
	return clSkill[skilluinque].siSkillExp;
}


// ���� ������ ���� ��ų�� ���ߵǾ� �ִ��� Ȯ���Ѵ�. 
bool cltPSkillInfo::ChcekUseWeaponSkill(SI32 type, cltItem* pclitemlist, SI32* preturnval)
{
	SI32 needskillunique	= 0;
	SI32 needskilllevel		= 0;
	GetMountSkillKind( type, pclitemlist, &needskillunique, &needskilllevel);

	//cyj ȭ�� �� źȯ�� ��ų ���� ��������
	if (pclitemlist->IsBulletItem())
		return true;

	switch(type)
	{
	case ITEMTYPE_SWORD:
		if(GetTotalSkillLevel(SKILL_USESWORD1, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_USESWORD1;	return false;}
		break;
	case ITEMTYPE_SPEAR:
		if(GetTotalSkillLevel(SKILL_USESPEAR1, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_USESPEAR1;	return false;}
		break;
	case ITEMTYPE_STAFF:
		if(GetTotalSkillLevel(SKILL_USESTAFF1, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_USESTAFF1;	return false;}
		break;
	case ITEMTYPE_AXE:
		if(GetTotalSkillLevel(SKILL_USEAXE1, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_USEAXE1;		return false;}
		break;
	case ITEMTYPE_BOW:
		if(GetTotalSkillLevel(SKILL_USEBOW1, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_USEBOW1;		return false;}
		break;
	case ITEMTYPE_GUN:
		if(GetTotalSkillLevel(SKILL_USEGUN1, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_USEGUN1;		return false;}
		break;
	case ITEMTYPE_FISHINGROD:
		if(GetTotalSkillLevel(SKILL_FISH, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_FISH;		return false;}
		break;
	case ITEMTYPE_IRON:
		if(GetTotalSkillLevel(SKILL_FARM, 0, 0, pclitemlist) < needskilllevel){	*preturnval = SKILL_FARM;		return false;}
		break;
		

		
	default:
		return false;
	}

	return true;	
}

// 2003.10.23
bool cltPSkillInfo::GetMountSkillKind(SI32 type, cltItem* pclitemlist, SI32 *pMountSkill, SI32 *pSkillPoint )
{
	switch(type)
	{
	case ITEMTYPE_SWORD:
		*pMountSkill = SKILL_USESWORD1;	
		if((*pSkillPoint = GetTotalSkillLevel(*pMountSkill, 0, 0, pclitemlist)) <= 0)
		{			
			return false;
		}
		break;
	case ITEMTYPE_SPEAR:
		*pMountSkill = SKILL_USESPEAR1;
		if((*pSkillPoint = GetTotalSkillLevel(*pMountSkill, 0, 0, pclitemlist)) <= 0)
		{			
			return false;
		}
		break;
	case ITEMTYPE_STAFF:
		*pMountSkill = SKILL_USESTAFF1;
		if((*pSkillPoint = GetTotalSkillLevel(*pMountSkill, 0, 0, pclitemlist)) <= 0)
		{			
			return false;
		}
		break;
	case ITEMTYPE_AXE:
		*pMountSkill = SKILL_USEAXE1;
		if((*pSkillPoint = GetTotalSkillLevel(*pMountSkill, 0, 0, pclitemlist)) <= 0)
		{			
			return false;
		}
		break;
	case ITEMTYPE_BOW:
		*pMountSkill = SKILL_USEBOW1;
		if((*pSkillPoint = GetTotalSkillLevel(*pMountSkill, 0, 0, pclitemlist)) <= 0)
		{			
			return false;
		}
		break;
	case ITEMTYPE_GUN:
		*pMountSkill = SKILL_USEGUN1;
		if((*pSkillPoint = GetTotalSkillLevel(*pMountSkill, 0, 0, pclitemlist))<= 0)
		{			
			return false;
		}
		break;
	case ITEMTYPE_ANIMAL:
		*pMountSkill = SKILL_HORSETRAINING;
		if((*pSkillPoint = GetTotalSkillLevel(*pMountSkill, 0, 0, pclitemlist))<= 0)
		{			
			return false;
		}
		break;

	default:
		
		return false;

	}

	return true;	
}

// ������� ����� �����ϰ� ���׷��̵� ��ų ����� ������ ���� ���Ѵ�.
bool cltPSkillInfo::GetRandSkillForUpgrade(cltSkillManager* pclskillmanager, cltItem* pclitemlist, SI32* pskillunique, SI32* pupgradeskilllevel )
{
	SI32 i;

	SI32 silist[MAX_SKILL_NUMBER];
	SI32 listindex = 0;

	for(i = 0;i < MAX_SKILL_NUMBER;i++)
	{
		// ���� ���ߵ��� ���� ����� �ø� �� ����. 
		if(clSkill[i].uiLevel <= 0)continue;
		// �ִ� �������� ���ߵ� ����� ����� �ƴϴ�. 
		if(clSkill[i].uiLevel >= pclskillmanager->GetMaxLevel(i))continue;
		// ���������� �ȵȴ�.
		if ( pclskillmanager->pclSkillInfo[i] &&
			 pclskillmanager->pclSkillInfo[i]->siSkillType == SKILLTYPE_FIGHT ) continue ;

		silist[listindex] = i;
		listindex ++;
	}

	if(listindex <= 0)return false;

	*pskillunique		= silist[rand() % listindex];
	*pupgradeskilllevel	= GetTotalSkillLevel(*pskillunique, 0, 0, pclitemlist) + 1;

	return true;
}


// ������� ����� �����ϰ� ���׷��̵� ��ų ����� ������ ����ġ�� ���Ѵ�.
bool cltPSkillInfo::GetRandSkillEXPupForUpgrade(cltSkillManager* pclskillmanager, cltItem* pclitemlist, SI32* pskillunique,  SI32* increaseSkillExp )
{
	SI32 i;

	SI32 silist[MAX_SKILL_NUMBER];
	SI32 listindex = 0;

	for(i = 0;i < MAX_SKILL_NUMBER;i++)
	{
		// ���� ���ߵ��� ���� ����� �ø� �� ����. 
		if(clSkill[i].uiLevel <= 0)continue;
		// �ִ� �������� ���ߵ� ����� ����� �ƴϴ�. 
		if(clSkill[i].uiLevel >= pclskillmanager->GetMaxLevel(i))continue;
		// ���������� �ȵȴ�.
		if ( pclskillmanager->pclSkillInfo[i] &&
			pclskillmanager->pclSkillInfo[i]->siSkillType == SKILLTYPE_FIGHT ) continue ;

		silist[listindex] = i;
		listindex ++;
	}

	if(listindex <= 0)return false;

	*pskillunique		= silist[rand() % listindex];
	// ����ġ�� �����ϴ� �������� �����Ƿ�, �����ۿ� ���� �����п� ���ؼ� ������� �ʴ´�. (���� ����ġ ����Ʈ�� +1 �� �Ǹ� ����Ʈ �Ϸ� ������ �ȴ�.)
	*increaseSkillExp	= GetTotalSkillExp(*pskillunique) + 1;

	return true;
}

//------------------------------------------------
// cltSkillInfo
//------------------------------------------------
cltSkillInfo::cltSkillInfo(SI32 unique, SI32 skilltype, SI32 skillatb, TCHAR *code, TCHAR* name, SI32 maxskilllevel,
						   SI32 parentref, SI32 bitmapindex, SI32 explainunique ,SI32 weapontype)
{
	// ����ũ ����. 
	siUnique				= unique;

	siSkillType				= skilltype;
	siWeaponType			= weapontype;

	siParentRef				= parentref;

	siMaxSkillLevel			= maxskilllevel;

	siSkillAtb				= skillatb;

	siBitMapIndex			= bitmapindex;

	// ��ų �ڵ� ����. 
	if(code == NULL)
	{
		StringCchCopy(szCode, MAX_SKILL_NAME_LENGTH, TEXT("NOCodeSkill"));
	}
	else
	{
		MStrCpy(szCode, code, MAX_SKILL_NAME_LENGTH );
	}

	// �̸� ����. 
	if(name == NULL)
	{
		StringCchCopy(szName, MAX_SKILL_NAME_LENGTH, TEXT("NoNameSkill"));
	}
	else
	{
		MStrCpy(szName, name, MAX_SKILL_NAME_LENGTH );
	}

	siExplainUnique = explainunique;

	pclWeaponSkillInfo = NULL ;

	if ( weapontype && skilltype != SKILLTYPE_R_USEWEAPON )
	{
		pclWeaponSkillInfo = new cltWeaponSkillInfo * [siMaxSkillLevel] ;

		for ( SI32 i = 0 ; i < siMaxSkillLevel ; i ++ )
		{
			pclWeaponSkillInfo[i] = NULL ;
			pclWeaponSkillInfo[i] = new cltWeaponSkillInfo ;
		}
	}
}

cltSkillInfo::~cltSkillInfo()
{

	if ( pclWeaponSkillInfo )
	{
		for ( SI32 i = 0 ; i < siMaxSkillLevel ; i ++ )
		{
			if ( pclWeaponSkillInfo[i] )
			{
				delete pclWeaponSkillInfo[i] ;
				pclWeaponSkillInfo[i] = NULL ;
			}
		}

		delete [] pclWeaponSkillInfo ;
		pclWeaponSkillInfo = NULL ;
	}
}


//-------------------------------------------------
// cltSkillTypeInfo
//-------------------------------------------------
cltSkillTypeInfo::cltSkillTypeInfo(SI32 skilltype, TCHAR* pskillcode, TCHAR* name,BOOL bshow)
{
	siSkillType	= skilltype;
	bShowData = bshow ;

	if(name)
	{
		MStrCpy(szName, name, MAX_SKILL_TYPE_NAME_LENGTH );
	}
	else
	{
		StringCchCopy(szName, MAX_SKILL_NAME_LENGTH, TEXT("NoSkillTypeName"));
	}

	MStrCpy(szSkillCode, pskillcode, MAX_SKILL_TYPE_CODE_LENGTH );
}


cltSkillTypeInfo::~cltSkillTypeInfo()
{

}

//--------------------------------------------------------------------------------------------------
// ������� ���� / ������� ���� / ������� ���� / ������� ���� / ������� ���� / ������� ����
//--------------------------------------------------------------------------------------------------

//-------------------------------------------------
// ������� ���� ����
//-------------------------------------------------
cltWeaponSkillMaster::cltWeaponSkillMaster()
{
	ZeroMemory( this, sizeof(cltWeaponSkillMaster) );
}

cltWeaponSkillMaster::cltWeaponSkillMaster( SI16 siApplyLevel, SI16 siApplyAbility, SI32 siApplyValue )
{
	m_siApplyLevel		= siApplyLevel;
	m_siApplyAbility	= siApplyAbility;
	m_siApplyValue		= siApplyValue;
}

cltWeaponSkillMaster::~cltWeaponSkillMaster()
{
}

void cltWeaponSkillMaster::Init( void )
{
	ZeroMemory( this, sizeof(cltWeaponSkillMaster) );
}

void cltWeaponSkillMaster::Set( SI16 siApplyLevel, SI16 siApplyAbility, SI32 siApplyValue )
{
	m_siApplyLevel		= siApplyLevel;
	m_siApplyAbility	= siApplyAbility;
	m_siApplyValue		= siApplyValue;
}

SI32 cltWeaponSkillMaster::GetValue( SI16 siApplyLevel, SI16 siApplyAbility )
{
	if ( siApplyLevel < m_siApplyLevel )
	{
		return 0;
	}

	if ( siApplyAbility != m_siApplyAbility )
	{
		return 0;
	}

	return m_siApplyValue;
}

bool cltWeaponSkillMaster::IsEmpty( void )
{
	if ( 0 < m_siApplyLevel )
	{
		return false;
	}

	if ( 0 < m_siApplyAbility )
	{
		return false;
	}

	if ( 0 < m_siApplyValue )
	{
		return false;
	}

	return true;
}

SI16 cltWeaponSkillMaster::GetApplyLevel( void )
{
	return m_siApplyLevel;
}

SI16 cltWeaponSkillMaster::GetApplyAbility( void )
{
	return m_siApplyAbility;
}

SI32 cltWeaponSkillMaster::GetApplyValue( void )
{
	return m_siApplyValue;
}

//-------------------------------------------------
// ����� ���� �޴���
//-------------------------------------------------
cltWeaponSkillMasterManager::cltWeaponSkillMasterManager()
{
	m_clWeaponSkillMaster.ZeroMem();
}

cltWeaponSkillMasterManager::~cltWeaponSkillMasterManager()
{
}

void cltWeaponSkillMasterManager::Init( void )
{
	m_clWeaponSkillMaster.ZeroMem();
}

void cltWeaponSkillMasterManager::LoadSkillMasterFile( void )
{
	TCHAR		szFileName[128]	= TEXT("Data\\WeaponSkillMaster.txt");
	NDataLoader	dataloader;
	BOOL		bLoadFile		= FALSE;


	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
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
		if (pclClient->GameMode != GAMEMODE_SERVER)
		{
			MessageBox(NULL, TEXT("WeaponSkillMaster Load Error"), TEXT("Error"), MB_OK|MB_TOPMOST);
		}

		return;
	}

	TCHAR	szWeaponType[64]	= TEXT("");
	TCHAR	szAbility[64]		= TEXT("");
	SI32	siLevel				= 0;
	SI32	siValue				= 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	szWeaponType,	64,
		NDATA_MBSTRING,	szAbility,		64,
		NDATA_INT32,	&siLevel,		4,
		NDATA_INT32,	&siValue,		4,
		0,0,0
	};

	SI32 siWeaponType	= 0;
	SI32 siAbility		= 0;

	dataloader.RegDataType(pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData())	
		{
			siWeaponType	= ConvertTextToWeaponType( szWeaponType );
			siAbility		= ConvertTextToAbility( szAbility );

			Add( siWeaponType, siLevel, siAbility, siValue );
		}
	}
}

SI32 cltWeaponSkillMasterManager::ConvertTextToWeaponType( TCHAR* pszWeaponTypeText )
{
	if ( NULL == pszWeaponTypeText )
	{
		return 0;
	}

	COMPARE_TEXT_WITH_VALUE( pszWeaponTypeText, SKILLMSTER_WEAPONTYPE_SWORD );
	COMPARE_TEXT_WITH_VALUE( pszWeaponTypeText, SKILLMSTER_WEAPONTYPE_SPEAR );
	COMPARE_TEXT_WITH_VALUE( pszWeaponTypeText, SKILLMSTER_WEAPONTYPE_BOW );
	COMPARE_TEXT_WITH_VALUE( pszWeaponTypeText, SKILLMSTER_WEAPONTYPE_AXE );
	COMPARE_TEXT_WITH_VALUE( pszWeaponTypeText, SKILLMSTER_WEAPONTYPE_GUN );
	COMPARE_TEXT_WITH_VALUE( pszWeaponTypeText, SKILLMSTER_WEAPONTYPE_STAFF );

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ο� ����Ÿ���� ���� ���ּ���
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	NTCHARString256 strText( pszWeaponTypeText );
	NTCHARString64	strCaption( _T("Error") );

	strText += _T(" WeaponType Not Found");

	MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
#endif

	return 0;
}

SI32 cltWeaponSkillMasterManager::ConvertTextToAbility( TCHAR* pszAbilityText )
{
	if ( NULL == pszAbilityText )
	{
		return 0;
	}

	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_PHYSICALATTACK );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_PHYSICALDEFENSE );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_PHYSICALDODGE );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_PHYSICALHIT );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_MAGICALATTACK );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_MAGICALDEFENSE );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_MAGICALDODGE );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_MAGICALHIT );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_STR );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_HAND );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_DEX );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_MAG );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_WIS );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_VIT );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_LUCK );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_CRITICAL );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_ATTACKRANGE );
	COMPARE_TEXT_WITH_VALUE( pszAbilityText, SKILLMASTER_ATTACKINTERVAL );

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ο� �����׸��� ���� ���ּ���
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	NTCHARString256 strText( pszAbilityText );
	NTCHARString64	strCaption( _T("Error") );

	strText += _T(" Ability Not Found");

	MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
#endif

	return 0;
}

bool cltWeaponSkillMasterManager::GetEmblemExplain( IN SI32 siItemType, IN SI32 siSkillLevel, OUT TCHAR* pszExplain, IN SI32 siTextSize )
{
	if ( (0 >= siSkillLevel) || (NULL == pszExplain) || (0 >= siTextSize) )
	{
		return false;
	}

	SI32 siWeaponType = GetWeaponTypeFromItemType( siItemType );
	if ( (SKILLMSTER_WEAPONTYPE_NONE >= siWeaponType) || (SKILLMSTER_WEAPONTYPE_MAX <= siWeaponType) )
	{
		return false;
	}

	cltWeaponSkillMaster* pclGetInfo = &m_clWeaponSkillMaster[siWeaponType];
	if ( NULL == pclGetInfo )
	{
		return false;
	}

	if ( true == pclGetInfo->IsEmpty() )
	{
		return false;
	}

	if ( pclGetInfo->GetApplyLevel() > siSkillLevel )
	{
		return false;
	}
	
	SI32 siGetValue		= pclGetInfo->GetApplyValue();
	SI32 siGetAbility	= pclGetInfo->GetApplyAbility();
	if ( (SKILLMASTER_NONE >= siGetAbility) || (SKILLMASTER_MAX <= siGetAbility) )
	{
		return false;
	}

	SI32 siEmblemTextNum = GetEmblemTextNum( siWeaponType );
	if ( 0 >= siEmblemTextNum )
	{
		return false;
	}

	SI32 siAbilityTextNum = GetAbilityTextNum( siGetAbility );
	if ( 0 >= siAbilityTextNum )
	{
		return false;
	}

	NTCHARString128 strEmblemText	= GetTxtFromMgr( siEmblemTextNum );
	NTCHARString128 strAbilityText	= GetTxtFromMgr( siAbilityTextNum );

	strAbilityText.Replace( TEXT("#value#"), SI32ToString(siGetValue) );
	
	NTCHARString512 strBuffer = TEXT( "#emblem# : #ability#" );
	strBuffer.Replace( TEXT("#emblem#"), strEmblemText );
	strBuffer.Replace( TEXT("#ability#"), strAbilityText );

	MStrCpy( pszExplain, strBuffer, siTextSize );

	return true;
}

bool cltWeaponSkillMasterManager::IsCanTakeEmblemWithNotice( IN SI32 siSkillUnique, SI32 siSkillLevel, OUT TCHAR* pszNotice, IN SI32 siTextSize )
{
	if ( (0 >= siSkillLevel) || (NULL == pszNotice) || (0 >= siTextSize) )
	{
		return false;
	}

	SI32 siWeaponType = GetWeaponTypeFromSkillUnique( siSkillUnique );
	if ( SKILLMSTER_WEAPONTYPE_NONE >= siWeaponType )
	{
		return false;
	}

	cltWeaponSkillMaster* pclGetInfo = &m_clWeaponSkillMaster[ siWeaponType ];
	if ( NULL == pclGetInfo )
	{
		return false;
	}

	SI32 siGetLevel = pclGetInfo->GetApplyLevel();
	if ( siGetLevel != siSkillLevel )
	{
		return false;
	}

	SI32 siGetAbility = pclGetInfo->GetApplyAbility();
	if ( (SKILLMASTER_NONE >= siGetAbility) || (SKILLMASTER_MAX <= siGetAbility) )
	{
		return false;
	}

	SI32 siGetValue = pclGetInfo->GetApplyValue();

	SI32 siEmblemTextNum = GetEmblemTextNum( siWeaponType );
	if ( 0 >= siEmblemTextNum )
	{
		return false;
	}

	SI32 siAbilityTextNum = GetAbilityTextNum( siGetAbility );
	if ( 0 >= siAbilityTextNum )
	{
		return false;
	}

	NTCHARString128 strEmblemText	= GetTxtFromMgr( siEmblemTextNum );
	NTCHARString128 strAbilityText	= GetTxtFromMgr( siAbilityTextNum );

	strAbilityText.Replace( TEXT("#value#"), SI32ToString(siGetValue) );

	NTCHARString512 strBuffer = GetTxtFromMgr( 9829 );

	strBuffer.Replace( TEXT("#skilllevel#"),	SI32ToString(siGetLevel) );
	strBuffer.Replace( TEXT("#emblem#"),		strEmblemText );
	strBuffer.Replace( TEXT("#ability#"),		strAbilityText );

	MStrCpy( pszNotice, strBuffer, siTextSize );

	return true;	
}

/*
bool cltWeaponSkillMasterManager::GetEmblemGimgAndFontIndex( IN SI32 siItemType, IN SI32 siSkillLevel, OUT SI32* psiGimg, OUT SI32* psiFontIndex )
{
	if ( (0 >= siSkillLevel) || (NULL == psiGimg) || (NULL == psiFontIndex) )
	{
		return false;
	}

	SI32 siWeaponType = GetWeaponTypeFromItemType( siItemType );
	if ( (SKILLMSTER_WEAPONTYPE_NONE >= siWeaponType) || (SKILLMSTER_WEAPONTYPE_MAX <= siWeaponType) )
	{
		return false;
	}

	if ( m_clWeaponSkillMaster[siWeaponType].IsEmpty() )
	{
		return false;
	}

	if ( m_clWeaponSkillMaster[siWeaponType].GetApplyLevel() > siSkillLevel )
	{
		return false;
	}

	*psiGimg		= GIMG_EMBLEM;
	*psiFontIndex	= (siWeaponType - 1);

	return true;
}
*/

UI08 cltWeaponSkillMasterManager::GetEmblemIndex( IN SI32 siItemType, IN SI32 siSkillLevel )
{
	if ( 0 >= siSkillLevel )
	{
		return 0;
	}

	SI32 siWeaponType = GetWeaponTypeFromItemType( siItemType );
	if ( (SKILLMSTER_WEAPONTYPE_NONE >= siWeaponType) || (SKILLMSTER_WEAPONTYPE_MAX <= siWeaponType) )
	{
		return 0;
	}

	if ( m_clWeaponSkillMaster[siWeaponType].IsEmpty() )
	{
		return 0;
	}

	if ( m_clWeaponSkillMaster[siWeaponType].GetApplyLevel() > siSkillLevel )
	{
		return 0;
	}

	return (siWeaponType);
}

void cltWeaponSkillMasterManager::Add( SI32 siWeaponType, SI16 siApplyLevel, SI16 siApplyAbility, SI32 siApplyValue )
{
	if ( (SKILLMSTER_WEAPONTYPE_NONE >= siWeaponType) || (SKILLMSTER_WEAPONTYPE_MAX <= siWeaponType) )
	{
		return;
	}

	m_clWeaponSkillMaster[siWeaponType].Set( siApplyLevel, siApplyAbility, siApplyValue );
}

SI32 cltWeaponSkillMasterManager::GetApplyValue( SI32 siItemType, SI16 siSkillLevel, SI16 siApplyAbility )
{
	SI32 siWeaponType = GetWeaponTypeFromItemType( siItemType );
	if ( (SKILLMSTER_WEAPONTYPE_NONE >= siWeaponType) || (SKILLMSTER_WEAPONTYPE_MAX <= siWeaponType) )
	{
		return 0;
	}

	SI32 siReturnValue = m_clWeaponSkillMaster[siWeaponType].GetValue( siSkillLevel, siApplyAbility );

	return siReturnValue;
}

SI32 cltWeaponSkillMasterManager::GetSkillUseWeaponFromItemType( SI32 siItemType )
{
	SI32 siSkillUnique = 0;

	switch ( siItemType )
	{
		case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_USESWORD1;	}	break;
		case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_USESPEAR1;	}	break;
		case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_USEAXE1;		}	break;
		case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_USEBOW1;		}	break;
		case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_USEGUN1;		}	break;
		case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_USESTAFF1;	}	break;
	}

	return siSkillUnique;

}

SI32 cltWeaponSkillMasterManager::GetWeaponTypeFromItemType( SI32 siItemType )
{
	SI32 siWeaponType = SKILLMSTER_WEAPONTYPE_NONE;

	switch ( siItemType )
	{
		case ITEMTYPE_SWORD:	{	siWeaponType = SKILLMSTER_WEAPONTYPE_SWORD;	}	break;
		case ITEMTYPE_SPEAR:	{	siWeaponType = SKILLMSTER_WEAPONTYPE_SPEAR;	}	break;
		case ITEMTYPE_AXE:		{	siWeaponType = SKILLMSTER_WEAPONTYPE_AXE;	}	break;
		case ITEMTYPE_BOW:		{	siWeaponType = SKILLMSTER_WEAPONTYPE_BOW;	}	break;
		case ITEMTYPE_GUN:		{	siWeaponType = SKILLMSTER_WEAPONTYPE_GUN;	}	break;
		case ITEMTYPE_STAFF:	{	siWeaponType = SKILLMSTER_WEAPONTYPE_STAFF;	}	break;
	}

	return siWeaponType;
}

SI32 cltWeaponSkillMasterManager::GetWeaponTypeFromSkillUnique( SI32 siSkillUnique )
{
	SI32 siWeaponType = SKILLMSTER_WEAPONTYPE_NONE;

	switch ( siSkillUnique )
	{
		case SKILL_USESWORD1:	{	siWeaponType = SKILLMSTER_WEAPONTYPE_SWORD;	}	break;
		case SKILL_USESPEAR1:	{	siWeaponType = SKILLMSTER_WEAPONTYPE_SPEAR;	}	break;
		case SKILL_USEAXE1:		{	siWeaponType = SKILLMSTER_WEAPONTYPE_AXE;	}	break;
		case SKILL_USEBOW1:		{	siWeaponType = SKILLMSTER_WEAPONTYPE_BOW;	}	break;
		case SKILL_USEGUN1:		{	siWeaponType = SKILLMSTER_WEAPONTYPE_GUN;	}	break;
		case SKILL_USESTAFF1:	{	siWeaponType = SKILLMSTER_WEAPONTYPE_STAFF;	}	break;
	}

	return siWeaponType;
}

SI32 cltWeaponSkillMasterManager::GetEmblemTextNum( SI32 siWeaponType )
{
	SI32 siTextNum = 0;

	switch ( siWeaponType )
	{
		case SKILLMSTER_WEAPONTYPE_SWORD:	{	siTextNum = (9805);	}	break;
		case SKILLMSTER_WEAPONTYPE_SPEAR:	{	siTextNum = (9806);	}	break;
		case SKILLMSTER_WEAPONTYPE_BOW:		{	siTextNum = (9807);	}	break;
		case SKILLMSTER_WEAPONTYPE_AXE:		{	siTextNum = (9808);	}	break;
		case SKILLMSTER_WEAPONTYPE_GUN:		{	siTextNum = (9809);	}	break;
		case SKILLMSTER_WEAPONTYPE_STAFF:	{	siTextNum = (9810);	}	break;
	}

	return siTextNum;
}

SI32 cltWeaponSkillMasterManager::GetAbilityTextNum( SI32 siAbility )
{
	SI32 siTextNum = 0;

	switch ( siAbility )
	{
		case SKILLMASTER_PHYSICALATTACK:	{	siTextNum = (9811);	}	break;
		case SKILLMASTER_PHYSICALDEFENSE:	{	siTextNum = (9812);	}	break;
		case SKILLMASTER_PHYSICALDODGE:		{	siTextNum = (9813);	}	break;
		case SKILLMASTER_PHYSICALHIT:		{	siTextNum = (9814);	}	break;
		case SKILLMASTER_MAGICALATTACK:		{	siTextNum = (9815);	}	break;
		case SKILLMASTER_MAGICALDEFENSE:	{	siTextNum = (9816);	}	break;
		case SKILLMASTER_MAGICALDODGE:		{	siTextNum = (9817);	}	break;
		case SKILLMASTER_MAGICALHIT:		{	siTextNum = (9818);	}	break;
		case SKILLMASTER_STR:				{	siTextNum = (9819);	}	break;
		case SKILLMASTER_HAND:				{	siTextNum = (9820);	}	break;
		case SKILLMASTER_DEX:				{	siTextNum = (9821);	}	break;
		case SKILLMASTER_MAG:				{	siTextNum = (9822);	}	break;
		case SKILLMASTER_WIS:				{	siTextNum = (9823);	}	break;
		case SKILLMASTER_VIT:				{	siTextNum = (9824);	}	break;
		case SKILLMASTER_LUCK:				{	siTextNum = (9825);	}	break;
		case SKILLMASTER_CRITICAL:			{	siTextNum = (9826);	}	break;
		case SKILLMASTER_ATTACKRANGE:		{	siTextNum = (9827);	}	break;
		case SKILLMASTER_ATTACKINTERVAL:	{	siTextNum = (9828);	}	break;
	}

	return siTextNum;
}
