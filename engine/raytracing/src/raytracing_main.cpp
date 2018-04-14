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
    param.width = 512;
    param.height = 512;
    param.windowName = "Ray Tracing";
    winManager.create(param);
    winManager.show();

    std::unique_ptr<float[]> pixels;
    pixels.reset(new float[param.width * param.height * 4]);
    winManager.setWindowColor(pixels.get());

    raytracing::ttApplicationArgs args;
    args.width = 512U;
    args.height = 512U;
    args.samplingCount = 1U;
    raytracing::ttApplication app;
    app.initialize(args);

    app.run();
    winManager.setWindowColor(app.getPixels());

    // メッセージ処理
    MSG msg;
    do
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else{
            winManager.update();
        }
    }
    while(msg.message != WM_QUIT);


    app.terminate();
    winManager.terminate();

    return 0;
}
