//---------------------------------
// 2003/10/1 ���°�
//---------------------------------

#include "../Client/Client.h"
#include "Skill-Manager.h"
#include "../Resource.h"
#include "Char/CharManager/CharManager.h"

#include "../CommonLogic/MagicMgr/MagicBaseInfo.h"
#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/MagicMgr/MagicAttribute/MagicAttribute.h"
#include "../CommonLogic/MagicMgr/MagicMgr.h"
#include "../Common/Father/Father.h"
#include "../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "NFile.h"
#include "NUtil.h"
#include "NDataloader.h"

extern cltCommonLogic* pclClient;

//static SI32 ExpForSkillLevelUp[MAX_SKILL_LEVEL][3];
static NSafeTArray< NSafeTArray<SI32, 3>, MAX_SKILL_LEVEL + 1>	ExpForSkillLevelUp;

//-------------------------------------------------
// cltSkillManager
//-------------------------------------------------
cltSkillManager::cltSkillManager()
{

	SI32 i;

	m_hDlg				= NULL;			// ��ų ���� ���̾�α� �ڽ��� �ڵ�. 
	
	for(i = 0;i < MAX_SKILL_TYPE_NUMBER;i++)
	{
		TabDlg[i]				= NULL;
	}

	
	DlgRectInitSwitch	= FALSE;

	CharUnique				= 0;
	BonusButtonEnableSwitch	= false;

	CurrentSkillTypeUnique	= 1;
	CurrentSkillUnique		= 1;

	for(i = 0;i < MAX_SKILL_TYPE_NUMBER;i++)
	{
		pclSkillTypeInfo[i] = NULL;
	}

	for(i = 0;i < MAX_SKILL_NUMBER;i++)
	{
		pclSkillInfo[i] = NULL;
	}


	hImageList = NULL;

	//������� ����
	m_clMasterManager.Init();
	m_clMasterManager.LoadSkillMasterFile();

	// ��ų Ÿ���� �߰��Ѵ�. 
	SetSkillType();

	// ��ų�� �߰��Ѵ�. 
	SetSkill();

	LoadSkillExpData();

	LoadSkillLimitFile(TEXT("Data\\SkillLimitInfo.txt"));

	m_hDecreaseSkillHitBitmap = NULL ;
}

cltSkillManager::~cltSkillManager()
{
	SI32 i;

	for(i = 0;i < MAX_SKILL_NUMBER;i++)
	{
		if(pclSkillInfo[i])
		{
			delete pclSkillInfo[i];
			pclSkillInfo[i] = NULL;
		}
	}

	for(i = 0;i < MAX_SKILL_TYPE_NUMBER;i++)
	{
		if(pclSkillTypeInfo[i])
		{
			delete pclSkillTypeInfo[i];
			pclSkillTypeInfo[i] = NULL;
		}
	}
}

// ��ų Ÿ���� �߰��Ѵ�. 
SI32 cltSkillManager::AddSkillType(SI32 skilltype, TCHAR* pskillcode, TCHAR* name,BOOL bshow)
{
	SI32 i;

	for(i = 1;i < MAX_SKILL_TYPE_NUMBER;i++)
	{
		if(pclSkillTypeInfo[i] == NULL)
		{
			pclSkillTypeInfo[i] = new cltSkillTypeInfo(skilltype, pskillcode, name,bshow);
			return i;

		}
	}

	return 0;
}

SI32 cltSkillManager::FindTypeRefFromUnique(SI32 unique)
{
	SI32 i;

	for(i = 1;i < MAX_SKILL_TYPE_NUMBER;i++)
	{
		if(pclSkillTypeInfo[i])
		{
			if(pclSkillTypeInfo[i]->siSkillType == unique)
				return i;
		}
	}

	return 0;
}

// �ڵ带 �ٰŷ� ��ųŸ���� ���Ѵ�. 
SI32 cltSkillManager::FindSkillTypeFromCode(TCHAR* pcode)
{
	SI32 i;

	for(i = 1;i < MAX_SKILL_TYPE_NUMBER;i++)
	{
		if(pclSkillTypeInfo[i])
		{
			if(_tcscmp(pclSkillTypeInfo[i]->szSkillCode, pcode) == 0)
				return i;
		}
	}

	return 0;
}

// ��ų�� �߰��Ѵ�. 
SI32 cltSkillManager::AddSkill(SI32 unique, SI32 skilltype, SI32 skillatb, TCHAR *code, TCHAR* name,SI32 maxskilllevel,
							   SI32 parentref, SI32 bitmapindex, SI32 explainunique,SI32 weapontype)
{

	if(pclSkillInfo[unique] == NULL)
	{
		pclSkillInfo[unique] = new cltSkillInfo(unique, skilltype, skillatb, code, name, maxskilllevel,
												parentref, bitmapindex, explainunique,weapontype);
		
		return unique;
	}

	return 0;

}

bool cltSkillManager::LoadSkillLimitFile(TCHAR* szFileName)
{
	NDataLoader	dataloader;
	BOOL		bLoadFile	= FALSE;
	

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
			MessageBox(NULL, TEXT("SkillLimitInfoLoad Error"), TEXT("Error"), MB_OK|MB_TOPMOST);
		return false;
	}

	TCHAR	szCode[36]				= TEXT("");
	SI32	siSkillLevel			= 0;
	SI32	siLimitLevel			= 0;
	SI32	siBaseSkillLevel		= 0;
	TCHAR	szLimitSkillCode[36]	= TEXT("");
	SI32	siLimitSkillLevel		= 0;
	SI32	siNeedSkillPoint		= 0;
	SI32	siSkillCost				= 0;
	SI32	siApplyPercent			= 0;
	SI32	siHiddenSkillGrade		= 0;
	SI32	siHiddenLimitLevel		= 0;
	SI32	siHiddenLimitSkillLevel	= 0;
	SI32	siItemUnique			= 0;
	SI32	siItemNum				= 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	szCode,						36,
		NDATA_INT32,	&siSkillLevel,				4,
		NDATA_INT32,	&siLimitLevel,				4,
		NDATA_INT32,	&siBaseSkillLevel,			4,
		NDATA_MBSTRING,	szLimitSkillCode,			36,
		NDATA_INT32,	&siLimitSkillLevel,			4,
		NDATA_INT32,	&siNeedSkillPoint,			4,
		NDATA_INT32,	&siSkillCost,				4,
		NDATA_INT32,	&siApplyPercent,			4,
		NDATA_INT32,	&siHiddenSkillGrade,		4,
		NDATA_INT32,	&siHiddenLimitLevel,		4,
		NDATA_INT32,	&siHiddenLimitSkillLevel,	4,
		NDATA_INT32,	&siItemUnique,				4,
		NDATA_INT32,	&siItemNum,					4,
		0,0,0
	};

	dataloader.RegDataType(pDataTypeInfo );

	SI32 siIndex = 0 ;

	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData())	
		{
			if ( szCode[ 0 ] != NULL )
			{
				siIndex = FindUniqueFromSkillCode(szCode) ;
				if ( siIndex )
				{
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siUnique					= siIndex;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siLimitLevel				= siLimitLevel;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siBasicSkillLimitLevel	= siBaseSkillLevel;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siLimitSkillUnique		= FindUniqueFromSkillCode(szLimitSkillCode);
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siSkillLimitLevel		= siLimitSkillLevel;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siNeedSkillPoint			= siNeedSkillPoint;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siSkillCost				= siSkillCost;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siApplyPercent			= siApplyPercent;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siHiddenSkillGrade		= siHiddenSkillGrade;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siHiddenLimitLevel		= siHiddenLimitLevel;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siHiddenLimitSkillLevel	= siHiddenLimitSkillLevel;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siItemUnique				= siItemUnique;
					pclSkillInfo[siIndex]->pclWeaponSkillInfo[siSkillLevel-1]->siItemNum				= siItemNum;
				}
			}
		}
	}


	/*cyj
	TCHAR buffer[1024];

	SI32 i = 0 ;

	FILE* fp = _tfopen(szFileName, TEXT("rt"));
	if(fp == NULL)
	{
		MsgBox(TEXT("fileError"), TEXT("not SkillLimitFile"));
		return false ;
	}

	// ù��° 6���� �����Ѵ�. 
	for(i = 0;i < 6;i++)
		_fgetts(buffer, 1024, fp);

	SI32 index = 0 ;
	while( _fgetts(buffer, 1024, fp) != NULL)
	{
		TCHAR code[36] ;
		SI32 skilllevel ;
		SI32 limitlevel ;
		SI32 baseskilllevel ;
		TCHAR limitskillcode[36] ;
		SI32 limitskilllevel ;
		SI32 skillcost;

		_stscanf( buffer,TEXT("%s %d %d %d %s %d %d"),
				code,&skilllevel,&limitlevel,&baseskilllevel,limitskillcode,&limitskilllevel,&skillcost) ;

		index = FindUniqueFromSkillCode(code) ;
		if ( index )
		{
			pclSkillInfo[index]->pclWeaponSkillInfo[skilllevel-1]->siUnique = index ;
			pclSkillInfo[index]->pclWeaponSkillInfo[skilllevel-1]->siLimitLevel = limitlevel ;
			pclSkillInfo[index]->pclWeaponSkillInfo[skilllevel-1]->siBasicSkillLimitLevel = baseskilllevel ;
			pclSkillInfo[index]->pclWeaponSkillInfo[skilllevel-1]->siLimitSkillUnique = FindUniqueFromSkillCode(limitskillcode) ;
			pclSkillInfo[index]->pclWeaponSkillInfo[skilllevel-1]->siSkillLimitLevel = limitskilllevel ;
			pclSkillInfo[index]->pclWeaponSkillInfo[skilllevel-1]->siSkillCost = skillcost ;
		}
	}
	fclose(fp);

	*/


	return true ;
}

SI32 cltSkillManager::FindUniqueFromSkillCode( TCHAR *strSkillCode )
{
	if ( strSkillCode == NULL )
	{
		return 0;
	}

	SI32 i;

	for( i = 1; i < MAX_SKILL_NUMBER; ++i )
	{
		if( pclSkillInfo[ i ] )
		{
			if ( _tcscmp( pclSkillInfo[ i ]->szCode, strSkillCode ) == 0 )
			{
				return pclSkillInfo[ i ]->siUnique;
			}
		}
	}

	return 0;
}

SI32 cltSkillManager::FindUniqueFromSkillName( TCHAR *strSkillName)
{
	if ( strSkillName == NULL )
	{
		return 0;
	}

	SI32 i;

	for( i = 1; i < MAX_SKILL_NUMBER; ++i )
	{
		if( pclSkillInfo[ i ] )
		{
			if ( _tcscmp( pclSkillInfo[ i ]->szName, strSkillName ) == 0 )
			{
				return pclSkillInfo[ i ]->siUnique;
			}
		}
	}

	return 0;
}

SI32 cltSkillManager::FindSkillTypeFromUnique( SI32 siSkillUnique )
{
	SI32 i;

	for( i = 1; i < MAX_SKILL_NUMBER; ++i )
	{
		if ( pclSkillInfo[i] )
		{
			if ( pclSkillInfo[i]->siUnique == siSkillUnique )
			{
				return pclSkillInfo[i]->siSkillType;
			}
		}
	}

	return 0;
}

SI32 cltSkillManager::FindSkillUniqueFromWeaponSkillType( SI32 siWeaponSkillType )
{
	SI32 siSkillUnique = 0;

	switch( siWeaponSkillType )
	{
		case WEAPONSKILLTYPE_SWORD:	{	siSkillUnique = SKILL_USESWORD1;	}	break;
		case WEAPONSKILLTYPE_SPEAR:	{	siSkillUnique = SKILL_USESPEAR1;	}	break;
		case WEAPONSKILLTYPE_AXE:	{	siSkillUnique = SKILL_USEAXE1;	}	break;
		case WEAPONSKILLTYPE_STAFF:	{	siSkillUnique = SKILL_USESTAFF1;	}	break;
		case WEAPONSKILLTYPE_BOW:	{	siSkillUnique = SKILL_USEBOW1;	}	break;
		case WEAPONSKILLTYPE_GUN:	{	siSkillUnique = SKILL_USEGUN1;	}	break;
	}

	return siSkillUnique;
}


void cltSkillManager::GetSkillLevel()
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];

	SI32 i;

	for(i = 1;i < MAX_SKILL_NUMBER;i++)
	{
		if(pclSkillInfo[i] != NULL)
		{
			m_si32SkillLevel[i] = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( pclSkillInfo[i]->siUnique, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0]);
		}
	}
	
	return;
	
}


BOOL cltSkillManager::TreeViewInsert(HWND hwnd, SI32 type, SI32 parentref, HTREEITEM node)
{
	SI32 index	=  1;

	TV_ITEM tvi;
	TV_INSERTSTRUCT tvis;
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];

	if(id ==0 )return FALSE;

	for(index = 0; index < MAX_SKILL_NUMBER;index++)
	{
		if(pclSkillInfo[index] == NULL)continue;

		if(pclSkillInfo[index]->siSkillType == type)
		{
			if(pclSkillInfo[index]->siParentRef == parentref)
			{
				tvis.hInsertAfter	=	TVI_LAST;
				
				tvi.mask			=	TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM|TVIF_STATE; 
				tvi.iImage			= pclSkillInfo[index]->siBitMapIndex;
				tvi.iSelectedImage	= pclSkillInfo[index]->siBitMapIndex;

				SI32 level  = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel(pclSkillInfo[index]->siUnique, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0], 1 );
				if(level)
				{
					tvi.state		= TVIS_BOLD;
				}
				else
				{
					tvi.state		= TVIS_CUT;
				}
				tvi.stateMask		= TVIS_CUT|TVIS_BOLD;


				MakeSkillTitle(&pclClient->pclCM->CR[id]->pclCI->clCharSkill, &pclClient->pclCM->CR[id]->pclCI->clCharItem, pclSkillInfo[index]->siUnique);

				tvi.pszText			=	pclSkillInfo[index]->szSkillTitle;

				tvi.lParam			=	pclSkillInfo[index]->siUnique;
				
				if(node == 0)
					tvis.hParent		=	TVI_ROOT;
				else 
					tvis.hParent		=	node;
				
				tvis.item			=	tvi;
				
				
				HTREEITEM Node  = TreeView_InsertItem(hwnd, &tvis);
				SendMessage( hwnd, TVM_ENSUREVISIBLE, (WPARAM)0, (LPARAM)Node );
				
				TreeViewInsert(hwnd, type, index, Node);

			}

		}

	}


	return TRUE;
}



void cltSkillManager::MakeSkillTitle(cltPSkillInfo* pclskillmanager, cltPItemInfo* pclcharitem, SI32 skillunique,bool bWeapon)
{

	if(pclskillmanager == NULL)return ;

	SI32 level  = pclskillmanager->GetTotalSkillLevel(skillunique, 0, 0, &pclcharitem->clItem[0], 1);
	SI32 maxlevel = 0 ;
	
	if ( !bWeapon )
		maxlevel = GetTotalMaxLevel(skillunique);
	else maxlevel = GetMaxLevel(skillunique) ;

	if(level)
	{
		StringCchPrintf(pclSkillInfo[skillunique]->szSkillTitle, MAX_SKILL_NAME_LENGTH, TEXT("%s(%d/%d)"), pclSkillInfo[skillunique]->szName, level, maxlevel);
	}
	else
	{
		TCHAR* pText = GetTxtFromMgr(674);
		StringCchPrintf(pclSkillInfo[skillunique]->szSkillTitle, MAX_SKILL_NAME_LENGTH, pText, pclSkillInfo[skillunique]->szName);
	}
}

void cltSkillManager::MakeWeaponSkillTitle(cltPSkillInfo* pclskillmanager, cltPItemInfo* pclcharitem, SI32 skillunique)
{
	if(pclskillmanager == NULL)return ;

	SI32 level  = pclskillmanager->GetTotalSkillLevel(skillunique, 0, 0, &pclcharitem->clItem[0], 1);
	SI32 maxlevel = GetMaxLevel(skillunique);

	if(level)
	{
		StringCchPrintf(pclSkillInfo[skillunique]->szSkillTitle, MAX_SKILL_NAME_LENGTH, TEXT("%s(%d/%d)"), pclSkillInfo[skillunique]->szName, level, maxlevel);
	}
	else
	{
		TCHAR* pText = GetTxtFromMgr(674);
		StringCchPrintf(pclSkillInfo[skillunique]->szSkillTitle, MAX_SKILL_NAME_LENGTH, pText, pclSkillInfo[skillunique]->szName);
	}
}


// skillunique�� �ٰŷ� ��ų�� �̸��� ���´�.
bool cltSkillManager::GetSkillName(SI32 skillunique, TCHAR* buffer)
{
	if(skillunique <= 0 || skillunique >= MAX_SKILL_NUMBER )
	{
		return FALSE; 
	}

	if (pclSkillInfo[skillunique]==NULL)
		return FALSE;

    MStrCpy(buffer, pclSkillInfo[skillunique]->szName, MAX_SKILL_NAME_LENGTH );
	
	return TRUE;
}

bool cltSkillManager::GetWeaponSkillNeedSkillPoint( IN SI32 siSkillUnique, IN SI32 siSkillLevel, OUT SI32* psiNeedSkillPoint )
{
	if ( (0 >= siSkillUnique) || (MAX_SKILL_NUMBER <= siSkillUnique) )
	{
		return false;
	}

	if ( (0 >= siSkillLevel) || (MAX_WEAPONSKILL_LEVEL < siSkillLevel) )
	{
		return false;
	}

	if ( NULL == psiNeedSkillPoint )
	{
		return false;
	}

	// pclGetInfo�� ���罺ų�϶� �ٸ����� �� �� ����
	cltSkillInfo* pclGetInfo = pclSkillInfo[siSkillUnique];
	if ( NULL == pclGetInfo )
	{
		return false;
	}

	if ( SKILLTYPE_FIGHT != pclGetInfo->siSkillType )
	{
		return false;
	}

	// ���� ��ų�϶��� �θ� ���������� ������ �����;� �Ѵ�
	if ( (SKILLATB_HIDDENGRADE1 & pclGetInfo->siSkillAtb) || (SKILLATB_HIDDENGRADE2 & pclGetInfo->siSkillAtb) )
	{
		SI32 siParentSkillUnique = pclGetInfo->siParentRef;

		if ( (0 >= siParentSkillUnique) || (MAX_SKILL_NUMBER <= siParentSkillUnique) )
		{
			return false;
		}

		pclGetInfo = pclSkillInfo[siParentSkillUnique];
		if ( NULL == pclGetInfo )
		{
			return false;
		}
	}

	if ( NULL == pclGetInfo->pclWeaponSkillInfo )
	{
		return false;
	}

	SI32				siRealWeaponSkillIndex	= siSkillLevel-1; // ������ 0���� �����ϱ⶧���� -1�� ���ش�
	cltWeaponSkillInfo*	pclGetWeaponInfo		= pclGetInfo->pclWeaponSkillInfo[siRealWeaponSkillIndex];
	if ( NULL == pclGetWeaponInfo )
	{
		return false;
	}

	*psiNeedSkillPoint = pclGetWeaponInfo->siNeedSkillPoint;

	return true;
}

SI32 cltSkillManager::IsChanged()
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	
	if( id == 0 )
	{
		return false;
	}
	
	for ( SI32 i = 1; i < MAX_SKILL_NUMBER; ++i )
	{
		if(pclSkillInfo[i] != NULL)
		{
			SI32 TotalSkillLevel = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( pclSkillInfo[i]->siUnique, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0] );
			if ( m_si32SkillLevel[ i ] != TotalSkillLevel )
			{
				return i;
			}
		}
	}

	return false;
}

// Ʈ���� �˻��ؼ� �����͸� �����Ѵ�.
bool cltSkillManager::FindTreeData( HWND hDlg, HTREEITEM hNow, TV_ITEM *pFindItem, SI32 Param )
{
	hNow = TreeView_GetRoot( GetDlgItem( hDlg, IDC_TREE_SKILL) );	

	while( hNow )
	{
		if ( FindChildTreeData( hDlg, hNow, pFindItem, Param ) )
		{
			return true;
		}
		else
		{
			hNow = TreeView_GetNextItem( GetDlgItem(hDlg, IDC_TREE_SKILL), hNow, TVGN_NEXT );
		}
	}

	return false;
}

// ���ϵ� Ʈ���� �˻�
bool cltSkillManager::FindChildTreeData( HWND hDlg, HTREEITEM hChild, TV_ITEM *pFindItem, SI32 Param )
{
	while( hChild )
	{
		pFindItem->hItem = hChild;

		if( TreeView_GetItem( GetDlgItem( hDlg, IDC_TREE_SKILL ), pFindItem ) == TRUE )
		{
			if ( pFindItem->lParam == Param )
			{
				m_hNow = hChild;
				return true;
			}
		}

		hChild = TreeView_GetNextItem( GetDlgItem(hDlg, IDC_TREE_SKILL), hChild, TVGN_CHILD );
	}

	return false;
}

// skillunique�� �ٰŷ� �ִ� ��ų ������ ���Ѵ�. 
SI32 cltSkillManager::GetMaxLevel(SI32 skillunique)
{
	if(skillunique <= 0)return 0;
	if(pclSkillInfo[skillunique] == NULL)return 0;
	return pclSkillInfo[skillunique]->siMaxSkillLevel;
}

// skillunique�� �ٰŷ� �ִ� ���轺ų ������ ���Ѵ�. 
SI32 cltSkillManager::GetMaxExpLevel(SI32 skillunique)
{
	return MAX_SKILL_LEVEL;
}


// �θ� ����� ���۷����� ���Ѵ�. 
SI32 cltSkillManager::GetParentSkillRef(SI32 skillunique)
{
	if(skillunique <= 0)
	{
		return 0;
	}
	
	return pclSkillInfo[skillunique]->siParentRef;
}

// ��ų�� ������ ���õ� ��ų�ΰ�?
bool cltSkillManager::IsManufactureSkill(SI32 skillunique)
{
	if(skillunique <= 0)					return false;
	if(skillunique >= MAX_SKILL_NUMBER)		return false;

	if(pclSkillInfo[skillunique] == NULL)	return false;

	
	// �ƹ�Ÿ ������ �ϰ��, ��ų ����Ʈ�� ���� ���Ѿ� �Ѵ�.<������>
	switch(skillunique)
	{
		case SKILL_MAKEAVATAR_DRESS :
		case SKILL_MAKEAVATAR_HAT :
		case SKILL_MAKEAVATAR_MANTLE :
		case SKILL_MAKEAVATAR_RING :
		case SKILL_MAKEAVATAR_NECK :

		case SKILL_ARTIFACT :
			return false;
	}

	bool	bRet = false;
	switch(pclSkillInfo[skillunique]->siSkillType)
	{
	//case SKILLTYPE_WEAR:			// ������ۼ�  
	//case SKILLTYPE_ACCESSARY:		// ��ű����ۼ�
	//case SKILLTYPE_MAKEWEAPON:		// �������ۼ�
	//case SKILLTYPE_MAKETOOL:		// �������ۼ�
	//	{
	//		bRet = true;
	//	}
	//	break;
	//case SKILLTYPE_SEA:				// �ؾ���
	//	{
	//		if(skillunique == SKILL_MAKETOOL1)		bRet= true;
	//	}
	//	break;
	//case SKILLTYPE_HARVEST:			// �⺻�����
	//	{
	//		if(skillunique == SKILL_MAKEMED)		bRet= true;
	//		if(skillunique == SKILL_MAKEFOOD)		bRet= true;
	//	}
	//	break;
	//case SKILLTYPE_MAKEAVATAR:		// [����] �ƹ�Ÿ������ ���ۼ�
	//	{
	//		if(skillunique == SKILL_MAKEAVATAR_DRESS)	bRet=true;
	//		if(skillunique == SKILL_MAKEAVATAR_HAT)		bRet=true;
	//		if(skillunique == SKILL_MAKEAVATAR_MANTLE)	bRet=true;
	//		if(skillunique == SKILL_MAKEAVATAR_RING)	bRet=true;
	//		if(skillunique == SKILL_MAKEAVATAR_NECK)	bRet=true;
	//	}
	//	break;

	//	[��ȣ_SKILLINTERFACE]
		case SKILLTYPE_R_MAKEWEAPON:	// �������ۼ�
		case SKILLTYPE_R_ARMOR:			// �����ۼ�
		case SKILLTYPE_R_MAKEHARVEST:	// ���� ���ۼ�	
		case SKILLTYPE_R_MAKECLOTH:		// ��ܼ�
		case SKILLTYPE_R_MAKEACCESSARY:	// �Ǽ��縮���ۼ�
		{
			bRet = true;
		}
		break;
	}

	return bRet;
}

// NSKillDlg.ddf �� editbox_SkillStatus �ǿ� ��������� ���ش�.
void cltSkillManager::SetSkillExplainText( SI16 CurBaseSkillLevel, SI16 MaxBaseSkillLevel, SI16 ExpSkillLevel, SI16 MaxExpSkillLevel, SI32 CurExp, SI32 NextExp )
{
	cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[1];

	TCHAR Buffer[ 512 ] =  TEXT("");


	SI32 skillexp = 0;
	if(CurrentSkillUnique >= 0)
	{
		skillexp   = pclchar->pclCI->clCharSkill.clSkill[CurrentSkillUnique].siSkillExp;
	}
	
	SI32 explevel	= pclchar->pclCI->clCharSkill.GetSkillExpLevel(CurrentSkillUnique);

	TCHAR* pText = GetTxtFromMgr(675);

	StringCchPrintf( Buffer, 512, pText,
		pclchar->pclCI->clCharSkill.GetSkillLevel(CurrentSkillUnique),
		GetMaxLevel(CurrentSkillUnique),
		pclClient->pclItemManager->GetUpgradeSkillLevel(&pclchar->pclCI->clCharItem.clItem[0], CurrentSkillUnique,1),
		explevel,
		GetMaxExpLevel(CurrentSkillUnique),
		skillexp,
		GetRequiredSkillExpForLevel(explevel + 1));

	SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SKILLPOINT_EXPLAIN ), Buffer );

	return;
}

bool cltSkillManager::IsUpgradeWeaponSkill(SI32 unique,SI32 level,SI32 id)
{
	cltCharCommon* pclchar = pclClient->pclCM->CR[id];
	if ( pclchar == NULL ) return false ;

	if ( level < 1 || level > MAX_WEAPONSKILL_LEVEL ) return false ;
	if ( unique <= 0 || unique >= MAX_SKILL_NUMBER ) return false ;
	if ( pclSkillInfo[unique]->pclWeaponSkillInfo == NULL ) return false ;

	if ( pclSkillInfo[unique] == NULL ) return false ;
	cltWeaponSkillInfo * pclinfo = pclSkillInfo[unique]->pclWeaponSkillInfo[level-1] ;
	if ( pclinfo == NULL ) return false ;

	if ( unique != pclinfo->siUnique ) return false ;
	if ( pclchar->pclCI->clCharSkill.GetSkillLevel(unique) != level - 1 ) return false ;

	// �������ѿ� �ɸ���
	if ( pclchar->pclCI->clIP.GetLevel() < pclinfo->siLimitLevel ) return false ;

	SI32 basicskill = FindSkillUniqueFromWeaponSkillType( pclSkillInfo[unique]->siWeaponType );
	if ( 0 >= basicskill )	return false;

	// �⺻��ų ���� �Ѿ���
	if ( pclchar->pclCI->clCharSkill.GetSkillLevel(basicskill) + pclchar->pclCI->clCharSkill.GetSkillExpLevel(basicskill)
		< pclinfo->siBasicSkillLimitLevel ) return false ;

	// �߰����� ��ų �Ѿ���
	if ( pclSkillInfo[pclinfo->siLimitSkillUnique] )
	{
		if ( pclchar->pclCI->clCharSkill.GetSkillLevel(pclinfo->siLimitSkillUnique) + pclchar->pclCI->clCharSkill.GetSkillExpLevel(pclinfo->siLimitSkillUnique)
			< pclinfo->siSkillLimitLevel )
			return false ;
	}

	return true ;
}

bool cltSkillManager::IsUpgradeHiddenWeaponSkill( SI32 siSkillUnique, SI32 siLevel, SI32 siCharID )
{
	cltCharCommon* pclchar = pclClient->pclCM->GetChar( siCharID );
	if ( NULL == pclchar )
	{
		return false;
	}

	if ( (0 >= siLevel) || (MAX_WEAPONSKILL_LEVEL < siLevel) )				return false;
	if ( (0 >= siSkillUnique) || (MAX_SKILL_NUMBER <= siSkillUnique) )		return false;
	if ( NULL == pclSkillInfo[siSkillUnique] )								return false;

	SI32 siSkillATB		= pclSkillInfo[siSkillUnique]->siSkillAtb;
	SI32 siWeaponType	= pclSkillInfo[siSkillUnique]->siWeaponType;
	SI32 siParentUnique	= pclSkillInfo[siSkillUnique]->siParentRef;
	if ( (0 >= siParentUnique) || (MAX_SKILL_NUMBER <= siParentUnique) )	return false;

	if ( NULL == pclSkillInfo[siParentUnique]->pclWeaponSkillInfo )			return false;
	
	SI32 siRealWeaponSkillInfoIndex = siLevel - 1;
	cltWeaponSkillInfo* pclWeaponSkill = pclSkillInfo[siParentUnique]->pclWeaponSkillInfo[siRealWeaponSkillInfoIndex];
	if ( NULL == pclWeaponSkill )											return false;

	// �� ���� 1�̻��̾�� ��� �� �ִ�
	if ( 0 >= pclWeaponSkill->siHiddenSkillGrade )
	{
		return false;
	}

	// ���� ������ ������ �ϴ� �������� -1�� �Ѱ��� ���ؼ� �ٸ��ٸ� �̻��Ѱ� �̴ϱ� ����
	SI32 siWeaponSkillLevel = pclchar->pclCI->clCharSkill.GetSkillLevel( siSkillUnique );
	if ( siWeaponSkillLevel != (siLevel-1) )
	{
		return false;
	}

	// ���� ���� �˻�
	SI32 siCharLevel = pclchar->pclCI->clIP.GetLevel();
	if ( siCharLevel < pclWeaponSkill->siHiddenLimitLevel )
	{
		return false;
	}

	// ���������� �ش��ϴ� �⺻���� ��ų Ÿ���� �����´�
	SI32 siBasicSkillType = FindSkillUniqueFromWeaponSkillType( pclSkillInfo[siSkillUnique]->siWeaponType );
	if ( 0 >= siBasicSkillType )
	{
		return false;
	}

	// ������ ������ ��ų ����ġ�� �ø� �����θ� ��� �� �ִ�(å�� ����)
	SI32 siSkillLevel = pclchar->pclCI->clCharSkill.GetSkillExpLevel( siBasicSkillType );
	if ( siSkillLevel < pclWeaponSkill->siHiddenLimitSkillLevel )
	{
		return false;
	}

	// ���� ������ �ϴ� ������ ���� ������ �ٸ� ���� ��ų�� ������� �˻�
	cltSkillInfo* pclGetInfo = NULL;
	for ( SI32 siIndex = 1; siIndex < MAX_SKILL_NUMBER; ++siIndex )
	{
		if ( siIndex == siSkillUnique )						continue;

		pclGetInfo = pclSkillInfo[siIndex];
		if ( NULL == pclGetInfo )							continue;
		if ( siWeaponType != pclGetInfo->siWeaponType )		continue;

		if ( siSkillATB & pclGetInfo->siSkillAtb )
		{
			if ( 0 < pclchar->pclCI->clCharSkill.GetSkillLevel(siIndex) )
			{
				return false;
			}
		}
	}

	// ��~ �� ��ֹ����� �� ��� �ϴٴ� ����ϴ� �հ�!
	return true;

}

bool cltSkillManager::GetHiddenWeaponSkillItem( SI32 siSkillUnique, SI32 siLevel, cltItem* pclGetItem )
{
	if ( (0 >= siSkillUnique) || (MAX_SKILL_NUMBER <= siSkillUnique) )
	{
		return false;
	}

	if ( (0 >= siLevel) || (MAX_WEAPONSKILL_LEVEL < siLevel) )
	{
		return false;
	}

	if ( NULL == pclGetItem )
	{
		return false;
	}

	cltSkillInfo* pclGetInfo = pclSkillInfo[siSkillUnique];
	if ( NULL == pclGetInfo )
	{
		return false;
	}

	if ( !(SKILLATB_HIDDENGRADE1 & pclGetInfo->siSkillAtb) && !(SKILLATB_HIDDENGRADE2 & pclGetInfo->siSkillAtb) )
	{
		return false;
	}

	SI32 siParentUnique = pclGetInfo->siParentRef;
	if ( (0 >= siParentUnique) || (MAX_SKILL_NUMBER <= siParentUnique) )
	{
		return false;
	}

	pclGetInfo = pclSkillInfo[siParentUnique];
	if ( NULL == pclGetInfo )
	{
		return false;
	}

	if ( SKILLTYPE_FIGHT != pclGetInfo->siSkillType )
	{
		return false;
	}

	if ( NULL == pclGetInfo->pclWeaponSkillInfo )
	{
		return false;
	}

	SI32 siRealWeaponSkillIndex = siLevel - 1;
	cltWeaponSkillInfo* pclWeaponSkill = pclGetInfo->pclWeaponSkillInfo[siRealWeaponSkillIndex];
	if ( NULL == pclWeaponSkill )
	{
		return false;
	}

	if ( 0 >= pclWeaponSkill->siHiddenSkillGrade )
	{
		return false;
	}

	SI32 siGetItemUnique	= pclWeaponSkill->siItemUnique;
	SI32 siGetItemNum		= pclWeaponSkill->siItemNum;

	if ( (0 >= siGetItemUnique) || (0 >= siGetItemNum) )
	{
		return false;
	}

	cltItem clGetItem;
	clGetItem.Init();

	SI16 siRareSwitch = 0;
	if ( false == pclClient->pclItemManager->MakeRandItemUnique(siGetItemUnique, &clGetItem, 0, 0, &siRareSwitch) )
	{
		return false;
	}

	clGetItem.SetItemNum( siGetItemNum );

	pclGetItem->Set( &clGetItem );

	return true;
}

SI32 cltSkillManager::GetWeaponSkillRate( IN SI32 siSkillUnique, IN SI32 siSkillLevel )
{
	if ( (0 >= siSkillUnique) || (MAX_SKILL_NUMBER <= siSkillUnique) )
	{
		return 0;
	}

	if ( ( 0 >= siSkillLevel) || (MAX_WEAPONSKILL_LEVEL < siSkillLevel) )
	{
		return 0;
	}

	cltSkillInfo* pclGetInfo = pclSkillInfo[siSkillUnique];
	if ( NULL == pclGetInfo )
	{
		return 0;
	}

	if ( (SKILLATB_HIDDENGRADE1 & pclGetInfo->siSkillAtb) || (SKILLATB_HIDDENGRADE2 & pclGetInfo->siSkillAtb) )
	{
		SI32 siParentSkillUnique = pclGetInfo->siParentRef;
		if ( (0 >= siParentSkillUnique) || (MAX_SKILL_NUMBER <= siParentSkillUnique) )
		{
			return 0;
		}

		pclGetInfo = pclSkillInfo[siParentSkillUnique];
		if ( NULL == pclGetInfo )
		{
			return 0;
		}
	}

	if ( SKILLTYPE_FIGHT != pclGetInfo->siSkillType )
	{
		return 0;
	}

	if ( NULL == pclGetInfo->pclWeaponSkillInfo )
	{
		return 0;
	}

	SI32 siRealWeaponSkillIndex = siSkillLevel-1;
	cltWeaponSkillInfo* pclGetWeapon = pclGetInfo->pclWeaponSkillInfo[siRealWeaponSkillIndex];
	if ( NULL == pclGetWeapon )
	{
		return 0;
	}

	return pclGetWeapon->siApplyPercent;

}
/*
SI32 cltSkillManager::GetWeaponSkillRate(SI32 type , SI32 level)
{
	if ( level <= 0 || level > MAX_WEAPONSKILL_LEVEL ) return 0 ;

	if ( type == MAX_WEAPONSKILL_POW1 ) // 20% , 2
	{
		SI32 rate[MAX_WEAPONSKILL_LEVEL] = {3,5,8,12,20} ;

		return rate[level-1] ;
	}
	else if ( type == MAX_WEAPONSKILL_POW2 ) // 30% , 3
	{
		SI32 rate[MAX_WEAPONSKILL_LEVEL] = {3,7,12,18,30} ;

		return rate[level-1] ;
	}
	else if ( type == MAX_WEAPONSKILL_POW3 ) // 40% , 4
	{
		SI32 rate[MAX_WEAPONSKILL_LEVEL] = {10,15,22,30,40} ;

		return rate[level-1] ;
	}

	return 0 ;
}
*/
void cltSkillManager::GetWeaponSkillExplain( IN SI32 siUnique, IN SI32 siNextLevel, OUT TCHAR * pszExplain )
{
	if ( (0 >= siUnique) || (MAX_SKILL_NUMBER <= siUnique) )
	{
		return;
	}

	if ( (0 >= siNextLevel) || (MAX_WEAPONSKILL_LEVEL < siNextLevel) )
	{
		return;
	}


	if ( NULL == pszExplain )
	{
		return;
	}
	
	cltSkillInfo* pclGetInfo = pclSkillInfo[siUnique];
	if ( NULL == pclGetInfo )
	{
		return;
	}

	SI32 siBasicSkillUnique = FindSkillUniqueFromWeaponSkillType( pclGetInfo->siWeaponType );
	if ( (0 >= siBasicSkillUnique) || (MAX_SKILL_NUMBER <= siBasicSkillUnique) )
	{
		return;
	}

	bool bHiddenSkill	= false;

	SI32 siGetATB		= pclGetInfo->siSkillAtb;
	if ( (SKILLATB_HIDDENGRADE1 & siGetATB) || (SKILLATB_HIDDENGRADE2 & siGetATB) )
	{
		bHiddenSkill = true;

		SI32 siParentUnique = pclGetInfo->siParentRef;
		if ( (0 >= siParentUnique) || (MAX_SKILL_NUMBER <= siParentUnique) )
		{
			return;
		}

		pclGetInfo = pclSkillInfo[siParentUnique];
		if ( NULL == pclGetInfo )
		{
			return;
		}
	}

	if ( NULL == pclGetInfo->pclWeaponSkillInfo )
	{
		return;
	}

	// ������ 1���� ���������� �ε����� 0���� �����̹Ƿ� -1�� ���ش�
	SI32 siWeaponRealIndex = siNextLevel - 1;
	cltWeaponSkillInfo * pclWeapon = pclGetInfo->pclWeaponSkillInfo[siWeaponRealIndex];
	if ( NULL == pclWeapon )
	{
		return;
	}

	// ���� ������� ��ų �̸�
	TCHAR szSkillName[MAX_SKILL_NAME_LENGTH] = TEXT("");
	if ( false == GetSkillName(siBasicSkillUnique, szSkillName) )
	{
		return;
	}
	
	NTCHARString256 strBuffer = TEXT("");

	// ���� ��������
	if ( true == bHiddenSkill )
	{
		NTCHARString128 strLevelLimit = GetTxtFromMgr( 9797 );
		strLevelLimit.Replace( TEXT("#level#"), SI32ToString(pclWeapon->siHiddenLimitLevel) );
		strBuffer += strLevelLimit;

		NTCHARString256 strNeedSkill = GetTxtFromMgr( 9798 );
		strNeedSkill.Replace( TEXT("#skillname#"),	szSkillName );
		strNeedSkill.Replace( TEXT("#skilllevel#"),	SI32ToString(pclWeapon->siHiddenLimitSkillLevel) );
		strBuffer += TEXT("\r\n");
		strBuffer += strNeedSkill;
	}
	// �Ϲ� ��������
	else
	{
		NTCHARString128 strLevelLimit = GetTxtFromMgr( 9797 );
		strLevelLimit.Replace( TEXT("#level#"), SI32ToString(pclWeapon->siLimitLevel) );
		strBuffer += strLevelLimit;

		NTCHARString256 strNeedSkill = GetTxtFromMgr( 9798 );
		strNeedSkill.Replace( TEXT("#skillname#"),	szSkillName );
		strNeedSkill.Replace( TEXT("#skilllevel#"),	SI32ToString(pclWeapon->siBasicSkillLimitLevel) );
		strBuffer += TEXT("\r\n");
		strBuffer += strNeedSkill;
		
		// �߰����� ���� �ؽ�Ʈ
		SI32 siLimitSkillUnique = pclWeapon->siLimitSkillUnique;
		if ( (0 < siLimitSkillUnique) && (MAX_SKILL_NUMBER > siLimitSkillUnique) && (NULL != pclSkillInfo[siLimitSkillUnique]) )
		{
			TCHAR szLimitSkillName[MAX_SKILL_NAME_LENGTH] = TEXT("");
			if ( true == GetSkillName(siLimitSkillUnique, szLimitSkillName) )
			{
				NTCHARString256 strLimitSkill = GetTxtFromMgr( 9799 );
				strLimitSkill.Replace( TEXT("#skillname#"),	szLimitSkillName );
				strLimitSkill.Replace( TEXT("#skilllevel#"),SI32ToString( pclWeapon->siSkillLimitLevel ) );
				strBuffer += TEXT("\r\n");
				strBuffer += strLimitSkill;
			}
		}
	}

	MStrCpy( pszExplain, strBuffer, 256 );

	return ;
}

// level�� �ʿ��� ����ġ ��. (1���� �����Ѵ�.)
SI32 GetRequiredSkillExpForLevel(SI32 level)
{
	if(level < 1)								return 0;
	if(level >= ExpForSkillLevelUp.GetSize())	return 0;

	return ExpForSkillLevelUp[level][1];
}

// ��� ����ġ�� �ٰŷ� ���跹���� ���Ѵ�. 
SI32 GetSkillLevelFromExp(SI32 exp)
{
	//KHY - 0820 - 0~70���� �� 71�ܰ�. 70�������Ĵ� ����ġ�� ����.
	for(SI32 i = 0; i < ExpForSkillLevelUp.GetSize(); i++)
	{
		if(ExpForSkillLevelUp[i][1] > exp)
			return (i - 1);
	}

	if(i >= ExpForSkillLevelUp.GetSize())
		return MAX_SKILL_LEVEL;

	return 0;
}

BOOL LoadSkillExpData()
{
	FILE	*fp;

	SI32	data;
	TCHAR	buffer[1024 * 100];
	TCHAR	delimiter[] = TEXT("`\t\n");
	TCHAR	*pToken = NULL;
	INT		index;

	//----------------------------------
	// ����ġ�� ���Ѵ�. 
	//----------------------------------
	NFile file; 

	file.LoadFile( TEXT("SkillLevelUpExp.dat") );

	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{

		NLoadCryptFile( TEXT("SkillLevelUpExp.dat"),  (BYTE*)buffer );
		buffer[ pHeader->dwDataSize ] = NULL;

		TCHAR *pStart = &buffer[ 0 ];
		DWORD pos = 0;
		int lc = 0;

		while( pos < pHeader->dwDataSize && lc < 4 ) 
		{

			if( buffer[ pos ] == 13 ) { ++lc; pos+=2; }
			else ++pos;
		}

		lc = 0;
		pStart = &buffer[ pos ];
		//KHY - 0820 - 0~70���� �� 71�ܰ�. 70�������Ĵ� ����ġ�� ����.
		while( pos < pHeader->dwDataSize && lc < ExpForSkillLevelUp.GetSize() ) 
		{
			if( buffer[ pos ] == 13 ) 
			{ 
				pos+=2; pStart = &buffer[ pos ]; 
				_stscanf(pStart, TEXT("%d %d %d %d"), &ExpForSkillLevelUp[lc][0], &ExpForSkillLevelUp[lc][1], &ExpForSkillLevelUp[lc][2], &data);
				++lc; 
			}
			else ++pos;
		}


	} 
	else 
	{
  
		if ( (fp = _tfopen(TEXT("SkillLevelUpExp.dat"), TEXT("rt"))) == NULL )
		{
			MsgBox(TEXT("Error"), TEXT("File Open Error"), buffer);
			return FALSE;
		}

		// ù��° 5���� �����Ѵ�. 
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);

		index = 0;

		while( _fgetts(buffer, 1024, fp) != NULL)
		{ 
			if( index >= ExpForSkillLevelUp.GetSize())	break;

			_stscanf(buffer, TEXT("%d %d %d %d"), &ExpForSkillLevelUp[index][0], &ExpForSkillLevelUp[index][1], &ExpForSkillLevelUp[index][2], &data);
			index++;
		}

		fclose(fp);
	}

	return TRUE;
	
}


// ��ų ������ ���� �䱸�Ǵ� ������ �Ҹ� ���Ѵ�. 
SI32 GetWasteDurability(SI32 skilllevel)
{
	SI32 advdur = 0;

	if(skilllevel > 33)
	{
		advdur += (SI32)(((float)((skilllevel - 33)) * 2.8f / 10.0f));
		skilllevel = 33;
	}
	if(skilllevel > 30)
	{
		advdur += (skilllevel - 30) * 5 / 10;
		skilllevel = 30;
	}
	if(skilllevel > 20)
	{
		advdur += (skilllevel - 20) * 9 / 10;
		skilllevel = 20;
	}
	if(skilllevel > 10)
	{
		advdur += (skilllevel - 10) * 14 / 10;
		skilllevel = 10;
	}
	advdur += (skilllevel * 20 / 10);	// ��ų�� 2.0�� ����.. 
	
	return  max(2, MIN_DUR_FOR_REPAIR - advdur );	
	
}


SI32 ConvertTextToSkillUnique( TCHAR* pszSkillUnique )
{
	///////////////////////////////// ����ũ �� �� ��ũ��////////////////////////////////////
	#define SKILLUNIQUE_TEXT_TO_UNIQUE( text, unique ) \
	{	if ( 0 == _tcscmp(text, #unique) )	return unique;	}
	///////////////////////////////// ����ũ �� �� ��ũ��////////////////////////////////////

	if ( NULL == pszSkillUnique )
	{
		return 0;
	}

	if ( 0 == _tcslen(pszSkillUnique) )
	{
		return 0;
	}

	if ( 0 == _tcscmp(pszSkillUnique, TEXT("NULL")) )
	{
		return 0;
	}

	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEMED );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEFOOD );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEARMOUR1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEHELMET1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKESWORD1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKESPEAR1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEAXE1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKESTAFF1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEBOW1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEGUN1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKESHOES1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEBELT1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEDRESS1 ); //
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_USESWORD1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_USESPEAR1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_USEBOW1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_USEAXE1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_USEGUN1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_USESTAFF1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SUMMON );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_FISH );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_HORSETRAINING	 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEIRON1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_CAPTURE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEHAT1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_FARM );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MINE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_INCDR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_INCVIT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_INCMAGAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_INCDR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_INCVIT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_INCMAGAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_INCAC );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_DOUBLEAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_INCMAGAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_DECGAP );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_INDURE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_INCCRI );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_DRAIN );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_INCRANGE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_INCMAGAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_INCPHYAR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_DECMAGDELAY );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_INCWEAAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_INCMAG );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_DECUSEMANA );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_INCMAGAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKETOOL1 );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_ARTIFACT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_SPEAR_INCAC );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_AXE_DECGAP );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_BOW_DRAIN );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_GUN_INCPHYAR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_STAFF_INCMAG );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_SPEAR_DOUBLEAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_AXE_INDURE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_BOW_INCRANGE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_GUN_DECMAGDELAY );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SWORD_STAFF_DECUSEMANA );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_SWORD_INCDR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_AXE_DECGAP );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_BOW_DRAIN );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_GUN_INCPHYAR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_STAFF_INCMAG );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_SWORD_INCVIT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_AXE_INDURE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_BOW_INCRANGE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_GUN_DECMAGDELAY );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_SPEAR_STAFF_DECUSEMANA );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_SWORD_INCDR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_SPEAR_INCAC );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_BOW_DRAIN );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_GUN_INCPHYAR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_STAFF_INCMAG );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_SWORD_INCVIT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_SPEAR_DOUBLEAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_BOW_INCRANGE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_GUN_DECMAGDELAY );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_AXE_STAFF_DECUSEMANA );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_SWORD_INCDR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_SPEAR_INCAC );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_AXE_DECGAP );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_GUN_INCPHYAR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_STAFF_INCMAG );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_SWORD_INCVIT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_SPEAR_DOUBLEAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_AXE_INDURE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_GUN_DECMAGDELAY );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_BOW_STAFF_DECUSEMANA );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_SWORD_INCDR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_SPEAR_INCAC );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_AXE_DECGAP );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_BOW_DRAIN );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_STAFF_INCMAG );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_SWORD_INCVIT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_SPEAR_DOUBLEAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_AXE_INDURE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_BOW_INCRANGE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_GUN_STAFF_DECUSEMANA );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_SWORD_INCDR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_SPEAR_INCAC );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_AXE_DECGAP );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_BOW_DRAIN );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_GUN_INCPHYAR );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_SWORD_INCVIT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_SPEAR_DOUBLEAT );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_AXE_INDURE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_BOW_INCRANGE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_STAFF_GUN_DECMAGDELAY );

	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEAVATAR_DRESS );			//	[��ȣ]	�ƹ�Ÿ �Ǻ� ���ۼ�
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEAVATAR_HAT );				//	[��ȣ]	�ƹ�Ÿ ���� ���ۼ�
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEAVATAR_MANTLE );			//	[��ȣ]	�ƹ�Ÿ ���� ���ۼ�
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEAVATAR_RING );			//	[��ȣ]	�ƹ�Ÿ ���� ���ۼ�
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, SKILL_MAKEAVATAR_NECK );			//	[��ȣ]	�ƹ�Ÿ ����� ���ۼ�

	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, ALL_MAKESKILL_UNIQUE );			// ����
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, ALL_WEAPONSKILL_UNIQUE );	
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, ALL_PRODUCTSKILL_UNIQUE );	// ����
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, ALL_ALLSKILL_UNIQUE );
	SKILLUNIQUE_TEXT_TO_UNIQUE( pszSkillUnique, ALL_ALLAVATARSKILL_UNIQUE );   // ��� �ƹ�Ÿ ��ų
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ο� ����ũ�� �� ���� �߰��� �ּ���
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	NTCHARString256 strText( pszSkillUnique );
	NTCHARString64	strCaption( _T("Error") );

	strText += _T(" Unique Not Found");

	MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
#endif

	return 0;

}


//	[��ȣ] ��ųŸ���� ����ũ(�� �з�) �� ���ɴϴ�.
SI32 ConvertTextToSkillTypeUnique(TCHAR* pszSkillUnique)
{
	///////////////////////////////// ����ũ �� �� ��ũ��////////////////////////////////////
#define SKILLUNIQUE_TEXT_TO_UNIQUE( text, unique ) \
	{	if ( 0 == _tcscmp(text, #unique) )	return unique;	}
	///////////////////////////////// ����ũ �� �� ��ũ��////////////////////////////////////

	if ( NULL == pszSkillUnique )
		return 0;

	if ( 0 == _tcslen(pszSkillUnique) )
		return 0;

	if ( 0 == _tcscmp(pszSkillUnique, TEXT("NULL")) )
		return 0;


	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_USEWEAPON);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_MAKEWEAPON);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_ARMOR);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_MAKEHARVEST);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_HARVEST);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_MAKECLOTH);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_MAKEACCESSARY);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_R_ETC);
	SKILLUNIQUE_TEXT_TO_UNIQUE(pszSkillUnique, SKILLTYPE_FIGHT);

	//////////////////////////////////////////////////////////////////////////
	//	����ũ �߰��� �� ���� ���ּ���.
	//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
	NTCHARString256 strText( pszSkillUnique );
	NTCHARString64	strCaption( _T("Error") );

	strText += _T(" Unique Not Found");

	MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
#endif

	return 0;

}
