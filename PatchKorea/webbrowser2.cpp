
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-2000 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "webbrowser2.h"

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2

IMPLEMENT_DYNCREATE(CWebBrowser2, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2 properties

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2 operations

unsigned long CWebBrowser2::AddRef()
{
	unsigned long result;
	InvokeHelper(0x60000001, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CWebBrowser2::Release()
{
	unsigned long result;
	InvokeHelper(0x60000002, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::GoBack()
{
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWebBrowser2::GoForward()
{
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWebBrowser2::GoHome()
{
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWebBrowser2::GoSearch()
{
	InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWebBrowser2::Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		URL, Flags, TargetFrameName, PostData, Headers);
}

void CWebBrowser2::Refresh()
{
	InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWebBrowser2::Refresh2(VARIANT* Level)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		Level);
}

void CWebBrowser2::Stop()
{
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH CWebBrowser2::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CWebBrowser2::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CWebBrowser2::GetContainer()
{
	LPDISPATCH result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CWebBrowser2::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL CWebBrowser2::GetTopLevelContainer()
{
	BOOL result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CWebBrowser2::GetType()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CWebBrowser2::GetLeft()
{
	long result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		nNewValue);
}

long CWebBrowser2::GetTop()
{
	long result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		nNewValue);
}

long CWebBrowser2::GetWidth()
{
	long result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		nNewValue);
}

long CWebBrowser2::GetHeight()
{
	long result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		nNewValue);
}

CString CWebBrowser2::GetLocationName()
{
	CString result;
	InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CWebBrowser2::GetLocationURL()
{
	CString result;
	InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL CWebBrowser2::GetBusy()
{
	BOOL result;
	InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::Quit()
{
	InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWebBrowser2::ClientToWindow(long* pcx, long* pcy)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		pcx, pcy);
}

void CWebBrowser2::PutProperty(LPCTSTR szProperty, const VARIANT& vtValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		szProperty, &vtValue);
}

VARIANT CWebBrowser2::GetProperty(LPCTSTR szProperty)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		szProperty);
	return result;
}

CString CWebBrowser2::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CWebBrowser2::GetHwnd()
{
	long result;
	InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CWebBrowser2::GetFullName()
{
	CString result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CWebBrowser2::GetPath()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL CWebBrowser2::GetVisible()
{
	BOOL result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}

BOOL CWebBrowser2::GetStatusBar()
{
	BOOL result;
	InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetStatusBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}

CString CWebBrowser2::GetStatusText()
{
	CString result;
	InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetStatusText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		lpszNewValue);
}

long CWebBrowser2::GetToolBar()
{
	long result;
	InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetToolBar(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		nNewValue);
}

BOOL CWebBrowser2::GetMenuBar()
{
	BOOL result;
	InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetMenuBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}

BOOL CWebBrowser2::GetFullScreen()
{
	BOOL result;
	InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetFullScreen(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}

void CWebBrowser2::Navigate2(VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		URL, Flags, TargetFrameName, PostData, Headers);
}

long CWebBrowser2::QueryStatusWB(long cmdID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		cmdID);
	return result;
}

void CWebBrowser2::ExecWB(long cmdID, long cmdexecopt, VARIANT* pvaIn, VARIANT* pvaOut)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		cmdID, cmdexecopt, pvaIn, pvaOut);
}

long CWebBrowser2::GetReadyState()
{
	long result;
	InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CWebBrowser2::GetOffline()
{
	BOOL result;
	InvokeHelper(0x226, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetOffline(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x226, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}

BOOL CWebBrowser2::GetSilent()
{
	BOOL result;
	InvokeHelper(0x227, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetSilent(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x227, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}

BOOL CWebBrowser2::GetRegisterAsBrowser()
{
	BOOL result;
	InvokeHelper(0x228, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetRegisterAsBrowser(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x228, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}

BOOL CWebBrowser2::GetRegisterAsDropTarget()
{
	BOOL result;
	InvokeHelper(0x229, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CWebBrowser2::SetRegisterAsDropTarget(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x229, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		bNewValue);
}
