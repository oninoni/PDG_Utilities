#include "stdafx.h"

#include "Time.h"
#include "InputManager.h"
#include "Window.h"
#include "Game.h"
#include "RenderingEngine.h"

#include "CoreEngine.h"

CoreEngine::CoreEngine(int width, int height, float framerate, Game* game) {
    this->game = game;

    this->width = width;
    this->height = height;
    this->frameDurationLimit = 1.0 / framerate;

    isRunning = false;
}

CoreEngine::~CoreEngine() {
    delete game;
    delete inputManager;
    delete window;

    delete renderingEngine;
}

void CoreEngine::createWindow(string title) {
    window = new Window(width, height, title);

    game->setCamera((float) width / (float) height);
    renderingEngine = new RenderingEngine(game->getCamera(), window);
    inputManager = new InputManager(this);
}

void CoreEngine::start() {
    if (isRunning)return;

    game->init(renderingEngine->getShaderHandler());

    run();
}

void CoreEngine::stop() {
    if (!isRunning)return;

    isRunning = false;
}

GLFWwindow* CoreEngine::getGLFWWindow() {
    return window->getGLFWWindow();
}

InputManager * CoreEngine::getInputManager() {
    return inputManager;
}

void CoreEngine::run() {
    isRunning = true;

    double lastTime = Time::getTime();

    int frames = 0;
    double frameTime = 0;
    double frameDuration = 0;

    while (isRunning) {
        double thisTime = Time::getTime();
        double deltaTime = thisTime - lastTime;
        lastTime = thisTime;

        glfwPollEvents();
        if (window->isCloseRequested())
            stop();

        Time::setDelta(deltaTime);
        inputManager->update();

        game->update(deltaTime, inputManager);

        renderingEngine->render(game->getRootGameObject());
        window->swapBuffers();

        frames++;
        frameTime += deltaTime;

        if (frameTime >= 1) {
            frameTime -= 1;
            window->setTitle("FPS: " + to_string(frames));
            frames = 0;
        }

        frameDuration = Time::getTime() - thisTime;
        if (frameDurationLimit > frameDuration) {
            Sleep((DWORD)((frameDurationLimit - frameDuration) * 1000));
        }
    }
}