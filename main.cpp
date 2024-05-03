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
    Gamestatus gamestatus;
    gamestatus = inMenu;
    SDL_Texture* menuTexture = graphics.loadTexture("StartMenu.png");
    SDL_Texture* gameoverTexture = graphics.loadTexture("GameOver.jpg");



    Mix_Music *gameMusic = loadMusic("Game of throne.mp3");
    play(gameMusic);

    TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 20);
    SDL_Color color = {255, 255, 255};





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
    vector <Apple> apple;
    for(int i = 0; i <4; i++){
            Apple newApple;
            newApple.texture = graphics.loadTexture(APPLE_SPRITE_FILE);
            newApple.AppleInit();
            apple.push_back(newApple);
        }


    int waves = 1;
    int textWidth;
    int textHeigth;
    int numApple = 0;

    Mix_Chunk* soundEffect1 = graphics.loadSound(SOUND_EFFECT_FILE);
    Mix_Chunk* soundEffect2 = graphics.loadSound("GameOverSoundEffect.wav");

    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);


    int x; int y;


    Mouse mouse;
    mouse.x = 0;
    mouse.y = SCREEN_HEIGHT / 2 - 205 / 2;

    int delayTime = 50;






    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        Uint32 mousestate = SDL_GetMouseState(&x, &y);
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;

            if(e.type == SDL_MOUSEBUTTONDOWN) {
                if((double)sqrt((x-CenterX)*(x-CenterX)+(y-CenterY)*(y-CenterY)) <= Radius){
                    gamestatus = start;

                }
            }
        }
        if(gamestatus == inMenu) {

            SDL_RenderCopy(graphics.renderer, menuTexture, nullptr,  nullptr);
            graphics.presentScene();
        }
        if(gamestatus == start){
        SDL_Texture* helloText = graphics.renderText(TextWithVariable("Waves: ",waves).c_str(), font, color, graphics.renderer);
        SDL_Texture* numAppleText  = graphics.renderText(TextWithVariable("Apples: ", numApple).c_str(), font, color, graphics.renderer);
        SDL_QueryTexture(helloText,nullptr,nullptr,&textWidth, &textHeigth);

        graphics.renderTexture(helloText, SCREEN_WIDTH/2 - textWidth/2, 0);
        graphics.renderTexture(numAppleText, 0, 0);



        if(currentKeyStates[SDL_SCANCODE_UP]) mouse.turnNorth();
        if(currentKeyStates[SDL_SCANCODE_DOWN]) mouse.turnSouth();
        if(currentKeyStates[SDL_SCANCODE_LEFT]) mouse.turnWest();
        if(currentKeyStates[SDL_SCANCODE_RIGHT]) mouse.turnEast();

        for(int i=0;i<8;i++){
            plane[i].renderObject(graphics.renderer);
        }
        for(int i=0 ; i<4; i++){
            apple[i].renderObject(graphics.renderer);
        }
        plane[0].obj.x -= OBJECT_SPEED;
        if(plane[0].obj.x < 600){
        apple[0].obj.x -= OBJECT_SPEED;
        }

        checkMovePlane(plane, plane[0].obj.x);
        checkMoveApple(apple, apple[0].obj.x);


        if(plane[7].obj.x < 0){
            for(int i =0; i<8; i ++){
                Object newPlane;
                newPlane.texture = graphics.loadTexture(PLANE_SPRITE_FILE);
                newPlane.objectInit();
                plane[i]=newPlane;
            }
            for(int i = 0; i<4 ; i++){
                Apple newapple;
                newapple.texture = graphics.loadTexture(APPLE_SPRITE_FILE);
                newapple.AppleInit();
                apple[i] = newapple;
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


        if(isCollisionPlane(mouse.x, mouse.y, plane)){
            gamestatus = gameover;

        }
        if(isCollisionApple(mouse.x, mouse.y, apple, numApple)){
            graphics.play(soundEffect1);

        }
        }

        if(gamestatus == gameover){
            SDL_RenderCopy(graphics.renderer, gameoverTexture, nullptr, nullptr);
            graphics.play(soundEffect2);
            graphics.presentScene();
            //SDL_Texture* gameoverText = graphics.renderText(TextWithVariable("Apple gained: ",apple).c_str(), font, color, graphics.renderer);

        }





        SDL_Delay(delayTime);


    }

    TTF_CloseFont(font);
    SDL_DestroyTexture( background.texture );
    graphics.quit();
    return 0;
   }










