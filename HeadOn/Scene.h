#ifndef SCENE_H_
#define SCENE_H_

typedef enum
{
	SCENE_INDEX_TITTLE,
	SCENE_INDEX_RESULT,
	SCENE_INDEX_GAME,
	SCENE_INDEX_TUTORIAL,
	SCENE_INDEX_GAMEOVER
}SCENE_INDEX;

void SceneInit(SCENE_INDEX);
void SceneUpdate(void);
void SceneDraw(void);
void SceneCheck(void);
void SceneUnInit(void);

void SceneChange(SCENE_INDEX index);

#endif // !SCENE_H_
