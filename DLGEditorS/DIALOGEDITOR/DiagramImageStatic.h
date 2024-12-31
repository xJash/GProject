#pragma once

#include "DLGDefine.h"
#include "diagrameditor\diagramentity.h"
#include "ImageStaticPropertyDlg.h"

class CDiagramImageStatic :
	public CDiagramEntity
{
public:
	CDiagramImageStatic(void);
	virtual ~CDiagramImageStatic(void);

	static CDiagramEntity* CreateFromString( const CString& str);

	// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 ) const;

	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.

private:
	CImageStaticPropertyDlg	m_dlg;

};
