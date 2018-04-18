// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_materialfuctory.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/18
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_materialfactory.h"

#include "fw/material/raytracing_fw_lambertmaterial.h"

namespace raytracing { namespace fw { namespace material {

std::unique_ptr<ttIMaterial>
ttMaterialFactory::createMaterial(ttMaterialType type) {
    ttIMaterial* mat = nullptr;
    switch (type) {
    case ttMaterialType::LAMBERT:
        mat = new ttLambertMaterial();
        break;
    default:
        break;
    }
    ttASSERT(mat != nullptr);
    return std::move(std::unique_ptr<ttIMaterial>(mat));
}

void
ttMaterialFactory::setupLambert(ttIMaterial* mat, const ttVector& albedo) {
    auto lambert = static_cast<ttLambertMaterial*>(mat);
    lambert->setAlbedo(albedo.x, albedo.y, albedo.z);
}

}}}
