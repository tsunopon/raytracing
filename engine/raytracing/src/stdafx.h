// -*- coding: utf-8-with-signature-unix; astyle: yes -*-
//
//! @file   stdafx.cpp
//! @brief  
//! @author Tatsuya TSUNODA
//! @date   2018/04/14
//
//=====================================================================================================================
#pragma once

#include <codeanalysis/warnings.h>
#pragma warning (disable: 4481)     // override
#pragma warning (disable: 4201)     // 無名の構造体または共用体

#include <algorithm>
#include <cassert>
#include <memory>
#include <map>
#include <stdint.h>

#include <Windows.h>

#define ttUNUSED(V) ((void)(V))
#define ttNONCOPYABLE(CLASS)        \
    CLASS(const CLASS&) = delete;    \
    void operator = (const CLASS&) = delete;
#define ttARRAYSIZE(T) (static_cast<int>(sizeof(T)/sizeof(T[0])))