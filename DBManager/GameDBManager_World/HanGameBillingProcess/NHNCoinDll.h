// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� NHNCOINDLL_EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// NHNCOINDLL_API �Լ��� DLL���� �������� ������ ����,
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef NHNCOINDLL_EXPORTS
#define NHNCOINDLL_API __declspec(dllexport)
#else
#define NHNCOINDLL_API __declspec(dllimport)
#endif


class NHNCoin;


extern "C" NHNCOINDLL_API NHNCoin* __cdecl CreateNHNCoinInstance(const char *serverIP, unsigned short serverPort, unsigned int timeout = -1);


// �� Ŭ������ NHNCoinDll.dll���� ������ ���Դϴ�.
class NHNCoin 
{
public:
	enum RET_CODE
	{
		RET_OK,					// ����
		RET_ERR_INVALID_PARAM,	// �Ķ���� ����
		RET_ERR_NETWORK,		// ��Ʈ��ũ ���
		RET_ERR_SERVER,			// ���� ���� ���
		RET_ERR_NO_DATA,		// QueryCoin()���� �ش� ����� ������ ����
	};

	/**
	 * @brief constructor
	 * @param serverIP SQLMap���� IP�ּ�
	 * @param serverPort SQLMap���� ��Ʈ
	 * @param timeout SQLMap������ ���� ��� �ð�
	 */
	NHNCoin(const char *serverIP, unsigned short serverPort, unsigned int timeout = -1);

	/**
	 * @brief destructor
	 */
	virtual ~NHNCoin();

	/**
	 * @brief ����� ����Ʈ�� ��ȸ
	 * @param id [IN] ����� ���̵�
	 * @param idno [IN] ����� ��ȣ
	 * @param rtn [OUT] ó�� ��� �ڵ� (0: ����, �� �ܴ� ����)
	 * @param msg [OUT] ���� �޽��� (Max 1024bytes)
	 * @param totbal [OUT] ���ܾ� ( chrgbal+inevtbal+outevtbal+giftbal)
	 * @param chrgbal [OUT] ���� �����ܾ�
	 * @param inevtbal [OUT] �����̺�Ʈ �ܾ�
	 * @param outevtbal [OUT] �ܺ� �̺�Ʈ �ܾ�
	 * @param giftbal [OUT] �������� �ܾ�
	 */
	virtual RET_CODE queryCoin(const char *id, const char *idno, int *rtn, char *msg, int *totbal, int *chrgbal, int *inevtbal, int *outevtbal, int *giftbal);

	/**
	 * @brief ����� ����Ʈ ����
	 * @param id [IN] ����� ���̵�
	 * @param idno [IN] ����� ��ȣ
	 * @param prodkind [IN] ��ǰ �з� �ڵ�
	 * @param prodcode [IN] ��ǰ �ڵ�
	 * @param snm [IN] ��ǰ �̸�
	 * @param samt [IN] ��ǰ ����
	 * @param refkey [IN] �ֹ���ȣ (Max 20byte)
	 * @param ip [IN] ����� ������ �ּ�
	 * @param sid [OUT] �����ֹ��ڵ� (Max 20byte)
	 * @param rtn [OUT] ó�� ��� �ڵ� (0: ����, �� �ܴ� ����)
	 * @param bal [OUT] ���� �ܾ�
	 * @param msg [OUT] ���� �޽���
	 */
	virtual RET_CODE useCoin(const char *id, const char *idno, const char *prodkind, const char *prodcode, const char *snm, int samt, const char *refkey, const char *ip, char *sid, int *rtn, int *bal, char *msg);

	/**
	 * @brief ���� ���
	 * @param id [IN] ����� ���̵�
	 * @param idno [IN] ����� ��ȣ
	 * @param prodkind [IN] ��ǰ �з� �ڵ�
	 * @param prodcode [IN] ��ǰ �ڵ�
	 * @param snm [IN] ��ǰ �̸�
	 * @param samt [IN] ��ǰ ����
	 * @param refkey [IN] �ֹ���ȣ (Max 20byte)
	 * @param ip [IN] ����� ������ �ּ�
	 * @param sid [OUT] �����ֹ��ڵ� (Max 20byte)
	 * @param rtn [OUT] ó�� ��� �ڵ� (0: ����, �� �ܴ� ����)
	 * @param bal [OUT] ���� �ܾ�
	 * @param msg [OUT] ���� �޽���
	 */
	virtual RET_CODE useCoinGift(const char *id, const char *idno, const char *prodkind, const char *prodcode, const char *snm, int samt, const char *refkey, const char *ip, char *sid, int *rtn, int *bal, char *msg);

	/**
	 * @brief ����� ����Ʈ ������ ���
	 * @param id [IN] ����� ���̵�
	 * @param idno [IN] ����� ��ȣ
	 * @param prodkind [IN] ��ǰ �з� �ڵ�
	 * @param prodcode [IN] ��ǰ �ڵ�
	 * @param snm [IN] ��ǰ �̸�
	 * @param samt [IN] ��ǰ ����
	 * @param refkey [IN] �ֹ���ȣ (Max 20byte)
	 * @param ip [IN] ����� ������ �ּ�
	 * @param sid [OUT] �����ֹ��ڵ� (Max 20bytes)
	 * @param rtn [OUT] ó�� ��� �ڵ� (0: ����, �� �ܴ� ����)
	 * @param bal [OUT] ���� �ܾ�
	 * @param msg [OUT] ���� �޽���
	 */
	virtual RET_CODE cancelUse(const char *id, const char *idno, const char *prodkind, const char *prodcode, const char *snm, int samt, const char *refkey, const char *ip, char *sid, int *rtn, int *bal, char *msg);

private:
	RET_CODE _executeProcedure(const char *procedureName, const char *tcode, const char *id, const char *idno, const char *prodkind, const char *prodcode, const char *snm, int samt, const char *refkey, const char *ip, char *sid, int *rtn, int *bal, char *msg);

	char _ip[32];
	unsigned short _port;
	unsigned int _timeout;
};