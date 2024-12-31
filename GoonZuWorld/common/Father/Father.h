//---------------------------------
// 2004/2/25 ���°�
//---------------------------------
#ifndef _FATHER_H
#define _FATHER_H

#include <Directives.h>

#define ADD_FATHERSUPPLYER_ALREADY	1				// �̹� ��ϵǾ� �ִ�. 
#define ADD_FATHERSUPPLYER_FULL		2				// ����ڰ� ��á��. 
#define MAX_CHILD_LIST_IN_CLIENT_NUMBER		50		// ���İ��� �ִ� ��

class cltFatherManager{
public:
	RECT DlgRect;
	bool bDlgRectInitSwitch;

	bool bUpdateFatherSwitch;
	bool bUpdateFatherApplyerListSwitch;
	bool bUpdateChildListSwitch;

	// ���´� ��� ��û�� ���. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltFatherApplyerInfo, MAX_FATHER_APPLYER_LIST_NUMBER>	clApplyerList;
#else
	cltFatherApplyerInfo clApplyerList[MAX_FATHER_APPLYER_LIST_NUMBER];
#endif

	// ���ڴ� ����Ʈ. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltChildInfo, MAX_CHILD_LIST_IN_CLIENT_NUMBER>	clChildList;
#else
	cltChildInfo clChildList[MAX_CHILD_LIST_IN_CLIENT_NUMBER];
#endif

	SI32 m_siSelectedIndex ;								// ������ ����Ʈ ����Ÿ
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_FATHER_APPLYER_LIST_NUMBER>		m_siFatherApplyInx;
	NSafeTArray<SI32, MAX_CHILD_LIST_IN_CLIENT_NUMBER>		m_siChildListInx;
#else
	SI32 m_siFatherApplyInx[MAX_FATHER_APPLYER_LIST_NUMBER]; // ���� ��û�� ����Ʈ ������ ���� �ε���
	SI32 m_siChildListInx[MAX_CHILD_LIST_IN_CLIENT_NUMBER];	// ���� ����Ʈ ������ �� ����Ʈ ����Ÿ(��ġ)
#endif

	// ������������ �����Ѵ�. 
	void ChildSort(SI32 sisortdata[]);

	cltFatherManager();
	~cltFatherManager();
	
	// ���´��� �����ش�. 
	void ShowFatherName(HWND hDlg);
	// ���´� ����� ����� �����ش�. 
	void ShowFatherList();

	// ���´� ��� ��û�ڸ� �߰��Ѵ�. 
	bool AddApplyer(cltFatherApplyerInfo* pclinfo, SI32* preturnval);
	// ���´� ��� ��û�ڸ� ���� �Ѵ�. 
	bool DeleteApplyer(SI32 personid);
	// Ư�� ����ڰ� ����Ʈ�� �����ϴ°�. 
	bool IsExist(SI32 personid);


	// ���İ��� ����Ʈ�� ���Ѵ� 
	bool AddChildList(cltChildInfo* pclinfo);

	// ���İ��� ����Ʈ�� ��� �����Ѵ�. 
	void DelChildList();

	// ���İ��� �̸��� ���Ѵ�. 
	TCHAR* GetChildName(SI32 personid);

	void Action(cltCharManager* pclCM);

};

#endif