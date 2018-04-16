// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_lds.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/15
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_lds.h"

namespace raytracing { namespace fw {

ttVanDerCorputSequence::ttVanDerCorputSequence(uint32_t base, uint32_t cacheCapacity) {
    base_ = base;
    if(cacheCapacity > 0) {
        cache_.resize(cacheCapacity);
        for(auto& c : cache_) {
            c = -1.0f;
        }
    }
}

ttVanDerCorputSequence::~ttVanDerCorputSequence() {
}

float
ttVanDerCorputSequence::get(uint32_t base, uint32_t index) {
    float h = 0.0f;
    float f, factor;
    f = factor = 1.0f / base;
    while(index > 0) {
        h += (index % base) * factor;
        index /= base;
        factor *= f;
    }
    return h;
}

float
ttVanDerCorputSequence::get(uint32_t index) {
    if(index < cache_.size()) {
        auto result = cache_[index];
        if(result > 0.0f) {
            return result;
        }
        cache_[index] = get(base_, index);
        return cache_[index];
    }
    return get(base_, index);
}

ttHaltonSequence::ttHaltonSequence(uint32_t dimension, uint32_t cacheCapacity) {
    ttASSERT(dimension >= 1 && dimension <= 4 && "次元数は1<=n<=4である必要があります");

    uint32_t bases[4] = {2, 3, 5, 7};
    sequences_.reserve(dimension);
    for(auto Li = 0U; Li < dimension; ++Li) {
        sequences_.emplace_back(bases[Li], cacheCapacity);
    }
}

ttHaltonSequence::~ttHaltonSequence() {
}

ttVector ttHaltonSequence::get(uint32_t index) {
    ttVector result;
    for(auto Li = 0; Li < sequences_.size(); ++Li) {
        result[Li] = sequences_[Li].get(index);
    }
    return result;
}

}}
