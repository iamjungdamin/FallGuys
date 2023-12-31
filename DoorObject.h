#pragma once

#include "GameObject.h"

class CDoorObject
{
	CGameObject* Door[25][2];
	glm::vec3 m_pos[25][2];
	int m_type[25][2];
	float angle[25];
	glm::vec3 size[25];
public:
	CDoorObject();
	~CDoorObject();

	bool touch[25];

	void Render();
	void Update(float ElapsedTime);


	void SetShader(GLuint shader);
	void SetVao(GLuint vao, int vertexCount);

	void SetCameraMat(glm::mat4 cameraMat);
	void SetProjectMat(glm::mat4 projectMat);
	void SetCameraPos(glm::vec3 cameraPos);
	void SetLightPos(glm::vec3 lightPos);
	void SetLightColor(glm::vec3 lightColor);

	glm::vec3 GetPos(int i, int j);
	int GetType(int i, int j);




};

