/*
 * Dll.c -- A dynamic link library to display a web page in your own window.
 *
 * This is very loosely based upon a C++ example written by Chris Becke. I used
 * that to learn the minimum of what I needed to know about hosting the browser
 * object. Then I wrote this example from the ground up in C.
 *
 * The functions in this DLL callable by a program:
 *
 * EmbedBrowserObject() -- Embeds a browser object in your own window.
 * UnEmbedBrowserObject() -- Detaches the browser object from your window.
 * DisplayHTMLPage() -- Displays a URL or HTML file on disk.
 * DisplayHTMLStr() -- Displays a (in memory) string of HTML code.
 *
 * For the release (ie, not debug) version, then you should set your linker to
 * ignore the default libraries. This will reduce code size.
 */

#include <windows.h>
#include <exdisp.h>		/* Defines of stuff like IWebBrowser2. This is an include file with Visual C 6 and above */
#include <exdispid.h>		/* Defines of stuff like IWebBrowser2. This is an include file with Visual C 6 and above */
#include <mshtml.h>		/* Defines of stuff like IHTMLDocument2. This is an include file with Visual C 6 and above */
#include <mshtmhst.h>	// Defines of stuff like IDocHostUIHandler. This is an include file with Visual C 6 and above
#include <crtdbg.h>		/* for _ASSERT() */
#include <tchar.h>
#include "webhtml.h"

#if defined(_MSC_VER)
#pragma data_seg("Shared")
#endif

/* ============================== SHARED DATA ==============================
 * NOTE: I specify this data section to be Shared (ie, each program that uses
 * this shares these variables, rather than getting its own copies of these
 * variables). This is because, since I have only globals that are read-only
 * or whose value is the same for all processes, I don't need a separate copy
 * of these for each process that uses this DLL. In Visual C++'s Linker
 * settings, I add "/section:Shared,rws"
 */

/* This is used by DisplayHTMLStr(). It can be global because we never change it. */
static const SAFEARRAYBOUND ArrayBound = {1, 0};

unsigned char AppUrl[] = {'a', 0, 'p', 0, 'p', 0, ':', 0};
wchar_t Blank[] = {L"about:blank"};

#if defined(_MSC_VER)
#pragma data_seg()
#endif


//#define TRACE(text) MessageBoxA(NULL,text,TEXT("TRACE"),0);
#define TRACE(text) OutputDebugStringA(text);

/* Event Functions - Add user code in these functions */
/* -------------------------------------------------------------------------------- */
void BeforeNavigate2(IDispatch *pDisp, VARIANT * url,VARIANT * Flags,VARIANT * TargetFrameName, VARIANT * PostData,VARIANT * Headers,  VARIANT_BOOL * Cancel) 
{
	//static int PageCount; // sample code
	//TRACE("BeforeNavigate2");

	// Sample code - print out url with target frame as title
	//MessageBoxW(NULL,url->bstrVal,TargetFrameName->bstrVal,0);
	// Sample code - only allow five navigations before setting the cancel
	// argument to true and preventing further navigation
	//if (++PageCount >= 5) *Cancel = (VARIANT_BOOL) 0xffff;
}
/* -------------------------------------------------------------------------------- */
void ClientToHostWindow(long * CX,long * CY) {
	//TRACE("ClientToHostWindow");
}
/* -------------------------------------------------------------------------------- */
void CommandStateChange(long Command,VARIANT_BOOL Enable) {
	//TRACE("CommandStateChange");
}
/* -------------------------------------------------------------------------------- */
void DocumentComplete(IDispatch *pDisp, VARIANT *URL) {
	//TRACE("DocumentComplete");
}
/* -------------------------------------------------------------------------------- */
void DownloadBegin(VOID) {
	//TRACE("DownloadBegin");
}
/* -------------------------------------------------------------------------------- */
void DownloadComplete(VOID) {
	//TRACE("DownloadComplete");
}
/* -------------------------------------------------------------------------------- */
void FileDownload(VARIANT_BOOL * ActiveDocument, VARIANT_BOOL * Cancel) {
	//TRACE("FileDownload");
}
/* -------------------------------------------------------------------------------- */
void NavigateComplete2(IDispatch *pDisp, VARIANT *URL) {
	//TRACE("NavigateComplete2");
}
/* -------------------------------------------------------------------------------- */
void NavigateError(IDispatch *pDisp,VARIANT *URL,VARIANT *TargetFrameName,VARIANT *StatusCode,VARIANT_BOOL *Cancel) {
	//TRACE("NavigateError");
}
/* -------------------------------------------------------------------------------- */
void NewWindow2(IDispatch ** ppDisp,VARIANT_BOOL * Cancel)
{
	HWND hWnd = CreateBrowserWindow();

	if ( hWnd )
	{
		IWebBrowser2	*webBrowser2;
		IOleObject		*browserObject;

		browserObject = *((IOleObject **)GetWindowLong( hWnd, GWL_USERDATA ) );
		if (!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IWebBrowser2, (void**)&webBrowser2))
		{
			webBrowser2->lpVtbl->put_RegisterAsBrowser( webBrowser2, TRUE );
			webBrowser2->lpVtbl->get_Application( webBrowser2, ppDisp );
		}
	}

	//TRACE("NewWindow2");
}
/* -------------------------------------------------------------------------------- */
void OnFullScreen(VARIANT_BOOL FullScreen) {
	//TRACE("OnFullScreen");
}
/* -------------------------------------------------------------------------------- */
void OnMenuBar(VARIANT_BOOL MenuBar) {
	//TRACE("OnMenuBar");
}
/* -------------------------------------------------------------------------------- */
void OnQuit(VOID) {
	//TRACE("OnQuit");
}
/* -------------------------------------------------------------------------------- */
void OnStatusBar(VARIANT_BOOL StatusBar) {
	//TRACE("OnStatusBar");
}
/* -------------------------------------------------------------------------------- */
void OnTheaterMode(VARIANT_BOOL TheaterMode) {
	//TRACE("OnTheaterMode");
}
/* -------------------------------------------------------------------------------- */
void OnToolBar(VARIANT_BOOL ToolBar) {
	//TRACE("OnToolBar");
}
/* -------------------------------------------------------------------------------- */
void OnVisible(VARIANT_BOOL Visible) {
	//TRACE("OnVisible");
}
/* -------------------------------------------------------------------------------- */
void PrintTemplateInstantiation(IDispatch *pDisp) {
	//TRACE("PrintTemplateInstantiation");
}
/* -------------------------------------------------------------------------------- */
void PrintTemplateTeardown(IDispatch *pDisp) {
	//TRACE("PrintTemplateTeardown");
}
/* -------------------------------------------------------------------------------- */
void PrivacyImpactedStateChange(VARIANT_BOOL PrivacyImpacted) {
	//TRACE("PrivacyImpactedStateChange");
}
/* -------------------------------------------------------------------------------- */
void ProgressChange(long Progress, long ProgressMax) {
	//TRACE("ProgressChange");
}
/* -------------------------------------------------------------------------------- */
void PropertyChange(BSTR szProperty) {
	//TRACE("PropertyChange");
}
/* -------------------------------------------------------------------------------- */
void SetSecureLockIcon(long SecureLockIcon) {
	//TRACE("SetSecureLockIcon");
}
/* -------------------------------------------------------------------------------- */
void StatusTextChange(BSTR Text) {
	//TRACE("StatusTextChange");
}
/* -------------------------------------------------------------------------------- */
void TitleChange(BSTR Text) {
	//TRACE("TitleChange");
}
/* -------------------------------------------------------------------------------- */
void WindowClosing(VARIANT_BOOL IsChildWindow, VARIANT_BOOL *Cancel) {
	//TRACE("WindowClosing");
}
/* -------------------------------------------------------------------------------- */
void WindowSetHeight(long Height) {
	//TRACE("WindowSetHeight");
}
/* -------------------------------------------------------------------------------- */
void WindowSetLeft(long Left) {
	//TRACE("WindowSetLeft");
}
/* -------------------------------------------------------------------------------- */
void WindowSetResizable(VARIANT_BOOL Resizable) {
	//TRACE("WindowSetResizable");
}
/* -------------------------------------------------------------------------------- */
void WindowSetTop(long Top) {
	//TRACE("WindowSetTop");
}
/* -------------------------------------------------------------------------------- */
void WindowSetWidth(long Width) {
	//TRACE("WindowSetWidth");
}



/* -------------------------------------------------------------------------------- */
/* DWebBrowserEvents2 Disp Interface Prototypes */
HRESULT STDMETHODCALLTYPE WebEvents_QueryInterface(DWebBrowserEvents2 FAR* This, REFIID riid, void ** ppvObject);
HRESULT STDMETHODCALLTYPE WebEvents_AddRef(DWebBrowserEvents2 FAR* This);
HRESULT STDMETHODCALLTYPE WebEvents_Release(DWebBrowserEvents2 FAR* This);
HRESULT STDMETHODCALLTYPE WebEvents_GetTypeInfoCount(DWebBrowserEvents2 FAR* This, unsigned int FAR*  pctinfo );
HRESULT STDMETHODCALLTYPE WebEvents_GetTypeInfo(DWebBrowserEvents2 FAR* This, unsigned int  iTInfo, LCID  lcid, ITypeInfo FAR* FAR* ppTInfo );
HRESULT STDMETHODCALLTYPE WebEvents_GetIDsOfNames(DWebBrowserEvents2 FAR* This, REFIID  riid, OLECHAR FAR* FAR*  rgszNames, unsigned int cNames, LCID lcid, DISPID FAR* rgDispId);
HRESULT STDMETHODCALLTYPE WebEvents_Invoke(DWebBrowserEvents2 FAR* This, DISPID  dispIdMember, REFIID  riid, LCID  lcid, WORD  wFlags, DISPPARAMS FAR*  pDispParams, VARIANT FAR*  pVarResult, EXCEPINFO FAR*  pExcepInfo, unsigned int FAR*  puArgErr );


/* -------------------------------------------------------------------------------- */
/* Extended DWebBrowserEvents2 struct to contain reference count */
typedef struct tag_DWebBrowserEvents2Ex {
	DWebBrowserEvents2 WebEventsObj;
	LONG refCount;    // Our reference count
} _DWebBrowserEvents2Ex;


/* -------------------------------------------------------------------------------- */
/* Set up our single global vtbl */
DWebBrowserEvents2Vtbl MyDWebBrowserEvents2Vtbl = {
	WebEvents_QueryInterface,
	WebEvents_AddRef,
	WebEvents_Release,
	WebEvents_GetTypeInfoCount,
	WebEvents_GetTypeInfo,
	WebEvents_GetIDsOfNames,
	WebEvents_Invoke
};


/* DWebBrowserEvents2 functions - note these are just IUnknown/IDispatch functions */
/* -------------------------------------------------------------------------------- */
HRESULT STDMETHODCALLTYPE WebEvents_QueryInterface(DWebBrowserEvents2 FAR* This, REFIID riid, void ** ppvObject) {

	*ppvObject = NULL;

	if ( IsEqualGUID(riid, &IID_IUnknown) )
		*ppvObject = (void *) This;

	else if ( IsEqualGUID(riid, &IID_IDispatch) )
		*ppvObject = (void *) This;

	else if ( IsEqualGUID(riid, &DIID_DWebBrowserEvents2) )
		*ppvObject = (void *) This;

	if (*ppvObject)	{
		This->lpVtbl->AddRef(This);
		return S_OK;
	}
	else return E_NOINTERFACE;

}


/* -------------------------------------------------------------------------------- */
HRESULT STDMETHODCALLTYPE WebEvents_AddRef(DWebBrowserEvents2 FAR* This) {
	return InterlockedIncrement( &((_DWebBrowserEvents2Ex *) This)->refCount );
}


/* -------------------------------------------------------------------------------- */
HRESULT STDMETHODCALLTYPE WebEvents_Release(DWebBrowserEvents2 FAR* This) {

	if (InterlockedDecrement( &((_DWebBrowserEvents2Ex *) This)->refCount ) == 0) {
		// Every body is finished with this object
		// Let's destroy it!
		GlobalFree(This);
		return 0;
	}

	return ( (_DWebBrowserEvents2Ex *) This)->refCount;
}


/* -------------------------------------------------------------------------------- */
HRESULT STDMETHODCALLTYPE WebEvents_GetTypeInfoCount(DWebBrowserEvents2 FAR* This, unsigned int FAR*  pctinfo ) {
	return E_NOTIMPL;
}


/* -------------------------------------------------------------------------------- */
HRESULT STDMETHODCALLTYPE WebEvents_GetTypeInfo(DWebBrowserEvents2 FAR* This, unsigned int  iTInfo, LCID  lcid, ITypeInfo FAR* FAR* ppTInfo ) {
	return E_NOTIMPL;
}


/* -------------------------------------------------------------------------------- */
HRESULT STDMETHODCALLTYPE WebEvents_GetIDsOfNames(DWebBrowserEvents2 FAR* This, REFIID  riid, OLECHAR FAR* FAR*  rgszNames, unsigned int cNames, LCID lcid, DISPID FAR* rgDispId) {
	return S_OK;
}


/* -------------------------------------------------------------------------------- */
HRESULT STDMETHODCALLTYPE WebEvents_Invoke(DWebBrowserEvents2 FAR* This, DISPID  dispIdMember, REFIID  riid, LCID  lcid, WORD  wFlags, DISPPARAMS FAR*  pDispParams, VARIANT FAR*  pVarResult, EXCEPINFO FAR*  pExcepInfo, unsigned int FAR*  puArgErr ) {
  // This function is called to recevie an event. The event is identified by the
  // dispIdMember argument. It is our responsibility to retrieve the event arguments
  // from the pDispParams->rgvarg array and call the event function.
  // If we do not handle an event we can return DISP_E_MEMBERNOTFOUND.
  // The variant member that we use for each argument is determined by the argument
  // type of the event function. eg. If an event has the argument long x we would
  // use the lVal member of the VARIANT struct.

  // Here is our message map, where we map dispids to function calls.
  switch (dispIdMember) {
	case DISPID_BEFORENAVIGATE2:
		// call BeforeNavigate
		// (parameters are on stack, thus in reverse order)
		/*
		BeforeNavigate2( pDispParams->rgvarg[6].pdispVal,    // pDisp
				 pDispParams->rgvarg[5].pvarVal,     // url
				 pDispParams->rgvarg[4].pvarVal,     // Flags
				 pDispParams->rgvarg[3].pvarVal,     // TargetFrameName
				 pDispParams->rgvarg[2].pvarVal,     // PostData
				 pDispParams->rgvarg[1].pvarVal,     // Headers
				 pDispParams->rgvarg[0].pboolVal);   // Cancel
		*/
		break;

	case DISPID_CLIENTTOHOSTWINDOW:
		ClientToHostWindow(pDispParams->rgvarg[1].plVal, pDispParams->rgvarg[0].plVal);
		break;
	case DISPID_COMMANDSTATECHANGE:
		CommandStateChange(pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_DOCUMENTCOMPLETE:
		DocumentComplete(pDispParams->rgvarg[1].pdispVal, pDispParams->rgvarg[0].pvarVal);
		break;
	case DISPID_DOWNLOADBEGIN:
		DownloadBegin();
		break;
	case DISPID_DOWNLOADCOMPLETE:
		DownloadComplete();
		break;
	case DISPID_FILEDOWNLOAD:
		FileDownload(pDispParams->rgvarg[1].pboolVal, pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_NAVIGATECOMPLETE2:
		NavigateComplete2(pDispParams->rgvarg[1].pdispVal, pDispParams->rgvarg[0].pvarVal);
		break;
	case DISPID_NAVIGATEERROR:
		NavigateError(pDispParams->rgvarg[4].pdispVal, pDispParams->rgvarg[3].pvarVal, pDispParams->rgvarg[2].pvarVal, pDispParams->rgvarg[1].pvarVal, pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_NEWWINDOW2:
		NewWindow2(pDispParams->rgvarg[1].ppdispVal, pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_ONFULLSCREEN:
		OnFullScreen(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_ONMENUBAR:
		OnMenuBar(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_ONQUIT:
		OnQuit();
		break;
	case DISPID_ONSTATUSBAR:
		OnStatusBar(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_ONTHEATERMODE:
		OnTheaterMode(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_ONTOOLBAR:
		OnToolBar(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_ONVISIBLE:
		OnVisible(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_PRINTTEMPLATEINSTANTIATION:
		PrintTemplateInstantiation(pDispParams->rgvarg[0].pdispVal);
		break;
	case DISPID_PRINTTEMPLATETEARDOWN:
		PrintTemplateTeardown(pDispParams->rgvarg[0].pdispVal);
		break;
	case DISPID_PRIVACYIMPACTEDSTATECHANGE:
		PrivacyImpactedStateChange(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_PROGRESSCHANGE:
		ProgressChange(pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		break;
	case DISPID_PROPERTYCHANGE:
		PropertyChange(pDispParams->rgvarg[0].bstrVal);
		break;
	case DISPID_SETSECURELOCKICON:
		SetSecureLockIcon(pDispParams->rgvarg[0].lVal);
		break;
	case DISPID_STATUSTEXTCHANGE:
		StatusTextChange(pDispParams->rgvarg[0].bstrVal);
		break;
	case DISPID_TITLECHANGE:
		TitleChange(pDispParams->rgvarg[0].bstrVal);
		break;
	case DISPID_WINDOWCLOSING:
		WindowClosing(pDispParams->rgvarg[1].boolVal, pDispParams->rgvarg[0].pboolVal);
		break;
	case DISPID_WINDOWSETHEIGHT:
		WindowSetHeight(pDispParams->rgvarg[0].lVal);
		break;
	case DISPID_WINDOWSETLEFT:
		WindowSetLeft(pDispParams->rgvarg[0].lVal);
		break;
	case DISPID_WINDOWSETRESIZABLE:
		WindowSetResizable(pDispParams->rgvarg[0].boolVal);
		break;
	case DISPID_WINDOWSETTOP:
		WindowSetTop(pDispParams->rgvarg[0].lVal);
		break;
	case DISPID_WINDOWSETWIDTH:
		WindowSetWidth(pDispParams->rgvarg[0].lVal);
		break;
	
	default:
		return DISP_E_MEMBERNOTFOUND;


  } //end switch

  return S_OK;

}


/* Our IStorage functions that the browser may call */
HRESULT STDMETHODCALLTYPE Storage_QueryInterface(IStorage FAR* This, REFIID riid, LPVOID FAR* ppvObj);
HRESULT STDMETHODCALLTYPE Storage_AddRef(IStorage FAR* This);
HRESULT STDMETHODCALLTYPE Storage_Release(IStorage FAR* This);
HRESULT STDMETHODCALLTYPE Storage_CreateStream(IStorage FAR* This, const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm);
HRESULT STDMETHODCALLTYPE Storage_OpenStream(IStorage FAR* This, const WCHAR * pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm);
HRESULT STDMETHODCALLTYPE Storage_CreateStorage(IStorage FAR* This, const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg);
HRESULT STDMETHODCALLTYPE Storage_OpenStorage(IStorage FAR* This, const WCHAR * pwcsName, IStorage * pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg);
HRESULT STDMETHODCALLTYPE Storage_CopyTo(IStorage FAR* This, DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude,IStorage *pstgDest);
HRESULT STDMETHODCALLTYPE Storage_MoveElementTo(IStorage FAR* This, const OLECHAR *pwcsName,IStorage * pstgDest, const OLECHAR *pwcsNewName, DWORD grfFlags);
HRESULT STDMETHODCALLTYPE Storage_Commit(IStorage FAR* This, DWORD grfCommitFlags);
HRESULT STDMETHODCALLTYPE Storage_Revert(IStorage FAR* This);
HRESULT STDMETHODCALLTYPE Storage_EnumElements(IStorage FAR* This, DWORD reserved1, void * reserved2, DWORD reserved3, IEnumSTATSTG ** ppenum);
HRESULT STDMETHODCALLTYPE Storage_DestroyElement(IStorage FAR* This, const OLECHAR *pwcsName);
HRESULT STDMETHODCALLTYPE Storage_RenameElement(IStorage FAR* This, const WCHAR *pwcsOldName, const WCHAR *pwcsNewName);
HRESULT STDMETHODCALLTYPE Storage_SetElementTimes(IStorage FAR* This, const WCHAR *pwcsName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime);
HRESULT STDMETHODCALLTYPE Storage_SetClass(IStorage FAR* This, REFCLSID clsid);
HRESULT STDMETHODCALLTYPE Storage_SetStateBits(IStorage FAR* This, DWORD grfStateBits, DWORD grfMask);
HRESULT STDMETHODCALLTYPE Storage_Stat(IStorage FAR* This, STATSTG * pstatstg, DWORD grfStatFlag);

/* Our IStorage VTable. This is the array of pointers to the above functions in our C
 * program that someone may call in order to store some data to disk. We must define a
 * particular set of functions that comprise the IStorage set of functions (see above),
 * and then stuff pointers to those functions in their respective 'slots' in this table.
 * We want the browser to use this VTable with our IStorage structure (object).
 */
static const IStorageVtbl MyIStorageTable = {Storage_QueryInterface,
Storage_AddRef,
Storage_Release,
Storage_CreateStream,
Storage_OpenStream,
Storage_CreateStorage,
Storage_OpenStorage,
Storage_CopyTo,
Storage_MoveElementTo,
Storage_Commit,
Storage_Revert,
Storage_EnumElements,
Storage_DestroyElement,
Storage_RenameElement,
Storage_SetElementTimes,
Storage_SetClass,
Storage_SetStateBits,
Storage_Stat};

/* Our IStorage structure. NOTE: All it contains is a pointer to our IStorageVtbl, so we can easily initialize it
 * here instead of doing that programmably.
 */
static const IStorage			MyIStorage = { (IStorageVtbl *)&MyIStorageTable };





// Our IOleInPlaceFrame functions that the browser may call
HRESULT STDMETHODCALLTYPE Frame_QueryInterface(IOleInPlaceFrame FAR* This, REFIID riid, LPVOID FAR* ppvObj);
HRESULT STDMETHODCALLTYPE Frame_AddRef(IOleInPlaceFrame FAR* This);
HRESULT STDMETHODCALLTYPE Frame_Release(IOleInPlaceFrame FAR* This);
HRESULT STDMETHODCALLTYPE Frame_GetWindow(IOleInPlaceFrame FAR* This, HWND FAR* lphwnd);
HRESULT STDMETHODCALLTYPE Frame_ContextSensitiveHelp(IOleInPlaceFrame FAR* This, BOOL fEnterMode);
HRESULT STDMETHODCALLTYPE Frame_GetBorder(IOleInPlaceFrame FAR* This, LPRECT lprectBorder);
HRESULT STDMETHODCALLTYPE Frame_RequestBorderSpace(IOleInPlaceFrame FAR* This, LPCBORDERWIDTHS pborderwidths);
HRESULT STDMETHODCALLTYPE Frame_SetBorderSpace(IOleInPlaceFrame FAR* This, LPCBORDERWIDTHS pborderwidths);
HRESULT STDMETHODCALLTYPE Frame_SetActiveObject(IOleInPlaceFrame FAR* This, IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName);
HRESULT STDMETHODCALLTYPE Frame_InsertMenus(IOleInPlaceFrame FAR* This, HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths);
HRESULT STDMETHODCALLTYPE Frame_SetMenu(IOleInPlaceFrame FAR* This, HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject);
HRESULT STDMETHODCALLTYPE Frame_RemoveMenus(IOleInPlaceFrame FAR* This, HMENU hmenuShared);
HRESULT STDMETHODCALLTYPE Frame_SetStatusText(IOleInPlaceFrame FAR* This, LPCOLESTR pszStatusText);
HRESULT STDMETHODCALLTYPE Frame_EnableModeless(IOleInPlaceFrame FAR* This, BOOL fEnable);
HRESULT STDMETHODCALLTYPE Frame_TranslateAccelerator(IOleInPlaceFrame FAR* This, LPMSG lpmsg, WORD wID);

// Our IOleInPlaceFrame VTable. This is the array of pointers to the above functions in our C
// program that the browser may call in order to interact with our frame window that contains
// the browser object. We must define a particular set of functions that comprise the
// IOleInPlaceFrame set of functions (see above), and then stuff pointers to those functions
// in their respective 'slots' in this table. We want the browser to use this VTable with our
// IOleInPlaceFrame structure.
IOleInPlaceFrameVtbl MyIOleInPlaceFrameTable = {Frame_QueryInterface,
Frame_AddRef,
Frame_Release,
Frame_GetWindow,
Frame_ContextSensitiveHelp,
Frame_GetBorder,
Frame_RequestBorderSpace,
Frame_SetBorderSpace,
Frame_SetActiveObject,
Frame_InsertMenus,
Frame_SetMenu,
Frame_RemoveMenus,
Frame_SetStatusText,
Frame_EnableModeless,
Frame_TranslateAccelerator};

// We need to return an IOleInPlaceFrame struct to the browser object. And one of our IOleInPlaceFrame
// functions (Frame_GetWindow) is going to need to access our window handle. So let's create our own
// struct that starts off with an IOleInPlaceFrame struct (and that's important -- the IOleInPlaceFrame
// struct *must* be first), and then has an extra data field where we can store our own window's HWND.
//
// And because we may want to create multiple windows, each hosting its own browser object (to
// display its own web page), then we need to create a IOleInPlaceFrame struct for each window. So,
// we're not going to declare our IOleInPlaceFrame struct globally. We'll allocate it later using
// GlobalAlloc, and then stuff the appropriate HWND in it then, and also stuff a pointer to
// MyIOleInPlaceFrameTable in it. But let's just define it here.
typedef struct {
	IOleInPlaceFrame	frame;		// The IOleInPlaceFrame must be first!

	///////////////////////////////////////////////////
	// Here you add any extra variables that you need
	// to access in your IOleInPlaceFrame functions.
	// You don't want those functions to access global
	// variables, because then you couldn't use more
	// than one browser object. (ie, You couldn't have
	// multiple windows, each with its own embedded
	// browser object to display a different web page).
	//
	// So here is where I added my extra HWND that my
	// IOleInPlaceFrame function Frame_GetWindow() needs
	// to access.
	///////////////////////////////////////////////////
	HWND				window;
} _IOleInPlaceFrameEx;






// Our IOleClientSite functions that the browser may call
HRESULT STDMETHODCALLTYPE Site_QueryInterface(IOleClientSite FAR* This, REFIID riid, void ** ppvObject);
HRESULT STDMETHODCALLTYPE Site_AddRef(IOleClientSite FAR* This);
HRESULT STDMETHODCALLTYPE Site_Release(IOleClientSite FAR* This);
HRESULT STDMETHODCALLTYPE Site_SaveObject(IOleClientSite FAR* This);
HRESULT STDMETHODCALLTYPE Site_GetMoniker(IOleClientSite FAR* This, DWORD dwAssign, DWORD dwWhichMoniker, IMoniker ** ppmk);
HRESULT STDMETHODCALLTYPE Site_GetContainer(IOleClientSite FAR* This, LPOLECONTAINER FAR* ppContainer);
HRESULT STDMETHODCALLTYPE Site_ShowObject(IOleClientSite FAR* This);
HRESULT STDMETHODCALLTYPE Site_OnShowWindow(IOleClientSite FAR* This, BOOL fShow);
HRESULT STDMETHODCALLTYPE Site_RequestNewObjectLayout(IOleClientSite FAR* This);

// Our IOleClientSite VTable. This is the array of pointers to the above functions in our C
// program that the browser may call in order to interact with our frame window that contains
// the browser object. We must define a particular set of functions that comprise the
// IOleClientSite set of functions (see above), and then stuff pointers to those functions
// in their respective 'slots' in this table. We want the browser to use this VTable with our
// IOleClientSite structure.
IOleClientSiteVtbl MyIOleClientSiteTable = {Site_QueryInterface,
Site_AddRef,
Site_Release,
Site_SaveObject,
Site_GetMoniker,
Site_GetContainer,
Site_ShowObject,
Site_OnShowWindow,
Site_RequestNewObjectLayout};






// Our IDocHostUIHandler functions that the browser may call
HRESULT STDMETHODCALLTYPE UI_QueryInterface(IDocHostUIHandler FAR* This, REFIID riid, void ** ppvObject);
HRESULT STDMETHODCALLTYPE UI_AddRef(IDocHostUIHandler FAR* This);
HRESULT STDMETHODCALLTYPE UI_Release(IDocHostUIHandler FAR* This);
HRESULT STDMETHODCALLTYPE UI_ShowContextMenu(IDocHostUIHandler FAR* This, DWORD dwID, POINT __RPC_FAR *ppt, IUnknown __RPC_FAR *pcmdtReserved, IDispatch __RPC_FAR *pdispReserved);
HRESULT STDMETHODCALLTYPE UI_GetHostInfo(IDocHostUIHandler FAR* This, DOCHOSTUIINFO __RPC_FAR *pInfo);
HRESULT STDMETHODCALLTYPE UI_ShowUI(IDocHostUIHandler FAR* This, DWORD dwID, IOleInPlaceActiveObject __RPC_FAR *pActiveObject, IOleCommandTarget __RPC_FAR *pCommandTarget, IOleInPlaceFrame __RPC_FAR *pFrame, IOleInPlaceUIWindow __RPC_FAR *pDoc);
HRESULT STDMETHODCALLTYPE UI_HideUI(IDocHostUIHandler FAR* This);
HRESULT STDMETHODCALLTYPE UI_UpdateUI(IDocHostUIHandler FAR* This);
HRESULT STDMETHODCALLTYPE UI_EnableModeless(IDocHostUIHandler FAR* This, BOOL fEnable);
HRESULT STDMETHODCALLTYPE UI_OnDocWindowActivate(IDocHostUIHandler FAR* This, BOOL fActivate);
HRESULT STDMETHODCALLTYPE UI_OnFrameWindowActivate(IDocHostUIHandler FAR* This, BOOL fActivate);
HRESULT STDMETHODCALLTYPE UI_ResizeBorder(IDocHostUIHandler FAR* This, LPCRECT prcBorder, IOleInPlaceUIWindow __RPC_FAR *pUIWindow, BOOL fRameWindow);
HRESULT STDMETHODCALLTYPE UI_TranslateAccelerator(IDocHostUIHandler FAR* This, LPMSG lpMsg, const GUID __RPC_FAR *pguidCmdGroup, DWORD nCmdID);
HRESULT STDMETHODCALLTYPE UI_GetOptionKeyPath(IDocHostUIHandler FAR* This, LPOLESTR __RPC_FAR *pchKey, DWORD dw);
HRESULT STDMETHODCALLTYPE UI_GetDropTarget(IDocHostUIHandler FAR* This, IDropTarget __RPC_FAR *pDropTarget, IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget);
HRESULT STDMETHODCALLTYPE UI_GetExternal(IDocHostUIHandler FAR* This, IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);
HRESULT STDMETHODCALLTYPE UI_TranslateUrl(IDocHostUIHandler FAR* This, DWORD dwTranslate, OLECHAR __RPC_FAR *pchURLIn, OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut);
HRESULT STDMETHODCALLTYPE UI_FilterDataObject(IDocHostUIHandler FAR* This, IDataObject __RPC_FAR *pDO, IDataObject __RPC_FAR *__RPC_FAR *ppDORet);

// Our IDocHostUIHandler VTable. This is the array of pointers to the above functions in our C
// program that the browser may call in order to replace/set certain user interface considerations
// (such as whether to display a pop-up context menu when the user right-clicks on the embedded
// browser object). We must define a particular set of functions that comprise the
// IDocHostUIHandler set of functions (see above), and then stuff pointers to those functions
// in their respective 'slots' in this table. We want the browser to use this VTable with our
// IDocHostUIHandler structure.
IDocHostUIHandlerVtbl MyIDocHostUIHandlerTable =  {UI_QueryInterface,
UI_AddRef,
UI_Release,
UI_ShowContextMenu,
UI_GetHostInfo,
UI_ShowUI,
UI_HideUI,
UI_UpdateUI,
UI_EnableModeless,
UI_OnDocWindowActivate,
UI_OnFrameWindowActivate,
UI_ResizeBorder,
UI_TranslateAccelerator,
UI_GetOptionKeyPath,
UI_GetDropTarget,
UI_GetExternal,
UI_TranslateUrl,
UI_FilterDataObject};

// We'll allocate our IDocHostUIHandler object dynamically with GlobalAlloc() for reasons outlined later.



// Our IOleInPlaceSite functions that the browser may call
HRESULT STDMETHODCALLTYPE InPlace_QueryInterface(IOleInPlaceSite FAR* This, REFIID riid, void ** ppvObject);
HRESULT STDMETHODCALLTYPE InPlace_AddRef(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_Release(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_GetWindow(IOleInPlaceSite FAR* This, HWND FAR* lphwnd);
HRESULT STDMETHODCALLTYPE InPlace_ContextSensitiveHelp(IOleInPlaceSite FAR* This, BOOL fEnterMode);
HRESULT STDMETHODCALLTYPE InPlace_CanInPlaceActivate(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_OnInPlaceActivate(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_OnUIActivate(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_GetWindowContext(IOleInPlaceSite FAR* This, LPOLEINPLACEFRAME FAR* lplpFrame,LPOLEINPLACEUIWINDOW FAR* lplpDoc,LPRECT lprcPosRect,LPRECT lprcClipRect,LPOLEINPLACEFRAMEINFO lpFrameInfo);
HRESULT STDMETHODCALLTYPE InPlace_Scroll(IOleInPlaceSite FAR* This, SIZE scrollExtent);
HRESULT STDMETHODCALLTYPE InPlace_OnUIDeactivate(IOleInPlaceSite FAR* This, BOOL fUndoable);
HRESULT STDMETHODCALLTYPE InPlace_OnInPlaceDeactivate(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_DiscardUndoState(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_DeactivateAndUndo(IOleInPlaceSite FAR* This);
HRESULT STDMETHODCALLTYPE InPlace_OnPosRectChange(IOleInPlaceSite FAR* This, LPCRECT lprcPosRect);

// Our IOleInPlaceSite VTable. This is the array of pointers to the above functions in our C
// program that the browser may call in order to interact with our frame window that contains
// the browser object. We must define a particular set of functions that comprise the
// IOleInPlaceSite set of functions (see above), and then stuff pointers to those functions
// in their respective 'slots' in this table. We want the browser to use this VTable with our
// IOleInPlaceSite structure.
IOleInPlaceSiteVtbl MyIOleInPlaceSiteTable =  {InPlace_QueryInterface,
InPlace_AddRef,
InPlace_Release,
InPlace_GetWindow,
InPlace_ContextSensitiveHelp,
InPlace_CanInPlaceActivate,
InPlace_OnInPlaceActivate,
InPlace_OnUIActivate,
InPlace_GetWindowContext,
InPlace_Scroll,
InPlace_OnUIDeactivate,
InPlace_OnInPlaceDeactivate,
InPlace_DiscardUndoState,
InPlace_DeactivateAndUndo,
InPlace_OnPosRectChange};

// We need to pass our IOleClientSite structure to OleCreate (which in turn gives it to the browser).
// But the browser is also going to ask our IOleClientSite's QueryInterface() to return a pointer to
// our IOleInPlaceSite and/or IDocHostUIHandler structs. So we'll need to have those pointers handy.
// Plus, some of our IOleClientSite and IOleInPlaceSite functions will need to have the HWND to our
// window, and also a pointer to our IOleInPlaceFrame struct. So let's create a single struct that
// has the IOleClientSite, IOleInPlaceSite, IDocHostUIHandler, and IOleInPlaceFrame structs all inside
// it (so we can easily get a pointer to any one from any of those structs' functions). As long as the
// IOleClientSite struct is the very first thing in this custom struct, it's all ok. We can still pass
// it to OleCreate() and pretend that it's an ordinary IOleClientSite. We'll call this new struct a
// _IOleClientSiteEx.
//
// And because we may want to create multiple windows, each hosting its own browser object (to
// display its own web page), then we need to create a unique _IOleClientSiteEx struct for
// each window. So, we're not going to declare this struct globally. We'll allocate it later
// using GlobalAlloc, and then initialize the structs within it.

typedef struct {
	IOleInPlaceSite			inplace;	// My IOleInPlaceSite object. Must be first with in _IOleInPlaceSiteEx.

	///////////////////////////////////////////////////
	// Here you add any extra variables that you need
	// to access in your IOleInPlaceSite functions.
	//
	// So here is where I added my IOleInPlaceFrame
	// struct. If you need extra variables, add them
	// at the end.
	///////////////////////////////////////////////////
	_IOleInPlaceFrameEx		frame;		// My IOleInPlaceFrame object. Must be first within my _IOleInPlaceFrameEx
} _IOleInPlaceSiteEx;

typedef struct {
	IDocHostUIHandler		ui;			// My IDocHostUIHandler object. Must be first.

	///////////////////////////////////////////////////
	// Here you add any extra variables that you need
	// to access in your IDocHostUIHandler functions.
	///////////////////////////////////////////////////
} _IDocHostUIHandlerEx;

typedef struct {
	IOleClientSite			client;		// My IOleClientSite object. Must be first.
	_IOleInPlaceSiteEx		inplace;	// My IOleInPlaceSite object. A convenient place to put it.
	_IDocHostUIHandlerEx	ui;			// My IDocHostUIHandler object. Must be first within my _IDocHostUIHandlerEx.

	///////////////////////////////////////////////////
	// Here you add any extra variables that you need
	// to access in your IOleClientSite functions.
	///////////////////////////////////////////////////
} _IOleClientSiteEx;








// This is a simple C example. There are lots more things you can control about the browser object, but
// we don't do it in this example. _Many_ of the functions we provide below for the browser to call, will
// never actually be called by the browser in our example. Why? Because we don't do certain things
// with the browser that would require it to call those functions (even though we need to provide
// at least some stub for all of the functions).
//
// So, for these "dummy functions" that we don't expect the browser to call, we'll just stick in some
// assembly code that causes a debugger breakpoint and tells the browser object that we don't support
// the functionality. That way, if you try to do more things with the browser object, and it starts
// calling these TEXT("dummy functions"), you'll know which ones you should add more meaningful code to.
#define NOTIMPLEMENTED _ASSERT(0); return(E_NOTIMPL)





//////////////////////////////////// My IDocHostUIHandler functions  //////////////////////////////////////
// The browser object asks us for the pointer to our IDocHostUIHandler object by calling our IOleClientSite's
// QueryInterface (ie, Site_QueryInterface) and specifying a REFIID of IID_IDocHostUIHandler.
//
// NOTE: You need at least IE 4.0. Previous versions do not ask for, nor utilize, our IDocHostUIHandler functions.

HRESULT STDMETHODCALLTYPE UI_QueryInterface(IDocHostUIHandler FAR* This, REFIID riid, LPVOID FAR* ppvObj)
{
	// The browser assumes that our IDocHostUIHandler object is associated with our IOleClientSite
	// object. So it is possible that the browser may call our IDocHostUIHandler's QueryInterface()
	// to ask us to return a pointer to our IOleClientSite, in the same way that the browser calls
	// our IOleClientSite's QueryInterface() to ask for a pointer to our IDocHostUIHandler.
	//
	// Rather than duplicate much of the code in IOleClientSite's QueryInterface, let's just get
	// a pointer to our _IOleClientSiteEx object, substitute it as the 'This' arg, and call our
	// our IOleClientSite's QueryInterface. Note that since our _IDocHostUIHandlerEx is embedded right
	// inside our _IOleClientSiteEx, and comes immediately after the _IOleInPlaceSiteEx, we can employ
	// the following trickery to get the pointer to our _IOleClientSiteEx.
	return(Site_QueryInterface((IOleClientSite *)((char *)This - sizeof(IOleClientSite) - sizeof(_IOleInPlaceSiteEx)), riid, ppvObj));
}

HRESULT STDMETHODCALLTYPE UI_AddRef(IDocHostUIHandler FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE UI_Release(IDocHostUIHandler FAR* This)
{
	return(1);
}

// Called when the browser object is about to display its context menu.
HRESULT STDMETHODCALLTYPE UI_ShowContextMenu(IDocHostUIHandler FAR* This, DWORD dwID, POINT __RPC_FAR *ppt, IUnknown __RPC_FAR *pcmdtReserved, IDispatch __RPC_FAR *pdispReserved)
{
    // If desired, we can pop up your own custom context menu here. Of course,
	// we would need some way to get our window handle, so what we'd probably
	// do is like what we did with our IOleInPlaceFrame object. We'd define and create
	// our own IDocHostUIHandlerEx object with an embedded IDocHostUIHandler at the
	// start of it. Then we'd add an extra HWND field to store our window handle.
	// It could look like this:
	//
	// typedef struct _IDocHostUIHandlerEx {
	//		IDocHostUIHandler	ui;		// The IDocHostUIHandler must be first!
	//		HWND				window;
	// } IDocHostUIHandlerEx;
	//
	// Of course, we'd need a unique IDocHostUIHandlerEx object for each window, so
	// EmbedBrowserObject() would have to allocate one of those too. And that's
	// what we'd pass to our browser object (and it would in turn pass it to us
	// here, instead of 'This' being a IDocHostUIHandler *).

    // We will return S_OK to tell the browser not to display its default context menu,
	// or return S_FALSE to let the browser show its default context menu. For this
	// example, we wish to disable the browser's default context menu.
	return(S_OK);
}

// Called at initialization of the browser object UI. We can set various features of the browser object here.
HRESULT STDMETHODCALLTYPE UI_GetHostInfo(IDocHostUIHandler FAR* This, DOCHOSTUIINFO __RPC_FAR *pInfo)
{
	pInfo->cbSize = sizeof(DOCHOSTUIINFO);

	// Set some flags. We don't want any 3D border. You can do other things like hide
	// the scroll bar (DOCHOSTUIFLAG_SCROLL_NO), display picture display (DOCHOSTUIFLAG_NOPICS),
	// disable any script running when the page is loaded (DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE),
	// open a site in a new browser window when the user clicks on some link (DOCHOSTUIFLAG_OPENNEWWIN),
	// and lots of other things. See the MSDN docs on the DOCHOSTUIINFO struct passed to us.
	pInfo->dwFlags = DOCHOSTUIFLAG_NO3DBORDER;

	// Set what happens when the user double-clicks on the object. Here we use the default.
	pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

	return(S_OK);
}

// Called when the browser object shows its UI. This allows us to replace its menus and toolbars by creating our
// own and displaying them here.
HRESULT STDMETHODCALLTYPE UI_ShowUI(IDocHostUIHandler FAR* This, DWORD dwID, IOleInPlaceActiveObject __RPC_FAR *pActiveObject, IOleCommandTarget __RPC_FAR *pCommandTarget, IOleInPlaceFrame __RPC_FAR *pFrame, IOleInPlaceUIWindow __RPC_FAR *pDoc)
{
	// We've already got our own UI in place so just return S_OK to tell the browser
	// not to display its menus/toolbars. Otherwise we'd return S_FALSE to let it do
	// that.
	return(S_OK);
}

// Called when browser object hides its UI. This allows us to hide any menus/toolbars we created in ShowUI.
HRESULT STDMETHODCALLTYPE UI_HideUI(IDocHostUIHandler FAR* This)
{
	return(S_OK);
}

// Called when the browser object wants to notify us that the command state has changed. We should update any
// controls we have that are dependent upon our embedded object, such as TEXT("Back"), TEXT("Forward"), TEXT("Stop"), or "Home"
// buttons.
HRESULT STDMETHODCALLTYPE UI_UpdateUI(IDocHostUIHandler FAR* This)
{
	// We update our UI in our window message loop so we don't do anything here.
	return(S_OK);
}

// Called from the browser object's IOleInPlaceActiveObject object's EnableModeless() function. Also
// called when the browser displays a modal dialog box.
HRESULT STDMETHODCALLTYPE UI_EnableModeless(IDocHostUIHandler FAR* This, BOOL fEnable)
{
	return(S_OK);
}

// Called from the browser object's IOleInPlaceActiveObject object's OnDocWindowActivate() function.
// This informs off of when the object is getting/losing the focus.
HRESULT STDMETHODCALLTYPE UI_OnDocWindowActivate(IDocHostUIHandler FAR* This, BOOL fActivate)
{
	return(S_OK);
}

// Called from the browser object's IOleInPlaceActiveObject object's OnFrameWindowActivate() function.
HRESULT STDMETHODCALLTYPE UI_OnFrameWindowActivate(IDocHostUIHandler FAR* This, BOOL fActivate)
{
	return(S_OK);
}

// Called from the browser object's IOleInPlaceActiveObject object's ResizeBorder() function.
HRESULT STDMETHODCALLTYPE UI_ResizeBorder(IDocHostUIHandler FAR* This, LPCRECT prcBorder, IOleInPlaceUIWindow __RPC_FAR *pUIWindow, BOOL fRameWindow)
{
	return(S_OK);
}

// Called from the browser object's TranslateAccelerator routines to translate key strokes to commands.
HRESULT STDMETHODCALLTYPE UI_TranslateAccelerator(IDocHostUIHandler FAR* This, LPMSG lpMsg, const GUID __RPC_FAR *pguidCmdGroup, DWORD nCmdID)
{
	// We don't intercept any keystrokes, so we do nothing here. But for example, if we wanted to
	// override the TAB key, perhaps do something with it ourselves, and then tell the browser
	// not to do anything with this keystroke, we'd do:
	//
	//	if (pMsg && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
	//	{
	//		// Here we do something as a result of a TAB key press.
	//
	//		// Tell the browser not to do anything with it.
	//		return(S_FALSE);
	//	}
	//
	//	// Otherwise, let the browser do something with this message.
	//	return(S_OK);

	// For our example, we want to make sure that the user can invoke some key to popup the context
	// menu, so we'll tell it to ignore all messages.
	return(S_FALSE);
}

// Called by the browser object to find where the host wishes the browser to get its options in the registry.
// We can use this to prevent the browser from using its default settings in the registry, by telling it to use
// some other registry key we've setup with the options we want.
HRESULT STDMETHODCALLTYPE UI_GetOptionKeyPath(IDocHostUIHandler FAR* This, LPOLESTR __RPC_FAR *pchKey, DWORD dw)
{
	// Let the browser use its default registry settings.
	return(S_FALSE);
}

// Called by the browser object when it is used as a drop target. We can supply our own IDropTarget object,
// IDropTarget functions, and IDropTarget VTable if we want to determine what happens when someone drags and
// drops some object on our embedded browser object.
HRESULT STDMETHODCALLTYPE UI_GetDropTarget(IDocHostUIHandler FAR* This, IDropTarget __RPC_FAR *pDropTarget, IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget)
{
	// Return our IDropTarget object associated with this IDocHostUIHandler object. I don't
	// know why we don't do this via UI_QueryInterface(), but we don't.

	// NOTE: If we want/need an IDropTarget interface, then we would have had to setup our own
	// IDropTarget functions, IDropTarget VTable, and create an IDropTarget object. We'd want to put
	// a pointer to the IDropTarget object in our own custom IDocHostUIHandlerEx object (like how
	// we may add an HWND field for the use of UI_ShowContextMenu). So when we created our
	// IDocHostUIHandlerEx object, maybe we'd add a 'idrop' field to the end of it, and
	// store a pointer to our IDropTarget object there. Then we could return this pointer as so:
	//
	// *pDropTarget = ((IDocHostUIHandlerEx FAR *)This)->idrop;
    // return(S_OK);

	// But for our purposes, we don't need an IDropTarget object, so we'll tell whomever is calling
	// us that we don't have one.
    return(S_FALSE);
}

// Called by the browser when it wants a pointer to our IDispatch object. This object allows us to expose
// our own automation interface (ie, our own COM objects) to other entities that are running within the
// context of the browser so they can call our functions if they want. An example could be a javascript
// running in the URL we display could call our IDispatch functions. We'd write them so that any args passed
// to them would use the generic datatypes like a BSTR for utmost flexibility.
HRESULT STDMETHODCALLTYPE UI_GetExternal(IDocHostUIHandler FAR* This, IDispatch __RPC_FAR *__RPC_FAR *ppDispatch)
{
	// Return our IDispatch object associated with this IDocHostUIHandler object. I don't
	// know why we don't do this via UI_QueryInterface(), but we don't.

	// NOTE: If we want/need an IDispatch interface, then we would have had to setup our own
	// IDispatch functions, IDispatch VTable, and create an IDispatch object. We'd want to put
	// a pointer to the IDispatch object in our custom _IDocHostUIHandlerEx object (like how
	// we may add an HWND field for the use of UI_ShowContextMenu). So when we defined our
	// _IDocHostUIHandlerEx object, maybe we'd add a 'idispatch' field to the end of it, and
	// store a pointer to our IDispatch object there. Then we could return this pointer as so:
	//
	// *ppDispatch = ((_IDocHostUIHandlerEx FAR *)This)->idispatch;
    // return(S_OK);

	// But for our purposes, we don't need an IDispatch object, so we'll tell whomever is calling
	// us that we don't have one. Note: We must set ppDispatch to 0 if we don't return our own
	// IDispatch object.
	*ppDispatch = 0;
	return(S_FALSE);
}

/* **************************** asciiToNum() ***************************
 * Converts the string of digits (expressed in base 10) to a 32-bit
 * DWORD.
 *
 * val =	Pointer to the nul-terminated string of digits to convert.
 *
 * RETURNS: The integer value as a DWORD.
 *
 * NOTE: Skips leading spaces before the first digit.
 */

DWORD asciiToNum(OLECHAR *val)
{
	OLECHAR			chr;
	DWORD			len;

	// Result is initially 0
	len = 0;

	// Skip leading spaces
	while (*val == ' ' || *val == 0x09) val++;

	// Convert next digit
	while (*val)
	{
		chr = *(val)++ - '0';
		if ((DWORD)chr > 9) break;
		len += (len + (len << 3) + chr);
	}

	return(len);
}

// Called by the browser object to give us an opportunity to modify the URL to be loaded.
HRESULT STDMETHODCALLTYPE UI_TranslateUrl(IDocHostUIHandler *This, DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut)
{
	unsigned short	*src;
	unsigned short	*dest;
	DWORD			len;

	// Get length of URL
	src = pchURLIn;
	while ((*(src)++));
	--src;
	len = src - pchURLIn; 

	// See if the URL starts with 'app:'
	if (len >= 4 && !_wcsnicmp(pchURLIn, (wchar_t *)&AppUrl[0], 4))
	{
		// Allocate a new buffer to return an "about:blank" URL
		if ((dest = (OLECHAR *)CoTaskMemAlloc(12<<1)))
		{
			HWND	hwnd;

			*ppchURLOut = dest;

			// Return "about:blank"
			CopyMemory(dest, &Blank[0], 12<<1);

			// Convert the number after the "app:"
			len = asciiToNum(pchURLIn + 4);

			// Get our host window. That was stored in our _IOleInPlaceFrameEx
			hwnd = ((_IOleInPlaceSiteEx *)((char *)This - sizeof(_IOleInPlaceSiteEx)))->frame.window;

			// Post a message to this window using WM_APP, and pass the number converted above.
			// Do not SendMessage()!. Post instead, since the browser does not like us changing
			// the URL within this here callback.
			PostMessage(hwnd, WM_APP, (WPARAM)len, 0);

			// Tell browser that we returned a URL
			return(S_OK);
		}
	}

	// We don't need to modify the URL. Note: We need to set ppchURLOut to 0 if we don't
	// return an OLECHAR (buffer) containing a modified version of pchURLIn.
	*ppchURLOut = 0;
    return(S_FALSE);
}

// Called by the browser when it does cut/paste to the clipboard. This allows us to block certain clipboard
// formats or support additional clipboard formats.
HRESULT STDMETHODCALLTYPE UI_FilterDataObject(IDocHostUIHandler FAR* This, IDataObject __RPC_FAR *pDO, IDataObject __RPC_FAR *__RPC_FAR *ppDORet)
{
	// Return our IDataObject object associated with this IDocHostUIHandler object. I don't
	// know why we don't do this via UI_QueryInterface(), but we don't.

	// NOTE: If we want/need an IDataObject interface, then we would have had to setup our own
	// IDataObject functions, IDataObject VTable, and create an IDataObject object. We'd want to put
	// a pointer to the IDataObject object in our custom _IDocHostUIHandlerEx object (like how
	// we may add an HWND field for the use of UI_ShowContextMenu). So when we defined our
	// _IDocHostUIHandlerEx object, maybe we'd add a 'idata' field to the end of it, and
	// store a pointer to our IDataObject object there. Then we could return this pointer as so:
	//
	// *ppDORet = ((_IDocHostUIHandlerEx FAR *)This)->idata;
    // return(S_OK);

	// But for our purposes, we don't need an IDataObject object, so we'll tell whomever is calling
	// us that we don't have one. Note: We must set ppDORet to 0 if we don't return our own
	// IDataObject object.
	*ppDORet = 0;
	return(S_FALSE);
}





////////////////////////////////////// My IStorage functions  /////////////////////////////////////////
// NOTE: The browser object doesn't use the IStorage functions, so most of these are us just returning
// E_NOTIMPL so that anyone who *does* call these functions knows nothing is being done here.
//
// We give the browser object a pointer to our IStorage object when we call OleCreate().

HRESULT STDMETHODCALLTYPE Storage_QueryInterface(IStorage FAR* This, REFIID riid, LPVOID FAR* ppvObj)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_AddRef(IStorage FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE Storage_Release(IStorage FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE Storage_CreateStream(IStorage FAR* This, const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_OpenStream(IStorage FAR* This, const WCHAR * pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_CreateStorage(IStorage FAR* This, const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_OpenStorage(IStorage FAR* This, const WCHAR * pwcsName, IStorage * pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_CopyTo(IStorage FAR* This, DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude,IStorage *pstgDest)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_MoveElementTo(IStorage FAR* This, const OLECHAR *pwcsName,IStorage * pstgDest, const OLECHAR *pwcsNewName, DWORD grfFlags)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_Commit(IStorage FAR* This, DWORD grfCommitFlags)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_Revert(IStorage FAR* This)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_EnumElements(IStorage FAR* This, DWORD reserved1, void * reserved2, DWORD reserved3, IEnumSTATSTG ** ppenum)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_DestroyElement(IStorage FAR* This, const OLECHAR *pwcsName)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_RenameElement(IStorage FAR* This, const WCHAR *pwcsOldName, const WCHAR *pwcsNewName)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_SetElementTimes(IStorage FAR* This, const WCHAR *pwcsName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_SetClass(IStorage FAR* This, REFCLSID clsid)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE Storage_SetStateBits(IStorage FAR* This, DWORD grfStateBits, DWORD grfMask)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Storage_Stat(IStorage FAR* This, STATSTG * pstatstg, DWORD grfStatFlag)
{
	NOTIMPLEMENTED;
}









////////////////////////////////////// My IOleClientSite functions  /////////////////////////////////////
// We give the browser object a pointer to our IOleClientSite object when we call OleCreate() or DoVerb().

/************************* Site_QueryInterface() *************************
 * The browser object calls this when it wants a pointer to one of our
 * IOleClientSite, IDocHostUIHandler, or IOleInPlaceSite structures. They
 * are all accessible via the _IOleClientSiteEx struct we allocated in
 * EmbedBrowserObject() and passed to DoVerb() and OleCreate().
 *
 * This =		A pointer to whatever _IOleClientSiteEx struct we passed to
 *				OleCreate() or DoVerb().
 * riid =		A GUID struct that the browser passes us to clue us as to
 *				which type of struct (object) it would like a pointer
 *				returned for.
 * ppvObject =	Where the browser wants us to return a pointer to the
 *				appropriate struct. (ie, It passes us a handle to fill in).
 *
 * RETURNS: S_OK if we return the struct, or E_NOINTERFACE if we don't have
 * the requested struct.
 */

HRESULT STDMETHODCALLTYPE Site_QueryInterface(IOleClientSite FAR* This, REFIID riid, void ** ppvObject)
{
	// It just so happens that the first arg passed to us is our _IOleClientSiteEx struct we allocated
	// and passed to DoVerb() and OleCreate(). Nevermind that 'This' is declared is an IOleClientSite *.
	// Remember that in EmbedBrowserObject(), we allocated our own _IOleClientSiteEx struct, and lied
	// to OleCreate() and DoVerb() -- passing our _IOleClientSiteEx struct and saying it was an
	// IOleClientSite struct. It's ok. An _IOleClientSiteEx starts with an embedded IOleClientSite, so
	// the browser didn't mind. So that's what the browser object is passing us now. The browser doesn't
	// know that it's really an _IOleClientSiteEx struct. But we do. So we can recast it and use it as
	// so here.

	// If the browser is asking us to match IID_IOleClientSite, then it wants us to return a pointer to
	// our IOleClientSite struct. Then the browser will use the VTable in that struct to call our
	// IOleClientSite functions. It will also pass this same pointer to all of our IOleClientSite
	// functions.
	//
	// Actually, we're going to lie to the browser again. We're going to return our own _IOleClientSiteEx
	// struct, and tell the browser that it's a IOleClientSite struct. It's ok. The first thing in our
	// _IOleClientSiteEx is an embedded IOleClientSite, so the browser doesn't mind. We want the browser
	// to continue passing our _IOleClientSiteEx pointer wherever it would normally pass a IOleClientSite
	// pointer.
	// 
	// The IUnknown interface uses the same VTable as the first object in our _IOleClientSiteEx
	// struct (which happens to be an IOleClientSite). So if the browser is asking us to match
	// IID_IUnknown, then we'll also return a pointer to our _IOleClientSiteEx.

	if (!memcmp(riid, &IID_IUnknown, sizeof(GUID)) || !memcmp(riid, &IID_IOleClientSite, sizeof(GUID)))
		*ppvObject = &((_IOleClientSiteEx *)This)->client;

	// If the browser is asking us to match IID_IOleInPlaceSite, then it wants us to return a pointer to
	// our IOleInPlaceSite struct. Then the browser will use the VTable in that struct to call our
	// IOleInPlaceSite functions.  It will also pass this same pointer to all of our IOleInPlaceSite
	// functions (except for Site_QueryInterface, Site_AddRef, and Site_Release. Those will always get
	// the pointer to our _IOleClientSiteEx.
	//
	// Actually, we're going to lie to the browser. We're going to return our own _IOleInPlaceSiteEx
	// struct, and tell the browser that it's a IOleInPlaceSite struct. It's ok. The first thing in
	// our _IOleInPlaceSiteEx is an embedded IOleInPlaceSite, so the browser doesn't mind. We want the
	// browser to continue passing our _IOleInPlaceSiteEx pointer wherever it would normally pass a
	// IOleInPlaceSite pointer.
	else if (!memcmp(riid, &IID_IOleInPlaceSite, sizeof(GUID)))
		*ppvObject = &((_IOleClientSiteEx *)This)->inplace;

	// If the browser is asking us to match IID_IDocHostUIHandler, then it wants us to return a pointer to
	// our IDocHostUIHandler struct. Then the browser will use the VTable in that struct to call our
	// IDocHostUIHandler functions.  It will also pass this same pointer to all of our IDocHostUIHandler
	// functions (except for Site_QueryInterface, Site_AddRef, and Site_Release. Those will always get
	// the pointer to our _IOleClientSiteEx.
	//
	// Actually, we're going to lie to the browser. We're going to return our own _IDocHostUIHandlerEx
	// struct, and tell the browser that it's a IDocHostUIHandler struct. It's ok. The first thing in
	// our _IDocHostUIHandlerEx is an embedded IDocHostUIHandler, so the browser doesn't mind. We want the
	// browser to continue passing our _IDocHostUIHandlerEx pointer wherever it would normally pass a
	// IDocHostUIHandler pointer. My, we're really playing dirty tricks on the browser here. heheh.
	else if (!memcmp(riid, &IID_IDocHostUIHandler, sizeof(GUID)))
		*ppvObject = &((_IOleClientSiteEx *)This)->ui;

	// For other types of objects the browser wants, just report that we don't have any such objects.
	// NOTE: If you want to add additional functionality to your browser hosting, you may need to
	// provide some more objects here. You'll have to investigate what the browser is asking for
	// (ie, what REFIID it is passing).
	else
	{
		*ppvObject = 0;
		return(E_NOINTERFACE);
	}

	return(S_OK);
}

HRESULT STDMETHODCALLTYPE Site_AddRef(IOleClientSite FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE Site_Release(IOleClientSite FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE Site_SaveObject(IOleClientSite FAR* This)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Site_GetMoniker(IOleClientSite FAR* This, DWORD dwAssign, DWORD dwWhichMoniker, IMoniker ** ppmk)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Site_GetContainer(IOleClientSite FAR* This, LPOLECONTAINER FAR* ppContainer)
{
	// Tell the browser that we are a simple object and don't support a container
	*ppContainer = 0;

	return(E_NOINTERFACE);
}

HRESULT STDMETHODCALLTYPE Site_ShowObject(IOleClientSite FAR* This)
{
	return(NOERROR);
}

HRESULT STDMETHODCALLTYPE Site_OnShowWindow(IOleClientSite FAR* This, BOOL fShow)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Site_RequestNewObjectLayout(IOleClientSite FAR* This)
{
	NOTIMPLEMENTED;
}











////////////////////////////////////// My IOleInPlaceSite functions  /////////////////////////////////////
// The browser object asks us for the pointer to our IOleInPlaceSite object by calling our IOleClientSite's
// QueryInterface (ie, Site_QueryInterface) and specifying a REFIID of IID_IOleInPlaceSite.

HRESULT STDMETHODCALLTYPE InPlace_QueryInterface(IOleInPlaceSite FAR* This, REFIID riid, LPVOID FAR* ppvObj)
{
	// The browser assumes that our IOleInPlaceSite object is associated with our IOleClientSite
	// object. So it is possible that the browser may call our IOleInPlaceSite's QueryInterface()
	// to ask us to return a pointer to our IOleClientSite, in the same way that the browser calls
	// our IOleClientSite's QueryInterface() to ask for a pointer to our IOleInPlaceSite.
	//
	// Rather than duplicate much of the code in IOleClientSite's QueryInterface, let's just get
	// a pointer to our _IOleClientSiteEx object, substitute it as the 'This' arg, and call our
	// our IOleClientSite's QueryInterface. Note that since our IOleInPlaceSite is embedded right
	// inside our _IOleClientSiteEx, and comes immediately after the IOleClientSite, we can employ
	// the following trickery to get the pointer to our _IOleClientSiteEx.
	return(Site_QueryInterface((IOleClientSite *)((char *)This - sizeof(IOleClientSite)), riid, ppvObj));
}

HRESULT STDMETHODCALLTYPE InPlace_AddRef(IOleInPlaceSite FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE InPlace_Release(IOleInPlaceSite FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE InPlace_GetWindow(IOleInPlaceSite FAR* This, HWND FAR* lphwnd)
{
	// Return the HWND of the window that contains this browser object. We stored that
	// HWND in our _IOleInPlaceSiteEx struct. Nevermind that the function declaration for
	// Site_GetWindow says that 'This' is an IOleInPlaceSite *. Remember that in
	// EmbedBrowserObject(), we allocated our own _IOleInPlaceSiteEx struct which
	// contained an embedded IOleInPlaceSite struct within it. And when the browser
	// called Site_QueryInterface() to get a pointer to our IOleInPlaceSite object, we
	// returned a pointer to our _IOleClientSiteEx. The browser doesn't know this. But
	// we do. That's what we're really being passed, so we can recast it and use it as
	// so here.
	*lphwnd = ((_IOleInPlaceSiteEx FAR*)This)->frame.window;

	return(S_OK);
}

HRESULT STDMETHODCALLTYPE InPlace_ContextSensitiveHelp(IOleInPlaceSite FAR* This, BOOL fEnterMode)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE InPlace_CanInPlaceActivate(IOleInPlaceSite FAR* This)
{
	// Tell the browser we can in place activate
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE InPlace_OnInPlaceActivate(IOleInPlaceSite FAR* This)
{
	// Tell the browser we did it ok
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE InPlace_OnUIActivate(IOleInPlaceSite FAR* This)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE InPlace_GetWindowContext(IOleInPlaceSite FAR* This, LPOLEINPLACEFRAME FAR* lplpFrame, LPOLEINPLACEUIWINDOW FAR* lplpDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
	// Give the browser the pointer to our IOleInPlaceFrame struct. We stored that pointer
	// in our _IOleInPlaceSiteEx struct. Nevermind that the function declaration for
	// Site_GetWindowContext says that 'This' is an IOleInPlaceSite *. Remember that in
	// EmbedBrowserObject(), we allocated our own _IOleInPlaceSiteEx struct which
	// contained an embedded IOleInPlaceSite struct within it. And when the browser
	// called Site_QueryInterface() to get a pointer to our IOleInPlaceSite object, we
	// returned a pointer to our _IOleClientSiteEx. The browser doesn't know this. But
	// we do. That's what we're really being passed, so we can recast it and use it as
	// so here.
	//
	// Actually, we're giving the browser a pointer to our own _IOleInPlaceSiteEx struct,
	// but telling the browser that it's a IOleInPlaceSite struct. No problem. Our
	// _IOleInPlaceSiteEx starts with an embedded IOleInPlaceSite, so the browser is
	// cool with it. And we want the browser to pass a pointer to this _IOleInPlaceSiteEx
	// wherever it would pass a IOleInPlaceSite struct to our IOleInPlaceSite functions.
	*lplpFrame = (LPOLEINPLACEFRAME)&((_IOleInPlaceSiteEx *)This)->frame;

	// We have no OLEINPLACEUIWINDOW
	*lplpDoc = 0;

	// Fill in some other info for the browser
	lpFrameInfo->fMDIApp = FALSE;
	lpFrameInfo->hwndFrame = ((_IOleInPlaceFrameEx *)*lplpFrame)->window;
	lpFrameInfo->haccel = 0;
	lpFrameInfo->cAccelEntries = 0;

	// Give the browser the dimensions of where it can draw. We give it our entire window to fill.
	// We do this in InPlace_OnPosRectChange() which is called right when a window is first
	// created anyway, so no need to duplicate it here.
//	GetClientRect(lpFrameInfo->hwndFrame, lprcPosRect);
//	GetClientRect(lpFrameInfo->hwndFrame, lprcClipRect);

	return(S_OK);
}

HRESULT STDMETHODCALLTYPE InPlace_Scroll(IOleInPlaceSite FAR* This, SIZE scrollExtent)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE InPlace_OnUIDeactivate(IOleInPlaceSite FAR* This, BOOL fUndoable)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE InPlace_OnInPlaceDeactivate(IOleInPlaceSite FAR* This)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE InPlace_DiscardUndoState(IOleInPlaceSite FAR* This)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE InPlace_DeactivateAndUndo(IOleInPlaceSite FAR* This)
{
	NOTIMPLEMENTED;
}

// Called when the position of the browser object is changed, such as when we call the IWebBrowser2's put_Width(),
// put_Height(), put_Left(), or put_Right().
HRESULT STDMETHODCALLTYPE InPlace_OnPosRectChange(IOleInPlaceSite FAR* This, LPCRECT lprcPosRect)
{
	IOleObject			*browserObject;
	IOleInPlaceObject	*inplace;

	// We need to get the browser's IOleInPlaceObject object so we can call its SetObjectRects
	// function.
	browserObject = *((IOleObject **)((char *)This - sizeof(IOleObject *) - sizeof(IOleClientSite)));
	if (!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IOleInPlaceObject, (void**)&inplace))
	{
		// Give the browser the dimensions of where it can draw.
		inplace->lpVtbl->SetObjectRects(inplace, lprcPosRect, lprcPosRect);
	}

	return(S_OK);
}







////////////////////////////////////// My IOleInPlaceFrame functions  /////////////////////////////////////////

HRESULT STDMETHODCALLTYPE Frame_QueryInterface(IOleInPlaceFrame FAR* This, REFIID riid, LPVOID FAR* ppvObj)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Frame_AddRef(IOleInPlaceFrame FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE Frame_Release(IOleInPlaceFrame FAR* This)
{
	return(1);
}

HRESULT STDMETHODCALLTYPE Frame_GetWindow(IOleInPlaceFrame FAR* This, HWND FAR* lphwnd)
{
	// Give the browser the HWND to our window that contains the browser object. We
	// stored that HWND in our IOleInPlaceFrame struct. Nevermind that the function
	// declaration for Frame_GetWindow says that 'This' is an IOleInPlaceFrame *. Remember
	// that in EmbedBrowserObject(), we allocated our own IOleInPlaceFrameEx struct which
	// contained an embedded IOleInPlaceFrame struct within it. And then we lied when
	// Site_GetWindowContext() returned that IOleInPlaceFrameEx. So that's what the
	// browser is passing us. It doesn't know that. But we do. So we can recast it and
	// use it as so here.
	*lphwnd = ((_IOleInPlaceFrameEx *)This)->window;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE Frame_ContextSensitiveHelp(IOleInPlaceFrame FAR* This, BOOL fEnterMode)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Frame_GetBorder(IOleInPlaceFrame FAR* This, LPRECT lprectBorder)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Frame_RequestBorderSpace(IOleInPlaceFrame FAR* This, LPCBORDERWIDTHS pborderwidths)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Frame_SetBorderSpace(IOleInPlaceFrame FAR* This, LPCBORDERWIDTHS pborderwidths)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Frame_SetActiveObject(IOleInPlaceFrame FAR* This, IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE Frame_InsertMenus(IOleInPlaceFrame FAR* This, HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Frame_SetMenu(IOleInPlaceFrame FAR* This, HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE Frame_RemoveMenus(IOleInPlaceFrame FAR* This, HMENU hmenuShared)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE Frame_SetStatusText(IOleInPlaceFrame FAR* This, LPCOLESTR pszStatusText)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE Frame_EnableModeless(IOleInPlaceFrame FAR* This, BOOL fEnable)
{
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE Frame_TranslateAccelerator(IOleInPlaceFrame FAR* This, LPMSG lpmsg, WORD wID)
{
	NOTIMPLEMENTED;
}
													

/*************************** UnEmbedBrowserObject() ************************
 * Called to detach the browser object from our host window, and free its
 * resources, right before we destroy our window.
 *
 * hwnd =		Handle to the window hosting the browser object.
 *
 * NOTE: The pointer to the browser object must have been stored in the
 * window's USERDATA field. In other words, don't call UnEmbedBrowserObject().
 * with a HWND that wasn't successfully passed to EmbedBrowserObject().
 */

void WINAPI UnEmbedBrowserObject(HWND hwnd)
{
	IOleObject	**browserHandle;
	IOleObject	*browserObject;

	// Retrieve the browser object's pointer we stored in our window's GWL_USERDATA when we
	// initially attached the browser object to this window. If 0, you may have called this
	// for a window that wasn't successfully passed to EmbedBrowserObject(). Bad boy! Or, we
	// may have failed the EmbedBrowserObject() call in WM_CREATE, in which case, our window
	// may get a WM_DESTROY which could call this a second time (ie, since we may call
	// UnEmbedBrowserObject in EmbedBrowserObject).
	if ((browserHandle = (IOleObject **)GetWindowLong(hwnd, GWL_USERDATA)))
	{
		// Unembed the browser object, and release its resources.
		browserObject = *browserHandle;
		browserObject->lpVtbl->Close(browserObject, OLECLOSE_NOSAVE);
		browserObject->lpVtbl->Release(browserObject);

		// Zero out the pointer just in case UnEmbedBrowserObject is called again for this window
		SetWindowLong(hwnd, GWL_USERDATA, 0);
	}
}

/******************************* DisplayHTMLStr() ****************************
 * Takes a string containing some HTML BODY, and displays it in the specified
 * window. For example, perhaps you want to display the HTML text of...
 *
 * <P>This is a picture.<P><IMG src="mypic.jpg">
 *
 * hwnd =		Handle to the window hosting the browser object.
 * string =		Pointer to nul-terminated string containing the HTML BODY.
 *				(NOTE: No <BODY></BODY> tags are required in the string).
 *
 * RETURNS: 0 if success, or non-zero if an error.
 *
 * NOTE: EmbedBrowserObject() must have been successfully called once with the
 * specified window, prior to calling this function. You need call
 * EmbedBrowserObject() once only, and then you can make multiple calls to
 * this function to display numerous pages in the specified window.
 */

long WINAPI DisplayHTMLStr(HWND hwnd, LPCTSTR string)
{	
	IWebBrowser2	*webBrowser2;
	LPDISPATCH		lpDispatch;
	IHTMLDocument2	*htmlDoc2;
	IOleObject		*browserObject;
	SAFEARRAY		*sfArray;
	VARIANT			myURL;
	VARIANT			*pVar;
	BSTR			bstr;

	// Retrieve the browser object's pointer we stored in our window's GWL_USERDATA when
	// we initially attached the browser object to this window.
	browserObject = *((IOleObject **)GetWindowLong(hwnd, GWL_USERDATA));

	// Assume an error.
	bstr = 0;

	// We want to get the base address (ie, a pointer) to the IWebBrowser2 object embedded within the browser
	// object, so we can call some of the functions in the former's table.
	if (!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IWebBrowser2, (void**)&webBrowser2))
	{
		// Ok, now the pointer to our IWebBrowser2 object is in 'webBrowser2', and so its VTable is
		// webBrowser2->lpVtbl.

		// Call the IWebBrowser2 object's get_Document so we can get its DISPATCH object. I don't know why you
		// don't get the DISPATCH object via the browser object's QueryInterface(), but you don't.
		lpDispatch = 0;
		webBrowser2->lpVtbl->get_Document(webBrowser2, &lpDispatch);
		if (!lpDispatch)
		{
			// Before we can get_Document(), we actually need to have some HTML page loaded in the browser. So,
			// let's load an empty HTML page. Then, once we have that empty page, we can get_Document() and
			// write() to stuff our HTML string into it.
			VariantInit(&myURL);
			myURL.vt = VT_BSTR;
			myURL.bstrVal = SysAllocString(&Blank[0]);

			// Call the Navigate2() function to actually display the page.
			webBrowser2->lpVtbl->Navigate2(webBrowser2, &myURL, 0, 0, 0, 0);

			// Free any resources (including the BSTR).
			VariantClear(&myURL);
		}

		// Call the IWebBrowser2 object's get_Document so we can get its DISPATCH object. I don't know why you
		// don't get the DISPATCH object via the browser object's QueryInterface(), but you don't.
		if (!webBrowser2->lpVtbl->get_Document(webBrowser2, &lpDispatch))
		{
			// We want to get a pointer to the IHTMLDocument2 object embedded within the DISPATCH
			// object, so we can call some of the functions in the former's table.
			if (!lpDispatch->lpVtbl->QueryInterface(lpDispatch, &IID_IHTMLDocument2, (void**)&htmlDoc2))
			{
				// Ok, now the pointer to our IHTMLDocument2 object is in 'htmlDoc2', and so its VTable is
				// htmlDoc2->lpVtbl.

				// Our HTML must be in the form of a BSTR. And it must be passed to write() in an
				// array of "VARIENT" structs. So let's create all that.
				if ((sfArray = SafeArrayCreate(VT_VARIANT, 1, (SAFEARRAYBOUND *)&ArrayBound)))
				{
					if (!SafeArrayAccessData(sfArray, (void**)&pVar))
					{
						pVar->vt = VT_BSTR;
#ifndef UNICODE
						{
						wchar_t		*buffer;
						DWORD		size;

						size = MultiByteToWideChar(CP_ACP, 0, string, -1, 0, 0);
						if (!(buffer = (wchar_t *)GlobalAlloc(GMEM_FIXED, sizeof(wchar_t) * size))) goto bad;
						MultiByteToWideChar(CP_ACP, 0, string, -1, buffer, size);
						bstr = SysAllocString(buffer);
						GlobalFree(buffer);
						}
#else
						bstr = SysAllocString(string);
#endif
						// Store our BSTR pointer in the VARIENT.
						if ((pVar->bstrVal = bstr))
						{
							// Pass the VARIENT with its BSTR to write() in order to shove our desired HTML string
							// into the body of that empty page we created above.
							htmlDoc2->lpVtbl->write(htmlDoc2, sfArray);

							// Close the document. If we don't do this, subsequent calls to DisplayHTMLStr
							// would append to the current contents of the page
							htmlDoc2->lpVtbl->close(htmlDoc2);

							// Normally, we'd need to free our BSTR, but SafeArrayDestroy() does it for us
//							SysFreeString(bstr);
						}
					}

					// Free the array. This also frees the VARIENT that SafeArrayAccessData created for us,
					// and even frees the BSTR we allocated with SysAllocString
					SafeArrayDestroy(sfArray);
				}

				// Release the IHTMLDocument2 object.
bad:			htmlDoc2->lpVtbl->Release(htmlDoc2);
			}

			// Release the DISPATCH object.
			lpDispatch->lpVtbl->Release(lpDispatch);
		}

		// JAYCEE MODIFIED (NOT NEED - It's a Error
		//webBrowser2->lpVtbl->Navigate2(webBrowser2, pVar, 0, 0, 0, 0);
		// Release the IWebBrowser2 object.
		webBrowser2->lpVtbl->Release(webBrowser2);
	}

	// No error?
	if (bstr) return(0);

	// An error
	return(-1);
}






/******************************* DisplayHTMLPage() ****************************
 * Displays a URL, or HTML file on disk.
 *
 * hwnd =		Handle to the window hosting the browser object.
 * webPageName =	Pointer to nul-terminated name of the URL/file.
 *
 * RETURNS: 0 if success, or non-zero if an error.
 *
 * NOTE: EmbedBrowserObject() must have been successfully called once with the
 * specified window, prior to calling this function. You need call
 * EmbedBrowserObject() once only, and then you can make multiple calls to
 * this function to display numerous pages in the specified window.
 */

long WINAPI DisplayHTMLPage(HWND hwnd, LPCTSTR webPageName)
{
	IWebBrowser2	*webBrowser2;
	VARIANT			myURL;
	IOleObject		*browserObject;
	LPDISPATCH lpDispatch = 0;
	IHTMLDocument2* pDoc = NULL; 
	IHTMLElement* pElement = NULL; 
	IHTMLBodyElement* pBodyElement = NULL; 
	VARIANT v;
	VARIANT s;
	
	// Retrieve the browser object's pointer we stored in our window's GWL_USERDATA when
	// we initially attached the browser object to this window.
	browserObject = *((IOleObject **)GetWindowLong(hwnd, GWL_USERDATA));

	// We want to get the base address (ie, a pointer) to the IWebBrowser2 object embedded within the browser
	// object, so we can call some of the functions in the former's table.
	if (!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IWebBrowser2, (void**)&webBrowser2))
	{
		// Ok, now the pointer to our IWebBrowser2 object is in 'webBrowser2', and so its VTable is
		// webBrowser2->lpVtbl.

		// Our URL (ie, web address, such as "http://www.microsoft.com" or an HTM filename on disk
		// such as "c:\myfile.htm") must be passed to the IWebBrowser2's Navigate2() function as a BSTR.
		// A BSTR is like a pascal version of a double-byte character string. In other words, the
		// first unsigned short is a count of how many characters are in the string, and then this
		// is followed by those characters, each expressed as an unsigned short (rather than a
		// char). The string is not nul-terminated. The OS function SysAllocString can allocate and
		// copy a UNICODE C string to a BSTR. Of course, we'll need to free that BSTR after we're done
		// with it. If we're not using UNICODE, we first have to convert to a UNICODE string.
		//
		// What's more, our BSTR needs to be stuffed into a VARIENT struct, and that VARIENT struct is
		// then passed to Navigate2(). Why? The VARIENT struct makes it possible to define generic
		// 'datatypes' that can be used with all languages. Not all languages support things like
		// nul-terminated C strings. So, by using a VARIENT, whose first field tells what sort of
		// data (ie, string, float, etc) is in the VARIENT, COM interfaces can be used by just about
		// any language.
		VariantInit(&myURL);
		myURL.vt = VT_BSTR;

#ifndef UNICODE
		{
		wchar_t		*buffer;
		DWORD		size;

		size = MultiByteToWideChar(CP_ACP, 0, webPageName, -1, 0, 0);
		if (!(buffer = (wchar_t *)GlobalAlloc(GMEM_FIXED, sizeof(wchar_t) * size))) goto badalloc;
		MultiByteToWideChar(CP_ACP, 0, webPageName, -1, buffer, size);
		myURL.bstrVal = SysAllocString(buffer);
		GlobalFree(buffer);
		}
#else
		myURL.bstrVal = SysAllocString(webPageName);
#endif
		if (!myURL.bstrVal)
		{
badalloc:	webBrowser2->lpVtbl->Release(webBrowser2);
			return(-6);
		}

		// Call the Navigate2() function to actually display the page.
		webBrowser2->lpVtbl->Navigate2(webBrowser2, &myURL, 0, 0, 0, 0);

		// Free any resources (including the BSTR we allocated above).
		VariantClear(&myURL);

		//{{ 스크롤 없애기 - 문서 로드 완료 이벤트 후에 들어가야됨
	/*	webBrowser2->lpVtbl->get_Document(webBrowser2, &lpDispatch);
		if ( lpDispatch )
		{
			VariantInit(&v);
			lpDispatch->lpVtbl->QueryInterface(lpDispatch, &IID_IHTMLDocument2, (void**)&pDoc);
			pDoc->lpVtbl->get_body( pDoc, &pElement);
			if( pElement )
			{
				pElement->lpVtbl->QueryInterface( pElement, &IID_IHTMLBodyElement, (void**)&pBodyElement); 
				if (pBodyElement)
				{ 
					VariantInit(&s);
					s.vt = VT_BSTR;
					s.bstrVal = SysAllocString("no");

					pBodyElement->lpVtbl->put_scroll( pBodyElement, s.bstrVal ); //show : auto 
					pBodyElement->lpVtbl->Release(pBodyElement);

					VariantClear(&s);
				}
				pElement->lpVtbl->Release(pElement); 
				pDoc->lpVtbl->Release(pDoc); 
				lpDispatch->lpVtbl->Release(lpDispatch);
			}
		}*/

		// We no longer need the IWebBrowser2 object (ie, we don't plan to call any more functions in it,
		// so we can release our hold on it). Note that we'll still maintain our hold on the browser
		// object.
		webBrowser2->lpVtbl->Release(webBrowser2);

		// Success
		return(0);
	}

	return(-5);
}




/******************************* DoPageAction() **************************
 * Implements the functionality of a "Back". TEXT("Forward"), TEXT("Home"), TEXT("Search"),
 * TEXT("Refresh"), or "Stop" button.
 *
 * hwnd =		Handle to the window hosting the browser object.
 * action =		One of the following:
 *				0 = Move back to the previously viewed web page.
 *				1 = Move forward to the previously viewed web page.
 *				2 = Move to the home page.
 *				3 = Search.
 *				4 = Refresh the page.
 *				5 = Stop the currently loading page.
 *
 * NOTE: EmbedBrowserObject() must have been successfully called once with the
 * specified window, prior to calling this function. You need call
 * EmbedBrowserObject() once only, and then you can make multiple calls to
 * this function to display numerous pages in the specified window.
 */

void WINAPI DoPageAction(HWND hwnd, DWORD action)
{	
	IWebBrowser2	*webBrowser2;
	IOleObject		*browserObject;

	// Retrieve the browser object's pointer we stored in our window's GWL_USERDATA when
	// we initially attached the browser object to this window.
	browserObject = *((IOleObject **)GetWindowLong(hwnd, GWL_USERDATA));

	// We want to get the base address (ie, a pointer) to the IWebBrowser2 object embedded within the browser
	// object, so we can call some of the functions in the former's table.
	if (!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IWebBrowser2, (void**)&webBrowser2))
	{
		// Ok, now the pointer to our IWebBrowser2 object is in 'webBrowser2', and so its VTable is
		// webBrowser2->lpVtbl.

		// Call the desired function
		switch (action)
		{
			case WEBPAGE_GOBACK:
			{
				// Call the IWebBrowser2 object's GoBack function.
				webBrowser2->lpVtbl->GoBack(webBrowser2);
				break;
			}

			case WEBPAGE_GOFORWARD:
			{
				// Call the IWebBrowser2 object's GoForward function.
				webBrowser2->lpVtbl->GoForward(webBrowser2);
				break;
			}

			case WEBPAGE_GOHOME:
			{
				// Call the IWebBrowser2 object's GoHome function.
				webBrowser2->lpVtbl->GoHome(webBrowser2);
				break;
			}

			case WEBPAGE_SEARCH:
			{
				// Call the IWebBrowser2 object's GoSearch function.
				webBrowser2->lpVtbl->GoSearch(webBrowser2);
				break;
			}

			case WEBPAGE_REFRESH:
			{
				// Call the IWebBrowser2 object's Refresh function.
				webBrowser2->lpVtbl->Refresh(webBrowser2);
			}

			case WEBPAGE_STOP:
			{
				// Call the IWebBrowser2 object's Stop function.
				webBrowser2->lpVtbl->Stop(webBrowser2);
			}
		}

		// Release the IWebBrowser2 object.
		webBrowser2->lpVtbl->Release(webBrowser2);
	}
}





/******************************* ResizeBrowser() ****************************
 * Resizes the browser object for the specified window to the specified
 * width and height.
 *
 * hwnd =			Handle to the window hosting the browser object.
 * width =			Width.
 * height =			Height.
 *
 * NOTE: EmbedBrowserObject() must have been successfully called once with the
 * specified window, prior to calling this function. You need call
 * EmbedBrowserObject() once only, and then you can make multiple calls to
 * this function to resize the browser object.
 */

void WINAPI ResizeBrowser(HWND hwnd, DWORD width, DWORD height)
{
	IWebBrowser2	*webBrowser2;
	IOleObject		*browserObject;

	// Retrieve the browser object's pointer we stored in our window's GWL_USERDATA when
	// we initially attached the browser object to this window.
	browserObject = *((IOleObject **)GetWindowLong(hwnd, GWL_USERDATA));

	// We want to get the base address (ie, a pointer) to the IWebBrowser2 object embedded within the browser
	// object, so we can call some of the functions in the former's table.
	if (!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IWebBrowser2, (void**)&webBrowser2))
	{
		// Ok, now the pointer to our IWebBrowser2 object is in 'webBrowser2', and so its VTable is
		// webBrowser2->lpVtbl.

		// Call are put_Width() and put_Height() to set the new width/height.
		webBrowser2->lpVtbl->put_Width(webBrowser2, width);
		webBrowser2->lpVtbl->put_Height(webBrowser2, height);

		// We no longer need the IWebBrowser2 object (ie, we don't plan to call any more functions in it,
		// so we can release our hold on it). Note that we'll still maintain our hold on the browser
		// object.
		webBrowser2->lpVtbl->Release(webBrowser2);
	}
}





/***************************** EmbedBrowserObject() **************************
 * Puts the browser object inside our host window, and save a pointer to this
 * window's browser object in the window's GWL_USERDATA field.
 *
 * hwnd =		Handle of our window into which we embed the browser object.
 *
 * RETURNS: 0 if success, or non-zero if an error.
 *
 * NOTE: We tell the browser object to occupy the entire client area of the
 * window.
 *
 * NOTE: No HTML page will be displayed here. We can do that with a subsequent
 * call to either DisplayHTMLPage() or DisplayHTMLStr(). This is merely once-only
 * initialization for using the browser object. In a nutshell, what we do
 * here is get a pointer to the browser object in our window's GWL_USERDATA
 * so we can access that object's functions whenever we want, and we also pass
 * pointers to our IOleClientSite, IOleInPlaceFrame, and IStorage structs so that
 * the browser can call our functions in our struct's VTables.
 */

long WINAPI EmbedBrowserObject(HWND hwnd)
{
	IOleObject			*browserObject;
	IWebBrowser2		*webBrowser2;
	RECT				rect;
	char				*ptr;
	_IOleClientSiteEx	*_iOleClientSiteEx;

	// Our IOleClientSite, IOleInPlaceSite, and IOleInPlaceFrame functions need to get our window handle. We
	// could store that in some global. But then, that would mean that our functions would work with only that
	// one window. If we want to create multiple windows, each hosting its own browser object (to display its
	// own web page), then we need to create unique IOleClientSite, IOleInPlaceSite, and IOleInPlaceFrame
	// structs for each window. And we'll put an extra field at the end of those structs to store our extra
	// data such as a window handle. So, our functions won't have to touch global data, and can therefore be
	// re-entrant and work with multiple objects/windows.
	//
	// Remember that a pointer to our IOleClientSite we create here will be passed as the first arg to every
	// one of our IOleClientSite functions. Ditto with the IOleInPlaceFrame object we create here, and the
	// IOleInPlaceFrame functions. So, our functions are able to retrieve the window handle we'll store here,
	// and then, they'll work with all such windows containing a browser control.
	//
	// Furthermore, since the browser will be calling our IOleClientSite's QueryInterface to get a pointer to
	// our IOleInPlaceSite and IDocHostUIHandler objects, that means that our IOleClientSite QueryInterface
	// must have an easy way to grab those pointers. Probably the easiest thing to do is just embed our
	// IOleInPlaceSite and IDocHostUIHandler objects inside of an extended IOleClientSite which we'll call
	// a _IOleClientSiteEx. As long as they come after the pointer to the IOleClientSite VTable, then we're
	// ok.
	//
	// Of course, we need to GlobalAlloc the above structs now. We'll just get all 4 with a single call to
	// GlobalAlloc, especially since 3 of them are all contained inside of our _IOleClientSiteEx anyway.
	//
	// So, we're not actually allocating separate IOleClientSite, IOleInPlaceSite, IOleInPlaceFrame and
	// IDocHostUIHandler structs.
	//
	// One final thing. We're going to allocate extra room to store the pointer to the browser object.
	if (!(ptr = (char *)GlobalAlloc(GMEM_FIXED, sizeof(_IOleClientSiteEx) + sizeof(IOleObject *))))
		return(-1);

	// Initialize our IOleClientSite object with a pointer to our IOleClientSite VTable.
	_iOleClientSiteEx = (_IOleClientSiteEx *)(ptr + sizeof(IOleObject *));
	_iOleClientSiteEx->client.lpVtbl = &MyIOleClientSiteTable;

	// Initialize our IOleInPlaceSite object with a pointer to our IOleInPlaceSite VTable.
	_iOleClientSiteEx->inplace.inplace.lpVtbl = &MyIOleInPlaceSiteTable;

	// Initialize our IOleInPlaceFrame object with a pointer to our IOleInPlaceFrame VTable.
	_iOleClientSiteEx->inplace.frame.frame.lpVtbl = &MyIOleInPlaceFrameTable;

	// Save our HWND (in the IOleInPlaceFrame object) so our IOleInPlaceFrame functions can retrieve it.
	_iOleClientSiteEx->inplace.frame.window = hwnd;

	// Initialize our IDocHostUIHandler object with a pointer to our IDocHostUIHandler VTable.
	_iOleClientSiteEx->ui.ui.lpVtbl = &MyIDocHostUIHandlerTable;

	// Get a pointer to the browser object and lock it down (so it doesn't "disappear" while we're using
	// it in this program). We do this by calling the OS function OleCreate().
	//	
	// NOTE: We need this pointer to interact with and control the browser. With normal WIN32 controls such as a
	// Static, Edit, Combobox, etc, you obtain an HWND and send messages to it with SendMessage(). Not so with
	// the browser object. You need to get a pointer to its "base structure" (as returned by OleCreate()). This
	// structure contains an array of pointers to functions you can call within the browser object. Actually, the
	// base structure contains a 'lpVtbl' field that is a pointer to that array. We'll call the array a 'VTable'.
	//
	// For example, the browser object happens to have a SetHostNames() function we want to call. So, after we
	// retrieve the pointer to the browser object (in a local we'll name 'browserObject'), then we can call that
	// function, and pass it args, as so:
	//
	// browserObject->lpVtbl->SetHostNames(browserObject, SomeString, SomeString);
	//
	// There's our pointer to the browser object in 'browserObject'. And there's the pointer to the browser object's
	// VTable in 'browserObject->lpVtbl'. And the pointer to the SetHostNames function happens to be stored in an
	// field named 'SetHostNames' within the VTable. So we are actually indirectly calling SetHostNames by using
	// a pointer to it. That's how you use a VTable.
	//
	// NOTE: We pass our _IOleClientSiteEx struct and lie -- saying that it's a IOleClientSite. It's ok. A
	// _IOleClientSiteEx struct starts with an embedded IOleClientSite. So the browser won't care, and we want
	// this extended struct passed to our IOleClientSite functions.

	if (!OleCreate(&CLSID_WebBrowser, &IID_IOleObject, OLERENDER_DRAW, 0, (IOleClientSite *)_iOleClientSiteEx, (IStorage *)&MyIStorage, (void**)&browserObject))
	{
		// Ok, we now have the pointer to the browser object in 'browserObject'. Let's save this in the
		// memory block we allocated above, and then save the pointer to that whole thing in our window's
		// USERDATA field. That way, if we need multiple windows each hosting its own browser object, we can
		// call EmbedBrowserObject() for each one, and easily associate the appropriate browser object with
		// its matching window and its own objects containing per-window data.
		*((IOleObject **)ptr) = browserObject;
		SetWindowLong(hwnd, GWL_USERDATA, (LONG)ptr);

		// We can now call the browser object's SetHostNames function. SetHostNames lets the browser object know our
		// application's name and the name of the document in which we're embedding the browser. (Since we have no
		// document name, we'll pass a 0 for the latter). When the browser object is opened for editing, it displays
		// these names in its titlebar.
		//	
		// We are passing 3 args to SetHostNames. You'll note that the first arg to SetHostNames is the base
		// address of our browser control. This is something that you always have to remember when working in C
		// (as opposed to C++). When calling a VTable function, the first arg to that function must always be the
		// structure which contains the VTable. (In this case, that's the browser control itself). Why? That's
		// because that function is always assumed to be written in C++. And the first argument to any C++ function
		// must be its 'this' pointer (ie, the base address of its class, which in this case is our browser object
		// pointer). In C++, you don't have to pass this first arg, because the C++ compiler is smart enough to
		// produce an executable that always adds this first arg. In fact, the C++ compiler is smart enough to
		// know to fetch the function pointer from the VTable, so you don't even need to reference that. In other
		// words, the C++ equivalent code would be:
		//
		// browserObject->SetHostNames(L"My Host Name", 0);
		//
		// So, when you're trying to convert C++ code to C, always remember to add this first arg whenever you're
		// dealing with a VTable (ie, the field is usually named 'lpVtbl') in the standard objects, and also add
		// the reference to the VTable itself.
		//
		// Oh yeah, the L is because we need UNICODE strings. And BTW, the host and document names can be anything
		// you want.

		browserObject->lpVtbl->SetHostNames(browserObject, L"My Host Name", 0);

		GetClientRect(hwnd, &rect);

		// Let browser object know that it is embedded in an OLE container.
		if (!OleSetContainedObject((struct IUnknown *)browserObject, TRUE) &&

			// Set the display area of our browser control the same as our window's size
			// and actually put the browser object into our window.
			!browserObject->lpVtbl->DoVerb(browserObject, OLEIVERB_SHOW, NULL, (IOleClientSite *)_iOleClientSiteEx, -1, hwnd, &rect) &&

			// Ok, now things may seem to get even trickier, One of those function pointers in the browser's VTable is
			// to the QueryInterface() function. What does this function do? It lets us grab the base address of any
			// other object that may be embedded within the browser object. And this other object has its own VTable
			// containing pointers to more functions we can call for that object.
			//
			// We want to get the base address (ie, a pointer) to the IWebBrowser2 object embedded within the browser
			// object, so we can call some of the functions in the former's table. For example, one IWebBrowser2 function
			// we intend to call below will be Navigate2(). So we call the browser object's QueryInterface to get our
			// pointer to the IWebBrowser2 object.
			!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IWebBrowser2, (void**)&webBrowser2))
		{
			// Ok, now the pointer to our IWebBrowser2 object is in 'webBrowser2', and so its VTable is
			// webBrowser2->lpVtbl.

			// Let's call several functions in the IWebBrowser2 object to position the browser display area
			// in our window. The functions we call are put_Left(), put_Top(), put_Width(), and put_Height().
			// Note that we reference the IWebBrowser2 object's VTable to get pointers to those functions. And
			// also note that the first arg we pass to each is the pointer to the IWebBrowser2 object.
			webBrowser2->lpVtbl->put_Left(webBrowser2, 0);
			webBrowser2->lpVtbl->put_Top(webBrowser2, 0);
			webBrowser2->lpVtbl->put_Width(webBrowser2, rect.right);
			webBrowser2->lpVtbl->put_Height(webBrowser2, rect.bottom);
		
			// We no longer need the IWebBrowser2 object (ie, we don't plan to call any more functions in it
			// right now, so we can release our hold on it). Note that we'll still maintain our hold on the
			// browser object until we're done with that object.
			webBrowser2->lpVtbl->Release(webBrowser2);

			// Success
			return(0);
		}

		// Something went wrong!
		UnEmbedBrowserObject(hwnd);
		return(-3);
	}

	GlobalFree(ptr);
	return(-2);
}

DWORD InitializeWebEvents( HWND hWnd )
{
	// This function will connect our event sink to the web browser control
	// Upon completion we should start receving events.
	// The function returns an advise cookie. This cookie should be passed
	// to the DestroyWebEvents function to cleanup the event handler
	// before the web browser object is destroyed.
	// A return value of 0 means failure.

	_DWebBrowserEvents2Ex      *WebEventsEx;
	IOleObject	           *browserObject;
	HRESULT 	           hret;
	IConnectionPoint           *pConnectionPoint;
	IConnectionPointContainer  *pConnectionPointContainer;
	DWORD                       dwAdviseCookie = 0;


	// Retrieve the browser object's pointer we stored in our window's GWL_USERDATA when
	// we initially attached the browser object to this window.
	browserObject = *((IOleObject **)GetWindowLong(hWnd, GWL_USERDATA));


	// Allocate memory for our event sink object
	if ( !(WebEventsEx = (_DWebBrowserEvents2Ex *) GlobalAlloc(GMEM_FIXED, sizeof(_DWebBrowserEvents2Ex) ) ) ){
		return 0;
	}

	// Initialize the _DWebBrowserEvents2Ex object 
	WebEventsEx->WebEventsObj.lpVtbl = &MyDWebBrowserEvents2Vtbl;
	WebEventsEx->refCount = 0;

	// Get the connection point container
	hret = browserObject->lpVtbl->QueryInterface(browserObject,&IID_IConnectionPointContainer, (void**)(&pConnectionPointContainer));

	if (hret == S_OK) {
		// Get the appropriate connection point
		hret = pConnectionPointContainer->lpVtbl->FindConnectionPoint(pConnectionPointContainer,&DIID_DWebBrowserEvents2, &pConnectionPoint);

		if (hret == S_OK) {
			// Advise the connection point of our event sink
			hret = pConnectionPoint->lpVtbl->Advise(pConnectionPoint, (IUnknown *) WebEventsEx, &dwAdviseCookie);
			pConnectionPoint->lpVtbl->Release(pConnectionPoint);
		}

		pConnectionPointContainer->lpVtbl->Release(pConnectionPointContainer);

	}

	if (dwAdviseCookie == 0) {
		// connection failed - free our event sink memory
		GlobalFree(WebEventsEx);
		return 0;
	}

	return dwAdviseCookie;

}

BOOL DestroyWebEvents(HWND hwnd, DWORD dwAdviseCookie)
{
	IOleObject	           *browserObject;
	HRESULT 	           hret;
	IConnectionPoint           *pConnectionPoint;
	IConnectionPointContainer  *pConnectionPointContainer;

	// Get browser object
	browserObject = *((IOleObject **)GetWindowLong(hwnd, GWL_USERDATA));

	// Get the connection point container
	hret = browserObject->lpVtbl->QueryInterface(browserObject,&IID_IConnectionPointContainer, (void**)(&pConnectionPointContainer));

	if (hret == S_OK) {
		// Get the appropriate connection point
		hret = pConnectionPointContainer->lpVtbl->FindConnectionPoint(pConnectionPointContainer,&DIID_DWebBrowserEvents2, &pConnectionPoint);

		if (hret == S_OK) {
			// Unadvise the connection point of our event sink
			hret = pConnectionPoint->lpVtbl->Unadvise(pConnectionPoint,dwAdviseCookie);
			pConnectionPoint->lpVtbl->Release(pConnectionPoint);
		}

		pConnectionPointContainer->lpVtbl->Release(pConnectionPointContainer);

	}

	return (hret == S_OK);

}


/******************************** DllMain() ********************************
 * Automatically called by Win32 when the DLL is loaded or unloaded.
 */

#if defined(_MSC_VER)
#ifndef _DEBUG
BOOL WINAPI _DllMainCRTStartup(HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
#else
BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)  /* <--- Doesn't replace startup code */
#endif
#else
BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
#endif
{
    switch(fdwReason)
	{
		/* ============================================================== */
		case DLL_PROCESS_ATTACH:
		{
			/*
			 * Here you would do any initialization that you want to do when
			 * the DLL loads. The OS calls this every time another program
			 * runs which uses this DLL. You should put some complementary
			 * cleanup code in the DLL_PROCESS_DETACH case.
			 */

            /* Initialize the OLE interface */
			if (OleInitialize(NULL)) return(0);
			break;
		}

		/* ============================================================== */
		case DLL_THREAD_ATTACH:
		{
			/* We don't need to do any initialization for each thread of
			 * the program which uses this DLL, so disable thread messages.
			 */
			DisableThreadLibraryCalls(hinstDLL);
			break;
		}

/*
		case DLL_THREAD_DETACH:
		{
			break;
		}
*/
		/* ============================================================== */
		case DLL_PROCESS_DETACH:
		{
			OleUninitialize();
		}
	}

	/* Success */
	return(1);
}

