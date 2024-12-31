//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
#include "CommonHeader.h"

#include "FieldObject.h"

#include "..\CommonLogic\CommonLogic.h"

//------------------------------------
// Lib
//------------------------------------
#include <Graphic.h>
#include <Graphic_Capsule.h>
#include "EtcTool\EtcTool.h"
#include "NDataloader.h"
#include "NHashTableString.h"

#include "../../../../patch/unzip.h"

extern cltCommonLogic* pclClient;

struct cltFOT
{	
	int		type;
	TCHAR	typeString[ 64 ];
	int		color;
	TCHAR	atb[ 64 ];
	TCHAR	parentType[ 64 ];
};

//-------------------------------------------------
// Field Object Type Info
//-------------------------------------------------
cltFieldObjectTypeInfo::cltFieldObjectTypeInfo(DWORD type, UI08 color, TCHAR* name, DWORD atb, cltFieldObjectTypeInfo* pclinfo)
{

	Unique		= 0;
	dwType		= type;
	uiColor		= color;
	pParent		= pclinfo;
	dwAtb		= atb;

	if(name == NULL)
	{
		MsgBox(TEXT("vc8923jf"), TEXT("vd23trf:%d"), type);
	}
	pszName		= new TCHAR [lstrlen(name) + 1];
	StringCchCopy(pszName, lstrlen(name) + 1, name);


}

cltFieldObjectTypeInfo::~cltFieldObjectTypeInfo()
{
	if(pszName)
	{
		delete[] pszName;
		pszName = NULL;
	}
}

//-------------------------------------------------
// Field Object Info
//-------------------------------------------------
cltFieldObjectInfo::cltFieldObjectInfo(SHORT unique, DWORD dwtype, DWORD dwimagefilenumber,
									   TCHAR* szname, SI32 transmode,SI32 alphavalue,SI32 shadow,TCHAR* zipname)
{
	pszName		= NULL;
	pszZipName	= NULL;

	if(unique > 30000)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("Not Proper FieldObjectSet Unique. Over 30000"), TEXT("Error"), MB_OK|MB_TOPMOST);
		Unique	= 0;
	}
	else
	{
		Unique	= unique;
	}
	
	dwType	= dwtype;

	if(szname == NULL)
	{
		MsgBox(TEXT("vdxs"), TEXT("V3fds:%d"), unique);
	}
	pszName	= new TCHAR [lstrlen(szname) + 1];
	StringCchCopy(pszName, lstrlen(szname) + 1, szname);

	pszZipName	= new TCHAR [lstrlen(zipname) + 1];
	StringCchCopy(pszZipName, lstrlen(zipname) + 1, zipname);

	siTransMode = transmode;
	if ( alphavalue < 0 || alphavalue > 8 )
		alphavalue = 8 ;
	siAlphaValue = alphavalue ;
	if ( shadow < 0 )
		shadow = 0 ;
	siTreeShadow = shadow ;

	siFOSprRef		= -1;

	// ���Ͽ��� �迭 ������ �о�´�. 
	Init();

	//TCHAR szfilename[128];
	//if(GetInfoFileName(szfilename) == true)
	//{
	//	ReadSetArrayInfo(szfilename);
	//}

	if( pclClient->GameMode != GAMEMODE_CLIENT )
	{
		// ��������� �� ������ �ϵ忡�� �о�´�.
		LoadDetailInfo();
	}

}

cltFieldObjectInfo::~cltFieldObjectInfo()
{

	if(pszName)
	{
		delete[] pszName;
		pszName = NULL;
	}

	if(pszZipName)
	{
		delete[] pszZipName;
		pszZipName = NULL;
	}

}

void cltFieldObjectInfo::Init()
{
	TileXsize	= TileYsize		= 0;
	TileCenterX	= TileCenterY	= 0;
	IndentX		= IndentY		= 0;
	AniFrame	= AniDelay		= 1;
}

bool cltFieldObjectInfo::GetInfoFileName(TCHAR* szfilename)
{
	if(szfilename == NULL)return false;

	StringCchPrintf(szfilename, 128, TEXT("FieldObject\\%s\\%s.txt"), pszName, pszName);

	return true;
}

cltFieldObjectInfo* cltFieldObjectManager::GetInfoPointer(TCHAR* szname)
{
	SI32 i;

	// "NULL"�� �ԷµǸ� NULL�� �����Ѵ�. 
	if(_tcscmp(szname, TEXT("NULL")) == 0)
		return NULL;

	for(i = 0;i < MAX_FIELDOBJECTSET_NUMBER;i++)
	{
		if(pclInfo[i])
		{
			if(_tcscmp(pclInfo[i]->pszName, szname) == 0)
			{
				return pclInfo[i];
			}
		}
	}

	return NULL;

}

// �̹����� ��� �ִ� ������ �����͸� �����Ѵ�. 
TSpr* cltFieldObjectInfo::GetSpr(cltFieldObjectManager* pFOManager, DWORD dwframe)
{
	if(siFOSprRef < 0)
	{
		//---------------------------------------
		// ���� �ε��� �Ǿ� ���� �ʴٸ� �ε��Ѵ�.
		//---------------------------------------
		pFOManager->LoadSet(dwframe, this);
	}

	// ���������� ���� �������� Ȯ���Ѵ�.  ������� �ʴ� ��쿡 �����ϱ� ���ؼ�. 
	SetLastUseFrame(pFOManager, dwframe);

	return &pFOManager->FOSpr[siFOSprRef];
}

// ���������� ���� �������� �����Ѵ�. 
void cltFieldObjectInfo::SetLastUseFrame(cltFieldObjectManager* pFOManager, DWORD frame)
{
	if(siFOSprRef < 0)return ;

	pFOManager->dwLastUseFrame[siFOSprRef] = frame;
}

// �迭 ������ �о�´�. 
bool cltFieldObjectInfo::ReadSetArrayInfo(TCHAR* szfilename)
{

	SI32 i;
	FILE* fp;
	TCHAR buffer[1024];

	fp = _tfopen(szfilename, TEXT("rt"));
	if(fp == NULL)
	{
#ifdef _DEBUG
		if (pclClient->GameMode == GAMEMODE_CLIENT) 
			MessageBox(NULL, szfilename, TEXT("File Read Error"), MB_OK|MB_TOPMOST);
#endif
		return false;
	}

	// ù��° 3���� �����Ѵ�. 
	for(i = 0;i< 3;i++)
		_fgetts(buffer, 1024, fp);

	_fgetts(buffer, 1024, fp);

	_stscanf(buffer, TEXT("%d %d %d %d %d %d %d %d"), 
			&TileXsize,		&TileYsize,
			&TileCenterX,	&TileCenterY,
			&IndentX,		&IndentY,
			&AniFrame,		&AniDelay);

	fclose(fp);

	return true;

}

bool cltFieldObjectInfo::ReadSetArrayInfoFromMemory(BYTE* pMemory)						// �迭 ������ �о�´�. 
{
	if( pMemory == NULL )				return false;

	TCHAR* pszString = (TCHAR*)pMemory;

	int ptr = 0;
	int line = 0;
	
	// ù��° 3���� �����Ѵ�. 
	//	for(i = 0;i< 3;i++)
	//		_fgetts(buffer, 1024, fp);
	while( pszString[ptr] != '\0' )
	{
		if( _tcsncmp(&pszString[ptr], "\n",   1) == 0 )			{			line++;					}
		else if( _tcsncmp(&pszString[ptr], "\r\n", 2) == 0 )	{			line++;		ptr++;		}

		ptr++;
		if( line == 3 )			break;
	}
	if( pszString[ptr] == '\0' )			return false;

	_stscanf( &pszString[ptr],	TEXT("%d %d %d %d %d %d %d %d"), 
								&TileXsize,		&TileYsize,
								&TileCenterX,	&TileCenterY,
								&IndentX,		&IndentY,
								&AniFrame,		&AniDelay);

	//_stscanf(buffer, TEXT("%d %d %d %d %d %d %d %d"), 
	//			&TileXsize,		&TileYsize,
	//			&TileCenterX,	&TileCenterY,
	//			&IndentX,		&IndentY,
	//			&AniFrame,		&AniDelay);

	return true;
}

// �迭 ������ �����Ѵ�. 
bool cltFieldObjectInfo::WriteSetArrayInfo(TCHAR* szfilename)
{
	// �迭 ������ �о�´�. 
	FILE* fp;
	TCHAR buffer[1024];

	fp = _tfopen(szfilename, TEXT("wt"));
	if(fp == NULL)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, szfilename, TEXT("File Write Error"), MB_OK|MB_TOPMOST);
		return false;
	}

	// �̸� ����. 
	StringCchPrintf(buffer, 1024, TEXT("%s\n"), pszName);
	_fputts(buffer, fp);

	
	// ����� ����. 
	_fputts(TEXT("\n"), fp);


	// �з����̺� ����. 
	StringCchPrintf(buffer, 1024, TEXT("%s %s %s %s %s %s %s %s\n"), 
			TEXT("TileXsize"),	TEXT("TileYsize"),
			TEXT("TileCenterX"),	TEXT("TileCenterY"),
			TEXT("IndentX"),		TEXT("IndentY"),
			TEXT("AniFrame"),		TEXT("AniDelay"));

	_fputts(buffer, fp);


	// ���� ������ ����. 
	StringCchPrintf(buffer, 1024, TEXT("%d %d %d %d %d %d %d %d\n"), 
			TileXsize,		TileYsize,
			TileCenterX,	TileCenterY,
			IndentX,		IndentY,
			AniFrame,		AniDelay);

	_fputts(buffer, fp);

	fclose(fp);

	return true;
}

void cltFieldObjectInfo::LoadDetailInfo()
{
	if(TileXsize != 0)	return;

	TCHAR szfilename[128];

	if(GetInfoFileName(szfilename) == true)
	{
		BOOL bCompress = FALSE;
		BYTE* pFileBuf = NULL;
		BOOL bCompressLoaded = FALSE;

		//===========================================================================================
		// ������ �������Ͽ� ����ִ�ġ üũ�Ѵ�.
		//===========================================================================================
		TCHAR szZipName[MAX_PATH] = { '\0', };
		TCHAR szRealName[MAX_PATH] = { '\0', };
		if( pszZipName != NULL )	{		StringCchPrintf( szZipName, sizeof(szZipName), "FieldObject\\%s.mz", pszZipName);		}
		if( pszName != NULL )		{		StringCchPrintf( szRealName, sizeof(szRealName), "%s/%s.txt", pszName, pszName );		}

		unzFile uf = unzOpen( szZipName );
		bool bFind = false;
		if( uf )
		{
			unz_global_info gi;
			int ret = unzGetGlobalInfo(uf, &gi);

			for( UI32 j=0; j<gi.number_entry; j++ )
			{
				TCHAR filename[MAX_PATH];
				unz_file_info file_info;
				ret = unzGetCurrentFileInfo( uf, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);

				_tcsupr(filename);
				_tcsupr(szRealName);

				if( _tcscmp( filename, szRealName ) == 0 )
				{
					bCompress = TRUE;
					pFileBuf = new BYTE[file_info.uncompressed_size + 10];		// �ؽ�Ʈ �����̹Ƿ� ���������� ���� �ش�.
					ZeroMemory(pFileBuf, file_info.uncompressed_size + 10);
					if( pFileBuf != NULL )
					{
						unzOpenCurrentFile( uf );
						UI32 nReaded = unzReadCurrentFile( uf, pFileBuf, file_info.uncompressed_size);
						if( nReaded == file_info.uncompressed_size)		bCompressLoaded = true;
						unzCloseCurrentFile( uf );
					}
					break;
				}

				ret = unzGoToNextFile(uf);
			}
			unzClose( uf );
		}
		//===========================================================================================

		if( bCompress )
		{
			if( bCompressLoaded )
			{
				ReadSetArrayInfoFromMemory( pFileBuf );
			}
			else
			{
#ifdef _DEBUG
				MessageBox( NULL, szfilename, "ERROR", MB_OK );
#endif
			}
			if( pFileBuf != NULL )		delete [] pFileBuf;
		}
		else
		{
			ReadSetArrayInfo(szfilename);
		}
	}
}


//----------------------------------------------------------------
// Field Object Brush
//---------------------------------------------------------------
cltFieldObjectBrush::cltFieldObjectBrush(TCHAR* pname)
{
	SI32 i;

	StringCchCopy(szName, MAX_PATH, pname);

	FielObjectNumber = 0;

	for(i =0; i < MAX_FIELDOBJECT_PER_BRUSH;i++)
	{
		pFieldObjectInfo[i] = NULL;
	}


}

cltFieldObjectBrush::~cltFieldObjectBrush()
{
}


BOOL cltFieldObjectBrush::Add(cltFieldObjectInfo* pfieldobjectinfo)
{
	if(pfieldobjectinfo == NULL)return FALSE;
	if(FielObjectNumber >= MAX_FIELDOBJECT_PER_BRUSH)return FALSE;

	pFieldObjectInfo[FielObjectNumber] = pfieldobjectinfo;
	FielObjectNumber++;

	return TRUE;
}

// ������ �ִ� cltFieldObjectInfo�߿��� �Ѱ��� �����ϰ� �� �� ���� unique���� �����Ѵ�. 
SI32 cltFieldObjectBrush::GetRandUnique()
{
	if(FielObjectNumber == 0)return 0;

	SI32 data = rand() % FielObjectNumber;
	return pFieldObjectInfo[data]->Unique;
}


//-----------------------------------------------------------------
// Field Object Set
//-----------------------------------------------------------------

cltFieldObjectManager::cltFieldObjectManager(SI32 gamemode)
{
	SI32 i;

	siLoadedSize	= 0;

	for( i = 0; i < MAX_FIELDOBJECTSET_NUMBER;i++)
	{
		pclInfo[i] = NULL;
	}

	for( i = 0; i < MAX_FIELDOBJECTTYPE_NUMBER;i++)
	{
		pclTypeInfo[i] = NULL;
	}

	for( i = 0; i < MAX_FIELDOBJECTBRUSH_NUMBER;i++)
	{
		pclFieldObjectBrush[i] = NULL;
	}

	for( i = 0; i < MAX_FOUNIQUE;i++)
	{
		siFORef[i] = -1;
	}

	for( i = 0; i < MAX_FOSPR_NUMBER;i++)
	{
		FOInfoUnique[i]		= 0;
		dwLastUseFrame[i]	= 0;
	}

	InitFieldObjectManager();
	InitTypeSet();
	// }

	// Field Object Type�� ���� �ʱ�ȭ�� ���Ѵ�. 
	InitSet();
	
	if(gamemode == GAMEMODE_MAPEDIT)
	{
		InitBrush();
	}
	
	SI32 a = 0;
}

bool cltFieldObjectManager::InitFieldObjectManager()
{
	return true ;
}

cltFieldObjectManager::~cltFieldObjectManager()
{
	SI32 i;

	for(i = 0;i < MAX_FIELDOBJECTSET_NUMBER;i++)
	{
		if(pclInfo[i])
		{
			delete pclInfo[i];
			pclInfo[i] = NULL;
		}
	}

	for(i = 0;i < MAX_FIELDOBJECTTYPE_NUMBER;i++)
	{
		if(pclTypeInfo[i])
		{
			delete pclTypeInfo[i];
			pclTypeInfo[i] = NULL;
		}
	}

	for(i = 0;i < MAX_FIELDOBJECTBRUSH_NUMBER;i++)
	{
		if(pclFieldObjectBrush[i])
		{
			delete pclFieldObjectBrush[i];
			pclFieldObjectBrush[i] = NULL;
		}
	}

	for(i = 0;i < MAX_FOSPR_NUMBER;i++)
	{
		if(FOSpr[i].pImage)
		{
			GP.FreeSpr( FOSpr[i] );
		}
	}
}

// �귯���� �����Ѵ�. 
BOOL cltFieldObjectManager::InitBrush()
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	SI32 index = 0;
	TCHAR name[1024];
	TCHAR fieldobject[1024];
	TCHAR buffer[1024];
	TCHAR path[1024];

	FILE* fp;

	hSrch = FindFirstFile(TEXT("FieldObject\\Brush\\*.txt"), &wfd);

	if(GetLastError())
	{
		TCHAR buffer[256];
		TCHAR text[128];
		DWORD errcode = GetLastError();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, 0, buffer,  128, NULL);
		StringCchPrintf(text, 128, TEXT("ErrorCode=%d Message=%s"), errcode, buffer);
		
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, text, TEXT("InitBrush"), MB_OK|MB_TOPMOST);
	}

	while(bResult)
	{
		StringCchPrintf(path, 1024, TEXT("FieldObject\\Brush\\%s"), wfd.cFileName);
		// ã�� ������ �о ���� �ʱ�ȭ�Ѵ�.
		fp =_tfopen(path, TEXT("rt"));
		if(fp == NULL)
		{
			TCHAR buffer[256];
			StringCchPrintf(buffer, 1024, TEXT("Cannot Find Brush File:%s"), wfd.cFileName);
			if (pclClient->GameMode != GAMEMODE_SERVER)
				MessageBox(NULL, buffer, TEXT("Error"), MB_OK|MB_TOPMOST);
			return FALSE;
		}

		// �귯���� �̸��� ���ͼ� �귯�� ��ü�� �����. 
		_fgetts(buffer, 1024, fp);
		_stscanf(buffer, TEXT("%s"), name);
		pclFieldObjectBrush[index] = new cltFieldObjectBrush(name);

		// ������ �ǳ� �ڴ�. 
		_fgetts(buffer, 1024, fp);

		while( _fgetts(buffer, 1024, fp) != NULL)
		{
			_stscanf(buffer, TEXT("%s"), fieldobject);
			pclFieldObjectBrush[index]->Add( GetInfoPointer(fieldobject) );
		}

		fclose(fp);

		// ���� �귯���� ����Ű�� �Ѵ�. 
		// �ִ� �귯�� ������ �ʰ������� ���ϰ� �Ѵ�. 
		index++;
		if(index >= MAX_FIELDOBJECTBRUSH_NUMBER)
		{
			if (pclClient->GameMode != GAMEMODE_SERVER)
				MessageBox(NULL, TEXT("Exceed Max. Brush Number"), TEXT("Error"), MB_OK|MB_TOPMOST);
			break;
		}


		bResult = FindNextFile(hSrch, &wfd);
	}

	FindClose(hSrch);

	return TRUE;
}

// Field Object Type�� �ʱ�ȭ�Ѵ�. 
BOOL cltFieldObjectManager::InitTypeSet()
{
	NDataAtbParser  atbparser;

	// FOATB ���
	atbparser.AddAtbInfo( TEXT("FOATB_VILLAGE"), FOATB_VILLAGE );
	atbparser.AddAtbInfo( TEXT("FOATB_TREE"), FOATB_TREE );
	atbparser.AddAtbInfo( TEXT("FOATB_MOUNTINE"), FOATB_MOUNTINE );
	atbparser.AddAtbInfo( TEXT("FOATB_GATE"), FOATB_GATE );
	atbparser.AddAtbInfo( TEXT("FOATB_STATUE"), FOATB_STATUE );
	atbparser.AddAtbInfo( TEXT("FOATB_BUILD"), FOATB_BUILD );
	atbparser.AddAtbInfo( TEXT("FOATB_FLOOR"), FOATB_FLOOR );
	atbparser.AddAtbInfo( TEXT("FOATB_BRIDGE"), FOATB_BRIDGE );

	cltFOT clFot[ MAX_FIELDOBJECTTYPE_NUMBER ];
	int i, index = 0;
	BOOL bLoadFile = FALSE;

	NDataLoader	dataloader;

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/FieldObjectTypeInfo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/FieldObjectTypeInfo.txt") );
	}

	if (!bLoadFile)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("FieldObjectTypeInfo Load Error"), TEXT("Error"), MB_OK|MB_TOPMOST);
		return FALSE;
	}
	
	cltFOT aFOT;

	NDataTypeInfo pDataTypeInfo[] =
	{
			NDATA_INT32,	&aFOT.type,		4,
			NDATA_MBSTRING,	aFOT.typeString,		64,
			NDATA_INT32,	&aFOT.color,		4,
			NDATA_MBSTRING,	aFOT.atb,		64,
			NDATA_MBSTRING,	aFOT.parentType,		64,
			0,0,0
	};

	dataloader.RegDataType(pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData())	
		{
			if ( aFOT.typeString[ 0 ] != NULL )
			{
				clFot[index] = aFOT;

				pclClient->pclHashTableString->Insert( clFot[index].typeString , clFot[index].type);
				index++;
			}
		}

	}

	for (i=0; i<index; i++)
	{
		int iType = -1, iAtb = -1, iParentType = -1;
		BOOL bFind = FALSE;

		bFind = pclClient->pclHashTableString->Find(clFot[i].typeString, iType);
		iAtb = atbparser.GetValueByString( clFot[i].atb );

		if (!bFind )
		{
			MsgBox(TEXT("Error"), TEXT("Not Found FieldObjectTypeInfo(%s) In HashTable"), clFot[i].typeString);
		}
				
		cltFieldObjectTypeInfo* aParentInfo;
		if( !pclClient->pclHashTableString->Find(clFot[i].parentType, iParentType) ) 
		{
			aParentInfo = NULL;
		} else {
			aParentInfo = pclTypeInfo[ iParentType ];
		}

		pclTypeInfo[clFot[i].type] = new cltFieldObjectTypeInfo(iType, clFot[i].color, clFot[i].typeString , iAtb, aParentInfo);

	}
	
	
	return TRUE;

}

BOOL cltFieldObjectManager::InitSet()
{
	BOOL bLoadFile = FALSE;
	NDataLoader	dataloader;

	SI32 unique = 0 ;
	SI32 imagenumber = 0 ;
	TCHAR type[128] = TEXT("") ;
	TCHAR name[128] = TEXT("") ;
	SI32 transmode = 0 ;
	SI32 alphavalue = 0 ;
	SI32 shadow = 0 ; // ���� �׸��ڵ�
	TCHAR zipname[128] = TEXT("") ;

	NDataTypeInfo pDataTypeInfo[] =
	{
			NDATA_INT32,	&unique,			4,
			NDATA_MBSTRING,	type,			128,
			NDATA_INT32,	&imagenumber,	4,
			NDATA_MBSTRING,	name,			128,
			NDATA_INT32,	&transmode,		4,
			NDATA_INT32,	&alphavalue, 	4,
			NDATA_INT32,	&shadow,		4,
			NDATA_MBSTRING,	zipname,		128,
			0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/FieldObjectSetInfo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/FieldObjectSetInfo.txt") );
	}
	if (!bLoadFile)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("FieldObjectSetInfo Load Error"), TEXT("Error"), MB_OK|MB_TOPMOST);
		return FALSE;
	}

	SI32 index = 0;
	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData())
		{
			if (type[ 0 ] != NULL)
			{
				BOOL bFind = FALSE;

				// type���ڿ��� �м��Ͽ� ���ڿ��� �Ǿ� �ִ� �ؽ�Ʈ�� ���ӳ����� �ǹ��ִ� ���ڷ� �����Ͽ� �����Ѵ�. 
				SI32 sitype; 

				bFind = pclClient->pclHashTableString->Find(type, sitype);

				if (!bFind )
				{
					MsgBox(TEXT("Error"), TEXT("Not Found FieldObjectSetInfo(%s) In HashTable"), type);
				}


				pclInfo[index] = new cltFieldObjectInfo(unique, sitype, imagenumber, name, transmode,alphavalue,shadow,zipname);
				if(unique > 0 && unique < MAX_FOUNIQUE)
				{
					siFORef[unique] = index;		// ���۷����� ���� �� �ֵ��� �����Ѵ�.
				}
				else
				{
					MsgBox(TEXT("vfv93jfdf"), TEXT("vsf8jfd:%d"), unique);
				}


				index++;

				// Field Object ��Ʈ�� ���� �� �ִ� �ִ� ���� �ʰ��ϸ� ���� �޽����� ������. 
				if(index >= MAX_FIELDOBJECTSET_NUMBER)
				{
					if (pclClient->GameMode != GAMEMODE_SERVER)
						MessageBox(NULL, TEXT("Warning Out of FieldObject Number"), TEXT("Warning"), MB_OK|MB_TOPMOST);
				}
			}
		}

	}

	
	return TRUE;
}

// Spr�̹����� ������ �� ������ ã�´�. 
SI32 cltFieldObjectManager::FindEmptySpr()
{
	SI32 i;
	DWORD lastframe = 0xffffffff;
	SI32 lastref	= -1;

	// ���� ������ �������� ã�´�. 
	for(i = 0;i < MAX_FOSPR_NUMBER;i++)
	{
		if(FOSpr[i].pImage == NULL)return i;

		if(dwLastUseFrame[i] <= lastframe)
		{
			lastframe	= dwLastUseFrame[i];
			lastref		= i;
		}
	}
	return lastref;
}

// ���� ������ �°� Ÿ�� ��Ʈ�� �о�´�. 
BOOL cltFieldObjectManager::LoadSet(DWORD frame, cltFieldObjectInfo* pclinfo, bool bmainmap )		
{

	if(pclinfo == NULL)
	{
		TCHAR buffer[256];
		StringCchPrintf(buffer, 256, TEXT("Cannot Find required FieldObjectSet"));

		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, buffer, TEXT("Error"), MB_OK|MB_TOPMOST);
		return FALSE;
	}

	BOOL bCompress = FALSE;
	BYTE* pFileBuf = NULL;
	BOOL bCompressLoaded = FALSE;

	//===========================================================================================
	// ������ �������Ͽ� ����ִ�ġ üũ�Ѵ�.
	//===========================================================================================
	TCHAR szZipName[MAX_PATH] = { '\0', };
	TCHAR szRealName[MAX_PATH] = { '\0', };
	if( pclinfo->pszZipName != NULL)	{	StringCchPrintf( szZipName, sizeof(szZipName), "FieldObject\\%s.mz", pclinfo->pszZipName);					}
	if( pclinfo->pszName != NULL)		{	StringCchPrintf( szRealName, sizeof(szRealName), "%s/%s%d.mpr", pclinfo->pszName, pclinfo->pszName, 1 );	}

	unzFile uf = unzOpen( szZipName );
	bool bFind = false;
	if( uf )
	{
		unz_global_info gi;
		int ret = unzGetGlobalInfo(uf, &gi);

		for( UI32 j=0; j<gi.number_entry; j++ )
		{
			TCHAR filename[MAX_PATH];
			unz_file_info file_info;
			ret = unzGetCurrentFileInfo( uf, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);

			_tcsupr(filename);
			_tcsupr(szRealName);

			if( _tcscmp( filename, szRealName ) == 0 )
			{
				bCompress = TRUE;
				pFileBuf = new BYTE[file_info.uncompressed_size];
				if( pFileBuf != NULL )
				{
					unzOpenCurrentFile( uf );
					UI32 nReaded = unzReadCurrentFile( uf, pFileBuf, file_info.uncompressed_size);
					if( nReaded == file_info.uncompressed_size)		bCompressLoaded = true;
					unzCloseCurrentFile( uf );
				}
				break;
			}

			ret = unzGoToNextFile(uf);
		}
		unzClose( uf );
	}
	//===========================================================================================

	// �̹����� �ҷ��´�.
	TCHAR szfilename[128];
	StringCchPrintf(szfilename, 128, TEXT("FieldObject\\%s\\%s%d.Mpr"), pclinfo->pszName, pclinfo->pszName, 1);
	
	// ������ �̹��� ���� ������ ã�´�. 
	SI32 imgref = FindEmptySpr();
	if(imgref >= 0)
	{
		// ������ ������ �ʱ�ȭ�Ѵ�. 
		SI32 oldunique	= FOInfoUnique[imgref];
		SI32 oldref		= FindRefFromUniqueMinus(oldunique);
		if(oldref >= 0 )
		{
			pclInfo[ oldref ]->siFOSprRef = -1;
			siLoadedSize -= FOSpr[ imgref ].GetImageDataSize();
		}

		pclinfo->siFOSprRef		= imgref;
		pclinfo->bIsMainMap		= bmainmap;
		dwLastUseFrame[imgref]	= frame;
		FOInfoUnique[imgref]	= pclinfo->Unique;	

		if( bCompress )
		{
			if( bCompressLoaded )
			{
				GP.LoadSprFromMemory(pFileBuf, &FOSpr[ imgref ]);
			}
			else
			{
#ifdef _DEBUG
				MessageBox( NULL, szfilename, "ERROR", MB_OK );
#endif
			}
			if( pFileBuf != NULL )		delete [] pFileBuf;
		}
		else
		{
			GP.LoadSprFromFile(szfilename, &FOSpr[ imgref ]);
		}

		// �ε��� ����� �����Ѵ�. 
		siLoadedSize += FOSpr[ imgref ].GetImageDataSize();

	}


	return TRUE;
}

// ����ũ ���� �ٰŷ� ���۷����� ã�´�. 
SI32 cltFieldObjectManager::FindRefFromUniqueMinus(SI32 siunique)
{

	if(siunique <= 0 || siunique >= MAX_FOUNIQUE)return -1;

	return siFORef[siunique];

}


// FieldObject�� Atb�� ã�´�.
SI32 cltFieldObjectManager::GetAtb(SI32 founique)
{
	SI32 ref = FindRefFromUniqueMinus(founique);
	if(ref < 0)return 0;

	SI32 type = pclInfo[ref]->dwType;

	return pclTypeInfo[type]->dwAtb;
}


// ������ ���� Field Object�� �޸𸮿��� �����Ѵ�. 
void cltFieldObjectManager::DeleteIfNotUse(DWORD curframe)
{
	SI32 i;

	for(i = 0;i < MAX_FOSPR_NUMBER;i++)
	{
		if(FOSpr[i].pImage == NULL)continue;

		if( pclClient->IsCountrySwitch(Switch_FieldObjectPreLoad) == false )
		{
			if( TABS(curframe - dwLastUseFrame[i]) <= 500 ) continue;
		}

		SI32 ref = FindRefFromUniqueMinus( FOInfoUnique[i] );

		// ���θ��� �������� �ʴ´�.
		if ( pclInfo[ref]->bIsMainMap )	continue;

		// �̹��� ���۷����� �����Ѵ�. 
		pclInfo[ref]->siFOSprRef	= -1;


		// �޸��� ����� �ٿ��ش�. 
		siLoadedSize -= FOSpr[i].GetImageDataSize();
		GP.FreeSpr(FOSpr[i]);
	}
}

// �̸��� �ٰŷ� Unique�� ã�´�. 
SI32 cltFieldObjectManager::FindUniqueFromName(TCHAR* name)
{
	SI32 i;

	for(i = 0; i < MAX_FIELDOBJECTSET_NUMBER;i++)
	{
		if(pclInfo[i])
		{
			if( _tcscmp(pclInfo[i]->pszName, name)==0 )
			{
				return pclInfo[i]->Unique;
			}
		}
	}

	return 0;
}
