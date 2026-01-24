#include "headers/scene.hpp"

void Scene::addBody(Body *body) {
    bodies.push_back(body);
}

void Scene::removeBody(Body *body) {
    bodies.erase(std::remove(bodies.begin(), bodies.end(), body), bodies.end());
}

void Scene::addStaticBody(StaticBody *staticBody) {
    staticBodies.push_back(staticBody);
}

void Scene::removeStaticBody(StaticBody *staticBody) {
    staticBodies.erase(std::remove(staticBodies.begin(), staticBodies.end(), staticBody), staticBodies.end());
}

void Scene::update(double dt) {
    for (int i = 0; i < bodies.size(); i++) {
        Body *body = bodies[i];
        body->applyForce(gravity * body->mass);
        body->update(dt);

        for (int j = 0; j < staticBodies.size(); j++) {
            StaticBody *staticBody = staticBodies[j];
            staticBody->resolveCollision(*body);
        }
    }
}
