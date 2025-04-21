#include "packs.h"
#include <rand.h>
#include <gb/gb.h>
#include <string.h>

uint8_t table[12] = {};

void bitsToCard(uint8_t bits, pack_card* outCard) {
    struct pack_card card = {
        .bits = bits,
        .colour = (bits & 0b000011) >> (2*0),
        .shape =( bits & 0b001100) >> (2*1),
        .fill = (bits & 0b110000) >> (2*2),
        .num =( bits & 0b11000000) >> (2*3),
    };

    *outCard = card;
}

// https://sanderevers.github.io/2019/09/11/finding-sets.html#file-findingsets-py-L91
// [1,2,1,0].reverse().map((a,i) => a<<(2*i)).reduce((a,b) => a+b) 
uint8_t cardAttrsToBits(enum Colour colour, enum Shape shape, enum Fill fill, enum COUNT num) {
    uint8_t bits = 0;

    bits += colour << (2*0);
    bits += shape << (2*1);
    bits += fill << (2*2);
    bits += num << (2*3);

    return bits;
}

// https://sanderevers.github.io/2019/09/11/finding-sets.html#file-findingsets-py-L91

static const uint8_t mask0 = 0b01010101;
static const uint8_t mask1 = 0b10101010;

uint8_t CalculateThirdCardBits(uint8_t card0Bits, uint8_t card1Bits) {
    uint8_t xor = card0Bits ^ card1Bits;
    uint8_t swap = ((xor & mask1) >> 1) | ((xor & mask0) << 1);
    return (card0Bits&card1Bits) | (~(card0Bits|card1Bits) & swap);
}

uint8_t IsValidPack(uint8_t card0Bits, uint8_t card1Bits, uint8_t card2Bits) {
    return card2Bits == CalculateThirdCardBits(card0Bits, card1Bits);
}

uint8_t deck[81] = {};
uint8_t consumed[171] = {};

uint8_t numInDeck = 0;
uint8_t numConsumed = 0;

void PopulateHand(uint8_t singleColor) {
    for (uint8_t num = 0; num<3; num++) {
        for (uint8_t shape = 0; shape<3; shape++) {
            for (uint8_t fill = 0; fill<3; fill++) {
                if (singleColor) {
                    deck[numInDeck] = cardAttrsToBits(0, shape, fill, num);
                    numInDeck++;
                } else {
                    for (uint8_t colour = 0; colour<3; colour++) {
                        deck[numInDeck] = cardAttrsToBits(colour, shape, fill, num);
                        numInDeck++;
                    }
                }
            }
        }
    }
}

void ClearAll() {
    for (uint8_t i = 0; i<81; i++) {
        deck[i] = NULL;
    }
    numInDeck = 0;
    for (uint8_t i = 0; i<170; i++) {
        consumed[i] = NULL;
    }
    numConsumed = 0;
    for (uint8_t i = 0; i<12; i++) {
        table[i] = NULL;
    }
}

void DealGame(uint8_t singleColor) {
    // TODO: move this to splash screen
    uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
    // ---

    ClearAll();
    PopulateHand(singleColor);

    memset(consumed, 0, sizeof consumed);
    // pick 11 cards from deck and add to table
    for (uint8_t i = 0; i<11; i++) {
        do {
            uint8_t r = rand() % numInDeck + 1;
            if (!consumed[deck[r]]) {
                table[i] = deck[r];
                consumed[deck[r]] = 1;
                numConsumed++;
            }
        } while (!table[i]);
    }

    // pick 2 random cards from table, calculate third card, add to table in random place
    uint8_t card1Pos = rand() % 11 + 1;
    uint8_t card2Pos = rand() % 11 + 1;
    uint8_t cardDestination = rand() % 12 + 1;
    uint8_t card3Bits = CalculateThirdCardBits(table[card1Pos], table[card2Pos]);
    if (consumed[card3Bits]) {
        card3Bits = PickUnconsumedCard();
    }
    consumed[card3Bits] = 1;
    numConsumed++;

    if (table[cardDestination]) {
        uint8_t origCard = table[cardDestination];
        table[11] = origCard;
        table[cardDestination] = card3Bits;
    }
}

uint8_t PickUnconsumedCard() {

    do {
        uint8_t r = rand() % numInDeck + 1;
        if (!consumed[deck[r]]) {
            return deck[r];
        }
    } while (1);
}

uint8_t TableHasPack(uint8_t tableToTest[12]) {
    // for every 2 card combo
    for (uint8_t firstCardPos = 0; firstCardPos<12; firstCardPos++) {
        for (uint8_t secondCardPos = 0; secondCardPos<12; secondCardPos++) {
            if (firstCardPos != secondCardPos) {
                // calc third
                uint8_t card3Bits = CalculateThirdCardBits(tableToTest[firstCardPos], tableToTest[secondCardPos]);
                for (uint8_t possThirdCardPos = 0; possThirdCardPos<12; possThirdCardPos++) {
                    if (possThirdCardPos != firstCardPos && possThirdCardPos != secondCardPos) {
                        // is it on the table?
                        if (tableToTest[possThirdCardPos] == card3Bits) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// returns if the game is over
uint8_t PickupPack(uint8_t card0TablePos, uint8_t card1TablePos, uint8_t card2TablePos) {
    if (numInDeck - numConsumed == 0) {
        table[card0TablePos] = NULL;
        table[card1TablePos] = NULL;
        table[card2TablePos] = NULL;
        return !TableHasPack(table);
    }

    uint8_t newCard0 = 0;
    uint8_t newCard1 = 0;
    uint8_t newCard2 = 0;

    uint8_t newTable[12] = {};

    do {
        // pick 3 random cards
        newCard0 = PickUnconsumedCard();
        newCard1 = PickUnconsumedCard();
        newCard2 = PickUnconsumedCard();
        for (uint8_t i = 0; i<12; i++) {
            // put on the table
            if (i == card0TablePos) {
                newTable[i] = newCard0;
            } else if (i == card1TablePos) {
                newTable[i] = newCard1;
            } else if (i == card2TablePos) {
                newTable[i] = newCard2;
            } else {
                newTable[i] = table[i];
            }
        }
    } while (!TableHasPack(newTable));

    consumed[newCard0] = 1;
    numConsumed++;
    consumed[newCard1] = 1;
    numConsumed++;
    consumed[newCard2] = 1;
    numConsumed++;

    for (uint8_t i = 0; i<12; i++) {
        table[i] = newTable[i];
    }

    return 0;
}
