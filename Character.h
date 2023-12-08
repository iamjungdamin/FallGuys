#pragma once

#include "GameObject.h"

// ��ü ����
enum STATE { IDLE, LEFT, RIGHT, FRONT, BACK };

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
	glm::vec3 m_move;
	float m_rot;
	glm::mat4 final_tr, final_rot; // ������ �̵�, ������ ȸ��
	float gravity = 9.8f; // �߷�
	float speed = 0.001f; // �ӵ�
	float animationTime;

	struct Running_Animation {
		float animationTime;
		float bodyRotationAngle;
		float armleftRotationAngle;
		float armleftTranslationOffset;
		float armrightRotationAngle;
		float armrightTranslationOffset;
		float legleftRotationAngle;
		float legleftTranslationOffset;
		float legrightRotationAngle;
		float legrightTranslationOffset;
		
	};

	struct IDLE_Animation {
		float animationTime;
		float bodyRotationAngle;
		float armleftRotationAngle;
		float armleftTranslationOffset;
		float armrightRotationAngle;
		float armrightTranslationOffset;
		float legleftRotationAngle;
		float legleftTranslationOffset;
		float legrightRotationAngle;
		float legrightTranslationOffset;
		float initialLeftArmRotationAngle;
		float initialRightArmRotationAngle;

	};

	IDLE_Animation idle_animation;
	Running_Animation running_animation;

	bool isLeftKeyPressed;
	bool isRightKeyPressed;
	bool isFrontKeyPressed;
	bool isBackKeyPressed;


	int state;
	bool isJumping;

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
	void SetState(int a);
	void State_Idle();
	void State_Running();
	void State_Jumping();
	void CheckState();

	// Ű���� ���� ���� �Լ�
	void SetRightKeyPressed(bool a);
	void SetLeftKeyPressed(bool a);
	void SetBackKeyPressed(bool a);
	void SetFrontKeyPressed(bool a);

};

