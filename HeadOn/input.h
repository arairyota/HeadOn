/*****************************************************************************
input.cpp
Aythor	: ���@��
Data	: 2017_05_26
=============================================================================
Updata

*****************************************************************************/
#ifndef INPUT_H
#define INPUT_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include <dinput.h>

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define NUM_MOUSE_MAX		(8)		// �}�E�X�̍ő吔
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	LIMIT_COUNT_REPEAT	(20)	// ���s�[�g�J�E���g���~�b�^�[

#define MOUSE_LEFT			(0)		//���N���b�N
#define MOUSE_RIGHT			(1)		//�E�N���b�N
#define MOUSE_CENTER		(2)		//�z�C�[���{�^��

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
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
	static BYTE	mKeyState[NUM_KEY_MAX];				// �L�[�{�[�h�̓��͏�񃏁[�N
	static BYTE	mKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[��񃏁[�N
	static BYTE	mKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̃����[�X��񃏁[�N
	static BYTE	mKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	static int	mKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
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
	static DIMOUSESTATE2	mMouseState;			//�}�E�X
	static DIMOUSESTATE2	mMouseStateTrigger;		//�g���K�[�̏��
	static DIMOUSESTATE2	mMouseStateRelease;		//�}�E�X���������
	static POINT			mPosMouse;				//�}�E�X���W
	static bool				mFixing;				//true�ňʒu�Œ�
};

static	InputKeyboard	key;
static	InputMouse		mouse;

#endif