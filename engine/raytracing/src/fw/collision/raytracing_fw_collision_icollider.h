// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/raytracing_fw_forward.h"
#include "fw/raytracing_fw_vecmath.h"
#include "fw/raytracing_fw_types.h"

namespace raytracing { namespace fw { namespace collision {

//! 交差情報
struct IntersectInfo {
    float t = 0.0f;     //!< レイの交差位置
    ttVector point;     //!< 交差座標
    ttVector normal;    //!< 交差点の法線
};

//! 衝突判定を行うクラスのインターフェース
class ttICollider {
public:
    virtual ~ttICollider() {}

    //! コリジョンの種類を取得
    virtual ttColliderType getColliderType() const = 0;

    //! @brief      衝突判定
    //! @param[in]  ray     レイ
    //! @param      a_naer  レイの範囲(近接位置)
    //! @param      a_far   レイの範囲(最遠位置)
    //! @param[out] info    衝突情報
    //! @return     bool    衝突したかどうか
    virtual bool intersect(const ttRay& ray, float a_near, float a_far, IntersectInfo* info) const = 0;
};

}}}
