#ifndef BIKE_H
#define BIKE_H

#include <Assignment/Cube.h>
#include <Assignment/Cylinder.h>

class Bike {
public:
    Mesh center, bikeCenter;

    Cylinder frontWheel, backWheel;
    float speed = 100, wheelSpeed = 300, wheelAngleSpeed = 100, xSpeed = 5.0f;
    Cube body[4];

    Bike() {
        frontWheel.center.position = glm::vec3(0.0f, 0.0f, -1.0f);
        backWheel.center.position = glm::vec3(0.0f, 0.0f, 1.0f);

        body[0].position = glm::vec3(0.0f, 0.75f, 0.15f);
        body[0].scale = glm::vec3(0.5f, 0.1f, 2.25f);
        body[1].position = glm::vec3(0.0f, 0.75f, -1.0f);
        body[1].scale = glm::vec3(0.1f, 1.5f, 0.1f);
        body[2].position = glm::vec3(0.0f, 0.375f, 1.0f);
        body[2].scale = glm::vec3(0.1f, 0.75f, 0.1f);
        body[3].position = glm::vec3(0.0f, 1.5f, -1.0f);
        body[3].scale = glm::vec3(0.75f, 0.1f, 0.1f);

        for (int i = 0; i < 4; i++) {
            body[i].color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
            bikeCenter.children.push_back(&body[i]);
        }

        bikeCenter.children.push_back(&frontWheel.center);
        bikeCenter.children.push_back(&backWheel.center);

        center.children.push_back(&bikeCenter);
    }

    void draw(Shader& shader, float deltaTime) {
        center.draw(shader);
    }

    void rotateWheelLeft(float deltaTime) {
        body[1].rotation.y += deltaTime * wheelAngleSpeed;
        body[3].rotation.y += deltaTime * wheelAngleSpeed;
        frontWheel.center.rotation.y += deltaTime * wheelAngleSpeed;
    }

    void rotateWheelRight(float deltaTime) {
        body[1].rotation.y -= deltaTime * wheelAngleSpeed;
        body[3].rotation.y -= deltaTime * wheelAngleSpeed;
        frontWheel.center.rotation.y -= deltaTime * wheelAngleSpeed;
    }

    void resetWheel() {
        body[1].rotation.y = 0;
        body[3].rotation.y = 0;
        frontWheel.center.rotation.y = 0;
    }

    void autoRotateWheel(float deltaTime) {
        frontWheel.rotate(deltaTime, wheelSpeed);
        backWheel.rotate(deltaTime, wheelSpeed);
    }
};

#endif
