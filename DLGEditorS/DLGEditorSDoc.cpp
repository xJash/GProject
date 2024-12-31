// DLGEditorSDoc.cpp : CDLGEditorSDoc Ŭ������ ����
//

#include "stdafx.h"
#include "DLGEditorS.h"

#include "DLGEditorSDoc.h"
#include ".\dlgeditorsdoc.h"

// --- DiagramEditor ---
#include "./DialogEditor/DiagramControlFactory.h"
#include "./DialogEditor/TextFile.h"

#include "./DialogEditor/DLGDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDLGEditorSDoc

IMPLEMENT_DYNCREATE(CDLGEditorSDoc, CDocument)

BEGIN_MESSAGE_MAP(CDLGEditorSDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
END_MESSAGE_MAP()


// CDLGEditorSDoc ����/�Ҹ�

CDLGEditorSDoc::CDLGEditorSDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CDLGEditorSDoc::~CDLGEditorSDoc()
{
}

BOOL CDLGEditorSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ �ٽ� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	// --- DiagramEditor ---
	// Removing the current data
	m_objs.Clear();

	return true;
}




// CDLGEditorSDoc serialization

void CDLGEditorSDoc::Serialize(CArchive& ar)
{
	// --- DiagramEditor ---
	// Saving and loading to/from a text file
	// �� ��Ʈ�� ���� ���� ����!! => 2���� ���� ( DiagramEditor.cpp�� AddObject�� DLGEditorSDoc.cpp�� Serialize!!)
	//CTRL_SAVING_ORDER_INFO ctrl_saving_order[CTRL_COUNT] = 
	//{
	//	IMGSTT_STR, 0, 
	//	STATT_STR, 1,
	//	CHKB_STR, 2,
	//	RADB_STR, 3,
	//	BTN_STR, 4,
	//	ETB_STR, 5,
	//	CHTETB_STR, 6,
	//	LSTB_STR, 7, 
	//	LSTV_STR, 8,
	//	CBX_STR, 9,
	//	OUTLNE_STR, 10,
	//};

	if (ar.IsStoring())
	{
		ar.WriteString( m_objs.GetString() + _T( "\r\n" ) );	// ���̾�α� �Ӽ� ����!!
		
		int count = 0;
		CDiagramEntity* obj = NULL;

		for( int i = 0; i<CTRL_COUNT; i++)
		{
			count  = 0;
			obj = NULL;
			// OutLine Ÿ�Ը� �ɷ���
			while( ( obj = m_objs.GetAt( count++ ) ) )
			{
				if( obj != NULL)
				{
					// ���� i ��° ������ ��Ʈ���� �����ϱ� ���� ��Ʈ�� ������ �ɷ���
					if( strcmp( obj->m_pProperty[ KIND_NAME ], ctrl_saving_order[i].type) == 0 )
					{
						ar.WriteString( obj->GetString() + _T( "\r\n" ) );	// �� ��Ʈ�� �Ӽ� ����!!
					}
				}
			}
		}

		m_objs.SetModified( FALSE );
	}
	else
	{
		// �� ��Ʈ�� ���� ������ �ݴ�� �о� ���� ���� ����!!

		m_objs.Clear();
		CString str;
		CObArray tmp_ObjA;

		while(ar.ReadString( str ) )
		{
			str.TrimLeft("\t ");

			// file comment line ó��
			if(str.Find(DLG_FILE_COMMENT_SIGN) != 0)
			{
				// �о�� ���� paper ��("paper:x,y;") ���� �˻���
				if( !m_objs.FromString( str ) )
				{
					// paper ���� �ƴ϶� Entity ���̶�� ��ü ����
					CDiagramEntity* obj = CDiagramControlFactory::CreateFromString( str );
					if( obj )
					{
						// �ӽ� Array�� ��ü ����!!
						tmp_ObjA.Add( obj );
						//m_objs.Add( obj, true );
					}
				}
			}
		}

		for( int i = CTRL_COUNT-1; i>=0; i--)
		{
			for(int j= 0; j<tmp_ObjA.GetCount(); j++)
			{
				CString tmpStr;
				tmpStr = ((CDiagramEntity*)(tmp_ObjA.GetAt(j)))->m_pProperty[ RESOURCE_ID ];
				// ���� i ��° ������ ��Ʈ���� �����ϱ� ���� ��Ʈ�� ������ �ɷ���
				if( strcmp( ((CDiagramEntity*)(tmp_ObjA.GetAt(j)))->m_pProperty[ KIND_NAME ], ctrl_saving_order[i].type) == 0 )
				{
					tmpStr = ((CDiagramEntity*)(tmp_ObjA.GetAt(j)))->m_pProperty[ RESOURCE_ID ];					
                    m_objs.Add( ((CDiagramEntity*)(tmp_ObjA.GetAt(j))), true );                          
				}
			}
		}

		m_objs.SetModified( FALSE );
	}
}


// CDLGEditorSDoc ����

#ifdef _DEBUG
void CDLGEditorSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDLGEditorSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDialogEditorDemoDoc commands

// --- DiagramEditor ---
CDiagramEntityContainer* CDLGEditorSDoc::GetData()
{
    // Data accessor
	return &m_objs;
}

// CDLGEditorSDoc ���

BOOL CDLGEditorSDoc::SaveModified()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SetModifiedFlag( m_objs.IsModified() );
	return CDocument::SaveModified();
}

void CDLGEditorSDoc::Export()
{
	// An example of exporting

	CString filename;
	CStringArray stra;

	// Header. I don't want this in the CDiagramEntityContainer class
	// where it would normally belong, as it should not be necessary 
	// to derive a class from CDiagramEntityContainer.

	stra.Add( _T( "<html>" ) );
	stra.Add( _T( "<head>" ) );
	stra.Add( _T( "<style>" ) );
	stra.Add( _T( "\t.controls { font-family:MS Sans Serif;font-size:12; }" ) );
	stra.Add( _T( "\tbody { background-color:#c0c0c0; }" ) );
	stra.Add( _T( "</style>" ) );
	stra.Add( _T( "<script>" ) );
	stra.Add( _T( "function buttonHandler( obj )" ) );
	stra.Add( _T( "{" ) );
	stra.Add( _T( "\talert( obj.name )" ) );
	stra.Add( _T( "}" ) );
	stra.Add( _T( "function checkboxHandler( obj )" ) );
	stra.Add( _T( "{" ) );
	stra.Add( _T( "\talert( obj.name )" ) );
	stra.Add( _T( "}" ) );
	stra.Add( _T( "function radiobuttonHandler( obj )" ) );
	stra.Add( _T( "{" ) );
	stra.Add( _T( "\talert( obj.name )" ) );
	stra.Add( _T( "}" ) );
	stra.Add( _T( "function listboxHandler( obj )" ) );
	stra.Add( _T( "{" ) );
	stra.Add( _T( "\talert( obj.name )" ) );
	stra.Add( _T( "}" ) );
	stra.Add( _T( "function comboboxHandler( obj )" ) );
	stra.Add( _T( "{" ) );
	stra.Add( _T( "\talert( obj.name )" ) );
	stra.Add( _T( "}" ) );
	stra.Add( _T( "</script>" ) );
	stra.Add( _T( "</head>" ) );
	stra.Add( _T( "<body topmargin=0 leftmargin=0>" ) );

	CRect rect( 0, 0, m_objs.GetVirtualSize().cx + 1, m_objs.GetVirtualSize().cy + 1 );
	CString input1( _T( "<div style='position:absolute;left:%i;top:%i;width:%i;height:%i;border:1 solid black;'>" ) );
	CString input2( _T( "<div style='position:absolute;left:0;top:0;width:%i;height:%i;border-top:1 solid white;border-left:1 solid white;border-right:1 solid gray;border-bottom:1 solid gray;'>" ) );
	CString str;

	str.Format( input1, rect.left, rect.top, rect.Width(), rect.Height() );
	stra.Add( str );

	rect.InflateRect( -1, -1 );
	str.Format( input2, rect.Width(), rect.Height() );
	stra.Add( str );

	// The export itself
	m_objs.Export( stra );

	// The footer
	stra.Add( _T( "</div>" ) );
	stra.Add( _T( "</div>" ) );

	stra.Add( _T( "</body>" ) );
	stra.Add( _T( "</html>" ) );

	// Writing it to a file
	CTextFile tf( _T( "html" ), _T( "\n" ) );
	if( !tf.WriteTextFile( filename, stra ) )
		if( filename.GetLength() )
			AfxMessageBox( tf.GetErrorMessage() );

}
void CDLGEditorSDoc::OnFileSave()
{
	CString curPathName = CDocument::GetPathName();
	
	if(curPathName.IsEmpty())
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		char szFilter [] = "Dialog Design ( *.ddf ) |*.ddf;|All Files(*.*) | *.*||";

		CFileDialog dlg(FALSE, DIALOG_DESIGN_FORMAT_EXT, SAVE_FILE_PREFIX, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );

		if(dlg.DoModal() == IDOK)
		{
			SetPathName(dlg.GetFileName());
			DoSave(dlg.GetFileName());
		}
	}
	else
	{
		CDocument::OnFileSave();
	}
}


void CDLGEditorSDoc::OnFileSaveAs()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	char szFilter [] = "Dialog Design ( *.ddf ) |*.ddf;|All Files(*.*) | *.*||";

	CFileDialog dlg(FALSE, DIALOG_DESIGN_FORMAT_EXT, SAVE_FILE_PREFIX, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );

	if(dlg.DoModal() == IDOK)
	{
		SetPathName(dlg.GetFileName());
		DoSave(dlg.GetFileName());
	}
}
