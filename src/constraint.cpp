#include "headers/constraint.hpp"
#include "headers/body.hpp"
#include "headers/vector.hpp"

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

void DistanceConstraint::apply() {
    Vector2 normal = bodyB->position - bodyA->position;
    double distance = normal.length();
    if (distance == 0.0) return; // avoid division by zero
    normal = normal / distance;

    double position_error = distance - length;
    if (bodyA->isStatic || bodyB->isStatic) {
        Body* dynamicBody = bodyA->isStatic ? bodyB : bodyA;
        dynamicBody->position -= normal * position_error * (bodyA->isStatic ? 1 : -1);
    } else {
        bodyA->position += normal * (position_error / 2.0);
        bodyB->position -= normal * (position_error / 2.0);
    }

    Vector2 relativeVelocity = bodyB->velocity - bodyA->velocity;
    double velAlongNormal = relativeVelocity.dot(normal);

    double invMassA = bodyA->isStatic ? 0.0 : 1.0 / bodyA->mass;
    double invMassB = bodyB->isStatic ? 0.0 : 1.0 / bodyB->mass;
    double effectiveMass = invMassA + invMassB;
    if (effectiveMass == 0.0) return;

    double j = -velAlongNormal / effectiveMass;
    Vector2 impulse = normal * j;

    if (!bodyA->isStatic) bodyA->velocity -= impulse * invMassA;
    if (!bodyB->isStatic) bodyB->velocity += impulse * invMassB;
}

