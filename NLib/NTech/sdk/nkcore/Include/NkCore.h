//-------------------------------------------------------------------------------------------------
// NkCore.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#ifdef WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
#define WIN32_LEAN_AND_MEAN
# include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include "NkRTLib.h"
#include "NkDebug.h"
#include "NkMemoryManager.h"
#include "NkPointer.h"
#include "NkRTTI.h"
#include "NkChars.h"
#include "NkString.h"
#include "NkStringRef.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

class NKCORE_ENTRY NkCore
{
public:
	static NkCore& Get();
	NkAllocator* GetAllocator();

private:
	NkCore();
	~NkCore();
	//-NkCore(const NkCore&) {};

public:
	static void SetAllocator( NkAllocator* );
	//-static void	Startup(NkAllocator* pkAllocator = NULL);
	static void	Startup();
	static void Shutdown();

	static NkCore* ms_pkCore;
	static NkAllocator* ms_pkAllocator;
};

//////////////////////////////////////////////////////////////////////////

inline NkAllocator* NkCore::GetAllocator()
{
	return ms_pkAllocator;
}

//////////////////////////////////////////////////////////////////////////
// NDOORS (c) Oct. 5, 2009 by RX(������)
//////////////////////////////////////////////////////////////////////////
// ���� ������ �ʱ�ȭ ���� ���� Ŭ����
// �ʿ��� ��� ��� �޾� ���� ����
//////////////////////////////////////////////////////////////////////////
// ���� ���� ��ü�� NkNew NkDelete �Լ� ���� ���� �߻� ���� �ذ�.
// NkCore�� Startup/Shutdown, NkMemory, static object��
// ���� ������ �ʱ�ȭ ��� �߰���.
// cpp ���Ͽ��� ���� ������ �߰��� �ٰ�.
/*
NkCoreInitImplement( NkStaticDataInitor, 0 ); // NkStdAllocator ���
//�Ǵ�
//MyCustumAllocator ���. NkNew ��� NeExtNew ����� ��!
NkCoreInitImplement( NkStaticDataInitor, NkExtNew MyCustumAllocator );
*/
class NkStaticDataInitor
{
public:
	NkStaticDataInitor( NkAllocator* );
	virtual ~NkStaticDataInitor();
	virtual void Initor( NkAllocator* );
};

#define NkCoreInitImplement( ClassInitor, pAlloc ) static ClassInitor gs_initor_(pAlloc)
