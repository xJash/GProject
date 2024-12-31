#include <string.h>
#include <windows.h>
#include "MemoryInformation.h"
/////////////////////////////////////////////////////////////////////////////
// CMemoryInformation

//--------------------------------------------------------------------------------------------
//	Name : ���뷡
//	Desc : ��ġ�� �޸� �뷮 ���� ���
//	Date : 2005. 01. 31
//	Update : 
//--------------------------------------------------------------------------------------------
bool CMemoryInformation::get_RAMInstalled(unsigned long& Val)
{
	bool hRes = true;
	if ((hRes = GetInformation ()) != true)
	{
		return hRes;
	}

	Val = m_RAMInstalled;

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : ���뷡
//	Desc : ��� ���� �޸� �뷮 ���� ���
//	Date : 2005. 01. 31
//	Update : 
//--------------------------------------------------------------------------------------------
bool CMemoryInformation::get_MemoryAvailable(unsigned long& Val)
{
	bool hRes = true;
	if ((hRes = GetInformation ()) != true)
	{
		return hRes;
	}

	Val = m_MemoryAvailable;

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : ���뷡
//	Desc : ���ǰ� �ִ� ���� �޸� �뷮 ���� ���
//	Date : 2005. 01. 31
//	Update : 
//--------------------------------------------------------------------------------------------
bool CMemoryInformation::get_VirtualMemory(unsigned long& Val)
{
	bool hRes = true;
	if ((hRes = GetInformation ()) != true)
	{
		return hRes;
	}

	Val = m_VirtualMemory;

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : ���뷡
//	Desc : �ε�� �޸� �뷮 ���� ���
//	Date : 2005. 01. 31
//	Update : 
//--------------------------------------------------------------------------------------------
bool CMemoryInformation::get_MemoryLoad(unsigned long& Val)
{
	bool hRes = true;
	if ((hRes = GetInformation ()) != true)
	{
		return hRes;
	}

	Val = m_MemoryLoad;

	return true;
}

/**
leon add
* memory status�� üũ�� ���� �ٲ� �� �����Ƿ�
* reset function ����
*/
void CMemoryInformation::ResetMemoryInfo()
{
    m_bInformationObtained = false;
}

//--------------------------------------------------------------------------------------------
//	Name : ���뷡
//	Desc : �޸� ���� ���
//	Date : 2005. 01. 31
//	Update : 
//--------------------------------------------------------------------------------------------
bool CMemoryInformation::GetInformation ()
{
	bool hRes = true;
	MEMORYSTATUS memoryStatus;

	if (m_bInformationObtained)
	{
		return true;
	}

	memset (&memoryStatus, sizeof (MEMORYSTATUS), 0);
	memoryStatus.dwLength = sizeof (MEMORYSTATUS);

	// The function below doesn't return a value.

	::GlobalMemoryStatus (&memoryStatus);

	m_MemoryLoad = memoryStatus.dwMemoryLoad;
	m_RAMInstalled = memoryStatus.dwTotalPhys;
	m_MemoryAvailable = memoryStatus.dwAvailPhys;
	m_VirtualMemory = memoryStatus.dwTotalVirtual;

	m_bInformationObtained = true;

	return true;
}