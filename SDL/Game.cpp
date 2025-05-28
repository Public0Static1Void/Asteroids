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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer error: " << Mix_GetError() << std::endl;
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
	player = new Player(540, 270, 32, 32, 3, 2, "Assets/asteroids_nave.png", fps);
	player->LoadSprites(renderer);

	// Asteroides ----------------------------------------------------------------------
	SpawnAsteroids(5);
}

void Game::SpawnAsteroids(int num) {
	if (asteroids.size() >= 25) return;

	for (int i = 0; i < num; i++) {
		int x = -128 + rand() % (1080 + 128);
		int y = rand() % 2;
		switch (y) {
		case 0:
			y = -20;
			break;
		case 1:
			y = 580;
			break;
		}
		float rand_speed = 0.5f + rand() % (1 + round);
		Asteroid* as = new Asteroid(x, y, 115 + rand() % 9, 115 + rand() % 9, rand_speed, 2, asteroid_paths[2], false);
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

	if (asteroids.size() <= 0) {
		round++;
		SpawnAsteroids(4 + round);

		count = 0;
	}


	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i]->updatePosition(player);

		if (asteroids[i]->checkCollision(player->pRect))
			isRunning = false;
		for (int j = 0; j < player->bullet_num; j++) {
			if (player->bullet[j]->render && asteroids[i]->checkCollision(player->bullet[j]->bullet_rect)) {
				player->bullet[j]->render = false;
				player->bullet[j]->SumY(1000);
				// El asteroide se podrá dividir en 1 o 2
				createAsteroid(2, asteroids[i]->size - 1, asteroids[i]);
				asteroids.erase(asteroids.begin() + i);

				score += 105;
				break;
			}
		}
	}
}

void Game::createAsteroid(int num, int size, Asteroid* parent) {
	if (parent == nullptr)
		return;

	cout << "Created more" << endl;

	int new_size = parent->size - 1;
	if (new_size < 0)
		return;
	int current_speed = static_cast<int>(parent->speed);
	if (current_speed <= 0) current_speed = 1;

	for (int i = 0; i < num; i++) {
		float new_speed = 0.5f + rand() % static_cast<int>(current_speed);

		Asteroid* as = new Asteroid(parent->getX(), parent->getY(), parent->asteroidRect->w / 1.5f, parent->asteroidRect->h / 1.5f, new_speed, new_size, asteroid_paths[new_size], true);
		if (as == nullptr) return;

		as->LoadSprites(renderer);
		as->SetDir(parent->GetDir().x + (-15 + rand() % 16), parent->GetDir().y + (-15 + rand() % 16));
		asteroids.push_back(as);
	}

	delete parent;
}

void Game::Render() {
	SDL_RenderClear(renderer);

	// Aquí se añadirán las cosas para dibujarlas

	player->Render(renderer);

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