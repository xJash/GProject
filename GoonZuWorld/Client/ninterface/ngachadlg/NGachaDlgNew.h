/* ==========================================================================
Ŭ���� :		CNGachaDlgNew

�ۼ��� :		07/04/11
�ۼ��� :		�迵��

������� :		����(�̱�) �ý��� �������̽�

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../server/GachaManager/GachaManager.h"

#define	MAX_GACHA_PRODUCT_ITEM 8

class CNGachaDlgNew : public CDialogController
{
public:

	CNGachaDlgNew();
	~CNGachaDlgNew();

	void Create();
	void Destroy();

	void DrawDialogFirst(SI32 ScreenRX, SI32 ScreenRY );
	void DrawDialogLast(SI32 ScreenRX, SI32 ScreenRY );

	static void CALLBACK StatiCNGachaDlgNewProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NGachaDlgNewProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	void Action();	

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	void SetGachaProductAndCount( cltItem* pclItem, UI16 GachaCnt );
	void SetGachaCount( UI16 _GachaCnt );
	void SetGachaUseKeyKind( SI32 _siGachaUseKeyKind );
	SI32 GetGachaUseKeyKind();
	void SetExplain2(TCHAR* _pText);
	void Text( SI32 ScreenRX, SI32 ScreenRY );
	
private:

	InterfaceFactory	m_InterfaceFactory;
	
	SI32				m_uiGachaCnt;								// ������ ���� Ƚ��
	cltItem				m_clGachaProductItem[MAX_GACHA_PRODUCT];	// ������ ������ �ִ� ������.

	TSpr				m_GachaGageImg;
	TSpr				m_NumberImg;

	SI32				m_siGachaUseKeyKind;
	TCHAR*				m_pText;									// ���� ����� �ؽ�Ʈ ��ȣ.

};
 