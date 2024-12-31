/* ==========================================================================
	Ŭ���� :		CNBossMarketDlg

	�ۼ��� :		05/03/28
	�ۼ��� :		���뷡

	��  �� :			

	������� :		����
	
	�����۾� :		cpp ����

   ========================================================================*/
//#define _LEON_NBOSSMARKET_
//#define _CNBossMarketDlg_SAMPLE_

//#if defined(_LEON_NBOSSMARKET_) && defined(_DEBUG)

#pragma once

#include <Directives.h>
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

#include "./NBossMarketDetailDlg.h"

class CEdit;
class CButton;
class CImageStatic;

#define MAX_DETAIL_DLG_NUM	5

#define LOOP_OF_BUTTON( offset )		\
{									\
	switch( nEvent )				\
	{								\
	case EVENT_BUTTON_CLICKED:		\
		{							\
			m_DetailDlg[ offset ].Show();	\
		}							\
		break;						\
	}								\
}									\
break;								

class CNBossMarketDlg : public CDialogController
{
public:
	enum
	{
		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_WIDTH = 0,	// DDF ���Ͽ��� �о ó��
		DLG_HEIGHT = 0,	// DDF ���Ͽ��� �о ó��
		DLG_BIG_POS_X = 1024 - DLG_WIDTH + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 200,
		DLG_SMALL_POS_X = 800 - DLG_WIDTH + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 200,
	};

	CNBossMarketDlg();
	~CNBossMarketDlg();

	void Initialize();
	void Destroy();

	void Create( );

	static	void CALLBACK StaticCNBossMarketDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK CNBossMarketDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	bool IsShow();
	void Show();
	void Hide();

	//void Action();

	void SetPortrait(TCHAR* in_pFileFullPath, SI16 in_siFontIndex = 0 );	// ĳ���� �ʻ�ȭ ����
	void SetSpeech( SI32 in_siSpeechNum );		// ĳ���� Text	 ����

private:

	bool m_bShow;

	CNBossMarketDetailDlg	m_DetailDlg[MAX_DETAIL_DLG_NUM];
	
	CImageStatic			*m_pPortraitImage;
	CEdit					*m_pExplainEdit;
	CButton					*m_pDetailButton[MAX_DETAIL_DLG_NUM];
	CButton					*m_pCloseButton;
};

//#endif
