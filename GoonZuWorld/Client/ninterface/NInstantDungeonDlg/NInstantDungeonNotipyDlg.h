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


class InstanstDungeonNotipyDlg : public CDialogController
{
public:
	InstanstDungeonNotipyDlg();
	~InstanstDungeonNotipyDlg();

	void					Create();
	
	//[�߰� : Ȳ���� 2008. 1. 11 => �δ� ���� ����â ����.]
	void					SetInstantDungeon(SI32 _siGuildMarkIndex, TCHAR* _szGuildName, TCHAR* _szGuildMasterName);

	//[�߰� : Ȳ���� 2008. 1. 17 => �δ� �ְ� ��庯�� �˸�.]
	void					SetInstantDungeonTopChange(SI32 _siGuildMarkIndex, TCHAR* _szGuildName, SI32 _Score, TCHAR* _szGuildMasterName);
	
	static void CALLBACK	StatiCNInstanstDungeonNotipyDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NInstanstDungeonNotipyDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


	void                    Action();
	void					DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );

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
	SI32			m_siGuildMarkIndex;	// ��� ��ũ �ε���.	
};


