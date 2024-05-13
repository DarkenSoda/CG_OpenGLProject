#ifndef HOUSE_H
#define HOUSE_H

#include <Assignment/Cube.h>

class House {
public:
    Mesh center;
    Mesh roof;
    std::vector<Mesh*> walls;
    Cube bkWall;
    Cube f1, f2, f3;
    Cube sl1, sl2, sl3, sl4, sl5;
    Cube sr1, sr2, sr3, sr4, sr5;
    Mesh doorParent;
    Cube door;
    Mesh windowParent[8];
    Cube window;
    Cube floor1, floor2;
    bool isOpened;

    House() {
        Texture texture("../Textures/wall.jpg", GL_RGB);
        center.position = glm::vec3(0.0f, 1.5f, 0.0f);
        center.scale = glm::vec3(1.0f, 1.5f, 1.0f);
        float thickness = 0.1f;
        glm::vec4 wallColor = glm::vec4(0.5882, 0.4275, 0.2784, 1.0);
        glm::vec4 wallColor2 = glm::vec4(0.6863, 0.5373, 0.3098, 1.0);
        glm::vec4 roofColor = glm::vec4(0.5, 0.15, 0.15, 1.0);
        glm::vec4 floorColor = glm::vec4(0.3608, 0.2235, 0.0706, 1.0);;

        bkWall.position = glm::vec3(0.0f, 0.0f, -3.5f);
        bkWall.scale = glm::vec3(5.0f, 3.0f, thickness);
        bkWall.color = wallColor;

        f1.position = glm::vec3(-1.5f, 0.0f, 3.5f);
        f1.scale = glm::vec3(2.0f, 3.0f, thickness);
        f1.color = wallColor;

        f2.position = glm::vec3(1.5f, 0.0f, 3.5f);
        f2.scale = glm::vec3(2.0f, 3.0f, thickness);
        f2.color = wallColor;

        f3.position = glm::vec3(0.0f, 0.625f, 3.5f);
        f3.scale = glm::vec3(1.0f, 1.75f, thickness);
        f3.color = wallColor;

        sl1.position = glm::vec3(-2.5f, -0.625f, 0.0f);
        sl1.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sl1.scale = glm::vec3(7.0f, 1.75f, thickness);
        sl1.color = wallColor2;

        sl2.position = glm::vec3(-2.5f, 1.25f, 0.0f);
        sl2.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sl2.scale = glm::vec3(7.0f, 0.5f, thickness);
        sl2.color = wallColor2;

        sl3.position = glm::vec3(-2.5f, 0.75f, 0.0f);
        sl3.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sl3.scale = glm::vec3(3.0f, 1.0f, thickness);
        sl3.color = wallColor2;

        sl4.position = glm::vec3(-2.5f, 0.75f, -3.0f);
        sl4.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sl4.scale = glm::vec3(1.0f, 1.0f, thickness);
        sl4.color = wallColor2;

        sl5.position = glm::vec3(-2.5f, 0.75f, 3.0f);
        sl5.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sl5.scale = glm::vec3(1.0f, 1.0f, thickness);
        sl5.color = wallColor2;

        sr1.position = glm::vec3(2.5f, -0.625f, 0.0f);
        sr1.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sr1.scale = glm::vec3(7.0f, 1.75f, thickness);
        sr1.color = wallColor2;

        sr2.position = glm::vec3(2.5f, 1.25f, 0.0f);
        sr2.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sr2.scale = glm::vec3(7.0f, 0.5f, thickness);
        sr2.color = wallColor2;

        sr3.position = glm::vec3(2.5f, 0.75f, 0.0f);
        sr3.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sr3.scale = glm::vec3(3.0f, 1.0f, thickness);
        sr3.color = wallColor2;

        sr4.position = glm::vec3(2.5f, 0.75f, -3.0f);
        sr4.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sr4.scale = glm::vec3(1.0f, 1.0f, thickness);
        sr4.color = wallColor2;

        sr5.position = glm::vec3(2.5f, 0.75f, 3.0f);
        sr5.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
        sr5.scale = glm::vec3(1.0f, 1.0f, thickness);
        sr5.color = wallColor2;

        doorParent.position = glm::vec3(-0.5f, -0.875f, 3.55f);
        doorParent.children.push_back(&door);

        door.position = glm::vec3(0.5f, 0.0f, 0.0f);
        door.scale = glm::vec3(1.0f, 1.25f, thickness);
        door.color = glm::vec4(0.9, 0.9, 0.9, 1.0);

        floor1.position.y = -1.5f;
        floor1.scale = glm::vec3(5.0f, thickness, 7.0f);
        floor2.scale = glm::vec3(5.0f, thickness, 7.0f);
        floor1.color = floorColor + 0.15f;
        floor2.color = floorColor;

        windowParent[0].position = glm::vec3(-2.55f, 0.75f, 2.5f);
        windowParent[2].position = glm::vec3(-2.55f, 0.75f, -1.5f);
        windowParent[1].position = glm::vec3(-2.55f, 0.75f, 1.5f);
        windowParent[3].position = glm::vec3(-2.55f, 0.75f, -2.5f);
        windowParent[4].position = glm::vec3(2.55f, 0.75f, 2.5f);
        windowParent[6].position = glm::vec3(2.55f, 0.75f, -1.5f);
        windowParent[5].position = glm::vec3(2.55f, 0.75f, 1.5f);
        windowParent[7].position = glm::vec3(2.55f, 0.75f, -2.5f);

        window.position = glm::vec3(0.0f, -0.125f, -0.25f);
        window.scale = glm::vec3(thickness, 0.75f, 0.5f);
        window.color = glm::vec4(0.9, 0.9, 0.9, 1.0);

        for (int i = 0; i < 4; i += 2) {
            windowParent[i + 1].rotation.y = -180.0f;
        }
        for (int i = 4; i < 8; i += 2) {
            windowParent[i + 1].rotation.y = 180.0f;
        }
        for (int i = 0; i < 8; i++) {
            windowParent[i].children.push_back(&window);
            walls.push_back(&windowParent[i]);
        }

        walls.push_back(&bkWall);
        walls.push_back(&f1);
        walls.push_back(&f2);
        walls.push_back(&f3);
        walls.push_back(&sl1);
        walls.push_back(&sl2);
        walls.push_back(&sl3);
        walls.push_back(&sl4);
        walls.push_back(&sl5);
        walls.push_back(&sr1);
        walls.push_back(&sr2);
        walls.push_back(&sr3);
        walls.push_back(&sr4);
        walls.push_back(&sr5);
        walls.push_back(&doorParent);
        walls.push_back(&floor1);
        walls.push_back(&floor2);

        center.children = walls;

        roof.vertices = {
            // front triangle
            {-0.5f, -0.5, 0.5f},
            {0.0f, 0.5, 0.5f},
            {0.5f, -0.5, 0.5f},

            // back triangle
            {-0.5f, -0.5, -0.5f},
            {0.0f, 0.5, -0.5f},
            {0.5f, -0.5, -0.5f},

            // left cube
            {-0.5f, -0.5, 0.5f},
            {0.0f, 0.5, 0.5f},
            {0.0f, 0.5, -0.5f},
            {0.0f, 0.5, -0.5f},
            {-0.5f, -0.5, -0.5f},
            {-0.5f, -0.5, 0.5f},

            // right cube
            {0.5f, -0.5, 0.5f},
            {0.0f, 0.5, 0.5f},
            {0.0f, 0.5, -0.5f},
            {0.0f, 0.5, -0.5f},
            {0.5f, -0.5, -0.5f},
            {0.5f, -0.5, 0.5f},

            // bottom cube
            {-0.5f, -0.5f, -0.5f},
            {0.5f, -0.5f, -0.5f},
            {0.5f, -0.5f,  0.5f},
            {0.5f, -0.5f,  0.5f},
            {-0.5f, -0.5f,  0.5f},
            {-0.5f, -0.5f, -0.5f},
        };
        roof.position = glm::vec3(0.0f, 2.5f, 0.0f);
        roof.scale = glm::vec3(6.0f, 2.0f, 8.0f);
        roof.color = roofColor;
        roof.setupMesh();

        center.children.push_back(&roof);
    }

    void draw(Shader& shader, float deltaTime) {
        if (isOpened) {
            if (doorParent.rotation.y > -90) {
                doorParent.rotation.y -= 200 * deltaTime;
            }
            for (int i = 0; i < 4; i += 2) {
                if (windowParent[i].rotation.y < 135) {
                    windowParent[i].rotation.y += 200 * deltaTime;
                }
                if (windowParent[i + 1].rotation.y > -(180 + 135)) {
                    windowParent[i + 1].rotation.y -= 200 * deltaTime;
                }
            }
            for (int i = 4; i < 8; i += 2) {
                if (windowParent[i].rotation.y > -135) {
                    windowParent[i].rotation.y -= 200 * deltaTime;
                }
                if (windowParent[i + 1].rotation.y < (180 + 135)) {
                    windowParent[i + 1].rotation.y += 200 * deltaTime;
                }
            }
        }
        else {
            if (doorParent.rotation.y < 0) {
                doorParent.rotation.y += 200 * deltaTime;
            }
            for (int i = 0; i < 4; i++) {
                if (windowParent[i].rotation.y > 0) {
                    windowParent[i].rotation.y -= 200 * deltaTime;
                }
                if (windowParent[i + 1].rotation.y < -180) {
                    windowParent[i + 1].rotation.y += 200 * deltaTime;
                }
            }
            for (int i = 4; i < 8; i++) {
                if (windowParent[i].rotation.y < 0) {
                    windowParent[i].rotation.y += 200 * deltaTime;
                }
                if (windowParent[i + 1].rotation.y > 180) {
                    windowParent[i + 1].rotation.y -= 200 * deltaTime;
                }
            }
        }

        center.draw(shader);
    }
};

#endif