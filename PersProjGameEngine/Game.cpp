#include "Game.h"
#include "Timer.h"
#include <iostream>
using namespace std;

bool Game::initialize()
{
    bool isWindowInit = window.initialize();
    bool isRendererInit = renderer.initialize(window);

    return isWindowInit && isRendererInit;
}

void Game::loop()
{
    Timer timer;
    int numLines = 9; // Nombres de lignes 
    while (isRunning)
    {
        float dt = timer.computeDeltaTime() / 1000.0f;
        processInput();
        update(dt);
        render(numLines); 
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
void Game::render(int numLines)
{
    renderer.beginDraw();

    Rectangle paddleRect = { paddlePos.x, paddlePos.y, paddleWidth, paddleHeight };
    renderer.drawRect(paddleRect);

    Rectangle ballRect = { ballPos.x - ballSize / 2, ballPos.y - ballSize / 2, ballSize, ballSize };
    renderer.drawRect(ballRect);


    int rectWidth = 90; 
    int rectHeight = 20; 
    int spacing = 2; 
    int paddingVertical = 4; 

    int windowWidth = window.getWidth();
    int windowHeight = window.getHeight();

    int numRectanglesPerRow = (windowWidth - 8) / (rectWidth + spacing); 
    int numRectanglesTotal = numRectanglesPerRow * numLines; 

    int startX = 4; 
    int startY = paddingVertical; 

    for (int i = 0; i < numRectanglesTotal; ++i)
    {
        
        int rowIndex = i / numRectanglesPerRow;
        int columnIndex = i % numRectanglesPerRow;
        int x = startX + columnIndex * (rectWidth + spacing);
        int y = startY + rowIndex * (rectHeight + paddingVertical);

        Rectangle rect = { x, y, rectWidth, rectHeight }; 
        renderer.drawRect(rect); 
    }

    renderer.endDraw();
}
