/*!
  * @file nhnchinautil.h
  * @brief 
  * @author kelovon <kelovon@nhncorp.com>
  * @date $Date: 2007-05-17$
  * @version $Revision: $
  * $Id: $
  */

#ifndef __NHNCHINAUTIL_H_C0AE92BE_9587_4E9C_985E_CF707A55551A__
#define __NHNCHINAUTIL_H_C0AE92BE_9587_4E9C_985E_CF707A55551A__

#include <windows.h>

#ifdef _NHNCHINA_DLL

#ifdef NHNCHINADLL_EXPORTS
#define NHNCHINADLL_API __declspec(dllexport)
#else
#define NHNCHINADLL_API __declspec(dllimport)
	//#ifdef _DEBUG
	//	#pragma comment(lib, "NHNChinaBillingDllD.lib") 
	//	#pragma comment(lib, "NHNChinaBillingLibD.lib") 
	//#else
	//	#pragma comment(lib, "NHNChinaBillingDll.lib") 
	//	#pragma comment(lib, "NHNChinaBillingLib.lib") 
	//#endif //_DEBUG

#endif

#else // _NHNCHINA_DLL

#define NHNCHINADLL_API

#endif // _NHNCHINA_DLL

namespace NHNChinaUtil
{
	/**
	 * @brief Charset ��ȣ (Microsoft Code Page ��ȣ�� ������)
	 */
	enum CodePage
	{
		IDENTITY 	= 0, 			/**< Charset ���� */
		US_ASCII 	= 20127, 		/**< us-ascii (7 bit) */
		UTF_8 		= 65001, 		/**< utf-8 */
		UTF_16_LE 	= 1200, 		/**< utf-16 (little endian) */
		UTF_16_BE 	= 1201, 		/**< utf-16 (big endian) */
		MS_932 		= 932, 			/**< Microsoft Code Page 932 (Japanese) */
		MS_936 		= 936, 			/**< Microsoft Code Page 936 (Chinese Simplified) */
		MS_949 		= 949, 			/**< Microsoft Code Page 949 (Korean) */
		MS_950 		= 950, 			/**< Microsoft Code page 950 (Chinese Traditional) */
		MS_1252 	= 1252, 		/**< Microsoft Code Page 1252 (Western Europe) */
		EUC_JP 		= 51932, 		/**< euc-jp */
		SHIFT_JIS 	= MS_932, 		/**< shift-jis */
		GB 			= MS_936,		/**< gb2312-1980 */
		GB2312 		= MS_936, 		/**< gb2312-1980 */
		GBK 		= MS_936, 		/**< gbk */
		KSC5601 	= MS_949, 		/**< ks_c_5601-1987 */
		EUC_KR 		= MS_949, 		/**< euc-kr */
		UHC 		= MS_949, 		/**< unified hangul code */
		BIG5 		= MS_950, 		/**< big5 */
		LATIN_1 	= MS_1252, 		/**< latin1 */
		ISO_8859_1 	= MS_1252, 		/**< iso-8859-1 */
	};

	/*!
	  * @brief DBGW���� ���� ������ �����ϴ� class
	  */
	class NHNCHINADLL_API Connection
	{
	public:
		enum ConnType
		{
			CONN_NONE,			// default
			CONN_DIRECT,		// connect by ip, port
			CONN_SERVICENAME,	// connect by service name
		};

		/*!
		  * @brief ip, port�� �̿��Ͽ� ���� ������ ��� ����ϴ� ctor
		  * @param dbgwip DBGW�� IP
		  * @param dbgwport DBGW�� port
		  * @remark Connection�� default charset�� GB2312��
		  */
		Connection(const char *dbgwip, int dbgwport, bool encryption = false);

		/*!
		  * @brief ���丮 ���񽺸� �̿��Ͽ� ������ ��� ��� ctor
		  * @param servicename DBGW�� service name
		  * @param filename local directory ���� ���� �̸�, �⺻��: server.xml
		  * @remark Connection�� default charset�� GB2312��
		  */
		Connection(const char *servicename, bool encryption = false, const char *filename = NULL);

		/*!
		  * @brief payload�� character set�� �����Ѵ�.
		  * @param codepage mega::CodePage ����
		  */
		void SetCharacterSet(CodePage codepage);

		/*!
		  * @brief payload�� character set�� �����´�.
		  * @return mega::CodePage
		  */
		CodePage GetCharacterSet() const;

		/*!
		  * @brief dtor
		  */
		~Connection();

	private:
		Connection() {}

	public:
		class NHNCHINADLL_API Str
		{
		private:
			const char *_p;
		public:
			Str(const char *s) 
			{
				_p = _strdup(s);
			}
			Str() : _p(NULL) {}
			~Str() { if (NULL != _p) free ((void *)_p); }
			operator const char *() const { return _p; }
		};

	public:
		ConnType		connType;
		Str				dbgwip;
		int				dbgwport;
		Str				servicename;
		Str				localDirFileName;
		bool			encryptedPacket;
		CodePage		codePage;
	};

} // end of namespace NHNChinaUtil

#endif /*__NHNCHINAUTIL_H_C0AE92BE_9587_4E9C_985E_CF707A55551A__*/

