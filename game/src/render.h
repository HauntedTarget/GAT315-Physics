#pragma once
#include "raylib.h"
#include "raymath.h"

extern Vector2 elScreenSize;
extern float elScreenZoom;
extern float elViewSize;

Vector2 ConvertScreenToWorld(Vector2 screen);
Vector2 ConvertWorldToScreen(Vector2 world);
float ConvertWorldToPixel(float world);
