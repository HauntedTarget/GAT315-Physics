#pragma once
#include "raylib.h"

typedef struct elContact
{
	struct elBody* body1;
	struct elBody* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct elContact* next;
} elContact_t;

void AddContact(elContact_t* contact, elContact_t** contacts);
void DestroyAllContacts(elContact_t** contacts);
