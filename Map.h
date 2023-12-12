#pragma once
#pragma once
#include "GameObject.h"


class CMap : public CGameObject
{
private:


public:
	CMap();
	virtual ~CMap();

	virtual void Initialize() override;
	virtual void Update(float ElapsedTime) override;
	virtual void FixedUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	glm::vec3 GetPos() const;
	glm::vec3 GetBBSize() const;

};

