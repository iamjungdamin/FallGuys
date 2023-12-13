#include "Map.h"

CMap::CMap() : CGameObject()
{
	Initialize();
}

CMap::~CMap()
{
	Release();
}

void CMap::Initialize()
{
	m_pos = { 0.0f,0.f,0.f };
	
}

void CMap::Update(float ElapsedTime)
{
	if (isInitialized) {
	
		CGameObject::Update(ElapsedTime);
	}

}

void CMap::FixedUpdate()
{
	CGameObject::FixedUpdate();
}

void CMap::Render()
{
	CGameObject::Render();



	// Rectangle 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-60.0f, -2.0f, 40.0f);
	glVertex3f(-60.0f, -4.0f, 40.0f);
	glVertex3f(60.0f, -4.0f, 40.0f);
	glVertex3f(60.0f, -2.0f, 40.0f);
	glEnd();

	// Rectangle 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-60.0f, -2.0f, -440.0f);
	glVertex3f(-60.0f, -4.0f, -440.0f);
	glVertex3f(60.0f, -4.0f, -440.0f);
	glVertex3f(60.0f, -2.0f, -440.0f);
	glEnd();

	// Rectangle 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-60.0f, -2.0f, 40.0f);
	glVertex3f(-60.0f, -4.0f, 40.0f);
	glVertex3f(-60.0f, -4.0f, -440.0f);
	glVertex3f(-60.0f, -2.0f, -440.0f);
	glEnd();

	// Rectangle 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(60.0f, -2.0f, 40.0f);
	glVertex3f(60.0f, -4.0f, 40.0f);
	glVertex3f(60.0f, -4.0f, -440.0f);
	glVertex3f(60.0f, -2.0f, -440.0f);
	glEnd();

	// Top Rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-60.0f, -2.0f, 40.0f);
	glVertex3f(-60.0f, -2.0f, -440.0f);
	glVertex3f(60.0f, -2.0f, -440.0f);
	glVertex3f(60.0f, -2.0f, 40.0f);
	glEnd();

	// Bottom Rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-60.0f, -4.0f, 40.0f);
	glVertex3f(-60.0f, -4.0f, -440.0f);
	glVertex3f(60.0f, -4.0f, -440.0f);
	glVertex3f(60.0f, -4.0f, 40.0f);
	glEnd();

	////222222222222222222222222222222222222222
	glBegin(GL_LINE_LOOP);
	glVertex3f(-30.0f, 26.f, -500.f);
	glVertex3f(-30.0f, 24.f, -500.f);
	glVertex3f(30.0f, 24.f, -500.f);
	glVertex3f(30.0f, 26.f, -500.f);
	glEnd();

	// Rectangle 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-30.0f, 26.f, -680.f);
	glVertex3f(-30.0f, 24.f, -680.f);
	glVertex3f(30.0f, 24.f, -680.f);
	glVertex3f(30.0f, 26.f, -680.f);
	glEnd();

	// Rectangle 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-30.0f, 26.f, -500.f);
	glVertex3f(-30.0f, 24.f, -500.f);
	glVertex3f(-30.0f, 24.f, -680.f);
	glVertex3f(-30.0f, 26.f, -680.f);
	glEnd();

	// Rectangle 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(30.0f, 26.f, -500.f);
	glVertex3f(30.0f, 24.f, -500.f);
	glVertex3f(30.0f, 24.f, -680.f);
	glVertex3f(30.0f, 26.f, -680.f);
	glEnd();

	// Top Rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-30.0f, 26.f, -500.f);
	glVertex3f(-30.0f, 26.f, -680.f);
	glVertex3f(30.0f, 26.f, -680.f);
	glVertex3f(30.0f, 26.f, -500.f);
	glEnd();

	// Bottom Rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-30.0f, 24.f, -500.f);
	glVertex3f(-30.0f, 24.f, -680.f);
	glVertex3f(30.0f, 24.f, -680.f);
	glVertex3f(30.0f, 24.f, -500.f);
	glEnd();
}

void CMap::Release()
{
	CGameObject::Release();
}

glm::vec3 CMap::GetPos() const
{
	return m_pos;
}

glm::vec3 CMap::GetBBSize_1() const
{
	return { 60.0f, 2.0f, -438.f };
}
glm::vec3 CMap::GetBBSize_2() const
{
	return { 30.f, 2.f, 2.f };
}
glm::vec3 CMap::GetBBSize_3() const
{
	return { 2.f, 2.f, 2.f };
}
glm::vec3 CMap::GetBBSize_4() const
{
	return { 2.f, 2.f, 2.f };
}
