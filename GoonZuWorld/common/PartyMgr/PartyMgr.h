#ifndef _PARTYMGR_H_
#define _PARTYMGR_H_

#include "..\SMLib\LibList\LibListMgr.h"

#include "PartyBaseInfo.h"

class CPartyObj;
class CPartyMgr : public CLibListMgr
{
public:
	CPartyMgr();
	~CPartyMgr();

	void Initialize();
	void Destroy();

	void CreateMaxEmptyObj();

	void Action();

	SI32 CreateParty( SI32 PersonID, SI32 CharUnique, SI32 Level );			// ��Ƽ ��ȣ ����	
	//SI16 JoinParty( SI32 FromPersonID, SI32 CharUnique, SI32 PartyIndex );			// ��Ƽ ���ε� ��ġ ����( m_stPartyUserList[ index ], index ���� ���� )
	SI16 LeaveParty( SI32 PersonID, SI32 PartyIndex, SI32 *pRet );					// ��Ƽ���� ���� ��ġ ����( m_stPartyUserList[ index ], index ���� ���� )
	//SI16 ForceLeaveParty( SI32 FromPersonID, SI32 ToPersonID, SI32 PartyIndex );	// ��Ƽ���� ��Ƽ���� ���� ���� ��Ŵ


	CPartyObj *GetPartyObj( SI32 PartyIndex );

	// ��Ƽ��ȣ�� ��Ƽ������ Ȯ��
	bool IsPartyLeader( SI32 FromPersonID, SI32 PartyIndex );

	// ��Ƽ��ȣ�� ��Ƽ �ɹ����� Ȯ��
	bool IsPartyMember( SI32 siPersionID, SI32 siPartyIndex );


	// ��Ƽ�� ������ �� �߰��Ҽ� �ִ��� Ȯ��
	bool IsEmptyUserListExist( SI32 PartyIndex );

	void DeleteParty( CPartyObj *pObj );

	UI32 GetPartyNum();
	UI32 GetPartyTotalUserNum();

	void IncreaseExp( SI32 PartyIndex, SI32 PersonID, SI32 Exp );

	// [����] ������ : ��Ƽ�δ����� ��Ƽ�� �����Ǿ��� ��� ���縮���� ������Ų��
	void InPartyDungeonDeleteParty( SI32 siCharID );

	// [����] siPartyIndex�ɹ��� siClearCondition ����Ʈ�� �ϰ��ִ� ������ ���� ����
	SI32 CountQuestPalyUserNum( SI32 siPartyIndex, SI32 siClearCondition );

private:

};


#endif