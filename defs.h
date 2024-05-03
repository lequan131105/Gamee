#ifndef _DEFS__H

#define _DEFS__H

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;
const char * WINDOW_TITLE = "Hello World";
const int INITIAL_SPEED =10;
const char* APPLE_SPRITE_FILE = "apple.png";
const char* BIRD_SPRITE_FILE = "bird.png";
const char* PLANE_SPRITE_FILE = "af1.png";
const int PLANE_WIDTH = 80;
const int PLANE_HEIGHT = 33;
const char*SOUND_EFFECT_FILE = "appleGain.wav";
const int OBJECT_SPEED = 10;
const int CenterX = 396;
const int CenterY = 319;
const int Radius = 64;
enum Gamestatus {
    inMenu,
    start,
    pause,
    gameover,
    quitgame,
};
const int BIRD_CLIPS[][4] = {
    {0, 0, 182, 168},
    {181, 0, 182, 168},
    {364, 0, 182, 168},
    {547, 0, 182, 168},
    {728, 0, 182, 168},

    {0, 170, 182, 168},
    {181, 170, 182, 168},
    {364, 170, 182, 168},
    {547, 170, 182, 168},
    {728, 170, 182, 168},

    {0, 340, 182, 168},
    {181, 340, 182, 168},
    {364, 340, 182, 168},
    {547, 340, 182, 168},
};
const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;
#endif _DEFS__H
