#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/constraint.hpp"
#include "api.hpp"

const double framerate = 120;
const char window_title[] = "Spring";

Scene* setupScene() {
    Scene* scene = new Scene();
    scene->gravity = Vector2(0, 0);
    CircleBody* body = new CircleBody(Vector2(200, 150), 20);
    body->velocity = Vector2(150, 100);
    body->restitution = 0;
    body->friction = 1;
    body->mass = 1;
    scene->addBody(body);
    CircleBody* body2 = new CircleBody(Vector2(600, 450), 30);
    body2->velocity = Vector2(-100, -150);
    body2->restitution = 0;
    body2->friction = 1;
    body2->mass = 1;
    scene->addBody(body2);
    SpringConstraint* sc = new SpringConstraint(body, body2, 150, 50);
    sc->damping = 1;
    scene->addConstraint(sc);
    BoundedBoxBody* bb = new BoundedBoxBody(Vector2(400, 300), 700, 500);
    scene->addBody(bb);
    return scene;
}
