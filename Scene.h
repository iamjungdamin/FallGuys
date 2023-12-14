#pragma once
class CCharacter;
class CGameObject;
class CMap;
class CFloorObject;
class CDoorObject;

class CScene
{
private:
	int& w_width;
	int& w_height;
	//��ü
	CGameObject* m_Cube;
	CDoorObject* m_Door;

	CCharacter* m_Character;
	CMap* m_Map;
	CFloorObject* m_Floor;
	// ī�޶�
	glm::vec3 cameraPos;
	glm::vec3 cameraLook;
	glm::vec2 preMousePos { -1.f, -1.f };
	float cameraRotateY;

	glm::vec3 RotatedCameraFront = { 0,0,-1 };
	glm::vec3 RotatedCameraRight = { 1,0,0 };
	//����
	glm::vec3 lightPos;
	glm::vec3 lightColor;

	


public:
	CScene(int& width, int& height);
	~CScene();

	void Initialize();				//������ �� �� ��
	void Update(float ElapsedTime);					//Ÿ�̸ӿ��� �� ��
	void FixedUpdate();				//�浹ó�� ��
	void Render();					//��ο�
	void Release();					//�Ҹ�� �� �� ��

	void MouseEvent(int button, int state, int x, int y);
	void MouseMotionEvent(int x, int y);
	void KeyboardEvent(int state, unsigned char key);
	void SpecialKeyEvent(int state, int key);

	std::pair<GLuint, GLsizei> InitCube(GLuint shader);
	std::pair<GLuint, GLsizei> InitFace(GLuint shader);
	std::pair<GLuint, GLsizei> InitBody(GLuint shader);
	std::pair<GLuint, GLsizei> InitLeft_arm(GLuint shader);
	std::pair<GLuint, GLsizei> InitRight_arm(GLuint shader);
	std::pair<GLuint, GLsizei> Initleft_leg(GLuint shader);
	std::pair<GLuint, GLsizei> InitRight_leg(GLuint shader);
	std::pair<GLuint, GLsizei> InitEyes(GLuint shader);
	std::pair<GLuint, GLsizei> InitMap(GLuint shader);
	std::pair<GLuint, GLsizei> InitFloor(GLuint shader);

	std::pair<GLuint, GLsizei> InitDoor(GLuint shader);

};
