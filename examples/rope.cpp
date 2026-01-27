#include "headers/scene.hpp"
#include "headers/body.hpp"
#include "headers/vector.hpp"
#include "headers/constraint.hpp"
#include "common/api.hpp"

const double framerate = 240;
const char windowTitle[] = "Rope";
const Vector2 windowSize(800, 600);

Scene* setupScene() {
    Scene* scene = new Scene();

    // Create the bodies
    CircleBody* circleA = new CircleBody(Vector2(300, 200), 20);
    CircleBody* circleB = new CircleBody(Vector2(400, 300), 20);
    scene->addBody(circleA);
    scene->addBody(circleB);
    Body* prevBody = circleA;
    const int numSegments = 20;
    const double segmentLength = 5.0;
    for (int i = 1; i <= numSegments; ++i) {
        CircleBody* segment = new CircleBody(Vector2(300 + i * segmentLength, 200), 1);
        scene->addBody(segment);
        DistanceConstraint* c = new DistanceConstraint(prevBody, segment, segmentLength);
        scene->addConstraint(c);
        prevBody = segment;
    }
    DistanceConstraint* endConstraint = new DistanceConstraint(prevBody, circleB, segmentLength);
    scene->addConstraint(endConstraint);

    BoundedBoxBody* bb = new BoundedBoxBody(Vector2(400, 300), 700, 500);
    scene->addBody(bb);

    return scene;
}
