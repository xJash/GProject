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

	void SetPropertyDefault();	// 속성을 기본값으로 셋팅한다.
	void IncreaseUniqueIDNum();	// 고유 id 번호를 하나 증가 시킨다.

private:
	CImageStaticPropertyDlg	m_dlg;

};
