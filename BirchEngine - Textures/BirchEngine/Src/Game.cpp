#include "Game.h"
#include "Map.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "StaticObject.h"
#include "levelElements.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_main.h"
#include "Utils.h"
#include "Platform.h"
#include <iostream>
#include <string>

using namespace std;

std::vector<Platform*> Game::platforms;


extern MainCharacter* player;

Platform* platform1;
Platform* platform2;
Platform* platform3;
Platform* platform4;
Platform* platform5;
Platform* platform6;
Platform* platform7;
Platform* platform8;


LevelElements* lvl1plan1;
LevelElements* lvl1plan2;
LevelElements* lvl1plan3;
LevelElements* lvl1plan4;
LevelElements* lvl1plan5;

LevelElements* lvl2plan1;
LevelElements* lvl2plan2;
LevelElements* lvl2plan3;
LevelElements* lvl2plan4;
LevelElements* lvl2plan5;
LevelElements* lvl2plan6;

LevelElements* lvl3plan1;
LevelElements* lvl3plan2;
LevelElements* lvl3plan3;
LevelElements* lvl3plan4;
LevelElements* lvl3plan5;

LevelElements* lvl4plan1;
LevelElements* lvl4plan2;
LevelElements* lvl4plan3;
LevelElements* lvl4plan4;
LevelElements* lvl4plan5;



MainCharacter* player;
GameObject* enemy;
GameObject* enemy2;

Particles* firework1;
Particles* firework2;
Particles* firework3;
Particles* firework4;
Particles* firework5;
Particles* firework6;
Particles* firework7;
Particles* firework8;
Particles* firework9;
Particles* firework10;
Particles* firework11;
Particles* firework12;
Particles* firework13;
Particles* firework14;
Particles* firework15;
Particles* firework16;
Particles* firework17;
Particles* firework18;
Particles* firework19;
Particles* firework20;
Particles* firework21;
Particles* firework22;


Map* map;

StaticObject* chicken;
StaticObject* cow;
StaticObject* tree;
StaticObject* tree2;
StaticObject* tree3;
StaticObject* tree4;
StaticObject* tree5;
StaticObject* palmTree;
StaticObject* palmTree2;

CloudObjects* clearCloudLayer1;
CloudObjects* clearCloudLayer2;
CloudObjects* clearCloudLayer3;
CloudObjects* grayCloudLayer1;
CloudObjects* grayCloudLayer2;
CloudObjects* grayCloudLayer3;
CloudObjects* darkcloudLayer1;
CloudObjects* darkcloudLayer2;
CloudObjects* darkcloudLayer3;

SDL_Renderer* Game::renderer = nullptr;
SDL_Window* Game::window = nullptr;

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    return (a.x + a.w > b.x) &&
        (a.x < b.x + b.w) &&
        (a.y + a.h > b.y) &&
        (a.y < b.y + b.h);
}

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        isRunning = false;
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        isRunning = false;
        return;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!window)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }
    Game::window = window;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }



    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    isRunning = true;

    player = new MainCharacter("assets/WarriorRunRightSpriteSheet.png", 300, 770);

    enemy = new GameObject("assets/EnemyRun1.png", 1200, 770, 1, 2.0f);
    enemy2 = new GameObject("assets/EnemyRun1.png", 950, 770, -1, 3.5f);

    keybindTexture = TextureManager::LoadTexture("assets/KeyBindWASD1.png");
    if (!keybindTexture) {
        SDL_Log("Failed to load KeyBindWASD.png");
    }

    keybindTexture1 = TextureManager::LoadTexture("assets/KeyBindEscRCQ.png");
    if (!keybindTexture1) {
        SDL_Log("Failed to load KeyBindEscCQ.png");
    }

    pauseTexture = TextureManager::LoadTexture("assets/GamePaused1.png");
    if (!pauseTexture) {
        SDL_Log("Failed to load GamePaused1.png");
    }

    gameOverTexture = TextureManager::LoadTexture("assets/GameOver3.png");
    if (!gameOverTexture) {
        SDL_Log("Failed to load GameOver1.png");
    }

    isGameOver = false;


    levelCompletedTexture = TextureManager::LoadTexture("assets/LvlCompleted.png");

    if (!levelCompletedTexture) {
        SDL_Log("Failed to load level complete textures.");
    }
    levelStartTime = SDL_GetTicks();


    for (int i = 0; i < 60; i++) {
        std::string path = "assets/timer/" + std::to_string(i + 1) + ".png";
        timerTextures[i] = TextureManager::LoadTexture(path.c_str());
        if (!timerTextures[i]) {
            SDL_Log("Failed to load timer image: %s", path.c_str());
        }
    }
    timerStartTime = SDL_GetTicks();
    

    //map = new Map();
	chicken = new StaticObject("assets/chicken.png", 600, 800);
	cow = new StaticObject("assets/cow.png", 830, 200);

    clearCloudLayer1 = new CloudObjects("assets/clearCloudLayer1.png", 0, 0);
    clearCloudLayer2 = new CloudObjects("assets/clearCloudLayer1.png", 1700, 0);
    clearCloudLayer3 = new CloudObjects("assets/clearCloudLayer1.png", 3400, 0);
    grayCloudLayer1 = new CloudObjects("assets/grayCloudLayer1.png", 5100, 0);
    grayCloudLayer2 = new CloudObjects("assets/grayCloudLayer1.png", 6800, 0);
	grayCloudLayer3 = new CloudObjects("assets/grayCloudLayer1.png", 8500, 0);
	darkcloudLayer1 = new CloudObjects("assets/darkCloudLayer1.png", 10200, 0);
    darkcloudLayer2 = new CloudObjects("assets/darkCloudLayer1.png", 11900, 0);
    darkcloudLayer3 = new CloudObjects("assets/darkCloudLayer1.png", 13600, 0);

    
	lvl1plan5 = new LevelElements("assets/levels/lvl1/plan5.png", 0, 0);
    lvl1plan4 = new LevelElements("assets/levels/lvl1/plan4.png", 0, 0);
    lvl1plan3 = new LevelElements("assets/levels/lvl1/plan3.png", 0, 0);
    lvl1plan2 = new LevelElements("assets/levels/lvl1/plan2.png", 0, 0);
    lvl1plan1 = new LevelElements("assets/levels/lvl1/plan1.png", 0, -50);

    lvl2plan6 = new LevelElements("assets/levels/lvl2/plan6.png", 0, 0);
    lvl2plan5 = new LevelElements("assets/levels/lvl2/plan5.png", 0, 0);
    lvl2plan4 = new LevelElements("assets/levels/lvl2/plan4.png", 0, 0);
    lvl2plan3 = new LevelElements("assets/levels/lvl2/plan3.png", 0, 0);
    lvl2plan2 = new LevelElements("assets/levels/lvl2/plan2.png", 0, 0);
    lvl2plan1 = new LevelElements("assets/levels/lvl2/plan1.png", 0, -50);

    lvl3plan5 = new LevelElements("assets/levels/lvl3/plan5.png", 0, 0);
    lvl3plan4 = new LevelElements("assets/levels/lvl3/plan4.png", 0, 0);
    lvl3plan3 = new LevelElements("assets/levels/lvl3/plan3.png", 0, 0);
    lvl3plan2 = new LevelElements("assets/levels/lvl3/plan2.png", 0, 0);
	lvl3plan1 = new LevelElements("assets/levels/lvl3/plan1.png", 0, 0);

	lvl4plan5 = new LevelElements("assets/levels/lvl4/plan5.png", 0, 0);
    lvl4plan4 = new LevelElements("assets/levels/lvl4/plan4.png", 0, 0);
    lvl4plan3 = new LevelElements("assets/levels/lvl4/plan3.png", 0, 0);
    lvl4plan2 = new LevelElements("assets/levels/lvl4/plan2.png", 0, 0);
	lvl4plan1 = new LevelElements("assets/levels/lvl4/plan1.png", 0, 0);
    
	


	platform1 = new Platform("assets/platforms/platform128x16.png", 850, 600, 128, 16);
	platform2 = new Platform("assets/platforms/platformLong256x16.png", 1150, 730, 256, 16);
	platform3 = new Platform("assets/platforms/platformLong512x16.png", 100, 650, 512, 16);
    platform4 = new Platform("assets/platforms/platformLong512x16.png", 1500, 600, 512, 16);
	platform5 = new Platform("assets/platforms/platform128x16.png", 1600, 800, 128, 16);
	platform6 = new Platform("assets/platforms/platformLong256x16.png", 1120, 340, 256, 16);
	platform7 = new Platform("assets/platforms/platform128x16.png", 800, 410, 128, 16);
	platform8 = new Platform("assets/platforms/platformLong512x16.png", 0, 440, 512, 16);


    firework1 = new Particles("assets/particles/Firework1.png", -100, -100);
    firework2 = new Particles("assets/particles/Firework1.png", 1672, -30);
    firework3 = new Particles("assets/particles/Firework1.png", -78, 472);
    firework4 = new Particles("assets/particles/Firework1.png", 1572, 622);
    firework5 = new Particles("assets/particles/Firework1.png", 122, 22);
    firework6 = new Particles("assets/particles/Firework1.png", 1522, -78);
    firework7 = new Particles("assets/particles/Firework1.png", -28, 672);
    firework8 = new Particles("assets/particles/Firework1.png", 1632, 712);
    firework9 = new Particles("assets/particles/Firework1.png", 72, -108);
    firework10 = new Particles("assets/particles/Firework1.png", 1622, 522);
    firework11 = new Particles("assets/particles/Firework1.png", -58, 572);
    firework12 = new Particles("assets/particles/Firework1.png", 872, -28);
    firework13 = new Particles("assets/particles/Firework1.png", -8, 692);
    firework14 = new Particles("assets/particles/Firework1.png", 1772, 52);
    firework15 = new Particles("assets/particles/Firework1.png", -98, 272);
    firework16 = new Particles("assets/particles/Firework1.png", 1452, 672);
    firework17 = new Particles("assets/particles/Firework1.png", 372, -78);
    firework18 = new Particles("assets/particles/Firework1.png", 1372, -58);
    firework19 = new Particles("assets/particles/Firework1.png", 22, 552);
    firework20 = new Particles("assets/particles/Firework1.png", 1592, 422);
    firework21 = new Particles("assets/particles/Firework1.png", 772, -48);
    firework22 = new Particles("assets/particles/Firework1.png", 152, 652);





    isRunning = true;
    timerStartTime = SDL_GetTicks();
    pauseDuration = 0;
    timerActive = true;


}


void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;

    case SDL_KEYDOWN:
        // ALT + ENTER za fullscreen uvek radi
        if (event.key.keysym.sym == SDLK_RETURN && (event.key.keysym.mod & KMOD_ALT))
        {
            isFullScreen = !isFullScreen;
            Uint32 fullscreenFlag = isFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
            SDL_SetWindowFullscreen(window, fullscreenFlag);
            SDL_ShowCursor(!isFullScreen);
            break;
        }

        // ESC toggluje pauzu, ali ne ako je Game Over ili Level Complete
        if (event.key.keysym.sym == SDLK_ESCAPE && !isGameOver && !isLevelComplete)
        {
            if (!isPaused) {
                pauseStartTime = SDL_GetTicks();
                isPaused = true;
            }
            else {
                Uint32 now = SDL_GetTicks();
                Uint32 pauseTime = now - pauseStartTime;
                pauseDuration += pauseTime;
                isPaused = false;
            }

            break;
        }

        // Kada je LEVEL COMPLETE  — dozvoli  R, Q i ENTER za prelazak na sledeći nivo
        if (isLevelComplete) {
            if (event.key.keysym.sym == SDLK_r)
                requestRestart();
            else if (event.key.keysym.sym == SDLK_q)
                isRunning = false;
            else if (event.key.keysym.sym == SDLK_RETURN)
            {
                // Prelazak na sledeći nivo
                switch (currentLevel) {
                case Level::LEVEL_1:
                    currentLevel = Level::LEVEL_2;
                    break;
                case Level::LEVEL_2:
                    currentLevel = Level::LEVEL_3;
                    break;
                case Level::LEVEL_3:
                    currentLevel = Level::LEVEL_4;
                    break;
                case Level::LEVEL_4:
                    currentLevel = Level::GAME_COMPLETED;
                    break;
                default:
                    break;
                }

                loadLevel(currentLevel);
            }
            break;
        }

        // Kada je GAME OVER — dozvoli  R i Q
        if (isGameOver) {
            if (event.key.keysym.sym == SDLK_r)
                requestRestart();
            else if (event.key.keysym.sym == SDLK_q)
                isRunning = false;
            break;
        }

        // PAUSE MENU
        if (isPaused)
        {
            if (event.key.keysym.sym == SDLK_c)
                isPaused = false;
            else if (event.key.keysym.sym == SDLK_r)
                requestRestart();
            else if (event.key.keysym.sym == SDLK_q)
                isRunning = false;
            break;
        }

        player->handleEvent(event);
        break;

    default:
        if (!isPaused && !isLevelComplete && !isGameOver)
            player->handleEvent(event);
        break;
    }
}



void Game::update()
{



    if (isLevelComplete) {
        timerActive = false;
        firework1->Update();
        firework2->Update();
        firework3->Update();
        firework4->Update();
        firework5->Update();
        firework6->Update();
        firework7->Update();
        firework8->Update();
        firework9->Update();
        firework10->Update();
        firework11->Update();
        firework12->Update();
        firework13->Update();
        firework14->Update();
        firework15->Update();
        firework16->Update();
        firework17->Update();
        firework18->Update();
        firework19->Update();
        firework20->Update();
        firework21->Update();
        firework22->Update();
        return;
    }

    if (isLevelComplete) {
        timerActive = false;

        
        player->StopMovement();
        enemy->StopMovement();
        


        return;
    }

    if (timerActive && !isPaused && !isGameOver) {
        Uint32 elapsedTime = SDL_GetTicks() - timerStartTime - pauseDuration;
        int secondsPassed = elapsedTime / 1000;

        if (secondsPassed < 60) {
            currentTimerFrame = 59 - secondsPassed;
        }
        else {
            timerActive = false;
            isLevelComplete = true;
        }
    }

    if (isGameOver) {
        timerActive = false;
    }

    if (timerActive) {
        Uint32 elapsed = (SDL_GetTicks() - timerStartTime) / 1000;
        if (elapsed < 60)
            currentTimerFrame = 59 - elapsed;
        else {
            timerActive = false;
            isLevelComplete = true;
        }
    }


    if (isPaused)
    {
		

    return;
    }
        
        


    Uint32 deltaTime = 5;
    player->move(deltaTime);

    if (checkCollision(player->hitbox, lvl1plan1->getHitbox()))
    {
        if (player->yPos + player->destRect.h <= lvl1plan1->getHitbox().y + 10)
        {
            player->yPos = lvl1plan1->getHitbox().y - player->destRect.h;
            player->isJumping = false;
            player->jumpVelocity = 0;
            player->groundLevel = player->yPos; 
        }
        else
        {
        }
    }
    else
    {
        player->groundLevel = 770; 
    }

	player->Update();
	enemy->Update();
	enemy2->Update();

	platformHitbox1 = ShrinkRect(platform1->getHitbox(), 0);
	platformHitbox2 = ShrinkRect(platform2->getHitbox(), 0);
    platformHitbox3 = ShrinkRect(platform3->getHitbox(), 0);
	platformHitbox4 = ShrinkRect(platform4->getHitbox(), 0);
	platformHitbox5 = ShrinkRect(platform5->getHitbox(), 0);
	platformHitbox6 = ShrinkRect(platform6->getHitbox(), 0);
	platformHitbox7 = ShrinkRect(platform7->getHitbox(), 0);
	platformHitbox8 = ShrinkRect(platform8->getHitbox(), 0);

    SDL_Rect playerFeet = { player->getDestRect().x, player->getDestRect().y + player->getDestRect().h - 10, player->getDestRect().w, 10 };


    playerHitbox = ShrinkRect(player->getDestRect(), 30);
    enemyHitbox = ShrinkRect(enemy->getDestRect(), 40);
	enemyHitbox2 = ShrinkRect(enemy2->getDestRect(), 40);
	//levo,desno,gore,dole
    playerHitbox = AdjustHitbox(player->getDestRect(), 110, 110, 60, -30);
	//levo,desno,gore,dole
    enemyHitbox = AdjustHitbox(enemy->getDestRect(), 80, 80, 50, -30);
	enemyHitbox2 = AdjustHitbox(enemy2->getDestRect(), 80, 80, 50, -30);

    if (CheckCollision(playerHitbox, enemyHitbox))
    {
        isGameOver = true;
        isPaused = true;
    }

    if (CheckCollision(playerHitbox, enemyHitbox2))
    {
        isGameOver = true;
        isPaused = true;
    }


	//chicken->Update();
	//cow->Update();

    clearCloudLayer1->Update();
    clearCloudLayer2->Update();
    clearCloudLayer3->Update();
	grayCloudLayer1->Update();
    grayCloudLayer2->Update();
    grayCloudLayer3->Update();
    darkcloudLayer1->Update();
    darkcloudLayer2->Update();
	darkcloudLayer3->Update();

	lvl1plan5->Update();
	lvl1plan4->Update();
	lvl1plan3->Update();
	lvl1plan2->Update();
	lvl1plan1->Update();

	lvl2plan6->Update();
	lvl2plan5->Update();
	lvl2plan4->Update();
	lvl2plan3->Update();
	lvl2plan2->Update();
	lvl2plan1->Update();

	lvl3plan5->Update();
	lvl3plan4->Update();
	lvl3plan3->Update();
	lvl3plan2->Update();
	lvl3plan1->Update();

	lvl4plan5->Update();
	lvl4plan4->Update();
	lvl4plan3->Update();
	lvl4plan2->Update();
    lvl4plan1->Update();



	platform1->Update();
	platform2->Update();
    platform3->Update();
	platform4->Update();
    platform5->Update();
    platform6->Update();
	platform7->Update();
	platform8->Update();
    
	
}

void Game::render()
{
    SDL_RenderClear(renderer);

    // Render background layers based on current level
    if (currentLevel == Level::LEVEL_1)
    {
        lvl1plan5->Render();
        lvl1plan4->Render();
        lvl1plan3->Render();

        clearCloudLayer1->Render();
        clearCloudLayer2->Render();
        clearCloudLayer3->Render();

        grayCloudLayer1->Render();
        grayCloudLayer2->Render();
        grayCloudLayer3->Render();

        darkcloudLayer1->Render();
        darkcloudLayer2->Render();
        darkcloudLayer3->Render();

        lvl1plan2->Render();
        platform1->Render();
        platform2->Render();
        platform3->Render();
        platform4->Render();
        platform5->Render();
		platform6->Render();
		platform7->Render();
		platform8->Render();
        player->Render();
        enemy->Render();
        enemy2->Render();
		lvl1plan1->Render();
    }
    else if (currentLevel == Level::LEVEL_2)
    {
		lvl2plan6->Render();
        lvl2plan5->Render();

        clearCloudLayer1->Render();
        clearCloudLayer2->Render();
        clearCloudLayer3->Render();

        grayCloudLayer1->Render();
        grayCloudLayer2->Render();
        grayCloudLayer3->Render();

        darkcloudLayer1->Render();
        darkcloudLayer2->Render();
        darkcloudLayer3->Render();

        lvl2plan4->Render();
        lvl2plan3->Render();
        lvl2plan2->Render();

        platform1->Render();
        platform2->Render();
        platform3->Render();
        platform4->Render();
        platform5->Render();
		platform6->Render();
        platform7->Render();
		platform8->Render();
        
		player->Render();
        enemy->Render();
		enemy2->Render();
        lvl2plan1->Render();
    }
    else if (currentLevel == Level::LEVEL_3)
    {
		lvl3plan5->Render();
        
        
        clearCloudLayer1->Render();
        clearCloudLayer2->Render();
        clearCloudLayer3->Render();

        grayCloudLayer1->Render();
        grayCloudLayer2->Render();
        grayCloudLayer3->Render();

        darkcloudLayer1->Render();
        darkcloudLayer2->Render();
        darkcloudLayer3->Render();

        lvl3plan4->Render();
        lvl3plan3->Render();
        lvl3plan2->Render();

        platform1->Render();
        platform2->Render();
        platform3->Render();
        platform4->Render();
        platform5->Render();
		platform6->Render();
		platform7->Render();
		platform8->Render();

        player->Render();
        enemy->Render();
        enemy2->Render();
        lvl3plan1->Render();
    }
    else if (currentLevel == Level::LEVEL_4)
    {
        lvl4plan5->Render();
        lvl4plan4->Render();

        clearCloudLayer1->Render();
        clearCloudLayer2->Render();
        clearCloudLayer3->Render();

        grayCloudLayer1->Render();
        grayCloudLayer2->Render();
        grayCloudLayer3->Render();

        darkcloudLayer1->Render();
        darkcloudLayer2->Render();
        darkcloudLayer3->Render();

        lvl4plan3->Render();
        lvl4plan2->Render();

        platform1->Render();
        platform2->Render();
        platform3->Render();
        platform4->Render();
        platform5->Render();
		platform6->Render();
		platform7->Render();
		platform8->Render();
        
        player->Render();
        enemy->Render();
        enemy2->Render();
        lvl4plan1->Render();
    }
    

    

    /*if (currentLevel == Level::LEVEL_1)
        lvl1plan1->Render();

    if (currentLevel == Level::LEVEL_2){
        lvl2plan1->Render();
    }*/
		

    // PAUZA i GAME OVER ekran
    if (isPaused)
    {
        SDL_Rect overlay = { 0, 0, windowWidth, windowHeight };
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
        SDL_RenderFillRect(renderer, &overlay);

        SDL_Texture* screenTexture = isGameOver ? gameOverTexture : pauseTexture;

        if (screenTexture) {
            SDL_Rect imgRect;

            if (isGameOver) {
                imgRect.w = 1300;
                imgRect.h = 900;
                imgRect.x = (windowWidth - imgRect.w) / 2;
                imgRect.y = -100;
            }
            else {
                imgRect.w = 900;
                imgRect.h = 600;
                imgRect.x = (windowWidth - imgRect.w) / 2;
                imgRect.y = 50;
            }

            SDL_RenderCopy(renderer, screenTexture, nullptr, &imgRect);
        }

        if (!isGameOver)
        {
            if (keybindTexture)
            {
                SDL_Rect keybindRect = { 30, windowHeight - 384 - 250, 512, 384 };
                SDL_RenderCopy(renderer, keybindTexture, nullptr, &keybindRect);
            }

            if (keybindTexture1)
            {
                SDL_Rect keybindRect1 = { 30, windowHeight - 384 - 680, 512, 384 };
                SDL_RenderCopy(renderer, keybindTexture1, nullptr, &keybindRect1);
            }
        }
    }

    // Timer prikaz ako je aktivan i u opsegu
    if (timerActive && currentTimerFrame >= 0 && currentTimerFrame < 60)
    {
        SDL_Texture* tex = timerTextures[currentTimerFrame];

        int winW, winH;
        SDL_GetWindowSize(Game::window, &winW, &winH);

        int bgWidth = 140;
        int bgHeight = 80;
        SDL_Rect bgRect = { (winW - bgWidth) / 2, 0, bgWidth, bgHeight };

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 120);
        SDL_RenderFillRect(renderer, &bgRect);

        if (tex)
        {
            int texW = 64;
            int texH = 64;
            SDL_Rect dest = { bgRect.x + (bgRect.w - texW) / 2, bgRect.y + (bgRect.h - texH) / 2, texW, texH };
            TextureManager::Draw(tex, { 0, 0, texW, texH }, dest);
        }
    }

    // Level completed ekran
    if (isLevelComplete && levelCompletedTexture)
    {
        SDL_Rect overlay = { 0, 0, windowWidth, windowHeight };
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
        SDL_RenderFillRect(renderer, &overlay);

        SDL_Rect completedRect = { 0, 0, windowWidth, windowHeight };

        // Renderuj vatromete
        firework1->Render();
        firework2->Render();
        firework3->Render();
        firework4->Render();
        firework5->Render();
        firework6->Render();
        firework7->Render();
        firework8->Render();
        firework9->Render();
        firework10->Render();
        firework11->Render();
        firework12->Render();
        firework13->Render();
        firework14->Render();
        firework15->Render();
        firework16->Render();
        firework17->Render();
        firework18->Render();
        firework19->Render();
        firework20->Render();
        firework21->Render();
        firework22->Render();

        SDL_RenderCopy(renderer, levelCompletedTexture, nullptr, &completedRect);
    }

    // Debug prikaz hitboxova (ako ti treba)
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &platformHitbox1);
    SDL_RenderDrawRect(Game::renderer, &platformHitbox2);
    SDL_RenderDrawRect(Game::renderer, &platformHitbox3);
    SDL_RenderDrawRect(Game::renderer, &platformHitbox4);
    SDL_RenderDrawRect(Game::renderer, &platformHitbox5);
	SDL_RenderDrawRect(Game::renderer, &platformHitbox6);
	SDL_RenderDrawRect(Game::renderer, &platformHitbox7);
	SDL_RenderDrawRect(Game::renderer, &platformHitbox8);

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &playerFeet);

    SDL_RenderPresent(renderer);
}




void Game::clean()
{
    if (keybindTexture) {
        SDL_DestroyTexture(keybindTexture);
        keybindTexture = nullptr;
    }

    SDL_DestroyTexture(pauseTexture);
    pauseTexture = nullptr;

    SDL_DestroyTexture(gameOverTexture);
    gameOverTexture = nullptr;

    
    if (levelCompletedTexture) {
        SDL_DestroyTexture(levelCompletedTexture);
        levelCompletedTexture = nullptr;

    }

    for (int i = 0; i < 60; i++) {
        if (timerTextures[i]) {
            SDL_DestroyTexture(timerTextures[i]);
            timerTextures[i] = nullptr;
        }
    }

    for (Platform* p : Game::platforms) {
        delete p;
    }
    Game::platforms.clear();


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void GameObject::setPosition(int x, int y)
{
    xPos = x;
    yPos = y;

    destRect.x = xPos;
    destRect.y = yPos;
}




void Game::loadLevel(Level level)
{
    isLevelComplete = false;
    isGameOver = false;
    timerActive = true;
    currentTimerFrame = 59;
    timerStartTime = SDL_GetTicks();
    pauseDuration = 0;


    switch (level)
    {
    case Level::LEVEL_1:
        player->setPosition(300, 750);
        enemy->setPosition(1200, 750);
        enemy2->setPosition(750, 750);
        platform1->setPosition(850, 600);
        platform2->setPosition(1150, 730);
        platform3->setPosition(100, 650);
        platform4->setPosition(1500, 600);
        platform5->setPosition(1600, 800);
        platform6->setPosition(1120, 340);
        platform7->setPosition(800, 410);
        platform8->setPosition(0, 440);
        break;
       

    case Level::LEVEL_2:
        player->setPosition(300, 750);
        enemy->setPosition(1200, 750);
        enemy2->setPosition(750, 750);
        platform1->setPosition(850, 600);
        platform2->setPosition(1150, 730);
        platform3->setPosition(100, 650);
        platform4->setPosition(1500, 600);
        platform5->setPosition(1600, 800);
        platform6->setPosition(1120, 340);
        platform7->setPosition(800, 410);
        platform8->setPosition(0, 440);
        break;

    case Level::LEVEL_3:
        player->setPosition(300, 750);
        enemy->setPosition(1200, 750);
        enemy2->setPosition(750, 750);
        platform1->setPosition(850, 600);
        platform2->setPosition(1150, 730);
        platform3->setPosition(100, 650);
        platform4->setPosition(1500, 600);
        platform5->setPosition(1600, 800);
        platform6->setPosition(1120, 340);
        platform7->setPosition(800, 410);
        platform8->setPosition(0, 440);
        break;

    case Level::LEVEL_4:
        player->setPosition(300, 750);
        enemy->setPosition(1200, 750);
        enemy2->setPosition(750, 750);
        platform1->setPosition(850, 600);
        platform2->setPosition(1150, 730);
        platform3->setPosition(100, 650);
        platform4->setPosition(1500, 600);
        platform5->setPosition(1600, 800);
        platform6->setPosition(1120, 340);
        platform7->setPosition(800, 410);
        platform8->setPosition(0, 440);
        break;

    case Level::GAME_COMPLETED:
        isRunning = false;
        break;
    }
}

