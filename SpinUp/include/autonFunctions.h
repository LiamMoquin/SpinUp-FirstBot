#pragma once
using namespace vex;
#include "vex.h"
#include "PIDs.h"

void visionStrafe(float speed);
void trigMove(float distx, float disty, float vi, float vf, float rUpDist);
void driveTime(float seconds, float speed);
void driveInches(float dist, float speed);