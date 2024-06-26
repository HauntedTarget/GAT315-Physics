#include "Body.h"
#include "mathF.h"
#include "raylib.h"
#include "raymath.h"
#include "World.h"
#include "Force.h"
#include "Integrator.h"
#include "render.h"
#include "editor.h"
#include "Spring.h"
#include "contact.h"
#include "Collision.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{
	elBody* selectedBody = NULL;
	elBody* connectBody = NULL;
	elBody* editedBody = NULL;

	elContact_t* contacts = NULL;

	InitWindow((int)elScreenSize.x, (int)elScreenSize.y, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);

	float timeThing = 0;

	// Init World
	elGravity = CreateVector2(0, -1);

	// Game Loop
	while (!WindowShouldClose())
	{
		// Update Logic
		float deltaTime = GetFrameTime(),
			fps = (float)GetFPS(),
			fixedTime = 1 / elEditorData.timeStep;
		timeThing += deltaTime;

		Vector2 m_Pos = GetMousePosition();
		elScreenZoom -= GetMouseWheelMove() * 0.2f;
		elScreenZoom = Clamp(elScreenZoom, 0.1f, (float)INT_MAX);

		UpdateEditor(m_Pos);

		selectedBody = GetBodyIntersect(elBodies, m_Pos);
		if (selectedBody)
		{
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines((int)screen.x, (int)screen.y, ConvertWorldToPixel(selectedBody->mass * 0.5f) + 5, YELLOW);
		}

		// Create Body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_LEFT_SHIFT) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
		{
			if (!IsKeyDown(KEY_LEFT_CONTROL))
			{
				elBody* body = CreateBody(ConvertScreenToWorld(m_Pos),
					elEditorData.massValue,
					elEditorData.selectedType,
					elEditorData.resitution);
				body->damping = elEditorData.dampening;
				body->gravityScale = elEditorData.gravitationValue;
				body->color = WHITE;

				AddBody(body);
			}
		}

		// Edit Body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL))
		{
			editedBody = GetBodyIntersect(elBodies, m_Pos);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL))
		{
			editedBody = NULL;
		}

		if (editedBody)
		{
			Vector2 screen = ConvertWorldToScreen(editedBody->position);
			DrawCircleLines((int)screen.x, (int)screen.y, ConvertWorldToPixel(editedBody->mass * 0.5f) + 3, BLUE);

			editedBody->mass = elEditorData.massValue;
			editedBody->damping = elEditorData.dampening;
			editedBody->gravityScale = elEditorData.gravitationValue;
			editedBody->restitution = elEditorData.resitution;
		}

		// Delete Selected Body
		if (IsKeyPressed(KEY_DELETE) && selectedBody)
		{
			DestroyBody(selectedBody);
		}

		// Connect Spring
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody && !connectBody)
		{
			connectBody = selectedBody;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody)
		{
			DrawLineBodyToPosition(connectBody, m_Pos);
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody)
		{
			if (selectedBody && selectedBody != connectBody)
			{
				elSpring_t* spring = CreateSpring(connectBody, selectedBody, Vector2Distance(connectBody->position, selectedBody->position), elEditorData.stiffness);
				AddSpring(spring);
			}
			
			connectBody = NULL;
		}

		while (timeThing >= fixedTime)
		{
			timeThing -= fixedTime;

			// Apply force
			ApplyGravitation(elBodies, elEditorData.objectGravity);
			ApplySpringForce(elSprings);

			// Update Bodies
			for (elBody* body = elBodies; body; body = body->next)
			{
				Step(body, deltaTime);
			}

			// Collision
			CreateContacts(elBodies, &contacts);
			SeparateContacts(contacts);
			ResolveContacts(contacts);
		}
		
		// Render
		BeginDrawing();
		ClearBackground(BLACK);

		// Draw Springs
		for (elSpring_t* spring = elSprings; spring; spring = spring->next)
		{
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine(screen1.x, screen1.y, screen2.x, screen2.y, ORANGE);
		}

		// Draw Bodies
		for (elBody* body = elBodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass * 0.5f), body->color);
		}

		// Draw Contacts
		for (elContact_t* contact = contacts; contact; contact = contact->next)
		{
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircleLines((int)screen.x, (int)screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), RED);
		}

		DrawEditor(m_Pos);

		// Stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAMES: %.4f", deltaTime), 10, 30, 20, LIME);

		//DrawCircleLines((int)m_Pos.x, (int)m_Pos.y, 10, YELLOW);

		EndDrawing();
	}
	CloseWindow();

	free(elBodies);

	return 0;
}