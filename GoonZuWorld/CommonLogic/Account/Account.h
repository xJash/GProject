//---------------------------------
// 2003/6/18 ���°�
//---------------------------------

#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <Directives.h>


#include "..\..\Common\CommonHeader.h"


class cltAccount{
	
public:
	cltAccountNum	clAccountNum;
	SI32			siPersonID;		// ���� ���� PersonID
	SI32			siIdentity;		// ������Ʈ ���� �ĺ���. 

	cltAccount()
	{
		clAccountNum.Init();

		siPersonID		= 0;
		siIdentity		= 0;
	};

	cltAccount(cltAccountNum* pclaccountnumm, SI32 sipersonid )
	{
		clAccountNum.Set(pclaccountnumm);
		siPersonID		= sipersonid;
		siIdentity		= 0;

	}
	
	void Init()
	{
		clAccountNum.Init();
		siPersonID	= 0;
		siIdentity	= 0;

	}
	void Init(cltAccountNum* pclaccountnum, SI32 sipersonid)
	{
		clAccountNum.Set(pclaccountnum);
		siPersonID	= sipersonid;
		siIdentity = 0;

	}
};




#endif
