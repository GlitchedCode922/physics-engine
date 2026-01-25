#pragma once
#include "headers/vector.hpp"
#include "headers/body.hpp"
#include "headers/constraint.hpp"
#include <vector>

class Scene {
public:
    Vector2 gravity = Vector2(0, 327);
    std::vector<Body*> bodies;
    std::vector<Constraint*> constraints;
    int collisionIterations = 10;

    void addBody(Body* body);
    void removeBody(Body* body);
    void addConstraint(Constraint* constraint);
    void removeConstraint(Constraint* constraint);
    void update(double dt);
};
