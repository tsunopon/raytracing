// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { namespace collision { 

class ttICollider;

enum class ttColliderType {
    SPHERE = 0,
    RECTANGLE,
};

class ttColliderFactory {
public:
    static std::unique_ptr<ttICollider> createCollder(ttColliderType type);
    static void setupSphere(ttICollider* collider, float radius, const ttVector& center);
    static void setupRectangle(
                    ttICollider* collider,
                    float width, float height,
                    const ttVector& center, const ttVector& normal, const ttVector& up,
                    bool enableFlipBackFace);
};

}}}
