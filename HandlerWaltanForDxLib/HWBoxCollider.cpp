#include "h/HWBoxCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWBoxCollider�̎����t�@�C��
*/


#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h


HWBoxCollider::HWBoxCollider()
{
	colliderType = ColliderType::Box;
	size = VGet(50.f, 50.f, 50.f);
}

HWBoxCollider::HWBoxCollider(const VECTOR& _size) : size(_size)
{
	colliderType = ColliderType::Box;
}

HWBoxCollider::HWBoxCollider(const float& _sizeX, const float& _sizeY, const float& _sizeZ) : size(VGet(_sizeX, _sizeY, _sizeZ))
{
	colliderType = ColliderType::Box;
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


HWBoxCollider::~HWBoxCollider()
{
	CollisionWaltan::Instance().UnRegister(dynamic_cast<HWCollider*>(this));
}

void HWBoxCollider::DrawCollider()
{
	DrawLine3D(vertex[0][0], vertex[0][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][0], vertex[0][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][1], vertex[0][3], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][2], vertex[0][3], GetColor(0, 255, 0));
	
	DrawLine3D(vertex[0][0], vertex[1][0], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][1], vertex[1][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][2], vertex[1][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][3], vertex[1][3], GetColor(0, 255, 0));

	DrawLine3D(vertex[1][0], vertex[1][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][0], vertex[1][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][1], vertex[1][3], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][2], vertex[1][3], GetColor(0, 255, 0));

	DrawSphere3D(worldPosition, 5, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
}

void HWBoxCollider::SetCollider()
{
	// ���[�J�����W�ł̒��_���W�ݒ�
	vertex[0][0] = VGet(-size.x / 2, size.y / 2, -size.z / 2);
	vertex[0][1] = VGet(size.x / 2, size.y / 2, -size.z / 2);
	vertex[0][2] = VGet(-size.x / 2, size.y / 2, size.z / 2);
	vertex[0][3] = VGet(size.x / 2, size.y / 2, size.z / 2);
	vertex[1][0] = VGet(-size.x / 2, -size.y / 2, -size.z / 2);
	vertex[1][1] = VGet(size.x / 2, -size.y / 2, -size.z / 2);
	vertex[1][2] = VGet(-size.x / 2, -size.y / 2, size.z / 2);
	vertex[1][3] = VGet(size.x / 2, -size.y / 2, size.z / 2);

	// ��]�s��̍쐬�iZ -> Y -> X �̏��j
	MATRIX rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	mRotate = MMult(rotZ, MMult(rotY, rotX));

	//! ���s�ړ��p�̍s��(���_����̈ړ���)
	MATRIX trans = MGetTranslate(center);
	//! trans -> rotate �Ŋ|���邱�Ƃŉ�]��ɕ��s�ړ�����(���[�J���ȕ��s�ړ�)
	MATRIX mat = MMult(trans, mRotate);

	// �e���_�ɉ�]�s���K�p���A���[���h���W�֕ϊ�
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			// ���[�J�����W�ł̉�]
			vertex[i][j] = VTransform(vertex[i][j], mat);
			// ���[���h���W�ւ̕ϊ�
			vertex[i][j] = VAdd(vertex[i][j], transform->position);
		}
	}

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
	worldPosition = VTransform(VGet(0,0,0), mat);
	worldPosition = VAdd(worldPosition, transform->position);
}


void HWBoxCollider::Awake()
{
	center = VGet(0, 0, 0);

	// CollisionWaltan�ɓo�^
	CollisionWaltan::Instance().ColVec.push_back(dynamic_cast<HWCollider*>(this));
}

void HWBoxCollider::Update()
{
	// �R���C�_�[�̌`���\������
	SetCollider();

	// �f�o�b�O���[�h�A�������̓R���C�_�[�̉����t���O�������Ă���Ȃ�A�R���C�_�[��`�悷��
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}

void HWBoxCollider::OnCollisionEnter(HWCollider& _collider)
{
}


#pragma endregion

