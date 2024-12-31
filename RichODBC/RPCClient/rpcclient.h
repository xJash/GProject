/**
 * @file rpcclient.h
 * @brief
 * @author rapool <chankyulee@nhncorp.com>
 * @date $Date: 2007-01-02$
 * @version $Revision: $
 * $Id: $
 */
#ifndef __RPCCLIENT_H_4FE157CD_5035_43D1_830E_A65D4E326825__
#define __RPCCLIENT_H_4FE157CD_5035_43D1_830E_A65D4E326825__

#include "common.h"
#include "rpcNbfpClient.h"

namespace mega {
/**
 * @addtogroup megarpc
 * @{
 */


class IRPCClient;
class IRPCConnector;
class IVariant;
class IList;
class ITransport;

/**
 * @brief IRPCClient�� ��ü�� ���� �����Ѵ�
 * @return ������� IRPCClient�� object pointer
 * @remark ����� ���� IRPCClient�� delete�� �̿��Ͽ� ������ �־�� �Ѵ�
 */
IRPCClient* CreateRPCClient();

/**
 * @brief IRPCConnector��ü�� ���� �����Ѵ�
 * @return ������� IRPCConnector object pointer
 * @remark ����� ���� IRPCConnector�� delete�� �̿��Ͽ� ������ �־�� �Ѵ�
 */
IRPCConnector* CreateRPCConnector();


/**
 * @brief IRPCConnector
 */
class IRPCConnector
{
public:
	enum TransportType
	{
		TP_TCP = 0,
		TP_UDP
	};

public:
	virtual ~IRPCConnector() {}

	/**
	 * @brief RPC Ŭ���̾�Ʈ ������ �����Ѵ�.
	 *
	 * @param host ���� host
	 * @param port ���� Port
	 * @param timeout Timeout (ms)
	 * @param tp Transport Type( IRPCConnector::TP_TCP, IRPCConnector::TP_UDP )
	 * @return ������ true, ���н� false
	 */
	virtual bool open(IRPCClient *client, const char *host, int timeout = -1, TransportType tp = TP_TCP) = 0;

	/*!
	 * @brief ���丮 ���񽺸� �����ϴ� ������ ������ �Է��Ѵ�.
	 * 
	 * @param addr ���丮 ���� ���� �ּ�
	 * @param port ���丮 ���� ���� ��Ʈ
	 * @param isPrimary primary�̸� true, secondary�̸� false
	 * @param timeout Timeout(ms)
	 * @param tp Transport Type
	 */
	virtual void setDirectoryServerInformation(const char* addr, int port, bool isPrimary, int timeout = -1, TransportType tp = TP_TCP) = 0;

	/**
	 * @brief �����ڵ带 �����´�
	 * @return �߻��� �����ڵ�
	 */
	virtual int errorCode() = 0;

	/**
	 * @brief �����޼����� �����´�
	 * @return �����޼���
	 */
	virtual const char* errorMessage() = 0;
};
/* end of class IRPCConnector */


/**
 * @brief IRPCResult ������ ������ �ִ� Ŭ���� �������̽�
 * @remark IRPCClient�� ���Ͽ� ����� ���Ϲ��� �� ����Ѵ�
 */
class IRPCResult
{
public:
	/**
	 * @brief �����ڵ带 ��´�
	 * @return �����ڵ�
	 */
	virtual int errorCode() const = 0;

	/**
	 * @brief �����޼����� ��´�
	 * @return �����޼���
	 */
	virtual const char* errorMessage() const = 0;

	/**
	 * @brief �� ���� ������ ��´�
	 * @return �� ���� ����
	 * @remark !!! ��� �� �ݵ�� IVariant::relase()�� ȣ���ؾ� �� !!!
	 */
	virtual IVariant* errorDetail() = 0;

	/**
	 * @brief Return objects�� ��´�
	 * @return Return objects list
	 * @remark !!! ��� �� �ݵ�� IList::relase()�� ȣ���ؾ� �� !!!
	 */
	virtual const IList* objects() const = 0;

	/**
	 * @brief reply�� �� transport�� ��´�.
	 * @return Transport object
	 */
	virtual ITransport* getTransport() = 0;

	/**
	 * @brief Call ���� ����
	 * @return ������ ��� true, ������ ��� false
	 * @remark Stream���� ������ ����, application ������ SUCCESS�� ������ ��쿡�� �������� ���ֵȴ�
	 */
	virtual bool isSuccess() const = 0;
};
/* end of class IRPCResult */


/**
 * @brief Transport class
 */
class ITransport
{
public:
	/**
	 * @brief Option�� Ÿ��
	 */
	enum OptionType
	{
		OPT_PAYLOAD_SIZE            = 0,    /**< Payload: ���� */
		OPT_PAYLOAD_TYPE            = 1,    /**< Payload: Ÿ�� */
		OPT_PAYLOAD_ENCRYPTION      = 2,    /**< Payload: Encryption scheme */
		OPT_PAYLOAD_FRAGMENTATION   = 3,    /**< Payload: Fragmentation ���� */
		OPT_PAYLOAD_CHECKSUM        = 4,    /**< Payload: Checksum */
		OPT_PAYLOAD_LOCALE          = 5,    /**< Payload: Locale */
		OPT_SRC_ADDR                = 6,    /**< Routing: Source Address */
		OPT_DEST_ADDR               = 7,    /**< Routing: Destination Address */
		OPT_TTL                     = 8,    /**< Routing: TTL */
		OPT_TRANSPORT_CONTROL       = 9,    /**< Transrpot Control */
		OPT_TRANSACTION_ID          = 10,   /**< Transaction ID */
		OPT_PEER_ID                 = 11,   /**< Peer ID */
		OPT_PEER_NAME               = 12,   /**< Peer Name */
		OPT_NAMESPACE               = 13,   /**< Namespace */
		OPT_CONTINUED               = 31,   /**< (not used) */
		OPT_USER_DEFINED            = -1,   /**< User-defined Option */
	};

	/**
	 * @brief Protocol Version
	 */
	struct Version
	{
		uint8_t major;      /**< Major version */
		uint8_t minor;      /**< Minor version */

		/**
		 * @brief Set version via uint_t
		 * @param version version
		 */
		void set(uint8_t version)
		{
			major = ( version >> 4 ) & 0x0F;
			minor = version & 0x0F;
		}

		/**
		 * @brief Get version via uint8_t
		 * @return version
		 */
		uint8_t get() const
		{
			return ( ( major << 4 ) + minor );
		}
	};

	virtual ~ITransport() {}

	/**
	 * @brief ���� ����, option ���� ���� ��� �ʱ�ȭ
	 */
	virtual void reset() = 0;

	/**
	 * @brief ������ ��´�.
	 * @return version or NULL(ERROR)
	 */
	virtual const Version* version() const = 0;

	/**
	 * @brief Transport�� ũ�⸣ ��´�.
	 * @return Transport�� ũ��
	 * @remark read() �� ��쿡�� network�� �о���� ũ�⸦, write()�� ��쿡�� write�� ũ�⸦ return�Ѵ�.
	 */
	virtual uint16_t size() const = 0;

	/**
	 * @brief Ư�� option�� �����ϴ��� �˷��ش�.
	 * @param ot Option Type
	 * @param user_idx ot = OPT_USER_DEFINED�� ��� �ε��� (�� ���� ��쿡�� ���õȴ�)
	 * @return �ش� option�� �����ϴ� ��� true, �������� �ʴ� ��� false
	 */
	virtual bool hasOption(OptionType ot, size_t user_idx = 0) const = 0;

	/**
	 * @brief Ư�� option�� byte ���̸� ��´�.
	 * @param ot Option Type (�� ���� ��쿡�� ���õȴ�)
	 * @param user_idx ot = OPT_USER_DEFINED�� ��� �ε���
	 * @return �ش� option�� �����ϴ� ��� true, �������� �ʴ� ��� false
	 */
	virtual size_t getOptionSize(OptionType ot, size_t user_idx = 0) const = 0;

	/**
	 * @brief namespace ��뿩��
	 */
	virtual bool hasNamespace() const = 0;

	/**
	 * @brief Payload locale ��뿩��
	 */
	virtual bool hasPayloadLocale() const = 0;

	/**
	 * @brief Transaction ID ��뿩��
	 */
	virtual bool hasTransactionID() const = 0;

	/**
	 * @brief PayloadSize option�� ��´�.
	 * @return Payload size
	 */
	virtual uint32_t getPayloadSize() const = 0;

	/**
	 * @brief PayloadType option�� ��´�.
	 * @param size ���ڿ��� ���̸� ���� ������. ���� �������� NULL�� �����ϰų� �������� ������ �ȴ�.
	 * @return Payload type
	 */
	virtual const char* getPayloadType( size_t* size = NULL ) const = 0;

	/**
	 * @brief PayloadLocale option�� ��´�.
	 * @return Payload locale
	 */
	virtual uint16_t getPayloadLocale() const = 0;

	/**
	 * @brief SourceAddress option�� ��´�.
	 * @param size ���ڿ��� ���̸� ���� ������. ���� �������� NULL�� �����ϰų� �������� ������ �ȴ�.
	 * @return Source address
	 */
	virtual const char* getSrcAddr( size_t* size = NULL ) const = 0;

	/**
	 * @brief DestinationAddress option�� ��´�.
	 * @param size ���ڿ��� ���̸� ���� ������. ���� �������� NULL�� �����ϰų� �������� ������ �ȴ�.
	 * @return Destination address
	 */
	virtual const char* getDestAddr( size_t* size = NULL ) const = 0;

	/**
	 * @brief TransactionID option�� ��´�.
	 * @return Transaction ID
	 */
	virtual uint32_t getTransactionID() const = 0;

	/**
	 * @brief PeerID option�� ��´�.
	 * @return Peer ID
	 */
	virtual uint32_t getPeerID() const = 0;

	/**
	 * @brief PeerName option�� ��´�.
	 * @param size ���ڿ��� ���̸� ���� ������. ���� �������� NULL�� �����ϰų� �������� ������ �ȴ�.
	 * @return Peer name
	 */
	virtual const char* getPeerName( size_t* size = NULL ) const = 0;

	/**
	 * @brief Namespace option�� ��´�.
	 * @param size ���ڿ��� ���̸� ���� ������. ���� �������� NULL�� �����ϰų� �������� ������ �ȴ�.
	 * @return Namespace
	 */
	virtual const char* getNamespace( size_t* size = NULL ) const = 0;

public:
	/**
	 * @brief PayloadSize�� �����Ѵ�.
	 * @param opt Payload size
	 */
	virtual void setPayloadSize( uint32_t opt ) = 0;

	/**
	 * @brief PayloadType�� �����Ѵ�.
	 * @param opt Payload type
	 * @param size ���ڿ��� ����. �������� ������ ���ο��� strlen(3)���� ����Ѵ�.
	 */
	virtual void setPayloadType( const char* opt, size_t size = (size_t)-1 ) = 0;

	/**
	 * @brief PayloadLocale�� �����Ѵ�.
	 * @param opt Payload locale
	 */
	virtual void setPayloadLocale( uint16_t opt ) = 0;

	/**
	 * @brief SourceAddress�� �����Ѵ�.
	 * @param opt Source address
	 * @param size ���ڿ��� ����. �������� ������ ���ο��� strlen(3)���� ����Ѵ�.
	 */
	virtual void setSrcAddr( const char* opt, size_t size = (size_t)-1 ) = 0;

	/**
	 * @brief DestinationAddress�� �����Ѵ�.
	 * @param opt Destination address
	 * @param size ���ڿ��� ����. �������� ������ ���ο��� strlen(3)���� ����Ѵ�.
	 */
	virtual void setDestAddr( const char* opt, size_t size = (size_t)-1 ) = 0;

	/**
	 * @brief TransactionID�� �����Ѵ�.
	 * @param opt Transaction ID
	 */
	virtual void setTransactionID( uint32_t opt ) = 0;

	/**
	 * @brief PeerID�� �����Ѵ�.
	 * @param opt Peer ID
	 */
	virtual void setPeerID( uint32_t opt ) = 0;

	/**
	 * @brief PeerName�� �����Ѵ�.
	 * @param opt Peer name
	 * @param size ���ڿ��� ����. �������� ������ ���ο��� strlen(3)���� ����Ѵ�.
	 */
	virtual void setPeerName( const char* opt, size_t size = (size_t)-1 ) = 0;

	/**
	 * @brief Namespace�� �����Ѵ�.
	 * @param opt Namespace
	 * @param size ���ڿ��� ����. �������� ������ ���ο��� strlen(3)���� ����Ѵ�.
	 */
	virtual void setNamespace( const char* opt, size_t size = (size_t)-1 ) = 0;

public:
	/**
	 * @brief ���ڿ��� option ���
	 * @param ot Option type
	 * @param size ���ڿ��� ���̸� ������ ������. ���� ��������, �������� �ʰų� NULL�� �����ϸ� �ȴ�.
	 * @return �ش� option�� const char* ������. option�� �������� ������ NULL
	 */
	virtual const char* getOption( OptionType ot, size_t* size = NULL ) const = 0;

public:
	/**
	 * @brief ���ڿ��� option ����
	 * @param ot Option type
	 * @param opt Option
	 * @param size ���ڿ��� ����. �������� ������ ���ο��� strlen(3)���� ����Ѵ�.
	 */
	virtual void setOption( OptionType ot, const char* opt, size_t size = (size_t)-1 ) = 0;

public:
	/**
	 * @brief ���ڿ��� user-defined option ���
	 * @param idx Option index
	 * @param size ���ڿ��� ���̸� ������ ������. ���� ��������, �������� �ʰų� NULL�� �����ϸ� �ȴ�.
	 * @return �ش� option�� const char* ������. option�� �������� ������ NULL
	 */
	virtual const char* getUserOption( size_t idx, size_t* size = NULL ) const = 0;

public:
	/**
	 * @brief ���ڿ��� user-defined option ����
	 * @param idx Option idx
	 * @param opt Option
	 * @param size ���ڿ��� ����. �������� ������ ���ο��� strlen(3)���� ����Ѵ�.
	 */
	virtual void setUserOption( size_t idx, const char* opt, size_t size = (size_t)-1 ) = 0;

public:
	/**
	 * @brief Ư�� option ������ �����Ѵ�.
	 * @param ot Option type
	 * @param user_idx ot = OPT_USER_DEFINED�� ��� index. �� �ܿ��� ���õȴ�.
	 */
	virtual void clearOption( OptionType ot, size_t user_idx = 0 ) = 0;

};
/* end of class ITransport */


/**
 * @brief IRPCClient
 */
class IRPCClient
{
public:
	virtual ~IRPCClient() {}

	/**
	 * @brief Transport�� �����´�
	 * @return Transport �������̽�
	 */
	virtual ITransport* getTransport() = 0;

	/**
	 * @brief RPC Ŭ���̾�Ʈ ������ �����Ѵ�.
	 * @param host ���� host
	 * @param port ���� Port
	 * @param timeout Timeout (ms)
	 * @param tp Transport Type( IRPCConnector::TP_TCP, IRPCConnector::TP_UDP )
	 * @return ������ true, ���н� false
	 */
	virtual bool open( const char* host, int port, int timeout = -1, IRPCConnector::TransportType tp = IRPCConnector::TP_TCP ) = 0;

public:
	/**
	 * @brief IRPCResult�� ��´�
	 * @return IRPCResult
	 */
	virtual const IRPCResult* getLastResult() = 0;

	/**
	 * @brief reply �б�
	 * @return ���� ����� ���� reference
	 */
	virtual bool reply() = 0;

public:
	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param params �����ϰ��� �ϴ� �Ķ������ ����Ʈ
	 * @param size params ����
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, IList *params, size_t size) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @param param1 Paramter #18
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17,
		const VariantBoxing &param18) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @param param1 Paramter #18
	 * @param param1 Paramter #19
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17,
		const VariantBoxing &param18,
		const VariantBoxing &param19) = 0;

	/**
	 * @brief ������ Request�� ������
	 * @param Method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @param param1 Paramter #18
	 * @param param1 Paramter #19
	 * @param param1 Paramter #20
	 * @return ��������
	 * @remark ������ ����� reply()�� �̿��ؼ� ���� �� �ִ�
	 */
	virtual bool call(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17,
		const VariantBoxing &param18,
		const VariantBoxing &param19,
		const VariantBoxing &param20) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 1�� ����)
	 * @param method Method �̸�
	 * @param params �����ϰ��� �ϴ� �Ķ������ ����Ʈ
	 * @param size params ����
	 * @return ���� ����� ���� result 
	 */
	virtual const IRPCResult* exec(const char* method, IList *params, size_t size) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 0�� ����)
	 * @param method Method �̸�
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char* method) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 1�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 2�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 3�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 4�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 5�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 6�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 7�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 8�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 9�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 10�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 11�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 12�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 13�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 14�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 15�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 16�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 17�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 18�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @param param1 Paramter #18
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17,
		const VariantBoxing &param18) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 19�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @param param1 Paramter #18
	 * @param param1 Paramter #19
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17,
		const VariantBoxing &param18,
		const VariantBoxing &param19) = 0;

	/**
	 * @brief Method ȣ�� + Reply �б� (Parameter 20�� ����)
	 * @param method Method �̸�
	 * @param param1 Paramter #1
	 * @param param1 Paramter #2
	 * @param param1 Paramter #3
	 * @param param1 Paramter #4
	 * @param param1 Paramter #5
	 * @param param1 Paramter #6
	 * @param param1 Paramter #7
	 * @param param1 Paramter #8
	 * @param param1 Paramter #9
	 * @param param1 Paramter #10
	 * @param param1 Paramter #11
	 * @param param1 Paramter #12
	 * @param param1 Paramter #13
	 * @param param1 Paramter #14
	 * @param param1 Paramter #15
	 * @param param1 Paramter #16
	 * @param param1 Paramter #17
	 * @param param1 Paramter #18
	 * @param param1 Paramter #19
	 * @param param1 Paramter #20
	 * @return ���� ����� ���� result
	 */
	virtual const IRPCResult* exec(const char *method, 
		const VariantBoxing &param1,
		const VariantBoxing &param2,
		const VariantBoxing &param3,
		const VariantBoxing &param4,
		const VariantBoxing &param5,
		const VariantBoxing &param6,
		const VariantBoxing &param7,
		const VariantBoxing &param8,
		const VariantBoxing &param9,
		const VariantBoxing &param10,
		const VariantBoxing &param11,
		const VariantBoxing &param12,
		const VariantBoxing &param13,
		const VariantBoxing &param14,
		const VariantBoxing &param15,
		const VariantBoxing &param16,
		const VariantBoxing &param17,
		const VariantBoxing &param18,
		const VariantBoxing &param19,
		const VariantBoxing &param20) = 0;
};
/* end of class IRPCClient */

/** @} */
} /* end of namespace mega */ 
#endif /*__RPCCLIENT_H_4FE157CD_5035_43D1_830E_A65D4E326825__*/
