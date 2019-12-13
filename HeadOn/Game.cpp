#include "Game.h"
#include "common.h"
#include "Timer.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "DamageEfect.h"
#include "Background.h"
#include "sprite.h"

unsigned int s = 0;

void GameInit(void)
{

	FadeStart(false, 90, D3DCOLOR_RGBA(0, 0, 0, 255));

	BackgroundInit();

	ScoreInit();

	PlayerInit();

	EffectInit();

	BulletInit();

	EnemyInit();

	EnemyBulletInit();

	ExplosionInit();

	CapacityInit();

	DamageEfectInit();
}

void GameUpdate(void)
{
	BackgroundUpdate();

	EffectUpdate();

	DamageEfectUpdate();

	JudgementUpdate();

	EnemyCreate();

	EnemyUpdate();

	PlayerUpdate();

	ExplosionUpdate();

	
}

void GameDraw(void)
{
	//SpriteDrawSp(TEXTURE_INDEX_BACKGROUND, 0, 0, 1280, 760, 0, 0, 1, 1, 0);

	BackgroundDraw();

	EffectDraw();

	PlayerDraw();

	EnemyDraw();

	ExplosionDraw();

	s = GetScore();

	ScoreDraw(0, 0, s, 5);

	CapacityDraw(PlayerPositionX(), PlayerPositionY() + 43, GetCapacity(), 3);

	TimerDraw(600, 0, TimerLimit(), 2);

	//SpriteDrawHp(TEXTURE_INDEX_HP, 300, 20, s, 20);
}

void GameUnInit(void)
{
	
}