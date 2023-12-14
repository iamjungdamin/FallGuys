#pragma once
#include "GameObject.h"

#define num 25 * 4

namespace TYPE {
	enum TYPE {	// 충돌 시 효과
		IDLE,	// 미충돌 시
		// 이하 충돌 시
		SHAKE,
		TRANSLATE,
		ROTATE,
		ROTATE2,
		SCALE
	};
}

class CFloorObject
{
private:
	CGameObject* Floor[num];

	int type[num];
	bool isDeleted[num];

	float InitPosY[num];
	glm::vec3 m_pos[num];
	glm::vec3 scale[num];
	float rotateY[num];

public:
	CFloorObject();
	virtual ~CFloorObject();

	void SetShader(GLuint shader);
	void SetVao(GLuint vao, int vertexCount);
	void SetCameraMat(glm::mat4 cameraMat);
	void SetProjectMat(glm::mat4 projectMat);
	void SetCameraPos(glm::vec3 cameraPos);
	void SetLightPos(glm::vec3 lightPos);
	void SetLightColor(glm::vec3 lightColor);

	virtual void Initialize();
	virtual void Update(float ElapsedTime);
	virtual void FixedUpdate();
	virtual void Render();
	virtual void Release();

	glm::vec3 GetPos(int i) const;
	void SetPosY(int i, float y);
	glm::vec3 GetBBSize() const;

	void Drop(int i);
	int GetIndex() const;
	bool GetIsDeleted(int i) const;
	float GetInitPosY(int i) const;
};

