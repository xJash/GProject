//---------------------------------
// 2008/05/22 �̰���
//---------------------------------

#include "MoneyStatistics.h"

void cltMoneyStatistics::Action()
{
	if(m_kUpdateTimer_Action.IsTimed(::GetTickCount()) == false)		return;

	// ���� �����Ͱ� �߰�
	ReadStatistics();

	// ������ �� ���
	WriteStatistics();

	// ������ �ʱ�ȭ
	if(m_Row)		ZeroMemory(m_Row, sizeof(SI64) * m_siColumnCount);
}


bool cltMoneyStatistics::CreateFile()
{
	NTCHARString<64>	FileName;
	FileName = "Config\\";
	FileName += m_kFileName;
	FileName += ".log";

	FILE*	fp = fopen(FileName, "w");

	if( fp == NULL )			return false;

	for(SI32 i=0; i<m_siColumnCount; i++)
	{
		fprintf(fp, "%s\t", (const TCHAR*)m_pColumnNames[i]);
	}
	fprintf(fp, "\n" );

	fclose(fp);

	return true;
}

bool cltMoneyStatistics::ChangeExistFileName()
{
	NTCHARString<64>	SrcFileName;
	SrcFileName = "Config\\";
	SrcFileName += m_kFileName;
	SrcFileName += ".log";

	SYSTEMTIME	stLocal;	GetLocalTime(&stLocal);

	TCHAR	szDateTime[32] = { 0, };
	StringCchPrintf(szDateTime, sizeof(szDateTime), "%04d%02d%02d_%02d%02d%02d", stLocal.wYear, stLocal.wMonth, stLocal.wDay, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
	szDateTime[sizeof(szDateTime)-1] = '\0';

	NTCHARString<64>	DstFileName;
	DstFileName = "Config\\";
	DstFileName += m_kFileName;
	DstFileName += szDateTime;
	DstFileName += ".log";

	::MoveFile(SrcFileName, DstFileName);

	return true;
}


int cltMoneyStatistics::CheckColumn()
{
	NTCHARString<64>	FileName;
	FileName = "Config\\";
	FileName += m_kFileName;
	FileName += ".log";

	FILE*	fp = fopen(FileName, "r");
	if( fp == NULL )			return -1;

	TCHAR	szLine[1024];	
	if( fgets(szLine, sizeof(szLine), fp) == NULL)		return 0;

	SI32	siColumnCount = 0;

	TCHAR*	pTok = _tcstok(szLine, "\t");
	while(pTok)
	{
		siColumnCount++;
		pTok = _tcstok(NULL, "\t");
	}

	fclose(fp);

	if( siColumnCount - 1 != m_siColumnCount )		return 0;

	return 1;
}

bool cltMoneyStatistics::WriteStatistics()
{
	NTCHARString<64>	FileName;
	FileName = "Config\\";
	FileName += m_kFileName;
	FileName += ".log";

	FILE* fp = fopen(FileName, "r+");
	if( fp == NULL )			return false;

	// ���� ũ��
	fseek(fp, 0, SEEK_END);
	SI32	siFileSize = ftell(fp);

	// �ٽ� ó������
	fseek(fp, 0, SEEK_SET);

	SI32	siFilePos = 0;
	SI32	siFilePrev = 0;

	siFilePrev = siFilePos;	
	siFilePos = ftell(fp);

	// ù���� �÷����̴�.
	TCHAR	szLine[1024];	
	if( fgets(szLine, sizeof(szLine), fp) == NULL)		return false;

	bool bUnlimit = true;
	while(bUnlimit)
	{
		siFilePos = ftell(fp);
		if( fgets(szLine, sizeof(szLine), fp) == NULL )		break;

		siFilePrev = siFilePos;
	}

	SYSTEMTIME	stLocal;	GetLocalTime(&stLocal);
	TCHAR	szDateTime[16] = { 0, };
	StringCchPrintf(szDateTime, sizeof(szDateTime), "%04d-%02d-%02d", stLocal.wYear, stLocal.wMonth, stLocal.wDay );

	fseek(fp, siFilePrev, SEEK_SET);
	fgets(szLine, sizeof(szLine), fp);

	// ù �÷��� �а� ��¥�� ���Ѵ�.
	TCHAR* pTok = _tcstok(szLine, "\t");
	if( pTok != NULL && _tcsncmp(pTok, szDateTime, sizeof(szDateTime)) == 0 )
	{
		siFilePos = siFilePrev;
	}
	else
	{
		siFilePos = siFileSize;
	}

	fseek(fp, siFilePos, SEEK_SET);

	fprintf(fp, "%s\t", szDateTime);
	for(SI32 i=1; i<m_siColumnCount; i++)
	{
		fprintf(fp, "%I64d\t", m_Row[i]);
	}
	fprintf(fp, "\n" );

	fclose(fp);

	return true;
}

bool cltMoneyStatistics::ReadStatistics()
{
	NTCHARString<64>	FileName;
	FileName = "Config\\";
	FileName += m_kFileName;
	FileName += ".log";

	FILE* fp = fopen(FileName, "r");
	if( fp == NULL )			return false;

	// ���� ũ��
	fseek(fp, 0, SEEK_END);
	SI32	siFileSize = ftell(fp);

	// �ٽ� ó������
	fseek(fp, 0, SEEK_SET);

	SI32	siFilePos = 0;
	SI32	siFilePrev = 0;

	siFilePrev = siFilePos;	
	siFilePos = ftell(fp);

	// ù���� �÷����̴�.
	TCHAR	szLine[1024];	
	if( fgets(szLine, sizeof(szLine), fp) == NULL)		return false;

	bool bUnlimit = true;
	while(bUnlimit)
	{
		siFilePos = ftell(fp);
		if( fgets(szLine, sizeof(szLine), fp) == NULL )		break;

		siFilePrev = siFilePos;
	}

	SYSTEMTIME	stLocal;	GetLocalTime(&stLocal);
	TCHAR	szDateTime[16] = { 0, };
	StringCchPrintf(szDateTime, sizeof(szDateTime), "%04d-%02d-%02d", stLocal.wYear, stLocal.wMonth, stLocal.wDay );

	fseek(fp, siFilePrev, SEEK_SET);
	fgets(szLine, sizeof(szLine), fp);

	// ù �÷��� �а� ��¥�� ���Ѵ�.
	TCHAR* pTok = _tcstok(szLine, "\t");
	SI32 i=1;
	if( pTok != NULL && _tcsncmp(pTok, szDateTime, sizeof(szDateTime)) == 0 )
	{
		while( (pTok = _tcstok(NULL, "\t")) != NULL )
		{
			if( i < m_siColumnCount )
			{
				m_Row[i] += _tstoi64(pTok);
				i++;
			}
		}
	}

	fclose(fp);

	return true;
}

void cltAddMoneyStatistics::Init(SI32 siColumnCount)
{
	if( siColumnCount <= 0 )			return;

	m_pColumnNames = new NTCHARString<32>[siColumnCount];
	m_Row = new SI64[siColumnCount];

	if(m_pColumnNames == NULL)			return;
	if(m_Row == NULL)					return;

	ZeroMemory(m_Row, sizeof(SI64) * siColumnCount);

	m_siColumnCount = siColumnCount;

#ifdef _DEBUG
	m_kUpdateTimer_Action.Init(60 * 1000);
#else
	m_kUpdateTimer_Action.Init(10 * 60 * 1000);
#endif
	m_kUpdateTimer_Action.SetActive(true, ::GetTickCount());

	//===========================================================
	m_kFileName = "AddMoney";
	//===========================================================

	//===========================================================
	// ���� �̸� ���� - �÷��� �߰��Ǹ�, ���ʿ� �߰��Ѵ�.

	m_pColumnNames[ADDMONEY_STATISTIC_DATE] = "��¥";
	m_pColumnNames[ADDMONEY_STATISTIC_DAILYQUEST] = "���ϸ�����Ʈ";
	m_pColumnNames[ADDMONEY_STATISTIC_LEVEL20] = "20����������";
	m_pColumnNames[ADDMONEY_STATISTIC_ANKALANSTOCK30] = "��ī���ֽĹ��";
	m_pColumnNames[ADDMONEY_STATISTIC_SKILLMONEY] = "���������";
	m_pColumnNames[ADDMONEY_STATISTIC_EVENT] = "�̺�Ʈ";
	m_pColumnNames[ADDMONEY_STATISTIC_FATHER] = "��������";	
	m_pColumnNames[ADDMONEY_STATISTIC_SPECIALQUEST] = "��ι�����Ʈ";
	m_pColumnNames[ADDMONEY_STATISTIC_QUEST] = "����Ʈ";
	m_pColumnNames[ADDMONEY_STATISTIC_SELLNPC] = "�������Ǹ�";
	m_pColumnNames[ADDMONEY_STATISTIC_SYSTEMREWARD] = "����NPC";
	m_pColumnNames[ADDMONEY_STATISTIC_MONTHMONEY] = "�������";
	m_pColumnNames[ADDMONEY_STATISTIC_NPCBUYITEM] = "�������Ǹ�";

	m_pColumnNames[ADDMONEY_STATISTIC_DIVIDEND] = "��������[����]";
	m_pColumnNames[ADDMONEY_STATISTIC_GUILDDUNGEON] = "������[����]";

	//===========================================================

	for( SI32 i=0; i<ADDMONEY_STATISTIC_TOTAL; i++ )
	{
		if( m_pColumnNames[i].IsEmpty() )
		{
#ifdef _DEBUG
			MessageBox(NULL, "��� �÷����� �������� �ʾҽ��ϴ�", "ERROR", MB_OK);
#endif
		}
	}

	if( CheckColumn() == -1 )
	{
		CreateFile();
	}
	else if( CheckColumn() == 0 )
	{
		ChangeExistFileName();
		CreateFile();
	}
}

void cltDelMoneyStatistics::Init(SI32 siColumnCount)
{
	if( siColumnCount <= 0 )			return;

	m_pColumnNames = new NTCHARString<32>[siColumnCount];
	m_Row = new SI64[siColumnCount];

	if(m_pColumnNames == NULL)			return;
	if(m_Row == NULL)					return;

	ZeroMemory(m_Row, sizeof(SI64) * siColumnCount);

	m_siColumnCount = siColumnCount;

#ifdef _DEBUG
	m_kUpdateTimer_Action.Init(60 * 1000);
#else
	m_kUpdateTimer_Action.Init(10 * 60 * 1000);
#endif
	m_kUpdateTimer_Action.SetActive(true, ::GetTickCount());

	//===========================================================
	m_kFileName = "DelMoney";
	//===========================================================

	//===========================================================
	// ���� �̸� ���� - �÷��� �߰��Ǹ�, ���ʿ� �߰��Ѵ�.

	m_pColumnNames[DELMONEY_STATISTIC_DATE]			= "��¥";
	m_pColumnNames[DELMONEY_SERVICECHARGE]			= "������";			
	m_pColumnNames[DELMONEY_TAX]					= "����";					
	m_pColumnNames[DELMONEY_DONATE]					= "��α�";					
	m_pColumnNames[DELMONEY_SAVEHOUSE]				= "Ŭ���ȸ��";				
	m_pColumnNames[DELMONEY_DEATHPANELTY]			= "����г�Ƽ";			
	m_pColumnNames[DELMONEY_MARKETSERVICECHARGE]	= "���ϵ�Ϻ�";	
	m_pColumnNames[DELMONEY_WARP]					= "�������";		
	m_pColumnNames[DELMONEY_ENTEREVENT]				= "�̺�Ʈ���";		
	m_pColumnNames[DELMONEY_BUYNPC]					= "�����۱���(NPC)";				
	m_pColumnNames[DELMONEY_POSTOFFICE]				= "��ü��������";			
	m_pColumnNames[DELMONEY_STOCK]					= "�ֽı��Ժ�";					
	m_pColumnNames[DELMONEY_GUILDCREATE]			= "��尳����[����]";			
	m_pColumnNames[DELMONEY_BANK_FEE]				= "����[����]";				
	m_pColumnNames[DELMONEY_BANK_SERVICECHARGE]		= "������[����]";	
	m_pColumnNames[DELMONEY_BUFF_ROULETTE]			= "�����귿 ���� ���� ���";
	m_pColumnNames[DELMONEY_MARKETCONDITIONS]		= "�ü�Ȯ�� ���� ���� ���";
	m_pColumnNames[DELMONEY_CHAR_ROULETTE]			= "TransformRoulette";
	m_pColumnNames[DELMONEY_NEWYEAREVENT_ROULETTE]	= "�ų��̺�Ʈ�귿 ���� ���";
	m_pColumnNames[DELMONEY_BALANCECURRENCY]		= "��ȭ�� ��� ��å";

	//===========================================================

	for( SI32 i=0; i<DELMONEY_STATISTIC_TOTAL; i++ )
	{
		if( m_pColumnNames[i].IsEmpty() )
		{
#ifdef _DEBUG
			MessageBox(NULL, "��� �÷����� �������� �ʾҽ��ϴ�", "ERROR", MB_OK);
#endif
		}
	}

	if( CheckColumn() == -1 )
	{
		CreateFile();
	}
	else if( CheckColumn() == 0 )
	{
		ChangeExistFileName();
		CreateFile();
	}
}
