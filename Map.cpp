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



	glBegin(GL_LINE_LOOP);
	glVertex3f(-GetBBSize().x / 2.f, -GetBBSize().y / 2.f, -GetBBSize().z / 2.f); // -1บฮลอ -GetBBSize().x / 2.f
	glVertex3f(-GetBBSize().x / 2.f, +GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, +GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, -GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-GetBBSize().x / 2.f, -GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	glVertex3f(-GetBBSize().x / 2.f, +GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, +GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, -GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-GetBBSize().x / 2.f, -GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(-GetBBSize().x / 2.f, -GetBBSize().y / 2.f, +GetBBSize().z / 2.f);

	glVertex3f(-GetBBSize().x / 2.f, +GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(-GetBBSize().x / 2.f, +GetBBSize().y / 2.f, +GetBBSize().z / 2.f);

	glVertex3f(+GetBBSize().x / 2.f, +GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, +GetBBSize().y / 2.f, +GetBBSize().z / 2.f);

	glVertex3f(+GetBBSize().x / 2.f, -GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, -GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
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

glm::vec3 CMap::GetBBSize() const
{
	return { 2.f, 2.f, 2.f };
}

