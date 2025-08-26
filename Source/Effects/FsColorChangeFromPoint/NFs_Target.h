#pragma once

#include "../NFsLibrary/NFsVersion.h"

// Name used to identify the plugin
#define NFS_NAME "F's ColorChangeFromPoint"
#define NFS_DISPNAME "F's ColorChangeFromPoint"

// Characters used for plugin description
#define NFS_DESCRIPTION "Plugin skeleton"

// Menu name where the plugin is displayed
#define NFS_CATEGORY "NF's Plugins-Cell"

// Enable this to support SmartFX+Float_Color
#define SUPPORT_SMARTFX

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

// #define NFS_OUT_FLAGS	33556032	// Usually this one
#define NFS_OUT_FLAGS \
  33556036  // If this is enabled, it will be drawn every frame. Also use this
            // when switching NON_PARAM_VARY during operation.
// #define NFS_OUT_FLAGS	1600		// 8bit only

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
#define NFS_OUT_FLAGS2 134222921
#else
#define NFS_OUT_FLAGS2 73
#endif
