// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_collision_rectanglecollider.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/19
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_collision_rectanglecollider.h"

#include "fw/raytracing_fw_types.h"

namespace raytracing { namespace fw { namespace collision {

struct ttRectangleCollider::Member {
    ttVector center;
    ttVector normal;
    ttVector up;
    float width = FLT_MAX;
    float height = FLT_MAX;
    bool enableFilpBackFace = false;
    ttOthonormalBasis local;    // ローカル座標空間の基底軸
    ttVector localCenter;       // ローカル座標空間での中心座標
};

ttRectangleCollider::ttRectangleCollider() {
    m_.reset(new Member());
    // 初期値を代入
    m_->normal = ttVector(0.0f, 1.0f, 0.0f, 0.0f);
    m_->up = ttVector(0.0f, 0.0f, 1.0f, 0.0f);
    updateLocalBasis_();
}

ttRectangleCollider::~ttRectangleCollider() {
}

void
ttRectangleCollider::setCenter(const ttVector& center) {
    m_->center = center;
    m_->localCenter = m_->local.getLocal(m_->center);
}

void
ttRectangleCollider::setNormal(const ttVector& normal) {
    m_->normal = normal;
    m_->normal.normalize();
    updateLocalBasis_();
}

void
ttRectangleCollider::setUpVector(const ttVector& up) {
    m_->up = up;
    updateLocalBasis_();
}

void
ttRectangleCollider::setRectSize(float width, float height) {
    m_->width = width;
    m_->height = height;
}

void
ttRectangleCollider::setRectWidth(float width) {
    m_->width = width;
}

void
ttRectangleCollider::setRectHeight(float height) {
    m_->height = height;
}

void
ttRectangleCollider::enableFilpBackFace(bool enable) {
    m_->enableFilpBackFace = enable;
}

void
ttRectangleCollider::updateLocalBasis_() {
    // ローカル空間の基底軸を計算
    m_->local.createFromWAxis(m_->normal, m_->up);
    m_->localCenter = m_->local.getLocal(m_->center);
}

bool
ttRectangleCollider::intersect(const ttRay& ray, float a_near, float a_far, ttIntersectInfo* info) const {
    ttVector normal = m_->normal;
    if(ray.direction.dot(m_->normal) > 0) {
        if(m_->enableFilpBackFace) {
            normal = -1.0f * m_->normal;
        } else {
            return false;
        }
    }

    // ローカル空間で衝突判定
    auto localBase = m_->local.getLocal(ray.base);
    auto localDir = m_->local.getLocal(ray.direction);
    if(localDir.z == 0.0f) {
        return false;
    }
    auto t = (m_->localCenter.z - localBase.z) / localDir.z;
    if(t < a_near || t > a_far) {
        return false;
    }

    auto x = localBase.x + t * localDir.x;
    auto y = localBase.y + t * localDir.y;
    auto minX = m_->localCenter.x - 0.5f * m_->width;
    auto minY = m_->localCenter.y - 0.5f * m_->height;
    auto maxX = m_->localCenter.x + 0.5f * m_->width;
    auto maxY = m_->localCenter.y + 0.5f * m_->height;
    if(x < minX || x > maxX || y < minY || y > maxY) {
        return false;
    }

    // ローカル座標は回転しか行われていないからtをそのまま使ってワールド座標を計算
    info->point = ray.base + t * ray.direction;
    info->point.w = 0.0f;
    info->normal = normal;
    info->t = t;

    return true;
}

const ttOthonormalBasis&
ttRectangleCollider::getLocalBasis() const {
    return m_->local;
}

}}}
