/* ==========================================================================
	Ŭ���� :		CNRareItemDlg

	�ۼ��� :		05/03/17
	�ۼ��� :		���¾�

	��  �� :		CNRareItemDlg Ŭ������  ��ü ȭ�� ��� ����� NInterface��
					���� ���� ȭ�� �ȿ��� ��ǰâ ���̾�α׸� �����Ѵ�.

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/
#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"


#define HITBUTTON_RECOMMEND		1
#define HITBUTTON_SUMMON		2
#define HITBUTTON_RAREITEM		3

class CStatic;
class CButton;
class CImageStatic;
class COutLine;

#define POPUP_TIME		200


class CNRareItemDlg : public CDialogController
{
public:
	CNRareItemDlg();
	~CNRareItemDlg();

	void					Create();
	void					Set( cltItem *pclItem, TCHAR *PlayerName,TCHAR *strTitleData, TCHAR *strPrintData,
								 SI32 siHorse = 0 ,SI32 siSummon = 0 ,SI32 siHintButton = 0 );
	
	void					SetBestGacha( cltItem *pclItem, TCHAR *PlayerName,TCHAR *strTitleData, TCHAR *strPrintData );
	void					SetVillageEvent( SI32 siVillageUnique, TCHAR *strTitleData, TCHAR *strPrintDatabool, SI16 _siConstructType, SI32 _siKind ); //[����] _siConstructType ������ Ÿ�Ժ� ó���� ����. => 2008-7-22
	void					SetVillageEventGetItem(TCHAR *strTitleData, TCHAR *strPrintData, SI16 _siConstructType ,SI32 siItemunique,TCHAR *PlayerName );// �������̺�Ʈ�� ������ ������ ���� ��� �˸��� ����

	//void					CreateDlg();

	static void CALLBACK	StatiCNRareItemDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NRareItemDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	
	void                    Action();

	void					SetCharName(TCHAR* szName);
	void					SetDescription(TCHAR* szDescription);
	void					SetImage(TCHAR* ImagePath, SI32 siIndex = 0);
	void					SetMainImage(TCHAR* ImagePath, SI32 siIndex = 0);
	void					SetResize(SI32 siWidth, SI32 siHeight);
	void					SetPosition(SI32 siX, SI32 siY);

private:
	CStatic                *m_pNRareItemStatic;    
	CStatic                *m_pNRareItemStatic1;
	CStatic                *m_pNRareItemStatic2;
	CImageStatic           *m_pNRareItemImageStatic1;   
	CImageStatic           *m_pNRareItemImageStatic2;   
	CButton                *m_pNRareItemButton1;
	CButton                *m_pNRareItemButton2;
	COutLine               *m_pNRareItemOutLine;
	
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

