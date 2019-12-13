//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "Explosion.h"

//////////////////////////////////////////////////////////////////////////////
//グローバル変数宣言
//////////////////////////////////////////////////////////////////////////////
static unsigned int FrameCnt = 0;

static EXPLOSION Explosion[MAX_EXPLOSION];

//////////////////////////////////////////////////////////////////////////////
//関数名	: ExplosionInit
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void ExplosionInit(void)
{
	for (int cnt = 0; cnt < MAX_EXPLOSION; cnt++)
	{
		Explosion[cnt].PositionX = 0.0f;
		Explosion[cnt].PositionY = 0.0f;

		Explosion[cnt].Aeg = 0;
		Explosion[cnt].CerateFrame = 0;
		Explosion[cnt].PatternCnt = 0;

		Explosion[cnt].is_Enable = false;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ExplosionCreate
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void ExplosionCreate(float x, float y)
{
	for (int cnt = 0; cnt < MAX_EXPLOSION; cnt++)
	{
		if (!Explosion[cnt].is_Enable)
		{
			Explosion[cnt].PositionX = x;
			Explosion[cnt].PositionY = y;

			Explosion[cnt].CerateFrame = FrameCnt;
			Explosion[cnt].PatternCnt = 0;

			Explosion[cnt].is_Enable = true;

			PlaySound(SOUND_LABEL_SE_EXPLOSION);

			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ExplosionUpdate
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void ExplosionUpdate(void)
{
	for (int cnt = 0; cnt < MAX_EXPLOSION; cnt++)
	{
		if (Explosion[cnt].is_Enable)
		{
			Explosion[cnt].Aeg = FrameCnt - Explosion[cnt].CerateFrame;
			Explosion[cnt].PatternCnt = Explosion[cnt].Aeg;
		}

		if (Explosion[cnt].PatternCnt >= MAX_PATTERN)
		{
			Explosion[cnt].is_Enable = false;
		}
	}
	FrameCnt++;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ExplosionDraw
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void ExplosionDraw(void)
{
	for (int cnt = 0; cnt < MAX_EXPLOSION; cnt++)
	{
		if (Explosion[cnt].is_Enable)
		{
			SpriteDraw(TEXTURE_INDEX_EXPROTION, Explosion[cnt].PositionX, Explosion[cnt].PositionY,
				(Explosion[cnt].PatternCnt %  PATTERN_WIDTH_MAX) * EXPLOSION_SCALE, (Explosion[cnt].PatternCnt / PATTERN_WIDTH_MAX) * EXPLOSION_SCALE,
				128, 128, 1);
		}
	}
}