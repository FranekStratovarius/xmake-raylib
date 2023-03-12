#include "raylib.h"
#include <stdio.h>

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

const int screenWidth = 800;
const int screenHeight = 450;

Vector2 ballPosition = { -100.0f, -100.0f };
Color ballColor = DARKBLUE;

void UpdateDrawFrame(void);	 // Update and Draw one frame

int main(void) {
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60);
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	// Main game loop
	while (!WindowShouldClose()) {	// Detect window close button or ESC key
		UpdateDrawFrame();
	}
#endif

	CloseWindow();

	return 0;
}

void UpdateDrawFrame(void) {
    ballPosition = GetMousePosition();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ballColor = MAROON;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) ballColor = LIME;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) ballColor = DARKBLUE;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) ballColor = PURPLE;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA)) ballColor = YELLOW;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD)) ballColor = ORANGE;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_BACK)) ballColor = BEIGE;

	BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawCircleV(ballPosition, 40, ballColor);

		DrawText("move ball with mouse and click mouse button to change color", 10, 10, 20, DARKGRAY);

		// DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		char str[80];
		sprintf(str, "width: %d, height: %d", GetScreenWidth(), GetScreenHeight());
		DrawText(str, 190, 200, 20, LIGHTGRAY);

	EndDrawing();

	printf("width: %d, height: %d", GetScreenWidth(), GetScreenHeight());
}