#pragma once

typedef struct elSpring
{
	struct elBody* body1;
	struct elBody* body2;
	float restLength, stiffness;

	struct elSpring* next;
	struct elSpring* prev;

} elSpring_t;

extern elSpring_t* elSprings;

elSpring_t* CreateSpring(struct elBody* body1, struct elBody* body2, float restLength, float stiffness);
void AddSpring(elSpring_t* spring);
void DestroySpring(elSpring_t* spring);

void ApplySpringForce(elSpring_t* springs);