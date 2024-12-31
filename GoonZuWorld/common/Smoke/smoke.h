#ifndef _SMOKE_H
#define _SMOKE_H

/*
#define MAX_SMOKE_KIND_NUMBER		90

#define SMOKE_GUN 					1
#define SMOKE_SINK      			2
#define SMOKE_EXP1					3
#define SMOKE_EXP2     				4
#define SMOKE_GROUNDFIRE			5
#define SMOKE_KIMBOMB1				6
#define SMOKE_KIMBOMB2				7
#define SMOKE_KIMBOMB3				8
#define SMOKE_LIGHTNING  			9
#define SMOKE_GHOST					10
#define SMOKE_HORSEDUST				11
#define SMOKE_CANNONEXP				12
#define SMOKE_FIRESMOKE				13			// �ҿ��� // 2003.10.29
#define SMOKE_RAREITEMSMOKE1		14			// ��ǰ ������ ��¦��
#define SMOKE_RAREITEMSMOKE2		15			// ��ǰ ������ ��¦��
#define SMOKE_RAREITEMSMOKE3		16			// ��ǰ ������ ��¦��
#define SMOKE_RAREITEMSMOKE4		17			// ��ǰ ������ ��¦��
#define SMOKE_FIREBALLHIT			18
#define SMOKE_CASTLEBOOM			19
#define SMOKE_SELFDESTUCT			20
#define SMOKE_ICESMOKE				21
#define SMOKE_JARSMOKE				22
#define SMOKE_WINDBLADE				23			// ��ȸŻ
#define SMOKE_TREEMON				24			// ������
#define SMOKE_VINE					25			// �ܴ�����
#define SMOKE_GHOSTFIRE				26			// ���ɱͽ�
#define SMOKE_DRAGONEXPLOSION		27
#define SMOKE_DRAGONEXPTAIL			28
#define SMOKE_SIMTORYONGSTONE		29			// �����
#define SMOKE_KINGCUTTLEFISH		30			// ��տ�����
#define SMOKE_BEGINWARP				31			// WARP ����
#define SMOKE_ENDWARP				32			// WARP ���� 
#define SMOKE_CRANE_TAIL			33			// ź������ ����
#define SMOKE_CRANE_HIT				34			// ź������ Ÿ��
#define SMOKE_SELFBOMBWHALE			35			// ���� ����
#define SMOKE_THROWKNIFE_RIGHT		36			// ǥâ���� ���� ���� ������
#define SMOKE_THROWKNIFE_LEFT		37			// ǥâ���� ���� ���� ����
#define SMOKE_KINGCRAB_TAIL			38			// ��ռҶ�� ����
#define SMOKE_DEADMESSENGER			39			// ���»���
#define SMOKE_FIRGROUNDTAIL			40	
#define SMOKE_FIREGROUNDEXPLOSION	41
#define SMOK_MASKMONK_STONE			42			// ��Ż �������� ��
#define SMOK_MASKMONK_DROPSTONE		43			// ��Ż ������ ��
#define SMOKE_PERSONCANNON_HIT		44			// ������ź ������ ��
#define SMOKE_MAGICFREEZEEXPLOSION	45			// �������� ������ ��

#define SMOKE_STAFFSCROLL_HIT		46			// �����̼� �߸� �����̿� �¾��� ��
#define SMOKE_STAFFSCROLL_TAIL		47			// �����̼� �߸� �����̿��� ������ ������ ����

#define SMOKE_GUNSCROLL_HIT			48			// �Ѽ� �߸� �����̿� �¾��� ��
#define SMOKE_GUNSCROLL_TAIL		49			// �Ѽ� �߸� �����̿��� ������ ������ ����

#define SMOKE_BOWSCROLL_HIT			50			// �ü� �߸� �����̿� �¾��� ��
#define SMOKE_BOWSCROLL_TAIL		51			// �ü� �߸� �����̿��� ������ ������ ����

#define SMOKE_FOAM_HIT				52			// �Ա��� ��Ʈ
#define SMOKE_MORTAL_FIRE			53			// ȸ�������� ����

#define SMOKE_WATERARROW_TAIL		54			// ��ȭ�� ����
#define SMOKE_WATERARROW_HIT		55			// ��ȭ�� ��Ʈ

#define SMOKE_MAGIC_PALMWIND_HIT	56			// ����� ��ǳ���� ��Ʈ

#define SMOKE_DOWNING_VINE			57			// ���� ������� ���

#define SMOKE_PALMWIND_TAIL			58			// ����� ��ǳ ����

#define SMOKE_HORSE_TICKET_EFFECT	59			// ���ɷ�����̿�� ���� �� Ÿ��

#define SMOKE_MAGIC_SKELLGHOST_TAIL 60			// �ذ����� ���� ����
#define SMOKE_MAGIC_SKELLGHOST_FIRE	61			// �ذ����� ���� �߻�

#define SMOKE_SWORDMETEOR_EXPLOSION	62			// ���ϼ����� ������ ��
#define SMOKE_SWORDMETEOR_TAIL		63			// ���ϼ����� ����
#define SMOKE_SWORDMETEOR_HIT		64			// ���ϼ����� ���� ��

#define SMOKE_MAIGCFROZEN_TAIL		65			// ������ ���� ���� ����
#define SMOKE_ICESTONE_HIT			66			// ������ ������ Ÿ��

#define SMOKE_TWINSPEAR_TAIL		67			// �糯â ����

#define SMOKE_FIREWHIRLWIND_HIT		68			// �����ٶ� ���� ����

#define SMOKE_NORTHWIND_HIT			69			// ��ǳ ����

#define SMOKE_NEW_STAFFSCROLL_HIT		70			// �����̼�(2��) �߸� �����̿� �¾��� ��
#define SMOKE_NEW_STAFFSCROLL_TAIL		71			// �����̼�(2��) �߸� �����̿��� ������ ������ ����

#define SMOKE_NEW_GUNSCROLL_HIT			72			// �Ѽ�(2��) �߸� �����̿� �¾��� ��
#define SMOKE_NEW_GUNSCROLL_TAIL		73			// �Ѽ�(2��) �߸� �����̿��� ������ ������ ����

#define SMOKE_NEW_BOWSCROLL_HIT			74			// �ü�(2��) �߸� �����̿� �¾��� ��
#define SMOKE_NEW_BOWSCROLL_TAIL		75			// �ü�(2��) �߸� �����̿��� ������ ������ ����

#define SMOKE_FIRESTORM_TAIL			76			// ��ȭ�� ���� ����

#define SMOKE_SPEAR_MANA_TAIL			77			// ���� ���� ����
#define SMOKE_SPEAR_DRAGON_TAIL			78			// ���� ���� ����
#define SMOKE_SPEAR_DRAGON_HIT			79			// ���� ���� ��Ʈ

#define SMOKE_BLACKSPIDER_HIT			80			// ��Ź� ���� ��Ʈ
#define SMOKE_PRIEST_HIT				81			// Ÿ�� ������ ���� ��Ʈ
#define SMOKE_GIRAFFE_HIT				82			// �⸰ ���� ��Ʈ

#define SMOKE_MINEGIRL_HIT				83			// ź���ҳ� ���� ��Ʈ

#define SMOKE_CATRANGE_HIT				84			// ���Ÿ� ����� ���� ��Ʈ
*/
	
//#define MAX_SMOKE_KIND_NUMBER		80

enum SMOKE_TYPE
{
	SMOKE_GUN					= 1
	,SMOKE_SINK
	,SMOKE_EXP1
	,SMOKE_EXP2
	,SMOKE_GROUNDFIRE
	,SMOKE_KIMBOMB1
	,SMOKE_KIMBOMB2
	,SMOKE_KIMBOMB3
	,SMOKE_LIGHTNING
	,SMOKE_GHOST

	,SMOKE_HORSEDUST
	,SMOKE_CANNONEXP
	,SMOKE_FIRESMOKE					// �ҿ��� // 2003.10.29
	,SMOKE_RAREITEMSMOKE1				// ��ǰ ������ ��¦��
	,SMOKE_RAREITEMSMOKE2				// ��ǰ ������ ��¦��
	,SMOKE_RAREITEMSMOKE3				// ��ǰ ������ ��¦��
	,SMOKE_RAREITEMSMOKE4				// ��ǰ ������ ��¦��
	,SMOKE_FIREBALLHIT	
	,SMOKE_CASTLEBOOM	
	,SMOKE_SELFDESTUCT

	,SMOKE_ICESMOKE	
	,SMOKE_JARSMOKE	
	,SMOKE_WINDBLADE					// ��ȸŻ
	,SMOKE_TREEMON						// ������
	,SMOKE_VINE							// �ܴ�����
	,SMOKE_GHOSTFIRE					// ���ɱͽ�
	,SMOKE_DRAGONEXPLOSION
	,SMOKE_DRAGONEXPTAIL
	,SMOKE_SIMTORYONGSTONE				// �����
	,SMOKE_KINGCUTTLEFISH				// ��տ�����

	,SMOKE_BEGINWARP					// WARP ����
	,SMOKE_ENDWARP						// WARP ���� 
	,SMOKE_CRANE_TAIL					// ź������ ����
	,SMOKE_CRANE_HIT					// ź������ Ÿ��
	,SMOKE_SELFBOMBWHALE				// ���� ����
	,SMOKE_THROWKNIFE_RIGHT				// ǥâ���� ���� ���� ������
	,SMOKE_THROWKNIFE_LEFT				// ǥâ���� ���� ���� ����
	,SMOKE_KINGCRAB_TAIL				// ��ռҶ�� ����
	,SMOKE_DEADMESSENGER				// ���»���
	,SMOKE_FIRGROUNDTAIL

	,SMOKE_FIREGROUNDEXPLOSION
	,SMOK_MASKMONK_STONE				// ��Ż �������� ��
	,SMOK_MASKMONK_DROPSTONE			// ��Ż ������ ��
	,SMOKE_PERSONCANNON_HIT				// ������ź ������ ��
	,SMOKE_MAGICFREEZEEXPLOSION			// �������� ������ ��
	,SMOKE_STAFFSCROLL_HIT				// �����̼� �߸� �����̿� �¾��� ��
	,SMOKE_STAFFSCROLL_TAIL				// �����̼� �߸� �����̿��� ������ ������ ����
	,SMOKE_GUNSCROLL_HIT				// �Ѽ� �߸� �����̿� �¾��� ��
	,SMOKE_GUNSCROLL_TAIL				// �Ѽ� �߸� �����̿��� ������ ������ ����
	,SMOKE_BOWSCROLL_HIT				// �ü� �߸� �����̿� �¾��� ��

	,SMOKE_BOWSCROLL_TAIL				// �ü� �߸� �����̿��� ������ ������ ����
	,SMOKE_FOAM_HIT						// �Ա��� ��Ʈ
	,SMOKE_MORTAL_FIRE					// ȸ�������� ����
	,SMOKE_WATERARROW_TAIL				// ��ȭ�� ����
	,SMOKE_WATERARROW_HIT				// ��ȭ�� ��Ʈ
	,SMOKE_MAGIC_PALMWIND_HIT			// ����� ��ǳ���� ��Ʈ
	,SMOKE_DOWNING_VINE					// ���� ������� ���
	,SMOKE_PALMWIND_TAIL				// ����� ��ǳ ����
	,SMOKE_HORSE_TICKET_EFFECT			// ���ɷ�����̿�� ���� �� Ÿ��
	,SMOKE_MAGIC_SKELLGHOST_TAIL		// �ذ����� ���� ����

	,SMOKE_MAGIC_SKELLGHOST_FIRE		// �ذ����� ���� �߻�
	,SMOKE_SWORDMETEOR_EXPLOSION		// ���ϼ����� ������ ��
	,SMOKE_SWORDMETEOR_TAIL				// ���ϼ����� ����
	,SMOKE_SWORDMETEOR_HIT				// ���ϼ����� ���� ��
	,SMOKE_MAIGCFROZEN_TAIL				// ������ ���� ���� ����
	,SMOKE_ICESTONE_HIT					// ������ ������ Ÿ��
	,SMOKE_TWINSPEAR_TAIL				// �糯â ����
	,SMOKE_FIREWHIRLWIND_HIT			// �����ٶ� ���� ����
	,SMOKE_NORTHWIND_HIT				// ��ǳ ����
	,SMOKE_NEW_STAFFSCROLL_HIT			// �����̼�(2��) �߸� �����̿� �¾��� ��

	,SMOKE_NEW_STAFFSCROLL_TAIL			// �����̼�(2��) �߸� �����̿��� ������ ������ ����
	,SMOKE_NEW_GUNSCROLL_HIT			// �Ѽ�(2��) �߸� �����̿� �¾��� ��
	,SMOKE_NEW_GUNSCROLL_TAIL			// �Ѽ�(2��) �߸� �����̿��� ������ ������ ����
	,SMOKE_NEW_BOWSCROLL_HIT			// �ü�(2��) �߸� �����̿� �¾��� ��
	,SMOKE_NEW_BOWSCROLL_TAIL			// �ü�(2��) �߸� �����̿��� ������ ������ ����
	,SMOKE_FIRESTORM_TAIL				// ��ȭ�� ���� ����
	,SMOKE_SPEAR_MANA_TAIL				// ���� ���� ����
	,SMOKE_SPEAR_DRAGON_TAIL			// ���� ���� ����
	,SMOKE_SPEAR_DRAGON_HIT				// ���� ���� ��Ʈ
	,SMOKE_BLACKSPIDER_HIT				// ��Ź� ���� ��Ʈ

	,SMOKE_PRIEST_HIT					// Ÿ�� ������ ���� ��Ʈ
	,SMOKE_GIRAFFE_HIT					// �⸰ ���� ��Ʈ
	,SMOKE_MINEGIRL_HIT					// ź���ҳ� ���� ��Ʈ
	,SMOKE_CATRANGE_HIT					// ���Ÿ� ����� ���� ��Ʈ
	,SMOKE_BEARTANG_HIT					// ���� ���� ��Ʈ
	,SMOKE_SUPERBEARTANG_HIT			// �������� ���� ��Ʈ
	//,SMOKE_GREATWALLASURA_HIT			// ��������� �Ƽ��� ���� ��Ʈ
	,SMOKE_MARRIED_FULLDRESS			// ��ȥ ���� ��¦�� ����Ʈ 	

	//**************************************************************//
	//
	// [����] ����ũ �߰��� �� ���� ���ּ���
	//
	//**************************************************************//
	,MAX_SMOKE_KIND_NUMBER
};

// ������ �ִϸ��̼� �ӵ��� ���.
#define	SMOKE_DELAY_1	1
#define SMOKE_DELAY_2	2
#define SMOKE_DELAY_3	3
#define	SMOKE_DELAY_4	4
#define	SMOKE_DELAY_5	5
#define	SMOKE_DELAY_10	10

#define ORDER_SMOKE_EXP     1

#define MAX_SMOKE_FILE_NAME_LENGTH	64

#include <Graphic.h>
#include <Graphic_Capsule.h>

class cltMapCommon;

//-------------------------------------------
// cltSmokeKindInfo
//-------------------------------------------
class cltSmokeKindInfo
{
public:
	cltSmokeKindInfo();
	~cltSmokeKindInfo();
	void Init( TCHAR *filename, SHORT startfont, SHORT moveframenumber, SHORT maxrepeatnumber, SI32 siStepDelay, SHORT risingswitch, SI32 transparentmode, SI08 siAlpha, SI32 siyindent,bool direction = false);
	void LoadSpr();

	TCHAR szFileName[MAX_SMOKE_FILE_NAME_LENGTH];
	TSpr Spr;

	SI32  StartFont;
	SHORT MoveFrameNumber;
	SHORT MaxRepeatNumber;
	SHORT RisingSwitch;
	SI32  TransparentMode;
	SI32  m_siStepDelay;
	SI32 siYIndent;
	SI08 siAlpha;
	bool bDirection; // 16������ �ؾ��ϴ°�
};

//--------------------------------------
// cltSmokeCommon
//--------------------------------------
class cltSmokeCommon{
public:
	cltSmokeKindInfo* pclSKI;
	cltMapCommon* pclMap;

	//----------------
	// �źа��� 
	//----------------
	SI32	ID;
	SI32	Kind;
	SI32	GroundKind; // �̳��� �����ϸ� �̳��� �ѹ� �� �׷��ش�.

	//--------------------
	// ��ǥ 
	///-------------------
	SI32 RealX, RealY;
	SI32 X, Y;
	SI32 CenterX, CenterY;

	//--------------------
	// �ൿ 
	//--------------------
	SI32  CurrentOrder;               // ���� ĳ���Ͱ� �ϰ� �ִ� �۾� 
	SI32	Animation;
	SI32	Step;

	//--------------------
	// ���� �Ⱓ.
	//--------------------
	SI32 MaxRepeatNumber;
	SI32 RepeatNumber;
	SI32  m_siStepDelay;			// �ִϸ��̼��� �ӵ�.
	DWORD LastChangedFrame;           // �ִϸ��̼��� ����� ������ 
	SI32 MoveFrameNumber;

	//--------------------
	// ���� 
	//--------------------
	SI32 AttackID;
	SI32 Apower;

	//--------------------
	// �ɼ� 
	//--------------------
	BOOL RisingSwitch;
	
	//--------------------
	// ���⼺
	//-------------------
	SI32 TempDirection;

public:
	virtual void Init(){};
	virtual BOOL Draw(){return FALSE;};

	
	cltSmokeCommon();
	void Init(SHORT kind, SHORT id, SHORT realx, SHORT realy, cltMapCommon* pmap,
			  cltSmokeKindInfo* pclinfo,SI32 tempdirection = 0 ,SI32 groundkind = 0 );
	BOOL Action();
	void CalculateRealXY();

};

//---------------------------------------
// cltSmokeServer
//---------------------------------------
class cltSmokeServer : public cltSmokeCommon
{
public:

	cltSmokeServer();

	void Init();


};

//---------------------------------------
// cltSmokeClient
//---------------------------------------
class cltSmokeClient : public cltSmokeCommon
{
public:
	SI32 StartFont;
	TSpr* pSpr;

	SI32	Font;
	SI32  TransparentMode;          // ����ȿ���� ���� ���ΰ� ?
	bool DrawSwitch;                   // �׷��� ���ΰ� �����ΰ�?
	bool ReverseSwitch;                // ����� ���� ���ΰ�?
	SI32  DrawStartX, DrawStartY;      // �׸��� �׷����� ���� ��ġ
	bool DirectionMode;					// 16������ ���� �ϴ°�?
	SI08 siAlphaValue;				// Alpha ��

	cltSmokeClient();

	void Init();
	BOOL Draw();
	void DecideFont();
	void DecideFontMove();
	void CalculateDrawStartXY();

};

//----------------------------------------------
// cltSmokeManager
//----------------------------------------------
class cltSmokeManager{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltSmokeCommon*, MAX_SMOKE_NUMBER>			pclSmoke;
	NSafeTArray<cltSmokeKindInfo, MAX_SMOKE_KIND_NUMBER>	SKI;

	NSafeTArray<SI32, MAX_SMOKE_NUMBER>						SmokeInfo;
#else
	cltSmokeCommon*		pclSmoke[MAX_SMOKE_NUMBER];   // ����� ������ 
	cltSmokeKindInfo	SKI[MAX_SMOKE_KIND_NUMBER];

	SI32 SmokeInfo[MAX_SMOKE_NUMBER]; // ���⿡ ���� ������ ������ ���� 
#endif

private:
	void InitSmokeKindInfo();
	void DeleteSmoke(SI32 id);
	SI32 FindEmptySmoke();

public:
	cltSmokeManager(SI32 gamemode);
	~cltSmokeManager();
	SI32 SetSmoke(SI16 siKind, SI16 x, SI16 y, cltMapCommon* pmap,SI32 tempdirection = 0 ,SI32 groundkind = 0 );
	void Draw();
	void Action();
	void DeleteSmoke();

	int TempDirection; // 16����

};

#endif









