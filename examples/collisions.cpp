#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/vector.hpp"
#include "api.hpp"

const double framerate = 120;
const char window_title[] = "Collisions";

Scene* setupScene() {
    Scene* scene = new Scene();
    for (int i = 0; i < 50; ++i) {
        CircleBody* body = new CircleBody(Vector2(i * 20, i * 25), i % 20 + 5);
        body->velocity = Vector2((-5 + i * 20) % 24000, (20 + i * 18) % 24000);
        body->restitution = 0.8;
        body->friction = 1;
        body->mass = pow(i % 20 + 5, 2) / 400;
        scene->addBody(body);
    }
    BoundedBoxBody* bb = new BoundedBoxBody(Vector2(400, 300), 700, 500);
    scene->addBody(bb);
    return scene;
}
