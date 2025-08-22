#pragma once

// Name used to identify the plugin
#define FS_NAME "F's ColorChangeSimple"

// Text used for the plugin description
#define FS_DESCRIPTION "Performs single color replacement"

// Menu name where the plugin is displayed
// #define FS_CATEGORY "F's Plugins-Channel"
// #define FS_CATEGORY "F's Plugins-Draw"
// #define FS_CATEGORY "F's Plugins-Filter"
#define FS_CATEGORY "NF's Plugins-Cell"
// #define FS_CATEGORY "F's Plugins-Colorize"
// #define FS_CATEGORY "F's Plugins-Script"
// #define FS_CATEGORY "F's Plugins-Test"

// Enabling this supports SmartFX + Float_Color
#define SUPPORT_SMARTFX
// Enabling this prevents FsGraphics-related files from being included
// #define NO_USE_FSGRAPHICS

// clang-format off
#include "FsVersion.h"
// clang-format on

// out_flags
/*
out_data->out_flags
    PF_OutFlag_PIX_INDEPENDENT		1024
    PF_OutFlag_NON_PARAM_VARY			4
    PF_OutFlag_DEEP_COLOR_AWARE		33554432
    PF_OutFlag_USE_OUTPUT_EXTENT	64
    PF_OutFlag_I_EXPAND_BUFFER		512
    PF_OutFlag_I_DO_DIALOG				32
*/

// Usually this one
#define FS_OUT_FLAGS 33556032
// Enable this to draw every frame. Also use this when switching NON_PARAM_VARY
// during operation.
// #define FS_OUT_FLAGS	33556036
// 8bit only
// #define FS_OUT_FLAGS	1600

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
