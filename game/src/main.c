#include "Body.h"
#include "mathF.h"
#include "raylib.h"
#include "raymath.h"
#include "World.h"
#include "Integrator.h"

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
		if (IsMouseButtonDown(0))
		{
			elBody* body = CreateBody();
			body->position = m_Pos;
			body->mass = GetRandomFloatValue(1, 10);
		}

		// Apply force
		elBody* body = elBodies;
		for (int i = 0; i < elBodyCount; i++)
		{
			ApplyForce(body, CreateVector2(0, -100));
			
			body = body->next;
		}

		// Update Bodies
		body = elBodies;
		for (int i = 0; i < elBodyCount; i++)
		{
			ExplicitEuler(body, deltaTime);
			ClearForce(body);
			body = body->next;
		}

		// Render
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAMES: %.4f", deltaTime), 10, 30, 20, LIME);

		DrawCircleLines((int)m_Pos.x, (int)m_Pos.y, 10, YELLOW);

		// Draw Bodies
		body = elBodies;
		for (int i = 0; i < elBodyCount; i++)
		{
			DrawCircle(body->position.x, body->position.y, body->mass, WHITE);
			body = body->next;
		}

		EndDrawing();
	}
	CloseWindow();

	free(elBodies);

	return 0;
}