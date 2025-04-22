#include "stdint.h"

enum Colour {
    RED,
    ORANGE,
    BLUE
};

enum Shape {
    DIAMOND,
    RECTANGLE,
    SQUISH
};

enum Fill {
    FILLED,
    STRIPED,
    EMPTY
};

enum COUNT {
    ONE_SHAPE,
    TWO_SHAPE,
    THREE_SHAPE,
};

typedef struct PackPos {
    uint8_t firstCardPos;
    uint8_t secondCardPos;
    uint8_t thirdCardPos;
} PackPos;

typedef struct pack_card {
    enum Colour colour;
    enum Shape shape;
    enum Fill fill;
    enum COUNT num;
    uint8_t bits;
} pack_card;

uint8_t IsValidPack(uint8_t card0Bits, uint8_t card1Bits, uint8_t card2Bits);
void bitsToCard(uint8_t bits, pack_card* outCard);
uint8_t cardAttrsToBits(enum Colour colour, enum Shape shape, enum Fill fill, enum COUNT num);
uint8_t PickupPack(uint8_t card0TablePos, uint8_t card1TablePos, uint8_t card2TablePos);

void DealGame(uint8_t singleColor);

extern uint8_t table[12];

// for testing
uint8_t TableHasDupes(uint8_t tableToTest[12]);
void FindPack(uint8_t tableToTest[12], struct PackPos* outPackPos);
