#include "./DLGDefine.h"

#define MAX_CONTROL_PROPERTY_NUM  30
#define MAX_HEADER_TYPE_LENGTH 30

class CTokenizer
{
public:
// Construction/destruction
	CTokenizer( char* pstrInput, const char strHeaderDelimiter = DLG_HEADER_SPLITTER_CHAR, const char strDelimiter = DLG_ITEM_SPLITTER_CHAR, const char strEndline = DLG_ENDLINE_CHAR );
	~CTokenizer();

// Operations
	void Init( char* pstrInput, const char strHeaderDelimiter = DLG_HEADER_SPLITTER_CHAR, const char strDelimiter = DLG_ITEM_SPLITTER_CHAR, const char strEndline = DLG_ENDLINE_CHAR );
	int GetSize(  ) const;
	bool GetAt( int nIndex, char* pchar, int max_length) const;
   
// Attributes

public:
	char  m_headertype[MAX_HEADER_TYPE_LENGTH];	// ��� Ÿ�� ���� ����
	char* m_pstra[MAX_CONTROL_PROPERTY_NUM];	// ���ڿ����� ������ �� �Ӽ��� �Ӽ��� ����Ű�� ������ �迭
    int	  m_propertycount;	// ���ڿ����� ������ �Ӽ��� �� ����, m_propertycount < MAX_CONTROL_PROPERTY_NUM

};
