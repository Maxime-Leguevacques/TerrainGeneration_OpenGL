#pragma once


#include <math.h>

#include "Float/float.hpp"



float DegToRad(float _deg);
float RadToDeg(float _rad);

// https://www.youtube.com/watch?v=NzjF1pdlK7Y&t=1042s for explanation and usage of Lerp, InvLerp and Remap
float Lerp(float a, float b, float t);
float InvLerp(float a, float b, float v);
float Remap(float iMin, float iMax, float oMin, float oMax, float value);

float Q_rsqrt0(float _number, int _mode);
float Q_rsqrt(float _number) noexcept;