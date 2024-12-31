#ifndef _NNEWMAGIC_INFO_H_
#define _NNEWMAGIC_INFO_H_

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

#define MAGIC_NUM			10
#define SKILLBOOK_MAGIC		0

class CNNewMagicInfoDlg : public CDialogController
{
public:

	CNNewMagicInfoDlg();
	~CNNewMagicInfoDlg();
	
	void Clear( void );
	void Create();

	static void CALLBACK StaticCallBackDialogNNewMagicInfoDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNNewMagicInfoDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show();
	void Hide();

	void Action();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );
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

	void DrawMagic( SI32 ScreenRX, SI32 ScreenRY );
	void SetMagicInfo( SI32 index );
	void Refresh( void );
	void SetActiveMagicKind( SI32 _siActiveMagicKind );
	
private:

	SI32			m_siCurrentButtonIndex;
	SI32			m_siSelectListIndex;
	SI32			m_siActiveMagicKind;			// ����ϴ� ������ ����.
	SI32			m_siMagicKind;
	SI32			m_siParentMagicKind;
	SI32			m_siNewMagicKind[MAGIC_NUM];

	DWORD			m_dwLastChangedMagic; 

	CList*			m_pList[2];				// 0 : �������� 1 : ��������
	CButton*		m_pMagicNameButton[6];	// ���� �̸� ��ư
	CButton*		m_pButton[2];			// 0 : ���� , 1 : �ݱ�
	CEdit*			m_pEdit;
	CEdit*			m_pEdit2;
	CImageStatic*	m_pMagicImageStatic[MAGIC_NUM];		
	CImageStatic*	m_pSelcetMagicImageStatic;
	CImageStatic*	m_pUpgradeMagicImageStatic;
	CStatic*		m_pKey;
	CStatic*		m_pKeyExplain;
	CStatic*		m_pMagicName;
	CStatic*		m_pSubMagicName;
	
	CButton*		m_pMagicCancelButton;			


	TSpr			m_SprMagicIcon;
	TSpr			m_SprMagicIconOut;
	TSpr			m_SprMagicCoolTime;
	TSpr			m_SprSkillBook;

	// ���� ��Ÿ�� ǥ�ÿ� ����
	clock_t			m_CoolTimeStart;
	SI32			m_CoolTime;
};

#endif _NMAGIC_INFO_H_