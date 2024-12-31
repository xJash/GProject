#if !defined(AFX_DIAGRAMSTATIC_H__F29766BB_546B_4DB9_8228_17DDC74885BF__INCLUDED_)
#define AFX_DIAGRAMSTATIC_H__F29766BB_546B_4DB9_8228_17DDC74885BF__INCLUDED_

// DiagramStatic.h : header file
//

#include "DiagramEditor/DiagramEntity.h"
//#include "ButtonPropertyDlg.h"
#include "StaticTextPropertyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagramStatic window

class CDiagramStatic : public CDiagramEntity
{
// Construction
public:
	CDiagramStatic();
	~CDiagramStatic();

	static	CDiagramEntity* CreateFromString( const CString& str );

// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 );

	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.

private:
//	CButtonPropertyDlg	m_dlg;
	CStaticTextPropertyDlg m_dlg;

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_DIAGRAMSTATIC_H__F29766BB_546B_4DB9_8228_17DDC74885BF__INCLUDED_)
