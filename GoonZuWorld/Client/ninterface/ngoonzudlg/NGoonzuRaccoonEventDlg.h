#pragma once
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����

#include "../../InterfaceMgr/DialogController.h"
#include "../common/CommonHeader.h"

enum
{
	FirstMapIndex = 0 ,	//���ε��� 1
	SecondMapIndex,		//���ε��� 2
	ThirdMapIndex,		//���ε��� 3
};
enum
{
	FirstRaccoonTime = 0 ,	//����Ÿ�� 1
	SecondRaccoonTime,		//����Ÿ�� 2
	ThirdRaccoonTime,		//����Ÿ�� 3
};
#define MAX_DATA_MAP_NUM	20			// ���ҽ��� ������ �ִ� �� ������ 20�� ����
#define MAX_DATA_MAPCOMBOBOX_NUM	9	// ���޺��ڽ� ����
#define MAX_DATA_TIME_NUM	24			// ���ҽ��� ������ �ִ� �ð��� 24�� ���� 
#define MAX_MAP_NUM	3					// ������ ���� ���� ����
// ���ҽ����� �о� ���� ������ ������ ���� Ŭ����
class CNGoonzuRaccoonEventDlg : public CDialogController
{
public:

	InterfaceFactory	m_InterfaceFactory_;

	CNGoonzuRaccoonEventDlg();
	~CNGoonzuRaccoonEventDlg();

	void init();
	void Create();
	static void CALLBACK StaticCallBackDialogNGoonzuRaccoonEventDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNGoonzuRaccoonEventDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void AddHuntmaps();
	void AddCombo(TCHAR* maptypename);
	void Action()	;

	void Select_FiledComboBox(SI32 siComboBoxID, SI32 siRaccoonTimeIndex, SI32 siMapIndexArray)	;
	void Select_TimeComboBox(SI32 siComboBoxID, SI32 siRaccoonTimeIndex)	;
	void Select_MonsterNumComboBox(SI32 siComboBoxID, SI32 siRaccoonTimeIndex)	;

	void SetComboX(cGoonzuRaccoonEventData* pData,SI32 siRaccoonTime)	;	// �����Ϳ� ���° ���������� �־���� �Ѵ�.
	void SetComboBox_Cursel( SI32 siComboBoxID , TCHAR* pText)	;
	void SetComboBox_Cursel( SI32 siComboBoxID , SI32 siNumber )	;

	void EnableComboBox_Map(SI32 siComboBoxID,SI32 siMonsterNum)	;	// ���޺� �ڽ��� enable��Ű�� ���ؼ� 

	void BeforeCheckData()	;			// �����͸� ������ ���� ������ �����Ͱ� ����ִ��� Ȯ�� �Ѵ� , �����Ͷ�� ���� �ʿ䰡 ���� 

	bool CheckSetMapData( SI32 siMapname )	;			// ������ �ʵ��������� Ȯ��
private:
	RocData GoonzuRaccoonLoadData[MAX_DATA_MAP_NUM]	;
	cGoonzuRaccoonEventData GoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT]	; //������ ���� ������. �޺��ڽ���Ŭ���ϸ� �ش� �����͸� �� Ŭ������ �־ ������ .
};