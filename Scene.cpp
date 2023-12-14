#include "stdafx.h"
#include "Scene.h"
#include "CubeObject.h"
#include "Character.h"
#include "Map.h"
#include "FloorObject.h"
#include "DoorObject.h"

CScene::CScene(int& width, int& height) : w_width{ width }, w_height{ height }
{
	Initialize();
}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	GLuint shader = CreateShaderProgram("./Shader/vertex.glsl", "./Shader/fragment.glsl");	// ���̴� ���α׷� ����

	//m_Cube = new CCubeObject;
	//m_Cube->SetShader(shader);
	//auto c_vao = InitCube(shader);
	//m_Cube->SetVao(c_vao.first, c_vao.second);

	m_Map = new CMap;
	m_Map->SetShader(shader);
	auto M_vao = InitMap(shader);
	m_Map->SetVao(M_vao.first, M_vao.second);



	m_Character = new CCharacter;
	m_Character->SetShader(shader);


	auto f_vao = InitFace(shader);
	m_Character->SetVao_face(f_vao.first, f_vao.second);
	auto b_vao = InitBody(shader);
	m_Character->SetVao_body(b_vao.first, b_vao.second);
	auto la_vao = InitLeft_arm(shader);
	m_Character->SetVao_left_arm(la_vao.first, la_vao.second);
	auto ra_vao = InitRight_arm(shader);
	m_Character->SetVao_right_arm(ra_vao.first, ra_vao.second);
	auto ll_vao = Initleft_leg(shader);
	m_Character->SetVao_left_leg(ll_vao.first, ll_vao.second);
	auto rl_vao = InitRight_leg(shader);
	m_Character->SetVao_right_leg(rl_vao.first, rl_vao.second);
	auto e_vao = InitEyes(shader);
	m_Character->SetVao_eyes(e_vao.first, e_vao.second);


	m_Door = new CDoorObject;
	m_Door->SetShader(shader);
	auto c_vao = InitDoor(shader);
	m_Door->SetVao(c_vao.first, c_vao.second);

	
	m_Floor = new CFloorObject;
	if (m_Floor) {
		auto floor_vao = InitFloor(shader);
		m_Floor->SetShader(shader);
		m_Floor->SetVao(floor_vao.first, floor_vao.second);
	}

	cameraPos = { 0.f, 0.f, 1.f };
	cameraLook = { 0.f, 0.f, 0.f };

	lightPos = glm::vec3{ 5.f, 5.f, 0.f };
	lightColor = glm::vec3{ 1.f, 1.f, 1.f };
	

}

void CScene::Update(float ElapsedTime)
{
	// ī�޶�
	cameraPos = m_Character->GetPos() + glm::vec3(0.f, 5.f, 20.f);
	cameraLook = m_Character->GetPos();

	glm::mat4 cameraMat = glm::lookAt(cameraPos, cameraLook, glm::vec3{ 0.f, 1.f, 0.f });
	cameraMat = glm::translate(cameraMat, m_Character->GetPos());
	cameraMat = glm::rotate(cameraMat, glm::radians(cameraRotateY), glm::vec3(0.f, 1.f, 0.f));
	cameraMat = glm::translate(cameraMat, -m_Character->GetPos());
	glm::mat4 projectMat = glm::perspective(glm::radians(45.f), (float)w_width / (float)w_height, 0.1f, 1000.f);


	if (m_Character) {
		m_Character->SetCameraMat(cameraMat);
		m_Character->SetProjectMat(projectMat);
		m_Character->SetCameraPos(cameraPos);
		m_Character->SetLightPos(lightPos);
		m_Character->SetLightColor(lightColor);
		m_Character->Update(ElapsedTime);
	}

	if (m_Map) {
		m_Map->SetCameraMat(cameraMat);
		m_Map->SetProjectMat(projectMat);
		m_Map->SetCameraPos(cameraPos);
		m_Map->SetLightPos(lightPos);
		m_Map->SetLightColor(lightColor);
		m_Map->Update(ElapsedTime);
	}

	if (m_Door) {
		m_Door->SetCameraMat(cameraMat);
		m_Door->SetProjectMat(projectMat);
		m_Door->SetCameraPos(cameraPos);
		m_Door->SetLightPos(lightPos);
		m_Door->SetLightColor(lightColor);
		m_Door->Update(ElapsedTime);
	}

	
	if (m_Floor) {
		m_Floor->SetCameraMat(cameraMat);
		m_Floor->SetProjectMat(projectMat);
		m_Floor->SetCameraPos(cameraPos);
		m_Floor->SetLightPos(lightPos);
		m_Floor->SetLightColor(lightColor);
		m_Floor->Update(ElapsedTime);


	}

	if (m_Character->IsCollided(m_Door)) {
		/*	std::cout << vFloors[i].GetIndex() << '\n';*/
	}

	if (m_Character->IsCollided(m_Floor)) {

	}
	else {
		for (int i = 0; i < 4; ++i) {
			if (m_Character->IsCollided(i + 1, m_Map)) {
				break;
			}
		}
	}

	
}

void CScene::FixedUpdate()
{
}

void CScene::Render()
{
	

	if (m_Character) {
		m_Character->Render();
	}

	if (m_Map) {
		m_Map->Render();
	}


	if (m_Door) {
		m_Door->Render();
	}

	if (m_Floor) {
		m_Floor->Render();
	}


}

void CScene::Release()
{
	//delete m_Cube;
	//m_Cube = nullptr;

	delete m_Character;
	m_Character = nullptr;

	delete m_Map;
	m_Map = nullptr;

	delete m_Door;
	m_Door = nullptr;
	

	delete m_Floor;
	m_Floor = nullptr;
}

void CScene::MouseEvent(int button, int state, int x, int y)
{
	static const int WHEEL_UP = 3, WHEEL_DOWN = 4;
	switch (state) {
	case GLUT_DOWN:
		switch (button) {
		case GLUT_LEFT_BUTTON:
			preMousePos = { x, y };
			break;
		case GLUT_RIGHT_BUTTON:
			
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case WHEEL_DOWN:
			break;
		case WHEEL_UP:
			break;
		}
		break;
	case GLUT_UP:
		switch (button) {
		case GLUT_LEFT_BUTTON:
			preMousePos = { -1.f, -1.f };
			break;
		}
		break;
	default:
		break;
	}
}

void CScene::MouseMotionEvent(int x, int y)
{
	float sens = 0.02f;		//ȸ�� �� �ΰ���
	glm::vec2 currMousePos{ -1.f, -1.f };
	
	if (preMousePos.x > -1 && preMousePos.y > -1) {
		currMousePos.x = x;
		currMousePos.y = y;

		if (currMousePos.x != preMousePos.x) {
			cameraRotateY += (currMousePos.x - preMousePos.x) * sens;
			currMousePos.x = preMousePos.x;
			currMousePos.y = preMousePos.y;
		}
	}
}


void CScene::KeyboardEvent(int state, unsigned char key) {
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		case 'a':
		case 'A':
			m_Character->SetState(STATE::LEFT);
			m_Character->SetLeftKeyPressed(true);
			break;
		case 's':  
		case 'S':
			m_Character->SetState(STATE::BACK);
			m_Character->SetBackKeyPressed(true);
			break;
		case 'd':
		case 'D':
			m_Character->SetState(STATE::RIGHT);
			m_Character->SetRightKeyPressed(true);
			break;
		case 'w':
		case 'W':
			m_Character->SetState(STATE::FRONT);
			m_Character->SetFrontKeyPressed(true);
			break;
		case ' ':
			m_Character->SetJumpKeyPressed(true);
			break;
		
		default:
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
		case 'a':
		case 'A':
			m_Character->SetLeftKeyPressed(false);
			break;
		case 's':
		case 'S':
			m_Character->SetBackKeyPressed(false);
			break;
		case 'd':
		case 'D':
			m_Character->SetRightKeyPressed(false);
			break;
		case 'w':
		case 'W':
			m_Character->SetFrontKeyPressed(false);
			break;
	
		default:
			break;
		}
		break;
	}
}

void CScene::SpecialKeyEvent(int state, int key)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		
			break;
		default:
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
		default:
			break;
		}
		break;
	}
}

std::pair<GLuint, GLsizei> CScene::InitCube(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�
	glm::vec3 fixedColor = { 0.0f, 0.0f, 0.0f }; // ���
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/left_leg.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitFace(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 1.0f, 1.0f, 1.0f }; // ���
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/face.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitBody(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // ��ȫ��
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/body.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitLeft_arm(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // ��ȫ��
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/left_arm.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitRight_arm(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // ��ȫ��
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/right_arm.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::Initleft_leg(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // ��ȫ��
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/left_leg.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitRight_leg(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // ��ȫ��
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/right_leg.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitEyes(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 0.0f, 0.0f, 0.f }; // ������
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/eyes.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitMap(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 0.3f, 0.4f, 0.f }; // ������
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/map.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitFloor(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 0.3f, 0.8f, 1.f };
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/Cube.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitDoor(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { 0.6f, 0.8f, 1.f };
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/Door.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}
