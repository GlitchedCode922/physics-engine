#pragma once
#include "headers/vector.hpp"

class Body {
public:
    Vector2 velocity = Vector2(0, 0);
    Vector2 position;
    Vector2 acceleration = Vector2(0, 0);
    double restitution = 0.8;
    double friction = 1;
    double mass = 1;
    bool isStatic = false;

    Body(const Vector2& pos): position(pos) {}

    virtual void update(double deltaTime) = 0;
    virtual void applyForce(const Vector2& force) = 0;
    virtual void resolveCollision(Body* other) = 0;
    virtual ~Body() {}
};

class CircleBody : public Body {
public:
    double radius;

    CircleBody(const Vector2& pos, double r): Body(pos), radius(r) {}

    void update(double deltaTime) override;
    void applyForce(const Vector2& force) override;
    void resolveCollision(Body* other) override;
};

class BoundedBoxBody : public Body {
public:
    double width;
    double height;

    BoundedBoxBody(const Vector2& pos, double w, double h): Body(pos), width(w), height(h) {
        isStatic = true;
    }

    BoundedBoxBody(): Body(Vector2(0, 0)), width(0), height(0) {
        isStatic = true;
    }

    void update(double deltaTime) override;
    void applyForce(const Vector2& force) override;
    void resolveCollision(Body* other) override;
};
