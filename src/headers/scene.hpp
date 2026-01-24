#pragma once
#include "vector.hpp"
#include "body.hpp"
#include "staticbody.hpp"
#include "constraint.hpp"
#include <vector>

class Scene {
public:
    Vector2 gravity = Vector2(0, 327);
    std::vector<Body*> bodies;
    std::vector<StaticBody*> staticBodies;
    std::vector<Constraint*> constraints;
    int collisionIterations = 10;

    void addBody(Body* body);
    void removeBody(Body* body);
    void addStaticBody(StaticBody* staticBody);
    void removeStaticBody(StaticBody* staticBody);
    void addConstraint(Constraint* constraint);
    void removeConstraint(Constraint* constraint);
    void update(double dt);

};
