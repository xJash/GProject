#include "ITZPerson.h"
#include "ITZNetworkThread.h"
#include "GMSectionData.h"


struct sGMRequest_UpdateData;
class cltCharServer;


class CGMProtocol_Updata
{
public:
	// �ɸ��� �⺻������ ���õ� ������ ��ȯ
	SI16	BasicInfoUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar );
	// ��ų�� ���õ� ������ ��ȯ
	SI16	SkillInfoUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar );
	// ����ǰ�� ���õ� ������ ��ȯ
	SI16	InventoryUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar );
	// �ε��꿡 ���õ� ������ ��ȯ
	SI16	RealestateUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar );
	// ��ȯ���� ���õ� ������ ��ȯ
	SI16	SummonUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar );
	// ������ ���õ� ������ ��ȯ
	SI16	AnimalUpdata( sGMRequest_UpdateData* pRecvMsg , SI32 siButtonID , cltCharServer* pclChar );

};