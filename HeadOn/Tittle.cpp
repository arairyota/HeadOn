#include "common.h"
#include "CUrsor.h"

static bool g_bNextScene = false;
static int Select = 0;
static int SelectNum = 0;

//////////////////////////////////////////////////////////////////////////////
//関数名	:
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void TittleInit(void)
{
	g_bNextScene = false;
	Select = 0;
	SelectNum = 0;
	CursorInit();
	FadeStart(false, 10, D3DCOLOR_RGBA(0, 0, 0, 255));
	
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: TittleUpdate
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void TittleUpdate(void)
{
	//SceneChange(SCENE_INDEX_GAME);	//デバッグ用
	CursorUpate();

	if (!g_bNextScene)
	{
		if (key.getTrigger(DIK_W))
		{
			//SelectNum = (SelectNum + 2) % 3;
			SelectNum++;
		}

		if (key.getTrigger(DIK_S))
		{
			//SelectNum = (SelectNum + 1) % 3;
			SelectNum++;
		}

		if (key.getTrigger(DIK_SPACE))
		{
			FadeStart(true, 10, D3DCOLOR_RGBA(0, 0, 0, 255));

			g_bNextScene = true;

			PlaySound(SOUND_LABEL_SE_SHOT);
			
			
		}
	}

	else
	{
		if (!FadeIsFade())
		{
			if (SelectNum % 2 == 0) {
				SceneChange(SCENE_INDEX_GAME);
			}

			if (SelectNum % 2 == 1) {
				SceneChange(SCENE_INDEX_TUTORIAL);
			}
		}
	}

	Select = SelectNum % 2;
	
	/*if (Keyboard_IsPress(DIK_SPACE))
	{
		SceneChange(SCENE_INDEX_GAME);
	}*/	
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: TittleDraw
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void TittleDraw(void)
{
	SpriteDrawSp(TEXTURE_INDEX_TITLE, 0, 0, 1280, 760, 0, 0, 1, 1, 0);
	SpriteDraw(TEXTURE_INDEX_GAMEMODESTART,		SCREEN_WIDTH / 2 -150, 400, 300, 100, 0.8);
	SpriteDraw(TEXTURE_INDEX_GAMEMODETUTORIAL,	SCREEN_WIDTH / 2 -150, 500, 300, 100, 0.8);
	CursorDraw(Select);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void TittleUnInit(void)
{

}