#include "Body.h"
#include "World.h"
#include "Integrator.h"

void Step(elBody* body, float timeStep)
{
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(elGravity, body->gravityScale), body->mass));
	body->accleration = Vector2Scale(body->force, body->iMass);

	SemiImplicitEuler(body, timeStep);

	// Apply Damping
	float damping = 1 / (1 + (body->damping * timeStep));
	body->velocity = Vector2Scale(body->velocity, damping);

	ClearForce(body);
}