#pragma once

// clang-format off
#include "../NFsLibrary/AE_SDK.h"
#include "../NFsLibrary/AEInfo.h"
#include "../NFsLibrary/NFsWorld.h"
#include "ColorChangeFromPoint.h"
// clang-format on

class ColorChangeFromPointFX : public NFsWorld {
 private:
 public:
  ColorChangeFromPointFX(PF_EffectWorld* wld = NULL, PF_InData* ind = NULL,
                         PF_PixelFormat fmt = PF_PixelFormat_ARGB32)
      : NFsWorld(wld, ind, fmt) {}
};