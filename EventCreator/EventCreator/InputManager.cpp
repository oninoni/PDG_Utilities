#include "stdafx.h"

#include "CoreEngine.h"

#include "InputManager.h"

void InputManager::scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
    InputManager* inputManager = ((CoreEngine*)glfwGetWindowUserPointer(window))->getInputManager();
    if (yoffset != 0) {
        if (yoffset > 0) {
            inputManager->getScrollData()[IM_SCROLL_UP] = (int)yoffset;
        }
        else {
            inputManager->getScrollData()[IM_SCROLL_DOWN] = (int)yoffset;
        }
    }
}

int InputManager::getScroll(int keyCode) {
    if (keyCode == IM_SCROLL_DOWN || keyCode == IM_SCROLL_UP) {
        return scrollData[keyCode + 2];
    }
    return -1;
}

InputManager::InputManager(CoreEngine* mC) {
    window = mC->getGLFWWindow();

    glfwSetWindowUserPointer(window, mC);
    glfwSetScrollCallback(window, scroll_callback);

    bindDefaults();
}

InputManager::~InputManager() {
}

vec2 InputManager::getMousePos() {
    // sry wollte es testen und habs schnell selbst geschrieben...
    // du kannst es aber noch besser machen
    // ich würds machen, dass man ne möglichkeit hat rauszufinden ob sich der cursor bewegt hat
    // dann muss das laser-VAO nicht jeden frame geupdated werden
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    return vec2((float)x / w * 2 - 1, 1 - (float)y / h * 2);
}

void InputManager::bindKey(KeyAction keycode, int keyID) {
	keyBinds[keycode] = keyID;
    keyState[keycode] = false;
	keyStateOld[keycode] = false;
}

void InputManager::bindDefaults() {
    bindKey(kaForward, GLFW_KEY_W);
    bindKey(kaLeft, GLFW_KEY_A);
    bindKey(kaBack, GLFW_KEY_S);
    bindKey(kaRight, GLFW_KEY_D);
    bindKey(kaFirePrimary, GLFW_MOUSE_BUTTON_LEFT);
    bindKey(kaFireSecondary, GLFW_MOUSE_BUTTON_RIGHT);
    bindKey(kaReload, GLFW_KEY_R);
    bindKey(kaSpace, GLFW_KEY_SPACE);
    bindKey(kaShift, GLFW_KEY_LEFT_SHIFT);
}

void InputManager::update()  {
	for (int i = 0; i < KA_SIZE; i++) {
		keyStateOld[i] = keyState[i];
		keyState[i] = glfwGetKey(window, keyBinds[i]) == 1 || glfwGetMouseButton(window, keyBinds[i]) == 1;
	}
}

bool InputManager::keyPressed(KeyAction keycode) {
	return keyState[keycode] && !keyStateOld[keycode];
}

bool InputManager::keyReleased(KeyAction keycode) {
	return !keyState[keycode] && keyStateOld[keycode];
}

bool InputManager::keyDown(KeyAction keycode) {
	return keyState[keycode];
}

bool InputManager::keyUp(KeyAction keycode) {
	return !keyState[keycode];
}

int* InputManager::getScrollData() {
    return scrollData;
}
