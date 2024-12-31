//===================================================================================================
// ����	 : ���Һ� �̴ϰ���
// ����ġ: Switch_BokBulBok
// ����	 : ���Һ� ���� ������ �޴���.
// �ۼ���: 2009.08.10
// �ۼ���: ������
//===================================================================================================

#ifndef _BBBEVENTMAP_MANAGER_H_
#define _BBBEVENTMAP_MANAGER_H_


#include "../../Common/CommonHeader.h"
#include "BBBEventMap.h"
#include <vector>

#define MAX_MAP_COUNT		4
//#define MAX_MAP_COUNT		1	 //test


class CBBBEventMapManager
{
public:
	CBBBEventMapManager(void);
	~CBBBEventMapManager(void);

	// �ܺ� �������̽�
public:
    bool IsFull();
	SI16 AddUser(SI32 siPersonID, TCHAR* pszCharName);
	void RemoveUser(SI32 siPersonID);
	void SubAction();

	void StageFail(SI32 siPersonID);
	void StageClear(SI32 siPersonID);

	void SetTemporaryReserve(SI32 siPersonID);
	void ActiveTemporaryReserve(SI32 siPersonID);
	void CancelTemporaryReserve(SI32 siPersonID);

	void SetPlayTime(SI32 siPlayTime);

	// ���� ���
protected:
	typedef std::vector<CBBBEventMap*> MAPLIST;

	MAPLIST m_MapList;
	MAPLIST::iterator m_MLitr;
};

#endif