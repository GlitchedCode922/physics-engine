#pragma once
#include "headers/vector.hpp"
#include "headers/body.hpp"

class Constraint {
public:
    Body* bodyA;
    Body* bodyB;

    Constraint(Body* a, Body* b)
        : bodyA(a), bodyB(b) {}

    virtual void apply() = 0;
    virtual ~Constraint() {}
};

class SpringConstraint: public Constraint {
public:
    double restLength;
    double springConstant;
    double damping = 0.1;

    SpringConstraint(Body* a, Body* b, double restLength, double springConstant)
        : Constraint(a, b), restLength(restLength), springConstant(springConstant) {}

    void apply() override;
};

class DistanceConstraint: public Constraint {
public:
    double length;

    DistanceConstraint(Body* a, Body* b, double length): Constraint(a, b), length(length) {}

    void apply() override;
};
