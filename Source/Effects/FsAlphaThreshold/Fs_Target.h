#pragma once

// Name used for plugin identification
#define FS_NAME "F's alphaThreshold"

// String used for the plugin description
#define FS_DESCRIPTION "Binarizes the alpha channel."

// Menu name where the plugin will be displayed
#define FS_CATEGORY "NF's Plugins-Channel"

// Enable this to support SmartFX + Float Color
#define SUPPORT_SMARTFX
// Enable this to not include FsGraphics related files
// #define NO_USE_FSGRAPHICS

// clang-format off
#include "FsVersion.h"
// clang-format on

// out_flags
// This is the standard setting
#define FS_OUT_FLAGS 33556032
// Enable this to render every frame. Also use this when switching
// NON_PARAM_VARY during execution.
// #define FS_OUT_FLAGS	33556036
//  8bit only
//  #define FS_OUT_FLAGS	1600

// out_flags2
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
