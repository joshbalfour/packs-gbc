#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
_STATE(StateDone)\
_STATE(StateSplash)\
_STATE(StateMenu)\
STATE_DEF_END

#define SPRITES \
_SPRITE(SpriteSelector, selector, FLIP_NONE)\
_SPRITE(SpriteArrow, arrow, FLIP_NONE)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif