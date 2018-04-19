// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_vecmath.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/14
//
//=====================================================================================================================
#include "stdafx.h"
#include "fw/raytracing_fw_vecmath.h"

namespace raytracing { namespace fw { 

static const double D_ERR = 0.0000000001;

float
ttVector::dot(const ttVector& lhs, const ttVector& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

ttVector
ttVector::cross(const ttVector& lhs, const ttVector& rhs) {
    ttVector result;
    result.x = lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = lhs.x * rhs.y - lhs.y * rhs.x;
    result.w = 0.0f;
    return result;
}

ttVector&
ttVector::normalize() {
    double length = dot(*this);
    if(length > D_ERR) {
        length = std::sqrt(length);
        x = static_cast<float>(x / length);
        y = static_cast<float>(y / length);
        z = static_cast<float>(z / length);
        w = static_cast<float>(w / length);
    }
    return (*this);
}

ttVector
ttVector::normalize(const ttVector& vec) {
    ttVector result(vec);
    return result.normalize();
}

float
ttVector::length(const ttVector& vec) {
    return std::sqrt(dot(vec, vec));
}

ttVector
ttVector::operator*(const ttMatrix& rhs) const {
    ttVector result;

    for(auto Li = 0U; Li < 4U; ++Li) {
        result[Li] = 0.0f;
        for(auto Lj = 0U; Lj < 4U; ++Lj) {
            result[Li] += f32[Lj] * rhs[Lj * 4U + Li];
        }
    }
    return result;
}

ttVector
operator*(float lhs, const ttVector& rhs) {
    return rhs * lhs;
}


void
ttOthonormalBasis::createFromWAxis(const ttVector& z) {
    basis_[2] = z;
    basis_[2].w = 0.0f;
    basis_[2].normalize();
    ttVector a;
    if(std::fabs(basis_[2].x) >= 0.99f) {
        a = ttVector(0.0f, 1.0f, 0.0f, 0.0f);
    } else {
        a = ttVector(1.0f, 0.0f, 0.0f, 0.0f);
    }
    basis_[1] = ttVector::normalize(basis_[2].cross(a));
    basis_[0] = basis_[2].cross(basis_[1]);
}

void
ttMatrix::perspective(
            ttMatrix* result,
            float a_near, float a_far,
            float fovY_degree, float aspect) {
    for(auto Li = 0U; Li < 16U; ++Li) {
        result->m[Li] = 0.0f;
    }
    float f = static_cast<float>(1.0 / (::tan((PI / 180.0f) * (fovY_degree) / 2.0)));
    result->m11 = f / aspect;
    result->m22 = f;
    result->m33 = (a_far + a_near) / (a_near - a_far);
    result->m43 = (2.0f * a_far * a_near) / (a_near - a_far);
    result->m34 = -1.0f;
}

void
ttMatrix::orthographic(
            ttMatrix* result,
            float a_near, float a_far,
            float width, float height) {
    for(auto Li = 0U; Li < 16U; ++Li) {
        result->m[Li] = 0.0f;
    }
    result->m11 = 2.0f / width;
    result->m22 = 2.0f / height;
    result->m33 = 2.0f / (a_near / a_far);
    result->m44 = 1.0f;
    result->m41 = -1.0f;
    result->m42 = 1.0f;
    result->m43 = a_near / (a_near - a_far);
}

void
ttMatrix::lookAt(
                ttMatrix* result,
                const ttVector& eye,
                const ttVector& look,
                const ttVector& up) {
    ttVector tmp(look.x - eye.x, look.y - eye.y, look.z - eye.z, 0.0f);
    ttVector f = ttVector::normalize(tmp);
    ttVector u = ttVector::normalize(up);
    ttVector s = ttVector::normalize(ttVector::cross(f, u));
    u = ttVector::cross(s, f);
    result->m11 = s.x;
    result->m21 = s.y;
    result->m31 = s.z;
    result->m12 = u.x;
    result->m22 = u.y;
    result->m32 = u.z;
    result->m13 = -f.x;
    result->m23 = -f.y;
    result->m33 = -f.z;
    result->m41 = -ttVector::dot(s, eye);
    result->m42 = -ttVector::dot(u, eye);
    result->m43 = ttVector::dot(f, eye);
    result->m14 = 0.0f;
    result->m24 = 0.0f;
    result->m34 = 0.0f;
    result->m44 = 1.0f;
}

void
ttMatrix::getTransMatrixPos(ttMatrix* result, float x, float y, float z) {
    result->setIdentity();
    result->m41 = x;
    result->m42 = y;
    result->m43 = z;
}

void
ttMatrix::getTransMatrixScale(ttMatrix* result, float x, float y, float z) {
    result->setIdentity();
    result->m11 = x;
    result->m12 = y;
    result->m13 = z;
}

}}
