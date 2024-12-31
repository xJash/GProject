// DiagramRadiobutton.h : header file
//

#pragma once

#include "DiagramEditor/DiagramEntity.h"
#include "RadioButtonPropertyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagramRadiobutton window

class CDiagramRadiobutton : public CDiagramEntity
{
// Construction
public:
	CDiagramRadiobutton();
	~CDiagramRadiobutton();

	static	CDiagramEntity* CreateFromString( const CString& str );

// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 ) const;

	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.


private:
	CRadioButtonPropertyDlg	m_dlg;

};
