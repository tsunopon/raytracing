// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/sub/raytracing_fw_sub_isubstance.h"

namespace raytracing { namespace fw { namespace sub {

class ttSubstance : public ttISubstance {
public:
    ttSubstance();
    virtual ~ttSubstance();

    virtual collision::ttICollider* getCollider() const override {
        return collider_.get();
    }
    virtual material::ttIMaterial* getMaterial() const override {
        return material_.get();
    }
    virtual bool getRadiance(const ttRay& ray, const collision::ttIntersectInfo& info, ttVector* color) const override;

public:
    void moveCollider(std::unique_ptr<collision::ttICollider>& collider);

    void moveMaterial(std::unique_ptr<material::ttIMaterial>& material);

private:
    std::unique_ptr<collision::ttICollider> collider_;
    std::unique_ptr<material::ttIMaterial> material_;
};

}}}
