#include <SFML/Graphics.hpp>
#include <sstream>
#include<string>
#include <iostream>
#include<vector>
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  
using namespace std;
using namespace sf;
float dtAsSeconds;
class Block
{
public:
	Block() {
		blockHP = 1;
		blockType = 0;
	}
	int Hitted() {
		blockHP -= 1;
		if (blockHP == 0)
		{
			Destroy();
		}
	}
	void Destroy() {

	}
	void Show(RenderWindow *win) {

	}
	Sprite block;
	int blockHP;
	int blockType;
	Vector2i pos;
};

class Ball {
public:
	Ball();
	void start();
	void draw(RenderWindow* win);
	CircleShape theball;
	float radius;
	Vector2f loc;
	Vector2f speed;
	Texture ballOne;
};
Ball::Ball() {

	radius = 20;
	speed.x=0;
	speed.y = 0;
	loc.x = 250 - radius;
	loc.y = 1000 - 30 - 20 - 2*radius;
	CircleShape theball(radius);
	this->theball.setPosition(loc);
	if (!ballOne.loadFromFile("images/ball.png"))
	{
		std::cerr << "ball texture failed!";
	}
	ballOne.loadFromFile("images/ball.png");
	ballOne.setSmooth(true);

}

void Ball::draw(RenderWindow* win) {
	theball.setPosition(loc);
	theball.setRadius(radius);
	this->theball.setTexture(&ballOne);
	win->draw(theball);
}
void Ball::start() {
	float spd = 100;
	speed.x = spd*sin(0.5)* dtAsSeconds;
	speed.y = -spd*cos(0.5) * dtAsSeconds;
}

class Paddle {
public:
	Paddle()
	{
		size.x = (100);
		size.y = 20;
		loc.x = 250 - size.x / 2;
		loc.y = 1000 - 30 - size.y;
		RectangleShape thispd;
		thispd.setPosition(loc);
	};
	void draw(RenderWindow* win);
	Vector2f size;
	Vector2f loc;
	RectangleShape thispd;
	void moveleft(float speed) {
		if (loc.x- speed > 0)
			loc.x-=speed;
		else
			return;
	}
	void moveright(float speed) {
		if (loc.x + speed < 500 - size.x)
			loc.x +=speed;
		else
			return;
	}
	
};

void Paddle::draw(RenderWindow* win) {
	thispd.setPosition(loc);
	thispd.setSize(size);
	thispd.setFillColor(Color::Blue);
	win->draw(thispd);
}

class Game {
public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game();
	void run();
	void processEvents(float);
	void update(float);
	void render();
	void renderwin(int);
	RenderWindow gamewindow;
	Ball ball;
	Paddle Paddle;
	int gamestate = 0;// 0 for wait 1 for run 2 for end;
	Block map[5][10][10];
	Vector2f dloc;
	int point;
	//Buffrect buff;
};


Game::Game() : gamewindow(sf::VideoMode(500, 1000), "PONG") {
	Ball ball;
	//Paddle;
	dloc = ball.loc - Paddle.loc;
	point = 0;
}

void Game::run() {
	Time timer;
	Clock clock;
	while (gamewindow.isOpen()) {
		gamewindow.setFramerateLimit(288);
		timer = clock.restart();
		processEvents(dtAsSeconds);
		update(dtAsSeconds);
		render();
		dtAsSeconds = timer.asSeconds();
	}
}

void Game::processEvents(float dt) {
	Event event;
	float pdspeed = 1000 * dt;
	while (gamewindow.pollEvent(event)) {
		if ((event.type == Event::Closed) || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
			gamewindow.close();
		}
		else if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Escape) {
				gamewindow.close();
			}
			else if (event.key.code == Keyboard::Space) {
				gamestate = 1;
				ball.start();
			}
			else if (event.key.code == Keyboard::Left) {
				Paddle.moveleft(pdspeed);
			}
			else if (event.key.code == Keyboard::Right) {
				Paddle.moveright(pdspeed);
			}

		}
	}
}

void Game::update(float dtime) {
	if (gamestate == 0) {
		ball.loc = Paddle.loc+dloc;
	}
	if (gamestate == 1) {
		ball.loc+=ball.speed;
	}
}
void Game::renderwin(int n) {

}

void Game::render() {
	Text text;
	gamewindow.clear();
	Paddle.draw(&gamewindow);
	ball.draw(&gamewindow);
	gamewindow.draw(text);
	gamewindow.display();
}

int main() {
	Game game;
	game.run();
	return 0;
}