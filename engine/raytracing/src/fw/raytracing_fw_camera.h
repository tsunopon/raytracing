// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { 

class ttCamera {
public:
    ttCamera();
    ~ttCamera();

    //! u, vピクセル位置でのレイを取得
    //! @param      u           スクリーンのU座標
    //! @param      v           スクリーンのV座標
    //! @param      sampleIndex 何個目のサンプリング点か？(0, 1, ..., n)
    //! @param[out] ray         レイ
    void getRay(float u, float v, uint32_t sampleIndex, ttRay* ray) const;

public:
    //! カメラの注視点を取得
    const ttVector& getLookAt() const {
        return lookat_;
    }
    //! カメラの座標を取得
    const ttVector& getEyePos() const {
        return eye_;
    }
    //! カメラのアップベクトルを取得
    const ttVector& getUpVector() const {
        return up_;
    }
    //! カメラのアスペクト比を取得
    float getAspectRatio() const {
        return aspect_;
    }
    //! カメラの垂直視野角を度単位で取得
    float getVerticalFOVDegree() const {
        return vfovDegree_;
    }
    //! 最大サンプリング数を取得
    uint32_t getMaxSamplingCount() const {
        return maxSamplingCount_;
    }

    //! カメラの注視点を設定
    void setLookAt(const ttVector& lookat) {
        lookat_ = lookat;
    }
    //! カメラの座標を設定
    void setEyePos(const ttVector& eye) {
        eye_ = eye;
    }
    //! カメラのアップベクトルを設定
    void setUpVector(const ttVector& up) {
        up_ = up;
    }
    //! カメラのアスペクト比を設定
    void setAspectRatio(float aspect) {
        aspect_ = aspect;
    }
    //! カメラの垂直視野角を度単位で設定
    void setVerticalFOV(float degree) {
        vfovDegree_ = degree;
    }
    //! 最大サンプリング数を設定
    void setMasSamplingCount(uint32_t count);

    void update();

private:
    ttVector lookat_ = ttVector(0.0f, 0.0f, -1.0f, 0.0f);
    ttVector eye_ = ttVector(0.0f, 0.0f, 0.0f, 0.0f);
    ttVector up_ = ttVector(0.0, 1.0f, 0.0, 0.0f);
    float aspect_ = 1.0f;
    float vfovDegree_ = 45.0f;
    uint32_t maxSamplingCount_ = 1U;

    ttVector baseU_; // カメラのビュー空間のx軸
    ttVector baseV_; // カメラのビュー空間のy軸
    ttVector baseW_; // カメラのビュー空間のz軸

};

}}
