//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "Direct3D.h"
#include "common.h"
#include "Texture.h"


//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDev = NULL;


//////////////////////////////////////////////////////////////////////////////
//関数名	:	Direct3D_Init
//戻り値	:	bool
//説明		:	デバイス初期化
//////////////////////////////////////////////////////////////////////////////
bool Direct3D_Init(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	//Direct3Dインターフェース p40
	D3DPRESENT_PARAMETERS d3dpp = {};			//デバイスを取得するための構造体

												//D3DPRESENT_PARAMETERS構造体の設定
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//バックバッファの幅の設定
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//高さの設定 p41
	d3dpp.BackBufferCount = 1;					//バックバッファの枚数
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//フルスクリーンを使用する場合必ず入れる UNKNOWNウィンドウなら使える p47

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//スワップエフェクトp45 一番処理の早いのを設定　ただし全画面書き換え　毎フレーム画面クリア必須

	d3dpp.Windowed = true;						//画面モードの指定falseでフルスクリーンただしモニタードライバーで対応しているものがあればその解像度にしてくれる

	d3dpp.EnableAutoDepthStencil = TRUE;		//3Dで使うp44

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//デプスバッファ16ビット stencilを使う時~

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//フルスクリーンの時にしか意味がない

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//モニターの話水平同期 


	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev);

	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev);


		if (FAILED(hr))
		{
			hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev);
		}

		if (FAILED(hr))
		{
			MessageBox(hWnd, "取得失敗", "エラー", MB_OK);
		}
	}
	FontLoad();

	if (Texture_Load() > 0) {
		return false;
	}
	else
	{
		return true;
	}

}


//////////////////////////////////////////////////////////////////////////////
//関数名	:	Direct3D_Uninit
//戻り値	:	void
//説明		:	デバイス後片付け
//////////////////////////////////////////////////////////////////////////////
void Direct3D_Uninit(void)
{
	//使い終わったら解放 p55
	if (g_pD3DDev)		//場所がわからないとウィンドウズがエラーを吐く
	{
		g_pD3DDev->Release();		//
		g_pD3DDev = NULL;					//後片付け
	}

	if (g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	FontRelease();
}


//////////////////////////////////////////////////////////////////////////////
//関数名	:	Direct3D_GetDevice
//戻り値	:	LPDIRECT3DDEVICE9
//説明		:	デバイス取得
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE9 Direct3D_GetDevice(void)
{
	return g_pD3DDev;
}