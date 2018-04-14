// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/raytracing_fw_vecmath.h"

namespace raytracing { namespace fw {

//! レイ
struct ttRay {
    ttVector base;          //!< 基点座標
    ttVector direction;     //!< 向き
};

//! 球
struct ttSphere {
    ttVector center;        //!< 中心座標
    float radius = 0.0f;    //!< 半径
};

//! 長方形
struct ttRectangle {
    union {
        float f32[4] = {};
        struct {
            float x;
            float y;
            float width;
            float height;
        };
    };
};

//! Axis Aligned Bounding Box
struct ttAABB {
    ttVector minimum;       //! 最小値座標
    ttVector maximum;       //! 最大値座標
};

}}
