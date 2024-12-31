/* ==========================================================================
	Ŭ���� :		CNBossMarketDetailDlg

	�ۼ��� :		05/03/28
	�ۼ��� :		���뷡

	��  �� :		

	������� :		����
	
	�����۾� :		cpp ����

   ========================================================================*/
//#if defined(_LEON_NBOSSMARKET_) && defined(_DEBUG)

#pragma once

#include <Directives.h>

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/interface/Edit.h"
#include "../../InterfaceMgr/Interface/ImageStatic.h"

class CEdit;
class CButton;
class CImageStatic;

#define MAX_FILE_FULLPATH	256

class CNBossMarketDetailDlg : public CDialogController
{
public:
	enum
	{
		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_WIDTH = 0,	// DDF ���Ͽ��� �о ó��
		DLG_HEIGHT = 0,	// DDF ���Ͽ��� �о ó��
		DLG_BIG_POS_X = 1024 - DLG_WIDTH + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 80,
		DLG_SMALL_POS_X = 800 - DLG_WIDTH + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 80,
		PREV_INDEX = 0,
		NEXT_INDEX = 1,
		
		MAX_SCENE_NUM = 10,
	};

	CNBossMarketDetailDlg();
	~CNBossMarketDetailDlg();

	void Create();

	static	void CALLBACK StaticNBossMarketDetailDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NBossMarketDetailDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	bool IsShow();
	void Show();
	void Hide();

	// WM_TIMER �� ���
	//void Action();
	bool CheckValidation();						// ���� ������ ���Ἲ üũ
	void UpdateControls( SI16 in_psiIndex );	// �� ��Ʈ�� ������Ʈ

	void SetTextInfo( SI16 *in_pTextNum, SI16 in_siMaxIndex );							// ���� Text ��ȣ ���� �迭 ����
	void SetImageInfo( TCHAR* in_pImageFullPath, SI16 in_siMaxIndex, SI16 *in_pImageFont = NULL);  // ���� Image ��ȣ ���� �迭 ����
	void SetImageInfoWithFiles( TCHAR** in_pImageFullPath, SI16 in_siMaxIndex );  // ���� Image ��ȣ ���� �迭 ����
	void SetMaxScene( SI16 in_siMaxScene );							// �ִ� ��� �� ����
	void SetCurControl(  SI16 in_siCurIndex );						// ���� ��� ���� ( Image + Edit )

	void SetPortrait( TCHAR* in_pImageFullPath, SI16 in_siIndex = 0);	// �ʻ�ȭ ����

private:	
	bool					m_bMustDelete;		// m_psiImageIndex�� new�� �Ҵ� �ߴ��� ����
	bool					m_bShow;
	bool					m_bFileNameMode;	// true : �׸� ������ ������ , false : �� ���Ͽ� FontIndex�� �޶���
	SI16					m_siCurSceneIndex;	// ���� ��� ��ȣ
	SI16					m_siMaxScene;		// �̹����� Text�� ������ ����, �ѽ��� Scene�̶� ����!
	SI16*					m_psiTextIndex;		// Scene�� ���� �ؽ�Ʈ ��ȣ �ε���
	SI16*					m_psiImageIndex;	// Scene�� ���� �ؽ�Ʈ ��ȣ �ε���
	TCHAR**					m_ppImageFileName;	// �׸� ������ �������϶� 

	CImageStatic			*m_pPortraitImage;
	CImageStatic			*m_pDetailImage;
	CEdit					*m_pExplainEdit;
	CButton					*m_pPrevButton;
	CButton					*m_pNextButton;
	CButton					*m_pCloseButton;
   
};

//#endif	//#if defined(_LEON_NBOSSMARKET_) && defined(_DEBUG)

