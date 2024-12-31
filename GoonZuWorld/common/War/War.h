#ifndef _WAR_H
#define _WAR_H

#include <Windows.h>
#include <Directives.h>

#include <DDraw.h>

#define MAX_WAR_UNIT	10

#define WAR_MIN_MON_NUMBER			20		// �� ���ϸ� 10��� ����. 

class cltWarUnit{
public:
	SI32 siKind;

	SI32 siNum;				// ���� �ֺ��� ���ð͵�
	SI32 siOtherNum;		// 4���⿡�� ���ܼ� ���ð͵�

	SI32 siRate;
	SI32 siBasicLevel;
	SI32 siRandLevel;

	SI32 siCurNum;
	SI32 siOtherCurNum;

	cltWarUnit()
	{
		siKind		= 0;
		siNum		= 0;
		siOtherNum  = 0;
		siRate		= 0;
		siBasicLevel= 0;
		siRandLevel	= 0;
		siCurNum	= 0;
		siOtherCurNum = 0;
	}

	cltWarUnit(SI32 kind, SI32 num, SI32 othernum, SI32 rate, SI32 curnum, SI32 othercurnum, SI32 basic, SI32 rand)
	{
		siKind		= kind;
		siNum		= num;
		siOtherNum	= othernum;
		siRate		= rate;
		siCurNum	= curnum;
		siOtherCurNum = othercurnum;
		siBasicLevel= basic;
		siRandLevel	= rand;
	}
};

//-----------------------------
// cltWarManager
//-----------------------------
class cltWarManager{
public:
	bool bWarSwitch ;	// ���� ������ �������ΰ�?
	bool bWarOsakaSwitch;	// ����ī ������ �����ؾ� �ϳ�?

	SI32		siTotalUnitNum;		// ��ü �����. 

	SI32		siCurUnitNum;		// ���� �����. 
	SI32		siPorterNum;		// ���� �����ִ� ���� �ֱ� ��. 
	SI32		siMadeNum;			// ������� ������� ��. 
	cltWarUnit clWarUnit[MAX_WAR_UNIT];
	SI32		siWatUnitNum;		// ����Ʈ�� �� ���� �ִ°�?
	SI32		siCasulty;			// ����� ����. 
	DWORD		uiLeftTime;			// ���� �ð�. (ms) 
	DWORD		dwWarStartClock;
	DWORD		dwWarOsakaClock;	// �ֱ� ����¸� �� ����ī ������ �����Ѵ�
	DWORD		dwNewWarUnitClock;	// 4���⿡ ���� �ֱ��� �ð�üũ~
	SI32		siLeftMon;			// ���� ���� ����.
	
	SI32		siPorterVillageUnique;	// ���� �ֱ��� ��ġ�� ����. 

	//------------
	// ��� 
	//------------
	bool bDrawSwitch;
	SI32 siDrawCmdFont;
	DWORD dwDrawStartClock;
	
	cltWarManager();
	~cltWarManager();

	// ������ ��ȹ�Ѵ�. 
	bool MakeWar(DWORD clock);
	// ���� ���͸� �߰��Ѵ�. 
	void AddWarMonNum(SI32 kind, SI32 monnum);

	
	// ������ ���� ���´�
	void WarEnd();

	// ���� �׼� (����) 
	void Action();
	
	void SendWarMsg(SI32 cmd, SI32 mapindex1, SI32 x1, SI32 y1, SI32 mapindex2, SI32 x2, SI32 y2,SI16 vill1, SI16 kill1, SI16 vill2, SI16 kill2, SI16 vill3, SI16 kill3, SI16 portervillageunique);
	

	void SetDraw(SI32 cmd);
	// ��Ȳ�� ǥ���Ѵ�. (Ŭ���̾�Ʈ) 
	void Draw(LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry);

};
#endif