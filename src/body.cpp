#include "headers/body.hpp"
#include "headers/vector.hpp"

void Body::applyForce(const Vector2& force) {
    acceleration += force / mass;
}

void Body::update(double deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    acceleration = Vector2(0, 0); // Reset acceleration after each update
}

void Body::resolveCollision(Body* other) {
    Vector2 normal = other->position - position;
    double n_len = normal.length();
    normal = normal.normalize();
    if (n_len >= radius + other->radius) return;
    double overlap = radius + other->radius - n_len;
    position -= normal * overlap / 2;
    other->position += normal * overlap / 2;
    double e = (restitution + other->restitution) / 2;
    double vn = (velocity - other->velocity).dot(normal);
    double impulse = -(1 + e) * vn / (1 / mass + 1 / other->mass);
    velocity += normal * (impulse / mass);
    other->velocity -= normal * (impulse / other->mass);
}
