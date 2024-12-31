#ifndef _MONSTERINFODLG_H_
#define _MONSTERINFODLG_H_

#include <Directives.h>
#include "..\..\..\Resource.h"
#include <windows.h>

#include "..\..\..\Common\Char\KindInfo\KindInfo.h"
#include <Graphic.h>
#include <stdio.h>

class CMonsterInfoDlg
{
public:
	CMonsterInfoDlg();
	~CMonsterInfoDlg();

	void Initialize();
	void Destroy();

	void Create( HINSTANCE hInst, HWND hWnd );

	static	BOOL CALLBACK StaticMonsterInfoDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam );
	BOOL	CALLBACK MonsterInfoDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam );

	bool IsShow();
	void Show();
	void ShowMonsterInfo(char *pStrName);
	void Hide();
	void ShowMonsterInfo(HWND hDlg, char* szSelText);

	bool AddCombo();

	void SortName(SI32 comboindex[]);

private:
	HWND m_hDlg;
	bool m_bShow;

	bool m_bComboBoxInit;

	SI16 m_siSelectedIndex;

	HBITMAP m_hPortraitBitmap;
	HBITMAP m_hSearchDetailBitmap;


	HBRUSH	m_hEditBrush;
	HWND	m_hItemListCtrl;
	HWND	m_hSummonListCtrl;
	HWND	m_hToleranceListCtrl;
	
	SI32	m_siSort; // ��Ʈ�� �������� �� ������ üũ ��ư�� ����� ���ڰ� 0 : �̸� 1 : ���
	char	m_szSortName[MAX_KIND_NUMBER][MAX_KIND_NAME_LENGTH] ;

};

extern CMonsterInfoDlg g_MonsterInfoDlg;

#endif