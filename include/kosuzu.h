#ifndef KOSUZU_H
#define KOSUZU_H

#include <algorithm>
#include <cmath>
#include <limits>

template <typename T>
class Vector2;
template <typename T>
class Vector3;
template <typename T>
class Point2;
template <typename T>
class Point3;
class Matrix4x4;
class Transform;

static constexpr float MIN_FLOAT = -std::numeric_limits<float>::max();
static constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
static constexpr float PI = 3.14159265358979323846264f;

inline float degreeToRadian(float degree) {
    return (float)(degree * PI / 180.);
}
#endif // KOSUZU_H