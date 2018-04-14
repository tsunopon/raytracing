﻿// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { 

class ttMatrix;

class ttVector {
public:
    union {
        float f32[4] = {};
        struct {
            float x;
            float y;
            float z;
            float w;
        };
    };
    ttVector() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
    }
    ttVector(float ax, float ay, float az, float aw) {
        x = ax;
        y = ay;
        z = az;
        w = aw;
    }
    ttVector(const ttVector& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
    }
    static float dot(const ttVector& lhs, const ttVector& rhs);
    float dot(const ttVector& vec) const {
        return ttVector::dot(*this, vec);
    }
    static ttVector cross(const ttVector& lhs, const ttVector& rhs);
    ttVector cross(const ttVector& vec) {
        return cross(*this, vec);
    }
    static ttVector normalize(const ttVector& vec);
    ttVector& normalize();
    static float length(const ttVector& vec);
    float length() const {
        return ttVector::length(*this);
    }
    ttVector& operator=(const ttVector& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
        return (*this);
    }
    ttVector operator+(const ttVector& rhs) const {
        return ttVector(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }
    ttVector operator-(const ttVector& rhs) const {
        return ttVector(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }
    ttVector operator*(float rhs) const {
        return ttVector(x * rhs, y * rhs, z * rhs, z * rhs);
    }
    ttVector operator*(const ttVector& rhs) const {
        return ttVector(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
    }
    ttVector operator*(const ttMatrix& rhs) const;
    ttVector operator/(float rhs) const {
        return ttVector(x / rhs, y / rhs, z / rhs, w / rhs);
    }
    ttVector operator/(const ttVector& rhs) const {
        return ttVector(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
    }
    float& operator[](int n) {
        return f32[n];
    }
    const float& operator [](int n) const {
        return f32[n];
    }

    friend ttVector operator*(float lhs, const ttVector& rhs);
};

class ttMatrix {
public:
    union {
        float m[16] = {};
        struct {
            float m11;
            float m12;
            float m13;
            float m14;
            float m21;
            float m22;
            float m23;
            float m24;
            float m31;
            float m32;
            float m33;
            float m34;
            float m41;
            float m42;
            float m43;
            float m44;
        };
    };

    ttMatrix() {
        setIdentity();
    }
    ttMatrix(const ttMatrix& rhs) {
        for(auto Li = 0U; Li < 16; ++Li) {
            m[Li] = rhs.m[Li];
        }
    }
    explicit ttMatrix(const float rhs[16]) {
        for(auto Li = 0U; Li < 16; ++Li) {
            m[Li] = rhs[Li];
        }
    }
    float& operator[](int n) {
        return m[n];
    }
    const float& operator [](int n) const {
        return m[n];
    }
    ttMatrix& operator=(const ttMatrix& rhs) {
        for(auto Li = 0U; Li < 16; ++Li) {
            m[Li] = rhs.m[Li];
        }
        return (*this);
    }

    ttMatrix& operator*(const ttMatrix& rhs) const {
        ttMatrix result;
        for(auto Li = 0U; Li < 4U; ++Li) {
            for(auto Lj = 0U; Lj < 4U; ++Lj) {
                result.m[Li * 4U + Lj] = 0;
                for(auto Lk = 0U; Lk < 4U; ++Lk) {
                    result.m[Li * 4 + Lj] += m[Li * 4U + Lk] * rhs.m[Lk * 4U + Lj];
                }
            }
        }
        return result;
    }

    //! 単位行列化
    ttMatrix& setIdentity() {
        m[0] = 1.0f;
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 0.0f;
        m[4] = 0.0f;
        m[5] = 1.0f;
        m[6] = 0.0f;
        m[7] = 0.0f;
        m[8] = 0.0f;
        m[9] = 0.0f;
        m[10] = 1.0f;
        m[11] = 0.0f;
        m[12] = 0.0f;
        m[13] = 0.0f;
        m[14] = 0.0f;
        m[15] = 1.0f;
        return (*this);
    }

    //! 転置
    ttMatrix setTranspose() {
        float tmp;

        tmp = m12;
        m12 = m21;
        m21 = tmp;
        
        tmp = m13;
        m13 = m31;
        m31 = tmp;
        
        tmp = m14;
        m14 = m41;
        m41 = tmp;

        tmp = m23;
        m23 = m32;
        m32 = tmp;

        tmp = m24;
        m24 = m42;
        m42 = tmp;

        tmp = m34;
        m34 = m43;
        m43 = tmp;

        return (*this);
    }

    //! 転置行列の取得
    ttMatrix getTranspose() const {
        ttMatrix result(*this);
        return result.setTranspose();
    }

public:
    static void perspective(
                    ttMatrix* result,
                    float a_near, float a_far,
                    float fovY_degree, float aspect);
    static void orthographic(
                    ttMatrix* result,
                    float a_near, float a_far,
                    float width, float height);
    static void lookAt(
                    ttMatrix* result,
                    const ttVector& eye,
                    const ttVector& look,
                    const ttVector& up);
    static void getTransMatrixPos(ttMatrix* result, float x, float y, float z);
    static void getTransMatrixScale(ttMatrix* result, float x, float y, float z);
};

}}