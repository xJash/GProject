/*
//---------------------------------
// 2004/2/10 ���°�
//---------------------------------
#include <Windows.h>
#include <Directives.h>

#define MAX_SCHOOL_AREA				40

#define SCHOOLAREA_SEOUL			1		// ����.
#define SCHOOLAREA_KANGWON			2		// ����. 
#define SCHOOLAREA_KYOUNGBOOK		3		// ���ϵ� 
#define SCHOOLAREA_KWANGJU			4		// ����. 
#define SCHOOLAREA_DAIGU			5		// �뱸
#define SCHOOLAREA_BOOSAN			6		// �λ�. 
#define SCHOOLAREA_JOUNNAM			7		// ���󳲵� 
#define SCHOOLAREA_CHOONGBOOK		8		// ��û�ϵ�
#define SCHOOLAREA_KYOUNGKI			9		// ��⵵ 
#define SCHOOLAREA_KYOUNGNAM		10		// ��󳲵� 
#define SCHOOLAREA_CHINA			11		// �߱� 
#define SCHOOLAREA_WOOLSAN			12		// ��� 
#define SCHOOLAREA_CHOONGNAM		13		// ��û����
#define SCHOOLAREA_JOUNBOOK			14		// ����ϵ� 
#define SCHOOLAREA_INCHEON			15		// ��õ 
#define SCHOOLAREA_ZEJU				16		// ���ֵ� 
#define SCHOOLAREA_DAIJEON			17		// ���� 
#define SCHOOLAREA_WONJU			18		// ����
#define SCHOOLAREA_CANADA			19		// ĳ����
#define SCHOOLAREA_CHEONAN			20		// õ��
#define SCHOOLAREA_SINGAPORE		21		// �̰�����
#define SCHOOLAREA_NEWZEALAND		22		// ��������
#define SCHOOLAREA_USA				23		// �̱�
#define SCHOOLAREA_CHUNCHEON		24		// ��õ

#define MAX_SCHOOL_GRADE			10

#define SCHOOLGRADE_PRI				1		// �ʵ�.
#define SCHOOLGRADE_MID				2		// �ߵ�.
#define SCHOOLGRADE_HIG				3		// ���.
#define SCHOOLGRADE_UNV				4		// ��
#define SCHOOLGRADE_SECON			5		// Secondary
#define SCHOOLGRADE_INTER			6		// InternationalSchool
#define SCHOOLGRADE_HIGH			7		// HighSchool

#define MAX_SCHOOL_NUMBER			1000

#define MAX_SCHOOL_NAME_SIZE		32

//-------------------------------
// �б� ���� 
//------------------------------
class cltSchoolArea{
public:
	char szName[32];


	cltSchoolArea()
	{
		strcpy(szName, "");
	}

	cltSchoolArea(char* pname)
	{
		strcpy(szName, pname);
	}

	void Set(cltSchoolArea* pclarea)
	{
		strcpy(szName, pclarea->szName);
	}
	
};

//-----------------------------
// �б���� 
//-----------------------------
class cltSchoolGrade{
public:
	char szName[32];

	cltSchoolGrade()
	{
		strcpy(szName, "");
	}

	cltSchoolGrade(char* pname)
	{
		strcpy(szName, pname);
	}

	void Set(cltSchoolGrade* pclgrade)
	{
		strcpy(szName, pclgrade->szName);
	}
};

//-----------------------------
// ���� �б� ����. 
//-----------------------------
class cltSchool{
public:
	SI16 siUnique;
	SI16 siAreaCode;				// �����ڵ� 
	SI16 siGradeCode;				// ����ڵ� (���߰��)
	char szName[MAX_SCHOOL_NAME_SIZE];	// �б� �̸�. 
	SI16 siFile;
	SI16 siIconIndex;					// ������ �̹��� �ε���. 


	cltSchool()
	{
		Init();
	}
	cltSchool(SI16 unique, SI16 areacode, SI16 gradecode, char* pname, SI16 file, SI16 icon)
	{
		siUnique	= unique;
		siAreaCode	= areacode;
		siGradeCode	= gradecode;
		MStrCpy( szName, pname, MAX_SCHOOL_NAME_SIZE );
		siFile		= file;
		siIconIndex	= icon;
	}

	void Init()
	{
		siUnique	= 0;
		siAreaCode	= 0;
		siGradeCode	= 0;
		strcpy(szName, "");
		siFile		= 0;
		siIconIndex = 0;
	}

	void Set(cltSchool* pclschool)
	{
		siUnique	= pclschool->siUnique;
		siAreaCode	= pclschool->siAreaCode;
		siGradeCode	= pclschool->siGradeCode;
		strcpy(szName, pclschool->szName);
		siFile		= pclschool->siFile;
		siIconIndex = pclschool->siIconIndex;
	}

	// ��ü �̸��� ���Ѵ�. 
	bool GetFullName(cltSchoolManager* pchoolmanager, char* pname);

};

//------------------------
// �б� ������. 
//------------------------
class cltSchoolManager{
public:

	HWND m_hDlg;					// ������ ����. 

	RECT DlgRect;
	bool bDlgRectInitSwitch;
	

	SI32			siCurrentSchoolUnique;
	bool			bShowUserNumSwitch;
	SI32			siUserNum;

	SI32			siSchoolIndex;
	cltSchool		clSchool[MAX_SCHOOL_NUMBER];
	cltSchoolArea	clSchoolArea[MAX_SCHOOL_AREA];
	cltSchoolGrade	clSchoolGrade[MAX_SCHOOL_GRADE];

	// ���� �ڵ�.
	SI32			siCurrentSchoolArea;
	// ��� �ڵ� 
	SI32			siCurrentSchoolGrade;

	cltSchoolManager();
	~cltSchoolManager();

	BOOL CreateDlg(HINSTANCE hinst, HWND hwnd);
	static BOOL CALLBACK StaticDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	// �б������ ����Ѵ�. 
	bool AddGrade(SI32 areacode, cltSchoolGrade* pclgrade);

	// ��޸��� �ٰŷ� ��� �ڵ带 ��´�. 
	SI32 GetGradeCode(char* pname);

	// �б������� ����Ѵ�. 
	bool AddArea(SI32 areacode, cltSchoolArea* pclarea);

	// �������� �ٰŷ� ���� �ڵ带 ��´�. 
	SI32 GetAreaCode(char* pname);

	// �б��� ����Ѵ�. 
	bool Add(cltSchool* pclschool);

	//�б������ �����ش�.  
	void ShowSchoolList();

	// ����ũ�� �ٰŷ� ref�� ���Ѵ�. 
	SI32 GetRefFromUnique(SI32 unique);

	// �б� ����Ʈ�� ����Ѵ�. 
	void SetSchoolList();

	// �б� �ΰ� ����Ѵ�. 
	void DrawLogo(SI32 schoolunique);


};
*/