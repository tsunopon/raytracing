// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_application.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/15
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_application.h"

#include "fw/collision/raytracing_fw_collision_spherecollider.h"
#include "fw/raytracing_fw_camera.h"
#include "fw/raytracing_fw_types.h"


namespace raytracing { 

struct ttApplication::Member {
    uint32_t width = 0U;
    uint32_t height = 0U;
    uint32_t samplingCount = 0U;
    std::vector<std::unique_ptr<fw::collision::ttICollider>> scene;
    std::unique_ptr<float[]> pixels;
    ttCamera camera;
    bool finished = false;
    bool isRunning = false;
};

ttApplication::ttApplication() {
    m_.reset(new Member());
}

ttApplication::~ttApplication() {
}

bool
ttApplication::initialize(const ttApplicationArgs& args) {
    m_->width = args.width;
    m_->height = args.height;
    m_->samplingCount = args.samplingCount;
    m_->finished = false;
    m_->isRunning = false;
    if(m_->width > 0 && m_->height > 0 && m_->samplingCount > 0) {
        m_->scene.reserve(1);
        // シーン構築
        {
            // カメラ設定
            m_->camera.setAspectRatio(static_cast<float>(m_->width) / m_->height);
            m_->camera.setVerticalFOV(45.0f);
            m_->camera.setMasSamplingCount(m_->samplingCount);
            m_->camera.setEyePos(ttVector(0.0f, 0.0f, 0.0f, 0.0f));
            m_->camera.setLookAt(ttVector(0.0f, 0.0f, -1.0f, 0.0f));
            m_->camera.setUpVector(ttVector(0.0f, 1.0f, 0.0f, 0.0f));

            // 球配置
            auto sphere = std::unique_ptr<collision::ttSphereCollider>(new collision::ttSphereCollider());
            sphere->setCenter(ttVector(0.0f, 0.0f, -3.0f, 0.0f));
            sphere->setRadius(1.0f);
            m_->scene.push_back(std::move(sphere));
        }

        // 描画バッファ確保
        m_->pixels.reset(new float[m_->width * m_->height * 4U]);
        for(auto Lh = 0U; Lh < m_->height; ++Lh) {
            for(auto Lw = 0U; Lw < m_->width; ++Lw) {
                uint32_t index = Lw * 4U + Lh * m_->width * 4U;
                m_->pixels[index + 0U] = 0.0f;
                m_->pixels[index + 1U] = 0.0f;
                m_->pixels[index + 2U] = 0.0f;
                m_->pixels[index + 3U] = 0.0f;
            }
        }
        return true;
    }
    return false;
}

void
ttApplication::terminate() {
    m_.reset();
}

void
ttApplication::run() {
    ttRay ray;
    m_->finished = false;
    m_->isRunning = true;
    for(auto Lh = 0U; Lh < m_->height; ++Lh) {
        for(auto Lw = 0U; Lw < m_->width; ++Lw) {
            for(auto Ls = 0U; Ls < m_->samplingCount; ++Ls) {
                uint32_t index = Lw * 4U + Lh * m_->width * 4U;
                float u = static_cast<float>(Lw) / m_->width;
                float v = static_cast<float>(Lh) / m_->height;
                m_->camera.getRay(u, v, Ls, &ray);
                bool intersected = false;
                float distance = 100000000.0f;
                collision::IntersectInfo info;
                for(auto& collider : m_->scene) {
                    if(collider->intersect(ray, 0.00001f, distance, &info)) {
                        distance = info.t;
                        intersected = true;
                    }
                }
                if(intersected) {
                    m_->pixels[index + 0U] = 1.0f;
                    m_->pixels[index + 1U] = 0.0f;
                    m_->pixels[index + 2U] = 0.0f;
                    m_->pixels[index + 3U] = 0.0f;
                } else {
                    m_->pixels[index + 0U] = 0.0f;
                    m_->pixels[index + 1U] = 0.5f;
                    m_->pixels[index + 2U] = 1.0f;
                    m_->pixels[index + 3U] = 0.0f;
                }
            }
        }
    }
    m_->finished = true;
    m_->isRunning = false;
}

const float*
ttApplication::getPixels() const{
    return m_->pixels.get();
}

bool
ttApplication::finished() const {
    return m_->finished;
}

bool
ttApplication::isRunning() const {
    return m_->isRunning;
}

}
