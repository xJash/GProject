// NdoorsStarter.cpp : DLL ���������� �����Դϴ�.


#include "stdafx.h"
#include "resource.h"
#include "NdoorsStarter.h"


class CNdoorsStarterModule : public CAtlDllModuleT< CNdoorsStarterModule >
{
public :
	DECLARE_LIBID(LIBID_NdoorsStarterLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_NDOORSSTARTER, "{9273E927-187B-422E-8989-E4A8048B9D38}")
};

CNdoorsStarterModule _AtlModule;


#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL �������Դϴ�.
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif




// DLL�� OLE�� ���� ��ε�� �� �ִ��� �����ϴ� �� ���˴ϴ�.
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// Ŭ���� ���͸��� ��ȯ�Ͽ� ��û�� ������ ��ü�� ����ϴ�.
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - �ý��� ������Ʈ���� �׸��� �߰��մϴ�.
STDAPI DllRegisterServer(void)
{
    // ��ü, ���� ���̺귯�� �� ���� ���̺귯���� ��� �ִ� ��� �������̽��� ����մϴ�.
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - �ý��� ������Ʈ������ �׸��� �����մϴ�.
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

