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
	state = 0;
	m_rot = 180.f;

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


	// 처음 초기값


}

void CCharacter::Update(float ElapsedTime)
{
	final_tr = glm::translate(glm::mat4(1.f), glm::vec3(m_pos.x, m_pos.y, m_pos.z));
	final_rot = glm::rotate(glm::mat4(1.f), glm::radians(m_rot), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 tr; 
	glm::mat4 sc;
	glm::mat4 rot;

	
	

	
	//여기까지 위치 초기값

	//상태 따라 행동하는 함수
	CheckState();


	

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

void CCharacter::CheckState() {	//	enum STATE { IDLE, LEFT, RIGHT, FRONT, BACK }; 
	if (isLeftKeyPressed || isRightKeyPressed || isFrontKeyPressed || isBackKeyPressed) {
		State_Running();
	}
	else {
		State_Idle();
	}
}

void CCharacter::SetRightKeyPressed(bool a)
{
	isRightKeyPressed = a;
}

void CCharacter::SetLeftKeyPressed(bool a)
{
	isLeftKeyPressed = a;

}

void CCharacter::SetBackKeyPressed(bool a)
{
	isBackKeyPressed = a;
}

void CCharacter::SetFrontKeyPressed(bool a)
{
	isFrontKeyPressed = a;
}

void CCharacter::SetState(int a)
{
	state = a;

	if (a == 1) // LEFT
	{
		m_move.x = -1;
	}
	if (a == 2) //RIGHT
	{
		m_move.x = 1;
	}
	if (a == 3) // FRONT
	{
		m_move.z = -1;
	}
	if (a == 4) // BACK
	{
		m_move.z = 1;
	}

}

void CCharacter::State_Idle()
{
	m_move = { 0,0,0 };
	
}

void CCharacter::State_Running()
{
	
	float legAmplitude = 0.1f;
	float legFrequency = 2.0f;
	
	// 이동
	m_pos.x += m_move.x * speed;
	m_pos.z += m_move.z* speed;


	//회전
	float rotationAngle = glm::atan(m_move.x, m_move.z);
	final_rot = glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0.f, 1.f, 0.f));


	// 몸
	bodyRotationAngle_RUNNING = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(animationTime);
	bodyRotationAngle_RUNNING = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(animationTime);
	// 팔
	armleftRotationAngle_RUNNING = glm::radians(90.f) + glm::radians(15.f) * glm::sin(animationTime);
	armleftTranslationOffset_RUNNING = 0.3f * glm::sin(animationTime);	
	armrightRotationAngle_RUNNING = glm::radians(90.f) + glm::radians(15.f) * glm::sin(animationTime);
	armrightTranslationOffset_RUNNING = 0.3f * glm::sin(animationTime);

	armleftTranslationOffset_RUNNING = legAmplitude * glm::sin(legFrequency * animationTime);
	armrightTranslationOffset_RUNNING = -legAmplitude * glm::sin(legFrequency * animationTime);

	

	//다리
	legleftRotationAngle_RUNNING = glm::radians(5.f) + glm::radians(5.f) * glm::sin(animationTime);
	legleftTranslationOffset_RUNNING = 0.3f * glm::sin(animationTime);
	legrightRotationAngle_RUNNING = glm::radians(5.f) + glm::radians(5.f) * glm::sin(animationTime);
	legrightTranslationOffset_RUNNING = 0.3f * glm::sin(animationTime);

	legleftTranslationOffset_RUNNING = legAmplitude * glm::sin(legFrequency * animationTime);
	legrightTranslationOffset_RUNNING = -legAmplitude * glm::sin(legFrequency * animationTime);



	animationTime += 0.001f;

	// Arms animation
	glm::mat4 rot_leftarm = glm::rotate(glm::mat4(1.f), armleftRotationAngle_RUNNING, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 tr_leftarm = glm::translate(glm::mat4(1.f), glm::vec3(0.2f, -0.8f + armleftTranslationOffset_RUNNING, 0.1f));
	glm::mat4 rot_rightarm = glm::rotate(glm::mat4(1.f), armrightRotationAngle_RUNNING, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 tr_rightarm = glm::translate(glm::mat4(1.f), glm::vec3(-0.2f, -0.8f + armrightTranslationOffset_RUNNING, 0.1f));
	left_arm->SetModelMat(final_tr * final_rot  * rot_leftarm * tr_leftarm);
	right_arm->SetModelMat(final_tr * final_rot* rot_rightarm * tr_rightarm);
	
	// Legs animation
	glm::mat4 tr_leftleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, legleftTranslationOffset_RUNNING));
	glm::mat4 tr_rightleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, legrightTranslationOffset_RUNNING));
	left_leg->SetModelMat(final_tr * final_rot *tr_leftleg);
	right_leg->SetModelMat(final_tr * final_rot* tr_rightleg);

	// Body and eyes animation
	glm::mat4 rot_body = glm::rotate(glm::mat4(1.f), bodyRotationAngle_RUNNING, glm::vec3(-1.f, 0.f, 0.f));
	body->SetModelMat(final_tr * final_rot * rot_body);
	face->SetModelMat(final_tr * final_rot* rot_body);
	eyes->SetModelMat(final_tr * final_rot* rot_body);

	


}

void CCharacter::State_Jumping()
{
	
}
