#pragma once
#include "Body.h"

extern elBody* elBodies;
extern int elBodyCount;
extern Vector2 elGravity;

elBody* CreateBody(Vector2 position, float mass, elBodyType bType, float restitution);
void AddBody(elBody* body);
void DestroyBody(elBody* body);