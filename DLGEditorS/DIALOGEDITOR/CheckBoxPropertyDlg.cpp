#include "stdafx.h"
#include "./CheckBoxPropertyDlg.h"
#include ".\checkboxpropertydlg.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxPropertyDlg dialog


CCheckBoxPropertyDlg::CCheckBoxPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CCheckBoxPropertyDlg::IDD, pParent)
{
}


void CCheckBoxPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// leon add
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_KIND_NAME	, 	m_editCHKB_Property	[CHKB_KIND_NAME]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_ID	, 	m_editCHKB_Property	[CHKB_RESOURCE_ID]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_X_COORD	, 	m_editCHKB_Property	[CHKB_X_COORD]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_Y_COORD	, 	m_editCHKB_Property	[CHKB_Y_COORD]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_WIDTH	, 	m_editCHKB_Property	[CHKB_WIDTH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_HEIGHT	, 	m_editCHKB_Property	[CHKB_HEIGHT]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_IMAGE_FULLPATH	, 	m_editCHKB_Property	[CHKB_BG_IMAGE_FULLPATH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_BG_WIDTH	, 	m_editCHKB_Property	[CHKB_BG_WIDTH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_BG_HEIGHT	, 	m_editCHKB_Property	[CHKB_BG_HEIGHT]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_BG_TILE	, 	m_editCHKB_Property	[CHKB_BG_TILE]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_BG_TILE_IMAGE_NUM	, 	m_editCHKB_Property	[CHKB_BG_TILE_IMAGE_NUM])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_START_FONT	, 	m_editCHKB_Property	[CHKB_BG_START_FONT])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_TEXT_COLOR	, 	m_editCHKB_Property	[CHKB_TEXT_COLOR])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_R	, 	m_editCHKB_Property	[CHKB_TEXT_COLOR_R])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_G	, 	m_editCHKB_Property	[CHKB_TEXT_COLOR_G])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_B	, 	m_editCHKB_Property	[CHKB_TEXT_COLOR_B])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_WEIGHT, 	m_editCHKB_Property	[CHKB_WEIGHT])	;

	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_TEXT_STYLE	, 	m_editCHKB_Property	[CHKB_TEXT_STYLE])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_TEXT_SIZE	, 	m_editCHKB_Property	[CHKB_TEXT_SIZE])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_GROUP_NUM	, 	m_editCHKB_Property	[CHKB_GROUP_NUM]	)	;

	DDX_Control	(	pDX	, 	IDC_EDIT_CHKB_TEXT	, 	m_editCHKB_Property	[CHKB_TEXT_STR]	)	;
}


BEGIN_MESSAGE_MAP(CCheckBoxPropertyDlg, CDialog)

	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CHKB_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_CHKB_HIDE, OnBnClickedCHKBHide)
	ON_BN_CLICKED(IDC_BUTTON_CHKB_SEARCH, OnBnClickedButtonCHKBSearch)
	ON_BN_CLICKED(IDC_BUTTON_CHKB_PATH_EMPTY, OnBnClickedButtonCHKBPathEmpty)

	ON_BN_CLICKED(IDC_BUTTON_CHKB_TEXT_SEARCH, OnBnClickedButtonCHKBTextSearch)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxPropertyDlg virtuals

// Property Dialog ���ڸ� �� �� �ʱ�ȭ ��
// ��ü�� ũ�� ���� - SetRect(...)�Լ� ȣ��� ȣ�� ��
// ���� ������ �ʿ䰡 ���� �� ȣ���
// �۾� ���� : ��Ʈ���� ���� ������ ����� => ��Ʈ���� �Ӽ�â
void CCheckBoxPropertyDlg::SetValues()
{
	CString strTmp;

	int i =0;

	if( m_hWnd )
	{
		if( GetEntity() )
		{
			for(i=0; i<CHKB_PROPERTY_COUNT; i++)
			{
				// ���� ����� �����Ͱ� ����
				// ������ �� ����
				GetEntity()->GetPropertyWithIndex(strTmp, i);
			
				if(i == CHKB_BG_IMAGE_FULLPATH)
				{
					// ���� ����� ������ ���� Dialog �Ӽ� â�� �̴� �̹����� �ٸ��ٸ�
					// �̴� �̹��� ����!!
					if(strTmp != m_picFullPath || !GetBufferDC(REAL_BACKGROUND_NUM) ) // todo - �ٸ� �̹��� ���� �Ӽ� ó�� ��!!
					{
						DeleteAllBmp();
						
						ClearAllOldBmp();

						if(m_picFullPath != strTmp)
							m_picFullPath = strTmp;

						m_editCHKB_Property[i].SetWindowText(strTmp);

						if(strTmp.Trim(STR_TRIM_LETTER) != STR_EMPTY)
						{
							if(m_spr.LoadSpr( (char *)(LPCTSTR) strTmp.Trim(STR_TRIM_LETTER)))
							{
								CString strTile, strStartFont, strTileImageNum;

								GetEntity()->GetPropertyWithIndex(strTile, CHKB_BG_TILE);
								GetEntity()->GetPropertyWithIndex(strStartFont, CHKB_BG_START_FONT);
								GetEntity()->GetPropertyWithIndex(strTileImageNum, CHKB_BG_TILE_IMAGE_NUM);

								if(strTile != STR_ZERO)
									MakeMemDC( this->GetDC(), atoi(strStartFont), atoi(strTileImageNum));
								else
									MakeMemDC( this->GetDC(), atoi(strStartFont), WHOLE_IMAGE_STYLE_FONTNUM);
							}
						}

						if(m_oldPicFullPath != m_picFullPath)
							m_oldPicFullPath = m_picFullPath;
					}

					CRect rect(0, 0, m_spr.clHeader.siXsize+2*PIXEL_OFFSET_X, m_spr.clHeader.siYsize+2*PIXEL_OFFSET_Y);

					if(strTmp.Trim(STR_TRIM_LETTER) != STR_EMPTY)
					{
						CStdGrfx::drawframed3dBox( GetBufferDC(WORK_BACKGROUND_NUM), rect );
	
						BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(MASK_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);
						BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(REAL_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);
						BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
					}
					else
					{
						CStdGrfx::drawframed3dBox( GetBufferDC(WORK_BACKGROUND_NUM), rect );
						BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
						m_picFullPath.Empty();
						m_oldPicFullPath.Empty();
					}
				}
				else
					m_editCHKB_Property[i].SetWindowText(strTmp);

			}

		}
	}
}

// ��ǥ ��� : ���̾�α� �������� ��Ʈ��
// �۾� ���� : ��Ʈ���� �Ӽ�â�� => ��Ʈ���� ���� ������ �����
void CCheckBoxPropertyDlg::OnButtonApply() 
{
	int i=0;

	m_bError = false;

	if( m_hWnd )
	{
		if( GetEntity() )
		{
			CString	strTemp[CHKB_PROPERTY_COUNT];
			CString strTemp2;
			CString strTileImageNum;
			CString strTile;
			CString strTimeImageStartFont;
			CString tmpstr;

			int R = 0, G = 0, B = 0;
            m_editCHKB_Property[CHKB_TEXT_COLOR_R].GetWindowText(tmpstr);
			R = _ttoi(tmpstr);
			m_editCHKB_Property[CHKB_TEXT_COLOR_G].GetWindowText(tmpstr);
			G = _ttoi(tmpstr);
			m_editCHKB_Property[CHKB_TEXT_COLOR_B].GetWindowText(tmpstr);
			B = _ttoi(tmpstr);
			tmpstr.Format("%d", RGB(R,G,B) );
            m_editCHKB_Property[CHKB_TEXT_COLOR].SetWindowText(tmpstr);

			for(i=0; i<CHKB_PROPERTY_COUNT; i++)
			{
				// ��Ʈ�ѿ� �Է��� �� ����
                m_editCHKB_Property[i].GetWindowText(strTemp[i]);
				
				if(i == CHKB_RESOURCE_ID)
				{
                    if(GetEntity()->IsOverLapping(GetEntity(), strTemp[CHKB_RESOURCE_ID]))
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
						&& i == CHKB_BG_IMAGE_FULLPATH )/*|| i == CHKB_BG_TILE*/ || i == CHKB_BG_START_FONT
						|| i == CHKB_BG_WIDTH || i == CHKB_BG_HEIGHT || i == CHKB_BG_TILE_IMAGE_NUM )
					{
						if(GetEntity()->GetPicFullPath() != strTemp[CHKB_BG_IMAGE_FULLPATH])
							GetEntity()->SetPicFullPath(strTemp[CHKB_BG_IMAGE_FULLPATH]);

						GetEntity()->DeleteAllBmp();
						GetEntity()->DeleteAllBufferDC();
						GetEntity()->ClearAllOldBmp();

						GetEntity()->m_spr.ClearImageData();

						// Ÿ�� �̹��� ������ ���� ũ��� �޸� ���� ����!!
						if(GetEntity()->m_spr.LoadSpr( (char*)(LPCTSTR) strTemp[CHKB_BG_IMAGE_FULLPATH].Trim(STR_TRIM_LETTER)))
						{
							m_editCHKB_Property[CHKB_BG_TILE_IMAGE_NUM].GetWindowText(strTileImageNum);
							m_editCHKB_Property[CHKB_BG_TILE].GetWindowText(strTile);
							m_editCHKB_Property[CHKB_BG_START_FONT].GetWindowText(strTimeImageStartFont);

                            if(strTile != STR_ZERO) // Ÿ�� ����϶� ��Ʈ �̹��� ����
								GetEntity()->MakeMemDC(GetParent()->GetDC(), atoi(strTimeImageStartFont), atoi(strTileImageNum) );
							else	// �� �̹��� ��� �϶�
								GetEntity()->MakeMemDC(GetParent()->GetDC(), atoi(strTimeImageStartFont), WHOLE_IMAGE_STYLE_FONTNUM);
						}

						if(GetEntity()->GetOldPicFullPath() != strTemp[CHKB_BG_IMAGE_FULLPATH])
							GetEntity()->SetOldPicFullPath(strTemp[CHKB_BG_IMAGE_FULLPATH]);

					}
				}

			} // for(...)

			strTemp2.Empty();
			int sub_width = 0, sub_BG_width =0, sub_height = 0, sub_BG_height = 0;

			sub_width = _ttoi(strTemp[CHKB_WIDTH]);
			sub_height = _ttoi(strTemp[CHKB_HEIGHT]);
			sub_BG_width = _ttoi(strTemp[CHKB_BG_WIDTH]);
			sub_BG_height = _ttoi(strTemp[CHKB_BG_HEIGHT]);

			//strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_width, m_spr.clHeader.siXsize));
			strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_width, 1));
			m_editCHKB_Property[CHKB_WIDTH].SetWindowText(strTemp2);
			GetEntity()->SetPropertyWithIndex(strTemp2, CHKB_WIDTH);
	
			//if(sub_width > sub_BG_width)
			//{
	            m_editCHKB_Property[CHKB_BG_WIDTH].SetWindowText(strTemp2);
				GetEntity()->SetPropertyWithIndex(strTemp2, CHKB_BG_WIDTH);
			//}
			//else
			//{
			//	strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_BG_width, m_spr.clHeader.siXsize));
	  //          m_editCHKB_Property[CHKB_BG_WIDTH].SetWindowText(strTemp2);
			//	GetEntity()->SetPropertyWithIndex(strTemp2, CHKB_BG_WIDTH);
			//}

			//strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_height, m_spr.clHeader.siYsize));
			strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_height, 1));
			m_editCHKB_Property[CHKB_HEIGHT].SetWindowText(strTemp2);
			GetEntity()->SetPropertyWithIndex(strTemp2, CHKB_HEIGHT);
	
			//if(sub_height > sub_BG_height)
			//{
				m_editCHKB_Property[CHKB_BG_HEIGHT].SetWindowText(strTemp2);
				GetEntity()->SetPropertyWithIndex(strTemp2, CHKB_BG_HEIGHT);
			//}
			//else
			//{
			//	strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_BG_height, m_spr.clHeader.siYsize));
			//	m_editCHKB_Property[CHKB_BG_HEIGHT].SetWindowText(strTemp2);
			//	GetEntity()->SetPropertyWithIndex(strTemp2, CHKB_BG_HEIGHT);
			//}

			// id ���ڼ��� 30�ڸ� ���� ���ϰ� ��
			CString tmpStr;           
			m_editCHKB_Property[RESOURCE_ID].GetWindowText(tmpStr);
			if(tmpStr.GetLength() > ID_LENGTH)
			{
				AfxMessageBox(tmpStr + " ID ���� 30�ڸ� �ʰ��߽��ϴ�.\n �ٽ� �Է��ϼ���!");
				tmpStr = tmpStr.Left( 30 );
				m_editCHKB_Property[RESOURCE_ID].SetWindowText(tmpStr);
				m_bError = true;
			}
			GetParent()->RedrawWindow();
		}
	}	
}

// ��ư �Ӽ�â�� �̹��� �̸� ���� ó��
// ��ǥ ��� : ��Ʈ���� �Ӽ�â
void CCheckBoxPropertyDlg::OnBnClickedButtonCHKBSearch()
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

			m_editCHKB_Property[CHKB_BG_IMAGE_FULLPATH].SetWindowText( fileDlg.GetPathName() );

			if(m_spr.LoadSpr( (char *)(LPCTSTR)fileDlg.GetPathName().Trim(STR_TRIM_LETTER)))
				MakeMemDC(this->GetDC());

			if(m_oldPicFullPath != m_picFullPath)
				m_oldPicFullPath = m_picFullPath;

			CRect rect(0, 0, m_spr.clHeader.siXsize+2*PIXEL_OFFSET_X, m_spr.clHeader.siYsize+2*PIXEL_OFFSET_Y);

			CStdGrfx::drawframed3dBox( GetBufferDC(WORK_BACKGROUND_NUM), rect );

			BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(MASK_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);
			BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(REAL_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);
			BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);

			CString strTmp;

			// �Է��� �̹��� ���� fullpath �Ľ�
			ParsingFileFullPath(fileDlg.GetPathName());

			CString tileMode = GetTileMode();
			CString tileImageNum = GetTileImageNum();

			if(tileMode.Trim() != STR_EMPTY)
			{
				if(tileMode.Trim() == STR_ZERO && _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM0)	// ��� ���
					m_editCHKB_Property[CHKB_BG_TILE].SetWindowText(STR_ZERO);
				else // "1"�̸� ���� ���, "2"�̸� ���� ���
					m_editCHKB_Property[CHKB_BG_TILE].SetWindowText(STR_ONE);
			}
			else // ����Ʈ�� ��ʹ��
				m_editCHKB_Property[CHKB_BG_TILE].SetWindowText(STR_ZERO);

			if(tileImageNum.Trim() != STR_EMPTY)
			{
				if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM0 || _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM1
					|| _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM3 || _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM9)
				{
					strTmp.Format("%d", _ttoi(tileImageNum));
					m_editCHKB_Property[CHKB_BG_TILE_IMAGE_NUM].SetWindowText(strTmp);
				}
				else
				{
					strTmp = STR_ZERO;
					m_editCHKB_Property[CHKB_BG_TILE_IMAGE_NUM].SetWindowText(strTmp);
				}
			}

			//if(_ttoi(tileImageNum) < 2)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize);
			//	m_editCHKB_Property[CHKB_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize);
			//	m_editCHKB_Property[CHKB_HEIGHT].SetWindowText(strTmp);
			//}
			//else if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM3)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize * _ttoi(tileImageNum));
			//	m_editCHKB_Property[CHKB_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize);
			//	m_editCHKB_Property[CHKB_HEIGHT].SetWindowText(strTmp);
			//}
			//else if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM9)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize * 3);
			//	m_editCHKB_Property[CHKB_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize * 3 );
			//	m_editCHKB_Property[CHKB_HEIGHT].SetWindowText(strTmp);
			//}

			//// ũ�⿡ ����.. surface ����
			//m_editCHKB_Property[CHKB_WIDTH].GetWindowText(strTmp);
			//m_editCHKB_Property[CHKB_BG_WIDTH].SetWindowText(strTmp);
			//m_editCHKB_Property[CHKB_HEIGHT].GetWindowText(strTmp);
			//m_editCHKB_Property[CHKB_BG_HEIGHT].SetWindowText(strTmp);

			// ���̾�α� ũ�� ��ȭ ���� �̹��� ���� ��Ű��!!
			int sub_width = 0, sub_height = 0;
			m_editCHKB_Property[CHKB_WIDTH].GetWindowText(strTmp);
			sub_width = _ttoi(strTmp);
			m_editCHKB_Property[CHKB_HEIGHT].GetWindowText(strTmp);
			sub_height = _ttoi(strTmp);
            
			//strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_width, m_spr.clHeader.siXsize));
			strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_width, 1));
			// ũ�⿡ ����.. surface ����
			m_editCHKB_Property[CHKB_WIDTH].SetWindowText(strTmp);
			m_editCHKB_Property[CHKB_BG_WIDTH].SetWindowText(strTmp);

			//strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_height, m_spr.clHeader.siYsize));
			strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_height, 1));
			m_editCHKB_Property[CHKB_HEIGHT].SetWindowText(strTmp);
			m_editCHKB_Property[CHKB_BG_HEIGHT].SetWindowText(strTmp);

		}
	}
	
	this->SendMessage( WM_PAINT );
}

void CCheckBoxPropertyDlg::OnPaint()
{
	CDiagramPropertyDlg::OnPaint();
}

BOOL CCheckBoxPropertyDlg::OnInitDialog()
{
	CDiagramPropertyDlg::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCheckBoxPropertyDlg::OnBnClickedCHKBHide()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	this->ShowWindow(SW_HIDE);
}

void CCheckBoxPropertyDlg::OnBnClickedButtonCHKBPathEmpty()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_editCHKB_Property[CHKB_BG_IMAGE_FULLPATH].SetWindowText(STR_EMPTY);
	m_editCHKB_Property[CHKB_BG_TILE].SetWindowText(STR_ZERO);
	m_editCHKB_Property[CHKB_BG_TILE_IMAGE_NUM].SetWindowText(STR_ZERO);
	m_editCHKB_Property[CHKB_BG_START_FONT].SetWindowText(STR_ZERO);
	
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

// Font ��ȭ���ڿ��� => ��Ʈ�� �Ӽ� ���̾�α� ���ڷ� ����
void CCheckBoxPropertyDlg::OnBnClickedButtonCHKBTextSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShowFontDialog();
	CString tmpStr;

	m_editCHKB_Property[CHKB_TEXT_STYLE].SetWindowText(GetFontName());
	tmpStr.Format("%d", GetFontSize());
	m_editCHKB_Property[CHKB_TEXT_SIZE].SetWindowText(tmpStr);
	tmpStr.Format("%d", GetFontColor());
	m_editCHKB_Property[CHKB_TEXT_COLOR].SetWindowText(tmpStr);

}

void CCheckBoxPropertyDlg::OnOK()
{
	OnButtonApply();
	if(m_bError == false)
		CDialog::OnOK();
}
void CCheckBoxPropertyDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDiagramPropertyDlg::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}