#pragma once
#include "GameObject.h"

enum TYPE {	// �浹 �� ȿ��
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
	float type;

public:
	CFloorObject();
	virtual ~CFloorObject();

	virtual void Initialize() override;
	virtual void Update(float ElapsedTime) override;
	virtual void FixedUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

