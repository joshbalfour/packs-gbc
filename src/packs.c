#include "packs.h"
#include <rand.h>
#include <gb/gb.h>

static const pack_card deck[81] = {
    {.num = ONE_SHAPE, .colour = RED, .shape = SQUISH, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = RED, .shape = SQUISH, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = RED, .shape = SQUISH, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = RED, .shape = DIAMOND, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = RED, .shape = DIAMOND, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = RED, .shape = DIAMOND, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = FILLED},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = FILLED},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = FILLED},
    {.num = ONE_SHAPE, .colour = RED, .shape = SQUISH, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = RED, .shape = SQUISH, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = RED, .shape = SQUISH, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = RED, .shape = DIAMOND, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = RED, .shape = DIAMOND, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = RED, .shape = DIAMOND, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = EMPTY},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = EMPTY},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = EMPTY},
    {.num = ONE_SHAPE, .colour = RED, .shape = SQUISH, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = RED, .shape = SQUISH, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = RED, .shape = SQUISH, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = SQUISH, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = SQUISH, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = RED, .shape = RECTANGLE, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = RECTANGLE, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = RECTANGLE, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = RED, .shape = DIAMOND, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = RED, .shape = DIAMOND, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = RED, .shape = DIAMOND, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = ORANGE, .shape = DIAMOND, .fill = STRIPED},
    {.num = ONE_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = STRIPED},
    {.num = TWO_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = STRIPED},
    {.num = THREE_SHAPE, .colour = BLUE, .shape = DIAMOND, .fill = STRIPED},
};

pack_card* table[12] = {};
pack_card* hand[81] = {};

pack_card* PickNewCard() {
    uint8_t r = rand() % 81;
    while (HandContains(&deck[r])) {
        r = rand() % 81;
    }
    return &deck[r];
}

uint8_t IsValidPack(pack_card* card0, pack_card* card1, pack_card* card2) {
    return CalculateThirdBits(card0->bits, card1->bits) == card2->bits;
}

// from https://sanderevers.github.io/2019/09/11/finding-sets.html

uint8_t mask0 = 85;
uint8_t mask1 = 170;

uint8_t CalculateThirdBits(uint8_t card0bits, uint8_t card1bits) {
    uint8_t xor = card0bits^card1bits;
    uint8_t swap = ((xor & mask1) >> 1) | ((xor & mask0) << 1);
    return (card0bits & card1bits) | (~(card0bits | card1bits) & swap);
}

pack_card* CalculateThird(pack_card* card0, pack_card* card1) {
    
}

uint8_t HandContains(pack_card* card) {
    for (uint8_t i = 0; i<81; i++) {
        if (hand[i] && hand[i]->bits == card->bits) {
            return 1;
        }
    }
    return 0;
}

uint8_t TableContainsPack(pack_card* tbl[12]) {

}

void PopulateTable() {
    // if remaining table contains pack, pick 3 random cards using PickNewCard(), add to table, done
    if (TableContainsPack(table)) {
        for (uint8_t i = 0; i<11; i++) {
            if (!table[i]) {
                table[i] = PickNewCard();
            }
        }
        return;
    }

    pack_card* newTable[12] = {};
    uint8_t ctr = 0;
    for (uint8_t i = 0; i<11 && ctr < 2; i++) {
        // pick 2 random cards using PickNewCard()
        // add to prospective table
        if (!newTable[i]) {
            ctr++;
            newTable[i] = PickNewCard();
        }
    }

    if (TableContainsPack(newTable)) {
        for (uint8_t i = 0; i<11; i++) {
            if (!newTable[i]) {
                newTable[i] = PickNewCard();
                break;
            }
        }
    } else {
        pack_card* card2 = NULL;
        pack_card* card0;
        pack_card* card1;

        // repeat until third is not in hand already
        while (!card2 || HandContains(&card2)) {
            // pick 2 random cards from table
            uint8_t r = rand() % 12;
            card0 = newTable[r];
            uint8_t r2 = rand() % 12;
            card1 = newTable[r2];
            // calculate third
            card2 = CalculateThird(&card0, &card1);
        }

        uint8_t gaps[3] = {};

        // place on newTable in random order
        uint8_t j = 0;
        for (uint8_t i = 0; i<11; i++) {
            if (!table[i]) {
                gaps[j] = i;
                j++;
            }
        }

        uint8_t r = rand() % 3; // between 0 and 2
        if (r == 0) {
            table[gaps[0]] = &card0;
            table[gaps[1]] = &card1;
            table[gaps[2]] = &card2;
        } else if (r == 1) {
            table[gaps[1]] = &card0;
            table[gaps[0]] = &card1;
            table[gaps[2]] = &card2;
        } else if (r == 2) {
            table[gaps[2]] = &card0;
            table[gaps[1]] = &card1;
            table[gaps[0]] = &card2;
        }
        return;
    }

    // copy newTable over to table
    for (uint8_t i = 0; i<12; i++) {
        table[i] = newTable[i];
    }
}

void ClearAll() {
    for (uint8_t i = 0; i<12; i++) {
        table[i] = NULL;
    }
    for (uint8_t i = 0; i<80; i++) {
        hand[i] = NULL;
    }
}

void DealGame(uint8_t singleColor) {
    // TODO: move this to splash screen
    uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
    // ---

    ClearAll();

    // pick 11 cards from deck and add to table
    for (uint8_t i = 0; i<11; i++) {
        uint8_t r = rand() % 80;
        table[i] = &deck[r];
    }
    // pick 2 random cards from table, calculate third card, add to table in random place
}
