
/* ==========================================================================
	Ŭ���� :		CNVoteDlg

	�ۼ��� :		05/03/25
	�ۼ��� :		���¾�

	��  �� :		.
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/


#pragma once

#include <Directives.h>
#include "..\..\..\Resource.h"
#include "client.h"
#include "../../InterfaceMgr/DialogController.h"

struct stCandidature;

class CStatic;
class CList;
class CButton;


class CNVoteDlg  : public CDialogController
{
public:	
	
	CNVoteDlg();
	~CNVoteDlg();

	void Initialize();

	void Create();


	static	void CALLBACK StaticNVoteDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void	CALLBACK NVoteDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl);
	
	
	void Set( TCHAR *VoteExplain, stCandidature *pCandidature );
	
	void LoadCandidatureList();
	void DisplayVoteAdvertise( TCHAR *HtmlPage );

	void RetMsgBox(bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:
	bool m_bShow;

	CList       	*m_pVoteKingList;
	CButton     	*m_pVoteKingButton1;
	CButton			*m_pVoteKingButton2;
	
	stCandidature *m_pstCandidatureList;		
	SI32 m_iSelectVoteInx;
	
};

