#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "kosuzu.h"

#include <cassert>
#include <iomanip>

template <typename T>
inline bool isNaN(const T x) { return std::isnan(x); }

template <>
inline bool isNaN(const int x) { return false; }

template <typename T>
class Vector2 {
public:
    T x, y;
    Vector2() { x = y = 0; }
    Vector2(T x, T y) : x(x), y(y) { assert(!hasNaNs()); }
    Vector2(const Vector2<T>& v) {
        assert(!v.hasNaNs());
        x = v.x;
        y = v.y;
    }
    Vector2<T>& operator=(const Vector2<T>& v) {
        assert(!v.hasNaNs());
        x = v.x;
        y = v.y;
        return *this;
    }
    explicit Vector2(const Point2<T>& p);
    explicit Vector2(const Point3<T>& p);

    bool hasNaNs() const;
    Vector2<T> operator+(const Vector2<T>& v) const;
    Vector2<T>& operator+=(const Vector2<T>& v);
    Vector2<T> operator-(const Vector2<T>& v) const;
    Vector2<T>& operator-=(const Vector2<T>& v);
    Vector2<T> operator-(const Point2<T>& p) const;
    Vector2<T>& operator-=(const Point2<T>& p);
    template <typename U>
    Vector2<T> operator*(U s) const;
    template <typename U>
    Vector2<T>& operator*=(U s);
    template <typename U>
    Vector2<T> operator/(U s) const;
    template <typename U>
    Vector2<T>& operator/=(U s);
    bool operator==(const Vector2<T>& v) const;
    bool operator!=(const Vector2<T>& v) const;
    float lengthSquared() const;
    float length() const;
};

template <typename T>
Vector2<T>::Vector2(const Point2<T>& p) {
    assert(!p.hasNaNs());
    x = p.x;
    y = p.y;
}

template <typename T>
Vector2<T>::Vector2(const Point3<T>& p) {
    assert(!p.hasNaNs());
    x = p.x;
    y = p.y;
}

template <typename T>
bool Vector2<T>::hasNaNs() const {
    return isNaN(x) || isNaN(y);
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const {
    return Vector2<T>(x + v.x, y + v.y);
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& v) {
    assert(!v.hasNaNs());
    x += v.x;
    y += v.y;
    return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const {
    return Vector2<T>(x - v.x, y - v.y);
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& v) {
    assert(!v.hasNaNs());
    x -= v.x;
    y -= v.y;
    return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Point2<T>& p) const {
    return Vector2<T>(x - p.x, y - p.y);
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Point2<T>& p) {
    assert(!p.hasNaNs());
    x -= p.x;
    y -= p.y;
    return *this;
}

template <typename T>
template <typename U>
Vector2<T> Vector2<T>::operator*(U s) const {
    return Vector2<T>(s * x, s * y);
}

template <typename T>
template <typename U>
Vector2<T>& Vector2<T>::operator*=(U s) {
    assert(!isNaN(s));
    x *= s;
    y *= s;
    return *this;
}

template <typename T>
template <typename U>
Vector2<T> Vector2<T>::operator/(U s) const {
    assert(s != 0);
    float inv = (float)1 / s;
    return Vector2<T>(inv * x, inv * y);
}

template <typename T>
template <typename U>
Vector2<T>& Vector2<T>::operator/=(U s) {
    assert(s != 0);
    float inv = (float)1 / s;
    x *= inv;
    y *= inv;
    return *this;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& v) const {
    return x == v.x && y == v.y;
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& v) const {
    return x != v.x || y != v.y;
}

template <typename T>
float Vector2<T>::lengthSquared() const {
    return x * x + y * y;
}

template <typename T>
float Vector2<T>::length() const {
    return std::sqrt(lengthSquared());
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
    os << "[ " << v.x << ", " << v.y << " ]";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector2<float>& v) {
    os << std::setprecision(6) << "[ " << v.x << ", " << v.y << " ]";
    return os;
}

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;

template <typename T>
class Vector3 {
public:
    T x, y, z;
    Vector3() { x = y = z = 0; }
    Vector3(T x, T y, T z) : x(x), y(y), z(z) { assert(!hasNaNs()); }
    Vector3(const Vector3<T>& v) {
        assert(!v.hasNaNs());
        x = v.x;
        y = v.y;
        z = v.z;
    }
    Vector3<T>& operator=(const Vector3<T>& v) {
        assert(!v.hasNaNs());
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    explicit Vector3(const Point3<T>& p);

    bool hasNaNs() const;
    Vector3<T> operator+(const Vector3<T>& v) const;
    Vector3<T>& operator+=(const Vector3<T>& v);
    Vector3<T> operator-(const Vector3<T>& v) const;
    Vector3<T>& operator-=(const Vector3<T>& v);
    Vector3<T> operator-(const Point3<T>& p) const;
    Vector3<T>& operator-=(const Point3<T>& p);
    template <typename U>
    Vector3<T> operator*(U s) const;
    template <typename U>
    Vector3<T>& operator*=(U s);
    template <typename U>
    Vector3<T> operator/(U s) const;
    template <typename U>
    Vector3<T>& operator/=(U s);
    bool operator==(const Vector3<T>& v) const;
    bool operator!=(const Vector3<T>& v) const;
    float lengthSquared() const;
    float length() const;
};

template <typename T>
Vector3<T>::Vector3(const Point3<T>& p) {
    assert(!p.hasNaNs());
    x = p.x;
    y = p.y;
    z = p.z;
}

template <typename T>
bool Vector3<T>::hasNaNs() const {
    return isNaN(x) || isNaN(y) || isNaN(z);
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const {
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

template <typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& v) {
    assert(!v.hasNaNs());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const {
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& v) {
    assert(!v.hasNaNs());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Point3<T>& p) const {
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const Point3<T>& p) {
    assert(!p.hasNaNs());
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
}

template <typename T>
template <typename U>
Vector3<T> Vector3<T>::operator*(U s) const {
    return Vector2<T>(s * x, s * y, s * z);
}

template <typename T>
template <typename U>
Vector3<T>& Vector3<T>::operator*=(U s) {
    assert(!isNaN(s));
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

template <typename T>
template <typename U>
Vector3<T> Vector3<T>::operator/(U s) const {
    assert(s != 0);
    float inv = (float)1 / s;
    return Vector3<T>(inv * x, inv * y, inv * z);
}

template <typename T>
template <typename U>
Vector3<T>& Vector3<T>::operator/=(U s) {
    assert(s != 0);
    float inv = (float)1 / s;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

template <typename T>
bool Vector3<T>::operator==(const Vector3<T>& v) const {
    return x == v.x && y == v.y && z == v.z;
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T>& v) const {
    return x != v.x || y != v.y || z != v.z;
}

template <typename T>
float Vector3<T>::lengthSquared() const {
    return x * x + y * y + z * z;
}

template <typename T>
float Vector3<T>::length() const {
    return std::sqrt(lengthSquared());
}

template <typename T>
inline Vector3<T> normailize(const Vector3<T>& v) {
    return v / v.length();
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<float>& v) {
    os << std::setprecision(6) << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

template <typename T>
inline T dot(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y),
                      (v1z * v2x) - (v1x * v2z),
                      (v1x * v2y) - (v1y * v2x));
}

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;

template <typename T>
class Point2 {
public:
    T x, y;
    Point2() { x = y = 0; }
    Point2(T x, T y) : x(x), y(y) { assert(!hasNaNs()); }
    Point2(const Point2<T>& p) {
        assert(!p.hasNaNs());
        x = p.x;
        y = p.y;
    }
    Point2<T>& operator=(const Point2<T>& p) {
        assert(!p.hasNaNs());
        x = p.x;
        y = p.y;
        return *this;
    }

    bool hasNaNs() const;
    Point2<T> operator+(const Point2<T>& p) const;
    Point2<T>& operator+=(const Point2<T>& p);
    Point2<T> operator+(const Vector2<T>& v) const;
    Point2<T>& operator+=(const Vector2<T>& v);
    Point2<T> operator-(const Point2<T>& p) const;
    Point2<T>& operator-=(const Point2<T>& p);
    Vector2<T> operator-(const Vector2<T>& v) const;
    Point2<T>& operator-=(const Vector2<T>& v);
    template <typename U>
    Point2<T> operator*(U s) const;
    template <typename U>
    Point2<T>& operator*=(U s);
    template <typename U>
    Point2<T> operator/(U s) const;
    template <typename U>
    Point2<T>& operator/=(U s);
    bool operator==(const Point2<T>& p) const;
    bool operator!=(const Point2<T>& p) const;
};

template <typename T>
bool Point2<T>::hasNaNs() const {
    return isNaN(x) || isnan(y);
}

template <typename T>
Point2<T> Point2<T>::operator+(const Point2<T>& p) const {
    return Point2<T>(x + p.x, y + p.y);
}

template <typename T>
Point2<T>& Point2<T>::operator+=(const Point2<T>& p) {
    assert(!p.hasNaNs());
    x += p.x;
    y += p.y;
    return *this;
}

template <typename T>
Point2<T> Point2<T>::operator+(const Vector2<T>& v) const {
    return Point2<T>(x + v.x, y + v.y);
}

template <typename T>
Point2<T>& Point2<T>::operator+=(const Vector2<T>& v) {
    assert(!v.hasNaNs());
    x += v.x;
    y += v.y;
    return *this;
}

template <typename T>
Point2<T> Point2<T>::operator-(const Point2<T>& p) const {
    return Point2<T>(x - p.x, y - p.y);
}

template <typename T>
Point2<T>& Point2<T>::operator-=(const Point2<T>& p) {
    assert(!p.hasNaNs());
    x -= p.x;
    y -= p.y;
    return *this;
}

template <typename T>
Vector2<T> Point2<T>::operator-(const Vector2<T>& v) const {
    return Vector2<T>(x - v.x, y - v.y);
}

template <typename T>
Point2<T>& Point2<T>::operator-=(const Vector2<T>& v) {
    assert(!v.hasNaNs());
    x -= v.x;
    y -= v.y;
    return *this;
}

template <typename T>
template <typename U>
Point2<T> Point2<T>::operator*(U s) const {
    return Point2<T>(s * x, s * y);
}

template <typename T, typename U>
inline Point2<T> operator*(U s, const Point2<T>& p) {
    return p * s;
}

template <typename T>
template <typename U>
Point2<T>& Point2<T>::operator*=(U s) {
    assert(!isNaN(s));
    x *= s;
    y *= s;
    return *this;
}

template <typename T>
template <typename U>
Point2<T> Point2<T>::operator/(U s) const {
    assert(s != 0);
    float inv = (float)1 / s;
    return Point2<T>(inv * x, inv * y);
}

template <typename T>
template <typename U>
Point2<T>& Point2<T>::operator/=(U s) {
    assert(s != 0);
    float inv = (float)1 / s;
    x *= inv;
    y *= inv;
    return *this;
}

template <typename T>
bool Point2<T>::operator==(const Point2<T>& p) const {
    return x == p.x && y == p.y;
}

template <typename T>
bool Point2<T>::operator!=(const Point2<T>& p) const {
    return x != p.x || y != p.y;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Point2<T>& p) {
    os << "[ " << p.x << ", " << p.y << " ]";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Point2<float>& p) {
    os << std::setprecision(6) << "[ " << p.x << ", " << p.y << " ]";
    return os;
}

using Point2i = Point2<int>;
using Point2f = Point2<float>;

template <typename T>
class Point3 {
public:
    T x, y, z;
    Point3() { x = y = z = 0; }
    Point3(T x, T y, T z) : x(x), y(y), z(z) { assert(!hasNaNs()); }
    Point3(const Point3<T>& p) {
        assert(!p.hasNaNs());
        x = p.x;
        y = p.y;
        z = p.z;
    }
    Point3<T>& operator=(const Point3<T>& p) {
        assert(!p.hasNaNs());
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }

    bool hasNaNs() const;
    Point3<T> operator+(const Point3<T>& p) const;
    Point3<T>& operator+=(const Point3<T>& p);
    Point3<T> operator+(const Vector3<T>& v) const;
    Point3<T>& operator+=(const Vector3<T>& v);
    Vector3<T> operator-(const Point3<T>& p) const;
    Point3<T>& operator-=(const Point3<T>& p);
    Point3<T> operator-(const Vector3<T>& v) const;
    Point3<T>& operator-=(const Vector3<T>& v);
    template <typename U>
    Point3<T> operator*(U s) const;
    template <typename U>
    Point3<T>& operator*=(U s);
    template <typename U>
    Point3<T> operator/(U s) const;
    template <typename U>
    Point3<T>& operator/=(U s);
    bool operator==(const Point3<T>& p) const;
    bool operator!=(const Point3<T>& p) const;
};

template <typename T>
bool Point3<T>::hasNaNs() const {
    return isNaN(x) || isNaN(y) || isNaN(z);
}

template <typename T>
Point3<T> Point3<T>::operator+(const Point3<T>& p) const {
    return Point3<T>(x + p.x, y + p.y, z + p.z);
}

template <typename T>
Point3<T>& Point3<T>::operator+=(const Point3<T>& p) {
    assert(!p.hasNaNs());
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
}

template <typename T>
Point3<T> Point3<T>::operator+(const Vector3<T>& v) const {
    return Point3<T>(x + v.x, y + v.y, z + v.z);
}

template <typename T>
Point3<T>& Point3<T>::operator+=(const Vector3<T>& v) {
    assert(!v.hasNaNs());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <typename T>
Vector3<T> Point3<T>::operator-(const Point3<T>& p) const {
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
}

template <typename T>
Point3<T>& Point3<T>::operator-=(const Point3<T>& p) {
    assert(!p.hasNaNs());
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
}

template <typename T>
Point3<T> Point3<T>::operator-(const Vector3<T>& v) const {
    return Point3<T>(x - v.x, y - v.y, z - v.z);
}

template <typename T>
Point3<T>& Point3<T>::operator-=(const Vector3<T>& v) {
    assert(!v.hasNaNs());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template <typename T>
template <typename U>
Point3<T> Point3<T>::operator*(U s) const {
    return Point3<T>(s * x, s * y, s * z);
}

template <typename T, typename U>
inline Point3<T> operator*(U s, const Point3<T>& p) {
    return p * s;
}

template <typename T>
template <typename U>
Point3<T>& Point3<T>::operator*=(U s) {
    assert(!isNaN(s));
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

template <typename T>
template <typename U>
Point3<T> Point3<T>::operator/(U s) const {
    assert(s != 0);
    float inv = (float)1 / s;
    return Point3<T>(inv * x, inv * y, inv * z);
}

template <typename T>
template <typename U>
Point3<T>& Point3<T>::operator/=(U s) {
    assert(s != 0);
    float inv = (float)1 / s;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

template <typename T>
bool Point3<T>::operator==(const Point3<T>& p) const {
    return x == p.x && y == p.y && z == p.z;
}

template <typename T>
bool Point3<T>::operator!=(const Point3<T>& p) const {
    return x != p.x || y != p.y || z != p.z;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Point3<T>& p) {
    os << "[ " << p.x << ", " << p.y << ", " << p.z << " ]";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Point3<float>& p) {
    os << std::setprecision(6) << "[ " << p.x << ", " << p.y << ", " << p.z << " ]";
    return os;
}

using Point3i = Point3<int>;
using Point3f = Point3<float>;

template <typename T>
class Quaternion {
public:
    Vector3<T> im;
    T re;
    Quaternion() {
        re = 0;
        im = Vector3<T>();
    }
    Quaternion(Vector3<T> im) : re(0), im(im) { assert(!hasNaNs()); }
    Quaternion(T re, Vector3<T> im) : re(re), im(im) { assert(!hasNaNs()); }
    Quaternion(T x, T y, T z, T w) : im(x, y, z), re(w) { assert(!hasNaNs()); }
    Quaternion(const Quaternion<T>& q) {
        assert(!q.hasNaNs());
        re = q.re;
        im = q.im;
    }
    Quaternion<T>& operator=(const Quaternion<T>& q) {
        assert(!q.hasNaNs());
        re = q.re;
        im = q.im;
        return *this;
    }

    bool hasNaNs() const;
    Quaternion<T> operator+(const Quaternion<T>& q) const;
    Quaternion<T>& operator+=(const Quaternion<T>& q);
    Quaternion<T> operator-(const Quaternion<T>& q) const;
    Quaternion<T>& operator-=(const Quaternion<T>& q);
    template <typename U>
    Quaternion<T> operator*(U s) const;
    template <typename U>
    Quaternion<T>& operator*=(U s);
    template <typename U>
    Quaternion<T> operator/(U s) const;
    template <typename U>
    Quaternion<T>& operator/=(U s);
    bool operator==(const Quaternion<T>& q) const;
    bool operator!=(const Quaternion<T>& q) const;
    float lengthSquared() const;
    float length() const;
};

template <typename T>
bool Quaternion<T>::hasNaNs() const {
    return isNaN(re) || im.hasNaNs();
}

template <typename T>
Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& q) const {
    return Quaternion<T>(re + q.re, im + q.im);
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& q) {
    assert(!q.hasNaNs());
    re += q.re;
    im += q.im;
    return *this;
}

template <typename T>
Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& q) const {
    return Quaternion<T>(re - q.re, im - q.im);
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& q) {
    assert(!q.hasNaNs());
    re -= q.re;
    im -= q.im;
    return *this;
}

template <typename T>
template <typename U>
Quaternion<T> Quaternion<T>::operator*(U s) const {
    return Quaternion<T>(s * re, s * im);
}

template <typename T, typename U>
inline Quaternion<T> operator*(U s, const Quaternion<T>& q) {
    return q * s;
}

template <typename T>
template <typename U>
Quaternion<T>& Quaternion<T>::operator*=(U s) {
    assert(!isNaN(s));
    re *= s;
    im *= s;
    return *this;
}

template <typename T>
template <typename U>
Quaternion<T> Quaternion<T>::operator/(U s) const {
    assert(s != 0);
    float inv = (float)1 / s;
    return Quaternion<T>(inv * re, inv * im);
}

template <typename T>
template <typename U>
Quaternion<T>& Quaternion<T>::operator/=(U s) {
    assert(s != 0);
    float inv = (float)1 / s;
    re *= inv;
    im *= inv;
    return *this;
}

template <typename T>
bool Quaternion<T>::operator==(const Quaternion<T>& q) const {
    return re == q.re && im == q.im;
}

template <typename T>
bool Quaternion<T>::operator!=(const Quaternion<T>& q) const {
    return re != q.re || im != q.im;
}

template <typename T>
float Quaternion<T>::lengthSquared() const {
    return re * re + im.lengthSquared();
}

template <typename T>
float Quaternion<T>::length() const {
    return std::sqrt(lengthSquared());
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q) {
    os << "[ " << q.re << ", " << q.im.x << ", " << q.im.y << ", " << q.im.z << " ]";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Quaternion<float>& q) {
    os << std::setprecision(6) << "[ " << q.re << ", " << q.im.x << ", " << q.im.y << ", " << q.im.z << " ]";
    return os;
}

template <typename T>
inline Quaternion<T> grabmann(const Quaternion<T>& q1, const Quaternion<T>& q2) {
    return Quaternion<T>(q1.re * q2.re - dot(q1.im, q2.im), q1.re * q2.im + q2.re * q1.im - cross(q1.im, q2.im));
}
#endif // GEOMETRY_H