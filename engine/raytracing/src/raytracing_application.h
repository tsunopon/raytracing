﻿// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

namespace raytracing { 

struct ttApplicationArgs {
    uint32_t width = 512U;
    uint32_t height = 512U;
    uint32_t samplingCount = 1U;
};

class ttApplication {
public:
    ttApplication();
    ~ttApplication();

    //! 初期化
    bool initialize(const ttApplicationArgs& args);
    //! 処理を実行
    void run();
    //! 終了処理
    void terminate();

    //! 完了したかどうか
    bool finished() const;
    //! 実行中かどうか
    bool isRunning() const;
    bool enabled() const;

    const uint32_t* getPixels() const;

    const char* getProgressText() const;

private:
    bool getRadiance_(const ttRay& ray, const ttVector& prevNormal, uint32_t depth, ttVector* color) const;
    void calcPixel_(uint32_t Ls, uint32_t Li, const ttVector& offset, float buffer[]) const;

private:
    struct Member;
    std::unique_ptr<Member> m_;
    std::atomic_bool quit_ = false;
    std::atomic_bool enableTerminate_ = false;

private:
    ttNONCOPYABLE(ttApplication);
};

}
