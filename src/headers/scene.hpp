#pragma once
#include "vector.hpp"
#include "body.hpp"
#include "staticbody.hpp"
#include <vector>

class Scene {
public:
    Vector2 gravity = Vector2(0, 327);
    std::vector<Body*> bodies;
    std::vector<StaticBody*> staticBodies;
    int collisionIterations = 10;

    void addBody(Body *body);
    void removeBody(Body *body);
    void addStaticBody(StaticBody *staticBody);
    void removeStaticBody(StaticBody *staticBody);
    void update(double dt);

};
