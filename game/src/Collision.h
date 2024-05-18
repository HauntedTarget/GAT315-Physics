#pragma once
#include "raylib.h"

typedef struct elContact elContact_t;
typedef struct elBody elBody;

void CreateContacts(elBody* bodies, elContact_t** contacts);
elContact_t* GenerateContact(elBody* body1, elBody* body2);

void SeparateContacts(elContact_t* contacts);
void ResolveContacts(elContact_t* contacts);