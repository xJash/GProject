/* ==========================================================================
	Ŭ���� :		CNBattleRoyalResultDlg

	�ۼ��� :		09/10/22
	�ۼ��� :		�ڱ���

	��  �� :		CNBattleRoyalResultDlg Ŭ������   ��Ʋ�ξ� ����� ����� �˷��ش�.

	��  �� :		
	������� :		����

	�����۾� :		

   ========================================================================*/
#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"


class CStatic;
class CButton;
class CImageStatic;

#define POPUP_TIME		200

class CNBattleRoyalResultDlg : public CDialogController
{
public:
	CNBattleRoyalResultDlg();
	~CNBattleRoyalResultDlg();

	void					Create();

	static void CALLBACK	StatiCNBattleRoyalResultDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NBattleRoyalResultDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	
	void                    Action();

	void					SetDescription(TCHAR* szDescription);
	void					SetImage(TCHAR* ImagePath, SI32 siIndex = 0);
	void					SetResize(SI32 siWidth, SI32 siHeight);
	void					SetPosition(SI32 siX, SI32 siY);
	void					SetResult(bool bResult);
private:

	CStatic                *m_pResultStatic;
	CImageStatic           *m_pResultImageStatic;   
	
	bool			m_bResult;
	TCHAR			m_strPrintMsg[ 2048 ];
	TCHAR			m_strTitleMsg[ 64 ];
	TCHAR			m_strPlayerName[ MAX_PLAYER_NAME ];
	SI32			m_siHintDlg;
	SI16			m_siBitmapAnimationIndex;
	SI32			m_siImageType;	// ������ �̹��� Ÿ��(�̹����� 3��)
	SI32			m_siImageIndex; // ������ �̹������� ����
	SI16            Popupflag;
};

//extern	CNRareItemDlg		g_RareItemMsg;

