/*====================================

Ŭ���� : CNHappyBeanDlg
�ۼ��� : 07 .08 . 22
�ۼ���: �ռ���
�������:
�����۾�:
=====================================*/

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.	

#include "NHappyBeanDlg.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client/Client.h"
#include "Char/CharManager/CharManager.h"
#include "../../common/Quest/Quest.h"
#include "../CommonLogic/Msg/MsgType-HappyBeanQuest.h"


CNHappyBeanDlg :: CNHappyBeanDlg()
{
    Initialize();
}

CNHappyBeanDlg ::~CNHappyBeanDlg(){
	Destroy();
}

void CNHappyBeanDlg::init(){

}


void CNHappyBeanDlg :: Destroy(){

}
void CNHappyBeanDlg ::Create(){

	if ( IsCreate() )
		return;

	CInterfaceFile file;

	file.LoadFile(TEXT("NInterface/Data/NHappyBeanDlg/DLG_HappyBeanDlg.ddf"));
	file.CreatePopupDialog( this, NHAPPYBEAN_DLG , TEXT("dialog_happybean"), StaticSelectHappyBeanProc );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NSELECTHAPPYBEN_BUTTON_ACCEPT , this ), NSELECTHAPPYBEN_BUTTON_ACCEPT,   "button_accept");
	Show(true);
}

void CALLBACK CNHappyBeanDlg ::StaticSelectHappyBeanProc(CControllerMgr *pControllerMgr,UINT nEvent, int nControlID,CControllerObj *pControl)
{
	CNHappyBeanDlg *pThis = (CNHappyBeanDlg*)pControllerMgr;
	pThis->NSelectHappyBeanProc(nEvent, nControlID, pControl);
}


void CALLBACK CNHappyBeanDlg ::NSelectHappyBeanProc(UINT nEvent, int nControlID,CControllerObj* pControl)
{
	cltClient *pclclient = (cltClient *)pclClient;
	switch(nControlID)
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NSELECTHAPPYBEN_BUTTON_ACCEPT:
		if (EVENT_BUTTON_CLICKED == nEvent)
		{
			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
			cltQuestInfoCommon* pclhappybeaninfo = NULL;

			pclhappybeaninfo = &pclClient->pclCM->CR[1]->pclCI->clQuestInfo.clHappyBeanQuestInfo;

			if( pclhappybeaninfo->clQuestClearConditionInfo.siFlag == 0 )
			{
				SelectHappyBean();
				DeleteDialog();
			}
			else //���� �������� ���Ǻ� ����Ʈ�� �ִ�.
			{
				TCHAR buffer[256] =TEXT("");
				TCHAR temp[256];

				TCHAR* pText = GetTxtFromMgr(223); //����Ʈ ���� ����.

				TCHAR* pText2 = GetTxtFromMgr(7146);

				StringCchPrintf(temp, 256, pText2);
				StringCchCat(buffer, 256, temp);		

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText,	buffer);
			}
		}
		break;
	}
}

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
void CNHappyBeanDlg ::SelectHappyBean( )
{
	cltGameMsgRequest_HappyBeanQuestStart clInfo( QUEST_TYPE_HAPPYBEAN, QUEST_HAPPYBEAN_STEP_START );
	cltMsg clMsg( GAMEMSG_REQUEST_HAPPYBEANQUEST_START, sizeof( clInfo ), (BYTE*)&clInfo );
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
}
