#include "game.h"
#include "GameOver.h"

// Game Engine
// To do -
// 30 / 4 / 24
// Add enemy mechanics
// Add Player controls - 
	// Cyote jump
	// Player Buff - 50%

// CLEAN UP - 1/4/24
// Audio
// Fix animations (min & max) and state machines
// Comment every mechanic!

// Enough time 
// particles
SDL_Event m_event;					// SDL input
Transition* transition;				// Transition screen

GameWorld* gameWorld = new GameWorld();		// Game world

UI* countdown;				// UI 60s countdown
UI* points;					// UI score

SDL_Renderer* game::renderer = nullptr;

// Constructor creates the game
game::game()
{
	// Initilize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { std::cout << "SDL_CreateWindow: " << SDL_GetError << endl; }		
	
	// Create Window
	m_window = SDL_CreateWindow("Toby Gardiner, 26584700, CGP2015M, Adventures of Robo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);	// Create the SDL window
	
	// Check if SDL window works
	if (m_window == nullptr) { std::cout << "SDL_CreateWindow: " << SDL_GetError << endl; return; }

	// Create renderer
	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	// Check if SDL renderer works
	if (renderer == nullptr) { std::cout << "SDL_CreateRenderer: " << SDL_GetError << endl; return; }

	// Initilize Font
	if (TTF_Init()) { std::cout << "Failed to Initilize SDL2 TTF" << std::endl; return; }

	// Initilize Mixer
	if (Mix_Init(MIX_INIT_WAVPACK)) { std::cout << "Failed to Initilize SDL2 Mixer" << std::endl; return; }

	// Get Mixer Open Audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { std::cout << "Failed to open Mix Audio: " << Mix_GetError() << std::endl; return; }

	running = true;											// Used for running the game
	isFullscreen = false;									// Used to for minimising/maximising the window

	//audio* sfx = new audio("assets/sounds/Splash.wav");		// Get Splash SFX
	//sfx->playSound(0);										// Play sound
	//splashscreen plash(renderer);								// Display Splash screen
	//SDL_Delay(5000);											// 5s of displaying Slashscreen

	gameWorld->init(renderer);								// Initilize the game world

	seconds = 0;
	timer = 60;

	TTF_Font* m_font = TTF_OpenFont("assets/font.ttf", 30);
	countdown = new UI("00:00", 140, 40, m_font);				// Timer to cowndown from 1 minute
	points = new UI("SCORE: 00", 1100, 40, m_font);				// Score to count how many coins player has collected

	transition = new Transition(DELTA_TIME, WIDTH, HEIGHT);

	loop();
}
// Deconstructor Frees up all the memory
game::~game()
{
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void game::loop()
{
	while (running)
	{
		SDL_RenderClear(renderer);
		m_Timer.resetTicks();

		input();
		update();
		render();

		if (m_Timer.getTicks() < DELTA_TIME)
		{
			SDL_Delay(DELTA_TIME - m_Timer.getTicks());

			seconds--;
			if (seconds <= 0)
			{
				timer--;
				seconds = 60;
			}
			if (timer <= 0)
			{
				running = false;
			}
			if (gameWorld->get_score() == 30 && bonusTime)
			{
				timer += 15;
				bonusTime = false;
			}
		}
	}

	if (timer <= 0) { GameOver yl("You lose", renderer); }
	if (timer > 0) { GameOver yw("You win", renderer); }
	SDL_Delay(4000);

	return;
}

// Used to get user inputs
void game::input()
{
	while (SDL_PollEvent(&m_event))
	{
		// Game world input
		gameWorld->input(m_event);

		// Checks if user has stopped pressing a key
		if (m_event.type == SDL_KEYUP && m_event.key.repeat == NULL) 
		{
			switch (m_event.key.keysym.sym)
			{
			case SDLK_TAB:							// Change Screen size
				isFullscreen = !isFullscreen;
				if (isFullscreen) { SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN); }
				else { SDL_SetWindowFullscreen(m_window, 0); }
				break;

			case SDLK_ESCAPE:						// Quit game
				running = false;
				break;

			case SDLK_q:							// Debug Toggle
				gameWorld->debug.set_Debugger(!gameWorld->debug.get_Debugger());
				if (gameWorld->debug.get_Debugger()) { gameWorld->debug.get_Debug("Debug On."); }
				else { cout << "Debug Off." << endl; }
			}
		}
	}
}

// Used to update player animation and game general
void game::update()
{
	// Update game world
	gameWorld->update();

	// Update User interface
	std::string timer_str = "00:" + std::to_string(timer);
	const char* time_char = timer_str.c_str();
	countdown->update(time_char);

	std::string score_str = "SCORE:" + std::to_string(gameWorld->get_score());
	const char* score_char = score_str.c_str();
	points->update(score_char);

	// Checks if can Start transition
	if (gameWorld->setTransition()) { transition->StartTransition(); }

	// Checks if transition value is enough to smoothly change level (visually)
	if (transition->getTransitionValue() >= 254) 
	{
		// Check if the transition request is next level or reset level
		if (gameWorld->canSwitch) { gameWorld->load_scene(renderer); }
		else { gameWorld->resetWorld(); }
	}
	if (gameWorld->destroyWorld()) { running = false; }
}

void game::render()
{
	// Background colour
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect rect{};
	rect.x = rect.y = 0;
	rect.w = WIDTH;
	rect.h = HEIGHT;
	SDL_RenderFillRect(renderer, &rect);

	// Game World
	gameWorld->render(renderer);

	// User interface
	countdown->render(renderer);
	points->render(renderer);

	transition->render(renderer);

	SDL_RenderPresent(renderer);
}