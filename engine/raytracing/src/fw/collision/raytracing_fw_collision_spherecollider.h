// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/collision/raytracing_fw_collision_icollider.h"

namespace raytracing { namespace fw { namespace collision { 

class ttSphereCollider : public ttICollider {
public:
    ttSphereCollider();
    virtual ~ttSphereCollider();
    virtual bool intersect(const ttRay& ray, float a_near, float a_far, IntersectInfo* info) const override;

public:
    //! 球情報を取得
    const ttSphere& getSphere() const;
    //! 球の中心座標を取得
    const ttVector& getCenter() const;
    //! 球の半径を取得
    float getRadius() const;

    //! 球を設定
    void setSphere(const ttSphere& sphere);
    //! 球の中心座標を取得
    void setCenter(const ttVector& center);
    //! 球の半径を取得
    void setRadius(float radius);

private:
    struct Member;
    std::unique_ptr<Member> m_;
};

}}}
