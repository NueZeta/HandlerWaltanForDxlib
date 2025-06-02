// �����C�u�����ŕK�{�ɂȂ�C���N���[�h�t�@�C��
// "DxLib.h" ��include�����
#include "HandlerWaltanForDxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DX���C�u�����̏��������������˂Ă���
	if (HandlerWaltan::Instance().Init() == -1)
	{
		return 0;
	}


#ifdef _DEBUG

	// ��: 1920, ����: 1080, �r�b�g�[�x: 32
	SetGraphMode(1920, 1080, 32);
	ChangeWindowMode(TRUE);
	// �f�o�b�O���[�h�ŋN��
	HandlerWaltan::debugMode = true;

#else

	// ��: 1920, ����: 1080, �r�b�g�[�x: 32
	SetGraphMode(1920, 1080, 32);
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(FALSE);
	// ��f�o�b�O���[�h�ŋN��
	HandlerWaltan::debugMode = false;

#endif // DEBUG


	SetUseZBuffer3D(TRUE);     // �f�v�X�o�b�t�@�iZ�o�b�t�@�j��L���ɂ���
	SetWriteZBuffer3D(TRUE);   // Z�o�b�t�@�ւ̏������݂�L���ɂ���

	//! �n���h���[�⃉�C�t�T�C�N���Ɋ�Â����^�C�~���O�Ń��\�b�h�������I�ɌĂяo���I�u�W�F�N�g
	//! �V���O���g���Ő݌v����Ă��邽�߁A�ȉ��̕��@�ȊO�ŃC���X�^���X���擾���邱�Ƃ͂ł��Ȃ�
	HandlerWaltan& HW = HandlerWaltan::Instance();

	//! �I�u�W�F�N�g�̐���(unity�ł����Ƃ����GameObject�̐���)
	HWGameObject* obj = new HWGameObject();

	//! �R���X�g���N�^�̈����Ŗ��O��v���C�I���e�B�̏����ݒ���\(�w�肵�Ȃ������ꍇ�͖��O��"hwObj",
	//! �v���C�I���e�B�� 0 �ɂȂ�)
	// HWGameObject* obj = new HWGameObject("obj");
	// HWGameObject* obj = new HWGameObject(20);
	// HWGameObject* obj = new HWGameObject("obj", 20);


	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		//����ʏ���
		ClearDrawScreen();
		//�`���𗠉�ʂ�
		SetDrawScreen(DX_SCREEN_BACK);

		// ESCAPE�L�[�̓��͂ŏI��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;


		// �S�Ă�Update���\�b�h��S�ČĂяo��
		HW.Update();

		DrawFormatString(0, 0, GetColor(255, 255, 255), "Escape key to exit");

		//����ʂ�\��ʂɃR�s�[
		ScreenFlip();
	}

	// �\�t�g�̏I�� 
	HandlerWaltan::End();

	return 0;
}