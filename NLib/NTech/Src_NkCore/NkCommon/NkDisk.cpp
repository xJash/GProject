#include "NkDisk.h"

NkImplementRootRTTI(NkDiskNode_Base);
NkImplementRTTI(NkDiskNode_Folder,NkDiskNode_Base);
NkImplementRTTI(NkDiskNode_File,NkDiskNode_Base);

NkDisk::NkDisk()
{
	m_hDiskFile = INVALID_HANDLE_VALUE;

	m_dwCurrentStringPos = 0;

	m_bReadOnly = FALSE;
	m_bModified = FALSE;
}

NkDisk::~NkDisk()
{
	CloseDisk();
}

NkDiskNode_Folder* NkDisk::NewNode_Folder()
{
	return NkNew NkDiskNode_Folder;
}

NkDiskNode_File* NkDisk::NewNode_File()
{
	return NkNew NkDiskNode_File;
}

void NkDisk::DeleteNode( NkDiskNode_Base* pkNode )
{
	delete pkNode;
}

//-----------------------------------------------------------------------------
// ��ũ ������ �����Ѵ�
//-----------------------------------------------------------------------------
BOOL NkDisk::CreateDisk( const char* szDiskName )
{
	if( m_pkRootNode ) return FALSE;

	m_hDiskFile = CreateFile( szDiskName, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0 );

	if( m_hDiskFile == INVALID_HANDLE_VALUE ) return FALSE;

	m_llEndOfFileDataOffset = 128;

	// ��� ����
	m_pkFileHeader = NkNew NkDiskHeader;

	// ��� ���� �ʱ�ȭ
	InitHeader();

	// Root Node ����
	m_pkRootNode = NewNode_Folder();
	m_pkRootNode->SetFileName("");

	// �ؽ� �� ���� 
	m_pkFileMap = NkNew NkDiskFileMap( 10000 );

	m_bReadOnly = FALSE;
	m_bModified = TRUE;

	return TRUE;
}

//-----------------------------------------------------------------------------
// ��ũ ������ �����Ѵ�
//-----------------------------------------------------------------------------
BOOL NkDisk::OpenDisk( const char* szDiskName, BOOL bReadOnly )
{
	if( m_pkRootNode ) return FALSE;

	m_hDiskFile = CreateFile( szDiskName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0 );

	if( m_hDiskFile == INVALID_HANDLE_VALUE ) return FALSE;

	m_bReadOnly = bReadOnly;
	m_bModified = FALSE;

	// ��� �� ��ũ ���� �ε�
	LoadDiskInfos();

	return TRUE;
}

//-----------------------------------------------------------------------------
// ��ũ ������ �ݴ´�
//-----------------------------------------------------------------------------
void NkDisk::CloseDisk()
{
	// ���� �Ǿ��ٸ�, ��� �� ��ũ ������ ����Ѵ�
	if( m_bModified )
	{
		SaveDiskInfos();
	}

	if( m_hDiskFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hDiskFile );
		m_hDiskFile = INVALID_HANDLE_VALUE;
	}

	// ��� ����
	if( m_pkRootNode )
	{
		RemoveAllChildNodes( m_pkRootNode );
		m_pkRootNode.Delete();
	}

	// ���� �� ����
	m_pkFileMap.Delete();

	m_bReadOnly = FALSE;
	m_bModified = FALSE;
}

//-----------------------------------------------------------------------------
// ��� �ʱ�ȭ
//-----------------------------------------------------------------------------
void NkDisk::InitHeader()
{
	if( m_pkFileHeader )
	{
		ZeroMemory( m_pkFileHeader, sizeof(NkDiskHeader) );

		m_pkFileHeader->m_dwUnique = 0x00000036;
		m_pkFileHeader->m_dwVersion = 0x00000101;
		m_pkFileHeader->m_llFileDataOffset = 128;
		m_pkFileHeader->m_llFileListOffset = 128;
		m_pkFileHeader->m_llStringTableOffset = 128;
		m_pkFileHeader->m_dwFileListSize = 0;
		m_pkFileHeader->m_dwStringTableSize = 0;
		m_pkFileHeader->m_dwRootFolderCount = 0;
		m_pkFileHeader->m_dwRootFileCount = 0;
		m_pkFileHeader->m_dwTotalFolderCount = 0;
		m_pkFileHeader->m_dwTotalFileCount = 0;
	}
}


//-----------------------------------------------------------------------------
// �־��� ���� ��忡 ���ο� ���� ��带 �߰��Ѵ�.
//-----------------------------------------------------------------------------
NkDiskNode_Folder* NkDisk::AddNode_Folder( const char* szFolderName, NkDiskNode_Folder* pkParentNode )
{
	// ��� ����
	NkDiskNode_Folder* pkNewNode = NewNode_Folder();

	// �θ� ����
	pkNewNode->m_pkParent = pkParentNode;

	// ������ ����
	pkNewNode->SetFileName( szFolderName );

	// �ؽ��㿡 �߰�
	if( m_pkFileMap->AddAt( pkNewNode->m_pcFileName, pkNewNode ) == false )
	{
		DeleteNode( pkNewNode );
		return NULL;
	}

	// �־��� ���(����)�� �ڽ� ���(����)�� �߰�
	pkNewNode->m_pkNext = pkParentNode->m_pkFirstFolder;
	pkParentNode->m_pkFirstFolder = pkNewNode;

	++pkParentNode->m_dwFolderCount;
	++m_pkFileHeader->m_dwTotalFolderCount;

	return pkNewNode;
}

//-----------------------------------------------------------------------------
// �־��� ���� ��忡 ���ο� ���� ��带 �߰��Ѵ�.
//-----------------------------------------------------------------------------
NkDiskNode_File* NkDisk::AddNode_File( const char* szFileName, NkDiskNode_Folder* pkParentNode )
{
	// ��� ����
	NkDiskNode_File* pkNewNode = NewNode_File();

	// �θ� ����
	pkNewNode->m_pkParent = pkParentNode;

	// ���ϸ� ����
	pkNewNode->SetFileName( szFileName );

	// �ؽ��ʿ� �߰�
	if( m_pkFileMap->AddAt( pkNewNode->m_pcFileName, pkNewNode ) == false )
	{
		DeleteNode( pkNewNode );
		return NULL;
	}

	// �־��� ���(����)�� �ڽ� ���(����)�� �߰�
	pkNewNode->m_pkNext = pkParentNode->m_pkFirstFile;
	pkParentNode->m_pkFirstFile = pkNewNode;

	++pkParentNode->m_dwFileCount;
	++m_pkFileHeader->m_dwTotalFileCount;

	return pkNewNode;
};

//-----------------------------------------------------------------------------
// ���� ��带 ���� �Ѵ�.
//-----------------------------------------------------------------------------
BOOL NkDisk::RemoveNode_Folder( NkDiskNode_Folder* pkFolderNode )
{

	NkDiskNode_Folder* pkParent = pkFolderNode->m_pkParent;
	NkDiskNode_Folder* pkCurrNode = pkParent->m_pkFirstFolder;
	NkDiskNode_Folder* pkPrevNode = 0;

	while( pkCurrNode )
	{
		if( pkCurrNode == pkFolderNode )
		{
			if( pkPrevNode )
			{
				pkPrevNode->m_pkNext = pkCurrNode->m_pkNext;
			}
			else
			{
				pkParent->m_pkFirstFolder = (NkDiskNode_Folder*)pkCurrNode->m_pkNext;
			}

			DeleteNode( pkCurrNode );

			--pkParent->m_dwFolderCount;
			--m_pkFileHeader->m_dwTotalFolderCount;

			// �ؽ��ʿ��� ����
			m_pkFileMap->RemoveAt( pkFolderNode->m_pcFileName, (NkDiskNode_Base**)&pkFolderNode );

			return TRUE;
		}

		pkPrevNode = pkCurrNode;
		pkCurrNode = (NkDiskNode_Folder*)pkCurrNode->m_pkNext;
	}

	return FALSE;
}


//-----------------------------------------------------------------------------
// ���� ��带 ���� �Ѵ�.
//-----------------------------------------------------------------------------
BOOL NkDisk::RemoveNode_File( NkDiskNode_File* pkFileNode )
{

	NkDiskNode_Folder* pkParent = pkFileNode->m_pkParent;
	NkDiskNode_File* pkCurrNode = pkParent->m_pkFirstFile;
	NkDiskNode_File* pkPrevNode = 0;

	while( pkCurrNode )
	{
		if( pkCurrNode == pkFileNode )
		{
			if( pkPrevNode )
			{
				pkPrevNode->m_pkNext = pkCurrNode->m_pkNext;
			}
			else
			{
				pkParent->m_pkFirstFile = (NkDiskNode_File*)pkCurrNode->m_pkNext;
			}

			DeleteNode( pkCurrNode );

			--pkParent->m_dwFileCount;
			--m_pkFileHeader->m_dwTotalFileCount;

			// �ؽ��ʿ��� ����
			m_pkFileMap->RemoveAt( pkFileNode->m_pcFileName, (NkDiskNode_Base**)&pkFileNode );

			return TRUE;
		}

		pkPrevNode = pkCurrNode;
		pkCurrNode = (NkDiskNode_File*)pkCurrNode->m_pkNext;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
// �ڽ� ���� �� ���� ��带 ��� ���� �Ѵ�
//-----------------------------------------------------------------------------
void NkDisk::RemoveAllChildNodes( NkDiskNode_Folder* pkFolderNode )
{
	// �ڽ� ���� ����
	NkDiskNode_Folder* pkCurrFolderNode = pkFolderNode->m_pkFirstFolder;

	while( pkCurrFolderNode )
	{
		NkDiskNode_Folder* pkDelNode = pkCurrFolderNode;	

		pkCurrFolderNode = (NkDiskNode_Folder*)pkCurrFolderNode->m_pkNext;

		RemoveAllChildNodes( pkDelNode );

		DeleteNode( pkDelNode );

		--m_pkFileHeader->m_dwTotalFolderCount;
	}

	pkFolderNode->m_dwFolderCount = 0;
	pkFolderNode->m_pkFirstFolder = 0;

	// �ڽ� ���� ����
	NkDiskNode_File* pkCurrFileNode = pkFolderNode->m_pkFirstFile;

	while( pkCurrFileNode )
	{
		NkDiskNode_File* pkDelNode = pkCurrFileNode;	

		pkCurrFileNode = (NkDiskNode_File*)pkCurrFileNode->m_pkNext;

		DeleteNode( pkDelNode );

		--m_pkFileHeader->m_dwTotalFolderCount;
	}

	pkFolderNode->m_dwFileCount = 0;
	pkFolderNode->m_pkFirstFile = 0;
}

//-----------------------------------------------------------------------------
// ���� Ʈ���� �����Ѵ�
//-----------------------------------------------------------------------------
void NkDisk::MakeFoldersTree( const char* szFolderName, NkDiskNode_Folder* pkFolderNode )
{
	BOOL bResult;

	NkCharsT< 256 > kPath;

	WIN32_FIND_DATA wfd;
	HANDLE hFindFile;

	kPath = szFolderName;	
	kPath += "\\*.*";

	hFindFile = ::FindFirstFile( kPath.GetString(), &wfd );

	if( hFindFile != INVALID_HANDLE_VALUE )
	{
		bResult = TRUE;

		while( bResult )
		{
			if( !(wfd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) )
			{
				// �����̸�,
				if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					if( wfd.cFileName[ 0 ] != _T('.') )
					{
						AddNode_Folder( wfd.cFileName, pkFolderNode );						
					}
				}
				// �����̸�,
				else
				{
					AddNode_File( wfd.cFileName, pkFolderNode );
				}
			}

			bResult = ::FindNextFile( hFindFile, &wfd );
		}
		::FindClose( hFindFile );

		// ���� ���� Ž��
		pkFolderNode = pkFolderNode->m_pkFirstFolder;

		while( pkFolderNode )
		{
			kPath.Format( "%s\\%s", szFolderName, pkFolderNode->m_pcFileName );

			MakeFoldersTree( kPath.GetString(), pkFolderNode );

			pkFolderNode = (NkDiskNode_Folder*)pkFolderNode->m_pkNext;
		}
	}

};

//-----------------------------------------------------------------------------
// Ʈ���� Ž���Ͽ� ������ ����ġ �Ѵ�
//-----------------------------------------------------------------------------
void NkDisk::AttachFilesOnTree( const char* szFolderName, NkDiskNode_Folder* pkFolderNode )
{
	NkCharsT< 256 > kPath;

	// ������ ���� Ž�� �� ��Ű¡ ���Ͽ� ���̱�
	NkDiskNode_File* pkFileNode = pkFolderNode->m_pkFirstFile;
	while( pkFileNode )
	{
		kPath.Format( "%s\\%s", szFolderName, pkFileNode->m_pcFileName );

		AttachFile( kPath, pkFileNode );

		pkFileNode = (NkDiskNode_File*)pkFileNode->m_pkNext;
	}

	// ���� ���� Ž��
	pkFolderNode = pkFolderNode->m_pkFirstFolder;
	while( pkFolderNode )
	{
		kPath.Format( "%s\\%s", szFolderName, pkFolderNode->m_pcFileName );

		AttachFilesOnTree( kPath.GetString(), pkFolderNode );

		pkFolderNode = (NkDiskNode_Folder*)pkFolderNode->m_pkNext;
	}
}

//-----------------------------------------------------------------------------
// ������ ���� �Ѵ�
//-----------------------------------------------------------------------------
BOOL NkDisk::AttachFile( const char* szFileName, NkDiskNode_File* pkFileNode )
{
	HANDLE hFile = CreateFile( szFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0 );

	if( hFile == INVALID_HANDLE_VALUE ) return FALSE;

	BOOL bRet = AttachFile( hFile, pkFileNode );

	CloseHandle( hFile );

	return bRet;
}


//-----------------------------------------------------------------------------
// ������ ���� �Ѵ�
//-----------------------------------------------------------------------------
BOOL NkDisk::AttachFile( HANDLE hFile, NkDiskNode_File* pkFileNode )
{

	// ���� ũ�� ���ϱ�
	DWORD dwFileSize, dwFileSizeHigh;
	dwFileSize = GetFileSize( hFile, &dwFileSizeHigh );

	// ������ �ʹ� ũ�� FALSE ��ȯ
	if( dwFileSizeHigh != 0 || dwFileSize > (DWORD)0x7FFFFFFF ) 
	{
		return FALSE;
	}

	// ����� ã�´�
	LONGLONG llFileDataOffset;
	if( !GetEmptyBlock( dwFileSize + sizeof( NkDiskFileDesc ), &llFileDataOffset ) )
	{
		llFileDataOffset = m_llEndOfFileDataOffset;
	}

	pkFileNode->m_llFileDataOffset = llFileDataOffset;

	HANDLE hFileMapping = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
	if( hFileMapping == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}

	void* pFilePtr = (BYTE*)MapViewOfFile( hFileMapping, FILE_MAP_READ, 0, 0, 0 );
	if( pFilePtr == NULL )
	{
		CloseHandle( hFileMapping );
		return FALSE;
	}

	// ���� ���� ����
	NkDiskFileDesc kFileDesc;
	DWORD dwWritten;

	GetFileTime( hFile, &kFileDesc.m_ftCreation, NULL, &kFileDesc.m_ftLastWrite );

	LARGE_INTEGER liOffset;
	liOffset.QuadPart = llFileDataOffset;
	SetFilePointerEx( m_hDiskFile, liOffset, 0, FILE_BEGIN );

	WriteFile( m_hDiskFile, &kFileDesc, sizeof(kFileDesc), &dwWritten, 0 );
	llFileDataOffset += dwWritten;

	WriteFile( m_hDiskFile, pFilePtr, dwFileSize, &dwWritten, 0 );
	llFileDataOffset += dwWritten;

	if( llFileDataOffset > m_llEndOfFileDataOffset ) m_llEndOfFileDataOffset = llFileDataOffset;

	UnmapViewOfFile( pFilePtr );

	CloseHandle( hFileMapping );

	pkFileNode->m_dwFileSize = dwFileSize;

	return TRUE;
}


//-----------------------------------------------------------------------------
// Ʈ���� Ž���Ͽ� ������ �̾Ƴ���
//-----------------------------------------------------------------------------
void NkDisk::ExtractFilesFromTree( const char* /*szFolderName*/, NkDiskNode_Folder* /*pkFolderNode*/ )
{
	/*
	NkChars< 256 > kPath;

	// ������ ���� Ž�� �� ��Ű¡ ���Ͽ� ���̱�
	NkDiskNode_File* pkFileNode = pkFolderNode->m_pkFirstFile;
	while( pkFileNode )
	{
		kPath.Format( "%s\\%s", szFolderName, pkFileNode->m_pcFileName );

		SetCurrentDirectory( szFolderName )

		ExtractFile( kpkFileNode );
		pkFileNode->m_qwFileDataOffset = m_llCurrentFilePos;

		pkFileNode = (NkDiskNode_File*)pkFileNode->m_pkNext;
	}

	// ���� ���� Ž��
	pkFolderNode = pkFolderNode->m_pkFirstFolder;
	while( pkFolderNode )
	{
		kPath.Format( "%s\\%s", szFolderName, pkFolderNode->m_pcFileName );

		m_pkCurrentNode = pkFolderNode;
		AttachFilesOnTree( kPath.GetString(), pkFolderNode );

		pkFolderNode = (NkDiskNode_Folder*)pkFolderNode->m_pkNext;
	}
	*/
}

//-----------------------------------------------------------------------------
// ������ �̾� ����
//-----------------------------------------------------------------------------
BOOL NkDisk::ExtractFile( NkDiskNode_File* pkFileNode )
{
	HANDLE hFile = CreateFile( pkFileNode->m_pcFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0 );

	if( hFile == INVALID_HANDLE_VALUE ) return FALSE;

	DWORD dwFileSize = pkFileNode->m_dwFileSize;

	HANDLE hFileMapping = CreateFileMapping( hFile, NULL, PAGE_WRITECOPY, 0, dwFileSize, NULL );
	if( hFileMapping == INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile );
		return FALSE;
	}

	void* pFilePtr = (BYTE*)MapViewOfFile( hFileMapping, FILE_MAP_COPY, 0, 0, 0 );
	if( pFilePtr == NULL )
	{
		CloseHandle( hFileMapping );
		CloseHandle( hFile );
		return FALSE;
	}

	LARGE_INTEGER liOffset;
	liOffset.QuadPart = pkFileNode->m_llFileDataOffset;
	SetFilePointerEx( m_hDiskFile, liOffset, 0, FILE_BEGIN );
	
	NkDiskFileDesc kFileDesc;
	DWORD dwRead;
	ReadFile( m_hDiskFile, &kFileDesc, sizeof(kFileDesc), &dwRead, 0 );

	ReadFile( m_hDiskFile, pFilePtr, pkFileNode->m_dwFileSize, &dwRead, 0 );
	
	SetFileTime( hFile, &kFileDesc.m_ftCreation, NULL, &kFileDesc.m_ftLastWrite );

	UnmapViewOfFile( pFilePtr );

	CloseHandle( hFileMapping );
	CloseHandle( hFile );

	return TRUE;
}


//-----------------------------------------------------------------------------
// ���� ����Ʈ( ����, ���� )�� �о�´�.
//-----------------------------------------------------------------------------
BOOL NkDisk::ReadFileList( NkDiskNode_Folder* pkNode, DWORD dwFolderCount, DWORD dwFileCount )
{
	DWORD i;
	DWORD dwRead;
	char* pcFileName;

	// ���� ���� �б�
	NkDiskFolderInfo kFolderInfo;

	for( i = 0; i < dwFolderCount; ++i )
	{
		ReadFile( m_hDiskFile, &kFolderInfo, sizeof(kFolderInfo), &dwRead, 0 );

		pcFileName = &m_pStringTable[ kFolderInfo.m_dwFolderNameOffset ];

		NkDiskNode_Folder* pkNewFolderNode = AddNode_Folder( pcFileName, pkNode );

		ReadFileList( pkNewFolderNode, kFolderInfo.m_dwFolderCount, kFolderInfo.m_dwFileCount );
	}

	// ���� ���� �б�
	NkDiskFileInfo kFileInfo;

	for( i = 0; i < dwFileCount; ++i )
	{
		ReadFile( m_hDiskFile, &kFileInfo, sizeof(kFileInfo), &dwRead, 0 );

		pcFileName = &m_pStringTable[ kFileInfo.m_dwFileNameOffset ];

		NkDiskNode_File* pkNewFileNode = AddNode_File( pcFileName, pkNode );
		pkNewFileNode->m_llFileDataOffset = kFileInfo.m_llFileDataOffset;
		pkNewFileNode->m_dwFileSize = kFileInfo.m_dwFileSize;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
// ���� ����Ʈ( ����, ���� )�� ����Ѵ�.
//-----------------------------------------------------------------------------
BOOL NkDisk::WriteFileList( NkDiskNode_Folder* pkNode )
{
	NkDiskFolderInfo kFolderInfo;
	DWORD dwWritten;

	// ���� ���� ����ϱ�
	NkDiskNode_Folder* pkFolderNode = pkNode->m_pkFirstFolder;
	while( pkFolderNode )
	{
		kFolderInfo.m_dwFolderCount = pkFolderNode->m_dwFolderCount;
		kFolderInfo.m_dwFileCount = pkFolderNode->m_dwFileCount;
		kFolderInfo.m_dwFolderNameOffset = m_dwCurrentStringPos;

		m_dwCurrentStringPos += (DWORD)strlen( pkFolderNode->m_pcFileName ) + 1;

		WriteFile( m_hDiskFile, &kFolderInfo, sizeof(kFolderInfo), &dwWritten, 0 );

		// ���� ���⿡ �����ϸ�, FALSE ��ȯ
		if( sizeof(kFolderInfo) != dwWritten ) return FALSE;

		// ���� ����Ʈ ũ�� ����
		m_pkFileHeader->m_dwFileListSize += dwWritten;

		if( WriteFileList( pkFolderNode ) == FALSE ) return FALSE;

		pkFolderNode = (NkDiskNode_Folder*)pkFolderNode->m_pkNext;
	}

	// ���� ���� ����ϱ�
	NkDiskFileInfo kFileInfo;

	NkDiskNode_File* pkFileNode = pkNode->m_pkFirstFile;
	while( pkFileNode )
	{
		kFileInfo.m_llFileDataOffset = pkFileNode->m_llFileDataOffset;
		kFileInfo.m_dwFileSize = pkFileNode->m_dwFileSize;
		kFileInfo.m_dwFileNameOffset = m_dwCurrentStringPos;

		m_dwCurrentStringPos += (DWORD)strlen( pkFileNode->m_pcFileName ) + 1;

		WriteFile( m_hDiskFile, &kFileInfo, sizeof(kFileInfo), &dwWritten, 0 );

		// ���� ���⿡ �����ϸ�, FALSE ��ȯ
		if( sizeof(kFileInfo) != dwWritten ) return FALSE;

		// ���� ����Ʈ ũ�� ����
		m_pkFileHeader->m_dwFileListSize += dwWritten;

		pkFileNode = (NkDiskNode_File*)pkFileNode->m_pkNext;
	}

	return TRUE;
}

BOOL NkDisk::ReadEmptyBlockList()
{

	DWORD i, dwRead;
	for( i = 0; i < m_pkFileHeader->m_dwEmptyBlockCount; ++i )
	{
		NkDiskEmptyBlockInfo* pkEmptyBlockInfo = m_pkEmptyList->NewBack();

		ReadFile( m_hDiskFile, pkEmptyBlockInfo, sizeof(NkDiskEmptyBlockInfo), &dwRead, 0 );
	}

	return TRUE;
}

BOOL NkDisk::WriteEmptyBlockList()
{
	if( !m_pkEmptyList )
	{
		m_pkFileHeader->m_dwEmptyBlockCount = 0;
		return TRUE;
	}

	NkListPos kPos = m_pkEmptyList->GetFrontPos();

	NkDiskEmptyBlockInfo* pkEmptyBlockInfo;
	while( NULL != (pkEmptyBlockInfo = m_pkEmptyList->GetDataPtr( kPos )) )
	{
		DWORD dwWritten;
		WriteFile( m_hDiskFile, pkEmptyBlockInfo, sizeof(NkDiskEmptyBlockInfo), &dwWritten, 0 );

		m_pkEmptyList->MoveNext( kPos );
	}
	
	return TRUE;
}

//-----------------------------------------------------------------------------
// ��Ʈ�� ���̺�( ������, ���ϸ� )�� ����Ѵ�.
//-----------------------------------------------------------------------------
BOOL NkDisk::WriteStringTable( NkDiskNode_Folder* pkNode )
{
	DWORD dwWritten;
	DWORD iSize;

	// ������ ����ϱ�
	NkDiskNode_Folder* pkFolderNode = pkNode->m_pkFirstFolder;
	while( pkFolderNode )
	{
		iSize = (int)strlen( pkFolderNode->m_pcFileName ) + 1;
		WriteFile( m_hDiskFile, pkFolderNode->m_pcFileName, iSize, &dwWritten, 0 );

		// ���� ���⿡ �����ϸ�, FALSE ��ȯ
		if( iSize != dwWritten ) return FALSE;

		if( WriteStringTable( pkFolderNode ) == FALSE ) return FALSE;

		pkFolderNode = (NkDiskNode_Folder*)pkFolderNode->m_pkNext;
	}

	// ���ϸ� ����ϱ�
	NkDiskNode_File* pkFileNode = pkNode->m_pkFirstFile;
	while( pkFileNode )
	{
		iSize = (int)strlen( pkFileNode->m_pcFileName ) + 1;
		WriteFile( m_hDiskFile, pkFileNode->m_pcFileName, iSize, &dwWritten, 0 );

		// ���� ���⿡ �����ϸ�, FALSE ��ȯ
		if( iSize != dwWritten ) return FALSE;

		pkFileNode = (NkDiskNode_File*)pkFileNode->m_pkNext;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
// Ư�� ������ ���� ������ ��� ��ŷ�Ѵ�
//-----------------------------------------------------------------------------
void NkDisk::PackFiles( LPCSTR szWorkFolderName )
{
	// �۾� ���� ����
	if( szWorkFolderName )
	{
		SetWorkFolder( szWorkFolderName );
	}

	// Ʈ�� �� �ؽ� ���̺� ����
	MakeFoldersTree( m_kWorkFolderName, m_pkRootNode );

	// ���� ���� 
	AttachFilesOnTree( m_kWorkFolderName, m_pkRootNode );
}


//-----------------------------------------------------------------------------
// ������ �߰� �Ѵ�
//-----------------------------------------------------------------------------
BOOL NkDisk::AddFile( const char* szSourceFileName, const char* szTargetFileName )
{

	HANDLE hFile = CreateFile( szSourceFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0 );

	if( hFile == INVALID_HANDLE_VALUE ) return FALSE;

	// ���� ã��, ������ �����
	NkCharsA< 256 > kStr;
	kStr = szTargetFileName;

	char* pStr1 = kStr;
	char* pStr2 = kStr;

	NkDiskNode_Base** ppkNode = (NkDiskNode_Base**)&m_pkRootNode;

	NkDiskNode_Folder* pkFolderNode;

	while( *pStr2 )
	{
		if( *pStr2 == '\\' || *pStr2 == '/' )
		{
			*pStr2 = '\0';

			if( NkIsExactKindOf( NkDiskNode_Folder, (*ppkNode) ) )
			{
				pkFolderNode = (NkDiskNode_Folder*)(*ppkNode);
				ppkNode = m_pkFileMap->GetAt( pStr1, (NkDiskNode_Base**)&pkFolderNode->m_pkFirstFolder );

				// ������ ������ �����Ѵ�
				if( !ppkNode ) 
				{
					pkFolderNode = AddNode_Folder( pStr1, pkFolderNode );
					if( !pkFolderNode )
					{
						CloseHandle( hFile );
						return FALSE;
					}

					ppkNode = (NkDiskNode_Base**)&pkFolderNode;
				}
			}
			else
			{
				CloseHandle( hFile );
				return FALSE;
			}

			pStr1 = ++pStr2;
			continue;
		}
		++pStr2;
	}

	// ���� ��� �߰�
	if( NkIsExactKindOf( NkDiskNode_Folder, (*ppkNode) ) )
	{
		pkFolderNode = (NkDiskNode_Folder*)*ppkNode;

		NkDiskNode_File* pkFileNode = AddNode_File( pStr1, pkFolderNode );

		if( !pkFileNode )
		{
			CloseHandle( hFile );
			return FALSE;
		}

		// ���� ���̱�
		if( AttachFile( hFile, pkFileNode ) )
		{
			CloseHandle( hFile );
			return TRUE;
		}

		CloseHandle( hFile );
		return FALSE;
	}

	CloseHandle( hFile );
	return FALSE;
}



//-----------------------------------------------------------------------------
// ������ ���� �Ѵ�
//-----------------------------------------------------------------------------
BOOL NkDisk::DeleteFile( const char* szFileName )
{
	NkDiskNode_File* pkFileNode = FindFile( szFileName );

	if( !pkFileNode ) return FALSE;

	NkDiskEmptyBlockInfo* pkEmptyBlockInfo;

	pkEmptyBlockInfo = m_pkEmptyList->NewFront();

	pkEmptyBlockInfo->m_llEmptyBlockOffset = pkFileNode->m_llFileDataOffset;
	pkEmptyBlockInfo->m_llEmptyBlockSize = pkFileNode->m_dwFileSize;

	return RemoveNode_File( pkFileNode );
}


//-----------------------------------------------------------------------------
// �۾� ������ �����Ѵ�
//-----------------------------------------------------------------------------
BOOL NkDisk::SetWorkFolder( const char* szFolderName )
{
	m_kWorkFolderName = szFolderName;
	return TRUE;
}


//-----------------------------------------------------------------------------
// ��ũ(��Ű¡ ����) ������ �ε��Ѵ� (���, ��Ʈ�� ���̺�, ���� ����Ʈ)
//-----------------------------------------------------------------------------
BOOL NkDisk::LoadDiskInfos()
{
	DWORD dwRead;
	LARGE_INTEGER liOffset;

	// Root Node ����
	m_pkRootNode = NewNode_Folder();
	m_pkRootNode->SetFileName("");

	// ��� ����
	m_pkFileHeader = NkNew NkDiskHeader;

	// ��� �б�
	SetFilePointer( m_hDiskFile, 0, 0, FILE_BEGIN );
	ReadFile( m_hDiskFile, m_pkFileHeader, sizeof(NkDiskHeader), &dwRead, 0 );

	m_llEndOfFileDataOffset = m_pkFileHeader->m_llFileDataOffset + m_pkFileHeader->m_llFileDataSize;

	// �б� ������ �ƴ� ���, �� �� ����Ʈ �б�
	if( !m_bReadOnly )
	{
		liOffset.QuadPart = m_pkFileHeader->m_llEmptyBlockListOffset;
		SetFilePointerEx( m_hDiskFile, liOffset, 0, FILE_BEGIN );
		ReadEmptyBlockList();
	}

	// �ؽ� �� ���� 
	DWORD size = m_pkFileHeader->m_dwTotalFileCount + m_pkFileHeader->m_dwTotalFolderCount;
	size /= 3;

	m_pkFileMap = NkNew NkDiskFileMap( size );

	// ��Ʈ�� ���̺� ����
	m_pStringTable = new char[ m_pkFileHeader->m_dwStringTableSize ];

	// ��Ʈ�� ���̺� �б�
	liOffset.QuadPart = m_pkFileHeader->m_llStringTableOffset;
	SetFilePointerEx( m_hDiskFile, liOffset, 0, FILE_BEGIN );
	ReadFile( m_hDiskFile, m_pStringTable, m_pkFileHeader->m_dwStringTableSize, &dwRead, 0 );

	// ���� ����Ʈ �б�
	liOffset.QuadPart = m_pkFileHeader->m_llFileListOffset;
	SetFilePointerEx( m_hDiskFile, liOffset, 0, FILE_BEGIN );
	ReadFileList( m_pkRootNode, m_pkFileHeader->m_dwRootFolderCount, m_pkFileHeader->m_dwRootFileCount );

	m_pStringTable.Delete();

	return TRUE;
}

//-----------------------------------------------------------------------------
// ��ũ(��Ű¡ ����) ������ �����Ѵ� (���� ����Ʈ, ��Ʈ�� ���̺�, ���)
//-----------------------------------------------------------------------------
BOOL NkDisk::SaveDiskInfos()
{
	m_dwCurrentStringPos = 0;

	// ���� ����Ʈ ���
	LARGE_INTEGER liOffset;
	liOffset.QuadPart = m_llEndOfFileDataOffset;
	SetFilePointerEx( m_hDiskFile, liOffset, 0, FILE_BEGIN );

	WriteFileList( m_pkRootNode );

	// ��Ʈ�� ���̺� ���
	WriteStringTable( m_pkRootNode );

	// �� �� ����Ʈ ���
	WriteEmptyBlockList();

	// ��� ���
	m_pkFileHeader->m_dwRootFolderCount = m_pkRootNode->m_dwFolderCount;
	m_pkFileHeader->m_dwRootFileCount = m_pkRootNode->m_dwFileCount;

	m_pkFileHeader->m_llFileDataSize = m_llEndOfFileDataOffset - m_pkFileHeader->m_llFileDataOffset;

	m_pkFileHeader->m_llFileListOffset = m_llEndOfFileDataOffset;
	m_pkFileHeader->m_llStringTableOffset = m_pkFileHeader->m_llFileListOffset + m_pkFileHeader->m_dwFileListSize;
	m_pkFileHeader->m_dwStringTableSize = m_dwCurrentStringPos;

	m_pkFileHeader->m_llEmptyBlockListOffset = m_pkFileHeader->m_llStringTableOffset + m_pkFileHeader->m_dwStringTableSize;

	SetFilePointer( m_hDiskFile, 0, 0, FILE_BEGIN );
	
	DWORD dwWritten;
	WriteFile( m_hDiskFile, m_pkFileHeader, sizeof(NkDiskHeader), &dwWritten, 0 );

	return TRUE;
}

//-----------------------------------------------------------------------------
// ������ ã�´�
//-----------------------------------------------------------------------------
NkDiskNode_File* NkDisk::FindFile( const char* szPath )
{
	NkCharsA< 256 > kStr;
	kStr = szPath;

	char* pStr1 = kStr;
	char* pStr2 = kStr;

	NkDiskNode_Base** ppkNode = (NkDiskNode_Base**)&m_pkRootNode;

	NkDiskNode_Folder* pkFolderNode;

	while( *pStr2 )
	{
		if( *pStr2 == '\\' || *pStr2 == '/' )
		{
			*pStr2 = '\0';

			if( NkIsExactKindOf( NkDiskNode_Folder, (*ppkNode) ) )
			{
				pkFolderNode = (NkDiskNode_Folder*)(*ppkNode);
				ppkNode = m_pkFileMap->GetAt( pStr1, (NkDiskNode_Base**)&pkFolderNode->m_pkFirstFolder );
				if( !ppkNode ) return NULL;
			}
			else
			{
				return NULL;
			}

			pStr1 = ++pStr2;
			continue;
		}
		++pStr2;
	}

	if( NkIsExactKindOf( NkDiskNode_Folder, (*ppkNode) ) )
	{
		pkFolderNode = (NkDiskNode_Folder*)*ppkNode;
		ppkNode = m_pkFileMap->GetAt( pStr1, (NkDiskNode_Base**)&pkFolderNode->m_pkFirstFile );

		if( ppkNode )
		{
			if( NkIsExactKindOf( NkDiskNode_File, (*ppkNode) ) )
			{
				return (NkDiskNode_File*)(*ppkNode);
			}
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// ������ ã�´�
//-----------------------------------------------------------------------------
NkDiskNode_Folder* NkDisk::FindFolder( const char* szPath )
{
	NkCharsA< 256 > kStr;
	kStr = szPath;

	char* pStr1 = kStr;
	char* pStr2 = kStr;

	NkDiskNode_Base** ppkNode = (NkDiskNode_Base**)&m_pkRootNode;

	NkDiskNode_Folder* pkFolderNode;

	while( *pStr2 )
	{
		if( *pStr2 == '\\' || *pStr2 == '/' )
		{
			*pStr2 = '\0';

			if( NkIsExactKindOf( NkDiskNode_Folder, (*ppkNode) ) )
			{
				pkFolderNode = (NkDiskNode_Folder*)(*ppkNode);
				ppkNode = m_pkFileMap->GetAt( pStr1, (NkDiskNode_Base**)&pkFolderNode->m_pkFirstFolder );
				if( !ppkNode ) return NULL;
			}
			else
			{
				return NULL;
			}

			pStr1 = ++pStr2;
			continue;
		}
		++pStr2;
	}

	if( NkIsExactKindOf( NkDiskNode_Folder, (*ppkNode) ) )
	{
		pkFolderNode = (NkDiskNode_Folder*)*ppkNode;
		ppkNode = m_pkFileMap->GetAt( pStr1, (NkDiskNode_Base**)&pkFolderNode->m_pkFirstFolder );

		if( ppkNode )
		{
			if( NkIsExactKindOf( NkDiskNode_Folder, (*ppkNode) ) )
			{
				return (NkDiskNode_Folder*)(*ppkNode);
			}
		}
	}

	return NULL;
}


BOOL NkDisk::ReadFileData( NkDiskNode_File* pkFileNode, DWORD dwPosition, LPVOID lpBuffer, DWORD dwBytesToRead, LPDWORD lpBytesRead )
{
	LARGE_INTEGER liOffset;
	liOffset.QuadPart = pkFileNode->m_llFileDataOffset;

	liOffset.QuadPart += sizeof(NkDiskFileDesc) + dwPosition;

	SetFilePointerEx( m_hDiskFile, liOffset, 0, FILE_BEGIN );

	ReadFile( m_hDiskFile, lpBuffer, dwBytesToRead, lpBytesRead, 0 );

	return TRUE;
}


BOOL NkDisk::GetEmptyBlock( DWORD dwSize, LONGLONG* pllOffset )
{
	if( !m_pkEmptyList ) 
	{
		*pllOffset = 0;
		return FALSE;
	}

	NkDiskEmptyBlockInfo* pkEmptyBlock;
	
	NkListPos kPos = m_pkEmptyList->GetFrontPos();

	while( NULL != (pkEmptyBlock = m_pkEmptyList->GetDataPtr( kPos )) )
	{
		if( pkEmptyBlock->m_llEmptyBlockSize >= dwSize ) 
		{
			*pllOffset = pkEmptyBlock->m_llEmptyBlockOffset;

			if( pkEmptyBlock->m_llEmptyBlockSize == dwSize )
			{
				m_pkEmptyList->Remove( kPos );
			}
			else
			{
				pkEmptyBlock->m_llEmptyBlockOffset += dwSize;
				pkEmptyBlock->m_llEmptyBlockSize -= dwSize;
			}

			return TRUE;
		}

		m_pkEmptyList->MoveNext( kPos );
	}
	
	*pllOffset = 0;
	return NULL;
}

void NkDisk::GetTotalEmptyBlockSize( LONGLONG* pllSize )
{
	if( !m_pkEmptyList )
	{
		*pllSize = 0;
		return;
	}

	LONGLONG llSize = 0;

	NkDiskEmptyBlockInfo* pkEmptyBlock;

	NkListPos kPos = m_pkEmptyList->GetFrontPos();

	while( NULL != (pkEmptyBlock = m_pkEmptyList->GetDataPtr( kPos )) )
	{
		llSize += pkEmptyBlock->m_llEmptyBlockSize;
		m_pkEmptyList->MoveNext( kPos );
	}

	*pllSize = llSize;
}

