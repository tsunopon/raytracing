// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_substance.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/18
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_substance.h"

#include "fw/collision/raytracing_fw_collision_icollider.h"
#include "fw/material/raytracing_fw_imaterial.h"

namespace raytracing { namespace fw { 

ttSubstance::ttSubstance() {
}

ttSubstance::~ttSubstance() {
}

void
ttSubstance::moveCollider(std::unique_ptr<collision::ttICollider>& collider) {
    collider_ = std::move(collider);
}

void
ttSubstance::moveMaterial(std::unique_ptr<material::ttIMaterial>& material) {
    material_ = std::move(material);
}


}}
