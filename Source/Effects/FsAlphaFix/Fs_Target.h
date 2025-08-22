#pragma once

#define FS_NAME "F's AlphaFix"
#define FS_DESCRIPTION "Fills in the opaque areas."

// The menu name where the plug-in is displayed
#define FS_CATEGORY "NF's Plugins-Channel"

// Prevent double registration
#ifndef SUPPORT_SMARTFX
// If this is enabled, it will support SmartFX+Float_Color
#define SUPPORT_SMARTFX
#endif
// If this is enabled, FsGraphics related files will not be included
// #define NO_USE_FSGRAPHICS

// clang-format off
#include "FsVersion.h"
// clang-format on

// out_flags
/*
        out_data->out_flags	  =
                PF_OutFlag_PIX_INDEPENDENT
                //| PF_OutFlag_NON_PARAM_VARY
                | PF_OutFlag_DEEP_COLOR_AWARE
                | PF_OutFlag_USE_OUTPUT_EXTENT
                | PF_OutFlag_I_EXPAND_BUFFER;
                //33556032
                //33556036 +PF_OutFlag_NON_PARAM_VARY
*/
#define FS_OUT_FLAGS 33556032
// #define Fs_OUTFLAGS 33556036

// out_flags2
/*
        out_data->out_flags2  =	PF_OutFlag2_FLOAT_COLOR_AWARE
                                                  |
   PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG |
   PF_OutFlag2_SUPPORTS_SMART_RENDER | PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS
                                                  |
   PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS |
   PF_OutFlag2_SUPPORTS_THREADED_RENDERING;		// PF_Cmd_GLOBAL_SETUP

                                                //5193
                                                //134222921
*/
#if defined(SUPPORT_SMARTFX)
// #define FS_OUT_FLAGS2 134222921
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif
