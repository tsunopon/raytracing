// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_lambertmaterial.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/18
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_material_lambertmaterial.h"

#include "fw/raytracing_fw_types.h"
#include "fw/raytracing_fw_random.h"

namespace raytracing { namespace fw { namespace material { 

ttLambertMaterial::ttLambertMaterial() {
}

ttLambertMaterial::~ttLambertMaterial() {
}

ttVector
ttLambertMaterial::getRadiance(const ttRay& outRay, const ttVector& point) const {
    ttUNUSED(outRay);
    ttUNUSED(point);
    return ttVector();
}

ttVector
ttLambertMaterial::function(const ttRay& inRay, const ttRay& outRay, const ttVector& normal) const {
    ttUNUSED(inRay);
    ttUNUSED(outRay);
    ttUNUSED(normal);
    return funcValue_; // albedo_ / PI;
}

static float
inverseCDF(float x) {
    return std::asin(x);
}

void
ttLambertMaterial::getNextRay(
                const ttVector& point,
                const ttVector& normal,
                const ttVector& inDir,
                ttRandom& random,
                ttRay* ray,
                float* pdf) const {
    ttUNUSED(inDir);
    // 法線と光の入力ベクトルとの角度をθとする
    // 確率密度関数がcosθになるような乱数を生成する
    // 累積分布関数はF(θ)=sinθ
    // 累積分布関数の逆関数はF^-1(θ)=Asin(θ)
    //
    // 乱数の確率を偏らせて収束を早めるのと、計算量の増大とのトレードオフ
    // ランバートくらいなら実は一様乱数を使用したほうが早いかもしれない
    auto theta = inverseCDF(random.range(0.0f, 1.0f));
    auto phi = random.range(0.0f, 2 * PI);
    auto sinT = std::sin(theta);
    auto cosT = std::cos(theta);
    auto r = 1.0f;
    auto x = r * sinT * cos(phi);
    auto y = r * sinT * sin(phi);
    auto z = r * cosT;

    // 法線を軸とした正規直交基底を作成
    ttOthonormalBasis onb;
    onb.createFromWAxis(normal);
    ray->direction = onb.getXYZ(x, y, z);
    ray->direction.w = 0.0f;
    ray->base = point;
    // もちろん確率密度関数はcosθ
    *pdf = cosT;
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
