#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/vector.hpp"
#include "api.hpp"

const double framerate = 60;
const char window_title[] = "Bouncing Ball";

Scene* setupScene() {
    Scene* scene = new Scene();
    scene->gravity = Vector2(0, 0);
    Body* body = new Body(Vector2(400, 300), 20);
    body->velocity = Vector2(400, 400);
    body->restitution = 1;
    body->friction = 1;
    body->mass = 2;
    scene->addBody(body);
    StaticBoundedBox* bb = new StaticBoundedBox(Vector2(400, 300), 700, 500);
    scene->addStaticBody(bb);
    return scene;
}
