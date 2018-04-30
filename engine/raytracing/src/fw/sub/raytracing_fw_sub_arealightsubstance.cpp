// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_sub_arealightsubstance.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/05/01
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_sub_arealightsubstance.h"

#include "fw/material/raytracing_fw_material_arealight.h"
#include "fw/collision/raytracing_fw_collision_icollider.h"

namespace raytracing { namespace fw { namespace sub {

ttAreaLightSubstance::ttAreaLightSubstance() {
    material_.reset(new material::ttAreaLight());
}

ttAreaLightSubstance::~ttAreaLightSubstance() {

}

material::ttIMaterial*
ttAreaLightSubstance::getMaterial() const {
    return material_.get();
}

bool
ttAreaLightSubstance::getRadiance(const ttRay& ray, const collision::ttIntersectInfo& info, ttVector* color) const {
    if(material_->isLight() && collider_) {
        *color = material_->getRadiance(ray, info.point);
        return true;
    }
    return false;
}

void
ttAreaLightSubstance::moveCollider(std::unique_ptr<collision::ttICollider>& collider) {
    collider_ = std::move(collider);
}

void
ttAreaLightSubstance::setLightColor(const ttVector& color) {
    material_->setLightColor(color);
}

}}}
