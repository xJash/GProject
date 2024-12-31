//---------------------------------
// 2004/2/5 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :		CNVillageDetailInfo

	�ۼ��� :		05/03/02
	�ۼ��� :		���뷡

	��  �� :		CNVillageDetailInfo Ŭ������  ��ü ȭ�� ��� ����� NInterface��
					���� ���� ȭ�� �ȿ��� ���� �� ���� ���̾�α׸� �����Ѵ�.

	������� :		����
	
	�����۾� :		cpp �۾� �Ϸ� ���

   ========================================================================*/

//#if (defined(__LEON_START_ALL__) || defined(__LEON_NVILLAGEDETAILINFO__)) && defined(_DEBUG)

#pragma once

#include <Directives.h>
#include "../../InterfaceMgr/DialogController.h"
#include "../../../Common/Item/ItemCommon/ItemUnit.h"

#define NVILLAGEDETAILINFOTYPE_VILLAGELIST		1		// ������� 
#define NVILLAGEDETAILINFOTYPE_SCORE			2		// ��������
#define NVILLAGEDETAILINFOTYPE_VISITORNUM		3		// �����湮�ڼ� ��ȸ
#define NVILLAGEDETAILINFOTYPE_VILLAGEMONEY		4		// ������ ���� �ڱ�. 
#define NVILLAGEDETAILINFOTYPE_VILLAGEPROFIT	5		// ������ ���� �ڱ�(���ͱ�) 
#define NVILLAGEDETAILINFOTYPE_VILLAGESTOCK		6		// ���� �� �ֽļ�.
#define NVILLAGEDETAILINFOTYPE_GENERALMEETING	7		// ������ȸ���ึ�� 
#define NVILLAGEDETAILINFOTYPE_WAR				8		// ���� ��� ǥ��. 
#define NVILLAGEDETAILINFOTYPE_WARPERRESIDENT	9		// ���� ��� ǥ��. (�ֹ� 100���)
#define NVILLAGEDETAILINFOTYPE_PEOPLE			10		// �ֹμ�  ǥ��. 
#define NVILLAGEDETAILINFOTYPE_USER				11		// ���� ����ڼ� 
#define NVILLAGEDETAILINFOTYPE_PREVYEARDBID		12		// ���⵵ ����. 
#define NVILLAGEDETAILINFOTYPE_HUNT				13		// ������
#define NVILLAGEDETAILINFOTYPE_DECLAREWAR		14		// ������ ���� ����. 
#define NVILLAGEDETAILINFOTYPE_HORSEMARKET		15		// �纹�� 
#define NVILLAGEDETAILINFOTYPE_STOCK			16		// ���� 
#define NVILLAGEDETAILINFOTYPE_REALESTATEMARKET	17		// �Ű�
#define NVILLAGEDETAILINFOTYPE_SUMMONMARKET		18		// �忹��
#define NVILLAGEDETAILINFOTYPE_SUMMONHEROMARKET	19		// �񺯻�
#define NVILLAGEDETAILINFOTYPE_FARM				20		// ����
#define NVILLAGEDETAILINFOTYPE_FEAST			21		// ���ڽ�
#define NVILLAGEDETAILINFOTYPE_MINE				22		// ����
#define NVILLAGEDETAILINFOTYPE_GUILD			23		// ���(���)
#define NVILLAGEDETAILINFOTYPE_CITYHALLSTATE	24		// ��û��������( �����, �Ļ��, ������, �ʱ�ȭ�� ��..)
#define NVILLAGEDETAILINFOTYPE_VILLAGEWARRECORD	25		// �������� ��ȸ
#define NVILLAGEDETAILINFOTYPE_NEWMARKET		26		// [����] ���ո���.

#define MAX_VILLAGEDETIALINFOTYPE	30
#define LEAST_COMMON_MULTILPLE	30


class CStatic;
class CComboBox;
class CList;
class CCheckBox;
class CButton;
class CEdit;

class cltGameMsgResponse_VillageDetailInfo;

class cltNVillageDetailData{
public:
	SI32	siType;
	TCHAR	szTypeText[64];
	TCHAR	szExplainText[256];
};

class CNVillageDetailInfo : public CDialogController
{
public:
	enum
	{
		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_WIDTH = 0,	// DDF ���Ͽ��� �о ó��
		DLG_HEIGHT = 0,	// DDF ���Ͽ��� �о ó��
		DLG_BIG_POS_X = 1024 - DLG_WIDTH + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 100,
		DLG_SMALL_POS_X = 800 - DLG_WIDTH + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 100,
	};


	cltNVillageDetailData m_clvillagedata[MAX_VILLAGEDETIALINFOTYPE];

	RECT DlgRect;
	bool bDlgRectInitSwitch;
	bool bCheckSortVillage;			// ���� ���� üũ ��ư�� ���� 01/18 �߰�

	SI32 siCurrentType;
	SI32 siOldCurrentType;
	SI32 siOldViliage;

	bool bMasterView;				// [�߰� : Ȳ���� 2008. 2. 22 => ������ ����̸� ������ȸ ���� ������ ���̰� ����Ʈ ����.]

	CNVillageDetailInfo();
	~CNVillageDetailInfo();
	

	void Create(CControllerMgr * pParent);

	static void CALLBACK StaticDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK DlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	// �޺��� ������ Ÿ���� �ִ´�. 
	void SetDataTypeInCombo();

	// Ÿ���� �ٰŷ� ���� �����͸� ���Ѵ�. 
	cltNVillageDetailData* GetNVillageDetailData(SI32 type);

	// �ؽ�Ʈ�� �ٰŷ� ���� �� ���� �ڵ带 ���Ѵ�. 
	SI32 GetVillageDetailType(TCHAR* ptext);

	// ������ ���� ���� ������ ǥ���Ѵ�. 
	void ShowInfo(cltGameMsgResponse_VillageDetailInfo* pclinfo);
	
	// �ǹ� �� ������ ǥ���Ѵ�. 
	void ShowStrInfo(TCHAR*  ptext);


	// ������������ �����Ѵ�. 
	SI32 Sort(SI32 sisortdata[], SI32* pvillageunique);
	SI32 Sort(SI64 sisortdata[], SI32* pvillageunique);
	SI32 Sort(TCHAR* pSortname[], SI32* pvillageunique);

	//bool IsShow();
	void Show();
	void	 Hide();

	void Action();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void GeneralMeetingSuggestInfo(void);

    void FindVillage(TCHAR * szVillagename);
	// �˻� ����� ����
	void ItemFind(TCHAR* pStrname);	// ���õ� ������ ������ ǥ��
	void Find(TCHAR* pItemname);
	void AddListItem(TCHAR* findname);
	void Update();

	bool		m_bShow;
	SI32		m_timerCount;

	CStatic		*m_pNVillageDetailStatic;
	CComboBox	*m_pNVillageDetailComboBox;
	CList		*m_pNVillageDetailList;
	CButton		*m_pWarpToNVillageButton;
	CEdit		*m_pNVillageDetailEdit;
	CButton		*m_pCloseButton;
	CCheckBox	*m_pSortVillageCheckBox;
	 
    SI32		m_siListdata[MAX_VILLAGE_NUMBER];

	//[�߰� : Ȳ���� 2008. 2. 22 => ������ ������ȸ ���� ��ư �߰�.]
	CButton*	pSetGeneralmeetingButton;
	// �˻����
	CList			*m_pListBox_AutoMake;
	CEdit			*m_pEdit_Name;
	CButton			*m_pButton_Accept;
	CStatic			*m_pStatic_Back;//��׶���

private:
	NTCHARString64		m_LastInput;
};

//#endif //#if (defined(__LEON_START_ALL__) || defined(__LEON_NVILLAGEDETAILINFO__)) && defined(_DEBUG)