struct ButtonState {
	bool isDown;
	bool changed;
};

enum ButtonsEnum {
	BUTTON_CTRL,

	BUTTON_COUNT
};

struct Input {
	ButtonState buttons[BUTTON_COUNT];
};
