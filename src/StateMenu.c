#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"

#include "StateGame.h"

IMPORT_MAP(menu);

Sprite* arrowSpr;

uint8_t choice;

void START(void) {
    choice = 1;

    InitScroll(BANK(menu), &menu, 0, 0);
    arrowSpr = SpriteManagerAdd(SpriteArrow, 40, 80);
}

void UPDATE(void) {
    if(KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN)) {
        choice = !choice;

        if (!choice) {
            TranslateSprite(arrowSpr, 0, 25);
        } else {
            TranslateSprite(arrowSpr, 0, -25);
        }
	}

    if (KEY_TICKED(J_START | J_A | J_B)) {
        singleColourGame = choice;
        SetState(StateGame);
    }
}

void DESTROY(void) {
}