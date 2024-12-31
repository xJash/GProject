#ifndef __PorteAuthForClient__
#define __PorteAuthForClient__

#ifdef PORTEAUTHFORCLIENT_EXPORTS
#define PAUTH_API __declspec(dllexport)
#else
#define PAUTH_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib, "PorteAuthForClientD.lib") 
#else
#pragma comment(lib, "PorteAuthForClient.lib") 
#endif
#endif

namespace Porte {
	namespace PorteAuthSystem {

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

		// predefine size
		// usage at game client code
		///////////////////////////////////////////////////////////////////
		#define SIZE_AUTHTICKET			2048
		#define SIZE_USERID				21
		#define SIZE_GAMEID				11
		#define SIZE_GAMEINFOSTRING		4096
		///////////////////////////////////////////////////////////////////

		// service code
		///////////////////////////////////////////////////////////////////
		// nation service code
		#define SERVICE_NATION  0x000000FF	// mask of nation service code
		#define SERVICE_KOR		0x00000001
		#define SERVICE_USA		0x00000002
		#define SERVICE_JPN		0x00000003
		#define SERVICE_CHN		0x00000004

		// stage service code
		#define SERVICE_STAGE   0x00000F00	// mask of stage service code
		#define SERVICE_ALPHA	0x00000100
		#define SERVICE_REAL	0x00000200
		#define SERVICE_BETA	0x00000300

		// idc service code
		#define SERVICE_IDC		0x0000F000	// mask of idc service code
		#define SERVICE_IDC01	0x00001000
		#define SERVICE_IDC02	0x00002000
		#define SERVICE_IDC03	0x00003000
		#define SERVICE_IDC04	0x00004000
		#define SERVICE_IDC05	0x00005000
		#define SERVICE_IDC06	0x00006000
		#define SERVICE_IDC07	0x00007000
		#define SERVICE_IDC08	0x00008000
		#define SERVICE_IDC09	0x00009000
		#define SERVICE_IDC10	0x0000A000
		#define SERVICE_IDC11	0x0000B000
		#define SERVICE_IDC12	0x0000C000
		#define SERVICE_IDC13	0x0000D000
		#define SERVICE_IDC14	0x0000E000
		#define SERVICE_IDC15	0x0000F000
		#define SERVICE_IDCNONE	0x00000000
		///////////////////////////////////////////////////////////////////


		/* error code
		Return value Info:
		 0 : OK
		 - : fault from function / this system 
		///////////////////////////////////////////////////////////////////
		*/
		#define	ERR_OK						 0	// ����
		#define ERR_UNEXPECTED				-1	// ����ġ ���� ����
		#define ERR_INVALIDARGUMENT			-2	// argument�� NULL�� ���(ex. Game Info String�̳� Out buffer�� NULL�ΰ�� ������ ������)
		#define ERR_ISNOTINITED				-3	// ����� Init�Ǿ� ���� ����. (PubAuthInit�� ȣ������ �ʾҰų� �����Ѱ��)
		#define ERR_ALREADYINITED			-4	// PubAuthInit, PubSetEventCallBack API�� �ι�° ȣ���� ��� �̹� Init�Ǿ� ������ �˸�
		#define ERR_INITFAIL				-5	// init ����. GameInfoString�� ������ ȯ��(ServiceCode)���� �ʱ�ȭ ����
		#define ERR_GAMEINFOSTRINGELEMENT	-6	// Game Info String�� ������ Ʋ��(!= GAMEINFOSTRING_EMELENTCOUNT)
		#define ERR_STARTREFRESH			-7	// refresh ������ ����
		#define ERR_GAMEINFOSTRINGFORMAT	-8	// Game Info String�� ���� ���ڰ� PARAM_CHECK_FLAG���ڿ� �������� ���� ��� �߻�
		#define ERR_SMALLBUFFER				-9	// buffer������ ���� ����
		#define ERR_NO_USERID				-10	// User ID�� �������. �� �α��� ������ �����

		#define ERR_UNKNOWNCALLBACK			-20	// callback �Լ� ��� ����(����� __stdcall�� ������ ��)
		///////////////////////////////////////////////////////////////////

		/* EVENT CALLBACK : pState
		Return value Info:
		 0 : OK
		 - : error message
		 + : information or state
		///////////////////////////////////////////////////////////////////
		*/
		enum PORTE_EVENT_STAT { EVENT_TRACE, EVENT_INFO, EVENT_WARNING, EVENT_ERROR, EVENT_FATAL};

		// EVENT CALLBACK : pEventCode
		#define PORTE_AUTH_REFRESH					 10			// Auth TICKET�� ���������� Refresh�Ǿ���
		#define PORTE_AUTH_BROKENDATA				-30			// ���� Data�� ����(MSGID�� ����)
		#define PORTE_AUTH_WRONGMSGID				-31			// ������ MSGID�� �ƴ�( = RefreshMessagID)

		#define PORTE_AUTH_CONNECT_FAIL				-40			// ���������� ������ ������ ���. 1�� �� �ٽ� ����
		#define PORTE_AUTH_DESTROY					-41			// ���������� ������ ���������� 4�� ������ ��� ���� �����带 �����Ѵ�.

		// auth server return message
		///////////////////////////////////////////
		#define PORTE_AUTH_SUCCESS					  0			// �����δ� ���޵��� ������. PORTE_AUTH_REFRESH Event Code�� ��ü��
		#define	PORTE_AUTH_FAIL						 -1			// Auth TICKET Refresh ����

		#define PORTE_AUTH_TICKET_TIMEOVER			-10			// Auth TICKET�� ��ȿ�ð��� �������
		#define PORTE_AUTH_TICKET_DIFF_IP			-11			// Auth TICKET�� ��ϵ� Client IP�� Refresh�� �õ��ϴ� Client IP�� �ٸ�
		#define PORTE_AUTH_TICKET_DIFF_ID			-12			// Auth TICKET�� ��ϵ� User ID�� Refresh�� �õ��ϴ� User ID�� �ٸ�
		#define PORTE_AUTH_TICKET_WRONG_FORMAT		-13			// Auth TICKET�� �׸��� ������ Ʋ�����
		#define PORTE_AUTH_UNKONWN_CLIENT_IP		-14			// Refresh�� �õ��ϴ� Client IP�� �� �� ���� ���(����� IP�� Connection�� ���� �ľ�)

		#define PORTE_AUTH_TICKET_MAKEKEY_FAIL		-20			// Auth TICKET ��ȣȭ KEY ���� ����
		#define	PORTE_AUTH_TICKET_ENCRYPT_FAIL		-21			// Auth TICKET�� ��ȣȭ ����
		#define	PORTE_AUTH_TICKET_DECRYPT_FAIL		-22			// Auth TICKET�� ��ȣȭ ����
		#define	PORTE_AHTH_TICKET_INVALID			-23			// ���� ���̱� ������ ũ�⸦ �ʰ���
		///////////////////////////////////////////
		///////////////////////////////////////////////////////////////////

		// Event CallBack Function Format
		typedef void(__stdcall *TPAuthEvent) (PORTE_EVENT_STAT pStat, int pEventCode, const char* pMessage, void *pContext);

#if defined(__cplusplus)
		extern "C"{
#endif

		// Init client module
		PAUTH_API int __stdcall PubAuthInit(IN const char* szGameInfoString,
										    IN const char* szUserLocation);
		// set event callback function
		PAUTH_API int _stdcall PubSetEventCallBack(IN TPAuthEvent pFunc,
												   IN void* pUserContext);
		// modify user location
		PAUTH_API int __stdcall PubSetUserLocation(IN const char* szUserLocation);

		// get updated game info string
		PAUTH_API int __stdcall PubGetUpdatedGameInfoString(OUT char *szGameInfoString, 
														    IN  unsigned int nSize);
		// stop refresh auth ticket
		PAUTH_API int __stdcall PubStopRefresh();

		// get auth ticket
		PAUTH_API int __stdcall PubGetAuthTicket(OUT char *szTicket, 
												 IN  unsigned int nSize);
		// get user ID
		PAUTH_API int __stdcall PubGetUserID(OUT char *szUserID,
											 IN  unsigned int nSize);
		// get game ID
		PAUTH_API int __stdcall PubGetGameID(OUT char *szGameID,
											 IN  unsigned int nSize);
		// get service code
		PAUTH_API int __stdcall PubGetServiceCode ();

		// get nation service code
		PAUTH_API int __stdcall PubGetNationServiceCode ();

		// get stage service code
		PAUTH_API int __stdcall PubGetStageServiceCode ();

		// get idc service code
		PAUTH_API int __stdcall PubGetIDCServiceCode ();

		// get game info url
		PAUTH_API int __stdcall PubGetGameInfoUrl(OUT char *szGameInfoUrl,
												  IN  unsigned int nSize);
		// get cookie in game info string
		PAUTH_API int __stdcall PubGetCookie(OUT char *szCookie,
											 IN unsigned int nSize);
		// get CP cookie in game info string
		PAUTH_API int __stdcall PubGetCPCookie(OUT char *szCPCookie,
											IN unsigned int nSize);
		// get value of key in game info string
		PAUTH_API int __stdcall PubGetValue(IN  char *szKeyName,
											OUT char *pBuffer,
											IN  size_t nSize);
#if defined(__cplusplus)
		}
#endif

	}
}
#endif // __PorteAuthForClient__