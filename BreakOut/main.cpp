#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include<string>
#include <iostream>
#include<vector>
using namespace std;
using namespace sf;

class Block
{
public:
	Block() {

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
	void reset();
	void draw(RenderWindow* win);
	CircleShape theball;
	int radius;
	Vector2f loc;
	Vector2f speed;
	Texture ballOne;
};
Ball::Ball() {

	radius = 20;
	speed.x=0;
	speed.y = 0;
	loc.x = 0;
	loc.y=	0;
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
void Ball::reset() {
	theball.setPosition(loc);
	theball.setRadius(radius);
	this->theball.setTexture(&ballOne);
}

class Paddle {
public:
	Paddle();
	void draw(RenderWindow* win);
	Vector2f size;
	Vector2f loc;
	Vector2f speed;
	RectangleShape thispd;
};
Paddle::Paddle() {

	thispd.setSize(size);
	thispd.setPosition(loc);
}
void Paddle::draw(RenderWindow* win) {
	thispd.setPosition(Vector2f(locX, locY));
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
	Paddle PaddleP1;
	Block[]
	int point;
	//Buffrect buff;
};


Game::Game() : gamewindow(sf::VideoMode(500, 1000), "PONG") {
	Ball ball;
	Paddle Paddle;
}

void Game::run() {
	Time timer;
	Clock clock;
	ball.reset();
	while (gamewindow.isOpen()) {
		gamewindow.setFramerateLimit(80);
		timer = clock.restart();
		float dtAsSeconds = timer.asSeconds();
		processEvents(dtAsSeconds);
		update(dtAsSeconds);
		render();
	}
}

void Game::processEvents(float dt) {
	Event event;
	float pdspeed = 600 * dt;
	while (gamewindow.pollEvent(event)) {
		if ((event.type == Event::Closed) || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
			gamewindow.close();
		}
		else if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Escape) {
				gamewindow.close();
			}
			else if (event.key.code == Keyboard::Up) {
				if (PaddleP2.locY - pdspeed > 0)
					PaddleP2.locY -= pdspeed;
				else
					PaddleP2.locY = 0;
			}
			else if (event.key.code == Keyboard::Down) {
				if (PaddleP2.locY + pdspeed + PaddleP2.length < 600)
					PaddleP2.locY += pdspeed;
				else
					PaddleP2.locY = 600 - PaddleP2.length;
			}

		}
	}
}

void Game::update(float dtime) {

}
void Game::renderwin(int n) {

}

void Game::render() {
	Text text;
	gamewindow.clear();
	PaddleP1.draw(&gamewindow);
	PaddleP2.draw(&gamewindow);
	

	ball.draw(&gamewindow);

	gamewindow.draw(text);
	gamewindow.display();
}

int main(int argc, char* argv[]) {
	Game game;
	game.run();
	return 0;
}