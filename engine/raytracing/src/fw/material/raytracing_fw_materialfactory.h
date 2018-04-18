// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { namespace material { 

class ttIMaterial;

enum class ttMaterialType {
    LAMBERT = 0,
};

class ttMaterialFactory {
public:
    static std::unique_ptr<ttIMaterial> createMaterial(ttMaterialType type);
    static void setupLambert(ttIMaterial* mat, const ttVector& albedo);
};

}}}
