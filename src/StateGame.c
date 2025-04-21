#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Keys.h"

#include "packs.h"

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

void DrawCardFrame (uint8_t gridX, uint8_t gridY, uint8_t frameType) BANKED {
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

void DrawCard (uint8_t gridX, uint8_t gridY, uint8_t num, uint8_t colour, uint8_t shape, uint8_t fill) {
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

void DrawGrid() BANKED {
    for (uint8_t i = 0; i<12; i++) {
        struct pack_card card;
        bitsToCard(table[i], &card);
        DrawCard(
            i % 4,
            i / 4,
            card.num + 1,
            card.colour,
            card.shape == DIAMOND ? SHAPE_DIAMOND : (card.shape == RECTANGLE ? SHAPE_RECT : SHAPE_SQUISH),
            card.fill == FILLED ? FILL_FILLED : (card.fill == STRIPED ? FILL_STRIPED : FILL_EMPTY)
        );
    }
}

void START(void) {
	// scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);

    selectorSpr = SpriteManagerAdd(SpriteSelector, INITIAL_X, INITIAL_Y);

    DealGame(1);

    DrawGrid();
}

uint8_t selectedCard0X = 99;
uint8_t selectedCard0Y = 99;
uint8_t selectedCard1X = 99;
uint8_t selectedCard1Y = 99;

void SelectCard(uint8_t gridX, uint8_t gridY) BANKED {
    DrawCardFrame(gridX, gridY, CARD_FRAME_SELECTED);

    if (selectedCard0X != 99) {
        if (selectedCard1X != 99) {
            if (IsValidPack(
                table[selectedCard0X + (selectedCard0Y*4)],
                table[selectedCard1X + (selectedCard1Y*4)],
                table[gridX + (gridY*4)]
            )) {
                uint8_t gameOver = PickupPack(selectedCard0X + (selectedCard0Y*4), selectedCard1X + (selectedCard1Y*4), gridX + (gridY*4));
                DrawGrid();
                if (gameOver) {
                    // do something
                }
            } else {
                // not a valid pack
                DrawCardFrame(selectedCard0X, selectedCard0Y, CARD_FRAME_DEFAULT);
                DrawCardFrame(selectedCard1X, selectedCard1Y, CARD_FRAME_DEFAULT);
                DrawCardFrame(gridX, gridY, CARD_FRAME_DEFAULT);
            }
            
            selectedCard0X = 99;
            selectedCard0Y = 99;
            selectedCard1X = 99;
            selectedCard1Y = 99;
        } else {
            selectedCard1X = gridX;
            selectedCard1Y = gridY;
        }
    } else {
        selectedCard0X = gridX;
        selectedCard0Y = gridY;
    }
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
        SelectCard(gridX, gridY);
    }
}