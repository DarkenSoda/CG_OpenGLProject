#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <VAO.h>
#include <Texture.h>
#include <BufferObject.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
float mixValue = 0.2f;

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

    float vertices[] = {
        // positions         // colors          // texture coords
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f,     // top left  
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    VAO VAO1;
    VAO1.bind();
    BufferObject VBO(GL_ARRAY_BUFFER, (GLfloat*)vertices, sizeof(vertices), GL_STATIC_DRAW);
    BufferObject EBO(GL_ELEMENT_ARRAY_BUFFER, (GLuint*)indices, sizeof(indices), GL_STATIC_DRAW);

    // position attribute
    VAO1.linkVBO(VBO, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    // color attribute
    VAO1.linkVBO(VBO, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    // texture attribute
    VAO1.linkVBO(VBO, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    VBO.unbind();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Texture texture("../Textures/container.jpg", GL_RGB);
    Texture texture2("../Textures/awesomeface.png", GL_RGBA);
    
    Texture::activate(GL_TEXTURE0);
    texture.bind();

    Texture::activate(GL_TEXTURE1);
    texture2.bind();
    
    // be sure to activate the shader
    Shader ourShader("../Shaders/VertexShader.vs", "../Shaders/FragmentShader.fs");
    ourShader.use();    // don't forget to activate/use the shader before setting uniforms!
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // Close window on ESC key press
        processInput(window);

        // update window title with FPS and cursor position
        updateTitle(window, title, calculateFPS(window), cursorPosition(window));

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.setFloat("mixValue", mixValue);
        // draw our first rectangle
        // VAO1.bind();  // no need to bind it every time
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
    VAO1.deleteVAO();
    VBO.deleteBuffer();
    EBO.deleteBuffer();
    glDeleteProgram(ourShader.ID);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixValue += 0.005f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixValue -= 0.005f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
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
