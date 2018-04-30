// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/sub/raytracing_fw_sub_isubstance.h"

namespace raytracing { namespace fw { 
    
namespace material {
class ttAreaLight;
}
    
namespace sub { 

class ttAreaLightSubstance : public ttISubstance {
public:
    ttAreaLightSubstance();
    virtual ~ttAreaLightSubstance();

    virtual collision::ttICollider* getCollider() const override {
        return collider_.get();
    }
    virtual material::ttIMaterial* getMaterial() const override;
    virtual bool getRadiance(const ttRay& ray, const collision::ttIntersectInfo& info, ttVector* color) const override;

public:
    void moveCollider(std::unique_ptr<collision::ttICollider>& collider);
    void setLightColor(const ttVector& color);

private:
    std::unique_ptr<collision::ttICollider> collider_;
    std::unique_ptr<material::ttAreaLight> material_;
};

}}}
