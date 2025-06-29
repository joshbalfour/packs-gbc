#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"

#include "StateGame.h"
#include "Sound.h"

IMPORT_MAP(menu);

DECLARE_SFX(bark);

uint8_t choice;
uint16_t menu_map_offset;

void START(void) {
    choice = 1;

    sfx_sound_init();

    LoadMap(TARGET_BKG, 0, 0, BANK(menu), &menu);
}

void Selected(uint8_t isBottom, uint8_t isEmpty) BANKED {
    UpdateMapTile(TARGET_BKG, 5, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 46, 0);
    UpdateMapTile(TARGET_BKG, 6, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 47, 0);
    UpdateMapTile(TARGET_BKG, 7, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 48, 0);
    UpdateMapTile(TARGET_BKG, 8, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 49, 0);
    UpdateMapTile(TARGET_BKG, 9, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 50, 0);
    UpdateMapTile(TARGET_BKG, 10, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 51, 0);
    UpdateMapTile(TARGET_BKG, 11, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 52, 0);
    UpdateMapTile(TARGET_BKG, 12, 7 + isBottom, menu_map_offset, isEmpty ? 1 : 53, 0);

    
    UpdateMapTile(TARGET_BKG, 4, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 54, 0);
    UpdateMapTile(TARGET_BKG, 5, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 55, 0);
    UpdateMapTile(TARGET_BKG, 6, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 56, 0);
    UpdateMapTile(TARGET_BKG, 7, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 57, 0);
    UpdateMapTile(TARGET_BKG, 8, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 58, 0);
    UpdateMapTile(TARGET_BKG, 9, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 59, 0);
    
    UpdateMapTile(TARGET_BKG, 11, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 60, 0);
    UpdateMapTile(TARGET_BKG, 12, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 61, 0);
    UpdateMapTile(TARGET_BKG, 13, 8 + isBottom, menu_map_offset, isEmpty ? 1 : 62, 0);

    
    UpdateMapTile(TARGET_BKG, 4, 9 + isBottom, menu_map_offset, isEmpty ? 1 : 63, 0);
    UpdateMapTile(TARGET_BKG, 13, 9 + isBottom, menu_map_offset, isEmpty ? 1 : 71, 0);

    
    UpdateMapTile(TARGET_BKG, 4, 10 + isBottom, menu_map_offset, isEmpty ? 1 : 72, 0);
    UpdateMapTile(TARGET_BKG, 5, 10 + isBottom, menu_map_offset, isEmpty ? 1 : 73, 0);
    UpdateMapTile(TARGET_BKG, 12, 10 + isBottom, menu_map_offset, isEmpty ? 1 : 74, 0);
    UpdateMapTile(TARGET_BKG, 13, 10 + isBottom, menu_map_offset, isEmpty ? 1 : 75, 0);

    
    UpdateMapTile(TARGET_BKG, 5, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 76, 0);
    UpdateMapTile(TARGET_BKG, 6, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 77, 0);
    UpdateMapTile(TARGET_BKG, 7, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 78, 0);
    UpdateMapTile(TARGET_BKG, 8, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 79, 0);
    UpdateMapTile(TARGET_BKG, 9, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 80, 0);
    UpdateMapTile(TARGET_BKG, 10, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 81, 0);
    UpdateMapTile(TARGET_BKG, 11, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 82, 0);
    UpdateMapTile(TARGET_BKG, 12, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 83, 0);
    UpdateMapTile(TARGET_BKG, 13, 11 + isBottom, menu_map_offset, isEmpty ? 1 : 84, 0);
}


uint8_t playingBorkSound = 0;

// bork voice indicator: 7,3 = 18 & 7,4 = 31

uint8_t borksndTick=0;
uint8_t isEmpty=0;
void PlayBorkSound(void) BANKED {
    if (borksndTick % 10 == 0) {
        isEmpty = !isEmpty;
    }

    UpdateMapTile(TARGET_BKG, 7, 3, menu_map_offset, isEmpty ? 1 : 18, 0);
    UpdateMapTile(TARGET_BKG, 7, 4, menu_map_offset, isEmpty ? 1 : 31, 0);

    borksndTick++;

    if (borksndTick == 40) {
        borksndTick = 0;
        playingBorkSound = 0;
    }
}

void UPDATE(void) {
    if(KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN)) {
        choice = !choice;
        if (!choice) {
            Selected(0, 1);
            Selected(4, 0);
        } else {
            Selected(4, 1);
            Selected(0, 0);
        }
	}

    if (KEY_TICKED(J_START | J_A | J_B)) {
        singleColourGame = choice;
        SetState(StateGame);
    }

    if (playingBorkSound) {
        PlayBorkSound();
    } else if (KEY_TICKED(J_SELECT)) {
        ExecuteSFX(BANK(bark), bark, SFX_MUTE_MASK(bark), SFX_PRIORITY_NORMAL);
        playingBorkSound = 1;
    }
}



void DESTROY(void) {
}