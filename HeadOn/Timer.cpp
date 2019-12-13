#include "Timer.h"
#include "sprite.h"
#include "nember.h"

unsigned int TimeCnt = 0;
unsigned int TimeLimit = 0;

void TimerInit(void)
{
	TimeCnt = 0;
	TimeLimit = TIME_LIMIT;
}

void TimerUpdate(void)
{
	TimeCnt++;
}

void TimerUninit(void)
{
	
}

unsigned int TimerCnt(void)
{
	return TimeCnt;
}

unsigned int TimerLimit(void)
{
	return TimeLimit - TimerCnt() / 60;
}

void TimerDraw(float x, float y, int capacity, int keta)
{
	//カンスト数値を求める
	int CountStopValue = 1;
	
	for (int i = 0; i < keta; i++)
	{
		CountStopValue *= 10;
	}
	
	//カンストしてるかどうか
	if (capacity >= CountStopValue)
	{
		capacity = CountStopValue - 1;
	}
	
	for (int i = keta - 1; i >= 0; i--)
	{
		//int n = score % 10;
		//float dx = (keta - 1) * NEMBER_WIDTH;
		NemberDraw(x + i * NEMBER_WIDTH, y, capacity % 10);
		capacity /= 10;
	}
}