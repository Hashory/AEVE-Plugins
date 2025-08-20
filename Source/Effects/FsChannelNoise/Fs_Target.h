#pragma once

// Name used to identify the plugin
#define FS_NAME "F's ChannelNoise"
// Text used for the plugin description
#define FS_DESCRIPTION "Applies noise to each channel."

// Menu name where the plugin is displayed
#define FS_CATEGORY "NF's Plugins-Noise"

// If enabled, supports SmartFX + Float_Color
#define SUPPORT_SMARTFX

// clang-format off
#include "FsVersion.h"
// clang-format on

// If this is enabled, it will draw every frame.
// Also enable this when switching NON_PARAM_VARY during operation.
#define FS_OUT_FLAGS 33556036

#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
