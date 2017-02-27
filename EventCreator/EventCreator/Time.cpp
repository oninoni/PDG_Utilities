#include "stdafx.h"

#include "Time.h"

const double Time::SECOND = 1;
double Time::delta = 0;

double Time::getTime() {
    return glfwGetTime();
}

double Time::getDelta() {
    return delta;
}

void Time::setDelta(double delta) {
    Time::delta = delta;
}
