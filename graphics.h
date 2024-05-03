#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "logic.h"
#include "defs.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

struct Graphics{
    SDL_Renderer *renderer;
    SDL_Window *window;


    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void init() {
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );


        }

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());
        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }
        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());


        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

       void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }


    void quit()
    {
        Mix_Quit();
        IMG_Quit();
        TTF_Quit();


        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    void render(const ScrollingBackground& background) {
        renderTexture(background.texture, background.scrollingOffset, 0);
       renderTexture(background.texture, background.scrollingOffset - background.width, 0);
    }

    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Load font %s", TTF_GetError());
        }
    }

    SDL_Texture* renderText(const char* text,
                        TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer)
{
    SDL_Surface* textSurface =
            TTF_RenderText_Solid( font, text, textColor );
    if( textSurface == nullptr ){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture =
            SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == nullptr ){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface( textSurface);
    return texture;

}
    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
            if (gChunk == nullptr) {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                        SDL_LOG_PRIORITY_ERROR,
               "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }



};


struct Sprite {
    SDL_Texture * texture;
    vector <SDL_Rect> clips;
    int currentFrame = 0;

    void init (SDL_Texture* _texture, int frames, const int _clips[][4]){
        texture = _texture;
        for(int i = 0; i < frames; i++){
            SDL_Rect  clip;
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick (){
        currentFrame = (currentFrame +1 ) % clips.size();
    }
    const SDL_Rect* getCurrentClip() const{
        return &(clips[currentFrame]);
    }


};

void render(int x, int y, const Sprite& sprite, SDL_Renderer* renderer){
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect renderQuad = {x,y,(clip -> w)/2, (clip -> h)/2};
    SDL_RenderCopy(renderer,sprite.texture,clip,&renderQuad);

}

Mix_Music *loadMusic(const char* path){
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if(gMusic == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                        SDL_LOG_PRIORITY_ERROR,
                        "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}

void play(Mix_Music *gMusic){
    if(gMusic == nullptr) return;

    if(Mix_PlayingMusic() == 0){
        Mix_PlayMusic(gMusic, -1);
    }
    else if( Mix_PausedMusic()== 1){
        Mix_ResumeMusic();
    }
}



#endif  _GRAPHICS__H
