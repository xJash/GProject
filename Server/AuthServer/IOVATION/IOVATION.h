// 다음 ifdef 블록은 DLL에서 내보내기하는 작업을 쉽게 해 주는 매크로를 만드는 
// 표준 방식입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 IOVATION_EXPORTS 기호로
// 컴파일되며, 동일한 DLL을 사용하는 다른 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 들어 있는 다른 모든 프로젝트에서는 
// IOVATION_API 함수를 DLL에서 가져오는 것으로 보고,
// 이 DLL은 해당 매크로로 정의된 기호가 내보내지는 것으로 봅니다.
#ifdef IOVATION_EXPORTS
#define IOVATION_API extern "C" __declspec(dllexport)
#else
#define IOVATION_API __declspec(dllimport)
#endif

IOVATION_API int Init_IOVATION(const char* pszSubScriberID, const char* pszAdminCode, const char* pszAdminPassword, const char* pszType);
IOVATION_API int Shutdown_IOVATION(void);

IOVATION_API int CheckTransantion(const char* pszURL, const char* pszID, const char* pszBlackBox, const char* pszIP);
IOVATION_API const char* GetLastErrorString();

IOVATION_API const char* GetReasonString();
IOVATION_API const char* GetDeviceAliasString();
IOVATION_API const char* GetTrackingNumberString();

enum
{
	IOVATION_RESULT_ERROR = 0,
	IOVATION_RESULT_ALLOW,
	IOVATION_RESULT_DENY,
	IOVATION_RESULT_REVIEW,
};