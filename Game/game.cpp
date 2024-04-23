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
tilemap* map = new tilemap();

object* player = new object();
object* flag = new object();

SDL_Renderer* game::renderer = nullptr;

// Constructor creates the game
game::game()
{
	init();
}
// Deconstructor Frees up all the memory
game::~game()
{
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

	map->loadmap("assets/level1.map", renderer);

	// Get Coin(s)
	coin->setImage("assets/coin.png", renderer);
	coin->setID(2);
	coin->setSource(0, 0, 32, 32);
	coin->setDest(Vector2D(542, 190), 32, 32);
	spin = coin->createAnimation(1, 32, 32, 4, 5);
	coin->setCurrectAnimation(spin);
	//flag
	flag->setImage("assets/Flag.png", renderer);
	flag->setID(3);
	flag->setSource(0, 0, 32, 32);
	flag->setDest(Vector2D(542, 96), 32, 32);
	// get Player
	player->setImage("assets/Player.png", renderer);
	player->setID(1);
	//player.setSource(0, 0, 32, 32);
	player->setDest(Vector2D(150, 286), 32, 32);
	idle = player->createAnimation(1, 32, 32, 4, 5);
	run = player->createAnimation(2, 32, 32, 4, 5);
	jump = player->createAnimation(3, 32, 32, 0, 0);
	fall = player->createAnimation(3, 32, 32, 1, 0);

	l = false;
	r = false;
	u = false;
	isFalling = false;
	Levelnum = 0;

	running = true;
	isFullscreen = false;

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
	while (running == true)
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

	// TileMap layer
	map->drawMap(renderer);

	// Enemy layer

	// Object layer
	coin->render(renderer);
	flag->render(renderer);

	// Player layer
	player->render(renderer);

	// UI layer


	SDL_RenderPresent(renderer);
}

// Used to update player animation and game general
void game::update()
{
	isFalling = true;
	for (int i = 0; i < map->map.size(); i++)
	{
		if (collisionTile(player, map->map[i]))
		{
			// WARNING: Only get floor not ceiling or wall
			if (map->map[i].getSolid()) { isFalling = false; }
			else { isFalling = true; }
		}
	}

	if (collision(player, coin))
	{
		// Delete coin object
		score += 10;
		cout << score << endl;
	}
	/*
	if (collision(player, flag))
	{
		// Change level
	}
	*/
	if (isFalling) { player->setDest(Vector2D(player->getDX(), player->getDY() + GRAVITY)); player->setCurrectAnimation(fall); }
	if (l) { if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_HORIZONTAL; } player->setDest(Vector2D(player->getDX() - speed, player->getDY())); }
	if (r) { if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_NONE; } player->setDest(Vector2D(player->getDX() + speed, player->getDY())); }
	if (u) { if (player->getCurrentAnimation() != jump) { player->setCurrectAnimation(jump); } player->setDest(Vector2D(player->getDX(), player->getDY() - jumpSpeed)); }
	//else { player.setCurrectAnimation(fall); }
	coin->updateAnimation();
	player->updateAnimation();
}

// Used to get user input to control player
void game::input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN) {

			// Change Screen size
			if (e.key.keysym.sym == SDLK_TAB) { isFullscreen = !isFullscreen; }

			// Quit game
			if (e.key.keysym.sym == SDL_QUIT) { running = false; }

			if (e.key.keysym.sym == SDLK_a) { l = true; r = false; }
			else if (e.key.keysym.sym == SDLK_d) { l = false; r = true; }
			else if (e.key.keysym.sym == SDLK_SPACE && isFalling == false) { u = true; isFalling = true; }

		}
		// Checks if user has stopped pressing a key
		if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_a) { l = false; player->setCurrectAnimation(idle); }
			if (e.key.keysym.sym == SDLK_d) { r = false; player->setCurrectAnimation(idle); }
			if (e.key.keysym.sym == SDLK_SPACE) { u = false; }
		}
	}
}

bool game::collision(object* a, object* b)
{
	if ((a->getDX() < (b->getDX() + b->getDW())) && ((a->getDX() + a->getDW()) > b->getDX()) && (a->getDY() < (b->getDY() + b->getDH())) && ((a->getDY() + a->getDH()) > b->getDY())) {
		return true;
	}
	else {
		return false;
	}
}

bool game::collisionTile(object* a, object b)
{
	if ((a->getDX() < (b.getDX() + b.getDW())) && ((a->getDX() + a->getDW()) > b.getDX()) && (a->getDY() < (b.getDY() + b.getDH())) && ((a->getDY() + a->getDH()) > b.getDY())) {
		return true;
	}
	else {
		return false;
	}
}