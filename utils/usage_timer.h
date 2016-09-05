#pragma once

#ifndef USAGE_TIMER_H
#define USAGE_TIMER_H

class UsageTimer {
public:
    UsageTimer();

    struct Result {
        double wall;
        double user;
        double system;
    };

    Result Mark() const;

    static double Now();

private:
    static Result Sample();

    const Result start_;
}; // UsageTimer

#endif // USAGE_TIMER_H
