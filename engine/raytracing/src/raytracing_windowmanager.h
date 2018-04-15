// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//=====================================================================================================================
#pragma once

#include "./raytracing_forward.h"

namespace raytracing { 

class ttWindowManager {
public:
    ttWindowManager();
    virtual ~ttWindowManager();

    //! ウィンドウの作成
    /// @param[in]  param
    bool create(const ttWindowParam& param);

    //! 終了処理
    void terminate();

    //! ウィンドウの表示
    void show();

    //! ウィンドウカラー設定
    void setWindowColor(const float pixels[]);

    //! ウィンドウ更新
    void update();

    //! ウィンドウタイトル設定
    void setWindowTitle(const char* text);

private:
    struct Member;
    std::unique_ptr<Member> m_;

private:
    ttNONCOPYABLE(ttWindowManager);
};

}
