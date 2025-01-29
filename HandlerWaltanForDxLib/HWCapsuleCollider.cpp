#include "h/HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWCapsuleCollider�̎����t�@�C��
*/


#pragma region private���\�b�h


#pragma region �����o������

void HWCapsuleCollider::PushOut_Capsule_Box(HWCollider& other)
{
}

void HWCapsuleCollider::PushOut_Capsule_Capsule(HWCapsuleCollider& other)
{
}

void HWCapsuleCollider::PushOut_Capsule_Sphere(HWCollider& other)
{
}

#pragma endregion


#pragma endregion

#pragma region public���\�b�h


HWCapsuleCollider::HWCapsuleCollider()
{
	colliderType = ColliderType::Capsule;	
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


HWCapsuleCollider::~HWCapsuleCollider()
{
	CollisionWaltan::Instance().UnRegister(dynamic_cast<HWCollider*>(this));
}

void HWCapsuleCollider::DrawCollider()
{
	DrawCapsule3D(startPos, endPos, radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
}

void HWCapsuleCollider::SetCollider()
{
	startPos = VGet(0, 0, 0);
	endPos = VGet(0, height, 0);

	// ��]�s��̍쐬�iZ -> Y -> X �̏��j
	MATRIX rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	MATRIX mRotate = MMult(rotZ, MMult(rotY, rotX));

	//! ���s�ړ��p�̍s��(���_����̈ړ���)
	MATRIX trans = MGetTranslate(center);
	//! trans -> rotate �Ŋ|���邱�Ƃŉ�]��ɕ��s�ړ�����(���[�J���ȕ��s�ړ�)
	MATRIX mat = MMult(trans, mRotate);

	// ���[�J�����W�ł̉�]
	startPos = VTransform(startPos, mat);
	// ���[���h���W�ւ̕ϊ�
	startPos = VAdd(startPos, transform->position);
	// ���[�J�����W�ł̉�]
	endPos = VTransform(endPos, mat);
	// ���[���h���W�ւ̕ϊ�
	endPos = VAdd(endPos, transform->position);


	// ��]�s��̍쐬�iZ -> Y -> X �̏��j
	rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	MATRIX mRotate2 = MMult(rotX, MMult(rotY, rotZ));
	//! ���s�ړ��p�̍s��(���_����̈ړ���)
	trans = MGetTranslate(center);
	//! trans -> rotate �Ŋ|���邱�Ƃŉ�]��ɕ��s�ړ�����(���[�J���ȕ��s�ړ�)
	mat = MMult(trans, mRotate);
	// �R���C�_�[�̒��S���W���X�V
	worldPosition = VTransform(VGet(0, 0, 0), mat);
	worldPosition = VAdd(worldPosition, transform->position);
}


void HWCapsuleCollider::Awake()
{
	priority = -10;
	center = VGet(0, 0, 0);
	radius = 50.f;

	UsStartPos = VGet(0, 0, 0);
	UsEndPos = VGet(0, 0, 0);

	// �R���C�_�[�̌`���\������
	SetCollider();

	// CollisionWaltan�ɓo�^
	CollisionWaltan::Instance().ColVec.push_back(dynamic_cast<HWCollider*>(this));
}

void HWCapsuleCollider::Update()
{
	// �R���C�_�[�̎n�_���I�_��ݒ肵�Ă��Ȃ��ꍇ�͎����ŃL�����N�^�[�ɒǏ]����悤�ɂ���
	if ((UsStartPos.x == 0.f && UsStartPos.y == 0.f && UsStartPos.z == 0.f) &&
		(UsEndPos.x == 0.f && UsEndPos.y == 0.f && UsEndPos.z == 0.f))
		// �R���C�_�[�̌`���\������
		SetCollider();
	// �ǂ��炩���ݒ肳��Ă���ꍇ�͂��̂܂܏㏑��
	else
	{
		startPos = UsStartPos;
		endPos = UsEndPos;
	}

	// �f�o�b�O���[�h�A�������̓R���C�_�[�̉����t���O�������Ă���Ȃ�A�R���C�_�[��`�悷��
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}

void HWCapsuleCollider::OnCollisionEnter(HWCollider& _collider)
{
	//! �R���C�_�[���J�v�Z���ɃL���X�g
	switch (_collider.GetColliderType())
	{
	case ColliderType::Box:
		PushOut_Capsule_Box(static_cast<HWBoxCollider&>(_collider));
		break;

	case ColliderType::Capsule:
		PushOut_Capsule_Capsule(static_cast<HWCapsuleCollider&>(_collider));
		break;

	case ColliderType::Sphere:
		PushOut_Capsule_Sphere(static_cast<HWSphereCollider&>(_collider));
		break;
	}
}


#pragma endregion