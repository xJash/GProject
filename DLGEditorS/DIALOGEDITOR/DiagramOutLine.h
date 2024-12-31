
#pragma once
// DiagramStatic.h : header file
//

#include "DiagramEditor/DiagramEntity.h"
#include "OutLinePropertyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagramOutLine window

class CDiagramOutLine : public CDiagramEntity
{
// Construction
public:
	CDiagramOutLine();
	~CDiagramOutLine();

	static	CDiagramEntity* CreateFromString( const CString& str );

// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 );

	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.

private:
	COutLinePropertyDlg m_dlg;

};

/////////////////////////////////////////////////////////////////////////////

