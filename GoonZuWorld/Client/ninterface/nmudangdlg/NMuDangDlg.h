/* ==========================================================================
	Ŭ���� :		CNMudangDlg

	�ۼ��� :		05/04/08
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/
//#define _LEON_NNMUDANGDLG_

//#if defined(_DEBUG) && defined( _LEON_NNMUDANGDLG_)

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class CImageStatic;
class CStatic;
class CButton;
class CEdit;
class CList;
class CComboBox;
class CRadioButton;
class COutLine;
class CNMudangDlg;

#define NMUDANGDLG_SETTIMER_TIME 300
#define MAX_NMUDANG_PAGE_NUMBER	3

class CNMudangReviveDlg : public CDialogController
{
public:
	CNMudangReviveDlg();
	~CNMudangReviveDlg();

	static	void CALLBACK NMuDangReviveStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NMuDangReviveProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	bool IsShow();

	bool m_bShow;
	CNMudangDlg*		m_pParent;


	CStatic		*m_pStatic_now_summon	;
	CButton		*m_pButton_summon_revive	;
	CEdit		*m_pEdit_summon_revive_explain	;
	CComboBox	*m_pComboBox_now_summon	;
};

class CNMudangScrollDlg : public CDialogController
{
public:
	CNMudangScrollDlg();
	~CNMudangScrollDlg();

	static	void CALLBACK NMudangScrollStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NMudangScrollProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	bool IsShow();

	bool m_bShow;
	CNMudangDlg*		m_pParent;

	CStatic			*m_pStatic_now_summon	;
	CStatic			*m_pStatic_arrow	;
	CStatic			*m_pStatic_scroll	;
	CStatic			*m_pStatic_scroll_percent_1	;
	CStatic			*m_pStatic_scroll_percent_2	;
	CRadioButton	*m_pRadioButton_have_scroll_1	;
	CRadioButton	*m_pRadioButton_have_scroll_2	;
	CButton			*m_pButton_summon_scroll	;
	CEdit			*m_pEdit_summon_scroll_explain	;
	CComboBox		*m_pComboBox_now_summon	;
	COutLine		*m_pOutLine_scroll	;

};

class CNMudangEvolveDlg : public CDialogController
{
public:
	CNMudangEvolveDlg();
	~CNMudangEvolveDlg();

	static	void CALLBACK NMudangEvolveStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NMudangEvolveProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	bool IsShow();

	CNMudangDlg*		m_pParent;
	bool m_bShow;

	CStatic		*m_pStatic_now_summon	;
	CStatic		*m_pStatic_arrow	;
	CStatic		*m_pStatic_new_summon	;
	CButton		*m_pButton_summon_evolve	;
	CEdit		*m_pEdit_summon_evolve_explain	;
	CList		*m_pList_new_summon	;
	CComboBox	*m_pComboBox_now_summon	;

	CRadioButton	*m_pRadioButton_evolution	;
	CRadioButton	*m_pRadioButton_devolution	;
	CRadioButton	*m_pRadioButton_transform	;

};

class CNMudangEquipItemDlg : public CDialogController
{
protected:

	//cltSummon		*pclSummon;
	CNMudangDlg*	m_pParent;
	bool			m_bShow;
	cltSummonInfo *pclSummonInfo;

	SI16 invennum ;
	SI32 matnum ;
	SI16 siArmorStonUnique ;
	SI16 siArmorStonNUM ;
	SI16 siWeaponestonUnique ;
	SI16 siWeaponestonNUM ;

	//��Ʈ���� �� 17���� �ʿ���.
	CStatic			*m_pStatic_now_summon		;	// TEXT : ���� ��ȯ�� 
	CImageStatic	*m_pStaticimage_summonface	;	// ���ո����̹���
	COutLine		*m_pOutline_summonface		;	// ���ո����̹����ƿ�����
	CStatic			*m_pStatic_summonlevel		;	// TEXT : ��ȯ������
	CStatic			*m_pStatic_weaponston		;	// TEXT : �������뼮
	CStatic			*m_pStatic_armorston		;	// TEXT : �����뼮 
	CStatic			*m_pStatic_summonlevelNow		;	// TEXT : ���� ��ȯ������
	CStatic			*m_pStatic_weaponstonNow		;	// TEXT : ���� �������뼮
	CStatic			*m_pStatic_armorstonNow		;	// TEXT : ���������뼮 
	COutLine		*m_pOutline_summonstat		;	// ���ո����̹����ƿ�����

	CStatic			*m_pStatic_weapontitle		;	// TITLE : ���� ���뼮
	CStatic			*m_pStatic_armortitle		;	// TITLE : �� ���뼮
	CListView		*m_pListview_weaponston	;	// ���� ���뼮 �̹���
	CListView		*m_pListview_armorston	;	// �� ���뼮 �̹���
	COutLine		*m_pOutline_weaponston		;	// ���� ���뼮 �̹����ƿ�����	
	COutLine		*m_pOutline_armorston		;	// �� ���뼮 �̹����ƿ�����
	//CStatic			*m_pStatic_maxweaponston	;	// TEXT : �����뼮 
	//CStatic			*m_pStatic_maxarmorston		;	// TEXT : �����뼮 
	COutLine		*m_pOutline_ston			;	// ���뼮 �̹����ƿ�����

	CStatic			*m_pStatic_useston			;	// TEXT : ����� ���뼮 
	CEdit			*m_pEdit_useston			;	// ����� ������ ���뼮 ����
	CButton			*m_pButton_weaponuseston			;	// ���⼮��� ��ư
	CButton			*m_pButton_armoruseston			;	// ���� ��� ��ư

public:
	CNMudangEquipItemDlg();
	~CNMudangEquipItemDlg();

	static	void CALLBACK NMudangEquipItemStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NMudangEquipItemProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	bool IsShow();
	void Showsummonstatus( );	// ���� ������ ��ȯ�� ������ ������Ʈ �Ѵ�.
	bool GetSummonmonsterNow( cltSummon *pclSummon );	// ���� ������ ��ȯ�� ������ ������Ʈ �Ѵ�.
	bool CheckUseston( SI32 ItemType,  SI32 summonlevel,SI32 siStonNum, SI16 siSummonIndex ) ;
	bool IsShowSummon()	;
	void InitTextnImage()	;
	void showitemImage();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
};


class CNMudangDlg : public CDialogController
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

	struct stTabTextInfo
	{
		CControllerObj	*st_pControllerObj;
		COLORREF	st_Color;
		SI16		st_siWeight;

		stTabTextInfo()
		{
			Init();
		}

		void Init()
		{
			memset( this, 0, sizeof( stTabTextInfo ));
		}

		void Set( CControllerObj* in_pControllerObj, COLORREF in_Color, SI16 in_siWeight )
		{
			st_pControllerObj = in_pControllerObj;
			st_Color = in_Color;
			st_siWeight = in_siWeight;
		}

	};

	CNMudangDlg();
	~CNMudangDlg();

	void Create();
	void Show();
	void Hide();
	bool IsShow();
	void Action();

	void ShowTabBy( int i_Index);
	void SetTabTextInfo( stTabTextInfo* in_SelectedText );

	void Set();
	
	static	void CALLBACK NMudangStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );

	void CALLBACK NMudangProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	BOOL GetComboSummonNameIndex( TCHAR *CurrSummonName, SI16 txtSize, SI32 *siSummonIndex);
	
	void UpdateCurrentSummonInfo( BOOL bALive);
	void UpdateScrollSummonInfo();

	// Evolve, Devolution, Transform
	void UpdateEvolveSummonInfo();
	void UpdateDevolutionSummonInfo();
	void UpdateTransformSummonInfo();
	// ��ȯ�� ������ �ش� ���� ������Ʈ
	void UpdateEquipItwmInfo();

	// Evolve, Devolution, Transform
	BOOL SendSummonEvolveMessageToServer(SI32 id);
	BOOL SendSummonDevolutionMessageToServer(SI32 id);
	BOOL SendSummonTransformMessageToServer(SI32 id);

	BOOL SendSummonScrollMessageToServer( SI32 id);
	BOOL SendSummonReviveMessageToServer( SI32 id);
	
	BOOL DisplayMessage(BOOL bSuccess, TCHAR *pStr);

	void UpdateReviveMent();
	void UpdateScrollMent();
	void UpdateEvolveMent();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void SetTextBySummonEquip();

	void SetMudangPresentTxt(TCHAR * Txt);

public:

	RECT				m_DlgRect;
	bool				m_bRect;

	clock_t				m_LastSendSummonTime;
	BOOL				m_bChangedScrollPercent;
	SI32				m_siActiveScrollIndex;
	SI32				m_CurrentStatusPage;

	// Evolve, Devolution, Transform
	SI32			m_siSelectEvolveDlg;

	bool m_bShow;

	CNMudangReviveDlg	*m_pTabReviveDlg;
	CNMudangScrollDlg	*m_pTabScrollDlg;
	CNMudangEvolveDlg	*m_pTabEvolveDlg;
	CNMudangEquipItemDlg	*m_pTabEquipitemDlg;

	CImageStatic		*m_pImageStatic_portrait_mudang	;
	CButton				*m_pButton_revive	;
	CButton				*m_pButton_scroll	;
	CButton				*m_pButton_evolve	;
	CButton				*m_pButton_equipitem	;// ������ ����	
	CButton				*m_pButton_close	;
	CEdit				*m_pEdit_mudang	;
	CEdit				*m_pEdit_message	;
	COutLine			*m_pOutLine_portrait_mudang	;

};

//#endif	
