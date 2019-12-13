#ifndef SPRITE_H_
#define SPRITE_H_

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//FVF�������ɏ���	VERTEX2D��FVF RHW�ɂP�𗧂ĂȂ���2D�ɂȂ�Ȃ�

#include<d3dx9.h>
#include<math.h>

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
void SpriteDrawBack(int texture_index, float dx, float dy);
void SpriteDrawEx(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);	//�e�N�X�`�����Wfloat dy
bool SpriteDrawSp(int texture_index, float dx, float dy, int tw, int th, float cx, float cy, float sx, float sy, float rotation);	//�����Ŋ֐�
void SpriteDraw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, int size);
void SpriteDraw(int texture_index, float dx, float dy, int tw, int th, float size);
void SpriteDrawHp(int texture_index, float dx, float dy, int life, int th);

#endif // !SPRITE_H_
