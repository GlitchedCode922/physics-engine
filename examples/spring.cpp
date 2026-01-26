#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/constraint.hpp"
#include "api.hpp"

const double framerate = 120;
const char windowTitle[] = "Spring";
const Vector2 windowSize(800, 600);

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
    CircleBody* body3 = new CircleBody(Vector2(244, 170), 20);
    body3->velocity = Vector2(150, 100);
    body3->restitution = 0;
    body3->friction = 1;
    body3->mass = 1;
    scene->addBody(body3);
    CircleBody* body4 = new CircleBody(Vector2(275, 135), 20);
    body4->velocity = Vector2(150, 100);
    body4->restitution = 0;
    body4->friction = 1;
    body4->mass = 1;
    scene->addBody(body4);
    SpringConstraint* sc = new SpringConstraint(body, body2, 150, 50);
    sc->damping = 1;
    scene->addConstraint(sc);
    SpringConstraint* sc2 = new SpringConstraint(body3, body4, 150, 50);
    sc2->damping = 1;
    scene->addConstraint(sc2);
    BoundedBoxBody* bb = new BoundedBoxBody(Vector2(400, 300), 700, 500);
    scene->addBody(bb);
    return scene;
}
