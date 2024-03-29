#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Rectangle.h"
#include "Vector2.h"
#include <vector>

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

    Game() :
        isRunning(true),
        ballPos({ window.getWidth() / 2.f, window.getHeight() / 2.f }),
        ballVelocity({ 250, 250 }),
        paddlePos({ 949, 607 }),
        paddleVelocity({ 5, 5 }),
        wallThickness(10),
        topWall(Rectangle()),
        rightWall(Rectangle()),
        leftWall(Rectangle()),
        ballRect({ ballPos.x - ballSize / 2, ballPos.y - ballSize / 2, ballSize, ballSize }),
        paddleRect({ paddlePos.x, paddlePos.y, paddleWidth, paddleHeight }),
        finishLine({ 885, 440, 115, 10 }),
        topLimit({ 0, 0, 1024, 100 }),
        botLimit({ 0, 668, 1024, 100 }),
        rightLimit({ 999, 0, 25, 768 }),
        leftLimit({ 0, 0, 25, 768 }),
        limit1({ 150, 548, 1000, 20 }),
        limit2({ 150, 200, 20, 350 }),
        limit3({ 150, 200, 755, 20 }),
        limit4({ 885, 200, 20, 350 }),
        limit5({ 885, 450, 120, 100 }),
        limit6({ 150, 200, 755, 350 })
        {}

public:
    bool initialize();
    void loop();
    void load();
    void close();
    void removeRectangle(int index);

private:
    void processInput();
    void update(float dt);
    void render();
    std::vector<Rectangle> rectangles;
    void addRec(Rectangle recta);
    

    bool isRunning;
    Window window;
    Renderer renderer;

    Rectangle topWall;
    Rectangle rightWall;
    Rectangle leftWall;
    Rectangle finishLine;
    Rectangle paddleRect;
    const float wallThickness;

    Rectangle topLimit;
    Rectangle botLimit;
    Rectangle rightLimit;
    Rectangle leftLimit;
    Rectangle limit1;
    Rectangle limit2;
    Rectangle limit3;
    Rectangle limit4;
    Rectangle limit5;
    Rectangle limit6;

    Vector2 ballPos;
    Vector2 ballVelocity;
    const float ballSize = 10;
    Rectangle ballRect; 

    Vector2 paddlePos;
    Vector2 paddleVelocity;
    const float paddleWidth = 35;
    const float paddleHeight = 35;

    // Fonction de détection de collision
    bool checkCollision(const Rectangle& rect1, const Rectangle& rect2) const;
    bool checkCollisionWithLimits(const Rectangle& rect);
};
