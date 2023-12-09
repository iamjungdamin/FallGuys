#pragma once
#include "GameObject.h"

class CFloorObject : public CGameObject
{
private:
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

