#include "Body.h"
#include "mathF.h"
#include "raylib.h"
#include "raymath.h"
#include "World.h"
#include "Force.h"
#include "Integrator.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{
	InitWindow(800, 450, "Physics Engine");
	SetTargetFPS(60);

	// Init World
	elGravity = CreateVector2(0, 0);

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
			body->iMass = 1 / body->mass;
			body->type = DYNAMIC;
			body->damping = 2.5f;
			body->gravityScale = 20;
			ApplyForce(body, (Vector2) { GetRandomFloatValue(-200, 200), GetRandomFloatValue(-200, 200) }, Velocity);
		}

		// Apply force
		ApplyGravitation(elBodies, 30);

		// Update Bodies
		for (elBody* body = elBodies; body; body = body->next)
		{
			Step(body, deltaTime);
		}

		// Render
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAMES: %.4f", deltaTime), 10, 30, 20, LIME);

		DrawCircleLines((int)m_Pos.x, (int)m_Pos.y, 10, YELLOW);

		// Draw Bodies
		for (elBody* body = elBodies; body; body = body->next)
		{
			DrawCircle(body->position.x, body->position.y, body->mass, WHITE);
		}

		EndDrawing();
	}
	CloseWindow();

	free(elBodies);

	return 0;
}