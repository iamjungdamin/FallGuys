#include "FloorObject.h"

CFloorObject::CFloorObject()
{
	Initialize();
}

CFloorObject::~CFloorObject()
{
	Release();
}

void CFloorObject::SetShader(GLuint shader)
{
	for (int i = 0; i < num; ++i) {
		Floor[i]->SetShader(shader);
	}
}

void CFloorObject::SetVao(GLuint vao, int vertexCount)
{
	for (int i = 0; i < num; ++i) {
		Floor[i]->SetVao(vao, vertexCount);
	}
}

void CFloorObject::Initialize()
{
	for (int i = 0; i < num; ++i) {
		Floor[i] = new CGameObject;

		type[i] = TYPE::IDLE;
		isDeleted[i] = false;

		m_pos[i] = {i % 5 * 2.f, 1.5f, i / 5 * -2.f - 10.f};
		Floor[i]->SetPos(m_pos[i]);
		scale[i] = {3.f, 0.1f, 3.f};
		Floor[i]->SetScale(scale[i]);
		rotateY[i] = 0.f;
	}
}

void CFloorObject::Update(float ElapsedTime)
{
	for (int i = 0; i < num; ++i) {
		glm::mat4 TransformMatrix = glm::mat4(1.f);

		if (isDeleted[i] == false) {

			if (type[i] == TYPE::SHAKE) {
			}
			else if (type[i] == TYPE::TRANSLATE) {
				m_pos[i].y -= 0.001f;
				if (m_pos[i].y <= -1.5f - 1.f) {
					//isDeleted = true;
				}
			}
			else if (type[i] == TYPE::ROTATE) {
				rotateY[i] += 0.5f;
				if (rotateY[i] > 180.f) {
					type[i] = TYPE::ROTATE2;
				}
			}
			else if (type[i] == TYPE::ROTATE2) {
				rotateY[i] += 0.5f;
				m_pos[i].y -= 0.001f;
				if (m_pos[i].y <= -1.5f - 1.f) {
					//isDeleted = true;
				}
			}
			else if (type[i] == TYPE::SCALE) {
				scale[i].x -= 0.001f;
				scale[i].z -= 0.001f;
				if (scale[i].x <= 0.f || scale[i].z <= 0.f) {
					isDeleted[i] = true;
				}
			}

			TransformMatrix = glm::scale(TransformMatrix, scale[i]);

			TransformMatrix = glm::translate(TransformMatrix, m_pos[i]);
			TransformMatrix = glm::rotate(TransformMatrix, glm::radians(rotateY[i]), glm::vec3(0.f, 1.f, 0.f));

			Floor[i]->SetModelMat(TransformMatrix);
		}

	}
	
}

void CFloorObject::SetCameraMat(glm::mat4 cameraMat)
{
	for (int i = 0; i < num; ++i) {
		Floor[i]->SetCameraMat(cameraMat);
	}
}

void CFloorObject::SetProjectMat(glm::mat4 projectMat)
{

	for (int i = 0; i < num; ++i) {
		Floor[i]->SetProjectMat(projectMat);
	}
}

void CFloorObject::SetCameraPos(glm::vec3 cameraPos)
{
	for (int i = 0; i < num; ++i) {
		Floor[i]->SetCameraPos(cameraPos);
	}
}

void CFloorObject::SetLightPos(glm::vec3 lightPos)
{
	for (int i = 0; i < num; ++i) {
		Floor[i]->SetLightPos(lightPos);
	}
}

void CFloorObject::SetLightColor(glm::vec3 lightColor)
{
	for (int i = 0; i < num; ++i) {
		Floor[i]->SetLightColor(lightColor);
	}
}

void CFloorObject::FixedUpdate()
{
	//CGameObject::FixedUpdate();
}

void CFloorObject::Render()
{
	for (int i = 0; i < 25; ++i) {

		Floor[i]->Render();
	}
}

void CFloorObject::Release()
{
	//CGameObject::Release();
	delete[] Floor;
}

void CFloorObject::Drop(int i)
{
	if (type[i] == TYPE::IDLE) {
		int r = rand() % 4;

		if (r == 0) {
			type[i] = TYPE::ROTATE;
		}
		else if (r == 1) {
			type[i] = TYPE::TRANSLATE;
		}
		else if (r == 2) {
			type[i] = TYPE::ROTATE;
		}
		else if (r == 3) {
			type[i] = TYPE::SCALE;
		}
	}
}

glm::vec3 CFloorObject::GetPos(int i) const
{
	return m_pos[i];
}

glm::vec3 CFloorObject::GetBBSize() const
{
	return { 1.f, 0.5f, 1.f };
}

bool CFloorObject::GetIsDeleted(int i) const
{
	return isDeleted[i];
}
