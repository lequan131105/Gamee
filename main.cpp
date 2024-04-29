#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Object.h"

using namespace std;








 int main(int argc, char *argv[])
{   Graphics graphics;
    graphics.init();
    srand(time(nullptr));


    Mix_Music *gameMusic = loadMusic("Game of throne.mp3");
    play(gameMusic);

    TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 20);
    SDL_Color color = {255, 255, 255};



    int x, y;

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("bg2.png"));

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture(BIRD_SPRITE_FILE);
    bird.init(birdTexture, BIRD_FRAMES, BIRD_CLIPS);

    vector <Object> plane;
    for(int i =0; i<8; i ++){
    Object newPlane;
    newPlane.texture = graphics.loadTexture(PLANE_SPRITE_FILE);
    newPlane.objectInit();
    plane.push_back(newPlane);
   }

    int waves = 1;
    int textWidth;
    int textHeigth;



    Mouse mouse;
    mouse.x = 0;
    mouse.y = SCREEN_HEIGHT / 2 - 205 / 2;

    int delayTime = 50;



    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
        SDL_Texture* helloText = graphics.renderText(TextWithVariable("Waves: ",waves).c_str(), font, color, graphics.renderer);

        SDL_QueryTexture(helloText,nullptr,nullptr,&textWidth, &textHeigth);

        graphics.renderTexture(helloText, SCREEN_WIDTH/2 - textWidth/2, 0);

        Uint32 mouseState = SDL_GetMouseState(&x,&y);

        const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

        if(currentKeyStates[SDL_SCANCODE_UP]) mouse.turnNorth();
        if(currentKeyStates[SDL_SCANCODE_DOWN]) mouse.turnSouth();
        if(currentKeyStates[SDL_SCANCODE_LEFT]) mouse.turnWest();
        if(currentKeyStates[SDL_SCANCODE_RIGHT]) mouse.turnEast();

        for(int i=0;i<8;i++){
            plane[i].renderObject(graphics.renderer);
        }
        plane[0].obj.x -= OBJECT_SPEED;
       checkMove(plane, plane[0].obj.x);

        if(plane[7].obj.x < 0){
            for(int i =0; i<8; i ++){
            Object newPlane;
            newPlane.texture = graphics.loadTexture(PLANE_SPRITE_FILE);
            newPlane.objectInit();
            plane[i]=newPlane;
            }
            waves ++;
            delayTime -= 2;
        }
        graphics.presentScene();



        check(mouse.x, mouse.y, mouse);

        bird.tick();

        background.scroll(5);


        graphics.render(background);
        render(mouse.x, mouse.y, bird, graphics.renderer);

        if(isCollision(mouse.x, mouse.y, plane)){
            break;
        }



        SDL_Delay(delayTime);


    }

    TTF_CloseFont(font);
    SDL_DestroyTexture( background.texture );
    graphics.quit();
    return 0;
   }










