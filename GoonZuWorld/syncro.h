//--------------------------------------------------------------------------
// Name: HQSync CLASS
// Desc: ���μ������� Win32 Sync  
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Name: HQSync
// Desc: ���� �Լ�
//--------------------------------------------------------------------------
class HQSync
{
public:
	virtual inline void Lock()   {return;};
	virtual inline void Unlock() {return;};
	virtual inline ~HQSync()     {return;};
};


//--------------------------------------------------------------------------
// Name: UCriticalSection
// Desc: ����ȭ ��ü
//--------------------------------------------------------------------------
class HQCriticalSection : public HQSync
{
public:
	inline  HQCriticalSection()  {InitializeCriticalSection(&CriticalSection);return;};
	inline  void Lock()          {EnterCriticalSection(&CriticalSection);return;};
	inline  void Unlock()        {LeaveCriticalSection(&CriticalSection);return;};
	inline ~HQCriticalSection()  {DeleteCriticalSection(&CriticalSection);return;};
private:
	CRITICAL_SECTION CriticalSection;
	
};

//--------------------------------------------------------------------------
// Name: HQLock
// Desc: ����ȭ ������ ���� ��ü 
//--------------------------------------------------------------------------
class HQLock
{
public:
	inline  HQLock(HQSync *pSO) {pSync=pSO;pSync->Lock();return;};
	inline ~HQLock()            {pSync->Unlock();return;};
private:
  	HQSync  *pSync;
};
