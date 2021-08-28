static void fillScreen(u32 color) {
	u32* pixel = (u32*)renderstate.memory;
	for (int y = 0; y < renderstate.height; ++y) {
		for (int x = 0; x < renderstate.width; ++x) {
			*pixel++ = color;
		}
	}
}

static void drawRectPix(int x0, int y0, int x1, int y1, u32 color) {
	x0 = clamp(0, x0, renderstate.width);
	x1 = clamp(0, x1, renderstate.width);
	y0 = clamp(0, y0, renderstate.height);
	y1 = clamp(0, y1, renderstate.height);

	for (int y = y0; y < y1; ++y) {
		u32* pixel = (u32*)renderstate.memory + x0 + y * renderstate.width;

		for (int x = x0; x < x1; ++x) {
			*pixel++ = color;
		}
	}
}

static void drawRectFloat(float x, float y, float halfX, float halfY, u32 color) {
	x *= renderstate.height * 0.01;
	y *= renderstate.height * 0.01;
	halfX *= renderstate.height * 0.01;
	halfY *= renderstate.height * 0.01;

	x += renderstate.width / 2.f;
	y += renderstate.height / 2.f;

	int x0 = x - halfX;
	int x1 = x + halfX;
	int y0 = y - halfY;
	int y1 = y + halfY;

	drawRectPix(x0, y0, x1, y1, color);
}