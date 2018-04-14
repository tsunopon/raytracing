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
    pixels.reset(new float[512 * 512 * 4]);
    for(auto w = 0U; w < 512; ++w) {
        for(auto h = 0U; h < 512; ++h) {
            pixels[0 + w * 4 + h * 512] = 0.0f;
            pixels[1 + w * 4 + h * 512] = 0.5f;
            pixels[2 + w * 4 + h * 512] = 1.0f;
            pixels[3 + w * 4 + h * 512] = 1.0f;
        }
    }
    winManager.setWindowColor(pixels.get());

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

    winManager.terminate();

    return 0;
}
