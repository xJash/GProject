#include <Graphic.h>
#include "EtcTool.h"

//palette ȭ���� �ҷ��´�.
BOOL cltGrp::LoadOnlyPaletteFile(char* filename, unsigned char* pal)
{
	FILE *fp;

	fp=fopen(filename, "rb");
	if(fp==NULL)
	{
		return FALSE;
	}

	fread(pal, 768, 1, fp);

	fclose(fp);
	return TRUE;
}

//palette ȭ���� �ҷ��´�.
BOOL cltGrp::LoadOnlyPaletteFile(char* filename)
{
	FILE *fp;

	fp=fopen(filename, "rb");
	if(fp==NULL)
	{
		return FALSE;
	}

	fread( Palette, 768, 1, fp );		//Palette �� type �� unsigned char Palette[768];

	fclose(fp);
	return TRUE;
}


void cltGrp::SetColorTable()
{

    SetPalette16("Pal\\Palette16.dat");
	// ����ȿ�� 1 �迭 �ʱ�ȭ 
    InitLightEffect1();

	//DarkAlpha���� �����Ѵ�.
	InitDarkAlpha(Palette);
	InitShadowAlpha(Palette);
	
	InitDarkTable(Palette);

	// JAYCEE MODIFIED
	InitAddTable("Pal\\Add.dat");
	InitScreenTable("Pal\\Screen.dat");
	InitMultiplyTable("Pal\\Multiply.dat");

}

// 16��Ʈ �ȷ�Ʈ�� ���� �ִ´�. 
BOOL cltGrp::SetPalette16(char* filename)
{
	int r, g, b;
	int i;
	int min_diff;
	int diff;
	int index;

	FILE* fp;
	// ���Ͽ��� �о�� ������ �����. 

	fp = fopen(filename, "rb");
	if(fp)
	{
		fread(Palette16,  sizeof(UI08)*64*64*64 , 1, fp);
		fread(PaletteRGB, sizeof(UI08)*256*3	, 1, fp);
		fclose(fp);
	}
	else
	{
		
		for( r = 0; r < 64; ++r )
			for( g = 0; g < 64; ++g )
				for( b = 0; b < 64; ++b )
				{
					min_diff = 30000;
					
					for( i = 0; i < 256; ++i )
					{
						index = i * 3;
						
						
						diff =  (TABS(r - Palette[index])     * TABS(r - Palette[index]))
							+(TABS(g - Palette[index + 1]) * TABS(g - Palette[index + 1]))
							+(TABS(b - Palette[index + 2]) * TABS(b - Palette[index + 2]));
						
						if( diff < min_diff )
						{
							min_diff                 = diff;
							Palette16[ r ][ g ][ b ] = i;
						}
					}
				}
				
		for( i = 0; i < 256; ++i )
		{
			index = i * 3;
					
			PaletteRGB[ i ][ 0 ] = Palette[ index ];
			PaletteRGB[ i ][ 1 ] = Palette[ index + 1 ];
			PaletteRGB[ i ][ 2 ] = Palette[ index + 2 ];
		}
				
		// ������ ������ �����Ѵ�. 
		fp = fopen(filename, "wb");
		if(fp)
		{
			fwrite(Palette16,  sizeof(UI08)*64*64*64 , 1, fp);
			fwrite(PaletteRGB, sizeof(UI08)*256*3	, 1, fp);
			fclose(fp);
		}
		
	}
	
	return FALSE;
}

// 2002.9.11 ���� ����, ����ȭ �۾�
UI16 cltGrp::GetPalette16(int r, int g, int b)
{
	// ����� ���� �ε����� ã�´�. 
	int i;
	int index;
	int diff;
	int min_diff=1000;
	UI16 min_color=0;
	
	for(i = 0; i < 256; i++)
	{
		index = i * 3;
		diff  = TABS(Palette[index] - r) + TABS(Palette[index + 1] - g) + TABS(Palette[index + 2] - b);
		if(diff < min_diff)
		{
			min_diff  = diff;
			min_color = i;
		}
	}
	
	return min_color;
}

// ����ȿ�� 1 �迭 �ʱ�ȭ 
void cltGrp::InitLightEffect1()
{
    SHORT bg;  // �� �׶��� 
	SHORT spr;  // ��������Ʈ 
	SHORT tempsum;

	for( bg = 0; bg < 64; bg++ )
	{
		for( spr = 0; spr < 64; spr++ )
		{
			tempsum = ( 64 - max( bg, spr ) ) / 64 * min( bg, spr );
			LightEffect1[ bg ][ spr ] = max( bg, spr ) + tempsum;
		}
	}

}



// rgb���� Palette16�� ���� index������ ��ȯ �����ش�. 
void cltGrp::GetArrayIndexFromColor(int r, int g, int b, int& r1, int &g1, int &b1)
{
	r1 = ( r >> 3 );
	g1 = ( g >> 2 );
	b1 = ( b >> 3 );

	return;
}

LPDIRECTDRAWPALETTE cltGrp::CreateDirectDrawPalette(LPDIRECTDRAW7 pDirectDrawObj, unsigned char* pal)
{
	LPDIRECTDRAWPALETTE pDirectDrawPal;
	PALETTEENTRY *oldentry;
	HDC hdc;
	int i, number;

	
	oldentry = new PALETTEENTRY[256];

	if(oldentry==NULL)
	{
		MsgBox("Palette", "OldEntry:0001");
	}


	hdc = GetDC( NULL );

	if( GetSystemPaletteUse( hdc ) == SYSPAL_NOSTATIC )
	{
		memcpy( OriginalPal, pal, 768 );
	}
	else
	{
		number = GetDeviceCaps( hdc, NUMCOLORS );
		GetSystemPaletteEntries( hdc, 0, 256, oldentry );

		memcpy( OriginalPal, pal, 768 );

		for( i = 0; i < number/2; ++i )
		{
			OriginalPal[ i * 3 ] = oldentry[i].peRed/4;
			OriginalPal[ i * 3 + 1 ] = oldentry[ i ].peGreen / 4;
			OriginalPal[ i * 3 + 2 ] = oldentry[ i ].peBlue / 4;
		}

		for( i = ( 256 - number ); i < 256; ++i )
		{
			OriginalPal[ i * 3 ] = oldentry[ i ].peRed / 4;
			OriginalPal[ i * 3 + 1 ] = oldentry[ i ].peGreen / 4;
			OriginalPal[ i * 3 + 2 ] = oldentry[ i ].peBlue / 4;
		}
	}

	ReleaseDC(0, hdc);

	for( int x = 0; x < 256; ++x )
	{
		PalEntries[ x ].peRed = pal[ x * 3 ] * 4;
		PalEntries[ x ].peGreen = pal[ x * 3 + 1 ] * 4;
		PalEntries[ x ].peBlue = pal[ x * 3 + 2 ] * 4;
		
		PalEntries[ x ].peFlags = PC_NOCOLLAPSE;
	}

	HRESULT result = pDirectDrawObj->CreatePalette( DDPCAPS_8BIT, PalEntries, &pDirectDrawPal, NULL );

	if( result != DD_OK )
	{
		pDirectDrawPal = NULL;
	}

	delete [] oldentry;

	oldentry = NULL;

	return pDirectDrawPal;
}

// �ȷ�Ʈ�� ��ü�� ����� �����Ѵ�.
BOOL cltGrp::SetAllPalette()
{
	// 8��Ʈ �÷��� ������ �ȷ�Ʈ�� ������ �� �ִ�. 
	if(ColorDepth !=8)	return FALSE;
	
	// �ȷ�Ʈ ��ü�� �����. 
	lpDDPal = CreateDirectDrawPalette( lpDD7, Palette );


	// �ȷ�Ʈ ��ü�� �����Ѵ�. 
	SetPalette();

    return TRUE;
}

// ������ lpddPal��ü�� ������ �ȷ�Ʈ�� �����Ѵ�. 
HRESULT cltGrp::SetPalette()
{
	if(lpDDPal != NULL)
	{
		// ���� ������ �ȷ�Ʈ�� �����Ѵ�. 
	    memcpy(CurrentPal, Palette, 768);

		if ( lpDDSBack )
		{
			lpDDSBack->SetPalette(lpDDPal);
		}

		if( lpDDSPrimary )
		{
			return lpDDSPrimary->SetPalette(lpDDPal);
		}
	}

	return DD_OK;
}


void cltGrp::InitDarkAlpha(const unsigned char *pal)
{
	SI32 i;
	SI32 r, g, b;
	SI32 alpha;
	for(i = 0;i < 256;i++)
	{
		r = pal[i*3];
		g = pal[i*3 + 1];
		b = pal[i*3 + 2];

		alpha = 15 - ((r+ g+ b) / ((64*3)/MAX_DARK_STEP) );

		if(alpha < 0)				alpha = 0;
		if(alpha >= MAX_DARK_STEP)	alpha = MAX_DARK_STEP-1;

		DarkAlpha[i] = alpha;

	}


}

void cltGrp::InitShadowAlpha(const unsigned char *pal)
{
	SI32 i;

	for(i = 0;i < 256;i++)
	{
		ShadowAlpha[i] = i / (256/MAX_DARK_STEP);
	}
}


void cltGrp::InitDarkTable(const unsigned char *pal)
{
	SHORT i, j;
	SHORT r, g, b;

	for(i = 0;i < MAX_DARK_STEP;i++)
	{

		for(j = 0;j < 256;j++)
		{
			r=max(0, pal[j * 3    ] - (pal[j * 3    ] * i / MAX_DARK_STEP));
			g=max(0, pal[j * 3 + 1] - (pal[j * 3 + 1] * i / MAX_DARK_STEP));
			b=max(0, pal[j * 3 + 2] - (pal[j * 3 + 2] * i / MAX_DARK_STEP));

			DarkTable[i][j]=FindNearColor((UI08)r, (UI08)g, (UI08)b, pal);
		}
	}

	// ���� ��ο� ���� ���������� ĥ�Ѵ�. 
	for(j = 0;j < 256;j++)
	{
		DarkTable[MAX_DARK_STEP - 1][j] = 0;
	}

}


void cltGrp::InitAddTable(char* filename)
{
	// ���Ͽ��� �о�� ������ �����. 
	FILE* fp= fopen(filename, "rb");
	if(fp)
	{
		fread(AddTable,  sizeof(UI08)*256*256, 1, fp);
		fclose(fp);
	}
	else
	{
		SI32  siOrigRed, siOrigGreen, siOrigBlue;
		SI32  siEffRed,  siEffGreen,  siEffBlue;
		SI32  siRed, siGreen, siBlue;
		for(SI32 siCountB = 0; siCountB < 256; siCountB++ )
		{
			for(SI32 siCountA = 0; siCountA < 256; siCountA++)
			{
				// siCountA : BASE �̹��� , siCountB : Blend �̹��� 
				siOrigRed   = Palette[siCountA * 3    ] ;	// BASE
				siOrigGreen = Palette[siCountA * 3 +1 ] ;
				siOrigBlue  = Palette[siCountA * 3 +2 ] ;
				siEffRed	= Palette[siCountB * 3    ] ;	// Blend
				siEffGreen  = Palette[siCountB * 3 +1 ] ;
				siEffBlue   = Palette[siCountB * 3 +2 ] ;
				siRed   = siEffRed	+ siOrigRed;
				siGreen = siEffGreen+ siOrigGreen;
				siBlue  = siEffBlue + siOrigBlue;
				if(siRed   <0) siRed   = 0;	if(siRed  >=64) siRed   = 63;
				if(siGreen <0) siGreen = 0; if(siGreen>=64) siGreen = 63;  
				if(siBlue  <0) siBlue  = 0; if(siBlue >=64) siBlue  = 63;   
				AddTable[siCountA][siCountB] = Palette16[siRed][siGreen][siBlue];
			}
		}

		fp = fopen(filename, "wb");
		fwrite(AddTable,  sizeof(UI08)*256*256, 1, fp);
		fclose(fp);
	}
}

void cltGrp::InitScreenTable(char* filename)
{
	// ���Ͽ��� �о�� ������ �����. 
	FILE* fp= fopen(filename, "rb");
	if(fp)
	{
		fread(ScreenTable,  sizeof(UI08)*256*256, 1, fp);
		fclose(fp);
	}
	else
	{
		SI32  siOrigRed, siOrigGreen, siOrigBlue;
		SI32  siEffRed,  siEffGreen,  siEffBlue;
		SI32  siRed, siGreen, siBlue;
		for(SI32 siCountB = 0; siCountB < 256; siCountB++ )
		{
			for(SI32 siCountA = 0; siCountA < 256; siCountA++)
			{
				// siCountA : BASE �̹��� , siCountB : Blend �̹��� 
				siOrigRed   = Palette[siCountA * 3    ] ;	// BASE
				siOrigGreen = Palette[siCountA * 3 +1 ] ;
				siOrigBlue  = Palette[siCountA * 3 +2 ] ;
				siEffRed	= Palette[siCountB * 3    ] ;	// Blend
				siEffGreen  = Palette[siCountB * 3 +1 ] ;
				siEffBlue   = Palette[siCountB * 3 +2 ] ;
				siRed   = siEffRed	+ siOrigRed	 *(63 - siEffRed  )/63;
				siGreen = siEffGreen+ siOrigGreen*(63 - siEffGreen)/63;
				siBlue  = siEffBlue + siOrigBlue *(63 - siEffBlue )/63;
				if(siRed   <0) siRed   = 0;	if(siRed  >=64) siRed   = 63;
				if(siGreen <0) siGreen = 0; if(siGreen>=64) siGreen = 63;  
				if(siBlue  <0) siBlue  = 0; if(siBlue >=64) siBlue  = 63;   
				ScreenTable[siCountA][siCountB] = Palette16[siRed][siGreen][siBlue];
			}
		}

		fp = fopen(filename, "wb");
		fwrite(ScreenTable,  sizeof(UI08)*256*256, 1, fp);
		fclose(fp);
	}
}

void cltGrp::InitMultiplyTable(char* filename)
{
	
	// ���Ͽ��� �о�� ������ �����. 
	FILE* fp= fopen(filename, "rb");

	if(fp)
	{
		fread(MultiplyTable,  sizeof(UI08)*256*256, 1, fp);
		fclose(fp);
	}
	else
	{
		SI32  siOrigRed, siOrigGreen, siOrigBlue;
		SI32  siEffRed,  siEffGreen,  siEffBlue;
		SI32  siRed, siGreen, siBlue;

		for(SI32 siCountB = 0; siCountB < 256; siCountB++ )
		{
			for(SI32 siCountA = 0; siCountA < 256; siCountA++)
			{
				// siCountA : BASE �̹��� , siCountB : Blend �̹��� 
				siOrigRed   = Palette[siCountA * 3    ] ;
				siOrigGreen = Palette[siCountA * 3 +1 ] ;
				siOrigBlue  = Palette[siCountA * 3 +2 ] ;
				siEffRed	= Palette[siCountB * 3    ] ;
				siEffGreen  = Palette[siCountB * 3 +1 ] ;
				siEffBlue   = Palette[siCountB * 3 +2 ] ;
				siRed   = siOrigRed	 * siEffRed	 /63;
				siGreen = siOrigGreen* siEffGreen/63;
				siBlue  = siOrigBlue * siEffBlue /63;
				if(siRed   <0) siRed   = 0;	if(siRed  >=64) siRed   = 63;
				if(siGreen <0) siGreen = 0; if(siGreen>=64) siGreen = 63;  
				if(siBlue  <0) siBlue  = 0; if(siBlue >=64) siBlue  = 63;   
				MultiplyTable[siCountA][siCountB] = Palette16[siRed][siGreen][siBlue];
			}
		}
		fp = fopen(filename, "wb");
		fwrite(MultiplyTable,  sizeof(UI08)*256*256, 1, fp);
		fclose(fp);
	}
}

// �ȷ�Ʈ�� Ư�� ��ġ ���鸸 �����Ѵ�. 
HRESULT cltGrp::SetPaletteEntries(DWORD dwStartingEntry, DWORD dwCount, LPPALETTEENTRY lpEntries)
{
	if(ColorDepth != 8)return FALSE;

	return lpDDPal->SetEntries(NULL, dwStartingEntry, dwCount,  lpEntries);
}


BOOL cltGrp::SetPalette(unsigned char* pal)
{
	int i;

    for(i=0;i<256;i++)
    {
       PalEntries[ i ].peRed   = pal[ i * 3 ];
       PalEntries[ i ].peGreen = pal[ i * 3 + 1 ];
       PalEntries[ i ].peBlue  = pal[ i * 3 + 2 ];
    }

    lpDDPal->SetEntries(NULL, 0, 256, PalEntries);

	return TRUE;
}


UI08 cltGrp::FindNearColor(UI08 r, UI08 g, UI08 b, const UI08 *pal)
{

	SHORT i;
	UI08 min_color	=	0;
	SHORT min_diff	=	10000;
	SHORT diff;

	for(i = 0;i < 256;i++)
	{
		diff	=	TABS(pal[i*3]-r)+TABS(pal[i*3+1]-g)+TABS(pal[i*3+2]-b);

		if(diff < min_diff)
		{
			min_diff	=	diff;
			min_color	=	(UI08)i;
		}
	}

	return min_color;
}

void cltGrp::WaitForVerticalBlank()
{
	if(lpDD7)
       lpDD7->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL);// vertical retrace���� ��� 
}
