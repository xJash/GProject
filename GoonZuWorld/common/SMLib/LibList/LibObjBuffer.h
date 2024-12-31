#ifndef _LIBOBJBUFFER_H_
#define _LIBOBJBUFFER_H_

#include "LibListBaseInfo.h"

class CLibObjBuffer
{
public:
	CLibObjBuffer( UI32 uiMaxBufferSize );							// ������
	~CLibObjBuffer();												// �Ҹ���

	void Initialize();												// �ʱ�ȭ
	void Destroy();													// ����ó��

	void SetData( BYTE *pData, UI32 ui32DataSize );					// �����͸� ���ۿ� ����
	void GetData( BYTE *pData, UI32 *pDataSize );					// ���۷κ��� �����͸� �о �����ؼ� �־���
	BYTE *GetDataPtr();												// ������ ������ �����͸� ��ȯ, �����ͷ� ������ ���� ������ ����� ���̸� �̰� �ξ� �����Ƿ�..., �� ������ ���� �д� ���ȿ��� �����Ͱ� ���� ���ؼ��� �� �ȴٴ� ���̴�.

	bool IsDataExist();												// ������ ����� �޾ƿ��� �ͺ��� ������ �ִ��� �����ĸ� üũ�ϴ°� �ֵ� ���̹Ƿ� �����Ͱ� �ִ��ĸ� üũ ( �̰� ������ �� ���� )	

private:
	BYTE	*m_pData;
	UI32	m_uiDataSize;
};

#endif