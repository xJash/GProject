/* ==========================================================================
	Ŭ���� :		CNHintDlg

	�ۼ��� :		05/04/24
	�ۼ��� :		���¾�

	��  �� :		.
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/
#pragma once

#include <Directives.h>
#include <stdio.h>

#include "../../Resource.h"
#include "../../InterfaceMgr/DialogController.h"

#define     MAX_HINTCOMBO_TYPE		20
#define     MAX_HINTLIST_TYPE		20


#define 	FAMELEVEL_GET	         1    //������� ȹ����
#define 	FISHING_READY	         2     //���ø� �ϱ� ���� �ʿ��� �غ�
#define 	FISHING_WISEANGLER	     3     //������ ���ñ��� �Ǵ� ���
#define 	FISHING_PLACE	         4     //���� �����ʹ�?
#define 	WHAT_REPORT	             5     //����� �Ű�� �����Դϱ�?
#define 	WHATIS_AUTO_REPORT	     6     //�ڵ� ���α׷��̶� �����Դϱ�?
#define 	HOWCANFIND_REPORT	     7     //��� �ڵ����α׷� ����ڸ� �������� �ֽ��ϱ�?
#define 	WHAT_DO_REPORT	         8     //�Ű� �ϸ� ��� �˴ϱ�?
#define 	FIND_AUTO_REPORT	     9     //�ڵ� ���α׷� ����ڷ� �Ǹ�Ǹ�?
#define 	IF_FALSE_ACCUSATIOR	     10    //���� �Ű��϶���?
#define 	ETC_ACCUSATION_REPORT    11    //��Ÿ �Ű� �Ұ����� ���  
#define 	HOK_WHO	                 12    //Ȥ�θ������� �����Դϱ�?
#define 	HOK_WHATJOB	             13    //Ȥ�θ������� �������� �մϱ�?
#define 	HOK_CREATE	             14    //ȣǰ. ��ǰ �����
#define 	HOK_UPGRADE	             15    //��ǰ �ɷ�ġ �ø��� 
#define 	HOK_FAILURE	             16    //Ȥ�θ� ������ �����ϸ�?
#define 	PERSONALMARKET_OPEN	     17    //���� ���� ����
#define 	PERSONALMARKET_USE	     18    //���� ���� �̿��
#define 	PERSONALMARKET_FIND	     19    //���� �������� �Ǹŵǰ� �ִ� ��ǰ �˻�	��
#define 	SWORD	                 20    //���� ����Ͻʴϱ�?
#define 	SPEAR	                 21    //â�� ����Ͻʴϱ�?
#define 	BOW	                     22    //Ȱ�� ����Ͻʴϱ�?
#define 	AXE	                     23    //������ ����Ͻʴϱ�?
#define 	GUN	                     24    //���� ����Ͻʴϱ�?
#define 	STAFF	                 25    //�����̸� ����Ͻʴϱ�?
#define 	WHAT_DIVIDEND	         26    //����̶� �����ΰ���?
#define 	STOCK_WHAT	             27    //���ֹ���̶�?
#define 	RESIDENTS_DIVIDEND	     28    //�ֹι���̶�?
#define 	DECISION_DIVIDEND	     29    //�ֹ� ���� ���ֹ���� ����
#define 	WHAT_CANNOTKILL	         30    //�Ұ��縮�� �����Դϱ�?
#define 	WHERE_CANNOTKILL	     31    //�Ұ��縮�� ��� ���� �ֽ��ϱ�?
#define 	HOWCANGET_CANNOTKILL     32    //�Ұ��縮�� ��� ������ �ֽ��ϱ�?
#define 	REWARD_CANNOTKILL	     33    //�Ұ��縮 �̺�Ʈ�� �����ϸ� � ������ �ֽ��ϱ�?
#define 	SUMMONSWHATIS	         34    //��ȯ���� �����Դϱ�?
#define 	SUMMONSLIFE	             35    //��ȯ���� ������?
#define 	SUMMONSHOWCANIGET        36    //��ȯ���� ��� ����ϱ�?
#define 	SUMMONSWELLBEING	     37    //��ȯ���� �� Ű��� �����?
#define 	SUMMONSEVOLUTION	     38    //��ȯ���� ��� ��ȭ�մϱ�?
#define 	SUMMONSUPGRADE	         39    //��ȯ���� ��� �������ϱ�?
#define 	SUMMONSDIE	             40    //��ȯ���� �������� ������?
#define     WHO_TEACHER              41    //���´��� �����Դϱ�?
#define     WANT_STUDENT             42    //���ڰ� �ǰ� ��������?
#define     CHANGE_TEACHER           43    //���´��� �ٲٰ� ��������?
#define     NOCONNECT_STUDENT        44    //���ڰ� �������� ������ ���� ������?
#define     WANT_TEACHER             45    //������ �ǰ� ��������?  
#define     WHAT_GOOD_TEACHER        46    //������ �Ǹ� ������ ��������?
#define 	HOZO_WHAT	             47    //ȣ�� �Ǽ��� �����Դϱ�?
#define 	HOZO_RECOMMAND	         48    //��õ�� ����� �����̶�?
#define 	HOZO_MONEY	             49    //�ű� ȸ�� �����ڱ��̶�?
#define 	HOZO_POPULATION	         50    //�� ���� �ֹ� �� �����̶�?
//#define 	HOWCANWIN_GOGURYO	     51    //���� ���� �̺�Ʈ�� �����Դϱ�?
//#define     OPEN_GOGURYO	         52    //���� ���� ��ȣ �̺�Ʈ�� ��� �ߵ��˴ϱ�?
//#define 	SUCESS_GOGURYO           53    //���� ���� ��ȣ �̺�Ʈ�� ������Ű�� �����?
//#define     REWARD_GOGURYO	         54    //���� ���� ��ȣ �̺�Ʈ�� ���� ������?
#define     VILLAGE_LEVEL            55    //���� �����̶� �����Դϱ�?
#define     WHAT_GOOD_VILLAGE        56    //���� ������ ������ ������ �����ϱ�?
#define     HOW_VILLAGE_LEVEL        57    //���� ������ ��� �ø��ϱ�?      
#define 	DOWN_TOWNLEVEL	         58    //���� ������ ��������?
#define 	PARTY_WHAT	             59    //��Ƽ ����̶�?
#define 	PARTY_MUSTKNOW	         60    //��Ƽ ���, �̰͸��� �˾� ���� 
#define 	HORSEWHAT	             61    //���� �����Դϱ�? 
#define 	HORSEWHATGOOD	         62    //���� Ű��� ������ �����ϱ�?
#define 	HORSEAGE	             63    //���� ������ ���ϸ�?
#define 	HORSEHOW	             64    //���� ��� ����ϱ�?
#define 	HORSEFREE	             65    //�� Ǯ���ֱ�?
#define 	HORSEHOWBREED	         66    //���� �� Ű��� �����?
#define 	HORSEITEM	             67    //������ ������ �ű�� ��
#define 	RECOMMAND_WHAT	         68    //��õ�� ������ �����ΰ���?
#define 	RECOMMAND_GOOD	         69    //��õ�� ������ ������ ��������?
#define 	RECOMMAND_WARNING	     70    //��õ�� �ÿ� ������ ��
#define 	STOCK_SUBSCRIPTION	     71    //���ֿ��� �ֽ��̶�?
#define 	STOCK_INCREASE	         72    //�ֽ� ���� �����غ���
#define 	STOCKHOLDER_DIVIDEND	 73    //�ֽ� ���ڿ� �����غ���
#define     WHAT_CAPITAL             74    //�ں����̶� �����ΰ���?
#define     HOW_CAPITAL              75    //�ں����� ��� ����°���?
#define     WHAT_PROFIT              76    //���ͱ��̶� �����ΰ���?
#define 	WAR_JOINING	             77    //�ֱ� ���￡ �����غ���
#define 	WAR_BONUSTIME	         78    //���ʽ� Ÿ��
#define 	WHATGOOD_GOODPRODUCT     79    //��ǰ�̶� �����Դϱ�?
#define 	HOWCANGET_GOODPRODUCT    80    //��ǰ�� ��� ������ �ֽ��ϱ�?
#define     WHAT_GOODPRODUCT         81    //��ǰ�� ��� �Ǹ� ������ �����ϱ�?
#define     WHAT_FAME                82    // �� ����� ����	
#define     WHAT_ENCHANT                83    //��æƮ��


class CStatic;
class CButton;
class CComboBox;
class CList;
class CEdit;

class NHintDlgExplain : public CDialogController
{
public:
	NHintDlgExplain();
	~NHintDlgExplain();

	//void AddComboType(TCHAR *szName,TCHAR *szFile);

	void Create();

	static void CALLBACK NHintDlgExplainStaticProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NHintDlgExplainProc( UINT nEvent, int nControlID, CControllerObj* pControl);

	SI32 GetExplainType(TCHAR* pExplainType);
	void ShowExplainHint(SI32 siHintType);

	void Show(TCHAR * szFileName ) ;
	void Set(TCHAR * szFileName ) ;

	void ReadListFile();
	void ShowList(TCHAR * szFileName, SI16 txtSize);

private:
	//HWND			m_hWnd;
	//HINSTANCE		m_hInst;

	//HWND	m_hDlg;	
	//RECT	m_DlgRect;
	//HBITMAP m_hHitBitmap;
	BOOL	m_DlgRectInitSwitch;

	TCHAR	m_szBmpName[MAX_HINTCOMBO_TYPE][128] ;
	TCHAR	m_szComboType[MAX_HINTCOMBO_TYPE][256] ;

	TCHAR	m_szListType[MAX_HINTLIST_TYPE][128] ;
	TCHAR	m_szSubject[MAX_HINTLIST_TYPE][128] ;

	//CStatic     	*m_pNHintStatic1; 
	CStatic     	*m_pNHintStatic2;
    CStatic     	*m_pNHintStatic3;
	CComboBox       *m_pNHintCombo;
	CList     	    *m_pNHintList;
	CButton     	*m_pNHintButton;
	CEdit     	    *m_pNHintEdit;

};

