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
	type = TYPE::IDLE;
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

		if (isDeleted == false) {
			if (type == TYPE::SHAKE) {
			}
			else if (type == TYPE::TRANSLATE) {
				m_pos.y -= 0.001f;
				if (m_pos.y <= -1.5f - 1.f) {
					//isDeleted = true;
				}
			}
			else if (type == TYPE::ROTATE) {
				rotateY += 0.1f;
				if (rotateY > 180.f) {
					type = TYPE::ROTATE2;
				}
			}
			else if (type == TYPE::ROTATE2) {
				rotateY += 0.1f;
				m_pos.y -= 0.001f;
				if (m_pos.y <= -1.5f - 1.f) {
					//isDeleted = true;
				}
			}
			else if (type == TYPE::SCALE) {
				scale.x -= 0.001f;
				scale.z -= 0.001f;
				if (scale.x <= 0.f || scale.z <= 0.f) {
					isDeleted = true;
				}
			}
		}

		TransformMatrix = glm::translate(TransformMatrix, m_pos);
		TransformMatrix = glm::rotate(TransformMatrix, glm::radians(rotateY), glm::vec3(0.f, 1.f, 0.f));
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
	if (type == TYPE::IDLE) {
		int r = rand() % 4;

		if (r == 0) {
			type = TYPE::SHAKE;
		}
		else if (r == 1) {
			type = TYPE::TRANSLATE;
		}
		else if (r == 2) {
			type = TYPE::ROTATE;
		}
		else if (r == 3) {
			type = TYPE::SCALE;
		}
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
