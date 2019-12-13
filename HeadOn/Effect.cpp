#include "common.h"
#include "Effect.h"
//////////////////////////////////////////////////////////////////////////////
//構造体宣言
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR4 position;	//頂点 クラスfloatx,y,z,wが入っている
	D3DCOLOR color;			//色設定
	D3DXVECTOR2 texcode;	//テクスチャ
}EffectVertex;

#define FVF_EFFETC (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//FVFすぐ下に書く	VERTEX2DのFVF RHWに１を立てないと2Dにならない


static EFFECT g_Effect[EFFECT_COUNT_MAX];
static int g_EffectFrameCnt = 0;
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

void EffectInit(void)
{
	//エフェクトの初期化処理
	for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
	{
		g_Effect[cnt].life = -1;

	}
	g_EffectFrameCnt = 0;

	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();
	pDevice->CreateVertexBuffer(sizeof(EffectVertex) * 4 * EFFECT_COUNT_MAX, D3DUSAGE_WRITEONLY, FVF_EFFETC, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * 6 * EFFECT_COUNT_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

}

void EffectCreate(float x, float y, float radius, int life, D3DCOLOR color)
{
	for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
	{
		if (g_Effect[cnt].life < 0)
		{
			g_Effect[cnt].alpha = 1.0f;
			g_Effect[cnt].birth = g_EffectFrameCnt;
			g_Effect[cnt].color = color;
			g_Effect[cnt].life = life;
			g_Effect[cnt].radius = radius;
			g_Effect[cnt].x = x;
			g_Effect[cnt].y = y;
			break;
		}
	}

}

void EffectUpdate(void)
{
	for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
	{
		g_Effect[cnt].x -= 10;
		if (g_Effect[cnt].life >= 0)
		{
			int age = g_EffectFrameCnt - g_Effect[cnt].birth;
			if (age >= g_Effect[cnt].life)
			{
				g_Effect[cnt].life = -1;
				continue;
			}

			g_Effect[cnt].alpha = 1.0f - (float)age / g_Effect[cnt].life;
			D3DXCOLOR c = g_Effect[cnt].color;
			c.a = g_Effect[cnt].alpha;
			g_Effect[cnt].color = c;
			
			g_Effect[cnt].radius *= 0.98f;
			
		}
	}
	g_EffectFrameCnt++;
}

void EffectDraw(void)
{
	EffectVertex* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);

	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	WORD n = 0;	//生きてる数
	for (int cnt = 0; cnt < EFFECT_COUNT_MAX; cnt++)
	{
		if (g_Effect[cnt].life >= 0)
		{
			for (int j = 0; j < 4; j++)
			{
				pV[n * 4 + j].position.x = cos(D3DXToRadian(45 + j * 90)) * g_Effect[cnt].radius + g_Effect[cnt].x;
				pV[n * 4 + j].position.y = sin(D3DXToRadian(45 + j * 90)) * g_Effect[cnt].radius + g_Effect[cnt].y;
				pV[n * 4 + j].position.z = 1.0f;
				pV[n * 4 + j].position.w = 1.0f;
				pV[n * 4 + j].color = g_Effect[cnt].color;
			}

			pV[n * 4 + 0].texcode = D3DXVECTOR2(1.0f, 1.0f);
			pV[n * 4 + 1].texcode = D3DXVECTOR2(0.0f, 1.0f);
			pV[n * 4 + 2].texcode = D3DXVECTOR2(0.0f, 0.0f);
			pV[n * 4 + 3].texcode = D3DXVECTOR2(1.0f, 0.0f);

			pIndex[n * 6 + 0] = n * 4 + 0;
			pIndex[n * 6 + 1] = n * 4 + 1;
			pIndex[n * 6 + 2] = n * 4 + 2;
			pIndex[n * 6 + 3] = n * 4 + 2;
			pIndex[n * 6 + 4] = n * 4 + 3;
			pIndex[n * 6 + 5] = n * 4 + 0;

			n++;
		}
	}

	g_pVertexBuffer->Unlock();
	g_pIndexBuffer->Unlock();

	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(EffectVertex));

	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->SetFVF(FVF_EFFETC);

	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_EFFECT));

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	//加算合成にする

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, n * 4, 0, n * 2);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //元に戻す

	
}

void EffectUninit(void)
{
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}

	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}