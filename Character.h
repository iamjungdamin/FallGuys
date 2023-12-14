#pragma once

#include "GameObject.h"
class CFloorObject;
class CMap;
class CDoorObject;
// ��ü ����
enum STATE { IDLE, LEFT, RIGHT, FRONT, BACK,JUMP };

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
	glm::vec3 prevMove;
	float m_rot;
	glm::mat4 final_tr, final_rot; // ������ �̵�, ������ ȸ��
	float gravity = 5.f; // �߷�
	float speed = 0.01f; // �ӵ�
	float jump_speed = 15.f;
	float animationTime;
	float min_y; // �ٴ�
	bool isInGround = true;

	// scene에서 전달받은 카메라 정보
	glm::vec3 RotatedCameraFront;
	glm::vec3 RotatedCameraRight;

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
	bool isJumpKeyPressed;

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


	void SetCameraMat(glm::mat4 cameraMat, glm::vec3 frontVec, glm::vec3 rightVec);
	void SetProjectMat(glm::mat4 projectMat);
	void SetCameraPos(glm::vec3 cameraPos);
	void SetLightPos(glm::vec3 lightPos);
	void SetLightColor(glm::vec3 lightColor);

	void SetPos(float x);
	glm::vec3 GetPos() const;
	glm::vec3 GetBBSize() const;
	bool IsCollided(int index, CGameObject* Obj);
	bool IsCollided(CDoorObject* D);
	bool IsCollided(CFloorObject* F);


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
	void SetJumpKeyPressed(bool a);
};

