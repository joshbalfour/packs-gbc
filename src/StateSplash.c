#include "Banks/SetAutoBank.h"
#include <rand.h>
#include <gb/gb.h>
#include "Keys.h"
#include "ZGBMain.h"
#include "StateGame.h"

IMPORT_MAP(splash);

void START(void) {
    InitScroll(BANK(splash), &splash, 0, 0);
}

void UPDATE(void) {
    if (KEY_TICKED(J_START | J_A | J_B)) {
        uint16_t seed = LY_REG;
        seed |= (uint16_t)DIV_REG << 8;
        initrand(seed);

        singleColourGame = 1;
        SetState(DEVICE_SUPPORTS_COLOR ? StateMenu : StateGame);
    }
}

void DESTROY(void) {
}