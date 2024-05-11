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
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

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

    ~Mesh();
protected:
    VAO vao;
    BufferObject* vbo;
    // BufferObject* ebo;
    void setupMesh();
};

#endif