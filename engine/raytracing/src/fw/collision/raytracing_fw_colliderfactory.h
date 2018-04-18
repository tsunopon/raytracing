// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { namespace collision { 

class ttICollider;

enum class ttColliderType {
    SPHERE = 0,
};

class ttColliderFactory {
public:
    static std::unique_ptr<ttICollider> createCollder(ttColliderType type);
    static void setupSphere(ttICollider* collider, float radius, const ttVector& center);
};

}}}
