#include "stdafx.h"
#include "Timer.h"
#include "Scene.h"
#include <iostream>


// �ݹ��Լ�
GLvoid Display(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid SpecialKeyboardUp(int key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid PassiveMotion(int x, int y);
GLvoid IdleScene(GLvoid);
GLvoid TimerFunction(int value);


// --- ���� ����
GLint winWidth = 1600, winHeight = 1000;
std::string Title = "SampleProject_8_2";

CTimer g_gameTimer{ Title };

CScene* g_pscene = nullptr;


void main(int argc, char** argv)								//--- ������ ����ϰ� �ݹ��Լ� ���� 
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);										// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);							// �������� ��ġ ����
	glutInitWindowSize(winWidth, winHeight);								// �������� ũ�� ����
	glutCreateWindow(Title.c_str());									// ������ ����(������ �̸�)

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {								// glew �ʱ�ȭ
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}

	if (glewIsSupported("GL_VERSION_3_0")) {
		std::cout << "GLEW Version is 3.0\n";
		std::cout << "GLEW Version is 3.0\n";
	}
	else {
		std::cout << "GLEW 3.0 not supported\n";
	}

	// ���� �����Ѵ�.
	g_pscene = new CScene{ winWidth, winHeight };

	srand(unsigned int(time(NULL)));


	//	�ݹ��Լ� ����
	glutDisplayFunc(Display);									// ��� �Լ��� ����
	glutReshapeFunc(Reshape);									// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);									// Ű���� �Է�(������ ��) �ݹ��Լ� ����
	glutKeyboardUpFunc(KeyboardUp);								// Ű���� �Է�(���� ��) �ݹ��Լ� ����
	glutSpecialFunc(SpecialKeyboard);							// F1~F9 ���
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);										// Ŭ������ ��
	glutMotionFunc(Motion);										// ������ �̵��� ��
	glutPassiveMotionFunc(PassiveMotion);						// ������ �ʰ� �̵��� ��
	glutIdleFunc(IdleScene);									// �ƹ� �̺�Ʈ�� ���� ��
	//glutTimerFunc(16, TimerFunction, 0);						// Ư�� �ð����� �� �� ����

	glEnable(GL_DEPTH_TEST);	// ���̰˻� Ȱ��ȭ
	glEnable(GL_CULL_FACE);		// �ø�	(�޸� ����)
	//glFrontFace(GL_CCW);		// �ø��� �ո� ���� (GL_CW - �ð�, GL_CCW - �ݽð�)
	//glCullFace(GL_BACK);		// � ���� �������� ����

	//glEnable(GL_BLEND);			// ���� ����� Ȱ��ȭ�Ѵ�.	// Alpha Ȱ��ȭ
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//������ ���� �÷� ���� Csource�� ���İ����� ����

	glutMainLoop();												// �̺�Ʈ ó�� ����
	glutLeaveMainLoop();										// ���α׷� ����
}

GLvoid Display(GLvoid)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);						// ������ ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// ������ ������ ��ü�� ĥ�ϱ�

	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.

	if (g_pscene)
		g_pscene->Render();

	glutSwapBuffers();											// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (g_pscene)
		g_pscene->KeyboardEvent(GLUT_DOWN, key);

	switch (key) {
	case 27:			// ESC Key
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	if (g_pscene)
		g_pscene->KeyboardEvent(GLUT_UP, key);
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	if (g_pscene)
		g_pscene->SpecialKeyEvent(GLUT_DOWN, key);
}

GLvoid SpecialKeyboardUp(int key, int x, int y)
{
	if (g_pscene)
		g_pscene->SpecialKeyEvent(GLUT_UP, key);

	switch (key) {
	case GLUT_KEY_F8:			// F9 ������ ��üȭ��
		
		break;
	case GLUT_KEY_F9:			// F9 ������ ��üȭ��
		glutFullScreenToggle();
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (g_pscene)
		g_pscene->MouseEvent(button, state, x, y);
}

GLvoid Motion(int x, int y)
{
	if (g_pscene)
		g_pscene->MouseMotionEvent(x, y);
}

GLvoid PassiveMotion(int x, int y)
{
	return GLvoid();
}

GLvoid IdleScene(GLvoid)
{
	float elapsedTime = g_gameTimer.Tick(0);	// ���� �ð� ��� �� Ÿ�̸� �۵� (value�� 0���� ������ ���������� X)

	if (g_pscene)
		g_pscene->Update(elapsedTime);

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();						// ȭ�� �� ���
	glutTimerFunc(16, TimerFunction, 0);			// Ÿ�̸��Լ� �� ����
}
