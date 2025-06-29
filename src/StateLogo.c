#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"

IMPORT_MAP(logo);

uint8_t logoctr1 = 0;
uint8_t logoctr2 = 0;

uint8_t logodoneWithIt = 0;

void START(void) {
	InitScroll(BANK(logo), &logo, 0, 0);
}

void UPDATE(void) {
    if (!logodoneWithIt) {
        logoctr1++;
        if (logoctr1 == 30) {
            logoctr1 = 0;
            logoctr2++;
        }
    
        if (logoctr2 == 3) {
            logodoneWithIt = 1;
            SetState(StateSplash);
        }
    }
}

void DESTROY(void) {
}