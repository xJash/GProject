#pragma once

#include "DLGDefine.h"
#include "diagrameditor\diagramentity.h"
#include "ListViewPropertyDlg.h"

class CDiagramListView :
	public CDiagramEntity
{
public:
	CDiagramListView(void);
	virtual ~CDiagramListView(void);

	static	CDiagramEntity* CreateFromString( const CString& str );

	// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 ) const;

	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.

private:
	CListViewPropertyDlg	m_dlg;

};
