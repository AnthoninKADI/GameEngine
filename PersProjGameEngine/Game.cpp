#include "Game.h"
#include "Timer.h"
#include <iostream>
using namespace std;

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowWidth = window.getWidth();
	int windowHeight = window.getHeight();
	topWall = { 0,0, static_cast<float>(windowWidth), wallThickness };
	bottomWall = { 0, windowHeight - wallThickness, static_cast<float>(windowWidth), wallThickness };
	rightWall = { windowWidth - wallThickness, 0, wallThickness, static_cast<float>(windowHeight) };

	return isWindowInit && isRendererInit; // Return bool && bool && .. to detect error
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	// Paddle move Left
	if (keyboardState[SDL_SCANCODE_Z])
	{
		paddleDirectionLeft = -1;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		paddleDirectionLeft = 1;
	}
	// Paddle move Right
	if (keyboardState[SDL_SCANCODE_UP])
	{
		paddleDirectionRight = -1;
	}
	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		paddleDirectionRight = 1;
	}
}

void Game::update(float dt)
{
	// Paddle move left
	paddlePosLeft += paddleVelocityLeft * dt * paddleDirectionLeft;
	if(paddlePosLeft.y < paddleHeight / 2 + wallThickness)
	{
		paddlePosLeft.y = paddleHeight / 2 + wallThickness;
	}
	if (paddlePosLeft.y > window.getHeight() - paddleHeight / 2 - wallThickness)
	{
		paddlePosLeft.y = window.getHeight() - paddleHeight / 2 - wallThickness;
	}

	// Paddle move right
	paddlePosRight += paddleVelocityRight * dt * paddleDirectionRight;
	if (paddlePosRight.y < paddleHeight / 2 + wallThickness)
	{
		paddlePosRight.y = paddleHeight / 2 + wallThickness;
	}
	if (paddlePosRight.y > window.getHeight() - paddleHeight / 2 - wallThickness)
	{
		paddlePosRight.y = window.getHeight() - paddleHeight / 2 - wallThickness;
	}

	//Ball move
	ballPos += ballVelocity * dt;
	if(ballPos.y < ballSize / 2 + wallThickness)
	{
		ballPos.y = ballSize / 2 + wallThickness;
		ballVelocity.y *= -1;
	}
	if(ballPos.x > window.getWidth() - ballSize / 2 - wallThickness)
	{
		ballPos.x = window.getWidth() - ballSize / 2 - wallThickness;
		ballVelocity.x *= -1;
	}

	// Ball-Paddle collision
	Vector2 leftDiff = ballPos - paddlePosLeft;
	if (fabsf(leftDiff.y) <= paddleHeight / 2
		&& fabsf(leftDiff.x) <= paddleWidth / 2 + ballSize / 2
		&& ballVelocity.x < 0)
	{
		ballVelocity.x *= -1;
		ballPos.x = paddlePosLeft.x + paddleWidth / 2 + ballSize / 2;
	}

	Vector2 rightDiff = ballPos - paddlePosRight;
	if (fabsf(rightDiff.y) <= paddleHeight / 2
		&& fabsf(rightDiff.x) <= paddleWidth / 2 + ballSize / 2
		&& ballVelocity.x < 0)
	{
		ballVelocity.x *= -1;
		ballPos.x = paddlePosRight.x + paddleWidth / 2 + ballSize / 2;
	}

	//Restart automatically
	if (ballPos.x < 0) {
		ballVelocity.x *= -1;
		ballPos.x = window.getWidth() / 2.f;
		ballPos.y = window.getHeight() / 2.f;
	}
	else if (ballPos.x > window.getWidth() - ballSize / 2) {
		ballVelocity.x *= -1;
		ballPos.x = window.getWidth() / 2.f;
		ballPos.y = window.getHeight() / 2.f;
	}
}

void Game::render()
{
	renderer.beginDraw();

	renderer.drawRect(topWall);
	renderer.drawRect(bottomWall);
	renderer.drawRect(rightWall);

	Rectangle ballRect = { ballPos.x - ballSize / 2, ballPos.y - ballSize / 2, ballSize, ballSize };
	renderer.drawRect(ballRect);

	Rectangle paddleRectLeft = { paddlePosLeft.x - paddleWidth / 2, paddlePosLeft.y - paddleHeight / 2, paddleWidth, paddleHeight };
	renderer.drawRect(paddleRectLeft);

	Rectangle paddleRectRight = { paddlePosRight.x - paddleWidth / 2, paddlePosRight.y - paddleHeight / 2, paddleWidth, paddleHeight };
	renderer.drawRect(paddleRectRight);

	renderer.endDraw();
}
