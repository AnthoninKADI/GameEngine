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
        ballRect({ ballPos.x - ballSize / 2, ballPos.y - ballSize / 2, ballSize, ballSize })
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
    const float wallThickness;

    Vector2 ballPos;
    Vector2 ballVelocity;
    const float ballSize = 10;
    Rectangle ballRect; // Rectangle pour représenter la boîte de collision du cube

    Vector2 paddlePos;
    Vector2 paddleVelocity;
    const float paddleWidth = 35;
    const float paddleHeight = 35;

    // Fonction de détection de collision
    bool checkCollision(const Rectangle& rect1, const Rectangle& rect2) const;
};
