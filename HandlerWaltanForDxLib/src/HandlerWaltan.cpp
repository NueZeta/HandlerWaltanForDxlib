#include "h/HandlerWaltan.h"


/**
* @author   NZ
* @date     24/07/29
* @note		HandlerWaltan�̎����t�@�C��
*/


// �ÓI�����o�ϐ��̏����� ------------------------------------------------------------------------------------------------

bool HandlerWaltan::debugMode = false;
std::vector<InputSystem*> InputSystem::inputSystemVec;

int HWUtility::ScreenSizeX = -1;
int HWUtility::ScreenSizeY = -1;

float Time::deltaTime = 0.0f;
float Time::lastTime = 0.0f;
int Time::targetFPS = -1;  // �f�t�H���g��-1
float Time::targetFrameTime = 1.0f / 60.0f;  // 60FPS�Ȃ�1�t���[���������0.01666�b
bool Time::debugMode = false;
int Time::frameCount = 0;  // �t���[�����̏�����
float Time::elapsedTime = 0.0f;  // �o�ߎ��Ԃ̏�����
unsigned int Time::color = GetColor(255,0,255);

//------------------------------------------------------------------------------------------------------------------------


#pragma region publuc���\�b�h


void HandlerWaltan::Update()
{
    Time::Update();

    // �폜���X�g���Q�Ƃ��A�J�E���g��0�ɂȂ����I�u�W�F�N�g�͍폜����
    for (auto it = HWGameObject::destroyList.begin(); it != HWGameObject::destroyList.end(); )
    {
        if (it->time <= GetNowCount()) 
        {

            delete it->object;  
            it->object = nullptr;
            it = HWGameObject::destroyList.erase(it);  
        }
        else 
            ++it;
    }

    //! Dotween��Update���Ăяo��
    HWDotween::Update();

    //! �C���X�^���X�����ꂽ�S�Ă�GameObject
    auto gameObjects = HWGameObject::GetGameObjects();

    // Transform��Update���\�b�h���Ăяo��
    for (auto obj : gameObjects)
        if(obj->active.load())
            obj->CallTransformUpdate();

    // �C���X�^���X�����ꂽInputSystem��Update���\�b�h���Ă�
    for (auto it = InputSystem::inputSystemVec.begin(); it != InputSystem::inputSystemVec.end(); ++it)
    {
        if ((*it)->active)
            (*it)->Update();
    }

    // �C���X�^���X�����ꂽ�S�Ă�HWGameObject��Update���\�b�h���Ăяo��
    for (auto obj : gameObjects)
        if(obj->active.load())
            obj->CallAllUpdates();

    // �C���X�^���X�����ꂽ�S�Ă�HWGameObject��LateUpdate���\�b�h���Ăяo��
    for (auto obj : gameObjects)
        if(obj->active.load())
            obj->CallAllLateUpdates();

    // �����蔻����m�F
    CollisionWaltan::Instance().Update();

    // �V�[���̍X�V
	HWSceneManager::Update();


    // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
    UpdateEffekseer3D();

    // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
    DrawEffekseer3D();

    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();

    // �t���[���I�����Ɏ��̃t���[���܂őҋ@�iFPS�Œ�j
    if(Time::targetFPS != -1)
    {
        Time::WaitForNextFrame();
        if (Time::debugMode)
            Time::ShowFPS();
    }
}


#pragma endregion

#pragma region private���\�b�h


HandlerWaltan::HandlerWaltan()
{
}


HandlerWaltan::~HandlerWaltan()
{

}


#pragma endregion

#pragma region static���\�b�h


HandlerWaltan& HandlerWaltan::Instance()
{
    // �V���O���g���C���X�^���X�𐶐�
    static HandlerWaltan instance;
    return instance;
}

int HandlerWaltan::Init(int _particle)
{
    // DX���C�u������Effekseer�̏�����

    // DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    if (DxLib_Init() == -1)		// �c�w���C�u��������������
        // �G���[�R�[�h��Ԃ�
        return -1;

    // Effekseer������������B
    // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Z�o�b�t�@��L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetUseZBuffer3D(TRUE);

    // Z�o�b�t�@�ւ̏������݂�L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetWriteZBuffer3D(TRUE);

    GetWindowSize(&HWUtility::ScreenSizeX, &HWUtility::ScreenSizeY);

    return 0;
}

void HandlerWaltan::End()
{
    // Effekseer���I������B
    Effkseer_End();

    DxLib_End();				// �c�w���C�u�����g�p�̏I������
}

#pragma endregion



