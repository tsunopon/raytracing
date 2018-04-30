// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { namespace material { 

class ttIMaterial;

enum class ttMaterialType {
    LAMBERT = 0,
    DIRECTIONAL_LIGHT = 1000,
    AREA_LIGHT,
};

class ttMaterialFactory {
public:
    static std::unique_ptr<ttIMaterial> createMaterial(ttMaterialType type);
    static void setupLambert(ttIMaterial* mat, const ttVector& albedo);
    static void setupDirectionalLight(ttIMaterial* mat, const ttVector& lightColor);
    static void setupAreaLight(ttIMaterial* mat, const ttVector& lightColor);
};

}}}
