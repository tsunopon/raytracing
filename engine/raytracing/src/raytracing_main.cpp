// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_main.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/14
//
//=====================================================================================================================
#include "./stdafx.h"

#include "./raytracing_types.h"
#include "./raytracing_windowmanager.h"
#include "./raytracing_application.h"


#ifdef _DEBUG
// メモリリーク検出
#define _CRTDGB_MAP_ALLOCC
#include <stdlib.h>
#include <crtdbg.h>
#endif

//! メイン関数
extern "C" int APIENTRY 
WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
    int nCmdShow) {
    ttUNUSED(hInstance);
    ttUNUSED(hPrevInstance);
    ttUNUSED(lpCmdLine);
    ttUNUSED(nCmdShow);
#ifdef _DEBUG
    // メモリリーク検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    
    raytracing::ttWindowManager winManager;
    raytracing::ttWindowParam param;
    param.width = 640U;
    param.height = 360U;
    param.windowName = "Ray Tracing";
    winManager.create(param);
    winManager.show();

    raytracing::ttApplicationArgs args;
    args.width = param.width;
    args.height = param.height;
    args.samplingCount = 1024U;
    raytracing::ttApplication app;
    app.initialize(args);

    std::thread t1([&app]() {
        app.run();
    });
    t1.detach();

    auto start = std::chrono::system_clock::now();

    // メッセージ処理
    MSG msg;
    do
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else{
            auto end = std::chrono::system_clock::now();
            auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            if(msec > 33.333f) {
                winManager.setWindowColor(app.getPixels());
                winManager.setWindowTitle(app.getProgressText());
                start = end;
                winManager.update();
            }
        }
    }
    while(msg.message != WM_QUIT);


    app.terminate();
    winManager.terminate();

    return 0;
}
