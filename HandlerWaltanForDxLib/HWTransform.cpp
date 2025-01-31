#include"h/HWTransform.h"


/**
* @author   NZ
* @date     24/07/29
* @note		MyTransform�̎����t�@�C��
*/


#pragma region private���\�b�h


void HWTransform::SetMatrix()
{
	MATRIX pos, rot, scl;

	// ���s�ړ�
	pos = MGetTranslate(position);
	// ��]
	MATRIX rotX = MGetRotX((float)Deg2Rad(rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(rotate.z));
	// �O���[�o����]
	rot = MMult(rotZ, MMult(rotY, rotX));
	// ���[�J����]
	//rot = MMult(rotX, MMult(rotY, rotZ));

	// �g�k
	scl = MGetScale(scale);

	// �Ō�ɍs����������킹��
	globalMat = MMult(scl, MMult(rot, pos));


	// ���ʃx�N�g�����X�V
	forward = VTransform(VGet(0, 0, -1), rot);
	// �x�N�g���𐳋K��
	forward = VNorm(forward);
}


#pragma endregion

#pragma region public���\�b�h


void HWTransform::LookAt(const VECTOR& _target)
{
	// ENEMY -> Player �ւ̕����x�N�g�����v�Z
	VECTOR dir = VNorm(VSub(_target, position));

	// ���ς��g���ăx�N�g���Ԃ̊p�x���v�Z
	float dot = VDot(forward, dir);

	// acosf ���g���O�ɃN���b�s���O�i�덷�΍�j
	if (dot < -1.0f) dot = -1.0f;
	if (dot > 1.0f) dot = 1.0f;

	// �Ȃ��p���v�Z
	float angle = acosf(dot);

	// �O�ς�p���ĉ�]�������߂�
	VECTOR axis = VCross(forward, dir);

	// �O�ς��[���x�N�g���łȂ������`�F�b�N�i�قړ��������̏ꍇ�A�O�ς̓[���ɂȂ�j
	if (VSize(axis) > 0.0001f) {
		axis = VNorm(axis);

		// ��]�ɓK�p
		rotate.x += (float)Rad2Deg(axis.x * angle);
		rotate.y += (float)Rad2Deg(axis.y * angle);
		rotate.z += (float)Rad2Deg(axis.z * angle);
	}
	else {
		// ��]���������ȏꍇ�A�������X�L�b�v�܂��͑�֏���
		// ��F�قړ��������Ɍ����Ă���̂ŁA��]�͕K�v�Ȃ�
	}
}

HWTransform::HWTransform() : position({ 0.0f, 0.0f, 0.0f }), rotate({ 0.0f, 0.0f, 0.0f }),
scale({ 1.0f, 1.0f, 1.0f }), localPosition({ 0.0f, 0.0f, 0.0f }), localRotate({ 0.0f, 0.0f, 0.0f }),
localScale({ 1.0f, 1.0f, 1.0f }), previousPosition(position)
{
	priority = 20;
	globalMat = MGetIdent();
}


#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


void HWTransform::Update()
{
	// position�𑀍삵���ꍇ�̈ړ��ʂ�velocity�ɑ���
	velocity = VAdd(velocity, VSub(position, previousPosition));

	// ���W�Ɉړ��x�N�g���𑫂�
	position = VAdd(previousPosition, velocity);

	// �e�I�u�W�F�N�g�̉e�����q�ɗ^����
	if (gameObject->isAffect)
	{
		// �e�I�u�W�F�N�g�����݂���ꍇ�A�e�̍s����q�ɓK�p
		if (gameObject->Parent() != nullptr)
		{
			// �e�̃O���[�o���s����擾
			MATRIX parentMatrix = gameObject->Parent()->transform->globalMat;

			// �q�̃��[�J���s��ɐe�̍s����|����
			globalMat = MMult(globalMat, parentMatrix);
		}
	}
	// �q�I�u�W�F�N�g�ɐe�̕ϊ���K�p
	if (gameObject->GetChildren().size() > 0)
		for (auto it = gameObject->GetChildren().begin(); it != gameObject->GetChildren().end(); ++it)
			if((*it)->isAffect)	(*it)->transform->velocity = VAdd((*it)->transform->velocity, velocity);

	// �ړ��x�N�g���̏�����
	velocity = VGet(0, 0, 0);
	// �OF�̍��W���X�V
	previousPosition = position;

	SetMatrix();
}


#pragma endregion