/*****************************************************************************
main.h
Aythor	: 上野　匠
Data	: 2017_04_19
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <d3dx9.h>
#include <windows.h>
#include <xaudio2.h>
#define	DisableLoad	(0x0800)

//ライブラリリンク
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")		//システム時刻取得に必要
#pragma comment (lib, "dinput8.lib")	//入力装置ライブラリ

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define PACKAGE_EDITOR
//#define MAP_EDITOR
//#define MOTION_EDITOR
//#define COLLISION_EDITOR
//#define GAME

#ifdef PACKAGE_EDITOR
#define CLASS_NAME	"PACKAGE_EDITOR"		//ウィンドウのクラス名
#endif // PACKAGE_EDITOR


#define WINDOW_NAME	"ウィンドウ"	//ウィンドウの名前
#define SCREEN_WIDTH	(1280)		//ウィンドウの高さ
#define SCREEN_HEIGHT	(720)		//ウィンドウの幅

#define TIMER_INTERVAL	(1000/60)	//待ち時間

#define NUM_VERTEX		(4)			//頂点数
#define NUM_POLYGON		(2)			//ポリゴン数

#define PI				(3.141592f)	//円周率

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef D3DXCOLOR		Dcolor;
typedef D3DXMATRIX		Dmtx;
typedef D3DXQUATERNION	DQuate;
typedef D3DXMATRIX		DMtx;
typedef D3DXVECTOR3		Dvec3;
typedef D3DXVECTOR2		Dvec2;
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HWND getWnd(void);
int GetFPS(void);
POINT getClientSize();