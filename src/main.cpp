#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <Camera.h>
#include <VAO.h>
#include <Texture.h>
#include <BufferObject.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <Mesh.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Assignment/Cube.h>
#include <Assignment/House.h>


struct MousePosition {
    double x, y;
};

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

MousePosition cursorPos = { 0.0, 0.0 };

bool camMode = false;
Camera camera(glm::vec3(11.0f, 8.0f, 12.0f), glm::vec3(0.0f, 1.0f, 0.0f), -135.0f, -20.0f);
float lastX = 0, lastY = 0;

void calculateDeltaTime();
void processInput(GLFWwindow* window);
double calculateFPS(GLFWwindow* window);
void calculateMousePos(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void updateTitle(GLFWwindow* window, const char* title, double fps);
void mouseClick_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
float mixValue = 0.2f;

// Assignment Variables to be deleted
bool isOpened;

int main(void) {
    GLFWwindow* window;
    char title[] = "OpenGL Project";

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("Refresh Rate: %dHz\n", glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate);

    // Loading Textures
    Texture texture("../Textures/wall.jpg", GL_RGB);
    Texture texture2("../Textures/container.jpg", GL_RGB);
    Texture texture3("../Textures/awesomeface.png", GL_RGBA);

    // be sure to activate the shader
    Shader ourShader("../Shaders/VertexShader.vs", "../Shaders/FragmentShader.fs");
    ourShader.use();    // don't forget to activate/use the shader before setting uniforms!

    // configure global opengl state
    // -----------------------------
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouseClick_callback);
    glfwSetKeyCallback(window, key_callback);


    House house;
    Mesh m;
    Cube c;
    c.position = glm::vec3(0.0f, 0.0f, 7.0f);

    m.children.push_back(&c);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        calculateDeltaTime();
        processInput(window);
        calculateMousePos(window);
        updateTitle(window, title, calculateFPS(window));

        /* Render here */
        glClearColor(0.2f, 0.45f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        if (isOpened) {
            if (house.doorParent.rotation.y < 90) {
                house.doorParent.rotation.y += 200 * deltaTime;
            }
        }
        else {
            if (house.doorParent.rotation.y > 0) {
                house.doorParent.rotation.y -= 200 * deltaTime;
            }
        }

        house.draw(ourShader);

        // m.rotation = glm::vec3(m.rotation.x, glfwGetTime() * 20, m.rotation.z);

        m.draw(ourShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteProgram(ourShader.ID);

    glfwTerminate();
    return 0;
}

void calculateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (camMode) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.processKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.processKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.processKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.processKeyboard(RIGHT, deltaTime);
    }
}

double calculateFPS(GLFWwindow* window) {
    static double fps;
    static double previousTime = glfwGetTime();
    static int frameCount = 0;
    double currentTime = glfwGetTime();
    frameCount++;

    if (currentTime - previousTime >= 1.0) {
        fps = frameCount / (currentTime - previousTime);
        frameCount = 0;
        previousTime = currentTime;
    }

    return fps;
}

void calculateMousePos(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    cursorPos.x = xpos;
    cursorPos.y = ypos;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (!camMode) return;

    camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.processMouseScroll(static_cast<float>(yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}

void updateTitle(GLFWwindow* window, const char* title, double fps) {
    char newTitle[256];
    sprintf(newTitle, "%s | FPS: %.1f | Cursor Position: %.0f, %.0f", title, fps, cursorPos.x, cursorPos.y);
    glfwSetWindowTitle(window, newTitle);
}

void mouseClick_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        camMode = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        camMode = false;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        isOpened = !isOpened;
    }
}
