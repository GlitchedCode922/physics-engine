#include "headers/constraint.hpp"

void SpringConstraint::apply() {
    Vector2 diff = bodyB->position - bodyA->position;
    double distance = diff.length();
    Vector2 normal = diff / distance;
    double displacement = distance - restLength;

    double v_rel = (bodyB->velocity - bodyA->velocity).dot(normal);

    Vector2 force = normal * springConstant * displacement + normal * damping * v_rel;
    bodyA->applyForce(force);
    bodyB->applyForce(-force);
}
