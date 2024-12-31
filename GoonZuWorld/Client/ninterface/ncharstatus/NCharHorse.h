//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :		cltNHorseStatus

	�ۼ��� :		05/03/14
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#pragma once

#include <directives.h>

#include "CommonHeader.h"

#include "../../InterfaceMgr/DialogController.h"

#define MAX_CHARSTATUS_PAGE_NUMBER	5

#define WANTIED_ANIMAL_CHANGE_TYPE	2

class cltCharClient;
class cltParametaBox;
class cltSummonScroll;
class cltCharManager;
class cltItem;

class CButton;
class CCheckBox;
class CComboBox;
class CEdit;
class CImageStatic;
class CList;
class CRadioButton;
class CStatic;
class COutLine;

// �� ���� â
class cltNHorseStatus : public CDialogController
{
public:

	CImageStatic	*m_pImagestatic_portrait;
	CStatic			*m_pStatictext_horsename;
	CEdit			*m_pEditbox_horsename;
	CButton			*m_pButton_changename;
	CStatic			*m_pStatictext_horsekind;
	CStatic			*m_pStatictext_horsekindname;
	CStatic			*m_pStatictext_birthday;
	
	//CButton			*m_pButton_changetype;
	
	CStatic			*m_pStatictext_birthdayname;
	CStatic			*m_pStatictext_age;
	CStatic			*m_pStatictext_agevalue;
	CStatic			*m_pStatictext_life;
	CStatic			*m_pStatictext_lifevalue;
	CStatic			*m_pStatictext_sex;
	CStatic			*m_pStatictext_sexkind;
	CStatic			*m_pStatictext_speed;
	CStatic			*m_pStatictext_strength;
	CStatic			*m_pStatictext_dex;
	CStatic			*m_pStatictext_magic;
	CStatic			*m_pStatictext_bonus;
	CEdit			*m_pEditbox_speed;
	CEdit			*m_pEditbox_strength;
	CEdit			*m_pEditbox_dex;
	CEdit			*m_pEditbox_magic;
	CEdit			*m_pEditbox_bonus;
	CButton			*m_pButton_speed;
	CButton			*m_pButton_strength;
	CButton			*m_pButton_dex;
	CButton			*m_pButton_magic;
	CButton			*m_pButton_ridehorse;
	CButton			*m_pButton_explain;
	
	//CButton			*m_pButton_init;

	
	CButton			*m_pButton_addstatus;
	CCheckBox		*m_pCheckbox_autofood;
	CButton			*m_pButton_free;
	CStatic			*m_pStatictext_free;
	CEdit			*m_pEditbox_need;

	COutLine		*m_pOutline_noname1	;
	COutLine		*m_pOutline_noname2	;
	COutLine		*m_pOutline_noname3	;

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	CComboBox		*m_pCombobox_horse;

	CButton			*m_pButton_oilling;
	
	BOOL 		m_bChangedInitHorseStatus;
	SI16 		m_siLastHorseComboList;	//���������� Ÿ�� �ִ� ��µ���

	
	cltNHorseStatus(cltCharManager* pclCM);
	~cltNHorseStatus();

	void Create( CControllerMgr *pParent );
	bool IsShow();
	void Show();
	void Hide();
	void Action();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	
	//KHY - 1001 - ��µ��� 5���� ���� ����.
	void InitHorseStatusInfo();
	
	void UpdateHorseStatusInfo();
	void SendUseHorseBonusMessageToServer(SI08 data);

	cltCharManager* pclCM;
	bool m_bShow;
	bool bBonusButtonEnableSwitch;			// ���ʽ� �÷��ִ� ��ư�� Ȱ��ȭ �Ǿ� �ִ��� Ȯ���ϴ� ����. 
	bool BonusHorseButtonEnableSwitch;
	TCHAR strHorseName[ MAX_HORSE_NAME ];

	SI32 CharUnique;

	static void CALLBACK NHorseStatusStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NHorseStatusProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Close();

	SI32 GetPremiumStatusHorse_AGI( SI32 siSlotUnique );	// �����̾� ������ ���ؼ� ��� ����
	SI32 GetPremiumStatusHorse_STR( SI32 siSlotUnique );	// �����̾� ������ ���ؼ� ��� ����
	SI32 GetPremiumStatusHorse_WIS( SI32 siSlotUnique );	// �����̾� ������ ���ؼ� ��� ����
};

//#endif
