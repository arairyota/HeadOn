#include "sprite.h"
#include "Texture.h"
#include "Direct3D.h"
#include "DebugPrintf.h"
#include "sprite.h"
#include "common.h"

static unsigned short int TextureUV = 0;
static unsigned short int TextureUV_X = 0;
static unsigned short int TextureUV_Y = 0;
static unsigned int FrameCnt = 0;


//////////////////////////////////////////////////////////////////////////////
//�\���̐錾
//////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	D3DXVECTOR4 position;	//���_ �N���Xfloatx,y,z,w�������Ă���
	D3DCOLOR color;			//�F�ݒ�
	D3DXVECTOR2 texcode;	//�e�N�X�`��
}My_Vertex2D;

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	SpriteDraw
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void SpriteDrawBack(int texture_index, float dx, float dy)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();

}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	SpriteDrawEx
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void SpriteDrawEx(int texture_index, float dx, float dy, int tx, int ty, int tw, int th)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();

	int w = Texture_GetWidth(texture_index);
	int h = Texture_GetHeight(texture_index);

	float u0 = (float)tx / (float)w;
	float v0 = (float)ty / (float)h;
	float u1 = (float)(tx + tw) / (float)w;
	float v1 = (float)(ty + th) / (float)h;

	//�|���S���f�[�^�쐬 �B
	My_Vertex2D v[] = {
		{ D3DXVECTOR4(dx,      dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0 , v0) },
		{ D3DXVECTOR4(dx + tw, dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1 , v0) },
		{ D3DXVECTOR4(dx,      dy + th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0 , v1) },
		{ D3DXVECTOR4(dx + tw, dy + th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1 , v1) }
		
	};

	//�e�N�X�`���ݒ�
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	//�f�o�C�X��ݒ� �C
	g_pD3DDevice->SetFVF(FVF_VERTEX2D);

	//�v���~�e�B�u�ݒ�  �D
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(My_Vertex2D));		//�i�`�A�@���A�@�\���̂̃f�[�^�A�@�jp158~159


}

bool SpriteDrawSp(int texture_index, float dx, float dy, int tw, int th, float cx, float cy, float sx, float sy, float rotatsion)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();
	HRESULT hr;

	if (!g_pD3DDevice) {
		return false;
	}

	int w = Texture_GetWidth(texture_index);
	int h = Texture_GetHeight(texture_index);

	//��]��
	float px0 = (float)((-cx)      * sx * cos(rotatsion) - (-cy)      *sy * sin(rotatsion));
	float py0 = (float)((-cx)      * sx * sin(rotatsion) + (-cy)      *sy * cos(rotatsion));
				 								  	
	float px1 = (float)((-cx + tw) * sx * cos(rotatsion) - (-cy)      *sy  * sin(rotatsion));
	float py1 = (float)((-cx + tw) * sx * sin(rotatsion) + (-cy)      *sy  * cos(rotatsion));
				 
	float px2 = (float)((-cx)      * sx * cos(rotatsion) - (-cy + th) *sy  * sin(rotatsion));
	float py2 = (float)((-cx)      * sx * sin(rotatsion) + (-cy + th) *sy  * cos(rotatsion));
				
	float px3 = (float)((-cx + tw) * sx * cos(rotatsion) - (-cy + th) *sy  * sin(rotatsion));
	float py3 = (float)((-cx + tw) * sx * sin(rotatsion) + (-cy + th) *sy  * cos(rotatsion));


	//�|���S���f�[�^�쐬 �B
	My_Vertex2D v[] = {
		{ D3DXVECTOR4(px0 + dx + cx,	py0 + dy + cy,	1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0 , 0) },
		{ D3DXVECTOR4(px1 + dx + cx,	py1 + dy + cy,	1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1 , 0) },
		{ D3DXVECTOR4(px2 + dx + cx,	py2 + dy + cy,	1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0 , 1) },
		{ D3DXVECTOR4(px3 + dx + cx,	py3 + dy + cy,	1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1 , 1) }
	};

	//�f�o�C�X��ݒ� �C
	hr =g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	if (hr == D3DERR_INVALIDCALL)
	{
		DebugPrintf("test");
	}

	//�e�N�X�`���ݒ�
	hr = g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));
	if (hr == D3DERR_INVALIDCALL)
	{
		DebugPrintf("test");
	}

	//�v���~�e�B�u�ݒ�D
	hr = g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(My_Vertex2D));		//�i�`�A�@���A�@�\���̂̃f�[�^�A�@�jp158~159
	if (hr == D3DERR_INVALIDCALL)
	{
		DebugPrintf("test");
	}

	return true;
}


void SpriteDraw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, int size)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();

	int w = Texture_GetWidth(texture_index);
	int h = Texture_GetHeight(texture_index);

	float u0 = (float)tx / (float)w;
	float v0 = (float)ty / (float)h;
	float u1 = (float)(tx + tw) / (float)w;
	float v1 = (float)(ty + th) / (float)h;

	//�|���S���f�[�^�쐬 �B
	My_Vertex2D v[] = {
		{ D3DXVECTOR4(dx,      dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0 , v0) },
		{ D3DXVECTOR4(dx + (tw * size), dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1 , v0) },
		{ D3DXVECTOR4(dx,      dy + (th * size), 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0 , v1) },
		{ D3DXVECTOR4(dx + (tw * size), dy +( th * size), 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1 , v1) }

	};

	//�e�N�X�`���ݒ�
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	//�f�o�C�X��ݒ� �C
	g_pD3DDevice->SetFVF(FVF_VERTEX2D);

	//�v���~�e�B�u�ݒ�  �D
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(My_Vertex2D));		//�i�`�A�@���A�@�\���̂̃f�[�^�A�@�jp158~159
}

void SpriteDraw(int texture_index, float dx, float dy, int tw, int th, float size)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();

	int w = Texture_GetWidth(texture_index);
	int h = Texture_GetHeight(texture_index);

	//�|���S���f�[�^�쐬 �B
	My_Vertex2D v[] = {
		{ D3DXVECTOR4(dx,      dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0 , 0) },
		{ D3DXVECTOR4(dx + (tw * size), dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1 , 0) },
		{ D3DXVECTOR4(dx,      dy + (th * size), 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0 , 1) },
		{ D3DXVECTOR4(dx + (tw * size), dy + (th * size), 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1 , 1) }

	};

	//�e�N�X�`���ݒ�
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	//�f�o�C�X��ݒ� �C
	g_pD3DDevice->SetFVF(FVF_VERTEX2D);

	//�v���~�e�B�u�ݒ�  �D
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(My_Vertex2D));		//�i�`�A�@���A�@�\���̂̃f�[�^�A�@�jp158~159
}

void SpriteDrawHp(int texture_index, float dx, float dy, int life, int th)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();

	int w = Texture_GetWidth(texture_index);
	int h = Texture_GetHeight(texture_index);

	//�|���S���f�[�^�쐬 �B
	My_Vertex2D v[] = {
		{ D3DXVECTOR4(dx,      dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0 , 0) },
		{ D3DXVECTOR4(dx + life, dy,      1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1 , 0) },
		{ D3DXVECTOR4(dx,      dy + th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0 , 1) },
		{ D3DXVECTOR4(dx + life, dy + th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1 , 1) }

	};

	//�e�N�X�`���ݒ�
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	//�f�o�C�X��ݒ� �C
	g_pD3DDevice->SetFVF(FVF_VERTEX2D);

	//�v���~�e�B�u�ݒ�  �D
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(My_Vertex2D));		//�i�`�A�@���A�@�\���̂̃f�[�^�A�@�jp158~159
}