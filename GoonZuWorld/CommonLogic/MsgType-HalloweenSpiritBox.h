#ifndef __MSGTYPE_HALLOWEENSPIRITBOX_H__
#define __MSGTYPE_HALLOWEENSPIRITBOX_H__


//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"

#pragma once 

class cltGameRequest_HalloweenSpiritBox
{
public:
	SI32 m_siDelItemUinque;	// ������ ������ unique
	SI32 m_siAddItemUinque;	// �߰��� ������ unique

public:
	cltGameRequest_HalloweenSpiritBox(SI32 siDelItemUnique, SI32 siAddItemUnique)
	{
		ZeroMemory(this, sizeof(cltGameRequest_HalloweenSpiritBox));

		m_siDelItemUinque = siDelItemUnique;
		m_siAddItemUinque = siAddItemUnique;
	}
};

//class cltGameResponse_HalloweenSpiritBox
//{
//public:
//	cltGameResponse_HalloweenSpiritBox()
//	{
//		ZeroMemory(this, sizeof(cltGameResponse_HalloweenSpiritBox));
//	}
//};


#endif