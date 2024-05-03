#ifndef _OBJECT__H
#define _OBJECT__H

#include <bits/stdc++.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"

struct Object {
    SDL_Texture* texture;
    SDL_Rect obj;

    void objectInit() {
        obj.x = 801;
        obj.w = PLANE_WIDTH;
        obj.h = PLANE_HEIGHT;
        obj.y = rand() % (SCREEN_HEIGHT - 168 + 1);
    }

    void renderObject(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &obj);
    }
};
struct Apple {

    SDL_Texture* texture;
    SDL_Rect obj;
    void AppleInit(){
        int x; int y;
        SDL_QueryTexture(texture, nullptr, nullptr, &x, &y);
        obj.x = 801;
        obj.w = x/50;
        obj.h = y/50;
        obj.y = rand() %(SCREEN_HEIGHT - 168 -y/50 +1);

    }
   void renderObject(SDL_Renderer* renderer){
        SDL_RenderCopy(renderer, texture, nullptr, &obj);
    }

};







#endif  _OBJECT__H
