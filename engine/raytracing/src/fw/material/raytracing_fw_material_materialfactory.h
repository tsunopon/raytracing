// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { namespace material { 

class ttIMaterial;
enum class ttMaterialType;

class ttMaterialFactory {
public:
    static std::unique_ptr<ttIMaterial> createMaterial(ttMaterialType type);
    static void setupLambert(ttIMaterial* mat, const ttVector& albedo);
    static void setupDirectionalLight(ttIMaterial* mat, const ttVector& lightColor, const ttVector& lightDir);
    static void setupAreaLight(ttIMaterial* mat, const ttVector& lightColor);
};

}}}
