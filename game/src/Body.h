#pragma once
#include <raylib.h>
#include <raymath.h>

typedef enum
{
	Force,
	Impulse,
	Velocity
}elForceMode;

typedef enum
{
	STATIC,
	KINEMATIC,
	DYNAMIC
}elBodyType;

typedef struct elBody
{
	elBodyType type;

	// force -> acceleration -> velocity -> position
	Vector2 position,
		velocity,
		force,
		accleration;

	Color color;

	float mass,
		iMass, // 1 / mass (static = 0)
		damping,
		gravityScale,

		restitution; 

	struct elBody* next;
	struct elBody* prev;
} elBody;

inline void ApplyForce(elBody* body, Vector2 force, elForceMode forceMode)
{
	if (body->type != DYNAMIC) return;

	switch (forceMode)
	{
		case Force:
			body->force = Vector2Add(body->force, force);
			
			break;
		case Impulse:
			body->velocity = Vector2Scale(force, body->iMass);

			break;
		case Velocity:
			body->velocity = force;

			break;
	}
}

inline void ClearForce(elBody* body)
{
	body->force = Vector2Zero();
}

void Step(elBody* body, float timeStep);