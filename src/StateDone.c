#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Keys.h"

IMPORT_MAP(done);

void START(void) {
    InitScroll(BANK(done), &done, 0, 0);
}

void UPDATE(void) {
    if (KEY_TICKED(J_START | J_A | J_B)) {
        SetState(DEVICE_SUPPORTS_COLOR ? StateMenu : StateSplash);
    }
}

void DESTROY(void) {
}