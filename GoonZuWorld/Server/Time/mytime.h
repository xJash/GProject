#ifndef _CLTTIME_H
#define _CLTTIME_H

#include <Directives.h>

#include "../../common/CommonHeader.h"

class cltTime{
protected:
	bool bDayChangedSwitch;			// ��¥�� ����Ǿ����� ����. 

public:

	cltDate clDate;

	cltTime();
	BOOL Action(bool bforcetimeswitch);
	
	// ��¥�� ����Ǿ��°� ?
	bool IsDayChanged(){return bDayChangedSwitch;}

};

#endif
