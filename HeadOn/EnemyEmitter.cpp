#include "common.h"
#include "enemy.h"


typedef struct
{
	float x, y;
	int frame;
	// ENEMY_TYPE type;
}ENEMYEMITTER;

static ENEMYEMITTER EnemyEmitter[] = {

	{ SCREEN_WIDTH, 100.0f, 60 },
	{ SCREEN_WIDTH, 200.0f, 60 },
	{ SCREEN_WIDTH, 300.0f, 60 },
	{ SCREEN_WIDTH, 400.0f, 60 },
	{ SCREEN_WIDTH, 500.0f, 60 },

	{ SCREEN_WIDTH, 100.0f, 120 },
	{ SCREEN_WIDTH, 200.0f, 120 + 30  },
	{ SCREEN_WIDTH, 300.0f, 120 + 60  },
	{ SCREEN_WIDTH, 400.0f, 120 + 90  },
	{ SCREEN_WIDTH, 500.0f, 120 + 120 },

	{ 0.0f, 0.0f, -1 }		//ÉèÉìÉãÅ[ÉvèIÇÌÇ¡ÇΩÇ®
};

static int FrameCount = 0;
static int Index = 0;


void EnemyEmitter_Initialize(void)
{
	FrameCount = 0;
	Index = 0;
}

void EnemyEmitter_Finalize(void)
{
}

void EnemyEmitter_Update(void)
{
	for(;;){
		
		if( EnemyEmitter[Index].frame < 0 ) {
			break;
		}
		else if( EnemyEmitter[Index].frame <= FrameCount ) {
			//Enemy_Create(g_EE[g_Index].x, g_EE[g_Index].y);
			Index++;
		}
		else {
			break;
		}
	}

	FrameCount++;
}
