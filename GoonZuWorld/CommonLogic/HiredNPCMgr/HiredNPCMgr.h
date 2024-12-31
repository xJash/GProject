#ifndef _HIREDNPCMGR_H
#define _HIREDNPCMGR_H

#include <Directives.h>

#define MAX_HIREDNPC_KIND_NUM							80

class cltHiredNPCPayInfo
{
public:
	cltHiredNPCPayInfo();
	~cltHiredNPCPayInfo();

	void					Init();
	
public:
	SI32					siNPCKind;						// NPC kind
	SI32					siTotalHiredNum;				// �ش� NPC�� ��ü �������� ���� �� ���� 
	GMONEY					siPayment;						// �޿�
};

class cltHiredNPCPayManager
{
public:
	cltHiredNPCPayManager();
	~cltHiredNPCPayManager();

public:
	void					Init();
	void					CalcPayment( int i );
	
	void					AddNPC( int npckind );
	void					DelNPC( int npckind );

	GMONEY					GetPayment( int npckind );
	
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHiredNPCPayInfo, MAX_HIREDNPC_KIND_NUM>		clHiredNPCPayInfo;
#else
	cltHiredNPCPayInfo		clHiredNPCPayInfo[ MAX_HIREDNPC_KIND_NUM ];		// NPC ������ ���� ����
#endif
	SI32					siTotalNPCNum;									// ���� ��ü NPC���� 
	SI32					siNPCKindNum;									// NPC���� 

};

#endif
