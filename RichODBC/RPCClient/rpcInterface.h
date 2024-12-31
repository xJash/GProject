/**
* @brief RPC �������̽� ����
* @author rapool <chankyulee@nhncorp.com>
* @date $Date: 2006-05-10$
* @version $Revision: $
*/


#ifndef MEGA_RPC_INTERFACE_H
#define MEGA_RPC_INTERFACE_H


#include "common.h"

#ifdef __NANO_OS_WIN32__
#include "winutil.h"
#else
#include "unixutil.h"
#endif


namespace mega
{
/**
 * @addtogroup nbfpInterface
 * @{
 */


extern int objectCount;

class IList;
class IMap;
class ITable;
class IVariant;
class VariantBoxing;


/**
 * @brief nano::Variant �������̽� Ŭ����
 */
class IVariant
{
	public:
		/**
		 * @brief IVariant���� ����ϴ� Ÿ�԰� ����
		 */
		enum Type {
			TYPE_UNKNOWN = 0, 		/**< UNKNOWN */
			/* basic */
			TYPE_NULL = 1, 			/**< NULL */
			TYPE_BOOL, 				/**< BOOL : boolean */
			TYPE_CHAR, 				/**< CHAR : �� ����. 1 byte integer�� �ƴ� */
			TYPE_INT, 				/**< INT : 4 byte signed integer */
			TYPE_LONG, 				/**< LONG : 8 byte signed integer */
			TYPE_DOUBLE, 			/**< DOUBLE : IEEE 754, 8 byte floating point number */
			TYPE_DATE, 				/**< DATE : miliseconds since epoch. 8 byte signed integer */
			TYPE_STRING, 			/**< STRING */
			TYPE_BINARY, 			/**< BINARY */
			TYPE_BIGINT, 			/**< BIGINT */
			/* derived from basic */
			TYPE_XML = 50, 			/**< ������ ���� */
			TYPE_REMOTE, 			/**< ������ ���� */
			TYPE_REF, 				/**< ������ ���� */
			/* container */
			TYPE_LIST = 100, 		/**< LIST */
			TYPE_MAP, 				/**< MAP */
			TYPE_TABLE, 			/**< TABLE */
			/* type only */
			TYPE_NUMBER = 150, 		/**< NUMBER : TABLE�� COLUMN TYPE���θ� ���̸�, ���� FIELD�� INT/LONG/DOUBLE�� �������� ��Ÿ���� */
			TYPE_TABLE_COLUMN, 		/**< TABLE_COLUMN : TABLE�� COLUMN�� ��Ÿ����. ���� object�� �������� �ʴ´� */
			TYPE_TABLE_ROW, 		/**< TABLE_ROW : TABLE�� ROW�� ��Ÿ����. ���� object�� �������� �ʴ´� */
			/* other */
			TYPE_EOO = 255, 		/**< EOO : end ob object. STREAM������ ���ȴ�. */
		};

		enum ConvertOption
		{
			CONVERT_NONE = 0, // conversion�� �������� �ʴ´�. type�� ��Ȯ�� �´� ��쿡�� ���� ��ų� conversion�� �����Ѵ�.  
			CONVERT_CAST = 1, // conversion�� ������ ��� conversion�� �����Ѵ�. (range�� ����ų�, ���� �ջ�� �� �ִ�)  
			CONVERT_RANGE_SAFE = 2, // CONVERT_CAST�� ������, range�� ����� ��� conversion ���з� �����Ѵ�. (��: LONG -> INT)  
			CONVERT_VALUE_SAFE = 3, // CONVERT_RANGE_SAFE�� ������, ���� �ջ�Ǵ� ��� conversion ���з� �����Ѵ�. (��: �Ҽ��� ���ϰ� �ִ� DOUBLE -> LONG) 
		};

	public:
		/**
		 * @brief ����� ���� Ÿ���� ����
		 * @return IVariant::Type������ Ÿ�԰�
		 */
		virtual IVariant::Type type() const = 0;

		/**
		 * @brief ����� ���� ����Ʈ���� ����
		 * @return ����Ʈ��
		 */
		virtual size_t size() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 */
		virtual bool boolVal() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 */
		virtual int intVal() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 */
		virtual double doubleVal() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 */
		virtual int64_t longVal() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 */
		virtual const char *stringVal() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 */
#ifdef __NANO_OS_WIN32__
		virtual struct nano::timeval timeVal() const = 0;
#else
		virtual struct timeval timeVal() const = 0;
#endif

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 * @remark !!! ��� �� �ݵ�� IList::relase()�� ȣ���ؾ� �� !!!
		 */
		virtual IList* listVal() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 * @remark !!! ��� �� �ݵ�� ITable::relase()�� ȣ���ؾ� �� !!!
		 */
		virtual ITable* tableVal() const = 0;

		/**
		 * @brief ����� ���� ������
		 * @return ����� ��
		 * @remark !!! ��� �� �ݵ�� IMap::relase()�� ȣ���ؾ� �� !!!
		 */
		virtual IMap* mapVal() const = 0;

		/**
		 * @brief ����� ���� �����͸� ������
		 * @return ������
		 */
		virtual const void* ptr() const = 0;

public:
		/**
		 * @brief bool �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(bool *val, ConvertOption opt = CONVERT_CAST) const = 0;

		/**
		 * @brief int �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(int *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief float �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(float *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief double �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(double *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief int8_t �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(int8_t *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief uint8_t �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(uint8_t *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief int16_t �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(int16_t *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief uint16_t �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(uint16_t *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief uint32_t �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(uint32_t *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief int64_t �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(int64_t *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief uint64_t �� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(uint64_t *val, ConvertOption opt = CONVERT_RANGE_SAFE) const = 0;

		/**
		 * @brief string �� ���
		 * @param ptr ���� ���� pointer
		 * @param size ũ�⸦ ���� pointer
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(const char **ptr, size_t *size = NULL, ConvertOption opt = CONVERT_CAST) const = 0;

		/**
		 * @brief binary �� ���
		 * @param ptr ���� ���� pointer
		 * @param size ũ�⸦ ���� pointer
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
		virtual bool get(const void **ptr, size_t *size = NULL, ConvertOption opt = CONVERT_CAST) const = 0;

		/**
		 * @brief date�� ���
		 * @param val ���� ���� ����
		 * @param opt type ��ȯ�� ��ȯ ���
		 * @return ��ȯ�� �����ϰ�, val�� valid�� ���� �־��� ��� true, �ƴ� ��� false
		 * @remark Type�� �ٸ� ���, ���� ��ȯ�ϳ� ��ü�� type�� ������ �ʴ´�.
		 */
#ifdef __NANO_OS_WIN32__
		virtual bool get(struct nano::timeval* val, ConvertOption opt = CONVERT_CAST) const = 0;
#else
		virtual bool get(struct timeval* val, ConvertOption opt = CONVERT_CAST) const = 0;
#endif

	public:
		/**
		 * @brief ���۷��� ī��Ʈ�� ������Ŵ
		 */
		virtual void addRef() const = 0;

		/**
		 * @brief ���۷��� ī��Ʈ�� ���ҽ�Ŵ
		 * @remark ���۷��� ī��Ʈ�� 0�� �Ǵ� ���� �ڵ� �Ҹ��
		 */
		virtual void release() const = 0;

	public:
		/**
		 * @brief �ش� ���� XML ���·� stdout�� �����
		 */
		virtual void printAsXML() const = 0;

		/**
		 * @brief �ش� ���� XML ������ ��Ʈ������ ������, ������ ũ�⺸�� ��Ʈ���� �� ��� (size-1)��ŭ�� ������
		 * @param buf ��Ʈ���� ���� ����
		 * @param size ��Ʈ���� ���� ������ ũ��
		 * @return XML ������ null-terminated string
		 */
		virtual const char* toXML(char *buf, unsigned int size) const = 0;
};


class ITable
{
	public:
		/**
		 * @brief ����� Row�� ���� ������
		 * @return ����� Row�� ��
		 * @remark rowSize() �� ����
		 */
		virtual size_t size() const = 0;

		/**
		 * @brief ����� Row�� ���� ������
		 * @return ����� Row�� ��
		 */
		virtual size_t rowSize() const = 0;

		/**
		 * @brief ����� Column�� ���� ������
		 * @return ����� Column�� ��
		 */
		virtual size_t columnSize() const = 0;

		/**
		 * @brief ���̺� ����� �����͸� ������
		 * @return ����� IVariant ������
		 * @remark rowIndex�� columnIndex�� �߸��� ��� IVariant::TYPE_NULL�� ���� IVariant�� ���ϵ�
		 * @remark ���Ϲ��� IVariant�� ���Ͽ� release() ȣ���� �ʿ� ����
		 */
		virtual const IVariant* getValue(size_t rowIndex, size_t columnIndex) const = 0;

		/**
		 * @brief ���̺� ����� �����͸� ������
		 * @return columnName�� �߸��� ��� NULL�� ������
		 * @remark rowIndex�� columnIndex�� �߸��� ��� IVariant::TYPE_NULL�� ���� IVariant�� ���ϵ�
		 * @remark ���Ϲ��� IVariant�� ���Ͽ� release() ȣ���� �ʿ� ����
		 * @remark ***** getValue(0, 0) ȣ��ÿ� ���� �Լ��� ambigious�� �߻��ؼ� �ϴ� ���� ******
		 */
		//virtual IVariant* getValue(size_t rowIndex, const char *columnName) = 0;

		/**
		 * @brief �÷��� Ÿ���� ������
		 * @param columnIndex �÷� �ε��� (zero-based)
		 */
		virtual IVariant::Type columnType(size_t columnIndex) const = 0;

		/**
		 * @brief �÷��̸��� ������
		 * @param columnIndex �÷� �ε��� (zero-based)
		 */
		virtual const char *columnName(size_t columnIndex) const = 0;

	public:
		/**
		 * @brief ���۷��� ī��Ʈ�� ������Ŵ
		 */
		virtual void addRef() const = 0;

		/**
		 * @brief ���۷��� ī��Ʈ�� ���ҽ�Ŵ
		 * @remark ���۷��� ī��Ʈ�� 0�� �Ǵ� ���� �ڵ� �Ҹ��
		 */
		virtual void release() const = 0;

	public:
		/**
		 * @brief �ش� ���� XML ���·� stdout�� �����
		 */
		virtual void printAsXML() const = 0;

		/**
		 * @brief �ش� ���� XML ������ ��Ʈ������ ������, ������ ũ�⺸�� ��Ʈ���� �� ��� (size-1)��ŭ�� ������
		 * @param buf ��Ʈ���� ���� ����
		 * @param size ��Ʈ���� ���� ������ ũ��
		 * @return XML ������ null-terminated string
		 */
		virtual const char* toXML(char *buf, unsigned int size) const = 0;
};


/**
 * @brief RPC Variant List �������̽�
 */
class IList
{
	public:
		/**
		 * @brief ����Ʈ�� ���Ҹ� ������
		 * @param index ����Ʈ �ε��� (zero-based)
		 * @return ������ ������
		 * @remark ���ϵ� IVariant�� ���ؼ� release()�� ȣ���� �ʿ� ����
		 */
		virtual const IVariant* at(size_t index) const = 0;

		/**
		 * @brief ����Ʈ�� ���Ҹ� ������
		 * @param index ����Ʈ �ε��� (zero-based)
		 * @return ������ ������
		 * @remark ���ϵ� IVariant�� ���ؼ� release()�� ȣ���� �ʿ� ����
		 */
		virtual const IVariant* operator[] (size_t index) const = 0;

		/**
		 * @brief ����Ʈ�� ���Ҹ� �߰�
		 * @param iv �߰��ϰ��� �ϴ� ��
		 */
		virtual void add(const VariantBoxing &iv) = 0;

		/**
		 * @brief ����Ʈ�� binary�� �߰�
		 * @param ptr �߰��ϰ��� �ϴ� binary ���� ������
		 * @param size �߰��ϰ��� �ϴ� binary ���� ������
		 */
		virtual void add(const void *ptr, size_t size) = 0;

		/**
		 * @brief ����Ʈ ������ ������ ������
		 * @return ����Ʈ ������ ����
		 */
		virtual size_t size() const = 0;

	public:
		/**
		 * @brief ���۷��� ī��Ʈ�� ������Ŵ
		 */
		virtual void addRef() const = 0;

		/**
		 * @brief ���۷��� ī��Ʈ�� ���ҽ�Ŵ
		 * @remark ���۷��� ī��Ʈ�� 0�� �Ǵ� ���� �ڵ� �Ҹ��
		 */
		virtual void release() const = 0;

	public:
		/**
		 * @brief �ش� ���� XML ���·� stdout�� �����
		 */
		virtual void printAsXML() const = 0;

		/**
		 * @brief �ش� ���� XML ������ ��Ʈ������ ������, ������ ũ�⺸�� ��Ʈ���� �� ��� (size-1)��ŭ�� ������
		 * @param buf ��Ʈ���� ���� ����
		 * @param size ��Ʈ���� ���� ������ ũ��
		 * @return XML ������ null-terminated string
		 */
		virtual const char* toXML(char *buf, unsigned int size) const = 0;
};


/** 
 * @brief RPC Variant Hashmap �������̽�
 */
class IMap
{
	public:
		/**
		 * @brief �ؽ��ʿ��� key�� �ش��ϴ� ����������
		 * @param key Ű
		 * @param value ���� �����ϱ� ���� IVariant�� ������
		 * @return �ش� Ű�� �������� ���� ��� false ����
		 * @remark ���Ϲ��� value�� ���Ͽ� release()�� ȣ���� �ʿ� ����
		 */
		virtual bool get(const VariantBoxing &key, IVariant **value) const = 0;

		/**
		 * @brief �ؽ��ʿ� �������� ������
		 * @param key �������� Ű
		 * @param value ������
		 * @return ���� Ű�� ������ ��� false ����
		 */
		virtual bool put(const VariantBoxing &key, const VariantBoxing &value) = 0;

		/**
		 * @brief �ؽ��ʿ� ����� ����� ���� ������
		 * @return ����� ��
		 */
		virtual size_t size() const = 0;

	public:
		/**
		 * @brief ���۷��� ī��Ʈ�� ������Ŵ
		 */
		virtual void addRef() const = 0;

		/**
		 * @brief ���۷��� ī��Ʈ�� ���ҽ�Ŵ
		 * @remark ���۷��� ī��Ʈ�� 0�� �Ǵ� ���� �ڵ� �Ҹ��
		 */
		virtual void release() const = 0;

	public:
		/**
		 * @brief �ش� ���� XML ���·� stdout�� �����
		 */
		virtual void printAsXML() const = 0;

		/**
		 * @brief �ش� ���� XML ������ ��Ʈ������ ������, ������ ũ�⺸�� ��Ʈ���� �� ��� (size-1)��ŭ�� ������
		 * @param buf ��Ʈ���� ���� ����
		 * @param size ��Ʈ���� ���� ������ ũ��
		 * @return XML ������ null-terminated string
		 */
		virtual const char* toXML(char *buf, unsigned int size) const = 0;
};


/** @}*/
} /*end of namespace mega*/


#endif
