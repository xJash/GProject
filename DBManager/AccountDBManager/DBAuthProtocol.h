#ifndef _DBAUTHPROTOCOL_H
#define _DBAUTHPROTOCOL_H

#include "AccountDB.h"
#include "ITZNetworkThread.h"

class DBAuthProtocol : public ITZNetworkThread
{
public:
	DBAuthProtocol();
	~DBAuthProtocol();

public:
	void			Init( UI16 usPort, char *szDBIP, char *szDatabase, char *szUserID, char *szUserPW );

	virtual void	Update();
	virtual void	SessionProc( ITZSession *pSession );

private:
	ITZSessionFactory< cAuth >	m_SF;
	
//#ifdef USE_DBGW
//	DBGW						m_odbc;
//#else
	RichODBC					m_odbc;
//#endif
	char						m_szSPName[ 512 ];

	void Convert_SYSTEMTIME_from_TIMESTAMP(_SYSTEMTIME *stST, TIMESTAMP_STRUCT *stTS);
	void Convert_TIMESTAMP_from_SYSTEMTIME(TIMESTAMP_STRUCT *stTS, _SYSTEMTIME *stST);

public:
	// ��ǥ ���� �Լ�
	void Statistics_UserCount(SYSTEMTIME stTime);			// 1. ��������
	void Statistics_UserInfo(SYSTEMTIME stTime);			// 2. �̿��� ����
	void Statistics_TotalUserLevel(SYSTEMTIME stTime);		// 3. ��ü �̿��� ������ ����
	void Statistics_WeekUserLevel(SYSTEMTIME stTime);		// 4. �ְ� �̿��� ������ ����
	void Statistics_NewUserLevel(SYSTEMTIME stTime);		// 5. �ű԰� ������ ����
	void Statistics_ActiveUserLevel(SYSTEMTIME stTime);		// 6. ��Ƽ���̿��� ������ ����
	void Statistics_TotalUserAgeGender(SYSTEMTIME stTime);	// 7. ��ü �̿��� ���� �� ���� ����
	void Statistics_WeekUserAgeGender(SYSTEMTIME stTime);	// 8. �ְ� �̿��� ���� �� ���� ����
	void Statistics_NewUserAgeGender(SYSTEMTIME stTime);	// 9. �ű� �� ���� �� ���� ����
	void Statistics_ActiveUserAgeGender(SYSTEMTIME stTime);	// 10. ��Ƽ�� �̿��� ���� �� ���� ����
};


#endif
