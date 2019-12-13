/*****************************************************************************
input.cpp
Aythor	: 上野　匠
Data	: 2017_05_26
=============================================================================
Updata

*****************************************************************************/
#ifndef INPUT_H
#define INPUT_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include <dinput.h>

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define NUM_MOUSE_MAX		(8)		// マウスの最大数
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター

#define MOUSE_LEFT			(0)		//左クリック
#define MOUSE_RIGHT			(1)		//右クリック
#define MOUSE_CENTER		(2)		//ホイールボタン

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class Input
{
public:
	Input() :mDIDevice(nullptr) {}
	~Input() {}

	virtual HRESULT init(HINSTANCE inst);
	virtual void	uninit(void);
	virtual HRESULT	update(void) = 0;

protected:
	static LPDIRECTINPUT8	mDinput;
	LPDIRECTINPUTDEVICE8 mDIDevice;
};

class	InputKeyboard :public Input
{
public:
	InputKeyboard(){}
	~InputKeyboard(){}

	HRESULT	init(HINSTANCE hInstance, HWND hWnd);
	void	uninit(void);
	HRESULT	update(void);

	static InputKeyboard*	create(HINSTANCE hInstance, HWND hWnd);
	static bool				getPress(int nKey);
	static bool				getTrigger(int nKey);
	static bool				getRepeat(int nKey);
	static bool				getRelease(int nKey);

private:
	static BYTE	mKeyState[NUM_KEY_MAX];				// キーボードの入力情報ワーク
	static BYTE	mKeyStateTrigger[NUM_KEY_MAX];		// キーボードのトリガー情報ワーク
	static BYTE	mKeyStateRelease[NUM_KEY_MAX];		// キーボードのリリース情報ワーク
	static BYTE	mKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
	static int	mKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
};

class InputMouse : public Input
{
public:
	InputMouse();
	~InputMouse() {}

	HRESULT init(HINSTANCE inst, HWND wnd);
	void	uninit(void);
	HRESULT	update(void);

	static InputMouse*	create(HINSTANCE hInstance, HWND hWnd);
	static BOOL		getPress(const int button);
	static BOOL		getTrigger(const int button);
	static BOOL		getRelease(const int button);
	static LONG		getHweelX(void) {}
	static LONG		getHweelY(void) {}
	static LONG		getHweelZ(void) {}
	static POINT	getPos(void) { return mPosMouse; }
	static POINT	getScreenPos(void);
	static Dvec2	getMoving(void) { return Dvec2((float)mMouseState.lX, (float)mMouseState.lY); }
	static LONG		getWheel(void) { return mMouseState.lZ;}
	static void		fixing(bool flag);
	static void		setCenter(void);
	static void		setPos(POINT pos);
	static void		setScreenPos(POINT pos);
	//const POINT	*getPos(void){return &mPosMouse;}

private:
	static DIMOUSESTATE2	mMouseState;			//マウス
	static DIMOUSESTATE2	mMouseStateTrigger;		//トリガーの状態
	static DIMOUSESTATE2	mMouseStateRelease;		//マウスを放したか
	static POINT			mPosMouse;				//マウス座標
	static bool				mFixing;				//trueで位置固定
};

static	InputKeyboard	key;
static	InputMouse		mouse;

#endif