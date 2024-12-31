//---------------------------------
// 2003/5/24 ���°�
//---------------------------------

#ifndef _CHARANI_H
#define _CHARANI_H

#include "TSpr.h"
#include "NArray.h"

//-------------------------------------------------
// AniAtb
//-------------------------------------------------
//  2 Direction Animation - 1 Dir mirror 
#define ANIATB_DIR2								1		
// 16 Direction Animation - 9 Dir mirror
#define ANIATB_DIR16					 	    2		
// Animation ONLY once
#define ANIATB_ONLYONCE							8		
// Single Frame
#define ANIATB_SINGLEFRAME					    16		

//----------------------------------------------------
//  AniType
//----------------------------------------------------
#define MAX_ANINUM_PER_KIND						50		// �� ������ ĳ���Ͱ� ���� �� �ִ� �ִ� �ִϸ��̼� ��. 

#define ANITYPE_ATTACK							1
#define ANITYPE_DYING							2
#define ANITYPE_HEAL							3
#define ANITYPE_MOVE							4
#define ANITYPE_WAIT0							5
#define ANITYPE_WAIT1							6
#define ANITYPE_EXP								7
#define ANITYPE_HIT								8
#define ANITYPE_MAGIC							9
#define ANITYPE_FISH							10
#define ANITYPE_FARM							11
#define ANITYPE_ATTACKSHADOW					12		// ���� �ִϽ� ���� ���� �ִϸ��̼�
#define ANITYPE_ATTACK1							13
#define ANITYPE_ATTACK2							14
#define ANITYPE_MAGICSHADOW						15		// ���� �ִϽ� ���� ���� �ִϸ��̼�
#define ANITYPE_DYINGSHADOW						16		// ���� �� ���� ���� �ִϸ��̼�
#define ANITYPE_MOVESHADOW						17		// ������ �� ���� ���� �ִϸ��̼�
#define ANITYPE_WAIT0SHADOW						18		// ���ڸ����� 0�� �� ���� ���� �ִϸ��̼�
#define ANITYPE_WAIT1SHADOW						19		// ���ڸ����� 1�� �� ���� ���� �ִϸ��̼�
#define ANITYPE_HITSHADOW						20		// �ǰݽ� ���� ���� �ִϸ��̼�
#define ANITYPE_MINE							21		// ä��
#define ANITYPE_ATTACKSHADOW1					22		// ���� �ִϽ� ���� ���� �ִϸ��̼� 
#define ANITYPE_SITDOWN							23		// �ɱ� ����
#define ANITYPE_MAKEARMOR						24		// �� ���� ����
#define ANITYPE_MAKEHEAL						25		// �� ���� ����
#define ANITYPE_MAKEFOOD						26		// ���� ���� ����
#define ANITYPE_CRY								27		// ���� ��ȯ�� ��� ����
#define ANITYPE_VERYCRY							28		// ���� ��ȯ�� ���� ��� ����
#define ANITYPE_PLAY							29		// ���� ��ȯ�� ���� ����
#define ANITYPE_SMILE							30		// ���� ��ȯ�� ���� ����
#define ANITYPE_SURPRISE						31		// ���� ��ȯ�� ���� ����
#define ANITYPE_ANGRY							32		// ���� ��ȯ�� ȭ���� ����
#define ANITYPE_CATANGRY						33		// ����̰� ���� ���� ��ô �Ѵ�
#define ANITYPE_GOOD							34		// ����̰� ���� �����δ�
#define ANITYPE_SIT								35		// ����̰� �ɴ´�
#define ANITYPE_HAND							36		// ����̰� ���� ���� ���δ�
#define ANITYPE_FEATHER							37		// ����� ������ ����� ����̰� ������ ����
#define ANITYPE_SLEEP							38		// �̺� - �ܴ�.
#define ANITYPE_EAT								39		// �絹���� �����ɾ� ���ö��� �Դ´�.
#define ANITYPE_EMIT							40		// �絹���� �ڿ��� �������� ���´�.
#define ANITYPE_ROUDOLPHCRY						41		// �絹���� �����ɾ� �������.
#define ANITYPE_ROUDOLPHDANCE					42		// �絹���� ���� ���.
#define	ANITYPE_ROUDOLPHSMILE					43		// �絹���� �ڼ��� ġ�� ȯ�ϰ� ���´�.
#define	ANITYPE_ROUDOLPHSUPRISE					44		// �絹���� ��¦�����.
#define ANITYPE_SOULGUARDSF						45		// ��ȣ���� Ư���ɷ� �ߵ� ���
#define ANITYPE_SLEEPCAT						46		// ���ڴ� �Ŀ��� �漮 ���
#define ANITYPE_SOULGUARDSFSHADOW				47		// ��ȣ���� Ư���ɷ� �ߵ� ���(����Ʈ)





#define MAX_IMG_FILE_PER_KIND					6		// �� ������ ĳ���Ͱ� ���� �� �ִ� �ִ� �̹��� ���� ��. 
#define MAX_ATTACKTYPE_PER_KIND					5		// �ִ� ���ݵ��� Ÿ��

class cltCharAnimationManager;
class TSpr;

//--------------------------------------------------
// �������� ĳ���Ͱ� �����ϰ� �Ǵ� �ִϸ��̼� ����. 
//--------------------------------------------------
class cltAniInfo{
public:
	SI32	siAniStep;
	SI32	siAniDelayor;
	SI32	siAniDelay;
	SI32	siAniInstant;
	DWORD	dwElapsedClock;			// �ִ� ���ۺ����� �ð� 
	DWORD	dwAniStartClock;		// �ִ� ���� �ð�. 

	SI32	siRetryNum;				// �ִϸ� �ݺ� �Ϸ��� ȸ��. 
public:
	
	cltAniInfo();
	~cltAniInfo();

	void Init1();
	BOOL IsInstant()const;

	void SetAniStep(SI32 step);
	SI32 GetAniStep() const;
	void IncreaseAniStep(SI32 amount);
	void DecreaseAniStep(SI32 amount);
	
	BOOL IsLast() const;
	SI32 GetAniDelayor() const;
	void SetAniDelayor(SI32 delayor);
	void IncreaseAniDelayor(SI32 amount);
	void SetAniDelay(SI32 delay);
	SI32 GetAniDelay() const;
	
	void SetAniInstant(SI32 instant);
	SI32 GetAniInstant() const;
};

//----------------------------------------------
// �������� ĳ���� �ִϸ��̼� ���� 
//----------------------------------------------
class cltCharAnimation {

public:
	BOOL  bDirSwitch;

private:
	cltCharAnimationManager* pclAniMng;

	SI32	siRef;
	SI32	siAniType;
    SI32	siFrameNum;

public:
	SI32	siFont;
	SI32	siInstant;
	SI32	siDelay;
	SI32	siAtb;
	SI32	siEffectFont;
	SI32	siTransMode;
	SI08	siAlphaValue;

	SI32	siShadowAni;
	SI32	siShadowFont;

	SI32	siShadowXIndent;
	SI32	siShadowYIndent;

	DWORD dwLastUseClock;	// ���������� ���� �ð�. 

	TSpr* pSpr;

	cltCharAnimation(cltCharAnimationManager* pclAniMng);
	~cltCharAnimation();

	SI32 GetAniType() const;

	void Set(SI32 sianitype, BOOL dirswitch, SI32 framenumber, TCHAR* filename,
			 SI32 font, SI32 instant, SI32 delay, SI32 atb, SI32 EffectFont ,SI32 transmode = 0,
			 SI08 alphavalue = 0 , SI32 ShadowAni = 0 ,SI32 ShadowFont = 0 );

	// �̹����� ���� ���� ����� ���Ѵ�. 
	SI32 GetImageXsize(DWORD currentclock);
	SI32 GetImageYsize(DWORD currentclock);

	// ����� �̹����� �׷��� ������ ȹ���Ѵ�. 
	void DecideDrawImg(SI32 dir, cltAniInfo claniinfo, DWORD currentclock, TSpr** ppSpr, int* return_font,
					   bool * return_reverseswitch, SI32 *psiEffectFont,
					   SI32 * psiShadowAni=0,SI32 * psiShadowFont=0);
	
	BOOL IsReady(SI32 step);

	void SetShadowIndentXY(SI32 psiX , SI32 psiY) ;
	void GetShadowIndentXY(SI32 * psiX , SI32 * psiY) ;

	SI32 GetFrameNum();

	// �̹����� �ε��Ѵ�. �̹� �ε��� ��쿡�� �ε����� �ʴ´�. 
	BOOL Load(DWORD currentclock);
};

//-------------------------------------------
// ĳ���� �ִϸ��̼��� �����ϴ� �޴���.
//-------------------------------------------
class cltCharAnimationManager{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<TCHAR*, MAX_IMG_FILE_PER_KIND>		pszFileName;
	NSafeTArray<TSpr*, MAX_IMG_FILE_PER_KIND>		pSpr;
#else
	TCHAR* pszFileName[MAX_IMG_FILE_PER_KIND];
	TSpr* pSpr[MAX_IMG_FILE_PER_KIND];	// �ִϸ��̼��� ������ ���� �̹��� ������ ����� 
#endif

#ifdef _SAFE_MEMORY
	NSafeTArray<cltCharAnimation*, MAX_ANINUM_PER_KIND>		pclCharAni;
#else
	cltCharAnimation*		pclCharAni[MAX_ANINUM_PER_KIND];
#endif

	cltCharAnimationManager();
	~cltCharAnimationManager();

	BOOL Add(SI32 Ani, BOOL DirSwitch, TCHAR* FileName, SI32 Font, SI32 Frame,
			 SI32 Instant, SI32 Delay, SI32 atb, SI32 EffectFont ,SI32 transmode = 0,SI08 alphavalue = 0 ,
			 SI32 ShadowAni = 0 , SI32 ShadowFont = 0 );
	BOOL DecideDrawImg(SI32 anitype, SI32 dir, cltAniInfo claniinfo, DWORD currentclock, TSpr** ppspr,
					   int* return_font, bool * return_reverseswitch, SI32 *psiEffectFont ,
					   SI32 * psiShadowAni=NULL,SI32 * psiShadowFont=NULL);

	BOOL GetDirSwitch(SI32 anitype);
	SI32 FindRefFromAnitype(SI32 anitype);

	SI32 FindFirstAni();
#ifdef _SAFE_MEMORY
	SI32 GetDelay(SI32 ref);
#else
	SI32 GetDelay(SI32 ref)		const;
#endif
	SI32 GetFrameNum(SI32 ref);
#ifdef _SAFE_MEMORY
	SI32 GetInstant(SI32 ref);
#else
	SI32 GetInstant(SI32 ref)	const;
#endif
	SI32 GetImageXsize(SI32 ref, DWORD currentclock );
	SI32 GetImageYsize(SI32 ref, DWORD currentclock );

	// ������ �ʴ� ������ �����Ѵ�. 
	void DeleteIfNotUse(DWORD curclock);

	BOOL SetShadowIndentXY(SI32 anitype ,SI32 psiX , SI32 psiY) ;
	void GetShadowIndentXY(SI32 anitype ,SI32 * psiX , SI32 * psiY) ;

	static SI32 siLodedSize;

};

#endif

