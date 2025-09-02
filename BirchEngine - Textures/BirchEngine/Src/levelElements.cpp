#include "levelElements.h"
#include "TextureManager.h"

LevelElements::LevelElements(const char* texturesheet, int x, int y)
{
	levelElementsTexture = TextureManager::LoadTexture(texturesheet);
	if (!levelElementsTexture) {
		SDL_Log("Failed to load texture for LevelElements.cpp: %s", texturesheet);
	}

	xPos = x;
	yPos = y;
}


void LevelElements::Update()
{

	srcRect.h = 1080;
	srcRect.w = 1920;
	srcRect.x = 0;
	srcRect.y = 0;

	hitbox.x = xPos;
	hitbox.y = yPos;
	hitbox.w = destRect.w;
	hitbox.h = destRect.h;


	destRect.x = xPos;
	destRect.y = yPos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;

	hitbox.x = destRect.x;
	hitbox.y = destRect.y;
	hitbox.w = destRect.w;
	hitbox.h = destRect.h;
}

void LevelElements::Render()
{
	SDL_RenderCopy(Game::renderer, levelElementsTexture, &srcRect, &destRect);
}