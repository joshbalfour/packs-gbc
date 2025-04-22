#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "packs.h"
#include "tests.h"
#include <gbdk/emu_debug.h>

void TEST(uint8_t singleColour, uint16_t seed) {
    EMU_printf("singleColour=%d, seed=%d => ", singleColour, seed);
    uint8_t result = RunTest(singleColour, seed);
    EMU_printf("result=%d\n",result);
    if (result) {
        EMU_printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7], table[8], table[9], table[10], table[11], table[12]);
    }
}

void START(void) {
    uint8_t singleColour = 0;
    // for (uint16_t seed = 0; seed < UINT16_MAX; seed++) {
    //     TEST(singleColour, seed);
    // }

    TEST(singleColour, 277);
}

void UPDATE(void) {
}

void DESTROY(void) {
}