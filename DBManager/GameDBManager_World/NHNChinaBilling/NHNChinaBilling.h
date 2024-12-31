/*!
  * @file nhnchinabillinglib.h
  * @brief
  * @author kelovon <kelovon@nhncorp.com>
  * @date $Date: 2007-04-18$
  * @version $Revision: $
  * $Id: $
  */

#ifndef __NHNCHINABILLINGLIB_H_BFDB17F1_37A7_476A_A49E_A453FFF7B8C3__
#define __NHNCHINABILLINGLIB_H_BFDB17F1_37A7_476A_A49E_A453FFF7B8C3__

#ifdef _NHNCHINA_DLL

#ifdef NHNCHINADLL_EXPORTS
#define NHNCHINADLL_API __declspec(dllexport)
#else
#define NHNCHINADLL_API __declspec(dllimport)
#endif

#else // _NHNCHINA_DLL

#define NHNCHINADLL_API

#endif // _NHNCHINA_DLL

#include "nhnchinautil.h"

#define NHNCHINABILLING_MSG_SIZE			200
#define NHNCHINABILLING_LOGSEQ_SIZE			20+1

namespace NHNChinaBilling
{
	typedef NHNChinaUtil::Connection Connection;

	/*!
	  * @brief �� �Լ��� ��� �ڵ�
	  */
	enum ReturnCode
	{
		SUCC,	// ����
		FAIL,	// �ý��� ����
		R001,	// ���� Invalid Parameter  �Ķ���Ͱ� ���̰ų� ���� ���  
		R002,	// ���� Invalid Parameter (svrid)  ��ϵ� ������ �ƴ� ���  
		R003,	// ���� Invalid Account (status)  ���� ���°� Y �� �ƴ� ���  
		R004,	// ���� Invalid Coinlog (status)  �ش� logseq ���� �̹� ��Ұ� �� ���  
		R005,	// ���� Invalid Coinlog (logseq)  �ش� logseq ���� ���� ���  
		C001,	// ���� Invalid Parameter (pgid)  ��ϵ� ���������� �ƴ� ���  
		C002,	// ���� Invalid Parameter (logseq)  �ش� logseq �� �����α� table �� ���� ���  
		U001,	// ���� Invalid Parameter (itemid)  ��ϵ� ��ǰ�� �ƴ� ���  
		U002,	// ���� Invalid Parameter (price)  �ݾ� / �Ǽ� �� ��ϵ� ���ݰ� �ٸ� ���  
		U003,	// ���� Invalid Account (balance)  �ܾ��� ������ ���  
		U004,	// ���� Invalid Account (userid)  �ش� ���̵��� ���°� ���� ���
		U005,	// ���� Duplication (authno) authno�� �ߺ��� ���
		NONE
	};

	NHNCHINADLL_API inline const char* getStateString(ReturnCode s);
	/*!
	  * @brief ���
	  * @param con Connection instance
	  * @param gameid ����ID (C_R2,C_BD,C_GZ..etc)
	  * @param svrid world id
	  * @param userid customer id
	  * @param charid character id
	  * @param itemid item id
	  * @param authno ���� ��ȣ(ourgame FK)
	  * @param cnt �Ǽ�
	  * @param amt ���� �ݾ�
	  * @param clientip ������
	  * @param memo �޸�
	  * @param joincode ���޻��ڵ�
	  * @param msg ���� �޽����� ������ ����, char[NHNCHINABILLING_MSG_SIZE]�� ������
	  * @param logseq ���� �ֹ� ��ȣ�� ������ NHNCHINABILLING_LOGSEQ_SIZE ����, ������ ���� 20 byte string, �� �ܿ��� NULL
	  * @return ó�� ���
	  */
	NHNCHINADLL_API ReturnCode UseCoin(const Connection &con,
							const char *gameid,
							int svrid,
							const char *userid,
							const char *charid,
							const char *itemid,
							__int64 authno,
							int cnt,
							__int64 amt,
							const char *clientip,
							const char *memo,
							const char *joincode,
							char *msg,
							char *logseq);

	/*!
	  * @brief �ܾ� ��ȸ
	  * @param con Connection instance
	  * @param gameid ����ID (C_R2,C_BD,C_GZ..etc)
	  * @param svrid world id
	  * @param userid customer id
	  * @param msg ���� �޽����� ������ ����, char[NHNCHINABILLING_MSG_SIZE]�� ������
	  * @param balance �ܾ�
	  * @return ó�� ���
	  */
	NHNCHINADLL_API ReturnCode GetBalance(const Connection &con,
							const char *gameid,
							int svrid,
							const char *userid,
							char *msg,
							__int64 *balance1,
							__int64 *balance2
							);

	/*!
	* @brief Gift ��ȸ
	* @param con Connection instance
	* @param gameid ����ID (C_R2,C_BD,C_GZ..etc)
	* @param svrid world id
	* @param userid customer id
	* @param msg ���� �޽����� ������ ����, char[NHNCHINABILLING_MSG_SIZE]�� ������
	* @param balance �ܾ�
	* @param balance1 �ܾ�1
	* @param balance2 �ܾ�2
	* @return ó�� ���
	*/
	NHNCHINADLL_API ReturnCode GiftBalance(const Connection &con,
		const char *gameid,
		int svrid,
		const char *userid,
		char *msg,
		__int64 *balance,
		__int64 *balance1,
		__int64 *balance2
		);

	/*!
	* @brief ���
	* @param con Connection instance
	* @param gameid ����ID (C_R2,C_BD,C_GZ..etc)
	* @param svrid world id
	* @param userid customer id
	* @param charid character id
	* @param itemid item id
	* @param authno ���� ��ȣ(ourgame FK)
	* @param cnt �Ǽ�
	* @param amt ���� �ݾ�
	* @param clientip ������
	* @param memo �޸�
	* @param joincode ���޻��ڵ�
	* @param msg ���� �޽����� ������ ����, char[NHNCHINABILLING_MSG_SIZE]�� ������
	* @param logseq ���� �ֹ� ��ȣ�� ������ NHNCHINABILLING_LOGSEQ_SIZE ����, ������ ���� 20 byte string, �� �ܿ��� NULL
	* @return ó�� ���
	*/
	NHNCHINADLL_API ReturnCode GiftCoin(const Connection &con,
		const char *gameid,
		int svrid,
		const char *userid,
		const char *charid,
		const char *itemid,
		__int64 authno,
		int cnt,
		__int64 amt,
		__int64 giftamt,
		const char *clientip,
		const char *memo,
		const char *joincode,
		char *msg,
		char *logseq);

	/*!
	* @brief ����
	* @param gameid		����ID (C_R2,C_BD,C_GZ..etc)
	* @param userid		customer id
	* @param svrid		world id
	* @param activecode	
	* @param authno		
	* @param giftamt	
	* @param start_dt	
	* @param end_dt		
	* @param clientip	ip
	* @param chn_id
	* @param msg
	* @param giftno
	* @return ó�� ���
	*/
// 	NHNCHINADLL_API ReturnCode ChargeCoin(const Connection &con,
// 		const char *gameid,
// 		const char *userid,
// 		int svrid,
// 		int activecode,
// 		__int64 authno,
// 		__int64 giftamt,
// 		const char *start_dt,
// 		const char *end_dt,
// 		const char *clientip,
// 		const char *chn_id,
// 		char *msg,
// 		__int64 *giftno
// 		);
	/*!
	  * @brief ȯ�� ���
	  * @param exgkind	ȯ������, 0: ���, 1:�ǹ�
	  * @param gameid ����ID (C_R2,C_BD,C_GZ..etc)
	  * @param svrid	world id
	  * @param userid	customer id
	  * @param charid	character id
	  * @param authno	������ȣ (R2 FK)
	  * @param amt	���ݾ�
	  * @param silveramt	���ݾ�
	  * @param clientip	ip
	  * @param memo	�޸�
	  * @param msg ���� �޽����� ������ ����, char[NHNCHINABILLING_MSG_SIZE]�� ������
	  * @param logseq_out ���� �ֹ� ��ȣ�� ������ NHNCHINABILLING_LOGSEQ_SIZE ����, ������ ���� 20 byte string, �� �ܿ��� NULL
	  * @return ó�� ���
	  */
	NHNCHINADLL_API ReturnCode RegisterExchange(const Connection &con,
							int exgkind,
							const char *gameid,
							int svrid,
							const char *userid,
							const char *charid,
							__int64 authno,
							__int64 amt,
							__int64 silveramt,
							const char *clientip,
							const char *memo,
							char *msg,
							char *logseq_out);

	/*!
	  * @brief ȯ�� ���
	  * @param logseq	ȯ����ȣ
	  * @param gameid ����ID (C_R2,C_BD,C_GZ..etc)
	  * @param svrid	world id
	  * @param userid	customer id
	  * @param authno	������ȣ (R2 FK)
	  * @param clientip	ip
	  * @param memo	�޸�
	  * @param msg ���� �޽����� ������ ����, char[NHNCHINABILLING_MSG_SIZE]�� ������
	  * @param logseq_out ���� �ֹ� ��ȣ�� ������ NHNCHINABILLING_LOGSEQ_SIZE ����, ������ ���� 20 byte string, �� �ܿ��� NULL
	  * @return ó�� ���
	  */
	NHNCHINADLL_API ReturnCode CancelExchange(const Connection &con,
							const char *logseq,
							const char *gameid,
							int svrid,	
							const char *userid,	
							__int64 authno,	
							const char *clientip,
							const char *memo,	
							char *msg,
							char *logseq_out);

	/*!
	  * @brief ȯ�� �Ϸ�
	  * @param cmpKind  0: �Ǹ��� �Ϸ�, 1: ������ �Ϸ�
	  * @param logseq	ȯ����ȣ
	  * @param gameid ����ID (C_R2,C_BD,C_GZ..etc)
	  * @param svrid	world id
	  * @param userid	customer id
	  * @param charid	character id
	  * @param authno	������ȣ (R2 FK)
	  * @param amt	���ݾ�
	  * @param silveramt	�ǹ��ݾ�
	  * @param clientip	ip
	  * @param memo	�޸�
	  * @param msg ���� �޽����� ������ ����, char[NHNCHINABILLING_MSG_SIZE]�� ������
	  * @param logseq_out ���� �ֹ� ��ȣ�� ������ NHNCHINABILLING_LOGSEQ_SIZE ����, ������ ���� 20 byte string, �� �ܿ��� NULL
	  * @return ó�� ���
	  */
	NHNCHINADLL_API ReturnCode CompleteExchange(const Connection &con,
							int cmpKind,
							const char *logseq,
							const char *gameid,
							int svrid,
							const char *userid,
							const char *charid,
							__int64 authno,
							__int64 amt,
							__int64 silveramt,
							const char *clientip,
							const char *memo,
							char *msg,
							char *logseq_out);

} // end of NHNChinaBilling

#endif /*__NHNCHINABILLINGLIB_H_BFDB17F1_37A7_476A_A49E_A453FFF7B8C3__*/
