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
	DWORD				m_PrevTickCount;								// 이전 카운트.
	DWORD				m_DelayTickCount;								// 이전 카운트.
	DWORD				m_dwTickCount;									// 비교 카운트.

	SI32				m_BuffKindArray[BUF_END];						// 전체 버프의 번호 배열.
	SI32				m_SetBuffKindArray[BUF_END];					// 세팅된 버프의 번호 배열.
	SI32				m_SetBuffKindRate[BUF_END];						// 세팅된 버프 확률값.
	SI32				m_SetBuffNum;									// 세팅된 버프의 개수.

	SI32				m_CompleteBuffKind;								// 서버에서 받은 완료된 버프종류.

	SI32				m_sItemImageiFont;			// 크리스마스 이벤트용 아이템, 그래픽 인덱스.
	SI32				m_siGimgIndex;

	bool				m_bRouletteButtunOnly;		// 룰렛이 도는 중에는 Start버튼을 막는다 (그 용도로만 쓴다.)
};