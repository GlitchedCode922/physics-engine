#pragma once
#include "vector.hpp"
#include "body.hpp"
#include <algorithm>

inline double clamp(double value, double min, double max) {
    return std::max(min, std::min(max, value));
}

class StaticBody {
public:
    Vector2 position;

    virtual void resolveCollision(Body& body) = 0;
};

class StaticBoundedBox : public StaticBody {
public:
    double width;
    double height;
    double rotation = 0.0;

    StaticBoundedBox(const Vector2& pos, double w, double h) {
        position = pos;
        width = w;
        height = h;
    }

    void resolveCollision(Body& body) override;
};