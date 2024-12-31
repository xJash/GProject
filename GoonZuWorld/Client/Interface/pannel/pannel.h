//---------------------------------
// 2003/8/27 ���°�
//---------------------------------
#ifndef _PANNEL_H
#define _PANNEL_H

#include <Directives.h>

#include "../../FontManager/FontManager.h"


#define HEALTH_SICK			0x1	   // �������
#define HEALTH_HUNGRY		0x2   // �����
#define HEALTH_LEPLETE		0x4   // �ʹ� ��θ�



class cltPannel
{

	enum CONST_VARIABLE
	{
		PANNEL_MAX_STRING_SIZE = 128	// ���ڿ� ������
	};
	//------------------------------------------------
	// ��������
	//------------------------------------------------
public:
	SI32	m_siDrawStartX;	// �ǳ� �׸��� ������ġ X,Y
	SI32	m_siDrawStartY;	

private:
	TCHAR	m_szDate[PANNEL_MAX_STRING_SIZE];
	TCHAR	m_szMoney[PANNEL_MAX_STRING_SIZE];
	

	//------------------------------------------------
	// �Լ�����
	//------------------------------------------------
public:
	cltPannel(SI32 siDrawStartX, SI32 siDrawStartY);
	~cltPannel();

	void SetszDate(TCHAR* szDate);  // ����� �ð� ���ڿ� ����
	void Draw( 
		LPDIRECTDRAWSURFACE7 lpsurface,	// �׷��� �����̽�
		SI32 siRealX,					// ���� ��ũ�� ��ġ
		SI32 siRealY, 
		SI32 siRandomX,					// ��������� ���� ������ǥ
		SI32 siRandomY
		);



/*
public:
	SI32 DrawStartX, DrawStartY;

	cltPannel(SI32 drawstartx, SI32 drawstarty);
	~cltPannel();

	void Draw(LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry,
		TCHAR* rank, GMONEY money, SI32 level, SI32 curexp, SI32 nextexp, SI32 life, SI32 maxlife,
		SI32 mana, SI32 maxmana,SI32 health,SI32 siMousePosX = 0, SI32 siMousePosY = 0, SI32 preexp = 0 ,
		SI32 heallife = 0 ,SI32 healmana = 0 ,SI32 randx = 0 , SI32 randy = 0 );

	void DrawSummon(LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry, SI16 portrait,
		SI32 curexp, SI32 nextexp, SI32 life, SI32 maxlife, SI32 mana, SI32 maxmana,SI32 preexp = 0,SI32 heallife = 0 ,
		SI32 status = 0 , SI32 stamina = 0 ,SI32 maxstamina = 0, SI32 leftsummonstart = 0, SI32 summonindex = 0,SI32 randx = 0 , SI32 randy = 0 );
	
	void SetszPosition(TCHAR* szposition) ; // ����� ��ġ ���ڿ� ����
	void SetszDate(TCHAR* szdate);  // ����� �ð� ���ڿ� ����

private:
	TSpr m_PannelBackGroundSpr;
	TSpr m_SummonPannelBackSpr;

	TSpr m_HpMpSqr;
	TSpr m_PlayerPortraitSqr;

//	TSpr m_LifeSpr;	// ���� �ʿ�
//	TSpr m_LifeRoundSpr;	// ����
	TSpr m_SummonLifeSpr;

	TSpr m_ExpSpr;			
	TSpr m_ExpRoundSpr;		
	TSpr m_SummonExpSpr;
	

//	TSpr m_ManaSpr;  // ����
//	TSpr m_ManaRoundSpr;  // ����
	TSpr m_SummonManaSpr;

	TSpr m_SummonStaminaSpr;
	TSpr m_SummonRecoverySpr;

	TSpr m_GageBackGroundSpr;
	TSpr m_SummonBackGroundSpr;
	TSpr m_SummonBackGroundSpr2;

	TSpr m_SummonPortrait[2];

	TSpr m_HealthStatusSpr;
	TSpr m_HungryGageSpr ;

	TSpr m_HealthStatusSpr2;

	TSpr m_LevelMark;
	TSpr m_LevelNumber;

	//TSpr m_HealthStatusSpr

	void DrawHungryGage(SI32 x , SI32 y , SI32 health); // ��θ�
	void DrawBreath(SI32 x,SI32 y,SI32 health); // ȣ����
	void DrawDigest(SI32 x,SI32 y,SI32 health); // ��ȭ���
	void DrawCirculation(SI32 x,SI32 y,SI32 health); // ��ȯ���
	void DrawNerve(SI32 x,SI32 y,SI32 health); // �Ű���

	SI32 m_siHungryStatus ;
	SI32 m_siSickStatus;
	
	SI32 m_siDrawHealthStatusCnt;
//	BOOL m_bDrawHealthStatus;

	TCHAR	m_szDate[256];
	TCHAR	m_szMoney[256];

	bool GetHealthText( TCHAR* pHealthText );
*/
};
#endif

