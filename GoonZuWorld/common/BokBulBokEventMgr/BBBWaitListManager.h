//===================================================================================================
// ����	 : ���Һ� �̴ϰ���
// ����ġ: Switch_BokBulBok
// ����	 : ���Һ� ���ฮ��Ʈ�� ������ �޴���.
// �ۼ���: 2009.08.10
// �ۼ���: ������
//===================================================================================================

#ifndef _BBBWAITLIST_MANANGER_H_
#define _BBBWAITLIST_MANANGER_H_


#include "../../Common/CommonHeader.h"
#include <list>





#define MAX_RESERVATION_NUM	30	// �ִ� ���డ�� ��
#define MAX_CHARACTER_NAME_LENGTH	20		// ĳ���� �̸� �ִ����



struct _BBBWaitUserData
{
	SI32 siUserID;
	TCHAR szUserName[MAX_CHARACTER_NAME_LENGTH];
	//SI32 siPersionID;

	// ��Ÿ ���ฮ��Ʈ�� �߰��� �ð� ���� �����Ҽ���..

};


class CBBBWaitListManager
{
public:
	CBBBWaitListManager(void);
	~CBBBWaitListManager(void);

	// ��⸮��Ʈ ����
protected:
	typedef std::list< _BBBWaitUserData > WAITLIST;

	WAITLIST m_WaitList;										// ����ڸ���Ʈ
	WAITLIST::iterator m_WLitr;									// ��⸮��Ʈ���� �� ���ͷ�����

	DWORD m_dwWaitListRefreshTime;								// ���� ��⸮��Ʈ ���� �ð�

public:
	//SI16 GetWaitLength();										// ���� ������� ����� �� ����
	bool IsFull();												// ��⿭�� ��á���� üũ (30�� Ǯ����..)

    bool AddUser(SI32 siUserID, TCHAR* pszUserName = NULL);		// ���ฮ��Ʈ�� �߰�
	void RemoveUser(SI32 siUserID);								// ���ฮ��Ʈ���� ����

	void GetWaitList(_BBBWaitUserData* pWaitList);				// ����� ����Ʈ�� ��´�.
	void SubAction();											// �� ��ȯ �������� ���Ŵ����� �ؾ� ���� ó��

	bool WaitUserExist();										// ��⸮��Ʈ�� ������� ������ �ִ��� Ȯ��
	void Send_EnterMapQuestion();								// 1���� ����ڿ��� �ʿ� �����Ұųİ� ��Ŷ ����
	SI32 Get1stUserID();

public:
	bool _AlreadyExist(TCHAR* pszUserName);						// ��⸮��Ʈ�� �̹� �����ϴ� �������� Ȯ��
	void _Refresh_UserList();									// ����� ����Ʈ�� ��ȿ���� ���� ������ ã�Ƽ� ����
};

#endif