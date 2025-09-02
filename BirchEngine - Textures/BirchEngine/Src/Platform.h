#pragma once
#include "SDL.h"

class Platform {
public:
    Platform(const char* texturePath, int x, int y, int w, int h);
    ~Platform();

    void Update();
    void Render();

    SDL_Rect getHitbox() const;

    void setPosition(int x, int y);

private:
    SDL_Texture* objTexture = nullptr;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int xPos, yPos;
    int width, height;
};
