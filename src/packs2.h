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

typedef struct pack_card {
    enum Colour colour;
    enum Shape shape;
    enum Fill fill;
    enum COUNT num;
    uint8_t bits;
} pack_card;


uint8_t IsValidPack(uint8_t card0Bits, uint8_t card1Bits, uint8_t card2Bits);
pack_card bitsToCard(uint8_t bits);
uint8_t cardAttrsToBits(enum Colour colour, enum Shape shape, enum Fill fill, enum COUNT num);

void DealGame(uint8_t singleColor);