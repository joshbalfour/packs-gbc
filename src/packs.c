#include "packs.h"
#include <rand.h>
#include <string.h>

// #include <gbdk/emu_debug.h>

uint8_t table[12] = {0};

void bitsToCard(uint8_t bits, pack_card* outCard) {
    struct pack_card card = {
        .bits = bits,
        .colour = (bits & 0b000011) >> (2*0),
        .shape =( bits & 0b001100) >> (2*1),
        .fill = (bits & 0b110000) >> (2*2),
        .num =( bits & 0b11000000) >> (2*3),
    };

    // EMU_printf("bits=%d => num=%d, colour=%d, shape=%d, fill=%d\n", bits, card.num,card.colour,card.shape,card.fill);

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

uint8_t deck[81] = {0};
uint8_t consumed[171] = {0};

uint8_t numInDeck = 0;
uint8_t numConsumed = 0;

void PopulateDeck(uint8_t singleColor) {
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

void ClearAll(void) {
    memset(deck, 0, sizeof deck);
    numInDeck = 0;
    memset(consumed, 0, sizeof consumed);
    numConsumed = 0;
    memset(table, 0, sizeof table);
}

uint8_t PickUnconsumedCard(void) {
    uint8_t r = rand() % numInDeck + 1;

    for (uint8_t c = 0; c < numInDeck; c++) {
        uint8_t idx = (r + c) % numInDeck;
        if (!consumed[deck[idx]]) {
            return deck[idx];
        }
    }

    return UINT8_MAX;
}

void DealGame(uint8_t singleColor) {
    ClearAll();
    PopulateDeck(singleColor);

    // pick 11 cards from deck and add to table
    for (uint8_t i = 0; i<11; i++) {
        table[i] = PickUnconsumedCard();
        consumed[table[i]] = 1;
        numConsumed++;
    }

    // pick 2 random cards from table, calculate third card, add to table in random place
    uint8_t card1Pos = rand() % 10 + 1;
    uint8_t card2Pos = rand() % 10 + 1;
    while (card1Pos == card2Pos) {
        card2Pos = rand() % 10 + 1;
    }
    uint8_t cardDestination = rand() % 11 + 1;
    uint8_t card3Bits = CalculateThirdCardBits(table[card1Pos], table[card2Pos]);
    if (consumed[card3Bits]) {
        card3Bits = PickUnconsumedCard();
        consumed[card3Bits] = 1;
        numConsumed++;
    } else {
        consumed[card3Bits] = 1;
        numConsumed++;
    }

    if (table[cardDestination]) {
        uint8_t origCard = table[cardDestination];
        table[11] = origCard;
    }

    table[cardDestination] = card3Bits;
}

uint8_t TableHasDupes(uint8_t tableToTest[12]) {
    for (uint8_t firstCardPos = 0; firstCardPos<12; firstCardPos++) {
        for (uint8_t secondCardPos = 0; secondCardPos<12; secondCardPos++) {
            if (firstCardPos != secondCardPos) {
                if (tableToTest[firstCardPos] == tableToTest[secondCardPos]) {
                    if (tableToTest[firstCardPos] != UINT8_MAX) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

void FindPack(uint8_t tableToTest[12], struct PackPos* outPackPos) {
    struct PackPos packPos = {
        .firstCardPos = UINT8_MAX,
        .secondCardPos = UINT8_MAX,
        .thirdCardPos = UINT8_MAX,
    };
    *outPackPos = packPos;

    // for every 2 card combo
    for (uint8_t firstCardPos = 0; firstCardPos<12; firstCardPos++) {
        if (tableToTest[firstCardPos] == UINT8_MAX) {
            continue;
        }

        for (uint8_t secondCardPos = 0; secondCardPos<12; secondCardPos++) {
            if (tableToTest[secondCardPos] == UINT8_MAX) {
                continue;
            }
            if (firstCardPos == secondCardPos) {
                continue;
            }

            // calc third
            uint8_t card3Bits = CalculateThirdCardBits(tableToTest[firstCardPos], tableToTest[secondCardPos]);
            for (uint8_t possThirdCardPos = 0; possThirdCardPos<12; possThirdCardPos++) {
                if (possThirdCardPos != firstCardPos && possThirdCardPos != secondCardPos) {
                    // is it on the table?
                    if (tableToTest[possThirdCardPos] == card3Bits) {
                        outPackPos->firstCardPos = firstCardPos;
                        outPackPos->secondCardPos = secondCardPos;
                        outPackPos->thirdCardPos = possThirdCardPos;

                        return;
                    }
                }
            }
        }
    }
}

uint8_t TableHasPack(uint8_t tableToTest[12]) {
    struct PackPos pp;
    FindPack(tableToTest, &pp);
    return pp.firstCardPos != UINT8_MAX;
}

uint8_t TableHasCard(uint8_t tableToTest[12], uint8_t cardToFind) {
    for (uint8_t i = 0; i<12; i++) {
        if (tableToTest[i] == cardToFind) {
            return 1;
        }
    }
    return 0;
}

uint8_t PickThirdCard(uint8_t newTable[12]) {
    uint8_t newCard2 = UINT8_MAX;
    for (uint8_t r1 = 0; r1<12; r1++) {
        if (newTable[r1] == UINT8_MAX) {
            continue;
        }

        for (uint8_t r2 = 0; r2<12; r2++) {
            if (newTable[r2] == UINT8_MAX || r2 == r1) {
                continue;
            }

            // calc 3rd
            newCard2 = CalculateThirdCardBits(newTable[r1], newTable[r2]);

            if (consumed[newCard2]) {
                // is it on the table?
                if (TableHasCard(newTable, newCard2)) {
                    // pick random unconsumed card from deck
                    newCard2 = PickUnconsumedCard();
                    return newCard2;
                } else {
                    newCard2 = UINT8_MAX;
                }
            } else {
                // otherwise, use it
                return newCard2;
            }
        }
    }
    return newCard2;
}

// returns if the game is over
uint8_t PickupPack(uint8_t card0TablePos, uint8_t card1TablePos, uint8_t card2TablePos) {
    // EMU_printf("numInDeck=%d, numConsumed=%d\n", numInDeck, numConsumed);
    if ((numInDeck - numConsumed) == 0) {
        table[card0TablePos] = UINT8_MAX;
        table[card1TablePos] = UINT8_MAX;
        table[card2TablePos] = UINT8_MAX;
        return !TableHasPack(table);
    }

    if ((numInDeck - numConsumed) < 3) {
        // something went wrong
        // EMU_printf("numInDeck=%d, numConsumed=%d\n", numInDeck, numConsumed);
        return 4;
    }

    // pick 2 random unconsumed cards from the deck
    uint8_t newCard0 = PickUnconsumedCard();
    uint8_t newCard1;
    do {
        newCard1 = PickUnconsumedCard();
    } while (newCard0 == newCard1);

    consumed[newCard0] = 1;
    numConsumed++;
    consumed[newCard1] = 1;
    numConsumed++;

    table[card0TablePos] = newCard0;
    table[card1TablePos] = newCard1;
    table[card2TablePos] = UINT8_MAX;

    uint8_t newCard2 = PickThirdCard(table);

    // if no pack ever found, game over
    if (newCard2 == UINT8_MAX) {
        return 1;
    }

    consumed[newCard2] = 1;
    numConsumed++;
    
    uint8_t r = rand() % 2; // 1 or 0
    table[card0TablePos] = r ? newCard2 : newCard0;
    table[card2TablePos] = !r ? newCard2 : newCard0;

    return 0;
}
