// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/material/raytracing_fw_imaterial.h"

namespace raytracing { namespace fw { namespace material { 

class ttLambertMaterial : public ttIMaterial {
public:
    ttLambertMaterial();
    virtual ~ttLambertMaterial();

    //! 光源かどうか
    virtual bool isLight() const override {
        return false;
    }

    //! 放射輝度を取得
    virtual ttVector getRadiance(const ttRay& outRay, const ttVector& point, const ttVector& normal) const override;

    //! 反射関数を取得
    virtual ttVector function(const ttRay& inRay, const ttRay& outRay, const ttVector& normal) const override;

    void setAlbedo(float r, float g, float b);

private:
    ttVector albedo_;
    ttVector funcValue_;
};

}}}
