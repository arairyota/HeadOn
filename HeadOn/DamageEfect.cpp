#include "common.h"
#include "DamageEfect.h"
#include "Player.h"
#include "Timer.h"
#include "Texture.h"
#include "Effect.h"

DAMAGEEFECT DamageEfect[EFFECT_COUNT_MAX];
int Cnt = 0;

//////////////////////////////////////////////////////////////////////////////
//関数名	: DamageEfectInit
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void DamageEfectInit(void)
{
	for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
	{
		DamageEfect[cnt].PosX = 0;
		DamageEfect[cnt].PosY = 0;
		DamageEfect[cnt].Age = 0;
		DamageEfect[cnt].Now = 0;
		DamageEfect[cnt].is_Enable = false;
		DamageEfect[cnt].SmokeSize = 0.1f;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: DamageEfectCreate
//戻り値	:
//説明		:
//引数		: 描画元のX軸Y軸
//////////////////////////////////////////////////////////////////////////////
void DamageEfectCreate(float px, float py)
{
	Cnt++;
	if (Cnt > SMOKE_RATE + 1 * PlayerLife())
	{
		for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
		{
			if (!DamageEfect[cnt].is_Enable)
			{
				DamageEfect[cnt].is_Enable = true;
				DamageEfect[cnt].PosX = px;
				DamageEfect[cnt].PosY = py;

				DamageEfect[cnt].Now = TimerCnt();
				DamageEfect[cnt].SmokeSize = 0.1f;
				break;
			}
		}
		Cnt = 0;
	}
	//if (Cnt > ENEMY_RATE)
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: DamageEfectUpdate
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void DamageEfectUpdate(void)
{
	for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
	{
		/*
		DamageEfect[cnt].Age = TimerCnt() - DamageEfect[cnt].Now;
		if (DamageEfect[cnt].Age / 60 < 5)
		{
			DamageEfect[cnt].PosX -= 5;
			DamageEfect[cnt].SmokeSize += 0.01f;
		}
		*/

		if (DamageEfect[cnt].is_Enable) {
			DamageEfect[cnt].PosX -= 5;
			if(DamageEfect[cnt].SmokeSize < 1)
			DamageEfect[cnt].SmokeSize += 0.01f;
		}

		if (DamageEfect[cnt].PosX < 0) {
			DamageEfect[cnt].is_Enable = false;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: DamageEfectDraw
//戻り値	:
//説明		:
//引数		: プレイヤーのダメージによって色変更
//////////////////////////////////////////////////////////////////////////////
void DamageEfectDraw(int color)
{
	for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
	{
		if (DamageEfect[cnt].is_Enable)
		{
			//画像を用意する
			SpriteDraw(TEXTURE_INDEX_SMOKE_NONE + color, DamageEfect[cnt].PosX, DamageEfect[cnt].PosY + 30, 64, 64, DamageEfect[cnt].SmokeSize);
		}
	}
}