#pragma once
#include "Body.h"

extern elBody* elBodies;
extern int elBodyCount;

elBody* CreateBody();
void DestroyBody(elBody* body);