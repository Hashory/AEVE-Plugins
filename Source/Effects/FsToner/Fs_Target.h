#pragma once

// Name used to identify the plugin
#define FS_NAME "F's Toner"

// Text used for the plugin description
#define FS_DESCRIPTION "Same as Tritone"

// Menu name where the plugin is displayed
#define FS_CATEGORY "NF's Plugins-Colorize"

// Enable this to support SmartFX + Float_Color
#define SUPPORT_SMARTFX

// clang-format off
// Plugin version
#include "FsVersion.h"
// clang-format on

// out_flags
#define FS_OUT_FLAGS 33556032  // Usually this one
// #define FS_OUT_FLAGS	33556036	//Enable this to draw every frame.
// Also use this when switching NON_PARAM_VARY during operation. #define
// FS_OUT_FLAGS	1600		//8bit only

// out_flags2
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
