#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/vector.hpp"
#include "headers/constraint.hpp"
#include "api.hpp"

const double framerate = 120;
const char window_title[] = "Rod";

Scene* setupScene() {
    Scene* scene = new Scene();

    CircleBody* circleA = new CircleBody(Vector2(300, 200), 20);
    CircleBody* circleB = new CircleBody(Vector2(400, 300), 20);

    DistanceConstraint* rod = new DistanceConstraint(circleA, circleB, 100.0);

    BoundedBoxBody* box = new BoundedBoxBody(Vector2(400, 300), 700, 500);
    scene->addBody(circleA);
    scene->addBody(circleB);
    scene->addBody(box);
    scene->addConstraint(rod);

    return scene;
}
