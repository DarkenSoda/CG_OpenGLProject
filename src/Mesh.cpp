#include <Mesh.h>

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->textures = textures;

    setupMesh();
}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords) {
    this->vertices = vertices;
    this->texCoords = texCoords;

    setupMesh();
}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->texCoords = texCoords;
    this->textures = textures;

    setupMesh();
}

void Mesh::draw(Shader& shader) {
    shader.setBool("useTexture", isTextured);
    shader.setVec4("color", color);
    for (unsigned int i = 0; i < textures.size(); i++) {
        Texture::activate(GL_TEXTURE0 + i);
        textures[i].bind();
        shader.setInt("texture1", i);
    }

    // draw mesh
    vao.bind();

    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, scale);

    shader.setMat4("model", model);


    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    vao.unbind();

    for (auto& child : children) {
        child->model = model;
        child->draw(shader);
    }
    model = glm::mat4(1.0f);
}

Mesh::~Mesh() {
    vao.deleteVAO();
    vbo->deleteBuffer();
    delete vbo;
}

void Mesh::setupMesh() {
    vao.bind();

    size_t totalSize = vertices.size() * sizeof(glm::vec3) + texCoords.size() * sizeof(glm::vec2);
    vbo = new BufferObject(GL_ARRAY_BUFFER, nullptr, totalSize, GL_STATIC_DRAW);
    vbo->bind();
    size_t offset = 0;
    vbo->updateData(offset, vertices.size() * sizeof(glm::vec3), vertices.data());
    offset += vertices.size() * sizeof(glm::vec3);
    vbo->updateData(offset, texCoords.size() * sizeof(glm::vec2), texCoords.data());

    vao.linkVBO(*vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0); // vertices
    vao.linkVBO(*vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)offset); // texCoords

    vao.unbind();
    vbo->unbind();
}
