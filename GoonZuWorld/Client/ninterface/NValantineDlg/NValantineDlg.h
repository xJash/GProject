//-----------------------------------------------------------------------------------------------
//	�ۼ���		:	�ռ���
//	�ۼ�����	:	2008-12-10
//	����		:	�߷�Ÿ�ε��� �̺�Ʈ�� �ʱ⿡ �ڽ��� Ŀ������ �ַ����� �����ϴ� ���̾�α�
//					�� ���̾�α״� ������ ������ ������ �ϸ� �Ѵ�. -�����ִ� ���� ����.-
//-----------------------------------------------------------------------------------------------


#ifndef _NVALANTINEDLG_H_
#define _NVALANTINEDLG_H_

#include "../Client/client.h"
#include "../Common/Util/Util.h"
#include "../../InterfaceMgr/DialogController.h"

class CNValantineDlg : public CDialogController
{
private:
        
public:
	CNValantineDlg();
	~CNValantineDlg();

	InterfaceFactory m_InterfaceFactory;

	LPDIRECTDRAWSURFACE7		lpBackScreen;	// ������ �׷��� ȭ�� ���� ���ǽ�. 

	void Create();
	
	static void CALLBACK StaticNValantineDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )	;
		   void CALLBACK NValantineDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl )	;
	void SendMyStatus(SI32 siMyStatus )	;	// ���� �ַ����� Ŀ������ ������ ������.
	void MsgBox( )	;	// ���� �ַ����� Ŀ������ ������ ������.
};
#endif
