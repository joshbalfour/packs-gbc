#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

IMPORT_MAP(map);

#define VERT_SPACING 6
#define HORIZ_SPACING 5

#define X_START 1
#define Y_START 1

#define FILL_FILLED 0
#define FILL_EMPTY 3
#define FILL_STRIPED 9

#define SHAPE_RECT 11
#define SHAPE_SQUEEZY 27
#define SHAPE_DIAMOND 40

#define COLOUR_RED 0
#define COLOUR_BLUE 1
#define COLOUR_ORANGE 2


void PopulateCard (uint8_t gridX, uint8_t gridY, uint8_t num, uint8_t colour, uint8_t shape, uint8_t fill) {
    uint8_t x = X_START + (HORIZ_SPACING * gridX);
    uint8_t y = Y_START + (VERT_SPACING * gridY);

    for (uint8_t i = 0; i<num; i++) {
        uint8_t dedupe = fill != FILL_FILLED ? 2 : 1;
        uint8_t tileNum = shape + fill + (colour * dedupe);

        uint8_t anotherOne = fill == FILL_FILLED ? 0 : 1;

        UpdateMapTile(TARGET_BKG, x, y + i, BANK(map), tileNum, NULL);
        UpdateMapTile(TARGET_BKG, x + 1, y + i, BANK(map), tileNum + anotherOne, NULL);
    }
}!


void START(void) {
	// scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);
    PopulateCard(0, 0, 1, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
    PopulateCard(0, 1, 2, COLOUR_ORANGE, SHAPE_RECT, FILL_FILLED);
    PopulateCard(0, 2, 1, COLOUR_BLUE, SHAPE_RECT, FILL_STRIPED);
    
    PopulateCard(1, 0, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
    PopulateCard(1, 1, 1, COLOUR_ORANGE, SHAPE_RECT, FILL_STRIPED);
    PopulateCard(1, 2, 3, COLOUR_BLUE, SHAPE_RECT, FILL_STRIPED);

    PopulateCard(2, 0, 1, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
    PopulateCard(2, 1, 1, COLOUR_BLUE, SHAPE_RECT, FILL_FILLED);
    PopulateCard(2, 2, 3, COLOUR_BLUE, SHAPE_RECT, FILL_STRIPED);

    PopulateCard(3, 0, 2, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
    PopulateCard(3, 1, 1, COLOUR_RED, SHAPE_RECT, FILL_STRIPED);
    PopulateCard(3, 2, 3, COLOUR_BLUE, SHAPE_RECT, FILL_EMPTY);
}

void UPDATE(void) {
}