// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_fw_random.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/15
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_fw_random.h"

#include <random>

namespace raytracing { namespace fw { 

struct ttRandom::Member {
    std::mt19937 mt;
};

ttRandom::ttRandom() {
    m_.reset(new Member());
}

ttRandom::~ttRandom() {
}

int
ttRandom::range(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_->mt);
}

float
ttRandom::range(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_->mt);
}

double
ttRandom::range(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(m_->mt);
}

}}
