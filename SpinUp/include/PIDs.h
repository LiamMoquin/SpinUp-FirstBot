#pragma once
using namespace vex;
#include "vex.h"

void mtrReset(void);
void driveStraighti(float dist, float vi, float vf, float rUpDist);
void driveStraightc(float endDistPerc);
void driveStraightf(float vf,float endDistPerc);
void turnPD(float targetHead);