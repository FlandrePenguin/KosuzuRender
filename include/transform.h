#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "geometry.h"

#include <cassert>
#include <cmath>
#include <iomanip>

class Matrix4x4 {
public:
    float m[4][4];
    Matrix4x4() {
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
        m[0][1] = m[0][2] = m[0][3] = 0.f;
        m[1][0] = m[1][2] = m[1][3] = 0.f;
        m[2][0] = m[2][1] = m[2][3] = 0.f;
        m[3][0] = m[3][1] = m[3][2] = 0.f;
    }
    Matrix4x4(float mat[4][4]) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = mat[i][j];
    }
    Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
    }
    Matrix4x4(const Matrix4x4& mat) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = mat.m[i][j];
    }
    Matrix4x4& operator=(const Matrix4x4& mat) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = mat.m[i][j];
        return *this;
    }

    Matrix4x4 operator+(const Matrix4x4& mat) const;
    Matrix4x4& operator+=(const Matrix4x4& mat);
    Matrix4x4 operator-(const Matrix4x4& mat) const;
    Matrix4x4& operator-=(const Matrix4x4& mat);
    Matrix4x4 operator*(const Matrix4x4& mat) const;
    Matrix4x4& operator*=(const Matrix4x4& mat);
    Matrix4x4 operator*(float s) const;
    Matrix4x4& operator*=(float s);
    Matrix4x4 operator/(float s) const;
    Matrix4x4& operator/=(float s);
    bool operator==(const Matrix4x4& mat);
    bool operator!=(const Matrix4x4& mat);
    Matrix4x4& transpose();
    Matrix4x4& inverse();
};

Matrix4x4 transpose(const Matrix4x4& mat);
Matrix4x4 inverse(const Matrix4x4& mat);
std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat);

class Transform {
public:
    Transform() {}
    Transform(float mat[4][4]) {
        m = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
                      mat[1][0], mat[1][1], mat[1][2], mat[1][3],
                      mat[2][0], mat[2][1], mat[2][2], mat[2][3],
                      mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
        m_inv = inverse(m);
    }
    Transform(const Matrix4x4& m) : m(m), m_inv(inverse(m)) {}
    Transform(const Matrix4x4& m, const Matrix4x4& m_inv) : m(m), m_inv(m_inv) {}

    Transform operator*(const Transform& t) const;
    template <typename T>
    Point3<T> operator()(const Point3<T>& p) const;
    template <typename T>
    Vector3<T> operator()(const Vector3<T>& v) const;
    bool operator==(const Transform& t);
    bool operator!=(const Transform& t);
    const Matrix4x4& getMatrix() const;
    const Matrix4x4& getInverseMatrix() const;

    friend Transform transpose(const Transform& t);
    friend Transform inverse(const Transform& t);
    friend std::ostream& operator<<(std::ostream& os, const Transform& t);

private:
    Matrix4x4 m, m_inv;
};

Transform scale(float sx, float sy, float sz);
Transform rotateX(float theta);
Transform rotateY(float theta);
Transform rotateZ(float theta);
Transform translate(const Vector3f& d);
Transform lookAt(const Point3f& pos, const Point3f& look, const Vector3f& up);
Transform perspective(float fov, float aspect, float near, float far);
Transform viewPort(int width, int height);

template <typename T>
Point3<T> Transform::operator()(const Point3<T>& p) const {
    T x = p.x, y = p.y, z = p.z;
    T xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
    T yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
    T zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
    T wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
    assert(wp != 0);
    if (wp == 1)
        return Point3<T>(xp, yp, zp);
    else
        return Point3<T>(xp, yp, zp) / wp;
}

template <typename T>
Vector3<T> Transform::operator()(const Vector3<T>& v) const {
    T x = v.x, y = v.y, z = v.z;
    T xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z;
    T yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z;
    T zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z;
    return Vector3<T>(xp, yp, zp);
}
#endif // TRANSFORM_H