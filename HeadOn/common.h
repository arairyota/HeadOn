#ifndef _COMMON_H_
#define _COMMON_H_
	
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include "Direct3D.h"
#include "Texture.h"
#include <math.h>
#include "Sprite.h"
#include "Bullet.h"
#include "input.h"
#include <time.h>
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Collision.h"
#include "Judgement.h"
#include "nember.h"
#include "Score.h"
#include "Scene.h"
#include "Result.h"
#include "Tittle.h"
#include "Reload.h"
#include "Fade.h"
#include "Effect.h"
#include "sound.h"
#include "Capacity.h"
#include "GameOver.h"
#include "Font.h"
#include "Explosion.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define SCREEN_WIDTH	(1280)				//スクリーンの幅
#define SCREEN_HEIGHT	(720)				//高さ
#define WAIT_FRAME		(5)					//フレーム待ち時間
#define WAIT_EXP_FRAME	(10)

#endif