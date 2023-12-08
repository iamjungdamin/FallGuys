#include "Character.h"
#include <iostream>

CCharacter::CCharacter()
{
	face = new CGameObject;
	body = new CGameObject;
	left_arm = new CGameObject;
	right_arm = new CGameObject;
	left_leg = new CGameObject;
	right_leg = new CGameObject;
	eyes = new CGameObject;
	final_tr = glm::translate(glm::mat4(1.f), m_pos);
	
	state = STATE::IDLE;
	isJumping = false;

	animationTime = 0.0f;

}

CCharacter::~CCharacter()
{

}

void CCharacter::Render()
{
	face->Render();
	body->Render();
	left_arm->Render();
	right_arm->Render();
	left_leg->Render();
	right_leg->Render();
	eyes->Render();

}

void CCharacter::Update(float ElapsedTime)
{
	final_tr = glm::translate(glm::mat4(1.f), m_pos);
	glm::mat4 tr; 
	glm::mat4 sc;
	glm::mat4 rot;

	// 처음 초기값
	glm:: mat4 first_rot = glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
	

	
	//여기까지 위치 초기값

	//상태 따라 행동하는 함수
	CheckState();

	//face->SetModelMat(first_rot);
	//body->SetModelMat(first_rot);
	//left_arm->SetModelMat(first_rot);
	//right_arm->SetModelMat(first_rot);
	//left_leg->SetModelMat(first_rot);
	//right_leg->SetModelMat(first_rot);
	//eyes->SetModelMat(first_rot);
	

	face->Update(ElapsedTime);
	body->Update(ElapsedTime);
	left_arm->Update(ElapsedTime);
	right_arm->Update(ElapsedTime);
	left_leg->Update(ElapsedTime);
	right_leg->Update(ElapsedTime);
	eyes->Update(ElapsedTime);

}


void CCharacter::SetShader(GLuint shader)
{
	face->SetShader(shader);
	body->SetShader(shader);
	left_arm->SetShader(shader);
	right_arm->SetShader(shader);
	left_leg->SetShader(shader);
	right_leg->SetShader(shader);
	eyes->SetShader(shader);

}

void CCharacter::SetVao_face(GLuint vao, int vertexCount)
{
	face->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_body(GLuint vao, int vertexCount)
{
	body->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_left_arm(GLuint vao, int vertexCount)
{
	left_arm->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_right_arm(GLuint vao, int vertexCount)
{
	right_arm->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_left_leg(GLuint vao, int vertexCount)
{
	left_leg->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_right_leg(GLuint vao, int vertexCount)
{
	right_leg->SetVao(vao, vertexCount);
}
void CCharacter::SetVao_eyes(GLuint vao, int vertexCount)
{
	eyes->SetVao(vao, vertexCount);
}



void CCharacter::SetCameraMat(glm::mat4 cameraMat)
{
	face->SetCameraMat(cameraMat);
	body->SetCameraMat(cameraMat);
	left_arm->SetCameraMat(cameraMat);
	right_arm->SetCameraMat(cameraMat);
	left_leg->SetCameraMat(cameraMat);
	right_leg->SetCameraMat(cameraMat);
	eyes->SetCameraMat(cameraMat);

}

void CCharacter::SetProjectMat(glm::mat4 projectMat)
{
	face->SetProjectMat(projectMat);
	body->SetProjectMat(projectMat);
	left_arm->SetProjectMat(projectMat);
	right_arm->SetProjectMat(projectMat);
	left_leg->SetProjectMat(projectMat);
	right_leg->SetProjectMat(projectMat);
	eyes->SetProjectMat(projectMat);
}

void CCharacter::SetCameraPos(glm::vec3 cameraPos)
{
	face->SetCameraPos(cameraPos);
	body->SetCameraPos(cameraPos);
	left_arm->SetCameraPos(cameraPos);
	right_arm->SetCameraPos(cameraPos);
	left_leg->SetCameraPos(cameraPos);
	right_leg->SetCameraPos(cameraPos);
	eyes->SetCameraPos(cameraPos);
}

void CCharacter::SetLightPos(glm::vec3 lightPos)
{
	face->SetLightPos(lightPos);
	body->SetLightPos(lightPos);
	left_arm->SetLightPos(lightPos);
	right_arm->SetLightPos(lightPos);
	left_leg->SetLightPos(lightPos);
	right_leg->SetLightPos(lightPos);
	eyes ->SetLightPos(lightPos);
}

void CCharacter::SetLightColor(glm::vec3 lightColor)
{
	face->SetLightColor(lightColor);
	body->SetLightColor(lightColor);
	left_arm->SetLightColor(lightColor);
	right_arm->SetLightColor(lightColor);
	left_leg->SetLightColor(lightColor);
	right_leg->SetLightColor(lightColor);
	eyes->SetLightColor(lightColor);
}

void CCharacter::SetPos(float x)
{
	m_pos.x += x;
}

void CCharacter::CheckState() {
	if (isJumping) {
		State_Jumping();
	}

	switch (state)
	{
	case STATE::IDLE:
		State_Idle();
		break;
	case STATE::LEFT:
		State_Running();
		break;
	case STATE::RIGHT:
		State_Running();
		break;
	case STATE::FRONT:
		State_Running();
		break;
	case STATE::BACK:
		State_Running();
		break;
	}
}

void CCharacter::SetState(int a)
{
	state = a;
}

void CCharacter::State_Idle()
{
	
	
}

void CCharacter::State_Running()
{
	float armRotationAngle = glm::radians(90.f) + glm::radians(45.f) * glm::sin(animationTime);
	float bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(animationTime);
	float armTranslationOffset = 0.3f * glm::sin(animationTime);

	// Update animation time
	animationTime += 0.001f; // You can adjust the speed of the animation by changing this value

	// Arms animation
	glm::mat4 rot_arm = glm::rotate(glm::mat4(1.f), armRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 tr_arm = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -0.5f + armTranslationOffset, 0.f));
	left_arm->SetModelMat(final_tr * rot_arm * tr_arm);
	right_arm->SetModelMat(final_tr * rot_arm * tr_arm);

	// Body and eyes animation
	glm::mat4 rot_body = glm::rotate(glm::mat4(1.f), bodyRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
	body->SetModelMat(final_tr * rot_body);
	face->SetModelMat(final_tr * rot_body);
	eyes->SetModelMat(final_tr * rot_body);
}

void CCharacter::State_Jumping()
{
	
}
