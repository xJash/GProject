/* ==========================================================================
Ŭ���� :		CNGacha2Dlg

�ۼ��� :		08/11/04
�ۼ��� :		����

������� :		����(�̱�)2 �ý��� �������̽�

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../server/GachaManager/GachaManager.h"
#include "../../server/Gacha2Manager/Gacha2Manager.h"

enum eGacha2Step{
	GACHA2STEP_TOP	= 1	,
	GACHA2STEP_CHOOSEKEY	,
	GACHA2STEP_DROPBOX	,
	GACHA2STEP_SELECTBOX ,
	GACHA2STEP_OPENBOX ,
	GACHA2STEP_ITEMGET ,
	GACHA2STEP_RAREITEMGET ,
	GACHA2STEP_KEYNEED 
};

const SI32 GACHA2_BOX_NUM = 5;

class CNGacha2Dlg : public CDialogController
{
public:

	CNGacha2Dlg();
	~CNGacha2Dlg();

	void Initialize();
	void Destroy();

	void Create();

	static void CALLBACK StaticNGacha2DlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NGacha2DlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	//Action
	void Action();	
	
	//void ActionStepTop();
	void ActionStepDropBox();
	void ActionStepOpenBox();
	//void ActionStepSelectBox();
	//void ActionStepOpenBox();

	//Draw
	void DrawDialogFirst(SI32 ScreenRX, SI32 ScreenRY );

	void DrawStepTop( SI32 ScreenRX, SI32 ScreenRY );
	void DrawStepDropBox( SI32 ScreenRX, SI32 ScreenRY );
	void DrawStepSelectBox( SI32 ScreenRX, SI32 ScreenRY );
	void DrawStepOpentBox( SI32 ScreenRX, SI32 ScreenRY );
	void DrawStepItemGet( SI32 ScreenRX, SI32 ScreenRY );
	void DrawStepRareItemGet( SI32 ScreenRX, SI32 ScreenRY );
	void DrawStepKeyNeed( SI32 ScreenRX, SI32 ScreenRY );

	void DrawDialogLast(SI32 ScreenRX, SI32 ScreenRY );
	void DrawLastStepTop( SI32 ScreenRX , SI32 ScreenRY );
	void DrawLastStepChooseKey( SI32 ScreenRX , SI32 ScreenRY );
	void DrawLastStepDropBox( SI32 ScreenRX, SI32 ScreenRY );
	void DrawLastStepItemGet( SI32 ScreenRX , SI32 ScreenRY );
	void DrawLastStepRareItemGet( SI32 ScreenRX , SI32 ScreenRY );
	void DrawLastStepKeyNeed( SI32 ScreenRX , SI32 ScreenRY );


	//Init
	void ChangeCurrentStepAndInit(SI16 Step );	// �ܺο����� ȣ��Ǳ⵵ ��
	void InitStepTop();
	void InitStepChooseKey();
	void InitStepDropBox();
	void InitStepOpenBox();
	void InitStepItemGet();
	void InitStepRareItemGet();
	void InitStepKeyNeed();
	
	// Etc
	bool CheckHaveKey( SI32 GachaUseKeyKind );
    bool CheckHaveKeyPiece();

	// �ܺο����� ȣ��Ǵ�  �Լ�
	void SetGachaProductAndCount( cltItem * pclItem , UI16 GachaCnt );  // ������ ������ �ִ� ������ ����
	void SetGachaGetProductAndCount( cltItem * pclItem , UI16 GachaCnt , bool BestProduct );	// ������ ȹ���� ������ ����
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
private:

	InterfaceFactory	m_InterfaceFactory;
	
	SI32 m_FrameCnt;

	TSpr m_NumberImg;
	TSpr m_RunRaccoonImg;
	TSpr m_ClickImg;
	TSpr m_GachaGageImg;
	TSpr m_GachaGageOutLineImg;
	TSpr m_GachaResultImg;
	TSpr m_GachaFieldImg;

	UI16 m_uiGachaCnt; // ������ ���� Ƚ��

	SI16 m_siCurrentStep; // ���� ���� ���� �ܰ�
	
	cltItem m_GachaProduct[ MAX_SHOW_GACHA2_PRODUCT ];

	POINT m_GachaProductPoint[ MAX_SHOW_GACHA2_PRODUCT ];

	POINT m_RunRaccoonPoint;
	bool  m_bRaccoonDraw;

	cltItem m_GachaGetProduct;
	
	SI32 m_myGachaRaccoonKeyNum;
	//SI32 m_myGachaSilverKeyNum;
	//SI32 m_myGachaBronzeKeyNum;

	//SI32 m_myGachaPieceNum;
		
	//bool m_bUseCashKey;	// ���ݿ��踦 ����Ͽ� ������ �ϴ��� ������
	// � ���踦 ����ϴ���
	SI32 m_myGachaUseKeyKind;

	

	//POINT m_BoxPoint[GACHA_BOX_NUM];

};
 
