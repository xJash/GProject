/* ==========================================================================
Ŭ���� :		 

�ۼ��� :		 
�ۼ��� :		 

������� :		 

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class NPromoter_Introduce : public CDialogController
{
public:

	NPromoter_Introduce();
	~NPromoter_Introduce();

	void Create();

	static void CALLBACK StaticNPromoter_IntroduceProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NPromoter_IntroduceProc( UINT nEvent, int nControlID, CControllerObj* pControl );


	void SetRecommendIntroduce( TCHAR* _pszRecommendName, SI32 _siKind, bool _siIsConnect );		// ��õ����   �Ұ��Ѵ�.
	void SetRecommendeeIntroduce( TCHAR* _pszRecommendeeName, SI32 _siKind, bool _siIsConnect );	// ����õ���� �Ұ��Ѵ�.
	
private:
	InterfaceFactory	m_InterfaceFactory;

	TCHAR				m_WhispererCharName[MAX_PLAYER_NAME];
};
 