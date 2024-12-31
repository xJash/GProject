#include "StdAfx.h"
#include ".\editboxpropertydlg.h"

CEditBoxPropertyDlg::CEditBoxPropertyDlg(CWnd* pParent)
: CDiagramPropertyDlg(CEditBoxPropertyDlg::IDD, pParent)
{
}

CEditBoxPropertyDlg::~CEditBoxPropertyDlg(void)
{
}

// Control�� ��� ������ ����
void CEditBoxPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_KIND_NAME	, 	m_editETB_Property	[ETB_KIND_NAME]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_ID	, 	m_editETB_Property	[ETB_RESOURCE_ID]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_X_COORD	, 	m_editETB_Property	[ETB_X_COORD]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_Y_COORD	, 	m_editETB_Property	[ETB_Y_COORD]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_WIDTH	, 	m_editETB_Property	[ETB_WIDTH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_HEIGHT	, 	m_editETB_Property	[ETB_HEIGHT]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_IMAGE_FULLPATH	, 	m_editETB_Property	[ETB_BG_IMAGE_FULLPATH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_BG_WIDTH	, 	m_editETB_Property	[ETB_BG_WIDTH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_BG_HEIGHT	, 	m_editETB_Property	[ETB_BG_HEIGHT]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_BG_TILE	, 	m_editETB_Property	[ETB_BG_TILE]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_BG_TILE_IMAGE_NUM	, 	m_editETB_Property	[ETB_BG_TILE_IMAGE_NUM])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_START_FONT	, 	m_editETB_Property	[ETB_BG_START_FONT])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_TEXT_COLOR	, 	m_editETB_Property	[ETB_TEXT_COLOR])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_R	, 	m_editETB_Property	[ETB_TEXT_COLOR_R])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_G	, 	m_editETB_Property	[ETB_TEXT_COLOR_G])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_B	, 	m_editETB_Property	[ETB_TEXT_COLOR_B])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_WEIGHT, 	m_editETB_Property	[ETB_WEIGHT])	;

	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_TEXT_STYLE	, 	m_editETB_Property	[ETB_TEXT_STYLE])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_TEXT_SIZE	, 	m_editETB_Property	[ETB_TEXT_SIZE])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_GROUP_NUM	, 	m_editETB_Property	[ETB_GROUP_NUM]	)	;

	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_TEXT	, 	m_editETB_Property	[ETB_TEXT_STR]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_MULTILINE	, 	m_editETB_Property	[ETB_MULTI_LINE]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_ETB_READONLY	, 	m_editETB_Property	[ETB_READONLY]	)	;
}

// Control�� �޼��� �Լ� ����
BEGIN_MESSAGE_MAP(CEditBoxPropertyDlg, CDialog)

	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ETB_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_ETB_HIDE, OnBnClickedHide)
	ON_BN_CLICKED(IDC_BUTTON_ETB_SEARCH, OnBnClickedButtonCbxSearch)

	ON_BN_CLICKED(IDC_BUTTON_ETB_PATH_EMPTY, OnBnClickedButtonEtbPathEmpty)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditBoxPropertyDlg virtuals

// Button Property Dialog ���ڸ� �� �� �ʱ�ȭ ��

void CEditBoxPropertyDlg::SetValues()
{
	//CString real_picFullPath;
	CString strTmp;

	int i =0;

	if( m_hWnd )
	{
		if( GetEntity() )
		{
			/**
			leon add
			* property �ϰ� ó���� ���� �迭 ���·� ������
			*/
			for(i=0; i<ETB_PROPERTY_COUNT; i++)
			{
				GetEntity()->GetPropertyWithIndex(strTmp, i);
			
				if(i == ETB_BG_IMAGE_FULLPATH)
				{
					if(strTmp != m_picFullPath || !GetBufferDC(REAL_BACKGROUND_NUM) ) // todo - �ٸ� �̹��� ���� �Ӽ� ó�� ��!!
					{
						DeleteAllBmp();
						
						ClearAllOldBmp();

						if(m_picFullPath != strTmp)
							m_picFullPath = strTmp;

						m_editETB_Property[i].SetWindowText(strTmp);

						if(strTmp.Trim(STR_TRIM_LETTER) != STR_EMPTY)
						{
							if(m_spr.LoadSpr( (char *)(LPCTSTR) strTmp.Trim(STR_TRIM_LETTER)))
                                MakeMemDC(this->GetDC());
						}
					}

					CRect rect(MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_LEFT + MINI_PICTURE_WIDTH, MINI_PICTURE_TOP + MINI_PICTURE_HEIGHT);
					//CStdGrfx::draw3dFrame(this->GetDC(), rect);
					CStdGrfx::drawframed3dBox( this->GetDC(), rect );

					if(strTmp.Trim(STR_TRIM_LETTER) != STR_EMPTY)
					{
						BitBltDS( this->GetDC(), GetBufferDC(MASK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
						BitBltDS( this->GetDC(), GetBufferDC(REAL_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
					}
				}
				else
					m_editETB_Property[i].SetWindowText(strTmp);

			}

		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEditBoxPropertyDlg message handlers

void CEditBoxPropertyDlg::OnButtonApply() 
{
	int i=0;
	m_bError = false;

	if( m_hWnd )
	{
		if( GetEntity() )
		{
			CString	strTemp[ETB_PROPERTY_COUNT];
			CString strTemp2;
			CString strTileImageNum;
			CString strTile;
			CString strTimeImageStartFont;
			CString tmpstr;

			int R = 0, G = 0, B = 0;
            m_editETB_Property[ETB_TEXT_COLOR_R].GetWindowText(tmpstr);
			R = _ttoi(tmpstr);
			m_editETB_Property[ETB_TEXT_COLOR_G].GetWindowText(tmpstr);
			G = _ttoi(tmpstr);
			m_editETB_Property[ETB_TEXT_COLOR_B].GetWindowText(tmpstr);
			B = _ttoi(tmpstr);
			tmpstr.Format("%d", RGB(R,G,B) );
            m_editETB_Property[ETB_TEXT_COLOR].SetWindowText(tmpstr);

			for(i=0; i<ETB_PROPERTY_COUNT; i++)
			{
				// ��Ʈ�ѿ� �Է��� �� ����
                m_editETB_Property[i].GetWindowText(strTemp[i]);

				if(i == ETB_RESOURCE_ID)
				{
                    if(GetEntity()->IsOverLapping(GetEntity(), strTemp[ETB_RESOURCE_ID]))
					{
						AfxMessageBox("�ߺ��� ID�� �̹� �����մϴ�.\n �ٽ� �Է��ϼ���!!");
						m_bError = true;
						return;
					}
				}

				
				// ���� �����ͷ� �����ϰ� �ִ� ��
				GetEntity()->GetPropertyWithIndex(strTemp2, i);

				if(strTemp2 != strTemp[i])
				{
					// ���� ������ ����ҿ� ��Ʈ�� �Ӽ� �� ����
					GetEntity()->SetPropertyWithIndex(strTemp[i], i);
					
					if( (GetEntity()->GetPicFullPath().Trim(STR_TRIM_LETTER) != STR_EMPTY && GetEntity()->GetPicFullPath() != GetEntity()->GetOldPicFullPath()
						&& i == ETB_BG_IMAGE_FULLPATH )/*|| i == ETB_BG_TILE*/ || i == ETB_BG_START_FONT
						|| i == ETB_BG_WIDTH || i == ETB_BG_HEIGHT || i == ETB_BG_TILE_IMAGE_NUM )
					{
						if(GetEntity()->GetPicFullPath() != strTemp[ETB_BG_IMAGE_FULLPATH])
							GetEntity()->SetPicFullPath(strTemp[ETB_BG_IMAGE_FULLPATH]);

						//if(GetEntity()->GetPicFullPath().Trim(STR_TRIM_LETTER) != STR_EMPTY && GetEntity()->GetPicFullPath() != GetEntity()->GetOldPicFullPath())
						{
							GetEntity()->DeleteAllBmp();
							GetEntity()->DeleteAllBufferDC();
							GetEntity()->ClearAllOldBmp();

							GetEntity()->m_spr.ClearImageData();

							// Ÿ�� �̹��� ������ ���� ũ��� �޸� ���� ����!!
							if(GetEntity()->m_spr.LoadSpr( (char*)(LPCTSTR) strTemp[ETB_BG_IMAGE_FULLPATH].Trim(STR_TRIM_LETTER)))
							{
								m_editETB_Property[ETB_BG_TILE_IMAGE_NUM].GetWindowText(strTileImageNum);
								m_editETB_Property[ETB_BG_TILE].GetWindowText(strTile);
								m_editETB_Property[ETB_BG_START_FONT].GetWindowText(strTimeImageStartFont);

                                if(strTile != STR_ZERO) // Ÿ�� ����϶� ��Ʈ �̹��� ����
									GetEntity()->MakeMemDC(GetParent()->GetDC(), atoi(strTimeImageStartFont), atoi(strTileImageNum) );
								else	// �� �̹��� ��� �϶�
									GetEntity()->MakeMemDC(GetParent()->GetDC(), atoi(strTimeImageStartFont), WHOLE_IMAGE_STYLE_FONTNUM);
							}

							if(GetEntity()->GetOldPicFullPath() != strTemp[ETB_BG_IMAGE_FULLPATH])
								GetEntity()->SetOldPicFullPath(strTemp[ETB_BG_IMAGE_FULLPATH]);

							//if(m_picFullPath != strTemp[ETB_BG_IMAGE_FULLPATH])
							//	m_picFullPath = strTemp[ETB_BG_IMAGE_FULLPATH];

							//if(m_oldPicFullPath != m_picFullPath)
							//	m_oldPicFullPath = m_picFullPath;
						}
					}
				}
			} // for(...)

			strTemp2.Empty();
			int sub_width = 0, sub_BG_width =0, sub_height = 0, sub_BG_height = 0;

			sub_width = _ttoi(strTemp[ETB_WIDTH]);
			sub_height = _ttoi(strTemp[ETB_HEIGHT]);
			sub_BG_width = _ttoi(strTemp[ETB_BG_WIDTH]);
			sub_BG_height = _ttoi(strTemp[ETB_BG_HEIGHT]);

			//strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_width, m_spr.clHeader.siXsize));
			strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_width, 1));
			m_editETB_Property[ETB_WIDTH].SetWindowText(strTemp2);
			GetEntity()->SetPropertyWithIndex(strTemp2, ETB_WIDTH);
	
			//if(sub_width > sub_BG_width)
			//{
	            m_editETB_Property[ETB_BG_WIDTH].SetWindowText(strTemp2);
				GetEntity()->SetPropertyWithIndex(strTemp2, ETB_BG_WIDTH);
			//}
			//else
			//{
			//	strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_BG_width, m_spr.clHeader.siXsize));
	  //          m_editETB_Property[ETB_BG_WIDTH].SetWindowText(strTemp2);
			//	GetEntity()->SetPropertyWithIndex(strTemp2, ETB_BG_WIDTH);
			//}

			//strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_height, m_spr.clHeader.siYsize));
			strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_height, 1));
			m_editETB_Property[ETB_HEIGHT].SetWindowText(strTemp2);
			GetEntity()->SetPropertyWithIndex(strTemp2, ETB_HEIGHT);
	
			//if(sub_height > sub_BG_height)
			//{
				m_editETB_Property[ETB_BG_HEIGHT].SetWindowText(strTemp2);
				GetEntity()->SetPropertyWithIndex(strTemp2, ETB_BG_HEIGHT);
			//}
			//else
			//{
			//	strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_BG_height, m_spr.clHeader.siYsize));
			//	m_editETB_Property[ETB_BG_HEIGHT].SetWindowText(strTemp2);
			//	GetEntity()->SetPropertyWithIndex(strTemp2, ETB_BG_HEIGHT);
			//}

			// id ���ڼ��� 30�ڸ� ���� ���ϰ� ��
			CString tmpStr;           
			m_editETB_Property[RESOURCE_ID].GetWindowText(tmpStr);
			if(tmpStr.GetLength() > ID_LENGTH)
			{
				AfxMessageBox(tmpStr + " ID ���� 30�ڸ� �ʰ��߽��ϴ�.\n �ٽ� �Է��ϼ���!");
				tmpStr = tmpStr.Left( 30 );
				m_editETB_Property[RESOURCE_ID].SetWindowText(tmpStr);
				m_bError = true;
			}

			GetParent()->RedrawWindow();
		}
	}	
}

void CEditBoxPropertyDlg::OnBnClickedButtonCbxSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilters[] = "Spr Files(*.spr)|*.spr|Mpr Files(*.mpr)|*.mpr|All Files(*.*)|*.*||";

	CFileDialog fileDlg( TRUE, NULL, "*.spr", OFN_FILEMUSTEXIST, szFilters, this);

	if( IDOK == fileDlg.DoModal() )
	{
		m_picFullPath = fileDlg.GetPathName();

		if(m_picFullPath.Trim(STR_TRIM_LETTER) != STR_EMPTY && m_picFullPath != m_oldPicFullPath)
		{
			DeleteAllBmp();
			DeleteAllBufferDC();
			ClearAllOldBmp();
			m_spr.ClearImageData();

			m_editETB_Property[ETB_BG_IMAGE_FULLPATH].SetWindowText( fileDlg.GetPathName() );

			if(m_spr.LoadSpr( (char *)(LPCTSTR)fileDlg.GetPathName().Trim(STR_TRIM_LETTER)))
                MakeMemDC(this->GetDC());

			if(m_oldPicFullPath != m_picFullPath)
				m_oldPicFullPath = m_picFullPath;

			CRect rect(MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_LEFT + MINI_PICTURE_WIDTH, MINI_PICTURE_TOP + MINI_PICTURE_HEIGHT);
			//CStdGrfx::draw3dFrame(this->GetDC(), rect);
			CStdGrfx::drawframed3dBox( this->GetDC(), rect );

			BitBltDS( this->GetDC(), GetBufferDC(MASK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
			BitBltDS( this->GetDC(), GetBufferDC(REAL_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);

			CString strTmp;
			
			//strTmp.Format("%d", m_spr.clHeader.siXsize);
			//m_editETB_Property[ETB_BG_WIDTH].SetWindowText(strTmp);
			//strTmp.Format("%d", m_spr.clHeader.siYsize);
			//m_editETB_Property[ETB_BG_HEIGHT].SetWindowText(strTmp);

			// �Է��� �̹��� ���� fullpath �Ľ�
			ParsingFileFullPath(fileDlg.GetPathName());

			CString tileMode = GetTileMode();
			CString tileImageNum = GetTileImageNum();

			if(tileMode.Trim() != STR_EMPTY)
			{
				if(tileMode.Trim() == STR_ZERO && _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM0)	// ��� ���
					m_editETB_Property[ETB_BG_TILE].SetWindowText(STR_ZERO);
				else // "1"�̸� ���� ���, "2"�̸� ���� ���
					m_editETB_Property[ETB_BG_TILE].SetWindowText(STR_ONE);
			}
			else // ����Ʈ�� ��ʹ��
				m_editETB_Property[ETB_BG_TILE].SetWindowText(STR_ZERO);

			if(tileImageNum.Trim() != STR_EMPTY)
			{
				if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM0 || _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM1
					|| _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM3 || _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM9)
				{
					strTmp.Format("%d", _ttoi(tileImageNum));
					m_editETB_Property[ETB_BG_TILE_IMAGE_NUM].SetWindowText(strTmp);
				}
				else
				{
					strTmp = STR_ZERO;
					m_editETB_Property[ETB_BG_TILE_IMAGE_NUM].SetWindowText(strTmp);
				}
			}

			//if(_ttoi(tileImageNum) < 2)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize);
			//	m_editETB_Property[ETB_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize);
			//	m_editETB_Property[ETB_HEIGHT].SetWindowText(strTmp);
			//}
			//else if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM3)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize * _ttoi(tileImageNum));
			//	m_editETB_Property[ETB_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize);
			//	m_editETB_Property[ETB_HEIGHT].SetWindowText(strTmp);
			//}
			//else if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM9)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize * 3);
			//	m_editETB_Property[ETB_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize * 3 );
			//	m_editETB_Property[ETB_HEIGHT].SetWindowText(strTmp);
			//}

			//// ũ�⿡ ����.. surface ����
			//m_editETB_Property[ETB_WIDTH].GetWindowText(strTmp);
			//m_editETB_Property[ETB_BG_WIDTH].SetWindowText(strTmp);
			//m_editETB_Property[ETB_HEIGHT].GetWindowText(strTmp);
			//m_editETB_Property[ETB_BG_HEIGHT].SetWindowText(strTmp);

			// ���̾�α� ũ�� ��ȭ ���� �̹��� ���� ��Ű��!!
			int sub_width = 0, sub_height = 0;
			m_editETB_Property[ETB_WIDTH].GetWindowText(strTmp);
			sub_width = _ttoi(strTmp);
			m_editETB_Property[ETB_HEIGHT].GetWindowText(strTmp);
			sub_height = _ttoi(strTmp);
            
			//strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_width, m_spr.clHeader.siXsize));
			strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_width, 1));
			// ũ�⿡ ����.. surface ����
			m_editETB_Property[ETB_WIDTH].SetWindowText(strTmp);
			m_editETB_Property[ETB_BG_WIDTH].SetWindowText(strTmp);

			//strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_height, m_spr.clHeader.siYsize));
			strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_height, 1));
			m_editETB_Property[ETB_HEIGHT].SetWindowText(strTmp);
			m_editETB_Property[ETB_BG_HEIGHT].SetWindowText(strTmp);

		}
	}
	
	//this->RedrawWindow();
	this->SendMessage( WM_PAINT );
}

void CEditBoxPropertyDlg::OnPaint()
{
	CDiagramPropertyDlg::OnPaint();
}

BOOL CEditBoxPropertyDlg::OnInitDialog()
{
	CDiagramPropertyDlg::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CEditBoxPropertyDlg::OnBnClickedHide()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	this->ShowWindow(SW_HIDE);
}



void CEditBoxPropertyDlg::OnBnClickedButtonEtbPathEmpty()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_editETB_Property[ETB_BG_IMAGE_FULLPATH].SetWindowText(STR_EMPTY);
	m_editETB_Property[ETB_BG_TILE].SetWindowText(STR_ZERO);
	m_editETB_Property[ETB_BG_TILE_IMAGE_NUM].SetWindowText(STR_ZERO);
	m_editETB_Property[ETB_BG_START_FONT].SetWindowText(STR_ZERO);

	if(m_spr.Image != NULL)
	{
		CRect rect(0, 0, m_spr.clHeader.siXsize+2*PIXEL_OFFSET_X, m_spr.clHeader.siYsize+2*PIXEL_OFFSET_Y);

		CStdGrfx::drawframed3dBox( GetBufferDC(WORK_BACKGROUND_NUM), rect );
		BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
		m_picFullPath.Empty();
		m_oldPicFullPath.Empty();
	}

	m_spr.ClearImageData();

}

void CEditBoxPropertyDlg::OnOK()
{
	OnButtonApply();
	if(m_bError == false)
		CDialog::OnOK();
}
void CEditBoxPropertyDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDiagramPropertyDlg::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
