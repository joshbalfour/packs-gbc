#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"

#include "StateGame.h"

IMPORT_MAP(paused);

void START(void) {
    LoadMap(TARGET_BKG, 0, 0, BANK(paused), &paused);
}

void UPDATE(void) {
    if (KEY_TICKED(J_START)) {
        fade_enabled = TRUE;
        SetState(StateMenu);
    }

    if (KEY_TICKED(J_SELECT | J_A | J_B)) {
        resumeGame = 1;
        SetState(StateGame);
    }
}

void DESTROY(void) {
}