#include "NBillProtocol.h"
#include "NBillMsg.h"
#include <atlenc.h>

NBillProtocol::NBillProtocol()
{

	m_hModule = LoadLibrary( "gb.dll" );

	if( m_hModule ) {
		m_pMyFunc = (pDllFunc)GetProcAddress( m_hModule, "EncryptBill" );
	}

}


NBillProtocol::~NBillProtocol()
{
	if( m_hModule ) FreeLibrary( m_hModule );
	m_hModule = NULL;
}


void NBillProtocol::Init()
{

	m_SF.CreateFactory( GetSessionManager(), MAX_GAMESERVER_CONNECTION, 1000 * 1000, 1000 * 1000 );

	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), 3800 );

}


void NBillProtocol::SessionProc( ITZSession *pSession )
{
	cGame *pPerson;

	pPerson = (cGame *)pSession->GetPerson();

	// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
	sPacketHeader *pPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );

	if( pPacket == NULL ) return;										// ��Ŷ�� ������ ������	

	// ��Ŷ Ŀ�ǵ忡 ���� ó��
	switch( pPacket->usCmd ) {

	case BILLMSG_REQUEST_ENCRYPTIDPW:
		{
			NBillRequest_EncryptIDPW* pclinfo	= ( NBillRequest_EncryptIDPW * )pPacket;

			char ret[ 1024 ];

			if( m_pMyFunc )
			{								
				m_pMyFunc( 0, pclinfo->m_szID, pclinfo->m_szPW, ret );
				
				NBillResponse_EncryptIDPW clinfo(pclinfo->m_charid,pclinfo->m_personid,ret);
				
				pSession->GetSendBuffer()->Write( (BYTE*)&clinfo );
			}
		}
		break;

	case BILLMSG_REQUEST_ENCRYPTIDPW_WEB:
		{
			NBillRequest_EncryptIDPW_Web* pclinfo	= ( NBillRequest_EncryptIDPW_Web * )pPacket;

			char ret[ 1024 ];

			if( m_pMyFunc )
			{								
				m_pMyFunc( 1, pclinfo->m_szID, pclinfo->m_szPW, ret );

				NBillResponse_EncryptIDPW_Web clinfo(pclinfo->m_charid,pclinfo->m_personid, pclinfo->m_szUrl, ret );

				pSession->GetSendBuffer()->Write( (BYTE*)&clinfo );
			}
		}
		break;
	case BILLMSG_REQUEST_ENCRYPTIDPW_GACHA:
		{
			NBillRequest_EncryptIDPW_Gacha* pclinfo	= ( NBillRequest_EncryptIDPW_Gacha * )pPacket;

			char ret[ 1024 ];

			if( m_pMyFunc )
			{								
				m_pMyFunc( 2, pclinfo->m_szID, pclinfo->m_szPW, ret );

				NBillResponse_EncryptIDPW_Gacha clinfo(pclinfo->m_charid,pclinfo->m_personid, ret );

				pSession->GetSendBuffer()->Write( (BYTE*)&clinfo );
			}
		}
		break;
	}

	pSession->GetRecvBuffer()->RemoveFirstPacket();
}


void NBillProtocol::Update()
{

}
