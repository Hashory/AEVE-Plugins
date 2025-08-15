#pragma once

#include "AEConfig.h"

#if defined(AE_OS_WIN) && !defined(_WINDOWS)
#define _WINDOWS
#endif

#ifdef AE_OS_WIN
#include <Windows.h>
#endif

#include "entry.h"
#include "AE_Effect.h"
#include "A.h"
#include "AE_EffectCB.h"
#include "AE_Macros.h"
#include "Param_Utils.h"

// Effects includes below
