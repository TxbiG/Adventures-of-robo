#include "game.h"
//#include "TextureManager.h"

// Game Engine
// To do -
// Player knows if their touching a wall or ceiling
// Switch between levels

// 16/02/24
// Add a transition

// 23/02/24
// Add 1 enemy
// Add Player buff(s)

// 2/03/24
// Add splash screen
object* coin = new object();
//entity enemy;

SDL_Renderer* game::renderer = nullptr;

GameWorld* world1;

// Constructor creates the game
game::game()
{
	init();
}
// Deconstructor Frees up all the memory
game::~game()
{
	delete world1;
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void game::init()
{
	// Render SDL Window
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { std::cout << "SDL_CreateWindow: " << SDL_GetError << endl; }
	window = SDL_CreateWindow("Adventures of Robo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow: " << SDL_GetError << endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateRenderer: " << SDL_GetError << endl;
	}
	TTF_Init(); // Add Font

	// Get map
	//map.loadmap("assets/level1.map", renderer);

	world1->loadWorld("assets/level1.map", game::renderer);
	//world.loadWorld("assets/level1.map", game::renderer);

	world1->set_player_position(150, 286);
	world1->set_flag_position(542, 96);
	world1->set_coin_position(542, 190);

	running = true;
	font = TTF_OpenFont("assets/font.ttf", 24);
	//effect.load("");
	loop();
}

void game::loop()
{
	// Frame Per-Second cap
	const int FPS = 24;
	const int FrameDelay = 1000 / FPS;
	// Cap FPS to 24FPS
	while (running)
	{
		Startframe = SDL_GetTicks();
		input();
		update();
		render();
		frameTime = SDL_GetTicks() - Startframe;
		if (FrameDelay > frameTime)
		{
			SDL_Delay(FrameDelay - frameTime);
		}
	}
}

void game::render()
{
	// Background colour
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Rect rect{};
	rect.x = rect.y = 0;
	rect.w = WIDTH;
	rect.h = HEIGHT;
	SDL_RenderFillRect(renderer, &rect);

	// World layer
	world1->render(renderer);

	// UI layer


	SDL_RenderPresent(renderer);
}

// Used to update player animation and game general
void game::update()
{
	world1->update();

	if (isFullscreen)
	{
		SDL_SetWindowFullscreen(window,0);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 1);
	}
}

// Used to get user input to control player
void game::input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		world1->input(e);

		// Change Screen size
		if (e.type == SDLK_TAB) { isFullscreen = !isFullscreen; }

		// Quit game
		if (e.type == SDL_QUIT) { running = false; }

	}
}

bool game::collision(object a, object* b)
{
	if ((a.getDX() < (b->getDX() + b->getDW())) && ((a.getDX() + a.getDW()) > b->getDX()) && (a.getDY() < (b->getDY() + b->getDH())) && ((a.getDY() + a.getDH()) > b->getDY())) {
		return true;
	}
	else {
		return false;
	}
}

bool game::collisionTile(object a, object b)
{
	if ((a.getDX() < (b.getDX() + b.getDW())) && ((a.getDX() + a.getDW()) > b.getDX()) && (a.getDY() < (b.getDY() + b.getDH())) && ((a.getDY() + a.getDH()) > b.getDY())) {
		return true;
	}
	else {
		return false;
	}
}
