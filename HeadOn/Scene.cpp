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
//�֐���	: SceneInit
//�߂�l	:
//����		:
//����		:
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
//�֐���	: SceneUpdate
//�߂�l	:
//����		:
//����		:
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
//�֐���	: SceneDraw
//�߂�l	:
//����		:
//����		:
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
//�֐���	: SceneCheck
//�߂�l	:
//����		:
//����		:
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
//�֐���	: SceneUnInit
//�߂�l	:
//����		:
//����		:
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
//�֐���	: SceneChange
//�߂�l	:
//����		:
//����		:
//////////////////////////////////////////////////////////////////////////////
void SceneChange(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}