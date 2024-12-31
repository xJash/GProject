#pragma once
// DiagramEdit.h : header file
//

#include "DiagramEditor/DiagramEntity.h"
//#include "EditPropertyDlg.h"
#include "ChatEditPropertyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagramChatEdit window

class CDiagramChatEdit : public CDiagramEntity
{
// Construction
public:
	CDiagramChatEdit();
	~CDiagramChatEdit();

	static	CDiagramEntity* CreateFromString( const CString& str );

// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );
	virtual CString	Export( UINT format = 0 ) const;

	void SetPropertyDefault();	// �Ӽ��� �⺻������ �����Ѵ�.
	void IncreaseUniqueIDNum();	// ���� id ��ȣ�� �ϳ� ���� ��Ų��.

private:
	CChatEditPropertyDlg	m_dlg;

};

