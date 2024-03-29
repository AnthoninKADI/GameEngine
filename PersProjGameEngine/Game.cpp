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

void Game::load()
{

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

    if (keyboardState[SDL_SCANCODE_UP])
    {
        paddlePos.y -= paddleVelocity.y;
        if (paddlePos.y < wallThickness)
            paddlePos.y = wallThickness;
    }

    else if (keyboardState[SDL_SCANCODE_DOWN])
    {
        paddlePos.y += paddleVelocity.y;
        if (paddlePos.y + paddleHeight > window.getHeight() - wallThickness)
            paddlePos.y = window.getHeight() - paddleHeight - wallThickness;
    }
}

void Game::update(float dt)
{
    if (checkCollisionWithLimits(paddleRect)) 
    {
        cout << "Collision avec " << endl;
    }

    paddleRect.x = paddlePos.x;
    paddleRect.y = paddlePos.y;

    // Collision avec la ligne de fin
    if (checkCollision(paddleRect, finishLine)) {
        paddlePos = { 949, 607 };
        paddleRect.x = paddlePos.x; 
        paddleRect.y = paddlePos.y;
    }
}

bool Game::checkCollision(const Rectangle& rect1, const Rectangle& rect2) const
{
    return (rect1.x < rect2.x + rect2.width &&
        rect1.x + rect1.width > rect2.x &&
        rect1.y < rect2.y + rect2.height &&
        rect1.y + rect1.height > rect2.y);
}

void Game::removeRectangle(int index)
{
    if (index >= 0 && index < rectangles.size()) {
        rectangles.erase(rectangles.begin() + index);
    }
}

void Game::render()
{
    renderer.beginDraw();

    Rectangle paddleRect = { paddlePos.x, paddlePos.y, paddleWidth, paddleHeight };
    renderer.drawPaddle(paddleRect, 255, 255, 255, 255);

    // Track Limit
    Rectangle topLimit = { 0, 0, 1024, 100 };
    renderer.drawRect(topLimit);

    Rectangle botLimit = { 0, 668, 1024, 100 };
    renderer.drawRect(botLimit);

    Rectangle leftLimit = { 0, 0, 25, 768 };
    renderer.drawRect(leftLimit);

    Rectangle rightLimit = { 999, 0, 25, 768 };
    renderer.drawRect(rightLimit);

    // Start & Finish Line
    Rectangle finishLine = { 885, 440, 115, 10 };
    renderer.drawPaddle(finishLine, 255, 0, 0, 255);

    Rectangle startLine = { 989, 568, 10, 100 };
    renderer.drawPaddle(startLine, 0, 255, 0, 255);

    // Interior Track Limit
    Rectangle limit1 = { 150, 548, 1000, 20 };
    renderer.drawRect(limit1);

    Rectangle limit2 = { 150, 200, 20, 350 };
    renderer.drawRect(limit2);

    Rectangle limit3 = { 150, 200, 755, 20 };
    renderer.drawRect(limit3);

    Rectangle limit4 = { 885, 200, 20, 350 };
    renderer.drawRect(limit4);

    Rectangle limit5 = { 885, 450, 120, 100 };
    renderer.drawRect(limit5);

    Rectangle limit6 = { 150, 200, 755, 350 };
    renderer.drawRect(limit6);

    for (auto rect : rectangles)
    {
        renderer.drawRect(rect);
    }

    renderer.endDraw();
}

void Game::addRec(Rectangle recta)
{
    rectangles.emplace_back(recta);
}

bool Game::checkCollisionWithLimits(const Rectangle& rect)
{
    if (checkCollision(rect, topWall) ||
        checkCollision(rect, botLimit) ||
        checkCollision(rect, rightLimit) ||
        checkCollision(rect, leftLimit) ||
        checkCollision(rect, limit1) ||
        checkCollision(rect, limit2) ||
        checkCollision(rect, limit3) ||
        checkCollision(rect, limit4) ||
        checkCollision(rect, limit5) ||
        checkCollision(rect, limit6))
    {
        return true; 
    }

    return false; 
}