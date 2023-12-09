#include "stdafx.h"
#include "Scene.h"
#include "CubeObject.h"
#include "Character.h"
#include "FloorObject.h"

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

	for (int i = 0; i < 5; ++i) {
		vFloors.push_back({ });
	}

	auto floor_vao = InitFloor(shader);
	for (int i = 0; i < vFloors.size(); ++i) {
		vFloors[i].SetShader(shader);
		vFloors[i].SetVao(floor_vao.first, floor_vao.second);
	}
	// set vao
	
	cameraRot.x = 0.f, cameraRot.y = 10.f, cameraRot.z = 20.f;
	cameraPos = glm::vec3{ cameraRot.x, cameraRot.y, cameraRot.z };
	cameraLook = glm::vec3{ 0.f ,4.f,0.f};

	lightPos = glm::vec3{ 5.f, 5.f, 0.f };
	lightColor = glm::vec3{ 1.f, 1.f, 1.f };


}

void CScene::Update(float ElapsedTime)
{
	// ī�޶�
	cameraPos = glm::vec3{ cameraRot.x, cameraRot.y, cameraRot.z };

	glm::mat4 cameraMat = glm::lookAt(cameraPos, cameraLook, glm::vec3{ 0.f, 1.f, 0.f });
	glm::mat4 projectMat = glm::perspective(glm::radians(45.f), (float)w_width / (float)w_height, 0.1f, 1000.f);

	//if (m_Cube) {
	//	m_Cube->SetCameraMat(cameraMat);
	//	m_Cube->SetProjectMat(projectMat);
	//	m_Cube->SetCameraPos(cameraPos);
	//	m_Cube->SetLightPos(lightPos);
	//	m_Cube->SetLightColor(lightColor);
	//	m_Cube->Update(ElapsedTime);
	//}

	if (m_Character) {
		m_Character->SetCameraMat(cameraMat);
		m_Character->SetProjectMat(projectMat);
		m_Character->SetCameraPos(cameraPos);
		m_Character->SetLightPos(lightPos);
		m_Character->SetLightColor(lightColor);
		m_Character->Update(ElapsedTime);
	}

	for (int i = 0; i < vFloors.size(); ++i) {
		vFloors[i].SetCameraMat(cameraMat);
		vFloors[i].SetProjectMat(projectMat);
		vFloors[i].SetCameraPos(cameraPos);
		vFloors[i].SetLightPos(lightPos);
		vFloors[i].SetLightColor(lightColor);
		vFloors[i].Update(ElapsedTime);
	}
}

void CScene::FixedUpdate()
{
}

void CScene::Render()
{
	//if (m_Cube) {
	//	m_Cube->Render();
	//}

	if (m_Character) {
		m_Character->Render();
	}

	for (int i = 0; i < vFloors.size(); ++i) {
		vFloors[i].Render();
	}
}

void CScene::Release()
{
	//delete m_Cube;
	//m_Cube = nullptr;

	delete m_Character;
	m_Character = nullptr;

	vFloors.clear();
}

void CScene::MouseEvent(int button, int state, int x, int y)
{
	static const int WHEEL_UP = 3, WHEEL_DOWN = 4;
	switch (state) {
	case GLUT_DOWN:
		switch (button) {
		case GLUT_LEFT_BUTTON:
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
		break;
	default:
		break;
	}
}

void CScene::KeyboardEvent(int state, unsigned char key)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		case 'a':
		case 'A':
			RotateSceneY(1.0f);
			m_Character->SetState(STATE::LEFT);
			break;
		case 's':
		case 'S':
			RotateSceneY(-1.0f);
			m_Character->SetState(STATE::BACK);
			break;
		case 'd':
		case 'D':
			cameraRot.z += 1.f;		
			m_Character->SetState(STATE::RIGHT);
			break;
		case 'w':
		case 'W':
			m_Character->SetState(STATE::FRONT);
			break;
		case 'e':
			cameraRot.z -= 1.f;
			break;
		default:
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
			m_Character->SetState(STATE::IDLE);
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

std::pair<GLuint, GLsizei> CScene::InitFloor(GLuint shader)
{
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	glm::vec3 fixedColor = { (rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f };
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


void CScene::RotateSceneY(float angle)
{
	// Rotate the scene around the Y-axis
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// Apply the rotation to the camera position
	glm::vec4 rotatedCameraPos = rotationMatrix * glm::vec4(cameraRot.x, cameraRot.y, cameraRot.z, 1.0f);

	// Update the camera position
	cameraRot.x = rotatedCameraPos.x;
	cameraRot.y = rotatedCameraPos.y;
	cameraRot.z = rotatedCameraPos.z;
}