#pragma once
#include "raylib.h"

typedef struct elEditorData {
	float massMinValue,
		massMaxValue,
		gravitationValue;
}elEditorData_t;

extern elEditorData_t elEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();