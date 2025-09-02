#pragma once

#include "Game.h"


class LevelElements
{
public:
	LevelElements(const char* texturesheet, int x, int y);
	~LevelElements();
	void Update();
	void Render();
	SDL_Rect getHitbox() const { return hitbox; }


private:

	int xPos, yPos;

	SDL_Texture* levelElementsTexture;
	SDL_Rect srcRect, destRect;
	SDL_Rect hitbox;

};