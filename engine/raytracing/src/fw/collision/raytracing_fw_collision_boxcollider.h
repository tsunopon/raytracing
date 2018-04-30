// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/collision/raytracing_fw_collision_icollider.h"

namespace raytracing { namespace fw { namespace collision { 

class ttBoxCollider : public ttICollider {
public:
    ttBoxCollider();
    virtual ~ttBoxCollider();

    //! セットアップ
    void setup(const ttVector& center,
               const ttVector& dir,
               const ttVector& up,
               const ttVector& size,
               bool enableFlipBackFace);

    //! 中心の位置を設定
    void setCenter(const ttVector& center);
    //! 向きを設定
    void setDirection(const ttVector& normal);
    //! アップベクトルを設定(回転を制御)
    void setUpVector(const ttVector& up);
    //! 長方形を設定
    void setBoxSize(float xSize, float ySize, float zSize);
    //! 背面を有効にするかどうかを設定
    void setEnableFilpBackFace(bool enable);

    //! @brief      衝突判定
    //! @param[in]  ray     レイ
    //! @param      a_naer  レイの範囲(近接位置)
    //! @param      a_far   レイの範囲(最遠位置)
    //! @param[out] info    衝突情報
    //! @return     bool    衝突したかどうか
    virtual bool intersect(const ttRay& ray, float a_near, float a_far, IntersectInfo* info) const;

private:
    void setup_();

private:
    struct Member;
    std::unique_ptr<Member> m_;

private:
    ttNONCOPYABLE(ttBoxCollider);
};

}}}
