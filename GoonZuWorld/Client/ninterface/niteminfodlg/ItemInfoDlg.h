#ifndef _NITEMINFO_H_
#define _NITEMINFO_H_

#include "../Client/InterfaceMgr/DialogController.h"
#include "../common/Item/ItemCommon/cltItem.h"

#define LEAST_COMMON_MULTILPLE	30
class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

class cltItem;


class CNItemInfoDlg : public CDialogController
{
public:

	CNItemInfoDlg();
	~CNItemInfoDlg();

	void Create(CControllerMgr * pParent);

	static void CALLBACK StaticCallBackDialogNItemInfoDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNItemInfoDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show();
	void Hide();

	void Action();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );

	void SetItemTypeInComboBox(BOOL bshowall);
	BOOL ShowItemListInComboBox(CComboBox* pComboBox, SI32 typeindex, bool btradeinterface);

	void ShowItemInfo(TCHAR * pStrname);
	void SetItemInfo(TCHAR* pStrname);	// ���õ� ������ ������ ǥ��

	SI32 GetItemInfoPosX();
	SI32 GetItemInfoPosY();

	TCHAR* GetFromTypeFromName(SI16 ItemType);//Ÿ������ �̸� ã��
	void SetMaterialRefresh()	{		m_bRequestMaterialRefresh = true;	}
	
	// �˻� ����� ����
	void ItemFind(TCHAR* pStrname);	// ���õ� ������ ������ ǥ��
	void Find(TCHAR* pItemname);
	void AddListItem(TCHAR* findname);
	void Update();
private:

	SI32			m_siTypeIndex;	// ǰ�� �ε���
	SI32			m_siItemIndex;	// ǰ�� �ε���
	SI32			m_siSelectMonsterIndex;

	SI32			m_siImageType;	// ������ �̹��� Ÿ��(�̹����� 3��)
	SI32			m_siImageIndex; // ������ �̹������� ����

	SI32			m_arrTypeIndex[MAX_ITEMTYPE_NUMBER];
	
	SI32			m_siCurrentSelectedItemUnique;
	SI32			m_timerCount;

	CComboBox*		m_pComboBox[2];
	CStatic*		m_pStatic[7]; // 0: ǰ��, 1: ǰ��, 2: ����, 3: ���, 4:����, 5:����, 6:���� ���� ��ǰ

	CEdit*			m_pEdit[3];
	CImageStatic*	m_pImageStatic;
	
	CList			*m_pList[3];

	BOOL			m_bRequestMaterialRefresh;

	CButton*		m_pQuestButton;
	CButton*		m_pQuestButtonProperty;

	// �˻����
	CList			*m_pListBox_AutoMake;
	CEdit			*m_pEdit_Name;
	CButton			*m_pButton_Accept;
	CStatic			*m_pStatic_Back;//��׶���
private:
	NTCHARString64		m_LastInput;
};

#endif