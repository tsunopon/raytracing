// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing {

struct ttWindowParam {
    const char* windowName = nullptr;
    bool fullScreen = false;
    uint32_t width = 256U;
    uint32_t height = 256U;
};

}
