#if !defined(AFX_DIAGRAMLISTBOX_H__A34BFDFD_1CBE_463B_94EF_907D9123D614__INCLUDED_)
#define AFX_DIAGRAMLISTBOX_H__A34BFDFD_1CBE_463B_94EF_907D9123D614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiagramListbox.h : header file
//

#include "DiagramEditor/DiagramEntity.h"
//#include "EditPropertyDlg.h"
#include "ListBoxPropertyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagramListbox window

class CDiagramListbox : public CDiagramEntity
{
// Construction
public:
	CDiagramListbox();
	~CDiagramListbox();

	static	CDiagramEntity* CreateFromString( const CString& str );

// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 ) const;

	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.

private:
//	CEditPropertyDlg	m_dlg;
	CListBoxPropertyDlg m_dlg;

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_DIAGRAMLISTBOX_H__A34BFDFD_1CBE_463B_94EF_907D9123D614__INCLUDED_)
