#include <Windows.h>
#include "platform_common.cpp"

typedef unsigned int u32;

struct RenderState {
	int width;
	int height;

	void* memory;

	BITMAPINFO bitmapinfo;
};

bool running{ true };
static RenderState renderstate;

LRESULT CALLBACK window_callback(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
		LRESULT result{ 0 };

		switch (uMsg)
		{
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
			break;
		}

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			renderstate.width = rect.right - rect.left;
			renderstate.height = rect.bottom - rect.top;

			int buffer_size{ renderstate.width * renderstate.height * static_cast<int>(sizeof(u32)) };

			if (renderstate.memory) {
				VirtualFree(renderstate.memory, 0, MEM_RELEASE);
			}

			renderstate.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			renderstate.bitmapinfo.bmiHeader.biSize = sizeof(renderstate.bitmapinfo.bmiHeader);
			renderstate.bitmapinfo.bmiHeader.biHeight = renderstate.height;
			renderstate.bitmapinfo.bmiHeader.biWidth = renderstate.width;
			renderstate.bitmapinfo.bmiHeader.biPlanes = 1;
			renderstate.bitmapinfo.bmiHeader.biBitCount = 32;
			renderstate.bitmapinfo.bmiHeader.biCompression = BI_RGB;


			break;
		}


		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd) {
	//create window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"factor clock class";
	window_class.lpfnWndProc = window_callback;


	//register it
	RegisterClass(&window_class);

	//create window
	HWND window = CreateWindow(window_class.lpszClassName, L"Factor Clock", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	while (running) {
		//get inputs
		MSG message;

		Input input = {};

		float deltaTime = 0.01666f;
		LARGE_INTEGER frameBegin;
		QueryPerformanceCounter(&frameBegin);

		float performanceFrequency;
		{
			LARGE_INTEGER perf;
			QueryPerformanceFrequency(&perf);
			performanceFrequency = (float)perf.QuadPart;
		}

		for (int i = 0; i < BUTTON_COUNT; ++i) {
			input.buttons[i].changed = false;
		}


		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
				switch (message.message)
				{
				case WM_KEYUP:
				case WM_KEYDOWN: {
					u32 vk_code = (u32)message.wParam;
					bool is_down = ((message.lParam & (1 << 31)) == 0);

#define processButton(b, vk)\
case vk:{\
	input.buttons[b].isDown = is_down;\
	input.buttons[b].changed = true;\
} break;\

					switch (vk_code)
					{
						processButton(BUTTON_UP, VK_UP);
						processButton(BUTTON_DOWN, VK_DOWN);
						processButton(BUTTON_W, 'W');
						processButton(BUTTON_S, 'S');
						processButton(BUTTON_LEFT, VK_LEFT);
						processButton(BUTTON_RIGHT, VK_RIGHT);
						processButton(BUTTON_ENTER, VK_RETURN);

					case 'Q':
						running = false;
						break;
					}
				} break;

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				} break;
			}

		}
	}
}
