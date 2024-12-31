/* ==========================================================================
	Ŭ���� :		CNDailyQuestSituationDlg

	�ۼ��� :		05/05/10
	�ۼ��� :		���뷡
	
	������� :		��� ����

	�����۾� :		

   ========================================================================*/

#if defined(_NDAILYQUESTSELECTDLG) && defined(_STARTING_NOT_USING)

#pragma once

#include <Directives.h>
#include "..\..\..\Resource.h"
#include <windows.h>

class CNDailyQuest2SituationDlg
{
public:
	HWND m_hDlg;

	CNDailyQuest2SituationDlg();
	~CNDailyQuest2SituationDlg();

	void Initialize();

	void Create( HINSTANCE hInst, HWND hWnd );

	static	BOOL CALLBACK StatiCNDailyQuest2SituationDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam );
	BOOL	CALLBACK DailyQuest2SituationDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam );

	bool IsShow();
	void Show();
	void Hide();
	
	void LoadSituation();

private:
	bool m_bShow;

	bool m_bLoadSituationComplete;
};

#endif