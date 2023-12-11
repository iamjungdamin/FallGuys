#include "GameObject.h"

CGameObject::CGameObject()
{
	Initialize();
}

CGameObject::~CGameObject()
{
	Release();
}

void CGameObject::SetShader(GLuint shader)
{
	m_shader = shader;
}

void CGameObject::SetVao(GLuint vao, int vertexCount)
{
	m_vao = vao;
	m_vertexCount = vertexCount;
	isInitialized = true;
}

void CGameObject::Initialize()
{
	m_vao = 0;
	m_shader = 0;
	m_vertexCount = 0;

	isInitialized = false;

	m_pos = glm::vec3(0.f);
	modelMat = glm::mat4(1.f);
	cameraMat = glm::mat4(1.f);
	projectMat = glm::mat4(1.f);

	scaleMat = glm::mat4(1.f);
}

void CGameObject::Update(float ElapsedTime)
{
	if (isInitialized) {
		modelMat = glm::translate(glm::mat4(1.f), m_pos) * modelMat * scaleMat;
	}
}

void CGameObject::FixedUpdate()
{
}

void CGameObject::Render()
{
	if (isInitialized) {
		glUseProgram(m_shader);
		glBindVertexArray(m_vao);

		GLint modelLoc = glGetUniformLocation(m_shader, "modelMat");
		GLint cameraLoc = glGetUniformLocation(m_shader, "cameraMat");
		GLint projectLoc = glGetUniformLocation(m_shader, "projectMat");
		if (modelLoc < 0 or cameraLoc < 0 or projectLoc < 0)
			std::cerr << "transformLoc Err" << std::endl;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(cameraMat));
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projectMat));

		glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	}
}

void CGameObject::Release()
{
}

void CGameObject::SetCameraMat(glm::mat4 camera)
{
	cameraMat = camera;
}

void CGameObject::SetProjectMat(glm::mat4 project)
{
	projectMat = project;
}

void CGameObject::SetModelMat(glm::mat4 model)
{
	modelMat = model;
}


void CGameObject::SetCameraPos(glm::vec3 cameraPos)
{
	GLint cameraPosLoc = glGetUniformLocation(m_shader, "cameraPos");
	if (cameraPosLoc < 0)
		std::cerr << "Can not found cameraPosLoc" << std::endl;
	glUniform3f(cameraPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
}

void CGameObject::SetLightPos(glm::vec3 lightPos)
{
	GLint lPosLoc = glGetUniformLocation(m_shader, "lightPos");
	if (lPosLoc < 0)
		std::cerr << "Can not found lightPosLoc" << std::endl;
	glUniform3f(lPosLoc, lightPos.x, lightPos.y, lightPos.z);
}

void CGameObject::SetLightColor(glm::vec3 lightColor)
{
	GLint lColorLoc = glGetUniformLocation(m_shader, "lightColor");
	if (lColorLoc < 0)
		std::cerr << "Can not found lightColorLoc" << std::endl;
	glUniform3f(lColorLoc, lightColor.x, lightColor.y, lightColor.z);
}

void CGameObject::SetPos(float x, float y, float z)
{
	SetPos({ x, y, z });
}

void CGameObject::SetPos(glm::vec3 pos)
{
	m_pos = pos;
}

void CGameObject::SetScale(float x, float y, float z)
{
	SetScale({ x, y, z });
}

void CGameObject::SetScale(glm::vec3 scale)
{
	scaleMat = glm::scale(glm::mat4(1.f), scale);
}

