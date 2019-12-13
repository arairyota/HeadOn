#ifndef SPRITE_H_
#define SPRITE_H_

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//FVFすぐ下に書く	VERTEX2DのFVF RHWに１を立てないと2Dにならない

#include<d3dx9.h>
#include<math.h>

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void SpriteDrawBack(int texture_index, float dx, float dy);
void SpriteDrawEx(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);	//テクスチャ座標float dy
bool SpriteDrawSp(int texture_index, float dx, float dy, int tw, int th, float cx, float cy, float sx, float sy, float rotation);	//完成版関数
void SpriteDraw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, int size);
void SpriteDraw(int texture_index, float dx, float dy, int tw, int th, float size);
void SpriteDrawHp(int texture_index, float dx, float dy, int life, int th);

#endif // !SPRITE_H_
