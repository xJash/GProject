#pragma once
// NDormancyPointDlg.h: interface for the NDormancyPointDlg class.
//
//////////////////////////////////////////////////////////////////////
/* ==========================================================================
Ŭ���� :		CNDormancyPointDlg

�ۼ��� :		09/08/13
�ۼ��� :		�ڱ���

��  �� :		�޸��������Ʈ ���� �� ����Ʈ ����
��  �� :		
������� :		����

�����۾� :		

========================================================================*/
#include "Resource.h"

#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CImageStatic;
class CListBox;
class CStatic;
class CEdit;

class CNDormancyPointDlg  : public CDialogController
{
public:
	CNDormancyPointDlg();
	~CNDormancyPointDlg();

	static VOID CALLBACK	StatiCNDormancyPointProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	VOID CALLBACK			NDormancyPointDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl );
	VOID Create();

	VOID Destroy();
	
	// ȭ�� ��ư ������ 
	VOID Minimi(BOOL bMini);
	SI32 GetMinimizedSlot(){return m_siMinimizedSlot;};
	VOID SetMinimizedSlot(SI16 MinimizedSlot){  m_siMinimizedSlot = MinimizedSlot; };

	// ����Ʈ ������ ��� ��������
	VOID ShowPointItemList();

	// ���� ������ ����
	VOID BuySelectItem();

	//	������ ����
	VOID SelectItem();

	//  �޸� ���� ����
	VOID RefreshDormancyInfo();

	VOID VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );

	//	�޼��� �ڽ� ó��
	VOID RetMsgBox( bool bRetValue, SI16 siMsgIndex, BYTE *pData, SI16 siDataLen );
private:
	InterfaceFactory m_InterfaceFactory;
	
	SI32		m_siSelctedUnique;		// ���õ� ������ ����ũ

	SI32		m_siImageType;			// ������ �̹��� ����
	SI32		m_siImageIndex;			// ������ �̹��� ����

	//	������ �̹���
	CImageStatic	*m_pItemImage;
	//	������ ����Ʈ
	CList		*m_pItemListBox;
	//	���� ��ư
	CButton		*m_pBuyButton;
	//	���� ��ư
	CButton		*m_pCloseButton;
	//	����
	CStatic		*m_pTextStatic;
	//  �޸� ����Ʈ ����
	CEdit		*m_pPointInfoEdit;
	//	�̴Ϲ� ��ư
	CButton		*m_pMinimiButton;

	BOOL		m_bMini	;
	SI32		m_siOldPosX;
	SI32		m_siOldPosY;
	SI32		m_siOldXSize;
	SI32		m_siOldYSize;

	SI32		m_siMinimizedSlot;
	TCHAR		m_szTempBgImgFilePath[MAX_PATH];	// �ӽ� ��� �̹��� ���� ���
	TCHAR		m_szTempTitle[MAX_PATH];	// title �ӽ� ����
};
