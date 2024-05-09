#include "Body.h"
#include "mathF.h"
#include "raylib.h"
#include "raymath.h"
#include "World.h"
#include "Force.h"
#include "Integrator.h"
#include "render.h"
#include "editor.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{
	InitWindow(elScreenSize.x, elScreenSize.y, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);

	// Init World
	elGravity = CreateVector2(0, -1);

	// Game Loop
	while (!WindowShouldClose())
	{
		// Update Logic
		float deltaTime = GetFrameTime(), 
			fps = (float)GetFPS();

		Vector2 m_Pos = GetMousePosition();
		elScreenZoom -= GetMouseWheelMove() * 0.2f;
		elScreenZoom = Clamp(elScreenZoom, 0.1f, INT_MAX);

		UpdateEditor(m_Pos);

		if (IsMouseButtonDown(0))
		{
			elBody* body = CreateBody();
			body->position = ConvertScreenToWorld(m_Pos);
			body->mass = GetRandomFloatValue(elEditorData.massMinValue, elEditorData.massMaxValue);
			body->iMass = 1 / body->mass;
			body->type = DYNAMIC;
			body->damping = 0;
			body->gravityScale = 0;
			body->color = WHITE;
			//ApplyForce(body, (Vector2) { GetRandomFloatValue(-200, 200), GetRandomFloatValue(-200, 200) }, Velocity);
		}

		// Apply force
		ApplyGravitation(elBodies, elEditorData.gravitationValue);

		// Update Bodies
		for (elBody* body = elBodies; body; body = body->next)
		{
			Step(body, deltaTime);
		}

		// Render
		BeginDrawing();
		ClearBackground(BLACK);

		// Draw Bodies
		for (elBody* body = elBodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle(screen.x, screen.y, ConvertWorldToPixel(body->mass), body->color);
		}

		DrawEditor();

		// Stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAMES: %.4f", deltaTime), 10, 30, 20, LIME);

		DrawCircleLines((int)m_Pos.x, (int)m_Pos.y, 10, YELLOW);

		EndDrawing();
	}
	CloseWindow();

	free(elBodies);

	return 0;
}