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
    //int rectWidth = 90;
    //int rectHeight = 20;
    //int spacing = 2;
    //int paddingVertical = 4;
    //int numLines = 1; // Nombres de lignes 

    //int windowWidth = window.getWidth();
    //int windowHeight = window.getHeight();

    //int numRectanglesPerRow = (windowWidth - 8) / (rectWidth + spacing);
    //int numRectanglesTotal = numRectanglesPerRow * numLines;

    //int startX = 4;
    //int startY = paddingVertical;

    //for (int i = 0; i < numRectanglesTotal; ++i)
    //{

    //    int rowIndex = i / numRectanglesPerRow;
    //    int columnIndex = i % numRectanglesPerRow;
    //    int x = startX + columnIndex * (rectWidth + spacing);
    //    int y = startY + rowIndex * (rectHeight + paddingVertical);

    //    Rectangle rect = { x, y, rectWidth, rectHeight };
    //    
    //    addRec(rect);
    //}
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
    for (size_t i = 0; i < rectangles.size(); ++i) {
        const auto& rect = rectangles[i];
        if (ballPos.y + ballSize / 2 > rect.y && ballPos.y - ballSize / 2 < rect.y + 20 &&
            ballPos.x + ballSize / 2 > rect.x && ballPos.x - ballSize / 2 < rect.x + 90)
        {
            cout << "Collision avec le rectangle à l'index " << i << endl;
            ballVelocity.y *= -1;
            removeRectangle(i);
            break;
        }
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
    renderer.drawPaddle(paddleRect, 0, 255, 255, 255);

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
