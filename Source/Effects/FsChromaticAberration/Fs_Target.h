#pragma once

// Name used to identify the plugin
#define FS_NAME "F's ChromaticAberration"
#define FS_DISPNAME "F's ChromaticAberration"

// String for the plugin description
#define FS_DESCRIPTION "ChromaticAberration"

// Menu name where the plugin appears
#define FS_CATEGORY "NF's Plugins-Filter"

// Enable for SmartFX + Float_Color support
#define SUPPORT_SMARTFX
// Enable to exclude FsGraphics-related includes
// #define NO_USE_FSGRAPHICS

// clang-format off
#include "FsVersion.h"
// clang-format on

// out_flags
#define FS_OUT_FLAGS 33556032  // Default
// #define FS_OUT_FLAGS	33556036	// Enable this to draw every frame.
// Also use when switching NON_PARAM_VARY during operation. #define
// FS_OUT_FLAGS	1600		// 8bit only

// out_flags2
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
