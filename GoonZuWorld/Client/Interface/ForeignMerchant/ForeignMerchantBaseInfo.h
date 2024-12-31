#ifndef _FOREIGNMERCHANTBASEINFO_H_
#define _FOREIGNMERCHANTBASEINFO_H_

#include <Directives.h>
#include <windows.h>

#include "..\..\..\Resource.h"

#include "..\..\..\Common\Item\ItemCommon\ItemUnit.h"
#include "..\..\..\Common\SystemNPC\ForeignMerchantNPC\ForeignMerchantNPC.h"
#include "..\..\..\CommonLogic\ImageList\ImageList.h"
#include "Msg\MsgType-NPC.h"
#include "..\..\FontManager\FontManager.h"
#include "..\..\Inventory\ItemInventoryBaseDefinition.h"

#define FOREIGNMERCHANTDLG_SETTIMER_TIME			1000

#define MAX_FOREIGN_MERCHANT_OBJ_NUM				30
#define MAX_FOREIGN_MERCHANT_OBJ_BUFFER_SIZE		128		// 128 byte �� ���


struct stForeignMerchantHeader
{
	UI16 uiMsg;
	UI16 uiSize;
};

struct stSellToForeignMerchant
{
	stForeignMerchantHeader sHeader;
	SI16					siForeignMerchantKind;		// ���� ����(�Ϻ� ����, û����)
	UI16					uiSelectedIndex;			// ������ ��ġ (�翬�� 10�̻��� ���̰���... ����â������ �ٷ� �ȼ� �����Ƿ�... )
	UI16					uiSellItemNum;				// ������ �Ǹ� ����
	SI16					siSellItemUnique;			// ������ ����ũ ��, <--- ������ ���輺 ������... �Ⱓ�� ������ �������� �ٸ� ���������� ����Ǵ� ���ȿ� ������ ��Ŷ�� ��쿡 ���� ���å
	
	SI32					siNPCCharUnique;			// NPC CharUnique

	stSellToForeignMerchant()
	{
		siForeignMerchantKind = 0;
		uiSelectedIndex = 0;
		uiSellItemNum = 0;
		siSellItemUnique = 0;
		siNPCCharUnique = 0;

		sHeader.uiMsg = SELL_TO_FOREIGNMERCHANT;
		sHeader.uiSize = sizeof( stSellToForeignMerchant );
	}
};

#endif