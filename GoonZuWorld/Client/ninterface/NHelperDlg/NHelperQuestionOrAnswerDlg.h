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
#include "../../Server/HelperManager/HelperManager.h"

enum
{
	 QUESTION_DLG
	,ANSWER_DLG
};

class NHelperQuestionOrAnswerDlg : public CDialogController
{
public:

	NHelperQuestionOrAnswerDlg();
	~NHelperQuestionOrAnswerDlg();

	void Init();

	void Create();
	void Destroy();

	void Action();

	static	void CALLBACK StaticNHelperQuestionOrAnswerProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
			void CALLBACK NHelperQuestionOrAnswerProc( UINT nEvent, int nControlID, CControllerObj* pControl );

public:
	void SetQuestionDlg( bool _bQuestionDlg );
	void SetQuestionCharInfo( const TCHAR* _pszName, TCHAR* _pszQuestionTitle, SI32 _siQuestionPersonID );

private:
	InterfaceFactory	m_InterfaceFactory;

	TCHAR				m_szTitle[ TITLE_LETTER_NUM ];							// �����̳� �亯 ����
	TCHAR				m_szContents[ CONTENTS_LETTER_NUM ];					// �����̳� �亯 ����.

	bool				m_bQuestionDlg;											// ����â�ΰ� �亯â�ΰ�.

	TCHAR				m_szQuestionCharName[MAX_PLAYER_NAME];					// ������ �̸�.
	SI32				m_siQuestionPersonID;									// ������ personID

	DWORD				m_dwPrevTime;											// �亯�Ҷ� �ð� ī��Ʈ.
};
