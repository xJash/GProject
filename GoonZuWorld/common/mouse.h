#ifndef _MOUSE_H
#define _MOUSE_H   1

#include <directives.h>
 
#include <ddraw.h>

// ���콺�� ���� 
#define MOUSE_ATTACK         1
#define MOUSE_NORMAL         2
#define MOUSE_CHAR           3
#define MOUSE_HEAL           4
#define MOUSE_HARVEST        5
#define MOUSE_RIDE           6
#define MOUSE_SCROLL_SOUTH   7
#define MOUSE_SCROLL_SW      8
#define MOUSE_SCROLL_WEST    9
#define MOUSE_SCROLL_NW     10
#define MOUSE_SCROLL_NORTH  11
#define MOUSE_SCROLL_NE     12
#define MOUSE_SCROLL_EAST   13
#define MOUSE_SCROLL_SE     14
#define MOUSE_SCROLL_SOUTH_X 15
#define MOUSE_SCROLL_SW_X   16 
#define MOUSE_SCROLL_WEST_X 17
#define MOUSE_SCROLL_NW_X   18 
#define MOUSE_SCROLL_NORTH_X 19
#define MOUSE_SCROLL_NE_X   20
#define MOUSE_SCROLL_EAST_X 21
#define MOUSE_SCROLL_SE_X   22
#define MOUSE_MAGIC         23
#define MOUSE_RESULT        24
#define MOUSE_INITMENU      25
#define MOUSE_EXTINGUISH    27
#define MOUSE_CHOOSEMISSION 28
#define MOUSE_SETGAME		29
#define MOUSE_PROVIDER		30
#define MOUSE_SESSION		31
#define MOUSE_CHOOSESCENARIO 32
#define MOUSE_BRIEFING      33
#define MOUSE_TRAINSPOT     34

//----------------------------------------
// ���콺 ������ ���� 
//----------------------------------------
#define MOUSEMODE_MOVE					0x1      // �̵������ϴ�.
#define MOUSEMODE_ATTACK				0x2      // ���콺 �ؿ� ���� �ִ�. 
#define MOUSEMODE_SELECTNPC				0x4		// NPC ���� .
#define MOUSEMODE_CHAR					0x8      // ���콺 �ؿ� ĳ���Ͱ� �ִ�. 
#define MOUSEMODE_OTHERUSER				0x10      // �ٸ� ����� 
#define MOUSEMODE_SELECTSTRUCTURE       0x20
#define MOUSEMODE_HEAL					0x40    // ġ�� �����Ѱ�?
#define MOUSEMODE_WARP					0x80
#define MOUSEMODE_PICKUPITEM			0x100
#define MOUSEMODE_CHARNPC				0x200	// ĳ���� NPC
#define MOUSEMODE_DESK					0x400	// �Ǽ����� å��. 
#define MOUSEMODE_FARM					0x800	// ��� ���� 
#define MOUSEMODE_MINE					0x1000	// ä�� ����

// ������� �Է� ����. 
class _InputDevice{
public:
	SI32	Mouse_X, Mouse_Y;						// ȭ��󿡼� ���콺�� �ִ� ��ǥ 
	BOOL	LeftPressSwitch;						// ���� ��ư�� ������ �ִ��� ���� 
	BOOL	LeftPressDoneSwitch;
	BOOL	RightPressSwitch;						// ������ ��ư�� ������ �ִ��� ���� 
	BOOL	RightPressDoneSwitch;
	BOOL    DoubleLeftPressSwich;
	BOOL    DoubleLeftPressDoneSwich;
	   
	
	BOOL	AltKeyPressSwitch ;						// altŰ�� ���ȴ��� ���θ� �˷��ִ� ���� 
	DWORD   PrevLeftUp1Clock, PrevLeftUp2Clock;		// ������ ���콺 ���� Ű�� ������ �ð�. 

};

void SetMouse(SHORT mousemode);
// ���콺�� �׷��ش�. 
void DrawMouse();
// ���콺�� �׷��ش�. 
void DrawMouse(LPDIRECTDRAWSURFACE7 surface);

void DetermineShowCursor(DWORD nhittest);
void ShowHardwareCursor(BOOL mode);

enum 
{
	VK_NONE = 0,
	VK_RELEASE,
	VK_PRESS,
	VK_REPEAT
};

void	ScanVKey();
void	SetVKeyState(int VirtKey);
int		GetVKeyState(int VirtKey);
DWORD	GetVKeyPressTime(int VirtKey);
BYTE	GetRecentVKey(int fClear=TRUE);
void	GetMousePos(HWND hwnd, LPPOINT lpPoint);

inline bool VKNone(int Key)		{ return (GetVKeyState(Key) == VK_NONE); }
inline bool VKRelease(int Key)	{ return (GetVKeyState(Key) == VK_RELEASE); }
inline bool VKPress(int Key)	{ return (GetVKeyState(Key) == VK_PRESS); }
inline bool VKRepeat(int Key)	{ return (GetVKeyState(Key) == VK_REPEAT); }

#endif
