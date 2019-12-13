#include "common.h"

static bool g_bNextScene = false;

void GameOverInit(void)
{
	g_bNextScene = false;

	FadeStart(false, 90, D3DCOLOR_RGBA(0, 0, 0, 255));
}

void GameOverUpdate(void)
{
	if (!g_bNextScene)
	{
		if (key.getTrigger(DIK_SPACE))
		{
			SceneChange(SCENE_INDEX_TITTLE);
			FadeStart(true, 10, D3DCOLOR_RGBA(0, 0, 0, 255));
		}
	}
}

void GameOverDraw(void)
{
	SpriteDrawSp(TEXTURE_INDEX_GAMEOVER, 0, 0, 1280, 760, 0, 0, 1, 1, 0);
}

void GameOverUnInit(void)
{

}