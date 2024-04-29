#ifndef _LOGIC__H
#define _LOGIC__H



#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Object.h"


using namespace std;



struct Mouse {
    int x, y;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    void move() {
        x += dx; y += dy;
    }
    void turnNorth() {
        dy = -speed; dx = 0;
    }
    void turnSouth() {
        dy = speed; dx = 0;
    }
    void turnWest() {
        dy = 0; dx = -speed;
    }
    void turnEast() {
        dy = 0; dx = speed;
    }
};


struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 ) { scrollingOffset = width - scrollingOffset; }
    }
};

void check(int &x, int &y, Mouse mouse){
    mouse.move();
    if(mouse.x<0)
        mouse.x = 0;
    if(mouse.y < 0)
        mouse.y = 0;
    if(mouse.y > SCREEN_HEIGHT - 168)
        mouse.y = SCREEN_HEIGHT -168;
    x = mouse.x;
    y = mouse.y;

}

bool isCollision(int &x, int &y, const vector <Object>& plane) {

    for(int i = 0 ;i < 8; i++)
    if (x < plane[i].obj.x + PLANE_WIDTH-10 &&
        x + 182/2 > plane[i].obj.x+10 &&
        y < plane[i].obj.y + PLANE_HEIGHT-20 &&
        y + 168/2 > plane[i].obj.y+20) {
        return true;
    }
    return false;
}
void checkMove (vector <Object> &plane, int x ){
        if(x <500){
            plane[1].obj.x -= OBJECT_SPEED;
        }
        if(plane[1].obj.x <500){
            plane[2].obj.x -= OBJECT_SPEED;
        }
        if(plane[2].obj.x <500){
            plane[3].obj.x -= OBJECT_SPEED;
        }
        if(plane[3].obj.x <500){
            plane[4].obj.x -= OBJECT_SPEED;
        }
        if(plane[4].obj.x <500){
            plane[5].obj.x -= OBJECT_SPEED;
        }
        if(plane[5].obj.x <500){
            plane[6].obj.x -= OBJECT_SPEED;
        }
        if(plane[6].obj.x <500){
            plane[7].obj.x -= OBJECT_SPEED;
        }

}

string TextWithVariable (const char* text, int varible){

        stringstream oss;
        oss << text << varible;
        string buffer = oss.str();
        return buffer;


}




#endif  _LOGIC__H

