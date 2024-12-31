// DiagramCheckbox.h : header file
//
#pragma once

#include "DiagramEditor/DiagramEntity.h"
#include "CheckBoxPropertyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagramCheckbox window

class CDiagramCheckbox : public CDiagramEntity
{
// Construction
public:
	CDiagramCheckbox();
	~CDiagramCheckbox();

	static	CDiagramEntity* CreateFromString( const CString& str );

// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 ) const;


	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.

private:
	CCheckBoxPropertyDlg	m_dlg;

};
