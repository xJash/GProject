#ifndef _LIBBUFFER_H_
#define _LIBBUFFER_H_

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj::CObj( SI32 siMaxBufferSize )
//	Desc : �ַ� Socket ��ſ��� Recv Buffer �Ǵ� Send Buffer��
//		   �� Ŭ������ ��ӹ޾Ƽ� ����ϸ� ����
//	Date : 2003. 11. 15
//	Update : 
//--------------------------------------------------------------------------------------------

class CLibBuffer
{
public:
	CLibBuffer();
	virtual ~CLibBuffer();

	void Initialize();
	void Destroy();


private:

};


#endif