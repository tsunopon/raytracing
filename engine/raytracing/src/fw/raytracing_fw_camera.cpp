// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_camera.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/15
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_camera.h"

#include "./fw/raytracing_fw_types.h"

namespace raytracing { namespace fw { 

ttCamera::ttCamera() {
}

ttCamera::~ttCamera() {
}

void
ttCamera::getRay(float u, float v, uint32_t sampleIndex, ttRay* ray) const {
    ttUNUSED(sampleIndex);
    ray->base = eye_;
    ray->direction = baseW_ + baseU_ * u + baseV_ * v - eye_;
    ray->direction.w = 0.0f;
    ray->direction.normalize();
    ray->base.w = 0.0f;
}

void
ttCamera::setMasSamplingCount(uint32_t count) {
    maxSamplingCount_ = count;
}

void
ttCamera::update() {
    ttVector u, v, w;
    float halfH = std::tan(0.5f * (vfovDegree_ * PI / 180.0f));
    float halfW = aspect_ * halfH;
    w = (eye_ - lookat_);
    w.w = 0.0;
    w.normalize();
    u = up_.cross(w).normalize();
    v = w.cross(u).normalize();
    baseW_ = eye_ - halfW * u - halfH * v - w;
    baseU_ = 2.0f * halfW * u;
    baseV_ = 2.0f * halfH * v;
}

}}
