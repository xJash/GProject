#pragma  once


#include "../../Client/Client.h"
#include "../../InterfaceMgr/DialogController.h"

class CImageStatic;

#define BUFF_MAX_NUM				22
#define BUFF_ROULETTE_IMAGE_MAX_NUM	3
#define BUFF_LIMIT_NUM				3

enum {	BUFF_PREV, BUFF_CUR, BUFF_NEXT };

class CNBuffRoulette : public CDialogController
{
public:
	CNBuffRoulette();
	~CNBuffRoulette();

	void	SetControl(void);
	
	void	Create(void);
	void	Destroy(void);
	void	DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );

	void	Action(void);
	void	StartRoulette(void);
	void	ChangeBuff(void);
	GMONEY	GetBuffCost(void);
	void	SetBuff(void);
	void	SetCompleteBuff(bool _Action, SI32 _CompleteBuffKind);
	bool	GetRouletteAction(void);

	static void CALLBACK StaticNBuffRouletteProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NBuffRouletteDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

    void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	
private:
	InterfaceFactory	m_InterfaceFactory;
	
	bool				m_bRouletteAction;
	bool				m_bRouletteComplete;
	SI32				m_CurBuffNum;
	SI32				m_PrevBuffNum;
	SI32				m_NextBuffNum;			
	CImageStatic*		m_pBuffImage[BUFF_ROULETTE_IMAGE_MAX_NUM];
	DWORD				m_PrevTickCount;								// ���� ī��Ʈ.
	DWORD				m_DelayTickCount;								// ���� ī��Ʈ.
	DWORD				m_dwTickCount;									// �� ī��Ʈ.

	SI32				m_BuffKindArray[BUF_END];						// ��ü ������ ��ȣ �迭.
	SI32				m_SetBuffKindArray[BUF_END];					// ���õ� ������ ��ȣ �迭.
	SI32				m_SetBuffKindRate[BUF_END];						// ���õ� ���� Ȯ����.
	SI32				m_SetBuffNum;									// ���õ� ������ ����.

	SI32				m_CompleteBuffKind;								// �������� ���� �Ϸ�� ��������.

	SI32				m_sItemImageiFont;			// ũ�������� �̺�Ʈ�� ������, �׷��� �ε���.
	SI32				m_siGimgIndex;

	bool				m_bRouletteButtunOnly;		// �귿�� ���� �߿��� Start��ư�� ���´� (�� �뵵�θ� ����.)
};