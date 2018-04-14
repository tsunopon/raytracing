// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_collision_spherecollider.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/15
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_collision_spherecollider.h"
#include "fw/raytracing_fw_types.h"

namespace raytracing { namespace fw { namespace collision {

struct ttSphereCollider::Member {
    ttSphere sphere;
};

ttSphereCollider::ttSphereCollider() {
    m_.reset(new Member());
}

ttSphereCollider::~ttSphereCollider() {
    m_.reset();
}

bool
ttSphereCollider::intersect(const ttRay& ray, float a_near, float a_far, IntersectInfo* info) const {
    // 判別式を使って交差判定
    ttVector bc = ray.base - m_->sphere.center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * ray.direction.dot(bc);
    float c = bc.dot(bc) - m_->sphere.radius * m_->sphere.radius;
    float D = b * b - 4.0f * a * c;
    if(D > 0) {
        float root = std::sqrt(D);
        // まずは近いほうから判定
        float temp = (-b - root) / (2.0f * a);
        bool intersect = false;
        if(temp < a_far && temp > a_near) {
            intersect = true;
        } else {
            // 遠いほうの判定
            temp = (-b + root) / (2.0f * a);
            if(temp < a_far && temp > a_near) {
                intersect = true;
            }
        }
        if(intersect) {
            if(info != nullptr) {
                // 交点と法線を渡す
                info->t = temp;
                info->point = ray.base + temp * ray.direction;
                info->normal = (info->point - m_->sphere.center) / m_->sphere.radius;
            }
            return true;
        }
    }
    return false;
}

const ttSphere& 
ttSphereCollider::getSphere() const {
    return m_->sphere;
}

const ttVector&
ttSphereCollider::getCenter() const {
    return m_->sphere.center;
}

float
ttSphereCollider::getRadius() const {
    return m_->sphere.radius;
}

void
ttSphereCollider::setSphere(const ttSphere& sphere) {
    m_->sphere = sphere;
}

void
ttSphereCollider::setCenter(const ttVector& center) {
    m_->sphere.center = center;
}

void
ttSphereCollider::setRadius(float radius) {
    m_->sphere.radius = radius;
}

}}}
