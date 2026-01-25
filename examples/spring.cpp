#include "headers/scene.hpp"
#include "headers/staticbody.hpp"
#include "headers/body.hpp"
#include "headers/constraint.hpp"
#include "api.hpp"

const double framerate = 120;
const char window_title[] = "Spring";

Scene* setupScene() {
    Scene* scene = new Scene();
    scene->gravity = Vector2(0, 0);
    Body* body = new Body(Vector2(200, 150), 20);
    body->velocity = Vector2(150, 100);
    body->restitution = 0;
    body->friction = 1;
    body->mass = 1;
    scene->addBody(body);
    Body* body2 = new Body(Vector2(600, 450), 30);
    body2->velocity = Vector2(-100, -150);
    body2->restitution = 0;
    body2->friction = 1;
    body2->mass = 1;
    scene->addBody(body2);
    SpringConstraint* sc = new SpringConstraint(body, body2, 150, 50);
    sc->damping = 1;
    scene->addConstraint(sc);
    StaticBoundedBox* bb = new StaticBoundedBox(Vector2(400, 300), 700, 500);
    scene->addStaticBody(bb);
    return scene;
}
