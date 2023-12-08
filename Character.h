#pragma once

#include "GameObject.h"

class CCharacter
{

	CGameObject* face;
	CGameObject* body;
	CGameObject* left_arm;
	CGameObject* right_arm;
	CGameObject* left_leg;
	CGameObject* right_leg;
	CGameObject* eyes;
	glm::vec3 m_pos;
	glm::mat4 final_tr;
	float  animationTime;

	float armRotationAngle_RUNNING;
	float bodyRotationAngle_RUNNING;
	float armTranslationOffset_RUNNING;
	float legleftRotationAngle_RUNNING;
	float legleftTranslationOffset_RUNNING;
	float legrightRotationAngle_RUNNING;
	float legrightTranslationOffset_RUNNING;

	int state;
public:
	CCharacter();
	~CCharacter();



	void Render();
	void Update(float ElapsedTime);


	void SetShader(GLuint shader);
	void SetVao_face(GLuint vao, int vertexCount);
	void SetVao_body(GLuint vao, int vertexCount);
	void SetVao_left_leg(GLuint vao, int vertexCount);
	void SetVao_right_leg(GLuint vao, int vertexCount);
	void SetVao_eyes(GLuint vao, int vertexCount);
	void SetVao_left_arm(GLuint vao, int vertexCount);
	void SetVao_right_arm(GLuint vao, int vertexCount);


	void SetCameraMat(glm::mat4 cameraMat);
	void SetProjectMat(glm::mat4 projectMat);
	void SetCameraPos(glm::vec3 cameraPos);
	void SetLightPos(glm::vec3 lightPos);
	void SetLightColor(glm::vec3 lightColor);

	void SetPos(float x);

	
	// ĳ���� ���� ���� �Լ�
	void State(int a);
	void State_Idle();
	void State_Running();
	void State_Jumping();
	void CheckState();
	


};

