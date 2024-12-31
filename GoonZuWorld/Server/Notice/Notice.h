#ifndef _NOTICE_H
#define _NOTICE_H

#define MAX_NOTICE_TEXT_SIZE	1024
#define MAX_NOTICE_NUM			10


#include <Directives.h>
#include "../../../NLib/NArray.h"

//----------------------------
// �ϳ��ϳ��� ���� ����. 
//----------------------------
class cltNoticeUnit{
public:
	TCHAR szNoticeText[MAX_NOTICE_TEXT_SIZE];
	DWORD dwStartFrame;	// ù ��� ������. 
	DWORD dwInterval;	// ��� ����. 


	cltNoticeUnit()
	{
		Init();
	}

	void Init()
	{
		StringCchCopy(szNoticeText, MAX_NOTICE_TEXT_SIZE, TEXT(""));
		dwStartFrame	= 0;
		dwInterval		= 0;

	}

	void Set(DWORD startframe, DWORD interval, TCHAR* ptext)
	{
		dwStartFrame	= startframe;
		dwInterval		= interval;
		StringCchCopy(szNoticeText, MAX_NOTICE_TEXT_SIZE, ptext);
	}
};

//------------------------------
// ���� ������.
//-----------------------------
class cltNoticeManager{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltNoticeUnit, MAX_NOTICE_NUM>		clNotice;
	NSafeTArray<SI32, MAX_NOTICE_NUM>		Counting;	// ���� ������ ���� Ƚ��
	NSafeTArray<SI32, MAX_NOTICE_NUM>		Count;		// ��ǥ ���� 
#else
	cltNoticeUnit clNotice[MAX_NOTICE_NUM];
	SI32 Counting[MAX_NOTICE_NUM];
	SI32 Count[MAX_NOTICE_NUM];
#endif

	//�α��� ���� 
	bool bLoginNoticeSwitch;
	TCHAR szLogInNotice[2048];

	cltNoticeManager();
	~cltNoticeManager();

	// ������ �߰��Ѵ�. 
	void Add(DWORD interval, TCHAR* ptext , SI32 siCount);	// �ݺ�Ƚ�� �߰�

	// ������ �����ش�. 
	void Action();

	// ��� ������ �����. 
	void DelAllNotice();

	// �α��� ������ on/ff
	void OnOffLogInNotice();

};


#endif
