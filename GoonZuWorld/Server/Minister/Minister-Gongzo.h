#ifndef _MINISTER_GONGZO_H_
#define _MINISTER_GONGZO_H_

//#define FIRST_GONGZO_SKILL	SKILL_MAKESWORD1
//#define END_GONGZO_SKILL	SKILL_MAKEGUN1

// ������ ����..������ �ȹٲ�..
const GMONEY ConstCraftFund_Min = 0;
const GMONEY ConstCraftFund_Max = 100;

class CMinisterGongzo : public CMinisterBase
{
public:
	SI32	m_siPriceTime;  // ���������� ������ �ð�
	SI16	m_siLeftOverValue;
	SI16	m_siLeftOverValue_Armor;
	GongzoMember m_stGongzoMember; // ���� ������ - ��ų �߰��� , ��ų ����
//	SI16	m_siPriceValue[GONGZO_SKILL_TOTAL]; // ��� ��ų�� ���� �迭
//	SI16	m_siSkillValue[GONGZO_SKILL_TOTAL]; // ��ų ����
/*	SI16	m_siPriceSword; // �˽�ų
	SI16	m_siPriceSpear; // â��ų
	SI16	m_siPriceAxe;	// ������ų
	SI16	m_siPriceStaff; // �����̽�ų
	SI16	m_siPriceBow;	// Ȱ��ų
	SI16	m_siPriceGun;	// �ѽ�ų*/

	CMinisterGongzo();
	~CMinisterGongzo();

	void 	InitializeDB();
	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket);

	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID);

	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID);

	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket);

	// gongzomembervalue = GONGZO_SKILL_SWORD,GONGZO_SKILL_SPEAR,GONGZO_SKILL_STAFF,GONGZO_SKILL_AXE,GONGZO_SKILL_BOW,GONGZO_SKILL_GUN
	SI32	GetGongzoSkillValue(SI16 gongzomembervalue);
	SI32	GetSkillExpPercent(SI32 siGoongzoSkill)
	{
		if( siGoongzoSkill < GONGZO_SKILL_SWORD || siGoongzoSkill > GONGZO_SKILL_RESERVED3 )
			return 0;

		return m_stGongzoMember.siPriceValue[siGoongzoSkill];
	}
};

#endif