//---------------------------------
// 2004/5/19 ���°�
//---------------------------------

#include "..\CharManager\CharManager.h"

#include "..\Common\Order\Order.h"

#include "..\..\Client\Client.h"
#include "..\..\Server\Server.h"

//-------------------------------------
// CommonLogic 
//-------------------------------------
#include "..\..\CommonLogic\MsgType-Person.h"

extern cltCommonLogic* pclClient;

// �̺�Ʈ ĳ���ͷ� �����Ѵ�. 
void cltCharCommon::SetEventChar(SI32 eventindex, bool bmode)
{
	switch(eventindex)
	{
	case 1:	clInnerStatus.clEventInfo.bEvent1Switch = bmode;	break;
	case 2:	clInnerStatus.clEventInfo.bEvent2Switch = bmode;	break;
	case 3:	clInnerStatus.clEventInfo.bEvent3Switch = bmode;	break;
	case 4:	clInnerStatus.clEventInfo.bEvent4Switch = bmode;	break;
	case 5:	clInnerStatus.clEventInfo.bEvent5Switch = bmode;	break;
	case 6:	clInnerStatus.clEventInfo.bEvent6Switch = bmode;	break;
	case 7:	clInnerStatus.clEventInfo.bEvent7Switch = bmode;	break;
	}

	if(bmode == true)
	{
		
		// ������ �̺�Ʈ ������ ���� �浹 ������ �缳���Ѵ�. 
		SetBlock();
		
		// Ŭ���̾�Ʈ�� �̿����� �뺸�Ѵ�. 
		cltGameMsgResponse_EventInfo clInfo(GetID(), &clInnerStatus.clEventInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_EVENTINFO, sizeof(clInfo), (BYTE*)&clInfo);
		SendNetMsg((sPacketHeader*)&clMsg);
		((cltCharServer*)this)->SendNeighbourMsg(&clMsg, false);
	}
	else
	{
		
		// ������ �̺�Ʈ ������ ���� �浹 ������ �缳���Ѵ�. 
		SetBlock();
		
		// Ŭ���̾�Ʈ�� �̿����� �뺸�Ѵ�. 
		cltGameMsgResponse_EventInfo clInfo(GetID(), &clInnerStatus.clEventInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_EVENTINFO, sizeof(clInfo), (BYTE*)&clInfo);
		SendNetMsg((sPacketHeader*)&clMsg);
		((cltCharServer*)this)->SendNeighbourMsg(&clMsg, false);
	}
}
