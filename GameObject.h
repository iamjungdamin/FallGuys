#pragma once
#include "stdafx.h"

class CGameObject
{
protected:
	GLuint m_shader;
	GLuint m_vao;

	int m_vertexCount;

	bool isInitialized;

	glm::vec3 m_pos;

	glm::mat4 modelMat;
	glm::mat4 cameraMat;
	glm::mat4 projectMat;
	
	glm::mat4 scaleMat;

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void SetShader(GLuint shader) final;
	virtual void SetVao(GLuint vao, int vertexCount) final;

	virtual void Initialize();				//생성될 때 할 일
	virtual void Update(float ElapsedTime);					//타이머에서 할 일
	virtual void FixedUpdate();				//충돌처리 등
	virtual void Render();					//드로우
	virtual void Release();					//소멸될 때 할 일

	void SetCameraMat(glm::mat4 camera);
	void SetProjectMat(glm::mat4 project);

	void SetCameraPos(glm::vec3 cameraPos);
	void SetLightPos(glm::vec3 lightPos);
	void SetLightColor(glm::vec3 lightColor);

	void SetPos(float x, float y, float z);
	void SetPos(glm::vec3 pos);

	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 scale);

	void SetModelMat(glm::mat4 modelMat);
};

