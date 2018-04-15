// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { namespace fw { 

class ttRandom {
public:
    ttRandom();
    ~ttRandom();

    int range(int min, int max);
    float range(float min, float max);
    double range(double min, double max);

private:
    struct Member;
    std::unique_ptr<Member> m_;

private:
    ttNONCOPYABLE(ttRandom);
};

}}
