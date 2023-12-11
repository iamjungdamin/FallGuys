#pragma once
#include "GameObject.h"

namespace TYPE {
	enum TYPE {	// �浹 �� ȿ��
		IDLE,	// ���浹 ��

		// ���� �浹 ��
		SHAKE,
		TRANSLATE,
		ROTATE,
		ROTATE2,
		SCALE
	};
}

static int FloorCount = 0;

class CFloorObject : public CGameObject
{
private:
	int index;
	int type;
	bool isDeleted;

	glm::vec3 scale = { 1.f, 1.f, 1.f };
	float rotateY;

public:
	CFloorObject();
	virtual ~CFloorObject();

	virtual void Initialize() override;
	virtual void Update(float ElapsedTime) override;
	virtual void FixedUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	void Drop();
	int GetIndex() const;
	bool GetIsDeleted() const;
};

