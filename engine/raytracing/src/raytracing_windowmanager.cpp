// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   raytracing_windowmanager.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/14
//
//=====================================================================================================================
#include "stdafx.h"
#include "./raytracing_windowmanager.h"

#include "./raytracing_types.h"

namespace raytracing { 

static const int MAX_WINDOW_NAME = 128;

struct ttWindowManager::Member {
    char windowName[MAX_WINDOW_NAME] = "no name";
    HWND hWnd = NULL;
};

ttWindowManager::ttWindowManager() {
    m_.reset(new Member());
}

ttWindowManager::~ttWindowManager() {
}

//! ウィンドウプロージャ
static LRESULT CALLBACK
WndProc(
        HWND hWnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam) {
    switch(msg) {
    case WM_ACTIVATE:
        break;
    case WM_DESTROY:
        // ウィンドウを閉じる
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        // ウィンドウサイズ変更
        break;
    case WM_KEYDOWN:
        // キー入力
        switch(wParam){
        case VK_ESCAPE:
            // [ESCAPE]で終了
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        default:
            break;
        }
    default:
        break;
    }

    if(msg == WM_DESTROY || msg == WM_CLOSE) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool
ttWindowManager::create(const ttWindowParam& param) {
    const HINSTANCE hInstance = GetModuleHandle(nullptr);
    if(param.windowName != nullptr) {
        strcpy_s(m_->windowName, ttARRAYSIZE(m_->windowName), param.windowName);
    }

    WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        WndProc,
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW+1),
        NULL,
        m_->windowName,
        NULL
    };
    if(!RegisterClassEx(&wcex)) {
        return false;
    }

    RECT R = {0, 0, static_cast<LONG>(param.width), static_cast<LONG>(param.height)};
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, FALSE);
    m_->hWnd = CreateWindow(
                m_->windowName,
                m_->windowName,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                0,
                R.right - R.left,
                R.bottom - R.top,
                NULL,
                NULL,
                hInstance,
                NULL);
    if(m_->hWnd == NULL){
        return false;
    }

    return true; 
}


void
ttWindowManager::show() {
    ShowWindow(m_->hWnd, SW_SHOW);
}

void
ttWindowManager::terminate() {
    m_.reset();
}

}
