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
