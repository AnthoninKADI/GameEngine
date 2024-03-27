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
        paddlePos({ 400, 720 }),
        paddleVelocity({ 10, 0 }),
        wallThickness(10),
        topWall(Rectangle()),
        rightWall(Rectangle()),
        leftWall(Rectangle())
    {}

public:
    bool initialize();
    void loop();
    void close();

private:
    void processInput();
    void update(float dt);
    void render(int numLines);
    std::vector<Rectangle> rectangles;

    bool isRunning;
    Window window;
    Renderer renderer;

    Rectangle topWall;
    Rectangle rightWall;
    Rectangle leftWall;
    const float wallThickness;

    Vector2 ballPos;
    Vector2 ballVelocity;
    const float ballSize = 10;

    Vector2 paddlePos;
    Vector2 paddleVelocity;
    const float paddleWidth = 100;
    const float paddleHeight = 20;
};

