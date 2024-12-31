#ifndef _NMAGIC_INFO_H_
#define _NMAGIC_INFO_H_

#include "../../InterfaceMgr/DialogController.h"

#include "..\..\..\Common\Char\KindInfo\KindInfo.h"
#include <Graphic.h>
#include <Graphic_Capsule.h>

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

class CNMagicInfoDlg : public CDialogController
{
public:

	CNMagicInfoDlg();
	~CNMagicInfoDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNMagicInfoDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNMagicInfoDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show();
	void Hide();

	void Action();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	bool IsChanged();
	BOOL SetMagic();		// ���⺰ ���� �̸�
	void SetExplain();		// ���� ����
	SI16 GetMagicKind();
	SI16 GetMagicKind(SI32 index);
	BOOL SetNewMagic(SI32 index);
	
	void ShowMagicList(SI32 SelectButtonIdex);
	void AddMagicList( TCHAR *MagicName, SI32 index );

	void DrawMagicIcon( LPDIRECTDRAWSURFACE7 lpsurface,SI32 x , SI32 y );
	void EnableButton(CButton* pButton, BOOL Flag);	// ��ư Ȱ��ȭ ��Ȱ��ȭ
	void SetButtonTextColor(SI32 Index);

	void StartMagicCoolTime(SI32 CoolTime);

private:

	SI32		m_siCurrentButtonIndex;
	SI32		m_siSelectListIndex;
	SI32		m_siMagicKind;

	DWORD m_dwLastChangedMagic; 

	CList*		m_pList[2];		 // 0 : �������� 1 : ��������
	
	CButton*	m_pMagicNameButton[6];	// ���� �̸� ��ư
	CButton*	m_pButton[2];			// 0 : ���� , 1 : �ݱ�

	CEdit*		m_pEdit;

	TSpr		m_SprMagicIcon;
	TSpr		m_SprMagicCoolTime;

	// ���� ��Ÿ�� ǥ�ÿ� ����
	clock_t		m_CoolTimeStart;
	SI32		m_CoolTime;
};

#endif _NMAGIC_INFO_H_