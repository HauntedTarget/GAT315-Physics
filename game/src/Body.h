#pragma once
#include <raylib.h>
#include <raymath.h>

typedef enum
{
	STATIC,
	KINEMATIC,
	DYNAMIC
}elBodyType;

typedef struct elBody
{
	elBodyType body;

	// force -> acceleration -> velocity -> position
	Vector2 position,
		velocity,
		force;

	float mass,
		iMass; // 1 / mass (static = 0)

	struct elBody* next;
	struct elBody* prev;
} elBody;

inline void ApplyForce(elBody* body, Vector2 force)
{
	body->force = Vector2Add(body->force, force);
}

inline void ClearForce(elBody* body)
{
	body->force = Vector2Zero();
}