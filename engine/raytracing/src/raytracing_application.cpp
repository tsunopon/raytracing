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

#include "fw/raytracing_fw_substance.h"
#include "fw/collision/raytracing_fw_collision_colliderfactory.h"
#include "fw/collision/raytracing_fw_collision_icollider.h"
#include "fw/material/raytracing_fw_material_materialfactory.h"
#include "fw/material/raytracing_fw_material_imaterial.h"
#include "fw/raytracing_fw_camera.h"
#include "fw/raytracing_fw_types.h"
#include "fw/raytracing_fw_random.h"
#include "fw/raytracing_fw_lds.h"


namespace raytracing { 

struct ttApplication::Member {
    uint32_t width = 0U;
    uint32_t height = 0U;
    uint32_t samplingCount = 0U;
    std::vector<std::unique_ptr<ttSubstance>> scene;
    std::unique_ptr<uint32_t[]> pixels;
    ttCamera camera;
    bool finished = false;
    bool isRunning = false;
    char progressText[128] = "";
    ttRandom rand;
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
            m_->camera.setEyePos(ttVector(0.0f, 2.0f, 8.0f, 0.0f));
            m_->camera.setLookAt(ttVector(0.0f, 0.0f, 0.0f, 0.0f));
            m_->camera.setUpVector(ttVector(0.0f, 1.0f, 0.0f, 0.0f));
            m_->camera.update();

            ttVector colors[6] = {
                ttVector(1.0f, 0.2f, 0.2f, 1.0f),
                ttVector(0.2f, 1.0f, 0.2f, 1.0f),
                ttVector(0.2f, 0.2f, 1.0f, 1.0f),
                ttVector(1.0f, 1.0f, 0.2f, 1.0f),
                ttVector(0.2f, 1.0f, 1.0f, 1.0f),
                ttVector(1.0f, 0.2f, 1.0f, 1.0f),
            };
            // 球の配置
            for(auto Li = 0; Li < 6; ++Li) {
                auto sphere = std::unique_ptr<ttSubstance>(new ttSubstance());
                auto collider = collision::ttColliderFactory::createCollder(collision::ttColliderType::SPHERE);
                collision::ttColliderFactory::setupSphere(collider.get(), 0.5f, ttVector(2.5f - 1.0f * Li, 0.0f, 0.0f, 0.0f)); 
                auto mat = material::ttMaterialFactory::createMaterial(material::ttMaterialType::LAMBERT);
                material::ttMaterialFactory::setupLambert(mat.get(), colors[Li % 6]);
                sphere->moveCollider(collider);
                sphere->moveMaterial(mat);
                m_->scene.push_back(std::move(sphere));
            }

            // 箱を配置
            {
                auto box = std::unique_ptr<ttSubstance>(new ttSubstance());
                auto collider = collision::ttColliderFactory::createCollder(collision::ttColliderType::BOX);
                collision::ttColliderFactory::setupBox(
                    collider.get(),
                    ttVector(0.0f, 0.0f, 1.5f, 0.0f),
                    ttVector(1.0f, 0.0f, 1.0f, 0.0f),
                    ttVector(0.0f, 1.0f, 0.0f, 0.0f),
                    ttVector(1.0f, 1.0f, 1.0f, 0.0f), true);
                auto mat = material::ttMaterialFactory::createMaterial(material::ttMaterialType::LAMBERT);
                material::ttMaterialFactory::setupLambert(mat.get(), ttVector(1.0f, 1.0f, 1.0f, 0.0f));
                box->moveCollider(collider);
                box->moveMaterial(mat);
                m_->scene.push_back(std::move(box));
            }

            // 球の配置
            {
                auto sphere = std::unique_ptr<ttSubstance>(new ttSubstance());
                auto collider = collision::ttColliderFactory::createCollder(collision::ttColliderType::SPHERE);
                collision::ttColliderFactory::setupSphere(collider.get(), 1000.0f, ttVector(0.0f, -1000.5f, 0.0f, 0.0f)); 
                auto mat = material::ttMaterialFactory::createMaterial(material::ttMaterialType::LAMBERT);
                material::ttMaterialFactory::setupLambert(mat.get(), ttVector(1.0f, 0.5f, 0.5f, 0.0f));
                sphere->moveCollider(collider);
                sphere->moveMaterial(mat);
                m_->scene.push_back(std::move(sphere));
            }

            // ライトの配置
            {
                auto light = std::unique_ptr<ttSubstance>(new ttSubstance());
                auto collider = collision::ttColliderFactory::createCollder(collision::ttColliderType::RECTANGLE);
                collision::ttColliderFactory::setupRectangle(
                    collider.get(),
                    3.0f, 3.0f,                                 // size
                    ttVector(3.0, 2.0f, 1.0f, 0.0f),            // center
                    ttVector(-1.0f, 0.0f, 0.0f, 0.0f),          // normal
                    ttVector(0.0f, 1.0f, 0.0f, 0.0f), false);    // up
                auto mat = material::ttMaterialFactory::createMaterial(material::ttMaterialType::AREA_LIGHT);
                material::ttMaterialFactory::setupAreaLight(mat.get(), ttVector(5.0f, 5.0f, 5.0f, 0.0f));
                light->moveCollider(collider);
                light->moveMaterial(mat);
                m_->scene.push_back(std::move(light));
            }
        }

        // 描画バッファ確保
        m_->pixels.reset(new uint32_t[m_->width * m_->height]);
        for(auto Lh = 0U; Lh < m_->height; ++Lh) {
            for(auto Lw = 0U; Lw < m_->width; ++Lw) {
                uint32_t index = Lw + Lh * m_->width;
                m_->pixels[index] = 0U;
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
    Sleep(1);
    m_.reset();
}

bool
ttApplication::getRadiance_(const ttRay& ray, const ttVector& prevNormal, uint32_t depth, ttVector* color) const {
    ttUNUSED(prevNormal);
    bool intersected = false;
    float distance = 100000000.0f;
    collision::IntersectInfo info;
    material::ttIMaterial* mat = nullptr;
    for(auto& substance : m_->scene) {
        auto collider = substance->getCollider();
        if(collider->intersect(ray, 0.001f, distance, &info)) {
            distance = info.t;
            intersected = true;
            mat = substance->getMaterial();
        }
    }
    
    if(intersected && mat) {
        if(mat->isLight()) {
            *color = mat->getRadiance(ray, info.point);
            return true;
        } else if(depth < 100) {
            ttRay nextRay;
            float pdf;
            mat->getNextRay(info.point, info.normal, ray.direction, m_->rand, &nextRay, &pdf);
            ttVector c;
            nextRay.direction.normalize();
            if(getRadiance_(nextRay, info.normal, depth + 1, &c)) {
                c.w += max(0.000001f, pdf);
                float tmp = color->w;
                *color = c * mat->function(nextRay, ray, info.normal) * max(0.0f, nextRay.direction.dot(info.normal)) / max(0.000001f, pdf);
                color->w = tmp + pdf;
                return true;
            }
        }
        // 平行光源の処理
        intersected = false;
        distance = 100000000.0f;
        ttVector lightDir = ttVector(2.0f, -1.0f, 1.0f, 0.0f).normalize();
        ttRay nextRay;
        nextRay.direction = -1.0f * lightDir;
        nextRay.base = info.point;
        for(auto& substance : m_->scene) {
            auto collider = substance->getCollider();
            if(collider->intersect(nextRay, 0.001f, distance, &info)) {
                intersected = true;
                break;
            }
        }
        if(!intersected) {
            *color = ttVector(5.0f, 5.0f, 5.0f, 0.0f) * mat->function(nextRay, ray, info.normal) * max(0.0f, nextRay.direction.dot(info.normal));
            color->w = 1.0f;
        } else {
            *color = ttVector();
            color->w = 1.0f;
        }
        return true;
    }
    *color = ttVector();
    color->w = 1.0f;
    return false;
}

static
uint32_t getUint32Color(const float pixels[], uint32_t index) {
    const float GUMMA = 1 / 2.2f;
    auto weight = 1.0f / pixels[index + 3];
    float r = 1.0f - std::exp(-1.0f * pixels[index + 0] * weight);
    float g = 1.0f - std::exp(-1.0f * pixels[index + 1] * weight);
    float b = 1.0f - std::exp(-1.0f * pixels[index + 2] * weight);
    uint32_t r1 = static_cast<uint32_t>(std::pow(r, GUMMA) * 255);
    uint32_t g1 = static_cast<uint32_t>(std::pow(g, GUMMA) * 255);
    uint32_t b1 = static_cast<uint32_t>(std::pow(b, GUMMA) * 255);
    return (min(r1, 255U) << 16) | (min(g1, 255U) << 8) | min(b1, 255U);
}

void ttApplication::calcPixel_(uint32_t Ls, uint32_t Li, const ttVector& offset, float buffer[]) const {
    uint32_t Lw = Li % m_->width;
    uint32_t Lh = Li / m_->width;
    uint32_t index = Lw * 4U + Lh * m_->width * 4U;
    float u = (offset.x + Lw) / m_->width;
    float v = (offset.y + Lh) / m_->height;
    ttRay ray;
    m_->camera.getRay(u, v, Ls, &ray);
    ttVector color;
    getRadiance_(ray, ttVector(0.0f, 1.0f, 0.0f, 0.0f), 0, &color);
    buffer[index + 0] += color.x;
    buffer[index + 1] += color.y;
    buffer[index + 2] += color.z;
    buffer[index + 3] += 1.0f;
    m_->pixels[Li] = getUint32Color(buffer, index);

}

void
ttApplication::run() {
    enableTerminate_ = false;
    m_->finished = false;
    m_->isRunning = true;
    std::unique_ptr<float[]> buffer;
    buffer.reset(new float[m_->width * m_->height * 4U]);
    memset(buffer.get(), 0, sizeof(float) * m_->width * m_->height * 4U);
    sprintf_s(m_->progressText, sizeof(m_->progressText), "RayTrace: %d/%d", 0, m_->samplingCount);
    ttHaltonSequence halton(2, 0);
    for(auto Ls = 0U; Ls < m_->samplingCount && !quit_; ++Ls) {
        ttVector offset = halton.get(Ls);
#pragma omp parallel for schedule(dynamic, 1)
        for(auto Li = 0; Li < static_cast<int>(m_->height * m_->width); ++Li) {
            if(!quit_) {
                calcPixel_(Ls, Li, offset, buffer.get());
            }
        }
        sprintf_s(m_->progressText, sizeof(m_->progressText), "RayTrace: %d/%d", Ls + 1, m_->samplingCount);
    }
    m_->finished = true;
    m_->isRunning = false;
    enableTerminate_ = true;
}

const uint32_t*
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

bool
ttApplication::enabled() const {
    return (m_->isRunning || m_->finished) && !quit_;
}

}
