/* ==========================================================================
	Ŭ���� :		CNMonsterInfoDlg

	�ۼ��� :		05/02/25
	�ۼ��� :		���뷡

	��  �� :		CNMonsterInfoDlg Ŭ������  ��ü ȭ�� ��� ����� NInterface��
					���� ���� ȭ�� �ȿ��� ���� ���� ���̾�α׸� �����Ѵ�.

	��  �� :		Client.h�� ����� CNMonsterInfoDlg			*m_pNMonsterInfoDlg��
					��Ʈ�� �Ѵ�.

	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/

//#if (defined(__LEON_START_ALL__) || defined(__LEON_NMONSTERINFODLG__)) && defined(_DEBUG)
#pragma once

#include "..\..\..\Common\Char\KindInfo\KindInfo.h"

#include "../../InterfaceMgr/DialogController.h"
#include "../../../Common/Item/ItemCommon/ItemUnit.h"

#define LEAST_COMMON_MULTILPLE	30

class CStatic;
class CComboBox;
class CRadioButton;
class CCheckBox;
class CImageStatic;
class CEdit;
class CList;

struct stNMonsterInfoDlgData
{
	TCHAR *pData;
	SI16 siParam;
};

class CNMonsterInfoDlg : public CDialogController
{
public:
	enum
	{
		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_BIG_POS_X = 1024 - 340 + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 150,
		DLG_SMALL_POS_X = 800 - 340 + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 150,
	};

	CNMonsterInfoDlg();
	~CNMonsterInfoDlg();

	void Initialize();
	void Destroy();

	void Create(CControllerMgr * pParent);

	static	void CALLBACK StaticNMonsterInfoDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NMonsterInfoDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	void ShowMonsterInfo_Internal( TCHAR* szSelText );
	void ShowMonsterInfo( TCHAR* szSelText );

	void SetData( void *pData );

	bool AddCombo();

	void SortName(SI32 comboindex[]);
	
	void Show();
	void Hide();

	//�˻������ ����
	void Action();
	void MonsterFind(TCHAR* pStrname);
	void Find(TCHAR* pItemname);
	void AddListItem(TCHAR* findname);
	void Update();
	//void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	//void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );
    
private:
	bool m_bComboBoxInit;

	SI16 m_siSelectedIndex;

	TSpr *m_pBackGroundSpr;
	
	SI32			m_timerCount;

	CStatic			*m_pMonsterStatic;
	CComboBox		*m_pMonsterSelectComboBox;
	CRadioButton	*m_pNameSortRadioButton;
	CRadioButton	*m_pLevelSortRadioButton;
	CButton			*m_pSearchDetailButton;
	CImageStatic	*m_pMonsterPortraitImage;
	COutLine		*m_pOutlineInfo;
	CEdit			*m_pMonsterInfoEdit;
	CStatic			*m_pItemListStatic;
	CList			*m_pItemListList;
	CStatic			*m_pSummonListStatic;
	CList			*m_pSummonListList;
	//CStatic			*m_pToleranceListStatic;
	//CList			*m_pToleranceListList;
	// �˻����
	CList			*m_pListBox_AutoMake;
	CEdit			*m_pEdit_Name;
	CButton			*m_pButton_Accept;
	CImageStatic*	m_pImageStaticback;
	CStatic			*m_pStatic_Back;//��׶���
	
	SI32	m_siSort; // ��Ʈ�� �������� �� ������ üũ ��ư�� ����� ���ڰ� 0 : �̸� 1 : ���
	TCHAR	m_szSortName[MAX_KIND_NUMBER][MAX_KIND_NAME_LENGTH] ;

private:
	NTCHARString64		m_LastInput;

};

//#endif//#if (defined(__LEON_START_ALL__) || defined(__LEON_NMONSTERINFODLG__)) && defined(_DEBUG)
