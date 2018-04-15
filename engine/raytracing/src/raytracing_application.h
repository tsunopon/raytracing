// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
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

    const float* getPixels() const;

private:
    struct Member;
    std::unique_ptr<Member> m_;

private:
    ttNONCOPYABLE(ttApplication);
};

}
