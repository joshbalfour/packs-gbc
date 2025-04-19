#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#define HORIZ_CARD_SPACING 8
#define VERT_CARD_SPACING 15
#define VERT_SHAPE_SPACING 0

#define FILL_EMPTY 0
#define FILL_FILLED 1
#define FILL_STRIPED 2

#define SHAPE_RECT 0
#define SHAPE_SQUEEZY 1
#define SHAPE_DIAMOND 2

#define COLOUR_RED 0
#define COLOUR_ORANGE 1
#define COLOUR_BLUE 2

#define START_X 10
#define START_Y 10

#define CARD_HEIGHT 32

#define TILE_OFFSET 0

IMPORT_TILES(cardtiles);

uint16_t map_offset;

/*
1 2 2 3
4 5 5 6
4 5 5 6
7 8 8 9
*/

void DrawCard (uint8_t gridX, uint8_t gridY, uint8_t num, uint8_t colour, uint8_t shape, uint8_t fill) {
	uint16_t x = START_X + (gridX * HORIZ_CARD_SPACING);
	uint8_t i;

	for (i = 0; i<num; i++) {
		uint16_t y = START_Y + (gridY * (VERT_CARD_SPACING)) + (i * (VERT_SHAPE_SPACING + 8));

		UpdateMapTile(TARGET_BKG, x, y, map_offset, TILE_OFFSET + 1, NULL);
		UpdateMapTile(TARGET_BKG, x+1, y, map_offset, TILE_OFFSET + 2, NULL);
		UpdateMapTile(TARGET_BKG, x+2, y, map_offset, TILE_OFFSET + 2, NULL);
		UpdateMapTile(TARGET_BKG, x+3, y, map_offset, TILE_OFFSET + 3, NULL);

		UpdateMapTile(TARGET_BKG, x, y+1, map_offset, TILE_OFFSET + 4, NULL);
		UpdateMapTile(TARGET_BKG, x+1, y+1, map_offset, TILE_OFFSET + 5, NULL);
		UpdateMapTile(TARGET_BKG, x+2, y+1, map_offset, TILE_OFFSET + 5, NULL);
		UpdateMapTile(TARGET_BKG, x+3, y+1, map_offset, TILE_OFFSET + 6, NULL);

		UpdateMapTile(TARGET_BKG, x, y+2, map_offset, TILE_OFFSET + 4, NULL);
		UpdateMapTile(TARGET_BKG, x+1, y+2, map_offset, TILE_OFFSET + 5, NULL);
		UpdateMapTile(TARGET_BKG, x+2, y+2, map_offset, TILE_OFFSET + 5, NULL);
		UpdateMapTile(TARGET_BKG, x+3, y+2, map_offset, TILE_OFFSET + 6, NULL);

		UpdateMapTile(TARGET_BKG, x, y+3, map_offset, TILE_OFFSET + 7, NULL);
		UpdateMapTile(TARGET_BKG, x+1, y+3, map_offset, TILE_OFFSET + 8, NULL);
		UpdateMapTile(TARGET_BKG, x+2, y+3, map_offset, TILE_OFFSET + 8, NULL);
		UpdateMapTile(TARGET_BKG, x+3, y+3, map_offset, TILE_OFFSET + 9, NULL);

		// UpdateMapTile(TARGET_BKG, x+24, y, map_offset, 8, NULL);

		// Sprite* firstPart = SpriteManagerAdd(SpriteShape, x, y);
		// SetFrame(firstPart, 0);

		// Sprite* secondPart = SpriteManagerAdd(SpriteShape, x+8, y);
		// SetFrame(secondPart, 1);
	}
}

void START(void) {
	map_offset = ScrollSetTiles(last_tile_loaded, BANK(cardtiles), &(cardtiles));

	for (uint8_t x = 0; x < 160 / 8; x++) {
        for (uint8_t y = 0; y < 144 / 8; y++) {
            UpdateMapTile(TARGET_BKG, x,y, map_offset, 0, 0);
        }
    }

	DrawCard(0, 0, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(1, 0, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(2, 0, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(3, 0, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);

	// DrawCard(0, 1, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(1, 1, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(2, 1, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(3, 1, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);

	// DrawCard(0, 2, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(1, 2, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(2, 2, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
	// DrawCard(3, 2, 3, COLOUR_RED, SHAPE_RECT, FILL_EMPTY);
}

void UPDATE(void) {
}
