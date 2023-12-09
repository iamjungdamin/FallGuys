#include "FloorObject.h"

CFloorObject::CFloorObject() : CGameObject()
{
	Initialize();
}

CFloorObject::~CFloorObject()
{
	Release();
}

void CFloorObject::Initialize()
{
	type = 0;
}

void CFloorObject::Update(float ElapsedTime)
{
	CGameObject::Update(ElapsedTime);
}

void CFloorObject::FixedUpdate()
{
	CGameObject::FixedUpdate();
}

void CFloorObject::Render()
{
	CGameObject::Render();
}

void CFloorObject::Release()
{
	CGameObject::Release();
}
