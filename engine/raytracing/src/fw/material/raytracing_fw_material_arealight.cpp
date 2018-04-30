// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_material_arealight.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/30
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_material_arealight.h"

namespace raytracing { namespace fw { namespace material { 

ttAreaLight::ttAreaLight() {
}

ttAreaLight::~ttAreaLight() {

}

bool
ttAreaLight::isLight() const {
    return true;
}

ttVector
ttAreaLight::getRadiance(const ttRay& outRay, const ttVector& point) const {
    ttUNUSED(outRay);
    ttUNUSED(point);
    return lightColor_;
}

ttVector
ttAreaLight::function(const ttRay& inRay, const ttRay& outRay, const ttVector& normal) const {
    ttUNUSED(inRay);
    ttUNUSED(outRay);
    ttUNUSED(normal);
    ttASSERT(false && "使用すべきでない関数が呼び出されました");
    return ttVector();
}

void
ttAreaLight::getNextRay(
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
    ttASSERT(false && "使用すべきでない関数が呼び出されました");
}

}}}
