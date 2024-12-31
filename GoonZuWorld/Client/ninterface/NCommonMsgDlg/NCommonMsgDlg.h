//#ifndef _NMSGBOXDLG_H_
//#define _NMSGBOXDLG_H_

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/DialogController.h"

class CEdit;
class CButton;

#define COMMONDLG_NONE			0
#define COMMONDLG_REVIVE		1
#define COMMONDLG_RELOGIN		2
#define COMMONDLG_EXITCOUNT		3
#define COMMONDLG_CLOSE_PREMIUMSHOP		4
#define COMMONDLG_RESURRECTION			5	
#define COMMONDLG_INITLEVEL				6
#define COMMONDLG_MOFUMOFU_ENTER_FIELD1	7
#define COMMONDLG_MOFUMOFU_ENTER_FIELD2	8
#define COMMONDLG_MOFUMOFU_ENTER_FIELD3	9
#define COMMONDLG_MOFUMOFU_LEAVE_FIELD1	10
#define COMMONDLG_MOFUMOFU_LEAVE_FIELD2	11
#define COMMONDLG_MOFUMOFU_LEAVE_FIELD3	12
#define COMMONDLG_MOFUMOFU_AUTO_WARP	13
#define COMMONDLG_REQUEST_SETFATHER		14
#define COMMONDLG_DAILYQUEST_REWARD		15
#define COMMONDLG_CANNOTLOGIN_AGE		16
#define COMMONDLG_TICKETMONEY_WARP			17		//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.
#define COMMONDLG_EVENTCOUPON				18		//KHY - 0906 - ���ӹ� �̺�Ʈ ����.
#define COMMONDLG_AUCTIONEVENTCOUPON		19		//�����̺�Ʈ [2007.09.10 �ռ���]
#define COMMONDLG_GOSTOPPOCKERCOMPLETE		20		//����,��Ŀ�̺�Ʈ
#define COMMONDLG_GOSTOPPOCKERSTART			21
#define COMMONDLG_CANNOTLOGIN_ERROR			22
#define COMMONDLG_HANGAME_VIP_EVENT			23		//KHY - 1024 - �Ѱ��� VIP �̺�Ʈ
#define COMMONDLG_HANGAME_VIP_EVENT_ITEM	24		//KHY - 1024 - �Ѱ��� VIP �̺�Ʈ
#define COMMONDLG_NOWCOM_EVENT_COUPON		25		//KHY - 1025 - ������ �̺�Ʈ
#define COMMONDLG_NOWCOM_EVENT_10LEVEL		26		//KHY - 1025 - ������ �̺�Ʈ
#define COMMONDLG_NOWCOM_EVENT_HAVEFATHER	27		//KHY - 1025 - ������ �̺�Ʈ
#define COMMONDLG_INVITEEMPIRE				28		// ���� - �����ʴ�â
#define COMMONDLG_DAILYQUEST2_REWARD		29
#define COMMONDLG_DAILYQUEST3_REWARD		30
#define COMMONDLG_HALLOWEENMISSION_START	31
#define COMMONDLG_REQUEST_PVP				32
#define COMMONDLG_RESURRECTION_PVP			33
#define COMMONDLG_REQUEST_GUILDHUNTMAPWAR_WARP 34	// ������ �����ϱ� ���� ������� �����ϱ����� ���� �Ұ��ΰ�
#define COMMONDLG_REQUEST_TREASUREEVENT 35	// ����ã�� �̺�Ʈ - ����Ʈ�� �� ������ �޸������� ���� ��ī�� 10���� �ְ� ������ �޴´�
#define COMMONDLG_REQUEST_FAMILY_ADD_CHILDREN 36	// ���� �ý��� - ���� �߰�
#define COMMONDLG_REQUEST_FAMILY_DELL_CHILDREN 37	// ���� �ý��� - ���� Ż��
#define COMMONDLG_REQUEST_FAMILY_REMOVE_TARGET_CHILDREN 38 // �����ý��� - �������� ����
#define COMMONDLG_REQUEST_FAMILY_PLUS_FAMILYEFFECTDATE 39 // �����ý��� - ����ȿ�� ����
#define COMMONDLG_REQUEST_RACOONDODGEEVENT_ANSWER	40	// ���� ���ϱ� �̺�Ʈ �����Ҳ��Ĵ� ������ ���� �亯//Switch_10MonthEvent_RacoonDodge
#define COMMONDLG_BBB_WAIT_QUESTION			41		// [����] ����Ʈ�� ����ϰڳĴ� ��ȭ����
#define COMMONDLG_BBB_DELETE_WAITLIST		42		// [����] ����� ����Ʈ�κ��� ���� Ȯ�� ��ȭ����
#define COMMONDLG_BBB_WARPMAPQUESTION		43		// [����] 1���� ����ڿ��� �ߴ� "�����ҷ���?" ��ȭ����
#define COMMONDLG_BBB_NOTENOUGHMONEY		44		// [����] �������� ���� �����񺸴� ���ٰ� �˷��ִ� ��ȭ����
#define COMMONDLG_2010NEWYEARFORTUNE_BUF	45		// [����] 2010�ų��̺�Ʈ - ���� ���� �˷��ִ� ��ȭ����
#define COMMONDLG_2010NEWYEARFORTUNE_QUEST	46		// [����] 2010�ų��̺�Ʈ - ���� ����Ʈ �˷��ִ� ��ȭ����
#define COMMONDLG_INSURANCE_POLICY			47		// [����]	��������



//---------------------------------------------------

#define LOGOUT_DELAYTIME		20

class CNCommonMsgDlg : public CDialogController
{
public:
	CNCommonMsgDlg();
	~CNCommonMsgDlg();

	void Create();
	void Set(SI32 CommonDlg_mode);
	void Action();
	void LogOut();

	SI32 GetMode();
	void SetFather( SI32 PupilPersonID, TCHAR* PupilName );
	void SetInviteEmpire( SI08 InviteType, SI32 EmpireUnique, SI32 FromPersonID, SI32 EmproerVillageUnique );

	void SetText(TCHAR* pText);

	//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.
	void SetWarpMoney(SI32 MapIndex,SI32 Money );
	// PVP ��û�� ��� ID �� ���� 
	void SetPVPRequrstID( SI32 PVPRequestId );

	// â�� ���̴� �ð��� �����Ѵ�. �Լ� ȣ��ð� ���ĺ��� �ð��� ���.
	void SetShowTimeSec(SI32 siShowTimeSec);

	static void CALLBACK StaticCallBackDialogNCommonMsgDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNCommonMsgDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetGuildMapWar_PersonID( SI32 GuildMapWar_PersonID );

	void SetParentPersonID( SI32 siParentPersonID  )	;
	
private:
	SI32 siCommonDlg_mode;
	SI32 siExitCount;
	SI32 siPupilPersonID;
	TCHAR szPupilName[20];
	//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.
	SI64 siWarpMoney;
	SI32 szMapIndex;

	/// �������� �ʴ��ϴ� ���� 
	SI08	siInviteType;
	/// �ʴ�޽����� ���� ���� ����ũ
	SI32	siEmpireUnique;
	/// �ʴ�޽����� ���� PersonID
	SI32	siFromPersonID;
	/// �ʴ�޽����� ������ ���� ���� �̸�
	SI32	siEmproerVillageUnique;
	// PVP ��û�� ��� ID
	SI32	siPVPRequestID	;
	CEdit	*m_pEdit;
	CButton	*m_pOKButton;
	CButton	*m_pCancelButton;

	DWORD	m_dwStartTime;		// â�� �������� ���� �ð�
	DWORD	m_dwShowTimeMS;		// â�� �������� �ð� (ms)

	// ���� ������� ���� requset�� ������ PersoID
	SI32	siGuildMapWar_PersonID	;
	// �ڽ� ������ ���� �θ� personID
	SI32	m_siParentPersonID	;
};

//#endif
