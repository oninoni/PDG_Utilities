#pragma once

class GameObject;
class Camera;
class ShaderHandler;

class Game {
private:
    Camera* camera;

    GameObject* root;
public:
    Game();
    virtual ~Game() = 0;

    virtual void init(ShaderHandler* shaderHandler);
    virtual void update(const double & delta, InputManager* input);

    void setCamera(float aspectRatio);

    GameObject* getRootGameObject();

    Camera* getCamera();
};

