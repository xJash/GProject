#ifndef _MOVEMARK_H
#define _MOVEMARK_H

#include "Map\Map.h"

class _MoveMark {
	cltMapClient* pclMap;

	SHORT X, Y;   // �̵� ǥ���� ��ġ 
	int RealX, RealY;

	SHORT MoveMarkSwitch;
	SHORT Step;
	SHORT MaxStep;

	public:
	_MoveMark(cltMapClient* pclMap);
	~_MoveMark();
	void DrawMoveMark();
	void Action();
	void SetMoveMark(SHORT x, SHORT y);
	// real ��ǥ�� �����Ѵ�. 
    void SetMoveMarkReal(SHORT x, SHORT y);

};



#endif