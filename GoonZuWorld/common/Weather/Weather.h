#ifndef _WEATHER_H_
#define _WEATHER_H_

#include <Directives.h>


#define CHANGE_WEATHER_DELAY_TIME		60000			// ����
#define CHANGE_WIND_DELAY_TIME			50000			// ǳ��
#define CHANGE_WIND_SPEED_DELAY_TIME	30000			// ǳ��

#define	WEAHTER_RAIN_PERCENTAGE			30
#define	THUNDER_PERCENTAGE				50

#define MAX_WEATHER_WIND_SPEED			10

//enum { SEASON_SPRING, SEASON_SUMMER, SEASON_FALL, SEASON_WINTER };				// ������ ����.
enum { WEATHER_FINE, WEATHER_RAIN };
enum { WIND_SOUTH, WIND_SOUTHWEST, WIND_WEST, WIND_NORTHWEST, WIND_NORTH, WIND_NORTHEAST, WIND_EAST, WIND_SOUTHEAST };

struct stWeatherData
{
	SI08 m_si08WeatherStatus;
	SI08 m_si08WindDirection;
	SI08 m_si08WindSpeed;

	void Set( stWeatherData *pWeatherData )
	{
		memcpy( this, pWeatherData , sizeof( stWeatherData ) );
	}
};

class CWeather
{
public:
	CWeather();
	~CWeather();

	void	ChangeWeatherStatus();
	void	ChangeWindStatus();
	void	ChangeWindSpeed();
	bool	Action( DWORD dwCurrentTime );			// �� �Լ��� �ð� ������ �� �ΰ� ȣ��Ǿ�� �� ��... ��� ȣ��� �ʿ�� ���µ�... 
	
	//-------------------------------------------------------------------------------------------------
	//-------------- ���� ���� ������ ������ �Լ�
	bool	GetWeatherData( stWeatherData *pWeatherData );
	//-------------------------------------------------------------------------------------------------

private:

	stWeatherData m_stWeatherData;
	//bool	m_bThunderStatus;
	SI08	m_si08WeatherStatus;
	SI08	m_si08WindStatus;
	SI08	m_si08WindSpeed;
	//SI08	m_si08SeasonStatus;

	DWORD	m_dwWeatherStartTime;
	DWORD	m_dwWindStartTime;
	DWORD	m_dwWindSpeedStartTime;
};

#endif