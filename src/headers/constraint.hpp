#pragma once
#include "vector.hpp"
#include "body.hpp"

class Constraint {
public:
    Body* bodyA;
    Body* bodyB;

    Constraint(Body* a, Body* b)
        : bodyA(a), bodyB(b) {}

    virtual void apply() = 0;
};

class SpringConstraint : public Constraint {
public:
    double restLength;
    double springConstant;
    double damping = 0.1;

    SpringConstraint(Body* a, Body* b, double restLength, double springConstant)
        : Constraint(a, b), restLength(restLength), springConstant(springConstant) {}

    void apply() override;
};
