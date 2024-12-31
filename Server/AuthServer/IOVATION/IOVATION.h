// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� IOVATION_EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// IOVATION_API �Լ��� DLL���� �������� ������ ����,
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
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