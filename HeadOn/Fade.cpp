#include "common.h"

typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
}FADEVERTEX;

#define FADE_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

static bool g_bFade = false;								//フェードしてるかしてないか
static bool g_bOut = false;									//フェードアウトするかインするか
static float g_Alpha = 0.0f;
static float g_AddAlpha = 0.0f;								//アルファ値にどれだけ入れるか 1が透明0が不透明
static D3DCOLOR g_color = D3DCOLOR_RGBA(0, 0, 0, 255);		//色とアルファ値設定
static int g_FadeFrame = 0;									
static int g_FadeFrameCount = 0;

//////////////////////////////////////////////////////////////////////////////
//関数名	: FadeInit
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void FadeInit(void)
{
	g_bFade = false;								//フェードしてるかしてないか
	g_Alpha = 0.0f;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: FadeStart
//戻り値	:
//説明		:
//引数		: 
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
//関数名	: FadeUpdate
//戻り値	:
//説明		:
//引数		:
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
//関数名	: FadeDraw
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void FadeDraw(void)
{
	if (g_Alpha <= 0.000001f)
	{
		return;
	}

	D3DXCOLOR color = g_color;		//Xを使うとfloat型が使える(先生に許可を取る)

	color.a = g_Alpha;

	FADEVERTEX v[] = {
		{ D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), color},
		{ D3DXVECTOR4(SCREEN_WIDTH, 0.0f, 1.0f, 1.0f), color},
		{ D3DXVECTOR4(0.0f, SCREEN_HEIGHT, 1.0f, 1.0f), color},
		{ D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 1.0f), color}

	};

	LPDIRECT3DDEVICE9 g_pD3DDevice = Direct3D_GetDevice();

	//テクスチャ設定
	g_pD3DDevice->SetTexture(0, NULL);

	//デバイスを設定 ④
	g_pD3DDevice->SetFVF(FADE_VERTEX2D);

	//プリミティブ設定  ⑤
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FADEVERTEX));
}

bool FadeIsFade(void)
{
	return g_bFade;
}