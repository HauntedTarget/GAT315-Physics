#include "World.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

elBody* elBodies = NULL;
int elBodyCount = 0;
Vector2 elGravity;

elBody* CreateBody()
{
	elBody* newBody = (elBody*)malloc(sizeof(elBody));
	assert(newBody != NULL);

	memset(newBody, 0, sizeof(elBody));

	newBody->prev = NULL;
	newBody->next = elBodies;
	if (elBodies != NULL) elBodies->prev = newBody;
	elBodies = newBody;
	elBodyCount++;
	return newBody;
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