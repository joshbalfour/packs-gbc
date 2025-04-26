#include "Banks/SetAutoBank.h"
#include <rand.h>
#include <gb/gb.h>
#include "Keys.h"
#include "ZGBMain.h"

IMPORT_HICOLOR(splash);

void START(void) {
	// uninstall the standard LCD routine (used for the overlay window)
	LCD_uninstall();
	// disable fading between the state transitions
	fade_enabled = FALSE;
	HICOLOR_START(splash);
}

void UPDATE(void) {
    if (KEY_TICKED(J_START | J_A | J_B)) {
        // stop display
        HICOLOR_STOP;
        // reinstall the standard LCD routine
        LCD_install();
        // endble fading back
        fade_enabled = TRUE;

        uint16_t seed = LY_REG;
        seed |= (uint16_t)DIV_REG << 8;
        initrand(seed);

        SetState(StateMenu);
    }
}

void DESTROY(void) {
}