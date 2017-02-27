#pragma once

class Window;
class InputManager;
class Game;
class RenderingEngine;

struct GLFWwindow;

class CoreEngine {
private:
    int width, height;
    double frameDurationLimit;

    Window* window;
    bool isRunning;

    InputManager* inputManager;
    Game* game;

    RenderingEngine* renderingEngine;

    void run();
public:
    CoreEngine(int width, int height, float framerate, Game* game);
    ~CoreEngine();

    void createWindow(string title);

    void start();
    void stop();

    GLFWwindow* getGLFWWindow();
    InputManager* getInputManager();
};