//-------------------------------------------------------------------------------------------------
// NkDisk.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkCore.h"
#include "NkMultiMap.h"
#include "NkList.h"

//-----------------------------------------------------------------------------
// NkDiskHeader, NkDiskFileInfo, NkDiskFolderInfo, NkDiskFileDesc
// -��Ű¡ ���Ͽ� �������� ������ Ŭ���� ( ���, ��������, �������� )
//-----------------------------------------------------------------------------
class NkDiskHeader : public NkMemory
{
public:
	DWORD	m_dwUnique;
	DWORD	m_dwVersion;
	LONGLONG m_llFileDataOffset;
	LONGLONG m_llFileListOffset;
	LONGLONG m_llStringTableOffset;
	LONGLONG m_llEmptyBlockListOffset;
	LONGLONG m_llFileDataSize;
	DWORD	m_dwFileListSize;
	DWORD	m_dwStringTableSize;
	DWORD	m_dwEmptyBlockCount;
	DWORD	m_dwRootFolderCount;
	DWORD	m_dwRootFileCount;
	DWORD	m_dwTotalFolderCount;
	DWORD	m_dwTotalFileCount;	
};

class NkDiskFileInfo : public NkMemory
{
public:
	LONGLONG m_llFileDataOffset;
	DWORD m_dwFileSize;
	DWORD m_dwFileNameOffset;
};

class NkDiskFolderInfo : public NkMemory
{
public:
	DWORD m_dwFolderCount;
	DWORD m_dwFileCount;
	DWORD m_dwFolderNameOffset;
};

class NkDiskFileDesc : public NkMemory
{
public:
	FILETIME m_ftCreation;
	FILETIME m_ftLastWrite;
};

class NkDiskEmptyBlockInfo : public NkMemory
{
public:
	LONGLONG m_llEmptyBlockOffset;
	LONGLONG m_llEmptyBlockSize;
};


//-----------------------------------------------------------------------------
// NkDiskNode_Base , _Folder, _File
// - ���� �� ���� Ʈ�� ���� ���
//-----------------------------------------------------------------------------
class NkDiskNode_Folder;
class NkDiskNode_Base : public NkMemory, public NkCaster
{
	NkDeclareRootRTTI(NkDiskNode_Base);

public:
	NkDiskNode_Folder* m_pkParent;
	NkDiskNode_Base* m_pkNext;

	char* m_pcFileName;

public:
	NkDiskNode_Base() 
	{
		ZeroMemory( this, sizeof( *this ) );
	}

	virtual ~NkDiskNode_Base()
	{
		if( m_pcFileName ) free( (char*)m_pcFileName );
	}

	void SetFileName( const char* pcFileName )
	{
		if( m_pcFileName ) free( (char*)m_pcFileName );

		size_t size;
		StringCchLengthA( pcFileName, 4096, &size );
		++size;
		m_pcFileName = (char*)malloc( size );
		StringCchCopyA( (char*)m_pcFileName, size, pcFileName );
	}
};

class NkDiskNode_File : public NkDiskNode_Base
{
	NkDeclareRTTI;
public:
	NkDiskNode_File() : m_llFileDataOffset(0), m_dwFileSize(0) {}

	LONGLONG m_llFileDataOffset;
	DWORD m_dwFileSize;
};

class NkDiskNode_Folder : public NkDiskNode_Base
{
	NkDeclareRTTI;
public:
	NkDiskNode_Folder() : 
	  m_pkFirstFolder(0),
	  m_pkFirstFile(0),
	  m_dwFileCount(0),
	  m_dwFolderCount(0)
	{}

	NkDiskNode_Folder*	m_pkFirstFolder;
	NkDiskNode_File*	m_pkFirstFile;

	DWORD m_dwFileCount;
	DWORD m_dwFolderCount;
};

//-----------------------------------------------------------------------------
// MultiMap Functor classes
// - ��Ƽ �ؽ��� �ε��� ���� �Լ�, Ű �� �Լ�, ������ �� �Լ�
//-----------------------------------------------------------------------------
class NkDiskFileMapHashFunctor
{
public:
	static unsigned int KeyToHashIndex( const char* pcKey, unsigned int uiHashSize );
};

class NkDiskFileMapEqualsFunctor
{
public:
	static bool IsKeysEqual( const char* pcKey1, const char* pcKey2 );
	static bool IsDatasEqual( const char* pcKey1, NkDiskNode_Base** ppkData1, const char* pcKey2, NkDiskNode_Base** ppkData2 );
};


inline unsigned int NkDiskFileMapHashFunctor::KeyToHashIndex( const char* pcKey, unsigned int uiHashSize )
{
	unsigned int uiHash = 0;
	char ch = *pcKey;

	while( ch )
	{
		if( ch >= 'A' && ch <= 'Z' ) ch += ('a' - 'A');

		uiHash = (uiHash << 5) + uiHash + ch;

		ch = *(++pcKey);
	}
	return uiHash % uiHashSize;
}

inline bool NkDiskFileMapEqualsFunctor::IsKeysEqual( const char* pcKey1, const char* pcKey2 )
{
	return _stricmp( pcKey1, pcKey2 ) == 0;
}

inline bool NkDiskFileMapEqualsFunctor::IsDatasEqual( const char* pcKey1, NkDiskNode_Base** ppkData1, const char* pcKey2, NkDiskNode_Base** ppkData2 )
{
	if( (*ppkData1)->m_pkParent != (*ppkData2)->m_pkParent ) return false;

	return _stricmp( pcKey1, pcKey2 ) == 0;
}

// NkDiskFileMap Ÿ�� ����
typedef NkMultiMap<const char*, NkDiskNode_Base*, NkDiskFileMapHashFunctor, NkDiskFileMapEqualsFunctor> NkDiskFileMap;

// NkDiskEmptyList Ÿ�� ����
typedef NkList< NkDiskEmptyBlockInfo > NkDiskEmptyList;

//-----------------------------------------------------------------------------
// NkDisk
//-----------------------------------------------------------------------------
class NkDisk
{
public:
	NkDisk();
	~NkDisk();

	BOOL	CreateDisk( const char* szDiskName );
	BOOL	OpenDisk( const char* szDiskName, BOOL bReadOnly = TRUE );
	void	CloseDisk();

	BOOL	IsReadOnly() { return m_bReadOnly; }

	BOOL	AddFile( const char* szSourceFileName, const char* szTargetFileName );
	BOOL	DeleteFile( const char* szFileName );
	BOOL    ReplaceFile( const char* szFileName );

	void	PackFiles( const char* szWorkFolderName = NULL );
	void	UnPackFiles( const char* szWorkFolderName );

	BOOL	SetWorkFolder( const char* szFolderName );

	NkDiskNode_File* FindFile( const char* szPath );
	NkDiskNode_Folder* FindFolder( const char* szPath );

	BOOL	ReadFileData( NkDiskNode_File* pkFileNode, DWORD dwPosition, LPVOID lpBuffer, DWORD dwBytesToRead, LPDWORD lpBytesRead );

protected:
	NkDiskNode_Folder*	NewNode_Folder();
	NkDiskNode_File*	NewNode_File();
	void	DeleteNode( NkDiskNode_Base* pkNode );

	void	InitHeader();

	BOOL	LoadDiskInfos();
	BOOL	SaveDiskInfos();

	NkDiskNode_Folder*	AddNode_Folder( const char* szFolderName, NkDiskNode_Folder* pkFolderNode );
	NkDiskNode_File*	AddNode_File( const char* szFileName, NkDiskNode_Folder* pkFolderNode );

	BOOL	RemoveNode_Folder( NkDiskNode_Folder* pkFolderNode );
	BOOL	RemoveNode_File( NkDiskNode_File* pkFileNode );

	void	RemoveAllChildNodes( NkDiskNode_Folder* pkFolderNode );

	void	MakeFoldersTree( const char* szFolderName, NkDiskNode_Folder* pkFolderNode );
	void	AttachFilesOnTree( const char* szFolderName, NkDiskNode_Folder* pkFolderNode );
	void	ExtractFilesFromTree( const char* szFolderName, NkDiskNode_Folder* pkFolderNode );

	BOOL	AttachFile( const char* szFileName, NkDiskNode_File* pkFileNode );
	BOOL	AttachFile( HANDLE hFile, NkDiskNode_File* pkFileNode );
	BOOL	ExtractFile( NkDiskNode_File* pkFileNode );

	BOOL	ReadFileList( NkDiskNode_Folder* pkNode, DWORD dwFolderCount, DWORD dwFileCount );
	BOOL	WriteFileList( NkDiskNode_Folder* pkNode );

	BOOL	ReadEmptyBlockList();
	BOOL	WriteEmptyBlockList();

	BOOL	WriteStringTable( NkDiskNode_Folder* pkNode );

	BOOL	GetEmptyBlock( DWORD dwSize, LONGLONG* pllOffset );
	void	GetTotalEmptyBlockSize( LONGLONG* pllSize );

	NkCharsA< 256 >		m_kDiskFileName;				// ��Ű¡ ���ϸ�
	NkCharsA< 256 >		m_kWorkFolderName;				// �۾� ������

	NkAutoPtr< NkDiskHeader >		m_pkFileHeader;		// ��Ű¡ ���� ���

	NkAutoPtr< NkDiskNode_Folder >	m_pkRootNode;		// �ֻ��� ���
	NkRefPtr< NkDiskNode_Folder >	m_pkCurrentNode;	// ���� ���

	NkAutoPtr< NkDiskFileMap >		m_pkFileMap;		// �ؽ���
	NkAutoPtr< NkDiskEmptyList >	m_pkEmptyList;		// �� ���� ����Ʈ

	NkArrayPtr< char >				m_pStringTable;		// ��Ʈ�� ���̺�

	HANDLE				m_hDiskFile;					// ��Ű¡ ���� �ڵ�
	LONGLONG			m_llEndOfFileDataOffset;		// ��Ű¡ ���Ͽ��� ���� ��ġ
	DWORD				m_dwCurrentStringPos;			

	BOOL				m_bReadOnly;
	BOOL				m_bModified;

};
