#include "stdafx.h"
#include "DLGDefine.h"
#include "ButtonPropertyDlg.h"
#include ".\buttonpropertydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonPropertyDlg dialog


CButtonPropertyDlg::CButtonPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CButtonPropertyDlg::IDD, pParent)
{
}


void CButtonPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// leon add
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_KIND_NAME	, 	m_editBTN_Property	[BTN_KIND_NAME]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_ID	, 	m_editBTN_Property	[BTN_RESOURCE_ID]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_X_COORD	, 	m_editBTN_Property	[BTN_X_COORD]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_Y_COORD	, 	m_editBTN_Property	[BTN_Y_COORD]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_WIDTH	, 	m_editBTN_Property	[BTN_WIDTH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_HEIGHT	, 	m_editBTN_Property	[BTN_HEIGHT]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_IMAGE_FULLPATH	, 	m_editBTN_Property	[BTN_BG_IMAGE_FULLPATH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_BG_WIDTH	, 	m_editBTN_Property	[BTN_BG_WIDTH]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_BG_HEIGHT	, 	m_editBTN_Property	[BTN_BG_HEIGHT]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_BG_TILE	, 	m_editBTN_Property	[BTN_BG_TILE]	)	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_BG_TILE_IMAGE_NUM	, 	m_editBTN_Property	[BTN_BG_TILE_IMAGE_NUM])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_START_FONT	, 	m_editBTN_Property	[BTN_BG_START_FONT])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_TEXT_COLOR	, 	m_editBTN_Property	[BTN_TEXT_COLOR])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_R	, 	m_editBTN_Property	[BTN_TEXT_COLOR_R])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_G	, 	m_editBTN_Property	[BTN_TEXT_COLOR_G])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_B	, 	m_editBTN_Property	[BTN_TEXT_COLOR_B])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_WEIGHT, 	m_editBTN_Property	[BTN_WEIGHT])	;

	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_TEXT_STYLE	, 	m_editBTN_Property	[BTN_TEXT_STYLE])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_TEXT_SIZE	, 	m_editBTN_Property	[BTN_TEXT_SIZE])	;
	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_GROUP_NUM	, 	m_editBTN_Property	[BTN_GROUP_NUM]	)	;

	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_TEXT	, 	m_editBTN_Property	[BTN_TEXT_STR]	)	;

	DDX_Control	(	pDX	, 	IDC_EDIT_BTN_ANIMATION	, 	m_editBTN_Property	[BTN_ANIMATION]	)	;
}


BEGIN_MESSAGE_MAP(CButtonPropertyDlg, CDialog)

	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BTN_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_BTN_HIDE, OnBnClickedHide)
	ON_BN_CLICKED(IDC_BUTTON_BTN_SEARCH, OnBnClickedButtonBtnSearch)
	ON_BN_CLICKED(IDC_BUTTON_BTN_PATH_EMPTY, OnBnClickedButtonBtnPathEmpty)

	ON_BN_CLICKED(IDC_BUTTON_BTN_TEXT_SEARCH, OnBnClickedButtonBtnTextSearch)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonPropertyDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CButtonPropertyDlg virtuals

// Button Property Dialog ���ڸ� �� �� �ʱ�ȭ ��
// Button ��ü�� ũ�� ���� - SetRect(...)�Լ� ȣ��� ȣ�� ��

// ���� ������ �ʿ䰡 ���� �� ȣ���
// �۾� ���� : ��Ʈ���� ���� ������ ����� => ��Ʈ���� �Ӽ�â
void CButtonPropertyDlg::SetValues()
{
	CString strTmp;

	int i =0;

	if( m_hWnd )
	{
		if( GetEntity() )
		{
			/**
			leon add
			* button property �ϰ� ó���� ���� �迭 ���·� ������
			*/
			for(i=0; i<BTN_PROPERTY_COUNT; i++)
			{
				// ���� ����� �����Ͱ� ����
				// ������ �� ����
				GetEntity()->GetPropertyWithIndex(strTmp, i);
			
				if(i == BTN_BG_IMAGE_FULLPATH)
				{
					// ���� ����� ������ ���� Dialog �Ӽ� â�� �̴� �̹����� �ٸ��ٸ�
					// �̴� �̹��� ����!!
					if(strTmp != m_picFullPath || !GetBufferDC(REAL_BACKGROUND_NUM) ) // todo - �ٸ� �̹��� ���� �Ӽ� ó�� ��!!
					{
						DeleteAllBmp();
						
						ClearAllOldBmp();

						if(m_picFullPath != strTmp)
							m_picFullPath = strTmp;

						m_editBTN_Property[i].SetWindowText(strTmp);

						if(strTmp.Trim(STR_TRIM_LETTER) != STR_EMPTY)
						{
							if(m_spr.LoadSpr( (char *)(LPCTSTR) strTmp.Trim(STR_TRIM_LETTER)))
							{
                                //MakeMemDC(this->GetDC());

								CString strTile, strStartFont, strTileImageNum;

								GetEntity()->GetPropertyWithIndex(strTile, BTN_BG_TILE);
								GetEntity()->GetPropertyWithIndex(strStartFont, BTN_BG_START_FONT);
								GetEntity()->GetPropertyWithIndex(strTileImageNum, BTN_BG_TILE_IMAGE_NUM);

								if(strTile != STR_ZERO)
									MakeMemDC( this->GetDC(), atoi(strStartFont), atoi(strTileImageNum));
								else
									MakeMemDC( this->GetDC(), atoi(strStartFont), WHOLE_IMAGE_STYLE_FONTNUM);
							}
						}

						if(m_oldPicFullPath != m_picFullPath)
							m_oldPicFullPath = m_picFullPath;
					}

					//CRect rect(MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_LEFT + MINI_PICTURE_WIDTH, MINI_PICTURE_TOP + MINI_PICTURE_HEIGHT);
					//CStdGrfx::draw3dFrame(this->GetDC(), rect);
					//CStdGrfx::drawframed3dBox( this->GetDC(), rect );

					//if(strTmp.Trim(STR_TRIM_LETTER) != STR_EMPTY)
					//{
					//	BitBltDS( this->GetDC(), GetBufferDC(MASK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
					//	BitBltDS( this->GetDC(), GetBufferDC(REAL_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
					//}

					CRect rect(0, 0, m_spr.clHeader.siXsize+2*PIXEL_OFFSET_X, m_spr.clHeader.siYsize+2*PIXEL_OFFSET_Y);

					if(strTmp.Trim(STR_TRIM_LETTER) != STR_EMPTY)
					{
						CStdGrfx::drawframed3dBox( GetBufferDC(WORK_BACKGROUND_NUM), rect );

						BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(MASK_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);
						BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(REAL_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);

						CString tmpCStr;
						int iTmp = -1;
						int iTileNum = -1;
						m_editBTN_Property[BTN_BG_TILE_IMAGE_NUM].GetWindowText( tmpCStr );
						iTmp = _tstoi( tmpCStr );

						DrawMiniPicture( this->GetDC(), iTmp );

						//CString tmpCStr;
						//int iTmp = -1;
						//int iTileNum = -1;
						//m_editBTN_Property[BTN_BG_TILE_IMAGE_NUM].GetWindowText( tmpCStr );
						//iTmp = _tstoi( tmpCStr );

						//switch( iTmp )
						//{
						//case VALID_TILEIMAGE_NUM0:
						//	{
						//		//iTileNum = VALID_TILEIMAGE_NUM0;
						//		iTileNum = 1;

						//		//if( GetEntity() != NULL && iTileNum != -1 && m_spr.clHeader.siXsize < MINI_PICTURE_WIDTH && m_spr.clHeader.siYsize < MINI_PICTURE_HEIGHT )
						//		//	GetEntity()->DrawTileImg( this->GetDC(), SPR_PUTSPRT, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, iTileNum, true);
						//		//else
						//		//	BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
						//	}
						//	break;
						//case VALID_TILEIMAGE_NUM1:
						//	{
						//		iTileNum = VALID_TILEIMAGE_NUM1;
						//	}
						//	break;
						//case VALID_TILEIMAGE_NUM3:
						//	{
						//		iTileNum = VALID_TILEIMAGE_NUM3;
						//	}
						//	break;
						//case VALID_TILEIMAGE_NUM9:
						//	{
						//		iTileNum = VALID_TILEIMAGE_NUM9;
						//	}
						//	break;
						//}

						//if( GetEntity() != NULL && iTileNum != -1 )
						//	GetEntity()->DrawTileImg( this->GetDC(), SPR_PUTSPRT, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, iTileNum, true);

						// �̴� �׸� ũ�⿡ �°� ������ Scratch Mode!
						//if( m_spr.clHeader.siXsize > MINI_PICTURE_WIDTH && m_spr.clHeader.siYsize > MINI_PICTURE_HEIGHT )
						//	BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
						//else
						//	BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);

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
					m_editBTN_Property[i].SetWindowText(strTmp);

			}

		}
	}
}

// ��ǥ ��� : ���̾�α� �������� ��Ʈ��
// �۾� ���� : ��Ʈ���� �Ӽ�â�� => ��Ʈ���� ���� ������ �����
void CButtonPropertyDlg::OnButtonApply() 
{
	int i=0;
	m_bError = false;

	if( m_hWnd )
	{
		if( GetEntity() )
		{
			CString	strTemp[BTN_PROPERTY_COUNT];
			CString strTemp2;
			CString strTileImageNum;
			CString strTile;
			CString strTimeImageStartFont;
			CString tmpstr;

			int R = 0, G = 0, B = 0;
            m_editBTN_Property[BTN_TEXT_COLOR_R].GetWindowText(tmpstr);
			R = _ttoi(tmpstr);
			m_editBTN_Property[BTN_TEXT_COLOR_G].GetWindowText(tmpstr);
			G = _ttoi(tmpstr);
			m_editBTN_Property[BTN_TEXT_COLOR_B].GetWindowText(tmpstr);
			B = _ttoi(tmpstr);
			tmpstr.Format("%d", RGB(R,G,B) );
            m_editBTN_Property[BTN_TEXT_COLOR].SetWindowText(tmpstr);

			for(i=0; i<BTN_PROPERTY_COUNT; i++)
			{
				// ��Ʈ�ѿ� �Է��� �� ����
                m_editBTN_Property[i].GetWindowText(strTemp[i]);
				
				if(i == BTN_RESOURCE_ID)
				{
                    if(GetEntity()->IsOverLapping(GetEntity(), strTemp[BTN_RESOURCE_ID]))
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
						&& i == BTN_BG_IMAGE_FULLPATH )/*|| i == BTN_BG_TILE*/ || i == BTN_BG_START_FONT
						|| i == BTN_BG_WIDTH || i == BTN_BG_HEIGHT || i == BTN_BG_TILE_IMAGE_NUM )
					{
						if(GetEntity()->GetPicFullPath() != strTemp[BTN_BG_IMAGE_FULLPATH])
							GetEntity()->SetPicFullPath(strTemp[BTN_BG_IMAGE_FULLPATH]);

						//if(GetEntity()->GetPicFullPath().Trim(STR_TRIM_LETTER) != STR_EMPTY && GetEntity()->GetPicFullPath() != GetEntity()->GetOldPicFullPath())
						{
							GetEntity()->DeleteAllBmp();
							GetEntity()->DeleteAllBufferDC();
							GetEntity()->ClearAllOldBmp();

							GetEntity()->m_spr.ClearImageData();

							// Ÿ�� �̹��� ������ ���� ũ��� �޸� ���� ����!!
							if(GetEntity()->m_spr.LoadSpr( (char*)(LPCTSTR) strTemp[BTN_BG_IMAGE_FULLPATH].Trim(STR_TRIM_LETTER)))
							{
								m_editBTN_Property[BTN_BG_TILE_IMAGE_NUM].GetWindowText(strTileImageNum);
								m_editBTN_Property[BTN_BG_TILE].GetWindowText(strTile);
								m_editBTN_Property[BTN_BG_START_FONT].GetWindowText(strTimeImageStartFont);

                                if(strTile != STR_ZERO) // Ÿ�� ����϶� ��Ʈ �̹��� ����
									GetEntity()->MakeMemDC(GetParent()->GetDC(), atoi(strTimeImageStartFont), atoi(strTileImageNum) );
								else	// �� �̹��� ��� �϶�
									GetEntity()->MakeMemDC(GetParent()->GetDC(), atoi(strTimeImageStartFont), WHOLE_IMAGE_STYLE_FONTNUM);
							}

							if(GetEntity()->GetOldPicFullPath() != strTemp[BTN_BG_IMAGE_FULLPATH])
								GetEntity()->SetOldPicFullPath(strTemp[BTN_BG_IMAGE_FULLPATH]);

							//if(m_picFullPath != strTemp[BTN_BG_IMAGE_FULLPATH])
							//	m_picFullPath = strTemp[BTN_BG_IMAGE_FULLPATH];

							//if(m_oldPicFullPath != m_picFullPath)
							//	m_oldPicFullPath = m_picFullPath;
						}
					}
				}

			} // for(...)

			strTemp2.Empty();
			int sub_width = 0, sub_BG_width =0, sub_height = 0, sub_BG_height = 0;

			sub_width = _ttoi(strTemp[BTN_WIDTH]);
			sub_height = _ttoi(strTemp[BTN_HEIGHT]);
			sub_BG_width = _ttoi(strTemp[BTN_BG_WIDTH]);
			sub_BG_height = _ttoi(strTemp[BTN_BG_HEIGHT]);

			// tile size => strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_width, m_spr.clHeader.siXsize));
			strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_width, 1));
			m_editBTN_Property[BTN_WIDTH].SetWindowText(strTemp2);
			GetEntity()->SetPropertyWithIndex(strTemp2, BTN_WIDTH);
	
			// Disable�� �ؼ� �������
			//if(sub_width > sub_BG_width)
			//{
	            m_editBTN_Property[BTN_BG_WIDTH].SetWindowText(strTemp2);
				GetEntity()->SetPropertyWithIndex(strTemp2, BTN_BG_WIDTH);
			//}
			//else
			//{
			//	strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_BG_width, m_spr.clHeader.siXsize));
	  //          m_editBTN_Property[BTN_BG_WIDTH].SetWindowText(strTemp2);
			//	GetEntity()->SetPropertyWithIndex(strTemp2, BTN_BG_WIDTH);
			//}

			//tile size => strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_height, m_spr.clHeader.siYsize));
			strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_height, 1));
			m_editBTN_Property[BTN_HEIGHT].SetWindowText(strTemp2);
			GetEntity()->SetPropertyWithIndex(strTemp2, BTN_HEIGHT);
	
			//if(sub_height > sub_BG_height)
			//{
				m_editBTN_Property[BTN_BG_HEIGHT].SetWindowText(strTemp2);
				GetEntity()->SetPropertyWithIndex(strTemp2, BTN_BG_HEIGHT);
			//}
			//else
			//{
			//	strTemp2.Format("%d", GetEntity()->SetToMultipleSize(sub_BG_height, m_spr.clHeader.siYsize));
			//	m_editBTN_Property[BTN_BG_HEIGHT].SetWindowText(strTemp2);
			//	GetEntity()->SetPropertyWithIndex(strTemp2, BTN_BG_HEIGHT);
			//}

			// id ���ڼ��� 30�ڸ� ���� ���ϰ� ��
			CString tmpStr;           
			m_editBTN_Property[RESOURCE_ID].GetWindowText(tmpStr);
			if(tmpStr.GetLength() > ID_LENGTH)
			{
				AfxMessageBox(tmpStr + " ID ���� 30�ڸ� �ʰ��߽��ϴ�.\n �ٽ� �Է��ϼ���!");
				tmpStr = tmpStr.Left( 30 );
				m_editBTN_Property[RESOURCE_ID].SetWindowText(tmpStr);
				m_bError = true;
			}

            
			GetParent()->RedrawWindow();
		}
	}	
}

// ��ư �Ӽ�â�� �̹��� �̸� ���� ó��
// ��ǥ ��� : ��Ʈ���� �Ӽ�â
void CButtonPropertyDlg::OnBnClickedButtonBtnSearch()
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

			m_editBTN_Property[BTN_BG_IMAGE_FULLPATH].SetWindowText( fileDlg.GetPathName() );

			if(m_spr.LoadSpr( (char *)(LPCTSTR)fileDlg.GetPathName().Trim(STR_TRIM_LETTER)))
				MakeMemDC(this->GetDC());

			if(m_oldPicFullPath != m_picFullPath)
				m_oldPicFullPath = m_picFullPath;

			//CRect rect(MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_LEFT + MINI_PICTURE_WIDTH, MINI_PICTURE_TOP + MINI_PICTURE_HEIGHT);
			//CStdGrfx::draw3dFrame(this->GetDC(), rect);
			//CStdGrfx::drawframed3dBox( this->GetDC(), rect );

			CRect rect(0, 0, m_spr.clHeader.siXsize+2*PIXEL_OFFSET_X, m_spr.clHeader.siYsize+2*PIXEL_OFFSET_Y);

			CStdGrfx::drawframed3dBox( GetBufferDC(WORK_BACKGROUND_NUM), rect );

			BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(MASK_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);
			BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(REAL_BACKGROUND_NUM), m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, PIXEL_OFFSET_X, PIXEL_OFFSET_Y);
			BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize + PIXEL_OFFSET_X*2, m_spr.clHeader.siYsize + PIXEL_OFFSET_Y*2, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);

			//BitBltDS( this->GetDC(), GetBufferDC(MASK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
			//BitBltDS( this->GetDC(), GetBufferDC(REAL_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);

			CString strTmp;

			// �Է��� �̹��� ���� fullpath �Ľ�
			ParsingFileFullPath(fileDlg.GetPathName());

			CString tileMode = GetTileMode();
			CString tileImageNum = GetTileImageNum();

			if(tileMode.Trim() != STR_EMPTY)
			{
				if(tileMode.Trim() == STR_ZERO && _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM0)	// ��� ���
					m_editBTN_Property[BTN_BG_TILE].SetWindowText(STR_ZERO);
				else // "1"�̸� ���� ���, "2"�̸� ���� ���
					m_editBTN_Property[BTN_BG_TILE].SetWindowText(STR_ONE);
			}
			else // ����Ʈ�� ��ʹ��
				m_editBTN_Property[BTN_BG_TILE].SetWindowText(STR_ZERO);

			if(tileImageNum.Trim() != STR_EMPTY)
			{
				if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM0 || _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM1
					|| _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM3 || _ttoi(tileImageNum) == VALID_TILEIMAGE_NUM9)
				{
					strTmp.Format("%d", _ttoi(tileImageNum));
					m_editBTN_Property[BTN_BG_TILE_IMAGE_NUM].SetWindowText(strTmp);
				}
				else
				{
					strTmp = STR_ZERO;
					m_editBTN_Property[BTN_BG_TILE_IMAGE_NUM].SetWindowText(strTmp);
				}
			}

			//if(_ttoi(tileImageNum) < 2)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize);
			//	m_editBTN_Property[BTN_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize);
			//	m_editBTN_Property[BTN_HEIGHT].SetWindowText(strTmp);
			//}
			//else if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM3)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize * _ttoi(tileImageNum));
			//	m_editBTN_Property[BTN_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize);
			//	m_editBTN_Property[BTN_HEIGHT].SetWindowText(strTmp);
			//}
			//else if(_ttoi(tileImageNum) == VALID_TILEIMAGE_NUM9)
			//{
			//	strTmp.Format("%d", m_spr.clHeader.siXsize * 3);
			//	m_editBTN_Property[BTN_WIDTH].SetWindowText(strTmp);
			//	strTmp.Format("%d", m_spr.clHeader.siYsize * 3 );
			//	m_editBTN_Property[BTN_HEIGHT].SetWindowText(strTmp);
			//}

			//// ũ�⿡ ����.. surface ����
			//m_editBTN_Property[BTN_WIDTH].GetWindowText(strTmp);
			//m_editBTN_Property[BTN_BG_WIDTH].SetWindowText(strTmp);
			//m_editBTN_Property[BTN_HEIGHT].GetWindowText(strTmp);
			//m_editBTN_Property[BTN_BG_HEIGHT].SetWindowText(strTmp);

			// ���̾�α� ũ�� ��ȭ ���� �̹��� ���� ��Ű��!!
			int sub_width = 0, sub_height = 0;
			m_editBTN_Property[BTN_WIDTH].GetWindowText(strTmp);
			sub_width = _ttoi(strTmp);
			m_editBTN_Property[BTN_HEIGHT].GetWindowText(strTmp);
			sub_height = _ttoi(strTmp);
            
			// tile size => strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_width, m_spr.clHeader.siXsize));
			strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_width, 1));
			// ũ�⿡ ����.. surface ����
			m_editBTN_Property[BTN_WIDTH].SetWindowText(strTmp);
			m_editBTN_Property[BTN_BG_WIDTH].SetWindowText(strTmp);

			// tile size => strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_height, m_spr.clHeader.siYsize));
			strTmp.Format("%d", GetEntity()->SetToMultipleSize(sub_height, 1));
			m_editBTN_Property[BTN_HEIGHT].SetWindowText(strTmp);
			m_editBTN_Property[BTN_BG_HEIGHT].SetWindowText(strTmp);

		}
	}
	
	//this->RedrawWindow();
	this->SendMessage( WM_PAINT );
}

void CButtonPropertyDlg::OnPaint()
{
	CDiagramPropertyDlg::OnPaint();
}

BOOL CButtonPropertyDlg::OnInitDialog()
{
	CDiagramPropertyDlg::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CButtonPropertyDlg::OnBnClickedHide()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	this->ShowWindow(SW_HIDE);
}

void CButtonPropertyDlg::OnBnClickedButtonBtnPathEmpty()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_editBTN_Property[BTN_BG_IMAGE_FULLPATH].SetWindowText(STR_EMPTY);
	m_editBTN_Property[BTN_BG_TILE].SetWindowText(STR_ZERO);
	m_editBTN_Property[BTN_BG_TILE_IMAGE_NUM].SetWindowText(STR_ZERO);
	m_editBTN_Property[BTN_BG_START_FONT].SetWindowText(STR_ZERO);

	
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
void CButtonPropertyDlg::OnBnClickedButtonBtnTextSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShowFontDialog();
	//CString tmpStr = m_fontName;
	//tmpStr.Format("%s %d %d", tmpStr, m_fontSize, m_fontColor);
	//AfxMessageBox(tmpStr);
	CString tmpStr;

	m_editBTN_Property[BTN_TEXT_STYLE].SetWindowText(GetFontName());
	tmpStr.Format("%d", GetFontSize());
	m_editBTN_Property[BTN_TEXT_SIZE].SetWindowText(tmpStr);
	tmpStr.Format("%d", GetFontColor());
	m_editBTN_Property[BTN_TEXT_COLOR].SetWindowText(tmpStr);

}

void CButtonPropertyDlg::OnOK()
{
	OnButtonApply();
	if(m_bError == false)
		CDialog::OnOK();
}
void CButtonPropertyDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	
	CDiagramPropertyDlg::OnShowWindow(bShow, nStatus);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
