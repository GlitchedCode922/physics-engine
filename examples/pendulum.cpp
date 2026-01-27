#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/vector.hpp"
#include "headers/constraint.hpp"
#include "common/api.hpp"

const double framerate = 120;
const char windowTitle[] = "Pendulum";
const Vector2 windowSize(800, 600);

Scene* setupScene() {
    Scene* scene = new Scene();

    CircleBody* circleA = new CircleBody(Vector2(300, 200), 20);
    CircleBody* circleB = new CircleBody(Vector2(400, 300), 20);
    circleB->isStatic = true;

    DistanceConstraint* c = new DistanceConstraint(circleA, circleB, 100.0);

    scene->addBody(circleA);
    scene->addBody(circleB);
    scene->addConstraint(c);

    return scene;
}
