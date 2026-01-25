#include "headers/body.hpp"
#include "headers/vector.hpp"

void CircleBody::applyForce(const Vector2& force) {
    if (!isStatic) acceleration += force / mass;
}

void CircleBody::update(double deltaTime) {
    if (!isStatic) velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    acceleration = Vector2(0, 0); // Reset acceleration after each update
}

void resolveCirclesCollision(CircleBody* a, CircleBody* b) {
    Vector2 normal = b->position - a->position;
    double n_len = normal.length();
    normal = normal.normalize();
    if (n_len >= a->radius + b->radius) return; // No collision
    double overlap = a->radius + b->radius - n_len;
    a->position -= normal * overlap / 2;
    b->position += normal * overlap / 2;
    double e = (a->restitution + b->restitution) / 2;
    double vn = (a->velocity - b->velocity).dot(normal);
    double impulse = -(1 + e) * vn / (1 / a->mass + 1 / b->mass);
    a->velocity += normal * (impulse / a->mass);
    b->velocity -= normal * (impulse / b->mass);
}

void resolveStaticCirclesCollision(CircleBody* a, CircleBody* b) {
    CircleBody* staticCircle = a->isStatic ? a : b;
    CircleBody* dynamicCircle = a->isStatic ? b : a;
    Vector2 normal = dynamicCircle->position - staticCircle->position;
    double n_len = normal.length();
    normal = normal.normalize();
    if (n_len >= staticCircle->radius + dynamicCircle->radius) return; // No collision
    double overlap = staticCircle->radius + dynamicCircle->radius - n_len;
    dynamicCircle->position += normal * overlap;
    double e = (staticCircle->restitution + dynamicCircle->restitution) / 2;
    double vn = (dynamicCircle->velocity - staticCircle->velocity).dot(normal);
    double impulse = -(1 + e) * vn / (1 / dynamicCircle->mass);
    dynamicCircle->velocity += normal * (impulse / dynamicCircle->mass);
}

void resolveBoundedBoxCircleCollision(BoundedBoxBody* box, CircleBody* circle) {
    Vector2 min(box->position.x - box->width / 2, box->position.y - box->height / 2);
    Vector2 max(box->position.x + box->width / 2, box->position.y + box->height / 2);

    if (circle->position.x - circle->radius < min.x) {
        circle->position.x = min.x + circle->radius;
        circle->velocity.x *= -circle->restitution;
        circle->velocity.y *= circle->friction;
    }
    if (circle->position.x + circle->radius > max.x) {
        circle->position.x = max.x - circle->radius;
        circle->velocity.x *= -circle->restitution;
        circle->velocity.y *= circle->friction;
    }

    if (circle->position.y - circle->radius < min.y) {
        circle->position.y = min.y + circle->radius;
        circle->velocity.y *= -circle->restitution;
        circle->velocity.x *= circle->friction;
    }
    if (circle->position.y + circle->radius > max.y) {
        circle->position.y = max.y - circle->radius;
        circle->velocity.y *= -circle->restitution;
        circle->velocity.x *= circle->friction;
    }
}

void CircleBody::resolveCollision(Body* other) {
    if (isStatic && other->isStatic) return;
    if (dynamic_cast<CircleBody*>(other) && !isStatic && !other->isStatic) {
        resolveCirclesCollision(this, dynamic_cast<CircleBody*>(other));
        return;
    }
    if (dynamic_cast<CircleBody*>(other) && (isStatic || other->isStatic)) {
        resolveStaticCirclesCollision(this, dynamic_cast<CircleBody*>(other));
        return;
    }
    if (dynamic_cast<BoundedBoxBody*>(other) && !isStatic && other->isStatic) {
        resolveBoundedBoxCircleCollision(dynamic_cast<BoundedBoxBody*>(other), this);
        return;
    }
}

void BoundedBoxBody::applyForce(const Vector2& force) {
    return;
}

void BoundedBoxBody::update(double deltaTime) {
    return;
}

void BoundedBoxBody::resolveCollision(Body* other) {
    if (!isStatic) return;
    if (dynamic_cast<CircleBody*>(other) && !other->isStatic) {
        resolveBoundedBoxCircleCollision(this, dynamic_cast<CircleBody*>(other));
        return;
    }
}
