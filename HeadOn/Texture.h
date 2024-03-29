#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <d3dx9.h>

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
int Texture_Load(void);								//戻り値は読み込めなかった数
void Texture_Release(void);							//全部捨てる

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);	//テクスチャのポインタ

int Texture_GetWidth(int index);					//UV設定
int Texture_GetHeight(int index);					//UV設定


enum
{
	TEXTURE_INDEX_PLAYER,
	TEXTURE_INDEX_AKIYAMABULLET,
	TEXTURE_INDEX_PLAYERBULLET,
	TEXTURE_INDEX_ENEMY,
	TEXTURE_INDEX_EXPROTION,
	TEXTURE_INDEX_NUMBER,
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_GAMEOVER,
	TEXTURE_INDEX_EFFECT,
	TEXTURE_INDEX_REROAD,
	TEXTURE_INDEX_SMOKE_NONE,
	TEXTURE_INDEX_SMOKE_01,
	TEXTURE_INDEX_SMOKE_02,
	TEXTURE_INDEX_SMOKE_03,
	TEXTURE_INDEX_SMOKE_04,

	TEXTURE_INDEX_BACKGROUND,
	TEXTURE_INDEX_BACKGROUND1,
	TEXTURE_INDEX_BACKGROUND2,
	TEXTURE_INDEX_TUTORIAL,
	TEXTURE_INDEX_AKIYAMACURSOR,
	TEXTURE_INDEX_GAMEMODESTART,
	TEXTURE_INDEX_GAMEMODETUTORIAL,
	TEXTURE_INDEX_REDBAR,
	TEXTURE_INDEX_GREENBAR,
	TEXTURE_INDEX_ENEMYBULLET,
	TEXTURE_INDEX_RESULT,
	TEXTURE_INDEX_BOSS,
	TEXTURE_INDEX_BLACK,
	//TEXTURE_INDEX_RANNINGMAN0,
	//TEXTURE_INDEX_RANNINGMAN1,
	//TEXTURE_INDEX_RANNINGMAN2,
	

};

#endif // !_TEXTURE_H_

