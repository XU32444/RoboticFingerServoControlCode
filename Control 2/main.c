#include <REGX52.H>
#include "Timer.h"
#include "Delay.h"


sbit PMW = P1^0;
sbit Servo1 = P1^5;
sbit Servo2 = P1^6;

unsigned int count;

void ServoInit()
{
	count = 0;
	Delay(1000);
	count = 4;
	Delay(1000);
	count = 0;
	Delay(1000);
	count = 2;
	Delay(1000);
}


void main()
{

	Timer0Init();
	ServoInit();
	Servo1 = 1;
	Servo2 = 1;
	while (1)
	{
		if(count == 5)
		{
			count = 4;
		}
		if(P1_1 == 0)    // Key 1, 1 hit for 45 degree
		{	
			Delay(20);
			while(P1_1 == 0)
			{
			}
			Delay(20);
			count++;
		}
		else if(P1_4 == 0)	// Key 4, 1 hit for 45 degree back
		{
			Delay(20);
			while(P1_4 == 0)
			{
			}
			Delay(20);
			if(count > 0)
			{
				count--;
			}
		}
		else if(P1_3 == 0)	// key 2, hit reset to 0 degrees
		{
			Delay(20);
			while(P1_3 == 0)
			{
			}
			Delay(20);
			count = 0;
		}
		else if(P1_2 == 0)	// key 3, hit reset to 180 degrees
		{
			Delay(20);
			while(P1_2 == 0)
			{
			}
			Delay(20);
			count = 4;
		}

	}
}

void Timer0_Routine(void) interrupt 1
{
	static unsigned int T0count = 0;
	TL0 = 0x0C; // 设置定时初值
	TH0 = 0xFE; // 设置定时初值
	if (T0count <= 40)
	{
		if (T0count <= count)
		{
			PMW = 1;
		}
		else
		{
			PMW = 0;
		}
	}
	else
	{
		T0count = 0;
		PMW = 1;
	}
	T0count++;
}