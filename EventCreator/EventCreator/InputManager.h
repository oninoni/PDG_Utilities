#pragma once

class CoreEngine;

#define IM_SCROLL_UP -2
#define IM_SCROLL_DOWN -1

enum KeyAction {
	kaForward,
	kaBack,
	kaLeft,
	kaRight,
	kaFirePrimary,
	kaFireSecondary,
	kaReload,
    kaSpace,
    kaShift,

	KA_SIZE
};

class InputManager {
private:
	GLFWwindow* window;

	int keyBinds[KA_SIZE];
	bool keyStateOld[KA_SIZE];
	bool keyState[KA_SIZE];

    int scrollData[2];

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    int getScroll(int keyCode);
public:
    InputManager(CoreEngine* mC);
    ~InputManager();

    vec2 getMousePos();

	void bindKey(KeyAction keyaction, int keyID);
    void bindDefaults();

	void update();

	bool keyPressed(KeyAction keyaction);
	bool keyReleased(KeyAction keyaction);
	bool keyDown(KeyAction keyaction);
	bool keyUp(KeyAction keyaction);

    int* getScrollData();
};

