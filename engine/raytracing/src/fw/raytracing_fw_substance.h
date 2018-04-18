// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { 

namespace collision {
class ttICollider;
enum class ttColliderType;
}
namespace material {
class ttIMaterial;
enum class ttMaterialType;
}

class ttSubstance {
public:
    ttSubstance();
    ~ttSubstance();

    void moveCollider(std::unique_ptr<collision::ttICollider>& collider);

    void moveMaterial(std::unique_ptr<material::ttIMaterial>& material);

    collision::ttICollider* getCollider() const {
        return collider_.get();
    }
    material::ttIMaterial* getMaterial() const {
        return material_.get();
    }

private:
    std::unique_ptr<collision::ttICollider> collider_;
    std::unique_ptr<material::ttIMaterial> material_;
};

}}
