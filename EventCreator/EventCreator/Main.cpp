#include "stdafx.h"

#include "CoreEngine.h"
#include "TestGame.h"

#include "PerspectiveCamera.h"

#include "LightHandler.h"
#include "DirectionalLight.h"

int main() {
    CoreEngine coreEngine(1920, 1080, 120, new TestGame());
    coreEngine.createWindow("Test");
    coreEngine.start();
}