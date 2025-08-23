#pragma once

// Name used to identify the plugin
#define FS_NAME "F's ChannelShift"

// Text used for the plugin description
#define FS_DESCRIPTION "Shifts images by channel."

// Menu name where the plugin is displayed
#define FS_CATEGORY "NF's Plugins-Channel"

// clang-format off
#include "FsVersion.h"
// clang-format on

// out_flags
#define FS_OUT_FLAGS 33556032

// out_flags2
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
