
#pragma once

#include "../../InterfaceMgr/DialogController.h"

class CNCarryOver_ProductDlg : public CDialogController
{

// -- Member Variable Area
private:
	InterfaceFactory	m_InterfaceFactory;

	SI32				m_siKeyKind;

	SI32				m_siSelectGachaProductIndex;	// �ʱⰪ�� -1�̿�����
	SI32				m_siSelectGachaProductUnique;	// ��í ������ ����ũ

	SI32				m_siBestItemUnique;				// �ְ� ��ǰ ������ ����ũ;

protected:

public:


// -- Member Function Area
private:

protected:

public:
	CNCarryOver_ProductDlg( void );
	~CNCarryOver_ProductDlg( void );

	void Init();
	void Create();

	static void CALLBACK StaticCallBackDialogNCarryOver_ProductDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNCarryOver_ProductDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show( void );
	void Hide( void );


public:
	void OnClickGameStart( void );
	void OnClickBack( void );

public:
	void SetInfo( const SI32 siItemUnique, const SI32 siKeyKind, const SI32 siSelectGachaProductIndex, const SI32 siSelectGachaProductUnique );
		

};