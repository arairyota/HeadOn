//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "Capacity.h"
#include "common.h"

unsigned int Capacity = 0;

void CapacityInit(void)
{
	Capacity = 0;
}

void CapacityDraw(float x, float y, int capacity, int keta)
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

void CapacityUpdate(void)
{
	Capacity--;
}

