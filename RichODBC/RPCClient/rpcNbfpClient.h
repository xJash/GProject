/**
* @file rpcNbfpclient.h
* @brief 
* @author rapool <chankyylee@nhncorp.com>
* @date $Date: 2006-05-10$
* @version $Revision: $
* $Id: $
*/


#ifndef __MEGA_RPC_INBFPCLIENT_H_3ED5B414_2D1A_40D8_AA8A_EF5223D32A95__
#define __MEGA_RPC_INBFPCLIENT_H_3ED5B414_2D1A_40D8_AA8A_EF5223D32A95__

#include "common.h"
#include "rpcInterface.h"


namespace mega {
/**
 * @addtogroup nbfpInterface
 * @{
 */

#ifndef NULL
#define NULL 0
#endif

#ifdef _AFXEXT
#define EXPORT_TAG __declspec(dllexport)
#else
#define EXPORT_TAG
#endif


class INBFPClient;


/**
 * @brief INBFPClient �ν��Ͻ� ��ü�� ����
 * @return ������ INBFPClient ��ü�� ������
 * @remark �ڵ����� addRef()�� ȣ��ǹǷ� ���� ȣ���� �ʿ䰡 ����
 * @remark !!! �� �� �Ŀ� �ݵ�� INBFPClient::release()�� ȣ���ؾ� �� !!!
 */
EXPORT_TAG INBFPClient* CreateNBFPClientInstance();


/**
 * @brief IVariant��ü�� ����
 * @return ������ IVariant ��ü�� ������
 * @remark �ڵ����� addRef()�� ȣ��ǹǷ� ���� ȣ���� �ʿ䰡 ����
 * @remark !!! ��� �Ŀ� �ݵ�� IVariant::release()�� ȣ���ؾ� �� !!!
 */
EXPORT_TAG IVariant* CreateVariantInstance();

/**
 * @brief IList��ü�� ����
 * @return ������ IList ��ü�� ������
 * @remark �ڵ����� addRef()�� ȣ��ǹǷ� ���� ȣ���� �ʿ䰡 ����
 * @remark !!! ��� �Ŀ� �ݵ�� IList::release()�� ȣ���ؾ� �� !!!
 */
EXPORT_TAG IList* CreateListInstance();

/**
 * @brief IMap��ü�� ����
 * @return ������ IMap ��ü�� ������
 * @remark �ڵ����� addRef()�� ȣ��ǹǷ� ���� ȣ���� �ʿ䰡 ����
 * @remark !!! ��� �Ŀ� �ݵ�� IMap::release()�� ȣ���ؾ� �� !!!
 */
EXPORT_TAG IMap* CreateMapInstance();


/**
 * @brief �⺻Ÿ�԰� IList, IMap�� IVariant�� �ڵ� ��ȯ���ִ� Ŭ����
 * @remark IVariant::setValue()���� �Ķ���� �ڵ� ����ȯ �뵵�θ� ����
 */
class EXPORT_TAG VariantBoxing
{
	public:
		VariantBoxing(bool value);
		VariantBoxing(int value);
		VariantBoxing(int64_t value);
		VariantBoxing(double value);
		VariantBoxing(nano::timeval &value);
		VariantBoxing(const char *value);
		VariantBoxing(const IVariant *value);
		VariantBoxing(const IList *value);
		VariantBoxing(const IMap *value);
		~VariantBoxing();

	public:
		IVariant* getIVariant() const;

		int addRef();
		int release();

	private:
		VariantBoxing(const void *value) {}

		IVariant *_iv;
		int _refcnt;
};


/**
 * @brief NBFPResult �������̽� Ŭ����
 */
class INBFPResult
{
	public:
		/** 
		 * @brief ��û�� ���� ó���� ���� ����
		 * @return true or false
		 */
		virtual bool isSuccess() const = 0;

		/**
		 * @brief �����ڵ带 ������
		 * @return �����ڵ尪
		 */
		virtual int code() const = 0;

		/**
		 * @brief ���� �޽����� ������
		 * @return ���ڿ� ���� �޽���
		 */
		virtual const char* message() const = 0;

		/**
		 * @brief ������ �� ������ ������
		 * @return ��������
		 * @remark !!!���Ϲ��� IVariant*�� �� �� �� �ݵ�� release()�� ȣ���ؾ� ��!!!
		 */
		virtual IVariant* detail() const = 0;

		/**
		 * @brief ���� object�� ������
		 * @return ���� object
		 * @remark !!!���Ϲ��� IList*�� �� �� �� �ݵ�� release()�� ȣ���ؾ� ��!!!
		 */
		virtual IList* objects() const = 0;

	public:
		/**
		 * @brief ���۷��� ī���͸� ������Ŵ
		 * @return ������ ���۷��� ī����
		 */
		virtual unsigned short addRef() = 0;

		/**
		 * @brief ���۷��� ī���͸� ���ҽ�Ŵ
		 * @return ���ҵ� ���۷��� ī����
		 * @remark ���۷��� ī���Ͱ� 0�� �Ǹ� �ڵ����� ��ü�� �Ҹ��
		 */
		virtual unsigned short release() = 0;
};


/**
 * @brief NBFPClient �������̽� Ŭ����
 */
class INBFPClient
{
public:
	/**
	 * @copydoc nano::NBFPClient::TransportType
	 */
	enum TransportType {
		TP_TCP = 0,
		TP_UDP = 1
	};


public:
	/**
	 * @brief NBFP Ŭ���̾�Ʈ ������ ����
	 * @param host ���� �ּ�
	 * @param port ���� ��Ʈ
	 * @param timeout Timeout (ms)
	 * @param tp TransportType
	 * @return true or false
	 */
	virtual bool open(const char *host, int port, int timeout = -1, INBFPClient::TransportType tp = TP_TCP) = 0;

	/**
	 * @brief NBFP Ŭ���̾�Ʈ ������ ����
	 */
	virtual void close() = 0;

	/**
	 * @brief timeout�� ����
	 * @param timeout millseconds
	 */
	virtual void setTimeout(int timeout = -1) = 0;

	/**
	 * @brief Namespace�� ����
	 * @param ns Namespace
	 * @remark �ѹ� ������ Namespace�� ������ ���������� ������
	 */
	virtual void setNamespace(const char *ns) = 0;

	/**
	 * @brief Character set�� ����
	 * @param charscter set code (Microsoft code page ��ȣ) 
	 * @remark �ѹ� ������ Charset�� ������ ���������� ������
	 */
	virtual void setCharset(uint16_t charset) = 0;

	/**
	 * @brief Request ID ����
	 * @param reqID Request ID
	 * @remark �ѹ� ������ reqID�� ������ ���������� ������
	 */
	virtual void setReqID(int32_t reqID) = 0;

	/**
	 * @brief Result ���
	 * @return INBFPResult ��
	 * @remark exec()���� ���ϵǴ� ���� ����
	 * @remark release() �� �� �ʿ� ����
	 */
	virtual INBFPResult* getLastResult() = 0;

	/**
	 * @brief ����� �����´�
	 * @return ��û�� ���� ó�� ���
	 */
	virtual const INBFPResult* retval() = 0;

public:
		/**
		 * @brief ���۷��� ī��Ʈ�� ������Ŵ
		 * @return ������ ���۷��� ī��Ʈ
		 */
		virtual size_t addRef() = 0;

		/**
		 * @brief ���۷��� ī��Ʈ�� ���ҽ�Ŵ
		 * @return ���ҵ� ���۷��� ī��Ʈ
		 * @remark ���۷��� ī��Ʈ�� 0�� �Ǵ� ���� �ڵ� �Ҹ��
		 */
		virtual size_t release() = 0;

public:
	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 0�� ����)
	 * @param method Method �̸�
	 * @param params Parameter List
	 * @param size params number
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* exec(const char *method, IList &params, size_t size) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 0�� ����)
	 * @param method Method �̸�
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* exec(const char* method) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 1�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 2�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 3�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 4�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 5�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 6�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 7�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 8�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 9�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 10�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 11�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 12�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 13�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 14�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 15�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 16�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 17�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 18�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @param param18 Paramter #18
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17,
		const VariantBoxing& param18) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 19�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @param param18 Paramter #18
	 * @param param19 Paramter #19
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17,
		const VariantBoxing& param18,
		const VariantBoxing& param19) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 20�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @param param18 Paramter #18
	 * @param param19 Paramter #19
	 * @param param20 Paramter #20
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* INBFPClient::exec(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17,
		const VariantBoxing& param18,
		const VariantBoxing& param19,
		const VariantBoxing& param20) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 0�� ����)
	 * @param method Method �̸�
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(const char* method) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 1�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 2�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 3�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 4�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 5�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 6�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 7�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 8�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 9�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 10�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 11�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 12�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 13�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 14�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 15�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 16�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 17�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 18�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @param param18 Paramter #18
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17,
		const VariantBoxing& param18) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 19�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @param param18 Paramter #18
	 * @param param19 Paramter #19
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17,
		const VariantBoxing& param18,
		const VariantBoxing& param19) = 0;

	/**
	 * @brief Method ȣ�� (Parameter 20�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param2 Paramter #2
	 * @param param3 Paramter #3
	 * @param param4 Paramter #4
	 * @param param5 Paramter #5
	 * @param param6 Paramter #6
	 * @param param7 Paramter #7
	 * @param param8 Paramter #8
	 * @param param9 Paramter #9
	 * @param param10 Paramter #10
	 * @param param11 Paramter #11
	 * @param param12 Paramter #12
	 * @param param13 Paramter #13
	 * @param param14 Paramter #14
	 * @param param15 Paramter #15
	 * @param param16 Paramter #16
	 * @param param17 Paramter #17
	 * @param param18 Paramter #18
	 * @param param19 Paramter #19
	 * @param param20 Paramter #20
	 * @return ���� ����� ���� reference
	 */	 
	virtual const INBFPResult* call(
		const char* method,
		const VariantBoxing& param1,
		const VariantBoxing& param2,
		const VariantBoxing& param3,
		const VariantBoxing& param4,
		const VariantBoxing& param5,
		const VariantBoxing& param6,
		const VariantBoxing& param7,
		const VariantBoxing& param8,
		const VariantBoxing& param9,
		const VariantBoxing& param10,
		const VariantBoxing& param11,
		const VariantBoxing& param12,
		const VariantBoxing& param13,
		const VariantBoxing& param14,
		const VariantBoxing& param15,
		const VariantBoxing& param16,
		const VariantBoxing& param17,
		const VariantBoxing& param18,
		const VariantBoxing& param19,
		const VariantBoxing& param20) = 0;
};


/** @} */
} /*end of namespace mega*/


#endif
