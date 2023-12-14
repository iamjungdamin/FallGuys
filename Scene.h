#pragma once
class CCharacter;
class CGameObject;
class CMap;
class CFloorObject;
class CDoorObject;
class TitleScreen {
public:
    TitleScreen() {
        // Initialize title screen resources, shaders, etc.
        // For simplicity, let's just use a text title for now
        titleText = "My Game Title";
    }

    void Update(float ElapsedTime) {
        // Handle title screen logic, input, etc.
        // For simplicity, we'll just switch to the game scene if any key is pressed
        if (keyPressed) {
            keyHandled = true;
        }
    }

    void Render() {
        // Render title screen graphics
        // For simplicity, let's just render the title text
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-0.5f, 0.0f);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)titleText.c_str());
    }

    void Release() {
        // Release title screen resources
        // For simplicity, nothing to release in this example
    }

    // Add other necessary functions...

    // Function to check if a key is pressed on the title screen
    void KeyPressed() {
        keyPressed = true;
    }

    // Function to check if a key is handled
    bool IsKeyHandled() const {
        return keyHandled;
    }

private:
    std::string titleText;
    bool keyPressed = false;
    bool keyHandled = false;
    // Add members specific to the title screen
};

class CScene
{
private:
    int& w_width;
    int& w_height;
    //  ü
    CGameObject* m_Cube;
    CDoorObject* m_Door;

    CCharacter* m_Character;
    CMap* m_Map;
    CFloorObject* m_Floor;

    CGameObject* m_StartUI;

    // ī ޶ 
    glm::vec3 cameraPos;
    glm::vec3 cameraLook;
    glm::vec2 preMousePos{ -1.f, -1.f };
    float cameraRotateY;

    glm::vec3 RotatedCameraFront = { 0,0,-1 };
    glm::vec3 RotatedCameraRight = { 1,0,0 };
    //    
    glm::vec3 lightPos;
    glm::vec3 lightColor;

    bool m_isTitleScreen;
    bool GameStart = false;


public:
    CScene(int& width, int& height);
    ~CScene();

    void Initialize();            //               
    void Update(float ElapsedTime);               //Ÿ ̸ӿ         
    void FixedUpdate();            // 浹ó     
    void Render();               //  ο 
    void Release();               // Ҹ           

    void MouseEvent(int button, int state, int x, int y);
    void MouseMotionEvent(int x, int y);
    void KeyboardEvent(int state, unsigned char key);
    void SpecialKeyEvent(int state, int key);

    std::pair<GLuint, GLsizei> InitStartUI(GLuint shader);
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