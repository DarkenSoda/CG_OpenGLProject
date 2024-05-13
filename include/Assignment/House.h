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

    House() {
        Texture texture("../Textures/wall.jpg", GL_RGB);
        center.position = glm::vec3(0.0f, 1.5f, 0.0f);
        center.scale = glm::vec3(1.0f, 1.5f, 1.0f);
        float thickness = 0.1f;
        glm::vec4 wallColor2 = glm::vec4(0.5882, 0.4275, 0.2784, 1.0);
        glm::vec4 wallColor = glm::vec4(0.6863, 0.5373, 0.3098, 1.0);
        glm::vec4 roofColor = glm::vec4(0.6, 0.2, 0.2, 1.0);

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

        doorParent.position = glm::vec3(0.5f, -0.875f, 3.55f);
        doorParent.children.push_back(&door);

        door.position = glm::vec3(-0.5f, 0.0f, 0.0f);
        door.scale = glm::vec3(1.0f, 1.25f, thickness);

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

    void draw(Shader& shader) {
        center.draw(shader);
    }
};

#endif