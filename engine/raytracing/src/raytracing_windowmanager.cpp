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

static HBITMAP hBitmap_s = NULL;
static HDC hMemDC_s = NULL;
static uint32_t width_s = 0;
static uint32_t height_s = 0;

struct ttWindowManager::Member {
    char windowName[MAX_WINDOW_NAME] = "no name";
    HWND hWnd = NULL;
    LPDWORD lpPixels = nullptr;
    bool dirty = false;
};

ttWindowManager::ttWindowManager() {
    m_.reset(new Member());
}

ttWindowManager::~ttWindowManager() {
}

//! ウィンドウプロージャ
LRESULT CALLBACK
winProc(
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
        break;
    case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            BitBlt(hDC, 0, 0, width_s, height_s, hMemDC_s, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CLOSE:
        DeleteDC(hMemDC_s);
        DeleteObject(hBitmap_s);
        break;
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

    width_s = param.width;
    height_s = param.height;

    WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        &winProc,
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

    BITMAPINFO bmpInfo;
    // DIB構造体の初期化
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = param.width;
    bmpInfo.bmiHeader.biHeight = -1 * static_cast<LONG>(param.height);
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 32;
    bmpInfo.bmiHeader.biCompression = BI_RGB;

    HDC hDC = GetDC(m_->hWnd);
    hMemDC_s = CreateCompatibleDC(hDC);
    hBitmap_s = CreateDIBSection(NULL, &bmpInfo, DIB_RGB_COLORS, (LPVOID*)&m_->lpPixels, NULL, 0);
    SelectObject(hMemDC_s, hBitmap_s);
    ReleaseDC(m_->hWnd, hDC);

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

static
uint32_t getColor(const float pixels[], uint32_t index) {
    uint32_t r = static_cast<uint32_t>(pixels[index] * 255);
    uint32_t g = static_cast<uint32_t>(pixels[index + 1] * 255);
    uint32_t b = static_cast<uint32_t>(pixels[index + 2] * 255);
    return (min(r, 255U) << 16) | (min(g, 255U) << 8) | min(b, 255U);
}

void
ttWindowManager::setWindowColor(const float pixels[]) {
    for(auto h = 0U; h < height_s; ++h) {
        for(auto w = 0U; w < width_s; ++w) {
            m_->lpPixels[w + h * width_s] = getColor(pixels, w * 4 + h * width_s * 4);
        }
    }
    m_->dirty = true;
}

void
ttWindowManager::update() {
    if(m_->dirty) {
        UpdateWindow(m_->hWnd);
        m_->dirty = false;
    }
}

}
