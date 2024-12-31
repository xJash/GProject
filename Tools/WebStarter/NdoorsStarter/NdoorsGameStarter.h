// NdoorsGameStarter.h : CNdoorsGameStarter�� �����Դϴ�.

#pragma once
#include "resource.h"       // �� ��ȣ�Դϴ�.

#include "NdoorsStarter.h"
#include "_INdoorsGameStarterEvents_CP.h"
#include <atlctl.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "���� ������ COM ��ü�� ��ü DCOM ������ �������� �ʴ� Windows Mobile �÷����� ���� Windows CE �÷������� ����� �������� �ʽ��ϴ�. ATL�� ���� ������ COM ��ü�� ������ �����ϰ� ���� ������ COM ��ü ������ ����� �� �ֵ��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA�� �����Ͻʽÿ�. rgs ������ ������ ���� DCOM Windows CE�� �ƴ� �÷������� �����Ǵ� ������ ������ ���̹Ƿ� 'Free'�� �����Ǿ� �ֽ��ϴ�."
#endif



// CNdoorsGameStarter

class ATL_NO_VTABLE CNdoorsGameStarter :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNdoorsGameStarter, &CLSID_NdoorsGameStarter>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CNdoorsGameStarter>,
	public CProxy_INdoorsGameStarterEvents<CNdoorsGameStarter>,
	public IObjectWithSiteImpl<CNdoorsGameStarter>,	
	public IDispatchImpl<INdoorsGameStarter, &IID_INdoorsGameStarter, &LIBID_NdoorsStarterLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IObjectSafetyImpl<CNdoorsGameStarter, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>

{
public:
	CNdoorsGameStarter()
	{
		m_szGameTitle[ 0 ] = 0;
		m_szFileName[ 0 ] = 0;

		m_init = false;
		m_gameinstalled = 0;
		m_runresult = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NDOORSGAMESTARTER)

DECLARE_NOT_AGGREGATABLE(CNdoorsGameStarter)

BEGIN_COM_MAP(CNdoorsGameStarter)
	COM_INTERFACE_ENTRY(INdoorsGameStarter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()


BEGIN_CATEGORY_MAP(CNdoorsGameStarter)
	IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
	IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
END_CATEGORY_MAP()


BEGIN_CONNECTION_POINT_MAP(CNdoorsGameStarter)
	CONNECTION_POINT_ENTRY(__uuidof(_INdoorsGameStarterEvents))
END_CONNECTION_POINT_MAP()
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	bool	m_init;

	long	m_gameinstalled;
	long	m_runresult;

	TCHAR	m_szGameTitle[ MAX_PATH ];
	TCHAR   m_szDirectory[ MAX_PATH ];
	TCHAR	m_szFileName[ MAX_PATH ];
	

	STDMETHOD(InitStarter)(BSTR GameTitle, BSTR FileName);
	STDMETHOD(Run)(void);
	STDMETHOD(get_GameInstalled)(LONG* pVal);
	STDMETHOD(get_RunResult)(LONG* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(NdoorsGameStarter), CNdoorsGameStarter)
