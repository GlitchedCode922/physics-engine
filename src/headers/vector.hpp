#pragma once
#include <cmath>

class Vector2 {
public:
    double x, y;

    Vector2(double x = 0, double y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);
    }
    Vector2 operator/(const Vector2& other) const {
        return Vector2(x / other.x, y / other.y);
    }
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }
    Vector2 operator+(double scalar) const {
        return Vector2(x + scalar, y + scalar);
    }
    Vector2 operator-(double scalar) const {
        return Vector2(x - scalar, y - scalar);
    }
    Vector2 operator*(double scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2 operator/(double scalar) const {
        return Vector2(x / scalar, y / scalar);
    }
    Vector2 operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2 operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2 operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vector2 operator/=(const Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }
    Vector2 operator+=(double scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }
    Vector2 operator-=(double scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }
    Vector2 operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2 operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    double length() const {
        return std::sqrt(x * x + y * y);
    }
    double cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }
    double dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
};
