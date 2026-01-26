#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/vector.hpp"
#include "api.hpp"

const double framerate = 60;
const char windowTitle[] = "Bouncing Ball";
const Vector2 windowSize(800, 600);

Scene* setupScene() {
    Scene* scene = new Scene();
    scene->gravity = Vector2(0, 0);
    CircleBody* ball = new CircleBody(Vector2(400, 300), 20);
    ball->velocity = Vector2(400, 400);
    ball->restitution = 1;
    ball->friction = 1;
    ball->mass = 2;
    scene->addBody(ball);
    BoundedBoxBody* bb = new BoundedBoxBody(Vector2(400, 300), 700, 500);
    scene->addBody(bb);
    return scene;
}
