#include "contact.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

void AddContact(elContact_t* contact, elContact_t** contacts)
{
	assert(contact);

	// add element to linked list
	contact->next = *contacts;

	// set head of elements to new element
	*contacts = contact;
}

void DestroyAllContacts(elContact_t** contacts)
{
	if (!*contacts) return;

	elContact_t* contact = *contacts;
	while (contact)
	{
		elContact_t* next = contact->next;
		free(contact);
		contact = next;
	}

	*contacts = NULL;
}