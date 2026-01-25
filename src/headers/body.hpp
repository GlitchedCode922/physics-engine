#pragma once
#include "headers/vector.hpp"

class Body {
public:
    Vector2 velocity = Vector2(0, 0);
    Vector2 position;
    Vector2 acceleration = Vector2(0, 0);
    double radius = 10;
    double restitution = 0.8;
    double friction = 1;
    double mass = 1;

    Body(const Vector2& pos, double r): position(pos), radius(r) {}

    void update(double deltaTime);
    void applyForce(const Vector2& force);
    void resolveCollision(Body* other);
};
