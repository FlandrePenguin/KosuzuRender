#include "transform.h"
#include <iomanip>
#include <iostream>

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const {
    return Matrix4x4(m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2], m[0][3] + mat.m[0][3],
                     m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2], m[1][3] + mat.m[1][3],
                     m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2], m[2][3] + mat.m[2][3],
                     m[3][0] + mat.m[3][0], m[3][1] + mat.m[3][1], m[3][2] + mat.m[3][2], m[3][3] + mat.m[3][3]);
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& mat) {
    m[0][0] += mat.m[0][0];
    m[0][1] += mat.m[0][1];
    m[0][2] += mat.m[0][2];
    m[0][3] += mat.m[0][3];
    m[1][0] += mat.m[1][0];
    m[1][1] += mat.m[1][1];
    m[1][2] += mat.m[1][2];
    m[1][3] += mat.m[1][3];
    m[2][0] += mat.m[2][0];
    m[2][1] += mat.m[2][1];
    m[2][2] += mat.m[2][2];
    m[2][3] += mat.m[2][3];
    m[3][0] += mat.m[3][0];
    m[3][1] += mat.m[3][1];
    m[3][2] += mat.m[3][2];
    m[3][3] += mat.m[3][3];
    return *this;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const {
    return Matrix4x4(m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1], m[0][2] - mat.m[0][2], m[0][3] - mat.m[0][3],
                     m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1], m[1][2] - mat.m[1][2], m[1][3] - mat.m[1][3],
                     m[2][0] - mat.m[2][0], m[2][1] - mat.m[2][1], m[2][2] - mat.m[2][2], m[2][3] - mat.m[2][3],
                     m[3][0] - mat.m[3][0], m[3][1] - mat.m[3][1], m[3][2] - mat.m[3][2], m[3][3] - mat.m[3][3]);
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& mat) {
    m[0][0] -= mat.m[0][0];
    m[0][1] -= mat.m[0][1];
    m[0][2] -= mat.m[0][2];
    m[0][3] -= mat.m[0][3];
    m[1][0] -= mat.m[1][0];
    m[1][1] -= mat.m[1][1];
    m[1][2] -= mat.m[1][2];
    m[1][3] -= mat.m[1][3];
    m[2][0] -= mat.m[2][0];
    m[2][1] -= mat.m[2][1];
    m[2][2] -= mat.m[2][2];
    m[2][3] -= mat.m[2][3];
    m[3][0] -= mat.m[3][0];
    m[3][1] -= mat.m[3][1];
    m[3][2] -= mat.m[3][2];
    m[3][3] -= mat.m[3][3];
    return *this;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const {
    Matrix4x4 mul;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            mul.m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j] + m[i][2] * mat.m[2][j] + m[i][3] * mat.m[3][j];
    }
    return mul;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& mat) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j] + m[i][2] * mat.m[2][j] + m[i][3] * mat.m[3][j];
    }
    return *this;
}

Matrix4x4 Matrix4x4::operator*(float s) const {
    return Matrix4x4(s * m[0][0], s * m[0][1], s * m[0][2], s * m[0][3],
                     s * m[1][0], s * m[1][1], s * m[1][2], s * m[1][3],
                     s * m[2][0], s * m[2][1], s * m[2][2], s * m[2][3],
                     s * m[3][0], s * m[3][1], s * m[3][2], s * m[3][3]);
}

Matrix4x4 operator*(float s, const Matrix4x4& mat) {
    return mat * s;
}

Matrix4x4& Matrix4x4::operator*=(float s) {
    m[0][0] *= s;
    m[0][1] *= s;
    m[0][2] *= s;
    m[0][3] *= s;
    m[1][0] *= s;
    m[1][1] *= s;
    m[1][2] *= s;
    m[1][3] *= s;
    m[2][0] *= s;
    m[2][1] *= s;
    m[2][2] *= s;
    m[2][3] *= s;
    m[3][0] *= s;
    m[3][1] *= s;
    m[3][2] *= s;
    m[3][3] *= s;
    return *this;
}

Matrix4x4 Matrix4x4::operator/(float s) const {
    assert(s != 0);
    float inv = 1 / s;
    return Matrix4x4(inv * m[0][0], inv * m[0][1], inv * m[0][2], inv * m[0][3],
                     inv * m[1][0], inv * m[1][1], inv * m[1][2], inv * m[1][3],
                     inv * m[2][0], inv * m[2][1], inv * m[2][2], inv * m[2][3],
                     inv * m[3][0], inv * m[3][1], inv * m[3][2], inv * m[3][3]);
}

Matrix4x4& Matrix4x4::operator/=(float s) {
    assert(s != 0);
    float inv = 1 / s;
    m[0][0] *= inv;
    m[0][1] *= inv;
    m[0][2] *= inv;
    m[0][3] *= inv;
    m[1][0] *= inv;
    m[1][1] *= inv;
    m[1][2] *= inv;
    m[1][3] *= inv;
    m[2][0] *= inv;
    m[2][1] *= inv;
    m[2][2] *= inv;
    m[2][3] *= inv;
    m[3][0] *= inv;
    m[3][1] *= inv;
    m[3][2] *= inv;
    m[3][3] *= inv;
    return *this;
}

bool Matrix4x4::operator==(const Matrix4x4& mat) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (m[i][j] != mat.m[i][j])
                return false;
    return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& mat) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (m[i][j] == mat.m[i][j])
                return false;
    return true;
}

Matrix4x4& Matrix4x4::transpose() {
    for (int i = 0; i < 4; ++i)
        for (int j = i; j < 4; ++j)
            std::swap(m[i][j], m[j][i]);
    return *this;
}

Matrix4x4& Matrix4x4::inverse() {
    Matrix4x4 mat = m;
    m[0][0] = mat.m[1][1] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
              mat.m[1][2] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) +
              mat.m[1][3] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]);
    m[1][0] = -(mat.m[1][0] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
                mat.m[1][2] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
                mat.m[1][3] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]));
    m[2][0] = mat.m[1][0] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) -
              mat.m[1][1] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
              mat.m[1][3] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]);
    m[3][0] = -(mat.m[1][0] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]) -
                mat.m[1][1] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]) +
                mat.m[1][2] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]));
    m[0][1] = -(mat.m[0][1] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
                mat.m[0][2] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) +
                mat.m[0][3] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]));
    m[1][1] = mat.m[0][0] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
              mat.m[0][2] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
              mat.m[0][3] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]);
    m[2][1] = -(mat.m[0][0] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) -
                mat.m[0][1] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
                mat.m[0][3] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]));
    m[3][1] = mat.m[0][0] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]) -
              mat.m[0][1] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]) +
              mat.m[0][2] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]);
    m[0][2] = mat.m[0][1] * (mat.m[1][2] * mat.m[3][3] - mat.m[1][3] * mat.m[3][2]) -
              mat.m[0][2] * (mat.m[1][1] * mat.m[3][3] - mat.m[1][3] * mat.m[3][1]) +
              mat.m[0][3] * (mat.m[1][1] * mat.m[3][2] - mat.m[1][2] * mat.m[3][1]);
    m[1][2] = -(mat.m[0][0] * (mat.m[1][2] * mat.m[3][3] - mat.m[1][3] * mat.m[3][2]) -
                mat.m[0][2] * (mat.m[1][0] * mat.m[3][3] - mat.m[1][3] * mat.m[3][0]) +
                mat.m[0][3] * (mat.m[1][0] * mat.m[3][2] - mat.m[1][2] * mat.m[3][0]));
    m[2][2] = mat.m[0][0] * (mat.m[1][1] * mat.m[3][3] - mat.m[1][3] * mat.m[3][1]) -
              mat.m[0][1] * (mat.m[1][0] * mat.m[3][3] - mat.m[1][3] * mat.m[3][0]) +
              mat.m[0][3] * (mat.m[1][0] * mat.m[3][1] - mat.m[1][1] * mat.m[3][0]);
    m[3][2] = -(mat.m[0][0] * (mat.m[1][1] * mat.m[3][2] - mat.m[1][2] * mat.m[3][1]) -
                mat.m[0][1] * (mat.m[1][0] * mat.m[3][2] - mat.m[1][2] * mat.m[3][0]) +
                mat.m[0][2] * (mat.m[1][0] * mat.m[3][1] - mat.m[1][1] * mat.m[3][0]));
    m[0][3] = -(mat.m[0][1] * (mat.m[1][2] * mat.m[2][3] - mat.m[1][3] * mat.m[2][2]) -
                mat.m[0][2] * (mat.m[1][1] * mat.m[2][3] - mat.m[1][3] * mat.m[2][1]) +
                mat.m[0][3] * (mat.m[1][1] * mat.m[2][2] - mat.m[1][2] * mat.m[2][1]));
    m[1][3] = mat.m[0][0] * (mat.m[1][2] * mat.m[2][3] - mat.m[1][3] * mat.m[2][2]) -
              mat.m[0][2] * (mat.m[1][0] * mat.m[2][3] - mat.m[1][3] * mat.m[2][0]) +
              mat.m[0][3] * (mat.m[1][0] * mat.m[2][2] - mat.m[1][2] * mat.m[2][0]);
    m[2][3] = -(mat.m[0][0] * (mat.m[1][1] * mat.m[2][3] - mat.m[1][3] * mat.m[2][1]) -
                mat.m[0][1] * (mat.m[1][0] * mat.m[2][3] - mat.m[1][3] * mat.m[2][0]) +
                mat.m[0][3] * (mat.m[1][0] * mat.m[2][1] - mat.m[1][1] * mat.m[2][0]));
    m[3][3] = mat.m[0][0] * (mat.m[1][1] * mat.m[2][2] - mat.m[1][2] * mat.m[2][1]) -
              mat.m[0][1] * (mat.m[1][0] * mat.m[2][2] - mat.m[1][2] * mat.m[2][0]) +
              mat.m[0][2] * (mat.m[1][0] * mat.m[2][1] - mat.m[1][1] * mat.m[2][0]);
    float det = mat.m[0][0] * m[0][0] + mat.m[0][1] * m[1][0] + mat.m[0][2] * m[2][0] + mat.m[0][3] * m[3][0];
    assert(det != 0);
    det = 1 / det;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] *= det;
    return *this;
}

Matrix4x4 transpose(const Matrix4x4& mat) {
    Matrix4x4 m;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m.m[i][j] = mat.m[j][i];
    return m;
}

Matrix4x4 inverse(const Matrix4x4& mat) {
    Matrix4x4 inv;
    inv.m[0][0] = mat.m[1][1] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
                  mat.m[1][2] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) +
                  mat.m[1][3] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]);
    inv.m[1][0] = -(mat.m[1][0] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
                    mat.m[1][2] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
                    mat.m[1][3] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]));
    inv.m[2][0] = mat.m[1][0] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) -
                  mat.m[1][1] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
                  mat.m[1][3] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]);
    inv.m[3][0] = -(mat.m[1][0] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]) -
                    mat.m[1][1] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]) +
                    mat.m[1][2] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]));
    inv.m[0][1] = -(mat.m[0][1] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
                    mat.m[0][2] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) +
                    mat.m[0][3] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]));
    inv.m[1][1] = mat.m[0][0] * (mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2]) -
                  mat.m[0][2] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
                  mat.m[0][3] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]);
    inv.m[2][1] = -(mat.m[0][0] * (mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1]) -
                    mat.m[0][1] * (mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0]) +
                    mat.m[0][3] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]));
    inv.m[3][1] = mat.m[0][0] * (mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1]) -
                  mat.m[0][1] * (mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0]) +
                  mat.m[0][2] * (mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0]);
    inv.m[0][2] = mat.m[0][1] * (mat.m[1][2] * mat.m[3][3] - mat.m[1][3] * mat.m[3][2]) -
                  mat.m[0][2] * (mat.m[1][1] * mat.m[3][3] - mat.m[1][3] * mat.m[3][1]) +
                  mat.m[0][3] * (mat.m[1][1] * mat.m[3][2] - mat.m[1][2] * mat.m[3][1]);
    inv.m[1][2] = -(mat.m[0][0] * (mat.m[1][2] * mat.m[3][3] - mat.m[1][3] * mat.m[3][2]) -
                    mat.m[0][2] * (mat.m[1][0] * mat.m[3][3] - mat.m[1][3] * mat.m[3][0]) +
                    mat.m[0][3] * (mat.m[1][0] * mat.m[3][2] - mat.m[1][2] * mat.m[3][0]));
    inv.m[2][2] = mat.m[0][0] * (mat.m[1][1] * mat.m[3][3] - mat.m[1][3] * mat.m[3][1]) -
                  mat.m[0][1] * (mat.m[1][0] * mat.m[3][3] - mat.m[1][3] * mat.m[3][0]) +
                  mat.m[0][3] * (mat.m[1][0] * mat.m[3][1] - mat.m[1][1] * mat.m[3][0]);
    inv.m[3][2] = -(mat.m[0][0] * (mat.m[1][1] * mat.m[3][2] - mat.m[1][2] * mat.m[3][1]) -
                    mat.m[0][1] * (mat.m[1][0] * mat.m[3][2] - mat.m[1][2] * mat.m[3][0]) +
                    mat.m[0][2] * (mat.m[1][0] * mat.m[3][1] - mat.m[1][1] * mat.m[3][0]));
    inv.m[0][3] = -(mat.m[0][1] * (mat.m[1][2] * mat.m[2][3] - mat.m[1][3] * mat.m[2][2]) -
                    mat.m[0][2] * (mat.m[1][1] * mat.m[2][3] - mat.m[1][3] * mat.m[2][1]) +
                    mat.m[0][3] * (mat.m[1][1] * mat.m[2][2] - mat.m[1][2] * mat.m[2][1]));
    inv.m[1][3] = mat.m[0][0] * (mat.m[1][2] * mat.m[2][3] - mat.m[1][3] * mat.m[2][2]) -
                  mat.m[0][2] * (mat.m[1][0] * mat.m[2][3] - mat.m[1][3] * mat.m[2][0]) +
                  mat.m[0][3] * (mat.m[1][0] * mat.m[2][2] - mat.m[1][2] * mat.m[2][0]);
    inv.m[2][3] = -(mat.m[0][0] * (mat.m[1][1] * mat.m[2][3] - mat.m[1][3] * mat.m[2][1]) -
                    mat.m[0][1] * (mat.m[1][0] * mat.m[2][3] - mat.m[1][3] * mat.m[2][0]) +
                    mat.m[0][3] * (mat.m[1][0] * mat.m[2][1] - mat.m[1][1] * mat.m[2][0]));
    inv.m[3][3] = mat.m[0][0] * (mat.m[1][1] * mat.m[2][2] - mat.m[1][2] * mat.m[2][1]) -
                  mat.m[0][1] * (mat.m[1][0] * mat.m[2][2] - mat.m[1][2] * mat.m[2][0]) +
                  mat.m[0][2] * (mat.m[1][0] * mat.m[2][1] - mat.m[1][1] * mat.m[2][0]);
    float det = mat.m[0][0] * inv.m[0][0] + mat.m[0][1] * inv.m[1][0] + mat.m[0][2] * inv.m[2][0] + mat.m[0][3] * inv.m[3][0];
    assert(det != 0);
    det = 1 / det;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            inv.m[i][j] *= det;
    return inv;
}

std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat) {
    for (int i = 0; i < 4; ++i) {
        os << std::endl;
        for (int j = 0; j < 4; ++j) {
            if (j != 3)
                os << std::setprecision(4) << std::left << std::setw(10) << mat.m[i][j];
            else
                os << std::setprecision(4) << mat.m[i][j];
        }
    }
    return os;
}

Transform Transform::operator*(const Transform& t) const {
    return Transform(m * t.m, t.m_inv * m_inv);
}

bool Transform::operator==(const Transform& t) {
    return m == t.m && m_inv == t.m_inv;
}

bool Transform::operator!=(const Transform& t) {
    return m != t.m || m_inv != t.m_inv;
}

const Matrix4x4& Transform::getMatrix() const {
    return m;
}
const Matrix4x4& Transform::getInverseMatrix() const {
    return m_inv;
}

Transform scale(float sx, float sy, float sz) {
    assert(sx != 0 && sy != 0 && sz != 0);
    Matrix4x4 m(sx, 0.f, 0.f, 0.f,
                0.f, sy, 0.f, 0.f,
                0.f, 0.f, sz, 0.f,
                0.f, 0.f, 0.f, 1.f);
    Matrix4x4 m_inv(1 / sx, 0.f, 0.f, 0.f,
                    0.f, 1 / sy, 0.f, 0.f,
                    0.f, 0.f, 0.f, 1 / sz,
                    0.f, 0.f, 0.f, 1.f);
    return Transform(m, m_inv);
}

Transform rotateX(float theta) {
    float sin_theta = std::sin(degreeToRadian(theta));
    float cos_theta = std::cos(degreeToRadian(theta));
    Matrix4x4 m(1.f, 0.f, 0.f, 0.f,
                0.f, cos_theta, -sin_theta, 0.f,
                0.f, sin_theta, cos_theta, 0.f,
                0.f, 0.f, 0.f, 1.f);
    Matrix4x4 m_inv(1.f, 0.f, 0.f, 0.f,
                    0.f, cos_theta, sin_theta, 0.f,
                    0.f, -sin_theta, cos_theta, 0.f,
                    0.f, 0.f, 0.f, 1.f);
    return Transform(m, m_inv);
}

Transform rotateY(float theta) {
    float sin_theta = std::sin(degreeToRadian(theta));
    float cos_theta = std::cos(degreeToRadian(theta));
    Matrix4x4 m(cos_theta, 0.f, sin_theta, 0.f,
                0.f, 1.f, 0.f, 0.f,
                -sin_theta, 0.f, cos_theta, 0.f,
                0.f, 0.f, 0.f, 1.f);
    Matrix4x4 m_inv(cos_theta, 0.f, -sin_theta, 0.f,
                    0.f, 1.f, 0.f, 0.f,
                    sin_theta, 0.f, cos_theta, 0.f,
                    0.f, 0.f, 0.f, 1.f);
    return Transform(m, m_inv);
}

Transform rotateZ(float theta) {
    float sin_theta = std::sin(degreeToRadian(theta));
    float cos_theta = std::cos(degreeToRadian(theta));
    Matrix4x4 m(cos_theta, -sin_theta, 0.f, 0.f,
                sin_theta, cos_theta, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f);
    Matrix4x4 m_inv(cos_theta, -sin_theta, 0.f, 0.f,
                    -sin_theta, cos_theta, 0.f, 0.f,
                    0.f, 0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f, 1.f);
    return Transform(m, m_inv);
}

Transform translate(const Vector3f& d) {
    Matrix4x4 m(1.f, 0.f, 0.f, d.x,
                0.f, 1.f, 0.f, d.y,
                0.f, 0.f, 1.f, d.z,
                0.f, 0.f, 0.f, 1.f);
    Matrix4x4 m_inv(1.f, 0.f, 0.f, -d.x,
                    0.f, 1.f, 0.f, -d.y,
                    0.f, 0.f, 1.f, -d.z,
                    0.f, 0.f, 0.f, 1.f);
    return Transform(m, m_inv);
}

Transform lookAt(const Point3f& pos, const Point3f& look, const Vector3f& up) {
    Matrix4x4 camer_to_world;
    Vector3f z = normailize(look - pos);
    Vector3f x = cross(normailize(up), z);
    Vector3f y = cross(z, x);
    camer_to_world.m[0][0] = x.x;
    camer_to_world.m[1][0] = x.y;
    camer_to_world.m[2][0] = x.z;
    camer_to_world.m[3][0] = 0.f;
    camer_to_world.m[0][1] = y.x;
    camer_to_world.m[1][1] = y.y;
    camer_to_world.m[2][1] = y.z;
    camer_to_world.m[3][1] = 0.f;
    camer_to_world.m[0][2] = z.x;
    camer_to_world.m[1][2] = z.y;
    camer_to_world.m[2][2] = z.z;
    camer_to_world.m[3][2] = 0.f;
    camer_to_world.m[0][3] = pos.x;
    camer_to_world.m[1][3] = pos.y;
    camer_to_world.m[2][3] = pos.z;
    camer_to_world.m[3][3] = 1.f;
    return Transform(inverse(camer_to_world), camer_to_world);
}

Transform perspective(float fov, float aspect, float near, float far) {
    Matrix4x4 perspect;
    float cot_half_fov = 1 / std::tan(degreeToRadian(fov / 2));
    float inv_aspect = 1 / aspect;
    perspect.m[0][0] = cot_half_fov * inv_aspect;
    perspect.m[1][0] = 0.f;
    perspect.m[2][0] = 0.f;
    perspect.m[3][0] = 0.f;
    perspect.m[0][1] = 0.f;
    perspect.m[1][1] = cot_half_fov;
    perspect.m[2][1] = 0.f;
    perspect.m[3][1] = 0.f;
    perspect.m[0][2] = 0.f;
    perspect.m[1][2] = 0.f;
    perspect.m[2][2] = (near + far) / (near - far);
    perspect.m[3][2] = -1.f;
    perspect.m[0][3] = 0.f;
    perspect.m[1][3] = 0.f;
    perspect.m[2][3] = (2 * near * far) / (near - far);
    perspect.m[3][3] = 0.f;
    return Transform(perspect, inverse(perspect));
}

Transform viewPort(int width, int height) {
    Matrix4x4 view_port;
    view_port.m[0][0] = (float)width / 2;
    view_port.m[1][0] = 0.f;
    view_port.m[2][0] = 0.f;
    view_port.m[3][0] = 0.f;
    view_port.m[0][1] = 0.f;
    view_port.m[1][1] = (float)height / 2;
    view_port.m[2][1] = 0.f;
    view_port.m[3][1] = 0.f;
    view_port.m[0][2] = 0.f;
    view_port.m[1][2] = 0.f;
    view_port.m[2][2] = 1.f;
    view_port.m[3][2] = 0.f;
    view_port.m[0][3] = (float)width / 2;
    view_port.m[1][3] = (float)height / 2;
    view_port.m[2][3] = 0.f;
    view_port.m[3][3] = 1.f;
    return Transform(view_port, inverse(view_port));
}

Transform transpose(const Transform& t) {
    return Transform(transpose(t.m), transpose(t.m_inv));
}

Transform inverse(const Transform& t) {
    return Transform(t.m_inv, t.m);
}

std::ostream& operator<<(std::ostream& os, const Transform& t) {
    os << "t=" << t.m << "\ninv=" << t.m_inv;
    return os;
}
