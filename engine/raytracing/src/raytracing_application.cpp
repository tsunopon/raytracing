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
    char progressText[128] = "";
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
            m_->camera.setEyePos(ttVector(0.0f, 0.5f, 2.0f, 0.0f));
            m_->camera.setLookAt(ttVector(0.0f, 0.25f, 0.0f, 0.0f));
            m_->camera.setUpVector(ttVector(0.0f, 1.0f, 0.0f, 0.0f));

            // 球配置
            auto sphere = std::unique_ptr<collision::ttSphereCollider>(new collision::ttSphereCollider());
            sphere->setCenter(ttVector(0.0f, 0.0f, -1.0f, 0.0f));
            sphere->setRadius(0.5f);
            m_->scene.push_back(std::move(sphere));

            auto sphere2 = std::unique_ptr<collision::ttSphereCollider>(new collision::ttSphereCollider());
            sphere2->setCenter(ttVector(0.0f, -100.5f, -1.0f, 0.0f));
            sphere2->setRadius(100.0f);
            m_->scene.push_back(std::move(sphere2));
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
    quit_ = true;
    while(!enableTerminate_){
        Sleep(1);
    }
    m_.reset();
}

static float
drand48() {
    return float(((double)(rand()) / (RAND_MAX))); /* RAND_MAX = 32767 */
}

static ttVector
randomVector() {
    return ttVector(drand48(), drand48(), drand48(), 0.0f);
}

static ttVector
randomUnitSphere() {
    ttVector p;
    do {
        p = 2.0f * randomVector() - ttVector(1.0f, 1.0f, 1.0f, 0.0f);
    } while (p.dot(p) >= 1.0f);
    return p;
}

static ttVector
getBackgroundSky(const ttVector& dir) {
    ttVector n = ttVector::normalize(dir);
    float t = 0.5f * (n.y + 1.0f);
    ttVector base(1.0f, 1.0f, 1.0f, 0.0f);
    ttVector target(0.5, 0.7f, 1.0f, 0.0f);
    return  (target - base) * t + base;
}

static ttVector
getColor(const ttRay& ray, const std::vector<std::unique_ptr<fw::collision::ttICollider>>& scene, uint32_t depth) {
    bool intersected = false;
    float distance = 100000000.0f;
    collision::IntersectInfo info;
    for(auto& collider : scene) {
        if(collider->intersect(ray, 0.001f, distance, &info)) {
            distance = info.t;
            intersected = true;
        }
    }
    
    if(intersected && depth < 50) {
        ttRay nextRay;
        nextRay.base = info.point;
        ttVector target = info.point + info.normal + randomUnitSphere();
        nextRay.direction = target - info.point; 
        nextRay.direction.w = 0.0f;
        return 0.3f * getColor(nextRay, scene, depth + 1);
    } else {
        return getBackgroundSky(ray.direction);
    }
}

void
ttApplication::run() {
    ttRay ray;
    enableTerminate_ = false;
    m_->finished = false;
    m_->isRunning = true;
    std::unique_ptr<float[]> buffer;
    buffer.reset(new float[m_->width * m_->height * 4U]);
    memset(buffer.get(), 0, sizeof(float) * m_->width * m_->height * 4U);
    sprintf_s(m_->progressText, sizeof(m_->progressText), "RayTrace: %d/%d", 0, m_->samplingCount);
    for(auto Ls = 0U; Ls < m_->samplingCount && !quit_; ++Ls) {
        for(auto Lh = 0U; Lh < m_->height && !quit_; ++Lh) {
            for(auto Lw = 0U; Lw < m_->width && !quit_; ++Lw) {
                uint32_t index = Lw * 4U + Lh * m_->width * 4U;
                float u = static_cast<float>(Lw) / m_->width;
                float v = static_cast<float>(Lh) / m_->height;
                m_->camera.getRay(u, v, Ls, &ray);
                auto color = getColor(ray, m_->scene, 0);
                buffer[index + 0] += color.x;
                buffer[index + 1] += color.y;
                buffer[index + 2] += color.z;
                buffer[index + 3] += 1.0f;
                m_->pixels[index + 0] = std::pow(buffer[index + 0] / buffer[index + 3], 1 / 2.2f);
                m_->pixels[index + 1] = std::pow(buffer[index + 1] / buffer[index + 3], 1 / 2.2f);
                m_->pixels[index + 2] = std::pow(buffer[index + 2] / buffer[index + 3], 1 / 2.2f);
                m_->pixels[index + 3] = 1.0f;
            }
        }
        sprintf_s(m_->progressText, sizeof(m_->progressText), "RayTrace: %d/%d", Ls + 1, m_->samplingCount);
    }
    m_->finished = true;
    m_->isRunning = false;
    enableTerminate_ = true;
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

const char*
ttApplication::getProgressText() const {
    return m_->progressText;
}

}
