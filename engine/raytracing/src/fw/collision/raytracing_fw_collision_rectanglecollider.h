// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/collision/raytracing_fw_collision_icollider.h"

namespace raytracing { namespace fw { namespace collision { 

class ttRectangleCollider : public ttICollider {
public:
    ttRectangleCollider();
    virtual ~ttRectangleCollider();

    //! 中心の位置を設定
    void setCenter(const ttVector& center);
    //! 面の向きを設定
    void setNormal(const ttVector& normal);
    //! アップベクトルを設定(長方形の回転を制御)
    void setUpVector(const ttVector& up);
    //! 長方形を設定
    void setRectSize(float width, float height);
    //! 長方形の幅を設定
    void setRectWidth(float width);
    //! 長方形の高さを設定
    void setRectHeight(float height);
    //! 背面を有効にするかどうかを設定
    void enableFilpBackFace(bool enable);

    //! @brief      衝突判定
    //! @param[in]  ray     レイ
    //! @param      a_naer  レイの範囲(近接位置)
    //! @param      a_far   レイの範囲(最遠位置)
    //! @param[out] info    衝突情報
    //! @return     bool    衝突したかどうか
    virtual bool intersect(const ttRay& ray, float a_near, float a_far, IntersectInfo* info) const = 0;

private:
    void updateLocalBasis_();

private:
    struct Member;
    std::unique_ptr<Member> m_;

private:
    ttNONCOPYABLE(ttRectangleCollider);
};

}}}
