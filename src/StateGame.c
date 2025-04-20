#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Keys.h"

IMPORT_MAP(map);

#define VERT_SPACING 6
#define HORIZ_SPACING 5

#define X_START 1
#define Y_START 1

/*
red
    empty
        top + bottom
            l           13
            m           14
            r           15
        mid
            bl          16
            bm          17
            br          18
            tl          19
            tm          20
            tr          21
    striped (+9)
        top + bottom
            l           22
            m           23
            r           24
        mid
            bl          25
            bm          26
            br          27
            tl          28
            tm          29
            tr          30
    filled (+18)
        top + bottom    31  
        mid
            btm         32
            top         33
*/

#define SHAPE_TILE_OFFSET 13

#define FILL_EMPTY 0
#define FILL_STRIPED 1
#define FILL_FILLED 2

#define COLOUR_RED 0
#define COLOUR_ORANGE 1
#define COLOUR_BLUE 2

#define SHAPE_RECT 0
#define SHAPE_SQUISH 21
#define SHAPE_DIAMOND 48
#define BLANK_CARD_BG_TILE 10

#define CARD_FRAME_DEFAULT 0
#define CARD_FRAME_SELECTED 1
#define CARD_FRAME_SUCCESS 2
#define CARD_FRAME_ERROR 3

void DrawCardFrame (uint8_t gridX, uint8_t gridY, uint8_t frameType) {
    unsigned char pal = frameType == CARD_FRAME_DEFAULT ? 0x00 : (frameType == CARD_FRAME_SELECTED ? 0x03 : 0x01);
    uint8_t palette = (UINT8)(BANK(map) >> 8) + pal;

    uint8_t x = HORIZ_SPACING * gridX;
    uint8_t y = VERT_SPACING * gridY;

    UpdateMapTile(TARGET_BKG, x, y, BANK(map), 4 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 1, y, BANK(map), 7 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 2, y, BANK(map), 7 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 3, y, BANK(map), 7 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y, BANK(map), 1 - 1, &palette);

    UpdateMapTile(TARGET_BKG, x, y + 1, BANK(map), 5 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 1, BANK(map), 2 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x, y + 2, BANK(map), 5 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 2, BANK(map), 2 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x, y + 3, BANK(map), 5 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 3, BANK(map), 2 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x, y + 4, BANK(map), 5 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 4, BANK(map), 2 - 1, &palette);

    
    UpdateMapTile(TARGET_BKG, x, y + 5, BANK(map), 6 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 1, y + 5, BANK(map), 8 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 2, y + 5, BANK(map), 8 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 3, y + 5, BANK(map), 8 - 1, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 5, BANK(map), 3 - 1, &palette);
}

void PopulateCard (uint8_t gridX, uint8_t gridY, uint8_t num, uint8_t colour, uint8_t shape, uint8_t fill) {
    DrawCardFrame(gridX, gridY, CARD_FRAME_DEFAULT);
    uint8_t x = X_START + (HORIZ_SPACING * gridX);
    uint8_t y = Y_START + (VERT_SPACING * gridY);

    uint8_t tileOffset = SHAPE_TILE_OFFSET + shape - 1;
    uint8_t fillOffset = fill * 9;

    unsigned char pal = colour == COLOUR_RED ? 0x01 : (colour == COLOUR_BLUE ? 0x02 : 0x03);
    uint8_t palette = (UINT8)(BANK(map) >> 8) + pal;

    for (uint8_t cy = 0; cy<4; cy++) {
        if (num == 3 || num == 1) {
            if (fill == FILL_FILLED && shape == SHAPE_RECT) {
                if (cy == 0 || cy == 3) { // top or bottom rows
                    if (num == 1) {
                        UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), BLANK_CARD_BG_TILE, &palette);
                    } else {
                        UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), tileOffset + fillOffset + 0, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), tileOffset + fillOffset, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), tileOffset + fillOffset, &palette);
                    }
                }
                if (cy == 1) {
                    UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), tileOffset + fillOffset + 2, &palette);
                    UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), tileOffset + fillOffset + 2, &palette);
                    UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), tileOffset + fillOffset + 2, &palette);
                }
                if (cy == 2) {
                    UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), tileOffset + fillOffset + 1, &palette);
                    UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), tileOffset + fillOffset + 1, &palette);
                    UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), tileOffset + fillOffset + 1, &palette);
                }
            } else {
                if (cy == 0 || cy == 3) { // top or bottom rows
                    if (num == 1) {
                        UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), BLANK_CARD_BG_TILE, &palette);
                    } else {
                        UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), tileOffset + fillOffset + 0, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), tileOffset + fillOffset + 1, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), tileOffset + fillOffset + 2, &palette);
                    }
                } else {
                    uint8_t rowOffset = 6 / cy;
                    // l, m, r
                    UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), tileOffset + fillOffset + rowOffset + 0, &palette);
                    UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), tileOffset + fillOffset + rowOffset + 1, &palette);
                    UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), tileOffset + fillOffset + rowOffset + 2, &palette);
                }
            }
        }

        if (num == 2) {
            uint8_t top = cy % 2;
            uint8_t rowOffset = (fill == FILL_FILLED && shape == SHAPE_RECT) ? (top ? 1 : 2) : (top ? 3 : 6);
            // l, m, r
            UpdateMapTile(TARGET_BKG, x, y + cy, BANK(map), tileOffset + fillOffset + rowOffset + 0, &palette);
            UpdateMapTile(TARGET_BKG, x + 1, y + cy, BANK(map), tileOffset + fillOffset + rowOffset + ((fill == FILL_FILLED && shape == SHAPE_RECT) ? 0 : 1), &palette);
            UpdateMapTile(TARGET_BKG, x + 2, y + cy, BANK(map), tileOffset + fillOffset + rowOffset + ((fill == FILL_FILLED && shape == SHAPE_RECT) ? 0 : 2), &palette);
        }
    }
}

Sprite* selectorSpr;

uint8_t gridX = 0;
uint8_t gridY = 0;

#define INITIAL_X 20
#define INITIAL_Y 24

void START(void) {
	// scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);

    selectorSpr = SpriteManagerAdd(SpriteSelector, INITIAL_X, INITIAL_Y);

    PopulateCard(0, 0, 3, COLOUR_RED, SHAPE_DIAMOND, FILL_EMPTY);
    PopulateCard(1, 0, 3, COLOUR_RED, SHAPE_DIAMOND, FILL_FILLED);
    PopulateCard(2, 0, 3, COLOUR_ORANGE, SHAPE_DIAMOND, FILL_FILLED);
    PopulateCard(3, 0, 3, COLOUR_BLUE, SHAPE_DIAMOND, FILL_FILLED);

    PopulateCard(0, 1, 2, COLOUR_RED, SHAPE_DIAMOND, FILL_STRIPED);
    PopulateCard(1, 1, 2, COLOUR_RED, SHAPE_RECT, FILL_STRIPED);
    PopulateCard(2, 1, 2, COLOUR_ORANGE, SHAPE_DIAMOND, FILL_STRIPED);
    PopulateCard(3, 1, 2, COLOUR_BLUE, SHAPE_SQUISH, FILL_STRIPED);

    PopulateCard(0, 2, 1, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
    PopulateCard(1, 2, 1, COLOUR_RED, SHAPE_DIAMOND, FILL_STRIPED);
    PopulateCard(2, 2, 1, COLOUR_ORANGE, SHAPE_SQUISH, FILL_FILLED);
    PopulateCard(3, 2, 1, COLOUR_BLUE, SHAPE_DIAMOND, FILL_FILLED);
}

void UPDATE(void) {
    if(KEY_TICKED(J_UP)) {
        if (!gridY) {
            gridY = 2;
        } else {
            gridY--;
        }
	}

	if(KEY_TICKED(J_DOWN)) {
        gridY++;
        if (gridY > 2) {
            gridY = 0;
        }
	}

    
    if(KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN)) {
        selectorSpr->y = INITIAL_Y + (gridY * 48);
    }

	if(KEY_TICKED(J_LEFT)) {
        if (!gridX) {
            gridX = 3;
        } else {
            gridX--;
        }
	}

	if(KEY_TICKED(J_RIGHT)) {
        gridX++;
        if (gridX > 3) {
            gridX = 0;
        }
	}

    if(KEY_TICKED(J_LEFT) || KEY_TICKED(J_RIGHT)) {
        selectorSpr->x = INITIAL_X + (gridX * 40);
    }

    if (KEY_TICKED(J_A)) {
        DrawCardFrame(gridX, gridY, CARD_FRAME_SELECTED);
    }
}