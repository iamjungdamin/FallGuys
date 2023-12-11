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
	index = FloorCount;
	type = rand() % 4;	// enum TYPE
	isDeleted = false;

	++FloorCount;

	m_pos = { index % 5 * 2.f, -1.5f, index / 5 * -2.f};
	scale = { 3.f, 0.1f, 3.f };
	rotateY = 0.f;
}

void CFloorObject::Update(float ElapsedTime)
{
	if (isInitialized) {
		glm::mat4 TransformMatrix = glm::mat4(1.f);
		TransformMatrix = glm::rotate(TransformMatrix, glm::radians(rotateY), glm::vec3(0.f, 1.f, 0.f));
		TransformMatrix = glm::translate(TransformMatrix, m_pos);
		TransformMatrix = glm::scale(TransformMatrix, scale);
		modelMat = TransformMatrix;

		CGameObject::Update(ElapsedTime);
	}
	
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

void CFloorObject::Drop()
{
	if (type == TYPE::SHAKE) {
	
	}
	else if (type == TYPE::TRANSLATE) {

	}
	else if (type == TYPE::ROTATE) {
	
	}
	else if (type == TYPE::SCALE) {
	
	}
}

int CFloorObject::GetIndex() const
{
	return index;
}

bool CFloorObject::GetIsDeleted() const
{
	return isDeleted;
}
