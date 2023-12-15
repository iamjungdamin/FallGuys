#include "DoorObject.h"
#include <iostream>
#include <cstdlib>

namespace Door_TYPE {
	enum TYPE {	// 충돌 시 효과
		IDLE,	// 미충돌 시
		TRANSLATE,
		ROTATE,
		SCALE
	};
}

CDoorObject::CDoorObject()
{
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++)
		{
			Door[i][j] = new CGameObject;
			m_type[i][j] = Door_TYPE::IDLE;
		}
	}

	float a = 0;

	for (int i = 0; i < 25; i++)
	{
		if (i == 5 || i == 10 || i == 15|| i==20) {
			a -= 70;
		}
		for (int j = 0; j < 2; j++) {
			m_pos[i][j] = { 0.0f,0.f,a };
		
		}
	}

	for (int i = 0; i < 25; i++)
	{
		if (i == 5 || i == 10 || i == 15 || i == 20) {
			a -= 70;
		}
		for (int j = 0; j < 1; j++) {
			if (i % 5 == 0) {
				m_pos[i][j].x = -46.f;
				m_pos[i][j + 1].x = -38.f;
			}
			if (i % 5 == 1)
			{
				m_pos[i][j].x = -24.f;
				m_pos[i][j + 1].x = -16.f;
			}

			if (i % 5 == 2)
			{
				m_pos[i][j].x = -4.f;
				m_pos[i][j + 1].x = 4.f;
			}
			if (i % 5 == 3)
			{
				m_pos[i][j].x = 16.f;
				m_pos[i][j + 1].x = 24.f;
			}
			if (i % 5 == 4)
			{
				m_pos[i][j].x = 36.f;
				m_pos[i][j + 1].x = 44.f;
			}
		}
	}
	
	
	std::srand(static_cast<unsigned int>(std::time(0)));

	for (int k = 0; k < 5; k++) {
		int t = rand() % 5;
		for (int i = 0 ; i+k*5< 5+k*5; i++)
		{
			if (i == t) {
			
				m_type[i + k * 5][0] = 1+rand() % 3;
				m_type[i + k * 5][1] = m_type[i + k * 5][0];
			}
		}

	}
	
	for (int i = 0; i < 25; i++)
	{

		size[i] = { 1.f,1.f,1.f };
	}
	
	for (int i = 0; i < 25; i++)
	{
		angle[i] = 0;
	
	}
	

}

CDoorObject::~CDoorObject()
{

}

void CDoorObject::Render()
{
	glm::mat4 final_tr;
	glm::mat4 sc;
	glm::mat4 rot;

	

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->Render();

		}
	}
	
	
	
}

void CDoorObject::Update(float ElapsedTime)
{

	glm::mat4 tr;
	glm::mat4 sc;
	glm::mat4 rot;
	glm::mat4 final_tr;
	glm::mat4 scaleMat;

	for (int i = 0; i < 25; i++) {
		
			if (touch[i] == true)
			{
				/*if (m_type[i][j] == Door_TYPE::ROTATE) {
					angle[i] += 0.01f;
					glm::mat4 final_tr = glm::translate(glm::mat4(1.f), m_pos[i][j]);
					glm::mat4 rot_L = glm::rotate(glm::mat4(1.f), glm::radians(angle[i]), glm::vec3(0.f, -1.f, 0.f));
					glm::mat4 rot_R = glm::rotate(glm::mat4(1.f), glm::radians(angle[i]), glm::vec3(0.f, 1.f, 0.f));
					Door[i][0]->SetModelMat(final_tr * rot_L);
					Door[i][1]->SetModelMat(final_tr * rot_R);
				}*/
				if (m_type[i][0] == Door_TYPE::TRANSLATE) {
					m_pos[i][0].y += 0.01f;
					m_pos[i][1].y += 0.01f;
					final_tr = glm::translate(glm::mat4(1.f), m_pos[i][0]);
					Door[i][0]->SetModelMat(final_tr);
					final_tr = glm::translate(glm::mat4(1.f), m_pos[i][1]);
					Door[i][1]->SetModelMat(final_tr);
				}
				else if (m_type[i][0] == Door_TYPE::ROTATE) {
					angle[i] += 0.1f;
					if (angle[i] >= 90)
					{
						angle[i] = 90;
					}
					glm::mat4 rot_L = glm::rotate(glm::mat4(1.f), glm::radians(angle[i]), glm::vec3(0.f, 1.f, 0.f));
					glm::mat4 rot_R = glm::rotate(glm::mat4(1.f), glm::radians(angle[i]), glm::vec3(0.f, -1.f, 0.f));
					final_tr = glm::translate(glm::mat4(1.f), m_pos[i][0]);
					Door[i][0]->SetModelMat(final_tr * rot_L);
					final_tr = glm::translate(glm::mat4(1.f), m_pos[i][1]);
					Door[i][1]->SetModelMat(final_tr * rot_R);
				}
				else if (m_type[i][0] == Door_TYPE::SCALE) {
					size[i] -= 0.1f;
					scaleMat = glm::scale(glm::mat4(1.f), size[i]);
					final_tr = glm::translate(glm::mat4(1.f), m_pos[i][0]);
					Door[i][0]->SetModelMat(final_tr* scaleMat);
					final_tr = glm::translate(glm::mat4(1.f), m_pos[i][1]);
					Door[i][1]->SetModelMat(final_tr* scaleMat);
				}
			}
			else {
				final_tr = glm::translate(glm::mat4(1.f), m_pos[i][1]);
				Door[i][1]->SetModelMat(final_tr);
				final_tr = glm::translate(glm::mat4(1.f), m_pos[i][0]);
				Door[i][0]->SetModelMat(final_tr);

			}
			
			Door[i][0]->Update(ElapsedTime);
			Door[i][1]->Update(ElapsedTime);
	}
	

}
		




void CDoorObject::SetShader(GLuint shader)
{

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->SetShader(shader);
		}
	}
	
}

void CDoorObject::SetVao(GLuint vao, int vertexCount)
{

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->SetVao(vao, vertexCount);
		}
	}

	
}




void CDoorObject::SetCameraMat(glm::mat4 cameraMat)
{

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->SetCameraMat(cameraMat);
		}
	}

	//Cube[0][0]->SetCameraMat(cameraMat);
	//Cube[0][1]->SetCameraMat(cameraMat);
}

void CDoorObject::SetProjectMat(glm::mat4 projectMat)
{

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->SetProjectMat(projectMat);
		}
	}
	
}

void CDoorObject::SetCameraPos(glm::vec3 cameraPos)
{
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->SetCameraPos(cameraPos);
		}
	}



}

void CDoorObject::SetLightPos(glm::vec3 lightPos)
{
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->SetLightPos(lightPos);
		}
	}

}

void CDoorObject::SetLightColor(glm::vec3 lightColor)
{

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			Door[i][j]->SetLightColor(lightColor);
		}
	}
	
}

glm::vec3 CDoorObject::GetPos(int i, int j)
{
	return m_pos[i][j];
}

int CDoorObject::GetType(int i, int j)
{
	return m_type[i][j];
}

