#pragma once
#include "DxLib.h"
#include "Utilities.h"


/**
* @author   Suzuki N
* @date     24/06/17
* @note     ���ׂẴR���|�[�l���g�̊��N���X�̒�`�t�@�C��
*/


//HWComponent�N���X�������o�ϐ���HWGameObject�N���X���������邽�߂ɑO���錾
class HWGameObject;
class HWTransform;
class HWCollider;

/**
 * @class	HWComponent
 * @brief	�S�ẴR���|�[�l���g�̊��N���X
 */
class HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		���̃R���|�[�l���g���A�^�b�`����Ă���HWGameObject
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	HWGameObject* gameObject;

	/**
	 * @brief		HWGameObject�ɃA�^�b�`����Ă���HWTransform
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	HWTransform* transform;

	/**
	 * @brief		�����A�^�b�`�\�ȃR���|�[�l���g��
	 * @History		24/08/03 �쐬(Suzuki N)
	 */
	bool isMultiplePossession;

	/**
	 * @brief		�R���|�[�l���g�̃A�N�e�B�u
	 * @History		24/08/03 �쐬(Suzuki N)
	 */
	bool active;


private:

	/**
	 * @brief		�Փ˔������������ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void(HWCollider*)> OnCollisionEnterCallBack;

	/**
	 * @brief		�Փ˔��������Ă���ԂɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void(HWCollider*)> OnCollisionStayCallBack;

	/**
	 * @brief		�Փ˔��肪�����ꂽ���ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void(HWCollider*)> OnCollisionExitCallBack;

	/**
	 * @brief		�Փ˔������������ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void(HWCollider*)> OnTriggerEnterCallBack;

	/**
	 * @brief		�Փ˔��������Ă���ԂɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void(HWCollider*)> OnTriggerStayCallBack;

	/**
	 * @brief		�Փ˔��肪�����ꂽ���ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void(HWCollider*)> OnTriggerExitCallBack;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual ~HWComponent() {}

protected:

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	HWComponent();

#pragma region ���z�֐��Q

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Awake() {}


	/**
	 * @brief		�ŏ���Update���\�b�h�̒��O�ɓ���
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Start() {}


	/**
	 * @brief		���t���[���Ă΂�郁�\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Update() {}

#pragma region �R���W�����֌W

	/**
	 * @brief		�R���C�_�[�Փˎ��ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionEnter(HWCollider* _collider) {}


	/**
	 * @brief		�R���C�_�[�Փ˒��ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionStay(HWCollider* _collider) {}


	/**
	 * @brief		�R���C�_�[�Փ˂��������ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionExit(HWCollider* _collider) {}

	/**
	 * @brief		�R���C�_�[�Փˎ��ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnTriggerEnter(HWCollider* _collider) {}


	/**
	 * @brief		�R���C�_�[�Փ˒��ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnTriggerStay(HWCollider* _collider) {}


	/**
	 * @brief		�R���C�_�[�Փ˂��������ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnTriggerExit(HWCollider* _collider) {}

#pragma endregion


#pragma endregion

#pragma region �o�^���ꂽ�R�[���o�b�N�֐����Ăԃ��\�b�h�Q

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionEnterHandler(HWCollider* _collider);

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionStayHandler(HWCollider* _collider);

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionExsitHandler(HWCollider* _collider);

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	*/
	void OnTriggerEnterHandler(HWCollider* _collider);

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnTriggerStayHandler(HWCollider* _collider);

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnTriggerExsitHandler(HWCollider* _collider);

#pragma endregion
};
