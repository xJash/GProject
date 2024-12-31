#pragma once

//===============================================================
// ������ : �ڱ���
// ��¥ :  2009.1 .25
// ���� :  ����Ʈ �� Ŭ����
//===============================================================

#include <commctrl.h>

////	����Ʈ �� ��Ʈ�� Ŭ����
class ListView
{

	////	������ �Ҹ���
public:
	ListView(void);
	~ListView(void);

	////	Ŭ���� ���� ����
public:
	//	�̹��� ����Ʈ
	HIMAGELIST m_HImgList;

	//	����Ʈ �� ������ �ڵ�
	HWND	m_Handle;	
	//	���� �� �÷� ����
	int		m_ColCount;
	//	���õ� ������ ������
	LPVOID	m_Select;
	//	���� ( 0 : �ܺ��ڵ� ���, 1 : ���� ��ü ����)
	BOOL	m_Type;
	//	���õ� ���ڵ� �ε���
	int		m_SelctedRecordIndex;

	////	Ŭ���� ���� �Լ�
public:
	//	�����Լ�
	BOOL	Create(BOOL p_Type, HWND p_Hwnd, char *p_Tit = NULL, int Xx = 0, int Yy = 0, int Ww = 200, int Hh = 200, BOOL p_Check = FALSE);
	//	�����Լ�
	BOOL	Release();
	
	//	�ʱ� ����� �÷� ����
	BOOL	Set_Col(char *p_Tit, int p_size = 50);

	//	����Ʈ ������ �߰�
	BOOL	Set_Data(int p_Row_N, int p_Col_N, TCHAR *p_Text, VOID *p_Data = NULL);
	BOOL	Set_Data(int p_Row_N, int p_Col_N, int p_Value, VOID *p_Data = NULL);
	//	�̹��� �߰�
	BOOL	Set_ImgIcon(HICON p_HIcon);
	BOOL	Set_ImgBmp(HBITMAP p_HBitmap);
	//	�̹��� ����Ʈ ���
	BOOL	RegistImgList();

	//	����Ʈ�� Ư�� �ؽ�Ʈ �� ��������
	BOOL	Get_Data(TCHAR* data,int size, int p_Row_N, int p_Col_N);
	
	//	Ư�� ���� ���� ������ �����ֱ�
	LPVOID	GetData(int p_Rows,int p_Cols );

	//	����Ʈ �� �뺸 ó��
	int		Notify(WPARAM wParam, LPARAM lParam);

	//	����Ʈ �� ������ ��
	int		GetRecordCount();

	//	��� ���� ����
	BOOL	Clear();

	//	���õ� ���ڵ� ����
	BOOL	Delete_Data(int index);

	//	���õ� ���ڵ� �ε��� ���
	int		GetSelectedRCIdx();

	//	���ڵ� üũ ����
	BOOL	IsCheckedRecord(int index);

	//	���ڵ� üũ �ϱ�
	BOOL	SetCheckRecord(int index);

	//	���ڵ� üũ Ǯ��
	BOOL	SetUncheckRecord(int index);

	//	���ڵ� ã�� (���� ���ڿ� ������)
	int		FindRecord(TCHAR* p_Data,int p_Data_Size,int p_Col);
};
