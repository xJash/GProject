//===============================================================
// ������ : �ڱ���
// ��¥ :  2009.1 .25
// ���� :  ����Ʈ �� Ŭ����
//===============================================================
#include <windows.h>
#include <tchar.h>
#include "ListView.h"


ListView::ListView(void)
{
	m_Handle = NULL;	
	//	���� �� �÷� ����
	m_ColCount = 0;
	//	���õ� ������ ������
	m_Select = NULL;
	//	���� ( 0 : �ܺ��ڵ� ���, 1 : ���� ��ü ����)
	m_Type = false;

	//	�̹��� Ȯ�� ��
	int imgCount = 100;

	//	�̹��� ����Ʈ ����
	m_HImgList = ImageList_Create(GetSystemMetrics(SM_CXICON), 
									 GetSystemMetrics(SM_CYICON), 
									 ILC_COLORDDB, 1, imgCount);

	/*m_HImgList = ImageList_Create(32, 
									 32, 
									 ILC_COLORDDB, 1, imgCount);*/

	// �̹��� ����Ʈ ����
	// m_HImgList = ImageList_LoadImage(m_hInstance, lpbmp, cx, cGrow,RGB(255, 255, 255),IMAGE_BITMAP, 
	//	LR_DEFAULTCOLOR  | LR_LOADMAP3DCOLORS | LR_CREATEDIBSECTION
	//	);
	//	���õ� ���ڵ� �ε���
	m_SelctedRecordIndex = -1;

}
ListView::~ListView(void)
{
	Release();
}

//	�����Լ�
BOOL	ListView::Create(BOOL p_Type, HWND p_Hwnd, char *p_Tit, int Xx, int Yy, int Ww, int Hh, BOOL p_Check)
{
	//	����
	m_Type = p_Type;
	//	������ ���� ���� ó��
	if(m_Type == TRUE)
	{
		//	������ ����
		if( p_Hwnd != NULL)
		{
			//	�ڽ� ����Ʈ �� �����
			m_Handle = CreateWindowA( WC_LISTVIEWA, p_Tit,
			LVS_SHOWSELALWAYS | WS_HSCROLL | WS_VSCROLL | WS_VISIBLE | WS_BORDER | WS_THICKFRAME | LVS_REPORT | WS_CHILD,
			Xx, Yy, Ww, Hh, p_Hwnd, NULL, NULL, NULL);
		}
		else
		{
			//	���� ����Ʈ �� �����
			m_Handle = CreateWindowA( WC_LISTVIEWA, p_Tit,
			LVS_SHOWSELALWAYS | WS_HSCROLL | WS_VSCROLL | WS_VISIBLE | WS_BORDER | WS_THICKFRAME | LVS_REPORT,
			Xx, Yy, Ww, Hh, p_Hwnd, NULL, NULL, NULL);
		}
		//	������ �ڵ� Ȯ��
		if(m_Handle == NULL)
		{
			return false;
		}
		
	}
	else
	{
		//	��ȭ���� ���ҽ��� ����Ʈ �� �ڵ� ���
		m_Handle = p_Hwnd;
		if(m_Handle == NULL)
			return false;
	}
	//	üũ�ڽ� Ȯ�� ��Ÿ��
	if(p_Check)
	{
		//	üũ�ڽ� �߰�
		ListView_SetExtendedListViewStyle(m_Handle,
			LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_CHECKBOXES);
	}
	else
	{
		//	üũ�ڽ� ����
		ListView_SetExtendedListViewStyle(m_Handle,
			LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	}
	return true;
}
//	�����Լ�
BOOL	ListView::Release()
{
	//	������ ���� �˻�
	if(m_Type == TRUE)
	{
		DestroyWindow(m_Handle);
		m_Handle = NULL;
	}
	else
	{
		//	��ȭ���� ���ҽ��� ����Ʈ �� �ڵ�
		m_Handle = NULL;
	}
	m_ColCount = 0;
	m_Select = NULL;

	//�̹��� ����Ʈ ����
	ImageList_Destroy(m_HImgList);

	return true;
}
	
//	�ʱ� ����� �÷� ����
BOOL	ListView::Set_Col(char *p_Tit, int p_size)
{
	if(m_Handle == NULL)
	{
		return false;
	}

	//	�÷� ���� ����ü ����
	LVCOLUMNA	t_Col;
	t_Col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	t_Col.fmt = LVCFMT_LEFT;	//	���� ����
	t_Col.iSubItem = m_ColCount;		//	���� ��ȣ
	t_Col.cx = p_size;			//	�÷� ũ��
	t_Col.pszText = p_Tit;		//	���ڿ�

	//	�޽����� ���� �߰�
	SendMessageA(m_Handle, LVM_INSERTCOLUMNA, m_ColCount, (LPARAM)&t_Col);
	//	�÷� ���� ����
	m_ColCount++;
	return true;
}

//	����Ʈ ������ �߰�
BOOL	ListView::Set_Data(int p_Row_N, int p_Col_N, TCHAR *p_Text, VOID *p_Data)
{
	//	����Ʈ �� ���� Ȯ��
	if(m_Handle == NULL)
	{
		return false;
	}

	//	����Ʈ ���� ���� ���� ��� �ش� ����Ʈ ����
	if(p_Row_N < (int)SendMessage(m_Handle, LVM_GETITEMCOUNT, 0, 0))
	{
		
			LVITEM	t_Item;
			memset(&t_Item,0,sizeof(LVITEM));
			//	�÷� ��ȣ
			t_Item.iSubItem = p_Col_N;
			//	���ڿ�
			t_Item.pszText = p_Text;
			//	�̸�����
			SendMessage(m_Handle, LVM_SETITEMTEXT, p_Row_N, (LPARAM)&t_Item);

	}
	//	�ű� �߰�
	else
	{
		//	�߰�
		LVITEM	t_Item;
		memset(&t_Item,0,sizeof(LVITEM));
		//	����ü ���ο� ����� ���� ����
		t_Item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		//	�÷� ��ȣ
		t_Item.iSubItem = p_Col_N;
		//	���� ��ȣ
		t_Item.iItem = p_Row_N;
		//	���ڿ�
		t_Item.pszText = p_Text;
		//	������ ������ ����
		t_Item.lParam = (LPARAM)p_Data;
		//	�̹��� index
		t_Item.iImage = p_Row_N;
		//	�߰�
		SendMessage(m_Handle, LVM_INSERTITEM, 0, (LPARAM)&t_Item);
	}

	return true;
}

//	����Ʈ ������ �߰�
BOOL	ListView::Set_Data(int p_Row_N, int p_Col_N, int p_Value, VOID *p_Data)
{
	//	����Ʈ �� ���� Ȯ��
	if(m_Handle == NULL)
	{
		return false;
	}

	TCHAR t_Text[11];
	_itoa(p_Value , (char*)t_Text,11);

	//	����Ʈ ���� ���� ���� ��� �ش� ����Ʈ ����
	if(p_Row_N < (int)SendMessageA(m_Handle, LVM_GETITEMCOUNT, 0, 0))
	{
		
			LVITEMA	t_Item;
			memset(&t_Item,0,sizeof(LVITEMA));
			//	�÷� ��ȣ
			t_Item.iSubItem = p_Col_N;
			//	���ڿ�
			t_Item.pszText = (LPSTR)t_Text;
			//	�̸�����
			SendMessageA(m_Handle, LVM_SETITEMTEXTA, p_Row_N, (LPARAM)&t_Item);

	}
	//	�ű� �߰�
	else
	{
		//	�߰�
		LVITEMA	t_Item;
		memset(&t_Item,0,sizeof(LVITEMA));
		//	����ü ���ο� ����� ���� ����
		t_Item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		//	�÷� ��ȣ
		t_Item.iSubItem = p_Col_N;
		//	���� ��ȣ
		t_Item.iItem = p_Row_N;
		//	���ڿ�
		t_Item.pszText = (LPSTR)t_Text;
		//	������ ������ ����
		t_Item.lParam = (LPARAM)p_Data;
		//	�̹��� index
		t_Item.iImage = p_Row_N;
		//	�߰�
		SendMessageA(m_Handle, LVM_INSERTITEMA, 0, (LPARAM)&t_Item);
	}

	return true;
}


//	�̹��� �߰�
BOOL	ListView::Set_ImgIcon(HICON p_HIcon)
{
	if( p_HIcon == NULL)
		return false;

	// �̹��� ����Ʈ�� ������ �߰�
	ImageList_AddIcon(m_HImgList, p_HIcon);  
	return true;
}

BOOL	ListView::Set_ImgBmp(HBITMAP p_HBitmap)
{
	if( p_HBitmap == NULL)
		return false;

	// �̹��� ����Ʈ�� ������ �߰�
	ImageList_Add(m_HImgList, p_HBitmap,NULL);  
	return true;
}
//	�̹��� ����Ʈ ���
BOOL	ListView::RegistImgList()
{
	//	�̹��� ����Ʈ ���
	ListView_SetImageList(m_Handle, m_HImgList, LVSIL_SMALL); 
	return true;
}




//	����Ʈ�� Ư�� �ؽ�Ʈ �� ��������
BOOL ListView::Get_Data(TCHAR* data,int size, int p_Row_N, int p_Col_N)
{
	if(	data == NULL || size < 1 || p_Row_N < 0 || p_Col_N < 0)
		return false;
	
	ListView_GetItemText(m_Handle,p_Row_N,p_Col_N,data,size);
	return true;
}


//	����Ʈ �� �뺸 ó��
int		ListView::Notify(WPARAM wParam, LPARAM lParam)
{
	//	�뺸 �޽��� ����ü ������ ����ȯ
	LPNMHDR	t_hdr;
	t_hdr = (LPNMHDR)lParam;
	if( t_hdr->hwndFrom != m_Handle )
	{
		return -1;
	}

	switch (t_hdr->code){
	case LVN_ITEMCHANGED:
		{
			//	�ش� ����Ʈ �� ���� �޽��� ����
			LPNMLISTVIEW	p_LSV = (LPNMLISTVIEW)lParam;
			//	���ο� ����Ʈ ���� Ȯ��
			if(p_LSV->uChanged == LVIF_STATE && p_LSV->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
			{
				//	����Ʈ �߰� ������ ������ ������
				m_Select = (LPVOID)p_LSV->lParam;
				return (p_LSV->iItem);
			}
			break;
		}
	case NM_DBLCLK:
	case NM_CLICK:
		{
			//	Ŭ���� ���� ���ڵ� �ε����� ���
			m_SelctedRecordIndex = (int)SendMessage(m_Handle,LVM_GETSELECTIONMARK,0,0);

			break;
		}
	default:
		{
			break;
		}
	}
	
	return t_hdr->code;
}

//	��� ���� ����
BOOL	ListView::Clear()
{
	if(m_Handle != NULL)
	{
		// ����Ʈ ���� ��� ���� ����
		ListView_DeleteAllItems(m_Handle);
		return true;
	}

	return false;
	
}


//	����Ʈ �� ������ ��
int	ListView::GetRecordCount()
{
	return (int)SendMessage(m_Handle, LVM_GETITEMCOUNT, 0,0);
}

//	���õ� ���ڵ� �ε��� ���
int	 ListView::GetSelectedRCIdx()
{
	return m_SelctedRecordIndex;
}

//	���õ� ���ڵ� ����
BOOL ListView::Delete_Data(int index)
{
	if(index < 0)
	{
		return false;
	}
	
	return  ListView_DeleteItem(m_Handle, index);
}
//	���ڵ� üũ ����
BOOL	ListView::IsCheckedRecord(int index)
{
	if(index < 0)
	{
		return false;
	}
	
	return ListView_GetCheckState(m_Handle, index);
}

//	���ڵ� ã�� (�����ͷ� ã��)
int	ListView::FindRecord(TCHAR* p_Data,int p_Data_Size, int p_Col)
{
	TCHAR t_Data[1024];
	ZeroMemory( t_Data, 1024 *sizeof(TCHAR));

	int rValue = 0;
	for(int i = 0 ; i < GetRecordCount(); i++)
	{
		Get_Data(t_Data,1024,i, p_Col);
		
		if(_tcscmp(p_Data, t_Data) == 0)
		{
			rValue = i;
			break;
		}

	}
	return rValue;
 
}

//	���ڵ��� ���� ������ �����ֱ�
LPVOID	ListView::GetData(int p_Rows,int p_Cols)
{
	//	����ü ����
	LVITEM	t_Item;
	memset(&t_Item,0,sizeof(LVITEMA));
	//	����ü ���ο� ����� ���� ����
	t_Item.mask =  LVIF_PARAM;
	//	�÷� ��ȣ
	t_Item.iSubItem = p_Cols;
	//	���� ��ȣ
	t_Item.iItem = p_Rows;

	//	���ڵ� ������ ���
	ListView_GetItem(m_Handle, &t_Item);

	return (LPVOID)t_Item.lParam;
}
//	���ڵ� üũ �ϱ�
BOOL	ListView::SetCheckRecord(int index)
{
	ListView_SetCheckState(m_Handle,index,TRUE);
	return TRUE;
}
//	���ڵ� üũ Ǯ��
BOOL	ListView::SetUncheckRecord(int index)
{
	ListView_SetCheckState(m_Handle,index,FALSE);
	return TRUE;
}