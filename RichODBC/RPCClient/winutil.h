/**
	@file 
	@brief ������ ��ƿ��Ƽ��
	@author rapool
	@version $Revision: 1.0 $
	@date $Date: 2006/03/20 14:00:00 $

	$Id: filemng.h,v 1.0 2006/03/20 14:00:00 rapool Exp $
 */

#ifndef _NANO_WINUTILITIES_H_
#define _NANO_WINUTILITIES_H_

#include "common.h"
#include <float.h>
#include <limits.h>
#include <time.h>

namespace nano {
/**
	@addtogroup unixutilities
	@{
 */


#ifndef __DBL_EPSILON__
#define __DBL_EPSILON__ DBL_EPSILON
#endif
/**
 * @brief �������� ȣȯ���� ���Ͽ� timeval ����ü�� ������
 * @remark ���������� ���� ���̴� timeval ����ü�� �������� �������� �����Ƿ� ���� ������
 */
struct timeval
{
	long tv_sec; // second
	long tv_usec; // microsecond
};
/* end of struct timeval */


/**
 * @brief linux::gettimeofday()
 * @param tv ���ϵ� �ð����� �����ϴ� ����
 * @param tzp ������ (NULL�� �ѱ�� ��)
 * @remark timeval::tv_usec�� milli-second���� ��Ȯ�� (�������� micro-second�� ���ϴ� API�� �𸣰���)
 */
int gettimeofday(struct timeval *tv, void *tzp);

/**
 * @brief ��ҹ��� ���� ���� ���ڿ��� ������ ��
 * @param a ���ڿ�
 * @param b ���ڿ�
 * @return ������ 0, a > b �̸� +, a < b �̸� -
 */
int strcasecmp(const char *a, const char *b);

/**
 * @brief ��ҹ��� ���� ���� ���ڿ��� ������ ��
 * @param a ���ڿ�
 * @param b ���ڿ�
 * @param n ���ϰ��� �ϴ� ����Ʈ��
 * @return ������ 0, a > b �̸� +, a < b �̸� -
 */
int strncasecmp(const char *a, const char *b, size_t n);

/**
 * @brief POSIX::strtoll()�� ������ ����
 * @param __int64�� ��ȯ�ϰ��� �ϴ� string
 * @param nptr���� invalid�� ���ڿ��� ó�� ��ġ
 * @param base ������ ǥ��
 */
__int64 strtoll(const char *nptr, char **endptr, int base);

/**
 * @brief ���밪�� ����
 * @param value ��
 */
__int64 llabs(__int64 value);

/** @} */


} // end of namespcae nano

#endif
