#include "nember.h"
#include "common.h"

//ƒOƒ[ƒoƒ‹•Ï”
/*static unsigned short int TextureUV = 0;
static unsigned short int TextureUV_X = 0;
static unsigned short int TextureUV_Y = 0; */

void NemberDraw(float x, float y, int n)
{
	SpriteDraw(TEXTURE_INDEX_NUMBER, x, y, n *  NEMBER_WIDTH, 0, NEMBER_WIDTH, NEMBER_HEIGHT, 1);
}