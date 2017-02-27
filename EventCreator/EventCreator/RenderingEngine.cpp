#include "stdafx.h"

#include "PhongShader.h"
#include "ShadowmapShader.h"

#include "GameObject.h"
#include "Camera.h"

#include "LightHandler.h"
#include "ShaderHandler.h"
#include "Window.h"

#include "UniformBufferObject.h"

#include "TextureArrayFramebuffer.h"

#include "RenderingEngine.h"

RenderingEngine::RenderingEngine(Camera* camera, Window* window) {
    initGraphics();
    cout << getOpenGLVersion() << endl;

    lightHandler = new LightHandler();
    shaderHandler = new ShaderHandler();
    
    this->camera = camera;
    this->window = window;
}

RenderingEngine::~RenderingEngine() {
}

void RenderingEngine::render(GameObject * root) {
    lightHandler->renderShadowmaps(shaderHandler, root);

    window->bindAsRenderTarget();
    clearScreen();

    lightHandler->bindShader(shaderHandler->getPhongShader());
    root->preRender(shaderHandler, lightHandler);
    root->render(shaderHandler, camera);
}

ShaderHandler * RenderingEngine::getShaderHandler() {
    return shaderHandler;
}

void RenderingEngine::clearScreen() {
    //TODO Stencil Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingEngine::initGraphics() {
    glClearColor(0, 0, 0, 0);

    // Clockwise is front
    glFrontFace(GL_CCW);

    //Culling Back
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    //Enable z component on render result
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEPTH_CLAMP);

    glEnable(GL_MULTISAMPLE);
}

const char* RenderingEngine::getOpenGLVersion() {
    return (char*)glGetString(GL_VERSION);
}

void RenderingEngine::setClearColor(vec4 color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

inline void RenderingEngine::setClearColor(vec3 color) {
    glClearColor(color.r, color.g, color.b, 1.0);
}