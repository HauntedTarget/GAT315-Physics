#pragma once
#include "Collision.h"
#include "contact.h"
#include "Body.h"
#include "mathF.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

static bool Intersects(elBody* body1, elBody* body2)
{
	//if distance <= radius
	float distance = Vector2Distance(body1->position, body2->position);
	float radius = body1->mass + body2->mass;

	return (distance <= radius + EPSILON);
}

void CreateContacts(elBody* bodies, elContact_t** contacts)
{
	for (elBody* body1 = bodies; body1; body1 = body1->next)
	{
		for (elBody* body2 = body1->next; body2; body2 = body2->next)
		{
			if (body1 == body2) continue;

			if (body1->type != DYNAMIC && body2->type != DYNAMIC) continue;

			if (Intersects(body1, body2))
			{
				elContact_t* contact = GenerateContact(body1, body2);
				AddContact(contact, contacts);
			}
		}
	}
}

elContact_t* GenerateContact(elBody* body1, elBody* body2)
{
	elContact_t* contact = (elContact_t*)malloc(sizeof(elContact_t));
	assert(contact);

	memset(contact, 0, sizeof(elContact_t));

	contact->body1 = body1;
	contact->body2 = body2;

	Vector2 direction = Vector2Subtract(body1->position, body2->position);
	float distance = Vector2Length(direction);
	if (distance == 0)
	{
		direction = (Vector2){ GetRandomFloatValue(-0.05f, 0.05f), GetRandomFloatValue(-0.05f, 0.05f) };
	}

	float radius = (body1->mass + body2->mass);

	contact->depth = radius - distance;
	contact->normal = Vector2Normalize(direction);
	contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

	return contact;
}

void SeparateContacts(elContact_t* contacts)
{
	for (elContact_t* contact = contacts; contact; contact = contact->next)
	{
		float separationImpulse = contact->depth * 0.5f; // Separate by half the depth
		Vector2 separationVector = Vector2Scale(contact->normal, separationImpulse);

		if (contact->body1->type == DYNAMIC)
			contact->body1->position = Vector2Add(contact->body1->position, separationVector);
		if (contact->body2->type == DYNAMIC)
			contact->body2->position = Vector2Subtract(contact->body2->position, separationVector);
	}
}

void ResolveContacts(elContact_t* contacts)
{
	for (elContact_t* contact = contacts; contact; contact = contact->next)
	{
		Vector2 relativeVelocity = Vector2Subtract(contact->body1->velocity, contact->body2->velocity);
		float normalVelocity = Vector2DotProduct(relativeVelocity, contact->normal);
		if (normalVelocity > 0) continue;

		float impulseMagnitude = -(1 + contact->restitution) * normalVelocity / (contact->body1->iMass + contact->body2->iMass);
		Vector2 impulse = CreateVector2(contact->normal.x * impulseMagnitude, contact->normal.y * impulseMagnitude);

		ApplyForce(contact->body1, impulse, Impulse);
		ApplyForce(contact->body2, Vector2Negate(impulse), Impulse);
	}
}