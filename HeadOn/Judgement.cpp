//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "Judgement.h"
#include"common.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Timer.h"
#include "EnemyBullet.h"
#include "GameOver.h"

//////////////////////////////////////////////////////////////////////////////
//グローバル変数宣言
//////////////////////////////////////////////////////////////////////////////
static int cnt = 0;
static int cnt2 = 0;
static int cnt3 = 0;

//////////////////////////////////////////////////////////////////////////////
//関数名	:
//戻り値	:
//説明		:	全てのルールをつかさどる
//////////////////////////////////////////////////////////////////////////////
void JudgementUpdate(void)
{
	for (cnt2 = 0; cnt2 < MAX_ENEMY; cnt2++)
	{
		// Enemyが有効か？
		if (EnemyIs_Enable(cnt2))
		{
			//PlayerとEnemyの当たり判定
			if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), Enemy_GetCircleCollsion(cnt2)))
			{
				//プレイヤーダメージ処理
				PlayerDamage();
				EnemyIs_Destroy(cnt2);

				
			}

			//プレイヤーの弾の複数判定
			for (cnt = 0; cnt < MAX_BULLET; cnt++)
			{
				// プレイヤーの弾と敵との当たり判定
				// プレイヤーの弾が有効か？
				if (BulletIs_Enable(cnt))
				{
					// プレイヤーの弾のコリジョンと敵のコリジョンとの当たり判定
					if (Collision_is_HitCIRCLE(Bullet_GetCircleCollision(cnt), Enemy_GetCircleCollsion(cnt2)))
					{
						// 当たってたらプレイヤーの弾と敵を消す
						BulletDestroy(cnt);
						EnemyIs_Destroy(cnt2);
						//ScoreUpdate();
					}
				}
			}

			//プレイヤー機と敵の弾のコリジョン当たり判定
			for (cnt3 = 0; cnt3 < ENEMY_MAX_BULLET; cnt3++)
			{
				if (EnemyBulletIs_Enable(cnt3))
				{
					if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), EnemyBullet_GetCircleCollision(cnt3)))
					{
 						EnemyBulletDestroy(cnt3);
						PlayerDamage();
					}
				}
			}
		}	
	}

	
	// ボスが有効か？
	if (BossIs_Enable())
	{
		//PlayerとBossの当たり判定
		if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), Boss_GetCircleCollsion()))
		{
			//プレイヤーダメージ処理
			PlayerDamage();
			BossIs_Destroy();


			//画面移動（要因：プレイヤー死亡）
			if (PlayerLife() <= 0)
			{
				SceneChange(SCENE_INDEX_RESULT);
				FadeStart(true, 10, D3DCOLOR_RGBA(0, 0, 0, 255));
			}
		}

		//弾の複数判定
		for (cnt = 0; cnt < MAX_BULLET; cnt++)
		{
			// プレイヤーの弾と敵との当たり判定
			// プレイヤーの弾が有効か？
			if (BulletIs_Enable(cnt))
			{
				// プレイヤーの弾のコリジョンと敵のコリジョンとの当たり判定
				if (Collision_is_HitCIRCLE(Bullet_GetCircleCollision(cnt), Boss_GetCircleCollsion()))
				{
					// 当たってたらプレイヤーの弾と敵を消す
					BulletDestroy(cnt);
					BossIs_Destroy();
					//ScoreUpdate();
				}
			}
		}
		//プレイヤー機と敵の弾のコリジョン当たり判定
		for (cnt3 = 0; cnt3 < ENEMY_MAX_BULLET; cnt3++)
		{
			if (EnemyBulletIs_Enable(cnt3))
			{
				if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), EnemyBullet_GetCircleCollision(cnt3)))
				{
					EnemyBulletDestroy(cnt3);
					PlayerDamage();
				}
			}
		}

	}
	//画面チェンジ（要因:タイムアップ）
	if (TimerCnt()  /60 > TIME_LIMIT || PlayerLife() < 1)
	{
		SceneChange(SCENE_INDEX_GAMEOVER);
		FadeStart(true, 10, D3DCOLOR_RGBA(0, 0, 0, 255));
	}
}