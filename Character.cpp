	#include "Character.h"
	#include <iostream>
	#include "FloorObject.h"
	#include "Map.h"
	#include "DoorObject.h"

	CCharacter::CCharacter()
	{
		face = new CGameObject;
		body = new CGameObject;
		left_arm = new CGameObject;
		right_arm = new CGameObject;
		left_leg = new CGameObject;
		right_leg = new CGameObject;
		eyes = new CGameObject;

		m_pos = { 0.f, 0.f, 10.f };
		final_tr = glm::translate(glm::mat4(1.f), m_pos);
		state = 0;
		m_rot = 180.f;
		min_y = 0.0f;
		running_animation.animationTime = 0.0f;
		running_animation.bodyRotationAngle = 0.0f;
		running_animation.armleftRotationAngle = 0.0f;
		running_animation.armleftTranslationOffset = 0.0f;
		running_animation.armrightRotationAngle = 0.0f;
		running_animation.armrightTranslationOffset = 0.0f;
		running_animation.legleftRotationAngle = 0.0f;
		running_animation.legleftTranslationOffset = 0.0f;
		running_animation.legrightRotationAngle = 0.0f;
		running_animation.legrightTranslationOffset = 0.0f;

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


	//glBegin(GL_LINE_LOOP);
	//glVertex3f(-GetBBSize().x / 2.f, -GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	//glVertex3f(-GetBBSize().x / 2.f, +GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	//glVertex3f(+GetBBSize().x / 2.f, +GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	//glVertex3f(+GetBBSize().x / 2.f, -GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	//glEnd();
}

	void CCharacter::Update(float ElapsedTime)
	{
		

		final_tr = glm::translate(glm::mat4(1.f), glm::vec3(m_pos.x, m_pos.y, m_pos.z));
		final_rot = glm::rotate(glm::mat4(1.f), glm::radians(m_rot), glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 tr; 
		glm::mat4 sc;
		glm::mat4 rot;
		/*printf("x : %lf y : %lf z : %lf \n", m_pos.x, m_pos.y, m_pos.z);*/
		
		if (isInGround == true) {
			if (isJumpKeyPressed)
			{
				// 점프 중인 상태이면 수직 속도를 감소시킵니다.
				jump_speed -= gravity * ElapsedTime;

				// 조정된 수직 속도를 계산합니다.
				float adjusted_move_y = jump_speed * ElapsedTime*2;
				m_pos.y += adjusted_move_y;

				printf("%lf\n", m_pos.y);
			}
		}
		else
		{
			// 중력을 더해줍니다. (음수로 빼는 대신 양수로 더해줌)
			jump_speed -= gravity * ElapsedTime;

			// 조정된 수직 속도를 계산합니다.
			float adjusted_move_y = jump_speed * ElapsedTime*2;

			m_pos.y += adjusted_move_y;
		}


		//printf("%lf\n", m_pos.y);
			// ĳ���Ͱ� ���� �Ʒ��� �������� ���
		if (m_pos.y < min_y) {
			std::cout << "�ٴ� 2 ";
			m_pos.y = min_y; // ���鿡 ��� ����
			isJumpKeyPressed = false; // ���� ���� ���� ����
			jump_speed = 10.f; // ���� 10�� �ӵ��� �ʱ�ȭ
		}
		else if (m_pos.y < -100.f) {
			isJumpKeyPressed = false;
			m_pos = { 0.f, 20.f, m_pos.z};
		}

		
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




	void CCharacter::SetCameraMat(glm::mat4 cameraMat, glm::vec3 frontVec, glm::vec3 rightVec)
	{
		face->SetCameraMat(cameraMat);
		body->SetCameraMat(cameraMat);
		left_arm->SetCameraMat(cameraMat);
		right_arm->SetCameraMat(cameraMat);
		left_leg->SetCameraMat(cameraMat);
		right_leg->SetCameraMat(cameraMat);
		eyes->SetCameraMat(cameraMat);

		RotatedCameraFront = frontVec;
		RotatedCameraRight = rightVec;

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

	void CCharacter::SetPos(float x, float y, float z){
		m_pos = { x,y,z };
	}


	glm::vec3 CCharacter::GetPos() const
	{
		return m_pos;
	}

	glm::vec3 CCharacter::GetBBSize() const
	{
		return { 2.5f, 4.5f, 1.5f };
	}

	bool CCharacter::IsCollided(int index, CGameObject* Obj) {
		if (index == 2) {
			CMap* M = dynamic_cast<CMap*>(Obj);

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = { -30.0f, 26.f, -640.f };
			glm::vec3 floorMax = { 30.0f, 28.f, -460.f };

			// 충돌 체크
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

			if (collisionX && collisionY && collisionZ)
			{
				if (isInGround == false)
				{
					//printf("min_y: %lf\n", min_y);
					min_y = 30.f;
					m_pos.y = min_y;
					isInGround = true;
				}
				//printf("2충돌 ");
			}
			else {
				isInGround = false;
				min_y = -1000.f;
			}
			return collisionX && collisionY && collisionZ;
		}

		else if (index == 3) {//map1
			CMap* M = dynamic_cast<CMap*>(Obj);

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = { -60.0f, -4.0f, -440.0f };
			glm::vec3 floorMax = { 60.0f, -2.0f, 40.0f };

			// 충돌 체크
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

			if (collisionX && collisionY && collisionZ)
			{
				if (isInGround == false)
				{
 					min_y = 0;
					m_pos.y = min_y;
					isInGround = true;
				}
				//printf("1충돌 ");
			}
			else {
				isInGround = false;
				min_y = -1000.f;
			}
			return collisionX && collisionY && collisionZ;
		}
	
		else if (index == 1) {
			CMap* M = dynamic_cast<CMap*>(Obj);

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = { -40.f, 56.f, -700.f };
			glm::vec3 floorMax = { 40.f, 58.f, -640.f };

			// 충돌 체크
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

			if (collisionX && collisionY && collisionZ)
			{
				if (isInGround == false)
				{
					min_y = 58.f;
					m_pos.y = min_y;
					isInGround = true;
				}
				//printf("3충돌 ");
			}
			else {
				isInGround = false;
				min_y = -1000.f;
			}
			return collisionX && collisionY && collisionZ;
		}
		else if (index == 4) {
			CMap* M = dynamic_cast<CMap*>(Obj);

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = { -50.f, -4.0f, -900.f };
			glm::vec3 floorMax = { 50.f, -2.0f, -750.f };

			// 충돌 체크
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;
				
			if (collisionX && collisionY && collisionZ)
			{
				if (isInGround == false)
				{
					min_y = 0.f;
					m_pos.y = min_y;
					isInGround = true;
				}
				//printf("3충돌 ");
			}
			else {
				isInGround = false;
				min_y = -1000.f;
			}
			return collisionX && collisionY && collisionZ;
		}
	}

	bool CCharacter::IsCollided(CDoorObject* D) {
		bool isCollision = false;  // 충돌 여부를 저장하는 변수를 추가

		for (int i = 0; i < 25; ++i) {
			for (int j = 0; j < 2; ++j) {
				// 현재 문에 대한 충돌 박스 계산
				glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
				glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

				glm::vec3 floorMin = D->GetPos(i, j);
				glm::vec3 floorMax = D->GetPos(i, j);
				int type = D->GetType(i, j);

				floorMin.x -= 4.f;
				floorMin.y -= 10.f;
				floorMin.z -= 0.5f;

				floorMax.x += 4.f;
				floorMax.y += 10.f;
				floorMin.z += 0.5f;

				// 현재 문과 캐릭터 간의 충돌 체크
				bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
				bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
				bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

				if (collisionX && collisionY && collisionZ) {
					if (type == 0) {
						if (isInGround == false) {
							m_pos.z = collisionZ;
							isInGround = true;
						}
						//printf("문[%d][%d] 충돌합니다\n", i, j);
						isCollision = true;  // 충돌 발생 시 변수를 true로 설정
					}
					else if(type != 0) {
						if (isInGround == false) {
							D->touch[i] = true;
							isInGround = true;
						}
						//printf("문[%d][%d] 충돌합니다\n", i, j);
						isCollision = true;  // 충돌 발생 시 변수를 true로 설정
					}
				}
				else {
					isInGround = false;
					min_y = -1000.f;
				}
			}
		}

		return isCollision;  // 모든 문에 대한 충돌 체크를 완료한 후 충돌 여부 반환
	}

	bool CCharacter::IsCollided(CFloorObject* F)
	{
		bool result;

		for (int i = 0; i < num; ++i) {
			if (F->GetIsDeleted(i)) {
				continue;
			}

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = F->GetPos(i) - glm::vec3(2.f, 0.5f, 2.f);
			glm::vec3 floorMax = F->GetPos(i) + glm::vec3(2.f, 0.5f, 2.f);
			float originFloorY = F->GetInitPosY(i) + 1.f;

			// 충돌 체크
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

			result = collisionX && collisionY && collisionZ;

			if (result)
			{
				if (isInGround == false)
				{
					min_y = originFloorY;
					m_pos.y = min_y;
					isInGround = true;
				}
				F->Drop(i);
				IncreaseScore(10);
				return true;
			}

		}

		// 25개 다 검사 후 false 이면
		if (result == false) {
			isInGround = false;
			min_y = -1000.f;
			return false;
		}
	}



	void CCharacter::CheckState() {	//	enum STATE { IDLE, LEFT, RIGHT, FRONT, BACK }; 
		if (isJumpKeyPressed)
		{
	
		
		}
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

	void CCharacter::SetJumpKeyPressed(bool a)
	{
		isJumpKeyPressed = a;
	}

	int CCharacter::GetScore() const
	{
		return score;
	}

	void CCharacter::IncreaseScore(int amount)
	{
		score + amount;
	}

	
	void CCharacter::SetState(int a)
	{
		state = a;


		if (a == 1) // LEFT
		{
			m_move.x = -1 * RotatedCameraRight.x;
			m_move.z = -1 * RotatedCameraRight.z;
		}
		if (a == 2) //RIGHT
		{
			m_move.x = RotatedCameraRight.x;
			m_move.z = RotatedCameraRight.z;
		}
		if (a == 3) // FRONT
		{
			m_move.x = RotatedCameraFront.x;
			m_move.z = RotatedCameraFront.z;
		}
		if (a == 4) // BACK
		{
			m_move.x = -1 * RotatedCameraFront.x;
			m_move.z = -1 * RotatedCameraFront.z;
		}
	

	}

	void CCharacter::State_Idle() {
		// Stop movement

			m_move = { 0, 0, 0 };

			// 현재 방향을 유지합니다.
	

			float legAmplitude = 0.1f;
			float legFrequency = 2.0f;


			idle_animation.initialLeftArmRotationAngle = running_animation.armleftRotationAngle;
			idle_animation.initialRightArmRotationAngle = running_animation.armrightRotationAngle;

			//회전
			float rotationAngle = glm::atan(prevMove.x, prevMove.z);
			final_rot = glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0.f, 1.f, 0.f));


			// 몸
			idle_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(idle_animation.animationTime);
			idle_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(idle_animation.animationTime);
			// 팔
			idle_animation.armleftRotationAngle = glm::radians(20.f) + glm::radians(15.f) * glm::sin(idle_animation.animationTime);
			idle_animation.armleftTranslationOffset = 0.3f * glm::sin(idle_animation.animationTime);
			idle_animation.armrightRotationAngle = glm::radians(20.f) + glm::radians(15.f) * glm::sin(idle_animation.animationTime);
			idle_animation.armrightTranslationOffset = 0.3f * glm::sin(idle_animation.animationTime);

			idle_animation.armleftTranslationOffset = legAmplitude * glm::sin(legFrequency * idle_animation.animationTime);
			idle_animation.armrightTranslationOffset = -legAmplitude * glm::sin(legFrequency * idle_animation.animationTime);
			// Legs animation
			running_animation.legleftRotationAngle = glm::radians(5.f) + glm::radians(5.f) * glm::sin(running_animation.animationTime);
			running_animation.legleftTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);
			running_animation.legrightRotationAngle = glm::radians(5.f) + glm::radians(5.f) * glm::sin(running_animation.animationTime);
			running_animation.legrightTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);

			running_animation.legleftTranslationOffset = legAmplitude * glm::sin(legFrequency * running_animation.animationTime);
			running_animation.legrightTranslationOffset = -legAmplitude * glm::sin(legFrequency * running_animation.animationTime);



			idle_animation.animationTime += 0.001f;

			// Arms animation
			glm::mat4 rot_leftarm = glm::rotate(glm::mat4(1.f), idle_animation.armleftRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
			glm::mat4 tr_leftarm = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -0.3f + idle_animation.armleftTranslationOffset, 0.1f));
			glm::mat4 rot_rightarm = glm::rotate(glm::mat4(1.f), idle_animation.armrightRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
			glm::mat4 tr_rightarm = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -0.3f + idle_animation.armrightTranslationOffset, 0.1f));
			left_arm->SetModelMat(final_tr * final_rot * rot_leftarm * tr_leftarm);
			right_arm->SetModelMat(final_tr * final_rot * rot_rightarm * tr_rightarm);

			// Legs animation
			glm::mat4 tr_leftleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, running_animation.legleftTranslationOffset));
			glm::mat4 tr_rightleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, running_animation.legrightTranslationOffset));
			left_leg->SetModelMat(final_tr * final_rot * tr_leftleg);
			right_leg->SetModelMat(final_tr * final_rot * tr_rightleg);

			// Body and eyes animation
			glm::mat4 rot_body = glm::rotate(glm::mat4(1.f), idle_animation.bodyRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
			body->SetModelMat(final_tr * final_rot * rot_body);
			face->SetModelMat(final_tr * final_rot * rot_body);
			eyes->SetModelMat(final_tr * final_rot * rot_body);


	


	}

	void CCharacter::State_Running()
	{
		
		prevMove = m_move;

		float legAmplitude = 0.1f;
		float legFrequency = 2.0f;

	
		// 이동
		m_pos.x += m_move.x * speed;
		m_pos.z += m_move.z* speed;
		//printf("character move: %f, %f, %f\n", m_pos.x, m_pos.y, m_pos.z);
	

		//회전
		float rotationAngle = glm::atan(m_move.x, m_move.z);
		final_rot = glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0.f, 1.f, 0.f));


		// 몸
		running_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(running_animation.animationTime);
		running_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(running_animation.animationTime);
		// 팔
		running_animation.armleftRotationAngle = glm::radians(90.f) + glm::radians(15.f) * glm::sin(running_animation.animationTime);
		running_animation.armleftTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);
		running_animation.armrightRotationAngle= glm::radians(90.f) + glm::radians(15.f) * glm::sin(running_animation.animationTime);
		running_animation.armrightTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);

		running_animation.armleftTranslationOffset = legAmplitude * glm::sin(legFrequency * running_animation.animationTime);
		running_animation.armrightTranslationOffset = -legAmplitude * glm::sin(legFrequency * running_animation.animationTime);

	

		//다리
		running_animation.legleftRotationAngle = glm::radians(5.f) + glm::radians(5.f) * glm::sin(running_animation.animationTime);
		running_animation.legleftTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);
		running_animation.legrightRotationAngle = glm::radians(5.f) + glm::radians(5.f) * glm::sin(running_animation.animationTime);
		running_animation.legrightTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);

		running_animation.legleftTranslationOffset = legAmplitude * glm::sin(legFrequency * running_animation.animationTime);
		running_animation.legrightTranslationOffset = -legAmplitude * glm::sin(legFrequency * running_animation.animationTime);



		running_animation.animationTime += 0.001f;

		// Arms animation
		glm::mat4 rot_leftarm = glm::rotate(glm::mat4(1.f), running_animation.armleftRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
		glm::mat4 tr_leftarm = glm::translate(glm::mat4(1.f), glm::vec3(0.2f, -0.8f + running_animation.armleftTranslationOffset, 0.1f));
		glm::mat4 rot_rightarm = glm::rotate(glm::mat4(1.f), running_animation.armrightRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
		glm::mat4 tr_rightarm = glm::translate(glm::mat4(1.f), glm::vec3(-0.2f, -0.8f + running_animation.armrightTranslationOffset, 0.1f));
		left_arm->SetModelMat(final_tr * final_rot  * rot_leftarm * tr_leftarm);
		right_arm->SetModelMat(final_tr * final_rot* rot_rightarm * tr_rightarm);
	
		// Legs animation
		glm::mat4 tr_leftleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, running_animation.legleftTranslationOffset));
		glm::mat4 tr_rightleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, running_animation.legrightTranslationOffset));
		left_leg->SetModelMat(final_tr * final_rot *tr_leftleg);
		right_leg->SetModelMat(final_tr * final_rot* tr_rightleg);

		// Body and eyes animation
		glm::mat4 rot_body = glm::rotate(glm::mat4(1.f), running_animation.bodyRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
		body->SetModelMat(final_tr * final_rot * rot_body);
		face->SetModelMat(final_tr * final_rot* rot_body);
		eyes->SetModelMat(final_tr * final_rot* rot_body);

	


	}

	void CCharacter::State_Jumping()
	{

		float legAmplitude = 0.1f;
		float legFrequency = 2.0f;


		// Rotation
		float rotationAngle = glm::atan(m_move.x, m_move.z);
		final_rot = glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0.f, 1.f, 0.f));

		// Body animation
		running_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(running_animation.animationTime);

		// Arms animation
		running_animation.armleftRotationAngle = glm::radians(90.f) + glm::radians(15.f) * glm::sin(running_animation.animationTime);
		running_animation.armleftTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);
		running_animation.armrightRotationAngle = glm::radians(90.f) + glm::radians(15.f) * glm::sin(running_animation.animationTime);
		running_animation.armrightTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);

		running_animation.armleftTranslationOffset = legAmplitude * glm::sin(legFrequency * running_animation.animationTime);
		running_animation.armrightTranslationOffset = -legAmplitude * glm::sin(legFrequency * running_animation.animationTime);
	
		// Legs animation
		running_animation.legleftRotationAngle = glm::radians(5.f) + glm::radians(5.f) * glm::sin(running_animation.animationTime);
		running_animation.legleftTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);
		running_animation.legrightRotationAngle = glm::radians(5.f) + glm::radians(5.f) * glm::sin(running_animation.animationTime);
		running_animation.legrightTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);

		running_animation.legleftTranslationOffset = legAmplitude * glm::sin(legFrequency * running_animation.animationTime);
		running_animation.legrightTranslationOffset = -legAmplitude * glm::sin(legFrequency * running_animation.animationTime);

		// Update animation time
		running_animation.animationTime += 0.001f;

		// Arms animation
		glm::mat4 rot_leftarm = glm::rotate(glm::mat4(1.f), running_animation.armleftRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
		glm::mat4 tr_leftarm = glm::translate(glm::mat4(1.f), glm::vec3(0.2f, -0.8f + running_animation.armleftTranslationOffset, 0.1f));
		glm::mat4 rot_rightarm = glm::rotate(glm::mat4(1.f), running_animation.armrightRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
		glm::mat4 tr_rightarm = glm::translate(glm::mat4(1.f), glm::vec3(-0.2f, -0.8f + running_animation.armrightTranslationOffset, 0.1f));
		left_arm->SetModelMat(final_tr * final_rot * rot_leftarm * tr_leftarm);
		right_arm->SetModelMat(final_tr * final_rot * rot_rightarm * tr_rightarm);

		// Legs animation
		glm::mat4 tr_leftleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, running_animation.legleftTranslationOffset));
		glm::mat4 tr_rightleg = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.2f, running_animation.legrightTranslationOffset));
		left_leg->SetModelMat(final_tr * final_rot * tr_leftleg);
		right_leg->SetModelMat(final_tr * final_rot * tr_rightleg);

		// Body and eyes animation
		glm::mat4 rot_body = glm::rotate(glm::mat4(1.f), running_animation.bodyRotationAngle, glm::vec3(-1.f, 0.f, 0.f));
		body->SetModelMat(final_tr * final_rot * rot_body);
		face->SetModelMat(final_tr * final_rot * rot_body);
		eyes->SetModelMat(final_tr * final_rot * rot_body);
	}

	void CCharacter::Speed(float a)
	{
		jump_speed =  a;
	}