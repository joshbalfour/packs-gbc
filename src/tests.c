#include <rand.h>
#include "packs.h"
#include "tests.h"
#include <gbdk/emu_debug.h>

uint8_t RunTest(uint8_t singleColour, uint16_t seed) {
    initrand(seed);
    DealGame(singleColour);

    if (TableHasDupes(table)) {
        // log error
        // table has dupes
        EMU_printf("dupes after turn=%d\n",0);
        return 7;
    }

    uint8_t gameOver = 0;
    uint8_t turn = 0;
    while (!gameOver) {        
        if (turn > (singleColour ? 9 : 27)) {
            return 3;
        }

        turn++;

        struct PackPos pp;
        FindPack(table, &pp);
        if (pp.firstCardPos != UINT8_MAX) {
            // EMU_printf("singleColour=%d, seed=%d => turn=%d\n", 0,0,turn);
            gameOver = PickupPack(pp.firstCardPos, pp.secondCardPos, pp.thirdCardPos);
            if (gameOver > 1) {
                return gameOver;
            }
        } else {
            // log error
            // no pack on table but game is not over
            return 2;
        }

        // each turn
        if (TableHasDupes(table)) {
            // log error
            // table has dupes
            EMU_printf("dupes after turn=%d\n",turn);
            return 1;
        }
    }

    return 0;
}


