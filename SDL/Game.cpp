#include "Game.h"
using namespace std;

SDL_Texture* playerTex;
SDL_Rect src_Rect, dst_Rect;


const char* asteroid_paths[] = {
	"Assets/asteroids_meteor_little.png",
	"Assets/asteroids_meteor_medium.png",
	"Assets/asteroids_meteor_large.png"
};

Game::Game() {
	timer = new Timer();
	count = 0;
	fps = 12;

	isRunning = false;
}
Game::~Game() {

}

void Game::InitGame(const char* title, int width, int height, bool fullScreen, int f_p_s) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // No se ha iniciado todo bien
		isRunning = false;
		return;
	}

	cout << "Init succesful." << endl;

	std::srand(std::time(0));

	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (window)
		cout << "Window created at Game.cpp" << endl;
	else
		cout << "Failed to create a window at Game.cpp" << endl;

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		cout << "Renderer created at Game.cpp" << endl;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else
		cout << "Renderer failed to create at Game.cpp" << endl;

	fps = f_p_s;
	framerate = (1000 / fps); // Tiempo a tener entre frames

	isRunning = true; // Se ha creado todo bien y por tanto empieza el juego


	// Cargar texturas
	SDL_Surface* tmpSurface = IMG_Load("Assets/asteroids_nave.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	// Player
	player = new Player(540, 270, 32, 32, 3, 2, "Assets/asteroids_nave.png");
	player->LoadSprites(renderer);

	// Asteroide ----------------------------------------------------------------------
	asteroid_mini = new Asteroid(-10, -10, 32, 32, 2, 1, "Assets/asteroids_meteor_little.png");
	asteroid_mini->LoadSprites(renderer);

	asteroid_mid = new Asteroid(1080, 550, 128, 64, 2, 2, "Assets/asteroids_meteor_medium.png");
	asteroid_mid->LoadSprites(renderer);

	SpawnAsteroids(5);
}

void Game::SpawnAsteroids(int num) {
	if (asteroids.size() >= 50) return;

	for (int i = 0; i < num; i++) {
		int x = rand() % 1080;
		int y = rand() % 1;
		switch (y) {
		case 0:
			y = -10;
			break;
		case 1:
			y = 560;
			break;
		}
		Asteroid* as = new Asteroid(x, y, 64, 64, 1 + round, 2, asteroid_paths[2]);
		as->LoadSprites(renderer);
		asteroids.push_back(as);
	}
}

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		cout << "Requested a game exit" << endl;
		break;
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

	int dir_x = 0;
	int dir_y = 0;
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		dir_y = -1;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		dir_y = 1;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		dir_x = 1;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		dir_x = -1;
	}

	player->Move(dir_x, dir_y, timer);

	if (currentKeyStates[SDL_SCANCODE_SPACE])
		player->Shoot();
}

void Game::Update() {
	count++;
	player->loop_count++;

	if (count > framerate * 100) {
		SpawnAsteroids(5 + round);
		round++;

		count = 0;
	}

	asteroid_mini->updatePosition(player);
	asteroid_mini->checkCollision(player->pRect);

	if (asteroid_mini->checkCollision(player->pRect))
	{
		isRunning = false; // gg
	}

	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i]->updatePosition(player);

		if (asteroids[i]->checkCollision(player->pRect))
			isRunning = false;
		for (int j = 0; j < player->bullet_num; j++) {
			if (asteroids[i]->checkCollision(player->bullet[j]->bullet_rect)) {
				player->bullet[j]->SumY(1000);
				createAsteroid(1, asteroids[i]->size - 1, asteroids[i]);
				asteroids.erase(asteroids.begin() + i);

				score += 105;
				break;
			}
		}
	}

	asteroid_mid->updatePosition(player);
}

void Game::createAsteroid(int num, int size, Asteroid* parent) {
	if (parent == nullptr)
		return;

	int new_size = parent->size - 1;
	if (new_size <= 0)
		return;

	for (int i = 0; i < num; i++) {
		Asteroid* as = new Asteroid(parent->getX(), parent->getY(), parent->asteroidRect->w / 1.5f, parent->asteroidRect->h / 1.5f, 1 + round, new_size, asteroid_paths[new_size]);
		
		if (as == nullptr) return;

		as->LoadSprites(renderer);
		asteroids.push_back(as);
	}
}

void Game::Render() {
	SDL_RenderClear(renderer);

	// Aquí se añadirán las cosas para dibujarlas

	player->Render(renderer);
	asteroid_mini->Render(renderer);
	asteroid_mid->Render(renderer);

	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i]->Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Game::Clear() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SaveScore(score);

	SDL_Quit();
	cout << "Game cleaned" << endl;
}

bool Game::Running() {
	return isRunning;
}

void Game::SaveScore(int score) {
	ofstream file("score.txt", std::ios::app);
	if (file.is_open()) {
		file << "Player Score: " << score << endl;
		file.close();
		cout << "Score saved successfully." << endl;
	}
	else {
		cerr << "Unable to open file to save score." << endl;
	}
}