#include "headers/staticbody.hpp"
#include "headers/vector.hpp"
#include <cmath>
#include <algorithm>

void StaticBoundedBox::resolveCollision(Body &body) {
    Vector2 min(position.x - width / 2, position.y - height / 2);
    Vector2 max(position.x + width / 2, position.y + height / 2);

    if (body.position.x - body.radius < min.x) {
        body.position.x = min.x + body.radius;
        body.velocity.x *= -body.restitution;
        body.velocity.y *= body.friction;
    }
    if (body.position.x + body.radius > max.x) {
        body.position.x = max.x - body.radius;
        body.velocity.x *= -body.restitution;
        body.velocity.y *= body.friction;
    }

    if (body.position.y - body.radius < min.y) {
        body.position.y = min.y + body.radius;
        body.velocity.y *= -body.restitution;
        body.velocity.x *= body.friction;
    }
    if (body.position.y + body.radius > max.y) {
        body.position.y = max.y - body.radius;
        body.velocity.y *= -body.restitution;
        body.velocity.x *= body.friction;
    }
}

