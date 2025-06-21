#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Keys.h"

#include "packs.h"
#include "Sound.h"

IMPORT_TILES(cardtiles);

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
#define BLANK_CARD_BG_TILE 11

#define CARD_FRAME_DEFAULT 0
#define CARD_FRAME_SELECTED 1
#define CARD_FRAME_SUCCESS 2
#define CARD_FRAME_ERROR 3

uint16_t map_offset = 0;

#define CARD_FRAME_OFFSET 0

void DrawCardFrame (uint8_t gridX, uint8_t gridY, uint8_t frameType) BANKED {
    // error = 0x05
    // success = 0x06
    unsigned char pal = frameType == CARD_FRAME_DEFAULT ? 0x00 : (frameType == CARD_FRAME_SELECTED ? 0x04 : (frameType == CARD_FRAME_ERROR ? 0x05 : (frameType == CARD_FRAME_SUCCESS ? 0x06 : 0x01)));
    uint8_t palette = (UINT8)(BANK(cardtiles) >> 8) + pal;

    uint8_t x = HORIZ_SPACING * gridX;
    uint8_t y = VERT_SPACING * gridY;

    
    UpdateMapTile(TARGET_BKG, x, y, map_offset, 4 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 1, y, map_offset, 7 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 2, y, map_offset, 7 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 3, y, map_offset, 7 + CARD_FRAME_OFFSET, &palette);

    if (DEVICE_SUPPORTS_COLOR || frameType != CARD_FRAME_SELECTED) {
        UpdateMapTile(TARGET_BKG, x + 4, y, map_offset, 1 + CARD_FRAME_OFFSET, &palette);
    } else {
        UpdateMapTile(TARGET_BKG, x + 4, y, map_offset, 0, &palette);
    }
    

    UpdateMapTile(TARGET_BKG, x, y + 1, map_offset, 5 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 1, map_offset, 2 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x, y + 2, map_offset, 5 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 2, map_offset, 2 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x, y + 3, map_offset, 5 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 3, map_offset, 2 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x, y + 4, map_offset, 5 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 4, map_offset, 2 + CARD_FRAME_OFFSET, &palette);

    UpdateMapTile(TARGET_BKG, x, y + 5, map_offset, 6 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 1, y + 5, map_offset, 8 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 2, y + 5, map_offset, 8 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 3, y + 5, map_offset, 8 + CARD_FRAME_OFFSET, &palette);
    UpdateMapTile(TARGET_BKG, x + 4, y + 5, map_offset, 3 + CARD_FRAME_OFFSET, &palette);
}

void DrawCard (uint8_t gridX, uint8_t gridY, uint8_t num, uint8_t colour, uint8_t shape, uint8_t fill) BANKED {
    DrawCardFrame(gridX, gridY, CARD_FRAME_DEFAULT);
    uint8_t x = X_START + (HORIZ_SPACING * gridX);
    uint8_t y = Y_START + (VERT_SPACING * gridY);

    uint8_t tileOffset = SHAPE_TILE_OFFSET + shape;
    uint8_t fillOffset = fill * 9;

    unsigned char pal = colour == COLOUR_RED ? 0x01 : (colour == COLOUR_BLUE ? 0x02 : 0x03);
    uint8_t palette = (UINT8)(BANK(cardtiles) >> 8) + pal;

    for (uint8_t cy = 0; cy<4; cy++) {
        if (num == 3 || num == 1) {
            if (fill == FILL_FILLED && shape == SHAPE_RECT) {
                if (cy == 0 || cy == 3) { // top or bottom rows
                    if (num == 1) {
                        UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, BLANK_CARD_BG_TILE, &palette);
                    } else {
                        UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, tileOffset + fillOffset + 0, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, tileOffset + fillOffset, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, tileOffset + fillOffset, &palette);
                    }
                }
                if (cy == 1) {
                    UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, tileOffset + fillOffset + 2, &palette);
                    UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, tileOffset + fillOffset + 2, &palette);
                    UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, tileOffset + fillOffset + 2, &palette);
                }
                if (cy == 2) {
                    UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, tileOffset + fillOffset + 1, &palette);
                    UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, tileOffset + fillOffset + 1, &palette);
                    UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, tileOffset + fillOffset + 1, &palette);
                }
            } else {
                if (cy == 0 || cy == 3) { // top or bottom rows
                    if (num == 1) {
                        UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, BLANK_CARD_BG_TILE, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, BLANK_CARD_BG_TILE, &palette);
                    } else {
                        UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, tileOffset + fillOffset + 0, &palette);
                        UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, tileOffset + fillOffset + 1, &palette);
                        UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, tileOffset + fillOffset + 2, &palette);
                    }
                } else {
                    uint8_t rowOffset = 6 / cy;
                    // l, m, r
                    UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, tileOffset + fillOffset + rowOffset + 0, &palette);
                    UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, tileOffset + fillOffset + rowOffset + 1, &palette);
                    UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, tileOffset + fillOffset + rowOffset + 2, &palette);
                }
            }
        }

        if (num == 2) {
            uint8_t top = cy % 2;
            uint8_t rowOffset = (fill == FILL_FILLED && shape == SHAPE_RECT) ? (top ? 1 : 2) : (top ? 3 : 6);
            // l, m, r
            UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, tileOffset + fillOffset + rowOffset + 0, &palette);
            UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, tileOffset + fillOffset + rowOffset + ((fill == FILL_FILLED && shape == SHAPE_RECT) ? 0 : 1), &palette);
            UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, tileOffset + fillOffset + rowOffset + ((fill == FILL_FILLED && shape == SHAPE_RECT) ? 0 : 2), &palette);
        }
    }
}

void DrawEmptyCard(uint8_t gridX, uint8_t gridY) BANKED {
    DrawCardFrame(gridX, gridY, CARD_FRAME_DEFAULT);
    uint8_t x = X_START + (HORIZ_SPACING * gridX);
    uint8_t y = Y_START + (VERT_SPACING * gridY);

    for (uint8_t cy = 0; cy<4; cy++) {
        UpdateMapTile(TARGET_BKG, x, y + cy, map_offset, BLANK_CARD_BG_TILE, NULL);
        UpdateMapTile(TARGET_BKG, x + 1, y + cy, map_offset, BLANK_CARD_BG_TILE, NULL);
        UpdateMapTile(TARGET_BKG, x + 2, y + cy, map_offset, BLANK_CARD_BG_TILE, NULL);
    }
}

Sprite* selectorSpr;

uint8_t gridX = 0;
uint8_t gridY = 0;

#define INITIAL_X 20
#define INITIAL_Y 24

void DrawGrid(void) BANKED {
    for (uint8_t i = 0; i<12; i++) {
        if (table[i] == UINT8_MAX) {
            // empty space
            DrawEmptyCard(i % 4, i / 4);
        } else {
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
}

uint8_t singleColourGame = 0;
uint8_t resumeGame = 0;
void START(void) {
	map_offset = ScrollSetTiles(0, BANK(cardtiles), &cardtiles);

    selectorSpr = SpriteManagerAdd(SpriteSelector, INITIAL_X, INITIAL_Y);

    if (resumeGame) {
        resumeGame = 0;
        fade_enabled = TRUE;
    } else {
        DealGame(singleColourGame);
    }

    DrawGrid();
}

uint8_t selectedCard0X = UINT8_MAX;
uint8_t selectedCard0Y = UINT8_MAX;
uint8_t selectedCard1X = UINT8_MAX;
uint8_t selectedCard1Y = UINT8_MAX;
uint8_t selectedCard2X = UINT8_MAX;
uint8_t selectedCard2Y = UINT8_MAX;

uint8_t playSuccess = 0;
uint8_t playFail = 0;
uint8_t sndTick = 0;
uint8_t waitFor = 20;

void SelectCard(uint8_t gridX, uint8_t gridY) BANKED {
    if (table[gridX + (gridY*4)] == UINT8_MAX) {
       return; 
    }

    if (selectedCard0X != UINT8_MAX) {
        if (gridX == selectedCard0X && gridY == selectedCard0Y) {
            DrawCardFrame(gridX, gridY, CARD_FRAME_DEFAULT);
            selectedCard0X = UINT8_MAX;
            selectedCard0Y = UINT8_MAX;
            return;
        }
    }

    if (selectedCard1X != UINT8_MAX) {
        if (gridX == selectedCard1X && gridY == selectedCard1Y) {
            DrawCardFrame(gridX, gridY, CARD_FRAME_DEFAULT);
            selectedCard1X = UINT8_MAX;
            selectedCard1Y = UINT8_MAX;
            return;
        }
    }

    DrawCardFrame(gridX, gridY, CARD_FRAME_SELECTED);

    if (selectedCard0X != UINT8_MAX) {
        if (selectedCard1X != UINT8_MAX) {
            PlayFx(CHANNEL_1, 10, 0x00, 0x8A, 0xA3, 0xC9, 0x86);
            selectedCard2X = gridX;
            selectedCard2Y = gridY;
            if (IsValidPack(
                table[selectedCard0X + (selectedCard0Y*4)],
                table[selectedCard1X + (selectedCard1Y*4)],
                table[gridX + (gridY*4)]
            )) {
                sndTick = 0;
                playSuccess = 1;
            } else {
                // not a valid pack
                sndTick = 0;
                playFail = 1;
            }
        } else {
            PlayFx(CHANNEL_1, 10, 0x00, 0x8A, 0xA3, 0xA9, 0x86);
            selectedCard1X = gridX;
            selectedCard1Y = gridY;
        }
    } else {
        PlayFx(CHANNEL_1, 10, 0x00, 0x8A, 0xA3, 0x81, 0x86);
        selectedCard0X = gridX;
        selectedCard0Y = gridY;
    }
}

void SoundTicker(void) BANKED {
    if (playSuccess || playFail) {
        // if (sndTick == (0 + waitFor)) {
        //     PlayFx(CHANNEL_1, 3, 0x00, 0x8A, 0xA3, 0xA9, 0x86);
        // }
        if (sndTick == waitFor) {
            DrawCardFrame(selectedCard0X, selectedCard0Y, playFail ? CARD_FRAME_ERROR : CARD_FRAME_SUCCESS);
            DrawCardFrame(selectedCard1X, selectedCard1Y, playFail ? CARD_FRAME_ERROR : CARD_FRAME_SUCCESS);
            DrawCardFrame(selectedCard2X, selectedCard2Y, playFail ? CARD_FRAME_ERROR : CARD_FRAME_SUCCESS);
        }
        if (sndTick == (5 + waitFor)) {
            PlayFx(CHANNEL_1, 3, 0x00, 0x8A, 0xA3, 0x81, 0x86);
        }
        if (sndTick == (10 + waitFor)) {
            PlayFx(CHANNEL_1, 3, 0x00, 0x8A, 0xA3, 0xC9, 0x86);
        }
        if (sndTick == (15 + waitFor)) {
            PlayFx(CHANNEL_1, 3, 0x00, 0x8A, 0xA3, 0xEF, 0x86);
        }
        if (sndTick == (20 + waitFor)) {
            if (playFail) {
                PlayFx(CHANNEL_1, 3, 0x00, 0x8A, 0xA3, 0xA9, 0x86);
                DrawCardFrame(selectedCard0X, selectedCard0Y, CARD_FRAME_DEFAULT);
                DrawCardFrame(selectedCard1X, selectedCard1Y, CARD_FRAME_DEFAULT);
                DrawCardFrame(selectedCard2X, selectedCard2Y, CARD_FRAME_DEFAULT);
            } else if (playSuccess) {
                PlayFx(CHANNEL_1, 3, 0x00, 0x8A, 0xA3, 0xFF, 0x86);
                uint8_t gameOver = PickupPack(selectedCard0X + (selectedCard0Y*4), selectedCard1X + (selectedCard1Y*4), selectedCard2X + (selectedCard2Y*4));
                DrawGrid();
                if (gameOver) {
                    SetState(StateDone);
                }
            }
            
            selectedCard0X = UINT8_MAX;
            selectedCard0Y = UINT8_MAX;
            selectedCard1X = UINT8_MAX;
            selectedCard1Y = UINT8_MAX;
            selectedCard2X = UINT8_MAX;
            selectedCard2Y = UINT8_MAX;

            playSuccess = 0;
            playFail = 0;
        }
        sndTick++;
    }
}

void UPDATE(void) {
    SoundTicker();

    if (playSuccess || playFail) {
        return;
    }

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

    if (KEY_TICKED(J_START)) {
        fade_enabled = FALSE;
        SetState(StatePaused);
    }
}
