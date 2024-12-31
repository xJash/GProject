//---------------------------------
// 2003/3/11 ���°�
//---------------------------------

/* ==========================================================================
	Ŭ���� :		NcltNPCRepairManager

	�ۼ��� :		05/03/29
	�ۼ��� :		���¾�

	��  �� :		.
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/
#include <Directives.h>

#include "../../InterfaceMgr/DialogController.h"
#include "..\../../Client\Inventory\ItemInventoryBaseDefinition.h"

#define NPCREPAIR_SETTIMER_VALUE	1000

class CButton;
class CStatic;
class CListView;


class NcltNPCRepairManager : public CDialogController
{
public:

	bool bDlgRectInitSwitch;
	RECT DlgRect;

	NcltNPCRepairManager();
	~NcltNPCRepairManager();

	void Create(SI32 CharUnique);

	static void CALLBACK StaticNDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


	void Action();
	bool IsChangedInvItem();
	void LoadItemData();
	void SettingListView();


	void SetItemRepairPriceExplain( SI32 ItemUnique, GMONEY ItemPrice );
	void SetReairSuccessMent( TCHAR *Text );

private:
	//CItemListView	*m_pItemListView;
	cltItem			*m_pclUserInvItem;
	SI16			m_siInvSelectedIndex;
	SI16			m_siPreInvSelectedIndex;
	//HBITMAP			m_hPortraitBitmap;	
	SI32			m_siCharUnique;	
	GMONEY			m_siItemRepairPrice;
	
	CStatic     	*m_pNNPCRepairStatic1;
	CStatic     	*m_pNNPCRepairStatic2;
	CStatic     	*m_pNNPCRepairStatic3;
	CListView      	*m_pNNPCRepairListView;	
	CButton     	*m_pNNPCRepairButton1;
	CButton     	*m_pNNPCRepairButton2;





};


