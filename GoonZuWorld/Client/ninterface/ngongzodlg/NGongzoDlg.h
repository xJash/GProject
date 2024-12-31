#pragma once 

#include "../../InterfaceMgr/DialogController.h"
#include "../common/CommonHeader.h"
#include "../Server/Minister/Minister-Hozo.h"
#include "../Lib/Directives.h"

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;
class COutLine;


enum
{
	GOONGZO_SETMODE_NONE,
	GOONGZO_SETMODE_WEAPON,
	GOONGZO_SETMODE_ARMOR
};

class CNGongzoDlg : public CDialogController
{
public:

	CNGongzoDlg();
	~CNGongzoDlg();

	void Create();
	void Action();

	static void CALLBACK StaticCallBackDialogNGongzoDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNGongzoDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetGongzo(CMinisterBase *pMini,SI32 pricetime,SI16 leftovervalue,GongzoMember *gongzomember,SI16 leftovervalue_armor);

	void SetSpinButton();
	void SendGongzoMessage();
	void SetSpinDis(BOOL bView);
	void SetSpinValue(SI32 skillunique,SI32 editunique);
	void SetSpinData(SI32 skillunique,SI32 editunique,SI32 staticunique);

	void UpWeaponExp(SI32 Index);
	void DownWeaponExp(SI32 Index);

	void SetCraftFund(SI32 inc);

	void EnableButton(CButton* pButton, BOOL Flag);	// ��ư Ȱ��ȭ ��Ȱ��ȭ
	void SetButtonTextColor(CButton* pButton, BOOL Flag);

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	
private:

	TCHAR m_szGongzoName[MAX_PLAYER_NAME];
	TCHAR m_szGongzoProfile[256];
	TCHAR m_szGongzoID[MAX_PLAYER_NAME];

	SI32			m_siPriceTime; // ���� �ð�
	SI16			m_siLeftOverValue; // ���� ���� ��ġ
	SI16			m_siSetSkill ; // ������ ��ų�� ����ũ
	SI32			m_siIDCEditNum ; // ������ ��ų�� ����Ʈ �ڽ�
	SI32			m_siSpinNum; // ������ ��ų�� ���ɹ�ư
	SI16			m_siLeftOverValue_Armor; // ���� ���� ��ġ

	GongzoMember	m_stGongzoMember;

	BOOL m_bSet;
	BOOL m_bSetSpin ; // �̹� ���� ��ư�� �ѹ� ������ �¾��ߴ�.
	BOOL m_bMonthOver; // �������� �Ѵ��� ������.
    BOOL 	m_bGongzoCheck;
	BOOL m_bSoundCheck;
	BOOL m_bGongzoReturnValue; 

	CStatic*	m_pStatic[33];
	CButton*	m_pButton[19];
	CEdit*		m_pEdit[8];
	COutLine*	m_pOutLine[4];

	CButton*	m_pButton_Weapon;
	CButton*	m_pButton_Armor;

	SI32		m_siSetMode;
};