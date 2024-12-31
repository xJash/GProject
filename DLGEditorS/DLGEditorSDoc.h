// DLGEditorSDoc.h : CDLGEditorSDoc Ŭ������ �������̽�
//


#pragma once

// --- DiagramEditor ---
#include "./DialogEditor/DiagramEditor/DiagramEntityContainer.h"

class CDLGEditorSDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CDLGEditorSDoc();
	DECLARE_DYNCREATE(CDLGEditorSDoc)

// Ư��
public:
	// --- DiagramEditor ---
	CDiagramEntityContainer*	GetData();

// �۾�
public:
	// --- DiagramEditor ---
	void	Export();

// ������
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CDLGEditorSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL SaveModified();

// --- DiagramEditor ---
private:
	// ��� ��Ʈ�� ������(All Entity)�� ���̾�α� ������ ��� �̹��� �����͸� �о��
	CDiagramEntityContainer	m_objs; // The object data

public:
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};


