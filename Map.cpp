#include "Map.h"
#include <iostream>

CMap::CMap()
{
	map = new CGameObject;

}

CMap::~CMap()
{

}

void CMap::Render()
{
	map->Render();

}

void CMap::Update(float ElapsedTime)
{

	map->Update(ElapsedTime);

}


void CMap::SetShader(GLuint shader)
{
	map->SetShader(shader);
	
}

void CMap::SetVao_map(GLuint vao, int vertexCount)
{
	map->SetVao(vao, vertexCount);
}



void CMap::SetCameraMat(glm::mat4 cameraMat)
{
	map->SetCameraMat(cameraMat);
}

void CMap::SetProjectMat(glm::mat4 projectMat)
{
	map->SetProjectMat(projectMat);
	
}

void CMap::SetCameraPos(glm::vec3 cameraPos)
{
	map->SetCameraPos(cameraPos);
}

void CMap::SetLightPos(glm::vec3 lightPos)
{
	map->SetLightPos(lightPos);
}

void CMap::SetLightColor(glm::vec3 lightColor)
{
	map->SetLightColor(lightColor);
	
}

void CMap::SetPos(float x)
{
	m_pos.x += x;
}

