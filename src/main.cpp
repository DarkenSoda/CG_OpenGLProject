#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <iostream>
#include <math.h>

struct MousePosition {
    double x, y;
};

void processInput(GLFWwindow* window);
double calculateFPS(GLFWwindow* window);
MousePosition cursorPosition(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void updateTitle(GLFWwindow* window, const char* title, double fps, MousePosition cursorPos);

const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 480;

int main(void) {
    GLFWwindow* window;
    char title[] = "OpenGL Project";

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    float vertices[] = {
        // positions         // colors
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,   // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // be sure to activate the shader
    Shader ourShader("../Shaders/VertexShader.vs", "../Shaders/FragmentShader.fs");
    ourShader.use();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // Close window on ESC key press
        processInput(window);

        // update window title with FPS and cursor position
        updateTitle(window, title, calculateFPS(window), cursorPosition(window));

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first rectangle
        // glBindVertexArray(VAO);  // no need to bind it every time
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);    // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(ourShader.ID);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
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

MousePosition cursorPosition(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Update window title with cursor position
    return { xpos, ypos };
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void updateTitle(GLFWwindow* window, const char* title, double fps, MousePosition cursorPos) {
    char newTitle[256];
    sprintf(newTitle, "%s | FPS: %.1f | Cursor Position: %.0f, %.0f", title, fps, cursorPos.x, cursorPos.y);
    glfwSetWindowTitle(window, newTitle);
}
