// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { 

//! 1次元の低食い違い量列(Low Discrepancy Sequences)
class ttVanDerCorputSequence {
public:
    ttVanDerCorputSequence(uint32_t base, uint32_t cacheCapacity);
    ~ttVanDerCorputSequence();

    float get(uint32_t index);
    static float get(uint32_t base, uint32_t index);

private:
    uint32_t base_;
    std::vector<float> cache_;
};

//! n次元の低食い違い量列(最大4次元まで)
class ttHaltonSequence {
public:
    ttHaltonSequence(uint32_t dimension, uint32_t cacheCapacity);
    ~ttHaltonSequence();

    ttVector get(uint32_t index);

private:
    std::vector<ttVanDerCorputSequence> sequences_;
};
    
}}
