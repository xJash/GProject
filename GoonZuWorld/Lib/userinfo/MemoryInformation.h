#ifndef __MEMORYINFORMATION_H_
#define __MEMORYINFORMATION_H_

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------
//	Name : ���뷡
//	Desc : Memory ���� ��� Class Type CMemoryInformation
//	Date : 2005. 01. 31
//	Update : 
//--------------------------------------------------------------------------------------------
// CMemoryInformation
class CMemoryInformation
{

public:
	CMemoryInformation()
	{
		m_bInformationObtained = false;
		m_RAMInstalled = 0;
		m_MemoryAvailable = 0;
		m_VirtualMemory = 0;
		m_MemoryLoad = 0;
	};

// MemoryInformation
public:
	
	bool get_RAMInstalled( unsigned long& Val);// Physical Ram Installed

	bool get_MemoryAvailable( unsigned long& Val);
	bool get_VirtualMemory( unsigned long& Val);
	bool get_MemoryLoad( unsigned long& Val);
	
	void ResetMemoryInfo();

	bool GetInformation ();

private:
	bool m_bInformationObtained;

	unsigned long m_RAMInstalled;	// ���� �޸�S
	unsigned long m_MemoryAvailable; // ��밡�� �޸�
	unsigned long m_VirtualMemory;	// ���� �޸�
	unsigned long m_MemoryLoad;		// ?

};

#endif //__MEMORYINFORMATION_H_
