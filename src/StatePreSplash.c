#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"

IMPORT_HICOLOR(packsinc);

void START(void) {

    if (!DEVICE_SUPPORTS_COLOR) {
        SetState(StateSplash);
        return;
    }

	// uninstall the standard LCD routine (used for the overlay window)
	LCD_uninstall();
	// disable fading between the state transitions
	fade_enabled = FALSE;
	HICOLOR_START(packsinc);
}

uint8_t ctr1 = 0;
uint8_t ctr2 = 0;

uint8_t doneWithIt = 0;

void UPDATE(void) {
    if (!doneWithIt) {
        ctr1++;
        if (ctr1 == 60) {
            ctr1 = 0;
            ctr2++;
        }
    
        if (ctr2 == 3) {
            doneWithIt = 1;
            // stop display
            HICOLOR_STOP;
            // reinstall the standard LCD routine
            LCD_install();
            // endble fading back
            fade_enabled = TRUE;
            SetState(StateSplash);
        }
    }
}

void DESTROY(void) {
}