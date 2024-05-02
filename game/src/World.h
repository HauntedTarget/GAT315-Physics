#pragma once
#include "Body.h"

extern elBody* elBodies;
extern int elBodyCount;
extern Vector2 elGravity;

elBody* CreateBody();
void DestroyBody(elBody* body);