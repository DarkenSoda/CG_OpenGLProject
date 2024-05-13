#ifndef CYLINDER_H
#define CYLINDER_H

#include <Assignment/Cube.h>

class Cylinder {
public:
    Mesh center, modelCenter;

    Cube cube[8];
    Cube rims[4];
    glm::vec3 cubeScale = glm::vec3(0.1f, 0.5f, 0.1f);
    glm::vec3 rimScale = glm::vec3(0.05f, 1.0f, 0.05f);

    Cylinder() {
        cube[0].position.z = .55f;
        cube[1].position.z = -.55f;
        cube[2].position.y = .55f;
        cube[3].position.y = -.55f;

        cube[2].rotation.x = 90.0f;
        cube[3].rotation.x = 90.0f;
        cube[4].position = glm::vec3(0.0f, 0.3875f, -0.3875f);
        cube[4].rotation.x = 45.0f;
        cube[5].position = glm::vec3(0.0f, -0.3875f, 0.3875f);
        cube[5].rotation.x = 45.0f;
        cube[6].position = glm::vec3(0.0f, 0.3875f, 0.3875f);
        cube[6].rotation.x = -45.0f;
        cube[7].position = glm::vec3(0.0f, -0.3875f, -0.3875f);
        cube[7].rotation.x = -45.0f;

        for (int i = 0; i < 4; i++) {
            rims[i].rotation.x = 45 * i;
        }

        for (int i = 0; i < 8; i++) {
            cube[i].scale = cubeScale;
            rims[i / 2].scale = rimScale;
            modelCenter.children.push_back(&cube[i]);
            modelCenter.children.push_back(&rims[i / 2]);

            cube[i].color = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
            rims[i / 2].color = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
        }

        center.children.push_back(&modelCenter);
    }

    void draw(Shader& shader, float deltaTime) {
        center.draw(shader);
    }

    void rotate(float deltaTime, float speed = 100.0f) {
        modelCenter.rotation.x -= deltaTime * speed;
    }
};

#endif