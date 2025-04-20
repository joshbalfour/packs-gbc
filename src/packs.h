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


uint8_t IsValidPack(pack_card* card0, pack_card* card1, pack_card* card2);

void DealGame(uint8_t singleColor);