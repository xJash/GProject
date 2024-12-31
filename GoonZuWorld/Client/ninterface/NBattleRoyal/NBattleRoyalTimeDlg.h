/* ==========================================================================
	Ŭ���� :		CNBattleRoyalTimeDlg

	�ۼ��� :		09/10/22
	�ۼ��� :		�ڱ���

	��  �� :		CNBattleRoyalTimeDlg Ŭ������  ������ ���۵� ��Ʋ�ξ��� �ð��� �˷��ִ� â ������ �Ѵ�.

	��  �� :		
	������� :		����

	�����۾� :		
   ========================================================================*/
#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class CStatic;

class CNBattleRoyalTimeDlg : public CDialogController
{
public:
	CNBattleRoyalTimeDlg();
	~CNBattleRoyalTimeDlg();

	void					Create();

	static void CALLBACK	StatiCNBattleRoyalTimeDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NBattleRoyalTimeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	
	void					SetDescription(TCHAR* szDescription);

private:
	CStatic                *m_pNTimeStatic;    
};

