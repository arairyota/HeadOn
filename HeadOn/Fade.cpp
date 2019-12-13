#include "common.h"

typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
}FADEVERTEX;

#define FADE_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

static bool g_bFade = false;								//�t�F�[�h���Ă邩���ĂȂ���
static bool g_bOut = false;									//�t�F�[�h�A�E�g���邩�C�����邩
static float g_Alpha = 0.0f;
static float g_AddAlpha = 0.0f;								//�A���t�@�l�ɂǂꂾ������邩 1������0���s����
static D3DCOLOR g_color = D3DCOLOR_RGBA(0, 0, 0, 255);		//�F�ƃA���t�@�l�ݒ�
static int g_FadeFrame = 0;									
static int g_FadeFrameCount = 0;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: FadeInit
//�߂�l	:
//����		:
//����		:
//////////////////////////////////////////////////////////////////////////////
void FadeInit(void)
{
	g_bFade = false;								//�t�F�[�h���Ă邩���ĂȂ���
	g_Alpha = 0.0f;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: FadeStart
//�߂�l	:
//����		:
//����		: 
//////////////////////////////////////////////////////////////////////////////
void FadeStart(bool bOut, int frame, D3DCOLOR color)
{
	g_bFade = true;
	g_bOut = bOut;
	g_color = color;
	g_FadeFrame = frame;
	g_FadeFrameCount = 0;

	g_AddAlpha = 1.0f / g_FadeFrame;

	if (g_bOut)
	{
		g_Alpha = 0.0f;
	}

	else
	{
		g_Alpha = 1.0f;
		g_AddAlpha = -g_AddAlpha;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: FadeUpdate
//�߂�l	:
//����		:
//����		:
//////////////////////////////////////////////////////////////////////////////
void FadeUpdate(void)
{
	if (g_bFade)
	{
		g_Alpha = min(max(g_Alpha + g_AddAlpha, 0.0f), 1.0f);

		g_FadeFrameCount++;

		if (g_FadeFrameCount > g_FadeFrame)
		{
			g_FadeFrameCount = g_FadeFrame;
			g_bFade = false;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: FadeDraw
//�߂�l	:
//����		:
//����		:
//////////////////////////////////////////////////////////////////////////////
void FadeDraw(void)
{
	if (g_Alpha <= 0.000001f)
	{
		return;
	}

	D3DXCOLOR color = g_color;		//X���g����float�^���g����(�搶�ɋ������)

	color.a = g_Alpha;

	FADEVERTEX v[] = {
		{ D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), color},
		{ D3DXVECTOR4(SCREEN_WIDTH, 0.0f, 1.0f, 1.0f), color},
		{ D3DXVECTOR4(0.0f, SCREEN_HEIGHT, 1.0f, 1.0f), color},
		{ D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 1.0f), color}

	};

	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();

	//�e�N�X�`���ݒ�
	g_pD3DDevice->SetTexture(0, NULL);

	//�f�o�C�X��ݒ� �C
	g_pD3DDevice->SetFVF(FADE_VERTEX2D);

	//�v���~�e�B�u�ݒ�  �D
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FADEVERTEX));
}

bool FadeIsFade(void)
{
	return g_bFade;
}