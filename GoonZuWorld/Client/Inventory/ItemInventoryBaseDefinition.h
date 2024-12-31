#ifndef _ITEMINVENTORYBASEDEFINITION_H_H
#define _ITEMINVENTORYBASEDEFINITION_H_H

#include <Directives.h>
#include <commctrl.h> 
#include <stdio.h>

#include "..\..\Resource.h"
#include "..\..\Common\Item\ItemCommon\ItemUnit.h"

//------------------------------------------- �κ��丮 ��׶��� �̹��� 
#define MAX_ITEMDLG_BACKGROUND_BITMAP_NUM	2

#define MAX_BUFFER_INVENTORY_SIZE			384

#define	INVENTORY_SETTIMER_VALUE			1000

//------------------------------------------- ���� ������
#define MAX_TOOLTIP_WIDTH					150

//------------------------------------------- ������ �̹��� ������
#define	ITEM_IMAGE_WIDTH					48
#define ITEM_IMAGE_HEIGHT					48

//------------------------------------------- 
#define	MAX_IMAGELIST_NUM					100			// �̹��� ����Ʈ�� ����ϴ� �ִ� ����


//------------------------------------------- ������ ���� �ִ� ����
#define	MAX_TOOLTIP_LENGTH					200


//------------------------------------------- �κ��丮�� ���Ǵ� �޽�����
#define	INV_MOVE_ITEM						20000		// ������ �̵��� si32lParam ���� LOWORD �� ������ �κ��丮 �̰�, HIWORD�� ��ǥ�ϴ� �κ��丮 �̴�.
#define	INV_USE_ITEM						20001


// si32lParam = ������ ��ġ, clMoveItem = ������
#define	INV_REPAIR_ITEM						20002		// ������ ����

#define	INV_DROP_ITEM						20003

#define	INV_MOUNT_ITEM						20004		// ���� Ŭ���ÿ� ������ ���� �� ����


// si32lParam �� ���� ���� �������� index, lParam1 �� ���� ����
#define	INV_MAKE_ITEM						20005		// �κ��丮 ������ ������ ����ÿ� 

#define INV_ADD_ITEM						20006		// �κ��丮 ������ �������� ��ħ

#define INV_USE_NOTIFY_MSG_ITEM				20007		// ���� �޽��� �������� ����Ѵ�.

#define	INV_CHANGE_ITEM						20008       //�κ��� ������ �ٲٱ� 

#define INV_CANCELLATIONSEALINGUP_ITEM		20009		// �к� ������ �����ϱ�

#define	INV_ENCHANT_ITEM					20010		// ��æƮâ���� ��æƮ�ϱ�(by taeyang)

#define INV_SPLIT_ITEM						20011		// ������ �и�

struct stMoveData
{
	SI16	si16Message;
	SI32	si32lParam;
	SI32	si32lParam1;								// ����
	SI16	si16lParam2;								// ����ũ
	cltItem clMoveItem;	
};

struct stUseNotifyMsg
{
	SI16	si16Message;
	TCHAR	strNotifyMsg[ 256 ];						// ���� �޽���.
};

struct	stImageList					// �̹��� ����Ʈ�� ����� �����ϱ� ���ؼ�...
{
	bool	bImageStatus;			// �̹����� ���ִ� ����
	SI32	si32Index;
	SI32	si32ItemUnique;

	stImageList()
	{
		memset( this, 0, sizeof( stImageList ) );
	}
};

#endif