	#include "Character.h"
	#include <iostream>
	#include "FloorObject.h"
	#include "Map.h"

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


	glBegin(GL_LINE_LOOP);
	glVertex3f(-GetBBSize().x / 2.f, -GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(-GetBBSize().x / 2.f, +GetBBSize().y / 2.f, -GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, +GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	glVertex3f(+GetBBSize().x / 2.f, -GetBBSize().y / 2.f, +GetBBSize().z / 2.f);
	glEnd();
}

	void CCharacter::Update(float ElapsedTime)
	{
		final_tr = glm::translate(glm::mat4(1.f), glm::vec3(m_pos.x, m_pos.y, m_pos.z));
		final_rot = glm::rotate(glm::mat4(1.f), glm::radians(m_rot), glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 tr; 
		glm::mat4 sc;
		glm::mat4 rot;
		/*printf("x : %lf y : %lf z : %lf \n", m_pos.x, m_pos.y, m_pos.z);*/
		
		//printf("%lf\n", min_floor);
		if (min_floor == true) {
			if (isJumpKeyPressed)
			{
				// ���� ���� �����̸� ���� �ӵ��� ���ҽ�ŵ�ϴ�.
				jump_speed -= gravity * ElapsedTime;

				// ������ ���� �ӵ��� ����մϴ�.
				float adjusted_move_y = jump_speed * ElapsedTime;


				//printf("%lf\n", m_pos.y);
				// ĳ���Ͱ� ���� �Ʒ��� �������� ���
				if (m_pos.y < min_y) {
					m_pos.y = min_y; // ���鿡 ��� ����
					isJumpKeyPressed = false; // ���� ���� ���� ����
					jump_speed = 30.f; // ���� 10�� �ӵ��� �ʱ�ȭ
				}
				else {

					m_pos.y += adjusted_move_y;
				}

			}
		}
		if(min_floor== false)
		{
			// ���� ���� �����̸� ���� �ӵ��� ���ҽ�ŵ�ϴ�.
			jump_speed -= gravity * ElapsedTime;

			// ������ ���� �ӵ��� ����մϴ�.
			float adjusted_move_y = jump_speed * ElapsedTime;

			
			m_pos.y += adjusted_move_y;
			
		}

		//���� ���� �ൿ�ϴ� �Լ�
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

	glm::vec3 CCharacter::GetPos() const
	{
		return m_pos;
	}

	glm::vec3 CCharacter::GetBBSize() const
	{
		return { 2.5f, 4.5f, 1.5f };
	}

	bool CCharacter::IsCollided(int index, CGameObject* Obj) {
		if (index == 1) {
			CMap* M = dynamic_cast<CMap*>(Obj);

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = { -30.0f, 26.f, -670.f };
			glm::vec3 floorMax = { 30.0f, 28.f, -490.f };

			// �浹 üũ
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

			if (collisionX && collisionY && collisionZ)
			{
				if (min_floor == false)
				{
					printf("min_y: %lf\n", min_y);
					min_y = 30.f;
					m_pos.y = min_y;
				}
				min_floor = true;
				printf("2�浹");
			}
			else {
				min_floor = false;
			}
			return collisionX && collisionY && collisionZ;
		}

		else if (index == 2) {//map1
			CMap* M = dynamic_cast<CMap*>(Obj);

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = { -60.0f, -4.0f, -440.0f };
			glm::vec3 floorMax = { 60.0f, -2.0f, 40.0f };

			// �浹 üũ
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

			if (collisionX && collisionY && collisionZ)
			{
				if (min_floor == false)
				{
 					min_y = 0;
					m_pos.y = min_y;
				}
				min_floor = true;
				printf("1�浹");
			}
			else {
				min_floor = false;
			}
			return collisionX && collisionY && collisionZ;
		}
	
		else if (index == 3) {
			CMap* M = dynamic_cast<CMap*>(Obj);

			glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
			glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

			glm::vec3 floorMin = { -40.f, 68.f, -740.f };
			glm::vec3 floorMax = { 40.f, 70.f, -680.f };

			// �浹 üũ
			bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
			bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
			bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

			if (collisionX && collisionY && collisionZ)
			{
				if (min_floor == false)
				{
					min_y = 70.f;
					m_pos.y = min_y;
				}
				min_floor = true;
				printf("�浹");
			}
			else {
				min_floor = false;
			}
			return collisionX && collisionY && collisionZ;
		}
		else if (index == 4) {
			
		}
	}

	bool CCharacter::IsCollided(CFloorObject* F)
	{
		glm::vec3 boxMin = m_pos - GetBBSize() / 2.0f;
		glm::vec3 boxMax = m_pos + GetBBSize() / 2.0f;

		glm::vec3 floorMin = F->GetPos() - F->GetBBSize() / 2.0f;
		glm::vec3 floorMax = F->GetPos() + F->GetBBSize() / 2.0f;

		// �浹 üũ
		bool collisionX = boxMax.x >= floorMin.x && boxMin.x <= floorMax.x;
		bool collisionY = boxMax.y >= floorMin.y && boxMin.y <= floorMax.y;
		bool collisionZ = boxMax.z >= floorMin.z && boxMin.z <= floorMax.z;

		if (collisionX || collisionY || collisionZ)
		{
			/*printf("�浹");*/
		}
		return collisionX && collisionY && collisionZ;
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

	void CCharacter::State_Idle() {
		// Stop movement

			m_move = { 0, 0, 0 };

			// ���� ������ �����մϴ�.
	

			float legAmplitude = 0.1f;
			float legFrequency = 2.0f;


			idle_animation.initialLeftArmRotationAngle = running_animation.armleftRotationAngle;
			idle_animation.initialRightArmRotationAngle = running_animation.armrightRotationAngle;

			//ȸ��
			float rotationAngle = glm::atan(prevMove.x, prevMove.z);
			final_rot = glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0.f, 1.f, 0.f));


			// ��
			idle_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(idle_animation.animationTime);
			idle_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(idle_animation.animationTime);
			// ��
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

		//if (isLeftKeyPressed== true && isRightKeyPressed == false && isFrontKeyPressed== false&& isBackKeyPressed == false)
		//{
		//		m_move.x = -1;
		//		m_move.z = 0;
		//}
		//if (isLeftKeyPressed == false && isRightKeyPressed == true && isFrontKeyPressed == false  && isBackKeyPressed== false)
		//{
		//		m_move.x = 1;
		//		m_move.z = 0;
		//	
		//}
		//if (isLeftKeyPressed == false && isRightKeyPressed == false && isFrontKeyPressed== true && isBackKeyPressed== false)
		//{
		//		m_move.x = 0;
		//		m_move.z = -1;
		//	
		//}
		//if (isLeftKeyPressed == false && isRightKeyPressed== false && isFrontKeyPressed == false && isBackKeyPressed == true)
		//{
		//		m_move.x = 0;
		//		m_move.z = 1;
		//	
		//}
	

		prevMove = m_move;

		float legAmplitude = 0.1f;
		float legFrequency = 2.0f;
	
		// �̵�
		m_pos.x += m_move.x * speed;
		m_pos.z += m_move.z* speed;

	

		//ȸ��
		float rotationAngle = glm::atan(m_move.x, m_move.z);
		final_rot = glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0.f, 1.f, 0.f));


		// ��
		running_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(running_animation.animationTime);
		running_animation.bodyRotationAngle = glm::radians(5.f) + glm::radians(2.5f) * glm::sin(running_animation.animationTime);
		// ��
		running_animation.armleftRotationAngle = glm::radians(90.f) + glm::radians(15.f) * glm::sin(running_animation.animationTime);
		running_animation.armleftTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);
		running_animation.armrightRotationAngle= glm::radians(90.f) + glm::radians(15.f) * glm::sin(running_animation.animationTime);
		running_animation.armrightTranslationOffset = 0.3f * glm::sin(running_animation.animationTime);

		running_animation.armleftTranslationOffset = legAmplitude * glm::sin(legFrequency * running_animation.animationTime);
		running_animation.armrightTranslationOffset = -legAmplitude * glm::sin(legFrequency * running_animation.animationTime);

	

		//�ٸ�
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

