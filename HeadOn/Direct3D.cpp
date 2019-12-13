//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "Direct3D.h"
#include "common.h"
#include "Texture.h"


//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDev = NULL;


//////////////////////////////////////////////////////////////////////////////
//�֐���	:	Direct3D_Init
//�߂�l	:	bool
//����		:	�f�o�C�X������
//////////////////////////////////////////////////////////////////////////////
bool Direct3D_Init(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	//Direct3D�C���^�[�t�F�[�X p40
	D3DPRESENT_PARAMETERS d3dpp = {};			//�f�o�C�X���擾���邽�߂̍\����

												//D3DPRESENT_PARAMETERS�\���̂̐ݒ�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//�o�b�N�o�b�t�@�̕��̐ݒ�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//�����̐ݒ� p41
	d3dpp.BackBufferCount = 1;					//�o�b�N�o�b�t�@�̖���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//�t���X�N���[�����g�p����ꍇ�K������� UNKNOWN�E�B���h�E�Ȃ�g���� p47

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v�G�t�F�N�gp45 ��ԏ����̑����̂�ݒ�@�������S��ʏ��������@���t���[����ʃN���A�K�{

	d3dpp.Windowed = true;						//��ʃ��[�h�̎w��false�Ńt���X�N���[�����������j�^�[�h���C�o�[�őΉ����Ă�����̂�����΂��̉𑜓x�ɂ��Ă����

	d3dpp.EnableAutoDepthStencil = TRUE;		//3D�Ŏg��p44

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�f�v�X�o�b�t�@16�r�b�g stencil���g����~

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//�t���X�N���[���̎��ɂ����Ӗ����Ȃ�

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//���j�^�[�̘b�������� 


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
			MessageBox(hWnd, "�擾���s", "�G���[", MB_OK);
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
//�֐���	:	Direct3D_Uninit
//�߂�l	:	void
//����		:	�f�o�C�X��Еt��
//////////////////////////////////////////////////////////////////////////////
void Direct3D_Uninit(void)
{
	//�g���I��������� p55
	if (g_pD3DDev)		//�ꏊ���킩��Ȃ��ƃE�B���h�E�Y���G���[��f��
	{
		g_pD3DDev->Release();		//
		g_pD3DDev = NULL;					//��Еt��
	}

	if (g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	FontRelease();
}


//////////////////////////////////////////////////////////////////////////////
//�֐���	:	Direct3D_GetDevice
//�߂�l	:	LPDIRECT3DDEVICE9
//����		:	�f�o�C�X�擾
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE9 Direct3D_GetDevice(void)
{
	return g_pD3DDev;
}