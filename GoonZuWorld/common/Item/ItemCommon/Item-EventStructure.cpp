#include "Item-EventStructure.h"
#include "NDataLoader.h"

#include "../../../CommonLogic/CommonLogic.h"
#include "../../../common/Item/ItemCommon/cltItem.h"

extern cltCommonLogic* pclClient;

// ���� ������ �м��Ѵ�. 
bool cltEventStructureUnit::AnalyzeMaterial(TCHAR* pszMaterialText, cltItemManagerCommon* pclItemManager)
{
	TCHAR c;

	// �м��� ���ᰡ ����. 
	if(pszMaterialText == NULL)return false;

	SI32 itemunique = 0 ;
	TCHAR szitemname[128] =  TEXT("") ;
	SI32 itemnameindex	= 0 ;
	bool itemnameswith = false ;

	TCHAR szitemnum[128] = TEXT("") ;
	SI32 itemnumindex	= 0 ;
	bool itemnumswith = false ;

	SI32 textindex	= 0 ;

	bool unlimitloop = true;
	while( unlimitloop )
	{
		c = pszMaterialText[textindex];
		if(c == '\0')break;

		textindex++;

		// Space�� �����Ѵ�. 
		if( c == ' ')continue;
		if( c == '+')
		{
			itemnameswith = false;
			continue;
		}
		if( c == '(')
		{
			szitemname[itemnameindex] = '\0';	// �̸��� �������Ѵ�. 
			itemnameindex	= 0;

			itemunique = _tstoi(szitemname);

			itemnameswith = true;	// �̸��� ���Դ�. ������ �����۰��� ������. 
			continue;
		}
		if( c == ')')
		{
			szitemnum[itemnumindex] = '\0';		// ������ ������ �������Ѵ�. 
			itemnumindex	= 0;

			//-------------------------------------------
			// �̸��� ������ ��� �������Ƿ� �м��Ѵ�. 
			//-------------------------------------------

			// NULL�̸� �����Ѵ�. 
			if(_tcscmp(szitemname, TEXT("NULL")) == 0)return false;
			SI32 ref = pclItemManager->FindItemRefFromUnique(itemunique);

			if(ref)
			{
				SI32 itemnum	= _tstoi(szitemnum);
				// [���] �̺�Ʈ ����� ������ 5���� ������ �ø���. (09.10.23)
				if(itemnum > 0 && itemnum  <= MAX_ITEM_PILE_NUMBER + 40000)
				{
					// ��Ḧ �����Ѵ�. 
					cltMaterialInfo clmaterial(itemunique, itemnum);
					AddMaterial(&clmaterial);
				}

			}
			continue;
		}

		// �������� �̸��� ���� �������� �ʾ����� �̸��� �Է¹޴´�. 
		if(itemnameswith == false)
		{
			szitemname[itemnameindex] = c;
			itemnameindex++;
		}
		else
		{
			szitemnum[itemnumindex] = c;
			itemnumindex++;
		}

	}

	return true;
}

cltEventStructure::cltEventStructure()
{
	Init();
}

cltEventStructure::~cltEventStructure()
{
	Destroy();
}

void cltEventStructure::Init()
{
	for( SI32 i=0; i<MAX_EVENT_STRUCTURE_COUNT; i++ )
	{
		m_pclUnit[i] = NULL;
	}

	LoadFromFile();
}

void cltEventStructure::Destroy()
{
	for ( SI32 i=0; i<MAX_EVENT_STRUCTURE_COUNT; i++ )
	{
		if ( m_pclUnit[i] )
		{
			delete m_pclUnit[i];
			m_pclUnit[i] = NULL;
		}
	}
}

void cltEventStructure::LoadFromFile()
{
	BOOL bLoadFile = FALSE;
	NDataLoader	dataloader;

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/EventStructure.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/EventStructure.txt") );
	}

	if (!bLoadFile)
	{
		return;
	}

	SI32 siStructureType = 0;
	TCHAR szmaterial[128]	=	TEXT("");
	SI32 siItemUnique = 0;
	SI32 siItemNum = 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siStructureType,	4,
		NDATA_MBSTRING,	szmaterial,			128,
		NDATA_INT32,	&siItemUnique,		4,
		NDATA_INT32,	&siItemNum,			4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	SI16 index = 0;

	while( !dataloader.IsEndOfData() ) 
	{
		if ( index >= MAX_EVENT_STRUCTURE_COUNT ) break;

		if (dataloader.ReadData())	
		{
			m_pclUnit[index] = new cltEventStructureUnit();
			if(m_pclUnit[index] != NULL)
			{
				m_pclUnit[index]->m_siStructureType			= siStructureType;
				m_pclUnit[index]->AnalyzeMaterial(szmaterial, pclClient->pclItemManager);
				m_pclUnit[index]->m_siRewardItemUnique		= siItemUnique;
				m_pclUnit[index]->m_siRewardItemNum			= siItemNum;
			}

			++index;
		}
	}
}

cltEventStructureUnit* cltEventStructure::GetEventStructure( SI16 siStructureType )
{
	if( siStructureType <= 0 )			return NULL;

	for(int i=0; i<MAX_EVENT_STRUCTURE_COUNT; i++)
	{
		if(m_pclUnit[i] != NULL && m_pclUnit[i]->m_siStructureType == siStructureType)
			return m_pclUnit[i];
	}

	return NULL;
}
