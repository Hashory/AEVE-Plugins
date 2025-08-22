#pragma once

// Name used to identify the plugin
#define FS_NAME "F's Grad_Test"

// Text used for the plugin description
#define FS_DESCRIPTION "Test for gradation"

// Menu name where the plugin will be displayed
#define FS_CATEGORY "NF's Plugins-{Legacy}"

#define SUPPORT_SMARTFX  // Enable this for SmartFX + Float_Color support

// clang-format off
#include "FsVersion.h"
// clang-format on

// out_flags
#define FS_OUT_FLAGS \
  33556036  // Enable this to draw every frame. Also used when switching
            // NON_PARAM_VARY during operation.

// out_flags2
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
