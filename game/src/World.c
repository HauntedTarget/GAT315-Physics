#include "World.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

elBody* elBodies = NULL;
int elBodyCount = 0;
Vector2 elGravity;

elBody* CreateBody(Vector2 position, float mass, elBodyType bType)
{
	elBody* body = (elBody*)malloc(sizeof(elBody));
	assert(body != NULL);

	memset(body, 0, sizeof(elBody));

	body->position = position;
	body->mass = mass;
	body->iMass = (bType == DYNAMIC) ? 1 / mass : 0;
	body->type = bType;

	return body;
}

void AddBody(elBody* body)
{
	assert(body != NULL);

	body->prev = NULL;
	body->next = elBodies;

	if (elBodies != NULL) elBodies->prev = body;

	elBodies = body;

	elBodyCount++;
}

void DestroyBody(elBody* body)
{
	assert(elBodies != NULL);
	if (body->prev != NULL) body->prev->next = body->next;
	if (body->next != NULL) body->next->prev = body->prev;
	if (elBodies = body) elBodies = body->next;
	elBodyCount--;
	free(body);
}