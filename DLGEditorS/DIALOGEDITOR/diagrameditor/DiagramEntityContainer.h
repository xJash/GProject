#ifndef _DIAGRAMENTITYCONTAINER_H_
#define _DIAGRAMENTITYCONTAINER_H_

class CDiagramEntity;

#include "../DLGDefine.h"
#include "DiagramClipboardHandler.h"
#include "UndoItem.h"

class CDiagramEntityContainer {

public:

	// Construction/destruction/initialization
	CDiagramEntityContainer( CDiagramClipboardHandler* clip = NULL );
	virtual ~CDiagramEntityContainer();
	void Clear();
	virtual CString	GetString();// const;
	virtual BOOL FromString( const CString& str );
	virtual void Export( CStringArray& stra, UINT format = 0 ) const;
	virtual void SetClipboardHandler( CDiagramClipboardHandler* clip );
	virtual CDiagramClipboardHandler* GetClipboardHandler();

	// Data access
	virtual CDiagramEntity* GetAt( int index ) const;
	CObArray*		GetData();
	int				GetSize() const;

	// ����
	virtual void	Add( CDiagramEntity* obj, BOOL fromFile = false, int insertAt = -1 );

	virtual void	RemoveAt( int index );
	virtual void	RemoveAll();
	virtual void	RemoveAllSelected();
	virtual void	Remove( CDiagramEntity* obj );

	void			SetVirtualSize( CSize size, bool bIsLoading = false, int nModeDetail = -1 );
	CSize			GetVirtualSize();// const;

	void			SetModified( BOOL dirty );
	BOOL			IsModified() const;

	virtual void	SelectAll();
	virtual void	UnselectAll();
	int				GetSelectCount() const;

	// Undo handling
	virtual void	Undo();
	virtual void	Snapshot();
	BOOL			IsUndoPossible();
	virtual void	ClearUndo();
	void			SetUndoStackSize( int maxstacksize );
	int				GetUndoStackSize() const;

	// Group handling
	virtual void	Group();
	virtual void	Ungroup();

	// Single object handlers
	virtual void			Duplicate( CDiagramEntity* obj );
	virtual void			Cut( CDiagramEntity* obj );
	virtual void			Copy( CDiagramEntity* obj );
	virtual void			Up( CDiagramEntity* obj );
	virtual void			Down( CDiagramEntity* obj );
	virtual void			Front( CDiagramEntity* obj );
	virtual void			Bottom( CDiagramEntity* obj );
	virtual void			Paste();

	// Copy/paste
	virtual void			CopyAllSelected();
	virtual int				ObjectsInPaste();
	virtual void			ClearPaste();

	// Message handling
	virtual void			SendMessageToObjects( int command, BOOL selected = TRUE, CDiagramEntity* sender = NULL, CWnd* from = NULL );

	// Positional information
	CSize					GetTotalSize();
	CPoint					GetStartPoint();

	/**
	leon add
	* spr �̹��� �ε�
	*/
	BOOL ReadSprBG(CString picFullPath);
	// BackGround �̹��� ���
	CString GetBGPicFullPath();

	// ���̾�α� ������Ƽ ����Ʈ �� ����!!
	void SetDLGDefault(bool mustBe = false);

	void SetDefaultFilePath(CString defaultFilePath);	// ����Ʈ ��Ʈ ���� �н� ����
	void SetDefaultTxtFilePath(CString defaultTxtFilePath);	// ����Ʈ txt ���� ���
	CString GetDefaultFilePath();	// ����Ʈ ��Ʈ ���� ��� ����
	CString GetDefaultTxtFilePath(); // ����Ʈ txt ���� ���
	// �̹��� ��ü ���� ��� ����� ����Ʈ ��Ʈ ���� ��� ���� �Լ�
	CString DeleteDefaultFilePath(CString fullPath);

	int				SetToMultipleSize(double origin_val, double ref_multiple);

protected:
	CObArray*				GetPaste();
	CObArray*				GetUndo();
	int						Find( CDiagramEntity* obj );

public:
	// ##################Dialog Propery ���� - 21��#######################
	// ���� ������� �����ϹǷ�.. �� 30�� ������,, == DLG_FILE_PROPERTY_COUNT
	// �Ӽ� â������ �� 21���� ��������	== DLG_PROPERTY_COUNT

	CString m_DLG_Property[DLG_PROPERTY_COUNT];

	// ###################################################################
	/**
	leon add
	* spr �̹��� ������ : ���̾�α� ��� �̹����� ����
	*/
	cltTSpr m_spr;
	// ��� �̹��� ��ü ��� �� ���� �̸�
	CString m_BGFullPath;

	// ��� �̹����� �����ϴ� ����Ʈ ���
	CString m_defaultImagePath;

	// TxtMgr default path
	CString m_defaultTxtPath;

//private:
public:

	// Data
	CObArray		m_objs;
	CObArray		m_undo;
	int				m_maxstacksize;
	CSize			m_virtualSize;

	CDiagramClipboardHandler*	m_clip;
	CDiagramClipboardHandler	m_internalClip;

	// State
	BOOL			m_dirty;

	// Helpers
	void			Swap( int index1, int index2 );
	void			SetAt( int index, CDiagramEntity* obj );

};

#endif // _DIAGRAMENTITYCONTAINER_H_
