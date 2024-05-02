#pragma once
#include "Body.h"

inline void ExplicitEuler(elBody* body, float timeStep)
{
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timeStep));
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->accleration, timeStep));
}

inline void SemiImplicitEuler(elBody* body, float timeStep)
{
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->accleration, timeStep));
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timeStep));
}