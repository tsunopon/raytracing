// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_materialfuctory.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/18
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_material_materialfactory.h"

#include "fw/raytracing_fw_types.h"
#include "fw/material/raytracing_fw_material_lambertmaterial.h"
#include "fw/material/raytracing_fw_material_directionallight.h"
#include "fw/material/raytracing_fw_material_arealight.h"

namespace raytracing { namespace fw { namespace material {

std::unique_ptr<ttIMaterial>
ttMaterialFactory::createMaterial(ttMaterialType type) {
    ttIMaterial* mat = nullptr;
    switch (type) {
    case ttMaterialType::LAMBERT:
        mat = new ttLambertMaterial();
        break;
    case ttMaterialType::DIRECTIONAL_LIGHT:
        mat = new ttDirectionalLight();
        break;
    case ttMaterialType::AREA_LIGHT:
        mat = new ttAreaLight();
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

void
ttMaterialFactory::setupDirectionalLight(ttIMaterial* mat, const ttVector& lightColor, const ttVector& lightDir) {
    auto light = static_cast<ttDirectionalLight*>(mat);
    light->setLightColor(lightColor);
    light->setLightDirection(lightDir);
}

void
ttMaterialFactory::setupAreaLight(ttIMaterial* mat, const ttVector& lightColor) {
    auto light = static_cast<ttAreaLight*>(mat);
    light->setLightColor(lightColor);
}

}}}
