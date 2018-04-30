// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_collision_boxcollider.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/19
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_collision_boxcollider.h"

#include "./raytracing_fw_collision_rectanglecollider.h"
#include "fw/raytracing_fw_types.h"

namespace raytracing { namespace fw { namespace collision {

struct ttBoxCollider::Member {
    ttVector center = ttVector(0.0f, 0.0f, 0.0f, 0.0f);
    ttVector dir = ttVector(0.0f, 0.0f, 1.0f, 0.0f);
    ttVector up = ttVector(0.0f, 1.0f, 0.0f, 0.0f);
    ttVector size = ttVector(1.0f, 1.0f, 1.0f, 0.0f);
    collision::ttRectangleCollider rect[6];
    bool enableFilpBackFace = false;
};

ttBoxCollider::ttBoxCollider() {
    m_.reset(new Member());
}

ttBoxCollider::~ttBoxCollider() {
}

void
ttBoxCollider::setup(
        const ttVector& center,
        const ttVector& dir,
        const ttVector& up,
        const ttVector& size,
        bool enableFlipBackFace) {
    m_->center = center;
    m_->dir = dir;
    m_->up = up;

    m_->size.x = size.x;
    m_->size.y = size.y;
    m_->size.z = size.z;
    m_->size.w = 0.0f;

    m_->rect[0].setRectSize(m_->size.x, m_->size.y);
    m_->rect[1].setRectSize(m_->size.x, m_->size.y);
    m_->rect[2].setRectSize(m_->size.z, m_->size.y);
    m_->rect[3].setRectSize(m_->size.z, m_->size.y);
    m_->rect[4].setRectSize(m_->size.z, m_->size.x);
    m_->rect[5].setRectSize(m_->size.z, m_->size.x);

    setEnableFilpBackFace(enableFlipBackFace);
    
    setup_();
}

void
ttBoxCollider::setCenter(const ttVector& center) {
    m_->center = center;

    setup_();
}

void
ttBoxCollider::setup_() {
    m_->rect[0].setNormal(m_->dir);
    m_->rect[0].setUpVector(m_->up);

    auto local = m_->rect[0].getLocalBasis();
    m_->rect[1].setNormal(-1.0f * m_->dir);
    m_->rect[2].setNormal(local.getU());
    m_->rect[3].setNormal(-1.0f * local.getU());
    m_->rect[4].setNormal(-1.0f * local.getV());
    m_->rect[5].setNormal(local.getV());

    m_->rect[1].setUpVector(m_->up);
    m_->rect[2].setUpVector(m_->up);
    m_->rect[3].setUpVector(m_->up);
    m_->rect[4].setUpVector(local.getU());
    m_->rect[5].setUpVector(local.getU());

    m_->rect[0].setCenter(m_->center + 0.5f * local.getW() * m_->size.z);
    m_->rect[1].setCenter(m_->center - 0.5f * local.getW() * m_->size.z);
    m_->rect[2].setCenter(m_->center + 0.5f * local.getU() * m_->size.x);
    m_->rect[3].setCenter(m_->center - 0.5f * local.getU() * m_->size.x);
    m_->rect[4].setCenter(m_->center - 0.5f * local.getV() * m_->size.y);
    m_->rect[5].setCenter(m_->center + 0.5f * local.getV() * m_->size.y);
}

void
ttBoxCollider::setDirection(const ttVector& dir) {
    m_->dir = dir;
    setup_();
}

void
ttBoxCollider::setUpVector(const ttVector& up) {
    m_->up = up;
    setup_();
}

void
ttBoxCollider::setBoxSize(float xSize, float ySize, float zSize) {
    m_->size.x = xSize;
    m_->size.y = ySize;
    m_->size.z = zSize;

    m_->rect[0].setRectSize(xSize, ySize);
    m_->rect[1].setRectSize(xSize, ySize);
    m_->rect[2].setRectSize(zSize, ySize);
    m_->rect[3].setRectSize(zSize, ySize);
    m_->rect[4].setRectSize(zSize, xSize);
    m_->rect[5].setRectSize(zSize, xSize);

    setup_();
}

void
ttBoxCollider::setEnableFilpBackFace(bool enable) {
    m_->enableFilpBackFace = enable;
    for(auto Li = 0; Li < 6; ++Li) {
        m_->rect[Li].enableFilpBackFace(enable);
    }
}

bool
ttBoxCollider::intersect(const ttRay& ray, float a_near, float a_far, IntersectInfo* info) const {
    bool intersected = false;
    auto Li = 0;
    for(const auto& collider : m_->rect) {
        if(Li <= 6) {
            if(collider.intersect(ray, a_near, a_far, info)) {
                intersected = true;
                a_far = info->t;
            }
        }
        ++Li;
    }

    return intersected;
}

}}}
