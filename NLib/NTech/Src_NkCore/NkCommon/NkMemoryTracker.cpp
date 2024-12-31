#include "NkMemoryTracker.h"

#include "NkConsoleOutput.h"

NkMemoryTracker::NkMemoryTracker(NkAllocator* pkActualAllocator)
{

	m_pkConsoleOutput = NkExtNew NkConsoleOutput;

	m_ppkActiveMem = NkExtAlloc( NkAllocUnit*, 65536 );
	m_ppkReservedBlock = NkExtAlloc( NkAllocUnit*, 65536 );

	m_pkActualAllocator = pkActualAllocator;

	for( int i = 0; i < 65536; ++i )
	{
		m_ppkActiveMem[ i ] = NULL;
		m_ppkReservedBlock[ i ] = NULL;
	}

	m_pkReservedFirst = NkExtAlloc( NkAllocUnit, 4096 );
	m_ppkReservedBlock[ 0 ] = m_pkReservedFirst;
	m_uiReservedBlockCount = 1;

	// ó�� ������ ReservedBlock�� ���� �ʱ�ȭ
	for( int i = 0; i < 4096 - 1; ++i )
	{
		m_pkReservedFirst[ i ].m_pkNext = &m_pkReservedFirst[ i + 1 ];
	}
	
	m_pkReservedLast = &m_pkReservedFirst[ 4096 - 1 ];
	m_pkReservedLast->m_pkNext = NULL;
}

NkMemoryTracker::~NkMemoryTracker()
{
	for( unsigned int i = 0; i < m_uiReservedBlockCount; ++i )
	{
		NkExtFree( m_ppkReservedBlock[ i ] );
	}

	NkExtFree( m_ppkReservedBlock );
	
	NkExtFree( m_ppkActiveMem );

	NkExtDelete m_pkActualAllocator;

	NkExtDelete m_pkConsoleOutput;
}


void* NkMemoryTracker::Allocate(size_t& stSizeInBytes,
								size_t& stAlignment,
								NkMemoryEventType eEventType,
								bool bProvideAccurateSizeOnDeallocate,
								const char* pcFile,
								int iLine,
								const char* pcFunction)
{

	// ���� Allocate�� ȣ��
	void* pvMemory = m_pkActualAllocator->Allocate(stSizeInBytes, stAlignment, 
		eEventType, bProvideAccurateSizeOnDeallocate, 
		pcFile, iLine, pcFunction);

	// ��� ������Ʈ
	++m_stActiveAllocationCount;
	++m_stAccumulatedAllocationCount;

	if( m_stActiveAllocationCount > m_stPeakAllocationCount )
	{
		m_stPeakAllocationCount = m_stActiveAllocationCount;
	}
	
	m_stActiveMemory += stSizeInBytes;
	m_stAccumulatedMemory += stSizeInBytes;

	if( m_stActiveMemory > m_stPeakMemory )
	{
		m_stPeakMemory = m_stActiveMemory;
	}

	// ���ο� �� �Ҵ��� �ʿ��Ѱ�?
	if( m_pkReservedFirst == m_pkReservedLast )
	{
		AllocReservedBlock();
	}

	NkAllocUnit* pkUnit = m_pkReservedFirst;
	m_pkReservedFirst = m_pkReservedFirst->m_pkNext;

	pkUnit->Reset();
	pkUnit->m_pvMemory = pvMemory;
	pkUnit->m_eAllocType = eEventType;
	pkUnit->m_stSizeAllocated = stSizeInBytes;

	pkUnit->m_dwAllocThreadId = GetCurrentThreadId();

	pkUnit->m_pcFile = pcFile;
	pkUnit->m_pcFunc = pcFunction;
	pkUnit->m_uiLine = iLine;

	InsertAllocUnit( pkUnit );

	return pvMemory;
}

//---------------------------------------------------------------------------
void NkMemoryTracker::Deallocate(void* pvMemory, NkMemoryEventType eEventType, size_t stSizeInBytes)
{
	if( pvMemory == NULL )
		return;

	NkAllocUnit* pkPrevUnit = NULL;
	NkAllocUnit* pkUnit = FindAllocUnit( pvMemory, &pkPrevUnit );

	if( pkUnit == NULL )
	{
		return;
	}

	// ���� Deallocate�� ȣ��
	m_pkActualAllocator->Deallocate(pvMemory, eEventType, stSizeInBytes);

	RemoveAllocUnit( pkUnit, pkPrevUnit );

	// ��� ������Ʈ
	--m_stActiveAllocationCount;
	m_stActiveMemory -= pkUnit->m_stSizeAllocated;

}

//---------------------------------------------------------------------------
void* NkMemoryTracker::Reallocate(void* pvMemory,
								  size_t& stSizeInBytes,
								  size_t& stAlignment,
								  NkMemoryEventType eEventType,
								  bool bProvideAccurateSizeOnDeallocate,
								  size_t stSizeCurrent,
								  const char* pcFile,
								  int iLine,
								  const char* pcFunction)
{

	// pvMemory�� NULL�̸�, ���� �Ҵ��Ѵ�.
	if( pvMemory == NULL )
	{
		return Allocate( stSizeInBytes, stAlignment, eEventType,
			bProvideAccurateSizeOnDeallocate, 
			pcFile, iLine, pcFunction );
	}

	// size�� 0�̸�, ������ �Ѵ�.
	if( stSizeInBytes == 0 )
	{
		Deallocate( pvMemory, eEventType, NK_MEM_DEALLOC_SIZE_DEFAULT );
		return NULL;
	}

	// ���� Reallocate�� ȣ��
	void* pvNewMemory = m_pkActualAllocator->Reallocate( pvMemory,
		stSizeInBytes, stAlignment, eEventType,
		bProvideAccurateSizeOnDeallocate, stSizeCurrent,
		pcFile, iLine, pcFunction);

	// �ؽ� ���̺��� ���� �޸��� �Ҵ� ������ ã�´�.
	NkAllocUnit* pkPrevUnit = NULL;
	NkAllocUnit* pkUnit = FindAllocUnit( pvMemory, &pkPrevUnit );

	if( pkUnit == NULL )
	{
		return NULL;
	}

	// ��� ������Ʈ
	++m_stAccumulatedAllocationCount;
	m_stAccumulatedMemory += stSizeInBytes;

	m_stActiveMemory += ( stSizeInBytes - pkUnit->m_stSizeAllocated );

	if( m_stActiveMemory > m_stPeakMemory )
	{
		m_stPeakMemory = m_stActiveMemory;
	}

	// �ؽ� ���̺��� ���� �޸��� �Ҵ� ������ �����Ѵ�.
	RemoveAllocUnit( pkUnit, pkPrevUnit );


	// ���ο� �� �Ҵ��� �ʿ��Ѱ�?
	if( m_pkReservedFirst == m_pkReservedLast )
	{
		AllocReservedBlock();
	}

	NkAllocUnit* pkNewUnit = m_pkReservedFirst;
	m_pkReservedFirst = m_pkReservedFirst->m_pkNext;

	pkNewUnit->Reset();
	pkNewUnit->m_pvMemory = pvNewMemory;
	pkNewUnit->m_eAllocType = eEventType;
	pkNewUnit->m_stSizeAllocated = stSizeInBytes;

	pkNewUnit->m_dwAllocThreadId = GetCurrentThreadId();

	pkNewUnit->m_pcFile = pcFile;
	pkNewUnit->m_pcFunc = pcFunction;
	pkNewUnit->m_uiLine = iLine;

	InsertAllocUnit( pkNewUnit );

	return pvNewMemory;
}

//---------------------------------------------------------------------------
bool NkMemoryTracker::SetMarker(const char* /*pcMarkerType*/, const char* /*pcClassifier*/, const char* /*pcString*/)
{
	return true;
}

//---------------------------------------------------------------------------
void NkMemoryTracker::Init()
{
	ResetStats();
}

//---------------------------------------------------------------------------
void NkMemoryTracker::Shutdown()
{
	OutputLeakedMemory();
}

bool NkMemoryTracker::VerifyAddress(const void* /*pvMemory*/)
{
	return true;
}

void NkMemoryTracker::ResetStats()
{
	m_stActiveMemory = 0;
	m_stPeakMemory = 0;
	m_stAccumulatedMemory = 0;

	m_stActiveAllocationCount = 0;
	m_stPeakAllocationCount = 0;
	m_stAccumulatedAllocationCount = 0;
}


void NkMemoryTracker::InsertAllocUnit(NkAllocUnit* pkUnit)
{
	unsigned int uiHashIndex = AddressToHashIndex( pkUnit->m_pvMemory );

	pkUnit->m_pkNext = m_ppkActiveMem[ uiHashIndex ];
	m_ppkActiveMem[ uiHashIndex ] = pkUnit;
}

void NkMemoryTracker::RemoveAllocUnit(NkAllocUnit* pkUnit, NkAllocUnit* pkPrevUnit)
{
	unsigned int uiHashIndex = AddressToHashIndex( pkUnit->m_pvMemory );

	if( pkPrevUnit == NULL )
	{
		m_ppkActiveMem[ uiHashIndex ] = pkUnit->m_pkNext;
	}
	else
	{
		pkPrevUnit->m_pkNext = pkUnit->m_pkNext;
	}

	m_pkReservedLast->m_pkNext = pkUnit;
	m_pkReservedLast = pkUnit;
	m_pkReservedLast->m_pkNext = NULL;

	return;
}


NkAllocUnit* NkMemoryTracker::FindAllocUnit(const void* pvMemory, NkAllocUnit** ppkOutPrevUnit)
{
	unsigned int uiHashIndex = AddressToHashIndex(pvMemory);

	NkAllocUnit* pkPrev = NULL;
	NkAllocUnit* pkUnit = m_ppkActiveMem[ uiHashIndex ];
	
	while(pkUnit)
	{
		if( pkUnit->m_pvMemory == pvMemory )
		{
			*ppkOutPrevUnit = pkPrev;
			return pkUnit;
		}

		pkPrev = pkUnit;
		pkUnit = pkUnit->m_pkNext;
	}

	return NULL;
}

void NkMemoryTracker::AllocReservedBlock()
{
	NkAllocUnit* pkNewBlock = NkExtAlloc(NkAllocUnit, 4096);

	m_ppkReservedBlock[ m_uiReservedBlockCount ] = pkNewBlock;
	++m_uiReservedBlockCount;

	m_pkReservedLast->m_pkNext = pkNewBlock;

	// ���� ������ ReservedBlock�� ���� �ʱ�ȭ
	for( int i = 0; i < 4096 - 1; ++i )
	{
		pkNewBlock[ i ].m_pkNext = &pkNewBlock[ i + 1 ];
	}

	m_pkReservedLast = &pkNewBlock[ 4096 - 1 ];
	m_pkReservedLast->m_pkNext = NULL;
}

void NkMemoryTracker::OutputLeakedMemory()
{
	m_pkConsoleOutput->CreateConsole( "NkLib - �޸� ���� ����Ʈ" );

	m_pkConsoleOutput->Printf( "-----------------------------------------------------------\n" );
	m_pkConsoleOutput->Printf( "- ���� �ִ� �޸� ��뷮 : %d\n", m_stPeakMemory );
	m_pkConsoleOutput->Printf( "- �������� ���� �޸� �뷮 : %d\n", m_stActiveMemory );
	m_pkConsoleOutput->Printf( "- �������� ���� �޸� �Ҵ� ���� : %d\n", m_stActiveAllocationCount );
	m_pkConsoleOutput->Printf( "-----------------------------------------------------------\n" );

	NkAllocUnit** ppkLeakedUnit = NkExtAlloc( NkAllocUnit*, m_stActiveAllocationCount );
	size_t stLeakedUnitCount = 0;

	for( unsigned int i = 0; i < 65536; ++i )
	{
		NkAllocUnit* pkUnit = m_ppkActiveMem[ i ];

		while( pkUnit )
		{
			ppkLeakedUnit[ stLeakedUnitCount++ ] = pkUnit;
			pkUnit = pkUnit->m_pkNext;
		}
	}

	// ���� �޸� ���� ����ϱ�
	for( size_t i = 0; i < stLeakedUnitCount; ++i )
	{
		if( (i % 5) == 0 )
		{
			m_pkConsoleOutput->Printf( "����Ϸ��� ���콺�� Ŭ���ϼ���\n" );
			m_pkConsoleOutput->WaitInput();
		}
		m_pkConsoleOutput->SetTextColor( 7, 4 );
		m_pkConsoleOutput->Printf( "(%d/%d)\n", i + 1, stLeakedUnitCount );
		m_pkConsoleOutput->SetTextColor( 0, 7 );


		OutputAllocUnit( ppkLeakedUnit[ i ] );


	}

	NkExtFree( ppkLeakedUnit );

	m_pkConsoleOutput->Printf( "����Ϸ��� ���콺�� Ŭ���ϼ���\n" );
	m_pkConsoleOutput->WaitInput();

	m_pkConsoleOutput->CloseConsole();
	
}

void NkMemoryTracker::OutputAllocUnit(NkAllocUnit* pkUnit)
{
	static int count = 0;
	count++;
	
	m_pkConsoleOutput->Printf( "SourceFile: " );
	m_pkConsoleOutput->Printf( "%s\n", pkUnit->m_pcFile );
	m_pkConsoleOutput->Printf( "Function:" );
	m_pkConsoleOutput->SetTextColor( 0, 14 );
	m_pkConsoleOutput->Printf( "%s", pkUnit->m_pcFunc );
	m_pkConsoleOutput->SetTextColor( 0, 7 );
	m_pkConsoleOutput->Printf( ", Line: " );
	m_pkConsoleOutput->SetTextColor( 0, 14 );
	m_pkConsoleOutput->Printf( "%d", pkUnit->m_uiLine );
	m_pkConsoleOutput->SetTextColor( 0, 7 );
	m_pkConsoleOutput->Printf( ", Leaked Size: " );
	m_pkConsoleOutput->SetTextColor( 0, 14 );
	m_pkConsoleOutput->Printf( "%d\n", pkUnit->m_stSizeAllocated );
	m_pkConsoleOutput->SetTextColor( 0, 7 );

}
