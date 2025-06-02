#include "h/HWSceneManager.h"


HWSceneBase* HWSceneManager::crrScene = nullptr;
HWSceneBase* HWSceneManager::loadScene = nullptr;
std::atomic<LoadParameter> HWSceneManager::loadParam = LoadParameter::None;
std::thread HWSceneManager::loadThread;
std::mutex HWSceneManager::loadMutex;


std::unordered_map<std::string, std::function<HWSceneBase*()>>& HWSceneManager::GetRegistry()
{
    //! �V�[���N���X�̓o�^(���O : �N���X���C���X�^���X������R�[���o�b�N�֐�)
    static std::unordered_map<std::string, std::function<HWSceneBase* ()>> registry;
    return registry;
}

void HWSceneManager::RegisterScene(const std::string& name, std::function<HWSceneBase*()> factory)
{
	GetRegistry()[name] = factory;
}

void HWSceneManager::Update()
{
	// �񓯊����[�h���������Ă��邩�m�F
	if (loadParam.load() == LoadParameter::complete)
	{
		// �X���b�h�̏I����҂�
		if (loadThread.joinable())
			loadThread.join();

		// loadScene�̃A�N�Z�X�ɔr������
		std::lock_guard<std::mutex> lock(loadMutex);
		// ���s���̃V�[���̃C���X�^���X�ƃ��[�h�����V�[���̃C���X�^���X������
		std::swap(crrScene, loadScene);
		// �J�ڑO�̃V�[���̃C���X�^���X���폜
		delete loadScene;
		loadScene = nullptr;

		// ���[�h�p�����[�^��ҋ@���ɍX�V
		loadParam.store(LoadParameter::None);
	}
}

HWSceneBase* HWSceneManager::SceneChangeSync(const std::string& name)
{
	// ���[�h�p�����[�^���ҋ@���łȂ��ꍇ�͂��̂܂܏I��
	if (loadParam.load() != LoadParameter::None)
		return nullptr;

	// �V�[�������݂��邩���ׂ�
    auto it = GetRegistry().find(name);

	// ���݂���ꍇ�A�C���X�^���X�����̃R�[���o�b�N�����s
    if (it != GetRegistry().end())
    {
		crrScene = it->second();
        return crrScene;
    }

    // ���݂��Ȃ��ꍇ�A���̂܂܏I��
    return nullptr;
}

void HWSceneManager::SceneChangeAsync(const std::string& name)
{
	// ���[�h�p�����[�^���ҋ@���łȂ��ꍇ�A
	if (loadParam.load() != LoadParameter::None)
		return;

	// �V�[�������݂��邩���ׂ�
	auto it = GetRegistry().find(name);

	// ���݂��Ȃ��ꍇ�A���̂܂܏I��
	if (it == GetRegistry().end())
		return;

	//
	// �����܂ł�����A�V�[�����[�h�m��
	//

	// ���[�h�p�����[�^�����[�h���ɍX�V
	loadParam.store(LoadParameter::Loading);

	//! ���[�h�p�̃X���b�h�ɒl�n�����邽�߂̃R�s�[
	std::string sceneName = name;

	// �V�[�������݂���ꍇ�A���[�h�p�̃X���b�h���쐬���A
	// �񓯊��ŃV�[�������[�h���� 
	loadThread = std::thread([sceneName]()
		{
			// loadScene�̃A�N�Z�X�ɔr������
			std::lock_guard<std::mutex> lock(loadMutex);
			// �V�[���̃C���X�^���X�𐶐�
			loadScene = GetRegistry().find(sceneName)->second();
			// ���[�h�p�����[�^�������ɍX�V
			loadParam.store(LoadParameter::complete);
		});
}
