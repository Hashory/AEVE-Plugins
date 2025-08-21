#pragma once

// Name used for plugin identification
#define FS_NAME "F's Star"

// Text used for plugin description
#define FS_DESCRIPTION "A simple cross filter"

// Menu name where the plugin will be displayed
#define FS_CATEGORY "NF's Plugins-Filter"

// Enable this to support SmartFX + Float_Color
#define SUPPORT_SMARTFX

// clang-format off
// Plugin version
#include "FsVersion.h"
// clang-format on

// out_flags
/*
out_data->out_flags
        PF_OutFlag_PIX_INDEPENDENT              1024
        PF_OutFlag_NON_PARAM_VARY                       4
        PF_OutFlag_DEEP_COLOR_AWARE             33554432
        PF_OutFlag_USE_OUTPUT_EXTENT    64
        PF_OutFlag_I_EXPAND_BUFFER              512
        PF_OutFlag_I_DO_DIALOG                          32
*/
// Usually this one
#define FS_OUT_FLAGS 33556032
// If this is enabled, it will be rendered every frame.
// This is also the case when switching NON_PARAM_VARY during operation.
// #define FS_OUT_FLAGS	33556036
//  8bit only
//  #define FS_OUT_FLAGS	1600

// out_flags2
/*
out_data->out_flags2
        PF_OutFlag2_FLOAT_COLOR_AWARE
        PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG
        PF_OutFlag2_SUPPORTS_SMART_RENDER
        PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS
        PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS;
*/
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
