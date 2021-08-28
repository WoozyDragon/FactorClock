struct ButtonState {
	bool isDown;
	bool changed;
};

enum ButtonsEnum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_W,
	BUTTON_S,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ENTER,

	BUTTON_COUNT
};

struct Input {
	ButtonState buttons[BUTTON_COUNT];
};
