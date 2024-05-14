#pragma once
#include "spring.h"
#include "Body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

elSpring_t* elSprings = NULL;
int elSpringCount = 0;
Vector2 elGravity;

elSpring_t* CreateSpring(struct elBody* body1, struct elBody* body2, float restLength, float stiffness)
{
	elSpring_t* spring = (elSpring_t*)malloc(sizeof(elSpring_t));
	assert(spring != NULL);

	memset(spring, 0, sizeof(elSpring_t));

	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->stiffness = stiffness;

	return spring;
}

void AddSpring(elSpring_t* spring)
{
	assert(spring != NULL);

	spring->prev = NULL;
	spring->next = elSprings;

	if (elSprings != NULL) elSprings->prev = spring;

	elSprings = spring;

	elSpringCount++;
}

void DestroySpring(elSpring_t* spring)
{
	assert(spring != NULL);
	if (spring->prev != NULL) spring->prev->next = spring->next;
	if (spring->next != NULL) spring->next->prev = spring->prev;
	if (elSprings = spring) elSprings = spring->next;
	elSpringCount--;
	free(spring);
}

void ApplySpringForce(elSpring_t* springs)
{
	for (elSpring_t* spring = springs; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position); //<get direction vector from body2 to body1>
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction); //<get length from direction>
		float x = length - spring->restLength; //<compute displacement from current length to resting length>
		float force = -spring->stiffness * x; //<(f = -kx) compute force using product of displacement and stiffness(k)>

		Vector2 ndirection = Vector2Scale(Vector2Normalize(direction), force); //<get direction normal>

		ApplyForce(spring->body1, ndirection, Force);
		ApplyForce(spring->body2, Vector2Negate(ndirection), Force);
	}
}
