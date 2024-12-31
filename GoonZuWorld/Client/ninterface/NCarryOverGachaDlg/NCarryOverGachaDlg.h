#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../common/CommonHeader.h"

#include "../../Server/GachaManager/GachaManager.h"

//--------------------------------------------------
// 0	= �̴��� ��ǰ
// 1~8	= �̿� ��ǰ

//const SI32 Max_CarryOver_Gacha_Product		= 9;

enum CARRYOVER_SELECT_MODE
{
	CARRYOVER_SELECT_MODE_GACHA = 0,
	CARRYOVER_SELECT_MODE_PRODUCT,

	CARRYOVER_SELECT_MODE_MAX
};

class CNCarryOverGachaDlg : public CDialogController
{

// -- Member Variable Area
private:
	InterfaceFactory	m_InterfaceFactory;

	SI32				m_siSelectGachaProductIndex;	// �ʱⰪ�� -1�̿�����
	SI32				m_siSelectGachaProductUnique;	// ��í ������ ����ũ

	SI32				m_siKeyControllerID;			// Ű ��Ʈ�ѷ� ID
	SI32				m_siKeyKind;					// ��í Ű ī�ε�

	SI32				m_siGachaGage;					// ���Ȯ��

	TCHAR*				m_pText;						// ���� �ؽ�Ʈ

	NTCHARString512		m_strGachaExplain;				// ��í������ ���� �ؽ�Ʈ

	// �̴�,�̿� ��í��ǰ Unique
	SI32				m_siCarryOverItems[TOTAL_GACHA_PRODUCT];

	// ������ ��í�� ǰ��
	SI32				m_siGachaProducts[MAX_GACHA_PRODUCT];

	TSpr				m_sprNumber;					// ��íŰ ��ȣ �̹���
	TSpr				m_sprGage;						// ���Ȯ�� ������

	SI32				m_siSelectMode;
protected:

public:


// -- Member Function Area
private:

protected:

public:
	CNCarryOverGachaDlg( void );
	~CNCarryOverGachaDlg( void );

	void Init();
	void Create();

	static void CALLBACK StaticCallBackDialogNCarryOverGachaDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNCarryOverGachaDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );
	void Text( SI32 ScreenRX, SI32 ScreenRY );

public:
	void OnClickGachaProduct( const SI32 siControllerID );
	void OnClickKey( const SI32 siControllerID );
	void OnClickKeyBuy( void );
	void OnClickGameStart( void );

public:
	void OnEventBack( void );

public:

	void ToggleKeyButtonEnable( const bool bGachaKeyEnable, const bool bAllRoundKeyEnable );
	void SetExplain2( TCHAR* pText );

	void HideItemControllers( void );

	void SetEnableGameStartButton( bool bEnable );

public:
	void SetTotalGachaListAndGachaCount( SI32* psiTotalGachaList, SI32 siGachaCount );
	void SetGachaProducts( SI32* psiGachaProducts );
	void ShowItemList( const SI32* const psiItemList, const SI32 siItemCount );

	bool IsHaveKey( void );

public:
	void SetGachaGage( SI32 siGachaGage )		{	m_siGachaGage = siGachaGage;			}

	SI32 GetKeyKind( void )						{	return m_siKeyKind;						}
	SI32 GetSelectGachaProductIndex( void )		{	return m_siSelectGachaProductIndex;		}
	SI32 GetSelectGachaProductUnique( void )	{	return m_siSelectGachaProductUnique;	}

};