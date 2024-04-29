#include "Body.h"
#include "mathF.h"
#include "raylib.h"
#include "raymath.h"
#include "World.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{
	InitWindow(800, 450, "Physics Engine");
	SetTargetFPS(60);

	// Game Loop
	while (!WindowShouldClose())
	{
		// Update Logic
		float deltaTime = GetFrameTime(), 
			fps = (float)GetFPS();

		Vector2 m_Pos = GetMousePosition();
		if (IsMouseButtonPressed(0))
		{
			Body* body = CreateBody();
			body->position = m_Pos;
			body->velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
		}

		// Render
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAMES: %.4f", deltaTime), 10, 30, 20, LIME);

		DrawCircleLines((int)m_Pos.x, (int)m_Pos.y, 10, YELLOW);

		// Update Bodies
		Body* body = bodies;
		for (int i = 0; i < bodyCount; i++)
		{
			body->position = Vector2Add(body->position, body->velocity);
			DrawCircle(body->position.x, body->position.y, 10, WHITE);

			body = body->next;
		}

		EndDrawing();
	}
	CloseWindow();

	free(bodies);

	return 0;
}