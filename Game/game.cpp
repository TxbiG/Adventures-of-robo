#include "game.h"

// Game Engine
// To do -
// Player knows if their touching a wall or ceiling X
// Add 1 enemy X
// Add Player buff(s) X
// Add a Cyote jump
// Add a death box

GameWorld* gameWorld = new GameWorld();
Transition* transition;

UI* countdown;
UI* points;

SDL_Renderer* game::renderer = nullptr;

// Constructor creates the game
game::game()
{
	init();
}
// Deconstructor Frees up all the memory
game::~game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void game::init()
{
	// Render SDL Window
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { std::cout << "SDL_CreateWindow: " << SDL_GetError << endl; }									// Initilize SDL
	m_window = SDL_CreateWindow("Toby Gardiner, 26584700, CGP2015M, Adventures of Robo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);	// Create the SDL window
	if (m_window == nullptr)													// Check if SDL window works
	{
		std::cout << "SDL_CreateWindow: " << SDL_GetError << endl;
	}
	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);	// SDL renderer

	if (renderer == nullptr)												// Check if SDL renderer works
	{
		std::cout << "SDL_CreateRenderer: " << SDL_GetError << endl;
	}

	TTF_Init();						// Initilize Font

	running = true;					// Used for running the game
	isFullscreen = false;			// Used to for minimising/maximising the window


	//splashscreen plash(renderer);			// Splash screen
	//SDL_Delay(5000);

	gameWorld->init(renderer);				// Initilize the game world

	seconds = 0;					
	timer = 60;

	countdown = new UI("00:00", 140, 40, TTF_OpenFont("assets/font.ttf", 30));			// Timer to cowndown from 1 minute
	points = new UI("SCORE: 00", 1100, 40, TTF_OpenFont("assets/font.ttf", 30));		// Score to count how many coins player has collected

	transition = new Transition(DELTA_TIME, WIDTH, HEIGHT);

	loop();
}

void game::loop()
{
	while (running)
	{
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
		}
	}
	return;
}

// Used to get user inputs
void game::input()
{
	while (SDL_PollEvent(&m_event))
	{
		// Game world input
		gameWorld->input(game::m_event);

		// Checks if user has stopped pressing a key
		if (m_event.type == SDL_KEYUP && m_event.key.repeat == NULL) 
		{
			switch (m_event.key.keysym.sym)
			{
			case SDLK_TAB:												// Change Screen size
				isFullscreen = !isFullscreen;
				if (isFullscreen) { SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN); }
				else { SDL_SetWindowFullscreen(m_window, 0); }
				break;

			case SDLK_ESCAPE:											// Quit game
				running = false;
				break;
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

	if (gameWorld->setTransition())
	{
		transition->StartTransition();
	}

	if (transition->getTransitionValue() >= 254)
	{
		gameWorld->load_scene(renderer);
	}
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