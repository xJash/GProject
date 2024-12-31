#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"


#include "..\..\Client\Music\Music.h"

#include "..\Common\Bullet\Bullet.h"
#include "Util\Util.h"

#include "..\..\smoke\smoke.h"

extern cltCommonLogic* pclClient;

//-------------------------------------------
//�̵� ���� �Լ�.
//-------------------------------------------
void cltCharClient::CalculateRXY()
{
	cltMapClient* pclmap = (cltMapClient* )pclMap;
	// �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. 
	SHORT centerx, centery;
	pclmap->GetCenterXYByMapCenterXY(MOX, MOY, centerx, centery);
	
	// �̵��� ��ġ�� �߽��� ã�´�. 
	SHORT nx_centerx, ny_centery;
	pclmap->GetCenterXYByMapCenterXY(MDX, MDY, nx_centerx, ny_centery);
	
	//���� ��ǥ�� ���� ��ǥ���� ����� �� ������ ���Ѵ�.
	if(clMoveInfo.siMovePercent >= 0)
	{
		GetMoveRatio(centerx, centery, nx_centerx, ny_centery, min(100, clMoveInfo.siMovePercent), siRX, siRY);
	}
	else
	{
		GetMoveRatio(nx_centerx, ny_centery, centerx, centery, min(100, TABS(clMoveInfo.siMovePercent)), siRX, siRY);
	}
	
}

void cltCharClient::SetMoveStandardPos(SI32 mox, SI32 moy, SI32 mdx, SI32 mdy)
{
	MOX = mox;
	MOY = moy;
	MDX = mdx;
	MDY = mdy;
}

//���� ��ǥ�� ���� ��ǥ���� ����� �� ������ ���Ѵ�. 
void cltCharClient::GetMoveRatio(SI32 startx, SI32 starty, SI32 endx, SI32 endy, SI32 movepercent, 
								SI32& rx, SI32& ry)
{

	endx-=startx;
	endy-=starty;
	startx=0;
	starty=0;

	SHORT index=0;
	POINT point[100];

	int t, distance;
	int xerr=0, yerr=0, delta_x, delta_y;
	int incx, incy;

	delta_x=endx-startx;
	delta_y=endy-starty;

	if(delta_x>0)       incx=1;
	else if(delta_x==0) incx=0;
	else               incx=-1;

	if(delta_y>0)       incy=1;
	else if(delta_y==0) incy=0;
	else               incy=-1;

	delta_x=TABS(delta_x);
	delta_y=TABS(delta_y);
	if(delta_x>delta_y)distance=delta_x;
	else distance=delta_y;


	for(t=0;t<=distance+1;t++)
	{
		if(index<100)
		{
			point[index].x=startx;
			point[index].y=starty;
			index++;
		}

		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
		   xerr-=distance;
		   startx+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			starty+=incy;
		}
	}

	int temp;
	if(index>0)
	{
	   temp=((index-1)*movepercent)/100;
	   rx=(SHORT)point[temp].x;
	   ry=(SHORT)point[temp].y;
	}
	else
	{
		rx=ry=0;
	}

}

