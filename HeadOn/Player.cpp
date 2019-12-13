#include "common.h"
#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "Player.h"
#include "Bullet.h"
#include "Collision.h"
#include "DamageEfect.h"
#include "HpBar.h"

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
static unsigned int FrameCnt = 0;

PLAYER Player;

static int Hp = 300;
//////////////////////////////////////////////////////////////////////////////
//関数名	: PlayerInit
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void PlayerInit(void)
{
	Player.posX = 0.0f;
	Player.posY = SCREEN_HEIGHT / 2;
	Player.SpeedX = 0.0f;
	Player.SpeedY = SCREEN_HEIGHT / 2;
	Player.Collision.cx = 0.0f;
	Player.Collision.cy = 0.0f;
	Player.Collision.radius = 10;
	Player.Life = PLAYER_MAX_LIFE;
	Player.DamageCnt = 0;
	Player.Hp = 300;
	//Hp = 0;
	HpBarInit();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:　 PlayerUpdate
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void PlayerUpdate(void)
{
	if (key.getPress(DIK_W) && Player.SpeedY > 0)
	{
		Player.SpeedY -= PLAYERSPEED;
	}

	if (key.getPress(DIK_A) && Player.SpeedX > 0)
	{
		Player.SpeedX -= PLAYERSPEED;
	}

	if (key.getPress(DIK_S) && Player.SpeedY < SCREEN_HEIGHT - 73.0f)
	{
		Player.SpeedY += PLAYERSPEED;
	}

	if (key.getPress(DIK_D) && Player.SpeedX < SCREEN_WIDTH - 200.0f)
	{
		Player.SpeedX += PLAYERSPEED;
	}

	//デバッグ用画面停止処理
	if (key.getPress(DIK_J))
	{
		int a = 0;
	}

	//ヌルっと移動させる処理
	Player.posX += (Player.SpeedX - Player.posX) * 0.1f;
	Player.posY += (Player.SpeedY - Player.posY) * 0.1f;

	Player.Collision.cx = Player.posX;
	Player.Collision.cy = Player.posY;

	BulletCreate(Player.posX, Player.posY);

	EffectCreate(Player.posX , Player.posY, 64.0f, 60, D3DCOLOR_RGBA(32, 32, 32, 255));

	DamageEfectCreate(Player.posX + 50, Player.posY - 20);

	BulletUpdate();

	//HPを減らす処理
	HpBarUpdate();
	//Reload();

	//D3DXVec2Normalize(&vecSpeed, &vecSpeed)

	/*g_PlayerX += g_PlayerSpeedX;
	g_PlayerY += g_PlayerSpeedY;

	g_PlayerSpeedX *= 0.97f;
	g_PlayerSpeedX *= 0.97f;
*/
	FrameCnt++;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	PlayerDraw
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void PlayerDraw(void)
{
	BulletDraw(Player.posX, Player.posY);
	
	SpriteDrawEx(TEXTURE_INDEX_PLAYER, Player.posX - 100, Player.posY - 36, 0, 0, 200, 73);
	
	DamageEfectDraw(Player.DamageCnt);

	HpBarDraw();
}

const CIRCLE* Player_GetCircleCollision(void)
{
	return &Player.Collision;
}

void PlayerDamage(void)
{
	Player.Life--;
	Player.DamageCnt++;		//機体スモーク色制御変数

	HpBarDamage();
	//Hp += PLAYER_MAX_HP / PLAYER_MAX_LIFE;

	
}

int PlayerLife(void)
{
	return Player.Life;
}

float PlayerPositionY(void)
{
	return Player.posY;
}

float PlayerPositionX(void)
{
	return Player.posX;
}