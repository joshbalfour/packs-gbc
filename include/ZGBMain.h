#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
_STATE(StateDone)\
_STATE(StatePreSplash)\
_STATE(StateSplash)\
_STATE(StateTest)\
_STATE(StateMenu)\
_STATE(StatePaused)\
STATE_DEF_END

#define SPRITES \
_SPRITE(SpriteSelector, selector, FLIP_NONE)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif