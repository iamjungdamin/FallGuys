#include "DoorObject.h"
#include <iostream>
#include <cstdlib>

CDoorObject::CDoorObject()
{
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++)
		{
			Door[i][j] = new CGameObject;
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
	
	for (int i = 0; i < 25; i++)
	{

		for (int j = 0; j < 2; j++) {
			printf("[%d][%d] : x : %lf, y: %lf, z:%lf\n", i, j , m_pos[i][j].x, m_pos[i][j].y, m_pos[i][j].z);
		}
	}

	std::srand(static_cast<unsigned int>(std::time(0)));

	


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



	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 2; j++) {
			glm::mat4 final_tr = glm::translate(glm::mat4(1.f), m_pos[i][j]);
			Door[i][j]->SetModelMat(final_tr);
			Door[i][j]->Update(ElapsedTime);
		}
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

