#pragma once

#include "GameObject.h"


class CMap
{

	CGameObject* map;
	
	glm::vec3 m_pos;
	glm::vec3 m_move;
	

	int state;


public:
	CMap();
	~CMap();



	void Render();
	void Update(float ElapsedTime);


	void SetShader(GLuint shader);
	void SetVao_map(GLuint vao, int vertexCount);
	

	void SetCameraMat(glm::mat4 cameraMat);
	void SetProjectMat(glm::mat4 projectMat);
	void SetCameraPos(glm::vec3 cameraPos);
	void SetLightPos(glm::vec3 lightPos);
	void SetLightColor(glm::vec3 lightColor);

	void SetPos(float x);


	
};

