#ifndef _MINISTER_IZO_H_
#define _MINISTER_IZO_H_

const SI32 Const_SpecialTaxRange_Min = 100;		//Ư���� ���� ���� �ּҰ� ( 100% )
const SI32 Const_SpecialTaxRange_Max = 150;		//Ư���� ���� ���� �ִ밪 ( 100% )
const SI32 Const_SpecialTaxRate_Min = 5;		//Ư������ �ּҰ�( 5% )
const SI32 Const_SpecialTaxRate_Max = 50;		//Ư������ �ִ밪( 50% )
const SI32 Const_SpecialTaxStep = 5;			//5%�� �ø��ų� ������ ����

const SI32 Const_MarketDownRate_Min = 1;		// ���� ������ �ּҰ�
const SI32 Const_MarketDownRate_Max = 15;		// ���� ������ �ִ밪

class CMinisterIzo : public CMinisterBase
{
private:
	bool	m_bWorldTradeTax;			// ����_���� ���� ����
	SI32	m_siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
	SI32	m_siSpecialTaxRate;			// ����_Ư������( 10% ~ 100% )

	SI32	m_siMarketDownRate;			//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
	SI16	m_siTinTin;					// ƾƾ �߰� ������

public:
	SI32	m_siPriceValue;	// ������
	SI32	m_siPriceTime;  // ���������� ������ �ð�
	SI64	m_siTotalMoney; // ����ȭ��
	SI32	m_siCalcTime;	// ����ȭ�� ����� �ð�
	SI32	m_siTradeTax; // ������
	GMONEY	m_siTradeLimitMoney; // ��аŷ��� �ּҰ���

	CMinisterIzo();
	~CMinisterIzo();


	void 	InitializeDB();
	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket);
	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID);
	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID);
	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket);

	void	SetIsWorldTradeTax( bool mode ){ m_bWorldTradeTax = mode; }
	bool	GetIsWorldTradeTax(){ return m_bWorldTradeTax; }
	void	SetSpecialTaxRange( SI32 range ){ m_siSpecialTaxRange = range; }
	SI32	GetSpecialTaxRange(){ return m_siSpecialTaxRange; }
	void	SetSpecialTaxRate( SI32 rate ){ m_siSpecialTaxRate = rate; }
	SI32	GetSpecialTaxRate(){ return m_siSpecialTaxRate; }

	void	SetMarketDownRate( SI32 rate ){ m_siMarketDownRate = rate; }
	SI32	GetMarketDownRate(){ return m_siMarketDownRate; }

	SI32	GetTinTin()			{ return m_siTinTin;	}
};

#endif