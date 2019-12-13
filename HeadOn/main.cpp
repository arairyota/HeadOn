/*****************************************************************************
windowの表示[main.cpp]
Aythor	:	新井　崚太
Data	:	2018/06/18
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
//#include "DebugPrintf.h"
#include <stdio.h>
#include "common.h"
#include "system_timer.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define CLASS_NAME		"テクスチャ"
#define WINDOW_CAPTION	"シューティングゲーム基礎"	//名前はなんでもおｋ(課題名とか)
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX))	//スタイル

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
bool Init(HINSTANCE hInstance, HWND hWnd);
void Update(HWND hWnd);
void Draw(void);
void Uninit(void);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
static unsigned short int TextureUV = 0;
static unsigned short int TextureUV_X = 0;
static unsigned short int TextureUV_Y = 0;
static unsigned int FrameCnt = 0;
static float g_rotation;


//FPSカウンター用
static int g_FrameCounter = 0;
static int g_FPSBaseFrameCount = 0;
static double g_FPSBaseTime = 0.0;
//static double g_FPsBaseTime2 = 0.0;

//static float BulletSpeed = 0.0f;
//static float BulletPosX = 0.0f;


//////////////////////////////////////////////////////////////////////////////
//関数名	:	APIENTRY WindMain
//戻り値	:
//説明		:	メイン関数
//////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	//変数宣言
	DWORD wind_style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);	//スタイル変数宣言


	//クラスの登録
	WNDCLASS wc = {};									//構造体の初期化を忘れない, 0で初期化の省略
	wc.lpfnWndProc = WndProc;							//CALLBACK関数の登録
	wc.lpszClassName = CLASS_NAME;						//名前はなんでもおｋ
	wc.hInstance = hInstance;							//インスタンスハンドル
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			//マウスカーソルを通常に
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//バックグラウンドカラー(+1は仕様)


	RegisterClass(&wc);				//システムへの登録

	 
	//基本矩形座標
	RECT wind_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};		//RECT構造体に幅と高さをいれる(矩形)

	
	//ウィンドウの余分なところを調整する
	AdjustWindowRect(
		&wind_rect,		//先頭アドレス
		WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),	//ウィンドスタイルフラグ(ビット)  ^ (ウィンドウサイズを引っ張って変更できなくする | XOR演算子)
		FALSE			//大文字のBOOL
		);
		

	//ウィンドウのサイズ確定
	unsigned short window_width = (unsigned short)(wind_rect.right - wind_rect.left);		//幅計算
	unsigned short window_heigth = (unsigned short)(wind_rect.bottom - wind_rect.top);	//高さ計算


	//ハードディスクからいろいろデータを取ってっ来る
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);	//(プライマリモニターの幅)
	int desktop_heigth = GetSystemMetrics(SM_CYSCREEN);	//(高さ)


	//画面の中央に表示する為の値を求める処理
	desktop_width = max((desktop_width - window_width) / 2, 0);
	desktop_heigth = max((desktop_heigth - window_heigth) / 2, 0);

	
	//ウィンドの生成			
	//ウィンド生成するとウィンドハンドルがもらえる(重要)
	HWND hWnd = CreateWindow(
		CLASS_NAME,				//クラス名(関連性を持たせる)
		WINDOW_CAPTION,			//キャプション(ウィンドのタイトル)
		wind_style,				//ウィンドスタイルフラグ(ビット)  ^ (ウィンドウサイズを引っ張って変更できなくする | XOR演算子)
		desktop_width,			//X
		desktop_heigth,			//Y
		window_width,			//幅
		window_heigth,			//高さ
		NULL,					//親のウィンドウハンドル(今回はないからNULL)
		NULL,					//メニューハンドル(上に同じく)
		hInstance,				//インスタンスハンドル
		NULL					//メッセージに送るオリジナルデータなどのポインタ
		);


	//hWnd == NULL retrun 0 or -1で消すようにする or メッセージBoxで警告を出す


	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);		//ShowWindowで検索 とりあえずはnCmdShow


	//メッセージ処理 or メッセージループ(ループ処理をして情報を待つ)
	MSG msg = {};

	Init(hInstance, hWnd);

	//全体のループ
	do{ 
			//もしメッセージがあったら
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			//なかったら
			else
			{
				//ゲーム処理
				Update(hWnd);
				Draw();
				SceneCheck();
				//g_FrameBaseTime = SystemTimer_GetTime();
			}

		} while (msg.message != WM_QUIT);


	return (int)msg.wParam;

}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)	//DispatchMessageとほぼ同じを入れる
	{
	case WM_KEYDOWN:		//esckeyが押されたら
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if(MessageBox(hWnd,"終了しますか?", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);
		}

		return 0;	//だめならなかったことにする

	case WM_DESTROY:		//ウィンドウの破棄メッセージ
		PostQuitMessage(0);		
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//普通のメッセージが肩代わりする(やらせたくないことを引数にいれる)

}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	Init
//戻り値	:
//説明		:	初期化
//////////////////////////////////////////////////////////////////////////////
bool Init(HINSTANCE hInstance, HWND hWnd)
{
	key.init(hInstance, hWnd);
	mouse.init(hInstance, hWnd);

	InitSound(hWnd);

	Direct3D_Init(hWnd);

	SceneInit(SCENE_INDEX_TITTLE);

	FadeInit();			//フェード初期化

	if (!Direct3D_Init(hWnd))
	{
		//messegeboxで失敗だったら
		MessageBox(hWnd, "取得失敗", "エラー", MB_OK);
	}

	LPDIRECT3DDEVICE9 g_pD3DDev = Direct3D_GetDevice();
	
	g_pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);			//テクスチャサンプラー設定 p228(0, アドレッシングモードＵ方向設定 )彼女と合コンした後に住所聞く

	g_pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	
	
	g_pD3DDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		//テクスチャフィルタリング p232 

	g_pD3DDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		//ポリゴン座標を0.5にずらすと色が汚くならない

	g_pD3DDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);		//拡大縮小の多いゲームに設定

	g_pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンディングを有効(彼女の性格設定,あまり変えすぎると拗ねる)
	g_pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//描画元設定
	g_pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//描画先設定

	//α成分の計算式を無理やり変える 上から 左辺* 右辺
	g_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//(テクスチャステージ数, 左辺値D3D)α乗算
	g_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		//(							右辺値)ポリゴンカラー
	g_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		//モデュレート　＝　*
	
	//システムタイマー初期化
	SystemTimer_Initialize();

	//タイマースタート
	SystemTimer_Start();

	g_FPSBaseFrameCount = 0;

	g_FPSBaseTime = SystemTimer_GetTime();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	Update
//戻り値	:
//説明		:	更新
//////////////////////////////////////////////////////////////////////////////
void Update(HWND hWnd)
{
	key.update();
	mouse.update();

	FadeUpdate();

	SceneUpdate();

	FrameCnt++;

	//g_rotation += 0.01f;

	//rx = px * cos(rad) - py * sin(rad);
	//ry = px * sin(rad) + py * cos(rad);

	/*TextureUV = (FrameCnt / WAIT_FRAME) % 10;

	TextureUV_X = (700 / 5) * (TextureUV % 5);

	TextureUV_Y = (400 / 2) * (TextureUV / 5);
	*/

	
	g_FrameCounter++;

	double time = SystemTimer_GetTime();

	if (time - g_FPSBaseTime > 1.0f)
	{
		char buf[256];
		sprintf(buf, "%.2f fps", (g_FrameCounter - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));
		SetWindowText(hWnd, buf);

		g_FPSBaseTime = time;
		g_FPSBaseFrameCount = g_FrameCounter;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	Draw
//戻り値	:
//説明		:	描画
//////////////////////////////////////////////////////////////////////////////
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 255, 255), 1.0f, 0);	//画面クリア TARGET 色クリア Z_BUFFER 深さ 0が一番手前 1が一番後ろ
	pDevice->BeginScene();

	SceneDraw();

	FadeDraw();

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);	//前画面の後ろ画面を変える処理
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	Uninit
//戻り値	:
//説明		:	終了
//////////////////////////////////////////////////////////////////////////////
void Uninit(void)
{
	key.uninit();
	mouse.uninit();
	Texture_Release();
	Direct3D_Uninit();
	SceneUnInit();
	EffectUninit();
	UninitSound();
}