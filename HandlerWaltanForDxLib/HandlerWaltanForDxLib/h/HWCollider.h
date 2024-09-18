#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		�����蔻��̏���ێ�����R���|�[�l���g�̒�`
*/


/**
 * @enum	ColliderType
 * @brief	�R���C�_�[�̎��
 */
enum class ColliderType
{
	//! ������(0)
	Box,
	//! ����(1)
	Sphere,
	//! �J�v�Z���^(2)
	Capsule,
};


/**
 * @class	HWCollider
 * @brief	�����蔻��̏���ێ�����R���C�_�[�̊��R���|�[�l���g
 */
class HWCollider : public HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�R���C�_�[��`�悷�邩
	 * @History		24/09/15 �쐬(Suzuki N)
	 */
	bool isVisualization;

	/**
	 * @brief		�R���C�_�[���g���K�[��
	 * @History		24/09/15 �쐬(Suzuki N)
	 */
	bool isTrigger;

	/**
	 * @brief		�R���C�_�[�̒��S(gameObject��position�Ƃ̑��΋���)
	 * @History		24/09/15 �쐬(Suzuki N)
	 */
	VECTOR center;

	/**
	 * @brief		�R���C�_�[�̒��S(���[���h�̌��_�Ƃ̐�΋���)
	 * @History		24/09/15 �쐬(Suzuki N)
	 */
	VECTOR worldPosition;

protected:

	/**
	 * @brief		�R���C�_�[�̎��
	 * @History		24/09/15 �쐬(Suzuki N)
	 */
	ColliderType colliderType;

	/**
	 * @brief		�Փ˒��̃R���C�_�[
	 * @History		24/09/15 �쐬(Suzuki N)
	 */
	std::vector<HWCollider*> CollidersInCollision;


	/*     ���\�b�h     */

public:

	/**
	 * @brief		�R���C�_�[�^�C�v���擾����
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	const ColliderType GetColliderType() { return colliderType; }

	/**
	 * @brief		�Փ˒��̃R���C�_�[����S�Ď擾����
	 * @author		Suzuki N
	 * @date		24/09/18
	 */
	const std::vector<HWCollider*> GetCollidersInCollision() { return CollidersInCollision; }

	/**
	 * @brief		HWCollider�̃f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	virtual ~HWCollider() {}

protected:

	/**
	 * @brief		HWCollider�̃R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	HWCollider();

	/**
	 * @brief		�R���C�_�[��`�悷��
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	virtual void DrawCollider(){}

	/**
	 * @brief		�R���C�_�[�̍��W���Z�b�g����
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	virtual void SetCollider() {}

#pragma region �I�[�o�[���C�h���\�b�h

#pragma endregion
};