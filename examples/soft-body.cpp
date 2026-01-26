#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/constraint.hpp"
#include "api.hpp"

const double framerate = 240;
const char windowTitle[] = "Soft body";
const Vector2 windowSize(800, 600);

Scene* setupScene() {
    Scene* scene = new Scene();

    const int cols = 9;
    const int rows = 9;
    const float spacing = 26.0f;
    const float radius  = 4.5f;
    const Vector2 origin(291.5, 191.5);

    const float k_struct = 100.0f;
    const float k_shear  = 75.0f;
    const float k_bend   = 50.0f;
    const float damping  = 10.0f;

    Body* nodes[rows][cols];

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            Vector2 pos = origin + Vector2(x * spacing, y * spacing);
            CircleBody* body = new CircleBody(pos, radius);
            body->velocity = Vector2(0, 0);
            body->restitution = 0.5f;
            body->friction = 0.4f;
            body->mass = 1.0f;

            scene->addBody(body);
            nodes[y][x] = body;
        }
    }

    auto addSpring = [&](Body* a, Body* b, float rest, float k) {
        SpringConstraint* s = new SpringConstraint(a, b, rest, k);
        s->damping = damping;
        scene->addConstraint(s);
    };

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (x + 1 < cols) addSpring(nodes[y][x], nodes[y][x + 1], spacing, k_struct);
            if (y + 1 < rows) addSpring(nodes[y][x], nodes[y + 1][x], spacing, k_struct);
        }
    }

    float diag = spacing * std::sqrt(2.0f);
    for (int y = 0; y + 1 < rows; ++y) {
        for (int x = 0; x + 1 < cols; ++x) {
            addSpring(nodes[y][x], nodes[y + 1][x + 1], diag, k_shear);
            addSpring(nodes[y + 1][x], nodes[y][x + 1], diag, k_shear);
        }
    }

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (x + 2 < cols) addSpring(nodes[y][x], nodes[y][x + 2], spacing * 2, k_bend);
            if (y + 2 < rows) addSpring(nodes[y][x], nodes[y + 2][x], spacing * 2, k_bend);
        }
    }

    for (int y = 0; y + 2 < rows; ++y) {
        for (int x = 0; x + 2 < cols; ++x) {
            addSpring(nodes[y][x], nodes[y + 2][x + 2], spacing * std::sqrt(8.0f), k_bend);
            addSpring(nodes[y + 2][x], nodes[y][x + 2], spacing * std::sqrt(8.0f), k_bend);
        }
    }

    BoundedBoxBody* bb = new BoundedBoxBody(Vector2(400, 300), 700, 500);
    scene->addBody(bb);

    return scene;
}
