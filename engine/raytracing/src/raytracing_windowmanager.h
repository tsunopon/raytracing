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

private:
    struct Member;
    std::unique_ptr<Member> m_;

private:
    ttNONCOPYABLE(ttWindowManager);
};

}
