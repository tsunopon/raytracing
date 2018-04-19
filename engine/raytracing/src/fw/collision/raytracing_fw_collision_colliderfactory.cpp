// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_collistionfuctory.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/18
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_collision_colliderfactory.h"

#include "fw/collision/raytracing_fw_collision_spherecollider.h"

namespace raytracing { namespace fw { namespace collision {

std::unique_ptr<ttICollider>
ttColliderFactory::createCollder(ttColliderType type) {
    ttICollider* collider = nullptr;
    switch(type) {
    case ttColliderType::SPHERE:
        collider = new ttSphereCollider();
        break;
    default:
        break;
    }
    return std::move(std::unique_ptr<ttICollider>(collider));
}

void
ttColliderFactory::setupSphere(ttICollider* collider, float radius, const ttVector& center) {
    auto sphere = static_cast<ttSphereCollider*>(collider);
    sphere->setCenter(center);
    sphere->setRadius(radius);
}

}}}
