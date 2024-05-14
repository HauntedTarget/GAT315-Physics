#pragma once
#include "raylib.h"

typedef struct elEditorData {
	float massMinValue,
		massMaxValue,
		gravitationValue,
		objectGravity;
}elEditorData_t;

extern elEditorData_t elEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor(Vector2 position);

struct elBody* GetBodyIntersect(struct elBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct elBody* body, Vector2 position);