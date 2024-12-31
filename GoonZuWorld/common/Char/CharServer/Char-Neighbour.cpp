#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"
#include "char\CharServer\Char-Server.h"
#include "..\Common\Bullet\Bullet.h"
#include "Util\Util.h"

#include "../../../Server/Server.h"

#include "ITZCell.h"
#include "ITZEncrypt.h"

extern cltCommonLogic* pclClient;

extern SI32 AttackAtbInfo[];


// ĳ���� �ֺ��� �̿� �����͸� �����Ѵ�. 
// ������ ��쿡�� �����Ѵ�.
// bmode == TRUE :  �ֺ��� �̿��� �����Ѵ�. 
// bmode == FALSE : �ֺ��� �̿��� ��� �����Ѵ�.  
BOOL cltCharServer::SetNeighbour()
{
	// ĳ���Ͱ� �̵������ν� ��ġ�� ����Ǹ� �̿� ������ �����ϰ� �ȴ�. 
	pclClient->pclMapManager->m_world.GetMap( GetMapIndex() )->MoveChar( GetX(), GetY(), this , false);
	return TRUE;
}

// �̿����� �޽����� ������. 
BOOL cltCharServer::SendNeighbourMsg(cltMsg* pclmsg, bool bselfswitch)
{
	ITZCell* pCell	= GetCell();
	if(pCell == NULL)return FALSE;

	cltServer* pclserver = (cltServer*)pclClient;
	EnterCriticalSection( &pclserver->m_cs_SendNetMsg );
	{
		UI32 uiCompSize = 0;
		BOOL bCompress = FALSE;
		BYTE* pbufComp = pclserver->m_bufComp;

		if( GetSession() &&
			pclserver->m_uiCompressMinSize > 0 && pclmsg->clHead.usSize >= pclserver->m_uiCompressMinSize )		// ������ ����Ʈ�̻� �����Ѵ�.
		{
			BYTE* pMsg = (BYTE*)pclmsg;
			memcpy(pbufComp, pclmsg, sizeof(sPacketHeader));
			uiCompSize = GetSession()->Compress( &pMsg[sizeof(sPacketHeader)],		pclmsg->clHead.usSize - sizeof(sPacketHeader),		// SOURCE
												 &pbufComp[sizeof(sPacketHeader)],	sizeof(pclserver->m_bufComp) - sizeof(sPacketHeader) );			// COMPRESS BUFFER
			if( uiCompSize > 0 )	
			{
				sPacketHeader* pCompMsg = (sPacketHeader*)pbufComp;
				pCompMsg->usSize = sizeof(sPacketHeader) + uiCompSize;

				// ��Ŷ ����� �ֻ��� ��Ʈ�� ��Ʈ�ϸ�, ��Ŷ�� ����� ���̴�.
				pCompMsg->usCmd |= 0x8000;
				bCompress = TRUE;
			}
		}

		if( bCompress == FALSE )
		{
			memcpy(pbufComp, pclmsg, pclmsg->clHead.usSize);
		}

		if(bselfswitch)
		{
			//pCell->SendPacketNearAll((sPacketHeader*)pclmsg);
			pCell->SendPacketNearAll( pbufComp );
		}
		else
		{
			//pCell->SendPacketExceptOne(this, (sPacketHeader*)pclmsg);
			pCell->SendPacketExceptOne( this, pbufComp );	// ��ȣȭ �� �����͸� ������.
		}
	}
	LeaveCriticalSection( &pclserver->m_cs_SendNetMsg );

	return TRUE;
}

BOOL cltCharServer::SendNeighbourExceptMeMsg(cltMsg* pclmsg)
{
	ITZCell* pCell	= GetCell();
	if(pCell == NULL)return FALSE;

	cltServer* pclserver = (cltServer*)pclClient;
	EnterCriticalSection( &pclserver->m_cs_SendNetMsg );
	{
		UI32 uiCompSize = 0;
		BOOL bCompress = FALSE;
		BYTE* pbufComp = pclserver->m_bufComp;

		if( pclserver->m_uiCompressMinSize > 0 && pclmsg->clHead.usSize >= pclserver->m_uiCompressMinSize )		// ������ ����Ʈ�̻� �����Ѵ�.
		{
			BYTE* pMsg = (BYTE*)pclmsg;
			memcpy(pbufComp, pclmsg, sizeof(sPacketHeader));
			uiCompSize = GetSession()->Compress( &pMsg[sizeof(sPacketHeader)],		pclmsg->clHead.usSize - sizeof(sPacketHeader),		// SOURCE
												 &pbufComp[sizeof(sPacketHeader)],	sizeof(pclserver->m_bufComp) - sizeof(sPacketHeader) );			// COMPRESS BUFFER
			if( uiCompSize > 0 )	
			{
				sPacketHeader* pCompMsg = (sPacketHeader*)pbufComp;
				pCompMsg->usSize = sizeof(sPacketHeader) + uiCompSize;

				// ��Ŷ ����� �ֻ��� ��Ʈ�� ��Ʈ�ϸ�, ��Ŷ�� ����� ���̴�.
				pCompMsg->usCmd |= 0x8000;
				bCompress = TRUE;
			}
		}

		if( bCompress == FALSE )
		{
			memcpy(pbufComp, pclmsg, pclmsg->clHead.usSize);
		}

		pCell->SendPacketNearAllExceptOne( this, pbufComp );
	}
	LeaveCriticalSection( &pclserver->m_cs_SendNetMsg );

	return TRUE;
}