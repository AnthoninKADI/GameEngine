#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game():
		isRunning(true),
		ballPos({100, 100}),
		ballVelocity({500, 500}),
		paddlePosLeft({50, 100}), //Left paddle
		paddleVelocityLeft({0, 450}),
		paddleDirectionLeft(0),
		paddlePosRight({950, 100}), //Right paddle
		paddleVelocityRight({0, 450}),
		paddleDirectionRight(0),	
		wallThickness(10),
		topWall(Rectangle()),
		bottomWall(Rectangle()),
		rightWall(Rectangle())
	{}

public:
	bool initialize();
	void loop();
	void close();

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;

	Rectangle topWall;
	Rectangle bottomWall;
	Rectangle rightWall;
	const float wallThickness = 10;

	Vector2 ballPos;
	Vector2 ballVelocity;
	const float ballSize = 10;

	Vector2 paddlePosLeft;
	Vector2 paddleVelocityLeft;
	float paddleDirectionLeft;
	
	Vector2 paddlePosRight;
	Vector2 paddleVelocityRight;
	float paddleDirectionRight;

	const float paddleWidth = 10;
	const float paddleHeight = 64;
	
};

