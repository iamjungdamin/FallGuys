#pragma once
#include "GameObject.h"

enum TYPE {	// 충돌 시 효과
	SHAKE,
	TRANSLATE,
	ROTATE,
	SCALE
};

static int FloorCount = 0;

class CFloorObject : public CGameObject
{
private:
	int index;
	int type;

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
	void Delete();
};

