// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "fw/material/raytracing_fw_material_imaterial.h"

namespace raytracing { namespace fw { namespace material { 

class ttLambertMaterial : public ttIMaterial {
public:
    ttLambertMaterial();
    virtual ~ttLambertMaterial();

    //! 光源かどうか
    virtual bool isLight() const override {
        return false;
    }

    //! 放射輝度を取得
    virtual ttVector getRadiance(const ttRay& outRay, const ttVector& point) const override;

    //! 反射関数を取得
    virtual ttVector function(const ttRay& inRay, const ttRay& outRay, const ttVector& normal) const override;

    //! 次のレイを取得
    //! param[in] point     基点
    //! param[in] normal    法線
    //! param[in] inDir     入力ベクトル
    //! param[in] random    乱数
    //! param[out] ray      出力レイ
    //! param[out] pdf      確率密度関数
    virtual void getNextRay(
                    const ttVector& point,
                    const ttVector& normal,
                    const ttVector& inDir,
                    ttRandom& random,
                    ttRay* ray,
                    float* pdf) const override;

public:
    void setAlbedo(float r, float g, float b);

private:
    ttVector albedo_;
    ttVector funcValue_;
};

}}}
