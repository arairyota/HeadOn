#include "common.h"
#include "Scene.h"
#include "Tittle.h"
#include "Game.h"
#include "Result.h"
#include "Tutorial.h"
#include "Timer.h"

static SCENE_INDEX g_SceneIndex = SCENE_INDEX_TITTLE;
static SCENE_INDEX g_SceneNextIndex = g_SceneIndex;

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneInit
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void SceneInit(SCENE_INDEX index)
{
	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_INDEX_TITTLE:
		TittleInit();
		break;

	case SCENE_INDEX_GAME:
		GameInit();
		break;

	case SCENE_INDEX_RESULT:
		ResultInit();
		break;

	case SCENE_INDEX_TUTORIAL:
		TutorialInit();
		break;

	case SCENE_INDEX_GAMEOVER:
		GameOverInit();
		break;
	}
	TimerInit();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneUpdate
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void SceneUpdate(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_INDEX_TITTLE:
		TittleUpdate();
		break;

	case SCENE_INDEX_GAME:
		GameUpdate();
		break;

	case SCENE_INDEX_RESULT:
		ResultUpdate();
		break;

	case SCENE_INDEX_TUTORIAL:
		TutorialUpdate();
		break;

	case SCENE_INDEX_GAMEOVER:
		GameOverUpdate();
		break;
	}
	TimerUpdate();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneDraw
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void SceneDraw(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_INDEX_TITTLE:
		TittleDraw();
		break;

	case SCENE_INDEX_GAME:
		GameDraw();
		break;

	case SCENE_INDEX_RESULT:
		ResultDraw();
		break;

	case SCENE_INDEX_TUTORIAL:
		TutorialDraw();
		break;

	case SCENE_INDEX_GAMEOVER:
		GameOverDraw();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneCheck
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void SceneCheck(void)
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		SceneUnInit();

		SceneInit(g_SceneNextIndex);


	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneUnInit
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void SceneUnInit(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_INDEX_TITTLE:
		TittleUnInit();
		break;

	case SCENE_INDEX_GAME:
		GameUnInit();
		break;

	case SCENE_INDEX_RESULT:
		ResultUnInit();
		break;

	case SCENE_INDEX_TUTORIAL:
		TutorialUnInit();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneChange
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void SceneChange(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}