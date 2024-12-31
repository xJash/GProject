#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "Char\CharManager\CharManager.h"

#include "../Server/GZFtpMgr/GZFtpMgr.h"

void cltServer::DoMsg_GAMEMSG_GZFTP_PROTOCOL( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgGZFTPProtocol	*pclinfo	=	( cltGameMsgGZFTPProtocol* )pclMsg->cData;

	SI32	__id;

	if( pclinfo->personid_to == 0) 
	{
		// �������� ������ �޽����̴�.
		// �������� ���� ó���Ѵ�.

		if( pclCM->IsValidID( id ) == FALSE )						return;

		m_pclGZFtpMgr->DisaptchGZFtpMsg( ( cltCharServer*)pclCM->CR[ id ], pclinfo );
	}
	else
	{
		// ������ ��ε�ĳ���ø� ���ش�.
		if( ( __id = pclCM->GetIDFromPersonID( pclinfo->personid_to ) ) == 0 )
		{

			return;
		}


		if( pclCM->IsValidID( __id ) == FALSE )
		{
			return;
		}

		pclCM->CR[ __id ]->SendNetMsg( ( sPacketHeader* )pclMsg );
	}
};