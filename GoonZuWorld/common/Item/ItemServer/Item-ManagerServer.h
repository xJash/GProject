//---------------------------------
// 2003/8/7 ���°�
//---------------------------------

#ifndef _ITEMMANAGERSERVER_H
#define _ITEMMANAGERSERVER_H

#include "..\ItemCommon\cltItem.h"

class cltCharServer;
class CSetItemManager;

class cltItemManagerServer : public cltItemManagerCommon{
public:

	//CSetItemManager* pclSetItemManager;	

	cltItemManagerServer(SI32 gamemode);
	~cltItemManagerServer();

	// KindInfo�� ������ ������ �ٰŷ� ������ �������� �ϳ� �����. 
	bool MakeRandItem(SI32 level, SI32 addrate, cltKindItemProbabilitySet* pclikinditem, cltItem* pclitem );

	// ��ü���� ���� ����Ʈ�� ���´�. 
	bool GetDismantleMaterial( cltCharServer* pclchar, cltItem clitem, cltItem* pclitemlist, SI16 *pMakePercent );

//	SI32 GetEnchantDamageFromGrade(SI32 siGrade);
};


#endif