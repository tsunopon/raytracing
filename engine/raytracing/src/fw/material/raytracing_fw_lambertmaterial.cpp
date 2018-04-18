// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_lambertmaterial.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/18
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_lambertmaterial.h"

namespace raytracing { namespace fw { namespace material { 

ttLambertMaterial::ttLambertMaterial() {
}

ttLambertMaterial::~ttLambertMaterial() {
}

ttVector
ttLambertMaterial::getRadiance(const ttRay& outRay, const ttVector& point, const ttVector& normal) const {
    ttUNUSED(outRay);
    ttUNUSED(point);
    ttUNUSED(normal);
    return ttVector();
}

ttVector
ttLambertMaterial::function(const ttRay& inRay, const ttRay& outRay, const ttVector& normal) const {
    ttUNUSED(inRay);
    ttUNUSED(outRay);
    ttUNUSED(normal);
    return funcValue_; // albedo_ / PI;
}

void
ttLambertMaterial::setAlbedo(float r, float g, float b) {
    albedo_.x = r;
    albedo_.y = g;
    albedo_.z = b;
    // ランバートは反射率によって決まるのでここで計算
    funcValue_.x = r / PI;
    funcValue_.y = g / PI;
    funcValue_.z = b / PI;
    funcValue_.w = 0.0f;
}

}}}
