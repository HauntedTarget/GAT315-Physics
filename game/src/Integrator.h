#pragma once
#include "Body.h"

void ExplicitEuler(elBody* body, float timeStep)
{
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timeStep));
	body->velocity = Vector2Add(body->velocity, Vector2Scale(Vector2Scale(body->force, 1/body->mass), timeStep));
}

void SemiImplicitEuler(elBody* body, float timeStep)
{
	body->velocity = Vector2Add(body->velocity, Vector2Scale(Vector2Scale(body->force, 1 / body->mass), timeStep));
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timeStep));
}