// MapTileDivDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MapTileDiv.h"
#include "MapTileDivDlg.h"
#include ".\maptiledivdlg.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMapTileDivDlg ��ȭ ����



CMapTileDivDlg::CMapTileDivDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapTileDivDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_image = NULL;
	m_mask = NULL;
}

void CMapTileDivDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMapTileDivDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CMapTileDivDlg �޽��� ó����

BOOL CMapTileDivDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CMapTileDivDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if( (nID & 0xFFF0) == IDM_ABOUTBOX )
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMapTileDivDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();
	}
}

//  ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CMapTileDivDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMapTileDivDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	HANDLE hFile = NULL;

	XSPRImgTag		*imagetag = NULL;
	unsigned char   **image = NULL;

	unsigned char tile1[ 80 * 40 ];
	unsigned char tile2[ 80 * 40 ];

	char szFilters[] = "Pcx Files(*.pcx)|*.pcx|All Files(*.*)|*.*||";

	CFileDialog fileDlg( TRUE, NULL, "*.pcx", OFN_FILEMUSTEXIST, szFilters, this);


	// mask �̹����� �ҷ��´�
	LoadSpr( "mask.spr", &m_mask );

	if( m_mask == NULL ) {
		MessageBox( "mask.spr ������ �����ϴ�", "����" );
		goto end;
	}


	if( IDOK != fileDlg.DoModal() ) goto end;


	// pcx�� �ҷ��´�
	LoadPCX( (char *)(LPCTSTR)fileDlg.GetPathName() );


	if( m_image == NULL ) {
		MessageBox( "������ �о���µ� �����Ͽ����ϴ�", "����" );
		goto end;
	}


	int i, j, k, l;
	int orgx, xnum, ynum;
	int tx, ty;

	for( i = 0; i < m_imagewidth; ++i ) {
		if( m_image[ i ] != 254 ) break;
	}

	orgx = i + 1;

	// x, y Ÿ��  ���� ���ϱ� 
	xnum = ( m_imagewidth - orgx ) / 40;
	ynum = ( orgx ) / 40;



	// ������ ������ �����Ѵ� 
	
		
	hFile =	CreateFile( "convertmap.xpr", 
						GENERIC_WRITE, 
						NULL, 
						NULL, 
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL );

	if( hFile == INVALID_HANDLE_VALUE ) goto end;

	// ��������� ����Ѵ� 
	XSPRFileHeader	header;

	ZeroMemory( &header, sizeof( header ) );

	strcpy( header.id, "XPR" );
	header.version = 1;
	header.encodetype = 3;
	header.pixelformat = 0;
	header.pal_type = 16;
	header.canvasWidth = 80;
	header.canvasHeight = 40;
	header.xnum = xnum;
	header.ynum = ynum;

	header.imagenum = xnum * ynum;


	imagetag = new XSPRImgTag[ header.imagenum ];

	image = new unsigned char*[ header.imagenum ];
	
	for( i = 0; i < header.imagenum; ++i ) image[ i ] = NULL;

	DWORD dwWrite;


	int totallen = 0, len = 0;
	int n = 0;

	for( i = 0; i < ynum; ++i ) {

		for( j = 0; j < xnum; ++j ) {

			tx = (orgx - 40) + (j - i) * 40;
			ty = ( j + i ) * 20;

			if( tx < 0 || ty < 0 ||
				tx + 80 > m_imagewidth ||
				ty + 40 > m_imageheight ) {

					MessageBox( "�׸� ũ�Ⱑ �߸� �Ǿ����ϴ�", "����" );
					goto end;
				}


			for( k = 0; k < 40; ++k ) {
				for( l = 0; l < 80; ++l ) {
					
					if( m_mask[ k * 80 + l ] == 254 ) {
						tile1[ k * 80 + l ] = 254;
					} else {
						tile1[ k * 80 + l ] = m_image[ (ty + k ) * m_imagewidth + ( tx + l ) ];
					}
				}
			}

			len = EncodeZpr( tile2, tile1, 80, 40 );
			totallen += len;

			image[ n ] = new unsigned char[ len ];
			memcpy( image[ n ], tile2, len );

			if( n == 0 ) imagetag[ n ].offset = 0;
			else imagetag[ n ].offset = imagetag[ n - 1 ].offset + imagetag[ n - 1 ].size;
			imagetag[ n ].size = len;
			imagetag[ n ].height = 40;
			imagetag[ n ].width = 80;
			
			n++;
		}

	}

	header.bodysize = header.imagenum * sizeof( XSPRImgTag ) + totallen;

	int filesize = sizeof( header ) + header.bodysize + 1024;

	header.filesize = filesize;
	

	WriteFile( hFile, &header, sizeof( header ), &dwWrite, NULL );
	WriteFile( hFile, imagetag, sizeof( XSPRImgTag ) * header.imagenum, &dwWrite, NULL );
	for( i = 0; i < header.imagenum; ++i ) {
		WriteFile( hFile, image[ i ], imagetag[ i ].size, &dwWrite, NULL );
	}
	WriteFile( hFile, m_pal565, 512, &dwWrite, NULL );
	WriteFile( hFile, m_pal555, 512, &dwWrite, NULL );


	char buffer[ 1024 ];

	sprintf( buffer, "(%d,%d) �̹���ũ��: %dByte, ����ũ�� %dByte", xnum, ynum, totallen, filesize );

	MessageBox( buffer );

end:

	if( hFile ) CloseHandle( hFile );

	if( image ) {
		for( i = 0; i < header.imagenum; ++i ) {
			if( image[ i ] ) delete [] image[ i ];
		}

		delete [] image;
	}

	if( imagetag ) delete [] imagetag;

	if( m_image ) {
		delete [] m_image;
		m_image = NULL;
	}

	if( m_mask ) {
		delete [] m_mask;
		m_mask = NULL;
	}

}

void CMapTileDivDlg::LoadSpr( char *filename, unsigned char **pImg )
{
	if( *pImg ) delete [] *pImg;
	*pImg = NULL;

	cltTSpr spr;

	if( spr.LoadSpr( filename ) == FALSE ) return;

	unsigned char *pImage = new unsigned char[ spr.clHeader.siXsize * spr.clHeader.siYsize ];
	*pImg = pImage;

	int i, j;

	unsigned char *psrc;

	psrc = spr.Image;

	for( i = 0; i < spr.clHeader.siYsize; ++i ) {

		j = 0;

		while( j < spr.clHeader.siXsize ) {

			if( *psrc == 254 ) {
				++psrc;
				memset( &pImage[ i * spr.clHeader.siXsize + j ], 254, *psrc );
				j += *psrc;
				++psrc;
			
			} else {
				pImage[ i * spr.clHeader.siXsize + j ] = *psrc;
				++psrc;
				++j;
			}
		}
	}

}


void CMapTileDivDlg::LoadPCX( char *filename )
{

	unsigned char *buffer = NULL;
	unsigned char *pImage = NULL;
	unsigned char *canvas = NULL;

	PCXHEADER pcxheader;
	
	HANDLE hFile = NULL;
		
	// ������ �����Ѵ�
	hFile = CreateFile( filename, 
						GENERIC_READ, 
						FILE_SHARE_READ, 
						NULL, 
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL );

	if( hFile == INVALID_HANDLE_VALUE ) {
		hFile = NULL;
		goto end;
	}

	// ���� ũ�⸦ ���´�
	DWORD dwFileSize;
	dwFileSize = GetFileSize( hFile, NULL );

	if( dwFileSize == INVALID_FILE_SIZE ||
		dwFileSize == 0 ) {
		goto end;
	}

	// ���� ��ü �����͸� ������ ���۸� �����Ѵ�
	buffer = new unsigned char[ dwFileSize ];


	// ���� ��ü �����͸� ���´�
	DWORD dwRead;
	if( ReadFile( hFile, buffer, dwFileSize, &dwRead, NULL ) == FALSE ) {
		goto end;
	}

	if( dwRead != dwFileSize ) {
		goto end;
	}
	
	// ������ �ݴ´�
	CloseHandle( hFile );
	hFile = NULL;

	// ����� �����Ѵ�
	memcpy( &pcxheader, buffer, sizeof( pcxheader ) );

	// �̹��� �������� ���� ��ġ�� ��´�
	pImage = buffer + sizeof( pcxheader );

	// Each scan line MUST have a size that can be divided by a 'long' data type
	int scanLineSize = pcxheader.numPlanes * pcxheader.BPL;

	scanLineSize = ( ( scanLineSize + 3 ) / 4 ) * 4;

	// �̹��� ũ�⸦ ��´�
	int xsize, ysize;

	xsize = pcxheader.x2 - pcxheader.x1 + 1;
	ysize = pcxheader.y2 - pcxheader.y1 + 1;

	m_imagewidth = xsize;
	m_imageheight = ysize;

	if( m_image ) delete [] m_image;
	m_image = new unsigned char[ xsize * ysize ];
	canvas = m_image;
	
	// �̹��� �����͸� ���ڵ��Ѵ�
	int i, j, k, count;
	for( i = 0; i < ysize; ++i ) {

		for( j = 0; j < pcxheader.BPL; ) {
	
			if( *pImage > 192 ) {
			
				count = *pImage - 192;
				++pImage;

				for( k = 0; k < count; ++k ) {
					canvas[ i * xsize + j ] = *pImage;
					++j;
				}

			} else {

				canvas[ i * xsize + j ] = *pImage;
				++j;
			}

			++pImage;
		}

	}

	// Simple validation
	if( *pImage == 12 ) {		
		++pImage;

		// Get the palette
		for( i = 0; i < 256; ++i ) {

			m_pcxpal[ i * 3 ] = *(pImage);
			m_pcxpal[ i * 3 + 1 ] = *(pImage + 1);
			m_pcxpal[ i * 3 + 2 ] = *(pImage + 2);

			pImage += 3;
		}
	}

	// ���� Į�� �ٲٱ� 
	
	PCXPAL palTrans;
	unsigned char ci;


	palTrans.r = 248;
	palTrans.g = 8;
	palTrans.b = 248;

	// ������� �� ��ġ�� ������,
	if( m_pcxpal[ 254 * 3 ] == palTrans.r &&
		m_pcxpal[ 254 * 3 + 1 ] == palTrans.g &&
		m_pcxpal[ 254 * 3 + 2 ] == palTrans.b ) {
		goto makepal;
	}

	// ����� ��ġ ã�� 
	for( i = 0; i < 256; ++i ) {
		if( m_pcxpal[ i * 3 ] == palTrans.r &&
			m_pcxpal[ i * 3 + 1 ] == palTrans.g &&
			m_pcxpal[ i * 3 + 2 ] == palTrans.b ) {

			ci = i;
			break;
		}
	}

	if( i == 256 ) {
		MessageBox( "�ȷ�Ʈ�� ������� �����ϴ�. �����RGB(240,0,255)" );
		if( m_image ) {
			delete [] m_image;
			m_image = NULL;
		}
		goto end;
	}

	// ���� �ٲٱ� 
	for( i = 0; i < ysize; ++i ) {
		for( j = 0; j < xsize; ++j ) {
			if( m_image[ i * xsize + j ] == ci ) {
				m_image[ i * xsize + j ] = 254;
			} else if( m_image[ i * xsize + j ] == 254 ) {
				m_image[ i * xsize + j ] = ci;
			}
		}
	}

	// �ȷ�Ʈ �ٲٱ� 
	m_pcxpal[ ci * 3 ] = m_pcxpal[ 254 * 3 ];
	m_pcxpal[ ci * 3 + 1] = m_pcxpal[ 254 * 3 + 1 ];
	m_pcxpal[ ci * 3 + 2] = m_pcxpal[ 254 * 3 + 2 ];

	m_pcxpal[ 254 * 3 ] = palTrans.r;
	m_pcxpal[ 254 * 3 + 1] = palTrans.g;
	m_pcxpal[ 254 * 3 + 2] = palTrans.b;

makepal:
	// 16�ȷ�Ʈ �����

	UI16 r, g, b;

	for( i = 0; i < 256; ++i ) {

		r = m_pcxpal[ i * 3 ] >> 3;
		g = m_pcxpal[ i * 3 + 1 ] >> 2;
		b = m_pcxpal[ i * 3 + 2 ] >> 3;

		r = RGB16_565_RMASK & ( r << 11);
		g = RGB16_565_GMASK & ( g << 5);
		b = RGB16_565_BMASK & ( b );

		m_pal565[ i ] = r | g | b;

		r = m_pcxpal[ i * 3 ] >> 3;
		g = m_pcxpal[ i * 3 + 1 ] >> 3;
		b = m_pcxpal[ i * 3 + 2 ] >> 3;

		r = RGB16_555_RMASK & ( r << 10);
		g = RGB16_555_GMASK & ( g << 5);
		b = RGB16_555_BMASK & ( b );
		
		m_pal555[ i ] = r | g | b;

	}

end:
	if( hFile ) CloseHandle( hFile );
	if( buffer ) delete [] buffer;
	
	return;
}


int CMapTileDivDlg::EncodeZpr( UI08 *pDestImage, UI08 *pSrcImage, int width, int height )
{
	UI08 repcolor;			// �ݺ� ����
	UI08 repcnt;			// �ݺ� Ƚ��

	int i, j;
	LONG lPitch = width;
 
	UI08 *pdest = pDestImage;
	UI08 *psrc = pSrcImage;

	for( i = 0; i < height; ++i ) {

		repcolor = psrc[ 0 ];
		repcnt = 1;

		for( j = 1; j < width; ++j ) { 

			// ���� ����� ���� �Ѱ�
			if( psrc[ j ] == repcolor ) {

				if( repcnt == 254 ) {
					// �ݺ� Ƚ���� 255ȸ �̻��̸�, 

					if( repcolor == 254 ) {
						// ������̸�,
					
						*pdest = 254;
						++pdest;

						*pdest = 254;
						++pdest;

						repcnt = 1;
						continue;

					} else {
						// �Ϲݻ��̸�,

						*pdest = 254;
						++pdest;

						*pdest = 255;
						++pdest;

						*pdest = repcolor;
						++pdest;

						*pdest = 254;
						++pdest;
						
						repcnt = 1;
						continue;
					}
				
				} else {
					++repcnt;
					continue;
				}

			} else {

				if( repcolor == 254 ) {
					// ������̸�,

					*pdest = 254;
					++pdest;

					*pdest = repcnt;
					++pdest;

					repcolor = psrc[ j ];
					repcnt = 1;
					continue;

				} else {
					// �Ϲݻ��̸�,

					if( repcnt > 4 ) {
						// 5�ȼ� �̻��� ���� �Ǿ�����,
						
						*pdest = 254;
						++pdest;

						*pdest = 255;
						++pdest;

						*pdest = repcolor;
						++pdest;

						*pdest = repcnt;
						++pdest;

					} else {

						memset( pdest, repcolor, repcnt );
						pdest += repcnt;
					}

					repcolor = psrc[ j ];
					repcnt = 1;
					continue;
				}				
			}
		}

		if( repcolor == 254 ) {
			// ������̸�,

			*pdest = 254;
			++pdest;

			*pdest = repcnt;
			++pdest;

		} else {
			// �Ϲݻ��̸�,

			if( repcnt > 4 ) {
				// 5�ȼ� �̻��� ���� �Ǿ�����,
				
				*pdest = 254;
				++pdest;

				*pdest = 255;
				++pdest;

				*pdest = repcolor;
				++pdest;

				*pdest = repcnt;
				++pdest;

			} else {

				memset( pdest, repcolor, repcnt );
				pdest += repcnt;
			}

		}				

		psrc += lPitch;
	}

	return (int)(pdest - pDestImage);
}

