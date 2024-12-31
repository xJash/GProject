/* ==========================================================================
Ŭ���� :		CNGachaDlg

�ۼ��� :		07/04/11
�ۼ��� :		�迵��

������� :		����(�̱�) �ý��� �������̽�

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../server/GachaManager/GachaManager.h"

enum eGachaStep{
	GACHASTEP_TOP	= 1	,
	GACHASTEP_CHOOSEKEY	,
	GACHASTEP_DROPBOX	,
	GACHASTEP_SELECTBOX ,
	GACHASTEP_OPENBOX ,
	GACHASTEP_ITEMGET ,
	GACHASTEP_RAREITEMGET ,
	GACHASTEP_KEYNEED 
};

const SI32 GACHA_BOX_NUM = 5;

class CNGachaDlg : public CDialogController
{
public:

	CNGachaDlg();
	~CNGachaDlg();

	void Initialize();
	void Destroy();

	void Create();

	static void CALLBACK StaticNGachaDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NGachaDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

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
	
	cltItem m_GachaProduct[ MAX_SHOW_GACHA_PRODUCT ];

	POINT m_GachaProductPoint[ MAX_SHOW_GACHA_PRODUCT ];

	POINT m_RunRaccoonPoint;
	bool  m_bRaccoonDraw;

	cltItem m_GachaGetProduct;
	
	SI32 m_myGachaGoldKeyNum;
	SI32 m_myGachaSilverKeyNum;
	SI32 m_myGachaBronzeKeyNum;

	SI32 m_myGachaPieceNum;
		
	//bool m_bUseCashKey;	// ���ݿ��踦 ����Ͽ� ������ �ϴ��� ������
	// � ���踦 ����ϴ���
	SI32 m_myGachaUseKeyKind;

	

	//POINT m_BoxPoint[GACHA_BOX_NUM];

};
 