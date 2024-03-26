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
    rightWall = { windowWidth - wallThickness, 0, wallThickness, static_cast<float>(windowHeight) };
    leftWall = { 0, 0, wallThickness, static_cast<float>(windowHeight) }; 

    return isWindowInit && isRendererInit;
}

void Game::loop()
{
    Timer timer;
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

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    // Déplacement continu du paddle de gauche à droite
    if (keyboardState[SDL_SCANCODE_LEFT])
    {
        paddlePos.x -= paddleVelocity.x;
        if (paddlePos.x < wallThickness)
            paddlePos.x = wallThickness;
    }
    else if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        paddlePos.x += paddleVelocity.x;
        if (paddlePos.x + paddleWidth > window.getWidth() - wallThickness)
            paddlePos.x = window.getWidth() - paddleWidth - wallThickness;
    }
}

void Game::update(float dt)
{
    ballPos += ballVelocity * dt;

    if (ballPos.y < wallThickness) 
    {
        ballVelocity.y *= -1; 
    }
    if (ballPos.x < wallThickness || ballPos.x > window.getWidth() - wallThickness)
    {
        ballVelocity.x *= -1;
    }

    // Collision avec le paddle
    if (ballPos.y + ballSize / 2 > paddlePos.y && ballPos.y - ballSize / 2 < paddlePos.y + paddleHeight &&
        ballPos.x + ballSize / 2 > paddlePos.x && ballPos.x - ballSize / 2 < paddlePos.x + paddleWidth)
    {
        ballVelocity.y *= -1;
    }

    // Réinitialisation 
    if (ballPos.y > window.getHeight())
    {
        ballPos = { window.getWidth() / 2.f, window.getHeight() / 2.f };
        ballVelocity = { 250, 250 };
    }
}

void Game::render()
{
    renderer.beginDraw();

    renderer.drawRect(topWall);
    renderer.drawRect(rightWall);
    renderer.drawRect(leftWall);

    Rectangle ballRect = { ballPos.x - ballSize / 2, ballPos.y - ballSize / 2, ballSize, ballSize };
    renderer.drawRect(ballRect);

    Rectangle paddleRect = { paddlePos.x, paddlePos.y, paddleWidth, paddleHeight };
    renderer.drawRect(paddleRect);

    renderer.endDraw();
}
