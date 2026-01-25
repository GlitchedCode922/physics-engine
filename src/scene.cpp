#include "headers/scene.hpp"
#include <algorithm>

void Scene::addBody(Body *body) {
    bodies.push_back(body);
}

void Scene::removeBody(Body *body) {
    bodies.erase(std::remove(bodies.begin(), bodies.end(), body), bodies.end());
}

void Scene::addConstraint(Constraint *constraint) {
    constraints.push_back(constraint);
}

void Scene::removeConstraint(Constraint *constraint) {
    constraints.erase(std::remove(constraints.begin(), constraints.end(), constraint), constraints.end());
}

void Scene::update(double dt) {
    Body* body;
    for (int i = 0; i < bodies.size(); i++) {
        body = bodies[i];
        body->applyForce(gravity * body->mass);
        body->update(dt);
    }
    for (int i = 0; i < constraints.size(); i++) {
        Constraint* constraint = constraints[i];
        constraint->apply();
    }
    for (int i = 0; i < collisionIterations; i++) {
        for (int j = 0; j < bodies.size(); j++) {
            body = bodies[j];
            for (int k = j + 1; k < bodies.size(); k++) {
                Body* otherBody = bodies[k];
                body->resolveCollision(otherBody);
            }
        }
    }
}
