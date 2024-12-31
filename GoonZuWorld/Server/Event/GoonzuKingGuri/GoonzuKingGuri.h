#ifndef _GOONZUKINGGURI_H_
#define _GOONZUKINGGURI_H_

#include "../../../common/Event/event.h"
#include "../../../Client/ninterface/ngoonzudlg/NGoonzuRaccoonEventDlg.h"

const SI32 MAX_GOONZU_KINGGURI_NUM = 3;
const SI32 MAX_GOONZU_POSITION_NUM = 11;
const SI32 MAX_GOONZU_MESSAGE_SIZE = 256;

//#define CanSelect_EventNum	3		// �Ϸ簡���� ���̾�Ʈ ������ Ƚ�� 3ȸ 
//#define MAX_MONSTER_NUM_GOONZURACCOONEVENT	3	// �ִ� ���� ���� 3����
//#define MAX_SELECTRFIELD_NUM	3	//�� �����̺�Ʈ���� �����Ҽ� �ִ� �ִ����� �ʵ��޺��ڽ� �ε��� ����
class CGoonzuKingGuriEvent : public cltEvent
{
public:

	enum
	{
		START = 0,
		ACTION,
		DIE_KINGGURI,
		ITEM,				//[�߰� : Ȳ���� 2007. 11. 14 ��� ������ ���̰� ������ ȹ��.]
		END,
	};
	enum
	{
		GOONZU_KINGGURI_FIRSTMAP = 0,
		GOONZU_KINGGURI_SECONDMAP,
		GOONZU_KINGGURI_THIRDTMAP,
	};
	enum
	{
		GOONZU_KINGGURI_FIRSTTIME = 0,
		GOONZU_KINGGURI_SECONDTIME,
		GOONZU_KINGGURI_THIRDTTIME,
	};
	enum
	{
		GOONZU_KINGGURI_SAMETIME = 0,		// 3Ÿ���� ���� Ÿ���� �ִ�
		GOONZU_KINGGURI_NOTOVERTIME,		// 24�ð��� ������ ���� ���� �ߴ�
		GOONZU_KINGGURI_NOTENOUGHDATA,		// 3Ÿ���� ��� ���� ���� �ʾҴ�.
		GOONZU_KINGGURI_CORRECTDATA,		// ���� ������ 
	};

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_GOONZU_KINGGURI_NUM>		m_bKilledKingGuri;
	NSafeTArray<SI32, MAX_GOONZU_KINGGURI_NUM>		m_siKingGuriID;
#else
	// �ش� �������� �׾����� 
	bool m_bKilledKingGuri[MAX_GOONZU_KINGGURI_NUM];
	// ���� ������ ���̵�
	SI32  m_siKingGuriID[MAX_GOONZU_KINGGURI_NUM];
#endif

	

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_GOONZU_KINGGURI_NUM>		m_siAreaIndex;
#else
	// �������� ���� ���� �ε���
	SI32 m_siAreaIndex[MAX_GOONZU_KINGGURI_NUM];
#endif
	/// ���õ� �����̸�
	TCHAR m_szSelectedAreaName[MAX_GOONZU_KINGGURI_NUM][32];
	/// ���õ� ��ǥ
	POINT m_ptPosition[MAX_GOONZU_POSITION_NUM];


	SYSTEMTIME LsatsetTime	;	// ���������� ���� �� �ð�

	RocData GoonzuRaccoonRocData[MAX_DATA_MAP_NUM]	;	// ���� ��ǥ�� ������ �ִ´�.


	//�ʿ��� ����
	/*
	1. �������� ���� ������ ��ǥ
	2. ������ �������� ����Ʈ 
	*/
	// ������ �����ص� �迭

	cGoonzuRaccoonEventData GoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT]	; // �������� ������ �־���� �����̺�Ʈ �߻� ������ (�ð� , ���� ������,���� ���ε��� , ���� X y ��ǥ )

	CGoonzuKingGuriEvent();
	~CGoonzuKingGuriEvent();

	void Init();
	void Start();
	void Action();
	void End();
	void SendInfo( SI32 Type, DWORD LeftTime, TCHAR* UserNmae = NULL );
	void SetDieKingGuri( bool Flag, SI32 KingGuriID, SI32 UserID );

	void MakeKingGuri();	
	bool MonsterAllDie(void);

	// DATACHECK
	SI32 ChekData(cGoonzuRaccoonEventData* GoonzuRaccoonEventData)	; // ���� �ϱ⿡ ������ ������ ���� üũ �Ѵ� 
	void LoadData(void);	// ���ҽ����� ��ǥ�� �о� �´� .

	bool IsCorrectRoc(SI32 siMapname , SI32 X , SI32 y); // Ŭ���̾�Ʈ ���� �Ѿ�� ��ǥ�� �������� Ȯ�� �Ѵ� �������̸� ������ ���� �Ұ��� 

};

#endif
