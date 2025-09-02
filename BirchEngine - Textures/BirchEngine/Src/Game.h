#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <vector>
#include <iostream>

enum class Level
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	GAME_COMPLETED
};


class Platform;


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	void drawNumber(int number, int x, int y, float scale);

	SDL_Texture* timerTextures[60];
	int currentTimerFrame = 59;
	bool timerActive = true;
	Uint32 timerStartTime = 0;
	Uint32 pauseStartTime = 0;
	Uint32 pauseDuration = 0;


	void loadLevel(Level level);
	Level currentLevel = Level::LEVEL_1;
	Uint32 levelStartTime = 0;
	
	



	static SDL_Renderer* renderer;

	bool isPaused = false;
	SDL_Texture* keybindTexture = nullptr;
	SDL_Texture* keybindTexture1 = nullptr;
	SDL_Texture* pauseTexture = nullptr;
	SDL_Texture* gameOverTexture = nullptr;

	bool isGameOver = false;
	bool isLevelComplete = false;

	int windowWidth = 1920;
	int windowHeight = 1080;


	SDL_Rect playerHitbox;
	SDL_Rect enemyHitbox;
	SDL_Rect enemyHitbox2;
	SDL_Rect platformHitbox1;
	SDL_Rect platformHitbox2;
	SDL_Rect platformHitbox3;
	SDL_Rect platformHitbox4;
	SDL_Rect platformHitbox5;
	SDL_Rect platformHitbox6;
	SDL_Rect platformHitbox7;
	SDL_Rect platformHitbox8;
	SDL_Rect playerFeet;

	static SDL_Window* window;

	bool isFullScreen = false;

	bool restartRequested = false;

	bool shouldRestart() const { return restartRequested; }
	void requestRestart() { restartRequested = true; isRunning = false; }
	
	


	static std::vector<Platform*> platforms;
	void renderCollisionBoxes();


private:
	bool isRunning = false;
	int cnt = 0;

	int countdownSeconds = 60;

	SDL_Texture* levelCompletedTexture = nullptr;
	
	

};