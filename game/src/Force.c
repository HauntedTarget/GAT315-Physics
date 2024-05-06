#include "Force.h"
#include "Body.h"

void ApplyGravitation(elBody* bodies, float strength)
{
	for (elBody* body1 = bodies; body1; body1 = body1->next)
	{
		for (elBody* body2 = bodies; body2; body2 = body2->next)
		{
			if (body1 == body2) continue;

			Vector2 direction = Vector2Subtract(body2->position, body1->position); 
			float distance = Vector2Length(direction);

			distance = fmaxf(1, distance);
			float force = (body1->mass * body2->mass / (distance * distance)) * strength;

			direction = Vector2Scale(Vector2Normalize(direction), force);

			ApplyForce(body1, direction, Force);
			ApplyForce(body2, Vector2Negate(direction), Force);
		}
	}
}