#ifndef MESH_H
#define MESH_H

#include <vector>
#include <Texture.h>
#include <VAO.h>
#include <BufferObject.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mesh {
public:
    std::vector<Mesh*> children;
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    bool isTextured = false;

    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
    std::vector<glm::vec2> texCoords;
    std::vector<Texture> textures;

    Mesh();
    Mesh(std::vector<glm::vec3> vertices, std::vector<Texture> textures);
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords);
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<GLuint> indices);
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<Texture> textures);
    void draw(Shader& shader);
    void setupMesh();

    virtual ~Mesh();
protected:
    VAO vao;
    BufferObject* vbo;
    // BufferObject* ebo;
};

#endif