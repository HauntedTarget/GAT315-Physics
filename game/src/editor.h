#pragma once
#include "raylib.h"
#include "Body.h"

typedef struct elEditorData {
	float massValue,
		gravitationValue,
		objectGravity,
		resitution,
		dampening,
		stiffness;
	elBodyType selectedType;
}elEditorData_t;

extern elEditorData_t elEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor(Vector2 position);

struct elBody* GetBodyIntersect(struct elBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct elBody* body, Vector2 position);