// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { 
    
namespace collision {
class ttICollider;
enum class ttColliderType;
struct ttIntersectInfo;
}
namespace material {
class ttIMaterial;
enum class ttMaterialType;
}

namespace sub { 

class ttISubstance {
public:
    virtual ~ttISubstance() {}

    virtual collision::ttICollider* getCollider() const = 0;
    virtual material::ttIMaterial* getMaterial() const = 0;

    virtual bool getRadiance(const ttRay& ray, const collision::ttIntersectInfo& info, ttVector* color) const = 0;
};

}}}
