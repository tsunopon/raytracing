// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_material_directionallight.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/24
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_material_directionallight.h"

namespace raytracing { namespace fw { namespace material { 

ttDirectionalLight::ttDirectionalLight() {
    lightColor_.w = 1.0f;
}

ttDirectionalLight::~ttDirectionalLight() {
}

bool
ttDirectionalLight::isLight() const {
    return true;
}

ttVector
ttDirectionalLight::getRadiance(const ttRay& outRay, const ttVector& point) const {
    ttUNUSED(outRay);
    ttUNUSED(point);
    return lightColor_;
}

ttVector
ttDirectionalLight::function(const ttRay& inRay, const ttRay& outRay, const ttVector& normal) const {
    ttUNUSED(inRay);
    ttUNUSED(outRay);
    ttUNUSED(normal);
    return ttVector();
}

void
ttDirectionalLight::getNextRay(
                const ttVector& point,
                const ttVector& normal,
                const ttVector& inDir,
                ttRandom& random,
                ttRay* ray,
                float* pdf) const {
    ttUNUSED(point);
    ttUNUSED(normal);
    ttUNUSED(inDir);
    ttUNUSED(random);
    ttUNUSED(ray);
    ttUNUSED(pdf);
}

}}}
