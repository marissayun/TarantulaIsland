#include <stdlib.h>
#include "myLib.h"
#include "game.h"
#include "furtherTrees.h"
#include "trees.h"
#include "tempspritesheet.h"

//variables
VILLAGER villager;
SPIDER spider;
int spidersCaught;
int attacks;
int lives;
int spiderTimer;
int loseGame;
// States used for villager.aniState
// SPRITERIGHT is default walking right (since can only move right)
// SPRITENET is one anistate where the net is making contact with the ground
// Idle does not have an actual image associated with it;
// Whenever villager is idle, just show whatever state villager was before (prevAniState)
enum {SPRITERIGHT, SPRITENET, SPRITEIDLE};

// Horizontal Offset
unsigned short hOff;

OBJ_ATTR shadowOAM[128];

void initializeGame() {
    
    //load spritesheet palette and tiles
    //initialize backgrounds

    // load tile palette
    DMANow(3, furtherTreesPal, PALETTE, 256);
    // set up bg 1 control register
    REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_SIZE_SMALL | BG_4BPP;
    // load furtherTrees tiles to charblock
    DMANow(3, furtherTreesTiles, &CHARBLOCK[0], furtherTreesTilesLen / 2);
    // load furtherTrees map to screenblock
    DMANow(3, furtherTreesMap, &SCREENBLOCK[28], furtherTreesMapLen / 2);
    // set up bg 0 control register
    REG_BG0CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(30) | BG_SIZE_WIDE | BG_4BPP;
    // load trees tiles to charblock
    DMANow(3, treesTiles, &CHARBLOCK[1], treesTilesLen / 2);
    // load trees map to screenblock
    DMANow(3, treesMap, &SCREENBLOCK[30], treesMapLen / 2);

    // load the spritesheet Tiles and Pal into THEIR desired spaces in memory
    DMANow(3, tempspritesheetPal, SPRITEPALETTE, tempspritesheetPalLen / 2);
    DMANow(3, tempspritesheetTiles, &CHARBLOCK[4], tempspritesheetTilesLen / 2);
    
    hOff = 0;

    // initialize variables
    spidersCaught = 0;
    attacks = 0;
    lives = 3;

    loseGame = 0;

    initializeVillager();
    initializeSpider();
}

void initializeVillager() {
    villager.width = 64;
    villager.height = 64;
    villager.cdel = 1;
    villager.rdel = 1;
    villager.col = 0 + (villager.width / 2);
	villager.row = SCREENHEIGHT - (villager.height / 2) - 50;
    villager.aniCounter = 0;
    villager.curFrame = 0;
    villager.numFrames = 3;
	villager.aniState = SPRITERIGHT; 
}

void initializeSpider() {

}

// update game each frame
void updateGame() {
    // Scroll the background
    if(BUTTON_HELD(BUTTON_LEFT)) {
        hOff--;
    }
    if(BUTTON_HELD(BUTTON_RIGHT)) {
        hOff++;
    }

    waitForVBlank();

    // change to implement parallax
    REG_BG0HOFF = hOff; 
    REG_BG1HOFF = hOff / 2; 

    updateVillager();
    updateSpider();
}

void drawGame() {
    // set up villager sprite attributes
    shadowOAM[0].attr0 = villager.row | ATTR0_4BPP | ATTR0_SQUARE;
    shadowOAM[0].attr1 = villager.col | ATTR1_LARGE;
    shadowOAM[0].attr2 = ATTR2_TILEID(villager.aniState * 8, villager.curFrame * 8);

}

void updateVillager() {
    // set previous state to current state (if not idle)
	// then reset villager's state to idle
    if (villager.aniState != SPRITEIDLE) {
        villager.prevAniState = villager.aniState;
        villager.aniState = SPRITEIDLE;
    }

    // Change the animation frame every 20 frames of gameplay
    if(villager.aniCounter % 20 == 0) {
        villager.curFrame = (villager.curFrame + 1) % villager.numFrames;
    }

    // Control movement and change animation state
    if(BUTTON_HELD(BUTTON_RIGHT)) {
        villager.aniState = SPRITERIGHT;
    }

    if(BUTTON_PRESSED(BUTTON_A)) {
        villager.aniState = SPRITENET;
    }

    // If the villager aniState is idle (thus no key is held), 
    // we want the frame to be villager standing (frame 0)
    // in whatever direction villager was facing (set aniState to prevAniState)
    // Else, if villager aniState is not idle, we want to increment aniCounter
    if (villager.aniState == SPRITEIDLE) {
        villager.curFrame = 0;
        villager.aniState = villager.prevAniState;
    } else {
        villager.aniCounter++;
    }

}

void updateSpider() {

}


