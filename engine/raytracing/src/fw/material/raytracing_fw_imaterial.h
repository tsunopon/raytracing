// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/raytracing_fw_types.h"

namespace raytracing { namespace fw { namespace material { 

class ttIMaterial {
public:
    //! デストラクタ
    virtual ~ttIMaterial() {}

    //! 光源かどうか
    virtual bool isLight() const = 0;

    //! 放射輝度を取得
    virtual ttVector getRadiance(const ttRay& outRay, const ttVector& point, const ttVector& normal) const = 0;

    //! 反射関数を取得
    virtual ttVector function(const ttRay& inRay, const ttRay& outRay, const ttVector& normal) const = 0;
};

}}}
