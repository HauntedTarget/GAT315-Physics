#include "render.h"
#include "raymath.h"

Vector2 elScreenSize = { 800 , 450 };
float elScreenZoom = 1.0f;
float elViewSize = 25.0f;

Vector2 ConvertScreenToWorld(Vector2 screen)
{
	float ratio = elScreenSize.x / elScreenSize.y;
	Vector2 extents = (Vector2){ elViewSize * ratio, elViewSize };
	extents = Vector2Scale(extents, elScreenZoom);

	Vector2 lower = Vector2Negate(extents);
	Vector2 upper = extents;

	float nx = screen.x / elScreenSize.x;
	float ny = (elScreenSize.y - screen.y) / elScreenSize.y;

	Vector2 world;
	world.x = ((1 - nx) * lower.x) + (nx * upper.x);
	world.y = ((1 - ny) * lower.y) + (ny * upper.y);

	return world;
}

Vector2 ConvertWorldToScreen(Vector2 world)
{
	float ratio = elScreenSize.x / elScreenSize.y;
	Vector2 extents = (Vector2){ elViewSize * ratio, elViewSize };
	extents = Vector2Scale(extents, elScreenZoom);

	Vector2 lower = Vector2Negate(extents);
	Vector2 upper = extents;

	float nx = (world.x - lower.x) / (upper.x - lower.x);
	float ny = (world.y - lower.y) / (upper.y - lower.y);

	Vector2 screen;
	screen.x = nx * elScreenSize.x;
	screen.y = (1.0f - ny) * elScreenSize.y;

	return screen;
}

float ConvertWorldToPixel(float world)
{
	float ratio = elScreenSize.x / elScreenSize.y;
	Vector2 extents = (Vector2){ elViewSize * ratio, elViewSize };
	extents = Vector2Scale(extents, elScreenZoom);

	float nx = world / extents.x;
	float pixel = nx * elScreenSize.x;

	return pixel;
}
