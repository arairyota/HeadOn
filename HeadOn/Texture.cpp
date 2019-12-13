//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "Direct3D.h"
#include "common.h"
#include "Texture.h"
#include <d3dx9.h>

#define TEXTURE_FILENAME_MAX (80)	//8の倍数
//////////////////////////////////////////////////////////////////////////////
//構造体
//////////////////////////////////////////////////////////////////////////////
typedef struct TextureFile_tag
{
	const char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;
}TextureFile;	//

static const TextureFile g_TextureFile[] = {
	{ "Asset/Texture/IL2.png", 200, 73 },
	{ "Asset/Texture/AkiyamaBullet.png"  , 97, 9 },
	{ "Asset/Texture/PlayerBullet.png"  , 97, 9 },
	{"Asset/Texture/Enemy.png"  , 200, 73 },
	{"Asset/Texture/explosion.png ", 768, 768 },
	{ "Asset/Texture/number.png ", 320, 32 },
	{ "Asset/Texture/Tittle.png", 1280, 760 },
	{ "Asset/Texture/GameOver.png", 1280, 760 },
	{ "Asset/Texture/effect000.jpg", 80, 80 },
	{ "Asset/Texture/Reroad.png ", 320, 32 },
	{ "Asset/Texture/Smoke_None.png ", 64, 64 },
	{ "Asset/Texture/Smoke01.png ", 64, 64 },
	{ "Asset/Texture/Smoke02.png ", 64, 64 },
	{ "Asset/Texture/Smoke03.png ", 64, 64 },
	{ "Asset/Texture/Smoke04.png ", 64, 64 },
	{ "Asset/Texture/Background.png", 1280, 760 },
	{ "Asset/Texture/Background1.png ", 1280, 760 },
	{ "Asset/Texture/Background2.png ", 1280, 760 },
	{ "Asset/Texture/Tutorial.png ", 1280, 760 },
	{ "Asset/Texture/akiyama.png"      , 323 * 2, 456 * 2 },
	{ "Asset/Texture/GameModeStrat.png", 300, 100 },
	{ "Asset/Texture/GameModeTutorial.png", 300, 100 },
	{ "Asset/Texture/RedBar.png", 32, 32 },
	{ "Asset/Texture/GreenBar.png", 32, 32 },
	{ "Asset/Texture/EnemyBullet.png", 32, 32 },
	{ "Asset/Texture/Result.png", 1280, 760 },
	{ "Asset/Texture/Boss.png"  , 200, 73 },
	{ "Asset/Texture/BlackBar.png", 32, 32 },


	//{"Asset/Texture/runningman100.png", 700, 400},
	//{"Asset/Texture/runningman101.png", 700, 400},
	//{"Asset/Texture/runningman102.png", 700, 400},
	
	
};

static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFile) / sizeof(g_TextureFile[0]);
//static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFile); //windows.h内の関数を使った上と同じやり方

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT];		//テクスチャインターフェースのポインタ

//////////////////////////////////////////////////////////////////////////////
//関数名	:	Texture_Load
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
int Texture_Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();
	if (!pDevice)
	{
		return TEXTURE_FILE_COUNT;
	}

	HRESULT hr;

	int failed_count = 0;

	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, g_TextureFile[i].filename, &g_pTextures[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャ取得失敗", "確認", MB_OKCANCEL );
			failed_count++;
		}
	}
	return failed_count;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	Texture_Release
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void Texture_Release(void)
{
	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		if (g_pTextures[i])
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	Texture_GetDevice
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 Texture_GetTexture(int index)
{
	return g_pTextures[index];
}


int Texture_GetWidth(int index)
{
	return g_TextureFile[index].width;
}


int Texture_GetHeight(int index)
{
	return g_TextureFile[index].height;
}
