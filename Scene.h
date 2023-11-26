#pragma once

class CGameObject;
class CScene
{
private:
	int& w_width;
	int& w_height;

	CGameObject* m_Cube;

	glm::vec3 cameraPos;
	glm::vec3 cameraLook;

	glm::vec3 lightPos;
	glm::vec3 lightColor;

public:
	CScene(int& width, int& height);
	~CScene();

	void Initialize();				//생성될 때 할 일
	void Update(float ElapsedTime);					//타이머에서 할 일
	void FixedUpdate();				//충돌처리 등
	void Render();					//드로우
	void Release();					//소멸될 때 할 일

	void MouseEvent(int button, int state, int x, int y);
	void KeyboardEvent(int state, unsigned char key);
	void SpecialKeyEvent(int state, int key);

	std::pair<GLuint, GLsizei> InitCube(GLuint shader);
};
